#include "plugin/CMS_lumi.C"
#include "plugin/tdrstyle.C"
#include "categorizing.h"
void getcdf(string fname,string mva)
{
  setTDRStyle();
  TChain sig("tZg");
  TChain bkg("tZg");
  TChain data("tZg");
  
  //sig.Add(Form("../outfile/mc_%s_ele_HZg_*F_125GeV_ext1.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_mu_HZg_*F_125GeV_ext1.root",fname.c_str()));
  //sig.Add(Form("../outfile/mc_%s_ele_HZg_*H_125GeV.root",fname.c_str()));
  sig.Add(Form("../outfile/mc_%s_mu_HZg_*H_125GeV.root",fname.c_str()));
  //bkg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",fname.c_str()));
  //bkg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",fname.c_str()));    
  bkg.Add(Form("../outfile/mc_%s_ele_Zg_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_Zg_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_ele_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  bkg.Add(Form("../outfile/mc_%s_mu_DYJetsToLL_m50_aMCatNLO.root",fname.c_str()));
  data.Add(Form("../outfile/Data_%s_ele_EG.root",fname.c_str()));
  data.Add(Form("../outfile/Data_%s_mu_Mu.root",fname.c_str()));
  TH1 *bdt = new TH1D("bdt","",2000,-1,1);
  if(mva=="HZgMVA")sig.Draw(Form("%s>>bdt",mva.c_str()),"1*mcwei*genwei*puwei*totSF");
  else sig.Draw(Form("HZgVBF>>bdt",mva.c_str()),"(HZgVBF!=-99)*mcwei*genwei*puwei*totSF");
  TH1 *cul_bdt = bdt->GetCumulative();
  vector<float> bin, bdtval;
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
  TFile *f = new TFile(Form("%s_cdf_%s.root",fname.c_str(),mva.c_str()),"recreate");
  f->cd();
  cul->Write();
  f->Close();
  //generate plot
  Float_t HZgMVA,HZgVBF, totSF_,puwei_,mcwei_,genwei_,HZgMVA_transform;
  Int_t cat;
  Float_t gR9_,gSCEta_,lepSCEta_[2],lepEta_[2],mllgpt;
  TH1D *bdt_trans_sig = new TH1D("bdt_trans_sig","",20,0,1);
  TH1D *bdt_trans_sigcat1 = new TH1D("bdt_trans_sigcat1","",20,0,1);
  TH1D *bdt_trans_sigcat2 = new TH1D("bdt_trans_sigcat2","",20,0,1);
  TH1D *bdt_trans_sigcat3 = new TH1D("bdt_trans_sigcat3","",20,0,1);
  TH1D *bdt_trans_sigcat4 = new TH1D("bdt_trans_sigcat4","",20,0,1);
  TH1D *bdt_trans_sigcat501 = new TH1D("bdt_trans_sigcat501","",20,0,1);
  TH1D *bdt_trans_sigcat502 = new TH1D("bdt_trans_sigcat502","",20,0,1);
  TH1D *bdt_trans_sigcat6789 = new TH1D("bdt_trans_sigcat6789","",20,0,1);
  TH1D *bdt_trans_sigcat10 = new TH1D("bdt_trans_sigcat10","",20,0,1);
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
  sig.SetBranchAddress("totSF",    &totSF_);
  sig.SetBranchAddress("cat",      &cat);
  cout<<cul->Eval(-0.001)<<endl;

  for(Long64_t ev = 0; ev < sig.GetEntriesFast(); ev++)
    {
      sig.GetEntry(ev);
      if(mva=="HZgMVA") {
	HZgMVA_transform = cul->Eval(HZgMVA);
	
	int newcat = cat_limit(1,cat,gR9_,gSCEta_,lepEta_[0],lepEta_[1],mllgpt,HZgMVA,HZgVBF,-0.001,0.08);
	bdt_trans_sig->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==1)bdt_trans_sigcat1->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==2)bdt_trans_sigcat2->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==3)bdt_trans_sigcat3->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==4)bdt_trans_sigcat4->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==501)bdt_trans_sigcat501->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);	
	if(newcat==502)bdt_trans_sigcat502->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==6789)bdt_trans_sigcat6789->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);
	if(newcat==10)bdt_trans_sigcat10->Fill(HZgMVA,mcwei_*genwei_*puwei_*totSF_);	
      }
      else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_sig->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_);}
    }
  cout<<bdt_trans_sig->Integral(-1,-1)/(bdt_trans_sigcat1->Integral(-1,-1)+bdt_trans_sig->Integral(-1,-1)+bdt_trans_sigcat2->Integral(-1,-1)+bdt_trans_sigcat3->Integral(-1,-1)+bdt_trans_sigcat4->Integral(-1,-1)+bdt_trans_sigcat10->Integral(-1,-1))<<endl;;
  TH1D *bdt_trans_bkg = new TH1D("bdt_trans_bkg","",20,0,1);
  bkg.SetBranchAddress("HZgMVA", &HZgMVA);
  bkg.SetBranchAddress("HZgVBF", &HZgVBF);
  bkg.SetBranchAddress("puwei",    &puwei_);
  bkg.SetBranchAddress("genwei",   &genwei_);
  bkg.SetBranchAddress("mcwei",    &mcwei_);
  bkg.SetBranchAddress("totSF",    &totSF_);
  for(Long64_t ev = 0; ev < bkg.GetEntriesFast(); ev++)
    {
      bkg.GetEntry(ev);
	  if(mva=="HZgMVA"){HZgMVA_transform = cul->Eval(HZgMVA);bdt_trans_bkg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_);}
	  else if(mva=="HZgVBF"&&HZgVBF!=-99){HZgMVA_transform = cul->Eval(HZgVBF);bdt_trans_bkg->Fill(HZgMVA_transform,mcwei_*genwei_*puwei_*totSF_);}
	  
    }
 TH1D *bdt_trans_data = new TH1D("bdt_trans_data","",20,0,1);
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

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.);
  pad1->SetBottomMargin(0.15);
  pad1->Draw();
  pad1->cd();
  //gPad->SetLogy();
  bdt_trans_bkg->GetXaxis()->SetTitle("BDT");
  //bdt_trans_bkg->GetXaxis()->SetTitleOffset(0.7);
  //bdt_trans_bkg->GetXaxis()->SetTitleSize(0.38);
  bdt_trans_bkg->GetYaxis()->SetTitle("Weighted events");
  bdt_trans_sig->SetLineWidth(2);
  bdt_trans_sigcat1->SetLineWidth(3);
  bdt_trans_sigcat2->SetLineWidth(3);
  bdt_trans_sigcat3->SetLineWidth(3);
  bdt_trans_sigcat4->SetLineWidth(3);
  bdt_trans_sigcat501->SetLineWidth(3);
  bdt_trans_sigcat502->SetLineWidth(3);
  bdt_trans_sigcat6789->SetLineWidth(3);
  bdt_trans_sigcat10->SetLineWidth(3);
  bdt_trans_bkg->SetLineWidth(2);
  bdt_trans_sig->SetLineColor(kBlue);
  bdt_trans_sigcat1->SetLineColor(kRed-4);  
  bdt_trans_sigcat2->SetLineColor(kYellow+1);
  bdt_trans_sigcat3->SetLineColor(kOrange+1);
  bdt_trans_sigcat4->SetLineColor(kSpring-1);
  bdt_trans_sigcat501->SetLineColor(kCyan+1);
  bdt_trans_sigcat502->SetLineColor(kBlue-4);
  bdt_trans_sigcat6789->SetLineColor(kMagenta+7);
  bdt_trans_sigcat10->SetLineColor(kAzure+7);
  bdt_trans_bkg->SetLineColor(kRed);
  //bdt_trans_sig->SetFillColor(kBlue);
  //bdt_trans_bkg->SetFillColor(kRed);
  //bdt_trans_sig->SetFillStyle(3490);
  //bdt_trans_bkg->SetFillStyle(3490);
  bdt_trans_data->SetLineColor(kBlack);
  bdt_trans_data->SetMarkerStyle(20);
  bdt_trans_bkg->SetMinimum(0);
  bdt_trans_bkg->SetMaximum(0.25);
  bdt_trans_bkg->Draw("hist");
  bdt_trans_sig->Draw("histsame");
  bdt_trans_sigcat1->DrawNormalized("histsame");
  bdt_trans_sigcat2->DrawNormalized("histsame");
  bdt_trans_sigcat3->DrawNormalized("histsame");
  bdt_trans_sigcat4->DrawNormalized("histsame");
  bdt_trans_sigcat501->DrawNormalized("histsame");
  bdt_trans_sigcat502->DrawNormalized("histsame");
  bdt_trans_sigcat6789->DrawNormalized("histsame");
  bdt_trans_sigcat10->DrawNormalized("histsame");
  bdt_trans_data->Draw("epsame");
  TLegend *l = new TLegend(.5,.75,.945,.93);
  l->SetTextSize(0.035);
  l->SetNColumns(2);
  //l->AddEntry(bdt_trans_bkg,"Background","f");
  //l->AddEntry(bdt_trans_sig,"Signal","f");
  l->AddEntry(bdt_trans_sigcat1,"cat1","f");
  l->AddEntry(bdt_trans_sigcat2,"cat2","f");
  l->AddEntry(bdt_trans_sigcat3,"cat3","f");
  l->AddEntry(bdt_trans_sigcat4,"cat4","f");
  l->AddEntry(bdt_trans_sigcat501,"VBF enriched","f");
  l->AddEntry(bdt_trans_sigcat502,"ggH enriched","f");
  l->AddEntry(bdt_trans_sigcat6789,"lepton tag","f");
  l->AddEntry(bdt_trans_sigcat10,"boosted","f");
  //l->AddEntry(bdt_trans_data,"DATA","pl");
  l->Draw();
  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad1, 4, 0);
  c->Print(Form("plot/%s_%s_muncat.pdf",fname.c_str(),mva.c_str()));    	  
}
