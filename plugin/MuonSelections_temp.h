//no skim file
using namespace std;

void TightMuons2015(TreeReader &data, vector<int> &accepted, vector<int> &Zmumu, bool corr,  Int_t channel){
  Zmumu.clear();
  vector<int> tmpmu;
  tmpmu.clear(); 
  accepted.clear();

  Int_t  nMu         = data.GetInt("nMu");
  float* muPt        = data.GetPtrFloat("muCalibPt");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  float* muPFChIso   = data.GetPtrFloat("muPFChIso");
  float* muPFPhoIso  = data.GetPtrFloat("muPFPhoIso");
  float* muPFNeuIso  = data.GetPtrFloat("muPFNeuIso");
  float* muPFPUIso   = data.GetPtrFloat("muPFPUIso");
   UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
   
  for (int i = 0; i < nMu; ++i){


    if (muPt[i] < 5. ) continue;    ///loose the pt cut for additional leptons 10->5
    if (fabs(muEta[i]) > 2.4) continue;

    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6

    if ((muIDbit[i] >> 2 & 1) == 0) continue;

    if (fabs(muD0[i]) > 0.2) continue;
    if (fabs(muDz[i]) > 0.5) continue;


    if(muPt[i] >= 10.){    
      if((muPFChIso[i] + TMath::Max(0., muPFPhoIso[i] + muPFNeuIso[i] -0.5 * muPFPUIso[i]))/muPt[i] > 0.25) continue;//loose combine iso
    }

    else if(muPt[i]<10)
      {
	if ((muPFChIso[i] + TMath::Max(0., muPFPhoIso[i] + muPFNeuIso[i] -0.5 * muPFPUIso[i]))/muPt[i] > 0.15) continue;//tight combine iso
      }
    //    muIso.push_back((muPFChIso[i] + TMath::Max(0., muPFPhoIso[i] + muPFNeuIso[i] -0.5 * muPFPUIso[i]))/muPt[i]);
    tmpmu.push_back(i);
  }

  //electron channel-assign the leading muon pt as additional lepton
  if(channel==0) accepted.assign(tmpmu.begin(), tmpmu.end());
  //muon channel - remove the same event of Z
  if(channel==1)
    {

      TLorentzVector  t1,t2,tz, mu1,mu2,z;
      //select Z with closest to nominal Z mass                                                                                                    
      if(tmpmu.size() >=2){
	int ie = tmpmu[0];
	int je = tmpmu[1];
	mu1.SetPtEtaPhiM(muPt[tmpmu[0]],muEta[tmpmu[0]],muPhi[tmpmu[0]],105.658*0.001);
	mu2.SetPtEtaPhiM(muPt[tmpmu[1]],muEta[tmpmu[1]],muPhi[tmpmu[1]],105.658*0.001);
	z = mu1+mu2;
	for(unsigned int i = 0; i < tmpmu.size(); ++i)
	  {
	    if(muPt[tmpmu[i]]<10.) continue;
	    t1.SetPtEtaPhiM(muPt[tmpmu[i]],muEta[tmpmu[i]],muPhi[tmpmu[i]],105.658*0.001);
	    for(unsigned int j = 0 ; j < i; ++j)
	      {
		if(muPt[tmpmu[j]]<10.) continue;
		t2.SetPtEtaPhiM(muPt[tmpmu[j]],muEta[tmpmu[j]],muPhi[tmpmu[j]],105.658*0.001);
		tz = t1 + t2;
		if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
		  {
		    mu1 = t1;
		    mu2 = t2;
		    z = mu1+mu2;
		    ie = tmpmu[i];
		    je = tmpmu[j];
		  }
	      }
	  }
	
	Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? ie : je );
	Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? je : ie );
	for(unsigned int  i = 0 ; i < tmpmu.size(); i++)
	  {
	    if(tmpmu[i]==je||tmpmu[i]==ie) continue;
	    accepted.push_back(tmpmu[i]);
	  }
      }
      else accepted.push_back(1);
    } 

}


