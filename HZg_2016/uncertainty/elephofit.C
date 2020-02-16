#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
/*
  #include "flashggFinalFit/Background/interface/PdfModelBuilder.h"
  #include <Math/PdfFuncMathCore.h>
  #include <Math/ProbFunc.h>
  #include <iomanip>
  //#include "boost/program_options.hpp"
  #include "boost/algorithm/string/split.hpp"
  #include "boost/algorithm/string/classification.hpp"
  #include "boost/algorithm/string/predicate.hpp"

  //#include "boost/program_options.hpp"
  #include "boost/lexical_cast.hpp"
*/
#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooDecay.h>

#include "RooAddModel.h"

#include <RooNumConvPdf.h>
#include <RooFFTConvPdf.h>
#include <iostream>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "../../plugin/tdrstyle.C"
#include "../../plugin/CMS_lumi.C"

#include "TTree.h"
#include "TLegend.h"
#include "TFrame.h"
#include "RooFitResult.h"

using namespace RooFit ;

void SetConstantParams(const RooArgSet* params)
{
  // set constant parameters for signal fit, ... NO IDEA !!!!
  TIterator* iter(params->createIterator());
  for (TObject *a = iter->Next(); a != 0; a = iter->Next())
    {
      RooRealVar *rrv = dynamic_cast<RooRealVar *>(a);
      if (rrv)
        {
	  rrv->setConstant(true);
	  std::cout << " " << rrv->GetName();
	} // close set const parameters
    }
}
TTree* makeTTree_signal(string fname)
{
  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
  // gSystem->Load("libBackgroundProfileFitting");
  Double_t* mH = new Double_t;
  Double_t* weights = new Double_t;
  TTree *T1 = new TTree("T1", "data from ascii file");
  T1->Branch("mH", &mH, "mH/D"); // The branch name is m
  T1->Branch("weights", &weights, "weights/D");
  T1->ReadFile(fname.c_str(), "mH:weights");
  return T1 ;
}
TTree* makeTTree(string fname)
{
  // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y

  Double_t* mH = new Double_t;
  Double_t* weights = new Double_t;
  TTree *T1 = new TTree("T1", "data from ascii file");
  T1->Branch("mH", &mH, "mH/D"); // The branch name is m
  T1->ReadFile(fname.c_str(), "mH");
  return T1 ;
}

//code for making txt file
void make_Sig(int set1 = 0, int member1 = 0, string channel = "ttH")
{
  char inpathmu3[700],inpathmu4[700];
  //input file 
  TChain ch("tZg");//chain as one file
  if(channel =="WH")
    {
      sprintf(inpathmu3, "/home/mingyan/output/mc/uncertainty/muon/mc_Moriond17_updatexxxx_mucorr%d_mu_HZg_WplusH*_125GeV_%d.root",set1,  member1);
      sprintf(inpathmu4, "/home/mingyan/output/mc/uncertainty/muon/mc_Moriond17_updatexxxx_mucorr%d_mu_HZg_WminusH*_125GeV_%d.root",set1,  member1);
      ch.Add(inpathmu3);
      ch.Add(inpathmu4);
    }
  else
    {
      sprintf(inpathmu3, "/home/mingyan/output/mc/uncertainty/muon/mc_Moriond17_updatexxxx_mucorr%d_mu_HZg_%s*_125GeV_%d.root",set1, channel.c_str(), member1);
    
      ch.Add(inpathmu3);
    }    
  char outpath[500];
  sprintf(outpath,"/afs/cern.ch/work/m/milee/HtoZG/MYcode/uncertainty/muon/txt/mucorr_set%s_%d_member%d.txt",channel.c_str() ,set1,member1);
  ofstream sig(outpath);

  Int_t run_,lumis_, cat;
  Long64_t  event_;
  Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,totwei;
  ch.SetBranchAddress("cat",      &cat);
  ch.SetBranchAddress("puwei",    &puwei_);
  ch.SetBranchAddress("genwei",   &genwei_);
  ch.SetBranchAddress("mcwei",    &mcwei_);
  ch.SetBranchAddress("totSF",    &totSF_);
  ch.SetBranchAddress("mllg",    &mllg_);
  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
      if(cat<6&&cat>9) continue;
      if(genwei_<0) genwei_= genwei_*-1.;
      totwei = mcwei_*totSF_*puwei_;
      sig<<mllg_<<" "<<totwei<<endl;
    }
  ch.SetAutoDelete(kTRUE);
}
//making txt file end

