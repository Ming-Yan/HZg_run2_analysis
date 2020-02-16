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


///0->ele, 1->ele

//plot mc & data comparison
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
  TString fname;
  if(mode == 0|| mode == 2)//ele
    {
      ggF.Add(Form("../outfile/mc_%s_ele_HZg_ggF_125GeV_ext1.root",subname.Data()));
      VBF.Add(Form("../outfile/mc_%s_ele_HZg_VBF_125GeV_ext1.root",subname.Data()));
      ttH.Add(Form("../outfile/mc_%s_ele_HZg_ttH_125GeV.root",subname.Data()));	
      WplusH.Add(Form("../outfile/mc_%s_ele_HZg_WplusH_125GeV.root",subname.Data()));	
      WminusH.Add(Form("../outfile/mc_%s_ele_HZg_WminusH_125GeV.root",subname.Data()));	
      ZH.Add(Form("../outfile/mc_%s_ele_HZg_ZH_125GeV.root",subname.Data()));	
      DY.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      EWKZg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",subname.Data()));	
      Zg.Add(Form("../outfile/mc_%s_ele_Zg_aMCatNLO.root",subname.Data()));	
      TT2l2n.Add(Form("../outfile/mc_%s_ele_TTTo2L2Nu_powheg.root",subname.Data()));	
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
      if(addcut.Contains("isbtag"))TT.Add(Form("../outfile/mc_%s_ele_TT_powheg.root",subname.Data()));
      data.Add(Form("../outfile/Data_%s_ele_EG.root",subname.Data()));;
      //data.Add(Form("/home/mingyan/output/Data_Moriond17_skim_update0709_ele_EG.root",subname.Data()));;
    }
	  
  if(mode == 1|| mode == 2)//mu
    {
      ggF.Add(Form("../outfile/mc_%s_mu_HZg_ggF_125GeV_ext1.root",subname.Data()));
      VBF.Add(Form("../outfile/mc_%s_mu_HZg_VBF_125GeV_ext1.root",subname.Data()));
      ttH.Add(Form("../outfile/mc_%s_mu_HZg_ttH_125GeV.root",subname.Data()));	
      WplusH.Add(Form("../outfile/mc_%s_mu_HZg_WplusH_125GeV.root",subname.Data()));	
      WminusH.Add(Form("../outfile/mc_%s_mu_HZg_WminusH_125GeV.root",subname.Data()));	
      ZH.Add(Form("../outfile/mc_%s_mu_HZg_ZH_125GeV.root",subname.Data()));	
      DY.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_aMCatNLO.root",subname.Data()));	
      Zg.Add(Form("../outfile/mc_%s_mu_Zg_aMCatNLO.root",subname.Data()));	
      EWKZg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",subname.Data()));	
      TT2l2n.Add(Form("../outfile/mc_%s_mu_TTTo2L2Nu_powheg.root",subname.Data()));	
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
      if(addcut.Contains("isbtag"))TT.Add(Form("../outfile/mc_%s_mu_TT_powheg.root",subname.Data()));
      data.Add(Form("../outfile/Data_%s_mu_Mu.root",subname.Data()));;
      //data.Add(Form("/home/mingyan/output/Data_Moriond17_skim_update0709_mu_Mu.root",subname.Data()));;	  
    }

  //MC data comparison
  TH1F *MC = new TH1F("MC", " ",binning, min, max);    
  TH1F *Data = new TH1F("Data", " ",binning, min, max);    
  //histo for stack
  TH1F *hsig = new TH1F("hsig", " ",binning, min, max);
  TH1F *hVBF = new TH1F("hVBF"," ",binning,min,max);
  TH1F *hDY = new TH1F("hDY", " ",binning, min, max);
  TH1F *hZg = new TH1F("hZg", " ",binning, min, max);
  TH1F *hEWKZg = new TH1F("hEWKZg", " ",binning, min, max);
  TH1F *hVV= new TH1F("hVV", " ", binning, min, max);
  TH1F *hTT = new TH1F("hTT"," ",binning, min, max);
  TH1F *hHZZ = new TH1F("hHZZ"," ",binning, min, max);
  TH1F *hHmumu = new TH1F("hHmumu"," ",binning, min, max);
  /*TH1F *hZZ2l2q = new TH1F("hZZ2l2q"," ",11,115,170);
    TH1F *hZZ4l = new TH1F("hZZ4l"," ",11,115,170);
    TH1F *hZZ2l2n = new TH1F("hZZ2l2n"," ",11,115,170);*/
  TH1F *hTT2l2n = new TH1F("hTT2l2n"," ",binning,min,max);
  /*TH1F *hWW2l2q = new TH1F("hWW2l2q"," ",11,115,170);
    TH1F *hWWlnqq = new TH1F("hWWlnqq"," ",11,115,170);
    TH1F *hWZ3ln = new TH1F("hWZ3ln"," ",11,115,170);
    TH1F *hWZ2l2q = new TH1F("hWZ2l2q"," ",11,115,170);*/
  TH1F *hVVV = new TH1F("hVVV"," ",binning, min, max);
  TH1F *hdata = new TH1F("hdata"," ",binning, min, max);    
  char mccut[100];
  sprintf(mccut,"(%s)*puwei*mcwei*totSF*genwei",addcut.Data());
  TCut cut =  mccut;
  ggF.Draw(Form("%s>>hsig",var.Data()),cut);
  VBF.Draw(Form("%s>>+hsig",var.Data()),cut);
  VBF.Draw(Form("%s>>hVBF",var.Data()),cut);
  ttH.Draw(Form("%s>>+hsig",var.Data()),cut);
  ZH.Draw(Form("%s>>+hsig",var.Data()),cut);
  WplusH.Draw(Form("%s>>+hsig",var.Data()),cut);
  WminusH.Draw(Form("%s>>+hsig",var.Data()),cut); 
  Zg.Draw(Form("%s>>hZg",var.Data()),cut);
  DY.Draw(Form("%s>>hDY",var.Data()),cut);
  EWKZg.Draw(Form("%s>>hEWKZg",var.Data()),cut);
  VV.Draw(Form("%s>>hVV",var.Data()),cut);
  VVV.Draw(Form("%s>>hVVV",var.Data()),cut);
  //TT2l2n.Draw(Form("%s>>hVV",var.Data()),cut);	
  TT.Draw(Form("%s>>hTT",var.Data()),cut);
  HZZ.Draw(Form("%s>>hHZZ",var.Data()),cut);
  Hmumu.Draw(Form("%s>>hHmumu",var.Data()),cut);
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
  if(var=="mllg")data.Draw(Form("%s>>hdata",var.Data()),Form("%s(mllg<120||mllg>130)",datacut.Data()));

  data.Draw(Form("%s>>hdata",var.Data()),datacut);
  cout<<hdata->Integral(-1,-1)<<" "<<hsig->Integral(-1,-1)<<" "<<hDY->Integral(-1,-1)<<" "<<hZg->Integral(-1,-1)<<" "<<hEWKZg->Integral(-1,-1)<<endl;
  cout<<"s/sqrtb:"<<hsig->Integral(5,15)/sqrt(hDY->Integral(5,15)+hZg->Integral(5,15)+hVV->Integral(5,15))<<endl;
  hdata->Draw();
  if(isdataMC==true)
    {
      //mc/data
      ggF.Draw(Form("%s>>MC",var.Data()),cut);
      VBF.Draw(Form("%s>>+MC",var.Data()),cut);
      ttH.Draw(Form("%s>>+MC",var.Data()),cut);
      ZH.Draw(Form("%s>>+MC",var.Data()),cut);
      WplusH.Draw(Form("%s>>+MC",var.Data()),cut);
      WminusH.Draw(Form("%s>>+MC",var.Data()),cut); 
      //EWKZg.Draw(Form("%s>>+MC",var.Data()),cut);
      Zg.Draw(Form("%s>>+MC",var.Data()),cut);
      DY.Draw(Form("%s>>+MC",var.Data()),cut);
      ///TT2l2n.Draw(Form("%s>>+MC",var.Data()),cut);
      if(var=="mllg")data.Draw(Form("%s>>Data",var.Data()),Form("%s(mllg<120||mllg>130)",datacut.Data()));
      else data.Draw(Form("%s>>Data",var.Data()),datacut);
      if(addcut=="&&cat>5&&cat<10")
	{
	  VV.Draw(Form("%s>>+MC",var.Data()),cut);
	  VVV.Draw(Form("%s>>+MC",var.Data()),cut);
	}
      //if(addcut.Contains("isbtag"))TT.Draw(Form("%s>>+MC",var.Data()),cut);
    }
  cout<<MC->Integral(-1,-1)<<" "<<Data->Integral(-1,-1)<<endl;
  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.);
  if(isdataMC==true) pad1->SetPad(0,0.25,1.,1.);
  pad1->SetBottomMargin(0.1);
  pad1->Draw();
  pad1->cd();

  gStyle->SetOptStat(0);
  
  THStack *hs = new THStack("hs","");
  hVBF->SetLineWidth(3);
  hVBF->SetLineColor(kBlue);
  hVBF->SetLineStyle(9);
  hEWKZg->SetLineColor(kRed-9);
  hEWKZg->SetFillColor(kRed-9);
  hZg->SetFillColor(kYellow-9);
  hDY->SetFillColor(kCyan-9);
  if(addcut.Contains("isbtag"))hTT->SetFillColor(kOrange-9);
  hsig->SetLineColor(kRed);
  hZg->SetLineColor(kYellow-9);
  hDY->SetLineColor(kCyan-9);
  hTT2l2n->SetFillColor(kSpring-9);
  hTT2l2n->SetLineColor(kSpring-9);
  if(addcut.Contains("isbtag"))hTT->SetLineColor(kOrange-9);
  if(addcut.Contains("&&cat>5&&cat<10"))
    {
      hVV->SetFillColor(kGreen-9);
      hVVV->SetFillColor(kBlue-9);
      hVV->SetLineColor(kGreen-9);
      hVVV->SetLineColor(kBlue-9);
      hHZZ->SetFillColor(kViolet+1);
      hHmumu->SetFillColor(kOrange-3);
      hHZZ->SetLineColor(kViolet+1);
      hHmumu->SetLineColor(kOrange-3);

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
  //hs->Add(hEWKZg);
  hs->Add(hZg);
  hs->Add(hDY);
  //hs->Add(hTT2l2n);
  if(addcut.Contains("isbtag"))hs->Add(hTT);
  if(addcut.Contains("&&cat>5&&cat<10"))
    {
      hs->Add(hVV);
      hs->Add(hVVV);	  
      hs->Add(hHZZ);
      hs->Add(hHmumu);
    }
  /*hs->Add(hZZ2l2n);
    hs->Add(hZZ2l2q);
    hs->Add(hZZ4l);
    hs->Add(hTT2l2n);
    hs->Add(hWZ2l2q);
    hs->Add(hWZ3ln);
    hs->Add(hWWlnqq);
    hs->Add(hWW2l2q);
  */
  //hs->SetMaximum(80);
  hs->Draw("HIST");
  if(isdataMC==false)hs->GetXaxis()->SetLabelSize(0);
  hs->GetYaxis()->SetTitle("Events");
  if(isdataMC==false)hs->GetXaxis()->SetTitle(title);
  hs->SetMinimum(0);
  //hs->SetMaximum(80);
  hs->SetMaximum(MC->GetMaximum()*1.5);
  hsig->SetLineWidth(3);
  hVBF->SetLineWidth(3);
  hsig->SetLineColor(kRed);
  hsig->Scale(50.);
  //hHZZ->Scale(50.);
  //hHmumu->Scale(500.);
  hVBF->Scale(500.);     
  hdata->SetMarkerColor(kBlack);
  hdata->SetMarkerSize(1);
  hdata->SetMarkerStyle(20);
  hdata->SetLineColor(kBlack);
  hdata->Draw("ELPSAME");
  hsig->Draw("HISTSAME"); 
  //hHmumu->Draw("HISTSAME");
  //hHZZ->Draw("HISTSAME");
  if(subname.Contains("VBF"))hVBF->Draw("HISTSAME");
  TLegend *l8 = new TLegend(0.75,0.65,0.95,0.92);
  //l8->SetNColumns(2);
  l8->AddEntry(hdata, "Data", "lep");
  l8->AddEntry(hsig, "Signalx50", "l");
  if(subname.Contains("VBF"))l8->AddEntry(hVBF,"VBFx500","l");
  l8->AddEntry(hZg, "SM Zg", "f");
  if(subname.Contains("VBF"))  l8->AddEntry(hEWKZg, "EWK Zg", "f");
  l8->AddEntry(hDY, "DY+jet", "f");
  //l8->AddEntry(hTT2l2n,"TT#rightarrow2l2#nu","f");       
  if(addcut.Contains("isbtag")) l8->AddEntry(hTT,"TTbar","f");
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
      dataMC->Divide(Data,MC);
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
      dataMC->SetMaximum(2);
      dataMC->SetMinimum(0);
      dataMC->SetMarkerSize(1);
      dataMC->Draw();
      p2->Update();
      p2->RedrawAxis();
      p2->GetFrame()->Draw();
    }
  //extraText  = "";
  //extraText  = "Preliminary";
  extraText  = "In progress";

  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad1, 4, 0);
  c->Print(outpath);
}