/*void HZZmuIDforZg(TreeReader &data, vector<int> &accepted, vector<int> &Zmumu, vector<float> &muPt, Int_t channel){
  Zmumu.clear();
  vector<int> tmpmu;
  tmpmu.clear();
  vector<int>tmptmpmu;
  tmptmpmu.clear();
  accepted.clear();

  Int_t  nMu         = data.GetInt("nMu");
  // float* muPt   = data.GetPtrFloat("muCalibPt");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  float* muPFChIso03   = data.GetPtrFloat("muPFChIso03");
  float* muPFPhoIso03  = data.GetPtrFloat("muPFPhoIso03");
  float* muPFNeuIso03  = data.GetPtrFloat("muPFNeuIso03");
  float* muPFPUIso03   = data.GetPtrFloat("muPFPUIso03");
  UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
  Long64_t  event_        = data.GetLong64("event");
  
  //loose muon 
  Int_t* muBestTrkType = data.GetPtrInt("muBestTrkType");
  float* muBestTrkPt = data.GetPtrFloat("muBestTrkPt");
  float* muBestTrkPtError = data.GetPtrFloat("muBestTrkPtError");
  float* muSIP = data.GetPtrFloat("muSIP");
  Int_t* muStations = data.GetPtrInt("muStations");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muType      = data.GetPtrInt("muType");

  for (int i = 0; i < nMu; ++i){

    if (muPt[i] < 5. ) continue;    ///loose the pt cut for additional leptons 10->5
    if (fabs(muEta[i]) > 2.4) continue;

    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h

    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6

    /// loose muon(general cuts)

    if (muSIP[i]>4.) continue; 
    if (fabs(muD0[i]) > 0.5) continue;
    if (fabs(muDz[i]) > 1.) continue;    
    if (((muType[i] >> 1 & 1) == 0)&&((muType[i] >> 2 & 1) == 0&& muStations[i] >0))continue;
    if (muBestTrkType[i]==2) continue;
    if (muPt[i]<200&&(muType[i] >> 5 & 1) == 0 )continue;
    if(muPt[i]>200.)
      {
	if ((muType[i] >> 5 & 1)== 0)
	  {
	    if ((muType[i] >> 2 & 1)== 0) continue;
	    if (muBestTrkPtError[i]/muBestTrkPt[i]>=0.3) continue;
	    if (muStations[i] <2) continue;
	    if (fabs(muD0[i]) >= 0.2) continue;
	    if (fabs(muDz[i]) >= 0.5) continue;
	    if (muPixelHits[i]<=0) continue;
	    if (muTrkLayers[i]<=5) continue;
	  }
      }
    if((muPFChIso03[i] + TMath::Max(0., muPFPhoIso03[i] + muPFNeuIso03[i] -0.5 * muPFPUIso03[i]))/muPt[i] > 0.35) continue;//HZZ iso
    tmptmpmu.push_back(i);
  }
  //remove the dPhi problem muon for 2016 analysis
  TLorentzVector tmpmu1,tmpmu2;  
  for (unsigned int j = 0; j < tmptmpmu.size();j++)
    {
      tmpmu1.SetPtEtaPhiM(muPt[tmptmpmu[j]],muEta[tmptmpmu[j]],muPhi[tmptmpmu[j]],105.7*0.001);
      for(unsigned int k = j+1; k < tmptmpmu.size();k++)
	{
	  tmpmu2.SetPtEtaPhiM(muPt[tmptmpmu[k]],muEta[tmptmpmu[k]],muPhi[tmptmpmu[k]],105.7*0.001);
	  if (tmpmu1.Eta()*tmpmu2.Eta()>0&&fabs(tmpmu1.Eta())>1.2&&fabs(tmpmu2.Eta())>1.2&&fabs(tmpmu1.DeltaPhi(tmpmu2)) < 70.*3.14/180.) continue;

	  else 
	    {
	      tmpmu.push_back(tmptmpmu[k]);
	      tmpmu.push_back(tmptmpmu[j]);
	    }
	}	
    }
	
  //electron channel-assign the leading muon pt as additional lepton
  if(channel==0) accepted.assign(tmptmpmu.begin(), tmptmpmu.end());
  int tmpie,tmpje;  //muon channel - remove the same event of Z
  if(channel==1)
    {
      TLorentzVector  t1,t2,tz, mu1,mu2,z;
      //select Z with closest to nominal Z mass                                                                                                    
      if(tmpmu.size() >=2){
	int ie = tmpmu[0];
	int je = tmpmu[1];
	mu1.SetPtEtaPhiM(muPt[tmpmu[0]],muEta[tmpmu[0]],muPhi[tmpmu[0]],105.658*0.001);
	mu2.SetPtEtaPhiM(muPt[tmpmu[1]],muEta[tmpmu[1]],muPhi[tmpmu[1]],105.658*0.001);
	z = mu1+mu2;
	for(unsigned int i = 0; i < tmpmu.size(); ++i)
	  {
	    if(muPt[tmpmu[i]]<10.) continue;
	    t1.SetPtEtaPhiM(muPt[tmpmu[i]],muEta[tmpmu[i]],muPhi[tmpmu[i]],105.658*0.001);

	    for(unsigned int j = i+1 ; j < tmpmu.size(); ++j)
	      {
		if(tmpmu[i]==tmpmu[j]) continue;
		if(muPt[tmpmu[j]]<10.) continue;
		t2.SetPtEtaPhiM(muPt[tmpmu[j]],muEta[tmpmu[j]],muPhi[tmpmu[j]],105.658*0.001);
		tz = t1 + t2;
		if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
		  {
		    mu1 = t1;
		    mu2 = t2;
		    z = mu1+mu2;
		    ie = tmpmu[i];
		    je = tmpmu[j];
		  }
	      }
	  }
	
	Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? ie : je );
	Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? je : ie );
	for(unsigned int  i = 0 ; i < tmpmu.size(); i++)
	  {
	    if(tmpmu[i]==je||tmpmu[i]==ie) continue;
	    accepted.push_back(tmpmu[i]);
	  }
      }
      else accepted.push_back(1);
      } 
}*/
void HZZmuID16forZg(TreeReader &data, vector<int> &accepted, vector<int> &Zmumu, vector<float> &muPt,Int_t channel, vector<TLorentzVector> &multz){
  Zmumu.clear();
  vector<int> tmpmu;
  tmpmu.clear();
 
  vector<int>tmptmpmu;
  tmptmpmu.clear();
  accepted.clear();

  multz.clear();
  Int_t  nMu         = data.GetInt("nMu");
  // float* muPt   = data.GetPtrFloat("muCalibPt");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  float* muPFChIso03   = data.GetPtrFloat("muPFChIso03");
  float* muPFPhoIso03  = data.GetPtrFloat("muPFPhoIso03");
  float* muPFNeuIso03  = data.GetPtrFloat("muPFNeuIso03");
  float* muPFPUIso03   = data.GetPtrFloat("muPFPUIso03");
  UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
  Long64_t  event_        = data.GetLong64("event");
  
  //loose muon 
  Int_t* muBestTrkType = data.GetPtrInt("muBestTrkType");
  float* muBestTrkPt = data.GetPtrFloat("muBestTrkPt");
  float* muBestTrkPtError = data.GetPtrFloat("muBestTrkPtError");
  float* muSIP = data.GetPtrFloat("muSIP");
  Int_t* muStations = data.GetPtrInt("muStations");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muType      = data.GetPtrInt("muType");
 
  for (int i = 0; i < nMu; ++i){
 
    if (muPt[i] < 5. ) continue;    ///loose the pt cut for additional leptons 10->5
    if (fabs(muEta[i]) > 2.4) continue;
 
    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
 
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6
 
    /// loose muon(general cuts)
 
    if (muSIP[i]>4.) continue; 
    if (fabs(muD0[i]) > 0.5) continue;
    if (fabs(muDz[i]) > 1.) continue;    
    if (((muType[i] >> 1 & 1) == 0)&&((muType[i] >> 2 & 1) == 0&& muStations[i] >0))continue;
 
    if (muBestTrkType[i]==2) continue;
    if (muPt[i]<200&&(muType[i] >> 5 & 1) == 0 )continue;
 
    if(muPt[i]>200.)
      {
    if ((muType[i] >> 5 & 1)== 0)
      {
        if ((muType[i] >> 2 & 1)== 0) continue;
        if (muBestTrkPtError[i]/muBestTrkPt[i]>=0.3) continue;
        if (muStations[i] <2) continue;
        if (fabs(muD0[i]) >= 0.2) continue;
        if (fabs(muDz[i]) >= 0.5) continue;
        if (muPixelHits[i]<=0) continue;
        if (muTrkLayers[i]<=5) continue;
      }
      }
 
    if((muPFChIso03[i] + TMath::Max(0., muPFPhoIso03[i] + muPFNeuIso03[i] -0.5 * muPFPUIso03[i]))/muPt[i] > 0.35) continue;//HZZ iso
    tmptmpmu.push_back(i);
  }
  //remove the dPhi problem muon for 2016 analysis
 
  TLorentzVector tmpmu1,tmpmu2;  
 
  for (unsigned int j = 0; j < tmptmpmu.size();j++)
    {
      tmpmu1.SetPtEtaPhiM(muPt[tmptmpmu[j]],muEta[tmptmpmu[j]],muPhi[tmptmpmu[j]],105.7*0.001);
      for(unsigned int k = j+1; k < tmptmpmu.size();k++)
    {
      tmpmu2.SetPtEtaPhiM(muPt[tmptmpmu[k]],muEta[tmptmpmu[k]],muPhi[tmptmpmu[k]],105.7*0.001);
      //if(tmpmu1.Pt()<20.&&tmpmu2.Pt()<20.) continue;
      if (tmpmu1.Eta()*tmpmu2.Eta()>0&&fabs(tmpmu1.Eta())>1.2&&fabs(tmpmu2.Eta())>1.2&&fabs(tmpmu1.DeltaPhi(tmpmu2)) < 70.*3.14/180.) continue;
      
      else 
        {
          tmpmu.push_back(tmptmpmu[k]);
          tmpmu.push_back(tmptmpmu[j]);
        }
    }   
    }
    
  //electron channel-assign the leading muon pt as additional lepton
  if(channel==0) accepted.assign(tmptmpmu.begin(), tmptmpmu.end());
 
  int tmpie,tmpje;  //muon channel - remove the same event of Z
  if(channel==1)
    {
      TLorentzVector  t1,t2,tz, mu1,mu2,z;
      //select Z with closest to nominal Z mass                                                                                                    
      if(tmpmu.size() >=2){
    int ie = tmpmu[0];
    int je = tmpmu[1];
    mu1.SetPtEtaPhiM(muPt[tmpmu[0]],muEta[tmpmu[0]],muPhi[tmpmu[0]],105.658*0.001);
    mu2.SetPtEtaPhiM(muPt[tmpmu[1]],muEta[tmpmu[1]],muPhi[tmpmu[1]],105.658*0.001);
    z = mu1+mu2;
    for(unsigned int i = 0; i < tmpmu.size(); ++i)
      {
        if(muPt[tmpmu[i]]<10.) continue;
        t1.SetPtEtaPhiM(muPt[tmpmu[i]],muEta[tmpmu[i]],muPhi[tmpmu[i]],105.658*0.001);
         for(unsigned int j = i+1 ; j < tmpmu.size(); ++j)
          {
        if(tmpmu[i]==tmpmu[j]) continue;
        if(muPt[tmpmu[j]]<10.) continue;
        t2.SetPtEtaPhiM(muPt[tmpmu[j]],muEta[tmpmu[j]],muPhi[tmpmu[j]],105.658*0.001);
        tz = t1 + t2;
	if(tz.M()>50.&&(t1.Pt()>20||t2.Pt()>20))multz.push_back(tz);
        if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
          {
            mu1 = t1;
            mu2 = t2;
            z = mu1+mu2;
            ie = tmpmu[i];
            je = tmpmu[j];
          }
          }
      }

    Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? ie : je );
    Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? je : ie );
    for(unsigned int  i = 0 ; i < tmpmu.size(); i++)
      {
        if(tmpmu[i]==je||tmpmu[i]==ie) continue;
        accepted.push_back(tmpmu[i]);
      }
 
      }
      else accepted.push_back(1);
      } 
}

