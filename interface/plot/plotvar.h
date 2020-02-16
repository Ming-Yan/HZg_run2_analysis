#include "/afs/cern.ch/work/m/milee/MYcode/plugin/tdrstyle.C"
#include "/afs/cern.ch/work/m/milee/MYcode/plugin/CMS_lumi.C"
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
  //gStyle->SetPalette(kCool);
  vector<TCut> cut; cut.clear();
  vector<TFile* > f; f.clear();
  vector<TTree*> t; t.clear();
  vector<TH1F*> hist; hist.clear();
  //TFile *f1 = new TFile(Form("%s.root",var.c_str()),"RECREATE");
  //f1->cd();
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
  //string color8[8] = {"#A90303","#FA7128","#DFDA39","#15CC04","#3898FE","#7FB800","#0D2C54"};
  //string color8[8] = {"#16bac5","#f6511d","#ffb400","#7fb800","#0d2c54","#D359B8","#f57a77","#dca11d"};
  string color8[8] = {"#EC5F67","#F99157","#FAC863","#99C794","#5FB3B3","#6699CC","#C594C5","#AB7967"};
  string color[] = {"#2f4858","#277884","#5ec29a","#0090ba","#0065b9","#005a26","#007552","#002f13","#88d191","#e4e986","#649c84"};
  TLegend *l = new TLegend(0.15,0.75,0.5,0.92);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
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

	}
      hist.push_back(new TH1F(Form("hist[%d]",i), " ",hrange, bin1, bin2));
      cut.push_back(cuttype[i].c_str());
      char putvar[100];
      sprintf(putvar,"%s>>hist[%d]",var[i].c_str(),i);
      if(chain ==false)t[i]->Draw(putvar,cut[i]);
      else ch.Draw(putvar,cut[i]);
      cout<<hist[i]->Integral(-1,-1)<<endl;
      if(shape==true) hist[i]->Scale(1./hist[i]->Integral(-1,-1));
      if(logxy == 0)gPad->SetLogx();
      else if(logxy == 1)gPad->SetLogy();
      //hist[i]->SetFillStyle(3003);
      //hist[i]->SetFillColor(TColor::GetColor(color8[i].c_str()));
      hist[i]->SetLineColor(TColor::GetColor(color8[i].c_str()));
      //hist[i]->SetMarkerColor(TColor::GetColor(color[i].c_str()));

      hist[i]->SetLineWidth(4);
      hist[i]->Sumw2();
      if(hist[i]->GetMaximum()>hmax) hmax = hist[i]->GetMaximum()*1.2;
      
      //hist[i]->Write();
    }

  hist[0]->SetMaximum(hmax);
  hist[0]->GetXaxis()->SetTitle(xaxis);
  hist[0]->GetYaxis()->SetTitle(yaxis);
  if(shape==false)hist[0]->Draw("hist");
  //if(shape==false)hist[0]->Draw("PLC PMC HIST");
  else hist[0]->DrawNormalized("hist");
  l->AddEntry(hist[0],histname[0].c_str(),"f");
  for(int i = 1;i<nplot;i++)
    {
      if(shape==false)hist[i]->Draw("HISTSAME");
      //if(shape==false)hist[i]->Draw("SAME PLC PMC HIST");
      else hist[i]->DrawNormalized("histsame");
      l->AddEntry(hist[i],histname[i].c_str(),"f");
    }
  l->SetFillColor(0);
  l->SetNColumns(2);
  l->SetTextSize(0.04);
  l->Draw();

 
   extraText  = "Preliminary";
  //  extraText  = "In progress";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad2, 4, 0);
  c->Print(outname);
}
