#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"
using namespace std;
void limitplot2(){
  //things would changed  
  const int nf = 2;
  //string dirname [nf] = {"kinMVA_nompho_nocut","VBFMVA_v2_VBF2_0.05","VBFMVA_v2_pre_-0.01","VBFMVA_v2_woboost_comb125","VBFMVA_v2_refit_woboost_comb125","newflow_newmva_woboost_comb125"};
  //string dirname [nf] = {"VBFMVA_2017_VBF2_0.1","VBFMVA_2017_pre_0.01","VBFMVA_2017_wboost_comb125","VBFMVA_2017_refit"};
  //string dirname [nf] = {"VBFMVA_2017","VBFMVA_kinfit_nom","VBFMVA_kinfit_pre-0.03","VBFMVA_kinfit_woboost_comb0135","VBFMVA_kinfit_refit"};
  string dirname[nf] = {"VBFMVA_v2_woboost_comb125","VBFMVA_v2_env"};
  //string filename[nf] = {"kinMVA_nompho_ele_mu_12345678910","VBFMVA_v2_ele_mu_12345678910","VBFMVA_v2_ele_mu_12345678910","VBFMVA_v2_ele_mu_all","VBFMVA_v2_ele_mu_123456789","newflow_newmva_ele_mu_all"};
  //string filename[nf] = {"VBFMVA_2017_ele_mu_12345678910","VBFMVA_2017_ele_mu_12345678910","VBFMVA_2017_ele_mu_all","VBFMVA_2017_ele_mu_12345678910"};
  string filename[nf] = {"VBFMVA_v2_ele_mu_all","Test"};
  //string filename[nf] = {"-0.02" ,"-0.01",  "0." ,"0.01" ,"0.02" };
  //string filename[nf] = {"0.15","0.17", "0.11" ,"0.19" ,"0.2" ,"0.21" ,"0.22"};
  //string lname[nf] = {"nominal","VBF MVA","preselection","MVA inclusive cat.","kinematic fit+FSR"};
  //  string lname[nf] = {"nominal","VBF MVA", "preselection", "MVA categorization","kinematic refit","newflow"};
  //string lname[nf] = {"VBF MVA", "preselection", "MVA categorization","kinematic refit"};  
  string lname[nf] = {"nom","envelop"};
  setTDRStyle();

  vector <TGraph*> gr; gr.clear();

  TLegend *l = new TLegend(.3,0.7,0.95,.92);
  l->SetNColumns(2);
  l->SetShadowColor(0);
  l->SetTextSize(0.04);
  TCanvas *c = new TCanvas("c", "c", 800, 600);
  c->cd();


  string colors[]= {"#50514f","#f25f5c","#ffe066","#247ba0","#70c1b3","#9bc53d","#7c6fd2","#8b5100"};
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  for (int n = 0; n < nf; n++){
  vector<double> medlimit, upper1s, lower1s, upper2s, lower2s;
  medlimit.clear();  upper1s.clear();  lower1s.clear();  upper2s.clear();  lower2s.clear();
  vector<double> mass; mass.clear();
  for (int i = 0; i < 11; i++){
      Double_t masspt = 120 + i;
      TFile *f = new TFile(Form("DataCards/%s/higgsCombine%s.Asymptotic.mH%s.root",dirname[n].c_str(),filename[n].c_str(),name[i].Data()));    
      //ile *f = new TFile(Form("DataCards/newflow_newmva_pre_%s/higgsCombinenewflow_newmva_ele_mu_12345678910.Asymptotic.mH%s.root",filename[n].c_str(),name[i].Data()));    
      TTree *t = (TTree*)f->Get("limit");
      Double_t limit;	
      Float_t quantileExpected;
      t->SetBranchAddress("limit", &limit);
      t->SetBranchAddress("quantileExpected", &quantileExpected);   
      Long64_t nentries = t->GetEntries();
      Long64_t nbytes = 0;
      for (Long64_t j = 0; j < nentries; j++) {

	nbytes += t->GetEntry(j);
	if (j == 0) lower2s.push_back(limit);
	if (j == 1) lower1s.push_back(limit);
	if (j == 2) medlimit.push_back(limit);
	if (j == 3) upper1s.push_back(limit);
	if (j == 4) upper2s.push_back(limit);
	if(j==2&&masspt==125)cout << quantileExpected << " " << limit << " " << masspt << endl;
      }
      mass.push_back(masspt);
    }
    gr.push_back(new TGraph(mass.size(), &mass[0], &medlimit[0]));
  }
  for (int n = 0; n<nf ;n++)
    {
      gr[n]->SetLineWidth(4);
      gr[n]->SetLineStyle(9);
      gr[n]->SetLineColor(TColor::GetColor(colors[n].c_str()));
      l->AddEntry(gr[n],lname[n].c_str(),"l");
      //l->AddEntry(gr[n],filename[n].c_str(),"l");      
    if(n==0)
      {
	gr[0]->GetXaxis()->SetTitle("Mass[GeV/c^{2}]");
	gr[0]->GetYaxis()->SetTitle("95% CL UL #sigma/#sigma_{SM}");
	gr[0]->SetMaximum(10);
	gr[0]->SetMinimum(0);
	gr[0]->Draw("al");
      }
      else  gr[n]->Draw("lsame");
}
  l->Draw();
  gPad->Update();
  TLine *la1 = new TLine(gPad->GetUxmin(), 1.0, gPad->GetUxmax(), 1.0);
  la1->SetLineColor(kRed);
  la1->Draw();
  //extraText  = "Preliminary";
  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(c, 4, 0);
  c->Update();
  c->RedrawAxis();
  c->GetFrame()->Draw();
  
  //>Print("plot/2016_newMVA_pre.png");
  //c->Print("plot/2017_newMVA.pdf");
  c->Print("plot/2016_env_newMVA.png");   
}
