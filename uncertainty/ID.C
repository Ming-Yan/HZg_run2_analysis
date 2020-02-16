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

void integral()
{
  setTDRStyle();
  //signal
  TChain ggF("tZg");
  TChain VBF("tZg");
  TChain ttH("tZg");
  TChain ZH("tZg");
  TChain WplusH("tZg");
  TChain WminusH("tZg");
  
  ggF.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_ggF_125GeV_ext1.root");
  VBF.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_VBF_125GeV_ext1.root");
  ttH.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_ttH_125GeV.root");
  ZH.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_ZH_125GeV.root");
  WplusH.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_WplusH_125GeV.root");
  WminusH.Add("/home/mingyan/output/mc/mc_btag_ele_HZg_WminusH_125GeV.root");
  
  ggF.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_ggF_125GeV_ext1.root");
  VBF.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_VBF_125GeV_ext1.root");
  ttH.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_ttH_125GeV.root");
  ZH.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_ZH_125GeV.root");
  WplusH.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_WplusH_125GeV.root");
  WminusH.Add("/home/mingyan/output/mc/mc_btag_mu_HZg_WminusH_125GeV.root");


  //MC data comparison55,115,170
  TH1F *MC = new TH1F("MC", " ",55, 115, 170);    
  //histo for stack
  TH1F *hsig = new TH1F("hsig", " ",55, 115, 170);
  TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
  TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
  TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
  TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
  TH1F *hsig5 = new TH1F("hsig5", " ",55, 115, 170);
  TH1F *hdata = new TH1F("hdata"," ",55, 115, 170);    
  /*
  ggF.Draw("mllg>>hsig","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  VBF.Draw("mllg>>hsig1","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  ttH.Draw("mllg>>hsig2","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  ZH.Draw("mllg>>hsig3","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  WplusH.Draw("mllg>>hsig4","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  WminusH.Draw("mllg>>hsig5","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");*/
  ggF.Draw("mllg>>hsig","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))");
  VBF.Draw("mllg>>hsig1","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))");
  ttH.Draw("mllg>>hsig2","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))");
  ZH.Draw("mllg>>hsig3","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))*mcwei*genwei*puwei*totSF");
  WplusH.Draw("mllg>>hsig4","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))");
  WminusH.Draw("mllg>>hsig5","((cat>=6&&cat<=9)&&(mllg>=115&&mllg<=170))");


  double nominal = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  cout<<"@@"<<(hsig->Integral(-1,-1)+ hsig1->Integral(-1,-1))/nominal<<endl;
  cout<< hsig->Integral(-1,-1)<<"\n"<< hsig1->Integral(-1,-1)<<"\n"<<hsig2->Integral(-1,-1)<<"\n"<<hsig3->Integral(-1,-1)<<"\n"<<hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1)<<"\n"<<nominal<<endl;

  ///computing effective sigma
  TChain ch("tZg");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_ggF_125GeV_ext1.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_VBF_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_ttH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_ZH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_WplusH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_ele_HZg_WminusH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_ggF_125GeV_ext1.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_VBF_125GeV_ext1.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_ttH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_ZH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_WplusH_125GeV.root");
  ch.Add("/home/mingyan/output/mc/mc_Moriond17_update0709_mu_HZg_WminusH_125GeV.root");
  vector<float> sig;

  Int_t cat,isbtag;
  float mllg_;
  ch.SetBranchAddress("cat", &cat);
  ch.SetBranchAddress("mllg", &mllg_);
  //ch.SetBranchAddress("isbtag", &isbtag);
  //ch.SetBranchAddress("totSF*(sfGSF+unGSF)/sfGSF*(unGSF+sfGSF)/sfGSF", &totSF*(sfGSF+unGSF)/sfGSF*(unGSF+sfGSF)/sfGSF_);
  
  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
	
      if(cat>5&&cat<10)
	{

	  if(mllg_>170||mllg_<115)continue;
	  sig.push_back(mllg_);
	}

    }
  float min = 115.;
  float max = 170.;     
  float Zeffsigma = sigmaEff(sig, 0.68, min, max);
  cout<< min << " " << max << " " <<Zeffsigma<<endl;

  //==========================================MUON=================================================//
	
  //-----------------------------------------muon ID---------------------------------------------//
  //above 20GeV
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuID[0])");
  double muIDa1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  double muIDa2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  double muIDa3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  //below 20
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuID[1])");
  double muIDb2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
 
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuID[2])");
  double muIDb3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  double muID = sqrt(pow((muIDa1+muIDa2+muIDa3),2)+sqrt(pow((muIDb2+muIDb3),2)));
	
  //-----------------------------------------muon Iso---------------------------------------------//
  /*    
  //above 20GeV
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[0])");
  muIDa1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  muIDa2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  muIDa3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  //below 20
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[1])");
  muIDb2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=20.)*mcwei*puwei*genwei*totSF*(unmuIso[2])");
  muIDb3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  double muIso = sqrt(pow((muIDa1+muIDa2+muIDa3),2)+sqrt(pow((muIDb2+muIDb3),2)));
		
  //muon trk eff
  //above 20GeV
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[0]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[0])");
  muIDa1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  muIDa2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt>10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  muIDa3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  //below 10
  
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&lepPt[1]<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[1])");
  muIDb2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170)&&alepPt<=10.)*mcwei*puwei*genwei*totSF*(unmuTrk[2])");
  muIDb3= hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  double mutrk = sqrt(pow((muIDa1+muIDa2+muIDa3),2)+sqrt(pow((muIDb2+muIDb3),2)));
	
  cout<<"mutrk:"<<sqrt(pow(mutrk/nominal,2)+pow(muID/nominal,2)+pow(mutrk/nominal,2))<<endl;*/

  //-------------------------------------------mu trg----------------------------------------------//
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])");           
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])");             
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])");                 
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[0])"); 
	
  double mutrg1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])");                       
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])");                       
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])");                 
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unmutrg[1])"); 
	
  double mutrg2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  cout<<"mu trg:"<<sqrt(pow((mutrg1/nominal),2)+pow((mutrg2/nominal),2))<<endl;


  //==========================================ELECTRON=================================================//
	
  //-------------------------------------------ele ID----------------------------------------------//
  //above 10GeV
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  double eIDa1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  double eIDa2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  cout<<"eID2:"<< hsig->Integral(-1,-1)<<" "<<hsig1->Integral(-1,-1)<<" "<<hsig2->Integral(-1,-1)<<" "<<hsig3->Integral(-1,-1)<<" "<<hsig4->Integral(-1,-1)<<" "<<hsig5->Integral(-1,-1)<<endl;

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  double eIDb3 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
  cout<<"eID3:"<< hsig->Integral(-1,-1)<<" "<<hsig1->Integral(-1,-1)<<" "<<hsig2->Integral(-1,-1)<<" "<<hsig3->Integral(-1,-1)<<" "<<hsig4->Integral(-1,-1)<<" "<<hsig5->Integral(-1,-1)<<endl;
  cout<<eIDa1<<" "<<eIDa2<<" "<<" "<<eIDb3<<endl;
  double eID = eIDa1+eIDa2+eIDb3;
  

  //-------------------------------------------ele GSF----------------------------------------------//
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unGSF[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[0])");
  eIDa1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[1])");
  eIDa2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(uneID[2])");
  eIDa3 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	

  cout<<nominal<<endl;
  double egsf = eIDa1+eIDa2+eIDa3;
  cout<<eID/nominal<<" "<<egsf/nominal<<endl;	
  cout<<"ele ID:"<<sqrt(pow(eID/nominal,2)+pow(egsf/nominal,2))<<endl;
	
  //-------------------------------------------ele trg----------------------------------------------//

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[0])");
  double etrg1 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unetrg[1])");
  double etrg2 = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);

  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(unedz)");
  double edz = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);    

  cout<<"ele trg:"<<sqrt(pow((etrg1/nominal),2)+pow((etrg2/nominal),2)+pow((edz/nominal),2))<<endl;

  //==========================================PHOTON=================================================//
	
  //-------------------------------------------pho ID----------------------------------------------//
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungID)");
  double gID = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);
	
  //-------------------------------------------pho veto----------------------------------------------//
  ggF.Draw("mllg>>hsig","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  VBF.Draw("mllg>>hsig1","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  ttH.Draw("mllg>>hsig2","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  ZH.Draw("mllg>>hsig3","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  WplusH.Draw("mllg>>hsig4","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  WminusH.Draw("mllg>>hsig5","((cat==6||cat==7||cat==8||cat==9)&&(mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF*(ungVeto)");
  double gveto = hsig->Integral(-1,-1)+hsig1->Integral(-1,-1)+hsig2->Integral(-1,-1)+hsig3->Integral(-1,-1)+hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1);   
  //	cout<<gID<<" "<<gveto<<" "<<nominal<<endl;
  cout<<"gID:"<<sqrt(pow((gID/nominal),2)+pow((gveto/nominal),2))<<endl;

}
