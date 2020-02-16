#include "../plugin/untuplizer_07.h"
#include "../plugin/puweicalc.h"

void phocor_mmg(string run, TString period, float xs)
{
    float lumi;
    if(period.Contains("16"))lumi=35.9e3;
    else if(period.Contains("17"))lumi=42.5e3;
    else lumi=52.5e3;
  TreeReader data(Form("%s/ggtree_*.root",run.c_str()));
  TFile *f ;
  TTree *tnp;
  float phoMVA_,phores_,phoEta_,phoR9_,phoPt_,phoPhi_,mll,mcwei,genwei,puwei;
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
  f = new TFile(Form("%s_photonTnP_mmg.root",period.Data()),"recreate");
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
  tnp->Branch("puwei",  &puwei, "puwei/F");
  PUWeightCalculator puCalc;
  if(period.Contains("16"))puCalc.Init("../puwei/80X_puwei/36p0_invfb/PU_histo_13TeV_2016_GoldenJSON_69200nb.root");
  if(period.Contains("17"))puCalc.Init("../puwei/94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_72383nb.root");
  if(period.Contains("18")) puCalc.Init("../puwei/102X_puwei/fall17to2018/PU_histo_13TeV_2017to2018_GoldenJSON_75730nb.root");
  for(Long64_t ev = 0 ; ev< data.GetEntriesFast(); ev++)
    {
      data.GetEntry(ev);
      if (ev % 5000000 == 0)
        {
          fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
        if (data.HasMC())
        {
            float generatorWeight = data.GetFloat("genWeight");
            genwei = (generatorWeight > 0) ? 1. : -1.;
              float* puTrue = data.GetPtrFloat("puTrue");
          Int_t run_   = data.GetInt("run");
          puwei     = (float) puCalc.GetWeight(run_, puTrue[1]); // in-time PU  
        }
      Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
      Int_t   *muIDbit = data.GetPtrInt("muIDbit");
      float   *muPt    = data.GetPtrFloat("muPt");
      float   *muEta    = data.GetPtrFloat("muEta");
      float   *muPhi    = data.GetPtrFloat("muPhi");
      Int_t   nMu      = data.GetInt("nMu");
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
      if((HLTEleMuX >>  14 & 1)==0) continue;  
      if(nMu<2||nPho<1) continue;
      int passtight = 0;
      TLorentzVector lep[2], Z,pho,llg;
      for(int i = 0 ; i < nMu; i++)
	{
	   if(muPt[i]<10) continue;
	  if(fabs(muEta[i])>2.4)continue;
	  if((muIDbit[i]>>3&1)==0)continue;
	  passtight++;
	  if(passtight==1)lep[0].SetPtEtaPhiM(muPt[i],muEta[i],muPhi[i],105.7*0.001);
	  else lep[1].SetPtEtaPhiM(muPt[i],muEta[i],muPhi[i],105.7*0.001);
	  if(passtight==2) break;
	}
      Z = lep[0]+lep[1];
      if(passtight<2) continue;
      int withpho =0;
      int phoid =-99;
      
      for(int j =0; j < nPho; j++)
	{
	  if(phoEt[j]<15) continue;
	  if(fabs(phoSCEta[j])>2.5)continue;
	  if(fabs(phoSCEta[j])<1.566&&fabs(phoEta[j])>1.4442)continue;
	  if (fabs(phoSCEta[j])<1.4442&&phoIDMVA[j] < -0.02) continue;                                          
	  if (fabs(phoSCEta[j])>1.566&&phoIDMVA[j] < -0.26) continue; 
	  withpho++;
	  pho.SetPtEtaPhiM(phoEt[j],phoEta[j],phoPhi[j],0.);
	  if(pho.DeltaR(lep[0])>0.8&&pho.DeltaR(lep[1])>0.8)continue;
	  if(pho.DeltaR(lep[0])>0.1&&pho.DeltaR(lep[1])>0.1)continue;
	  //if(pho.DeltaR(lep[0])<0.1&&pho.DeltaR(lep[1])<0.1)continue;
	  phoid=j;
	  if(withpho>0) break;
	}
      int lt = (pho.DeltaR(lep[0])<pho.DeltaR(lep[1])) ? 1:0;
      if(lep[lt].Pt()<20)continue;
      llg = lep[0] + lep[1] +pho;
      if(phoid==-99)continue;
      //if(llg.M()>100.)continue;
      //if(llg.M()<80.)continue;
      if(llg.M()+Z.M()>180)continue;
      mll = llg.M();
      phoMVA_ = phoIDMVA[phoid];
      phores_ = phoSigmaE[phoid]/phoE[phoid];
      phoPt_ = phoEt[phoid];
      phoEta_ = phoEta[phoid];
      phoPhi_ = phoPhi[phoid];
      phoR9_ = phoR9[phoid];
      tnp->Fill();

    }
  tnp->Write();
}