void fit(string tree , float *mean, float *sigma)
{
  TTree* SigTree1 = makeTTree_signal(tree);
  ///define variables for fitting
  RooRealVar mH("mH", "mH", 115, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///build unbin data&signal distribution
  RooDataSet signal_2016("signal_2016", " ", RooArgSet(mH, weights), Import(*SigTree1), WeightVar(weights));


  //-------------------------------------------------------//
  // Siganl fit                                            //
  // Using Crystal ball plus 2Gaussian                     //
  // One Gaussian with the same mean, another to fit tail  //
  //-------------------------------------------------------//

  RooRealVar mean2("mean2", " ",125, 115, 135);
  RooRealVar sigma2("sigma2_Gau"," ",20 ,0.01, 40);//Gaussian2 sigma
  RooGaussian Gauss2("Gauss2"," ",mH, mean2, sigma2);

  RooRealVar sigma_CB("sigma_CB"," ", 3, 0.001,30);
  RooRealVar alpha("alpha"," ",0.1,-100,100); // Alpha: Gaussian tail
  RooRealVar n("n"," ",2. ,0., 50.); // n: normalization
  RooCBShape CBall("CBall"," ",mH,mean2,sigma_CB,alpha,n);
  RooRealVar frac_G1("frac_G1"," ",0.3,0.0,0.95);//fraction of Gaussian1

  RooAddPdf SigPdf_2016("SigPdf_2016"," ",RooArgList(CBall,Gauss2),frac_G1);//signal PDF

  ///setting fitting range
  mH.setRange("sigFitRange", 115, 170);
  RooFitResult* r_sig_2016 = SigPdf_2016.fitTo(signal_2016, Save(kTRUE), Range("sigFitRange"));
  *mean = mean2.getValV();
  *sigma = sigma_CB.getValV();
  //check the fitting
  TCanvas* c = new  TCanvas("c", "", 800, 600);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.08);
  RooPlot* xframe4 = mH.frame(115,170) ;
  TLatex* ltx1 = new TLatex();
  ltx1->SetNDC();
  ltx1->SetTextFont(61);
  ltx1->SetTextSize(0.05);
  ltx1->DrawLatex(0.19,0.85,"CMS");
  ltx1->SetTextFont(52);
  ltx1->SetTextSize(0.04);
  ltx1->DrawLatex(0.19,0.81,"Preliminary");
  ltx1->SetTextFont(42);
  ltx1->SetTextSize(0.03);
  ltx1->DrawLatex(0.16,0.94,"H#rightarrowZ#gamma#rightarrowll#gamma");
  ltx1->SetTextFont(42);
  ltx1->SetTextSize(0.04);
  ltx1->DrawLatex(0.68,0.94,"2016 36.46 fb^{-1} (13TeV)");
  signal_2016.plotOn(xframe4,Binning(55), RooFit::Name("Sig_plot")) ;
  SigPdf_2016.plotOn(xframe4, RooFit::Name("SigPdf_plot"),LineColor(kBlue));
  SigPdf_2016.plotOn(xframe4,RooFit::Components("Gauss2"),LineColor(kOrange+7),LineStyle(kDashed),RooFit::Name("Gauss2"));
  SigPdf_2016.plotOn(xframe4,RooFit::Components("CBall"),LineColor(kGreen),LineStyle(kDashed),RooFit::Name("CBall"));
  SigPdf_2016.paramOn(xframe4,Layout(0.05,0.3,0.5));

  xframe4->SetMinimum(0.00001);
  gPad->SetLogy();
  xframe4->GetYaxis()->SetTickSize(0.02);
  xframe4->GetYaxis()->SetTitleSize(0.03);
  xframe4->GetYaxis()->SetTitleOffset(1.3);
  xframe4->GetYaxis()->SetLabelSize(0.03);
  xframe4->GetXaxis()->SetTitleOffset(1.0);
  xframe4->GetXaxis()->SetTitle("M_{ll#gamma} (GeV)");
  xframe4->GetXaxis()->SetTickSize(0.02);
  xframe4->GetXaxis()->SetTitleSize(0.04);
  xframe4->GetXaxis()->SetLabelSize(0.04);
  xframe4->Draw();

  TLegend* leg4 = new TLegend(0.45,0.7,0.65,0.9);
  leg4->AddEntry(xframe4->findObject("Sig_plot"), "signal", "lep");
  leg4->AddEntry(xframe4->findObject("SigPdf_plot"), "Signal model", "l");
  leg4->AddEntry(xframe4->findObject("Gauss2"), "Gauss2", "l");
  leg4->AddEntry(xframe4->findObject("CBall"), "CBall", "l");
  leg4->Draw("same");
  string figname;
  figname = tree + ".png";
  const char *fig = figname.c_str();
  c->Print(fig);

}

