void getZpt()
{

  TCanvas *c = new TCanvas("c","",800,600);
  c->cd();
  TPad *p1 = new TPad("p1","",0.0,0.3,1.0,1.0);
  p1->SetTopMargin(0.05);
  p1->SetBottomMargin(0.05);
  p1->Draw();
  p1->cd();
  TFile *f = TFile::Open("../outfile/Data_Rereco17_newMVAv2_mu_Mu.root");
  TTree *t = (TTree*)f->Get("tMVA");
  //TFile *f = TFile::Open("../outfile/GEN/MC_nocut_test16_Zg_aMCatNLO.root");
  //TTree *t = (TTree*)f->Get("tMC");
  TH1F*h = new TH1F("h","",20,0,200.);
  //t->Draw("mcmllgpt/mcmllg>>h");
  t->Draw("mllgptdmllg*mllg>>h");
  h->SetLineColor(kBlack);
  h->SetMarkerColor(kBlack);
  h->SetMarkerStyle(20);
  ///h->SetMaximum(6500);
  gStyle->SetOptStat(0);
  
  h->GetYaxis()->SetTitle("Events");
h->GetXaxis()->SetLabelSize(0);
  h->GetYaxis()->SetNdivisions(505);
  h->Draw("ep");

  TChain mc("tMVA");
 TChain mc1("tMVA");
  mc.Add("../outfile/mc_Rereco17_newMVAv2_mu_Zg_aMCatNLO.root");
  mc.Add("../outfile/mc_Rereco17_newMVAv2_mu_DYJetsToLL_m50_aMCatNLO.root");
  //mc.Add("/eos/user/m/milee/GENbkg/MC_nocut17_Zg_aMCatNLO.root");
  //mc.Add("../outfile/GEN/MC_nocut_test17_Zg_aMCatNLO.root");
  //mc1.Add("../outfile/GEN/MC_2017_DYJetsToLL_m50_aMCatNLO.root");
  float L1wei,mcwei,puwei,totSF,lldmllg,mllg,mllgptdmllg,genwei,mcmllpt,mcmllg,mcmllgpt,genmllgpt,mllgpt;
  int genFSR,isFSR,totmatch;
  /*mc.SetBranchAddress("isFSR", &isFSR);
  mc.SetBranchAddress("mcmllpt", &mcmllpt);
  mc.SetBranchAddress("mcmllgpt", &mcmllgpt);
  mc.SetBranchAddress("mcmllg", &mcmllg);*/
  //mc.SetBranchAddress("genFSR",   &genFSR);
  mc.SetBranchAddress("totmatch",   &totmatch);
  //mc.SetBranchAddress("mllgpt",&mllgpt);
  //mc.SetBranchAddress("genmllgpt",&genmllgpt);
 mc.SetBranchAddress("mllgptdmllg",&mllgptdmllg);
  mc.SetBranchAddress("lldmllg", &lldmllg);
  mc.SetBranchAddress("mllg", &mllg);
  mc.SetBranchAddress("L1wei",&L1wei);
  mc.SetBranchAddress("mcwei",&mcwei);
  mc.SetBranchAddress("genwei",&genwei);
  mc.SetBranchAddress("puwei",&puwei);
  mc.SetBranchAddress("totSF",&totSF);
  mc1.SetBranchAddress("mllgptdmllg",&mllgptdmllg);
  mc1.SetBranchAddress("lldmllg", &lldmllg);
  mc1.SetBranchAddress("mllg", &mllg);
  mc1.SetBranchAddress("L1wei",&L1wei);
  mc1.SetBranchAddress("mcwei",&mcwei);
  mc1.SetBranchAddress("genwei",&genwei);
  mc1.SetBranchAddress("puwei",&puwei);
  mc1.SetBranchAddress("totSF",&totSF);
  //mc1.SetBranchAddress("genFSR",   &genFSR);  
  //mc.SetBranchAddress("mcmllpt", &mcmllpt);
  //mc.SetBranchAddress("genwei",&genwei);
    TH1F*h1 = new TH1F("h1","",20,0,200.);
    TH1F*h2 = new TH1F("h2","",20,0,200.);
    //    TFile *f2 = TFile::Open("17_weiZgpt_ISR_Zg.root");
    TFile *f2 = TFile::Open("external/17_mu_weiZgpt_datasb_new.root");
    TH1F *hh = (TH1F*)f2->Get("hd");
    //TFile *f4 = TFile::Open("17_weiZgpt_FSR_Zg.root");
    //TH1F *hh1 = (TH1F*)f2->Get("hd");
    //TFile *f3 = TFile::Open("17_weiZpt_DY.root");
    //TH1F *hhh = (TH1F*)f2->Get("hd");
  for(int i = 0 ; i < mc.GetEntriesFast();i++)
    {
      mc.GetEntry(i);
      //cout<<mcmllgpt<<endl;
      //cout<<genFSR<<endl;
      //if(totmatch==1&&genFSR==0)h1->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei*hh1->GetBinContent(hh1->FindBin(genmllgpt)));//FSR
      //else if (genFSR==1&&totmatch==1) h1->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei*hh->GetBinContent(hh->FindBin(genmllgpt)));//ISR
      //else
      //cout<<hh->GetBinContent(hh->FindBin(mllgptdmllg*mllg))<<endl;
      h1->Fill(mllg*mllgptdmllg,totSF*genwei*mcwei*puwei*hh->GetBinContent(hh->FindBin(mllgptdmllg*mllg)));
      h2->Fill(mllg*mllgptdmllg,totSF*genwei*mcwei*puwei);
      //if(isFSR==0)h1->Fill(mcmllgpt/mcmllg,hh1->GetBinContent(hh1->FindBin(mcmllgpt)));
      //else h1->Fill(mcmllgpt/mcmllg,hh->GetBinContent(hh->FindBin(mcmllgpt)));
      //h2->Fill(mcmllgpt/mcmllg);
    }
  /*for(int i = 0 ; i < mc1.GetEntriesFast();i++)
    {
      mc1.GetEntry(i);
      //h1->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei*hhh->GetBinContent(hhh->FindBin(lldmllg)));
      //h1->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei);
      //h2->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei);
      //h1->Fill(mcmllpt);
      }*/
  
  h1->Scale(h->Integral()/h1->Integral());
  h2->Scale(h->Integral()/h2->Integral());
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h1->SetLineColor(kAzure+7);
  h2->SetLineColor(kRed-7);
  h1->Draw("histsame");
  h2->Draw("histsame");
  TLegend *l = new TLegend(.7,.75,.9,.95);
l->AddEntry(h,"data","ep");
 l->AddEntry(h1,"Reweighted","l");
 l->AddEntry(h2,"No Reweight","l");
 l->Draw();
  /*
  TFile *f2 = new TFile("17_weiZpt_Zg.root","recreate");
  f2->cd();
  TH1F *hd  = new TH1F("hd","",39,xbin);
  hd->Divide(h,h1);
  hd->Write();*/
  c->cd();
  TPad *p2 = new TPad("p2","",0.0,0.0,1.0,0.32);
  p2->SetTopMargin(0.01);
  p2->SetBottomMargin(0.23);
  p2->Draw();
  p2->cd();
  TH1F *h_1 = new TH1F("h_1","",20,0,200.);
  TH1F *h_2 = new TH1F("h_2","",20,0,200.);
  h_1 ->Divide(h,h1);
  h_2 ->Divide(h,h2);
  //h_1->GetXaxis()->SetTitle("{p_T}_{ll#gamma}/m_{ll#gamma}");
  h_1->GetXaxis()->SetTitle("pT_{ll#gamma}");
  h_1->GetYaxis()->SetTitle("Data/MC");
  h_1->GetYaxis()->SetNdivisions(505);
  h_1->GetYaxis()->SetTitleSize(0.1);
  h_1->GetXaxis()->SetTitleSize(0.1);
  h_1->SetMarkerColor(kAzure+7);
  h_2->SetMarkerColor(kRed-7);
  h_1->SetLineColor(kAzure+7);
  h_2->SetLineColor(kRed-7);
  h_1->GetXaxis()->SetLabelSize(0.1);
  h_1->GetYaxis()->SetLabelSize(0.1);
  h_1->SetMaximum(2.0);
  h_1->SetMinimum(0.1);
  h_1->Draw("ep");
  h_2->Draw("epsame");
  c->Print("zgptrewei_datasb.pdf");
}
