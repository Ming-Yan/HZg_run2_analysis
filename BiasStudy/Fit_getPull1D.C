#include "../MYcode/plugin/tdrstyle.C"

#include "TStyle.h"
#include "TColor.h"

void Draw1DHist(TH1F *h, bool Pull, float lumi, const char* XaxisName, const char* outname,bool bias=false)
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

  h->GetYaxis()->SetTitleSize(0.03);
  h->GetYaxis()->SetLabelSize(0.03);
  h->GetXaxis()->SetTickSize(0.02);
  h->GetXaxis()->SetTitleSize(0.03);
  h->GetXaxis()->SetLabelSize(0.03);
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetTitleOffset(1.4);
  if(bias){h->SetMaximum(0.5);h->SetMinimum(-0.5);}
  h->Draw("EPL");
  if(bias){TLine *l1 = new TLine(-1,0.14,7,0.14);
    l1->SetLineColor(kRed);
    TLine *l2 = new TLine(-1,-0.14,7,-0.14);
    l2->SetLineColor(kRed);
    l1->Draw();l2->Draw();
      h->Draw("TEXTE SAME");}
  if(Pull == true)
    {
      TF1 *fit = new TF1("fit","gaus",-10,10);
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

void Fit_getPull1D(int rTrue, int catnum, string type)
{
  setTDRStyle();
  const int ncat =5;
  TH1F *pull = new TH1F("pull", "pull values", ncat, 0, ncat);
  //const char* label[ncat]={"bern1",  "exp1", "pow1", "lau1"}; //ele501,mu501                                                                                     
  //const char* label[ncat]={"bern1", "bern2", "exp1", "pow1", "lau1"}; // ele502,mu502,elemu6789                         
  //const char* label[ncat]={"bern1", "bern2", "bern3", "exp1", "pow1", "lau2"};//ele10                                                                              
  const char* label[ncat]={"bern1", "bern2", "exp1", "pow1", "lau2"};//mu10                                                                                       
  //const char* label[ncat]={"bern3", "exp1", "pow1", "lau1"};//ele4                                                                                               
  //const char* label[ncat]={"bern1", "bern2", "bern3", "exp1", "pow1" ,"lau1"};//mu1,ele1                                                                                
  ///const char* label[ncat]={"bern2", "bern3", "exp1", "pow1", "lau1"};//mu3,ele3,ele5                                                                              
  //const char* label[ncat]={"bern3", "bern4", "exp1", "pow1" ,"lau1"};//mu4                                                                                        
  //const char* label[ncat]={"bern2", "bern3", "bern4", "exp1" ,"pow1" ,"lau1"};//mu5  
  int failjobs = 0, failf =0;
  for(int i=0;i<ncat;i++)
    {
      //if(gSystem->cd("plots") == false)gSystem->mkdir("plots");
      system(Form("mkdir -p plots/%s_cat%d_mu%d",type.c_str(),catnum,rTrue));
      system(Form("mkdir -p plots/%s_cat%d_mu%d/trueFunc%d",type.c_str(),catnum,rTrue, i));
      for(int j=0;j<1;j++)
	{
	  TH1F *hM_mu = new TH1F("hM_mu"," ",100,-50,50);
	  TH1F *hM_muErr = new TH1F("hM_muErr", " ", 100 ,0, 100);
	  TH1F *hM_pull = new TH1F("hM_pull"," ",50,-5,5);
	  TH2F *hM_MuvsPull = new TH2F("hM_MuvsPull"," ",100,rTrue-50,rTrue+50,50,-5,5);
	  for(int n=0;n<1000;n++)
	    {

	      //TFile *f = new TFile(Form("results_2016_13TeV_123%d/higgsCombine_%s_cat%d_pdf%d_pdf%d_mu%d.MultiDimFit.mH125.123456.root",n+1,type.c_str(),catnum,i,j,rTrue));
	      // TFile *f = new TFile(Form("results_2016_13TeV_123%d/multidimfit_%s_cat%d_pdf%d_pdf%d_mu%d.root",n+1,type.c_str(),catnum,i,j,rTrue));
	      TFile *f = new TFile(Form("results_2016_13TeV_123%d/multidimfit_%s_cat%d_env_pdf%d_mu%d.root",n+1,type.c_str(),catnum,i,rTrue));
	      if(f->IsZombie())
		{
		  failjobs++;
		  string ff = type+"_cat"+std::to_string(catnum)+"_"+std::to_string(rTrue)+"_"+std::to_string(failf)+".sh";
		  if(failjobs%200==0)failf++;
		  ofstream fail(ff.c_str(),fstream::in | fstream::out | fstream::app);
		  fail <<"cd results_2016_13TeV_123"<<std::to_string(n+1)<<endl;
		  fail<<"combine /afs/cern.ch/work/m/milee/BiasStudy/results_2016_13TeV_123"<<std::to_string(n+1)<<"/card_VBFMVA_v2_"<<type<<"_"<<std::to_string(catnum)<<"_125_env.root  -M MultiDimFit --toysFile=higgsCombine_"<<type<<"_cat"<<std::to_string(catnum)<<"_pdfindex"<<std::to_string(i)<<"_mu"<<std::to_string(rTrue)<<".GenerateOnly.mH125.123"<<std::to_string(n+1)<<".root -P  r --expectSignal "<<std::to_string(rTrue)<<" -t 1 --saveSpecifiedIndex pdfindex_"<<type<<"_cat"<<std::to_string(catnum)<<"_13TeV -m 125 --cminDefaultMinimizerStrategy 0 --name  _"<<type<<"_cat"<<std::to_string(catnum)<<"_env_pdf"<<std::to_string(i)<<"_mu"<<std::to_string(rTrue)<<"--saveFitResult --setParameterRanges r=-120,120"<<endl;	
		  fail<<"cd .."<<endl;
		  //fail<<"genpdf:"<<std::to_string(i)<<"  fitpdf:"<<std::to_string(j)<<endl;
		  fail.close(); 
		  continue;
		}
	      RooFitResult * fitr = (RooFitResult*)f->Get("fit_mdf");
	      RooRealVar *var = (RooRealVar*)fitr->floatParsFinal().find("r");
	      double mu = var->getValV();
	      double muErr = var->getError();
	      hM_muErr->Fill(muErr);
	      hM_pull->Fill((mu-rTrue)/muErr);
	      hM_MuvsPull->Fill(mu,(mu-rTrue)/muErr);
	      hM_mu->Fill(mu);       
	      f->Close();
	      delete f;
	    }    

	  TF1 *fit = new TF1("fit","gaus",-5,5);
	  fit->SetLineColor(46);
	  fit->SetLineWidth(2);
	  hM_pull->Fit("fit","RQ");
	  //fit->SetLineColor(46);
	  //fit->SetLineWidth(2);

	  pull->SetBinContent(i + 1,fit->GetParameter("Mean"));
	  //pull->SetBinContent(i + 1, j + 1, out-rTrue);
	  pull->GetXaxis()->SetBinLabel(i+1, label[i]);

	  // Draw1DHist(TH1F *h, bool Pull, float lumi, const char* XaxisName, const char* outname)
	  Draw1DHist(hM_pull, true, 35.9, Form("#mu-#mu_{true}/#sigma_{#mu}, #mu_{true}=%d",rTrue), Form("plots/%s_cat%d_mu%d/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_Pull_mu%d.pdf", type.c_str(), catnum, rTrue, i, i, j, rTrue));
	  Draw1DHist(hM_mu, false, 35.9, "#mu", Form("plots/%s_cat%d_mu%d/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_mu%d.pdf", type.c_str(), catnum, rTrue,i, i, j,rTrue));
	  Draw1DHist(hM_muErr, false, 35.9, "#sigma_{#mu}", Form("plots/%s_cat%d_mu%d/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_muErr.pdf", type.c_str(), catnum, rTrue, i, i, j));
	  // Draw2DHist(TH2F* h, bool Pull, int PaletteNum, float lumi, const char* XaxisName, const char* YaxisName, const char* outname)
	  Draw2DHist(hM_MuvsPull, false, 35.9, "#mu", "#mu-#mu_{true}/#sigma_{#mu}", "colz", Form("plots/%s_cat%d_mu%d/trueFunc%d/trueFunc%d_FitTo_fitFunc%d_muVsPull.pdf",  type.c_str(), catnum, rTrue, i, i, j));
	}
    }
  Draw1DHist(pull, false, 35.9,  "Fit func.", Form("plots/%s_cat%d_mu%d/BiasTable.pdf",type.c_str(),catnum,rTrue),true);
  
  //TEST!!
  //gSystem->cd("plots");
  //gSystem->Exec(Form("mv trueFunc* mu%d", rTrue));
  //gSystem->Exec(Form("mv BiasTable.pdf mu%d",rTrue));
  //gSystem->cd("../");
}
