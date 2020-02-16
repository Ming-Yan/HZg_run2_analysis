#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooProduct.h"
#include "RooAddition.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"

using namespace RooFit;

void params(TString channel, TString name, Float_t *omean, Float_t *osigma, Float_t *ofrac, Float_t *oalpha, Float_t *opower, Float_t *oGsigma){
	TFile *f = TFile::Open("PDFs/WS_" + channel +"_" + name + ".root");
	RooWorkspace *w = (RooWorkspace*)f->Get("");

	Float_t mean = 0, sigma = 0, frac = 0, alpha = 0, power = 0, Gsigma = 0;

	if (name != "120" && name != "125" && name != "130")
	  {
	  mean = (w->var("mean2fr"))->getVal();
	  sigma = (w->var("sigmaCBfr"))->getVal();
	  frac = (w->var("fracG1fr"))->getVal();
	  alpha = (w->var("alphafr"))->getVal();
	  power = (w->var("powerfr"))->getVal();
	  //Gsigma = (w->function("sigma2"))->getVal();
	  Gsigma = (w->var("sigmaGau2fr"))->getVal();
	}
	
	else{
	  mean = (w->var("mean2"))->getVal();
	  sigma = (w->var("sigma_CB"))->getVal();
	  frac = (w->var("frac_G1"))->getVal();
	  alpha = (w->var("alpha"))->getVal();
	  power = (w->var("n"))->getVal();
	  Gsigma = (w->var("sigma2_Gau"))->getVal();

	  //	  cout << (w->var("Mean"))->getError() << " " << (w->var("Mean"))->getErrorHi() << " " << (w->var("Mean"))->getErrorLo() << endl;
	}

	*omean = mean;
	*osigma = sigma;
	*ofrac = frac;
	*oalpha = alpha;
	*opower = power;
	*oGsigma = Gsigma;
}

void paramsErr(TString channel, TString name, Float_t *omean, Float_t *osigma, Float_t *ofrac, Float_t *oalpha, Float_t *opower, Float_t *oGsigma){

	TFile *f = TFile::Open("PDFs/WS_" + channel +"_" + name + ".root");
	RooWorkspace *w = (RooWorkspace*)f->Get("");

	Float_t mean = 0, sigma = 0, frac = 0, alpha = 0, power = 0, Gsigma = 0;

	if (name != "120" && name != "125" && name != "130"){
	      mean = (w->var("mean2fr"))->getError();
	      sigma = (w->var("sigmaCBfr"))->getError();
	      frac = (w->var("fracG1fr"))->getError();
	      alpha = (w->var("alphafr"))->getError();
	      power = (w->var("powerfr"))->getError();
	      Gsigma = (w->var("sigmaGau2fr"))->getError();
	}
	else{
	  mean = (w->var("mean2"))->getError();
          sigma = (w->var("sigma_CB"))->getError();
          frac = (w->var("frac_G1"))->getError();
	  alpha = (w->var("alpha"))->getError();
          power = (w->var("n"))->getError();
          Gsigma = (w->var("sigma2_Gau"))->getError();
	}

	*omean = mean;
	*osigma = sigma;
	*ofrac = frac;
	*oalpha = alpha;
	*oGsigma = Gsigma;

}

