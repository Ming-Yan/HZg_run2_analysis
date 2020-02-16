#ifndef H_UNC_FIT
#define H_UNC_FIT
#include "../interface/Maketree.h"
#include "../interface/SetconstParam.h"
#include "/afs/cern.ch/work/m/milee/MYcode/limit/cat.h"
void  make_Sig(string vername, string fin, string channel, int period, int m, string type ,int catcut, bool isboost, float kinup, float kindown,float kincut, float VBFcut)
{
  // gROOT->ProcessLine( "gErrorIgnoreLevel = 3001;");
  char inpathele[500],inpathmu[500],outpath[500];
  if(channel=="WH") channel = "W*H";
  sprintf(inpathele, "/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s%s_ele_HZg_%s_%dGeV.root",fin.c_str(),vername.c_str(),channel.c_str(),m);
  sprintf(inpathmu, "/afs/cern.ch/work/m/milee/outfile/uncer/mc_%s%s_mu_HZg_%s_%dGeV.root",fin.c_str(),vername.c_str(),channel.c_str(),m);  
  TChain ch("tZg");
  if(channel=="W*H") channel = "WH";
  if(type=="ele"||type=="ele_mu")ch.Add(inpathele);
  if(type=="mu"||type=="ele_mu")ch.Add(inpathmu);
  sprintf(outpath,"sig/%s%s/HiggsMass_signal_%s_%s_%s_%d_%d_%d.txt",fin.c_str(), vername.c_str(), fin.c_str(),type.c_str(),channel.c_str(),catcut,m,period);
  ofstream sig(outpath);

  Int_t run_,lumis_, cat, alepCh, lepCh_[2],totmatch,totalev,mcev,isbtag;
  Long64_t  event_;
  Float_t totSF_, puwei_, mcwei_, genwei_,L1wei_, ptwei_, mllg_,HZgVBF,HZgMVA,ZgPTt,sfedz_[2],mllgpt,gR9_,gSCEta_,lepEta_[2],lepSCEta_[2],REFITmllg_;
  double totwei;
  // ch.SetBranchAddress("run",      &run_);
  // ch.SetBranchAddress("event",    &event_);
  // ch.SetBranchAddress("lumis",    &lumis_);
  ch.SetBranchAddress("cat",      &cat);
  ch.SetBranchAddress("puwei",    &puwei_);
  ch.SetBranchAddress("genwei",   &genwei_);
  ch.SetBranchAddress("mcwei",    &mcwei_);
  ch.SetBranchAddress("L1wei",    &L1wei_);
  ch.SetBranchAddress("ptwei",    &ptwei_);
  ch.SetBranchAddress("totSF",    &totSF_);
  ch.SetBranchAddress("HZgVBF",   &HZgVBF);
  ch.SetBranchAddress("HZgMVA",   &HZgMVA);
  ch.SetBranchAddress("ZgPTt",    &ZgPTt);
  ch.SetBranchAddress("mllgpt",  &mllgpt);
  ch.SetBranchAddress("phoR9",   &gR9_);
  ch.SetBranchAddress("phoSCEta",  &gSCEta_);
  ch.SetBranchAddress("lepEta",  lepEta_);
  ch.SetBranchAddress("lepSCEta",  lepSCEta_);
  ch.SetBranchAddress("mllg",    &mllg_);
  ch.SetBranchAddress("REFITmllg",    &REFITmllg_);

  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
      if(period==2016)ptwei_ = 1.;
      if(period==2018)L1wei_ = 1.;
      totwei = mcwei_*genwei_*totSF_*puwei_*L1wei_*ptwei_;
      int j = (lepSCEta_[0]==-5)? 1:0;
      int newcat = -999;
      if(REFITmllg_>170||REFITmllg_<115) continue;
      float lepEta0 = (lepSCEta_[0]==-5)? lepEta_[0]:lepSCEta_[0];
      float lepEta1 = (lepSCEta_[1]==-5)? lepEta_[1]:lepSCEta_[1];
      //newcat = cat_MVAlimit(j, period,cat, gR9_, gSCEta_, lepEta0, lepEta1,mllgpt,HZgMVA,HZgVBF,kincut,VBFcut);
      newcat = cat_MVA(j,period,cat,isboost,HZgMVA,HZgVBF,kincut,VBFcut,mllgpt);
      //newcat = cat_cutbase(j,cat, gR9_,gSCEta_,lepEta0,lepEta1, mllgpt);
      //if(newcat==-99)continue;//discard event with kinMVA pre
      if(catcut==6789&&newcat==6789)sig<<REFITmllg_<<" "<<totwei<<endl;
      if(catcut==501&&newcat==501) {sig<<REFITmllg_<<" "<<totwei<<endl;}
       if(catcut==502&&newcat==502) sig<<REFITmllg_<<" "<<totwei<<endl;
       //if(catcut==5&&newcat==5) sig<<REFITmllg_<<" "<<totwei<<endl;
       if(isboost==1&&catcut==10&&newcat==10)sig<<REFITmllg_<<" "<<totwei<<endl;
       //if(isboost==1&&catcut==10&&newcat==10)sig<<REFITmllg_<<" "<<totwei<<endl;
       if(catcut<7&&newcat==-1&&HZgMVA>=kindown&&HZgMVA<kinup)sig<<REFITmllg_<<" "<<totwei<<endl;  

    }
}

