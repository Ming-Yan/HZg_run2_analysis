#include "interface/HZg_FSR.h"  
bool ZeeSelector(TreeReader &data, bool isData,  vector<int> &eleID,int channel, HZgVariables &HZgvar, KinZfitter *kinZfitter, vector<int> &ZeeID)
{
  vector <TLorentzVector> Zpair; Zpair.clear();
  vector<int> Zee; Zee.clear();
	  
  //set up kinematic fit objects
  std::map<unsigned int, TLorentzVector> selectedLeptons;
  std::map<unsigned int, TLorentzVector> selectedFsrMap;
  std::vector<int> lepID_kin,fsrID_kin;
  vector<TLorentzVector> refitlep;
  TLorentzVector fsr_zll;
  TLorentzVector kinlep[2];
  TLorentzVector lep[2],refit_lep[2];
  HZgvar.sfsrID_[0] = HZgvar.sfsrID_[1] = -99;
  selectedFsrMap.clear(); selectedLeptons.clear(); 
  lepID_kin.clear();  fsrID_kin.clear();lepID_kin.clear();Zpair.clear();
  float* elePt     = data.GetPtrFloat("eleCalibPt");
  float* elenocalibPt     = data.GetPtrFloat("elePt");
  float *eleEta    = data.GetPtrFloat("eleEta");
  float *elePhi    = data.GetPtrFloat("elePhi");
  TLorentzVector temp,z;  
  int ie =0 , je =1;
  for(int i = 0 ; i < eleID.size() ; i++)
    {
      lepID_kin.clear(); 
      fsrID_kin.clear();
      selectedLeptons.clear();
      selectedFsrMap.clear();
      kinlep[0].SetPtEtaPhiM(elenocalibPt[eleID[i]], eleEta[eleID[i]], elePhi[eleID[i]], 0.511*0.001);
      selectedLeptons[0] = kinlep[0];
      fsrID_kin.push_back(-99);
      lepID_kin.push_back(eleID[i]);
      for(int j = i+1 ; j < eleID.size() ; j++)
	{
	  if(elePt[eleID[j]]<25.&&elePt[eleID[i]]<25.) continue;
	  kinlep[1].SetPtEtaPhiM(elenocalibPt[eleID[j]], eleEta[eleID[j]], elePhi[eleID[j]], 0.511*0.001);
	  temp = kinlep[0]+kinlep[1];
	  if(temp.M()<40.)continue;
	  selectedLeptons[1] = kinlep[1];
	  fsrID_kin.push_back(-99);
	  lepID_kin.push_back(eleID[j]);
	  vector<double> pTerr;
	  pTerr.clear();
	  kinZfitter->Setup(data,lepID_kin, fsrID_kin, pTerr, channel, isData, selectedLeptons, selectedFsrMap);
	  kinZfitter->KinRefitZ();
	  refitlep = kinZfitter->GetRefitP4s();
	  if(kinZfitter->GetRefitMZ1() < 50.) continue;
	  temp = refitlep[0] + refitlep[1];
	  if(fabs(temp.M()-91.18)<fabs(z.M()-91.18)||(i==0&&j==1))
	    {
	      Zee.clear();Zpair.clear();
	      ie = (refitlep[0].Pt()>refitlep[1].Pt()) ?eleID[i] : eleID[j];
	      je = (refitlep[0].Pt()>refitlep[1].Pt()) ?eleID[j] : eleID[i];
	      lep[0] = (refitlep[0].Pt()>refitlep[1].Pt()) ? refitlep[0] : refitlep[1];
	      lep[1] = (refitlep[0].Pt()>refitlep[1].Pt()) ? refitlep[1] : refitlep[0];
	      z = lep[0] + lep[1];
	      Zee.push_back(ie);
	      Zee.push_back(je);
	      Zpair.push_back(lep[0]);
	      Zpair.push_back(lep[1]);
	    }
	}
    }
  int siz = (int) Zpair.size();
  int ind[siz];
  if(siz>0&&lep[0].Pt()>25.){
    TLorentzVector oldlep[2];
    for(int i =0 ; i < 2; i++)
      {
	HZgvar.lepID_[i] = Zee[i];
	HZgvar.lepPt[i] = elePt[Zee[i]];
	oldlep[i].SetPtEtaPhiM(HZgvar.lepPt[i],eleEta[Zee[i]],elePhi[Zee[i]],0.511*0.001);
	HZgvar.vec_lep[i] = lep[i];
	HZgvar.REFIT_lepPt[i] = Zpair[i].Pt();
      }
    HZgvar.vec_Z  = HZgvar.vec_lep[0] + HZgvar.vec_lep[1];    // TMath::Sort(siz,&Zmass.front(),ind,kFALSE);
    HZgvar.REFIT_mll = HZgvar.vec_Z.M();
    HZgvar.vec_oldZ = oldlep[0]+oldlep[1];
    return true;
  }
  else return false;
  
}
bool ZmmSelector(TreeReader &data, bool isData, vector<int> &muID, vector<float> &muPt, int channel, HZgVariables &HZgvar,KinZfitter *kinZfitter)
{
  static vector <TLorentzVector> Zpair; Zpair.clear();// 4-vec use to select the final Z pair 
  static vector<int> Zmm; Zmm.clear();//ID use to select the final Z pair 
  static vector<int> fsr_; fsr_.clear();
  static vector<int> all_fsr;all_fsr.clear();
  //set up kinematic fit objects
  std::map<unsigned int, TLorentzVector> selectedLeptons;
  std::map<unsigned int, TLorentzVector> selectedFsrMap;
  static std::vector<int> lepID_kin,fsrID_kin; lepID_kin.clear(); fsrID_kin.clear();
  TLorentzVector fsr_zll,temp,z,fsr[2];
  TLorentzVector kinlep[2]	;
  TLorentzVector lep[2];
  HZgvar.sfsrID_[0] = HZgvar.sfsrID_[1] = HZgvar.afsrID_[0] = HZgvar.afsrID_[1] = -99;
  static vector<TLorentzVector> refitlep; refitlep.clear();
  static vector<double> pTerr;
  int ie = 0, je = 0;  
  float *muEta    = data.GetPtrFloat("muEta");
  float *muPhi    = data.GetPtrFloat("muPhi");
  float* pfPhoEt 		= data.GetPtrFloat("pfPhoEt");
  float* pfPhoEta 		= data.GetPtrFloat("pfPhoEta");
  float* pfPhoPhi 		= data.GetPtrFloat("pfPhoPhi");
  float* muPFChIso03   = data.GetPtrFloat("muPFChIso03");
  float* muPFPhoIso03  = data.GetPtrFloat("muPFPhoIso03");
  float* muPFNeuIso03  = data.GetPtrFloat("muPFNeuIso03");
  float* muPFPUIso03   = data.GetPtrFloat("muPFPUIso03");
  for(int i = 0 ; i < muID.size() ; i++)
    {
      lepID_kin.clear();fsrID_kin.clear();selectedLeptons.clear();selectedFsrMap.clear();
      kinlep[0].SetPtEtaPhiM(muPt[muID[i]], muEta[muID[i]], muPhi[muID[i]], 105.7*0.001);
      HZgvar.vec_lep[0] = kinlep[0];
      SMPZZ_FSR(data,HZgvar,all_fsr,1,0);
      TLorentzVector tmpfsr;
      //check isolation criteria
      if(HZgvar.sfsrID_[0]!=-99)
	{
	  tmpfsr.SetPtEtaPhiM(pfPhoEt[HZgvar.sfsrID_[0]],pfPhoEta[HZgvar.sfsrID_[0]],pfPhoPhi[HZgvar.sfsrID_[0]],0.);
	  fsrID_kin.push_back(HZgvar.sfsrID_[0]);
	  // fsr_.push_back(HZgvar.sfsrID_[0]);
	  if((muPFChIso03[muID[i]] + TMath::Max(0., muPFPhoIso03[muID[i]] + muPFNeuIso03[muID[i]] -0.5 * muPFPUIso03[muID[i]]-tmpfsr.Pt()))/muPt[muID[i]] > 0.35) continue;
	}
      else {
	tmpfsr.SetPtEtaPhiM(0.,0.,0.,0.);  fsrID_kin.push_back(-99);
	if ((muPFChIso03[muID[i]] + TMath::Max(0., muPFPhoIso03[muID[i]] + muPFNeuIso03[muID[i]] -0.5 * muPFPUIso03[muID[i]]))/muPt[muID[i]] > 0.35) continue;//HZZ iso
      }
      //getting all fsr
      //if(HZgvar.sfsrID_[0]!=-99)cout<<all_fsr.size()<<endl;
      // if(all_fsr.size()>0) all_fsrs.push_back(all_fsr);
      // else {all_fsr.push_back(-99);  all_fsrs.push_back(all_fsr);}
      // select particular fsr& the other info
      lepID_kin.push_back(muID[i]);//kinfit
      selectedFsrMap[0] = tmpfsr;
      selectedLeptons[0] = kinlep[0];//kinfit
      for(int j = i+1 ; j < muID.size() ; j++)
	{
	  //HZgvar.sfsrID_[0] = -99;
	  Zpair.clear();
	  //fsr_.clear();
	  if(muPt[muID[j]]<20.&&muPt[muID[i]]<20.) continue;
	  kinlep[1].SetPtEtaPhiM(muPt[muID[j]], muEta[muID[j]], muPhi[muID[j]],  105.7*0.001);
	  HZgvar.vec_lep[1] = kinlep[1];
	  SMPZZ_FSR(data,HZgvar,all_fsr,1,1);
	  if(HZgvar.sfsrID_[1]!=-99){
	    tmpfsr.SetPtEtaPhiM(pfPhoEt[HZgvar.sfsrID_[1]],pfPhoEta[HZgvar.sfsrID_[1]],pfPhoPhi[HZgvar.sfsrID_[1]],0.); fsrID_kin.push_back(HZgvar.sfsrID_[1]);
	    if((muPFChIso03[muID[j]] + TMath::Max(0., muPFPhoIso03[muID[j]] + muPFNeuIso03[muID[j]] -0.5 * muPFPUIso03[muID[j]]-tmpfsr.Pt()))/muPt[muID[j]] > 0.35) continue;
	  }
	  else{
	    tmpfsr.SetPtEtaPhiM(0.,0.,0.,0.); //Set NULL
	    fsrID_kin.push_back(-99);
	    if((muPFChIso03[muID[j]] + TMath::Max(0., muPFPhoIso03[muID[j]] + muPFNeuIso03[muID[j]] -0.5 * muPFPUIso03[muID[j]]))/muPt[muID[j]] > 0.35) continue;//HZZ iso
	  }
	  selectedFsrMap[1] = tmpfsr;
	  kinlep[1].SetPtEtaPhiM(muPt[muID[j]], muEta[muID[j]], muPhi[muID[j]], 105.7*0.001);
	  selectedLeptons[1] = kinlep[1];//kinfit
	  if(HZgvar.sfsrID_[1]!=-99) fsr_zll = kinlep[0] + kinlep[1] + selectedFsrMap[0]; 
	  else if(HZgvar.sfsrID_[1]!=-99) fsr_zll = kinlep[0] + kinlep[1] + selectedFsrMap[1]; 
	  else if(HZgvar.sfsrID_[0]!=-99&&HZgvar.sfsrID_[1]!=-99)fsr_zll = kinlep[0] + kinlep[1] + selectedFsrMap[0] + selectedFsrMap[1]; 
	  if(HZgvar.sfsrID_[0]==-99&&HZgvar.sfsrID_[1]==-99)fsr_zll = kinlep[0] + kinlep[1];
	  
	  if(fsr_zll.M()<40.)continue;
	  selectedLeptons[1] = kinlep[1];//kinfit
	  lepID_kin.push_back(muID[j]);//kinfit
	  pTerr.clear();
	  kinZfitter->Setup(data,lepID_kin, fsrID_kin, pTerr, channel, isData, selectedLeptons, selectedFsrMap);
	  //cout<<"Kin setup"<<endl;
	  kinZfitter->KinRefitZ();
	  //cout<<"Kin fit!"<<endl;
	  if(kinZfitter->GetRefitMZ1() < 50.) continue;
	  refitlep = kinZfitter->GetRefitP4s();
	  //cout<<"Kin getp4"<<endl;
	  temp = refitlep[0] + refitlep[1];
	  //cout<<"fitting done $_$"<<endl;
	  if(fabs(temp.M()-91.18)<fabs(z.M()-91.18)||(i==0&&j==1))
	    {
	      Zmm.clear();Zpair.clear();
	      ie = (refitlep[0].Pt()>refitlep[1].Pt()) ?muID[i] : muID[j];
	      je = (refitlep[0].Pt()>refitlep[1].Pt()) ?muID[j] : muID[i];
	      lep[0] = (refitlep[0].Pt()>refitlep[1].Pt()) ? refitlep[0] : refitlep[1];
	      lep[1] = (refitlep[0].Pt()>refitlep[1].Pt()) ? refitlep[1] : refitlep[0];
	      z = lep[0] + lep[1];
	      Zmm.push_back(ie);
	      Zmm.push_back(je);
	      Zpair.push_back(lep[0]);
	      Zpair.push_back(lep[1]);
	    }

	}
    }

  //  delete kinZfitter;
  int siz = (int) Zpair.size();
  int ind[siz];
  if(siz>0&&lep[0].Pt()>20.){
    TLorentzVector oldlep[2];
    for(int i =0 ; i < 2; i++)
      {
	HZgvar.lepID_[i] = Zmm[i];
	HZgvar.lepPt[i] = muPt[Zmm[i]];
	oldlep[i].SetPtEtaPhiM(HZgvar.lepPt[i],muEta[Zmm[i]],muPhi[Zmm[i]],105.7*0.001);
	HZgvar.vec_lep[i] = lep[i];
	HZgvar.REFIT_lepPt[i] = Zpair[i].Pt();
      }
    HZgvar.vec_Z  = HZgvar.vec_lep[0] + HZgvar.vec_lep[1];    // TMath::Sort(siz,&Zmass.front(),ind,kFALSE);
    HZgvar.REFIT_mll = HZgvar.vec_Z.M();
    HZgvar.vec_oldZ = oldlep[0]+oldlep[1];
    return true;
  }
  else return false;
}
