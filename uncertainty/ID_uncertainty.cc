

#include "../plugin/sigmaEff.h"
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"
#include <iostream>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TTree.h>
#include <TPad.h>
#include <TFile.h>
#include <TSystem.h>
///0->ele, 1->ele

void ID_uncertainty()
{
  gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");
  string categories[9] = 
    {
      "(cat>5&&cat<10)",
      "HZgVBF>0.05&&cat==5",
      "HZgVBF<=0.05&&HZgVBF>-0.05&&cat==5",
      "HZgVBF<=-0.05&&mllgpt>60.",
      "HZgVBF<=-0.05&&HZgMVA>0.123&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.123&&HZgMVA>0.0956&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.0956&&HZgMVA>0.0545&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.0545&&HZgMVA>0.004&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.004&&HZgMVA>-0.0395&&mllgpt<=60"
    };
  //signal
  for (int i= 0 ; i <2; i++)
    {
      for (int cat = 0; cat <9 ; cat++)
	{
	  for (int mass = 0; mass <3 ; mass++)
	    {
	      int m = 120+ mass*5;
	      cout<<"mass: "<<mass<<" eleormu: "<<i<<" cat:"<<cat<<endl;
	      TChain ggF("tZg");
	      TChain VBF("tZg");
	      TChain ttH("tZg");
	      TChain ZH("tZg");
	      TChain WH("tZg");
	      if(i==0)
		{
		  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_ggF_%dGeV.root",m));
		  if(m==125)VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_VBF_%dGeV_ext1.root",m));
		  else VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_VBF_%dGeV.root",m));
		  ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_ttH_%dGeV.root",m));
		  ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_ZH_%dGeV.root",m));
		  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_WplusH_%dGeV.root",m));
		  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_ele_HZg_WminusH_%dGeV.root",m));   
		}
	      else if(i==1){
		ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_ggF_%dGeV.root",m));
		if(m==125)VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_VBF_%dGeV_ext1.root",m));
		else VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_VBF_%dGeV.root",m));
		ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_ttH_%dGeV.root",m));
		ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_ZH_%dGeV.root",m));
		WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_WplusH_%dGeV.root",m));
		WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v2_mu_HZg_WminusH_%dGeV.root",m));
	      }
	      TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
	      TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
	      TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
	      TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
	      TH1F *hsig5 = new TH1F("hsig5", " ",55, 115, 170);
      
	      vector<float> nom; nom.clear();
	      string fname;
	      if (i==0) fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat)+"_m"+  std::to_string(m)+".txt";
	      else  fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat)+"_m"+  std::to_string(m)+".txt";
	      ofstream out(fname.c_str(),  std::ios_base::out);
	      //nominal
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei",categories[cat].c_str()));nom.push_back(hsig1->Integral());
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei",categories[cat].c_str()));nom.push_back(hsig2->Integral());
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei",categories[cat].c_str()));nom.push_back(hsig3->Integral());
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei",categories[cat].c_str()));nom.push_back(hsig4->Integral());
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei",categories[cat].c_str()));nom.push_back(hsig5->Integral());
       
	      //PU wei
	      float puggF[3] ={0}, puVBF[3]={0},puttH[3] = {0}, puZH[3] = {0}, puWH[3] = {0};
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puweiUp*totSF*genwei",categories[cat].c_str()));
	      puggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puweiUp*totSF*genwei",categories[cat].c_str()));
	      puVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puweiUp*totSF*genwei",categories[cat].c_str()));
	      puttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puweiUp*totSF*genwei",categories[cat].c_str()));
	      puZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puweiUp*totSF*genwei",categories[cat].c_str()));
	      puWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puweiDown*totSF*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>puggF[mass])puggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puweiDown*totSF*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>puVBF[mass])puVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puweiDown*totSF*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>puttH[mass])puttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puweiDown*totSF*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>puZH[mass])puZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puweiDown*totSF*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>puWH[mass])puWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      out<<"CMS_PU_13TeV       lnN     "<<1.+puggF[mass]<<"  "<<1.+puVBF[mass]<<"  "<<1.+puttH[mass]<<"  "<<1.+puZH[mass]<<"   "<<1.+puWH[mass]<<endl;
	      cout<<"CMS_PU_13TeV       lnN     "<<1.+puggF[mass]<<"  "<<1.+puVBF[mass]<<"  "<<1.+puttH[mass]<<"  "<<1.+puZH[mass]<<"   "<<1.+puWH[mass]<<endl;
	      if(m>120){
		for (int k = 0 ; k < 4 ; k++)
		  {
		    string fname2;
		    if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    ofstream out2(fname2.c_str());
		    out2<<"CMS_PU_13TeV       lnN     "<<1.+puggF[mass]*((k+1.)/5.)+puggF[mass-1]*((4-k)/5.)<<" "<<1.+puVBF[mass]*((k+1.)/5.)+puVBF[mass-1]*((4-k)/5.)<<" "<<1.+puttH[mass]*((k+1.)/5.)+puttH[mass-1]*((4-k)/5.)<<" "<<1.+puZH[mass]*((k+1.)/5.)+puZH[mass-1]*((4-k)/5.)<<" "<<1.+puWH[mass]*((k+1.)/5.)+puWH[mass-1]*((4-k)/5.)<<endl;
		  }
	      }
        
	      //trigger + electron dz
	      float trg1ggF[3] ={0}, trg1VBF[3]={0},trg1ttH[3] = {0}, trg1ZH[3] = {0}, trg1WH[3] = {0}, trg2ggF[3] ={0}, trg2VBF[3]={0},trg2ttH[3] = {0}, trg2ZH[3] = {0}, trg2WH[3] = {0}, edz1ggF[3] ={0}, edz1VBF[3]={0},edz1ttH[3] = {0}, edz1ZH[3] = {0}, edz1WH[3] = {0},edz2ggF[3] ={0}, edz2VBF[3]={0},edz2ttH[3] = {0}, edz2ZH[3] = {0}, edz2WH[3] = {0};
	      string trig = (i==0) ? "e":"mu";
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]+un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]+un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]+un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]+un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]+un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]-un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig1->Integral() - nom[0])>trg1ggF[mass])trg1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]-un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig2->Integral() - nom[1])>trg1VBF[mass])trg1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]-un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig3->Integral() - nom[2])>trg1ttH[mass])trg1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]-un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig4->Integral() - nom[3])>trg1ZH[mass])trg1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[0]*(sf%strg[0]-un%strg[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig5->Integral() - nom[4])>trg1WH[mass])trg1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
       
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]+un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]+un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]+un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]+un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]+un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      trg2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]-un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig1->Integral() - nom[0])>trg2ggF[mass])trg2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]-un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig2->Integral() - nom[1])>trg2VBF[mass])trg2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]-un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig3->Integral() - nom[2])>trg2ttH[mass])trg2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]-un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig4->Integral() - nom[3])>trg2ZH[mass])trg2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%strg[1]*(sf%strg[1]-un%strg[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig5->Integral() - nom[4])>trg2WH[mass])trg2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
        
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]+unedz[0])*genwei",categories[cat].c_str()));
	      edz1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]+unedz[0])*genwei",categories[cat].c_str()));
	      edz1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]+unedz[0])*genwei",categories[cat].c_str()));
	      edz1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]+unedz[0])*genwei",categories[cat].c_str()));
	      edz1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]+unedz[0])*genwei",categories[cat].c_str()));
	      edz1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]-unedz[0])*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>edz1ggF[mass])edz1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]-unedz[0])*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>edz1VBF[mass])edz1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]-unedz[0])*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>edz1ttH[mass])edz1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]-unedz[0])*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>edz1ZH[mass])edz1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[0]*(sfedz[0]-unedz[0])*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>edz1WH[mass])edz1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		  
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]+unedz[1])*genwei",categories[cat].c_str()));
	      edz2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]+unedz[1])*genwei",categories[cat].c_str()));
	      edz2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]+unedz[1])*genwei",categories[cat].c_str()));
	      edz2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]+unedz[1])*genwei",categories[cat].c_str()));
	      edz2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]+unedz[1])*genwei",categories[cat].c_str()));
	      edz2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]-unedz[1])*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>edz2ggF[mass])edz2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]-unedz[1])*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>edz2VBF[mass])edz2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]-unedz[1])*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>edz2ttH[mass])edz2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]-unedz[1])*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>edz2ZH[mass])edz2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfedz[1]*(sfedz[1]-unedz[1])*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>edz2WH[mass])edz2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      
	      if(i==0)out<<"CMS_HLTeff_e_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass],2)+pow(trg2ggF[mass],2) +pow(edz1ggF[mass],2)+pow(edz2ggF[mass],2))<<"  "<<1.+sqrt(pow(trg1VBF[mass],2)+pow(trg2VBF[mass],2)+pow(edz1VBF[mass],2)+pow(edz2VBF[mass],2))<<"  "<<1.+sqrt(pow(trg1ttH[mass],2)+pow(trg2ttH[mass],2)+pow(edz1ttH[mass],2)+pow(edz2ttH[mass],2))<<"  "<<1.+sqrt(pow(trg1ZH[mass],2)+pow(trg2ZH[mass],2)+pow(edz1ZH[mass],2)+pow(edz2ZH[mass],2))<<"   "<<1.+sqrt(pow(trg1WH[mass],2)+pow(trg2WH[mass],2)+pow(edz2WH[mass],2)+pow(edz2WH[mass],2))<<endl;
	      else out<<"CMS_HLTeff_m_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass],2)+pow(trg2ggF[mass],2))<<"  "<<1.+sqrt(pow(trg1VBF[mass],2)+pow(trg2VBF[mass],2))<<"  "<<1.+sqrt(pow(trg1ttH[mass],2)+pow(trg2ttH[mass],2))<<"  "<<1.+sqrt(pow(trg1ZH[mass],2)+pow(trg2ZH[mass],2))<<"   "<<1.+sqrt(pow(trg1WH[mass],2)+pow(trg2WH[mass],2))<<endl;
	      if(i==0)cout<<"CMS_HLTeff_e_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass],2)+pow(trg2ggF[mass],2) +pow(edz1ggF[mass],2)+pow(edz2ggF[mass],2))<<"  "<<1.+sqrt(pow(trg1VBF[mass],2)+pow(trg2VBF[mass],2)+pow(edz1VBF[mass],2)+pow(edz2VBF[mass],2))<<"  "<<1.+sqrt(pow(trg1ttH[mass],2)+pow(trg2ttH[mass],2)+pow(edz1ttH[mass],2)+pow(edz2ttH[mass],2))<<"  "<<1.+sqrt(pow(trg1ZH[mass],2)+pow(trg2ZH[mass],2)+pow(edz1ZH[mass],2)+pow(edz2ZH[mass],2))<<"   "<<1.+sqrt(pow(trg1WH[mass],2)+pow(trg2WH[mass],2)+pow(edz2WH[mass],2)+pow(edz2WH[mass],2))<<endl;
	      else cout<<"CMS_HLTeff_m_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass],2)+pow(trg2ggF[mass],2))<<"  "<<1.+sqrt(pow(trg1VBF[mass],2)+pow(trg2VBF[mass],2))<<"  "<<1.+sqrt(pow(trg1ttH[mass],2)+pow(trg2ttH[mass],2))<<"  "<<1.+sqrt(pow(trg1ZH[mass],2)+pow(trg2ZH[mass],2))<<"   "<<1.+sqrt(pow(trg1WH[mass],2)+pow(trg2WH[mass],2))<<endl;
	      if(m>120){
		for (int k = 0 ; k < 4 ; k++)
		  {
		    string fname2;
		    if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    ofstream out2(fname2.c_str(), std::ios_base::app | std::ios_base::out);
		    if(cat==0)
		      {
			if(i==0)out2<<"CMS_HLTeff_e_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass]*((k+1.)/5.)+trg1ggF[mass-1]*((4-k)/5.),2)+pow(trg2ggF[mass]*((k+1.)/5.)+trg2ggF[mass-1]*((4-k)/5.),2)+pow(edz1ggF[mass]*((k+1.)/5.)+edz1ggF[mass-1]*((4-k)/5.),2)+pow(edz2ggF[mass]*((k+1.)/5.)+edz2ggF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1VBF[mass]*((k+1.)/5.)+trg1VBF[mass-1]*((4-k)/5.),2)+pow(trg2VBF[mass]*((k+1.)/5.)+trg2VBF[mass-1]*((4-k)/5.),2)+pow(edz1VBF[mass]*((k+1.)/5.)+edz1VBF[mass-1]*((4-k)/5.),2)+pow(edz2VBF[mass]*((k+1.)/5.)+edz2VBF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ttH[mass]*((k+1.)/5.)+trg1ttH[mass-1]*((4-k)/5.),2)+pow(trg2ttH[mass]*((k+1.)/5.)+trg2ttH[mass-1]*((4-k)/5.),2)+pow(edz1ttH[mass]*((k+1.)/5.)+edz1ttH[mass-1]*((4-k)/5.),2)+pow(edz2ttH[mass]*((k+1.)/5.)+edz2ttH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ZH[mass]*((k+1.)/5.)+trg1ZH[mass-1]*((4-k)/5.),2)+pow(trg2ZH[mass]*((k+1.)/5.)+trg2ZH[mass-1]*((4-k)/5.),2)+pow(edz1ZH[mass]*((k+1.)/5.)+edz1ZH[mass-1]*((4-k)/5.),2)+pow(edz2ZH[mass]*((k+1.)/5.)+edz2ZH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1WH[mass]*((k+1.)/5.)+trg1WH[mass-1]*((4-k)/5.),2)+pow(trg2WH[mass]*((k+1.)/5.)+trg2WH[mass-1]*((4-k)/5.),2)+pow(edz1WH[mass]*((k+1.)/5.)+edz1WH[mass-1]*((4-k)/5.),2)+pow(edz2WH[mass]*((k+1.)/5.)+edz2WH[mass-1]*((4-k)/5.),2))<<endl;
			else out2<<"CMS_HLTeff_m_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass]*((k+1.)/5.)+trg1ggF[mass-1]*((4-k)/5.),2)+pow(trg2ggF[mass]*((k+1.)/5.)+trg2ggF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1VBF[mass]*((k+1.)/5.)+trg1VBF[mass-1]*((4-k)/5.),2)+pow(trg2VBF[mass]*((k+1.)/5.)+trg2VBF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ttH[mass]*((k+1.)/5.)+trg1ttH[mass-1]*((4-k)/5.),2)+pow(trg2ttH[mass]*((k+1.)/5.)+trg2ttH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ZH[mass]*((k+1.)/5.)+trg1ZH[mass-1]*((4-k)/5.),2)+pow(trg2ZH[mass]*((k+1.)/5.)+trg2ZH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1WH[mass]*((k+1.)/5.)+trg1WH[mass-1]*((4-k)/5.),2)+pow(trg2WH[mass]*((k+1.)/5.)+trg2WH[mass-1]*((4-k)/5.),2))<<endl;
				
		      }
		    else if(i==0)out2<<"CMS_HLTeff_e_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass]*((k+1.)/5.)+trg1ggF[mass-1]*((4-k)/5.),2)+pow(trg2ggF[mass]*((k+1.)/5.)+trg2ggF[mass-1]*((4-k)/5.),2)+pow(edz1ggF[mass]*((k+1.)/5.)+edz1ggF[mass-1]*((4-k)/5.),2)+pow(edz2ggF[mass]*((k+1.)/5.)+edz2ggF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1VBF[mass]*((k+1.)/5.)+trg1VBF[mass-1]*((4-k)/5.),2)+pow(trg2VBF[mass]*((k+1.)/5.)+trg2VBF[mass-1]*((4-k)/5.),2)+pow(edz1VBF[mass]*((k+1.)/5.)+edz1VBF[mass-1]*((4-k)/5.),2)+pow(edz2VBF[mass]*((k+1.)/5.)+edz2VBF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ttH[mass]*((k+1.)/5.)+trg1ttH[mass-1]*((4-k)/5.),2)+pow(trg2ttH[mass]*((k+1.)/5.)+trg2ttH[mass-1]*((4-k)/5.),2)+pow(edz1ttH[mass]*((k+1.)/5.)+edz1ttH[mass-1]*((4-k)/5.),2)+pow(edz2ttH[mass]*((k+1.)/5.)+edz2ttH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ZH[mass]*((k+1.)/5.)+trg1ZH[mass-1]*((4-k)/5.),2)+pow(trg2ZH[mass]*((k+1.)/5.)+trg2ZH[mass-1]*((4-k)/5.),2)+pow(edz1ZH[mass]*((k+1.)/5.)+edz1ZH[mass-1]*((4-k)/5.),2)+pow(edz2ZH[mass]*((k+1.)/5.)+edz2ZH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1WH[mass]*((k+1.)/5.)+trg1WH[mass-1]*((4-k)/5.),2)+pow(trg2WH[mass]*((k+1.)/5.)+trg2WH[mass-1]*((4-k)/5.),2)+pow(edz1WH[mass]*((k+1.)/5.)+edz1WH[mass-1]*((4-k)/5.),2)+pow(edz2WH[mass]*((k+1.)/5.)+edz2WH[mass-1]*((4-k)/5.),2))<<endl;
		    else out2<<"CMS_HLTeff_m_13TeV       lnN     "<<1.+sqrt(pow(trg1ggF[mass]*((k+1.)/5.)+trg1ggF[mass-1]*((4-k)/5.),2)+pow(trg2ggF[mass]*((k+1.)/5.)+trg2ggF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1VBF[mass]*((k+1.)/5.)+trg1VBF[mass-1]*((4-k)/5.),2)+pow(trg2VBF[mass]*((k+1.)/5.)+trg2VBF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ttH[mass]*((k+1.)/5.)+trg1ttH[mass-1]*((4-k)/5.),2)+pow(trg2ttH[mass]*((k+1.)/5.)+trg2ttH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1ZH[mass]*((k+1.)/5.)+trg1ZH[mass-1]*((4-k)/5.),2)+pow(trg2ZH[mass]*((k+1.)/5.)+trg2ZH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(trg1WH[mass]*((k+1.)/5.)+trg1WH[mass-1]*((4-k)/5.),2)+pow(trg2WH[mass]*((k+1.)/5.)+trg2WH[mass-1]*((4-k)/5.),2))<<endl;
		  }
	      }
        
	      //phoID & phoVeto
	      float gIDggF[3] ={0}, gIDVBF[3]={0},gIDttH[3] = {0}, gIDZH[3] = {0}, gIDWH[3] = {0}, gVetoggF[3] ={0}, gVetoVBF[3]={0},gVetottH[3] = {0}, gVetoZH[3] = {0}, gVetoWH[3] = {0};
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID+ungID)*genwei",categories[cat].c_str()));
	      gIDggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID+ungID)*genwei",categories[cat].c_str()));
	      gIDVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID+ungID)*genwei",categories[cat].c_str()));
	      gIDttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID+ungID)*genwei",categories[cat].c_str()));
	      gIDZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID+ungID)*genwei",categories[cat].c_str()));
	      gIDWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID-ungID)*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>gIDggF[mass])gIDggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID-ungID)*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>gIDVBF[mass])gIDVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID-ungID)*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>gIDttH[mass])gIDttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID-ungID)*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>gIDZH[mass])gIDZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgID*(sfgID-ungID)*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>gIDWH[mass])gIDWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto+ungVeto)*genwei",categories[cat].c_str()));
	      gVetoggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto+ungVeto)*genwei",categories[cat].c_str()));
	      gVetoVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto+ungVeto)*genwei",categories[cat].c_str()));
	      gVetottH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto+ungVeto)*genwei",categories[cat].c_str()));
	      gVetoZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto+ungVeto)*genwei",categories[cat].c_str()));
	      gVetoWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto-ungVeto)*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>gVetoggF[mass])gVetoggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto-ungVeto)*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>gVetoVBF[mass])gVetoVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto-ungVeto)*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>gVetottH[mass])gVetottH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto-ungVeto)*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>gVetoZH[mass])gVetoZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfgVeto*(sfgVeto-ungVeto)*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>gVetoWH[mass])gVetoWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
       
	      out<<"CMS_IDeff_g_13TeV       lnN     "<<1.+sqrt(gIDggF[mass]*gIDggF[mass]+gVetoggF[mass]*gVetoggF[mass])<<"  "<<1.+sqrt(gIDVBF[mass]*gIDVBF[mass]+gVetoVBF[mass]*gVetoVBF[mass])<<"  "<<1.+sqrt(gIDttH[mass]*gIDttH[mass]+gVetottH[mass]*gVetottH[mass])<<"  "<<1.+sqrt(gIDZH[mass]*gIDZH[mass]+gVetoZH[mass]*gVetoZH[mass])<<"   "<<1.+sqrt(gIDWH[mass]*gIDWH[mass]+gVetoWH[mass]*gVetoWH[mass])<<endl;
	      cout<<"CMS_IDeff_g_13TeV       lnN     "<<1.+sqrt(gIDggF[mass]*gIDggF[mass]+gVetoggF[mass]*gVetoggF[mass])<<"  "<<1.+sqrt(gIDVBF[mass]*gIDVBF[mass]+gVetoVBF[mass]*gVetoVBF[mass])<<"  "<<1.+sqrt(gIDttH[mass]*gIDttH[mass]+gVetottH[mass]*gVetottH[mass])<<"  "<<1.+sqrt(gIDZH[mass]*gIDZH[mass]+gVetoZH[mass]*gVetoZH[mass])<<"   "<<1.+sqrt(gIDWH[mass]*gIDWH[mass]+gVetoWH[mass]*gVetoWH[mass])<<endl;
	      if(m>120)
		{
		  for (int k = 0 ; k < 4 ; k++)
		    {
		      string fname2;
		      if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		      else   fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		      ofstream out2(fname2.c_str(), std::ios_base::app | std::ios_base::out);
		      out2<<"CMS_IDeff_g_13TeV       lnN     "<<1.+sqrt(pow(gIDggF[mass]*((k+1.)/5.)+gIDggF[mass-1]*((4-k)/5.),2)+pow(gVetoggF[mass]*((k+1.)/5.)+gVetoggF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(gIDVBF[mass]*((k+1.)/5.)+gIDVBF[mass-1]*((4-k)/5.),2)+pow(gVetoVBF[mass]*((k+1.)/5.)+gVetoVBF[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(gIDttH[mass]*((k+1.)/5.)+gIDttH[mass-1]*((4-k)/5.),2)+pow(gVetottH[mass]*((k+1.)/5.)+gVetottH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(gIDZH[mass]*((k+1.)/5.)+gIDZH[mass-1]*((4-k)/5.),2)+pow(gVetoZH[mass]*((k+1.)/5.)+gVetoZH[mass-1]*((4-k)/5.),2))<<" "<<1.+sqrt(pow(gIDWH[mass]*((k+1.)/5.)+gIDWH[mass-1]*((4-k)/5.),2)+pow(gVetoWH[mass]*((k+1.)/5.)+gVetoWH[mass-1]*((4-k)/5.),2))<<endl;
		    }
		}
        
	      //ID
	      float ID1ggF[3] ={0}, ID1VBF[3]={0},ID1ttH[3] = {0}, ID1ZH[3] = {0}, ID1WH[3] = {0}, ID2ggF[3] ={0}, ID2VBF[3]={0},ID2ttH[3] = {0}, ID2ZH[3] = {0}, ID2WH[3] = {0}, ID3ggF[3] ={0}, ID3VBF[3]={0},ID3ttH[3] = {0}, ID3ZH[3] = {0}, ID3WH[3] = {0}, ID3mggF[3] ={0}, ID3mVBF[3]={0},ID3mttH[3] = {0}, ID3mZH[3] = {0}, ID3mWH[3] = {0},GSF1ggF[3] ={0}, GSF1VBF[3]={0},GSF1ttH[3] = {0}, GSF1ZH[3] = {0}, GSF1WH[3] = {0},GSF2ggF[3] ={0}, GSF2VBF[3]={0},GSF2ttH[3] = {0}, GSF2ZH[3] = {0}, GSF2WH[3] = {0},GSF3ggF[3] ={0}, GSF3VBF[3]={0},GSF3ttH[3] = {0}, GSF3ZH[3] = {0}, GSF3WH[3] = {0};

	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]+un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]+un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]+un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]+un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]+un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]-un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig1->Integral() - nom[0])>ID1ggF[mass])ID1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]-un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig2->Integral() - nom[1])>ID1VBF[mass])ID1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]-un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig3->Integral() - nom[2])>ID1ttH[mass])ID1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]-un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig4->Integral() - nom[3])>ID1ZH[mass])ID1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[0]*(sf%sID[0]-un%sID[0])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig5->Integral() - nom[4])>ID1WH[mass])ID1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
       
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]+un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]+un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]+un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]+un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]+un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      ID2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]-un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig1->Integral() - nom[0])>ID2ggF[mass])ID2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]-un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig2->Integral() - nom[1])>ID2VBF[mass])ID2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]-un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig3->Integral() - nom[2])>ID2ttH[mass])ID2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]-un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig4->Integral() - nom[3])>ID2ZH[mass])ID2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sf%sID[1]*(sf%sID[1]-un%sID[1])*genwei",categories[cat].c_str(),trig.c_str(),trig.c_str(),trig.c_str()));
	      if((hsig5->Integral() - nom[4])>ID2WH[mass])ID2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      if(cat==0&&i==0){
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]+uneID[2])*genwei");
		ID3ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]+uneID[2])*genwei");
		ID3VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]+uneID[2])*genwei");
		ID3ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]+uneID[2])*genwei");
		ID3ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]+uneID[2])*genwei");
		ID3WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]-uneID[2])*genwei");
		if((hsig1->Integral() - nom[0])>ID3ggF[mass])ID3ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]-uneID[2])*genwei");
		if((hsig2->Integral() - nom[1])>ID3VBF[mass])ID3VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]-uneID[2])*genwei");
		if((hsig3->Integral() - nom[2])>ID3ttH[mass])ID3ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]-uneID[2])*genwei");
		if((hsig4->Integral() - nom[3])>ID3ZH[mass])ID3ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfeID[2]*(sfeID[2]-uneID[2])*genwei");
		if((hsig5->Integral() - nom[4])>ID3WH[mass])ID3WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
        
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]+unGSF[2])*genwei");
		GSF3ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]+unGSF[2])*genwei");
		GSF3VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]+unGSF[2])*genwei");
		GSF3ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]+unGSF[2])*genwei");
		GSF3ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]+unGSF[2])*genwei");
		GSF3WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]-unGSF[2])*genwei");
		if((hsig1->Integral() - nom[0])>GSF3ggF[mass])GSF3ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]-unGSF[2])*genwei");
		if((hsig2->Integral() - nom[1])>GSF3VBF[mass])GSF3VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]-unGSF[2])*genwei");
		if((hsig3->Integral() - nom[2])>GSF3ttH[mass])GSF3ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]-unGSF[2])*genwei");
		if((hsig4->Integral() - nom[3])>GSF3ZH[mass])GSF3ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==6)||(cat==7)))*puwei*totSF/sfGSF[2]*(sfGSF[2]-unGSF[2])*genwei");
		if((hsig5->Integral() - nom[4])>GSF3WH[mass])GSF3WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      }
	      else if(cat==0&&i==1){
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]+unmuID[2])*genwei");
		ID3mggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]+unmuID[2])*genwei");
		ID3mVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]+unmuID[2])*genwei");
		ID3mttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]+unmuID[2])*genwei");
		ID3mZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]+unmuID[2])*genwei");
		ID3mWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		ggF.Draw("mllg>>hsig1","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]-unmuID[2])*genwei");
		if((hsig1->Integral() - nom[0])>ID3mggF[mass])ID3mggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		VBF.Draw("mllg>>hsig2","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]-unmuID[2])*genwei");
		if((hsig2->Integral() - nom[1])>ID3mVBF[mass])ID3mVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		ttH.Draw("mllg>>hsig3","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]-unmuID[2])*genwei");
		if((hsig3->Integral() - nom[2])>ID3mttH[mass])ID3mttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		ZH.Draw("mllg>>hsig4","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]-unmuID[2])*genwei");
		if((hsig4->Integral() - nom[3])>ID3mZH[mass])ID3mZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		WH.Draw("mllg>>hsig5","(mllg>115&&mllg<170&&((cat==8)||(cat==9)))*puwei*totSF/sfmuID[2]*(sfmuID[2]-unmuID[2])*genwei");
		if((hsig5->Integral() - nom[4])>ID3mWH[mass])ID3mWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      }
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]+unGSF[0])*genwei",categories[cat].c_str()));
	      GSF1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]+unGSF[0])*genwei",categories[cat].c_str()));
	      GSF1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]+unGSF[0])*genwei",categories[cat].c_str()));
	      GSF1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]); 	
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]+unGSF[0])*genwei",categories[cat].c_str()));
	      GSF1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]+unGSF[0])*genwei",categories[cat].c_str()));
	      GSF1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]-unGSF[0])*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>GSF1ggF[mass])GSF1ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]-unGSF[0])*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>GSF1VBF[mass])GSF1VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]-unGSF[0])*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>GSF1ttH[mass])GSF1ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]-unGSF[0])*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>GSF1ZH[mass])GSF1ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[0]*(sfGSF[0]-unGSF[0])*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>GSF1WH[mass])GSF1WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
       
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]+unGSF[1])*genwei",categories[cat].c_str()));
	      GSF2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]+unGSF[1])*genwei",categories[cat].c_str()));
	      GSF2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]+unGSF[1])*genwei",categories[cat].c_str()));
	      GSF2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]+unGSF[1])*genwei",categories[cat].c_str()));
	      GSF2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]+unGSF[1])*genwei",categories[cat].c_str()));
	      GSF2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	      ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]-unGSF[1])*genwei",categories[cat].c_str()));
	      if((hsig1->Integral() - nom[0])>GSF2ggF[mass])GSF2ggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
	      VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]-unGSF[1])*genwei",categories[cat].c_str()));
	      if((hsig2->Integral() - nom[1])>GSF2VBF[mass])GSF2VBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
	      ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]-unGSF[1])*genwei",categories[cat].c_str()));
	      if((hsig3->Integral() - nom[2])>GSF2ttH[mass])GSF2ttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
	      ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]-unGSF[1])*genwei",categories[cat].c_str()));
	      if((hsig4->Integral() - nom[3])>GSF2ZH[mass])GSF2ZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
	      WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF/sfGSF[1]*(sfGSF[1]-unGSF[1])*genwei",categories[cat].c_str()));
	      if((hsig5->Integral() - nom[4])>GSF2WH[mass])GSF2WH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
       
	      if(cat==0){
		if(i==0)out<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2) +pow(ID3ggF[mass],2)+pow(GSF1ggF[mass],2)+pow(GSF2ggF[mass],2)+pow(GSF3ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(ID3VBF[mass],2)+pow(GSF1VBF[mass],2)+pow(GSF2VBF[mass],2)+pow(GSF3VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(ID3ttH[mass],2)+pow(GSF1ttH[mass],2)+pow(GSF2ttH[mass],2)+pow(GSF3ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(ID3ZH[mass],2)+pow(GSF1ZH[mass],2)+pow(GSF2ZH[mass],2)+pow(GSF3ZH[mass],2))<<"  "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(ID3WH[mass],2)+pow(GSF1WH[mass],2)+pow(GSF2WH[mass],2)+pow(GSF3WH[mass],2))<<endl;
	       else out<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2)+pow(ID3mggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(ID3mVBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(ID3mttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(ID3mZH[mass],2))<<"  "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(ID3mWH[mass],2))<<endl;
		if(i==0)cout<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2) +pow(ID3ggF[mass],2)+pow(GSF1ggF[mass],2)+pow(GSF2ggF[mass],2)+pow(GSF3ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(ID3VBF[mass],2)+pow(GSF1VBF[mass],2)+pow(GSF2VBF[mass],2)+pow(GSF3VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(ID3ttH[mass],2)+pow(GSF1ttH[mass],2)+pow(GSF2ttH[mass],2)+pow(GSF3ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(ID3ZH[mass],2)+pow(GSF1ZH[mass],2)+pow(GSF2ZH[mass],2)+pow(GSF3ZH[mass],2))<<"  "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(ID3WH[mass],2)+pow(GSF1WH[mass],2)+pow(GSF2WH[mass],2)+pow(GSF3WH[mass],2))<<endl;
		else cout<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2)+pow(ID3mggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(ID3mVBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(ID3mttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(ID3mZH[mass],2))<<"  "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(ID3mWH[mass],2))<<endl;
		cout<<ID3mWH[mass]<<endl;
	      }
	      else if(i==0)
		{		  
		  out<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2)+pow(GSF1ggF[mass],2)+pow(GSF2ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(GSF1VBF[mass],2)+pow(GSF2VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(GSF1ttH[mass],2)+pow(GSF2ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(GSF1ZH[mass],2)+pow(GSF2ZH[mass],2))<<"   "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(GSF1WH[mass],2)+pow(GSF2WH[mass],2))<<endl;
		  cout<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2)+pow(GSF1ggF[mass],2)+pow(GSF2ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2)+pow(GSF1VBF[mass],2)+pow(GSF2VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2)+pow(GSF1ttH[mass],2)+pow(GSF2ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2)+pow(GSF1ZH[mass],2)+pow(GSF2ZH[mass],2))<<"   "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2)+pow(GSF1WH[mass],2)+pow(GSF2WH[mass],2))<<endl;
		}
	      else 
		{
		  out<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2))<<"   "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2))<<endl;
		  cout<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass],2)+pow(ID2ggF[mass],2))<<"  "<<1.+sqrt(pow(ID1VBF[mass],2)+pow(ID2VBF[mass],2))<<"  "<<1.+sqrt(pow(ID1ttH[mass],2)+pow(ID2ttH[mass],2))<<"  "<<1.+sqrt(pow(ID1ZH[mass],2)+pow(ID2ZH[mass],2))<<"   "<<1.+sqrt(pow(ID1WH[mass],2)+pow(ID2WH[mass],2))<<endl;
		}
	      if(m>120){
		for (int k = 0 ; k < 4 ; k++)
		  {
		    string fname2;
		    if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat)+"_m"+  std::to_string(m-4+k)+".txt";
		    ofstream out2(fname2.c_str(), std::ios_base::app | std::ios_base::out);
		    if(cat==0)
		      {
			if(i==0)out2<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass]*((k+1.)/5.)+ID1ggF[mass-1]*((4-k)/5.),2)+pow(ID2ggF[mass]*((k+1.)/5.)+ID2ggF[mass-1]*((4-k)/5.),2)+pow(ID3ggF[mass]*((k+1.)/5.)+ID3ggF[mass-1]*((4-k)/5.),2)+pow(GSF1ggF[mass]*((k+1.)/5.)+GSF1ggF[mass-1]*((4-k)/5.),2)+pow(GSF2ggF[mass]*((k+1.)/5.)+GSF2ggF[mass-1]*((4-k)/5.),2)+pow(GSF3ggF[mass]*((k+1.)/5.)+GSF3ggF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1VBF[mass]*((k+1.)/5.)+ID1VBF[mass-1]*((4-k)/5.),2)+pow(ID2VBF[mass]*((k+1.)/5.)+ID2VBF[mass-1]*((4-k)/5.),2)+pow(ID3VBF[mass]*((k+1.)/5.)+ID3VBF[mass-1]*((4-k)/5.),2)+pow(GSF1VBF[mass]*((k+1.)/5.)+GSF1VBF[mass-1]*((4-k)/5.),2)+pow(GSF2VBF[mass]*((k+1.)/5.)+GSF2VBF[mass-1]*((4-k)/5.),2)+pow(GSF3VBF[mass]*((k+1.)/5.)+GSF3VBF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ttH[mass]*((k+1.)/5.)+ID1ttH[mass-1]*((4-k)/5.),2)+pow(ID2ttH[mass]*((k+1.)/5.)+ID2ttH[mass-1]*((4-k)/5.),2)+pow(ID3ttH[mass]*((k+1.)/5.)+ID3ttH[mass-1]*((4-k)/5.),2)+pow(GSF1ttH[mass]*((k+1.)/5.)+GSF1ttH[mass-1]*((4-k)/5.),2)+pow(GSF2ttH[mass]*((k+1.)/5.)+GSF2ttH[mass-1]*((4-k)/5.),2)+pow(GSF3ttH[mass]*((k+1.)/5.)+GSF3ttH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ZH[mass]*((k+1.)/5.)+ID1ZH[mass-1]*((4-k)/5.),2)+pow(ID2ZH[mass]*((k+1.)/5.)+ID2ZH[mass-1]*((4-k)/5.),2)+pow(ID3ZH[mass]*((k+1.)/5.)+ID3ZH[mass-1]*((4-k)/5.),2)+pow(GSF1ZH[mass]*((k+1.)/5.)+GSF1ZH[mass-1]*((4-k)/5.),2)+pow(GSF2ZH[mass]*((k+1.)/5.)+GSF2ZH[mass-1]*((4-k)/5.),2)+pow(GSF3ZH[mass]*((k+1.)/5.)+GSF3ZH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1WH[mass]*((k+1.)/5.)+ID1WH[mass-1]*((4-k)/5.),2)+pow(ID2WH[mass]*((k+1.)/5.)+ID2WH[mass-1]*((4-k)/5.),2)+pow(ID3WH[mass]*((k+1.)/5.)+ID3WH[mass-1]*((4-k)/5.),2)+pow(GSF1WH[mass]*((k+1.)/5.)+GSF1WH[mass-1]*((4-k)/5.),2)+pow(GSF2WH[mass]*((k+1.)/5.)+GSF2WH[mass-1]*((4-k)/5.),2)+pow(GSF3WH[mass]*((k+1.)/5.)+GSF3WH[mass-1]*((4-k)/5.),2))<<endl;           
			else out2<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass]*((k+1.)/5.)+ID1ggF[mass-1]*((4-k)/5.),2)+pow(ID2ggF[mass]*((k+1.)/5.)+ID2ggF[mass-1]*((4-k)/5.),2)+pow(ID3mggF[mass]*((k+1.)/5.)+ID3mggF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1VBF[mass]*((k+1.)/5.)+ID1VBF[mass-1]*((4-k)/5.),2)+pow(ID2VBF[mass]*((k+1.)/5.)+ID2VBF[mass-1]*((4-k)/5.),2)+pow(ID3mVBF[mass]*((k+1.)/5.)+ID3mVBF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ttH[mass]*((k+1.)/5.)+ID1ttH[mass-1]*((4-k)/5.),2)+pow(ID2ttH[mass]*((k+1.)/5.)+ID2ttH[mass-1]*((4-k)/5.),2)+pow(ID3mttH[mass]*((k+1.)/5.)+ID3mttH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ZH[mass]*((k+1.)/5.)+ID1ZH[mass-1]*((4-k)/5.),2)+pow(ID2ZH[mass]*((k+1.)/5.)+ID2ZH[mass-1]*((4-k)/5.),2)+pow(ID3mZH[mass]*((k+1.)/5.)+ID3mZH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1WH[mass]*((k+1.)/5.)+ID1WH[mass-1]*((4-k)/5.),2)+pow(ID2WH[mass]*((k+1.)/5.)+ID2WH[mass-1]*((4-k)/5.),2)+pow(ID3mWH[mass]*((k+1.)/5.)+ID3mWH[mass-1]*((4-k)/5.),2))<<endl;            
		      }
		    else if(i==0)
		      {
			out2<<"CMS_IDeff_e_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass]*((k+1.)/5.)+ID1ggF[mass-1]*((4-k)/5.),2)+pow(ID2ggF[mass]*((k+1.)/5.)+ID2ggF[mass-1]*((4-k)/5.),2)+pow(GSF1ggF[mass]*((k+1.)/5.)+GSF1ggF[mass-1]*((4-k)/5.),2)+pow(GSF2ggF[mass]*((k+1.)/5.)+GSF2ggF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1VBF[mass]*((k+1.)/5.)+ID1VBF[mass-1]*((4-k)/5.),2)+pow(ID2VBF[mass]*((k+1.)/5.)+ID2VBF[mass-1]*((4-k)/5.),2)+pow(GSF1VBF[mass]*((k+1.)/5.)+GSF1VBF[mass-1]*((4-k)/5.),2)+pow(GSF2VBF[mass]*((k+1.)/5.)+GSF2VBF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ttH[mass]*((k+1.)/5.)+ID1ttH[mass-1]*((4-k)/5.),2)+pow(ID2ttH[mass]*((k+1.)/5.)+ID2ttH[mass-1]*((4-k)/5.),2)+pow(GSF1ttH[mass]*((k+1.)/5.)+GSF1ttH[mass-1]*((4-k)/5.),2)+pow(GSF2ttH[mass]*((k+1.)/5.)+GSF2ttH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ZH[mass]*((k+1.)/5.)+ID1ZH[mass-1]*((4-k)/5.),2)+pow(ID2ZH[mass]*((k+1.)/5.)+ID2ZH[mass-1]*((4-k)/5.),2)+pow(GSF1ZH[mass]*((k+1.)/5.)+GSF1ZH[mass-1]*((4-k)/5.),2)+pow(GSF2ZH[mass]*((k+1.)/5.)+GSF2ZH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1WH[mass]*((k+1.)/5.)+ID1WH[mass-1]*((4-k)/5.),2)+pow(ID2WH[mass]*((k+1.)/5.)+ID2WH[mass-1]*((4-k)/5.),2)+pow(GSF1WH[mass]*((k+1.)/5.)+GSF1WH[mass-1]*((4-k)/5.),2)+pow(GSF2WH[mass]*((k+1.)/5.)+GSF2WH[mass-1]*((4-k)/5.),2))<<endl;
		      }
		    else 
		      {
			out2<<"CMS_IDeff_m_13TeV       lnN     "<<1.+sqrt(pow(ID1ggF[mass]*((k+1.)/5.)+ID1ggF[mass-1]*((4-k)/5.),2)+pow(ID2ggF[mass]*((k+1.)/5.)+ID2ggF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1VBF[mass]*((k+1.)/5.)+ID1VBF[mass-1]*((4-k)/5.),2)+pow(ID2VBF[mass]*((k+1.)/5.)+ID2VBF[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ttH[mass]*((k+1.)/5.)+ID1ttH[mass-1]*((4-k)/5.),2)+pow(ID2ttH[mass]*((k+1.)/5.)+ID2ttH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1ZH[mass]*((k+1.)/5.)+ID1ZH[mass-1]*((4-k)/5.),2)+pow(ID2ZH[mass]*((k+1.)/5.)+ID2ZH[mass-1]*((4-k)/5.),2))<<"  "<<1.+sqrt(pow(ID1WH[mass]*((k+1.)/5.)+ID1WH[mass-1]*((4-k)/5.),2)+pow(ID2WH[mass]*((k+1.)/5.)+ID2WH[mass-1]*((4-k)/5.),2))<<endl;
		      }
		  }
	      }
	      cout<<"=============================================================="<<endl;
	    }
	}
    }
}
