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
///0->%s, 1->%s

void UEPS()
{
  gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");
  string categories[24] = 
    {
      "(cat>5&&cat<10)",
      "HZgVBF>0.12&&cat==5",
      "HZgVBF<=0.12&&HZgVBF>-0.32&&cat==5",
      "(cat<6||cat>9)&&HZgVBF<=-0.32&&HZgMVA>0.0832",
      "(cat<6||cat>9)&&HZgVBF<=-0.32&&HZgMVA<=0.0832&&HZgMVA>0.0649",
      "(cat<6||cat>9)&&HZgVBF<=-0.32&&HZgMVA<=0.0649&&HZgMVA>0.0517",
      "(cat<6||cat>9)&&HZgVBF<=-0.32&&HZgMVA<=0.0517&&HZgMVA>0.0136",
      "(cat<6||cat>9)&&HZgVBF<=-0.32&&HZgMVA<=0.0136&&HZgMVA>-0.0645",
      "(cat>5&&cat<10)",
      "HZgVBF>0.16&&cat==5",
      "HZgVBF<=0.16&&HZgVBF>-0.26&&cat==5",
      "(cat<6||cat>9)&&HZgVBF<=-0.26&&HZgMVA>0.1036",
      "(cat<6||cat>9)&&HZgVBF<=-0.26&&HZgMVA<=0.1036&&HZgMVA>0.07",
      "(cat<6||cat>9)&&HZgVBF<=-0.26&&HZgMVA<=0.07&&HZgMVA>0.0505",
      "(cat<6||cat>9)&&HZgVBF<=-0.26&&HZgMVA<=0.0505&&HZgMVA>-0.0154",
      "(cat<6||cat>9)&&HZgVBF<=-0.26&&HZgMVA<=-0.0154&&HZgMVA>-0.0884",
      "(cat>5&&cat<10)",
      "HZgVBF>0.14&&cat==5",
      "HZgVBF<=0.14&&HZgVBF>-0.22&&cat==5",
      "(cat<6||cat>9)&&HZgVBF<=-0.22&&HZgMVA>0.1619",
      "(cat<6||cat>9)&&HZgVBF<=-0.22&&HZgMVA<=0.1619&&HZgMVA>0.1192",
      "(cat<6||cat>9)&&HZgVBF<=-0.22&&HZgMVA<=0.1192&&HZgMVA>0.0649",
      "(cat<6||cat>9)&&HZgVBF<=-0.22&&HZgMVA<=0.0649&&HZgMVA>0.0072",
      "(cat<6||cat>9)&&HZgVBF<=-0.22&&HZgMVA<=0.0072&&HZgMVA>-0.0884",
    };
  int cats[8] = {6789, 501, 502, 1, 2,3, 4,5};
  string fname[3] = {"Legacy16_newMVA","Rereco17_newMVAv2","Rereco18_newMVAv2"};
  string weight[3] ={"*L1wei","*L1wei*ptwei","*ptwei"};
  string types[2] = {"ele","mu"};
  //signal
  for(int y = 0 ; y <1 ; y++)
    {
      for (int i= 0 ; i <1; i++)
	{
	  for (int cat = 0; cat <1 ; cat++)
	    {
	      for (int mass = 1; mass <2 ; mass++)
		{
		  int m = 120+ mass*5;
		  if(m==125)cout<<"mass: "<<m<<" eleormu: "<<i<<" cat:"<<categories[cat+8*y]<<endl;
		  TChain ggF("tZg");
		  TChain VBF("tZg");
		  TChain ttH("tZg");
		  TChain ZH("tZg");
		  TChain WH("tZg");
	    
		  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_ggF_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));
		  VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_VBF_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));
		  ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_ttH_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));
		  ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_ZH_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));
		  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_WplusH_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));
		  WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_HZg_WminusH_%dGeV.root",fname[y].c_str(),types[i].c_str(),m));   

		  TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
		  TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
		  TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
		  TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
		  TH1F *hsig5 = new TH1F("hsig5", " ",55, 115, 170);
      
		  vector<float> nom; nom.clear();
		  string txtname;
		  if (i==0) txtname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/UEPS_"+std::to_string(y+2016)+"_ele_cat" + std::to_string(cats[cat])+".txt";
		  else  txtname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/UEPS_"+std::to_string(y+2016)+"_mu_cat" + std::to_string(cats[cat])+".txt";
		  ofstream out(txtname.c_str(), std::ios_base::out);
		   // nominal
		  ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));nom.push_back(hsig1->Integral());
		  VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));nom.push_back(hsig2->Integral());
		  ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));nom.push_back(hsig3->Integral());
		  ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));nom.push_back(hsig4->Integral());
		  WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));nom.push_back(hsig5->Integral());
		  
		  //UE
		  TChain ggF_UEU("tZg");
		  TChain VBF_UEU("tZg");
		  TChain ttH_UEU("tZg");
		  TChain ZH_UEU("tZg");
		  TChain WH_UEU("tZg");
		  TChain ggF_UED("tZg");
		  TChain VBF_UED("tZg");
		  TChain ttH_UED("tZg");
		  TChain ZH_UED("tZg");
		  TChain WH_UED("tZg");
		  ggF_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ggF_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		  VBF_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_VBF_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		  ttH_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ttH_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		  ZH_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ZH_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WplusH_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_UEU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WminusH_%dGeV_UEU.root",fname[y].c_str(),types[i].c_str(),m));
		 
		  ggF_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ggF_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));
		  VBF_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_VBF_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));
		  ttH_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ttH_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));
		  ZH_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ZH_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WplusH_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_UED.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WminusH_%dGeV_UED.root",fname[y].c_str(),types[i].c_str(),m));   
		  float ueggF[3] ={0}, ueVBF[3]={0},uettH[3] = {0}, ueZH[3] = {0}, ueWH[3] = {0};


		  ggF_UEU.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  ueggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		  VBF_UEU.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  ueVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		  ttH_UEU.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  uettH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		  ZH_UEU.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  ueZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		  WH_UEU.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  ueWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		  ggF_UED.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig1->Integral() - nom[0])>ueggF[mass])ueggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		  VBF_UED.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig2->Integral() - nom[1])>ueVBF[mass])ueVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		  ttH_UED.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig3->Integral() - nom[2])>uettH[mass])uettH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		  ZH_UED.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig4->Integral() - nom[3])>ueZH[mass])ueZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		  WH_UED.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig5->Integral() - nom[4])>ueWH[mass])ueWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		  if(cat==1||cat==2)
		  	{
		  		ueZH[mass] = ueVBF[mass];
		  		ueWH[mass] = ueVBF[mass];
		  		uettH[mass] = ueVBF[mass];
		  	}
		  else if(cat>2) 
		  	{
		  		ueZH[mass] =  ueggF[mass];
		  		ueWH[mass] = ueggF[mass];
		  		uettH[mass] = ueggF[mass];
		  	}

		  else {
		  	ueggF[mass] = ueWH[mass];
		  	ueVBF[mass] = ueWH[mass];
		  }
		  if((cat!=0&&i==1)||i==0)out<<"CMS_UE_13TeV       lnN     "<<1.+ueggF[mass]<<"  "<<1.+ueVBF[mass]<<"  "<<1.+uettH[mass]<<"  "<<1.+ueZH[mass]<<"   "<<1.+ueWH[mass]<<endl;
		  cout<<"CMS_UE_13TeV       lnN     "<<1.+ueggF[mass]<<"  "<<1.+ueVBF[mass]<<"  "<<1.+uettH[mass]<<"  "<<1.+ueZH[mass]<<"   "<<1.+ueWH[mass]<<endl;
		  if(m>120){
		    for (int k = 0 ; k < 4 ; k++)
		      {
			string fname2;
			if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/ID_"+std::to_string(y+2016)+"_%s_cat" + std::to_string(cats[cat])+".txt";
			else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/ID_"+std::to_string(y+2016)+"_mu_cat" + std::to_string(cats[cat])+".txt";
			ofstream out2(fname2.c_str(),std::ios_base::out);
			if((cat!=0&&i==1)||i==0)out2<<"CMS_UE_13TeV       lnN     "<<1.+ueggF[mass]*((k+1.)/5.)+ueggF[mass-1]*((4-k)/5.)<<" "<<1.+ueVBF[mass]*((k+1.)/5.)+ueVBF[mass-1]*((4-k)/5.)<<" "<<1.+uettH[mass]*((k+1.)/5.)+uettH[mass-1]*((4-k)/5.)<<" "<<1.+ueZH[mass]*((k+1.)/5.)+ueZH[mass-1]*((4-k)/5.)<<" "<<1.+ueWH[mass]*((k+1.)/5.)+ueWH[mass-1]*((4-k)/5.)<<endl;
		      }
		  }
		  //PS
		  TChain ggF_PSU("tZg");
		  TChain VBF_PSU("tZg");
		  TChain ttH_PSU("tZg");
		  TChain ZH_PSU("tZg");
		  TChain WH_PSU("tZg");
		  TChain ggF_PSD("tZg");
		  TChain VBF_PSD("tZg");
		  TChain ttH_PSD("tZg");
		  TChain ZH_PSD("tZg");
		  TChain WH_PSD("tZg");
		  ggF_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ggF_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));
		  VBF_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_VBF_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));
		  ttH_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ttH_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));
		  ZH_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ZH_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WplusH_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_PSU.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WminusH_%dGeV_PSU.root",fname[y].c_str(),types[i].c_str(),m));   
		  ggF_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ggF_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));
		  VBF_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_VBF_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));
		  ttH_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ttH_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));
		  ZH_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_ZH_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WplusH_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));
		  WH_PSD.Add(Form("/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s_%s_HZg_WminusH_%dGeV_PSD.root",fname[y].c_str(),types[i].c_str(),m));   

		  float psggF[3] ={0}, psVBF[3]={0},psttH[3] = {0}, psZH[3] = {0}, psWH[3] = {0};


		  ggF_PSU.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  psggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		  VBF_PSU.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  psVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		  ttH_PSU.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  psttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		  ZH_PSU.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  psZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		  WH_PSU.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  psWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		  ggF_PSD.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig1->Integral() - nom[0])>psggF[mass])psggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		  VBF_PSD.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig2->Integral() - nom[1])>psVBF[mass])psVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		  ttH_PSD.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig3->Integral() - nom[2])>psttH[mass])psttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		  ZH_PSD.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig4->Integral() - nom[3])>psZH[mass])psZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		  WH_PSD.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei%s",categories[cat+8*y].c_str(),weight[y].c_str()));
		  if((hsig5->Integral() - nom[4])>psWH[mass])psWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		 if(cat==1||cat==2)
		  	{
		  		psZH[mass] = psVBF[mass];
		  		psWH[mass] = psVBF[mass];
		  		psttH[mass] = psVBF[mass];
		  	}
		  else if(cat>2) 
		  	{
		  		psZH[mass] =  psggF[mass];
		  		psWH[mass] = psggF[mass];
		  		psttH[mass] = psggF[mass];
		  	}

		  else {
		  	psggF[mass] = psWH[mass];
		  	psVBF[mass] = psWH[mass];
		  }
		  if((cat!=0&&i==1)||i==0)out<<"CMS_PS_13TeV       lnN     "<<1.+psggF[mass]<<"  "<<1.+psVBF[mass]<<"  "<<1.+psttH[mass]<<"  "<<1.+psZH[mass]<<"   "<<1.+psWH[mass]<<endl;
		  cout<<"CMS_PS_13TeV       lnN     "<<1.+psggF[mass]<<"  "<<1.+psVBF[mass]<<"  "<<1.+psttH[mass]<<"  "<<1.+psZH[mass]<<"   "<<1.+psWH[mass]<<endl;
		  if(m>120){
		    for (int k = 0 ; k < 4 ; k++)
		      {
			string fname2;
			if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/ID_"+std::to_string(y+2016)+"_%s_cat" + std::to_string(cats[cat])+".txt";
			else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/ID_"+std::to_string(y+2016)+"_mu_cat" + std::to_string(cats[cat])+".txt";
			ofstream out2(fname2.c_str(), std::ios_base::out);
			if((cat!=0&&i==1)||i==0)out2<<"CMS_PS_13TeV       lnN     "<<1.+psWH[mass]*((k+1.)/5.)+psWH[mass-1]*((4-k)/5.)<<" "<<1.+psVBF[mass]*((k+1.)/5.)+psVBF[mass-1]*((4-k)/5.)<<" "<<1.+psttH[mass]*((k+1.)/5.)+psttH[mass-1]*((4-k)/5.)<<" "<<1.+psZH[mass]*((k+1.)/5.)+psZH[mass-1]*((4-k)/5.)<<" "<<1.+psWH[mass]*((k+1.)/5.)+psWH[mass-1]*((4-k)/5.)<<endl;
		      }
		  }
		 }
	    }
	}
    }
}
    
