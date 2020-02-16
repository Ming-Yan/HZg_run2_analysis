///USAGE::root -l -b datapdf.C\(\"Moriond17_update0709\"\,1\,\"mu\"\,\"bern\"\,1\)
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
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

#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooDecay.h>

#include "RooAddModel.h"

#include <RooNumConvPdf.h>
#include <RooFFTConvPdf.h>
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
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"

#include "TTree.h"
#include "TLegend.h"
#include "TFrame.h"
#include "RooFitResult.h"

//#include "make_bkg.h"

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

void  make_bkg(string fin, int cat1, string type)
{
  gSystem->Load("libBackgroundProfileFitting");
  int catcut = cat1;
  char txt[50];
  sprintf(txt,"sig/HiggsMass_%s_bkg_%s_cat%d_2016.txt",fin.c_str(),type.c_str(), catcut);
  ofstream sig(txt);
 string sample[2] =
    {
      "ele_EG.root",
      "mu_Mu.root"
    };

  for (Int_t j = 0; j < 2; ++j)
    {
      //TString inpath  = "/home/mingyan/output/mc/mc_btag_"+sample[j];
      if(type=="ele"&&j==1) continue;
      if(type=="mu"&&j==0) continue;
     char inpath[60];
     //sprintf(inpath,"/home/mingyan/output/Data_%s_skim_%s",fin.c_str(),sample[j].c_str());
     sprintf(inpath,"/home/mingyan/output/Data_Moriond17_skim_update0709_%s",sample[j].c_str());
     TFile *f = TFile::Open(inpath);
      TTree *t = (TTree*)f->Get("tZg");
      //t->Print();
      Int_t run_,lumis_, cat, alepCh, lepCh_[2], lepMatch[2],phoMatch,isbtag;
        Long64_t  event_;
        Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,mH,wei,sfeVeto_[2],sfgID_,gsig_;

        double totwei=0;
        t->SetBranchAddress("run",      &run_);
	//if(catcut>10)t->SetBranchAddress("isbtag",      &isbtag);
        t->SetBranchAddress("event",    &event_);
        t->SetBranchAddress("cat",      &cat);
	t->SetBranchAddress("mllg",    &mllg_);

        for ( Long64_t ev = 0; ev < t->GetEntriesFast(); ev++)
        {
            t->GetEntry(ev);
	    if(mllg_>170||mllg_<115)continue;
	    if(cat==catcut)sig<<mllg_<<endl;
	    if(catcut==6789&&cat>5&&cat<10)
	      {sig<<mllg_<<endl;
		//cout<<mllg_<<endl;
	      }
	    if(catcut==11&&isbtag==0)sig<<mllg_<<endl;
	    if(catcut==12&&isbtag==1)sig<<mllg_<<endl;
	    if(catcut==13&&(isbtag==1||isbtag==0))sig<<mllg_<<endl;
        }
  delete f;
    }

}

