#include "plugin/untuplizer_07.h"
void EGMTnP_cut(string run, bool tree=false)
{
  TreeReader data(Form("%s/ggtree_*.root",run.c_str()));
  int nondZ = 0, dZ = 0;
  Float_t cut_mva[3]  = {-0.145237,-0.0315746,-0.032173 };//MVA electron ID
 
  TFile *f ;
  TTree *tnp;
  float phoMVA_,phores_,phoEta_,phoR9_,phoPt_,phoPhi_,mll;
  //if(tree)
  //{
  f = new TFile(Form("data_photonTnP.root",run.c_str()),"recreate");
  tnp = new TTree("tnp", "TnP tree for photon variables");
  tnp->Branch("phoPt", &phoPt_, "phoPt/F");
  tnp->Branch("phoEta", &phoEta_, "phoEta/F");
  tnp->Branch("phoPhi", &phoPhi_, "phoPhi/F");
  tnp->Branch("phoMVA", &phoMVA_, "phoMVA/F");
  tnp->Branch("phores", &phores_, "phores/F");
  tnp->Branch("phoR9", &phoR9_, "phoR9/F");
  tnp->Branch("mll",    &mll, "mll/F");
  //}
  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
      data.GetEntry(ev);
      if (ev % 500000 == 0)
        {
          fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
      phoMVA_ = phores_ = phoEta_ = phoR9_ = phoPt_ = phoPhi_ = 0;
      Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
      Long64_t* eleFiredSingleTrgs = (Long64_t*) data.GetPtrLong64("eleFiredSingleTrgs");
      Long64_t* eleFiredDoubleTrgs =  (Long64_t*)data.GetPtrLong64("eleFiredDoubleTrgs");
      Long64_t* eleFiredL1Trgs =  (Long64_t*)data.GetPtrLong64("eleFiredL1Trgs");
      
      Long64_t event_         = data.GetLong64("event");

      Int_t nEle  = data.GetInt("nEle");
      float* eleEta           = data.GetPtrFloat("eleEta");
      float* elePhi           = data.GetPtrFloat("elePhi");
      float* eleSCEta         = data.GetPtrFloat("eleSCEta");
      float* elePt            = data.GetPtrFloat("eleCalibPt");
      float* eleIDMVAIso      = data.GetPtrFloat("eleIDMVAIso");
      float* eleD0 = data.GetPtrFloat("eleD0");
      float* eleDz = data.GetPtrFloat("eleDz");
      float* eleSIP = data.GetPtrFloat("eleSIP");
      int  * eleCharge = data.GetPtrInt("eleCharge");

      Int_t  nPho       = data.GetInt("nPho");                                                           
      float *phoEt      = data.GetPtrFloat("phoCalibEt");
      float *phoEta     = data.GetPtrFloat("phoEta");
      float *phoPhi     = data.GetPtrFloat("phoPhi");
      float* phoSCEta   = data.GetPtrFloat("phoSCEta");
      float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
      float* phoSigmaE  = data.GetPtrFloat("phoSigmaE");
      float* phoR9      = data.GetPtrFloat("phoR9");
      Int_t* phoEleVeto = data.GetPtrInt("phoEleVeto");
      if (nEle<2)continue;
      TLorentzVector tag_e, e1, Z;
      int istag=-99;

      if((HLTEleMuX >>  1 & 1)==0) continue;      
      // if((HLTEleMuX >>  40 & 1)==0&&(HLTEleMuX >>  5 & 1)==0)continue;
      if((HLTEleMuX >>  40 & 1)==0) continue;
      ///select tag
      for(int i = 0 ; i < nEle;  i++)
	 {
	  if(elePt[i]<30)continue;
	  if(fabs(eleEta[i])>2.17)continue;
	  if(eleIDMVAIso[i]<0.92)continue;
	  if((eleFiredSingleTrgs[i]>>11)==0)continue;
	  if((eleFiredL1Trgs[i]>>2)==0)continue;
	  istag=i;
	  tag_e.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],0.511*0.001);
  	}      
    //selecting probe   
    bool passpho=false;
    float tmppho= 0.; int phoid = -99;
      for (int i = 0 ; i < nEle ; i++)
	{
	  if(i==istag)continue;
	  //if((eleFiredDoubleTrgs[i]>>2)==0&&(eleFiredDoubleTrgs[i]>>3)==0)continue;
	  if(elePt[i]<15)continue;
	  if(fabs(eleEta[i])>2.5)continue;
    if(fabs(eleEta[i])<1.566&&fabs(eleEta[i])>1.4442) continue;
    // e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],0.511*0.001);
	  for(int j = 0 ; j < nPho; j++)
    {
      if(phoEta[j]!=eleEta[i]||phoPhi[j]!=elePhi[j])continue;
      if(fabs(phoEt[j]-elePt[j])>0.1) continue;
      if (fabs(phoSCEta[j])<1.4442&&phoIDMVA[j] < -0.02) continue; //fallv2                                                                                                  
      if (fabs(phoSCEta[j])>1.566&&phoIDMVA[j] < -0.26) continue; //fallv2     
      if(tmppho<phoEt[j]) {tmppho = phoEt[j]; phoid = j; }
      }
	  e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],0.511*0.001);      
	  Z = e1+tag_e;
	}
      
      if(Z.M()<80||Z.M()>110.)continue;    
      mll = Z.M();
      phoMVA_ = phoIDMVA[phoid];
      phores_ = phoSigmaE[phoid];
      phoPt_ = phoEt[phoid];
      phoEta_ = phoEta[phoid];
      phoPhi_ = phoPhi[phoid];
      phoR9_ = phoR9[phoid];
      //if((HLTEleMuX >>  40 & 1)==1)nondZ++;
      //if(tree)
	tnp->Fill();
    }
  cout<<"done"<<endl;
  // cout<<run<<":    "<<nondZ<<" "<<dZ<<endl;
  //if(tree)
      tnp->Write();
}
