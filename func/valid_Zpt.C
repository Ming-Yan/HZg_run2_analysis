void Zpt()
{
  //TFile *f = TFile::Open("../outfile/GEN/MC_nocut_test16_Zg_aMCatNLO.root");
  //TFile *f = TFile::Open("/eos/user/m/milee/GENbkg//MC_nocut16_DYJetsToLL_m50_aMCatNLO.root");
  //TFile *f = TFile::Open("../outfile/Data_Rereco17_HLT_ele_EG.root");
  TFile *f = TFile::Open("../outfile/Data_Rereco18_newZg_ele_EG.root");
  TTree *t = (TTree*)f->Get("tMVA");
//TFile *f = TFile::Open("../outfile/Data_Rereco17_HLT_
//  TTree *t = (TTree*)f->Get("tMC");
  //  TH1F*h = new TH1F("h","",40,0,2);
  //t->Draw("mllgptdmllg>>h");
  float xbin[10] = {0,5,10,15,25,30,40,50,100,500};
  TH1F *h = new TH1F("h","",9,xbin);
  TH1F *h1 = new TH1F("h1","",9,xbin);
  int isFSR;
  //float lldmllg, mllg,mcmllpt,mcwei,mcmll,mcmllg,mcmllgpt;
 float mllg,mllgptdmllg;
 /*t->SetBranchAddress("mcmllpt", &mcmllpt);
 t->SetBranchAddress("mcmllgpt", &mcmllgpt);
 t->SetBranchAddress("mcmll", &mcmll);
 t->SetBranchAddress("mcmllg", &mcmllg);
 t->SetBranchAddress("isFSR", &isFSR);*/
 //t->SetBranchAddress("genwei",&genwei);
  t->SetBranchAddress("mllg", &mllg);
  t->SetBranchAddress("mllgptdmllg", &mllgptdmllg);
 for(int i = 0 ; i < t->GetEntriesFast();i++)
    {
      t->GetEntry(i);
      if(mllg>120&&mllg<130) continue;
      if(mllg<115)continue;
      if(mllg>135)continue;
      h->Fill(mllgptdmllg*mllg);
//if(mcmll+mcmllg<175)continue;
      //if(isFSR==0)h->Fill(mcmllgpt);

    }
  h->SetLineColor(kRed);
  h->Draw("hist"); 
  TChain mc("tMVA");
  //mc.Add("/eos/user/m/milee/GENbkg//MC_nocut17_DYJetsToLL_m50_aMCatNLO.root");
  //mc.Add("../outfile/GEN/MC_nocut_test17_Zg_aMCatNLO.root");
  mc.Add("../outfile/mc_Rereco18_newZg_ele_Zg_aMCatNLO.root");
  mc.Add("../outfile/mc_Rereco18_HLT_ele_DYJetsToLL_m50_aMCatNLO.root");  
  //mc.Print();
  float  genwei,L1wei,mcwei,puwei,totSF,lldmllg;//,mllg,mllgptdmllg;
  mc.SetBranchAddress("mllgptdmllg",&mllgptdmllg);
  mc.SetBranchAddress("lldmllg", &lldmllg);
  mc.SetBranchAddress("mllg", &mllg);
  mc.SetBranchAddress("L1wei",&L1wei);
  mc.SetBranchAddress("mcwei",&mcwei);
  mc.SetBranchAddress("genwei",&genwei);
  mc.SetBranchAddress("puwei",&puwei);
  mc.SetBranchAddress("totSF",&totSF);/*
  mc.SetBranchAddress("mcmllpt", &mcmllpt);
  mc.SetBranchAddress("mcmllgpt", &mcmllgpt);
  mc.SetBranchAddress("mcmll", &mcmll);
  mc.SetBranchAddress("mcmllg", &mcmllg);
  mc.SetBranchAddress("isFSR", &isFSR);*/

  //mc.SetBranchAddress("genwei",&genwei);
  //  TH1F*h1 = new TH1F("h1","",40,0,2);
  //TFile *f2 = TFile::Open("Zptwei17.root");
  // TH1F *hh = (TH1F*)f2->Get("hd");
  for(int i = 0 ; i < mc.GetEntriesFast();i++)
    {
      mc.GetEntry(i);
      //if(mcmll+mcmllg<175)continue;
      
      //hd->GetBinContent()
      //he_dZ->GetBinContent(he_dZ->FindBin(1.2,1.2));
      //h1->Fill(mllgptdmllg,totSF*genwei*mcwei*puwei*hh->GetBinContent(hh->FindBin(lldmllg*mllg)));
      //if(isFSR==0)h1->Fill(mcmllgpt);
      if(mllg>120&&mllg<130) continue;
      if(mllg<115)continue;
      if(mllg>135)continue;
      h1->Fill(mllgptdmllg*mllg,totSF*mcwei*genwei*puwei);
      
    }
  h1->Scale(h->Integral()/h1->Integral());
  h1->Draw("histsame");

  TFile *f2 = new TFile("18_ele_weiZgpt_datasb_new.root","recreate");
  f2->cd();
  TH1F *hd  = new TH1F("hd","",9,xbin);
  hd->Divide(h,h1);
  hd->Write();
}
