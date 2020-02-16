#include "plugin/tdrstyle.C"
#include "plugin/CMS_lumi.C"
#include <iostream>
#include <TH1F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TTree.h>
#include <TPad.h>
#include <TFile.h>
#include <TSystem.h>
#include <TCut.h>
void plotvar(int nplot, const char *tree, string* var ,string *histname, string* finname,  const char *outname, string* cuttype, int hrange, float bin1, float bin2, const char* xaxis, const char* yaxis, bool shape,bool chain,int logxy)
{
  setTDRStyle();
  vector<TCut> cut; cut.clear();
  vector<TFile* > f; f.clear();
  vector<TTree*> t; t.clear();
  vector<TTree*> t2; t2.clear();
  vector<TH1F*> hist; hist.clear();
  TChain ch(tree);
  TCanvas *c = new TCanvas("c", "c", 800,600);
  c->cd();

  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 1.);
  pad2->SetBottomMargin(0.12);
  pad2->Draw();
  pad2->cd();
  string color2[2] = {"#0c3d67","#dca11d"};
  string color3[3] = {"#39a9df","#f57a77","#28b386"};
  string color5[5] = {"#16bac5","#f6511d","#ffb400","#7fb800","#0d2c54"};
  string color8[8] = {"#A90303","#FA7128","#DFDA39","#15CC04","#3898FE","#000799","#570281"};
	int cat =0;
	Float_t lepEta_[2], lepPt_[2], HZgVBF;
	Float_t gEta_,gMVA_,gR9_,lepEta1, lepEta2,cosTheta, costheta,Phi,mllgptdmllg,dRlg_,mllg_,phores, HZgMVA;
	
  TLegend *l = new TLegend(0.45,0.75,0.955,0.92);

  int fsize = sizeof(finname)/sizeof(finname[0]);
  float hmax = 0;
  if(chain ==true)
    {
      for(int i = 0 ; i < fsize;i++)
	{
	  ch.Add(finname[i].c_str());
	}
    }
  for (int i = 0 ; i <nplot ; i++)
    {
      if(chain == false)
	{
	  const char* fin = finname[i].c_str(); 
	  f.push_back(TFile::Open(fin));
	  t.push_back((TTree*)f[i]->Get(tree));
	  t2.push_back((TTree*)f[i]->Get("tZg"));
	  t2[i]->SetBranchAddress("lepEta", lepEta_);
	  t2[i]->SetBranchAddress("lepPt", lepPt_);
	  t2[i]->SetBranchAddress("HZgVBF", &HZgVBF); 
	  t2[i]->SetBranchAddress("cat", &cat);
	  t[i]->SetBranchAddress("lepEta1", &lepEta1);
	  t[i]->SetBranchAddress("lepEta2", &lepEta2);
	  t[i]->SetBranchAddress("phoEta", &gEta_);
	  t[i]->SetBranchAddress("phoMVA", &gMVA_);
	  t[i]->SetBranchAddress("phoR9", &gR9_);
	  t[i]->SetBranchAddress("cosTheta", &cosTheta);
	  t[i]->SetBranchAddress("costheta", &costheta);
	  t[i]->SetBranchAddress("Phi", &Phi);
	  t[i]->SetBranchAddress("mllgptdmllg", &mllgptdmllg);
	  t[i]->SetBranchAddress("dRlg", &dRlg_);
	  t[i]->SetBranchAddress("phores", &phores);
	  
	}
      hist.push_back(new TH1F(Form("hist[%d]",i), " ",10, 0., 1.0));
      cut.push_back(cuttype[i].c_str());
      char putvar[100];
      sprintf(putvar,"%s>>hist[%d]",var[i].c_str(),i);
      if(chain ==false){
		  vector<int> vec_cat;vec_cat.clear();
		 vector<float> eta1, eta2, pt1, pt2, vbf; eta1.clear();eta2.clear(); pt1.clear();pt2.clear(); vbf.clear();
		  for(Long64_t ev = 0 ; ev<t2[i]->GetEntriesFast() ; ev++)
		  {
			  t2[i]->GetEntry(ev);
			  vec_cat.push_back(cat);
			  eta1.push_back(lepEta_[0]);
			  pt1.push_back(lepPt_[0]);
			  eta2.push_back(lepEta_[1]);
			  pt2.push_back(lepPt_[1]);
			  vbf.push_back(HZgVBF);
		  }
		  for(Long64_t ev1 = 0; ev1 < t[i]->GetEntriesFast() ; ev1++)
		  {
			  t[i]->GetEntry(ev1);
			  if (vec_cat[ev1]>5&&vec_cat[ev1]<10) continue;
			  if (fabs(eta1[ev1])>1.0||fabs(eta2[ev1])>1.0) continue;
			  if (pt1[ev1]<25) continue;
			  if (pt2[ev1]<15) continue;
			  if (vbf[ev1]>-0.01) continue;
			  hist[i]->Fill(mllgptdmllg);
		  }
		  // t[i]->Draw(putvar,cut[i]);
	  }
      else ch.Draw(putvar,cut[i]);
      cout<<hist[i]->Integral(-1,-1)<<endl;
      if(shape==true) hist[i]->Scale(1./hist[i]->Integral(-1,-1));
      if(logxy == 0)gPad->SetLogx();
      else if(logxy == 1)gPad->SetLogy();
      //hist[i]->SetFillStyle(3003);
      //hist[i]->SetFillColor(TColor::GetColor(color8[i].c_str()));
      

	  hist[i]->SetLineColor(TColor::GetColor(color5[i].c_str()));
	  hist[i]->SetMarkerColor(TColor::GetColor(color5[i].c_str()));

      hist[i]->SetLineWidth(4);
      hist[i]->Sumw2();
      if(hist[i]->GetMaximum()>hmax) hmax = hist[i]->GetMaximum()*1.5;
      l->AddEntry(hist[i],histname[i].c_str(),"f");
    }

  hist[0]->SetMaximum(hmax);
  hist[0]->GetXaxis()->SetTitle(xaxis);
  hist[0]->GetYaxis()->SetTitle(yaxis);
  //if(shape==false)
    hist[0]->Draw("hist");
    //  else hist[0]->DrawNormalized("hist");
  
  for(int i = 1;i<nplot;i++)
    {
      //if(shape==false)
	hist[i]->Draw("histsame");
	//else hist[i]->DrawNormalized("histsame");
    }
  l->SetFillColor(0);
  l->SetNColumns(2);
  l->SetTextSize(0.04);
  l->Draw();

 
  //  extraText  = "Preliminary";
  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad2, 4, 0);
  c->Print("plot/mllgptdmllgbkgsig.png");
}
