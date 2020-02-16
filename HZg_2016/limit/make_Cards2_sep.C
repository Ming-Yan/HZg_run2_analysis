//--------USAGE------//
//root -l -b -q make_Cards2_sep.C\(\"fin\"\,\"ele\"\,\"11\"\)
//making signal pdf-interpolation and datacards
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace RooFit ;



//==============OBJECTS================//
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
	  //std::cout << " " << rrv->GetName();
        }
    }
} // close set const parameters

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

  TTree* SigTree = makeTTree(fname);

  Double_t* mH = new Double_t;
  Double_t* weights = new Double_t;
  TTree *T1 = new TTree("T1", "data from ascii file");
  T1->Branch("mH", &mH, "mH/D"); // The branch name is m
  T1->ReadFile(fname.c_str(), "mH");
  return T1 ;
}
//==================================================//
//compute  yield
void Yield(string fin, string type, string cat)
{
  char outyield[500];
  sprintf(outyield,"/afs/cern.ch/work/m/milee/MYcode/limit/sig/Higgs_yield_%s_%s_%s.txt",fin.c_str(),type.c_str(),cat.c_str());
  ofstream yield(outyield);
  TChain ggF120("tZg");
  TChain ggF125("tZg");
  TChain ggF130("tZg");
  TChain VBF120("tZg");
  TChain VBF125("tZg");
  TChain VBF130("tZg");
  TChain ttH120("tZg");
  TChain ttH125("tZg");
  TChain ttH130("tZg");
  TChain ZH120("tZg");
  TChain ZH125("tZg");
  TChain ZH130("tZg");
  TChain WH120("tZg");
  TChain WH125("tZg");
  TChain WH130("tZg");
  string fname;
  if(type=="ele"||type=="ele_mu")
    {
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ggF_120GeV_ext1.root";
      ggF120.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ggF_125GeV_ext1.root";
      ggF125.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ggF_130GeV_ext1.root";
      ggF130.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_VBF_120GeV.root";
      VBF120.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_VBF_125GeV_ext1.root";
      VBF125.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_VBF_130GeV.root";
      VBF130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ttH_120GeV.root";
      ttH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ttH_125GeV.root";
      ttH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ttH_130GeV.root";
      ttH130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ZH_120GeV.root";
      ZH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ZH_125GeV.root";
      ZH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_ZH_130GeV.root";
      ZH130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_W*H_120GeV.root";
      WH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_W*H_125GeV.root";
      WH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_ele_HZg_W*H_130GeV.root";
      WH130.Add(fname.c_str());
      fname.clear();
    }  
	    
  if(type=="mu"||type=="ele_mu")
    {
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ggF_120GeV_ext1.root";
      ggF120.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ggF_125GeV_ext1.root";
      ggF125.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ggF_130GeV_ext1.root";
      ggF130.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_VBF_120GeV.root";
      VBF120.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_VBF_125GeV_ext1.root";
      VBF125.Add(fname.c_str());
      fname.clear();
      fname ="/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_VBF_130GeV.root";
      VBF130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ttH_120GeV.root";
      ttH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ttH_125GeV.root";
      ttH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ttH_130GeV.root";
      ttH130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ZH_120GeV.root";
      ZH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ZH_125GeV.root";
      ZH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_ZH_130GeV.root";
      ZH130.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_W*H_120GeV.root";
      WH120.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_W*H_125GeV.root";
      WH125.Add(fname.c_str());
      fname.clear();
      fname = "/home/mingyan/output/mc/mc_"+fin+"_mu_HZg_W*H_130GeV.root";
      WH130.Add(fname.c_str());
      fname.clear();
    }  
  TH1F *hsig = new TH1F("hsig", " ",55, 115, 170);
  TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
  TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
  TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
  TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
  char cutvar[200];
  if(cat=="6789") sprintf(cutvar,"((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  else if(cat=="11") sprintf(cutvar,"((isbtag==0)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  else if(cat=="12") sprintf(cutvar,"((isbtag==1)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  else if(cat=="13") sprintf(cutvar,"((isbtag==0||isbtag==1)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  else sprintf(cutvar,"((cat==%s)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF",cat.c_str());
  TCut cut(cutvar);

  ggF120.Draw("mllg>>hsig",cut);
  VBF120.Draw("mllg>>hsig1",cut);
  ttH120.Draw("mllg>>hsig2",cut);
  ZH120.Draw("mllg>>hsig3",cut);
  WH120.Draw("mllg>>hsig4",cut);

  yield<<hsig->Integral(-1,-1)<<"\n"<<hsig1->Integral(-1,-1)<<"\n"<<hsig2->Integral(-1,-1)<<"\n"<<hsig3->Integral(-1,-1)<<"\n"<<hsig4->Integral(-1,-1)<<endl;
  hsig->Reset();
  hsig1->Reset();
  hsig2->Reset();
  hsig3->Reset();
  hsig4->Reset();
  ggF125.Draw("mllg>>hsig",cut);
  VBF125.Draw("mllg>>hsig1",cut);
  ttH125.Draw("mllg>>hsig2",cut);
  ZH125.Draw("mllg>>hsig3",cut);
  WH125.Draw("mllg>>hsig4",cut);
  yield<<hsig->Integral(-1,-1)<<"\n"<<hsig1->Integral(-1,-1)<<"\n"<<hsig2->Integral(-1,-1)<<"\n"<<hsig3->Integral(-1,-1)<<"\n"<<hsig4->Integral(-1,-1)<<endl;
  hsig->Reset();
  hsig1->Reset();
  hsig2->Reset();
  hsig3->Reset();
  hsig4->Reset();
  ggF130.Draw("mllg>>hsig",cut);
  VBF130.Draw("mllg>>hsig1",cut);
  ttH130.Draw("mllg>>hsig2",cut);
  ZH130.Draw("mllg>>hsig3",cut);
  WH130.Draw("mllg>>hsig4",cut);
  yield<<hsig->Integral(-1,-1)<<"\n"<<hsig1->Integral(-1,-1)<<"\n"<<hsig2->Integral(-1,-1)<<"\n"<<hsig3->Integral(-1,-1)<<"\n"<<hsig4->Integral(-1,-1)<<endl;

}
//==================================================//
//make signal txt file
void  make_Sig(string fin, string channel, int m, string type ,string catcut)
{

  char inpathele[500],inpathmu[500],outpath[500];

  sprintf(inpathele, "/home/mingyan/output/mc/mc_%s_ele_HZg_%s*_%dGeV*.root",fin.c_str(),channel.c_str(),m);
  sprintf(inpathmu, "/home/mingyan/output/mc/mc_%s_mu_HZg_%s*_%dGeV*.root",fin.c_str(),channel.c_str(),m);
  TChain ch("tZg");
  if(type=="ele"||type=="ele_mu")ch.Add(inpathele);
  if(type=="mu"||type=="ele_mu")ch.Add(inpathmu);
  
  sprintf(outpath,"/afs/cern.ch/work/m/milee/MYcode/limit/sig/HiggsMass_signal_%s_%s_%s_%s_%d.txt",fin.c_str(),type.c_str(),channel.c_str(),catcut.c_str(),m);
  ofstream sig(outpath);


  Int_t run_,lumis_, cat, alepCh, lepCh_[2],totmatch,totalev,mcev,isbtag;
  Long64_t  event_;
  Float_t totSF_, puwei_, mcwei_, genwei_,mllg_;
  double totwei;

  ch.SetBranchAddress("run",      &run_);
  ch.SetBranchAddress("event",    &event_);
  ch.SetBranchAddress("lumis",    &lumis_);
  ch.SetBranchAddress("cat",      &cat);
  ch.SetBranchAddress("puwei",    &puwei_);
  ch.SetBranchAddress("genwei",   &genwei_);
  ch.SetBranchAddress("mcwei",    &mcwei_);
  ch.SetBranchAddress("totSF",    &totSF_);
  if(catcut=="11"||catcut=="12"||catcut=="13")ch.SetBranchAddress("isbtag",   &isbtag);
  ch.SetBranchAddress("mllg",    &mllg_);


  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
      
      //if(genwei_<0) genwei_= genwei_*-1.;
      
      //if(cat<6||cat>9)continue;
      if(mllg_>170||mllg_<100) continue;
      if(catcut=="6789"&&(cat<6||cat>9)) continue;
      else if(catcut=="11"&&(isbtag==-99||isbtag==1)) continue; 
      else if(catcut=="12"&&(isbtag==-99||isbtag==0)) continue; 
      else if(catcut=="13"&&isbtag==-99)continue;
      else if(catcut!="13"&&catcut!="12"&&catcut!="11"&&catcut!="6789")
	{
	  int catn = atoi(catcut.c_str());
	  if(cat!=catn)  continue;
	  
	}
		
      totwei = mcwei_*genwei_*totSF_*puwei_;
      sig<<mllg_<<" "<<totwei<<endl;
	    
      //sig<<mllg_<<endl;
    }

}
 

//fit the mass point 
void fit(string txtname, Int_t Mean, RooFitResult *r_sig, RooWorkspace *w, string channel, string type, string cat)
{
   
   
  ///create tree
  TTree* SigTree1 = makeTTree_signal(txtname);

	if(channel=="W*H") channel = "WH";
  ///define variables for fitting
  RooRealVar mH("mH", "mH", 100, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///build unbin data&signal distribution
  RooDataSet signal_2016("signal_2016", " ", RooArgSet(mH, weights), Import(*SigTree1), WeightVar(weights));


  //-------------------------------------------------------//
  // Siganl fit                                            //
  // Using Crystal ball plus 2Gaussian                     //
  // One Gaussian with the same mean, another to fit tail  //
  //-------------------------------------------------------//

  RooRealVar mean("mean", " ",Mean, Mean-3, Mean+3);
  RooRealVar sigma_Gau("sigma_Gau"," ",15 , 2.5, 100);//Gaussian2 sigma
  RooGaussian Gauss("Gauss"," ",mH, mean, sigma_Gau);

  RooRealVar sigma_CB("sigma_CB"," ",1.3 , 0.001,15); 
  RooRealVar alpha("alpha"," ",1.5 ,.001,20); // Alpha: Gaussian tail
  RooRealVar n("n"," ",1.5 ,0.01, 50.); // n: normalization
  RooCBShape CBall("CBall"," ",mH,mean,sigma_CB,alpha,n);
  RooRealVar frac_G1("frac_G1"," ",0.65,0.0,1.0);//fraction of Gaussian1

  RooAddPdf Sig_bin2("Sig_bin2"," ",RooArgList(CBall,Gauss),frac_G1);//signal PDF

  ///setting fitting range
  mH.setRange("sigFitRange", 115, 170);
  RooFitResult* r_sig_2016 = Sig_bin2.fitTo(signal_2016, Save(kTRUE), Range("sigFitRange"));
  //end of signal fitting


  /////////////////////////////
  //                         //
  // building workspace      //
  //                         //
  /////////////////////////////
 
  
  
  w->import(Sig_bin2, RenameAllNodes(TString::Format("%s_%s_cat%s", type.c_str(),channel.c_str(),cat.c_str())), RenameAllVariablesExcept(TString::Format("%s_%s_cat%s", type.c_str(),channel.c_str(),cat.c_str()), "mH"),
	    RenameVariable("mH", "CMS_hzg_mass"));
		 w->defineSet("SigPdfParams",
	       RooArgSet(
			 *w->var(Form("mean_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("sigma_Gau_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("sigma_CB_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("n_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("alpha_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("frac_G1_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str()))));
  SetConstantParams(w->set("SigPdfParams"));
  w->pdf(TString::Format("Sig_bin2_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str()));
   if(type=="mu"||type== "ele_mu")
    {
			
      w->factory(Form("CMS_hzg_delta_muRoch_mean_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_muPho_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
	 
      w->factory(Form("CMS_hzg_delta_muRoch_sigma_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muPho_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));

      w->factory(Form("prod::mean_corr_%s_%s_cat%s(mean_%s_%s_cat%s,sum::CMS_hzg_delta_mu_mean_%s_%s_cat%s(CMS_hzg_delta_muRoch_mean_%s_%s_cat%s, CMS_hzg_delta_muEM_mean_%s_%s_cat%s, CMS_hzg_delta_muPho_mean_%s_%s_cat%s )",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("prod::sigma_corr_%s_%s_cat%s(sigma_CB_%s_%s_cat%s, sum::CMS_hzg_delta_mu_sigma_%s_%s_cat%s(CMS_hzg_delta_muRoch_sigma_%s_%s_cat%s, CMS_hzg_delta_muEM_sigma_%s_%s_cat%s, CMS_hzg_delta_muPho_sigma_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));

      w->factory(Form("EDIT::newPdf_%s_%s_cat%s(Sig_bin2_%s_%s_cat%s,mean_%s_%s_cat%s=mean_corr_%s_%s_cat%s, sigma_CB_%s_%s_cat%s=sigma_corr_%s_%s_cat%s)",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
	 
    }

  ///em scale 
  if(type=="ele")
  {
  w->factory(Form("CMS_hzg_delta_eleEM_mean_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
  w->factory(Form("CMS_hzg_delta_elePho_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod

  w->factory(Form("CMS_hzg_delta_eleEM_sigma_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
  w->factory(Form("CMS_hzg_delta_elePho_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));

  //wspace.factory(Form("prod::mean_corr_chan%d_m%d_cat%d(sig_mean1_chan%d_m%d_cat%d,CMS_hzg_delta_eleEM_mean_chan%d_m%d_cat%d)",p,5*mm+k,cat,p,5*mm+k,cat,p,5*mm+k,cat));
  //wspace.factory(Form("prod::sigma_corr_chan%d_m%d_cat%d(sig_sigma1_chan%d_m%d_cat%d,CMS_hzg_delta_eleEM_sigma_chan%d_m%d_cat%d)",p,5*mm+k,cat,p,5*mm+k,cat,p,5*mm+k,cat));
	 
  w->factory(Form("prod::mean_corr_%s_%s_cat%s(mean_%s_%s_cat%s,sum::CMS_hzg_delta_ele_mean_%s_%s_cat%s(CMS_hzg_delta_eleEM_mean_%s_%s_cat%s, CMS_hzg_delta_elePho_mean_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
  w->factory(Form("prod::sigma_corr_%s_%s_cat%s(sigma_CB_%s_%s_cat%s,sum::CMS_hzg_delta_ele_sigma_%s_%s_cat%s(CMS_hzg_delta_eleEM_sigma_%s_%s_cat%s, CMS_hzg_delta_elePho_sigma_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));

  w->factory(Form("EDIT::newPdf_%s_%s_cat%s(Sig_bin2_%s_%s_cat%s,mean_%s_%s_cat%s=mean_corr_%s_%s_cat%s, sigma_CB_%s_%s_cat%s=sigma_corr_%s_%s_cat%s)",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
   } 	

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
     ltx1->DrawLatex(0.68,0.94,"2016 35.9 fb^{-1} (13TeV)");
     signal_2016.plotOn(xframe4,Binning(55), RooFit::Name("Sig_plot")) ;
     Sig_bin2.plotOn(xframe4, RooFit::Name("SigPdf_plot"),LineColor(kBlue));
     Sig_bin2.plotOn(xframe4,RooFit::Components("Gauss"),LineColor(kOrange+7),LineStyle(kDashed),RooFit::Name("Gauss"));
     Sig_bin2.plotOn(xframe4,RooFit::Components("CBall"),LineColor(kGreen),LineStyle(kDashed),RooFit::Name("CBall"));
     Sig_bin2.paramOn(xframe4,Layout(0.7,0.95,0.95));

     xframe4->SetMinimum(0.00001);
     gPad->SetLogy();
     xframe4->getAttText()->SetTextSize(0.03);
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
     leg4->AddEntry(xframe4->findObject("Gauss"), "Gauss", "l");
     leg4->AddEntry(xframe4->findObject("CBall"), "CBall", "l");
     leg4->Draw("same");
     string figname;
     if(Mean == 120) figname  = "plot/sigfit_"+ channel + "_" + type + "_" + cat + "_" + "120_log.png";
     if(Mean == 125)figname  = "plot/sigfit_"+ channel + "_" + type + "_" + cat + "_" + "125_log.png";
     if(Mean == 130)figname  = "plot/sigfit_"+ channel + "_" + type + "_" + cat + "_" + "130_log.png";
     const char *fig = figname.c_str();
     c->Print(fig); 

}


///get the parameters of interpolation
void IntParams(Int_t m1, Int_t m2, Int_t mass, RooWorkspace w1, RooWorkspace w2, RooWorkspace *w, const char * name, string type)
{


  double a = (double(m2) - double(mass)) / (double(m2) - double(m1));
  double b = 1 - a;
  RooRealVar CMS_hzg_mass("CMS_hzg_mass", "CMS_hzg_mass", 115, 170, "GeV");
  cout<<"cms hzg mass::"<<name<<endl;
  float fitResult_sigmaGau1,fitResult_sigmaCB1, fitResult_mean1, fitResult_alpha1,fitResult_power1, fitResult_frac_G1;

  fitResult_sigmaGau1 = (w1.var(Form("sigma_Gau_%s",name)))->getVal();
 cout<<"get 1"<<endl;
  fitResult_sigmaCB1 = (w1.var(Form("sigma_CB_%s",name)))->getVal();
  fitResult_mean1 = (w1.var(Form("mean_%s",name)))->getVal();
  fitResult_alpha1 = (w1.var(Form("alpha_%s",name)))->getVal();
  fitResult_power1 = (w1.var(Form("n_%s",name)))->getVal();
  fitResult_frac_G1 = (w1.var(Form("frac_G1_%s",name)))->getVal();

  float fitResult_sigmaGau2,fitResult_sigmaCB2,  fitResult_mean2, fitResult_alpha2,fitResult_power2, fitResult_frac_G2;

  fitResult_sigmaGau2 = (w2.var(Form("sigma_Gau_%s",name)))->getVal();
  fitResult_sigmaCB2 = (w2.var(Form("sigma_CB_%s",name)))->getVal();
  fitResult_mean2 = (w2.var(Form("mean_%s",name)))->getVal();
  fitResult_alpha2 = (w2.var(Form("alpha_%s",name)))->getVal();
  fitResult_power2 = (w2.var(Form("n_%s",name)))->getVal();
  fitResult_frac_G2 = (w2.var(Form("frac_G1_%s",name)))->getVal();

  //ERROR
  float error_sigmaGau1,error_sigmaCB1, error_mean1, error_alpha1,error_power1, error_frac_G1;

  error_sigmaGau1 = (w1.var(Form("sigma_Gau_%s",name)))->getError();
  error_sigmaCB1 = (w1.var(Form("sigma_CB_%s",name)))->getError();
  error_mean1 = (w1.var(Form("mean_%s",name)))->getError();
  error_alpha1 = (w1.var(Form("alpha_%s",name)))->getError();
  error_power1 = (w1.var(Form("n_%s",name)))->getError();
  error_frac_G1 = (w1.var(Form("frac_G1_%s",name)))->getError();


  float error_sigmaGau2, error_sigmaCB2, error_mean2, error_alpha2, error_power2, error_frac_G2;

  error_sigmaGau2 = (w2.var(Form("sigma_Gau_%s",name)))->getError();
  error_sigmaCB2 = (w2.var(Form("sigma_CB_%s",name)))->getError();
  error_mean2 = (w2.var(Form("mean_%s",name)))->getError();
  error_alpha2 = (w2.var(Form("alpha_%s",name)))->getError();
  error_power2 = (w2.var(Form("n_%s",name)))->getError();
  error_frac_G2 = (w2.var(Form("frac_G1_%s",name)))->getError();
 cout<<"get param"<<endl;
  //INTERPOLATION
  float sigmaCB_fr,sigmaGau_fr, mean_fr, alpha_fr, power_fr, frac_G1_fr;
  sigmaCB_fr = a*fitResult_sigmaCB1 + b*fitResult_sigmaCB2;
  sigmaGau_fr = a*fitResult_sigmaGau1 + b*fitResult_sigmaGau2;
  mean_fr = a*fitResult_mean1 + b*fitResult_mean2;
  alpha_fr = a*fitResult_alpha1 + b*fitResult_alpha2;
  power_fr = a*fitResult_power1 + b*fitResult_power2;
  frac_G1_fr = a*fitResult_frac_G1 + b*fitResult_frac_G2;
 

  //ERROR
  float sigmaCB_err,sigmaGau_err, mean_err, alpha_err, power_err,frac_G1_err;
  sigmaCB_err = sqrt((a*error_sigmaCB1)*(a*error_sigmaCB1) + (b*error_sigmaCB2)*(b*error_sigmaCB2));
  sigmaGau_err = sqrt((a*error_sigmaGau1)*(a*error_sigmaGau1) + (b*error_sigmaGau2)*(b*error_sigmaGau2));
  mean_err = sqrt((a*error_mean1)*(a*error_mean1) + (b*error_mean2)*(b*error_mean2));
  alpha_err = sqrt((a*error_alpha1)*(a*error_alpha1) + (b*error_alpha2)*(b*error_alpha2));
  power_err = sqrt((a*error_power1)*(a*error_power1) + (b*error_power2)*(b*error_power2));
  frac_G1_err = sqrt((a*error_frac_G1)*(a*error_frac_G1) + (b*error_frac_G2)*(b*error_frac_G2));
cout<<"interpolate2"<<endl;
  RooRealVar s21("s21", "s21", 5, 0, 10); //sigma ratio
  RooRealVar delta21("delta21", "delta21", 0, -50, 50); //delta between means
  RooRealVar meanfr("meanfr", "meanfr", mean_fr);
  RooRealVar sigmaCBfr("sigmaCBfr", "sigmaCBfr", sigmaCB_fr);
  RooRealVar sigmaGaufr("sigmaGaufr", "sigmaGaufr", sigmaGau_fr);
  RooRealVar alphafr("alphafr", "alphafr", alpha_fr);
  RooRealVar powerfr("powerfr", "powerfr", power_fr);
  RooRealVar fracG1fr("fracG1fr", "fracG1fr", frac_G1_fr);

  RooGaussian IGauss("IGauss", "IGauss", CMS_hzg_mass, meanfr, sigmaGaufr);
  RooCBShape ICBall("ICBall", "ICrystal Ball Shape", CMS_hzg_mass, meanfr, sigmaCBfr, alphafr, powerfr);
  RooAddPdf ISig_bin2("ISig_bin2", "sum of Gaussian and CBall", RooArgList(ICBall,IGauss),fracG1fr);

  meanfr.setError(mean_err);
  sigmaCBfr.setError(sigmaCB_err);
  sigmaGaufr.setError(sigmaGau_err);
  alphafr.setError(alpha_err);
  powerfr.setError(power_err);
  fracG1fr.setError(frac_G1_err);


////////////////////////
//					  //
//  save to workspace //
//					  //
////////////////////////

  
  
  w->import(ISig_bin2, RenameAllNodes(name), RenameAllVariablesExcept(name,"CMS_hzg_mass"));
		 w->defineSet("SigPdfParams",
	       RooArgSet(
			 *w->var(Form("meanfr_%s",name)),
			 *w->var(Form("sigmaGaufr_%s",name)),
			 *w->var(Form("sigmaCBfr_%s",name)),
			 *w->var(Form("powerfr_%s",name)),
			 *w->var(Form("alphafr_%s",name)),
			 *w->var(Form("fracG1fr_%s",name))));
  SetConstantParams(w->set("SigPdfParams"));
  w->pdf(TString::Format("ISig_bin2_%s",name));
   if(type=="mu"||type== "ele_mu")
    {
			
      w->factory(Form("CMS_hzg_delta_muRoch_mean_%s[1]",name));
      w->factory(Form("CMS_hzg_delta_muEM_mean_%s[0]",name)); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_muPho_mean_%s[0]",name)); ///inside hte square brackets are hte initial values so change to 1 if i use prod
	 
      w->factory(Form("CMS_hzg_delta_muRoch_sigma_%s[1]",name));
      w->factory(Form("CMS_hzg_delta_muEM_sigma_%s[0]",name));
      w->factory(Form("CMS_hzg_delta_muPho_sigma_%s[0]",name));

      w->factory(Form("prod::mean_corr_%s(meanfr_%s,sum::CMS_hzg_delta_mu_mean_%s(CMS_hzg_delta_muRoch_mean_%s, CMS_hzg_delta_muEM_mean_%s, CMS_hzg_delta_muPho_mean_%s)",name,name,name,name,name,name));
      w->factory(Form("prod::sigma_corr_%s(sigmaCBfr_%s, sum::CMS_hzg_delta_mu_sigma_%s(CMS_hzg_delta_muRoch_sigma_%s, CMS_hzg_delta_muEM_sigma_%s, CMS_hzg_delta_muPho_sigma_%s))",name,name,name,name,name,name));

      w->factory(Form("EDIT::newPdf_%s(ISig_bin2_%s,meanfr_%s=mean_corr_%s, sigmaCBfr_%s=sigma_corr_%s)",name,name,name,name,name,name));
	 
    }

  ///em scale 
  if(type=="ele")
  {
  w->factory(Form("CMS_hzg_delta_eleEM_mean_%s[1]",name)); ///inside hte square brackets are hte initial values so change to 1 if i use prod
  w->factory(Form("CMS_hzg_delta_elePho_mean_%s[0]",name)); ///inside hte square brackets are hte initial values so change to 1 if i use prod

  w->factory(Form("CMS_hzg_delta_eleEM_sigma_%s[1]",name));
  w->factory(Form("CMS_hzg_delta_elePho_sigma_%s[0]",name));

  //wspace.factory(Form("prod::mean_corr_chan%d_m%d_cat%d(sig_mean1_chan%d_m%d_cat%d,CMS_hzg_delta_eleEM_mean_chan%d_m%d_cat%d)",p,5*mm+k,cat,p,5*mm+k,cat,p,5*mm+k,cat));
  //wspace.factory(Form("prod::sigma_corr_chan%d_m%d_cat%d(sig_sigma1_chan%d_m%d_cat%d,CMS_hzg_delta_eleEM_sigma_chan%d_m%d_cat%d)",p,5*mm+k,cat,p,5*mm+k,cat,p,5*mm+k,cat));
	 
  w->factory(Form("prod::mean_corr_%s(meanfr_%s,sum::CMS_hzg_delta_ele_mean_%s(CMS_hzg_delta_eleEM_mean_%s, CMS_hzg_delta_elePho_mean_%s))",name,name,name,name,name));
  w->factory(Form("prod::sigma_corr_%s(sigmaCBfr_%s,sum::CMS_hzg_delta_ele_sigma_%s(CMS_hzg_delta_eleEM_sigma_%s, CMS_hzg_delta_elePho_sigma_%s))",name,name,name,name,name));

  w->factory(Form("EDIT::newPdf_%s(ISig_bin2_%s,meanfr_%s=mean_corr_%s, sigmaCBfr_%s=sigma_corr_%s)",name,name,name,name,name,name));
   } 
  
 
}

void interpolate2(string fin, string type, string channel, string cat)
{
  TCanvas* c1 = new  TCanvas("c1", "", 800, 600);
  c1->cd();
  string massPt[3] = { "120", "125", "130" };
  Int_t massPts[3] = { 120, 125, 130 };
  string name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  RooPlot* xframe;

  //RooWorkspace wspace[11];
  int index = 0;

  for (int m = 0; m < 2; m++) //start with 0
    {

      for (int k = 1; k < 5; k++) //start with 1
        {
	  Int_t m1 = massPts[m];
	  Int_t m2 = massPts[m + 1];
	  Int_t mass = massPts[m] + k;

	  string txtname = "sig/HiggsMass_signal_" + fin+ "_" +type + "_" + channel + "_" + cat + "_" + massPt[m] + ".txt";
	  string txtname2 = "sig/HiggsMass_signal_" + fin +"_" + type + "_" + channel + "_" + cat + "_" + massPt[m + 1] + ".txt";

	  RooWorkspace w1, w2, w;
	  RooFitResult sig1, sig2;
	  fit(txtname, m1, &sig1, &w1, channel, type, cat);
	  fit(txtname2, m2, &sig2, &w2, channel, type, cat);
	  RooAbsPdf *pdf1, *pdf2;
	  pdf1 = (w1.pdf(Form("Sig_bin2_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())));
	  pdf2 = (w2.pdf(Form("Sig_bin2_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())));
	  RooRealVar *mH1 = w1.var("CMS_hzg_mass");
	  RooRealVar *mH2 = w2.var("CMS_hzg_mass");

	  if (m == 0 && k == 1)
            {
	      xframe = mH1->frame(Title("Signal MC and the Fit"));
	      xframe->SetAxisRange(115, 170, "X");
	      pdf1->plotOn(xframe, Binning(55), LineColor(1));
	      pdf2->plotOn(xframe, Binning(55), LineColor(46));
	      string w1path = "PDFs/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_120.root";
	      string w2path = "PDFs/WS_" + fin+ "_" +type + "_" + channel + "_" + cat + "_125.root";
	      const char *w1out = w1path.c_str();
	      const char *w2out = w2path.c_str();
	      w1.writeToFile(w1out);
	      w2.writeToFile(w2out);
	    }
	  if (m == 1 && k == 1)

            {
	      pdf2->plotOn(xframe, Binning(55), LineColor(41));
	      string w2path = "PDFs/WS_" + fin+ "_" + type + "_" + channel + "_" + cat + "_130.root";
	      const char *w2out = w2path.c_str();
	      w2.writeToFile(w2out);
	    }
		string wsname = type + "_" + channel + "_cat" + cat;
		const char *naming = wsname.c_str();
	   IntParams(m1, m2, mass, w1, w2, &w, naming,type);

	     RooRealVar *mH3 = w.var("CMS_hzg_mass");
	     int icol[] = { 2, 3, 4, 5, 6, 7, 8, 9, 40};
	     RooAbsPdf *pdf = (w.pdf(Form("ISig_bin2_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())));
	     pdf->plotOn(xframe, LineColor(icol[index]));
	     if (index <  4)
	     {
	     string wpath = "PDFs/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_" + name[index + 1] +".root";
	     const char * wout = wpath.c_str();
	     w.writeToFile(wout);
	     }
	     if (index >= 4)
	     {
	     string wpath = "PDFs/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_" + name[index + 2] +".root";
	     const char * wout = wpath.c_str();
	     w.writeToFile(wout);
	     }
	     index++;
        }
    }
    c1->cd();
     xframe->Draw();
     gPad->SetLogy();
     string figpath = "plot/interpolate_log" + fin+ "_" + type + "_" + channel + "_" + cat + ".png";
     const char * fig = figpath.c_str();
     c1->SaveAs(fig); 

}

double IntSigRate(int m, double accEff1, double accEff2)
{
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  const char* name2 = name[m];
  double mass = 120. + double(m);
  double m1, m2;
  if (mass < 125)
    {
      m1 = 120.;
      m2 = 125.;
    }
  if (mass > 125)
    {
      m1 = 125.;
      m2 = 130.;
    }
  double sigRate;
  if (mass != 120 && mass != 125 && mass != 130)
    {
      double a = (double(m2) - double(mass)) / (double(m2) - double(m1));
      double b = 1 - a;
      double IaccEff = a*accEff1 + b*accEff2;
      sigRate = IaccEff;
    }
  else if (mass == 120 || mass == 125) sigRate = accEff1;
  else sigRate = accEff2;

  return sigRate;

}
//==============MAIN================//
void make_Cards2_sep(string fin,string type, string cat)
{
   
  ///signal yield for different production channel
  //-----------------------//
  //ggF->VBF->ttH->ZH->WH
  //0-4 120   //
  //5-9 125   //
  //10-14 130 //
  //-----------------------//
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  string channel[5] = {"ggF", "VBF","ttH", "ZH", "W*H"};
  char input[500];
  sprintf(input,"sig/Higgs_yield_%s_%s_%s.txt",fin.c_str(),type.c_str(),cat.c_str());
  ifstream in;
  Yield(fin,type,cat);
  in.open(input);
  double total[15];
  float a;
  float phocov =  0.969;
  for (int i = 0;i<15;i++)
    { 
      in>>a;
      total[i] = a/phocov;
    }
	
  //do intepolation
  double sigRate[55];
  
  for(int n = 0; n < 5; n++) {  
    if(cat == "6789"&&n<2) continue;
    else if(cat != "6789"&&n>1) continue;
    make_Sig(fin, channel[n], 120, type , cat);
    make_Sig(fin, channel[n], 125, type , cat);
    make_Sig(fin, channel[n], 130, type , cat);
    interpolate2(fin, type, channel[n], cat);
  }
  for(int n = 0 ; n < 5 ; n ++)
    {
      for(int m = 0; m < 11; m++)
        {
	  double mass = 120 + m;

	  if (mass < 125) sigRate[n*11+m] = IntSigRate(m, total[n], total[5+n]);
	  if (mass >= 125) sigRate[n*11+m] = IntSigRate(m, total[5+n], total[10+n]);
        }
    }
  


  for (int m = 0; m < 11; m++)//loop for different mass point
    {

      TString datacard;
      datacard += "imax 1   number of channels\n";
      datacard += "jmax *   number of process minus 1\n";
      datacard += "kmax *   number of nuisance parameters (sources of systematic uncertainty)\n";
      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("shapes bgr        cat%s  ../PDFs/bkg_%s_WS_%s_cat%s_2016.root w:BkgPdf_2016_%s_cat%s\n",cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(),type.c_str(),cat.c_str());
      datacard += TString::Format("shapes data_obs   cat%s    ../PDFs/bkg_%s_WS_%s_cat%s_2016.root w:data_obs_%s_cat%s\n",cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(),type.c_str(),cat.c_str());
      const char* name2 = name[m];
	
        if (name[m] != "120" && name[m] != "125" && name[m] != "130")
	  {
	  if(cat == "6789"||cat=="11"||cat=="12"||cat=="13")
	  {
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_W*H_%s_%s.root :newPdf_%s_W*H_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_ttH_%s_%s.root :newPdf_%s_W*H_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_ttH_%s_%s.root :newPdf_%s_ttH_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s     ../PDFs/WS_%s_%s_ZH_%s_%s.root :newPdf_%s_ZH_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_W*H_%s_%s.root :newPdf_%s_W*H_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  }
	  else if(cat == "5")
	  {
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  }
	  else 
	  {
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s     ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(),cat.c_str());
	  }
	  } 
      else
      {
       if(cat == "6789"||cat=="11"||cat=="12"||cat=="13")
	{
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_W*H_%s_%s.root :newPdf_%s_WH_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(),cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_ttH_%s_%s.root :newPdf_%s_ttH_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(),cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_ttH_%s_%s.root :newPdf_%s_ttH_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s     ../PDFs/WS_%s_%s_ZH_%s_%s.root :newPdf_%s_ZH_cat%s\n", cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_W*H_%s_%s.root :newPdf_%s_WH_cat%s\n", cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	}
      else if(cat =="5")
	{
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n", cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s     ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	}
      else 
	{ 
	  datacard += TString::Format("shapes ggH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes qqH_hzg        cat%s    ../PDFs/WS_%s_%s_VBF_%s_%s.root :newPdf_%s_VBF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ttH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(),fin.c_str(),type.c_str(), cat.c_str(), name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes ZH_hzg        cat%s     ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	  datacard += TString::Format("shapes WH_hzg        cat%s    ../PDFs/WS_%s_%s_ggF_%s_%s.root :newPdf_%s_ggF_cat%s\n",cat.c_str(), fin.c_str(),type.c_str(), cat.c_str(),name2,type.c_str(), cat.c_str());
	}
      }
      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("bin               cat%s\n",cat.c_str());
      datacard += "observation       -1\n";
      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("bin               cat%s         cat%s        cat%s        cat%s        cat%s  cat%s\n",cat.c_str(),cat.c_str(),cat.c_str(),cat.c_str(),cat.c_str(),cat.c_str());
      datacard += "process           ggH_hzg          qqH_hzg         ttH_hzg         ZH_hzg          WH_hzg     bgr \n";
      datacard += "process           -4           -3          -2          -1          0      1   \n";
      datacard += TString::Format("rate           %f          %f          %f          %f       %f          1.000000\n"
				  ,sigRate[m], sigRate[m+11], sigRate[m+22], sigRate[m+33], sigRate[m+44]);//if bkg is normalized;
      datacard += "--------------------------------------------------------------------------\n";
      datacard += "lumi_13TeV  lnN        1.062         1.062         1.062         1.062         1.062         -\n";
      datacard += "pdf_ggH     lnN        0.968/1.032   -             -             -             -             -\n";
      datacard += "pdf_ttH     lnN        -             -             0.964/1.036   -             -             -\n";
      datacard += "pdf_Higgs_qqbar lnN    -             0.979/1.021   -             0.984/1.016   0.981/1.019   -\n";
      datacard += "QCDscale_ggH     lnN   0.9330/1.046  -             -             -             -             -\n";
      datacard += "QCDscale_qqH     lnN   -             0.9970/1.004  -             -             -             -\n";
      datacard += "QCDscale_VH      lnN   -             -             -             0.9690/1.038  0.9930/1.005  -\n";
      datacard += "QCDscale_ttH     lnN   -             -             0.9080/1.058  -             -             -\n";
      datacard += "br_Higgs    lnN        0.9429/1.0571 0.9429/1.0571 0.9429/1.0571 0.9429/1.0571 0.9429/1.0571 -\n";
      // datacard += "CMS_HLTeff_13TeV     lnN";
     
      datacard += "CMS_hzg_delta_eleEM_mean_chan0_m5_cat6789    param 1 1.008062 \n";
      datacard += "CMS_hzg_delta_eleEM_mean_chan1_m5_cat6789    param 1 1.008091 \n";
      datacard += "CMS_hzg_delta_eleEM_mean_chan2_m5_cat6789    param 1 1.008084 \n";
      datacard += "CMS_hzg_delta_eleEM_mean_chan3_m5_cat6789    param 1 1.008084 \n";
      datacard += "CMS_hzg_delta_eleEM_mean_chan4_m5_cat6789    param 1 1.008084 \n";
      datacard += "CMS_hzg_delta_elePho_mean_chan0_m5_cat6789    param 0 0.000173 \n"; 
      datacard += "CMS_hzg_delta_elePho_mean_chan1_m5_cat6789    param 0 0.000262 \n";
      datacard += "CMS_hzg_delta_elePho_mean_chan2_m5_cat6789    param 0 0.000208 \n";
      datacard += "CMS_hzg_delta_elePho_mean_chan3_m5_cat6789    param 0 0.000208 \n";
     datacard += "CMS_hzg_delta_elePho_mean_chan4_m5_cat6789    param 0 0.000208";
datacard += "CMS_hzg_delta_eleEM_reso_chan0_m5_cat6789    param 1 1.631506 \n" ;
datacard += "CMS_hzg_delta_eleEM_reso_chan1_m5_cat6789    param 1 1.837813 \n";
datacard += "CMS_hzg_delta_eleEM_reso_chan2_m5_cat6789    param 1 1.881778 \n";
datacard += "CMS_hzg_delta_eleEM_reso_chan3_m5_cat6789    param 1 1.881778 \n";
datacard += "CMS_hzg_delta_eleEM_reso_chan4_m5_cat6789    param 1 1.881778 \n";
datacard += "CMS_hzg_delta_elePho_reso_chan0_m5_cat6789    param 0 0.015750 \n";
datacard += "CMS_hzg_delta_elePho_reso_chan1_m5_cat6789    param 0 0.055895 \n";
datacard += "CMS_hzg_delta_elePho_reso_chan2_m5_cat6789    param 0 0.022784 \n";
datacard += "CMS_hzg_delta_elePho_reso_chan3_m5_cat6789    param 0 0.022784 \n";
datacard += "CMS_hzg_delta_elePho_reso_chan4_m5_cat6789    param 0 0.022784 \n"; 
	datacard += TString::Format("BkgPdf_2016_p0_%s_cat%s flatParam \n",type.c_str(),cat.c_str());
      datacard += TString::Format("BkgPdf_2016_p1_%s_cat%s flatParam \n",type.c_str(),cat.c_str());
      if(cat == "1"||cat =="2"||cat =="3"||cat =="4"||cat =="10")
	{
	  datacard += TString::Format("BkgPdf_2016_p2_%s_cat%s flatParam \n",type.c_str(),cat.c_str());
	  if(cat == "1"||cat =="2"||cat =="3"||cat =="4")
	    {
	      datacard += TString::Format("BkgPdf_2016_p3_%s_cat%s flatParam \n",type.c_str(),cat.c_str());
	      if(cat =="2")datacard += TString::Format("BkgPdf_2016_p4_%s_cat%s flatParam \n",type.c_str(),cat.c_str());
	    }
	} 

      std::ofstream outputFileSEB;
      outputFileSEB.open(TString::Format("DataCards/card_%s_%s_%s_%s.txt", fin.c_str(),type.c_str(), cat.c_str(),name2));
      outputFileSEB << datacard;
      outputFileSEB.close();
    }

}


