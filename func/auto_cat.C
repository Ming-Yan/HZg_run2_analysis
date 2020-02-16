void auto_kincat(TString fname,int ncat, bool isboost, int type, vector<string> &vname, vector<double> &nsig, vector<double> &nsignm1)
{
  TChain sig("tZg");
  if(type==0)sig.Add(Form("../outfile/mc_%s_ele_HZg_*_125GeV.root",fname.Data()));
  else sig.Add(Form("../outfile/mc_%s_mu_HZg_*_125GeV.root",fname.Data()));
  TChain bkg("tZg");
  if(type==0)bkg.Add(Form("../outfile/mc_%s_ele_*_aMCatNLO.root",fname.Data()));
  else bkg.Add(Form("../outfile/mc_%s_mu_*_aMCatNLO.root",fname.Data()));
  if(type==0)bkg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",fname.Data()));
  else bkg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",fname.Data()));

  TChain data("tZg");
  if(type==0)data.Add(Form("../outfile/Data_%s_ele_EG.root",fname.Data()));
  else data.Add(Form("../outfile/Data_%s_mu_Mu.root",fname.Data()));
  int allcats = (ncat!=5&&ncat!=6) ? 84:126;
  if(ncat==3) allcats=36;
  string weight;
  //Combine electron and muon
  // float MVAWP[27]
  // {
  //   0.0828,0.0646,0.0514,0.0398,0.0274,0.0134,-0.0038,-0.0647,-0.17,//2016
  //     0.1007,0.0688,0.0497,0.0346,0.0198,0.0036,-0.0158,-0.0892,-0.22,//2017
  //     0.1617,0.1191,0.0876,0.0647,0.0459,0.0278,0.0075,-0.0587,-0.19,
  //     };

	
  // float MVAWPb[27]
  // {
  //   0.0713,0.0563,0.0446,0.0331,0.021,0.0074,-0.0107,-0.0693,-0.18,//2016
  //     0.0676,0.0495,0.0356,0.0226,0.0088,-0.0068,-0.0255,-0.1014,-0.23,//2017
  //     0.1408,0.1008,0.0735,0.0538,0.037,0.0198,-0.0001,-0.0653,-0.2
  //     };
  float MVAWP_e[27] =
  {
    0.0715,0.0565,0.0447,0.0332,0.0215,0.0083,-0.009,-0.0671,-0.25,//2016
    0.0914,0.0685,0.0535,0.0408,0.0286,0.0158,0.0004,-0.0582,-0.24,//2017
    0.1411,0.102,0.0745,0.0545,0.0379,0.0205,0.0013,-0.0626,-0.26//2018
  };
  float MVAWP_m[27] =
  {
    0.071,0.0562,0.0445,0.0329,0.0207,0.0064,-0.0119,-0.0716,-0.25,//2016
    0.0891,0.067,0.0521,0.0395,0.027,0.0133,-0.0032,-0.0645,-0.24,//
    0.1404,0.0998,0.0726,0.0533,0.0363,0.0191,-0.0015,-0.0674,-0.26//2018
  };
  float MVAWPb_e[27] =
  {
    0.0831,0.0646,0.0513,0.0399,0.0275,0.014,-0.0025,-0.0625,-0.25,//2016
    0.0713,0.0553,0.043,0.0314,0.0206,0.0081,-0.0077,-0.0661,-0.23,
    0.1626,0.1201,0.0884,0.0655,0.0466,0.0286,0.0089,-0.0562,-0.26//2018
  };
  float MVAWPb_m[27] =
  {
    0.0824,0.0646,0.0514,0.0397,0.0273,0.00129,-0.0052,-0.0664,-0.25,//2016
    0.0714,0.0549,0.0424,0.031,0.0191,0.0059,-0.0111,-0.0713,-0.23,
    0.1612,0.1182,0.0867,0.0639,0.0454,0.0272,0.0065,-0.0612,-0.26//2018
  };
  if(fname.Contains("16")) weight = "*L1wei";
  if(fname.Contains("17")) weight = "*L1wei*ptwei";
  if(fname.Contains("18")) weight = "*ptwei";
  string boost = (isboost) ? "":"||cat==10";

  char cats[20];
  sprintf(cats,"limit/new_ncat%d.txt",ncat);

  ifstream fcat(cats);

  int category; static vector<int> catvec;  catvec.clear();
  vector<int> thiscat; thiscat.clear();
  while (fcat>>category)catvec.push_back(category);
  vector<TH1F*> hsig, hbkg; hsig.clear();hbkg.clear();

  for(int i = 0 ; i < allcats ; i++)
    {
      thiscat.clear();
      hsig.clear();hbkg.clear();
      string catname;
      for(int k = 0 ; k < ncat-1; k++)
	{
	  catname += std::to_string(catvec[k+i*(ncat-1)]);
	  thiscat.push_back(catvec[k+i*(ncat-1)]);
	}
      float autokin = 0.,m1autokin =0.;
      bool lowstat = false;
      for(int ii = 0 ; ii < ncat; ii++)
	{
	  float MVAup, MVAdown;
	  int p = 0;
	  if(fname.Contains("16")) p = 0;
	  else if(fname.Contains("17"))p=1;
	  else p =2;
    if(type==0){
      if(!isboost){
      MVAup = (ii==0) ? 1.0: MVAWP_e[thiscat[ii-1]+9*p];              
      MVAdown = (ii==ncat-1) ? -1.0: MVAWP_e[thiscat[ii]+9*p];
      }
      else 
      {
        MVAup = (ii==0) ? 1.0: MVAWPb_e[thiscat[ii-1]+9*p];              
        MVAdown = (ii==ncat-1) ? -1.0: MVAWPb_e[thiscat[ii]+9*p];
      }
    }
    else
    {
      if(!isboost){
      MVAup = (ii==0) ? 1.0: MVAWP_m[thiscat[ii-1]+9*p];              
      MVAdown = (ii==ncat-1) ? -1.0: MVAWP_m[thiscat[ii]+9*p];
      }
      else 
      {
        MVAup = (ii==0) ? 1.0: MVAWPb_m[thiscat[ii-1]+9*p];              
        MVAdown = (ii==ncat-1) ? -1.0: MVAWPb_m[thiscat[ii]+9*p];
      }
    }
	  
	  hsig.push_back(new TH1F(Form("hsig[%d]",ii),"",40,120,130));
	  hbkg.push_back(new TH1F(Form("hbkg[%d]",ii),"",40,120,130));
	  TH1F *hdata = new TH1F("hdata","",55,115.,170);
			
	  sig.Draw(Form("mllg>>hsig[%d]",ii),Form("((cat<5%s)&&mllg>120&&mllg<130&&HZgMVA<=%.2f&&HZgMVA>%.2f)*puwei*totSF*mcwei*genwei%s",boost.c_str(),MVAup,MVAdown,weight.c_str()));
	  bkg.Draw(Form("mllg>>hbkg[%d]",ii),Form("((cat<5%s)&&mllg>120&&mllg<130&&HZgMVA<=%.2f&&HZgMVA>%.2f)*puwei*totSF*mcwei*genwei%s",boost.c_str(),MVAup,MVAdown,weight.c_str()));
	  data.Draw("mllg>>hdata",Form("(cat<5%s)&&mllg>115&&mllg<170&&HZgMVA<=%.2f&&HZgMVA>%.2f",boost.c_str(),MVAup,MVAdown));
	  if(hdata->Integral()<70) lowstat = true;
	  autokin += hsig[ii]->Integral()*hsig[ii]->Integral()/fabs(hbkg[ii]->Integral());
	  if(ii<ncat-1)m1autokin += hsig[ii]->Integral()*hsig[ii]->Integral()/fabs(hbkg[ii]->Integral());
	  if(ii==ncat-1)	{
	    // cout<<"normal:"<<catname<<" "<<cat1+float(autoVBF)-float(sigsum)<<endl;
	    // cout<<cat1+float(autoVBF)-float(sigsum)<<endl;
	    // gain.push_back(autoVBF-sigsum);
	    // cout<<"minus1:"<<	catname<<" "<<cat1+ float(m1autoVBF)-float(sigsum)<<endl;
	    if(lowstat) {autokin = -999; m1autokin = -999;}	
	    vname.push_back(catname);	
	    nsig.push_back(autokin);
	    nsignm1.push_back(m1autokin);
	  }
	}
    }
}
void auto_VBFcat(TString fname,int ncat, vector<string> &vname, vector<double> &nom,vector<double> &nm1)
{
  TChain VBF("tZg");
  VBF.Add(Form("../outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname.Data()));
  VBF.Add(Form("../outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname.Data()));
  TChain sig("tZg");
  sig.Add(Form("../outfile/mc_%s_ele_HZg_*_125GeV.root",fname.Data()));
  sig.Add(Form("../outfile/mc_%s_mu_HZg_*_125GeV.root",fname.Data()));
  TChain bkg("tZg");
  bkg.Add(Form("../outfile/mc_%s_ele_*_aMCatNLO.root",fname.Data()));
  bkg.Add(Form("../outfile/mc_%s_mu_*_aMCatNLO.root",fname.Data()));
  bkg.Add(Form("../outfile/mc_%s_ele_Zg_EWK.root",fname.Data()));
  bkg.Add(Form("../outfile/mc_%s_mu_Zg_EWK.root",fname.Data()));
  TChain data("tZg");
  data.Add(Form("../outfile/Data_%s_ele_EG.root",fname.Data()));
  data.Add(Form("../outfile/Data_%s_mu_Mu.root",fname.Data()));

  string weight;
  float sigsum = 0., VBFcat = 0.;
  if(fname.Contains("16")){sigsum = 0.178999; VBFcat=0.122426; }
  if(fname.Contains("17")){sigsum = 0.130; VBFcat=0.133103;}
  if(fname.Contains("18")){sigsum = 2.06304; VBFcat=0.156851; }

  float MVAWP[15]
  {
    0.0889283,0.0436731,-0.0258199,-0.154931,-0.839576,//2016
      0.0902407,0.0318622,-0.0530894,-0.189453,-0.911372,//2017
      0.108736,0.0467022,-0.042305,-0.183781,-0.885997//2018
      };
	
  if(fname.Contains("16")) weight = "*L1wei";
  if(fname.Contains("17")) weight = "*L1wei*ptwei";
  if(fname.Contains("18")) weight = "*ptwei";

  TH1F *hs_vbf1 = new TH1F("hs_vbf1","",40,120,130);
  TH1F *hb_vbf1 = new TH1F("hb_vbf1","",40,120,130);
  sig.Draw("mllg>>hs_vbf1",Form("(cat==5&&mllg>120&&mllg<130&&HZgVBF>%.2f)*puwei*totSF*mcwei*genwei%s",VBFcat,weight.c_str()));
  bkg.Draw("mllg>>hb_vbf1",Form("(cat==5&&mllg>120&&mllg<130&&HZgVBF>%.2f)*puwei*totSF*mcwei*genwei%s",VBFcat,weight.c_str()));
  // float cat1 = 0.;
  float cat1 = hs_vbf1->Integral()*hs_vbf1->Integral()/fabs(hb_vbf1->Integral());


  int allcats = (ncat==2)? 5:10;	 
  char cats[50];
  sprintf(cats,"limit/VBF_ncat%d.txt",ncat);
  ifstream fcat(cats);
  int category; static vector<int> catvec;  catvec.clear();
  vector<int> thiscat; thiscat.clear();
  while (fcat>>category)catvec.push_back(category);
  vector<TH1F*> hsig, hbkg; hsig.clear();hbkg.clear();

  for(int i = 0 ; i < allcats ; i++)
    {
      thiscat.clear();
      hsig.clear();hbkg.clear();
      string catname;
      for(int k = 0 ; k < ncat-1; k++)
	{
			
	  catname += std::to_string(catvec[k+i*(ncat-1)]);
	  thiscat.push_back(catvec[k+i*(ncat-1)]);
	}
      float autoVBF = 0.,m1autoVBF =0.;
      bool lowstat = false;
      vname.push_back(catname);      
      for(int ii = 0 ; ii < ncat; ii++)
	{
	  float MVAup, MVAdown;
	  int p = 0;
	  if(fname.Contains("16")) p = 0;
	  else if(fname.Contains("17"))p=1;
	  else p =2;
	  MVAup = (ii==0) ? VBFcat: MVAWP[thiscat[ii-1]+5*p];              
	  MVAdown = (ii==ncat-1) ? -1.0: MVAWP[thiscat[ii]+5*p];
	  hsig.push_back(new TH1F(Form("hsig[%d]",ii),"",40,120,130));
	  hbkg.push_back(new TH1F(Form("hbkg[%d]",ii),"",40,120,130));
	  TH1F *hdata = new TH1F("hdata","",55,115.,170);
	  sig.Draw(Form("mllg>>hsig[%d]",ii),Form("(cat==5&&mllg>120&&mllg<130&&HZgVBF<=%.2f&&HZgVBF>%.2f)*puwei*totSF*mcwei*genwei%s",MVAup,MVAdown,weight.c_str()));
	  bkg.Draw(Form("mllg>>hbkg[%d]",ii),Form("(cat==5&&mllg>120&&mllg<130&&HZgVBF<=%.2f&&HZgVBF>%.2f)*puwei*totSF*mcwei*genwei%s",MVAup,MVAdown,weight.c_str()));
	  data.Draw("mllg>>hdata",Form("(cat==5&&mllg>115&&mllg<170&&HZgVBF<=%.2f&&HZgVBF>%.2f)",MVAup,MVAdown));
	  if(hdata->Integral()<120) lowstat = true;
	  autoVBF += hsig[ii]->Integral()*hsig[ii]->Integral()/fabs(hbkg[ii]->Integral());
	  if(ii<ncat-1)m1autoVBF += hsig[ii]->Integral()*hsig[ii]->Integral()/fabs(hbkg[ii]->Integral());
	  if(ii==ncat-1)	{
	    if(lowstat){m1autoVBF = -99; autoVBF =-99;}
	    nom.push_back(autoVBF);
	    nm1.push_back(m1autoVBF);
	  }

	}
    }

}
void auto_cat(int ncat0, int em,int ny=0,int ny2 =3)
{
  string fname[3] = {"Legacy16_newMVA","Rereco17_newMVAv3","Rereco18_newMVAv2"};
  gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");   
  gStyle->SetOptStat(0);
  int ncat1 = ncat0+1;
  // for (int t = 0; t < 2;)
  for(int j = ny; j < ny2; j++){
    vector<string> vb,v;vb.clear();v.clear();
    vector<double> nsig,nsignm1,nsigb,nsigbnm1;nsignm1.clear();nsig.clear();nsigb.clear();nsigbnm1.clear();
    //ofstream out(fname[j].c_str());
    TCanvas *c = new TCanvas("c","c",2400,600);
    c->cd();
    for(int i = ncat0; i < ncat1; i++)
      {	

	auto_kincat(fname[j],i, 1, em, vb, nsigb, nsigbnm1);
	auto_kincat(fname[j],i, 0, em, v, nsig, nsignm1);
	//auto_VBFcat(fname[j],i,v,nsig, nsignm1);
      }
    TH1F *h = new TH1F("h","",int(nsig.size()),0,nsig.size());
    TH1F *hnm1 = new TH1F("hnm1","",int(nsignm1.size()),0,float(nsignm1.size()));
    TH1F *hb = new TH1F("hb","",int(nsigb.size()),0,float(nsigb.size()));
    TH1F *hbnm1 = new TH1F("hbnm1","",int(nsigbnm1.size()),0,float(nsigbnm1.size()));
    for(int i = 0 ; i < nsig.size();i++) 
      {
	h->SetBinContent(i+1,nsig[i]);
	h->GetXaxis()->SetBinLabel(i+1,v[i].c_str());
      }
	
    for(int i = 0 ; i < nsignm1.size();i++)hnm1->SetBinContent(i+1,nsignm1[i]);
    for(int i = 0 ; i < nsigb.size();i++)hb->SetBinContent(i+1,nsigb[i]);	
    for(int i = 0 ; i < nsigbnm1.size();i++)hbnm1->SetBinContent(i+1,nsigbnm1[i]);
    /*    
    h->SetMarkerColor(kBlue);
    h->SetLineWidth(2);
    h->SetLineColor(kBlue);
    hnm1->SetLineWidth(2);
    hnm1->SetLineStyle(2);
    hnm1->SetMarkerColor(kBlue);
    hnm1->SetLineColor(kBlue);
    hb->SetMarkerColor(kRed);
    hb->SetLineWidth(2);
    hb->SetLineColor(kRed);
    hbnm1->SetLineWidth(2);
    hbnm1->SetLineStyle(2);
    hbnm1->SetMarkerColor(kRed);
    hbnm1->SetLineColor(kRed);
    //h->SetMaximum(0.25);
    h->SetMinimum(0.);*/
    if(em==1) cout<<ncat0<<" Muon:"<<endl;
    else cout<<ncat0<<" Electron:"<<endl;
    // cout<<" "<<h->GetBinContent(h->FindBin(h->GetMaximum()))<<" "<<hnm1->FindBin(hnm1->GetMaximum())<<endl;
    // cout<<v[max_element(std::begin(nsig), std::end(nsig))]<<endl; // c++11
    cout<<"cat:"<<v[max_element(nsig.begin(), nsig.end())-nsig.begin()]<<" "<<v[max_element(nsignm1.begin(), nsignm1.end())-nsignm1.begin()]<<" "<<v[max_element(nsigb.begin(), nsigb.end())-nsigb.begin()]<<" "<<v[max_element(nsigbnm1.begin(), nsigbnm1.end())-nsigbnm1.begin()]<<endl;
    cout<<" "<<h->GetMaximum()<<" "<<hnm1->GetMaximum()<<" "<<hb->GetMaximum()<<" "<<hbnm1->GetMaximum()<<endl;
    // cout<<"cat:"<<v[max_element(nsig.begin(), nsig.end())-nsig.begin()]<<" "<<v[max_element(nsignm1.begin(), nsignm1.end())-nsignm1.begin()]<<endl;

  }

}
