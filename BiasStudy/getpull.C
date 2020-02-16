#include "tdrstyle.C"
#include "TStyle.h"
#include "TColor.h"

void Draw1DHist(TH1F *h, bool Pull, float lumi, const char* XaxisName, const char* outname)
{
  TCanvas *c = new TCanvas("c", " ", 800,800);
  c->cd();
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.08);
  gPad->SetLeftMargin(0.13);
  if(Pull == true)
    {
      gStyle->SetOptFit(11111);
      gStyle->SetOptStat(1100);
    }
  else
    gStyle->SetOptStat(0);
  h->GetXaxis()->SetTitle(XaxisName);
  h->GetYaxis()->SetTitle("Entries");
  h->GetYaxis()->SetTickSize(0.02);
  h->GetYaxis()->SetTitleSize(0.03);
  h->GetYaxis()->SetLabelSize(0.03);
  h->GetXaxis()->SetTickSize(0.02);
  h->GetXaxis()->SetTitleSize(0.03);
  h->GetXaxis()->SetLabelSize(0.03);
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetTitleOffset(1.4);
  h->Draw();
  if(Pull == true)
    {
      TF1 *fit = new TF1("fit","gaus",-5,5);
      fit->SetLineColor(46);
      fit->SetLineWidth(2);
      h->Fit("fit","RQ");
      fit->Draw("sames");
      gPad->Update();
      TPaveStats *st = (TPaveStats*)h->FindObject("stats");
      st->SetX1NDC(0.69);
      st->SetX2NDC(0.89);
      st->SetY1NDC(0.69);
      st->SetY2NDC(0.89);
    }
  TLatex* ltx = new TLatex();
  ltx->SetNDC();
  ltx->SetTextFont(61);
  ltx->SetTextSize(0.04);
  ltx->DrawLatex(0.19,0.85,"CMS");
  ltx->SetTextFont(52);
  ltx->SetTextSize(0.03);
  ltx->DrawLatex(0.19,0.81,"Preliminary");
  ltx->SetTextFont(42);
  ltx->SetTextSize(0.03);
  ltx->DrawLatex(0.67,0.935,Form("2016 %.2f fb^{-1} (13TeV)", lumi));
  c->SaveAs(outname);

  return;
}

void Draw2DHist(TH2F* h, bool Pull, float lumi, const char* XaxisName, const char* YaxisName, const char* DrawOpt, const char* outname)
{
  TCanvas* c = new TCanvas("c1","",800,800);
  c->cd();
  if(Pull == true) gStyle->SetPaintTextFormat("1.3f");
  gPad->SetRightMargin(0.13); 
  gPad->SetTopMargin(0.08);
  gPad->SetLeftMargin(0.13);
  gStyle->SetOptStat(0);
  //gStyle->SetPalette(70);
  h->GetYaxis()->SetTitle(YaxisName);
  h->GetXaxis()->SetTitle(XaxisName);
  h->GetYaxis()->SetTickSize(0.02);
  h->GetYaxis()->SetTitleSize(0.03);
  h->GetYaxis()->SetLabelSize(0.03);
  h->GetXaxis()->SetTitleOffset(1.4);
  h->GetYaxis()->SetTitleOffset(1.55);
  h->GetXaxis()->SetTickSize(0.02);
  h->GetXaxis()->SetTitleSize(0.03);
  h->GetXaxis()->SetLabelSize(0.03);
  h->GetZaxis()->SetLabelSize(0.025);
  h->SetContour(10000);
  h->Draw(DrawOpt);
  //if(Pull == true) h->GetZaxis()->SetRangeUser(0,2.0);
  TLatex* ltx = new TLatex();
  ltx->SetNDC();
  ltx->SetTextFont(61);
  ltx->SetTextSize(0.04);
  ltx->DrawLatex(0.13,0.935,"CMS");
  ltx->SetTextFont(52);
  ltx->SetTextSize(0.03);
  ltx->DrawLatex(0.22,0.935,"Preliminary");
  ltx->SetTextFont(42);
  ltx->SetTextSize(0.03);
  ltx->DrawLatex(0.59,0.935,Form("2016 %.2f fb^{-1} (13TeV)", lumi));
  c->SaveAs(outname);

  return;
}

