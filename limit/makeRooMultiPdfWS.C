/*#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
//#include "HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"

#include "flashggFinalFit/Background/interface/PdfModelBuilder.h"
#include <Math/PdfFuncMathCore.h>
#include <Math/ProbFunc.h>
#include <iomanip>
//#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"*/

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
#include "flashggFinalFit/Background/interface/PdfModelBuilder.h"
#include <Math/PdfFuncMathCore.h>
#include <Math/ProbFunc.h>
#include <iomanip>
//#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"

#include <RooGaussModel.h>
#include <RooTruthModel.h>
#include <RooDecay.h>
#include "RooAddModel.h"
#include <RooNumConvPdf.h>
#include <RooFFTConvPdf.h>
#include "RooRealVar.h"
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
#include "/afs/cern.ch/work/m/milee/HtoZG/MYcode/plugin/tdrstyle.C"
#include "/afs/cern.ch/work/m/milee/HtoZG/MYcode/plugin/CMS_lumi.C"

using namespace RooFit;
using namespace std;

void SetConstantParams(const RooArgSet* params) {
	// set constant parameters for signal fit, ... NO IDEA !!!!
	TIterator* iter(params->createIterator());
	for (TObject *a = iter->Next(); a != 0; a = iter->Next()) {
		RooRealVar *rrv = dynamic_cast<RooRealVar *>(a);
		if (rrv) { rrv->setConstant(true); std::cout << " " << rrv->GetName(); }
	}
} // close set const parameters

TTree* makeTTree(string fname)
{
	// Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y

	Double_t* mH = new Double_t;
	TTree *T1 = new TTree("T1", "data from ascii file");
	T1->Branch("mH", &mH, "mH/D"); // The branch name is m
	T1->ReadFile(fname.c_str(), "mH");

	return T1;
}

void getNAccEv(Float_t *Nev){

	std::ifstream in;
	in.open("/afs/cern.ch/work/m/milee/HtoZG/MYcode/limit/HiggsMass_0426_2016.txt");
	double mass = 0;
	Int_t NevWei = 0;
	//	Double_t mass, fweight, mcwei, NevWei = 0;
	for(int t = 0;t<2000;t++)
	  {
	    if(!in.good()) break ;   
	    in>>mass;
	      NevWei++;
	  }
	in.close();

	*Nev = NevWei;

	std::cout << *Nev << std::endl;
}

