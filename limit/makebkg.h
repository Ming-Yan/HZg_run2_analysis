#ifndef H_MAKEBKG
#define H_MAKEBKG
#include <iostream>
#include "cat.h"

void  make_bkg(string vername, TString fin, int period, int catcut, string type,bool isboost, float kinup, float kindown, float kincut, float VBFcut)
{
  char txt[500];
  sprintf(txt,"/afs/cern.ch/work/m/milee/MYcode/limit/bkg/%s%s/HiggsMass_%s_bkg_%s_cat%d_%d.txt",fin.Data(), vername.c_str(), fin.Data(),type.c_str(), catcut,period);

  ofstream sig(txt);
  TChain t("tZg");
  if(type=="ele"||type=="ele_mu")t.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_ele_EG.root",fin.Data()));
  if(type=="mu"||type=="ele_mu")t.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_mu_Mu.root",fin.Data()));
      Int_t run_,lumis_, cat, alepCh, lepCh_[2], lepMatch[2],phoMatch,isbtag;
      Long64_t  event_;
      Float_t totSF_, puwei_, mcwei_, genwei_,mllg_,mH,wei,mllgpt,lepEta_[2],lepSCEta_[2],gR9_,gSCEta_,REFITmllg_,lepPt[2],phoPt;
      Float_t HZgVBF,HZgMVA,ZgPTt,bCsv2,MET;
      double totwei=0;
      t.SetBranchAddress("run",      &run_);
      //if(catcut>10)t.SetBranchAddress("isbtag",      &isbtag);
      t.SetBranchAddress("lepPt",     lepPt);
      t.SetBranchAddress("phoPt",     &phoPt);
      t.SetBranchAddress("event",    &event_);
      t.SetBranchAddress("cat",      &cat);
      t.SetBranchAddress("isbtag",      &isbtag);
      t.SetBranchAddress("mllg",    &mllg_);
      t.SetBranchAddress("REFITmllg",    &REFITmllg_);
      t.SetBranchAddress("HZgVBF",  &HZgVBF);
      t.SetBranchAddress("HZgMVA",  &HZgMVA);
      t.SetBranchAddress("ZgPTt",   &ZgPTt);
      t.SetBranchAddress("mllgpt",  &mllgpt);
      t.SetBranchAddress("phoR9",   &gR9_);
      t.SetBranchAddress("phoSCEta",  &gSCEta_);
      t.SetBranchAddress("lepEta",  lepEta_);  
      t.SetBranchAddress("lepSCEta",  lepSCEta_);
      t.SetBranchAddress("MET",  &MET);
      t.SetBranchAddress("bCsv2",  &bCsv2);
      int newcat = -1;
      for ( Long64_t ev = 0; ev < t.GetEntriesFast(); ev++)
        {
	  t.GetEntry(ev);
	  newcat=-1;
	  if(REFITmllg_>170||REFITmllg_<115) continue;
	  //if(mllg_>170||mllg_<115) continue;
	  int j = (lepSCEta_[0]==-5)? 1 :0;
	  float lepEta0 = (lepSCEta_[0]==-5)?lepEta_[0] : lepSCEta_[0];
	  float lepEta1 = (lepSCEta_[1]==-5)?lepEta_[1] : lepSCEta_[1];
	  //if(phoPt<20||lepPt[0]<25||lepPt[1]<20)continue;
	  //newcat = cat_cutbase(j,cat, gR9_,gSCEta_,lepEta0,lepEta1, mllgpt);
	  //newcat = cat_MVAlimit(j, period, cat, gR9_, gSCEta_, lepEta0, lepEta1,mllgpt,HZgMVA,HZgVBF,kincut,VBFcut);
	  //newcat = cat16_limit(j,  cat, gR9_, gSCEta_, lepEta0, lepEta1,mllgpt);
	  newcat = cat_MVA(j,period, cat,isboost,HZgMVA,HZgVBF,kincut,VBFcut,mllgpt);
	  //newcat = cat_VHMVA(j,period, cat,isboost, isbtag, HZgMVA,HZgVBF,mllgpt,MET, bCsv2);
	  //newcat = cat_cutbase(j ,cat, gR9_, gSCEta_, lepEta0, lepEta1,mllgpt);
          ////2016 cutbased                                                                                
          //if(newcat==-99)continue;//discard event with kinMVA pre                                        
	  if(catcut==6789&&newcat==6789)sig<<REFITmllg_<<endl;
	  //if(catcut==5&&newcat==5) sig<<REFITmllg_<<endl;
	  if(catcut==501&&newcat==501) sig<<REFITmllg_<<endl;
	  if(catcut==11&&newcat==11)sig<<REFITmllg_<<endl;
	  if(catcut==502&&newcat==502) sig<<REFITmllg_<<endl;
          if(isboost==1&&catcut==10&&newcat==10)sig<<REFITmllg_<<endl;
	  if(catcut<7&&newcat==-1&&HZgMVA>=kindown&&HZgMVA<kinup)sig<<REFITmllg_<<endl;//MVA cat 
	  //if(catcut==newcat)sig<<mllg_<<endl;
	  //if(catcut!=6789&&catcut==newcat)sig<<mllg_<<endl;
	  //else if(catcut==6789&&cat>5&&cat<10)sig<<mllg_<<endl;

	}	  

      //f->Close("R");
      //f->Delete("*i*");
}
#endif
