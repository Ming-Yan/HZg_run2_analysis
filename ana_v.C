//for skim file
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"

//selections
#include "plugin/puweicalc.h"
#include "plugin/untuplizer_07.h"//--for mc
//#include "plugin/untuplizerv8.h"//--for data in eos
#include "plugin/ElectronSelections_v.h"
#include "plugin/MuonSelections_v.h"//for mupt
#include "plugin/PhotonSelections_v.h"
#include "interface/HZgvar.h"
#include "interface/SaveTree.h"
#include "interface/cat.h"
#include "interface/TMVA_BDT.h"
#include "interface/storeSF.h"
#include "KinZfitter/KinZfitter/interface/KinZfitter.h"
//tools
#include "plugin/RoccoR.cc"//Rochester correction

using namespace std;
// MC mu collection for Rochester correction
void mcMu(TreeReader &data, std::vector<int> &accepted)
{
  accepted.clear();
  Int_t    nMC = data.GetInt("nMC");
  Float_t* mcEta = data.GetPtrFloat("mcEta");
  // use getptr for vectors
  Int_t*    mcPID = data.GetPtrInt("mcPID");
  Int_t*    mcMomPID = data.GetPtrInt("mcMomPID");
  for (int i = 0; i < nMC; i++)
    {
      if (fabs(mcPID[i]) != 13) continue;
      if (fabs(mcEta[i]) > 2.4) continue;
      accepted.push_back(i);
    }
}
//================================MAIN======================================//
void main_ana(const char* inpath, TString outpath = "output.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, bool mucorr = false, bool isSig = false, bool isMVA=true,bool isjetMVA=true, bool isData = false) 
//void mana(Int_t channel = 0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, Int_t processID=0)
{

  /// inpaths  = array of paths to files with ggNtuplizer's TTrees;
  /// npaths   = size of inpaths;
  /// outpath  = path to output root file;
  /// channel  = 0 : electron, 1 : muon
  /// xs       = cross section
  /// lumi     = luminosity
  /// aMCatNLO = 0 : not aMC@NLO, 1 : aMC@NLO (with negative weight)
  /// photonReovmal = 0 : do not remove signal photons, 1 : avoid double counting (only apply to Zjets)

  // open tree(s) with events to be processed
  //									|====================|
  //==============		|=========|		|select pho with 	 |	 |============|	  |=======|	  |=====|	|=========|
  // ele, mu      | ==> | mll >50 | ==> |phoPt>15,100-180GeV |==>| additional |==>|VBF tag|==>|b-tag|==>|inclusive|
  // pass HZZ ID  |		|=========|		|phoPt/mllg >15/110  |	 | lepton tag |   | (MVA) |   |=====|	|kinematic|
  //==============|						|mll+mllg > 185   	 |	 |============|   |=======|				|  (MVA)  |
  //									|====================|											|=========|
  
  ///counters
  Int_t N_totalev = 0;// total event #
  Int_t N_passPV = 0;//pass trigger #
  Int_t N_passtrigger = 0;//pass trigger #
  Int_t N_passele = 0;//pass particle selection:ele
  Int_t N_passmu = 0;//pass particle selection:mu
  Int_t N_passpho = 0;//pass particle selection:pho
  Int_t N_mll = 0; //pass mll>50 #
  Int_t N_passHpt = 0;//passing higgs mass /pt
  float wei_totalev, wei_passtrg, wei_passele, wei_passmu, wei_passpho, wei_mll, wei_passall;
  wei_totalev = wei_passtrg = wei_passele = wei_passmu = wei_passpho = wei_mll = wei_passall = 0.;
  Int_t N_cat1, N_cat2, N_cat3, N_cat4, N_cat5, N_cat6, N_cat7,  N_cat8, N_cat9, N_cat10,N_cat11;
  N_cat1 = N_cat2 = N_cat3 = N_cat4 = N_cat5 = N_cat6 = N_cat7 = N_cat8 = N_cat9 = N_cat10 = N_cat11 = 0;
  Int_t totalEvents;
  float mcwei_;
  totalEvents = mcwei_ = 0;
  //==============================================Import package=================================================================//
  KinZfitter* kinZfitter = new KinZfitter(isData); 
  TreeReader data(inpath);
  storeSF SFs;
  SFs.Setup();
  TFile *fg_R9 = new TFile("external/R9rewei_Moriond17_AfterPreApr_v1.root");
  TGraph *gg_R9EE = (TGraph*) fg_R9->Get("transffull5x5R9EE");
  TGraph *gg_R9EB = (TGraph*) fg_R9->Get("transffull5x5R9EB");
  AForest forest (outpath);
  /*TString outKIN = outpath  + "_KIN.txt";
    ofstream outkin(outKIN);
    time_t now = time(0);
    char * dt = ctime(&now);
    outkin<<"====> Produced by NCU HEP lab <=====\n"<<"      STUDY FOR HZg analysis MVA, kinematic/VBF MVA"<< dt <<"\n"<< endl;
    outkin<<"sample weight : event weight : phoEta : phoMVA : phoR9 : lepEta1 : lepEta2 : cosTheta : costheta : Phi : mllgptdmllg : D0_1 : D0_2 : DZ_1 : DZ_2 : SIP_1 : SIP_2 : DR(lep1,pho) : DR(lep2,pho) : pfMET : phoIDMVA: phoSCPhi: phoSigmaIEtaIPhiFull5x5 : phoSigmaIEtaIEtaFull5x5 : phoE1x3Full5x5 : phoE1x5Full5x5 : phoE2x2Full5x5 : phoE5x5Full5x5 : phoESEffSigmaRR : phoPFChIso : phoPFNeuIso : phoPFChWorstIso: rho"<<endl;*/
  forest.setAnaTree();
  forest.setkinMVAtree();
  forest.setVBFMVAtree();
  RoccoR rc("plugin/rcdata.2016.v3");//moriond roch
  if(data.HasMC())
    {
      if (aMCatNLO == 1)
	{
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
	  mcwei_ = (totalEvents != 0) ? (xs * lumi / totalEvents) : 1.;
	}
      else
	{
	  totalEvents = data.GetEntriesFast();
	  mcwei_ = xs * lumi / data.GetEntriesFast();
	}
    }
  cout<<"mcwei:"<<mcwei_<<"   xsection:"<<xs<<"  totalev:"<<totalEvents<<"   lumi"<< lumi<<endl;
  
  PUWeightCalculator puCalc;
  PUWeightCalculator puCalcUp;
  PUWeightCalculator puCalcDown;
  if (data.HasMC())
    {
      puCalc.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_69200nb.root");
      puCalcUp.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_71300nb.root");
      puCalcDown.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_69000nb.root");
    }
  TLorentzVector pho, lep[2], zll, higgs,jet[2], dijet, alep,mcpho;
  vector<int> nmult; 
  N_totalev = data.GetEntriesFast();
  //event loop
  for (Long64_t ev = 0; ev <  data.GetEntriesFast() ; ev++)
    {
      //default value
      HZgVariables HZgvar  = {};
      HZgvar.totalev = totalEvents;
      wei_totalev = totalEvents*mcwei_;
      HZgvar.mcwei = mcwei_;
      data.GetEntry(ev);
      vector<int> eleID;
      vector<int> ZeeID;
      Int_t nLep = 0;
      vector<int> muID;
      vector<int> Zmm;
      vector<float> muPt;
      muPt.clear();
      Long64_t event = data.GetLong64("event");
      float* elePt     = data.GetPtrFloat("eleCalibPt");
      float *eleEta    = data.GetPtrFloat("eleEta");
      float *eleSCEta    = data.GetPtrFloat("eleSCEta");
      float *elePhi    = data.GetPtrFloat("elePhi");
      Int_t  nMu         = data.GetInt("nMu");
      float* muEta 		 = data.GetPtrFloat("muEta");
      float* muPhi 		 = data.GetPtrFloat("muPhi");
      vector <float> passUnsortedPt;
      passUnsortedPt.clear();
      if (data.HasMC())
	{
	  float* puTrue = data.GetPtrFloat("puTrue");
	  Int_t run_   = data.GetInt("run");
	  HZgvar.puwei     = (float) puCalc.GetWeight(run_, puTrue[1]); // in-time PU
	  HZgvar.puweiUp   = (float) puCalcUp.GetWeight(run_, puTrue[1]); // in-time PU
	  HZgvar.puweiDown = (float) puCalcDown.GetWeight(run_, puTrue[1]); // in-time PU

	  float generatorWeight = data.GetFloat("genWeight");
	  if (aMCatNLO == 1) HZgvar.genwei = (generatorWeight > 0) ? 1. : -1.;
	  else               HZgvar.genwei = 1.;
	}
      if(mucorr == true)
	{
	  Int_t* muCharge    = data.GetPtrInt("muCharge");//for roch corr
	  Int_t* muType      = data.GetPtrInt("muType");//for roch corr
	  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");//for roch corr
	  float* muPt_			  = data.GetPtrFloat("muPt");
	  // do Rochester muon correction
	  for (Int_t i = 0; i < nMu ; i++)
	    {
	      //new roch
	      Float_t rand1, rand2;
	      TRandom g;
	      rand1 = g.Uniform(0,1);
	      rand2 = g.Uniform(0,1);

	      double SF = 0 ;
	      vector<int> imcMu;
	      int countmc = 0;
	      if (data.HasMC()) mcMu(data, imcMu);
	      TLorentzVector rochMu;
	      rochMu.SetPtEtaPhiM(muPt_[i], muEta[i], muPhi[i], 0.1057);
	      TLorentzVector mcMu;
	      if (data.HasMC()){
		//mc objects
		Int_t    nMC = data.GetInt("nMC");
		Float_t* mcPt = data.GetPtrFloat("mcPt");
		Float_t* mcEta = data.GetPtrFloat("mcEta");
		Float_t* mcPhi = data.GetPtrFloat("mcPhi");
		for (unsigned int mc = 0; mc < imcMu.size(); mc++){
		  if (countmc > 0) break;
		  TLorentzVector mcMutemp;
		  mcMutemp.SetPtEtaPhiM(mcPt[imcMu[mc]], mcEta[imcMu[mc]], mcPhi[imcMu[mc]], 0.1057);
		  Float_t dRmc = mcMutemp.DeltaR(rochMu);
		  if (dRmc > 0.1)continue;
		  mcMu = mcMutemp;
		  countmc++;
		}
		if (countmc > 0) SF = rc.kScaleFromGenMC(muCharge[i], muPt_[i], muEta[i], muPhi[i], muTrkLayers[i], mcMu.Pt(), rand1, 0, 0);
		if (countmc == 0) SF = rc.kScaleAndSmearMC(muCharge[i], muPt_[i], muEta[i], muPhi[i], muTrkLayers[i], rand1, rand2, 0, 0);
	      }
	      else SF = rc.kScaleDT(muCharge[i], muPt[i], muEta[i], muPhi[i], 0, 0);
	      muPt_[i] = muPt_[i]*SF;
	      passUnsortedPt.push_back(muPt_[i]);
	    }
	  muPt.assign(passUnsortedPt.begin(), passUnsortedPt.end());
	}
      else 
	{

	  //float* muCalibPt = data.GetPtrFloat("muCalibPt");
	  float* muCalibPt = data.GetPtrFloat("muPt");
	  
	  for(int j = 0; j < nMu; j++)
	    {
	      muPt.push_back(muCalibPt[j]);
	    }
	}

      if (ev % 1000000 == 0)
        {
	  fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
      //vertex filter
      Bool_t isPVGood = data.GetBool("isPVGood");
      if (isPVGood == false) continue;
      N_passPV++;
      //trigger
      Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
      ULong64_t   HLTEleMuXIsPrescaled  = (ULong64_t)data.GetLong64("HLTEleMuXIsPrescaled");
      // HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
      float tmptrgsf[2];
      if(channel==0)
        {
	  if((HLTEleMuX >>  40 & 1) == 0&&(HLTEleMuX >>  5 & 1) == 0) continue;
	  
        }
      if (channel == 1)
        {
	  // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v OR HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v
	  if ((HLTEleMuX >> 14 & 1) == 0 && (HLTEleMuX >> 15 & 1) == 0
	      && ((HLTEleMuX >> 41) & 1) == 0 && ((HLTEleMuX >> 42) & 1) == 0) continue;
	  
        }
      N_passtrigger++;

      //lepton selection
      vector<TLorentzVector> multz;
      std::map<unsigned int, TLorentzVector> selectedLeptons;
      std::map<unsigned int, TLorentzVector> selectedFsrMap;
      std::vector<TLorentzVector> selectedpho;
      std::vector<int> lepID_kin;
      selectedFsrMap.clear(); selectedLeptons.clear(); selectedpho.clear();
      multz.clear(); lepID_kin.clear();
      ElectronIDNonTrgMVA(data, 98, ZeeID,multz);
      HZZmuIDforZg(data, muID, Zmm, muPt, channel,multz);

      if (channel == 0)//electron loop
	{
	  if (ZeeID.size() < 2) continue;
	  if (elePt[ZeeID[0]] < 25.) continue;
	  if (elePt[ZeeID[1]] < 15.) continue;
	  lep[0].SetPtEtaPhiM(elePt[ZeeID[0]], eleEta[ZeeID[0]], elePhi[ZeeID[0]], 0.511*0.001);
	  lep[1].SetPtEtaPhiM(elePt[ZeeID[1]], eleEta[ZeeID[1]], elePhi[ZeeID[1]], 0.511*0.001);
	  N_passele++;
	}
      
      else if (channel==1) //muon loop
	{
	  if (Zmm.size() < 2) continue;
	  if (muPt[Zmm[0]] < 20.) continue;
	  if (muPt[Zmm[1]] < 10.) continue;
	  lep[0].SetPtEtaPhiM(muPt[Zmm[0]], muEta[Zmm[0]], muPhi[Zmm[0]], 105.7*0.001);
	  lep[1].SetPtEtaPhiM(muPt[Zmm[1]], muEta[Zmm[1]], muPhi[Zmm[1]], 105.7*0.001);
	  N_passmu++;
	}
      zll   = lep[0] + lep[1];
      if (zll.M()<50) continue;
      HZgvar.vec_Z = zll;
      for (int i = 0; i < 2; i++)
	{
	  HZgvar.lepID_[i] = channel==0 ? ZeeID[i]:Zmm[i]; 
	  lepID_kin.push_back(HZgvar.lepID_[i]);//kinfit
	  HZgvar.lepPt[i] = channel==0 ? elePt[ZeeID[i]]:muPt[Zmm[i]];
	  selectedLeptons[i] = lep[i];//kinfit
	  HZgvar.vec_lep[i] = lep[i];
	}
      N_mll++;

      //photon selection 
      float* phoEt    = data.GetPtrFloat("phoCalibEt");//use this for analysis
      float* phoEta   = data.GetPtrFloat("phoEta");	
      float* phoSCEta = data.GetPtrFloat("phoSCEta");	
      float* phoPhi   = data.GetPtrFloat("phoPhi");	
      float* phoR9    = data.GetPtrFloat("phoR9Full5x5");	
      Int_t  nMC      = 0;
      Int_t* mcPID	  = NULL;
      float* mcPt	  = NULL;
      float* mcEta 	  = NULL;
      float* mcPhi 	  = NULL;
      UShort_t* mcStatusFlag = NULL;
      if(data.HasMC())
	{
	  nMC = data.GetInt("nMC");
	  mcPID        = data.GetPtrInt("mcPID");
	  mcPt         = data.GetPtrFloat("mcPt");
	  mcEta        = data.GetPtrFloat("mcEta");
	  mcPhi        = data.GetPtrFloat("mcPhi");
	  mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");
	}
      vector<int> phoID;
      Int_t phoIndex = -999;
      PhotonIDMVA2016(data, phoID);
      
      int  passmult = 0;
      TLorentzVector multH;
      if (phoID.size() == 0) continue;
      if (phoEt[phoID[0]]<15.)continue;
      N_passpho++;

      bool haspho = false;
      Int_t isPromptPhoton = 0;
      TLorentzVector tmppho;

      for (size_t j=0; j<phoID.size(); ++j)
        {
	  if(haspho == true) break;
	  if (phoEt[phoID[j]] < 15.) continue;
	  tmppho.SetPtEtaPhiM(phoEt[phoID[j]], phoEta[phoID[j]], phoPhi[phoID[j]], 0.);
	  if (tmppho.DeltaR(lep[0]) < 0.4 || tmppho.DeltaR(lep[1]) < 0.4) continue;
	  higgs = tmppho + zll;
	  if (higgs.M() > 180.|| higgs.M()<100.) continue;
	  if (higgs.M() + zll.M() < 185.) continue; 
	  if (tmppho.Pt()/higgs.M() < 15./110.) continue; 
	  pho = tmppho;
	  haspho = true;
	  phoIndex = phoID[j];
	  
	  //double counting photon removal
	  if (data.HasMC()&&photonRemoval == 1)
	    {
	      for (Int_t i=0; i<nMC; ++i)
		{
		  if (mcPID[i] != 22) continue;
		  if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
		  mcpho.SetPtEtaPhiM(mcPt[i], mcEta[i], mcPhi[i], 0.);
		  if (mcpho.DeltaR(pho) < 0.1) isPromptPhoton = 1;
		}
	    }  
	}
      if (isPromptPhoton == 1) continue;
      if (phoIndex == -999) continue;
      if(passmult>1)nmult.push_back(passmult);
      N_passHpt++;
      HZgvar.phoID_ = phoIndex;
      HZgvar.vec_pho = pho;
      selectedpho.push_back(pho);
      HZgvar.vec_higgs = higgs;
	  
	  
	  //set kinematic fit
	  vector<double> pTerr;
	  pTerr.clear();
	  kinZfitter->Setup(data,lepID_kin, pTerr, channel, isData, selectedLeptons, selectedFsrMap,selectedpho);
	  kinZfitter->KinRefitZ();
	  vector<TLorentzVector> refitlep = kinZfitter->GetRefitP4s();
	  TLorentzVector refitH = refitlep[0] + refitlep[1] + pho;
	  HZgvar.REFIT_mllg = refitH.M();
	  HZgvar.REFIT_mll = kinZfitter->GetRefitMZ1();
	  for(int i = 0; i < 2; i++)
	  {
		HZgvar.REFIT_lepPt[i] =  refitlep[i].Pt();
		HZgvar.REFIT_lepPtErr[i] = pTerr[i];
	  }
	  
	  //apply R9 correction, jet smear
      vector<float> R9;
      R9.clear();
      if(isSig==true)R9.push_back(fabs(phoEta[phoIndex])<1.479 ? gg_R9EB->Eval(phoR9[phoIndex]) : gg_R9EE->Eval(phoR9[phoIndex]));
      else R9.push_back(phoR9[phoIndex]);
      vector<float> jetPt, jetEn;
      Int_t nJet  		 = data.GetInt("nJet");
      float *jetPt_ 	 = data.GetPtrFloat("jetPt");
      float *jetEn_ 	 = data.GetPtrFloat("jetEn");
      float *jetP4Smear  = NULL;
      if(data.HasMC())jetP4Smear = data.GetPtrFloat("jetP4Smear");
      for(int i = 0; i < nJet ; i++)
	{
	  float jetP4Smear_ = 1.;
	  if(data.HasMC()) jetP4Smear_ = jetP4Smear[i];
	  jetPt.push_back(jetPt_[i]*jetP4Smear_);
	  jetEn.push_back(jetEn_[i]*jetP4Smear_);
	}	 
      //put kinematic MVA info
      HZgAngles(HZgvar);
      HZgvar.kinMVA = HZgkin_MVA(data,channel,HZgvar, R9);
      
      //defining category	
      HZgvar.isdbtag = dbtag(data,HZgvar,jetPt,jetEn);//no overlap
      HZgvar.isLep= leptag(data, channel,muID, muPt, HZgvar);
      if(HZgvar.isLep!=1)  HZgvar.isVBF = VBFtag(data,HZgvar,jetPt,jetEn,isjetMVA);
      if(HZgvar.isLep!=1&&HZgvar.isVBF==1)
	{
	  HZgvar.VBFMVA = HZgVBF_MVA(data,HZgvar,0,jetPt,jetEn);
	  forest.fillVBFMVA(data, channel, HZgvar,jetPt,jetEn);  
	}
      // if(HZgvar.isLep!=1&&HZgvar.VBFMVA>0.){HZgvar.isVBF = 1;HZgvar.cat = 5;}
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1) HZgvar.isbtag = btag(data,HZgvar,jetPt,jetEn);
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1/*&&HZgvar.isbtag!=1*/)HZgvar.isboost = boosttag(data,HZgvar);
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1&&HZgvar.isboost!=1/*&&HZgvar.isbtag!=1*/)  HZgvar.cat = inclusive(data,channel,R9,HZgvar);	  
		
      if(HZgvar.cat==1) N_cat1++;
      else if(HZgvar.cat==2) N_cat2++;
      else if(HZgvar.cat==3) N_cat3++;
      else if(HZgvar.cat==4) N_cat4++;
      else if(HZgvar.cat==5) N_cat5++;
      else if(HZgvar.cat==6) N_cat6++;
      else if(HZgvar.cat==7) N_cat7++;
      else if(HZgvar.cat==8) N_cat8++;
      else if(HZgvar.cat==9) N_cat9++;
      else if(HZgvar.cat==10) N_cat10++;
      else if(HZgvar.cat==11) N_cat11++;
     
      if(data.HasMC())
	{
	  SFs.phoSF(data,HZgvar,R9);
	  SFs.eleSF(data,HZgvar,HZgvar.cat,channel);
	  SFs.muSF(data,HZgvar,HZgvar.cat,channel);
	}

      forest.fillkinMVA(data,channel, HZgvar,R9);	  
      forest.fillAna(data, channel, aMCatNLO, HZgvar, R9, jetPt, jetEn);
      /*
	float *phoIDMVA = data.GetPtrFloat("phoIDMVA");
	float *phoSCPhi = data.GetPtrFloat("phoSCPhi");
	float *phoSigmaIEtaIPhiFull5x5 = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
	float *phoSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
	float *phoE1x3Full5x5 = data.GetPtrFloat("phoE1x3Full5x5");
	float *phoE1x5Full5x5 = data.GetPtrFloat("phoE1x5Full5x5");
	float *phoE2x2Full5x5 = data.GetPtrFloat("phoE2x2Full5x5");
	float *phoE5x5Full5x5 = data.GetPtrFloat("phoE5x5Full5x5");
	float *phoESEffSigmaRR = data.GetPtrFloat("phoESEffSigmaRR");
	float *phoPFChWorstIso = data.GetPtrFloat("phoPFChWorstIso");
	float *phoPFChIso = data.GetPtrFloat("phoPFChIso");
	float *phoPFNeuIso = data.GetPtrFloat("phoPFNeuIso");
	float rho = data.GetFloat("rho");
	float *muD0 	  = data.GetPtrFloat("muD0");
	float *muDz 	  = data.GetPtrFloat("muDz");
	float *muSIP 	  = data.GetPtrFloat("muSIP");
	float *eleD0 	  = data.GetPtrFloat("eleD0");
	float *eleDz 	  = data.GetPtrFloat("eleDz");
	float *eleSIP   = data.GetPtrFloat("eleSIP");
	float pfMET    = data.GetFloat("pfMET");
	double D0[2],DZ[2],SIP[2];
	for(int i = 0; i<2;i++)
	{
	D0[i] = (channel ==0)?eleD0[ZeeID[i]]:muD0[Zmm[i]];
	DZ[i] = (channel ==0)?eleDz[ZeeID[i]]:muDz[Zmm[i]];
	SIP[i] = (channel ==0)?eleSIP[ZeeID[i]]:muSIP[Zmm[i]];
	}
	outkin<<mcwei_ <<" "<<HZgvar.totSF*HZgvar.genwei*HZgvar.puwei<<" "<<pho.Eta()<< " "<<R9[0]<<" "<<lep[0].Eta()<<" "<< lep[1].Eta()<< " "<<  HZgvar.HZgcosTheta<<" "<< HZgvar.HZgcostheta<<" "<< HZgvar.HZgPhi <<" "<< higgs.Pt()/higgs.M()<< " "<< D0[0] <<" "<< D0[1]<<" "<<DZ[0]<<" "<<DZ[1]<<" "<<SIP[0] <<" "<<SIP[1]<< " "<<lep[0].DeltaR(pho) <<" "<<lep[1].DeltaR(pho)<< " "<<pfMET <<" " <<phoIDMVA[phoIndex]<<" "<<phoSCPhi[phoIndex] << " "<< phoSigmaIEtaIPhiFull5x5[phoIndex]<<" "<<phoSigmaIEtaIEtaFull5x5[phoIndex]<<" "<<phoE1x3Full5x5[phoIndex]<<" "<<phoE1x5Full5x5[phoIndex]<<" "<<phoE2x2Full5x5[phoIndex]<<" "<<phoE5x5Full5x5[phoIndex]<<" "<<phoESEffSigmaRR[phoIndex]<<" "<<phoPFChIso[phoIndex]<<" "<<phoPFNeuIso[phoIndex]<<" "<<phoPFChWorstIso[phoIndex]<<" "<<rho <<endl;*/
 	  
      eleID.clear(); phoID.clear(); ZeeID.clear();  Zmm.clear();R9.clear();jetEn.clear();jetPt.clear();
    } // event loop end
 
  cout<<"-------------------------------------------------------"<<endl;
  fprintf(stderr, "Processed all events\n");
  
  cout << "totalev:" <<totalEvents<<"\n"<<"pass PV: "<< N_passPV<<"\n"<<"pass trigger:"<<" "<<N_passtrigger<<"\n"<<"ele:"<<N_passele<<" "<<"mu"<<N_passmu<<"\n"<<"mll:"<<N_mll<<"\n"<<"pho:"<<N_passpho<<"\n"<<"pass all:"<<N_passHpt<<endl;

  cout<<"-------------------------------------------------------------"<<endl;

  cout<<"cat"<<"\n"<<"1 = "<<N_cat1<<endl<<"2 = "<<N_cat2<<endl<<"3 = "<<N_cat3<<endl<<"4 = "<<N_cat4<<endl<<"5 = "<<N_cat5<<endl<<"6 = "<<N_cat6<<endl<<"7 = "<<N_cat7<<endl<<"8 = "<<N_cat8<<endl<<"9 ="<<N_cat9<<endl<<"10 ="<<N_cat10<<endl<<"11 = "<<N_cat11<<endl;
}
