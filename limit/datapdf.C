///USAGE::root -l -b datapdf.C\(\"Moriond17_update0709\"\,1\,\"mu\"\,\"bern\"\,1\)
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "flashggFinalFit/Background/interface/PdfModelBuilder.h"
#include <Math/PdfFuncMathCore.h>
#include <Math/ProbFunc.h>
#include <iomanip>
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/predicate.hpp"

//#include "boost/program_options.hpp"
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
#include "TChain.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"
#include "../interface/SetconstParam.h"
#include "../interface/Maketree.h"
#include "TTree.h"
#include "TLegend.h"
#include "TFrame.h"
#include "RooFitResult.h"

#include "makebkg.h"

using namespace RooFit;

void datapdf(string fin, string type, string pdf,int pdforder,bool makedir, bool isboost, int period,int cat = 1, float kinup = -1.0 , float kindown = 1.0, float kinMVA = -0.01, float VBFMVA = -0.01, string vername = "_wboost")
{
  //plot style setting

  setTDRStyle();
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "35.9 fb^{-1}";

  if(makedir==true)
  {
	      char file[200];
	      sprintf(file,"mkdir -p /afs/cern.ch/work/m/milee/MYcode/limit/bkg/%s%s/",fin.c_str(),vername.c_str());
	      system(file);
  }  
  make_bkg(vername,fin,period,cat,type,isboost,kinup, kindown, kinMVA,VBFMVA);

  ///create tree
  char intxt[500];
  sprintf(intxt,"/afs/cern.ch/work/m/milee/MYcode/limit/bkg/%s%s/HiggsMass_%s_bkg_%s_cat%d_%d.txt",fin.c_str(), vername.c_str(),fin.c_str(),type.c_str(), cat,period);
	
  int totalev = 0;
  TTree* DataTree1 = makeTTree(intxt);
  totalev = DataTree1->GetEntriesFast();

  ///define variables for fitting
  RooRealVar mH("mH", "mH", 115, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///setting fitting range
  mH.setRange("dataFitRange",115, 170);

  ///build unbin data&signal distribution
  RooDataSet data("data", " ", RooArgSet(mH), Import(*DataTree1));

  /////////////////////////////////
  //bkg fit                      //
  //Bernstein 2nd polynomial     //
  /////////////////////////////////
  
  RooRealVar BkgPdf_norm("BkgPdf_norm"," ",totalev, totalev*0.25,totalev*1.75);
  mH.setRange("window", 115, 170);
  PdfModelBuilder pdfsModel;
  pdfsModel.setObsVar(&mH);
  RooAbsPdf *BkgPdf ;
  if(pdf=="power")BkgPdf= pdfsModel.getPowerLawSingle("BkgPdf", pdforder);
  if(pdf=="bern")BkgPdf= pdfsModel.getBernstein("BkgPdf", pdforder);
  if(pdf=="laurent")BkgPdf= pdfsModel.getLaurentSeries("BkgPdf", pdforder);
  if(pdf=="exp")BkgPdf= pdfsModel.getExponentialSingle("BkgPdf", pdforder);

   RooFitResult* r_bkg = BkgPdf->fitTo(data, Range("dataFitRange"), Save(kTRUE)) ;
   

  /////////////////////////////
  //                         //
  // building workspace      //
  //                         //
  /////////////////////////////


  RooWorkspace *w = new RooWorkspace("w"," ") ;

  w->import(data,Rename(Form("data_obs_%s_cat%d_%d",type.c_str(),cat,period)),RenameVariable("mH", "CMS_hzg_mass"));
	//w->import(*BkgPdf_2016,RenameVariable("mH", "CMS_hzg_mass"));
  w->import(*BkgPdf,RenameAllNodes(TString::Format("%s_cat%d_%d", type.c_str(),cat,period)), RenameAllVariablesExcept(TString::Format("%s_cat%d_%d", type.c_str(),cat,period), "mH"),RenameVariable("mH", "CMS_hzg_mass"));
  w->pdf("BkgPdf");
  w->import(BkgPdf_norm,RenameVariable("BkgPdf_norm",Form("BkgPdf_%s_cat%d_%d_norm",type.c_str(),cat,period)));

  //w->import(*BkgPdf_2016,RenameVariable("mH", "CMS_hzg_mass"));
  /*if(pdforder == 1&&pdf=="bern")
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    else if(pdforder == 1&&pdf=="laurent")
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_l1_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    else if(pdforder == 1&&pdf!="laurent"&&pdf!="bern")
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    if(pdforder == 2)
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    if(pdforder ==3)
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    if(pdforder==4)
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p3_%s_cat%d",type.c_str(),cat))
    )
    );
    }
    if(pdforder==5)
    {
    w->defineSet("BkgPdfParams",
    RooArgSet(
    *w->var(Form("BkgPdf_2016_p0_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p1_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p2_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p3_%s_cat%d",type.c_str(),cat)),
    *w->var(Form("BkgPdf_2016_p4_%s_cat%d",type.c_str(),cat))
    )
    );
    }*/
   
  //SetConstantParams(w->set("BkgPdfParams"));
  char ws[80];
  sprintf(ws,"PDFs/%s%s/bkg_%s_WS_%s_cat%d_%d.root",fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(),cat,period);
  w->writeToFile(ws);

  ///plot
  TCanvas* c1 = new  TCanvas("c1", "", 800, 600);

  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.08);
				
  mH.setRange("blind1",115,120) ;
  mH.setRange("blind2",130,170);
  RooPlot* xframe1  = mH.frame(Title(Form("Data and the fit for %d",period))) ;
  data.plotOn(xframe1,Binning(55),CutRange("blind1"),RooFit::Name("data")) ;
  data.plotOn(xframe1,Binning(55),CutRange("blind2")) ;
  //  BkgPdf_2016->plotOn(xframe1, RooFit::Name("Bkg_2016"),VisualizeError(*r_bkg_2016,2),FillColor(7));
  //BkgPdf_2016->plotOn(xframe1, RooFit::Name("Bkg_2016"),VisualizeError(*r_bkg_2016,1),FillColor(kAzure+7));
  BkgPdf->plotOn(xframe1, RooFit::Name("Bkg"),LineColor(kBlue));
  data.plotOn(xframe1,Binning(55),CutRange("blind1"),RooFit::Name("data")) ;
  data.plotOn(xframe1,Binning(55),CutRange("blind2")) ;
  //  data_2016.plotOn(xframe1,Binning(55),RooFit::Name("data_2016")) ;
  BkgPdf->paramOn(xframe1,Layout(0.65,0.92,0.89));
  xframe1->getAttText()->SetTextSize(0.03);
  ///    gPad->SetLogy();  
  xframe1->SetMinimum(0.00001);
  xframe1->GetXaxis()->SetTitle("M_{ll#gamma} (GeV)");
  xframe1->GetXaxis()->SetTickSize(0.02);
  xframe1->GetXaxis()->SetTitleSize(0.04);
  xframe1->GetXaxis()->SetLabelSize(0.04);


  CMS_lumi(c1, 4, 11);
  xframe1->Draw();
  char outplot[80];
  sprintf(outplot,"plot/fit/%s%s/bkg_%s_cat%d.png",fin.c_str(),vername.c_str(),type.c_str(),cat);
  c1->Print(outplot); 
  // delete c1;  delete w; delete DataTree1;
}

