#include "readMVA.h"
#include "/afs/cern.ch/work/m/milee/MYcode/plugin/tdrstyle.C"
#include "/afs/cern.ch/work/m/milee/MYcode/plugin/CMS_lumi.C"
void getMVAuncs(string MVA, string type,int period)
{
  //setTDRStyle();
  string fname;
  string addwei;
  if(period==2016)addwei="*L1wei";
  if(period==2017)addwei="*L1wei*ptwei";
  if(period==2018)addwei="*ptwei";
  TCanvas *c = new TCanvas("c", "c", 800,600);
  c->cd();
  TLegend *l = new TLegend(.7,.7,.9,.9);
  //l->SetNColumn(2);
  if(period==2016) fname = "Legacy16_newMVA"; 
  else if(period==2017) fname = "Rereco17_newMVA"; 
  else if(period==2018) fname = "Rereco18_newMVA";
  string color[]= {"#F44336","#E91E63","#9C27B0","#673AB7","#3F51B5","#2196F3","#03A9F4","#00BCD4","#009688","#4CAF50","#8BC34A","#CDDC39","#FFEB3B","#FFC107","#FF9800","#FF5722","#795548","#9E9E9E","#607D8B"};
  float MVAunc[12] = {3.,3,3,3,3,3,3,3,3,3,3,3};
 float phoresunc[12] = 
 {
 	0.5,1.,0.5,2.,
 	0.5,0.5,0.5,1.0,
 	0.,1.,0.,1,
 };
 float phoR9unc[12]=
 {
	0.,0.1,0.1,0.4,
 	0.3,0.,0.3,0.3,
 	0.1,0.1,0.1,0.1,
 };
  TChain sig_nom(MVA.c_str());
  TChain bkg_nom(MVA.c_str());
  // sig_nom.Add(Form("../../outfile/mc_%s_%s_HZg_*H_125GeV.root",fname.c_str(),type.c_str()));
  // sig_nom.Add(Form("../../outfile/mc_%s_%s_HZg_*F_125GeV.root",fname.c_str(),type.c_str()));
  if(period==2016)
    {
      bkg_nom.Add(Form("../../outfile/mc_%s_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
      bkg_nom.Add(Form("../../outfile/mc_%s_%s_DYJetsToLL_m50_aMCatNLO.root",fname.c_str(),type.c_str()));
    }
  else
    {
      bkg_nom.Add(Form("../../outfile/mc_%sv2_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
      bkg_nom.Add(Form("../../outfile/mc_%sv2_%s_DYJetsToLL_m50_aMCatNLO.root",fname.c_str(),type.c_str()));
    }
  TH1F *hsig_nom,*hbkg_nom;
  if(MVA=="tVBF")
    {
      hsig_nom= new TH1F("hsig_nom","",24,-0.9,0.3);
      hbkg_nom= new TH1F("hbkg_nom","",24,-0.9,0.3);
      sig_nom.Draw("HZgVBF>>hsig_nom",Form("(HZgVBF!=-99)*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
      bkg_nom.Draw("HZgVBF>>hbkg_nom",Form("(HZgVBF!=-99)*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
    }
  else if(MVA=="tMVA")
    {
      hsig_nom= new TH1F("hsig_nom","",40,-0.6,0.4);
      hbkg_nom= new TH1F("hbkg_nom","",40,-0.6,0.4);
      sig_nom.Draw("HZgMVA>>hsig_nom",Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
      bkg_nom.Draw("HZgMVA>>hbkg_nom",Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
    }
  gStyle->SetOptStat(0);
  hsig_nom->SetLineColor(kBlack);
  hbkg_nom->SetLineColor(kBlack);
  hbkg_nom->SetLineStyle(2);
  hsig_nom->SetLineWidth(2);
  hbkg_nom->SetLineWidth(2);
  //hsig_nom->SetMaximum(1000);
  //    hsig_nom->SetMinimum(0);
  hbkg_nom->GetXaxis()->SetTitle(MVA.c_str());
  hbkg_nom->GetYaxis()->SetTitle("Events");
  //  hsig_nom->Scale(500.);
  hbkg_nom->Draw("hist");
  hsig_nom->Draw("histsame");
  l->AddEntry(hsig_nom,"nom_sig","l");
  l->AddEntry(hbkg_nom,"nom_bkg","l");
  vector<TH1F*> hsig_un;hsig_un.clear();
  vector<TH1F*> hbkg_un;hsig_un.clear();
  double max_sig[48] = {0};
  double unc_sig[48] = {0};
  double max_bkg[48] = {0};
  double unc_bkg[48] = {0};
  if(MVA=="tVBF")
    {
      for(int j = 0 ; j < 4; j++)
	{
	  TChain sig_jet(MVA.c_str());
	  TChain bkg_jet(MVA.c_str());
	  // sig_jet.Add(Form("../../outfile/uncer/mc_%s_jet%d_%s_HZg_*H_125GeV.root",fname.c_str(),j,type.c_str()));
	  // sig_jet.Add(Form("../../outfile/uncer/mc_%s_jet%d_%s_HZg_*F_125GeV.root",fname.c_str(),j,type.c_str()));
	  bkg_jet.Add(Form("../../outfile/uncer/mc_%s_jet%d_%s_Zg_aMCatNLO.root",fname.c_str(),j,type.c_str()));
	  bkg_jet.Add(Form("../../outfile/uncer/mc_%s_jet%d_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),j,type.c_str()));
	  hsig_un.push_back(new TH1F(Form("hsig_un[%d]",j),"",24,-0.9,0.3));
	  hbkg_un.push_back(new TH1F(Form("hbkg_un[%d]",j),"",24,-0.9,0.3));
	  sig_jet.Draw(Form("HZgVBF>>hsig_un[%d]",j),Form("(HZgVBF!=-99)*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
	  bkg_jet.Draw(Form("HZgVBF>>hbkg_un[%d]",j),Form("(HZgVBF!=-99)*mcwei*genwei*totSF*puwei%s",addwei.c_str()));

	  for(int b = 1; b < 25; b++)
	    {
	      if(fabs(hsig_un[j]->GetBinContent(b))>fabs(hsig_nom->GetBinContent(b))&&fabs((hsig_un[j]->GetBinContent(b)-hsig_nom->GetBinContent(b)))>max_sig[b-1])max_sig[b-1] = fabs(hsig_un[j]->GetBinContent(b)-hsig_nom->GetBinContent(b));
	      if(fabs(hbkg_un[j]->GetBinContent(b))>fabs(hbkg_nom->GetBinContent(b))&&fabs(hbkg_un[j]->GetBinContent(b)-hbkg_nom->GetBinContent(b))>max_bkg[b-1])max_bkg[b-1] = fabs(hbkg_un[j]->GetBinContent(b)-hbkg_nom->GetBinContent(b));

	      if(j%2==1)
		{
		  unc_sig[b-1] += max_sig[b-1]*max_sig[b-1];
		  unc_bkg[b-1] += max_bkg[b-1]*max_bkg[b-1];
		  max_bkg[b-1] = 0.;
		  max_sig[b-1] = 0.;
		}
	    }
	  hsig_un[j]->SetLineColor(TColor::GetColor(color[j].c_str()));
	  hbkg_un[j]->SetLineColor(TColor::GetColor(color[j].c_str()));
	  hbkg_un[j]->SetLineStyle(2);
	  hsig_un[j]->SetLineWidth(2);
	  hbkg_un[j]->SetLineWidth(2);
	  hsig_un[j]->Scale(500.);
	  hsig_un[j]->Draw("histsame");
	  hbkg_un[j]->Draw("histsame");
	  l->AddEntry(hsig_un[j],Form("sig_VBF_%d",j),"l");
	  l->AddEntry(hbkg_un[j],Form("bkg_VBF_%d",j),"l");
	}
    }
  if(MVA=="tMVA")
    {
      //electron scale/res
      if(type=="ele"){
	for(int j = 0 ; j < 16; j++)
	  {
	    TChain sig_ele(MVA.c_str());
	    TChain bkg_ele(MVA.c_str());
	    hsig_un.push_back(new TH1F(Form("hsig_un[%d]",j),"",40,-0.6,0.4));
	    hbkg_un.push_back(new TH1F(Form("hbkg_un[%d]",j),"",40,-0.6,0.4));
	    if(j<10){

	      // sig_ele.Add(Form("../../outfile/uncer/mc_%s_ele%d_%s_HZg_*H_125GeV.root",fname.c_str(),j,type.c_str()));
	      // sig_ele.Add(Form("../../outfile/uncer/mc_%s_ele%d_%s_HZg_*F_125GeV.root",fname.c_str(),j,type.c_str()));
	      bkg_ele.Add(Form("../../outfile/uncer/mc_%s_ele%d_%s_Zg_aMCatNLO.root",fname.c_str(),j,type.c_str()));
	      bkg_ele.Add(Form("../../outfile/uncer/mc_%s_ele%d_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),j,type.c_str()));
	      sig_ele.Draw(Form("HZgMVA>>hsig_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
	      bkg_ele.Draw(Form("HZgMVA>>hbkg_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
	    }
	    else 
	      	      {
		sig_ele.Add(Form("../../outfile/mc_%s_%s_HZg_*H_125GeV.root",fname.c_str(),type.c_str()));
		sig_ele.Add(Form("../../outfile/mc_%s_%s_HZg_*F_125GeV.root",fname.c_str(),type.c_str()));
		if(period==2016)
		  {bkg_ele.Add(Form("../../outfile/mc_%s_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		    bkg_ele.Add(Form("../../outfile/mc_%s_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),type.c_str()));}
		else 
		  {bkg_ele.Add(Form("../../outfile/mc_%sv2_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		    bkg_ele.Add(Form("../../outfile/mc_%sv2_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),type.c_str()));}
		float mllgptdmllg,cosTheta, costheta, Phi,gdmllg,lepEta1,lepEta2,phoEta,phoMVA,phoR9,Zdmllg,ZgPTt,dEtaZg,phores,mllmllg, dRlg,maxdRlg,puwei,mcwei,genwei,totSF,ptwei,L1wei;
		sig_ele.SetBranchAddress("mllgptdmllg", &mllgptdmllg);
		bkg_ele.SetBranchAddress("mllgptdmllg", &mllgptdmllg);
		sig_ele.SetBranchAddress("costheta",    &costheta);
		bkg_ele.SetBranchAddress("costheta",    &costheta);
		sig_ele.SetBranchAddress("cosTheta",    &cosTheta);
		bkg_ele.SetBranchAddress("cosTheta",    &cosTheta);
		sig_ele.SetBranchAddress("Phi",         &Phi);
		bkg_ele.SetBranchAddress("Phi",         &Phi);
		sig_ele.SetBranchAddress("lepEta1",     &lepEta1);
		bkg_ele.SetBranchAddress("lepEta1",     &lepEta1);
		sig_ele.SetBranchAddress("lepEta2",     &lepEta2);
		bkg_ele.SetBranchAddress("lepEta2",     &lepEta2);
		sig_ele.SetBranchAddress("phoEta",      &phoEta);
		bkg_ele.SetBranchAddress("phoEta",      &phoEta);
		sig_ele.SetBranchAddress("phoMVA",      &phoMVA);
		bkg_ele.SetBranchAddress("phoMVA",      &phoMVA);
		sig_ele.SetBranchAddress("phoR9",       &phoR9);
		bkg_ele.SetBranchAddress("phoR9",       &phoR9);
		sig_ele.SetBranchAddress("dRlg",        &dRlg);
		bkg_ele.SetBranchAddress("dRlg",        &dRlg);
		sig_ele.SetBranchAddress("maxdRlg",     &maxdRlg);
		bkg_ele.SetBranchAddress("maxdRlg",     &maxdRlg);
		sig_ele.SetBranchAddress("phores",      &phores);
		bkg_ele.SetBranchAddress("phores",      &phores);
		sig_ele.SetBranchAddress("mcwei",       &mcwei);
		bkg_ele.SetBranchAddress("mcwei",       &mcwei);
		if(period!=2018)sig_ele.SetBranchAddress("L1wei",		  &L1wei);
		if(period!=2018)bkg_ele.SetBranchAddress("L1wei",		  &L1wei);
		if(period!=2016)sig_ele.SetBranchAddress("ptwei",		  &ptwei);
		if(period!=2016)bkg_ele.SetBranchAddress("ptwei",		  &ptwei);
		sig_ele.SetBranchAddress("puwei",       &puwei);
		bkg_ele.SetBranchAddress("puwei",     &puwei);
		sig_ele.SetBranchAddress("genwei",      &genwei);
		bkg_ele.SetBranchAddress("genwei",      &genwei);
		sig_ele.SetBranchAddress("totSF",       &totSF);
		bkg_ele.SetBranchAddress("totSF",       &totSF);
		for(Long64_t ev= 0 ; ev< sig_ele.GetEntriesFast(); ev++)
		  {
		    sig_ele.GetEntry(ev);
		    float HZgMVA = -99.;
		    float shifted;
		    if(period==2016&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[0]*0.01 :MVAunc[1]*0.01;
		    if(period==2016&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[0]*0.01 :phoresunc[1]*0.01;
		    if(period==2016&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[0]*0.01 :phoR9unc[1]*0.01;
		    if(period==2017&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[4]*0.01 :MVAunc[5]*0.01;
		    if(period==2017&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[4]*0.01 :phoresunc[5]*0.01;
		    if(period==2017&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[4]*0.01 :phoR9unc[5]*0.01;
		    if(period==2018&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[8]*0.01 :MVAunc[9]*0.01;
		    if(period==2018&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[8]*0.01 :phoresunc[9]*0.01;
		    if(period==2018&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[8]*0.01 :phoR9unc[9]*0.01;
		    if(j==10)HZgMVA = readMVA(period,phoR9,phoMVA+0.03, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==11)HZgMVA = readMVA(period,phoR9,phoMVA-0.03, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==12)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.+shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==13)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.-shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==14)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==15)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    hsig_un[j]->Fill(HZgMVA,1.*mcwei*genwei*totSF*puwei*ptwei*L1wei);
		  }
		for(Long64_t ev= 0 ; ev< bkg_ele.GetEntriesFast(); ev++)
		  {
		    bkg_ele.GetEntry(ev);
		    float HZgMVA = -99.;
		    if(period==2016)ptwei=1.;
		    if(period==2018)L1wei=1.;
		    float shifted;
		    if(period==2016&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[0]*0.01 :MVAunc[1]*0.01;
		    else if(period==2016&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[0]*0.01 :phoresunc[1]*0.01;
		    else if(period==2016&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[0]*0.01 :phoR9unc[1]*0.01;
		    if(period==2017&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[4]*0.01 :MVAunc[5]*0.01;
		    else if(period==2017&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[4]*0.01 :phoresunc[5]*0.01;
		    else if(period==2017&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[4]*0.01 :phoR9unc[5]*0.01;
		    if(period==2018&&j<12) shifted= fabs(phoEta)<1.4442 ? MVAunc[8]*0.01 :MVAunc[9]*0.01;
		    else if(period==2018&&j<14) shifted= fabs(phoEta)<1.4442 ? phoresunc[8]*0.01 :phoresunc[9]*0.01;
		    else if(period==2018&&j<16) shifted= fabs(phoEta)<1.4442 ? phoR9unc[8]*0.01 :phoR9unc[9]*0.01;
		    if(j==10)HZgMVA = readMVA(period,phoR9,phoMVA+shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==11)HZgMVA = readMVA(period,phoR9,phoMVA-shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==12)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.+shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==13)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.-shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==14)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==15)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    hbkg_un[j]->Fill(HZgMVA,1.*mcwei*genwei*totSF*puwei*ptwei*L1wei);
		  }
	      }

	 //    else
	 //      {
          
		// // sig_ele.Add(Form("../../outfile/mc_%s_r9_%s_HZg_*H_125GeV.root",fname.c_str(),type.c_str()));
		// // sig_ele.Add(Form("../../outfile/mc_%s_r9_%s_HZg_*F_125GeV.root",fname.c_str(),type.c_str()));
		// bkg_ele.Add(Form("../../outfile/mc_%s_r9_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		// bkg_ele.Add(Form("../../outfile/mc_%s_r9_%s_DYJetsToLL_m50_aMCatNLO.root",fname.c_str(),type.c_str()));
          
		// sig_ele.Draw(Form("HZgMVA>>hsig_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
		// bkg_ele.Draw(Form("HZgMVA>>hbkg_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
	 //      }

	    for(int b = 1; b < 41; b++)
	      {
		if(hsig_un[j]->GetBinContent(b)>hsig_nom->GetBinContent(b)&&(hsig_un[j]->GetBinContent(b)-hsig_nom->GetBinContent(b))>max_sig[b-1])max_sig[b-1] = hsig_un[j]->GetBinContent(b)-hsig_nom->GetBinContent(b);
		if(hbkg_un[j]->GetBinContent(b)>hbkg_nom->GetBinContent(b)&&(hbkg_un[j]->GetBinContent(b)-hbkg_nom->GetBinContent(b))>max_bkg[b-1])max_bkg[b-1] = hbkg_un[j]->GetBinContent(b)-hbkg_nom->GetBinContent(b);
		if(j%2==1)
		  {
		    unc_sig[b-1] += max_sig[b-1]*max_sig[b-1];
		    unc_bkg[b-1] += max_bkg[b-1]*max_bkg[b-1];
		    max_bkg[b-1] = 0.;
		    max_sig[b-1] = 0.;
		  }
	      }
	  }
      }
      else 
	{
	  for(int j = 0; j<10; j++)
	    {
	      TChain sig_mu(MVA.c_str());
	      TChain bkg_mu(MVA.c_str());
	      hsig_un.push_back(new TH1F(Form("hsig_un[%d]",j),"",40,-0.6,0.4));
	      hbkg_un.push_back(new TH1F(Form("hbkg_un[%d]",j),"",40,-0.6,0.4 ));
	      if(j<4){
		bkg_mu.Add(Form("../../outfile/uncer/mc_%s_mu%d_un2_0_%s_Zg_aMCatNLO.root",fname.c_str(),j,type.c_str()));
		bkg_mu.Add(Form("../../outfile/uncer/mc_%s_mu%d_un2_0_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),j,type.c_str()));
		sig_mu.Draw(Form("HZgMVA>>hsig_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
		bkg_mu.Draw(Form("HZgMVA>>hbkg_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
	      }
	 //      else if (j==4)
		// {
		//   bkg_mu.Add(Form("../../outfile/mc_%s_r9_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		//   bkg_mu.Add(Form("../../outfile/mc_%s_r9_%s_DYJetsToLL_m50_aMCatNLO.root",fname.c_str(),type.c_str()));
		//   bkg_mu.Draw(Form("HZgMVA>>hbkg_un[%d]",j),Form("1.*mcwei*genwei*totSF*puwei%s",addwei.c_str()));
		// }
	      else 
		{
		  sig_mu.Add(Form("../../outfile/mc_%s_%s_HZg_*H_125GeV.root",fname.c_str(),type.c_str()));
		  sig_mu.Add(Form("../../outfile/mc_%s_%s_HZg_*F_125GeV.root",fname.c_str(),type.c_str()));
		  if(period==2016)
		    {
bkg_mu.Add(Form("../../outfile/mc_%s_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		  bkg_mu.Add(Form("../../outfile/mc_%s_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),type.c_str()));
		    }
		  else
		    {bkg_mu.Add(Form("../../outfile/mc_%sv2_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
		    bkg_mu.Add(Form("../../outfile/mc_%sv2_%s_DYJetsToLL_m50_aMCatNLO*.root",fname.c_str(),type.c_str()));}
		  float mllgptdmllg,cosTheta, costheta, Phi,gdmllg,lepEta1,lepEta2,phoEta,phoMVA,phoR9,Zdmllg,ZgPTt,dEtaZg,phores,mllmllg, dRlg,maxdRlg,puwei,mcwei,genwei,totSF,ptwei,L1wei;
		  sig_mu.SetBranchAddress("mllgptdmllg", &mllgptdmllg);
		  bkg_mu.SetBranchAddress("mllgptdmllg", &mllgptdmllg);
		  sig_mu.SetBranchAddress("costheta",    &costheta);
		  bkg_mu.SetBranchAddress("costheta",    &costheta);
		  sig_mu.SetBranchAddress("cosTheta",    &cosTheta);
		  bkg_mu.SetBranchAddress("cosTheta",    &cosTheta);
		  sig_mu.SetBranchAddress("Phi",         &Phi);
		  bkg_mu.SetBranchAddress("Phi",         &Phi);
		  sig_mu.SetBranchAddress("lepEta1",     &lepEta1);
		  bkg_mu.SetBranchAddress("lepEta1",     &lepEta1);
		  sig_mu.SetBranchAddress("lepEta2",     &lepEta2);
		  bkg_mu.SetBranchAddress("lepEta2",     &lepEta2);
		  sig_mu.SetBranchAddress("phoEta",      &phoEta);
		  bkg_mu.SetBranchAddress("phoEta",      &phoEta);
		  sig_mu.SetBranchAddress("phoMVA",      &phoMVA);
		  bkg_mu.SetBranchAddress("phoMVA",      &phoMVA);
		  sig_mu.SetBranchAddress("phoR9",       &phoR9);
		  bkg_mu.SetBranchAddress("phoR9",       &phoR9);
		  sig_mu.SetBranchAddress("dRlg",        &dRlg);
		  bkg_mu.SetBranchAddress("dRlg",        &dRlg);
		  sig_mu.SetBranchAddress("maxdRlg",     &maxdRlg);
		  bkg_mu.SetBranchAddress("maxdRlg",     &maxdRlg);
		  sig_mu.SetBranchAddress("phores",      &phores);
		  bkg_mu.SetBranchAddress("phores",      &phores);
		  sig_mu.SetBranchAddress("mcwei",       &mcwei);
		  bkg_mu.SetBranchAddress("mcwei",       &mcwei);
		  sig_mu.SetBranchAddress("puwei",       &puwei);
		  bkg_mu.SetBranchAddress("puwei",       &puwei);
		 if(period!=2018)sig_mu.SetBranchAddress("L1wei",		  &L1wei);
		if(period!=2018)bkg_mu.SetBranchAddress("L1wei",		  &L1wei);
		if(period!=2016)sig_mu.SetBranchAddress("ptwei",		  &ptwei);
		if(period!=2016)bkg_mu.SetBranchAddress("ptwei",		  &ptwei);
		  sig_mu.SetBranchAddress("genwei",      &genwei);
		  bkg_mu.SetBranchAddress("genwei",      &genwei);
		  sig_mu.SetBranchAddress("totSF",       &totSF);
		  bkg_mu.SetBranchAddress("totSF",       &totSF);
		  for(Long64_t ev= 0 ; ev< sig_mu.GetEntriesFast(); ev++)
		    {
		      sig_mu.GetEntry(ev);
		      float HZgMVA = -99.;
		      if(period==2016)ptwei=1.;
		      if(period==2018)L1wei=1.;
		      float shifted;
		      if(period==2016&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[0]*0.01 :MVAunc[1]*0.01;
		    if(period==2016&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[0]*0.01 :phoresunc[1]*0.01;
		    if(period==2016&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[0]*0.01 :phoR9unc[1]*0.01;
		    if(period==2017&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[4]*0.01 :MVAunc[5]*0.01;
		    if(period==2017&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[4]*0.01 :phoresunc[5]*0.01;
		    if(period==2017&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[4]*0.01 :phoR9unc[5]*0.01;
		    if(period==2018&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[8]*0.01 :MVAunc[9]*0.01;
		    if(period==2018&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[8]*0.01 :phoresunc[9]*0.01;
		    if(period==2018&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[8]*0.01 :phoR9unc[9]*0.01;
		    if(j==4)HZgMVA = readMVA(period,phoR9,phoMVA+shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==5)HZgMVA = readMVA(period,phoR9,phoMVA-shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==6)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.+shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==7)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.-shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==8)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==9)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		      hsig_un[j]->Fill(HZgMVA,1.*mcwei*genwei*totSF*puwei*L1wei*ptwei);
		    }
		  for(Long64_t ev= 0 ; ev< bkg_mu.GetEntriesFast(); ev++)
		    {
		      bkg_mu.GetEntry(ev);
		      float HZgMVA = -99.;
		      if(period==2016)ptwei=1.;
		      if(period==2018)L1wei=1.;
		       float shifted;
		      if(period==2016&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[0]*0.01 :MVAunc[1]*0.01;
		    if(period==2016&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[0]*0.01 :phoresunc[1]*0.01;
		    if(period==2016&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[0]*0.01 :phoR9unc[1]*0.01;
		    if(period==2017&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[4]*0.01 :MVAunc[5]*0.01;
		    if(period==2017&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[4]*0.01 :phoresunc[5]*0.01;
		    if(period==2017&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[4]*0.01 :phoR9unc[5]*0.01;
		    if(period==2018&&j<6) shifted= fabs(phoEta)<1.4442 ? MVAunc[8]*0.01 :MVAunc[9]*0.01;
		    if(period==2018&&j<8) shifted= fabs(phoEta)<1.4442 ? phoresunc[8]*0.01 :phoresunc[9]*0.01;
		    if(period==2018&&j<10) shifted= fabs(phoEta)<1.4442 ? phoR9unc[8]*0.01 :phoR9unc[9]*0.01;
		    if(j==4)HZgMVA = readMVA(period,phoR9,phoMVA+shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==5)HZgMVA = readMVA(period,phoR9,phoMVA-shifted, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==6)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.+shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==7)HZgMVA = readMVA(period,phoR9,phoMVA, phores*(1.-shifted),costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==8)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		    if(j==9)HZgMVA = readMVA(period,phoR9*(1.-shifted),phoMVA, phores,costheta,cosTheta, mllgptdmllg, lepEta1, lepEta2, phoEta, Phi,dRlg,maxdRlg);
		      hbkg_un[j]->Fill(HZgMVA,1.*mcwei*genwei*totSF*puwei*L1wei*ptwei);
		    }
		}
	    }
	}
     
    }
  string fsigout = "MVA/sig_"+MVA+"_"+type + "_"+ std::to_string(period)+".txt";
  string fbkgout = "MVA/bkg_"+MVA+"_"+type + "_"+std::to_string(period)+".txt";
  ofstream sig(fsigout.c_str());
  ofstream bkg(fbkgout.c_str());
  for(int i = 0; i < 40; i++)
    {
      // cout<<sqrt(unc_sig[i])<<endl;
      sig<<sqrt(unc_sig[i])<<endl;
      bkg<<sqrt(unc_bkg[i])<<endl;
    }
  extraText  = "Preliminary";
  string lumi;
  l->Draw();
  if(period==2016) lumi= "35.5";
  if(period==2017) lumi= "41.8";
  if(period==2018) lumi= "58.8";
  lumi_13TeV = lumi+"fb^{-1}";
  //  extraText  = "In progress";
  //lumi_13TeV = "35.9fb^{-1}";
  CMS_lumi(c, 4, 0);
  // string outname = MVA+"_"+type + "_"+std::to_string(period)+".pdf";
  // c->Print(outname.c_str());
}
void getMVAunc()
{
  //getMVAuncs("tVBF","ele",2016);
  //getMVAuncs("tMVA","ele",2016);
  //getMVAuncs("tVBF","mu",2016);
  //getMVAuncs("tMVA","mu",2016);
  getMVAuncs("tVBF","ele",2017);
  getMVAuncs("tMVA","ele",2017);
  getMVAuncs("tVBF","mu",2017);
  getMVAuncs("tMVA","mu",2017);
  getMVAuncs("tVBF","ele",2018);
  getMVAuncs("tMVA","ele",2018);
  getMVAuncs("tVBF","mu",2018);
  getMVAuncs("tMVA","mu",2018);
}
