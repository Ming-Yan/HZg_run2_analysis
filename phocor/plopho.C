void plot(int p, string var, string EB, int n, float bin1, float bin2, string set)
{
  TFile *f = TFile::Open(Form("data_%d_photonTnP%s.root",p,set.c_str()));
  //TFile *fmc = TFile::Open(Form("MC_%d_photonTnP%s.root",p,set.c_str()));
  TTree *t = (TTree*)f->Get("tnp");
  //TTree *tmc = (TTree*)fmc->Get("tnp");
  TChain tmc("tnp");
  tmc.Add(Form("MC_%d_photonTnP%s.root",p,set.c_str()));  
  tmc.Add(Form("TT_%d_photonTnP%s.root",p,set.c_str()));
  float phores, phoR9, phoEta,phoPt,mcwei,genwei,puwei;
  tmc.SetBranchAddress("phores", &phores); 
  tmc.SetBranchAddress("phoPt", &phoPt); 
  tmc.SetBranchAddress("phoR9", &phoR9); 
  tmc.SetBranchAddress("phoEta", &phoEta); 
  tmc.SetBranchAddress("mcwei",  &mcwei);
  tmc.SetBranchAddress("genwei", &genwei);
  tmc.SetBranchAddress("puwei", &puwei);
  t->SetBranchAddress("phores", &phores); 
  t->SetBranchAddress("phoR9", &phoR9); 
  t->SetBranchAddress("phoEta", &phoEta); 
  t->SetBranchAddress("phoPt", &phoPt); 
  TFile *fw = TFile::Open(Form("../external/%d_phocorr.root",p));
  TGraph *w = (TGraph*)fw->Get(Form("%s_%s",var.c_str(),EB.c_str()));
  TGraph *w1;
  if(EB=="EB")w1= (TGraph*)fw->Get(Form("%s_%s2",var.c_str(),EB.c_str()));
  TH1F *cor = new TH1F("cor","",n,bin1,bin2);
  TH1F *data = new TH1F("data","",n,bin1,bin2);
  TH1F *mc = new TH1F("mc","",n,bin1,bin2);

  for(Long64_t ev = 0; ev < tmc.GetEntriesFast(); ev++)
    {
      tmc.GetEntry(ev);
      //puwei =1.;
      if(ev%2==1) continue;
      if(EB=="EB"&&fabs(phoEta)>1.4442) continue;
      if(EB=="EE"&&fabs(phoEta)<1.566)continue;
      if(var=="gres"){cor->Fill(w->Eval(phores));mc->Fill(phores);}
      //else {
	
	//if(fabs(phoEta)<1.&&EB=="EB")cor->Fill(w1->Eval(phoR9));

      else {cor->Fill(w->Eval(phoR9),mcwei*genwei*puwei);
      //else if(fabs(phoEta)>1.566&&EB=="EE")cor->Fill(w->Eval(phoR9));
	mc->Fill(phoR9,mcwei*genwei*puwei);}
      
    }  

  for(Long64_t ev = 0; ev < t->GetEntriesFast(); ev++)
    {
      t->GetEntry(ev);
      if(ev%2==1) continue;
      if(EB=="EB"&&fabs(phoEta)>1.4442) continue;
      if(EB=="EE"&&fabs(phoEta)<1.566)continue;
      if(var=="gres")data->Fill(phores);
      else data->Fill(phoR9);
  
    }  
  TCanvas *c = new TCanvas("c","",700,700);
  c->cd();
  TPad *p1 = new TPad("p1","",0,0.25,1.,1.);
  p1->SetBottomMargin(0.05);
  p1->Draw();
  p1->cd();
  gStyle->SetOptStat(0);
  data->SetLineColor(kBlack);
  data->SetMarkerColor(kBlack);
  data->SetMarkerStyle(20);
  mc->SetLineColor(kRed);
  cor->SetLineColor(kBlue-7);
  cor->SetFillColor(kBlue-7);
  mc->Scale(data->Integral(1,n)/mc->Integral(1,n));
  cor->Scale(data->Integral(1,n)/cor->Integral(1,n));
  cor->SetMaximum(max(mc->GetMaximum(),cor->GetMaximum()));
  mc->Sumw2();cor->Sumw2();
  float xpos1= (var=="gR9") ? .1 : .7;
  float xpos2= (var=="gR9") ? .3 : .9;
  TLegend *l = new TLegend(xpos1,.7,xpos2,.9);
  l->SetTextSize(0.04);
  l->AddEntry(data,"Data", "ep");
//  l->AddEntry(mc,"Uncorr MC", "l");
//  l->AddEntry(cor,"Corr MC","l");
  l->AddEntry(cor,"Z#rightarrow#mu#mu#gamma","f");
  // if(var=="gR9")mc->GetXaxis()->SetTitle("photon R9");
  // else mc->GetXaxis()->SetTitle("#sigma_{#gamma}/E_{#gamma}");
  cor->GetYaxis()->SetTitle("Events");
  cor->GetXaxis()->SetLabelSize(0);
  cout<<data->Chi2Test(mc,"UW CHI2/NDF")<<endl;
  cout<<data->Chi2Test(cor,"UW CHI2/NDF")<<endl;
  cor->Draw("hist");
  data->Draw("epsame");
//  mc->Draw("histsame");
  l->Draw();
  c->cd();
  TPad *p2 = new TPad("p2","p2", 0, 0.0, 1, 0.27);
  p2->SetTopMargin(0.02);
  p2->SetBottomMargin(0.3);
  p2->Draw();
  p2->cd();
  TH1F *d = new TH1F("d","",n,bin1,bin2);
  TH1F *dcor = new TH1F("dcor","",n,bin1,bin2);
  d->Divide(mc,data);
  dcor->Divide(cor,data);
  d->Sumw2();dcor->Sumw2();
  d->SetLineColor(kRed);
  d->SetMarkerColor(kRed);
  dcor->SetLineColor(kBlue);
  dcor->SetMarkerColor(kBlue);
  d->SetMarkerStyle(20);
  dcor->SetMarkerStyle(20);
  dcor->GetXaxis()->SetLabelSize(0.1);
  dcor->GetYaxis()->SetLabelSize(0.08);
  dcor->GetXaxis()->SetTitleSize(0.1);
  dcor->GetYaxis()->SetTitleSize(0.08);
  dcor->GetYaxis()->SetTitleOffset(0.5);
  dcor->GetXaxis()->SetTitleOffset(0.9);
  dcor->SetMaximum(1.5);
  dcor->SetMinimum(0.6);
  dcor->GetYaxis()->SetTitle("Data/MC");
  if(var=="gR9")dcor->GetXaxis()->SetTitle("photon R9");
  else dcor->GetXaxis()->SetTitle("#sigma_{#gamma}/E_{#gamma}");
  dcor-> Draw("ep");
//  d->Draw("epsame");
  TLine *line = new TLine(bin1,1.0,bin2,1.0);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->Draw();
  c->Print(Form("%s_%d_%s_Z%s_filled.pdf",var.c_str(),p,EB.c_str(),set.c_str()));

}
void plopho()
{
  
//  plot(16,"gR9","EE",50,0.8,1.0,"");
//  plot(16,"gR9","EB",50,0.8,1.0,"");
//  plot(18,"gR9","EE",40,0.8,1.05,"_mmg");
//  plot(18 ,"gR9","EB",40,0.8,1.05,"_mmg");
  plot(17,"gR9","EE",30,0.4,1.1,"_mmg");
  plot(17 ,"gR9","EB",30,0.4,1.1,"_mmg");

//  plot(17,"gR9","EE",50,0.8,1.0,"");
//  plot(17,"gR9","EB",50,0.8,1.0,"");

//  plot(16,"gR9","EB",40,0.8,1.0,"_mmg");
//  plot(16 ,"gR9","EE",40,0.8,1.0,"_mmg");
//  plot(18,"gR9","EE",50,0.8,1.05,"");
//  plot(18,"gR9","EB",50,0.8,1.05,"");
  //plot(18,"gR9","EE",20,0.8,1.05,"_mmg");
  //plot(18 ,"gR9","EB",20,0.8,1.05,"_mmg");
}
