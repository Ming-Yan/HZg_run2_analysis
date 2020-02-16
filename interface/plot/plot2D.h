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

void plot2D(int nplot,const char*tree, const char* var ,string *histname, string* finname,  string *outname, const char* cuttype, int xrange, float xbin1, float xbin2, int yrange, float ybin1, float ybin2, const char* xaxis, const char* yaxis,int profile,)
  {
  setTDRStyle();
  extraText  = "Preliminary";
  lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(pad2, 4, 0);
  vector<TCut > cut; cut.clear();
  vector<TFile* > f; f.clear();
  vector<TTree*> t; t.clear();
  vector<TH2F*> hist; hist.clear();
  vector<TProfile* > prof; prof.clear();
  TCanvas *c = new TCanvas("c", "c", 800,600);
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 1.);
  pad2->SetBottomMargin(0.12);

  for (int i = 0 ; i <nplot ; i++)
  {
  c->cd();
  pad2->Draw();
  pad2->cd();
  const char* fin = finname[i].c_str();
  hist.push_back(new TH2F(histname[i].c_str(), " ",xrange, xbin1, xbin2,yrange, ybin1,ybin2));
  cut.push_back(cuttype);
  char putvar[100];
  sprintf(putvar,"%s>>%s",var,histname[i].c_str());
  t[i]->Draw(putvar,cut[i],"colz");
  if(profile!=-1) 
  {
  char profname[80];
  sprintf(profname,"%s_prof%d",histname[i].c_str(),profile);
  if(profile==0)prof.push_back(new TProfile(&profname," ",xrange,xbin1,xbin2));//profx
  if(profile==1)prof.push_back(new TProfile(&profname," ",yrange,ybin1,ybin2));//profy
  sprintf(putvar,"%s>>%s",var,profname);
  t[i]->Draw(putvar,cut[i]);
  prof[i]->GetXaxis()->SetTitle(xaxis);
  prof[i]->GetYaxis()->SetTitle(yaxis);
  char pfout[80];
  sprintf(pfout,"%s.png",profname);
  c->Print(pfout);
  }
  hist[i]->GetXaxis()->SetTitle(xaxis);
  hist[i]->GetYaxis()->SetTitle(yaxis);
  hist[i]->Draw("hist");
  c->Print(outname[i].c_str());
  }
  }


