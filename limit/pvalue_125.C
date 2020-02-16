#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"
void pvalue_125()
{
  setTDRStyle();
  
  int lumi[7] = {150,300,1000,1500,2000,2500,3000};
  vector<double> limit125,luminosity,limit125cut;
  limit125.clear();luminosity.clear();limit125cut.clear();
  Double_t limit = -1;
  TFile *f1 = TFile::Open("DataCards/VBFMVA_phores_comb/higgsCombineMVAcomb.ProfileLikelihood.mH125.root");
  TFile *f11 = TFile::Open("DataCards/kinMVA_nompho_nocut/higgsCombineMVAcomb.ProfileLikelihood.mH125.root");
  TTree *t1 = (TTree*)f1->Get("limit");
  t1->SetBranchAddress("limit", &limit);
  TTree *t11 = (TTree*)f11->Get("limit");
  t11->SetBranchAddress("limit", &limit);
  for (Long64_t j = 0; j < t1->GetEntriesFast(); j++) 
    {
      t1->GetEntry(j);
      luminosity.push_back(35.9);
      limit125.push_back(limit);
      cout<<"35.9 /fb MVA: "<<limit<<endl;
    }
  for (Long64_t j = 0; j < t11->GetEntriesFast(); j++) 
    {
      t11->GetEntry(j);
      limit125cut.push_back(limit);
      cout<<"35.9 /fb cut: "<<limit<<endl;
    }
 
  for(int i = 0 ; i < 7; i++)
    {
      TFile *f = TFile::Open(Form("DataCards/VBFMVA_phores_%d/higgsCombineMVAcomb.ProfileLikelihood.mH125.root",lumi[i]));
      TTree *t = (TTree*)f->Get("limit");
      TFile *f2 = TFile::Open(Form("DataCards/kinMVA_nompho_%d/higgsCombineMVAcomb.ProfileLikelihood.mH125.root",lumi[i]));
      TTree *t2 = (TTree*)f2->Get("limit");
      t->SetBranchAddress("limit", &limit);
      t2->SetBranchAddress("limit", &limit);
      for (Long64_t j = 0; j < t->GetEntriesFast(); j++) 
	{
	  t->GetEntry(j);
	  limit125.push_back(limit);
	  luminosity.push_back(lumi[i]);
	  cout<<lumi[i]<<" /fb MVA: "<<limit<<endl;
	}
      for (Long64_t j = 0; j < t2->GetEntriesFast(); j++) 
	{
	  t2->GetEntry(j);
	  limit125cut.push_back(limit);
	  cout<<lumi[i]<<" /fb cut: "<<limit<<endl;
	}
    }
	TCanvas *c = new TCanvas("c", "c", 800, 600);
  c->cd();
  double  atlaslum[2] = {300,3000};
  double atlaspvalue[2] = {0.010724,4.8E-05};
  TGraph *pvalueatlas = new TGraph(2,atlaslum,atlaspvalue);
  TGraph *pvalue = new TGraph(8,&luminosity[0],&limit125[0]);
  TGraph *pvaluecut = new TGraph(8,&luminosity[0],&limit125cut[0]);
  pvalueatlas->SetMarkerStyle(22);
  pvalueatlas->SetMarkerColor(kBlue);
  pvalue->SetMarkerStyle(20);
  pvalue->SetMarkerColor(kRed);
  pvalue->SetLineColor(kRed);
  pvaluecut->SetMarkerStyle(20);
  pvaluecut->SetMarkerColor(kBlack);
  pvaluecut->SetLineColor(kBlack);
  pvalue->SetLineWidth(3);
  pvalue->SetMaximum(0.35);
  pvaluecut->SetLineWidth(3);
  pvalueatlas->SetLineWidth(3);
  pvalueatlas->SetLineColor(kBlue);
  pvalue->GetXaxis()->SetTitle("Luminoisty(fb^{-1})");
  pvalue->GetYaxis()->SetTitle("P-value");
  pvalue->SetTitle("");
  pvalue->Draw("alp");
  pvaluecut->Draw("lpsame");
  pvalueatlas->Draw("lpsame");
  TLine *sig1 = new TLine(35,0.158655,3000,0.158655);
  TLine *sig2 = new TLine(35,0.02275,3000,0.02275);
  TLine *sig3 = new TLine(35,0.00135,3000,0.00135);
  TLine *sig4 = new TLine(35,0.000032,3000,0.000032);
  TLine *sig5 = new TLine(35, 0.0000003,3000, 0.0000003);
    
  sig1->SetLineStyle(2);
  sig2->SetLineStyle(2);
  sig3->SetLineStyle(2);
  sig4->SetLineStyle(2);
  sig5->SetLineStyle(2);

  sig1->Draw();
  sig2->Draw();
  sig3->Draw();
  sig4->Draw();
  sig5->Draw();
  gPad->SetLogy();
  TLegend *l = new TLegend(.15,.15,.35,.35);
  l->AddEntry(pvaluecut,"cutbased CMS","pl");
  l->AddEntry(pvalue,"MVA study CMS","pl");
  l->AddEntry(pvalueatlas,"ATLAS run-I","pl");
  l->Draw();
  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(c, 4, 0);
  // c->Update();
  // c->RedrawAxis();
  // c->GetFrame()->Draw();
  c->Print("pvalue_proj.png");
  c->Print("pvalue_proj.pdf");
}
