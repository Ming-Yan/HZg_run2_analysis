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

void eff(int nplot,const char*tree, const char* var, string* finname,  const char *outname, string* cuttype, int bins, float bin1, float bin2, const char* xaxis, const char* yaxis, string* label)
{

  // setTDRStyle();
  //objects declaration 
  vector<TCut > cut; cut.clear();
  vector<TH1F*> hist; hist.clear();
  vector<TGraphAsymmErrors *>asyerr; asyerr.clear();
  TChain ch(tree);
  int fsize = sizeof(finname)/sizeof(finname[0]);
  for(int j = 0;j < fsize;j++)
    {
      ch.Add(finname[j].c_str());
      cout<<finname[j]<<endl;
    }


  TCanvas *c = new TCanvas("c","c",800,600);
  c->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.0);
  pad1->Draw();
  pad1->cd();

  TLegend *l = new TLegend(0.15,0.15,0.37,0.35);
  l->SetFillColor(0);
  l->SetTextSize(0.04);
  Color_t color[]={kRed-7,kOrange+1,kSpring-2,kAzure+7,kBlue-7,kViolet+6,kMagenta-7,kGray};
  int marksty[]={20,21,22,23,29,33,34,39,47,48,49};
  //end declare


  for(int i = 0;i<nplot+1;i++)
    {
      char hname[10];
      sprintf(hname,"h%d",i);
      hist.push_back(new TH1F(hname,"",bins,bin1,bin2));
      char putvar[200];
      sprintf(putvar,"%s>>%s",var,hname);
      char cutvar[500];
      if(i>0)     sprintf(cutvar,"(%s&&mllg>115&&mllg<170)*puwei*genwei*mcwei*totSF",cuttype[i].c_str());
      else sprintf(cutvar,"(mllg>115&&mllg<170)*puwei*genwei*mcwei*totSF");
      TCut cut(cutvar);
      ch.Draw(putvar,cut);
    }
  
  cout<<(hist[0]->Integral(-1,-1)-hist[3]->Integral(-1,-1))/hist[0]->Integral(-1,-1)<<endl;
  //cout<<hist[4]->Integral(-1,-1)<<endl;
  for(int i = 0;i<nplot;i++) 
    {
      asyerr.push_back(new TGraphAsymmErrors());
      asyerr[i]->BayesDivide(hist[i+1],hist[0],"e0");
      asyerr[i]->SetMarkerColor(color[i]);
      asyerr[i]->SetLineColor(color[i]);
      asyerr[i]->SetMarkerStyle(marksty[i]);
      l->AddEntry(asyerr[i],label[i].c_str(),"pl");
      if(i==0)
	{
	  asyerr[i]->GetXaxis()->SetTitle(xaxis);
	  asyerr[i]->GetYaxis()->SetTitle(yaxis);
	  asyerr[i]->SetMaximum(1.01);
	  asyerr[i]->SetMinimum(0.9);
	  asyerr[i]->Draw("APL");
	}
      else asyerr[i]->Draw("PL");
      l->Draw();

    }

  extraText  = "Preliminary";
  lumi_13TeV = "";
  CMS_lumi(pad1, 4, 0);
  c->Print(outname);
}