void HZZmuID16forZg_mod(TreeReader &data, vector<int> &accepted, vector<float> &muPt,Int_t channel, vector<TLorentzVector> &multz)
{
  // Zmumu.clear();
  vector<int> tmpmu;
  tmpmu.clear();
 
  vector<int>tmptmpmu;
  tmptmpmu.clear();
  accepted.clear();
  multz.clear();
  Int_t  nMu         = data.GetInt("nMu");
  // float* muPt   = data.GetPtrFloat("muCalibPt");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  
  UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
  Long64_t  event_        = data.GetLong64("event");
  
  //loose muon 
  Int_t* muBestTrkType = data.GetPtrInt("muBestTrkType");
  float* muBestTrkPt = data.GetPtrFloat("muBestTrkPt");
  float* muBestTrkPtError = data.GetPtrFloat("muBestTrkPtError");
  float* muSIP = data.GetPtrFloat("muSIP");
  Int_t* muStations = data.GetPtrInt("muStations");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muType      = data.GetPtrInt("muType");
 
  for (int i = 0; i < nMu; ++i){
 
    if (muPt[i] < 10. ) continue;    ///loose the pt cut for additional leptons 10->5
    if (fabs(muEta[i]) > 2.4) continue;
 
    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
 
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6
 
    /// loose muon(general cuts)
 
    if (muSIP[i]>4.) continue; 
    if (fabs(muD0[i]) > 0.5) continue;
    if (fabs(muDz[i]) > 1.) continue;    
    if (((muType[i] >> 1 & 1) == 0)&&((muType[i] >> 2 & 1) == 0&& muStations[i] >0))continue;
 
    if (muBestTrkType[i]==2) continue;
    if (muPt[i]<200&&(muType[i] >> 5 & 1) == 0 )continue;
 
    if(muPt[i]>200.)
      {
    if ((muType[i] >> 5 & 1)== 0)
      {
        if ((muType[i] >> 2 & 1)== 0) continue;
        if (muBestTrkPtError[i]/muBestTrkPt[i]>=0.3) continue;
        if (muStations[i] <2) continue;
        if (fabs(muD0[i]) >= 0.2) continue;
        if (fabs(muDz[i]) >= 0.5) continue;
        if (muPixelHits[i]<=0) continue;
        if (muTrkLayers[i]<=5) continue;
      }
      }
 
    // if((muPFChIso03[i] + TMath::Max(0., muPFPhoIso03[i] + muPFNeuIso03[i] -0.5 * muPFPUIso03[i]))/muPt[i] > 0.35) continue;//HZZ iso
    tmptmpmu.push_back(i);
  }
  //remove the dPhi problem muon for 2016 analysis
 
  TLorentzVector tmpmu1,tmpmu2;  
 
  for (unsigned int j = 0; j < tmptmpmu.size();j++)
    {
      tmpmu1.SetPtEtaPhiM(muPt[tmptmpmu[j]],muEta[tmptmpmu[j]],muPhi[tmptmpmu[j]],105.7*0.001);
      for(unsigned int k = j+1; k < tmptmpmu.size();k++)
    {
      tmpmu2.SetPtEtaPhiM(muPt[tmptmpmu[k]],muEta[tmptmpmu[k]],muPhi[tmptmpmu[k]],105.7*0.001);
      //if(tmpmu1.Pt()<20.&&tmpmu2.Pt()<20.) continue;
      if (tmpmu1.Eta()*tmpmu2.Eta()>0&&fabs(tmpmu1.Eta())>1.2&&fabs(tmpmu2.Eta())>1.2&&fabs(tmpmu1.DeltaPhi(tmpmu2)) < 70.*3.14/180.) continue;
      
      else 
        {
          tmpmu.push_back(tmptmpmu[k]);
          tmpmu.push_back(tmptmpmu[j]);
        }
    }   
    }
    
  // electron channel-assign the leading muon pt as additional lepton
  if(channel==0) accepted.assign(tmptmpmu.begin(), tmptmpmu.end());
 
  // int tmpie,tmpje;  //muon channel - remove the same event of Z
  // else if(channel==1)
    // {
      // TLorentzVector  t1,t2,tz, mu1,mu2,z;
      // select Z with closest to nominal Z mass                                                                                                    
      // if(tmpmu.size() >=2){
    // int ie = tmpmu[0];
    // int je = tmpmu[1];
    // mu1.SetPtEtaPhiM(muPt[tmpmu[0]],muEta[tmpmu[0]],muPhi[tmpmu[0]],105.658*0.001);
    // mu2.SetPtEtaPhiM(muPt[tmpmu[1]],muEta[tmpmu[1]],muPhi[tmpmu[1]],105.658*0.001);
    // z = mu1+mu2;
    // for(unsigned int i = 0; i < tmpmu.size(); ++i)
      // {
        // if(muPt[tmpmu[i]]<10.) continue;
        // t1.SetPtEtaPhiM(muPt[tmpmu[i]],muEta[tmpmu[i]],muPhi[tmpmu[i]],105.658*0.001);
         // for(unsigned int j = i+1 ; j < tmpmu.size(); ++j)
          // {
        // if(tmpmu[i]==tmpmu[j]) continue;
        // if(muPt[tmpmu[j]]<10.) continue;
        // t2.SetPtEtaPhiM(muPt[tmpmu[j]],muEta[tmpmu[j]],muPhi[tmpmu[j]],105.658*0.001);
        // tz = t1 + t2;
	// if(tz.M()>50.&&(t1.Pt()>20||t2.Pt()>20))multz.push_back(tz);
        // if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
          // {
            // mu1 = t1;
            // mu2 = t2;
            // z = mu1+mu2;
            // ie = tmpmu[i];
            // je = tmpmu[j];
          // }
          // }
      // }

    // Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? ie : je );
    // Zmumu.push_back( (mu1.Pt() > mu2.Pt()) ? je : ie );
    for(unsigned int  i = 0 ; i < tmpmu.size(); i++)
      {
        // if(tmpmu[i]==je||tmpmu[i]==ie) continue;
        accepted.push_back(tmpmu[i]);
      }
 
      // }
      // else accepted.push_back(1);
      // } 
}

