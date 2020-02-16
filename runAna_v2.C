{
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("roccor.Run2.v3/RoccoR.cc");
  //gSystem->AddIncludePath(" -I KinZfitter/KinZfitter/interface/");
 
  gROOT->LoadMacro("KinZfitter/KinZfitter/src/KinZfitter_v1.cpp");
  gROOT->LoadMacro("KinZfitter/HelperFunction/src/HelperFunction.cc");
  gROOT->LoadMacro("ana_v2.C");
  Float_t XS[61] = {
    5.222E+01,//ggF 120-0
    3.935,//VBF 120-1
    5.697E-01,//ttH 120-2
    9.939E-01,//ZH 120-3
    9.558E-01,//W+H 120-4
    6.092E-01,//W-H 120-5
    0.5071,//ttH120,Z->ll-6
    0.8839,//ZH120,Z->ll,Z->ll-7
    0.8839,//ZH120,Z->all,Z->ll-8
    8.400E-01,//W+H120,W->lnu,Z->ll-9
    8.400E-01,//W+H120,W->all,Z->ll-10
    5.328E-01,//W-H120,W->lnu,Z->ll-11
    5.328E-01,//W-H120,W->all,Z->ll-12
    4.858E+01,//ggF 125-13
    3.782,//VBF 125-14
    0.5071,//ttH 125-15
    0.8839,//ZH 125-16
    8.400E-01,//W+H 125-17
    5.328E-01,//W-H 125-18
    0.5071,//ttH,Z->ll 125-19
    0.8839,//ZH125,Z->ll,Z->ll-20
    0.8839,//ZH125,Z->all,Z->ll-21
    8.400E-01,//W+H125,W->lnu,Z->ll-22
    8.400E-01,//W+H125,W->all,Z->ll-23
    5.328E-01,//W-H125,W->lnu,Z->ll-24
    5.328E-01,//W-H125,W->all,Z->ll-25
    4.531E+01,//ggF 130-26
    3.637,//VBF 130-27
    4.539E-01,//ttH 130-28
    7.899E-01,//ZH 130-29
    7.414E-01,//W+H 130-30
    4.676E-01,//W-H 130-31
    0.5071,//ttH,Z->ll 125-32
    0.8839,//ZH125,Z->ll,Z->ll-33
    0.8839,//ZH125,Z->all,Z->ll-34
    8.400E-01,//W+H125,W->lnu,Z->ll-35
    8.400E-01,//W+H125,W->all,Z->ll-36
    5.328E-01,//W-H125,W->lnu,Z->ll-37
    5.328E-01,//W-H125,W->all,Z->ll-38
    5943.2,//DY+jet (aMC@NLO)-39
    117.864,//SM Zg (aMC@NLO)-40
    12.178,//WW->2l2nu-41
    49.997,//WWtolNu2q-42
    1.212,//ZZto4l-43
    0.564,//ZZto2l2nu-44
    3.22,//ZZto2l2q-45
    5.595,//WZto2l2q-46
    4.42965,//WZto3lnu-47
    87.31,//TTto2l2nu-48
    0.2086,//WWW-49
    0.1651,//WWZ-50
    0.05565,//WZZ-51
    0.01398,//ZZZ-52
    1.818,//WGG-53
    0.2147,//WWG-54
    6.649E-01,//ZGG-55
    0.04123,//WZG-56
    6.351E-01,//TTG_dilept-57
    831.76,//TTbar-58
    0.1097,//Zg EWK-59,
    3.697//TTG_jets-60
  };
  
  Float_t pho[61],xs[61];
  Int_t aMCatNLO[61];
  bool mucorr[61],isSig[61];
  Float_t Zg120 =1.11E-03;//Zg branching ratio 120GeV
  Float_t Zg125 =1.533E-03;//Zg branching ratio 125GeV
  Float_t Zg130 =1.95E-03;//Zg branching ratio 130GeV
  Float_t Ztoll = 0.033658*3;
  Float_t Wtolnu = 0.108*3;
  for(int i = 0  ; i < 61; i++)
    {
      if(i<41||i==58) aMCatNLO[i] = 1;
      else aMCatNLO[i] = 0;

      if (i==39) pho[i] = 1;
      else pho[i] = 0;
      if(i<2) xs[i] = XS[i]*Zg120*Ztoll;
      if(i>=2&&i<6) xs[i] = XS[i]*Zg120;
      if(i==6) xs[i] = XS[i]*Zg120*Ztoll;
      if(i==7) xs[i] = XS[i]*Zg120*Ztoll*Ztoll;
      if(i==8) xs[i] = XS[i]*Zg120*Ztoll;
      if(i==9||i==11) xs[i] = XS[i]*Zg120*Wtolnu*Ztoll;
      if(i==10||i==12) xs[i] = XS[i]*Zg120*Ztoll;
      if(i==13||i==14) xs[i] = XS[i]*Zg125*Ztoll;
      if(i>=15&&i<19) xs[i] = XS[i]*Zg125;
      if(i==19) xs[i] = XS[i]*Zg125*Ztoll;
      if(i==20) xs[i] = XS[i]*Zg125*Ztoll*Ztoll;
      if(i==21) xs[i] = XS[i]*Zg125*Ztoll;
      if(i==22||i==24) xs[i] = XS[i]*Zg125*Wtolnu*Ztoll;
      if(i==23||i==25) xs[i] = XS[i]*Zg125*Ztoll;
      if(i==26||i==27) xs[i] = XS[i]*Zg130*Ztoll;
      if(i>=28&&i<32) xs[i] = XS[i]*Zg130;
      if(i==32) xs[i] = XS[i]*Zg130*Ztoll;
      if(i==33) xs[i] = XS[i]*Zg130*Ztoll*Ztoll;
      if(i==34) xs[i] = XS[i]*Zg130*Ztoll;
      if(i==35||i==37) xs[i] = XS[i]*Zg130*Wtolnu*Ztoll;
      if(i==36||i==38) xs[i] = XS[i]*Zg130*Ztoll;
      else if(i>38) xs[i] = XS[i];
      if(i<39) isSig[i] = true;
      else isSig[i] = false;
      if(i<49) mucorr[i] = false;
      else mucorr[i] = true;
    }
  string sample[61] = 
    {
      "HZg_ggF_120GeV",
      "HZg_VBF_120GeV",
      "HZg_ttH_120GeV",
      "HZg_ZH_120GeV",
      "HZg_WplusH_120GeV",
      "HZg_WminusH_120GeV",
      "HZg_ttH_ZToLL_120GeV",
      "HZg_ZH_ZToLL_ZToLL_120GeV",
      "HZg_ZH_ZToALL_ZToLL_120GeV",
      "HZg_WplusH_WToLNu_ZToLL_120GeV",
      "HZg_WplusH_WToAll_ZToLL_120GeV",
      "HZg_WminusH_WToLNu_ZToLL_120GeV",
      "HZg_WminusH_WToAll_ZToLL_120GeV",
      "HZg_ggF_125GeV",
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
      "HZg_ggF_130GeV",
      "HZg_VBF_130GeV",
      "HZg_ttH_130GeV",
      "HZg_ZH_130GeV",
      "HZg_WplusH_130GeV",
      "HZg_WminusH_130GeV",
      "HZg_ttH_ZToLL_130GeV",
      "HZg_ZH_ZToLL_ZToLL_130GeV",
      "HZg_ZH_ZToALL_ZToLL_130GeV",
      "HZg_WplusH_WToLNu_ZToLL_130GeV",
      "HZg_WplusH_WToAll_ZToLL_130GeV",
      "HZg_WminusH_WToLNu_ZToLL_130GeV",
      "HZg_WminusH_WToAll_ZToLL_130GeV",
      "DYJetsToLL_m50_aMCatNLO",
      //"DYJetsToLL_m50_MG",
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
      "ZGG",
      "WZG",
      "TTG_dilept",
      ///"TT_powheg",
      "TT_aMCatNLO",
      "Zg_EWK",
      "TTGJets"
    };
  //string ueps[4] = {"UEU","UED","PSU","PSD"};

  char inpath[200];
  //for (int i = 48; i < 49 ;i++)
  //for (int i = 60; i < 61; i++)
  //for(int j = 0 ; j < 1 ; j++){

    for (int i = 58;i < 60; i++)
      {
	if(i!=39&&i!=40&&i!=58&&i!=59)continue;
      int period             = 16;        
      bool isrewei           = false;//tmp use this to reweight PU
      if((period==17||period==18)&&i==40)isrewei=true;
      Float_t Lumi           ;
      if(period==16) Lumi=35.5e03;
      if(period==17) Lumi=41.9e03;
      if(period==18) Lumi=57.8e03;
      
      if(period==18&&(i==39||i==58||i==59))sprintf(inpath,"/data6/ggNtuples/V10_02_10_04/job_autumn18_%s*/ggtree_mc*.root",sample[i].c_str());
      if(period==16&&(i==60||i==40||i==39||i==58||i==59))sprintf(inpath,"/data6/ggNtuples/V09_04_13_04/job_summer16_%s*/ggtree_mc_*.root",sample[i].c_str());
      if(period==17&&(i==40||i==39||i==58||i==59))sprintf(inpath,"/data6/ggNtuples/V09_04_13_04/job_fall17_%s*/ggtree_mc_*.root",sample[i].c_str());
      if(isrewei)sprintf(inpath,"/data6/ggNtuples/V09_04_13_04/job_summer16_%s/ggtree_mc_*.root",sample[i].c_str());
      //else continue;
      TString vername = "HLT";
      TString outname;
      if(period==16)outname = "mc_Legacy16_" +vername;
      if(period==17)outname = "mc_Rereco17_" +vername;
      if(period==18)outname = "mc_Rereco18_" +vername;
      TString outpathEle     = "../outfile/" + outname + "_ele_" + sample[i].c_str() + ".root";
      TString outpathMu      = "../outfile/" + outname + "_mu_" + sample[i].c_str() + ".root";
      Int_t phoremove        = pho[i];    
      Float_t xsection       = xs[i];
      //if(period==17&&i==40)xsection = xsection*4.833e+01/117.864;
      Int_t negativeWeight   = aMCatNLO[i];
      Int_t photonRemoval    = pho[i];
      bool muonCorrection    = true;//mucorr[i];
      bool isSignal          = isSig[i];
      bool iskinMVA          = true;
      bool isdijetMVA        = true;
      bool isrefit           = true; 
      bool isFSR             = true;
      bool iscorr            = true;//correction for refit
      if(period==18) iscorr = false;
      cout<<"processing : "<<inpath<<endl;
      //const char* inpath, TString outpath = "output.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, bool mucorr = false, bool isSig = false, bool isMVA=true,bool isjetMVA=true, bool isData = false, bool isrefit = false, bool isFSR = false, int data1617 = 16, bool iscorr, bool is bool isbug = false
      main_ana(inpath, outpathEle, 0, xsection, Lumi, negativeWeight, photonRemoval, muonCorrection, isSignal,iskinMVA,isdijetMVA,0,isrefit,isFSR,period,0,isrewei);
      cout<<outpathEle<<" is finished"<<endl;
      if(period==18)Lumi=58.8e03;
      main_ana(inpath, outpathMu, 1, xsection, Lumi, negativeWeight, photonRemoval, muonCorrection, isSignal,iskinMVA,isdijetMVA,0,isrefit,isFSR,period,iscorr,isrewei);
      cout<<outpathMu<<" is finished"<<endl;

    }
}
