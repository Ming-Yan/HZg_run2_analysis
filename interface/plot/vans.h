#include "plugin/tdrstyle.C"
#include "plugin/CMS_lumi.C"
using namespace std;
void vans(/*TString cutbase,TString MVA,*/float mvacut,int type,int channel)
{ 
  TFile *f; TFile *f1;
if(type==0) 
{
	if(channel==0)
	{
		f = TFile::Open("../outfile/Data_kinMVA_nompho_ele_EG.root");
		f1 = TFile::Open("../outfile/Data_VBFMVA_dEta_dijet_ele_EG.root");
	}
	else 
	{
		f = TFile::Open("../outfile/Data_kinMVA_nompho_mu_Mu.root");
		f1 = TFile::Open("../outfile/Data_VBFMVA_dEta_dijet_mu_Mu.root");
	}
}
else
{
	if(channel==0)
	{
		f = TFile::Open("../outfile/mc_kinMVA_nompho_ele_HZg_VBF_125GeV_ext1.root");
		f1 = TFile::Open("../outfile/mc_VBFMVA_dEta_dijet_ele_HZg_VBF_125GeV_ext1.root");
	}
	else 
	{
		f = TFile::Open("../outfile/mc_kinMVA_nompho_mu_HZg_VBF_125GeV_ext1.root");
		f1 = TFile::Open("../outfile/mc_VBFMVA_dEta_dijet_mu_HZg_VBF_125GeV_ext1.root");
	}
}
  TTree *t = (TTree*)f->Get("tZg");
  TTree *t1 = (TTree*)f1->Get("tZg");
  vector<Long64_t >events,events1;
  Long64_t event_;
  Int_t cat;
  Float_t HZgVBF,mllg_;
  t->SetBranchAddress("event", &event_);
  t->SetBranchAddress("cat", &cat);
  t->SetBranchAddress("mllg", &mllg_);
  t1->SetBranchAddress("event", &event_);
  t1->SetBranchAddress("HZgVBF", &HZgVBF);
  t1->SetBranchAddress("mllg", &mllg_);

  for(Int_t i = 0;i<t->GetEntriesFast();i++)
    {
      t->GetEntry(i);
      if(cat!=5)continue;
      if(mllg_<127&&mllg_>123)events.push_back(event_);
    }
  for(Int_t i = 0;i<t1->GetEntriesFast();i++)
    {
      t1->GetEntry(i);
      if(HZgVBF<mvacut)continue;
      if(mllg_<127&&mllg_>123)events1.push_back(event_);
    }
  int overlap = 0;
  for(int a = 0; a<events.size();a++)
    {
      for(int b = 0;b<events1.size();b++)
	{
	  if(events1[b]==events[a])overlap++;
	}
    }
  cout<<overlap<<endl;
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.);
  pad1->Draw();
  pad1->cd();
  gStyle->SetOptStat(0);

  TEllipse *el3 = new TEllipse(0.32,0.5,.2,.4);
  el3->SetFillColor(2);
  el3->SetFillStyle(1001);
  el3->SetFillColorAlpha(kPink+6, 0.25);
  el3->SetFillStyle(3001);
  el3->SetLineWidth(0);
  el3->Draw("f");
  TEllipse *el4 = new TEllipse(0.58,0.5,.2,.4);
  el4->SetFillColor(2);
  el4->SetLineWidth(0);
  el4->SetFillStyle(3002);
  el4->SetFillColorAlpha(kAzure+1, 0.25);
  el4->Draw("fsame");
  TLatex latex;
  latex.SetTextSize(0.08);
  latex.SetTextAlign(13);  //align at top
  latex.DrawLatex(.25,.5,Form("%lu",events1.size()-overlap));//MVA
  latex.DrawLatex(.41,.5,Form("%d",overlap));//MVA-overlap
  latex.DrawLatex(.6,.5,Form("%lu",events.size()-overlap));//cutbase
  latex.DrawLatex(.5,.7,Form("MVA:%1.2f",mvacut));//cutbase
  TLatex latex1;
  latex1.SetTextSize(0.045);
  latex1.DrawLatex(.27,.85,"MVA");//MVA
  latex1.DrawLatex(.52,.85,"cut-based");//cut-base
if(type==0)cout<<"data / "<<endl;
else cout<<"MC / "<<endl;
if(channel==0)cout<<" ele / "<<endl;
else cout<<" mu / "<<endl;
cout<< "MVA only:"<<events1.size()-overlap<<" cutbased only: "<<events.size()-overlap<<" overlapped:"<<overlap<<endl;
extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad1, 4, 0);
  c->Print(Form("plot/%d_%d_overlap_narrower_mva%1.2f.png",type,channel,mvacut));
}