void HZZmuID17forZg_mod(TreeReader &data, vector<int> &accepted, vector<float> &muPt, Int_t channel){
  accepted.clear();

  Int_t  nMu         = data.GetInt("nMu");
  // float* muPt   = data.GetPtrFloat("muCalibPt");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  float* muPFChIso03   = data.GetPtrFloat("muPFChIso03");
  float* muPFPhoIso03  = data.GetPtrFloat("muPFPhoIso03");
  float* muPFNeuIso03  = data.GetPtrFloat("muPFNeuIso03");
  float* muPFPUIso03   = data.GetPtrFloat("muPFPUIso03");
  // UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
  Long64_t  event_        = data.GetLong64("event");
  
  //loose muon 
  Int_t* muBestTrkType = data.GetPtrInt("muBestTrkType");
  float* muBestTrkPt = data.GetPtrFloat("muBestTrkPt");
  float* muBestTrkPtError = data.GetPtrFloat("muBestTrkPtError");
  float* muSIP = data.GetPtrFloat("muSIP");
  Int_t* muStations = data.GetPtrInt("muStations");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muType      = data.GetPtrInt("muType");
 
  for (int i = 0; i < nMu; ++i){
 
    if (muPt[i] < 5. ) continue;    ///loose the pt cut for additional leptons 10->5
    if (fabs(muEta[i]) > 2.4) continue;
 
    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
 
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6
 
    /// loose muon(general cuts)
 
    if (muSIP[i]>4.) continue; 
    if (fabs(muD0[i]) > 0.5) continue;
    if (fabs(muDz[i]) > 1.) continue;    
    if (((muType[i] >> 1 & 1) == 0)&&((muType[i] >> 2 & 1) == 0||	muStations[i] < 1))continue;
    if (muBestTrkType[i]==2) continue;
    if (muPt[i]<200&&(muType[i] >> 5 & 1) == 0 )continue;
 
    if(muPt[i]>200.)
      {
    if ((muType[i] >> 5 & 1)== 0)
      {
        if ((muType[i] >> 2 & 1)== 0) continue;
        if (muBestTrkPtError[i]/muBestTrkPt[i]>=0.3) continue;
        if (muStations[i] <2) continue;
        if (fabs(muD0[i]) >= 0.2) continue;
        if (fabs(muDz[i]) >= 0.5) continue;
        if (muPixelHits[i]<=0) continue;
        if (muTrkLayers[i]<=5) continue;
      }
      }
 
    if((muPFChIso03[i] + TMath::Max(0., muPFPhoIso03[i] + muPFNeuIso03[i] -0.5 * muPFPUIso03[i]))/muPt[i] > 0.35) continue;//HZZ iso
    accepted.push_back(i);
  }
}
void  Lowpt16Muons (TreeReader &data, vector<int> &accepted, Int_t channel, Float_t mu1, Float_t mu2, vector<int> issoft){
  accepted. clear();
  Int_t  nMu         = data.GetInt("nMu");
  float* muPt        = data.GetPtrFloat("muPt");
  float* muEta       = data.GetPtrFloat("muEta");
  Int_t* muTrkQuality = data.GetPtrInt("muTrkQuality");
  float* muInnerD0   = data.GetPtrFloat("muInnerD0");
  float* muInnerDz   = data.GetPtrFloat("muInnerDz");
  Int_t* muType      = data.GetPtrInt("muType");
  Int_t* muMuonHits  = data.GetPtrInt("muMuonHits");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");

  int soft = 1;
  
  for (int i = 0; i < nMu; ++i){
    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6    
    if (((muType[i] >> 2 & 1) == 0)
	||muPt[i] < 2.
	||(fabs(muEta[i]) > 2.1) //stoyan's cut
	||(fabs(muInnerD0[i]) > 0.2)//stoyan's cut
	||(fabs(muInnerDz[i]) > 0.5) //stoyan's cut
	||(muPixelHits[i] == 0) 
	||(muTrkLayers[i] < 6) 
	||(muTrkQuality[i] == 0))soft = 0;
    accepted.push_back(i);
  }
}

