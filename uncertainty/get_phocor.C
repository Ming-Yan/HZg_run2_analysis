void chi2scan(int period, string type, string var, string EEEB, int ntry=200,float trys=0.001)
{
  gROOT->ProcessLine( "gErrorIgnoreLevel = 1001;");

  string fname;
  if(period==2016)fname = "Legacy16_newMVA";
  else if(period==2017)fname = "Rereco17_newMVAv2";
  else if(period==2018)fname = "Rereco18_newMVAv2";
  string ptype = (type=="ele") ? "ele_EG" : "mu_Mu";
  //input files
  TChain bkg("tMVA"); 
  bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_DYJetsToLL_m50_aMCatNLO.root",fname.c_str(),type.c_str()));
  bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_Zg_aMCatNLO.root",fname.c_str(),type.c_str()));
  bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_TT_aMCatNLO.root",fname.c_str(),type.c_str()));
  bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_%s_Zg_EWK.root",fname.c_str(),type.c_str()));
  TFile *f = TFile::Open(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_%s.root",fname.c_str(),ptype.c_str()));
  TTree *t =(TTree*)f->Get("tMVA");
  float puwei, genwei, mcwei, totSF, L1wei, ptwei;//weights
  float phoPt, phores,phoEta,phoMVA,phoR9;

  // bkg.SetBranchAddress("phoPt",	&phoPt);
  bkg.SetBranchAddress("phoMVA",	&phoMVA);
  bkg.SetBranchAddress("phores",	&phores);
  bkg.SetBranchAddress("phoR9",	&phoR9);
  bkg.SetBranchAddress("phoEta",	&phoEta);
  bkg.SetBranchAddress("puwei",	&puwei);
  bkg.SetBranchAddress("genwei",	&genwei);
  bkg.SetBranchAddress("mcwei",	&mcwei);
  bkg.SetBranchAddress("totSF",	&totSF);
  bkg.SetBranchAddress("L1wei",	&L1wei);
  bkg.SetBranchAddress("ptwei",	&ptwei);
  vector<TH1F*> hmc,hd;hmc.clear();hd.clear();
  vector<double> chi2,res,step;chi2.clear();res.clear();step.clear();
  string weight;
  if(period ==2016) weight= "*L1wei";
  else if(period==2017)weight = "*L1wei*ptwei";
  else weight= "*ptwei";
  for(int i = 0 ; i < ntry+1; i++)
    {
      if(var=="phoMVA")
	{
	  hmc.push_back(new TH1F(Form("hmc[%d]",i),"",24,-0.08,1));
	  hd.push_back(new TH1F(Form("hd[%d]",i),"",24,-0.08,1));
	  bkg.Draw(Form("phoMVA*%.2f>>hmc[%d]",float(1.-trys*i),i),Form("(fabs(phoEta)<1.4442)*mcwei*genwei*puwei*totSF%s",weight.c_str()));
	  t->Draw(Form("phoMVA*%.2f>>hd[%d]",float(1.-trys*i),i),"(fabs(phoEta)<1.4442)");
			
	}
      else if(EEEB=="EE"&&var=="phoMVA")
	{
	  hmc.push_back(new TH1F(Form("hmc[%d]",i),"",14,-0.4,1));
	  hd.push_back(new TH1F(Form("hd[%d]",i),"",14,-0.4,1));
	  bkg.Draw(Form("phoMVA*%.2f>>hmc[%d]",float(trys*i+0.9),i),Form("(fabs(phoEta)>1.566)*mcwei*genwei*puwei*totSF%s",weight.c_str()));
	  t->Draw(Form("phoMVA>>hd[%d]",i),"(fabs(phoEta)>1.566)");
	}
      else 
	{
	  hmc.push_back(new TH1F(Form("hmc[%d]",i),"",35,0.3,1.));
	  hd.push_back(new TH1F(Form("hd[%d]",i),"",35,0.3,1.));
	  if(EEEB=="EE")t->Draw(Form("phoR9>>hd[%d]",i),"(fabs(phoEta)>1.566)");
	  else t->Draw(Form("phoR9>>hd[%d]",i),"(fabs(phoEta)<1.4442)");
      for(Long64_t ev = 0; ev < bkg.GetEntriesFast();ev++)
    {
      bkg.GetEntry(ev);
      TRandom r(ev);
      if(period==2016)ptwei = 1.;
      if(period==2018)L1wei = 1.;
// cout<<phoR9*r.Gaus(1.,double(trys*i+0.9))<<endl;
      /*if(EEEB=="EE"&&fabs(phoEta)>1.566)hmc[i]->Fill(phoR9*r.Gaus(1.,double(trys*i+0.9)),mcwei*puwei*totSF*genwei*L1wei*ptwei);
	else if(EEEB=="EB"&&fabs(phoEta)<1.4442)hmc[i]->Fill(phoR9*r.Gaus(1.,double(trys*i+0.9)),mcwei*puwei*totSF*genwei*L1wei*ptwei);*/
      if(EEEB=="EE"&&fabs(phoEta)>1.566)hmc[i]->Fill(phoR9*double(trys*i+0.9),mcwei*puwei*totSF*genwei*L1wei*ptwei);
      else if(EEEB=="EB"&&fabs(phoEta)<1.4442)hmc[i]->Fill(phoR9*double(trys*i+0.9),mcwei*puwei*totSF*genwei*L1wei*ptwei);
    }
    }
	
      step.push_back(double(trys*i+0.9));
      chi2.push_back(hd[i]->Chi2Test(hmc[i],"UWCHI2/NDF",&res[0]));
    }
  hd[21]->SetMarkerStyle(20);
  hd[21]->SetLineColor(kBlack);
  hd[21]->SetMarkerColor(kBlack);
  hmc[21]->SetLineWidth(2);
  hmc[21]->SetLineColor(kBlue);
  hd[21]->Draw("ep");
  hmc[21]->Draw("histsame");
  	// gPad->Print(Form("plot/mcdata_%s_%s_%s_%d.pdf",var.c_str(),EEEB.c_str(),type.c_str(),period));
  TGraph *g = new TGraph(chi2.size(),&step[0],&chi2[0]);
  g->Draw("ap");
  g->SetTitle(Form("%s_%s_%s_%d",var.c_str(),EEEB.c_str(),type.c_str(),period));
  g->GetXaxis()->SetTitle("shifts");
  g->GetYaxis()->SetTitle("#chi^{2}/ndf");
  gPad->SetLogy();
  // TLatex tex;
  // tex.SetTextSize(0.03);
  // tex.SetTextAlign(13);

  int min;float minval=100;
  for(int i = 0 ; i < chi2.size();i++)
    {
      if(chi2[i]<minval) {minval = chi2[i]; min= i;}
    }
  cout<<var<<" "<<EEEB<<" "<<type<<" "<<period<<endl;
  cout<<"min:"<<step[min]<<" "<<chi2[min]<<endl;
  // tex.DrawLatex(.7,.7,Form("min:%.2f chi2:%.2f",step[minel],chi2[minel]));
  g->Draw("acp ");
 
  gPad->Print(Form("plot/%s_%s_%s_%d.pdf",var.c_str(),EEEB.c_str(),type.c_str(),period));

}
void get_phocor()
{
  string var[2]= {"phoR9","phoMVA"};
  string eb[2] ={"EE","EB"};

  for(int i  = 2016; i < 2019; i++)
    {
      for(int j = 0;j <1; j++)
	{
	  for(int k =0 ;k<2;k++)
	    {
	      chi2scan(i, "ele", var[j], eb[k]);
	      chi2scan(i, "mu", var[j], eb[k]);
	    }
	}
		

    }
}
