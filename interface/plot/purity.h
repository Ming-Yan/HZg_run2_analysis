#include "../../plugin/tdrstyle.C"
#include "../../plugin/CMS_lumi.C"
#include "../../limit/cat.h"
#include <iostream>
#include <TH1F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TTree.h>
#include <TPad.h>
#include <TFile.h>
#include <TSystem.h>
void purity(const char* vername, const char* outfile,string* category, const int ibin)
{
  setTDRStyle();
  TChain ggF("tZg");
  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV.root",vername));
  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV.root",vername));
  TChain VBF("tZg");
  VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_VBF_125GeV_ext1.root",vername));
  VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_VBF_125GeV_ext1.root",vername));
  TChain ttH("tZg");
  ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ttH_125GeV.root",vername));
  ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ttH_125GeV.root",vername));
  TChain ZH("tZg");
  ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ZH_125GeV.root",vername));
  ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ZH_125GeV.root",vername));
  TChain WH("tZg");
  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WplusH_125GeV.root",vername));
  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WminusH_125GeV.root",vername));
  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WplusH_125GeV.root",vername));
  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WminusH_125GeV.root",vername));
  Int_t run_,lumis_, cat, alepCh, lepCh_[2],totmatch,totalev,mcev,isbtag;
  Long64_t  event_;
  Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,HZgVBF,HZgMVA,ZgPTt,sfedz_[2],mllgpt,gR9_,gSCEta_,lepEta_[2],lepSCEta_[2]    ,REFITmllg_,MET, bCsv2;
  double totwei;
  ggF.SetBranchAddress("cat",      &cat);
  ggF.SetBranchAddress("puwei",    &puwei_);
  ggF.SetBranchAddress("genwei",   &genwei_);
  ggF.SetBranchAddress("mcwei",    &mcwei_);
  ggF.SetBranchAddress("totSF",    &totSF_);
  ggF.SetBranchAddress("HZgVBF",   &HZgVBF);
  ggF.SetBranchAddress("HZgMVA",   &HZgMVA);
  ggF.SetBranchAddress("mllgpt",   &mllgpt);
  ggF.SetBranchAddress("phoR9",    &gR9_);
  ggF.SetBranchAddress("phoSCEta", &gSCEta_);
  ggF.SetBranchAddress("lepEta",   lepEta_);
  ggF.SetBranchAddress("lepSCEta", lepSCEta_);
  ggF.SetBranchAddress("mllg",     &mllg_);
  ggF.SetBranchAddress("isbtag",   &isbtag);
  ggF.SetBranchAddress("bCsv2",   &bCsv2);
  ggF.SetBranchAddress("MET",   &MET);
  VBF.SetBranchAddress("cat",      &cat);
  VBF.SetBranchAddress("puwei",    &puwei_);
  VBF.SetBranchAddress("genwei",   &genwei_);
  VBF.SetBranchAddress("mcwei",    &mcwei_);
  VBF.SetBranchAddress("totSF",    &totSF_);
  VBF.SetBranchAddress("HZgVBF",   &HZgVBF);
  VBF.SetBranchAddress("HZgMVA",   &HZgMVA);
  VBF.SetBranchAddress("mllgpt",   &mllgpt);
  VBF.SetBranchAddress("phoR9",    &gR9_);
  VBF.SetBranchAddress("phoSCEta", &gSCEta_);
  VBF.SetBranchAddress("lepEta",   lepEta_);
  VBF.SetBranchAddress("lepSCEta", lepSCEta_);
  VBF.SetBranchAddress("mllg",     &mllg_);
  VBF.SetBranchAddress("isbtag",   &isbtag);
  VBF.SetBranchAddress("bCsv2",   &bCsv2);
  VBF.SetBranchAddress("MET",   &MET);
  ttH.SetBranchAddress("cat",      &cat);
  ttH.SetBranchAddress("puwei",    &puwei_);
  ttH.SetBranchAddress("genwei",   &genwei_);
  ttH.SetBranchAddress("mcwei",    &mcwei_);
  ttH.SetBranchAddress("totSF",    &totSF_);
  ttH.SetBranchAddress("HZgVBF",   &HZgVBF);
  ttH.SetBranchAddress("HZgMVA",   &HZgMVA);
  ttH.SetBranchAddress("mllgpt",   &mllgpt);
  ttH.SetBranchAddress("phoR9",    &gR9_);
  ttH.SetBranchAddress("phoSCEta", &gSCEta_);
  ttH.SetBranchAddress("lepEta",   lepEta_);
  ttH.SetBranchAddress("lepSCEta", lepSCEta_);
  ttH.SetBranchAddress("mllg",     &mllg_);
  ttH.SetBranchAddress("isbtag",   &isbtag);
  ttH.SetBranchAddress("bCsv2",   &bCsv2);
  ttH.SetBranchAddress("MET",   &MET);
  ZH.SetBranchAddress("cat",      &cat);
  ZH.SetBranchAddress("puwei",    &puwei_);
  ZH.SetBranchAddress("genwei",   &genwei_);
  ZH.SetBranchAddress("mcwei",    &mcwei_);
  ZH.SetBranchAddress("totSF",    &totSF_);
  ZH.SetBranchAddress("HZgVBF",   &HZgVBF);
  ZH.SetBranchAddress("HZgMVA",   &HZgMVA);
  ZH.SetBranchAddress("mllgpt",   &mllgpt);
  ZH.SetBranchAddress("phoR9",    &gR9_);
  ZH.SetBranchAddress("phoSCEta", &gSCEta_);
  ZH.SetBranchAddress("lepEta",   lepEta_);
  ZH.SetBranchAddress("lepSCEta", lepSCEta_);
  ZH.SetBranchAddress("mllg",     &mllg_);
  ZH.SetBranchAddress("isbtag",   &isbtag);
  ZH.SetBranchAddress("bCsv2",   &bCsv2);
  ZH.SetBranchAddress("MET",   &MET);
  WH.SetBranchAddress("cat",      &cat);
  WH.SetBranchAddress("puwei",    &puwei_);
  WH.SetBranchAddress("genwei",   &genwei_);
  WH.SetBranchAddress("mcwei",    &mcwei_);
  WH.SetBranchAddress("totSF",    &totSF_);
  WH.SetBranchAddress("HZgVBF",   &HZgVBF);
  WH.SetBranchAddress("HZgMVA",   &HZgMVA);
  WH.SetBranchAddress("mllgpt",   &mllgpt);
  WH.SetBranchAddress("phoR9",    &gR9_);
  WH.SetBranchAddress("phoSCEta", &gSCEta_);
  WH.SetBranchAddress("lepEta",   lepEta_);
  WH.SetBranchAddress("lepSCEta", lepSCEta_);
  WH.SetBranchAddress("mllg",     &mllg_);
  WH.SetBranchAddress("isbtag",   &isbtag);
  WH.SetBranchAddress("bCsv2",   &bCsv2);
  WH.SetBranchAddress("MET",   &MET);
  vector<TH1F*> hggF, hVBF, hWH,httH, hZH;
  vector<TH1F*> all;
  float norm_ggF[ibin],norm_VBF[ibin],norm_ttH[ibin],norm_WH[ibin],norm_ZH[ibin],norm_total[ibin];
  TCanvas *c = new TCanvas("c", "c", 1500,1000);
  c->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.0);
  pad1->Draw();
  pad1->cd();
  for(int j = 0; j < 5; j++)
    {
      all.push_back(new TH1F(Form("all[%d]",j),"",ibin,0,ibin));
    }
  TCut catcut;
  for(int i = 0; i <ibin ; i++)
    {
      hggF.push_back(new TH1F(Form("hggF[%d]",i),"",55,115,170));
      hVBF.push_back(new TH1F(Form("hVBF[%d]",i),"",55,115,170));
      hZH.push_back(new TH1F(Form("hZH[%d]",i),"",55,115,170));
      httH.push_back(new TH1F(Form("httH[%d]",i),"",55,115,170));
      hWH.push_back(new TH1F(Form("hWH[%d]",i),"",55,115,170));
      for(Long64_t a = 0 ; a < ggF.GetEntriesFast(); a++)
	{
	  ggF.GetEntry(a);
          int newcat = -999;
          totwei = mcwei_*genwei_*totSF_*puwei_;
          if(mllg_>170||mllg_<115) continue;
	  int j = (lepSCEta_[0]==-5)? 1:0;
	  newcat = cat_VHMVA(j, 16, cat, 1 ,isbtag,HZgMVA, HZgVBF, mllgpt, MET, bCsv2);
	  if(newcat==-1)continue;
	  if(i==newcat)hggF[i]->Fill(mllg_,totwei);
	    
	    // if(newcat==-99)continue;//discard event with kinMVA pre
          /*if(i==0&&cat>5&&cat<10)hggF[i]->Fill(mllg_,totwei);//lepton tag
          if(i==1&&cat==5&&HZgVBF>0.06)hggF[i]->Fill(mllg_,totwei);//VBF-vbf
	  if(i==2&&(cat==10||cat<6)&&HZgVBF<=0.06&&((bCsv2!=-99&&bCsv2<=0.9535&&MET>30)))hggF[i]->Fill(mllg_,totwei);//bmet-tag(VH)
          if(i==3&&cat==5&&HZgVBF<=0.06&&HZgVBF>-0.06&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//VBF-ggf
	  
	  if(i==4&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt>=60&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//boost
          if(i==5&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&HZgMVA>0.1&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//inclusive1 
          if(i==6&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.1&&HZgMVA>0.05751&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//inclusive 2
          if(i==7&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.05751&&HZgMVA>0.01785&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//inclusive 3
          if(i==8&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&bCsv2<=0.9535&&MET<=30)hggF[i]->Fill(mllg_,totwei);//inclusive 4*/
	  //if(i==7&&newcat==3)hggF[i]->Fill(mllg_,totwei);
          //if(i==8&&newcat==4)hggF[i]->Fill(mllg_,totwei);
	}
      cout<<i<<" "<<hggF[i]->Integral()<<endl;
      for(Long64_t b = 0 ; b < VBF.GetEntriesFast(); b++)
	{
	  VBF.GetEntry(b);
          int newcat = -999;
          totwei = mcwei_*genwei_*totSF_*puwei_;
	  // cout<<totwei<<endl;
          if(mllg_>170||mllg_<115) continue;
int j = (lepSCEta_[0]==-5)? 1:0;
	  newcat = cat_VHMVA(j, 16, cat, 1 ,isbtag,HZgMVA, HZgVBF, mllgpt, MET, bCsv2);
	  if(newcat==-1)continue;
	  if(i==newcat)hVBF[i]->Fill(mllg_,totwei);
	  /*          if(i==0&&cat>5&&cat<10)hVBF[i]->Fill(mllg_,totwei);//lepton tag
          if(i==1&&cat==5&&HZgVBF>0.06)hVBF[i]->Fill(mllg_,totwei);//VBF-vbf
	  if(i==2&&(cat==10||cat<6)&&HZgVBF<=0.06&&(bCsv2>0.9535||(bCsv2<=0.9535&&MET>30)))hVBF[i]->Fill(mllg_,totwei);//bmet-tag(VH)
          if(i==3&&cat==5&&HZgVBF<=0.06&&HZgVBF>-0.06&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//VBF-ggf
	  if(i==4&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt>=60&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//boost
          if(i==5&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&HZgMVA>0.1&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//inclusive1 
          if(i==6&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.1&&HZgMVA>0.05751&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//inclusive 2
          if(i==7&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.05751&&HZgMVA>0.01785&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//inclusive 3
          if(i==8&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&bCsv2<=0.9535&&MET<=30)hVBF[i]->Fill(mllg_,totwei);//inclusive 4*/
	}
      for(Long64_t c = 0 ; c < ttH.GetEntriesFast(); c++)
	{
	  ttH.GetEntry(c);
          int newcat = -999;
          totwei = mcwei_*genwei_*totSF_*puwei_;
          if(mllg_>170||mllg_<115) continue;
	  int j = (lepSCEta_[0]==-5)? 1:0;
          newcat = cat_VHMVA(j, 16, cat, 1 ,isbtag,HZgMVA, HZgVBF, mllgpt, MET, bCsv2);
          if(newcat==-1)continue;
          if(i==newcat)httH[i]->Fill(mllg_,totwei);
	  /*
          if(i==0&&cat>5&&cat<10)httH[i]->Fill(mllg_,totwei);//lepton tag
          if(i==1&&cat==5&&HZgVBF>0.06)httH[i]->Fill(mllg_,totwei);//VBF-vbf
	  if(i==2&&(cat==10||cat<6)&&HZgVBF<=0.06&&(bCsv2>0.9535||(bCsv2<=0.9535&&MET>30)))httH[i]->Fill(mllg_,totwei);//bmet-tag(VH)
          if(i==3&&cat==5&&HZgVBF<=0.06&&HZgVBF>-0.06&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//VBF-ggf
	  if(i==4&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt>=60&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//boost
          if(i==5&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&HZgMVA>0.1&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//inclusive1 
          if(i==6&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.1&&HZgMVA>0.05751&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//inclusive 2
          if(i==7&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.05751&&HZgMVA>0.01785&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//inclusive 3
          if(i==8&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&bCsv2<=0.9535&&MET<=30)httH[i]->Fill(mllg_,totwei);//inclusive 4*/
	}
      for(Long64_t d = 0 ; d < ZH.GetEntriesFast(); d++)
	{
	  ZH.GetEntry(d);
          int newcat = -999;
          totwei = mcwei_*genwei_*totSF_*puwei_;
          if(mllg_>170||mllg_<115) continue;
	  int j = (lepSCEta_[0]==-5)? 1:0;
          newcat = cat_VHMVA(j, 16, cat, 1 ,isbtag,HZgMVA, HZgVBF, mllgpt, MET, bCsv2);
          if(newcat==-1)continue;
          if(i==newcat)hZH[i]->Fill(mllg_,totwei);
	  /*
          if(i==0&&cat>5&&cat<10)hZH[i]->Fill(mllg_,totwei);//lepton tag
          if(i==1&&cat==5&&HZgVBF>0.06)hZH[i]->Fill(mllg_,totwei);//VBF-vbf
	  if(i==2&&(cat==10||cat<6)&&HZgVBF<=0.06&&(bCsv2>0.9535||(bCsv2<=0.9535&&MET>30)))hZH[i]->Fill(mllg_,totwei);//bmet-tag(VH)
          if(i==3&&cat==5&&HZgVBF<=0.06&&HZgVBF>-0.06&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//VBF-ggf
	  if(i==4&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt>=60&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//boost
          if(i==5&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&HZgMVA>0.1&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//inclusive1 
          if(i==6&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.1&&HZgMVA>0.05751&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//inclusive 2
          if(i==7&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.05751&&HZgMVA>0.01785&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//inclusive 3
          if(i==8&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&bCsv2<=0.9535&&MET<=30)hZH[i]->Fill(mllg_,totwei);//inclusive 4
	  */
	}
      for(Long64_t e = 0 ; e < WH.GetEntriesFast(); e++)
	{
	  WH.GetEntry(e);
          int newcat = -999;
          totwei = mcwei_*genwei_*totSF_*puwei_;
          if(mllg_>170||mllg_<115) continue;
	  int j = (lepSCEta_[0]==-5)? 1:0;
          newcat = cat_VHMVA(j, 16, cat, 1 ,isbtag,HZgMVA, HZgVBF, mllgpt, MET, bCsv2);
          if(newcat==-1)continue;
          if(i==newcat)hWH[i]->Fill(mllg_,totwei);
          /*if(i==0&&cat>5&&cat<10)hWH[i]->Fill(mllg_,totwei);//lepton tag
          if(i==1&&cat==5&&HZgVBF>0.06)hWH[i]->Fill(mllg_,totwei);//VBF-vbf
	  if(i==2&&(cat==10||cat<6)&&HZgVBF<=0.06&&(bCsv2>0.9535||(bCsv2<=0.9535&&MET>30)))hWH[i]->Fill(mllg_,totwei);//bmet-tag(VH)
          if(i==3&&cat==5&&HZgVBF<=0.06&&HZgVBF>-0.06&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//VBF-ggf
	  if(i==4&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt>=60&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//boost
          if(i==5&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&HZgMVA>0.1&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//inclusive1 
          if(i==6&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.1&&HZgMVA>0.05751&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//inclusive 2
          if(i==7&&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.05751&&HZgMVA>0.01785&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//inclusive 3
          if(i==8&mllgpt>60.&&(cat>9||cat<5)&&HZgVBF<=-0.06&&mllgpt<60.&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&bCsv2<=0.9535&&MET<=30)hWH[i]->Fill(mllg_,totwei);//inclusive 4*/
	}
      ///// normalized /////
		
      norm_total[i] = hggF[i]->Integral(-1,-1)+hVBF[i]->Integral(-1,-1)+httH[i]->Integral(-1,-1)+hZH[i]->Integral(-1,-1)+hWH[i]->Integral(-1,-1);
      norm_ggF[i] = hggF[i]->Integral(-1,-1)/norm_total[i];
      norm_VBF[i] = hVBF[i]->Integral(-1,-1)/norm_total[i];
      norm_ttH[i] = httH[i]->Integral(-1,-1)/norm_total[i];
      norm_ZH[i] = hZH[i]->Integral(-1,-1)/norm_total[i];
      norm_WH[i] = hWH[i]->Integral(-1,-1)/norm_total[i];
		
      // cout<<norm_total[i]<<" "<<norm_ggF[i]+norm_VBF[i]+norm_WH[i]+norm_ZH[i]+norm_ttH[i]<<endl;
    }
  for(int i = 0 ; i <ibin ; i++)
    {
      all[0]->SetBinContent(i+1,norm_ggF[i]);
      all[1]->SetBinContent(i+1,norm_VBF[i]);
      all[2]->SetBinContent(i+1,norm_ttH[i]);
      all[3]->SetBinContent(i+1,norm_ZH[i]);
      all[4]->SetBinContent(i+1,norm_WH[i]);
      all[0]->SetBarWidth(0.5);
      all[1]->SetBarWidth(0.5);
      all[2]->SetBarWidth(0.5);
      all[3]->SetBarWidth(0.5);
      all[4]->SetBarWidth(0.5);
      all[0]->SetBarOffset(0.25);
      all[1]->SetBarOffset(0.25);
      all[2]->SetBarOffset(0.25);
      all[3]->SetBarOffset(0.25);
      all[4]->SetBarOffset(0.25);
      // cout<<norm_ZH[i]<<endl;
    }
  all[0]->SetFillColor(kOrange+7);
  all[0]->SetLineColor(kOrange+7);
  all[1]->SetFillColor(kOrange-2);
  all[1]->SetLineColor(kOrange-2);
  all[2]->SetFillColor(kTeal+5);
  all[2]->SetLineColor(kTeal+5);
  all[3]->SetFillColor(kAzure+8);
  all[3]->SetLineColor(kAzure+8);
  all[4]->SetFillColor(kViolet-8);
  all[4]->SetLineColor(kViolet-8);
  THStack *st = new THStack("st","");
  st->Add(all[0]);
  st->Add(all[1]);
  st->Add(all[2]);
  st->Add(all[3]);
  st->Add(all[4]);
  st->SetMaximum(1.);
  st->SetMinimum(0);
  all[0]->GetYaxis()->SetTitle("Fraction(%)");
  for(int k = 1; k<ibin+1; k++)
    {
      all[0]->GetXaxis()->SetBinLabel(k, category[k-1].c_str());
    }
  st->Draw("hbar");
  // extraText  = "Preliminary";
  extraText  = "In Progress";
  lumi_13TeV = "";
  CMS_lumi(pad1, 4, 0);
  c->cd();
  TLegend *l = new TLegend(0.25,0.0,0.8,0.075);
  l->SetFillColor(0);
  l->SetTextSize(0.04);
  l->SetNColumns(5);
  l->AddEntry(all[0],"ggF","f");
  l->AddEntry(all[1],"VBF","f");
  l->AddEntry(all[2],"ttH","f");
  l->AddEntry(all[3],"ZH","f");
  l->AddEntry(all[4],"WH","f");
  l->Draw();
  c->Print(Form("plot/%s.png",outfile));
  c->Print(Form("plot/%s.pdf",outfile));
}

/*  LocalWords:  HZgMVA
 */
