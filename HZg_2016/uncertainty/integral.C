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
  
  ggF.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_ggF_125GeV_ext1.root");
  VBF.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_VBF_125GeV_ext1.root");
  ttH.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_ttH_125GeV.root");
  ZH.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_ZH_125GeV.root");
  WplusH.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_WplusH_125GeV.root");
  WminusH.Add("/home/mingyan/output/mc/mc_study_vtx_ele_HZg_WminusH_125GeV.root");
  
  ggF.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_ggF_125GeV_ext1.root");
  VBF.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_VBF_125GeV_ext1.root");
  ttH.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_ttH_125GeV.root");
  ZH.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_ZH_125GeV.root");
  WplusH.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_WplusH_125GeV.root");
  WminusH.Add("/home/mingyan/output/mc/mc_study_vtx_mu_HZg_WminusH_125GeV.root");


  //MC data comparison55,115,170
  TH1F *MC = new TH1F("MC", " ",55, 115, 170);    
  //histo for stack
  TH1F *hsig = new TH1F("hsig", " ",55, 115, 170);
  TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
  TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
  /*TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
  TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
  TH1F *hsig5 = new TH1F("hsig5", " ",55, 115, 170);
  TH1F *hdata = new TH1F("hdata"," ",55, 115, 170);    
  */

  
  
  ggF.Draw("mllg>>hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  VBF.Draw("mllg>>+hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  ttH.Draw("mllg>>+hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  ZH.Draw("mllg>>+hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  WplusH.Draw("mllg>>+hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");
  WminusH.Draw("mllg>>+hsig","((mllg>=115&&mllg<=170))*mcwei*puwei*genwei*totSF");

  cout<< hsig->Integral(-1,-1)<<"\n"<< hsig1->Integral(-1,-1)<<"\n"<<hsig2->Integral(-1,-1)<<"\n"<<hsig3->Integral(-1,-1)<<"\n"<<hsig4->Integral(-1,-1)+hsig5->Integral(-1,-1)<<"\n"<<nominal<<endl;

  ///computing effective sigma
  /*  TChain ch("tZg");
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
  cout<< min << " " << max << " " <<Zeffsigma<<endl;*/

}
