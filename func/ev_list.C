void ev_list()
{
  TFile *fmce = TFile::Open("../outfile/mc_MVA_phores_ele_HZg_ggF_125GeV_ext1.root");
  TFile *fmcm = TFile::Open("../outfile/mc_MVA_phores_mu_HZg_ggF_125GeV_ext1.root");
  TFile *fdatae = TFile::Open("../outfile/Data_MVA_phores_ele_EG_Run2016G_SepRereco.root"); 
  TFile *fdatam = TFile::Open("../outfile/Data_MVA_phores_mu_Mu_Run2016G_SepRereco.root");
  TTree *tmce = (TTree*)fmce->Get("tZg");
  TTree *tmcm = (TTree*)fmcm->Get("tZg");
  TTree *tdatae = (TTree*)fdatae->Get("tZg");
  TTree *tdatam = (TTree*)fdatam->Get("tZg");
  
  Long64_t event_; 
  Int_t lumis_,run_,cat;
  Float_t lepPt_[2],lepEta_[2],lepPhi_[2],gEta_,gPhi_,gPt_,VBFPt[2],VBFEta[2],VBFPhi[2],VBFEn[2],lepSCEta_[2],gSCEta_,gR9_;
  tmce->SetBranchAddress("event", &event_);
  tmce->SetBranchAddress("lumis", &lumis_); 
  tmce->SetBranchAddress("run", &run_);
  tmce->SetBranchAddress("cat", &cat);
  tmce->SetBranchAddress("phoR9", &gR9_);
  tmce->SetBranchAddress("phoSCEta", &gSCEta_); 
  tmce->SetBranchAddress("lepSCEta", lepSCEta_);
  tmce->SetBranchAddress("phoPt",&gPt_);
  tmce->SetBranchAddress("phoPhi",&gPhi_);
  tmce->SetBranchAddress("phoEta",&gEta_);
  tmce->SetBranchAddress("lepEta", lepEta_);
  tmce->SetBranchAddress("lepPhi", lepPhi_);
  tmce->SetBranchAddress("lepPt", lepPt_);
  tmce->SetBranchAddress("VBFEta", VBFEta);
  tmce->SetBranchAddress("VBFPhi", VBFPhi);
  tmce->SetBranchAddress("VBFPt", VBFPt);
  tmce->SetBranchAddress("VBFEn", VBFEn);
  tmcm->SetBranchAddress("event", &event_);
  tmcm->SetBranchAddress("lumis", &lumis_); 
  tmcm->SetBranchAddress("run", &run_);
  tmcm->SetBranchAddress("cat", &cat);
  tmcm->SetBranchAddress("phoPt",&gPt_);
  tmcm->SetBranchAddress("phoPhi",&gPhi_);
  tmcm->SetBranchAddress("phoEta",&gEta_);
  tmcm->SetBranchAddress("lepEta", lepEta_);
  tmcm->SetBranchAddress("lepPhi", lepPhi_);
  tmcm->SetBranchAddress("lepPt", lepPt_);
  tmcm->SetBranchAddress("VBFEta", VBFEta);
  tmcm->SetBranchAddress("VBFPhi", VBFPhi);
  tmcm->SetBranchAddress("VBFPt", VBFPt);
  tmcm->SetBranchAddress("VBFEn", VBFEn);
  tmcm->SetBranchAddress("phoR9", &gR9_);
  tmcm->SetBranchAddress("phoSCEta", &gSCEta_); 
  tmcm->SetBranchAddress("lepSCEta", lepSCEta_);
  tdatae->SetBranchAddress("event", &event_);
  tdatae->SetBranchAddress("lumis", &lumis_); 
  tdatae->SetBranchAddress("run", &run_);
  tdatae->SetBranchAddress("cat", &cat);
  tdatae->SetBranchAddress("phoPt",&gPt_);
  tdatae->SetBranchAddress("phoPhi",&gPhi_);
  tdatae->SetBranchAddress("phoEta",&gEta_);
  tdatae->SetBranchAddress("lepEta", lepEta_);
  tdatae->SetBranchAddress("lepPhi", lepPhi_);
  tdatae->SetBranchAddress("lepPt", lepPt_);
  tdatae->SetBranchAddress("VBFEta", VBFEta);
  tdatae->SetBranchAddress("VBFPhi", VBFPhi);
  tdatae->SetBranchAddress("VBFPt", VBFPt);
  tdatae->SetBranchAddress("VBFEn", VBFEn);
  tdatae->SetBranchAddress("phoR9", &gR9_);
  tdatae->SetBranchAddress("phoSCEta", &gSCEta_); 
  tdatae->SetBranchAddress("lepSCEta", lepSCEta_);
  tdatam->SetBranchAddress("event", &event_);
  tdatam->SetBranchAddress("lumis", &lumis_); 
  tdatam->SetBranchAddress("run", &run_);
  tdatam->SetBranchAddress("cat", &cat);
  tdatam->SetBranchAddress("phoPt",&gPt_);
  tdatam->SetBranchAddress("phoPhi",&gPhi_);
  tdatam->SetBranchAddress("phoEta",&gEta_);
  tdatam->SetBranchAddress("lepEta", lepEta_);
  tdatam->SetBranchAddress("lepPhi", lepPhi_);
  tdatam->SetBranchAddress("lepPt", lepPt_);
  tdatam->SetBranchAddress("VBFEta", VBFEta);
  tdatam->SetBranchAddress("VBFPhi", VBFPhi);
  tdatam->SetBranchAddress("VBFPt", VBFPt);
  tdatam->SetBranchAddress("VBFEn", VBFEn);
  tdatam->SetBranchAddress("phoR9", &gR9_);
  tdatam->SetBranchAddress("phoSCEta", &gSCEta_); 
  tdatam->SetBranchAddress("lepSCEta", lepSCEta_);
  ofstream mcecat1("evlists/ggF_ele/cat1.txt");
  ofstream mcecat2("evlists/ggF_ele/cat2.txt");
  ofstream mcecat3("evlists/ggF_ele/cat3.txt");
  ofstream mcecat4("evlists/ggF_ele/cat4.txt");
  ofstream mcecat5("evlists/ggF_ele/cat_dijet.txt");
  ofstream mcecat6("evlists/ggF_ele/cat_leptag.txt");
  ofstream mcecat10("evlists/ggF_ele/catboost.txt");

  for (Long64_t ev = 0 ; ev < tmce->GetEntriesFast() ; ev++)
    {
      tmce->GetEntry(ev);
      if(cat==5)cout<<VBFPt[0]<<" "<<VBFEta[0]<<" "<<VBFPhi[0]<<" "<<endl;
      if(cat==1)mcecat1<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==2)mcecat2<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==3)mcecat3<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==4)mcecat4<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==5)mcecat5<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<VBFPt[0]<<" "<<VBFEta[0]<<" "<<VBFPhi[0]<<" "<<VBFEn[0]<<" "<<VBFPt[1]<<" "<<VBFEta[1]<<" "<<VBFPhi[1]<<" "<<VBFEn[1]<<endl;
      if(cat>5&&cat<10)mcecat6<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
      if(cat==10)mcecat10<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
    }
  cout<<"done MC ele"<<endl;
  ofstream mcmcat1("evlists/ggF_mu/cat1.txt");
  ofstream mcmcat2("evlists/ggF_mu/cat2.txt");
  ofstream mcmcat3("evlists/ggF_mu/cat3.txt");
  ofstream mcmcat4("evlists/ggF_mu/cat4.txt");
  ofstream mcmcat5("evlists/ggF_mu/cat_dijet.txt");
  ofstream mcmcat6("evlists/ggF_mu/cat_leptag.txt");
  ofstream mcmcat10("evlists/ggF_mu/catboost.txt");
  for(Long64_t ev = 0 ; ev < tmcm->GetEntriesFast() ; ev++)
    {
      tmcm->GetEntry(ev);
      if(cat==1)mcmcat1<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;;
      if(cat==2)mcmcat2<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;;
      if(cat==3)mcmcat3<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;;
      if(cat==4)mcmcat4<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;;
      if(cat==5)mcmcat5<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<VBFPt[0]<<" "<<VBFEta[0]<<" "<<VBFPhi[0]<<" "<<VBFEn[0]<<" "<<VBFPt[1]<<" "<<VBFEta[1]<<" "<<VBFPhi[1]<<" "<<VBFEn[1]<<endl;
      if(cat>5&&cat<10)mcmcat6<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
      if(cat==10)mcmcat10<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
    }
  cout<<"done MC mu"<<gR9_<<" "<<gSCEta_<<endl;;
  ofstream dataecat1("evlists/data_ele/cat1.txt");
  ofstream dataecat2("evlists/data_ele/cat2.txt");
  ofstream dataecat3("evlists/data_ele/cat3.txt");
  ofstream dataecat4("evlists/data_ele/cat4.txt");
  ofstream dataecat5("evlists/data_ele/cat_dijet.txt");
  ofstream dataecat6("evlists/data_ele/cat_leptag.txt");
  ofstream dataecat10("evlists/data_ele/catboost.txt");
  for (Long64_t ev = 0 ; ev < tdatae->GetEntriesFast() ; ev++)
    {
      tdatae->GetEntry(ev);
      if(cat==1)dataecat1<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==2)dataecat2<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==3)dataecat3<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==4)dataecat4<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<" "<<lepSCEta_[0]<<" "<<lepSCEta_[1]<<endl;
      if(cat==5)dataecat5<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<VBFPt[0]<<" "<<VBFEta[0]<<" "<<VBFPhi[0]<<" "<<VBFEn[0]<<" "<<VBFPt[1]<<" "<<VBFEta[1]<<" "<<VBFPhi[1]<<" "<<VBFEn[1]<<endl;
      if(cat>5&&cat<10)dataecat6<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
      if(cat==10)dataecat10<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
    }
  cout<<"done data ele"<<endl;
  ofstream datamcat1("evlists/data_mu/cat1.txt");
  ofstream datamcat2("evlists/data_mu/cat2.txt");
  ofstream datamcat3("evlists/data_mu/cat3.txt");
  ofstream datamcat4("evlists/data_mu/cat4.txt");
  ofstream datamcat5("evlists/data_mu/cat_dijet.txt");
  ofstream datamcat6("evlists/data_mu/cat_leptag.txt");
  ofstream datamcat10("evlists/data_mu/catboost.txt");
  for (Long64_t ev = 0 ; ev < tdatam->GetEntriesFast() ; ev++)
    {
      tdatam->GetEntry(ev);
      if(cat==1)datamcat1<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;
      if(cat==2)datamcat2<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;
      if(cat==3)datamcat3<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;
      if(cat==4)datamcat4<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<gR9_<<" "<<gSCEta_<<endl;
      if(cat==5)datamcat5<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<" "<<VBFPt[0]<<" "<<VBFEta[0]<<" "<<VBFPhi[0]<<" "<<VBFEn[0]<<" "<<VBFPt[1]<<" "<<VBFEta[1]<<" "<<VBFPhi[1]<<" "<<VBFEn[1]<<endl;
      if(cat>5&&cat<10)datamcat6<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
      if(cat==10)datamcat10<<run_<<" "<<lumis_<<" "<<event_<<" "<<lepPt_[0]<<" "<<lepEta_[0]<<" "<<lepPhi_[0]<<" "<<lepPt_[1]<<" "<<lepEta_[1]<<" "<<lepPhi_[1]<<" "<<gPt_<<" "<<gEta_<<" "<<gPhi_<<endl;
    }
  cout<<"done data mu"<<endl;
}
