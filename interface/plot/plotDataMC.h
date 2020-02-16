#include "plugin/tdrstyle.C"
#include "plugin/CMS_lumi.C"
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

void plotDataMC(TString subname , int mode,const char outpath[10], TString addcut,bool isdataMC,int binning, float min, float max, TString var, TString title, TString tree)
{
  setTDRStyle();
  //signal
  TChain ggF(tree);
  TChain VBF(tree);
  TChain ttH(tree);
  TChain ZH(tree);
  TChain WplusH(tree);
  TChain WminusH(tree);
  //bkg
  TChain Zg(tree);
  TChain EWKZg(tree);
  TChain DY(tree);
  TChain DYMG(tree);
  TChain VV(tree);
  TChain VVV(tree);
  TChain data(tree);
  TChain TT(tree);
  TChain ZZ2l2q(tree);
  TChain WW2l2q(tree);
  TChain ZZ4l(tree);
  TChain ZZ2l2n(tree);
  TChain TT2l2n(tree);
  TChain WWlnqq(tree);
  TChain WZ3ln(tree);
  TChain WZ2l2q(tree);
  TChain HZZ(tree);
  TChain Hmumu(tree);
  TChain TTGJ(tree);
  TString fname;
  if(mode == 0|| mode == 2)//ele
    {
      ggF.Add(Form("../outfile/mc_%s_ele_HZg_ggF_125GeV.root",subname.Data()));
      VBF.Add(Form("../outfile/mc_%s_ele_HZg_VBF_125GeV.root",subname.Data()));
      ttH.Add(Form("../outfile/mc_%s_ele_HZg_ttH_125GeV.root",subname.Data()));	
      WplusH.Add(Form("../outfile/mc_%s_ele_HZg_WplusH_125GeV.root",subname.Data()));	
      WminusH.Add(Form("../outfile/mc_%s_ele_HZg_WminusH_125GeV.root",subname.Data()));	
      ZH.Add(Form("../outfile/mc_%s_ele_HZg_ZH_125GeV.root",subname.Data()));	
      //DY.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      DY.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      DYMG.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_MG.root",subname.Data()));	
      EWKZg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",subname.Data()));	
      Zg.Add(Form("../outfile/mc_%s_ele_Zg_aMCatNLO.root",subname.Data()));	
      TT2l2n.Add(Form("../outfile/mc_%s_ele_TTTo2L2Nu_powheg.root",subname.Data()));	
      TT.Add(Form("../outfile/mc_%s_ele_TT_powheg.root",subname.Data()));
      TTGJ.Add(Form("../outfile/mc_%s_ele_TTGjets.root",subname.Data()));
      /*ggF.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_ggF_125GeV_UEU.root",subname.Data()));
      VBF.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_VBF_125GeV.root",subname.Data()));
      ttH.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_ttH_125GeV.root",subname.Data()));	
      WplusH.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_WplusH_125GeV.root",subname.Data()));	
      WminusH.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_WminusH_125GeV.root",subname.Data()));	
      ZH.Add(Form("../outfile/mc_Legacy16_allMVA_ele_HZg_ZH_125GeV.root",subname.Data()));	
      //DY.Add(Form("../outfile/mc_Legacy16_allMVA_ele_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      DY.Add(Form("../outfile/mc_Legacy16_allMVA_ele_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      DYMG.Add(Form("../outfile/mc_Legacy16_allMVA_ele_DYJetsToLL_m50_MG.root",subname.Data()));	
      EWKZg.Add(Form("../outfile/mc_Legacy16_allMVA_ele_Zg_EWK.root",subname.Data()));	
      Zg.Add(Form("../outfile/mc_Legacy16_allMVA_ele_Zg_aMCatNLO.root",subname.Data()));	
      TT2l2n.Add(Form("../outfile/mc_Legacy16_allMVA_ele_TTTo2L2Nu_powheg.root",subname.Data()));	
      TTGJ.Add(Form("../outfile/mc_Legacy16_allMVA_ele_TTGjets.root",subname.Data()));
      TT.Add(Form("../outfile/mc_Legacy16_allMVA_ele_TT_powheg.root",subname.Data()));*/
      if(addcut.Contains("cat>5&&cat<10"))
	{
	  HZZ.Add(Form("../outfile/mc_%s_ele_HZZ4l.root",subname.Data()));	
	  Hmumu.Add(Form("../outfile/mc_%s_ele_HMuMu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_ele_ZZTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_ele_ZZTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_ele_ZZTo4L.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_ele_WWTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_ele_WWToLNuQQ.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_ele_WZTo3LNu.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_ele_WZTo2L2Q.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_ele_TTTo2L2Nu_powheg.root",subname.Data()));	
	  ZZ2l2n.Add(Form("../outfile/mc_%s_ele_ZZTo2L2Nu.root",subname.Data()));	
	  ZZ2l2q.Add(Form("../outfile/mc_%s_ele_ZZTo2L2Q.root",subname.Data()));	
	  ZZ4l.Add(Form("../outfile/mc_%s_ele_ZZTo4L.root",subname.Data()));	
	  TT2l2n.Add(Form("../outfile/mc_%s_ele_TTTo2L2Nu_powheg.root",subname.Data()));	
	  WW2l2q.Add(Form("../outfile/mc_%s_ele_WWTo2L2Nu.root",subname.Data()));
	  WWlnqq.Add(Form("../outfile/mc_%s_ele_WWToLNuQQ.root",subname.Data()));
	  WZ3ln.Add(Form("../outfile/mc_%s_ele_WZTo3LNu.root",subname.Data()));
	  WZ2l2q.Add(Form("../outfile/mc_%s_ele_WZTo2L2Q.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_ZZZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WZZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WWZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WWW.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WGG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WWG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_ZGG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_WZG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_ele_TTG_dilept.root",subname.Data()));
	}
      //if(addcut.Contains("isbtag"))
      data.Add(Form("../outfile/Data_%s_ele_EG.root",subname.Data())); 
      //data.Add(Form("../outfile/Data_%s_ele_EG.root",subname.Data()));
      //data.Add(Form("../outfile/Data_%s_ele_EG_Run2017B_MarReminiAOD.root",subname.Data()));
      //data.Add(Form("/home/mingyan/output/Data_Moriond17_skim_update0709_ele_EG.root",subname.Data()));;
    }
	  
  if(mode == 1|| mode == 2)//mu
    {
      ggF.Add(Form("../outfile/mc_%s_mu_HZg_ggF_125GeV.root",subname.Data()));
      VBF.Add(Form("../outfile/mc_%s_mu_HZg_VBF_125GeV.root",subname.Data()));
      ttH.Add(Form("../outfile/mc_%s_mu_HZg_ttH_125GeV.root",subname.Data()));	
      WplusH.Add(Form("../outfile/mc_%s_mu_HZg_WplusH_125GeV.root",subname.Data()));	
      WminusH.Add(Form("../outfile/mc_%s_mu_HZg_WminusH_125GeV.root",subname.Data()));	
      ZH.Add(Form("../outfile/mc_%s_mu_HZg_ZH_125GeV.root",subname.Data()));	
      DY.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      DYMG.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_MG.root",subname.Data()));	
      Zg.Add(Form("../outfile/mc_%s_mu_Zg_aMCatNLO.root",subname.Data()));	
      EWKZg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",subname.Data()));	
      TT2l2n.Add(Form("../outfile/mc_%s_mu_TTTo2L2Nu_powheg.root",subname.Data()));	
      TTGJ.Add(Form("../outfile/mc_%s_mu_TTGjets.root",subname.Data()));
      if(addcut.Contains("cat>5&&cat<10"))
	{
	  HZZ.Add(Form("../outfile/mc_%s_mu_HZZ4l.root",subname.Data()));	
	  Hmumu.Add(Form("../outfile/mc_%s_mu_HMuMu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_mu_ZZTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_mu_ZZTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_mu_ZZTo4L.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_mu_WWTo2L2Nu.root",subname.Data()));	
	  VV.Add(Form("../outfile/mc_%s_mu_WWToLNuQQ.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_mu_WZTo3LNu.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_mu_WZTo2L2Q.root",subname.Data()));
	  VV.Add(Form("../outfile/mc_%s_mu_TTTo2L2Nu_powheg.root",subname.Data()));	
	  ZZ2l2n.Add(Form("../outfile/mc_%s_mu_ZZTo2L2Nu.root",subname.Data()));	
	  ZZ2l2q.Add(Form("../outfile/mc_%s_mu_ZZTo2L2Q.root",subname.Data()));	
	  ZZ4l.Add(Form("../outfile/mc_%s_mu_ZZTo4L.root",subname.Data()));	
	  TT2l2n.Add(Form("../outfile/mc_%s_mu_TTTo2L2Nu_powheg.root",subname.Data()));	
	  WW2l2q.Add(Form("../outfile/mc_%s_mu_WWTo2L2Nu.root",subname.Data()));
	  WWlnqq.Add(Form("../outfile/mc_%s_mu_WWToLNuQQ.root",subname.Data()));
	  WZ3ln.Add(Form("../outfile/mc_%s_mu_WZTo3LNu.root",subname.Data()));
	  WZ2l2q.Add(Form("../outfile/mc_%s_mu_WZTo2L2Q.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_ZZZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WZZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WWZ.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WWW.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WGG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WWG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_ZGG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_WZG.root",subname.Data()));
	  VVV.Add(Form("../outfile/mc_%s_mu_TTG_dilept.root",subname.Data()));
	}
      //if(addallMVA.Contains("isbtag"))
      TT.Add(Form("../outfile/mc_%s_mu_TT_powheg.root",subname.Data()));
      data.Add(Form("../outfile/Data_%s_mu_Mu.root",subname.Data()));
      //data.Add(Form("../outfile/Data_2017_mu_Mu_Run2017F_MarReminiAOD.root",subname.Data()));
      //data.Add(Form("/home/mingyan/output/Data_Moriond17_skim_update0709_mu_Mu.root",subname.Data()));
    }

  //MC data comparison
  TH1F *MC = new TH1F("MC", " ",binning, min, max);    
  TH1F *Data = new TH1F("Data", " ",binning, min, max);    
  //histo for stack
  TH1F *hsig = new TH1F("hsig", " ",binning, min, max);
  TH1F *hVBF = new TH1F("hVBF"," ",binning,min,max);
  TH1F *hDY = new TH1F("hDY", " ",binning, min, max);
  TH1F *hDYMG = new TH1F("hDYMG", " ",binning, min, max);
  TH1F *hZg = new TH1F("hZg", " ",binning, min, max);
  TH1F *hEWKZg = new TH1F("hEWKZg", " ",binning, min, max);
  TH1F *hVV= new TH1F("hVV", " ", binning, min, max);
  TH1F *hTT = new TH1F("hTT"," ",binning, min, max);
  TH1F *hTTG = new TH1F("hTTG"," ",binning, min, max);
  TH1F *hHZZ = new TH1F("hHZZ"," ",binning, min, max);
  TH1F *hHmumu = new TH1F("hHmumu"," ",binning, min, max);
  TH1F *hZZ2l2q = new TH1F("hZZ2l2q"," ",binning,min,max);
  TH1F *hZZ4l = new TH1F("hZZ4l"," ",binning,min,max);
  TH1F *hZZ2l2n = new TH1F("hZZ2l2n"," ",binning,min,max);
  TH1F *hTT2l2n = new TH1F("hTT2l2n"," ",binning,min,max);
  TH1F *hWW2l2q = new TH1F("hWW2l2q"," ",binning,min,max);
  TH1F *hWWlnqq = new TH1F("hWWlnqq"," ",binning,min,max);
  TH1F *hWZ3ln = new TH1F("hWZ3ln"," ",binning,min,max);
  TH1F *hWZ2l2q = new TH1F("hWZ2l2q"," ",binning,min,max);
  TH1F *hVVV = new TH1F("hVVV"," ",binning, min, max);
  TH1F *hdata = new TH1F("hdata"," ",binning, min, max);    
  char mccut[200];
  //if(mode==0)
  sprintf(mccut,"(%s)*mcwei*genwei*totSF*puwei",addcut.Data());
  //else sprintf(mccut,"(%s)*mcwei*genwei*puwei*sfmuID[0]*sfmuID[1]*sfgID*sfgVeto",addcut.Data());
  
  //sprintf(mccut,"(%s&&phoPt>20)*mcwei*genwei*puwei*sfgVeto*sfeID[0]*sfeID[1]*sfGSF[0]*sfGSF[1]*sfGSF[2]*sfeID[2]*sfetrg[0]*sfetrg[1]*sfgID",addcut.Data());
  TString cut =  mccut;
  
  ggF.Draw(Form("%s>>hsig",var.Data()),cut.Data());
  VBF.Draw(Form("%s>>+hsig",var.Data()),cut.Data());
  VBF.Draw(Form("%s>>hVBF",var.Data()),cut.Data());
  ttH.Draw(Form("%s>>+hsig",var.Data()),cut.Data());
  ZH.Draw(Form("%s>>+hsig",var.Data()),cut.Data());
  WplusH.Draw(Form("%s>>+hsig",var.Data()),cut.Data());
  WminusH.Draw(Form("%s>>+hsig",var.Data()),cut.Data()); 
  Zg.Draw(Form("%s>>hZg",var.Data()),Form("%s",cut.Data())); 
  DY.Draw(Form("%s>>hDY",var.Data()),Form("%s",cut.Data())); 
  DYMG.Draw(Form("%s>>hDYMG",var.Data()),Form("%s*14420./5439.2",cut.Data())); 
  //Zg.Draw(Form("%s>>hZg",var.Data()),Form("%s*4.833e+01/117.864",cut.Data()));
  //EWKZg.Draw(Form("%s>>hEWKZg",var.Data()),Form("%s*0.1097/109.7",cut.Data()));
  EWKZg.Draw(Form("%s>>hEWKZg",var.Data()),Form("%s",cut.Data()));
  TT.Draw(Form("%s>>hTT",var.Data()),cut.Data());
  TTGJ.Draw(Form("%s>>hTTG",var.Data()),cut.Data());
  /*VV.Draw(Form("%s>>hVV",var.Data()),cut.Data());
    VVV.Draw(Form("%s>>hVVV",var.Data()),cut.Data());
    //TT2l2n.Draw(Form("%s>>hVV",var.Data()),cut);	

    HZZ.Draw(Form("%s>>hHZZ",var.Data()),cut.Data());
    Hmumu.Draw(Form("%s>>hHmumu",var.Data()),cut.Data());*/
  /*    ZZ2l2q.Draw("mllg>>hZZ2l2q",cut);
	ZZ2l2n.Draw("mllg>>hZZ2l2n",cut);
	ZZ4l.Draw("mllg>>hZZ4l",cut);
	TT2l2n.Draw("mllg>>hTT2l2n",cut);
	WW2l2q.Draw("mllg>>hWW2l2q",cut);
	WWlnqq.Draw("mllg>>hWWlnqq",cut);
	WZ2l2q.Draw("mllg>>hWZ2l2q",cut);
	WZ3ln.Draw("mllg>>hWZ3ln",cut);*/


  TString datacut;
  if(addcut=="1.") datacut = "";
  else datacut = addcut;


  if(var=="mllg")data.Draw(Form("%s>>hdata",var.Data()),Form("(mllg<120||mllg>130)",datacut.Data()));
  else data.Draw(Form("%s>>hdata",var.Data()),datacut);
x  cout<<hdata->Integral(-1,-1)<<" "<<hsig->Integral(-1,-1)<<" "<<hDY->Integral(-1,-1)<<" "<<hZg->Integral(-1,-1)<<" "<<hEWKZg->Integral(-1,-1)<<endl;
  cout<<"s/sqrtb:"<<hsig->Integral(5,15)/sqrt(hDY->Integral(5,15)+hZg->Integral(5,15)+hVV->Integral(5,15))<<endl;
  TH1F *MC1 = new TH1F("MC1", " ",binning, min, max);    
  if(isdataMC==true)
    {
      //mc/data
      ggF.Draw(Form("%s>>MC",var.Data()),cut);
      VBF.Draw(Form("%s>>+MC",var.Data()),cut);
      ttH.Draw(Form("%s>>+MC",var.Data()),cut);
      ZH.Draw(Form("%s>>+MC",var.Data()),cut);
      WplusH.Draw(Form("%s>>+MC",var.Data()),cut);
      WminusH.Draw(Form("%s>>+MC",var.Data()),cut); 
      //EWKZg.Draw(Form("%s>>+MC",var.Data()),Form("%s*0.1097/109.7",cut.Data()));
      EWKZg.Draw(Form("%s>>+MC",var.Data()),Form("%s",cut.Data()));
      ggF.Draw(Form("%s>>MC1",var.Data()),cut);
      VBF.Draw(Form("%s>>+MC1",var.Data()),cut);
      ttH.Draw(Form("%s>>+MC1",var.Data()),cut);
      ZH.Draw(Form("%s>>+MC1",var.Data()),cut);
      WplusH.Draw(Form("%s>>+MC1",var.Data()),cut);
      WminusH.Draw(Form("%s>>+MC1",var.Data()),cut); 
      EWKZg.Draw(Form("%s>>+MC1",var.Data()),Form("%s*0.1143/109.7",cut.Data()));
      //DY.Draw(Form("%s>>+MC",var.Data()),cut);
      ///TT2l2n.Draw(Form("%s>>+MC",var.Data()),cut);
      //Zg.Draw(Form("%s>>+MC",var.Data()),Form("%s*4.833e+01/117.864",cut.Data()));
      Zg.Draw(Form("%s>>+MC",var.Data()),Form("%s",cut.Data())); 
      DY.Draw(Form("%s>>+MC",var.Data()),Form("%s",cut.Data())); 
      TTGJ.Draw(Form("%s>>+MC",var.Data()),Form("%s",cut.Data()));
      Zg.Draw(Form("%s>>+MC1",var.Data()),Form("%s",cut.Data())); 
      DYMG.Draw(Form("%s>>+MC1",var.Data()),Form("%s*14420./5439.2",cut.Data())); 
      //Zg.Draw(Form("%s>>+MC",var.Data()),Form("%s",cut.Data()));
      
      if(var=="mllg")data.Draw(Form("%s>>Data",var.Data()),Form("%s(mllg<120||mllg>130)",datacut.Data()));
      else data.Draw(Form("%s>>Data",var.Data()),datacut);
      if(addcut=="&&cat>5&&cat<10")
	{
	  VV.Draw(Form("%s>>+MC",var.Data()),cut);
	  VVV.Draw(Form("%s>>+MC",var.Data()),cut);
	}
      //if(addcut.Contains("isbtag"))
      TT.Draw(Form("%s>>+MC",var.Data()),cut);
    }

  
  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.);
  if(isdataMC==true) pad1->SetPad(0,0.25,1.,1.);
  pad1->SetBottomMargin(0.1);
  pad1->Draw();
  pad1->cd();
  gStyle->SetOptStat(0);

  THStack *hs = new THStack("hs","");
  THStack *hs1 = new THStack("hs1","");
  hVBF->SetLineWidth(3);
  hVBF->SetLineColor(kBlue);
  hVBF->SetLineStyle(9);
  hEWKZg->SetLineColor(kAzure+1);
  hEWKZg->SetFillColor(kAzure+1);
  hZg->SetFillColor(TColor::GetColor("#16bac5"));
  hZg->SetLineColor(TColor::GetColor("#16bac5"));
  hDY->SetFillColor(TColor::GetColor("#ffb400"));
  hDY->SetLineColor(TColor::GetColor("#ffb400"));
  hDYMG->SetLineColor(TColor::GetColor("#9E6300"));
  //if(addcut.Contains("isbtag"))
  hTT->SetLineColor(kOrange+7);
  hTT->SetFillColor(kOrange+7);
  hTTG->SetFillColor(kRed-9);
  hTTG->SetLineColor(kRed-9);

  hZg->SetLineColor(TColor::GetColor("#16bac5"));
  
  ///hDYMG->SetFillStyle(3018);
  //hDY->SetFillStyle(3018);

  hTT2l2n->SetFillColor(TColor::GetColor("#00b5c4"));
  hTT2l2n->SetLineColor(TColor::GetColor("#00b5c4"));
  //  if(addcut.Contains("isbtag"))

  if(addcut.Contains("&&cat>5&&cat<10"))
    {
      hVV->SetFillColor(TColor::GetColor("#00d2aa"));
      hVVV->SetFillColor(TColor::GetColor("#93ea87"));
      hVV->SetLineColor(TColor::GetColor("#00d2aa"));
      hVVV->SetLineColor(TColor::GetColor("#93ea87"));
      /*hHZZ->SetFillColor(kViolet+1);
	hHmumu->SetFillColor(kOrange-3);
	hHZZ->SetLineColor(kViolet+1);
	hHmumu->SetLineColor(kOrange-3);*/

    }

  /*ZZ2l2n->SetFillColor(kSpring);
    hZZ2l2q->SetFillColor(kSpring+10);
    hZZ4l->SetFillColor(kSpring+9);
    hTT2l2n->SetFillColor(kSpring-7);
    hWZ3ln->SetFillColor(kTeal-3);
    hWZ2l2q->SetFillColor(kTeal);
    hWW2l2q->SetFillColor(kCyan);
    hWWlnqq->SetFillColor(kCyan-9);*/
  //gPad->SetLogy();
  hs->Add(hsig);
  hs->Add(hEWKZg);
  hs->Add(hZg);
  hs->Add(hTT);
  hs->Add(hTTG);
  hs->Add(hDY);

  hs1->Add(hsig);
  hs1->Add(hEWKZg);
  hs1->Add(hZg);
  hs1->Add(hTT);
  hs1->Add(hDY);


  //hs->Add(hTT2l2n);
  //if(addcut.Contains("isbtag"))
  if(addcut.Contains("&&cat>5&&cat<10"))
    {
      hs->Add(hVV);
      hs->Add(hVVV);	  
      hs->Add(hHZZ);
      hs->Add(hHmumu);
    }  
  //hs->SetMaximum(80);
  hs->Draw("hist");
  //hs1->Draw("hist");
  //pad1->SetLogy();
  if(isdataMC==false)hs->GetXaxis()->SetLabelSize(0);
  hs->GetYaxis()->SetTitle("Events");
  if(isdataMC==false)hs->GetXaxis()->SetTitle(title);
  hs->SetMinimum(10-e6);
  //hs->SetMaximum(80);
  hs->SetMaximum(MC->GetMaximum()*1.5);
  hsig->SetLineWidth(3);
  hVBF->SetLineWidth(3);
  hsig->SetLineColor(kRed);
  //hsig->SetFillColor(kRed);
  hsig->Scale(1000.);
  //hHZZ->Scale(50.);
  //hHmumu->Scale(500.);
  hVBF->Scale(1000.);     
  hdata->SetMarkerColor(kBlack);
  hdata->SetMarkerSize(1);
  hdata->SetMarkerStyle(20);
  hdata->SetLineColor(kBlack);
  hdata->Draw("ELPSAME");
  hsig->Draw("HISTSAME"); 

  //c1->SetLogy();
  //hHmumu->Draw("HISTSAME");
  //hHZZ->Draw("HISTSAME");
  //if(tree.Contains("tVBF"))
  hVBF->Draw("HISTSAME");
  TLegend *l8 = new TLegend(0.75,0.65,0.95,0.92);
  //l8->SetNColumns(2);
  l8->SetFillStyle(0);
  l8->SetBorderSize(0);
  l8->AddEntry(hdata, "Data", "lep");
  l8->AddEntry(hsig, "Signalx1000", "l");
  //if(tree.Contains("tVBF"))
  l8->AddEntry(hVBF,"VBFx1000","l");
  l8->AddEntry(hZg, "SM Z#gamma", "f");
  //if(subname.Contains("VBF"))
  l8->AddEntry(hEWKZg, "EWK Z#gamma", "f");
  l8->AddEntry(hDY, "DY+jet", "f");
  //l8->AddEntry(hDYMG, "DY+jet MG", "f");
  //l8->AddEntry(hTT2l2n,"TT#rightarrow2l2#nu","f");       
  //  if(addcut.Contains("isbtag"))
  l8->AddEntry(hTT,"TTbar","f");
  //l8->AddEntry(hTTG,"TT#gamma","f");
  if(addcut.Contains("&&cat>5&&cat<10"))
    {
      l8->AddEntry(hVV, "VV", "f");
      l8->AddEntry(hVVV, "VVV", "f");
      l8->AddEntry(hHZZ, "HZZ#rightarrow4l", "f");
      l8->AddEntry(hHmumu, "H#mu#mu", "f");
    }
  /*  l8->AddEntry(hZZ2l2q,"ZZ#rightarrow2l2q","f");
      l8->AddEntry(hZZ4l,"ZZ#rightarrow4l","f");
      l8->AddEntry(hZZ2l2n,"ZZ#rightarrow2l2#nu","f");
      l8->AddEntry(hTT2l2n,"TT#rightarrow2l2#nu","f"); 
      l8->AddEntry(hWW2l2q,"WW#rightarrow2l2q","f");
      l8->AddEntry(hWWlnqq,"WW#rightarrowl#nuqq","f");
      l8->AddEntry(hWZ2l2q,"WZ#rightarrow2l2q","f");
      l8->AddEntry(hWZ3ln,"WZ#rightarrow3l#nu","f");*/

  l8->SetFillColor(0);
  l8->SetTextSize(0.04);
  l8->Draw();
  if(isdataMC==true)
    {            
      c->cd();
      TPad *p2 = new TPad("p2","p2", 0, 0.0, 1, 0.25);
    
      p2->SetTopMargin(0.02);
      p2->SetBottomMargin(0.3);
      p2->Draw();
      p2->cd();
    
      TH1F *dataMC = new TH1F("dataMC", " ", binning,min, max);
      TH1F *dataMC1 = new TH1F("dataMC1", " ", binning,min, max);
      //cout<<"chi2:"<<Data->Chi2Test(MC,"UW")<<endl;
      
      dataMC->Divide(Data,MC);
      dataMC1->Divide(Data,MC1);
      //dataMC->Sumw2();
      gPad->SetGridy();
      dataMC->Draw("ap");
      dataMC->GetXaxis()->SetLabelSize(0.15);
      dataMC->GetYaxis()->SetLabelSize(0.15);
      dataMC->GetXaxis()->SetTitle(title);
      dataMC->GetYaxis()->SetTitle("Data/MC");
      dataMC->GetYaxis()->SetNdivisions(505);
      dataMC->GetXaxis()->SetTitleSize(0.15);
      dataMC->GetYaxis()->SetTitleOffset(0.45);
      dataMC->GetYaxis()->SetTitleSize(0.15);
      dataMC->SetMaximum(2.);
      dataMC->SetMinimum(0.3);
      dataMC->SetMarkerSize(1);
      /*dataMC->SetLineColor(TColor::GetColor("#ffb400"));
      dataMC->SetMarkerColor(TColor::GetColor("#ffb400"));
      dataMC1->SetLineColor(TColor::GetColor("#9E6300"));
      dataMC1->SetMarkerColor(TColor::GetColor("#9E6300"));
      */
      dataMC->Draw();
      //dataMC1->Draw("same");
      //p2->Update();
      //p2->RedrawAxis();
      //p2->GetFrame()->Draw();
    }
  //extraText  = "";
  extraText  = "Preliminary";
  // extraText  = "In progress";
  string lumi;
  
  if(subname.Contains("16")) lumi= "35.5";
  if(subname.Contains("17")) lumi= "41.8";
  if(subname.Contains("18")) lumi= "58.8";
  lumi_13TeV = lumi+"fb^{-1}";

  CMS_lumi(pad1, 4, 0);
  c->Print(outpath);
}