void plotvar(int nplot,const char*tree, const char* var ,string *histname, string* finname,  const char *outname, string* cuttype, int hrange, float bin1, float bin2, const char* xaxis, const char* yaxis, bool shape,bool chain,int logxy)
{
  setTDRStyle();
  vector<TCut > cut; cut.clear();
  vector<TFile* > f; f.clear();
  vector<TTree*> t; t.clear();
  vector<TH1F*> hist; hist.clear();
  TChain ch(tree);
  TCanvas *c = new TCanvas("c", "c", 800,600);
  c->cd();

  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 1.);
  pad2->SetBottomMargin(0.12);
  pad2->Draw();
  pad2->cd();
  Color_t color[]={kRed-4,kOrange-3,kYellow+1,kSpring-1,kTeal-5,kAzure+8,kAzure+2,kAzure+3,kViolet+1,kMagenta-7,kPink+9,kOrange-6,kGray+2};
  TLegend *l = new TLegend(0.45,0.75,0.955,0.92);

  int fsize = sizeof(finname)/sizeof(finname[0]);
  float hmax = 0;
  if(chain ==true)
    {
      for(int i = 0 ; i < fsize;i++)
	{
	  ch.Add(finname[i].c_str());
	}
    }
  for (int i = 0 ; i <nplot ; i++)
    {
      if(chain == false)
	{
	  const char* fin = finname[i].c_str(); 
	  f.push_back(TFile::Open(fin));
	  t.push_back((TTree*)f[i]->Get(tree));
	}
      hist.push_back(new TH1F(Form("hist[%d]",i), " ",hrange, bin1, bin2));
      cut.push_back(cuttype[i].c_str());
      char putvar[100];
      sprintf(putvar,"%s>>hist[%d]",var,i);
      if(chain ==false)t[i]->Draw(putvar,cut[i]);
      else ch.Draw(putvar,cut[i]);
      cout<<hist[i]->Integral(-1,-1)<<endl;
      if(shape==true) hist[i]->Scale(1./hist[i]->Integral(-1,-1));
      if(logxy == 0)gPad->SetLogx();
      else if(logxy == 1)gPad->SetLogy();
      hist[i]->SetLineColor(color[i]);
      hist[i]->SetLineWidth(2);

      if(hist[i]->GetMaximum()>hmax) hmax = hist[i]->GetMaximum()*1.5;
      l->AddEntry(hist[i],histname[i].c_str(),"f");
    }

  hist[0]->SetMaximum(hmax*1.2);
  hist[0]->GetXaxis()->SetTitle(xaxis);
  hist[0]->GetYaxis()->SetTitle(yaxis);
  hist[0]->Draw("hist");

  for(int i = 1;i<nplot;i++)
    {
      hist[i]->Draw("histsame");
    }
  l->SetFillColor(0);
  l->SetNColumns(2);
  l->SetTextSize(0.04);
  l->Draw();

 
  //  extraText  = "Preliminary";
  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad2, 4, 0);
  c->Print(outname);

}
/*void plot2D(int nplot,const char*tree, const char* var ,string *histname, string* finname,  string *outname, const char* cuttype, int xrange, float xbin1, float xbin2, int yrange, float ybin1, float ybin2, const char* xaxis, const char* yaxis,int profile,)
  {
  setTDRStyle();
  extraText  = "Preliminary";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad2, 4, 0);
  vector<TCut > cut; cut.clear();
  vector<TFile* > f; f.clear();
  vector<TTree*> t; t.clear();
  vector<TH2F*> hist; hist.clear();
  vector<TProfile* > prof; prof.clear();
  TCanvas *c = new TCanvas("c", "c", 800,600);
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 1.);
  pad2->SetBottomMargin(0.12);

  for (int i = 0 ; i <nplot ; i++)
  {
  c->cd();
  pad2->Draw();
  pad2->cd();
  const char* fin = finname[i].c_str();
  hist.push_back(new TH2F(histname[i].c_str(), " ",xrange, xbin1, xbin2,yrange, ybin1,ybin2));
  cut.push_back(cuttype);
  char putvar[100];
  sprintf(putvar,"%s>>%s",var,histname[i].c_str());
  t[i]->Draw(putvar,cut[i],"colz");
  if(profile!=-1) 
  {
  char profname[80];
  sprintf(profname,"%s_prof%d",histname[i].c_str(),profile);
  if(profile==0)prof.push_back(new TProfile(&profname," ",xrange,xbin1,xbin2));//profx
  if(profile==1)prof.push_back(new TProfile(&profname," ",yrange,ybin1,ybin2));//profy
  sprintf(putvar,"%s>>%s",var,profname);
  t[i]->Draw(putvar,cut[i]);
  prof[i]->GetXaxis()->SetTitle(xaxis);
  prof[i]->GetYaxis()->SetTitle(yaxis);
  char pfout[80];
  sprintf(pfout,"%s.png",profname);
  c->Print(pfout);
  }
  hist[i]->GetXaxis()->SetTitle(xaxis);
  hist[i]->GetYaxis()->SetTitle(yaxis);
  hist[i]->Draw("hist");
  c->Print(outname[i].c_str());
  }
  }
*/

