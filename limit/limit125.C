#include "../plugin/CMS_lumi.C"
#include "../plugin/tdrstyle.C"
void limit125()
{
  string cat[16] = {
    "ele_1","ele_2","ele_3","ele_4","ele_501","ele_502","ele_10",
    "mu_1","mu_2","mu_3","mu_4","mu_501","mu_502","mu_10",
    "ele_mu_6789","ele_mu_12345678910"};
  string catlabel[16] = {"ee#gamma cat1","ee#gamma cat2","ee#gamma cat3","ee#gamma_cat4","ee#gamma VBF enriched","ee#gamma ggF enriched","ee#gamma boosted tag","#mu#mu#gamma cat1","#mu#mu#gamma cat2","#mu#mu#gamma cat3","#mu#mu#gamma cat4","#mu#mu#gamma VBF enriched","#mu#mu#gamma ggF enriched","#mu#mu#gamma boosted tag","ee#gamma+#mu#mu#gamma lepton tag","Combined"};

  vector<double> medlimit, upper1s, lower1s, upper2s, lower2s, mass,space,zero;
  mass.clear();
  zero.clear();
  space.clear();
  medlimit.clear();
  upper1s.clear();
  lower1s.clear();
  upper2s.clear();
  lower2s.clear();
  for (int i = 0 ; i < 16 ; i++)
    {	
      TFile *f = TFile::Open(Form("DataCards/VBFMVA_phores_comb/higgsCombineVBFMVA_phores_%s.Asymptotic.mH125.root",cat[i].c_str()));
      TTree *t = (TTree*)f->Get("limit");
      Double_t limit;	
      Float_t quantileExpected;
      t->SetBranchAddress("limit", &limit);
      t->SetBranchAddress("quantileExpected", &quantileExpected);
      mass.push_back(i);
      space.push_back(0.1);
      zero.push_back(0.);
      double tmplow2s = 0., tmplow1s = 0., tmpup1s = 0. , tmpup2s = 0.,med= 0.;
      for (Long64_t j = 0; j < t->GetEntries(); j++)
	{
	  t->GetEntry(j);
	  if (j == 0) tmplow2s=limit;
	  if (j == 1) tmplow1s=limit;
	  if (j == 2) medlimit.push_back(limit);
	  if (j == 2) med = limit;
	  if (j == 3) tmpup1s=limit;
	  if (j == 4) tmpup2s=limit;
	}
      lower2s.push_back(med-tmplow2s);
      lower1s.push_back(med-tmplow1s);
      upper1s.push_back(tmpup1s-med);
      upper2s.push_back(tmpup2s-med);
    }
  // reverse(lower1s.begin(),lower1s.end());
  // reverse(lower2s.begin(),lower2s.end());
  // reverse(upper2s.begin(),upper2s.end());
  // reverse(upper1s.begin(),upper1s.end());
  // reverse(medlimit.begin(),medlimit.end());
  // reverse(mass.begin(),mass.end());
 
  TCanvas *c = new TCanvas("c", "c", 850, 800);
  c->cd();
  c->SetWindowSize(850+4,800+28);
  c->SetLeftMargin(0.25);
  c->SetRightMargin(0.04);
  c->Modified();
  c->Update();
  TGraphAsymmErrors *onesig = new TGraphAsymmErrors(mass.size(),&medlimit[0], &mass[0],&lower1s[0],&upper1s[0],&space[0],&space[0]);
  TGraphAsymmErrors *twosig = new TGraphAsymmErrors(mass.size(),&medlimit[0], &mass[0],&lower2s[0],&upper2s[0],&space[0],&space[0]);
  TGraphAsymmErrors *center = new TGraphAsymmErrors(mass.size(),&medlimit[0], &mass[0],&zero[0],&zero[0],&space[0],&space[0]);
  onesig->SetFillColor(kGreen+1);
  twosig->SetFillColor(kOrange);
  center->SetMarkerStyle(24);
  center->SetMarkerColor(kBlack);
  center->SetLineColor(kBlack);
  center->SetLineWidth(2);
  center->SetLineStyle(2);
  auto mg = new TMultiGraph();
  mg->Add(twosig,"2");
  mg->Add(onesig,"2");
  mg->Add(center,"P");
  mg->SetMinimum(-1);
  mg->SetMaximum(16);
  mg->Draw("AP");    
  mg->GetYaxis()->SetLabelSize(0);
  mg->GetXaxis()->SetTitle("95%CL UL #sigma/#sigma_{SM}");
  
  TLegend *l = new TLegend(0.78, 0.4, 0.96, 0.5);
  l->AddEntry(center, "Expected", "p");
  l->AddEntry(onesig, "#pm 1#sigma band", "f");
  l->AddEntry(twosig, "#pm 2#sigma band", "f");
  l->SetShadowColor(0);
  l->Draw();

  TLine *la1 = new TLine(1.0,gPad->GetUymin(),1.0,  gPad->GetUymax());
  la1->SetLineColor(kRed);
  la1->Draw(); 
    TLatex lat;
  for(int i =0 ; i< 16;i++)
  {
	  lat.SetTextSize(0.03);
	  lat.SetTextColor(kBlack);
	  if(i==15)lat.SetTextFont(72);
	  else lat.SetTextFont(42);
	  lat.SetTextAlign(32);
	  lat.DrawLatex(-3,.0+i*1.0, catlabel[i].c_str());
  }
  extraText  = "Preliminary";
  lumiTextSize  = 0.4;
  cmsTextSize   = 0.4;
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(c, 4, 0);
  c->Print("limit125.png");
   
 
}
