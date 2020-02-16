{
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("plugin/RoccoR.cc++");
  //  gROOT->LoadMacro("plugin/rochcor2016.cc++");
  //gROOT->LoadMacro("mana.C+");
  gROOT->LoadMacro("ana.c+");
  //gROOT->LoadMacro("event.C+");

  Float_t XS[59] = {
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
    831.76//TTbar-58
  };
  Float_t pho[59],xs[59];
  Int_t aMCatNLO[59];
  Float_t Zg120 =1.11E-03;//Zg branching ratio 120GeV
  Float_t Zg125 =1.533E-03;//Zg branching ratio 125GeV
  Float_t Zg130 =1.95E-03;//Zg branching ratio 130GeV
  Float_t Ztoll = 0.033*3;
  Float_t Wtolnu = 0.108*3;
  for(int i = 0  ; i < 59; i++)
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
    }
  string sample[59] = 
    {
      "HZg_ggF_120GeV_ext1",
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
      "HZg_ggF_130GeV_ext1",
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
      "TT_powheg"
    };
  Float_t Lumi           = 35.9e3; // pb-1 --2016full dataset
  char inpath[200];
  for (int i = 13 ;i < 14 ;i++)
    {
      //if(i!=39&&i!=40&&i!=58)continue;
      //if(i==58)sprintf(inpath, "root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/mc/V08_00_26_05/job_summer16_TT_powheg/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_job_summer16_TT_powheg/170709_142302/0000/*.root",sample[i].c_str());
      if(i<41)sprintf(inpath, "/data6/ggNtuples/V08_00_26_05/skim/job_summer16_%s.root",sample[i].c_str());
      //else sprintf(inpath, "/data6/ggNtuples/V08_00_26_05/job_summer16_%s/*.root",sample[i].c_str());
      //sprintf(inpath, "./ggtree_mc.root");
      //TString outname = "mc_kinfit";//for lepton tag
      TString outname = "mc_Moriond17_update0709_t2";//for lepton ta
      TString outpathEle     =  "/home/mingyan/output/mc/" + outname + "_ele_" + sample[i].c_str() + ".root";
      TString outpathMu      =  "/home/mingyan/output/mc/" + outname + "_mu_" + sample[i].c_str() + ".root";
      Float_t xsection;
      xsection   = xs[i];
      Int_t   negativeWeight =  aMCatNLO[i];
      int isdataGH = 0;
      Int_t phoremove = pho[i];    
      cout<<"processing : "<<inpath<<endl;
      //inpaths, outpath, channel, xs=1, lumi=1, aMCatNLO=0, double counting removal, isdataGH
      mana2(inpath, outpathEle, 0, xsection, Lumi, negativeWeight, phoremove, isdataGH);
      cout<<outpathEle<<" is finished"<<endl;
      mana2(inpath, outpathMu, 1, xsection, Lumi, negativeWeight,phoremove, isdataGH); 
      cout<<outpathMu<<" is finished"<<endl;
    }
}
