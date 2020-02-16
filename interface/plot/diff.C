void diff()
{
  TFile *f = new TFile("/home/mingyan/output/mc/mc_mkinfit_mu_HZg_ggF_125GeV_ext1.root");
  TFile *f1 = new TFile("/home/mingyan/output/mc/mc_oldpho_kinfit_mu_HZg_ggF_125GeV_ext1.root");
  TTree *t = (TTree *)f->Get("tZg");
  TTree *t1 = (TTree *)f1->Get("tZg");
  Float_t mllg_,mllgpt,mllgeta,mllgphi,mll_,mllpt,mlleta,mllphi,lepPt_[2],lepEta_[2],lepPhi_[2];
  t->SetBranchAddress("mllg",     &mllg_);
  t1->SetBranchAddress("mllg",    &mllg_);
  t->SetBranchAddress("mllgpt",   &mllgpt);
  t1->SetBranchAddress("mllgpt",  &mllgpt);
  t->SetBranchAddress("mllgeta",  &mllgeta);
  t1->SetBranchAddress("mllgeta", &mllgeta);
  t->SetBranchAddress("mllgphi",  &mllgphi);
  t1->SetBranchAddress("mllgphi", &mllgphi);
  t->SetBranchAddress("mll",  &mll_);
  t1->SetBranchAddress("mll",  &mll_);
  t->SetBranchAddress("mllpt",   &mllpt);
  t1->SetBranchAddress("mllpt",  &mllpt);
  t->SetBranchAddress("mlleta",  &mlleta);
  t1->SetBranchAddress("mlleta", &mlleta);
  t->SetBranchAddress("mllphi",  &mllphi);
  t1->SetBranchAddress("mllphi", &mllphi);
  t->SetBranchAddress("lepPt", lepPt_);
  t1->SetBranchAddress("lepPt", lepPt_);
  t->SetBranchAddress("lepEta", lepEta_);
  t1->SetBranchAddress("lepEta", lepEta_);
  t->SetBranchAddress("lepPhi", lepPhi_);
  t1->SetBranchAddress("lepPhi", lepPhi_);
  int hrange[6] = {55,50,30,15,45,40};
  TCanvas *c = new TCanvas("c","",800,600);
  TH2F *hmllg = new TH2F("hmllg","",55,115,170,55,115,170);
  TH2F *hmll = new TH2F("hll","",50,50,150,50,50,150);
  TH2F *heta = new TH2F("heta","",30,-3,3,30,-3,3);
  TH2F *hphi = new TH2F("hphi","",15,-3,3,15,-3,3);
  TH2F *hmllpt = new TH2F("hmllpt","",45,0,450,45,0,450);
  TH2F *hleppt = new TH2F("hleppt","",40,0,200,40,0,200);
  //for(int k = 0;k <6;k++){
  for(int i=0;i< t->GetEntriesFast();i++)
    {
      t->GetEntry(i);
      float imllg = mllg_;
      float imll = mll_;
      float imllgeta = mllgeta;
      float imllgphi = mllgphi;
      float imllgpt = mllgphi;
      float ilepPt =lepPt_[0];
      for(int j = 0; j<t1->GetEntriesFast();j++)
	{
	  t1->GetEntry(j);
	  hmllg->Fill(imllg,mllg_);
	  hmll->Fill(imll,mll_);
	  heta->Fill(imllgeta,mllgeta);
	  hphi->Fill(imllgphi,mllgphi);
	  hmllpt->Fill(imllgpt,mllgpt);
	  hleppt->Fill(ilepPt,lepPt_[0]);
	}
    }
  //}
  c->cd();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(57);
  hmllg->GetXaxis()->SetTitle("old mllg");
  hmllg->GetYaxis()->SetTitle("new mllg");
  hmllg->Draw("colz");
  c->Print("plot/mu_mllg_2D.png");
  hmll->GetXaxis()->SetTitle("old mll");
  hmll->GetYaxis()->SetTitle("new mll");
  hmll->Draw("colz");
  c->Print("plot/mu_mll_2D.png");
  hleppt->GetXaxis()->SetTitle("old lep1pt");
  hleppt->GetYaxis()->SetTitle("new lep1pt");
  hleppt->Draw("colz");
  c->Print("plot/mu_lep1pt_2D.png");
  

  hmllpt->GetXaxis()->SetTitle("old mllgpt");
  hmllpt->GetYaxis()->SetTitle("new mllgpt");
  hmllpt->Draw("colz");
  c->Print("plot/mu_mllgpt_2D.png");
  

  heta->GetXaxis()->SetTitle("old mllgeta");
  heta->GetYaxis()->SetTitle("new mllgeta");
  heta->Draw("colz");
  c->Print("plot/mu_mllgeta_2D.png");

  hphi->GetXaxis()->SetTitle("old mllgphi");
  hphi->GetYaxis()->SetTitle("new mllgphi");
  hphi->Draw("colz");
  c->Print("plot/mu_mllgphi_2D.png");
}
