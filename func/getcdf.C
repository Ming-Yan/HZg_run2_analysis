#include "plugin/CMS_lumi.C"
#include "plugin/tdrstyle.C"
//#include "categorizing.h"
void getcdf(string fname,string mva,int period,int nbin)
{
  setTDRStyle();
  TChain sig("tZg");
  TChain bkg("tZg");
  TChain Zg("tZg");
  TChain DY("tZg");
  TChain EWK("tZg");
  TChain TT("tZg");
  TChain data("tZg");
  TChain VBF("tZg");
  VBF.Add(Form("../outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname.c_str()));
  VBF.Add(Form("../outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_mu_HZg_*F_125GeV.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_ele_HZg_*F_125GeV.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_mu_HZg_*H_125GeV.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_ele_HZg_*H_125GeV.root",fname.c_str()));
  EWK.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",fname.c_str()));
  EWK.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",fname.c_str()));   
  Zg.Add(Form("../outfile/mc_%s_ele_Zg_aMCatNLO.root",fname.c_str()));
  Zg.Add(Form("../outfile/mc_%s_mu_Zg_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_ele_Zg_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_Zg_aMCatNLO.root",fname.c_str()));
  DY.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  DY.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  TT.Add(Form("../outfile/mc_%s_mu_TT_aMCatNLO.root",fname.c_str()));
  TT.Add(Form("../outfile/mc_%s_ele_TT_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_TT_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_ele_TT_aMCatNLO.root",fname.c_str()));
  data.Add(Form("../outfile/Data_%s_ele_EG.root",fname.c_str()));
  data.Add(Form("../outfile/Data_%s_mu_Mu.root",fname.c_str()));
  TH1 *bdt = new TH1D("bdt","",2000,-1,1);
  string weight;
  if(period==2016)weight = "*L1wei";
  if(period==2017)weight = "*L1wei*ptwei";
  if(period==2018)weight = "*ptwei";
  if(mva=="HZgMVA")VBF.Draw(Form("%s>>bdt",mva.c_str()),Form("1*mcwei*genwei*puwei*totSF%s",weight.c_str()));
  else VBF.Draw(Form("HZgVBF>>bdt",mva.c_str()),Form("(HZgVBF!=-99)*mcwei*genwei*puwei*totSF%s",weight.c_str()));
  TH1 *cul_bdt = bdt->GetCumulative();
  vector<float> bin, bdtval;
  vector<float> wp10,wp20,wp30, wp40,wp50,wp60,wp70,wp80,wp90,wp95;wp10.clear();wp20.clear();wp30.clear(); wp40.clear();wp50.clear();wp60.clear();wp70.clear();wp80.clear();wp90.clear();wp95.clear();
  vector<float> bdt10,bdt20,bdt30,bdt40,bdt50,bdt60,bdt70,bdt80,bdt90,bdt95; bdt40.clear();bdt60.clear();bdt70.clear();bdt80.clear();bdt90.clear();bdt95.clear();bdt10.clear();bdt20.clear();bdt30.clear();bdt50.clear();

  //get the val from th1
  for(int i = 0 ; i<=2000;i++)
    {
      float bdtscore = -1. + 0.001*i;
      bin.push_back(bdtscore);
      bdtval.push_back(cul_bdt->GetBinContent(i)/bdt->Integral(-1,-1));
    } 	
  TGraph *cul = new TGraph(2000,&bin[0],&bdtval[0]);
  cul->Draw("apl");
  gPad->Print("cdf.png");
  // TFile *f = new TFile(Form("%s_cdf_%s.root",fname.c_str(),mva.c_str()),"recreate");
  // f->cd();
  // cul->Write();
  // f->Close();
  //generate plot
  Float_t HZgMVA,HZgVBF, totSF_,puwei_,mcwei_,genwei_,HZgMVA_transform,ptwei,L1wei;
  Int_t cat;
  Float_t gR9_,gSCEta_,lepSCEta_[2],lepEta_[2],mllgpt;
  TH1D *bdt_trans_sig = new TH1D("bdt_trans_sig","",nbin,0,1);

  sig.SetBranchAddress("HZgMVA", &HZgMVA);
  sig.SetBranchAddress("HZgVBF", &HZgVBF);
  sig.SetBranchAddress("phoSCEta", &gSCEta_);
  sig.SetBranchAddress("phoR9",    &gR9_);
  sig.SetBranchAddress("lepEta",   lepEta_);
  sig.SetBranchAddress("lepSCEta", lepSCEta_);
  sig.SetBranchAddress("mllgpt",   &mllgpt); 
  sig.SetBranchAddress("puwei",    &puwei_);
  sig.SetBranchAddress("genwei",   &genwei_);
  sig.SetBranchAddress("mcwei",    &mcwei_);
  sig.SetBranchAddress("L1wei",    &L1wei);
  sig.SetBranchAddress("ptwei",    &ptwei);
  sig.SetBranchAddress("totSF",    &totSF_);
  sig.SetBranchAddress("cat",      &cat);


  for(Long64_t ev = 0; ev < sig.GetEntriesFast(); ev++)
    {
      sig.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA") {
	HZgMVA_transform = cul->Eval(HZgMVA);
	bdt_trans_sig->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*L1wei*ptwei);
      }
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_sig->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}

      wp10.push_back(fabs(HZgMVA_transform-0.1));bdt10.push_back(HZgMVA);
      wp20.push_back(fabs(HZgMVA_transform-0.2));bdt20.push_back(HZgMVA);
      wp30.push_back(fabs(HZgMVA_transform-0.3));bdt30.push_back(HZgMVA);
      wp40.push_back(fabs(HZgMVA_transform-0.4));bdt40.push_back(HZgMVA);
      wp50.push_back(fabs(HZgMVA_transform-0.5));bdt50.push_back(HZgMVA);
      wp60.push_back(fabs(HZgMVA_transform-0.6));bdt60.push_back(HZgMVA);
      wp70.push_back(fabs(HZgMVA_transform-0.7));bdt70.push_back(HZgMVA);
      wp80.push_back(fabs(HZgMVA_transform-0.8));bdt80.push_back(HZgMVA);
      wp90.push_back(fabs(HZgMVA_transform-0.9));bdt90.push_back(HZgMVA);
      wp95.push_back(fabs(HZgMVA_transform-0.95));bdt95.push_back(HZgMVA);
    }
  int siz = (int) wp40.size();
  //  cout<<siz<<endl;
  int ind[siz];
  // TMath::Sort(siz, &wp10.front(), ind, kFALSE);
  // cout<<"wp10:"<< wp10[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  // TMath::Sort(siz, &wp20.front(), ind, kFALSE);
  // cout<<"wp20:"<< wp20[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  // TMath::Sort(siz, &wp30.front(), ind, kFALSE);
  // cout<<"wp30:"<< wp30[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  // TMath::Sort(siz, &wp40.front(), ind, kFALSE);
  // cout<<"wp40:"<< wp40[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  // TMath::Sort(siz, &wp60.front(), ind,kFALSE);
  // cout<<"wp50:"<< wp50[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  // TMath::Sort(siz, &wp50.front(), ind,kFALSE);
  // cout<<"wp60:"<< wp60[ind[0]]<<" "<<bdt60[ind[0]]<<endl;
  // TMath::Sort(siz, &wp60.front(), ind,kFALSE);
  // cout<<"wp70:"<< wp70[ind[0]]<<" "<<bdt70[ind[0]]<<endl;
  // TMath::Sort(siz, &wp80.front(), ind,kFALSE);
  // cout<<"wp80:"<< wp80[ind[0]]<<" "<<bdt80[ind[0]]<<endl;
  // TMath::Sort(siz, &wp90.front(), ind,kFALSE);
  // cout<<"wp90:"<< wp90[ind[0]]<<" "<<bdt90[ind[0]]<<endl;
  // TMath::Sort(siz, &wp95.front(), ind,kFALSE);
  // cout<<"wp95:"<< wp95[ind[0]]<<" "<<bdt95[ind[0]]<<endl;



  TH1D *bdt_trans_VBF = new TH1D("bdt_trans_VBF","",nbin,0,1);

  VBF.SetBranchAddress("HZgMVA", &HZgMVA);
  VBF.SetBranchAddress("HZgVBF", &HZgVBF);
  VBF.SetBranchAddress("phoSCEta", &gSCEta_);
  VBF.SetBranchAddress("phoR9",    &gR9_);
  VBF.SetBranchAddress("lepEta",   lepEta_);
  VBF.SetBranchAddress("lepSCEta", lepSCEta_);
  VBF.SetBranchAddress("mllgpt",   &mllgpt); 
  VBF.SetBranchAddress("puwei",    &puwei_);
  VBF.SetBranchAddress("genwei",   &genwei_);
  VBF.SetBranchAddress("mcwei",    &mcwei_);
  VBF.SetBranchAddress("L1wei",    &L1wei);
  VBF.SetBranchAddress("ptwei",    &ptwei);
  VBF.SetBranchAddress("totSF",    &totSF_);
  VBF.SetBranchAddress("cat",      &cat);
  cout<<"VBF"<<endl;
  bdt10.clear();bdt20.clear();bdt30.clear();bdt40.clear();bdt50.clear();bdt60.clear();bdt70.clear();bdt80.clear();bdt90.clear();
  wp10.clear();wp20.clear();wp30.clear();wp40.clear();wp50.clear();wp60.clear();wp70.clear();wp80.clear();wp90.clear();
  for(Long64_t ev = 0; ev < VBF.GetEntriesFast(); ev++)
    {
      VBF.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA") {
	HZgMVA_transform = cul->Eval(HZgMVA);
	bdt_trans_VBF->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*L1wei*ptwei);
      }
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_VBF->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}

      wp10.push_back(fabs(HZgMVA_transform-0.1));bdt10.push_back(HZgVBF);
      wp20.push_back(fabs(HZgMVA_transform-0.2));bdt20.push_back(HZgVBF);
      wp30.push_back(fabs(HZgMVA_transform-0.3));bdt30.push_back(HZgVBF);
      wp40.push_back(fabs(HZgMVA_transform-0.4));bdt40.push_back(HZgVBF);
      wp50.push_back(fabs(HZgMVA_transform-0.5));bdt50.push_back(HZgVBF);
      wp60.push_back(fabs(HZgMVA_transform-0.6));bdt60.push_back(HZgVBF);
      wp70.push_back(fabs(HZgMVA_transform-0.7));bdt70.push_back(HZgVBF);
      wp80.push_back(fabs(HZgMVA_transform-0.8));bdt80.push_back(HZgVBF);
      wp90.push_back(fabs(HZgMVA_transform-0.9));bdt90.push_back(HZgVBF);
      wp95.push_back(fabs(HZgMVA_transform-0.95));bdt95.push_back(HZgVBF);
    }
  cout<<bdt_trans_VBF->Integral()<<endl;
  siz = (int) wp40.size();
  //  cout<<siz<<endl;
  //int ind[siz];
  TMath::Sort(siz, &wp10.front(), ind, kFALSE);
  cout<<"wp10:"<< wp10[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  TMath::Sort(siz, &wp20.front(), ind, kFALSE);
  cout<<"wp20:"<< wp20[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  TMath::Sort(siz, &wp30.front(), ind, kFALSE);
  cout<<"wp30:"<< wp30[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  TMath::Sort(siz, &wp40.front(), ind, kFALSE);
  cout<<"wp40:"<< wp40[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  TMath::Sort(siz, &wp60.front(), ind,kFALSE);
  cout<<"wp50:"<< wp50[ind[0]]<<" "<<bdt40[ind[0]]<<endl;
  TMath::Sort(siz, &wp50.front(), ind,kFALSE);
  cout<<"wp60:"<< wp60[ind[0]]<<" "<<bdt60[ind[0]]<<endl;
  TMath::Sort(siz, &wp60.front(), ind,kFALSE);
  cout<<"wp70:"<< wp70[ind[0]]<<" "<<bdt70[ind[0]]<<endl;
  TMath::Sort(siz, &wp80.front(), ind,kFALSE);
  cout<<"wp80:"<< wp80[ind[0]]<<" "<<bdt80[ind[0]]<<endl;
  TMath::Sort(siz, &wp90.front(), ind,kFALSE);
  cout<<"wp90:"<< wp90[ind[0]]<<" "<<bdt90[ind[0]]<<endl;
  TMath::Sort(siz, &wp95.front(), ind,kFALSE);
  cout<<"wp95:"<< wp95[ind[0]]<<" "<<bdt95[ind[0]]<<endl;

  /*cout<<bdt_trans_sig->Integral(-1,-1)/(bdt_trans_sigcat1->Integral(-1,-1)+bdt_trans_sig->Integral(-1,-1)+bdt_trans_sigcat2->Integral(-1,-1)+bdt_trans_sigcat3->Integral(-1,-1)+bdt_trans_sigcat4->Integral(-1,-1)+bdt_trans_sigcat10->Integral(-1,-1))<<endl;;*/
  

 TH1D *bdt_trans_bkg = new TH1D("bdt_trans_bkg","",nbin,0,1);


  bkg.SetBranchAddress("HZgMVA", &HZgMVA);
  bkg.SetBranchAddress("HZgVBF", &HZgVBF);
  bkg.SetBranchAddress("puwei",    &puwei_);
  bkg.SetBranchAddress("genwei",   &genwei_);
  bkg.SetBranchAddress("mcwei",    &mcwei_);
  bkg.SetBranchAddress("totSF",    &totSF_);
  bkg.SetBranchAddress("L1wei",    &L1wei);
  bkg.SetBranchAddress("ptwei",    &ptwei);
  for(Long64_t ev = 0; ev < bkg.GetEntriesFast(); ev++)
    {
      bkg.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_bkg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_bkg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
    
    }

  TH1D *bdt_trans_TT = new TH1D("bdt_trans_TT","",nbin,0,1);
  TH1D *bdt_trans_DY = new TH1D("bdt_trans_DY","",nbin,0,1);
  TH1D *bdt_trans_Zg = new TH1D("bdt_trans_Zg","",nbin,0,1);
  TH1D *bdt_trans_EWK = new TH1D("bdt_trans_EWK","",nbin,0,1);

  TT.SetBranchAddress("HZgMVA", &HZgMVA);
  TT.SetBranchAddress("HZgVBF", &HZgVBF);
  TT.SetBranchAddress("puwei",    &puwei_);
  TT.SetBranchAddress("genwei",   &genwei_);
  TT.SetBranchAddress("mcwei",    &mcwei_);
  TT.SetBranchAddress("totSF",    &totSF_);
  TT.SetBranchAddress("L1wei",    &L1wei);
  TT.SetBranchAddress("ptwei",    &ptwei);
  for(Long64_t ev = 0; ev < TT.GetEntriesFast(); ev++)
    {
      TT.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_TT->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_TT->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
    
    }
  DY.SetBranchAddress("HZgMVA", &HZgMVA);
  DY.SetBranchAddress("HZgVBF", &HZgVBF);
  DY.SetBranchAddress("puwei",    &puwei_);
  DY.SetBranchAddress("genwei",   &genwei_);
  DY.SetBranchAddress("mcwei",    &mcwei_);
  DY.SetBranchAddress("totSF",    &totSF_);
  DY.SetBranchAddress("L1wei",    &L1wei);
  DY.SetBranchAddress("ptwei",    &ptwei);

  for(Long64_t ev = 0; ev < DY.GetEntriesFast(); ev++)
    {
      DY.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;

      if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_DY->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_DY->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
    }

  Zg.SetBranchAddress("HZgMVA", &HZgMVA);
  Zg.SetBranchAddress("HZgVBF", &HZgVBF);
  Zg.SetBranchAddress("puwei",    &puwei_);
  Zg.SetBranchAddress("genwei",   &genwei_);
  Zg.SetBranchAddress("mcwei",    &mcwei_);
  Zg.SetBranchAddress("totSF",    &totSF_);
  Zg.SetBranchAddress("L1wei",    &L1wei);
  Zg.SetBranchAddress("ptwei",    &ptwei);

  for(Long64_t ev = 0; ev < Zg.GetEntriesFast(); ev++)
    {
     
      Zg.GetEntry(ev); if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_Zg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_Zg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
    }
  EWK.SetBranchAddress("HZgMVA", &HZgMVA);
  EWK.SetBranchAddress("HZgVBF", &HZgVBF);
  EWK.SetBranchAddress("puwei",    &puwei_);
  EWK.SetBranchAddress("genwei",   &genwei_);
  EWK.SetBranchAddress("mcwei",    &mcwei_);
  EWK.SetBranchAddress("totSF",    &totSF_);
  EWK.SetBranchAddress("L1wei",    &L1wei);
  EWK.SetBranchAddress("ptwei",    &ptwei);

  for(Long64_t ev = 0; ev < EWK.GetEntriesFast(); ev++)
    {
      EWK.GetEntry(ev);
      if(period==2016)ptwei =1.;
      if(period==2018)L1wei= 1.;
      if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_EWK->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_EWK->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_*ptwei*L1wei);}
    
    }


  TH1D *bdt_trans_data = new TH1D("bdt_trans_data","",nbin,0,1);
  data.SetBranchAddress("HZgMVA", &HZgMVA);
  data.SetBranchAddress("HZgVBF", &HZgVBF);
  for(Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
      data.GetEntry(ev);
      if(mva=="HZgMVA"){ HZgMVA_transform = cul->Eval(HZgMVA);      bdt_trans_data->Fill(HZgMVA_transform);}
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);      bdt_trans_data->Fill(HZgMVA_transform);}

    }

  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.25, 1, 1.);
  pad1->SetBottomMargin(0.1);
  pad1->Draw();
  pad1->cd();
  THStack *bdt_trans = new THStack("bdt_trans","");
  bdt_trans_EWK->SetLineColor(kAzure+1);
  bdt_trans_EWK->SetFillColor(kAzure+1);
  bdt_trans_Zg->SetFillColor(TColor::GetColor("#16bac5"));
  bdt_trans_Zg->SetLineColor(TColor::GetColor("#16bac5"));
  bdt_trans_DY->SetFillColor(TColor::GetColor("#ffb400"));
  bdt_trans_DY->SetLineColor(TColor::GetColor("#ffb400"));
  bdt_trans_TT->SetLineColor(kOrange+7);
  bdt_trans_TT->SetFillColor(kOrange+7);
  bdt_trans->Add(bdt_trans_EWK);
  bdt_trans->Add(bdt_trans_TT);
  bdt_trans->Add(bdt_trans_Zg);
  bdt_trans->Add(bdt_trans_DY);

  bdt_trans_sig->SetLineWidth(2);
  bdt_trans_sig->SetLineColor(kBlue);
  bdt_trans_sig->Scale(1000.);
  bdt_trans_sig->SetFillColor(kBlue);
  bdt_trans_sig->SetFillStyle(3005);
  bdt_trans_VBF->SetLineWidth(2);
  bdt_trans_VBF->SetLineColor(kRed);
  bdt_trans_VBF->Scale(5000.);
  bdt_trans_VBF->SetFillColor(kRed);
  bdt_trans_VBF->SetFillStyle(3005);
  bdt_trans_data->SetLineColor(kBlack);
  bdt_trans_data->SetMarkerStyle(20);
  bdt_trans->SetMinimum(0.01);
  bdt_trans->SetMaximum(bdt_trans->GetMaximum()*1.5);
  // bdt_trans->GetXaxis()->SetTitleSize(0);
  // bdt_trans_bkg->GetXaxis()->SetTitle("transformed BDT");
  //bdt_trans_bkg->GetXaxis()->SetTitleOffset(0.7);
  //bdt_trans_bkg->GetXaxis()->SetTitleSize(0.38);
  // bdt_trans_bkg->GetYaxis()->SetTitle("Events");
  bdt_trans->Draw("hist");
  bdt_trans_sig->Draw("histsame");
  bdt_trans_VBF->Draw("histsame");
  bdt_trans_data->Draw("epsame");
  TLegend *l = new TLegend(.5,.75,.945,.93);
  l->SetTextSize(0.035);
  l->SetNColumns(2);
  l->AddEntry(bdt_trans_TT,"TTbar","f");
  l->AddEntry(bdt_trans_Zg,"SM Z#gamma","f");
  l->AddEntry(bdt_trans_DY,"Z+jets","f");
  l->AddEntry(bdt_trans_EWK,"EWK Z#gamma","f");
  l->AddEntry(bdt_trans_sig,"Signal","f");
  l->AddEntry(bdt_trans_VBF,"VBF","f");
  l->AddEntry(bdt_trans_data,"DATA","pl");
  l->Draw();
  c->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.25);
  pad2->SetTopMargin(0.01);
  pad2->Draw();
  pad2->cd();
  TH1F *signi = new TH1F("signi","",nbin,0.,1.);
  signi->Divide(bdt_trans_VBF,bdt_trans_bkg);
  signi->GetXaxis()->SetTitle("transformed BDT");
  signi->GetYaxis()->SetTitle("S/B");
  signi->Draw("ep");
  extraText  = "In progress";
  string lumi;
  if(period==2016) lumi = "35.9fb^{-1}";
  if(period==2017) lumi = "41.8fb^{-1}";
  if(period==2018) lumi = "52.5fb^{-1}";
  lumi_13TeV = lumi;
  CMS_lumi(pad1, 4, 0);
  c->Print(Form("plot/%s_%s_cdf_VBF.pdf",fname.c_str(),mva.c_str()));    	  
  c->Print(Form("plot/%s_%s_cdf_VBF.png",fname.c_str(),mva.c_str()));    	  
  gPad->SetLogy();
  bdt_trans->SetMaximum(bdt_trans->GetMaximum()*1.5);
  c->Print(Form("plot/%s_%s_cdf_log_VBF.pdf",fname.c_str(),mva.c_str()));    	  
  c->Print(Form("plot/%s_%s_cdf_log_VBF.png",fname.c_str(),mva.c_str()));    	  
}