void MediumMuons2017(TreeReader &data, vector<int> &accepted, int isGH){

  accepted.clear();

  Int_t  nMu         = data.GetInt("nMu");
  float* muPt        = data.GetPtrFloat("muPt");
  float* muEta       = data.GetPtrFloat("muEta");
  Int_t* muType      = data.GetPtrInt("muType");
  float* muChi2NDF   = data.GetPtrFloat("muChi2NDF");
  float* muchi2LocalPosition  = data.GetPtrFloat("muchi2LocalPosition");
  float* mutrkKink = data.GetPtrFloat("mutrkKink");
  float* musegmentCompatibility = data.GetPtrFloat("musegmentCompatibility");
  float* muInnervalidFraction = data.GetPtrFloat("muInnervalidFraction");
  float* muPFChIso   = data.GetPtrFloat("muPFChIso");
  float* muPFPhoIso  = data.GetPtrFloat("muPFPhoIso");
  float* muPFNeuIso  = data.GetPtrFloat("muPFNeuIso");
  float* muPFPUIso   = data.GetPtrFloat("muPFPUIso");
  UShort_t* muIDbit  = (UShort_t*) data.GetPtrShort("muIDbit");
  //  vector<bool> &muIsMediumID = *((vector<bool>*)data.GetPtr("muIsMediumID"));

  for (int i = 0; i < nMu; ++i){
    ///loose the pt cut for additional leptons                     
    if (muPt[i] < 5. ) continue;
    if (fabs(muEta[i]) > 2.4) continue;
    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6
    
    if ((muType[i] >> 1 & 1) == 0) continue;
    /*    if (muChi2NDF[i] >= 3 ) continue;
	  if (muchi2LocalPosition[i] >= 12) continue;
	  if (mutrkKink[i] >= 20) continue;
	  if (musegmentCompatibility[i] <= 0.451) continue; //tight segment compatibility, loose:0.303*/
    if ((muIDbit[i]>> 1 & 1)== 0) continue;
    /*    if(isGH==0)
	  {
	  if (muInnervalidFraction[i] <= 0.49) continue;
	  }
	  if(isGH==1)
	  {
	  if (muInnervalidFraction[i] <= 0.8) continue;
	  }*/
    if ((muPFChIso[i] + TMath::Max(0., muPFPhoIso[i] + muPFNeuIso[i] -0.5 * muPFPUIso[i]))/muPt[i] > 0.25) continue;//loose iso
    accepted.push_back(i);
  }
}