void Fit_getPull(int rTrue, int catnum)
{
  setTDRStyle();

  // TEST!!
  gSystem->Exec(Form("rm -rf plots/mu%d/*",rTrue));

  TH2F *pull = new TH2F("pull", "pull values", 9, 0, 9, 9, 0, 9);
  const char* label[] = { "B 1st", "B 2nd", "B 3rd", "B 4th", "B 5th", "B 6th", "E 1st", "P 1st", "L 1st"};
  
  for(int i=0;i<9;i++)
    {
      if(gSystem->cd("plots") == false)
	gSystem->mkdir("plots");
      if(gSystem->cd(Form("plots/trueFunc%d",i)) == false)
	{
	  gSystem->cd("plots/");
	  gSystem->mkdir(Form("trueFunc%d", i));
	  gSystem->cd("../");
	}
      for(int j=0;j<9;j++)
	{
	  if(gSystem->cd(Form("plots/trueFunc%d/toys_sbfit_TruePdf%d_FitPdf%d",i,i,j)) == false)
	    {
	      gSystem->cd(Form("plots/trueFunc%d",i));
	      gSystem->mkdir(Form("toys_sbfit_TruePdf%d_FitPdf%d",i,j));
	      gSystem->cd("../../");
	    }
	  TH1F *hM_mu = new TH1F("hM_mu"," ",700,-400,1000);
	  TH1F *hM_muErr = new TH1F("hM_muErr", " ", 200 ,0, 200);
	  TH1F *hM_pull = new TH1F("hM_pull"," ",40,-5,5);
	  TH2F *hM_MuvsPull = new TH2F("hM_MuvsPull"," ",400,rTrue-200,rTrue+200,200,-5,5);
	    
	  for(int n=0;n<50;n++)
	    {
	      if(n==1) continue;
	      //if(i==1 && j==3 && n==22) continue;
	      TFile *f = new TFile(Form("results/mu%d/results__hJPgamma_13TeV_mu%d_123%d/mlfit_pdf%d_pdf%d_mu%d_123%d.root",rTrue,rTrue,n+1,i,j,rTrue,n+1));
	      if(f->IsZombie()) continue;
	      TTree *Tree  = (TTree*) f->Get("tree_fit_sb");
	      RooPlot *plot = (RooPlot*) f->Get(Form("cat%d_fit_s",catnum));
	      double mu, muErr;
	      Tree->SetBranchAddress("mu", &mu);
	      Tree->SetBranchAddress("muErr", &muErr);
	      for (Long64_t ev = 0; ev < Tree->GetEntriesFast(); ev++)
		{
		  Tree->GetEntry(ev);
		  
		  hM_pull->Fill((mu-rTrue)/muErr);
		  hM_MuvsPull->Fill(mu,(mu-rTrue)/muErr);
		  hM_mu->Fill(mu);
		  hM_muErr->Fill(muErr);
		}

	      TCanvas *c = new TCanvas("c"," ",800,800);
	      c->cd();
	      plot->Draw();
	      c->SaveAs(Form("plots/trueFunc%d/toys_sbfit_TruePdf%d_FitPdf%d/TruePdf%d_FitPdf%d_mu%d_sbfit_123%d_cat%d.pdf",i,i,j,i,j,rTrue,n+1,catnum));
	      f->Close();
	      f->Delete("*;*");
	    }

	  TF1 *fit = new TF1("fit","gaus",-5,5);
	  fit->SetLineColor(46);
	  fit->SetLineWidth(2);
	  hM_pull->Fit("fit","RQ");
	  //fit->SetLineColor(46);
	  //fit->SetLineWidth(2);

	  pull->SetBinContent(i + 1, j + 1, fit->GetParameter("Mean"));
	  pull->GetXaxis()->SetBinLabel(i+1, label[i]);
	  pull->GetYaxis()->SetBinLabel(j+1, label[j]);

	  // Draw1DHist(TH1F *h, bool Pull, float lumi, const char* XaxisName, const char* outname)
	  Draw1DHist(hM_pull, true, 35.86, Form("#mu-#mu_{true}/#sigma_{#mu}, #mu_{true}=%d",rTrue), Form("plots/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_Pull.pdf", i, i, j));
	  Draw1DHist(hM_mu, false, 35.86, "#mu", Form("plots/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_mu.pdf", i, i, j));
	  Draw1DHist(hM_muErr, false, 35.86, "#sigma_{#mu}", Form("plots/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_muErr.pdf", i, i, j));
	  // Draw2DHist(TH2F* h, bool Pull, int PaletteNum, float lumi, const char* XaxisName, const char* YaxisName, const char* outname)
	  Draw2DHist(hM_MuvsPull, false, 35.86, "#mu", "#mu-#mu_{true}/#sigma_{#mu}", "colz", Form("plots/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_muVsPull.pdf", i, i, j));
	}
    }
  Draw2DHist(pull, true, 35.86, "True func.", "Fit func.", "colztext", "plots/BiasTable.pdf");
  
  //TEST!!
  gSystem->cd("plots");
  gSystem->Exec(Form("mv trueFunc* mu%d", rTrue));
  gSystem->Exec(Form("mv BiasTable.pdf mu%d",rTrue));
  gSystem->cd("../");
}