void datapdf(string fin, int cat, string type, string pdf,int pdforder)
{

  setTDRStyle();

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "35.9 fb^{-1}";
  
  
  int totalev = 0;
  
  make_bkg(fin,cat, type);

  ///create tree
  // TTree* SigTree1 = makeTTree_signal("HiggsMass_signal_0211_120_2016.txt");
   char intxt[50];
   sprintf(intxt,"sig/HiggsMass_%s_bkg_%s_cat%d_2016.txt",fin.c_str(),type.c_str(), cat);
   cout<<cat<<endl;
  TTree* DataTree1 = makeTTree(intxt);
  totalev = DataTree1->GetEntriesFast();

  ///define variables for fitting
  RooRealVar mH("mH", "mH", 115, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///setting fitting range
  mH.setRange("dataFitRange",115, 170);

  ///build unbin data&signal distribution
  RooDataSet data_2016("data_2016", " ", RooArgSet(mH), Import(*DataTree1));

  /////////////////////////////////
  //bkg fit                      //
  //Bernstein 2nd polynomial     //
  /////////////////////////////////

  RooRealVar BkgPdf_2016_norm("BkgPdf_2016_norm"," ",totalev, totalev*0.25,totalev*1.75);
  mH.setRange("window", 115, 170);
  PdfModelBuilder pdfsModel;
  pdfsModel.setObsVar(&mH);
  RooAbsPdf *BkgPdf_2016 ;
  if(pdf=="power")BkgPdf_2016= pdfsModel.getPowerLawSingle("BkgPdf_2016", pdforder);
  if(pdf=="bern")BkgPdf_2016= pdfsModel.getBernstein("BkgPdf_2016", pdforder);
  if(pdf=="laurent")BkgPdf_2016= pdfsModel.getLaurentSeries("BkgPdf_2016", pdforder);
  if(pdf=="exp")BkgPdf_2016= pdfsModel.getExponentialSingle("BkgPdf_2016", pdforder);

  RooFitResult* r_bkg_2016 = BkgPdf_2016->fitTo(data_2016, Range("dataFitRange"), Save(kTRUE)) ;


  /////////////////////////////
  //                         //
  // building workspace      //
  //                         //
  /////////////////////////////

  RooWorkspace *w = new RooWorkspace("w"," ") ;

  w->import(data_2016,Rename(Form("data_obs_%s_cat%d",type.c_str(),cat)),RenameVariable("mH", "CMS_hzg_mass"));
	//w->import(*BkgPdf_2016,RenameVariable("mH", "CMS_hzg_mass"));
  w->import(*BkgPdf_2016,RenameAllNodes(TString::Format("%s_cat%d", type.c_str(),cat)), RenameAllVariablesExcept(TString::Format("%s_cat%d", type.c_str(),cat), "mH"),RenameVariable("mH", "CMS_hzg_mass"));
  /*if(pdforder == 1&&pdf=="bern")
    {
      w->defineSet("BkgPdfParams",
		   RooArgSet(
			     *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat))
			     )
		   );
    }
  else if(pdforder == 1&&pdf=="laurent")
    {
      w->defineSet("BkgPdfParams",
                   RooArgSet(
                             *w->var(Form("BkgPdf_2016_l1_%s_cat%d",type.c_str(),cat))
                             )
                   );
    }
  else if(pdforder == 1&&pdf!="laurent"&&pdf!="bern")
    {
      w->defineSet("BkgPdfParams",
                   RooArgSet(
                             *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat))
                             )
                   );
    }
  if(pdforder == 2)
    {
      w->defineSet("BkgPdfParams",
		   RooArgSet(
			     *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat))
			     )
		   );
    }
  if(pdforder ==3)
    {
  w->defineSet("BkgPdfParams",
	       RooArgSet(
			 *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
			 *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
			 *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat))
			 )
	       );
    }
  if(pdforder==4)
    {
      w->defineSet("BkgPdfParams",
		   RooArgSet(
			     *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p3_%s_cat%d",type.c_str(),cat))
			     )
		   );
    }
  if(pdforder==5)
    {
      w->defineSet("BkgPdfParams",
		   RooArgSet(
			     *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p3_%s_cat%d",type.c_str(),cat)),
			     *w->var(Form("BkgPdf_2016_p4_%s_cat%d",type.c_str(),cat))
			     )
		   );
    }*/
  // w->pdf("BkgPdf_2016");
  
  w->import(BkgPdf_2016_norm,RenameVariable("BkgPdf_2016_norm",Form("BkgPdf_2016_%s_cat%d_norm",type.c_str(),cat)));
  //SetConstantParams(w->set("BkgPdfParams"));
  char ws[80];

  sprintf(ws,"PDFs/bkg_%s_WS_%s_cat%d_2016.root",fin.c_str(),type.c_str(),cat);
  w->writeToFile(ws);

  ///plot
  TCanvas* c1 = new  TCanvas("c1", "", 800, 600);

  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.08);
    
  mH.setRange("blind1",115,120) ;
  mH.setRange("blind2",130,170);
  RooPlot* xframe1  = mH.frame(Title("Data and the fit for 2016")) ;
  data_2016.plotOn(xframe1,Binning(55),CutRange("blind1"),RooFit::Name("data_2016")) ; 
  data_2016.plotOn(xframe1,Binning(55),CutRange("blind2")) ;    
  BkgPdf_2016->plotOn(xframe1, RooFit::Name("Bkg_2016"),VisualizeError(*r_bkg_2016,2),FillColor(7));
  BkgPdf_2016->plotOn(xframe1, RooFit::Name("Bkg_2016"),VisualizeError(*r_bkg_2016,1),FillColor(kAzure+7));
  BkgPdf_2016->plotOn(xframe1, RooFit::Name("Bkg_2016"),LineColor(kBlue));
  data_2016.plotOn(xframe1,Binning(55),CutRange("blind1"),RooFit::Name("data_2016")) ;
  data_2016.plotOn(xframe1,Binning(55),CutRange("blind2")) ;
  //  data_2016.plotOn(xframe1,Binning(55),RooFit::Name("data_2016")) ;
  BkgPdf_2016->paramOn(xframe1,Layout(0.65,0.92,0.89));
  xframe1->getAttText()->SetTextSize(0.03);
  ///    gPad->SetLogy();  
  xframe1->SetMinimum(0.00001);
  xframe1->GetXaxis()->SetTitle("M_{ll#gamma} (GeV)");
  xframe1->GetXaxis()->SetTickSize(0.02);
  xframe1->GetXaxis()->SetTitleSize(0.04);
  xframe1->GetXaxis()->SetLabelSize(0.04);


  CMS_lumi(c1, 4, 11);
  xframe1->Draw();
  char outplot[80];
  sprintf(outplot,"plot/bkg_%s_%s_cat%d.png",fin.c_str(),type.c_str(),cat);
  c1->Print(outplot);
  delete DataTree1;
}