void eff(int nplot,const char*tree, const char* var, string* finname,  const char *outname, string* cuttype, int bins, float bin1, float bin2, const char* xaxis, const char* yaxis, string* label)
{

  // setTDRStyle();
  //objects declaration 
  vector<TCut > cut; cut.clear();
  vector<TH1F*> hist; hist.clear();
  vector<TGraphAsymmErrors *>asyerr; asyerr.clear();
  TChain ch(tree);
  int fsize = sizeof(finname)/sizeof(finname[0]);
  for(int j = 0;j < fsize;j++)
    {
      ch.Add(finname[j].c_str());
      cout<<finname[j]<<endl;
    }


  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.0);
  pad1->Draw();
  pad1->cd();

  TLegend *l = new TLegend(0.15,0.15,0.37,0.35);
  l->SetFillColor(0);
  l->SetTextSize(0.04);
  Color_t color[]={kRed-7,kOrange+1,kSpring-2,kAzure+7,kBlue-7,kViolet+6,kMagenta-7,kGray};
  int marksty[]={20,21,22,23,29,33,34,39,47,48,49};
  //end declare


  for(int i = 0;i<nplot+1;i++)
    {
      char hname[10];
      sprintf(hname,"h%d",i);
      hist.push_back(new TH1F(hname,"",bins,bin1,bin2));
      char putvar[200];
      sprintf(putvar,"%s>>%s",var,hname);
      char cutvar[500];
      if(i>0)     sprintf(cutvar,"(%s&&mllg>115&&mllg<170)*puwei*genwei*mcwei*totSF",cuttype[i].c_str());
      else sprintf(cutvar,"(mllg>115&&mllg<170)*puwei*genwei*mcwei*totSF");
      TCut cut(cutvar);
      ch.Draw(putvar,cut);
    }
  
  cout<<(hist[0]->Integral(-1,-1)-hist[3]->Integral(-1,-1))/hist[0]->Integral(-1,-1)<<endl;
  //cout<<hist[4]->Integral(-1,-1)<<endl;
  for(int i = 0;i<nplot;i++) 
    {
      asyerr.push_back(new TGraphAsymmErrors());
      asyerr[i]->BayesDivide(hist[i+1],hist[0],"e0");
      asyerr[i]->SetMarkerColor(color[i]);
      asyerr[i]->SetLineColor(color[i]);
      asyerr[i]->SetMarkerStyle(marksty[i]);
      l->AddEntry(asyerr[i],label[i].c_str(),"pl");
      if(i==0)
	{
	  asyerr[i]->GetXaxis()->SetTitle(xaxis);
	  asyerr[i]->GetYaxis()->SetTitle(yaxis);
	  asyerr[i]->SetMaximum(1.01);
	  asyerr[i]->SetMinimum(0.9);
	  asyerr[i]->Draw("APL");
	}
      else asyerr[i]->Draw("PL");
      l->Draw();

    }

  extraText  = "Preliminary";
  lumi_13TeV = "";
  CMS_lumi(pad1, 4, 0);
  c->Print(outname);
}
void purity(const char* vername, const char* outfile,string* cat, const int ibin)
{
  setTDRStyle();
  TChain ggF("tZg");
  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV_ext1.root",vername));
  ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV_ext1.root",vername));
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
	  if(i==0)catcut = "((mllg>=115&&mllg<=170)&&HZgMVA>0.007&&ZgPTt>25&&ZgPTt<60)*puwei*mcwei*genwei*totSF";
	  if(i==1)catcut = "((mllg>=115&&mllg<=170)&&HZgMVA>0.007&&(ZgPTt<=25||ZgPTt>=55))*puwei*mcwei*genwei*totSF";
	  if(i==2)catcut = "((mllg>=115&&mllg<=170)&&HZgMVA<=0.007&&HZgMVA>-0.034&&ZgPTt>25&&ZgPTt<55)*puwei*mcwei*genwei*totSF";
	  if(i==3)catcut = "((mllg>=115&&mllg<=170)&&HZgMVA<=0.007&&HZgMVA>-0.034&&(ZgPTt<=25||ZgPTt>=55))*puwei*mcwei*genwei*totSF";
	  if(i==4)catcut = "((mllg>=115&&mllg<=170)&&cat==5&&HZgMVA>-0.034)*puwei*mcwei*genwei*totSF";
	  if(i==5)catcut = "((mllg>=115&&mllg<=170)&&cat>5&&cat<10&&HZgMVA>-0.034)*puwei*mcwei*genwei*totSF";
	  ggF.Draw(Form("mllg>>hggF[%d]",i),catcut);
	  VBF.Draw(Form("mllg>>hVBF[%d]",i),catcut);
	  ttH.Draw(Form("mllg>>httH[%d]",i),catcut);
	  ZH.Draw(Form("mllg>>hZH[%d]",i),catcut);
	  WH.Draw(Form("mllg>>hWH[%d]",i),catcut);
    
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
      all[0]->GetXaxis()->SetBinLabel(k, cat[k-1].c_str());
    }
  st->Draw("hbar");
  extraText  = "Preliminary";
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

