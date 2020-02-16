#include <iostream>
#include "../interface/Maketree.h"
using namespace RooFit;
vector<float> fit_scale(string type,string fname,int bin)
{
    float REFITmll, lepPt[2],lepEta[2],puwei,genwei,mcwei,totSF,L1wei;
  //import the data
  TChain sig_ ("tZg");
  sig_.Add(Form("../../outfile/mc_%s_%s_HZg_*F_125GeV.root",fname.c_str(),type.c_str()));
  sig_.Add(Form("../../outfile/mc_%s_%s_HZg_*H_125GeV.root",fname.c_str(),type.c_str()));
    sig_.SetBranchAddress("REFITmll", &REFITmll);
    sig_.SetBranchAddress("lepPt", lepPt);
    sig_.SetBranchAddress("lepEta", lepEta);
    sig_.SetBranchAddress("genwei", &genwei);
    sig_.SetBranchAddress("mcwei",  &mcwei);
    sig_.SetBranchAddress("totSF",   &totSF);
    sig_.SetBranchAddress("puwei",   &puwei);
    sig_.SetBranchAddress("L1wei",   &L1wei);
    string signame,bkgname;
    signame = "scale/sig_"+fname+"_"+type+"_" +std::to_string(bin)+".txt";
    bkgname = "scale/bkg_"+fname+"_"+type+"_" +std::to_string(bin)+".txt";
    ofstream sigs(signame.c_str());
    ofstream bkgs(bkgname.c_str());
    for(Long64_t ev= 0; ev<sig_.GetEntriesFast();ev++)
    {
        sig_.GetEntry(ev);
        if(type=="ele")
        {
            if(bin%3==0&&fabs(lepEta[0])>0.8)continue;
            if(bin%3==1&&(fabs(lepEta[0])<=0.8||fabs(lepEta[0])>1.5))continue;
            if(bin%3==2&&(fabs(lepEta[0])<=1.5))continue;
            if(bin%4==0&&lepPt[0]>40.)continue;
            if(bin%4==1&&(lepPt[0]<=40.||lepPt[0]>50.))continue;
            if(bin%4==2&&(lepPt[0]<=50.||lepPt[0]>60.))continue;
            if(bin%4==3&&(lepPt[0]<=60.))continue;
            sigs<<REFITmll<<" "<<1.*mcwei*totSF*puwei*L1wei<<endl;
        }
        else
        {
           
                if(bin%3==0&&fabs(lepEta[0])>0.9)continue;
                if(bin%3==1&&(fabs(lepEta[0])<=0.9||fabs(lepEta[0])>1.4))continue;
                if(bin%3==2&&(fabs(lepEta[0])<=1.4))continue;
                if(bin%4==0&&lepPt[0]>40.)continue;
                if(bin%4==1&&(lepPt[0]<=40.||lepPt[0]>50.))continue;
                if(bin%4==2&&(lepPt[0]<=50.||lepPt[0]>60.))continue;
                if(bin%4==3&&(lepPt[0]<=60.))continue;
                sigs<<REFITmll<<" "<<1.*mcwei*totSF*puwei*L1wei<<endl;
            
        }
    }
    TTree* sig = makeTTree_signal(signame.c_str());
    sig->Print();
  TChain bkg_ ("tZg");
  if(type=="ele") bkg_.Add(Form("../../outfile/Data_%s_ele_EG.root",fname.c_str()));
  else if(type == "mu") bkg_.Add(Form("../../outfile/Data_%s_mu_Mu.root",fname.c_str()));
    bkg_.SetBranchAddress("REFITmll", &REFITmll);
    bkg_.SetBranchAddress("lepPt", lepPt);
    bkg_.SetBranchAddress("lepEta", lepEta);
    for(Long64_t ev= 0; ev<bkg_.GetEntriesFast();ev++)
    {
        bkg_.GetEntry(ev);
        if(type=="ele")
        {
            if(bin%3==0&&fabs(lepEta[0])>0.8)continue;
            if(bin%3==1&&(fabs(lepEta[0])<=0.8||fabs(lepEta[0])>1.5))continue;
            if(bin%3==2&&(fabs(lepEta[0])<=1.5))continue;
            if(bin%4==0&&lepPt[0]>40.)continue;
            if(bin%4==1&&(lepPt[0]<=40.||lepPt[0]>50.))continue;
            if(bin%4==2&&(lepPt[0]<=50.||lepPt[0]>60.))continue;
            if(bin%4==3&&(lepPt[0]<=60.))continue;
            bkgs<<REFITmll<<endl;
        }
        else
        {
            
            if(bin%3==0&&fabs(lepEta[0])>0.9)continue;
            if(bin%3==1&&(fabs(lepEta[0])<=0.9||fabs(lepEta[0])>1.4))continue;
            if(bin%3==2&&(fabs(lepEta[0])<=1.4))continue;
            if(bin%4==0&&lepPt[0]>40.)continue;
            if(bin%4==1&&(lepPt[0]<=40.||lepPt[0]>50.))continue;
            if(bin%4==2&&(lepPt[0]<=50.||lepPt[0]>60.))continue;
            if(bin%4==3&&(lepPt[0]<=60.))continue;
            bkgs<<REFITmll<<endl;
        }
    }
    TTree* bkg = makeTTree(bkgname.c_str());
    
    cout<<"import"<<endl;
  //build Z model
  RooRealVar mH("mH" ,"mH", 50, 120, "GeV");
  RooRealVar weights("weights" ,"weights", -5., 5., "");
  // RooRealVar eormu("eormu" ,"eormu", 10, 14, "GeV");
 
  RooDataSet Zmass_sig("Zmass_sig", "Zmass_sig", RooArgSet(mH,weights), Import(*sig),WeightVar(weights));
  RooDataSet Zmass_bkg("Zmass_bkg", "Zmass_bkg", RooArgSet(mH), Import(*bkg));
    cout<<"dataset"<<endl;
  RooRealVar bwMean("bwMean", "m_{Z^{0}}", 91.187);
  RooRealVar bwGamma("bwGamma", "#Gamma", 2.5,1.0,3.0);
  RooRealVar sg("sg", "sg", 4.99069e+00, 0.1, 10.);
  RooRealVar a("a", "a", 4.99069e+00, 0.1, 10.);
  RooRealVar n("n", "n", -0.5,2.0);
  RooRealVar mean("mean","mean",-10,10);
  RooCBShape CB("CB","CB",mH,mean,sg,a,n);
  RooRealVar f1("f1","f1",0.01,1.0);

  // RooRealVar mean2("mean2","mean2",0.,20);
  // RooRealVar sigma("sigma","sigma",0.1,10.);
  RooRealVar f2("f2","f2",0.000001,1.0000);

  RooGenericPdf RelBW("RelBW","1/( pow(mH*mH-bwMean*bwMean,2)+pow(mH,4)*pow(bwGamma/bwMean,2) )", RooArgSet(mH,bwMean,bwGamma) );

  RooFFTConvPdf *RelBWxCB_sig = new RooFFTConvPdf("RelBWxCB_sig","RelBWxCB_sig", mH, RelBW,CB);
  RooFFTConvPdf *RelBWxCB_bkg = new RooFFTConvPdf("RelBWxCB_bkg","RelBWxCB_bkg", mH, RelBW,CB);
    cout<<"build pdf"<<endl;
//   RooGaussian gauss("gauss","gauss",mH,mean2,sigma);
  RooFitResult* Zsig = RelBWxCB_sig->fitTo(Zmass_sig, Save(kTRUE));
  RooRealVar* sig_mean = (RooRealVar*) Zsig->floatParsFinal().find("mean");
  RooFitResult* Zbkg = RelBWxCB_bkg->fitTo(Zmass_bkg, Save(kTRUE));
  RooRealVar* bkg_mean = (RooRealVar*) Zbkg->floatParsFinal().find("mean");
    cout<<"fit "<<endl;
  //RooFitResult* GENZ = RelBWxCBxgauss->fitTo(Zmass, Save(kTRUE));
  RooPlot* xframe4 = mH.frame(50,120) ;
    
   Zmass_sig.plotOn(xframe4,Binning(70), RooFit::Name("Zmass_sig"),MarkerColor(TColor::GetColor("#FF7386"))) ;
   RelBWxCB_sig->plotOn(xframe4,RooFit::Name("RelBWxCB"),LineColor(TColor::GetColor("#FF7386")));
     RelBWxCB_sig->paramOn(xframe4,Layout(0.1,0.5,0.9));
    xframe4->Draw();
    gPad->Print(Form("plot/sig_%s_%s_%d.pdf",fname.c_str(),type.c_str(),bin));
    
    RooPlot* xframe5 = mH.frame(50,120) ;
  Zmass_bkg.plotOn(xframe5,Binning(70), RooFit::Name("Zmass_bkg"),MarkerColor(TColor::GetColor("#44CAFB"))) ;
   RelBWxCB_bkg->plotOn(xframe5,RooFit::Name("RelBWxCB"),LineColor(TColor::GetColor("#44CAFB")));

 
  RelBWxCB_bkg->paramOn(xframe5,Layout(0.1,0.5,0.9));
    cout<<"draw"<<endl;
  xframe5->Draw();
   gPad->Print(Form("plot/bkg_%s_%s_%d.pdf",fname.c_str(),type.c_str(),bin));
cout<<type<<" "<<bin<<endl;
cout<<"signal: "<<sig_mean->getVal()<<"\t bkg: "<<bkg_mean->getVal()<<" "<<sig_mean->getError()<<endl;
    vector<float> info;
    info.push_back((sig_mean->getVal()-bkg_mean->getVal())/91.187);
    info.push_back(sqrt(sig_mean->getError()*sig_mean->getError()+bkg_mean->getError()*bkg_mean->getError())/91.187);
    return info;
}
void get_refit_sc(string fname)
{
    TFile *f = new TFile(Form("%s.root",fname.c_str()),"recreate");
    f->cd();
    gStyle->SetOptStat(0);
    vector<float> ele_un,mu_un;
    float ele1[4],ele2[4],ele3[4],mu1[4],mu2[4],mu3[4];
    float elex[5] = {25.,40.,50.,60,200.};
    float mux[5] = {20.,40.,50.,60,200.};
    TH1F *gele_1 = new TH1F("gele_1","",4,elex);
    TH1F *gele_2 = new TH1F("gele_2","",4,elex);
    TH1F *gele_3 = new TH1F("gele_3","",4,elex);
    TH1F *gmu_1 = new TH1F("gmu_1","",4,mux);
    TH1F *gmu_2 = new TH1F("gmu_2","",4,mux);
    TH1F *gmu_3 = new TH1F("gmu_3","",4,mux);
  for (int i = 0 ; i < 12 ; i++)
  {
      ele_un.clear();mu_un.clear();
   ele_un = fit_scale("ele",fname,i);
   mu_un = fit_scale("mu",fname,i);
      if(i%3==0)gele_1->SetBinContent(i/3+1,ele_un[0]);
      if(i%3==1)gele_2->SetBinContent(i/3+1,ele_un[0]);
      if(i%3==2)gele_3->SetBinContent(i/3+1,ele_un[0]);
      if(i%3==0)gele_1->SetBinError(i/3+1,0.);
      if(i%3==1)gele_2->SetBinError(i/3+1,0.);
      if(i%3==2)gele_3->SetBinError(i/3+1,0.);
      if(i%3==0)gmu_1->SetBinError(i/3+1,0.);
      if(i%3==1)gmu_2->SetBinError(i/3+1,0.);
      if(i%3==2)gmu_3->SetBinError(i/3+1,0.);
      if(i%3==0)gmu_1->SetBinContent(i/3+1,mu_un[0]);
      if(i%3==1)gmu_2->SetBinContent(i/3+1,mu_un[0]);
      if(i%3==2)gmu_3->SetBinContent(i/3+1,mu_un[0]);
//      out<<fname<<"/ele "<<" bin:"<<i<<" "<<ele_un[0]<<" "<<ele_un[1]<<endl;
//      out<<fname<<"/mu "<<" bin:"<<i<<" "<<mu_un[0]<<" "<<mu_un[1]<<endl;
  }
    
//    gStyle->SetMakerStyle(25);
    gele_1->SetLineColor(kRed);
    gele_1->SetMarkerColor(kRed);
    gmu_1->SetLineColor(kRed);
    gmu_1->SetMarkerColor(kRed);
    gele_2->SetMarkerColor(kBlue);
    gele_2->SetLineColor(kBlue);
    gmu_2->SetMarkerColor(kBlue);
    gmu_2->SetLineColor(kBlue);
    gele_3->SetMarkerColor(kBlack);
    gele_3->SetLineColor(kBlack);
    gmu_3->SetMarkerColor(kBlack);
    gmu_3->SetLineColor(kBlack);
    gele_1->SetMarkerStyle(25);
    gele_2->SetMarkerStyle(25);
    gele_3->SetMarkerStyle(25);
    gmu_1->SetMarkerStyle(25);
    gmu_2->SetMarkerStyle(25);
    gmu_3->SetMarkerStyle(25);
    gele_1->SetMarkerSize(1);
    gele_2->SetMarkerSize(1);
    gele_3->SetMarkerSize(1);
    gmu_1->SetMarkerSize(1);
    gmu_2->SetMarkerSize(1);
    gmu_3->SetMarkerSize(1);
    gele_1->Write();
    gele_2->Write();
    gele_3->Write();
    gmu_1->Write();
    gmu_2->Write();
    gmu_3->Write();
//    gele_1->Draw("ep");
    gele_1->SetTitle("");
    gele_1->GetXaxis()->SetTitle("Electron pT(GeV)");
//    gele_1->GetXaxis()->SetTitleOffSet(1.2);
    gele_1->GetYaxis()->SetTitle("m_{Data}-m_{MC}/m_{PDG}");
    gele_1->SetMaximum(0.01);
    gele_1->SetMinimum(-0.01);
    gele_1->Draw("ep");
    gele_2->Draw("epsame");
    gele_3->Draw("epsame");
    TLegend *l = new TLegend(.6,.1,.9,.3);
    l->AddEntry(gele_1,"0<|#eta|<0.8");
    l->AddEntry(gele_2,"0.8<|#eta|<1.5");
    l->AddEntry(gele_3,"1.5<|#eta|<2.5");
    l->Draw();
    gPad->Print(Form("scale/%s_ele.pdf",fname.c_str()));
//    gmu_1->Draw("p");
    gmu_1->SetTitle("");
    gmu_1->GetXaxis()->SetTitle("Muon pT(GeV)");
//    gmu_1->GetXaxis()->SetTitleOffset(1.4);
    gmu_1->SetMaximum(0.01);
    gmu_1->SetMinimum(-0.01);
    gmu_1->GetYaxis()->SetTitle("m_{Data}-m_{MC}/m_{PDG}");
    gmu_1->Draw("ep");
    gmu_2->Draw("epsame");
    gmu_3->Draw("epsame");
    TLegend *l2 = new TLegend(.6,.1,.9,.3);
    l2->AddEntry(gmu_1,"0<|#eta|<0.9");
    l2->AddEntry(gmu_2,"0.9<|#eta|<1.4");
    l2->AddEntry(gmu_3,"1.4<|#eta|<2.4");
    l2->Draw();
     gPad->Print(Form("scale/%s_mu.pdf",fname.c_str()));
}
