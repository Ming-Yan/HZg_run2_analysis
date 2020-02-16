#include "plugin/untuplizer_07.h"
#include "plugin/puweicalc.h"

void EGMTnP_cut(string run, string period ,float xs,bool tree=false)
{
  float lumi;
  if(period==16)lumi=35.9e3;
  else if(period==17)lumi=42.5e3;
  else lumi=52.5e3;
  TreeReader data(Form("%s/ggtree_*.root",run.c_str()));
  int nondZ = 0, dZ = 0;
  Float_t cut_mva[3]  = {-0.145237,-0.0315746,-0.032173 };//MVA electron ID
 
  TFile *f ;
  TTree *tnp;
  float phoMVA_,phores_,phoEta_,phoR9_,phoPt_,phoPhi_,mll,genwei,mcwei,puwei;
  //if(tree)
  //{
  int totalEvents=0;
  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {

      data.GetEntry(ev);
      if (data.HasMC())
	{
	  float genWeight = data.GetFloat("genWeight");
	  if (genWeight > 0) totalEvents++;
	  else totalEvents--;
	}
    }
  mcwei = (totalEvents != 0) ? (xs * lumi / totalEvents) : 1.;
  

  f = new TFile(Form("%s_photonTnP.root",period.c_str()),"recreate");
  tnp = new TTree("tnp", "TnP tree for photon variables");
  tnp->Branch("phoPt", &phoPt_, "phoPt/F");
  tnp->Branch("phoEta", &phoEta_, "phoEta/F");
  tnp->Branch("phoPhi", &phoPhi_, "phoPhi/F");
  tnp->Branch("phoMVA", &phoMVA_, "phoMVA/F");
  tnp->Branch("phores", &phores_, "phores/F");
  tnp->Branch("phoR9", &phoR9_, "phoR9/F");
  tnp->Branch("mll",    &mll, "mll/F");
  tnp->Branch("genwei", &genwei, "genwei/F");
  tnp->Branch("mcwei", &mcwei, "mcwei/F");
  tnp->Branch("puwei", &puwei, "puwei/F");
  PUWeightCalculator puCalc;
  // if(period==16)
    // puCalc.Init("puwei/80X_puwei/36p0_invfb/PU_histo_13TeV_2016_GoldenJSON_69200nb.root");
  // if(period==17)
    // puCalc.Init("puwei/94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_72383nb.root");
  // if(period==18)
    puCalc.Init("puwei/102X_puwei/fall17to2018/PU_histo_13TeV_2017to2018_GoldenJSON_75730nb.root");
  //}
  int totalev;
  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
      data.GetEntry(ev);
      if (ev % 5000000 == 0)
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
      float* eleSCPhi           = data.GetPtrFloat("eleSCPhi");
      float* eleSCEta         = data.GetPtrFloat("eleSCEta");
      float* elePt            = data.GetPtrFloat("eleCalibPt");
      float* eleIDMVAIso      = data.GetPtrFloat("eleIDMVAIso");
      float* eleD0 = data.GetPtrFloat("eleD0");
      float* eleDz = data.GetPtrFloat("eleDz");
      float* eleSIP = data.GetPtrFloat("eleSIP");
      int  * eleCharge = data.GetPtrInt("eleCharge");

      Int_t  nPho       = data.GetInt("nPho");                                                           

      float *phoEt      = data.GetPtrFloat("phoCalibEt");
      float *phoE      = data.GetPtrFloat("phoCalibE");
      float *phoEta     = data.GetPtrFloat("phoEta");
      float *phoPhi     = data.GetPtrFloat("phoPhi");
      float *phoSCPhi     = data.GetPtrFloat("phoSCPhi");
      float* phoSCEta   = data.GetPtrFloat("phoSCEta");
      float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
      float* phoSigmaE  = data.GetPtrFloat("phoSigmaE");
      float* phoR9      = data.GetPtrFloat("phoR9Full5x5");
      Int_t* phoEleVeto = data.GetPtrInt("phoEleVeto");
      if (data.HasMC())
        {
	  float generatorWeight = data.GetFloat("genWeight");
	  genwei = (generatorWeight > 0) ? 1. : -1.;
       float* puTrue = data.GetPtrFloat("puTrue");
          Int_t run_   = data.GetInt("run");
          puwei     = (float) puCalc.GetWeight(run_, puTrue[1]); // in-time PU      
	}
      else genwei=1.;
      if (nEle<2)continue;
      TLorentzVector tag_e, e1, Z;
      int istag=-99;

      // if((HLTEleMuX >>  1 & 1)==0) continue;      
      if((HLTEleMuX >>  3 & 1)==0) continue;      
      // if((HLTEleMuX >>  40 & 1)==0&&(HLTEleMuX >>  5 & 1)==0)continue;
      //if((HLTEleMuX >>  40 & 1)==0) continue;
      ///select tag
      for(int i = 0 ; i < nEle;  i++)
	{
	  if(elePt[i]<35)continue;
	  if(fabs(eleEta[i])>2.5)continue;
	  if(eleIDMVAIso[i]<0.92)continue;
	  if((eleFiredSingleTrgs[i]>>13)==0)continue;
	  //if((eleFiredSingleTrgs[i]>>12)==0)continue;
	  // if((eleFiredSingleTrgs[i]>>11)==0)continue;
	  //if((eleFiredL1Trgs[i]>>2)==0)continue;
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
	  
	  // e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],0.511*0.001);
	  for(int j = 0 ; j < nPho; j++)
	    {
	     
	      if(phoSCEta[j]!=eleSCEta[j])continue;
	      if(phoSCPhi[j]!=eleSCPhi[j])continue;
	      if(phoEt[j]<15.)continue;
	      if (fabs(phoSCEta[j])<1.4442&&phoIDMVA[j] < -0.02) continue; //fallv2                       
	      if (fabs(phoSCEta[j])>1.566&&phoIDMVA[j] < -0.26) continue; //fallv2     
	      
		if(tmppho<phoEt[j]) {tmppho = phoEt[j]; phoid = j; }
    }
	  if(phoid==-99) continue;
	  e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],0.511*0.001);      
	  Z = e1+tag_e;
	}
      
      if(Z.M()<80||Z.M()>100.)continue;    
      mll = Z.M();
      phoMVA_ = phoIDMVA[phoid];
      phores_ = phoSigmaE[phoid]/phoE[phoid];
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
