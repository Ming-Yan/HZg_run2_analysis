#ifndef H_SIGFIT
#define H_SIGFIT
#include "../interface/Maketree.h"
#include "../interface/SetconstParam.h"

void sigfit(string txtname, Int_t Mean, RooFitResult *r_sig, RooWorkspace *w, string channel, string type, string cat,string fin,string vername)
{

  ///create tree
  TTree* SigTree1 = makeTTree_signal(txtname);

  ///define variables for fitting
  RooRealVar mH("mH", "mH", 115, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///build unbin data&signal distribution
  RooDataSet signal_2016("signal_2016", " ", RooArgSet(mH, weights), Import(*SigTree1), WeightVar(weights));


  //-------------------------------------------------------//
  // Siganl fit                                            //
  // Using Crystal ball plus 2Gaussian                     //
  // One Gaussian with the same mean, another to fit tail  //
  //-------------------------------------------------------//

  RooRealVar mean("mean", " ",Mean, Mean-3.5, Mean+3.5);
  RooRealVar sigma_Gau("sigma_Gau"," ",5. , 2.5, 20);//Gaussian2 sigdfma
  RooGaussian Gauss("Gauss"," ",mH, mean, sigma_Gau);

  RooRealVar sigma_CB("sigma_CB"," ",1.5 , 0.01,3.0); 
  RooRealVar alpha("alpha"," ",2.5,.01,10); // Alpha: Gaussian tail
  RooRealVar n("n"," ",10,.2, 30.); // n: normalization
  RooCBShape CBall("CBall"," ",mH,mean,sigma_CB,alpha,n);
  RooRealVar frac_G1("frac_G1"," ",0.7,0.45,.9999999);//fraction of Gaussian1

  RooAddPdf Sig_bin2("Sig_bin2"," ",RooArgList(CBall,Gauss),frac_G1);//signal PDF

  ///setting fitting range
  mH.setRange("sigFitRange", 115, 170);
  RooFitResult* r_sig_2016 = Sig_bin2.fitTo(signal_2016, Save(kTRUE), Range("sigFitRange"),RooFit::PrintLevel(-1));

  /////////////////////////////
  //                         //
  // building workspace      //
  //                         //
  /////////////////////////////
  RooMsgService::instance().setSilentMode(true); 
  RooMsgService::instance().setGlobalKillBelow(RooFit::INFO);
  w->import(signal_2016,Rename(TString::Format("%s_%s_%d_cat%s", type.c_str(),channel.c_str(),Mean,cat.c_str())), RenameVariable("mH", "CMS_hzg_mass"));
  w->import(Sig_bin2, RenameAllNodes(TString::Format("%s_%s_cat%s", type.c_str(),channel.c_str(),cat.c_str())), RenameAllVariablesExcept(TString::Format("%s_%s_cat%s", type.c_str(),channel.c_str(),cat.c_str()), "mH"),
	    RenameVariable("mH", "CMS_hzg_mass"));
  w->defineSet("SigPdfParams",
	       RooArgSet(
			 *w->var(Form("mean_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("sigma_Gau_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("sigma_CB_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("n_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("alpha_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str())),
			 *w->var(Form("frac_G1_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str()))));
  SetConstantParams(w->set("SigPdfParams"));
  w->pdf(TString::Format("Sig_bin2_%s_%s_cat%s",type.c_str(),channel.c_str(),cat.c_str()));
  if(type=="mu"||type== "ele_mu")
    {
			
      w->factory(Form("CMS_hzg_delta_muRoch_mean_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_muPho_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
	 
      w->factory(Form("CMS_hzg_delta_muRoch_sigma_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muEM_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_muPho_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));

      w->factory(Form("prod::mean_corr_%s_%s_cat%s(mean_%s_%s_cat%s,sum::CMS_hzg_delta_mu_mean_%s_%s_cat%s(CMS_hzg_delta_muRoch_mean_%s_%s_cat%s, CMS_hzg_delta_muEM_mean_%s_%s_cat%s, CMS_hzg_delta_muPho_mean_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("prod::sigma_corr_%s_%s_cat%s(sigma_CB_%s_%s_cat%s, sum::CMS_hzg_delta_mu_sigma_%s_%s_cat%s(CMS_hzg_delta_muRoch_sigma_%s_%s_cat%s, CMS_hzg_delta_muEM_sigma_%s_%s_cat%s, CMS_hzg_delta_muPho_sigma_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));

      w->factory(Form("EDIT::newPdf_%s_%s_cat%s(Sig_bin2_%s_%s_cat%s,mean_%s_%s_cat%s=mean_corr_%s_%s_cat%s, sigma_CB_%s_%s_cat%s=sigma_corr_%s_%s_cat%s)",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
	 
    }

  ///em scale 
  if(type=="ele")
    {
      w->factory(Form("CMS_hzg_delta_eleEM_mean_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod
      w->factory(Form("CMS_hzg_delta_elePho_mean_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str())); ///inside hte square brackets are hte initial values so change to 1 if i use prod

      w->factory(Form("CMS_hzg_delta_eleEM_sigma_%s_%s_cat%s[1]",type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("CMS_hzg_delta_elePho_sigma_%s_%s_cat%s[0]",type.c_str(),channel.c_str(),cat.c_str()));

	 
      w->factory(Form("prod::mean_corr_%s_%s_cat%s(mean_%s_%s_cat%s,sum::CMS_hzg_delta_ele_mean_%s_%s_cat%s(CMS_hzg_delta_eleEM_mean_%s_%s_cat%s, CMS_hzg_delta_elePho_mean_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
      w->factory(Form("prod::sigma_corr_%s_%s_cat%s(sigma_CB_%s_%s_cat%s,sum::CMS_hzg_delta_ele_sigma_%s_%s_cat%s(CMS_hzg_delta_eleEM_sigma_%s_%s_cat%s, CMS_hzg_delta_elePho_sigma_%s_%s_cat%s))",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));

      w->factory(Form("EDIT::newPdf_%s_%s_cat%s(Sig_bin2_%s_%s_cat%s,mean_%s_%s_cat%s=mean_corr_%s_%s_cat%s, sigma_CB_%s_%s_cat%s=sigma_corr_%s_%s_cat%s)",type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str(),type.c_str(),channel.c_str(),cat.c_str()));
    } 	

  //check the fitting
  TCanvas* c = new  TCanvas("c", "", 800, 600);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.08);
  RooPlot* xframe4 = mH.frame(115,170) ;
  TLatex* ltx1 = new TLatex();
  ltx1->SetNDC();
  ltx1->SetTextFont(61);
  ltx1->SetTextSize(0.05);
  ltx1->DrawLatex(0.19,0.85,"CMS");
  ltx1->SetTextFont(52);	
  ltx1->SetTextSize(0.04);
  ltx1->DrawLatex(0.19,0.81,"Preliminary");
  ltx1->SetTextFont(42);
  ltx1->SetTextSize(0.03);
  ltx1->DrawLatex(0.16,0.94,"H#rightarrowZ#gamma#rightarrowll#gamma");
  ltx1->SetTextFont(42);
  ltx1->SetTextSize(0.04);
  ltx1->DrawLatex(0.68,0.94,"2016 35.9 fb^{-1} (13TeV)");
  signal_2016.plotOn(xframe4,Binning(55), RooFit::Name("Sig_plot")) ;
  Sig_bin2.plotOn(xframe4, RooFit::Name("SigPdf_plot"),LineColor(kBlue));
  Sig_bin2.plotOn(xframe4,RooFit::Components("Gauss"),LineColor(kOrange+7),LineStyle(kDashed),RooFit::Name("Gauss"));
  Sig_bin2.plotOn(xframe4,RooFit::Components("CBall"),LineColor(kGreen),LineStyle(kDashed),RooFit::Name("CBall"));
  Sig_bin2.paramOn(xframe4,Layout(0.7,0.95,0.95));

  xframe4->SetMinimum(0.00001);
  //gPad->SetLogy();
  xframe4->getAttText()->SetTextSize(0.03);
  xframe4->GetYaxis()->SetTickSize(0.02);
  xframe4->GetYaxis()->SetTitleSize(0.03);
  xframe4->GetYaxis()->SetTitleOffset(1.3);
  xframe4->GetYaxis()->SetLabelSize(0.03);
  xframe4->GetXaxis()->SetTitleOffset(1.0);
  xframe4->GetXaxis()->SetTitle("M_{ll#gamma} (GeV)");
  xframe4->GetXaxis()->SetTickSize(0.02);
  xframe4->GetXaxis()->SetTitleSize(0.04);
  xframe4->GetXaxis()->SetLabelSize(0.04);
  xframe4->Draw();

  TLegend* leg4 = new TLegend(0.45,0.7,0.65,0.9);
  leg4->AddEntry(xframe4->findObject("Sig_plot"), "signal", "lep");
  leg4->AddEntry(xframe4->findObject("SigPdf_plot"), "Signal model", "l");
  leg4->AddEntry(xframe4->findObject("Gauss"), "Gauss", "l");
  leg4->AddEntry(xframe4->findObject("CBall"), "CBall", "l");
  leg4->Draw("same");
  string figname;
  string meanval = std::to_string(Mean);
  figname  = "plot/fit/"+fin+vername+"/sigfit_"+ type + "_" + channel+ "_" +cat + "_" + meanval + ".png";
  const char *fig = figname.c_str();
  c->Print(fig); 
  gPad->SetLogy();
  xframe4->Draw();
  leg4->Draw("same");
  figname  = "plot/fit/"+fin+vername+"/sigfit_"+ type + "_" + channel+ "_" +cat + "_" + meanval + "log.png";
  c->Print(figname.c_str()); 
}
#endif