void mufit()
{
  setTDRStyle();
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "36.9 fb^{-1}";
  TH1F *getmean = new TH1F("getmean", " ", 50 ,124.5, 125);
  TH1F *getsmear = new TH1F("getsmear", " ",25, 1.4, 2);
  ofstream muout("mu_smear_scale_err.txt");
  muout<<"channel:1-ttH ||  2-ZH  ||  3-WH"<<endl;
  char tree[700];
  //set the parameter of each channel 
  string channel[3] = {"ttH", "ZH", "WH"};
  float mean[3];
  float sigma[3];
  float meanerr[4],sigmaerr[4];
  //begin channel loop
  for(int k = 0; k < 1; k++)
    {
      //define tmp para for set>1
      float tmpmean, tmpsigma, unmean,unsigma;
      unmean = unsigma = 0;
    
      //define set&member loop 
      for(int i = 0; i < 5; i++)
	{
	  tmpmean = tmpsigma = 0;
	  int set = i;
	  for(int j = 0 ; j < 1; j++)
            {
	      int member = j;
	      //	      if(set==0&&member ==2) break;//remove when not test
	      if((set==0||set==2)&&member == 1) break;
	      else if(set >2 && member ==2) break;
	      ///-------------------build signal pdf to fit----------------------///
	      //create combine txt file
	      make_Sig(set, member,channel[k]);	     
	      sprintf(tree, "/afs/cern.ch/work/m/milee/HtoZG/MYcode/uncertainty/muon/txt/mucorr_set%s_%d_member%d.txt", channel[k].c_str(), set,member);
	      fit(tree,&tmpmean,&tmpsigma);
	      
	      ///create tree
	      muout<<"finish fit:"<<set<< " "<<member<<" "<<channel[k]<<" "<<tmpmean<<" "<<tmpsigma<<endl; 
	      //--------------------get nominal value-----------------//
	      if(set==0)
		{
		  mean[k] = tmpmean;
		  sigma[k] = tmpsigma;
		}
	      //--------------------get nominal value-----------------//

	      muout<<mean[k]<<" "<<sigma[k]<<"	"<<tmpmean<<" "<<tmpsigma<<endl;
	      //--------------------Calculation  of uncertainty-----------------//
	      if(set==1)
		{
		  getmean->Fill(tmpmean);
		  getsmear->Fill(tmpsigma);
		  cout<<"set 1:"<<endl;
		}
	      else if (set>1)
		{
		  if(member==0)
		    {
		      unmean = fabs(mean[k]-tmpmean)/mean[k];
		      unsigma = fabs(sigma[k]-tmpsigma)/sigma[k];
		      cout<<"member 0"<<endl;
		    }
		  else
		    {
		      tmpmean = fabs(mean[k]-tmpmean)/mean[k];
		      tmpsigma = fabs(sigma[k]-tmpsigma)/sigma[k];
		      if(tmpmean > unmean) unmean = tmpmean;
		      if(tmpsigma > unsigma) unsigma = tmpsigma;
		      cout<<"member not 0"<<endl;
		    }
		}
	    }//member end
	  if(set==1)
	    {
	      TCanvas *c = new TCanvas("c", "c", 800, 600);
	      c->cd();
	      gStyle->SetOptStat(1);
	      getmean->SetLineColor(kRed);
	      getmean->SetLineWidth(2);
	      getmean->Draw();
	      char outmean[50];
	      char outsig[50];
	      sprintf(outmean,"mumean_%s.png",channel[k].c_str());
	      c->Print(outmean);
	      c->cd();
	      getsmear->SetLineColor(kRed);
	      getsmear->SetLineWidth(2);
	      getsmear->Draw();
	      sprintf(outsig,"musmear_%s.png",channel[k].c_str());
	      c->Print(outsig);
	      cout<<"channel:1-ttH/2-ZH/3-WH"<<endl;

	      cout<<"channel:"<<channel[k]<<" "<<"set:"<<set<<"\n"<<"mean uncertainty:"<<getmean->GetRMS()<<" || "<<"sigma uncertainty:"<<getsmear->GetRMS()<<endl;
	      muout<<"channel:"<<channel[k]<<" "<<"set:"<<set<<"\n"<<"mean uncertainty:"<<getmean->GetRMS()<<" || "<<"sigma uncertainty:"<<getsmear->GetRMS()<<endl;
	      muout<<"\n"<<endl;
	      meanerr[set] = getmean->GetRMS();
	      sigmaerr[set] = getsmear->GetRMS();
	      getmean->Reset();
	      getsmear->Reset();
	    }
	  else
	    {
	      cout<<"channel:1-ttH/2-ZH/3-WH"<<endl;
	      cout<<"channel:"<<channel[k]<<"  "<<"set:"<<set<<"\n"<<"mean uncertainty:"<<unmean<<" || "<<"sigma uncertainty:"<<unsigma<<endl;
	      muout<<"channel:"<<channel[k]<<"  "<<"set:"<<set<<"\n"<<"mean uncertainty:"<<unmean<<" || "<<"sigma uncertainty:"<<unsigma<<" "<<tmpsigma<<endl;
	      muout<<"\n"<<endl;
	      meanerr[set+1] = unmean;
	      sigmaerr[set+1] = unsigma;
	    }
	  //--------------------calculation of uncertainty end-----------------//
	}//sets end	
      
      muout<<channel[k]<<meanerr[0]<<" "<<"mean:"<<sqrt(pow(meanerr[0],2)+pow(meanerr[1],2)+pow(meanerr[2],2)+pow(meanerr[3],2))<<"\n"<<"sigma:"<<sqrt(pow(sigmaerr[0],2)+pow(sigmaerr[1],2)+pow(sigmaerr[2],2)+pow(sigmaerr[3],2))<<endl;
    }//end channel loop
}//end code
