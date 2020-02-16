{
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("plugin/RoccoR.cc++");
  gROOT->LoadMacro("plugin/rochcor2016.cc++");
  gROOT->LoadMacro("mana.C+");
  //gROOT->LoadMacro("event.C+");

  Int_t aMCatNLO[20];
  Float_t XS[20] = {
    4.858E+01,//ggF-0
    3.782,//VBF-1
    0.5071,//ttH-2
    0.8839,//ZH-3
    8.400E-01,//W+H-4
    5.328E-01,//W-H-5
    5943.2,//DY+jet-6
    117.864,//SM Zg (aMC@NLO)-7
    12.178,//WW->2l2nu-8
    49.997,//WWtolNu2q-9
    1.212,//ZZto4l-10
    0.564,//ZZto2l2nu-11
    3.22,//ZZto2l2q-12
    5.595,//WZto2l2q-13
    4.42965,//WZto3lnu-14
    87.31,//TTto2l2nu-15
    0.2086,//WWW-16
    0.1651,//WWZ-17
    0.05565,//WZZ-18
    0.01398//ZZZ-19
  };
  Float_t pho[20];
  Float_t Zg =1.533E-03;//Zg branching ratio
  for(int i = 0  ; i < 20; i++)
    {
      if(i==7||i==6) aMCatNLO[i] = 1;
      else aMCatNLO[i] = 0;
      if (i==6) pho[i] = 1;
      else pho[i] = 0;
    }
  string sample[20] = 
    {
    "HZg_ggF_125GeV",
    "HZg_VBF_125GeV",
    "HZg_ttH_125GeV",
    "HZg_ZH_125GeV",
    "HZg_WplusH_125GeV",
    "HZg_WminusH_125GeV",
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
    "ZZZ"
  };
    Float_t Lumi           = 36.46e3; // pb-1 --2016full dataset
  char inpath[200];
  for (int i = 1 ; i < 2 ;i++)
    {
      //    if(i==13||i==15)continue;
      /*    if(i <6)*/    sprintf(inpath, "/data6/ggNtuples/V08_00_24_00/*spring16_%s*/ggtree_mc_*.root",sample[i].c_str());
    //    if(i >=6)   sprintf(inpath, "/data1/ggNtuples/V08_00_24_00/spring16_%s/ggtree_mc_*.root",sample[i].c_str());
    TString outname = "mc_Moriond17_update0217";//for lepton tag
    TString outpathEle     =  "/home/mingyan/output/mc/" + outname + "_ele_" + sample[i].c_str() + ".root";
    TString outpathMu      =  "/home/mingyan/output/mc/" + outname + "_mu_" + sample[i].c_str() + ".root";
    Float_t xsection;
    if (i<2)xsection =XS[i]*Zg*0.033*3;
    if (i>1&&i < 6)   xsection  = XS[i]*Zg;
    if (i >= 6)  xsection   = XS[i];
    Int_t   negativeWeight =  0;
    int isdataGH = 0;
    Int_t phoremove = pho[i];    
    cout<<"processing : "<<inpath<<endl;
    //inpaths, outpath, channel, xs=1, lumi=1, aMCatNLO=0, double counting removal, isdataGH
    mana2(inpath, outpathEle, 0, xsection, Lumi, negativeWeight, phoremove, isdataGH);
    cout<<outpathEle<<" is finished"<<endl;
    //    mana2(inpath, outpathMu, 1, xsection, Lumi, negativeWeight,phoremove, isdataGH); 
    //cout<<outpathMu<<" is finished"<<endl;
    }
}
