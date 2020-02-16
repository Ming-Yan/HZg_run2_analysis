// MAIN ANALYSIS FOR HZg ==> new FLOW
// Todo marked as the things need to change-2016/2017 period
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
//tools
#include "interface/HZgvar.h" //HZg related variables class
#include "plugin/puweicalc.h" //pileup weight calculation package
#include "plugin/untuplizer_07.h"//--for mc treereader
#include "plugin/RoccoR.cc"//Rochester correction
//#include "plugin/untuplizerv8.h"//--for data in eos
//selections
#include "plugin/ElectronSelections_v2.h" 
#include "plugin/MuonSelections_v2.h"
#include "plugin/PhotonSelections_v2.h"
#include "plugin/Zselector.h"
//plugin
#include "interface/SaveTree.h"//tree saver
#include "interface/cat2.h" //def categorization 
#include "interface/TMVA_BDT.h" // evaluate BDT score
#include "interface/storeSF2.h"// find SFs
#include "/afs/cern.ch/work/m/milee/MYcode/KinZfitter/KinZfitter/interface/KinZfitter.h" //Kinematic refit

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
//================================MAIN======================================
void main_ana(const char* inpath, TString outpath = "output.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, bool mucorr = false, bool isSig = false, bool isMVA=true,bool isjetMVA=true, bool isData = false, bool isrefit = false, bool isFSR = false, int period = 16, bool isbug = false) 
//void mana(Int_t channel = 0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, Int_t processID=0)
{
  gROOT->ProcessLine("gErrorIgnoreLevel = 3001;");
  /// inpaths  = array of paths to files with ggNtuplizer's TTrees;
  /// outpath  = path to output root file;
  /// channel  = 0 : electron, 1 : muon
  /// xs       = cross section
  /// lumi     = luminosity
  /// aMCatNLO = 0 : not aMC@NLO, 1 : aMC@NLO (with negative weight)
  /// photonReovmal = 0 : do not remove signal photons, 1 : avoid double counting (only apply to Zjets)
  /// mucorr : need ROCHESTER MUON CORRECTION
  /// isSig : flag of signal samples
  /// isData : flag of data samples
  /// isMVA : Kinematic MVA option true(1)/false(0)
  /// isjetMVA : VBFMVA option
  /// isrefit : Kinematic refit
  /// isFSR : do FSR recovery?
  /// period : 2016/2017 data
  /// isbug : debug flag
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
  float wei_totalev, wei_PV, wei_passtrg, wei_passele, wei_passmu, wei_passlep, wei_passpho, wei_mll, wei_passall;
  wei_totalev = wei_PV = wei_passtrg = wei_passele = wei_passmu = wei_passpho = wei_mll = wei_passall = 0.;
  Int_t N_cat1, N_cat2, N_cat3, N_cat4, N_cat5, N_cat6, N_cat7,  N_cat8, N_cat9, N_cat10,N_cat11;
  N_cat1 = N_cat2 = N_cat3 = N_cat4 = N_cat5 = N_cat6 = N_cat7 = N_cat8 = N_cat9 = N_cat10 = N_cat11 = 0;
  int N_FSRs = 0, N_FSR=0;
  Int_t totalEvents;
  float mcwei_;
  totalEvents = mcwei_ = 0;
  //==============================================Import package=================================================================//
  KinZfitter* kinZfitter = new KinZfitter(isData);
  TreeReader data(inpath);
  storeSF SFs;
  if(period==16)SFs.Setup16();
  else if(period==17)SFs.Setup17();
  TFile *fg_R9;
  fg_R9 = (period==16)? new TFile("external/R9rewei_Moriond17_AfterPreApr_v1.root"):new TFile("external/R9rewei_Moriond17_AfterPreApr_v1.root");//todo
  TGraph *gg_R9EE = (TGraph*) fg_R9->Get("transffull5x5R9EE");
  TGraph *gg_R9EB = (TGraph*) fg_R9->Get("transffull5x5R9EB");
  AForest forest (outpath);
  forest.setAnaTree();
  //forest.setfsrtree();
  forest.setkinMVAtree();
  forest.setVBFMVAtree();
  PUWeightCalculator puCalc;
  PUWeightCalculator puCalcUp;
  PUWeightCalculator puCalcDown;
  RoccoR rc("roccor.Run2.v2/RoccoR2016.txt");
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
  //puwei calculation
  if (data.HasMC())
    {
      if(period==16)
	{
	  puCalc.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_69200nb.root");
	  puCalcUp.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_71300nb.root");
	  puCalcDown.Init("80X_puwei/36p0_invfb/summer16/PU_histo_13TeV_GoldenJSON_69000nb.root");
	}
      else if(period==17)
	{
	  puCalc.Init("94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_69200nb.root");
	  puCalcUp.Init("94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_72383nb.root");
	  puCalcDown.Init("94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_66016nb.root");   
	}
    }
  TLorentzVector pho, lep[2], zll, higgs,jet[2], dijet, alep,mcpho;
  vector<int> nmult; 
  N_totalev = data.GetEntriesFast();
  //event loop
  if(isbug==true) cout<<"open file & create tree"<<endl;
  cout<<"No weighted events: "<< data.GetEntriesFast()<<endl;
  for (Long64_t ev = 0; ev <  data.GetEntriesFast(); ev++)
    {

      //default value
      HZgVariables HZgvar  = {};
      
      HZgvar.totalev = totalEvents;
     
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
      float* elenocalibPt     = data.GetPtrFloat("elePt");
      float *eleEta    = data.GetPtrFloat("eleEta");
      float *eleSCEta    = data.GetPtrFloat("eleSCEta");
      float *elePhi    = data.GetPtrFloat("elePhi");
      Int_t  nMu         = data.GetInt("nMu");
      float* muEta 		 = data.GetPtrFloat("muEta");
      float* muPhi 		 = data.GetPtrFloat("muPhi");
      float* muPt_			  = data.GetPtrFloat("muPt");
      vector <float> passUnsortedPt;
      passUnsortedPt.clear();
      //caculating GEN level info
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
      wei_totalev += 1.*mcwei_*HZgvar.puwei*HZgvar.genwei;
      // do Rochester muon correction
      if(mucorr == true)
	{
	  Int_t* muCharge    = data.GetPtrInt("muCharge");//for roch corr
	  Int_t* muType      = data.GetPtrInt("muType");//for roch corr
	  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");//for roch corr
	 
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
	      //if (data.HasMC()) mcMu(data, imcMu);
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
	      else SF = rc.kScaleDT(muCharge[i], muPt_[i], muEta[i], muPhi[i], 0, 0);
	      float tmppt = muPt_[i]*SF;
	      
	      passUnsortedPt.push_back(tmppt);
	    }
	  muPt.assign(passUnsortedPt.begin(), passUnsortedPt.end());
	}
      else 
	{
	  float* muCalibPt = data.GetPtrFloat("muCalibPt");
	  
	  for(int j = 0; j < nMu; j++)
	    {
	      muPt.push_back(muCalibPt[j]);
	    }
	}
      if(isbug==true)cout<<"mu pt corr"<<endl;
      if (ev % 1000000 == 0)//caculating events progress
        {
	  fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
      //vertex filter
      Bool_t isPVGood = data.GetBool("isPVGood");
      if (isPVGood == false) continue;
      N_passPV++;
      wei_PV += 1.*HZgvar.puwei*HZgvar.mcwei*HZgvar.genwei;
      if(isbug==true)cout<<"PV OK"<<endl;
      //trigger
      Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
      //ULong64_t   HLTEleMuXIsPrescaled  = (ULong64_t)data.GetLong64("HLTEleMuXIsPrescaled");
      // HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
      
      //float tmptrgsf[2];
      if(channel==0&&(HLTEleMuX >>  40 & 1) == 0&&(HLTEleMuX >>  5 & 1) == 0) continue;
      // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v OR HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v
      if (channel == 1 && (HLTEleMuX >> 14 & 1) == 0 && (HLTEleMuX >> 15 & 1) == 0 && ((HLTEleMuX >> 41) & 1) == 0 && ((HLTEleMuX >> 42) & 1) == 0) continue;
      N_passtrigger++;
      wei_passtrg += 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.genwei;
      if(isbug==true)cout<<"trg done"<<endl;
      
      //lepton selection
      vector<TLorentzVector> multz; multz.clear();
      eleID.clear();muID.clear();
      // if(period==16)ElectronID16NonTrgMVA(data, 98, ZeeID,multz);
      if(period==16){ElectronID16NonTrgMVA(data, 98, ZeeID,multz);ElectronID16NonTrgMVA_mod(data, 98, eleID,multz);}
      else if(period==17)ElectronID17NonTrgMVA(data, 98, eleID);
      //if(period==16)HZZmuID16forZg(data, muID, Zmm, muPt, channel,multz);
      if(period==16)HZZmuID16forZg_mod(data, muID, muPt, channel,multz);
      else if(period==17)HZZmuID17forZg(data, muID, Zmm, muPt, channel);
      
      if (channel == 0)//electron loop
	{
	  if (eleID.size() < 2) continue;
	  if(!ZeeSelector(data,isData,eleID,channel,HZgvar,kinZfitter,ZeeID)) continue;
	}      
      else if (channel==1) //muon loop
	{
	  if (muID.size() < 2) continue;
	  ///KinZfitter *tempfitter = kinZfitter;
	  if(!ZmmSelector(data,isData, muID, muPt, channel,HZgvar,kinZfitter)) continue;
	}
      //if(HZgvar.vec_Z.M()<50.) continue;
      N_mll++;
      if(data.HasMC())
	{
	  SFs.eleSF(data,HZgvar,HZgvar.cat,channel);
	  SFs.muSF(data,HZgvar,HZgvar.cat,channel);
	}//store SFs
      if(HZgvar.fsr.size()>1)N_FSRs++;
      if(HZgvar.fsr.size()==1)N_FSR++;
      if(data.HasMC()&&channel==0)wei_passele += 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1];
      if(data.HasMC()&&channel==1)wei_passmu +=  1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1];      
      if(data.HasMC())wei_mll += (channel==0)? 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]: 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1];
      ////////////////////=======================TMP testing=======================================////
     
      float* phoEt    = data.GetPtrFloat("phoCalibEt");//use this for analysis
      float* phoEta   = data.GetPtrFloat("phoEta");	
      float* phoSCEta = data.GetPtrFloat("phoSCEta");	
      float* phoPhi   = data.GetPtrFloat("phoPhi");	
      float* phoR9    = data.GetPtrFloat("phoR9Full5x5");	
      //int*   pfPhoPhoIndex  = data.GetPtrInt("pfPhoPhoIndex");
      Int_t  nMC      = 0;
      Int_t* mcPID	  = NULL;
      Int_t* mcMomPID = NULL;
      float* mcPt	  = NULL;
      float* mcEta 	  = NULL;
      float* mcPhi 	  = NULL;
      UShort_t* mcStatusFlag = NULL;
      if(data.HasMC())
	{
	  nMC = data.GetInt("nMC");
	  mcPID        = data.GetPtrInt("mcPID");
	  mcMomPID     = data.GetPtrInt("mcMomPID");
	  mcPt         = data.GetPtrFloat("mcPt");
	  mcEta        = data.GetPtrFloat("mcEta");
	  mcPhi        = data.GetPtrFloat("mcPhi");
	  mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");
	}
      vector<int> phoID;
      Int_t phoIndex = -999;
      if(period==16)PhotonIDMVA2016t(data, phoID,HZgvar,channel);
      else if(period==17)PhotonIDMVA2017(data, phoID);

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
	  if (tmppho.DeltaR(HZgvar.vec_lep[0]) < 0.4 || tmppho.DeltaR(HZgvar.vec_lep[1]) < 0.4) continue;
	  HZgvar.vec_higgs= tmppho + HZgvar.vec_Z;
	  HZgvar.vec_oldH  = tmppho + HZgvar.vec_oldZ;
	  if (HZgvar.vec_higgs.M() >180.|| HZgvar.vec_higgs.M()<100) continue;
	  if (HZgvar.vec_higgs.M() + HZgvar.vec_Z.M() < 185.) continue;
	  if (tmppho.Pt() / HZgvar.vec_higgs.M() < 15./110.) continue;
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
      //if(haspho==false) continue;
      // if(passmult>1)nmult.push_back(passmult);
      HZgvar.REFIT_mllg = HZgvar.vec_higgs.M();
      HZgvar.phoID_ = phoIndex;
      HZgvar.vec_pho = pho;
      N_passHpt++;      
      if(isbug==true)cout<<"event sel done"<<endl;	
    
      
      ///apply scale smear correc
      vector<float> R9;
      R9.clear();
      if(isSig==true)R9.push_back(fabs(phoEta[phoIndex])<1.479 ? gg_R9EB->Eval(phoR9[phoIndex]) : gg_R9EE->Eval(phoR9[phoIndex]));
      else R9.push_back(phoR9[phoIndex]);
      vector<float> jetPt, jetEn;
      Int_t nJet  		 = data.GetInt("nJet");
      float *jetPt_ 	 = data.GetPtrFloat("jetPt");
      float *jetEn_ 	 = data.GetPtrFloat("jetEn");
      float *jetP4Smear  = NULL;
      // if(data.HasMC())jetP4Smear = data.GetPtrFloat("jetP4Smear");
      for(int i = 0; i < nJet ; i++)
	{
	  float jetP4Smear_ = 1.;
	  // if(data.HasMC()) jetP4Smear_ = jetP4Smear[i];
	  jetPt.push_back(jetPt_[i]*jetP4Smear_);
	  jetEn.push_back(jetEn_[i]*jetP4Smear_);
	}	 
      if(isbug)cout<<"var corr"<<endl;
      if(data.HasMC())SFs.phoSF(data,HZgvar,R9);      
      

      if(data.HasMC())wei_passpho += (channel==0) ?1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_: 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_;
      
      //put kinematic MVA info
      HZgAngles(HZgvar);
      if(isMVA)HZgvar.kinMVA = HZgkin_MVA(data,channel,period,HZgvar, R9);
      //defining category	
      HZgvar.isdbtag = dbtag(data,HZgvar,jetPt,jetEn);//no overlap
      HZgvar.isLep= leptag(data, channel,muID, muPt, HZgvar,period);
      if(HZgvar.isLep!=1)  HZgvar.isVBF = VBFtag(data,HZgvar,jetPt,jetEn,isjetMVA,period);
      if(HZgvar.isLep!=1&&HZgvar.isVBF==1&&isjetMVA==1)
	{
	  HZgvar.VBFMVA = HZgVBF_MVA(data,HZgvar,channel,period,jetPt,jetEn);
	  forest.fillVBFMVA(data, channel, HZgvar,jetPt,jetEn);  
	}
      // if(HZgvar.isLep!=1&&HZgvar.VBFMVA>0.){HZgvar.isVBF = 1;HZgvar.cat = 5;}
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1) HZgvar.isbtag = btag(data,HZgvar,jetPt,jetEn);
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1/*&&HZgvar.isbtag!=1*/)HZgvar.isboost = boosttag(data,HZgvar);
      if(HZgvar.isVBF!=1&&HZgvar.isLep!=1&&HZgvar.isboost!=1/*&&HZgvar.isbtag!=1*/)  HZgvar.cat = inclusive(data,channel,R9,HZgvar);	  
      if(isbug==true)cout<<"cat done"<<endl;
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
      //delete kinZfitter;
     
      if(isbug==true) cout<<"sf fill"<<endl;
      forest.fillkinMVA(data, channel, HZgvar, R9);
      if(isbug==true) cout<<"fill kinmva tree"<<endl;

      forest.fillAna(data, channel, aMCatNLO, HZgvar, R9, jetPt, jetEn, isSig,isFSR,isrefit);
      if(isbug==true) cout<<"fill tree"<<endl;
      //forest.fillFSR(data,HZgvar,isSig);
      // if(isbug==true) cout<<"fill fsr tree"<<endl;
     
      eleID.clear(); phoID.clear(); ZeeID.clear();  Zmm.clear();R9.clear();jetEn.clear();jetPt.clear();
      if(isbug==true)cout<<"all done"<<endl; 	  
    } // event loop end
  cout<<"-------------------------------------------------------"<<endl;
  fprintf(stderr, "Processed all events\n");
  
  cout << "totalev:" <<totalEvents<<"\n"<<"pass PV: "<< N_passPV<<"\n"<<"pass trigger:"<<" "<<N_passtrigger<<"\n"<<"ele:"<<N_passele<<" "<<"\nmu:"<<N_passmu<<"\n"<<"mll:"<<N_mll<<"\n"<<"pho:"<<N_passpho<<"\n"<<"pass all:"<<N_passHpt<<endl;
  if(isData==0){
    cout<<"\nweighted events: "<<endl;
    cout << "totalev:" <<wei_totalev<<"\n pass:"<<wei_PV<<"\n"<<"pass trigger:"<<" "<<wei_passtrg<<"\n"<<"pass ele sel:"<<wei_passele<<" "<<"\nmu:"<<wei_passmu<<"\n"<<"mll:"<<wei_mll<<"\n"<<"pass all:"<<wei_passpho<<endl;
  }
  cout<<"-------------------------------------------------------------"<<endl;
  cout<<"cat"<<"\n"<<"1 = "<<N_cat1<<endl<<"2 = "<<N_cat2<<endl<<"3 = "<<N_cat3<<endl<<"4 = "<<N_cat4<<endl<<"5 = "<<N_cat5<<endl<<"6 = "<<N_cat6<<endl<<"7 = "<<N_cat7<<endl<<"8 = "<<N_cat8<<endl<<"9 ="<<N_cat9<<endl<<"10 ="<<N_cat10<<endl<<"11 = "<<N_cat11<<endl;
  cout<<N_FSR<<" "<<N_FSRs<<endl;
}
