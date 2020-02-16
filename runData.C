{
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("KinZfitter/KinZfitter/src/KinZfitter.cpp");
  gROOT->LoadMacro("KinZfitter/HelperFunction/src/HelperFunction.cc");
  gROOT->LoadMacro("plugin/RoccoR.cc++");
  gROOT->LoadMacro("ana_v.C");
  //gROOT->LoadMacro("mana.C++");
  string sample[18] = {
    "EG_Run2016B_FebReminiAOD",
    "EG_Run2016C_FebReminiAOD",
    "EG_Run2016D_FebReminiAOD",
    "EG_Run2016E_FebReminiAOD",
    "EG_Run2016F_FebReminiAOD1",
    "EG_Run2016F_FebReminiAOD2",
    /*"EG_Run2016G_FebReminiAOD",
    "EG_Run2016H_FebReminiAODv2",
    "EG_Run2016H_FebReminiAODv3",*/
    "EG_Run2016G_SepRereco",                                                                            
    "EG_Run2016H_PRv2",                                                                                  
    "EG_Run2016H_PRv3",
    "Mu_Run2016B_FebReminiAOD",
    "Mu_Run2016C_FebReminiAOD",
    "Mu_Run2016D_FebReminiAOD",
    "Mu_Run2016E_FebReminiAOD",
    "Mu_Run2016F_FebReminiAOD1",
    "Mu_Run2016F_FebReminiAOD2",
    /*"Mu_Run2016G_FebReminiAOD",
    "Mu_Run2016H_FebReminiAODv2",
    "Mu_Run2016H_FebReminiAODv3",*/
    "Mu_Run2016G_SepRereco",                                                                            
    "Mu_Run2016H_PRv2",                                                                                  
    "Mu_Run2016H_PRv3",
    };
  
  Float_t Lumi           = 35.9E03; // fb-1 --2016full dataset
  char inpath[200];
  int isGH;
  for (int i = 0;i < 18 ; i++){
    sprintf(inpath,"/data7/milee/job_Double%s/ggtree_data_*.root",sample[i].c_str());
    
    //        if(i==3)continue;
    //if(i<9)sprintf(inpath, "/data1/ggNtuples/V08_00_26_05/skim/job_Double%s.root",sample[i].c_str());
    //else sprintf(inpath, "/data1/ggNtuples/V08_00_26_05/skim/job_Double%s.root",sample[i].c_str());
    //if(i<9)sprintf(inpath, "/data1/ggNtuples/V08_00_26_07/job_Double%s/*.root",sample[i].c_str());
    //else sprintf(inpath, "/data1/ggNtuples/V08_00_26_07/job_Double%s/*.root",sample[i].c_str());

    TString outname = "Data_VBFMVA_kinfit";
    //TString outname = "Data_dbtag";
    TString outpathEle     =  "../outfile/" + outname + "_ele_" + sample[i].c_str() + ".root";;
    TString outpathMu      =  "../outfile/" + outname + "_mu_" + sample[i].c_str() + ".root";
    Float_t xsection = 1.;
    Int_t negativeWeight = 0;
    Int_t photonRemoval = 0;
    bool muonCorrection = false;
    bool isSignal = false;
    bool isMVA = true;
    bool isVBF = true;
    cout<<"processing : "<<inpath<<endl;

    if(i<9)main_ana(inpath, outpathEle, 0, xsection, Lumi, negativeWeight, photonRemoval, muonCorrection, isSignal,isMVA,isVBF,1);
    cout<<outpathEle<<" is finished"<<endl;
    if(i>=9)main_ana(inpath, outpathMu, 1, xsection, Lumi, negativeWeight, photonRemoval, muonCorrection, isSignal,isMVA,isVBF,1);
    cout<<outpathMu<<" is finished"<<endl;

    }
}
