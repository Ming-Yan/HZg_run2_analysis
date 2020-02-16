#ifndef H_MAKESIG
#define H_MAKESIG
#include "cat.h"
#include <iostream>
#include "sig_fit.h"

using namespace RooFit ;
using namespace std;
void Yield(string vername, string fin, string type, int period ,int catcut, bool isboost, float kinup, float kindown, float kincut, float VBFcut)
{
  char outyield[500];
  sprintf(outyield,"sig/%s%s/Higgs_yield_%s_%s_%d.txt",fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(),catcut);
  //cout<<outyield<<endl;
  //cout<<vername<<" "<<fin<<" "<<type<<" "<<period<<" "<<catcut<<" "<<isboost<<" "<<kinup<<" "<<kindown<<" "<<kincut<<" "<<VBFcut<<endl;
  ofstream yield(outyield);
  char inpathele[500],inpathmu[500],outpath[500];
  string sigsample[15]=
    {
      "HZg_ggF_120GeV.root",
      "HZg_VBF_120GeV.root",
      "HZg_ttH_120GeV.root",
      "HZg_ZH_120GeV.root",
      "HZg_W*H_120GeV.root",
      "HZg_ggF_125GeV.root",
      "HZg_VBF_125GeV.root",
      "HZg_ttH_125GeV.root",
      "HZg_ZH_125GeV.root",
      "HZg_W*H_125GeV.root",
      "HZg_ggF_130GeV.root",
      "HZg_VBF_130GeV.root",
      "HZg_ttH_130GeV.root",
      "HZg_ZH_130GeV.root",
      "HZg_W*H_130GeV.root",
    };
  for(int i = 0; i < 15 ; i++)
    {
      sprintf(inpathele, "/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_%s",fin.c_str(),sigsample[i].c_str());
      sprintf(inpathmu, "/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_%s",fin.c_str(),sigsample[i].c_str());
      cout<<inpathmu<<endl;
      TChain ch("tZg");
      if(type=="ele"||type=="ele_mu")ch.Add(inpathele);
      if(type=="mu"||type=="ele_mu")ch.Add(inpathmu);
      Int_t run_,lumis_, cat, alepCh, lepCh_[2],totmatch,totalev,mcev,isbtag;
      Long64_t  event_;
      Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,HZgVBF,HZgMVA,ZgPTt,sfedz_[2],mllgpt,gR9_,gSCEta_,lepEta_[2],lepSCEta_[2],REFITmllg_,bCsv2,MET,phoPt,lepPt[2];
      double totwei;
      ch.SetBranchAddress("run",      &run_);
      ch.SetBranchAddress("cat",      &cat);
      //ch.SetBranchAddress("isbtag",      &isbtag);
      ch.SetBranchAddress("puwei",    &puwei_);
      ch.SetBranchAddress("lepPt",     lepPt);
      ch.SetBranchAddress("phoPt",     &phoPt);
      ch.SetBranchAddress("genwei",   &genwei_);
      ch.SetBranchAddress("mcwei",    &mcwei_);
      ch.SetBranchAddress("totSF",    &totSF_);
      ch.SetBranchAddress("HZgVBF",   &HZgVBF);
      ch.SetBranchAddress("HZgMVA",   &HZgMVA);
      ch.SetBranchAddress("mllgpt",  &mllgpt);
      ch.SetBranchAddress("phoR9",   &gR9_);
      ch.SetBranchAddress("phoSCEta",  &gSCEta_);
      ch.SetBranchAddress("lepEta",  lepEta_);
      ch.SetBranchAddress("lepSCEta",  lepSCEta_);
      ch.SetBranchAddress("mllg",    &mllg_);
      ch.SetBranchAddress("REFITmllg",    &REFITmllg_);
      //ch.SetBranchAddress("MET",    &MET);
      //ch.SetBranchAddress("bCsv2",    &bCsv2);
      int newcat = -1;
      float yields = 0.;
      for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
	{
	  ch.GetEntry(ev);
	  newcat = -999; 
	  totwei = mcwei_*genwei_*totSF_*puwei_;      

	  int j = (type=="mu")? 1:0;
	  
	  float lepEta0 = (lepSCEta_[0]==-5)? lepEta_[0]:lepSCEta_[0];
	  float lepEta1 = (lepSCEta_[1]==-5)? lepEta_[1]:lepSCEta_[1];
	  //newcat = cat16_limit(j, cat, gR9_, gSCEta_, lepEta0, lepEta1,mllgpt);
     
	  //newcat = cat_VHMVA(j,period,cat,isboost,isbtag,HZgMVA,HZgVBF,mllgpt,MET,bCsv2);
	  /*if(isboost==false){
	    if(mllg_>170||mllg_<115) continue;
	    //if(phoPt<20||lepPt[0]<25||lepPt[1]<20)continue;
	    newcat = cat_cutbase(j,cat, gR9_,gSCEta_,lepEta0,lepEta1, mllgpt);
	    if(catcut==newcat)yields = yields + 1.*totwei;}//newcat = cat;
	    //MVA cat
	    else {*/
	  if(REFITmllg_>170||REFITmllg_<115) continue;
	  //if(REFITmllg_>170||REFITmllg_<115) continue;
	  newcat = cat_MVA(j,period,cat,isboost,HZgMVA,HZgVBF,kincut,VBFcut,mllgpt);	  
	  if(catcut==6789&&newcat==6789)yields = yields + 1.*totwei;
	  if(catcut==501&&newcat==501) yields = yields + 1.*totwei;
	  //if(catcut==11&&newcat==11) yields = yields + 1.*totwei;
	  if(catcut==502&&newcat==502) yields = yields + 1.*totwei;
	  if(isboost==1&&catcut==10&&newcat==10)yields = yields + 1.*totwei;
	  if(catcut<7&&newcat==-1&&HZgMVA>=kindown&&HZgMVA<kinup)yields = yields + 1.*totwei;//MVA cat 
	  //}
	  //if(newcat==-99)continue;//discard event with kinMVA pre

	  //2016 cutbased
	  
	}
      yield<<yields<<endl;
      cout<<yields<<endl;
    }
}

