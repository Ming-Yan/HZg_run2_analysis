{
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("plugin/RoccoR.cc++");
  //  gROOT->LoadMacro("plugin/rochcor2016.cc++");
  gROOT->LoadMacro("Mu_mana.C+");
  //gROOT->LoadMacro("event.C+");

  Float_t XS[30] = {
    4.858E+01,//ggF-0
    3.782,//VBF-1
    0.5071,//ttH-2
    0.8839,//ZH-3
    8.400E-01,//W+H-4
    5.328E-01,//W-H-5
    0.5071,//ttH,Z->ll-6
    0.8839,//ZH,Z->ll,Z->ll-7
    0.8839,//ZH,Z->all,Z->ll-8
    8.400E-01,//W+H,W->lnu,Z->ll-9
    8.400E-01,//W+H,W->all,Z->ll-10
    5.328E-01,//W-H,W->lnu,Z->ll-11
    5.328E-01,//W-H,W->all,Z->ll-12
    5943.2,//DY+jet-13a
    117.864,//SM Zg (aMC@NLO)-14
    12.178,//WW->2l2nu-15
    49.997,//WWtolNu2q-16
    1.212,//ZZto4l-17
    0.564,//ZZto2l2nu-18
    3.22,//ZZto2l2q-19
    5.595,//WZto2l2q-20
    4.42965,//WZto3lnu-21
    87.31,//TTto2l2nu-22
    0.2086,//WWW-23
    0.1651,//WWZ-24
    0.05565,//WZZ-25
    0.01398,//ZZZ-26
    1.,//WGG-27
    0.2147,//WWG-28
    1.//ZGG-29
  };
  Float_t pho[30],xs[30];
  Int_t aMCatNLO[30];
  Float_t Zg =1.533E-03;//Zg branching ratio
  Float_t Ztoll = 0.033*3;
  Float_t Wtolnu = 0.108*3;
  for(int i = 0  ; i < 30; i++)
    {
      if(i<15) aMCatNLO[i] = 1;
      else aMCatNLO[i] = 0;
      if (i==13) pho[i] = 1;
      else pho[i] = 0;
      if(i<2) xs[i] = XS[i]*Zg*Ztoll;
      if(i>=2&&i<6) xs[i] = XS[i]*Zg;
      if(i==6) xs[i] = XS[i]*Zg*Ztoll;
      if(i==7) xs[i] = XS[i]*Zg*Ztoll*Ztoll;
      if(i==8) xs[i] = XS[i]*Zg*Ztoll;
      if(i==9||i==11) xs[i] = XS[i]*Zg*Wtolnu*Ztoll;
      if(i==10||i==12) xs[i] = XS[i]*Zg*Ztoll;
      if(i>12) xs[i] = XS[i];
    }
  string sample[30] = 
    {
      "HZg_ggF_125GeV_ext1",
      "HZg_VBF_125GeV_ext1",
      "HZg_ttH_125GeV",
      "HZg_ZH_125GeV",
      "HZg_WplusH_125GeV",
      "HZg_WminusH_125GeV",
      "HZg_ttH_ZToLL_125GeV",
      "HZg_ZH_ZToLL_ZToLL_125GeV",
      "HZg_ZH_ZToALL_ZToLL_125GeV",
      "HZg_WplusH_WToLNu_ZToLL_125GeV",
      "HZg_WplusH_WToAll_ZToLL_125GeV",
      "HZg_WminusH_WToLNu_ZToLL_125GeV",
      "HZg_WminusH_WToAll_ZToLL_125GeV",
      "DYJets_M50_aMCatNLO",
      "Zg_aMCatNLO",
      "WWTo2L2Nu",
      "WWToLNuQQ",
      "ZZTo4L",
      "ZZTo2L2Nu",
      "ZZTo2L2Q",
      "WZTo2L2Q",
      "WZTo3LNu",
      "TTTo2L2Nu_powheg",
      "WWW",
      "WWZ",
      "WZZ",
      "ZZZ",
      "WGG",
      "WWG",
      "ZGG"
    };
  Float_t Lumi           = 35.9e3; // pb-1 --2016full dataset
  char inpath[200];

	
  for(int j = 0; j < 4 ; j++)
    {
      for(int k = 0; k < 300; k++)
	{
	  if(j==1&&k==1) break;
	  if((j==2||j==3)&&k==5) break;
	  for (int i = 2; i < 12 ;i++)
	    {

	      //sprintf(inpath, "/data6/ggNtuples/V08_00_26_01/skim/job_summer16_%s*.root",sample[i].c_str());
	      sprintf(inpath, "/data6/ggNtuples/V08_00_26_02/job_summer16_%s/*.root",sample[i].c_str());
	      char D[10];
	      sprintf(D, "%d", j);
	      string s;
	      s.assign(D);
	      char a[10];
	      sprintf(a, "%d", k);
	      string A;
	      A.assign(a);
	      TString outname = "mc_Moriond17_updatexxxx_mucorr";//for lepton tag
	      TString outpathEle =  "/home/mingyan/output/mc/uncertainty/muon/" + outname + s.c_str() + "_ele_" + sample[i].c_str() + "_" + A.c_str() + ".root";
	      TString outpathMu =  "/home/mingyan/output/mc/uncertainty/muon/" + outname + s.c_str() + "_mu_" + sample[i].c_str() + "_" + A.c_str() +".root";
	      Float_t xsection = xs[i];
	      Int_t   negativeWeight =  aMCatNLO[i];
	      int isdataGH = 0;
	      Int_t phoremove = pho[i];
	      Int_t member = k;
	      Int_t set;
	      if (j<2) set = j+1;
	      else set = j+2;
	      cout<<set<<endl;
	      cout<<"processing : "<<inpath<<endl;
	      //inpaths, outpath, channel, xs=1, lumi=1, aMCatNLO=0, double counting removal, isdataGH
	      mana2(inpath, outpathEle, 0, xsection, Lumi, negativeWeight, phoremove, isdataGH,0, set, member);
	      cout<<outpathEle<<" is finished"<<endl;
	      mana2(inpath, outpathMu, 1, xsection, Lumi, negativeWeight,phoremove, isdataGH,0, set, member); 
	      cout<<outpathMu<<" is finished"<<endl;
	    }
	}	
    }
  
}
