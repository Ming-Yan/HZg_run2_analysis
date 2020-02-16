void Un_R9_Jet()
{
  gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");
string categories[8] =
  {
    "(cat>5&&cat<10)",
    "HZgVBF>0.06&&cat==5",
    "HZgVBF<=0.06&&HZgVBF>-0.06&&cat==5",
    "HZgVBF<=-0.06&&mllgpt>60.&&(cat>9||cat<5)",
    "HZgVBF<=-0.06&&HZgMVA>0.1&&mllgpt<=60&&(cat>9||cat<5)",
    "HZgVBF<=-0.06&&HZgMVA<=0.1&&HZgMVA>0.05751&&mllgpt<=60&&(cat>9||cat<5)",
    "HZgVBF<=-0.06&&HZgMVA<=0.05751&&HZgMVA>0.01785&&mllgpt<=60&&(cat>9||cat<5)",
      "HZgVBF<=-0.06&&HZgMVA<=0.01785&&HZgMVA>-0.0543&&mllgpt<=60&&(cat>9||cat<5)"
  };

 string unc[9]=
    {
      "JECUp",
      "JECDown",
      "JERUp",
      "JERDown",
      "UEU",
      "UED",
      "PSU",
      "PSD",
      "R9"
    };
 int cat_[8] = {6789,501,502,10,1,2,3,4};
  //signal
    for (int u =  0; u < 5; u++)
    {
      for (int i= 0 ; i <2; i++)
	{
	  for (int cat = 1; cat <8 ; cat++)
	    {
	      for (int mass = 1; mass <2 ; mass++)
		{
		  int m = 120+ mass*5;
		  cout<<unc[u]<<"  mass: "<<mass<<" eleormu: "<<i<<" cat:"<<cat_[cat]<<endl;
		  TChain ggF("tZg");
		  TChain VBF("tZg");
		  TChain ttH("tZg");
		  TChain ZH("tZg");
		  TChain WH("tZg");
		  if(i==0)
		    {
		      ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_ggF_%dGeV.root",m));
		      if(m==125)VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_VBF_%dGeV_ext1.root",m));
		      else VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_VBF_%dGeV.root",m));
		      ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_ttH_%dGeV.root",m));
		      ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_ZH_%dGeV.root",m));
		      WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_WplusH_%dGeV.root",m));
		      WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_ele_HZg_WminusH_%dGeV.root",m));   
		    }
		  else if(i==1){
		    ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_ggF_%dGeV.root",m));
		    if(m==125)VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_VBF_%dGeV_ext1.root",m));
		    else VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_VBF_%dGeV.root",m));
		    ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_ttH_%dGeV.root",m));
		    ZH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_ZH_%dGeV.root",m));
		    WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_WplusH_%dGeV.root",m));
		    WH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_VBFMVA_v3_mu_HZg_WminusH_%dGeV.root",m));
		  }
		  TH1F *hsig1 = new TH1F("hsig1", " ",55, 115, 170);
		  TH1F *hsig2 = new TH1F("hsig2", " ",55, 115, 170);
		  TH1F *hsig3 = new TH1F("hsig3", " ",55, 115, 170);
		  TH1F *hsig4 = new TH1F("hsig4", " ",55, 115, 170);
		  TH1F *hsig5 = new TH1F("hsig5", " ",55, 115, 170);
      
		  vector<float> nom; nom.clear();
		  string fname;
		  if (i==0) fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat_[cat])+"_m"+  std::to_string(m)+".txt";
		  else  fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat_[cat])+"_m"+  std::to_string(m)+".txt";
		  ofstream out(fname.c_str(), std::ios_base::app);
		  //nominal
		  ggF.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));nom.push_back(hsig1->Integral());
		  VBF.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));nom.push_back(hsig2->Integral());
		  ttH.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));nom.push_back(hsig3->Integral());
		  ZH.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));nom.push_back(hsig4->Integral());
		  WH.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));nom.push_back(hsig5->Integral());
        
		  TChain ggF1("tZg");
		  TChain VBF1("tZg");
		  TChain ttH1("tZg");
		  TChain ZH1("tZg");
		  TChain WH1("tZg");
		  if(i==0)
		    {
		      ggF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ggF_%dGeV.root",unc[2*u].c_str(),m));
		      if(m==125)VBF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_VBF_%dGeV_ext1.root",unc[2*u].c_str(),m));
		      else VBF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_VBF_%dGeV.root",unc[2*u].c_str(),m));
		      ttH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ttH_%dGeV.root",unc[2*u].c_str(),m));
		      ZH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ZH_%dGeV.root",unc[2*u].c_str(),m));
		      WH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_WplusH_%dGeV.root",unc[2*u].c_str(),m));
		      WH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_WminusH_%dGeV.root",unc[2*u].c_str(),m));   
		    }
		  else if(i==1){
		    ggF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ggF_%dGeV.root",unc[2*u].c_str(),m));
		    if(m==125)VBF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_VBF_%dGeV_ext1.root",unc[2*u].c_str(),m));
		    else VBF1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_VBF_%dGeV.root",unc[2*u].c_str(),m));
		    ttH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ttH_%dGeV.root",unc[2*u].c_str(),m));
		    ZH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ZH_%dGeV.root",unc[2*u].c_str(),m));
		    WH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_WplusH_%dGeV.root",unc[2*u].c_str(),m));
		    WH1.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_WminusH_%dGeV.root",unc[2*u].c_str(),m));
		  }
		  float puggF[3] ={0}, puVBF[3]={0},puttH[3] = {0}, puZH[3] = {0}, puWH[3] = {0};
		  ggF1.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		  //cout<<hsig1->Integral()<<" "<<nom[0]<<endl;
		  //cout<<hsig1->GetEntries()<<endl;
		  puggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		  VBF1.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		  puVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		  ttH1.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		  puttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		  ZH1.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		  puZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		  WH1.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		  puWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
	     
	      
	    
		  if(u<4){
		    TChain ggF2("tZg");
		    TChain VBF2("tZg");
		    TChain ttH2("tZg");
		    TChain ZH2("tZg");
		    TChain WH2("tZg");
		    if(i==0)
		      {
			ggF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ggF_%dGeV.root",unc[2*u+1].c_str(),m));
			if(m==125)VBF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_VBF_%dGeV_ext1.root",unc[2*u+1].c_str(),m));
			else VBF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_VBF_%dGeV.root",unc[2*u+1].c_str(),m));
			ttH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ttH_%dGeV.root",unc[2*u+1].c_str(),m));
			ZH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_ZH_%dGeV.root",unc[2*u+1].c_str(),m));
			WH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_WplusH_%dGeV.root",unc[2*u+1].c_str(),m));
			WH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_ele_HZg_WminusH_%dGeV.root",unc[2*u+1].c_str(),m));   
		      }
		    else if(i==1){
		      ggF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ggF_%dGeV.root",unc[2*u+1].c_str(),m));
		      if(m==125)VBF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_VBF_%dGeV_ext1.root",unc[2*u+1].c_str(),m));
		      else VBF2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_VBF_%dGeV.root",unc[2*u+1].c_str(),m));
		      ttH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ttH_%dGeV.root",unc[2*u+1].c_str(),m));
		      ZH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_ZH_%dGeV.root",unc[2*u+1].c_str(),m));
		      WH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_WplusH_%dGeV.root",unc[2*u+1].c_str(),m));
		      WH2.Add(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v3_%s_mu_HZg_WminusH_%dGeV.root",unc[2*u+1].c_str(),m));
		    }
		    ggF2.Draw("mllg>>hsig1",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		    if((hsig1->Integral() - nom[0])>puggF[mass])puggF[mass] =( hsig1->Integral() - nom[0])/(nom[0]);
		    VBF2.Draw("mllg>>hsig2",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		    if((hsig2->Integral() - nom[1])>puVBF[mass])puVBF[mass] =( hsig2->Integral() - nom[1])/(nom[1]);
		    ttH2.Draw("mllg>>hsig3",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		    if((hsig3->Integral() - nom[2])>puttH[mass])puttH[mass] =(hsig3->Integral() - nom[2])/(nom[2]);
		    ZH2.Draw("mllg>>hsig4",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		    if((hsig4->Integral() - nom[3])>puZH[mass])puZH[mass] =(hsig4->Integral() - nom[3])/(nom[3]);
		    WH2.Draw("mllg>>hsig5",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",categories[cat].c_str()));
		    if((hsig5->Integral() - nom[4])>puWH[mass])puWH[mass] =(hsig5->Integral() - nom[4])/(nom[4]);
		  }
		  if(m>120){
		    for (int k = 0 ; k < 4 ; k++)
		      {
			string fname2;
			if (i==0) fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_ele_cat" + std::to_string(cat_[cat])+"_m"+  std::to_string(m-4+k)+".txt";
			else  fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/sys_mu_cat" + std::to_string(cat_[cat])+"_m"+  std::to_string(m-4+k)+".txt";
			ofstream out2(fname2.c_str(), std::ios_base::app);
			if(u==0)out2<<"CMS_JEC_13TeV      lnN     ";
			if(u==1)out2<<"CMS_JER_13TeV      lnN     ";
			if(u==2)out2<<"CMS_UE_13TeV      lnN     ";
			if(u==3)out2<<"CMS_PS_13TeV      lnN     ";
			if(u==4)out2<<"CMS_R9_13TeV      lnN     ";
		    
			out2<<1.+puggF[mass]*((k+1.)/5.)+puggF[mass-1]*((4-k)/5.)<<" "<<1.+puVBF[mass]*((k+1.)/5.)+puVBF[mass-1]*((4-k)/5.)<<" "<<1.+puttH[mass]*((k+1.)/5.)+puttH[mass-1]*((4-k)/5.)<<" "<<1.+puZH[mass]*((k+1.)/5.)+puZH[mass-1]*((4-k)/5.)<<" "<<1.+puWH[mass]*((k+1.)/5.)+puWH[mass-1]*((4-k)/5.)<<endl;
		      }
		  }
          
		  if(u==0)out<<"CMS_JEC_13TeV      lnN     ";
		  if(u==1)out<<"CMS_JER_13TeV      lnN     ";
		  if(u==2)out<<"CMS_UE_13TeV      lnN     ";
		  if(u==3)out<<"CMS_PS_13TeV      lnN     ";
		  if(u==4)out<<"CMS_R9_13TeV      lnN     ";
		  //cout<<puggF[mass]<<endl;
		  out<<1.+puggF[mass]<<"  "<<1.+puVBF[mass]<<"  "<<1.+puttH[mass]<<"  "<<1.+puZH[mass]<<"   "<<1.+puWH[mass]<<endl;
		  if(mass==1)cout<<1.+puggF[mass]<<"  "<<1.+puVBF[mass]<<"  "<<1.+puttH[mass]<<"  "<<1.+puZH[mass]<<"   "<<1.+puWH[mass]<<endl;
		}
	    }
	}
    }
}
	   