void makeRooMultiPdfWS(){

	// Load the combine Library
	gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	setTDRStyle();

	TTree* DataTree = makeTTree("/afs/cern.ch/work/m/milee/HtoZG/MYcode/limit/HiggsMass_0426_2016.txt");

	RooRealVar mH("mH", "m_{#mu#mu#gamma}", 115, 170, "GeV");
	RooRealVar weights("weights", "weights", -10, 10, "");

	RooDataSet data("data", "dataset with Higgs mass", RooArgSet(mH), Import(*DataTree));

	//BERNSTEIN 1
	//RooRealVar p0("p0", "coefficient of x^0 term", 0, 1);
	//RooRealVar p1("p1", "coefficient of x^1 term", 0, 1); // ROOT fit pane : -0.00293702
	//RooBernstein Bern1("Bern1", "polinomi", mH, RooArgList(RooConst(1), p1));
	PdfModelBuilder PdfModel;
	PdfModel.setObsVar(&mH);
	RooAbsPdf *Bern1 = PdfModel.getBernstein("Bern1", 1);

	//BERNSTEIN 2
	//RooRealVar p0_2("p0_2", "coefficient of x^0 term", 0, 1);
	//RooRealVar p1_2("p1_2", "coefficient of x^1 term", 0, 1); // ROOT fit pane : -0.00293702
	//RooRealVar p2_2("p2_2", "coefficient of x^2 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooBernstein Bern2("Bern2", "polinomi", mH, RooArgList(RooConst(1), p1_2, p2_2));
	RooAbsPdf *Bern2 = PdfModel.getBernstein("Bern2", 2);

	//BERNSTEIN 3
	//RooRealVar p0_3("p0_3", "coefficient of x^0 term", 0, 1);
	//RooRealVar p1_3("p1_3", "coefficient of x^1 term", 0, 1); // ROOT fit pane : -0.00293702
	//RooRealVar p2_3("p2_3", "coefficient of x^2 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooRealVar p3_3("p3_3", "coefficient of x^3 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooBernstein Bern3("Bern3", "polinomi", mH, RooArgList(RooConst(1), p1_3, p2_3, p3_3));
	RooAbsPdf *Bern3 = PdfModel.getBernstein("Bern3", 3);

	//BERNSTEIN 4
	//RooRealVar p0_4("p0_4", "coefficient of x^0 term", 0, 1);
	//RooRealVar p1_4("p1_4", "coefficient of x^1 term", 0, 1); // ROOT fit pane : -0.00293702
	//RooRealVar p2_4("p2_4", "coefficient of x^2 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooRealVar p3_4("p3_4", "coefficient of x^3 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooRealVar p4_4("p4_4", "coefficient of x^3 term", 0, 1); //-10 to 10 for RooPolynomial
	//RooBernstein Bern4("Bern4", "polinomi", mH, RooArgList(RooConst(1), p1_4, p2_4, p3_4, p4_4));
	RooAbsPdf *Bern4 = PdfModel.getBernstein("Bern4", 4);

	//EXPONENTIAL
	//RooRealVar alpha("alpha", " ", -1., -100., 0.);
	//RooExponential exp("exp", " ", mH, alpha);
	RooAbsPdf *exp = PdfModel.getExponentialSingle("exp", 1);

	//POWER LAW
	//RooRealVar a("a", " ", 1., 0., 10.);
	//RooRealVar b("b", " ", -1., -10., 0.);
	//RooGenericPdf powerlaw("powerlaw", "a*mH^b", RooArgList(mH, a, b));
	RooAbsPdf *powerlaw = PdfModel.getPowerLawSingle("powerlaw", 1);

	//LAURENT POLYNOMIAL
	//RooRealVar a1("a1", " ", 1, 0, 10);
	//RooRealVar b1("b1", " ", 1, 0, 10);
	//RooGenericPdf Laurent("Laurent", "a1*mH^(-4)+b1*mH^(-6)", RooArgList(mH, a1, b1));
	RooAbsPdf *Laurent = PdfModel.getLaurentSeries("Laurent", 1);

	RooFitResult* r_Bern1 = Bern1->fitTo(data, Save(kTRUE));
	RooFitResult* r_Bern2 = Bern2->fitTo(data, Save(kTRUE));
	RooFitResult* r_Bern3 = Bern3->fitTo(data, Save(kTRUE));
	RooFitResult* r_Bern4 = Bern4->fitTo(data, Save(kTRUE));
	RooFitResult* r_exp = exp->fitTo(data, Save(kTRUE));
	RooFitResult* r_powerlaw = powerlaw->fitTo(data, Save(kTRUE));
	RooFitResult* r_Laurent = Laurent->fitTo(data, Save(kTRUE));

	//Bern1_p0.setConstant(true);
	//Bern1_p1.setConstant(true);
	//p0_2.setConstant(true);
	//p1_2.setConstant(true);
	//p2_2.setConstant(true);
	//p0_3.setConstant(true);
	//p1_3.setConstant(true);
	//p2_3.setConstant(true);
	//p3_3.setConstant(true);
	//p0_4.setConstant(true);
	//p1_4.setConstant(true);
	//p2_4.setConstant(true);
	//p3_4.setConstant(true);
	//p4_4.setConstant(true);
	//alpha.setConstant(true);
	//a.setConstant(true);
	//b.setConstant(true);
	//a1.setConstant(true);
	//b1.setConstant(true);

	// Make a RooCategory object. This will control which of the pdfs is "active"
	RooCategory cat("pdf_index", "Index of Pdf which is active");

	// Make a RooMultiPdf object. The order of the pdfs will be the order of their index, ie for below
	// 0 == exponential
	// 1 == linear function
	// 2 == powerlaw
	RooArgList mypdfs;
	mypdfs.add(*Bern1);
	mypdfs.add(*Bern2);
	mypdfs.add(*Bern3);
	mypdfs.add(*Bern4);
	mypdfs.add(*exp);
	mypdfs.add(*powerlaw);
	mypdfs.add(*Laurent);

	//mypdfs.dump();

	RooMultiPdf multipdf("roomultipdf", "All Pdfs", cat, mypdfs);

	Float_t Nev;
	getNAccEv(&Nev);

	// As usual make an extended term for the background with _norm for freely floating yield---fit bkg...why need acc*eff??
	RooRealVar norm("roomultipdf_norm", "Number of background events", Nev, Nev*0.25, Nev*1.75);

	// Save to a new workspace
	TFile *fout = new TFile("background_pdfs.root", "RECREATE");
	RooWorkspace *wout = new RooWorkspace("backgrounds", "backgrounds");
	wout->import(cat);
	wout->import(norm);
	wout->import(multipdf);
	wout->Print();
	wout->Write();
	fout->Write();
	fout->Print();

	wout->defineSet("Params1",
		RooArgSet(
		*wout->var("Bern1_p0"),
		*wout->var("Bern2_p0"),
		*wout->var("Bern2_p1"),
		*wout->var("Bern3_p0"),
		*wout->var("Bern3_p1"),
		*wout->var("Bern3_p2")
		));
	SetConstantParams(wout->set("Params1"));

	wout->defineSet("Params2",
		RooArgSet(
		*wout->var("Bern4_p0"),
		*wout->var("Bern4_p1"),
		*wout->var("Bern4_p2"),
		*wout->var("Bern4_p3"),
		*wout->var("Laurent_l1"),
		*wout->var("exp_p1"),
		*wout->var("powerlaw_p1")
		));
	SetConstantParams(wout->set("Params2"));

	TCanvas* c1 = new  TCanvas("c1", "", 800, 600);
	c1->SetRightMargin(0.05);
	c1->SetTopMargin(0.08);

	mH.setRange("unblindR1", 115, 120);
	mH.setRange("unblindR2", 130, 170.0);

	RooPlot *xframe = mH.frame();
	data.plotOn(xframe, CutRange("unblindR1"), CutRange("unblindR2"), Binning(55), RooFit::Name("data"));
	Bern1->plotOn(xframe, LineColor(kRed), RooFit::Name("Bern1"));
	Bern2->plotOn(xframe, LineColor(kGreen), RooFit::Name("Bern2"));
	Bern3->plotOn(xframe, LineColor(kBlue), RooFit::Name("Bern3"));
	Bern4->plotOn(xframe, LineColor(kOrange), RooFit::Name("Bern4"));
	exp->plotOn(xframe, LineColor(7), RooFit::Name("exp"));
	powerlaw->plotOn(xframe, LineColor(6), RooFit::Name("powerlaw"));
	Laurent->plotOn(xframe, LineColor(13), RooFit::Name("Laurent"));
	xframe->SetTitle("PDF fits to toy data");

	TLegend* leg1 = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg1->AddEntry(xframe->findObject("data"), "2016 Data", "lep");
	leg1->AddEntry(xframe->findObject("Bern1"), "Bernstein 1st", "l");
	leg1->AddEntry(xframe->findObject("Bern2"), "Bernstein 2nd", "l");
	leg1->AddEntry(xframe->findObject("Bern3"), "Bernstein 3rd", "l");
	leg1->AddEntry(xframe->findObject("Bern4"), "Bernstein 4th", "l");
	leg1->AddEntry(xframe->findObject("exp"), "exponential", "l");
	leg1->AddEntry(xframe->findObject("powerlaw"), "power law", "l");
	leg1->AddEntry(xframe->findObject("Laurent"), "Laurent form", "l");

	c1->cd();
	xframe->Draw();
	xframe->SetMinimum(0.00001);
	leg1->Draw();

    extraText  = "Preliminary";
    lumi_13TeV = "35.9fb^{-1}";
	CMS_lumi(c1, 4, 0);

	c1->Update();
	c1->RedrawAxis();
	c1->GetFrame()->Draw();

	c1->SaveAs("MultiFitcat6.png");
	c1->SaveAs("MultiFitcat6.pdf");
	cout<<"N_event:"<<Nev<<endl;
}