void plotparams(){

  setTDRStyle();
  TString channel[3] = {"ttH","ZH","WH"};
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
	for(int j = 0;j<3;j++){
	vector<float> vmean, vsigma, vmass, vfrac, valpha, vn, vGsigma;
	vector<float> vmeanerr, vsigmaerr, vmasserr, vfracerr, valphaerr, vnerr, vGsigmaerr;

	vmean.clear();
	vsigma.clear();
	vfrac.clear();
	valpha.clear();
	vn.clear();
	vGsigma.clear();
	vmass.clear();

	vmeanerr.clear();
	vsigmaerr.clear();
	vfracerr.clear();
	valphaerr.clear();
	vnerr.clear();
	vGsigmaerr.clear();

	for (int i = 0; i < 11; i++){

		int mass = 120 + i;
		Float_t mean, sigma, frac, alpha, n, Gsigma;
		Float_t meanerr, sigmaerr, fracerr, alphaerr, nerr, Gsigmaerr;
		params(channel[j],name[i], &mean, &sigma, &frac, &alpha, &n, &Gsigma);
		paramsErr(channel[j],name[i], &meanerr, &sigmaerr, &fracerr, &alphaerr, &nerr, &Gsigmaerr);

		//cout << meanerr << " " << sigmaerr << " " << fracerr << " " << alphaerr << " " << nerr << " " << Gsigmaerr << endl;
		//cout << mean << " " << sigma << " " << frac << " " << alpha << " " << n << " " << Gsigma << endl;
		vmean.push_back(mean);
		vsigma.push_back(sigma);
		vfrac.push_back(frac);
		valpha.push_back(alpha);
		vn.push_back(n);
		vGsigma.push_back(Gsigma);
		vmass.push_back(mass);

		vmeanerr.push_back(meanerr);
		vsigmaerr.push_back(sigmaerr);
		vfracerr.push_back(fracerr);
		valphaerr.push_back(alphaerr);
		vnerr.push_back(nerr);
		vGsigmaerr.push_back(Gsigmaerr);
		vmasserr.push_back(0);
	}
	TGraphErrors* gmean = new TGraphErrors(vmass.size(), &vmass[0], &vmean[0], &vmasserr[0], &vmeanerr[0]);
	TGraphErrors* gsigma = new TGraphErrors(vmass.size(), &vmass[0], &vsigma[0], &vmasserr[0], &vsigmaerr[0]);
	TGraphErrors* gfrac = new TGraphErrors(vmass.size(), &vmass[0], &vfrac[0], &vmasserr[0], &vfracerr[0]);
	TGraphErrors* galpha = new TGraphErrors(vmass.size(), &vmass[0], &valpha[0], &vmasserr[0], &valphaerr[0]);
	TGraphErrors* gn = new TGraphErrors(vmass.size(), &vmass[0], &vn[0], &vmasserr[0], &vnerr[0]);
	TGraphErrors* gGsigma = new TGraphErrors(vmass.size(), &vmass[0], &vGsigma[0], &vmasserr[0], &vGsigmaerr[0]);
	const char *cchannel = channel[j];
 	TCanvas *c = new TCanvas("c", "c", 750, 750);
	c->cd();
	gmean->GetXaxis()->SetTitle("m_{H}");
	gmean->GetYaxis()->SetTitle("Mean (CB)");
	gmean->Draw("apl");
	CMS_lumi(c, 4, 0);
	TString pname;
	pname = TString::Format("mean1eeg_mmg_%s_allcats.pdf",cchannel);
	c->Print(pname);

	TCanvas *d = new TCanvas("d", "d", 750, 750);
	d->cd();
	gsigma->GetXaxis()->SetTitle("m_{H}");
	gsigma->GetYaxis()->SetTitle("Sigma (CB)");
	gsigma->Draw("ap");
	CMS_lumi(d, 4, 0);
	pname = TString::Format("sigma1eeg_mmg_%s_allcats.pdf",cchannel);
	d->Print(pname);
	
	TCanvas *e = new TCanvas("e", "e", 750, 750);
	e->cd();
	gfrac->GetXaxis()->SetTitle("m_{H}");
	gfrac->GetYaxis()->SetTitle("frac");
	gfrac->Draw("apl");
	CMS_lumi(e, 4, 0);
	pname = TString::Format("fraceeg_mmg_%s_allcats.pdf",cchannel);
        e->Print(pname);

	TCanvas *f = new TCanvas("f", "f", 750, 750);
	f->cd();
	galpha->GetXaxis()->SetTitle("m_{H}");
	galpha->GetYaxis()->SetTitle("Alpha");
	galpha->Draw("apl");
	CMS_lumi(f, 4, 0);
	pname = TString::Format("alphaeeg_mmg_%s_allcats.pdf",cchannel);
        f->Print(pname);

	TCanvas *g = new TCanvas("g", "g", 750, 750);
	g->cd();
	gn->GetXaxis()->SetTitle("m_{H}");
	gn->GetYaxis()->SetTitle("n");
	gn->Draw("apl");
	CMS_lumi(g, 4, 0);
	pname = TString::Format("powereeg_mmg_%s_allcats.pdf",cchannel);
        g->Print(pname);

	TCanvas *h = new TCanvas("h", "h", 750, 750);
	h->cd();
	gGsigma->GetXaxis()->SetTitle("m_{H}");
	gGsigma->GetYaxis()->SetTitle("Sigma (Gauss)");
	gGsigma->Draw("apl");
	CMS_lumi(h, 4, 0);
	pname = TString::Format("sigma2eeg_mmg_%s_allcats.pdf",cchannel);
        h->Print(pname);}
}
