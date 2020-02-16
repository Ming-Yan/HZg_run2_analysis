// #include "plugin/untuplizer_07.h"
void EGMTnP_cut18(string run,string run1, string tname, string period ,bool tree=false)
{
  float lumi;
  if(period==16)lumi=35.9e3;
  else if(period==17)lumi=42.5e3;
  else lumi=52.5e3;
  // TreeReader data(Form("%s.root",run.c_str()));
  TFile *f1 = TFile::Open(Form("%s.root",run.c_str()));
  TTree *data = (TTree*)f1->Get("tnpPhoIDs/fitter_tree");
  TFile *f2 = TFile::Open(Form("%s.root",run1.c_str()));
  TTree *t2 = (TTree*) f2->Get(tname.c_str());
  float pair_mass, tag_Ele_abseta, tag_Ele_pt,tag_Ele_q,event_met_pfmet,event_met_pfphi,ph_abseta,ph_et,ph_full5x5x_r9,ph_mva,tag_Ele_nonTrigMVA,tag_Ele_trigMVA,ph_mva94X;
  double totWeight;
  data->SetBranchAddress("pair_mass", &pair_mass);
  data->SetBranchAddress("tag_Ele_abseta",  &tag_Ele_abseta);
  // data->SetBranchAddress("tag_Ele_q", &tag_Ele_q);
  data->SetBranchAddress("tag_Ele_pt",  &tag_Ele_pt);
  data->SetBranchAddress("tag_Ele_trigMVA",  &tag_Ele_trigMVA);
  // data->SetBranchAddress("tag_Ele_nonTrigMVA",  &tag_Ele_nonTrigMVA);
  // data->SetBranchAddress("event_met_pfphi", &ta)
  data->SetBranchAddress("ph_abseta", &ph_abseta);
  //data->SetBranchAddress("ph_mva94X",    &ph_mva94X);
  // data->SetBranchAddress("ph_mva",    &ph_mva);

  data->SetBranchAddress("ph_full5x5x_r9",  &ph_full5x5x_r9);
  data->SetBranchAddress("ph_et",     &ph_et);
  t2->SetBranchAddress("totWeight", &totWeight);
  data->AddFriend(t2);
  int nondZ = 0, dZ = 0;
  Float_t cut_mva[3]  = {-0.145237,-0.0315746,-0.032173 };//MVA electron ID
 
  TFile *f ;
  TTree *tnp;
  float phoMVA_,phores_,phoEta_,phoR9_,phoPt_,phoPhi_,mll,mcwei,genwei,puwei;
  //if(tree)
  //{
  f = new TFile(Form("%s_photonTnP.root",period.c_str()),"recreate");
  tnp = new TTree("tnp", "TnP tree for photon variables");
  tnp->Branch("phoPt", &phoPt_, "phoPt/F");
  tnp->Branch("phoEta", &phoEta_, "phoEta/F");
  // tnp->Branch("phoPhi", &phoPhi_, "phoPhi/F");
  tnp->Branch("phoMVA", &phoMVA_, "phoMVA/F");
  // tnp->Branch("phores", &phores_, "phores/F");
  tnp->Branch("phoR9", &phoR9_, "phoR9/F");
  tnp->Branch("mll",    &mll, "mll/F");
  tnp->Branch("genwei", &genwei, "genwei/F");
  tnp->Branch("mcwei", &mcwei, "mcwei/F");
  tnp->Branch("puwei", &puwei, "puwei/F");
  mcwei = 6077.22*lumi/data->GetEntriesFast();
  genwei = 1.;

  //}
  for (Long64_t ev = 0; ev < data->GetEntriesFast(); ev++)
    {
      data->GetEntry(ev);
      if (ev % 5000000 == 0)
        {
          fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data->GetEntriesFast());
        }
      phoMVA_ = phores_ = phoEta_ = phoR9_ = phoPt_ = phoPhi_ = 0;
      if(tag_Ele_pt<35||tag_Ele_abseta>2.5) continue;
      // if(tag_Ele_nonTrigMVA<0.92) continue;
      if(tag_Ele_trigMVA<0.92) continue;

      if(ph_et<15.)continue;
      // if (ph_abseta<1.4442&&ph_mva < -0.02) continue; //fallv2                       
      // if (ph_abseta>1.566&&ph_mva < -0.26) continue; //fallv2     
      if (ph_abseta<1.4442&&ph_mva94X < -0.02) continue; //fallv2                       
      if (ph_abseta>1.566&&ph_mva94X < -0.26) continue; //fallv2  
	
      if(pair_mass<80||pair_mass>100.)continue;    
      puwei = totWeight;
      mll = pair_mass;
      phoMVA_ = ph_mva;
      // phores_ = phoSigmaE[phoid]/phoE[phoid];
      phoPt_ = ph_et;
      phoEta_ = ph_abseta;
      // phoPhi_ = phoPhi[phoid];
      phoR9_ = ph_full5x5x_r9;
      //if((HLTEleMuX >>  40 & 1)==1)nondZ++;
      //if(tree)
      tnp->Fill();
    }
  cout<<"done"<<endl;
  // cout<<run<<":    "<<nondZ<<" "<<dZ<<endl;
  //if(tree)
  tnp->Write();
}