void unc_fit(string txtname, Int_t Mean, int period, string channel, string type, int cat,string fin,string vername, float *un_mean, float *un_sigma, bool issigma)
{
  // gROOT->ProcessLine( "gErrorIgnoreLevel = 3001;");
  //Get info from nominal file
  string type2;
  type2=(cat==6789)?"ele_mu" : type;
  string pname;
  if (period==2016)pname = "_refit_woboost_comb_newcat01257";
  if (period==2017)pname = "_refit_woboost_comb_newcat01267";
  if (period==2018)pname = "_refit_woboost_comb_newcat01367";
  string nomf = (cat<6)? pname:"_refit_tag";
  string fins = (period==2016) ? fin : fin+"v2";
  TFile *f = TFile::Open(Form("/afs/cern.ch/work/m/milee/MYcode/limit/PDFs/%s%s/WS_%s_%s_%s_%d_%d_%d.root",fins.c_str(),nomf.c_str(),fins.c_str(),type2.c_str(),channel.c_str(),cat,Mean,period));
  // f->ls();
  //cout<<txtname<<endl;
  RooWorkspace *w = (RooWorkspace*)f->Get("");
  float nom_mean, nom_sigmaGau, nom_sigmaCB, nom_n,nom_a, nom_f;
  // w->Print();
  cout<<Form("mean_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)<<endl;
  nom_mean = (w->var(Form("mean_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  nom_sigmaCB = (w->var(Form("sigma_CB_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  nom_sigmaGau = (w->var(Form("sigma_Gau_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  nom_n = (w->var(Form("n_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  nom_a = (w->var(Form("alpha_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  nom_f = (w->var(Form("frac_G1_%s_%s_m%d_cat%d_%d",type2.c_str(),channel.c_str(),Mean,cat,period)))->getVal();
  //cout<<nom_sigmaCB<<" "<<nom_mean<<endl;  
  ///create tree

  TTree* SigTree1 = makeTTree_signal(txtname);
  

  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR) ;
  RooMsgService::instance().setSilentMode(true);
  ///define variables for fitting
  RooRealVar mH("mH", "mH", 115, 170, "GeV") ;
  RooRealVar weights("weights", "weights", -100, 100, "");

  ///build unbin data&signal distribution
  RooDataSet signal("signal", " ", RooArgSet(mH, weights), Import(*SigTree1), WeightVar(weights));

  //-------------------------------------------------------//
  // Siganl fit                                            //
  // Using Crystal ball plus 2Gaussian                     //
  // One Gaussian with the same mean, another to fit tail  //
  //-------------------------------------------------------//
  double sigd = nom_sigmaCB-0.05,sigu = nom_sigmaCB+0.05,md = nom_mean-3., mu = nom_mean+3.;
  //cout<<issigma<<endl;
  if(issigma) {md=nom_mean-0.0001; mu = nom_mean+0.0001;}
  else {sigd = nom_sigmaCB-0.000001; sigu=nom_sigmaCB+0.0000001;}
  RooRealVar sigma_CB("sigma_CB"," ",nom_sigmaCB , sigd,sigu); 
  RooRealVar alpha("alpha"," ",nom_a); // Alpha: Gaussian tail
  RooRealVar n("n"," ",nom_n); // n: normalization
  RooRealVar mean("mean", " ",nom_mean, md, mu);
  RooRealVar frac_G1("frac_G1"," ",nom_f);//fraction of Gaussian 
  RooRealVar sigma_Gau("sigma_Gau"," ",nom_sigmaGau);//Gaussian sigma
  sigma_Gau.setConstant(true);frac_G1.setConstant(true); n.setConstant(true);alpha.setConstant(true);
  //if(issigma)mean.setConstant(true);
  //if(!issigma) sigma_CB.setConstant(true);
  RooCBShape CBall("CBall"," ",mH,mean,sigma_CB,alpha,n);
  RooGaussian Gauss("Gauss"," ",mH, mean, sigma_Gau);
  RooAddPdf Sig_bin2("Sig_bin2"," ",RooArgList(CBall,Gauss),frac_G1);//signal PDF
  ///setting fitting range
  mH.setRange("sigFitRange", 115, 170);
  RooFitResult* r_sig = Sig_bin2.fitTo(signal, Save(kTRUE), Range("sigFitRange"),RooFit::PrintLevel(-1));
  RooRealVar *fit_mean = (RooRealVar*) r_sig->floatParsFinal().find("mean");
  RooRealVar *fit_sigma = (RooRealVar*) r_sig->floatParsFinal().find("sigma_CB");
  //cout<<fit_sigma->getVal()<<" "<<nom_sigmaCB<<" "<<fit_mean->getVal()<<" "<<nom_mean<<endl;
  *un_mean = (fit_mean->getVal()-nom_mean)/nom_mean;
  *un_sigma = (fit_sigma->getVal()-nom_sigmaCB)/nom_sigmaCB;

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
  signal.plotOn(xframe4,Binning(55), RooFit::Name("Sig_plot")) ;
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
  figname  = "plot/"+fin+vername+"/sigfit_"+ type + "_" + channel+ "_" + std::to_string(cat) + "_" + meanval + ".png";
  const char *fig = figname.c_str();
  c->Print(fig); 
  gPad->SetLogy();
  xframe4->Draw();
  leg4->Draw("same");
  figname  = "plot/"+fin+vername+"/sigfit_"+ type + "_" + channel+ "_" + std::to_string(cat) + "_" + meanval + "log.png";
  c->Print(figname.c_str()); 
  f->Close();
  delete f;
}

#endif