void  make_Sig(string vername, string fin, string channel, int period, int m, string type ,int catcut, bool isboost, float kinup, float kindown,float kincut, float VBFcut)
{
  char inpathele[500],inpathmu[500],outpath[500];
  //sprintf(inpathele, "/eos/user/m/milee/unc_files/mc_%s_ele_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
  sprintf(inpathele, "/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
  //sprintf(inpathmu, "/eos/user/m/milee/unc_files/mc_%s_mu_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
  sprintf(inpathmu, "/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
  if (/*(channel =="ggF")||*/(channel=="ggF" && m==125))
    {
      
      sprintf(inpathele, "/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
      sprintf(inpathmu, "/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_%s_%dGeV.root",fin.c_str(),channel.c_str(),m);
      
    }

  TChain ch("tZg");
  if(type=="ele"||type=="ele_mu")ch.Add(inpathele);
  if(type=="mu"||type=="ele_mu")ch.Add(inpathmu);
  if(channel=="W*H") channel = "WH";
  sprintf(outpath,"/afs/cern.ch/work/m/milee/MYcode/limit/sig/%s%s/HiggsMass_signal_%s_%s_%s_%d_%d.txt",fin.c_str(), vername.c_str(), fin.c_str(),type.c_str(),channel.c_str(),catcut,m);
  //sprintf(outpath,"/afs/cern.ch/work/m/milee/MYcode/uncertainty/sig/%s%s/HiggsMass_signal_%s_%s_%s_%d_%d.txt",fin.c_str(), vername.c_str(), fin.c_str(),type.c_str(),channel.c_str(),catcut,m);
  ofstream sig(outpath);
  Int_t run_,lumis_, cat, alepCh, lepCh_[2],totmatch,totalev,mcev,isbtag;
  Long64_t  event_;
  Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,HZgVBF,HZgMVA,ZgPTt,sfedz_[2],mllgpt,gR9_,gSCEta_,lepEta_[2],lepSCEta_[2],REFITmllg_,MET,bCsv2,phoPt,lepPt[2];
  double totwei;
  ch.SetBranchAddress("run",      &run_);
  ch.SetBranchAddress("event",    &event_);
  ch.SetBranchAddress("lumis",    &lumis_);
  ch.SetBranchAddress("cat",      &cat);
  ch.SetBranchAddress("phoPt",    &phoPt);
  ch.SetBranchAddress("lepPt",    lepPt);
  ch.SetBranchAddress("isbtag",   &isbtag);
  ch.SetBranchAddress("puwei",    &puwei_);
  ch.SetBranchAddress("genwei",   &genwei_);
  ch.SetBranchAddress("mcwei",    &mcwei_);
  ch.SetBranchAddress("totSF",    &totSF_);
  ch.SetBranchAddress("HZgVBF",   &HZgVBF);
  ch.SetBranchAddress("HZgMVA",   &HZgMVA);
  ch.SetBranchAddress("ZgPTt",    &ZgPTt);
  ch.SetBranchAddress("mllgpt",  &mllgpt);
  ch.SetBranchAddress("phoR9",   &gR9_);
  ch.SetBranchAddress("phoSCEta",  &gSCEta_);
  ch.SetBranchAddress("lepEta",  lepEta_);
  ch.SetBranchAddress("lepSCEta",  lepSCEta_);
  ch.SetBranchAddress("mllg",    &mllg_);
  ch.SetBranchAddress("REFITmllg",    &REFITmllg_);
  ch.SetBranchAddress("MET",     &MET);
  ch.SetBranchAddress("bCsv2",     &bCsv2);

  int hi = 0;
  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
      totwei = mcwei_*genwei_*totSF_*puwei_;
      int j = (lepSCEta_[0]==-5)? 1:0;
      int newcat = -999;
      //if(phoPt<20||lepPt[0]<25||lepPt[1]<20)continue;
      float lepEta0 = (lepSCEta_[0]==-5)? lepEta_[0]:lepSCEta_[0];
      float lepEta1 = (lepSCEta_[1]==-5)? lepEta_[1]:lepSCEta_[1];
      
      //newcat = cat16_limit(j, cat, gR9_, gSCEta_, lepEta0, lepEta1,REFITmllgpt);

      //newcat = cat;
      //newcat = cat_VHMVA(j,period,cat,isboost,isbtag,HZgMVA,HZgVBF,mllgpt,MET,bCsv2);
      /*if(isboost==false){
	if(mllg_>170||mllg_<115) continue;
	newcat = cat_cutbase(j,cat, gR9_,gSCEta_,lepEta0,lepEta1, mllgpt);
	if(catcut==newcat)sig<<mllg_<<" "<<totwei<<endl;
	cout<<"cut"<<endl;
	}
	else 
	{ 
	cout<<"not cut"<<endl;*/
      //if(mllg_>170||mllg_<115) continue;
      if(REFITmllg_>170||REFITmllg_<115) continue;
      newcat = cat_MVA(j,period,cat,isboost,HZgMVA,HZgVBF,kincut,VBFcut,mllgpt);
      if(catcut==6789&&newcat==6789)sig<<REFITmllg_<<" "<<totwei<<endl;
      if(catcut==501&&newcat==501) sig<<REFITmllg_<<" "<<totwei<<endl;
      //if(catcut==11&&newcat==11)sig<<REFITmllg_<<" "<<totwei<<endl;
      if(catcut==502&&newcat==502) sig<<REFITmllg_<<" "<<totwei<<endl;
      if(isboost==1&&catcut==10&&newcat==10)sig<<REFITmllg_<<" "<<totwei<<endl;
      if(catcut<7&&newcat==-1&&HZgMVA>=kindown&&HZgMVA<kinup)sig<<REFITmllg_<<" "<<totwei<<endl;  
      //}
      //if(newcat==-99)continue;//discard event with kinMVA pre

      /*if(catcut==1&&newcat==1)sig<<REFITmllg_<<" "<<totwei<<endl;
	if(catcut==2&&newcat==2)sig<<REFITmllg_<<" "<<totwei<<endl;
	if(catcut==3&&newcat==3)sig<<REFITmllg_<<" "<<totwei<<endl;
	if(catcut==4&&newcat==4)sig<<REFITmllg_<<" "<<totwei<<endl;*/

    }
}


///get the parameters of interpolation
void IntParams(Int_t m1, Int_t m2, Int_t mass, RooWorkspace w1, RooWorkspace w2, RooWorkspace *w, string type, string channel, string m, string cat, int period)
{
    
  double a = (double(m2) - double(mass)) / (double(m2) - double(m1));
  double b = 1 - a;
  RooRealVar CMS_hzg_mass("CMS_hzg_mass", "CMS_hzg_mass", 115, 170, "GeV");
  //m1
  float fitResult_sigmaGau1,fitResult_sigmaCB1, fitResult_mean1, fitResult_alpha1,fitResult_power1, fitResult_frac_G1;
  string name = type+"_"+channel+"_m"+std::to_string(m1)+"_cat"+cat+"_"+std::to_string(period);

  fitResult_sigmaGau1 = (w1.var(Form("sigma_Gau_%s",name.c_str())))->getVal();
  fitResult_sigmaCB1 = (w1.var(Form("sigma_CB_%s",name.c_str())))->getVal();
  fitResult_mean1 = (w1.var(Form("mean_%s",name.c_str())))->getVal();
  fitResult_alpha1 = (w1.var(Form("alpha_%s",name.c_str())))->getVal();
  fitResult_power1 = (w1.var(Form("n_%s",name.c_str())))->getVal();
  fitResult_frac_G1 = (w1.var(Form("frac_G1_%s",name.c_str())))->getVal();
  float error_sigmaGau1,error_sigmaCB1, error_mean1, error_alpha1,error_power1, error_frac_G1;
  //ERROR
  error_sigmaGau1 = (w1.var(Form("sigma_Gau_%s",name.c_str())))->getError();
  error_sigmaCB1 = (w1.var(Form("sigma_CB_%s",name.c_str())))->getError();
  error_mean1 = (w1.var(Form("mean_%s",name.c_str())))->getError();
  error_alpha1 = (w1.var(Form("alpha_%s",name.c_str())))->getError();
  error_power1 = (w1.var(Form("n_%s",name.c_str())))->getError();
  error_frac_G1 = (w1.var(Form("frac_G1_%s",name.c_str())))->getError();
  //m2
  float fitResult_sigmaGau2,fitResult_sigmaCB2,  fitResult_mean2, fitResult_alpha2,fitResult_power2, fitResult_frac_G2;
  name = type+"_"+channel+"_m"+std::to_string(m2)+"_cat"+cat+"_"+std::to_string(period);
  fitResult_sigmaGau2 = (w2.var(Form("sigma_Gau_%s",name.c_str())))->getVal();
  fitResult_sigmaCB2 = (w2.var(Form("sigma_CB_%s",name.c_str())))->getVal();
  fitResult_mean2 = (w2.var(Form("mean_%s",name.c_str())))->getVal();
  fitResult_alpha2 = (w2.var(Form("alpha_%s",name.c_str())))->getVal();
  fitResult_power2 = (w2.var(Form("n_%s",name.c_str())))->getVal();
  fitResult_frac_G2 = (w2.var(Form("frac_G1_%s",name.c_str())))->getVal();
    
  float error_sigmaGau2, error_sigmaCB2, error_mean2, error_alpha2, error_power2, error_frac_G2;

  error_sigmaGau2 = (w2.var(Form("sigma_Gau_%s",name.c_str())))->getError();
  error_sigmaCB2 = (w2.var(Form("sigma_CB_%s",name.c_str())))->getError();
  error_mean2 = (w2.var(Form("mean_%s",name.c_str())))->getError();
  error_alpha2 = (w2.var(Form("alpha_%s",name.c_str())))->getError();
  error_power2 = (w2.var(Form("n_%s",name.c_str())))->getError();
  error_frac_G2 = (w2.var(Form("frac_G1_%s",name.c_str())))->getError();
  //INTERPOLATION
  name = type+"_"+channel+"_m"+m+"_cat"+cat+"_"+std::to_string(period);//interpolate
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

  w->import(ISig_bin2, RenameAllNodes(name.c_str()), RenameAllVariablesExcept(name.c_str(),"CMS_hzg_mass"));

  w->defineSet("SigPdfParams",
	       RooArgSet(
			 *w->var(Form("meanfr_%s",name.c_str())),
			 *w->var(Form("sigmaGaufr_%s",name.c_str())),
			 *w->var(Form("sigmaCBfr_%s",name.c_str())),
			 *w->var(Form("powerfr_%s",name.c_str())),
			 *w->var(Form("alphafr_%s",name.c_str())),
			 *w->var(Form("fracG1fr_%s",name.c_str()))));
  SetConstantParams(w->set("SigPdfParams"));
  w->pdf(TString::Format("ISig_bin2_%s",name.c_str()));
  if(type=="mu"||type== "ele_mu")
    {
			
      w->factory(Form("CMS_hzg_delta_muRoch_mean_%s[1]",name.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_mean_%s[0]",name.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_muPho_mean_%s[0]",name.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
	 
      w->factory(Form("CMS_hzg_delta_muRoch_sigma_%s[1]",name.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_sigma_%s[0]",name.c_str()));
      w->factory(Form("CMS_hzg_delta_muPho_sigma_%s[0]",name.c_str()));

      w->factory(Form("prod::mean_corr_%s(meanfr_%s,sum::CMS_hzg_delta_mu_mean_%s(CMS_hzg_delta_muRoch_mean_%s, CMS_hzg_delta_muEM_mean_%s, CMS_hzg_delta_muPho_mean_%s))",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));
      w->factory(Form("prod::sigma_corr_%s(sigmaCBfr_%s, sum::CMS_hzg_delta_mu_sigma_%s(CMS_hzg_delta_muRoch_sigma_%s, CMS_hzg_delta_muEM_sigma_%s, CMS_hzg_delta_muPho_sigma_%s))",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));

      w->factory(Form("EDIT::newPdf_%s(ISig_bin2_%s,meanfr_%s=mean_corr_%s, sigmaCBfr_%s=sigma_corr_%s)",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));
	 
    }

  ///em scale 
  if(type=="ele")
    {
      w->factory(Form("CMS_hzg_delta_eleEM_mean_%s[1]",name.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_elePho_mean_%s[0]",name.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod

      w->factory(Form("CMS_hzg_delta_eleEM_sigma_%s[1]",name.c_str()));
      w->factory(Form("CMS_hzg_delta_elePho_sigma_%s[0]",name.c_str()));

	 
      w->factory(Form("prod::mean_corr_%s(meanfr_%s,sum::CMS_hzg_delta_ele_mean_%s(CMS_hzg_delta_eleEM_mean_%s, CMS_hzg_delta_elePho_mean_%s))",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));
      w->factory(Form("prod::sigma_corr_%s(sigmaCBfr_%s,sum::CMS_hzg_delta_ele_sigma_%s(CMS_hzg_delta_eleEM_sigma_%s, CMS_hzg_delta_elePho_sigma_%s))",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));

      w->factory(Form("EDIT::newPdf_%s(ISig_bin2_%s,meanfr_%s=mean_corr_%s, sigmaCBfr_%s=sigma_corr_%s)",name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str(),name.c_str()));
    } 
  
 
}

void interpolate2(string vername, string fin, string type, string channel, int catcut, int period)
{
  TCanvas* c1 = new  TCanvas("c1", "", 800, 600);
  c1->cd();
  Int_t massPts[3] = { 120, 125, 130 };
  string name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  RooPlot* xframe;
  //RooWorkspace wspace[11];
  int index = 0;
  if(channel=="W*H")channel= "WH";
  string cat = to_string(catcut);
  for (int m = 0; m < 2; m++) //start with 0
    {

      for (int k = 1; k < 5; k++) //start with 1
        {
	  Int_t m1 = massPts[m];
	  Int_t m2 = massPts[m + 1];
	  Int_t mass = massPts[m] + k;
	
	  string txtname = "sig/"+ fin  + vername  + "/HiggsMass_signal_" + fin+ "_" +type + "_" + channel + "_" + cat + "_" + std::to_string(massPts[m]) + ".txt";
	  string txtname2 = "sig/" + fin + vername + "/HiggsMass_signal_" + fin +"_" + type + "_" + channel + "_" + cat + "_" + std::to_string(massPts[m+1]) + ".txt";

	  RooWorkspace w1, w2, w;
	  RooFitResult sig1, sig2;
	  
	  sigfit(txtname, m1, &sig1, &w1, channel, type, cat, fin,vername,period);
	  sigfit(txtname2, m2, &sig2, &w2, channel, type, cat, fin,vername,period);
	  RooAbsPdf *pdf1, *pdf2;
	  w1.Print();
	  pdf1 = (w1.pdf(Form("Sig_bin2_%s_%s_m%d_cat%s_%d",type.c_str(),channel.c_str(),m1,cat.c_str(),period)));
	  pdf2 = (w2.pdf(Form("Sig_bin2_%s_%s_m%d_cat%s_%d",type.c_str(),channel.c_str(),m2,cat.c_str(),period)));
	  RooRealVar *mH1 = w1.var("CMS_hzg_mass");
	  RooRealVar *mH2 = w2.var("CMS_hzg_mass");
	  if (m == 0 && k == 1)
            {
	      xframe = mH1->frame(Title("Signal MC and the Fit"));
	      xframe->SetAxisRange(115, 170, "X");
	      pdf1->plotOn(xframe, Binning(55), LineColor(1));
	      pdf2->plotOn(xframe, Binning(55), LineColor(46));
	      string w1path = "PDFs/"+ fin + vername +"/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_120_" + std::to_string(period)+ ".root";
	      string w2path = "PDFs/" + fin + vername +"/WS_" + fin+ "_" +type + "_" + channel + "_" + cat + "_125_" + std::to_string(period)+ ".root";
	      const char *w1out = w1path.c_str();
	      const char *w2out = w2path.c_str();
	      w1.writeToFile(w1out);
	      w2.writeToFile(w2out);
	    }
	  if (m == 1 && k == 1)

            {
	      pdf2->plotOn(xframe, Binning(55), LineColor(41));
	      string w2path = "PDFs/" + fin + vername + "/WS_" + fin+ "_" + type + "_" + channel + "_" + cat + "_130_"+ std::to_string(period)+ ".root";
	      const char *w2out = w2path.c_str();
	      w2.writeToFile(w2out);
	    }

	  if(index<4)IntParams(m1, m2, mass, w1, w2, &w, type, channel,name[index+1],cat,period);
	  else IntParams(m1, m2, mass, w1, w2, &w, type, channel,name[index+2],cat,period);
	  RooRealVar *mH = w.var("CMS_hzg_mass");
	  int icol[] = { 2, 3, 4, 5, 6, 7, 8, 9, 40};
	  RooAbsPdf *pdf;
	  if (index <  4)
	    {
	      pdf = (w.pdf(Form("ISig_bin2_%s_%s_m%s_cat%s_%d",type.c_str(),channel.c_str(),name[index+1].c_str(),cat.c_str(),period)));
	      pdf->plotOn(xframe, LineColor(icol[index]));
	      string wpath = "PDFs/" + fin + vername + "/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_" + name[index + 1] +"_"+std::to_string(period)+".root";
	      const char * wout = wpath.c_str();
	      w.writeToFile(wout);
	    }
	  if (index >= 4)
	    {
	      pdf = (w.pdf(Form("ISig_bin2_%s_%s_m%s_cat%s_%d",type.c_str(),channel.c_str(),name[index+2].c_str(),cat.c_str(),period)));
	      pdf->plotOn(xframe, LineColor(icol[index]));
	      string wpath = "PDFs/" + fin + vername + "/WS_" +  fin+ "_" +type + "_" + channel + "_" + cat + "_" + name[index + 2] +"_"+std::to_string(period)+".root";
	      const char * wout = wpath.c_str();
	      w.writeToFile(wout);
	    }
	  index++;
        }
    }
  c1->cd();
  xframe->Draw();
  gPad->SetLogy();
  string figpath = "plot/fit/"+fin+ vername+"/interpolate_log_" + fin+ "_" + type + "_" + channel + "_" + cat + ".png";
  const char * fig = figpath.c_str();
  c1->SaveAs(fig); 

}

double IntSigRate(int m, double accEff1, double accEff2)
{
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  const char* name2 = name[m];
  double mass = 120. + double(m);
  double m1, m2;
  if (mass < 125.)
    {
      m1 = 120.;
      m2 = 125.;
    }
  if (mass > 125.)
    {
      m1 = 125.;
      m2 = 130.;
    }
  double sigRate;
  if (mass == 120. || mass == 125.) sigRate = accEff1;
  else if (mass == 130.) sigRate = accEff2;
  if (mass != 120. && mass != 125. && mass != 130.)
    {
      double a = (double(m2) - double(mass)) / (double(m2) - double(m1));
      double b = 1 - a;
      double IaccEff = a*accEff1 + b*accEff2;
      sigRate = IaccEff;
    }
  return sigRate;
}
#endif
