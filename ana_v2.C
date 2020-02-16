// MAIN ANALYSIS FOR HZg
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
#include "plugin/puweicalc.h" 
#include "plugin/untuplizer_07.h"//--for mc
// #include "plugin/RoccoR.cc"//Rochester correctio
#include "roccor.Run2.v3/RoccoR.cc"//Rochester correctio
#include "interface/HZgvar.h"
#include "plugin/untuplizerv8.h"//--for data in eos
//selections
#include "plugin/ElectronSelections_v2.h"
#include "plugin/MuonSelections_v2.h"
#include "plugin/PhotonSelections_v2.h"

//plugin

#include "interface/HZg_FSR.h"
#include "interface/SaveTree2.h"
#include "interface/cat2.h"
//#include "interface/TMVA_BDT1.h"
#include "interface/TMVA_BDT.h"
#include "interface/storeSF2.h"
#include "KinZfitter/KinZfitter/interface/KinZfitterv1.h"
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
void main_ana(const char* inpath, TString outpath = "output.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, bool mucorr = false, bool isSig = false, bool isMVA=true,bool isjetMVA=true, bool isData = false, bool isrefit = false, bool isFSR = false, int period = 16, bool corr = true, bool isrewei = false,bool isbug = false) 
//void mana(Int_t channel = 0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, Int_t processID=0)
{
  cout<<"SHOW STATUS===>  \nWhich dataset?"<<period<<"\tchannel:"<<channel<<"t PUreweight:"<<isrewei<<endl;
  cout<<"Rochester Corr:"<<mucorr<<"\tKinematic Refit:"<<isrefit<<" refit corr:"<<corr<<"\t FSR recovery:"<<isFSR<<endl;
  cout<<"kinematic MVA: "<<isMVA<<" \tVBFMVA: "<<isjetMVA<<endl;
  isbug=0;
  /// inpaths  = array of paths to files with ggNtuplizer's TTrees;
  /// npaths   = size of inpaths;
  /// outpath  = path to output root file;
  /// channel  = 0 : electron, 1 : muon
  /// xs       = cross section
  /// lumi     = luminosity
  /// aMCatNLO = 0 : not aMC@NLO, 1 : aMC@NLO (with negative weight)
  /// photonReovmal = 0 : do not remove signal photons, 1 : avoid double counting (only apply to Zjets)

  // open tree(s) with events to be processed
  //									                  |====================|
  //==============		  |=========|	    |select pho with 	   |	 |============|	  |=======|	  |=====|	  |=========|
  // ele, mu      | ==> | mll >50 | ==> |phoPt>15,100-180GeV |==>| additional |==>|VBF tag|==>|b-tag|==>|inclusive|
  // pass HZZ ID  |		  |=========|		  |phoPt/mllg >15/110  |	 | lepton tag |   | (MVA) |   |=====|	  |kinematic|
  //==============|						          |mll+mllg > 185   	 |	 |============|   |=======|				      |  (MVA)  |
  //									                  |====================|											                    |=========|
  
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
  Int_t totalEvents;
  int nfsr = 0;
  float mcwei_;
  totalEvents = mcwei_ = 0;
  //==============================================Import package=================================================================
  
  RoccoR rc(Form("roccor.Run2.v3/RoccoR20%d.txt",period));//moriond roch 
  
  KinZfitter* kinZfitter = new KinZfitter(isData,period); 
  TreeReader data(inpath);

  storeSF SFs;
  if(period==161||period==16)SFs.Setup16();
  else if(period==17)SFs.Setup17();
  else if(period==18)SFs.Setup18();
  TFile *fg_R9;
  if(period==16)fg_R9 = new TFile("external/16_phocorr.root");
  //if(period==16)fg_R9 = new TFile("external/transformation5x5_Legacy2016_v1.root");
  if(period==17)fg_R9 =  new TFile("external/17_phocorr.root");
  if(period==18)fg_R9 =  new TFile("external/18_phocorr.root");
  //TGraph *gg_R9EE = (TGraph*) fg_R9->Get("transffull5x5R9EE");
  //TGraph *gg_R9EB = (TGraph*) fg_R9->Get("transffull5x5R9EB");
  TGraph *gg_R9EE = (TGraph*) fg_R9->Get("gR9_EE");
  TGraph *gg_R9EB = (TGraph*) fg_R9->Get("gR9_EB");
  //TGraph *gg_resEB = (TGraph*) fg_R9->Get("gres_EB");
  //TGraph *gg_resEE = (TGraph*) fg_R9->Get("gres_EE");
  TFile *fptwei;
  if(period==17&&channel==0) fptwei= new TFile("external/17_ele_weiZgpt_datasb_new.root");
  if(period==17&&channel==1) fptwei= new TFile("external/17_mu_weiZgpt_datasb_new.root");
  if(period==18&&channel==0) fptwei= new TFile("external/18_ele_weiZgpt_datasb_new.root");
  if(period==18&&channel==1) fptwei= new TFile("external/18_mu_weiZgpt_datasb_new.root");
  TH1F *ptweight;
  if(period!=16)ptweight= (TH1F*) fptwei->Get("hd");
  AForest forest (outpath);
  //forest.setAnaTree();
  //forest.setfsrtree();
  //forest.setZTree();
  forest.setkinMVAtree();
  forest.setVBFMVAtree();
  PUWeightCalculator puCalc;
  PUWeightCalculator puCalcUp;
  PUWeightCalculator puCalcDown;
  //setting 
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
	  puCalcUp.Init("puwei/80X_puwei/36p0_invfb/PU_histo_13TeV_2016_GoldenJSON_69200nb.root");
	  puCalc.Init("puwei/80X_puwei/36p0_invfb/PU_histo_13TeV_2016_GoldenJSON_66000nb.root");
	  puCalcDown.Init("puwei/80X_puwei/36p0_invfb/PU_histo_13TeV_2016_GoldenJSON_63000nb.root");
	}
      else if(period==17)
	{
	      puCalcUp.Init("puwei/94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_75730nb.root");
	      puCalc.Init("puwei/94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_72383nb.root");
	      puCalcDown.Init("puwei/94X_puwei/42_invfb/PU_histo_13TeV_2017_GoldenJSON_69200nb.root");   
	}
      else if(period==18)
	{
	  /*if(isSig&&isrewei){
	    puCalcUp.Init("puwei/102X_puwei/fall17to2018/PU_histo_13TeV_2017to2018_GoldenJSON_80000nb.root");
	    puCalc.Init("puwei/102X_puwei/fall17to2018/PU_histo_13TeV_2017to2018_GoldenJSON_75730nb.root");  
	    puCalcDown.Init("puwei/102X_puwei/fall17to2018/PU_histo_13TeV_2017to2018_GoldenJSON_72400nb.root");
	  }
	  else if (isrewei)
	    {
	      puCalcUp.Init("puwei/102X_puwei/summer16to2018/PU_histo_13TeV_2016to2018_GoldenJSON_80000nb.root");
	      puCalc.Init("puwei/102X_puwei/summer16to2018/PU_histo_13TeV_2016to2018_GoldenJSON_75730nb.root");  
	      puCalcDown.Init("puwei/102X_puwei/summer16to2018/PU_histo_13TeV_2016to2018_GoldenJSON_72400nb.root");
	    }
	  
	    else {*/
	    puCalcUp.Init("puwei/102X_puwei/autum18/PU_histo_13TeV_2018_GoldenJSON_80000nb.root");
	    puCalc.Init("puwei/102X_puwei/autum18/PU_histo_13TeV_2018_GoldenJSON_75730nb.root");
	    puCalcDown.Init("puwei/102X_puwei/autum18/PU_histo_13TeV_2018_GoldenJSON_72400nb.root");
	    //}
	}
    }
  TLorentzVector pho, lep[2], zll, higgs,jet[2], dijet, alep,mcpho;
  vector<int> nmult; 
  /*ifstream in("runG.txt");
  vector<Long64_t> oldev;oldev.clear();
  while(!in.eof())
    {
      Long64_t tmp;
      in>>tmp;
      oldev.push_back(tmp);
    }
  */
  //int nphopt = 0, nmllgmll = 0 , nmllg= 0;
  //=======================EVENT  LOOP =========================//
  if(isbug==true) cout<<"open file & create tree"<<endl;
  cout<<"No weighted events: "<< data.GetEntriesFast()<<endl;
  for (Long64_t ev = 0; ev <  data.GetEntriesFast(); ev++)
    {
      N_totalev = data.GetEntriesFast();
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
      /*bool hasold = false;
      for(unsigned int num = 0 ; num < oldev.size(); num++)
	{
	  if(event==oldev[num])hasold= true;
	}
	if(!hasold)continue;*/
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
      wei_totalev += 1.*mcwei_*HZgvar.puwei*HZgvar.genwei;
      if(mucorr == true)
	{
	  Int_t* muCharge    = data.GetPtrInt("muCharge");//for roch corr
	  Int_t* muType      = data.GetPtrInt("muType");//for roch corr
	  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");//for roch corr
	  // do Rochester muon correction
	  for (Int_t i = 0; i < nMu ; i++)
	    {
	      //new roch
	      Float_t rand1;
	      //TRandom g;
	      rand1 = gRandom->Rndm();
	      
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

		///if (countmc > 0) SF = rc.kSpreadMC(muCharge[i], muPt_[i], muEta[i], muPhi[i], mcMu.Pt(),  0, 0);
		/*if (countmc == 0)*/ SF = rc.kSmearMC(muCharge[i], muPt_[i], muEta[i], muPhi[i], muTrkLayers[i], rand1,  0, 0);

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
	  //float* muCalibPt = data.GetPtrFloat("muPt");
	  
	  for(int j = 0; j < nMu; j++)
	    {
	      muPt.push_back(muCalibPt[j]);
	    }
	}
      if(isbug==true)cout<<"mu pt corr"<<endl;
      if (ev % 500000 == 0)
        {
	  fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
      //vertex filter
      Bool_t isPVGood = data.GetBool("isPVGood");
      if (isPVGood == false) continue;
      N_passPV++;
      wei_PV += 1.*HZgvar.puwei*HZgvar.mcwei*HZgvar.genwei;
      //trigger
      Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
      ULong64_t   HLTEleMuXIsPrescaled  = (ULong64_t)data.GetLong64("HLTEleMuXIsPrescaled");
      // HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
      float tmptrgsf[2];
      if(channel==0)
	{if (period>16&&(HLTEleMuX >>  40 & 1)==0) continue;
	  else if((HLTEleMuX >>  40 & 1)==0&&(HLTEleMuX >>  5 & 1) == 0)continue;
	    //== 0&&(HLTEleMuX >>  5 & 1) == 0) continue;//presscaled
	  /*if((HLTEleMuXIsPrescaled >>  40 & 1) == 1)cout<<"eledz is prescaled"<<endl;
	  if((HLTEleMuXIsPrescaled >>  5 & 1) == 1)cout<<"ele is prescaled"<<endl;*/
	}
      
      // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v OR HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v
      if (channel == 1)
	{ if (period>16&&(HLTEleMuX >> 14 & 1) == 0 && (HLTEleMuX >> 15 & 1) == 0)continue;
	  else if ((HLTEleMuX >> 14 & 1) == 0 && (HLTEleMuX >> 15 & 1) == 0&& ((HLTEleMuX >> 41) & 1) == 0 && ((HLTEleMuX >> 42) & 1) == 0)continue;
	  
	      //&& ((HLTEleMuX >> 41) & 1) == 0 && ((HLTEleMuX >> 42) & 1) == 0) continue;
	  /*if((HLTEleMuXIsPrescaled >>  14 & 1) == 1)cout<<"mu8 is prescaled"<<endl;
	  if((HLTEleMuXIsPrescaled >>  15 & 1) == 1)cout<<"tkmu8 is prescaled"<<endl;
	  if((HLTEleMuXIsPrescaled >>  41 & 1) == 1)cout<<"dzmu8 is prescaled"<<endl;
	  if((HLTEleMuXIsPrescaled >>  42 & 1) == 1)cout<<"dztkmu8 is prescaled"<<endl;*/
	}
      N_passtrigger++;
      wei_passtrg += 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.genwei;
      if(isbug==true)cout<<"trg done"<<endl;
      
      //lepton selection
      vector<TLorentzVector> multz;
      //set up kinematic fit objects
      std::map<unsigned int, TLorentzVector> selectedLeptons;
      std::map<unsigned int, TLorentzVector> selectedFsrMap;
      std::vector<int> lepID_kin,fsrID_kin;
      HZgvar.sfsrID_[0] = HZgvar.sfsrID_[1] = HZgvar.afsrID_[0] = HZgvar.afsrID_[1] = -99;
      selectedFsrMap.clear(); selectedLeptons.clear(); 
      multz.clear(); lepID_kin.clear();fsrID_kin.clear();
      
      //iaf(period==16)ElectronID16NonTrgMVA(data, 98, ZeeID,multz);
      //else if(period==17)ElectronID17NonTrgMVA(data, 98, ZeeID);
      //else 

      ElectronFallIDv2_16(data, 98, ZeeID);
      if(period==16)HZZmuID16forZg(data, muID, Zmm, muPt, channel,multz);
      else HZZmuID17forZg(data, muID, Zmm, muPt, channel);
      TLorentzVector kinlep[2];
      if (channel == 0)//electron loop
	{
	  if (ZeeID.size() < 2) continue;
	  if (elePt[ZeeID[0]] < 25.) continue;
	  if (elePt[ZeeID[1]] < 15.) continue;
	  lep[0].SetPtEtaPhiM(elePt[ZeeID[0]], eleEta[ZeeID[0]], elePhi[ZeeID[0]], 0.511*0.001);
	  lep[1].SetPtEtaPhiM(elePt[ZeeID[1]], eleEta[ZeeID[1]], elePhi[ZeeID[1]], 0.511*0.001);
	  if(isrefit)kinlep[0].SetPtEtaPhiM(elenocalibPt[ZeeID[0]], eleEta[ZeeID[0]], elePhi[ZeeID[0]], 0.511*0.001);
	  if(isrefit)kinlep[1].SetPtEtaPhiM(elenocalibPt[ZeeID[1]], eleEta[ZeeID[1]], elePhi[ZeeID[1]], 0.511*0.001);
	  N_passele++;
	}
      
      else if (channel==1) //muon loop
	{
	  if (Zmm.size() < 2) continue;
	  if (muPt[Zmm[0]] < 20.) continue;
	  if (muPt[Zmm[1]] < 10.) continue;
	  lep[0].SetPtEtaPhiM(muPt[Zmm[0]], muEta[Zmm[0]], muPhi[Zmm[0]], 105.7*0.001);
	  lep[1].SetPtEtaPhiM(muPt[Zmm[1]], muEta[Zmm[1]], muPhi[Zmm[1]], 105.7*0.001);
	  if(isrefit)kinlep[0].SetPtEtaPhiM(muPt_[Zmm[0]], muEta[Zmm[0]], muPhi[Zmm[0]], 105.7*0.001);
	  if(isrefit)kinlep[1].SetPtEtaPhiM(muPt_[Zmm[1]], muEta[Zmm[1]], muPhi[Zmm[1]], 105.7*0.001);
	  N_passmu++;
	}
      for (int i = 0; i < 2; i++)
	{
	  HZgvar.lepID_[i] = channel==0 ? ZeeID[i]:Zmm[i]; 
	  HZgvar.lepPt[i] = channel==0 ? elePt[ZeeID[i]]:muPt[Zmm[i]];
	  HZgvar.vec_lep[i] = lep[i];
	  if(isrefit)selectedLeptons[i] = kinlep[i];//kinfit
	  if(isrefit)lepID_kin.push_back(HZgvar.lepID_[i]);//kinfit
	}    
      if(data.HasMC())
	{
	  SFs.eleSF(data,HZgvar,HZgvar.cat,channel);
	  SFs.muSF(data,HZgvar,HZgvar.cat,channel);
	}//store SFs
      

      if(data.HasMC()&&channel==0)wei_passele += 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1];
      if(data.HasMC()&&channel==1)wei_passmu +=  1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1];

      //if(wei_passmu==0)cout<<HZgvar.SFmutrg_[0]<<HZgvar.SFmutrg_[1]<<" "<<HZgvar.SFmuID_[0]<<" "<<HZgvar.SFmuID_[1]<<endl;
      zll   = lep[0] + lep[1];
      if (zll.M()<50) continue;
      HZgvar.vec_Z = zll;
      N_mll++;
      if(data.HasMC())wei_mll += (channel==0)? 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]: 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1];
      //forest.fillZ(data, channel, aMCatNLO, HZgvar,  isSig);      
      if(isbug==true)cout<<"lep sel"<<endl;
     
      float* phoEt    = data.GetPtrFloat("phoCalibEt");//use this for analysis
      float* phoE    = data.GetPtrFloat("phoCalibE");//use this for analysis
      float* phoSigmaE    = data.GetPtrFloat("phoSigmaE");
      float* phoEta   = data.GetPtrFloat("phoEta");	
      float* phoSCEta = data.GetPtrFloat("phoSCEta");	
      float* phoPhi   = data.GetPtrFloat("phoPhi");	
      float* phoR9    = data.GetPtrFloat("phoR9Full5x5");	
      Int_t  nMC      = 0;
      Int_t* mcPID	  = NULL;
      Int_t* mcMomPID	  = NULL;
      float* mcMass	  = NULL;
      float* mcPt	  = NULL;
      float* mcEta 	  = NULL;
      float* mcPhi 	  = NULL;
      UShort_t* mcStatusFlag = NULL;
      if(data.HasMC())
	{
	  nMC = data.GetInt("nMC");
	  mcPID        = data.GetPtrInt("mcPID");
	  mcMomPID     = data.GetPtrInt("mcMomPID");
	  mcMass       = data.GetPtrFloat("mcMass");
	  mcPt         = data.GetPtrFloat("mcPt");
	  mcEta        = data.GetPtrFloat("mcEta");
	  mcPhi        = data.GetPtrFloat("mcPhi");
	  mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");
	}
      vector<int> phoID;
      Int_t phoIndex = -999;
      PhotonIDMVArun2(data,phoID,HZgvar,channel);

     
      int  passmult = 0;
      TLorentzVector multH;
      if (phoID.size() == 0) continue;
      if (phoEt[phoID[0]]<15.)continue;
      if(data.HasMC())wei_passpho += (channel==0)? 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]: 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1];
      N_passpho++;
      bool haspho = false;
      Int_t isPromptPhoton = 0;
      TLorentzVector tmppho;

      for (size_t j=0; j<phoID.size(); ++j)
	{
	  if(haspho == true) break; //tmp closed
	  if (phoEt[phoID[j]] < 15.) continue;
	  tmppho.SetPtEtaPhiM(phoEt[phoID[j]], phoEta[phoID[j]], phoPhi[phoID[j]], 0.);
	  if (tmppho.DeltaR(lep[0]) < 0.4 || tmppho.DeltaR(lep[1]) < 0.4) continue;
	  higgs = tmppho + zll;
	  //cout<<event<<" Hmass:"<<higgs.M()<<"  mll+mllg:"<<higgs.M() + zll.M()<<" phopt/mllg:"<<tmppho.Pt()/higgs.M()<<endl;
	  if (higgs.M() > 180.|| higgs.M()<100.) continue;
	  //nmllg++;
	  if (higgs.M() + zll.M() < 185.) continue; 
	  //nmllgmll++;
	  if (tmppho.Pt()/higgs.M() < 15./110.) continue; 
	  //nphopt++;
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
      HZgvar.phoID_= phoIndex;
      if(period!=16)HZgvar.ptwei = ptweight->GetBinContent(ptweight->FindBin(higgs.Pt()));
      vector<int> accepted;accepted.clear();
      if(passmult>1)nmult.push_back(passmult);
      if(isFSR&&channel==1)
	{
          float* pfPhoEt 		= data.GetPtrFloat("pfPhoEt");
          float* pfPhoEta 		= data.GetPtrFloat("pfPhoEta");
          float* pfPhoPhi 		= data.GetPtrFloat("pfPhoPhi");
          for(int i = 0 ; i < 2 ; i++)
	    {
	      SMPZZ_FSR(data,HZgvar,accepted,channel,i);
	      HZgvar.fsr.assign(accepted.begin(),accepted.end());
	      Atlas_FSR(data,HZgvar,i);
	      fsrID_kin.push_back(HZgvar.sfsrID_[i]);//put HZZ method
	      TLorentzVector tmpfsr;
	      if(HZgvar.sfsrID_[i]!=-99)tmpfsr.SetPtEtaPhiM(pfPhoEt[HZgvar.sfsrID_[i]],pfPhoEta[HZgvar.sfsrID_[i]],pfPhoPhi[HZgvar.sfsrID_[i]],0.);
	      else tmpfsr.SetPtEtaPhiM(0.,0.,0.,0.);
	      selectedFsrMap[i] = tmpfsr;
	    }
	}
      else{
        fsrID_kin.push_back(-99);  
        fsrID_kin.push_back(-99);  
      }

      ///apply scale smear correc
      vector<float> R9;
      R9.clear();
      vector<float>phores;phores.clear();
      if(data.HasMC())R9.push_back(fabs(phoEta[phoIndex])<1.479 ? gg_R9EB->Eval(phoR9[phoIndex]):gg_R9EE->Eval(phoR9[phoIndex]));
      else R9.push_back(phoR9[phoIndex]);
      if(data.HasMC())phores.push_back(phoSigmaE[phoIndex]/phoE[phoIndex]);
      else phores.push_back(phoSigmaE[phoIndex]/phoE[phoIndex]);
      vector<float> jetPt, jetEn;
      Int_t nJet  		 = data.GetInt("nJet");
      float *jetPt_ 	 = data.GetPtrFloat("jetPt");
      float *jetEn_ 	 = data.GetPtrFloat("jetEn");
      float *jetP4Smear  = NULL;

      if(data.HasMC())jetP4Smear = data.GetPtrFloat("jetP4Smear");
      for(int i = 0; i < nJet ; i++)
	{
	  float jetP4Smear_ = 1.;
	  //cout<<jetP4Smear_<<endl;
	  if(data.HasMC()) jetP4Smear_ = jetP4Smear[i];
	  jetPt.push_back(jetPt_[i]*jetP4Smear_);
	  jetEn.push_back(jetEn_[i]*jetP4Smear_);
	}	 
      if(isbug)cout<<"var corr"<<endl;
      if(data.HasMC())SFs.phoSF(data,HZgvar,R9,period);      
      
      N_passHpt++;
      if(data.HasMC())wei_passall += (channel==0) ?1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_: 1.*HZgvar.mcwei*HZgvar.puwei*HZgvar.SFmutrg_[0]* HZgvar.SFmutrg_[1]*HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_;
      //HZgvar.phoID_ = phoIndex;
      HZgvar.vec_pho = pho;
      HZgvar.vec_higgs = higgs;
      TLorentzVector fsrphoton;
      /*for (int l = 0 ; l < nMC; l++)
	{
	  if(mcPID[l]==22&&fabs(mcGMomPID[l])!=15&&(fabs(mcMomPID[l])==13||mcMomPID[l]==23)&&(((mcStatusFlag[l] >> 1) & 1) \
											     ==1||((mcStatusFlag[l] >> 0) & 1)==1)){fsrphoton.SetPtEtaPhiM(mcPt[l],mcEta[l],mcPhi[l],mcMass[l]);nfsr++;}
											     }*/
      //if(HZgvar.vec_pho.DeltaR(fsrphoton)<0.1)nfsr++;
      
      if(isbug==true)cout<<"event sel done"<<endl;	  
      
      //set kinematic fit
      if(isrefit)
	{
	  vector<double> pTerr;
	  pTerr.clear();
	  kinZfitter->Setup(data,lepID_kin, fsrID_kin, pTerr, channel, isData, selectedLeptons, selectedFsrMap,corr);
	  //if(isSig)HZgvar.mllerr = kinZfitter->GetMZ1Err();
	  //if(isSig)HZgvar.REFIT_mllerr =  kinZfitter->GetRefitM4lErr();
	  vector<TLorentzVector> refitlep ;
	  TLorentzVector refitH, refitZ;
	  kinZfitter->KinRefitZ();
	  refitlep = kinZfitter->GetRefitP4s();
	  refitH  = refitlep[0]+refitlep[1]+pho;
	  HZgvar.REFIT_mllg = refitH.M();
	  HZgvar.REFIT_mll = kinZfitter->GetRefitMZ1();
	  for(int i = 0; i < 2; i++)
	    {
	      HZgvar.REFIT_lepPt[i] = refitlep[i].Pt();
	      HZgvar.REFIT_lepPtErr[i] = pTerr[i];
	      
	    }
	  if(isbug==true)cout<<"kinfit done"<<endl;	  
	}
    
      //put kinematic MVA info
      HZgAngles(HZgvar);
      if(isMVA)HZgvar.kinMVA = HZgkin_MVA(data,channel,period,HZgvar, R9,phores);
      //defining category	
      HZgvar.isVH = VHtag(data,HZgvar,jetPt,jetEn);
      HZgvar.isdbtag = dbtag(data,HZgvar,jetPt,jetEn);//no overlap
      HZgvar.isLep= leptag(data, channel,muID, muPt, HZgvar,period);
      if(HZgvar.isLep!=1)  HZgvar.isVBF = VBFtag(data,HZgvar,jetPt,jetEn,isjetMVA,period);
      if(HZgvar.isLep!=1&&HZgvar.isVBF==1&&isjetMVA==1)
	{
	  HZgvar.VBFMVA = HZgVBF_MVA(data,HZgvar,channel,period,jetPt,jetEn);
	  forest.fillVBFMVA(data, channel, HZgvar,jetPt,jetEn,isSig);  
	}
      //if(HZgvar.isLep!=1&&HZgvar.VBFMVA>0.){HZgvar.isVBF = 1;HZgvar.cat = 5;}
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
     
      if(data.HasMC())
	{
	  SFs.eleSF(data,HZgvar,HZgvar.cat,channel);
	  SFs.muSF(data,HZgvar,HZgvar.cat,channel);
	}//store SFs
      if(isbug==true) cout<<"sf fill"<<endl;
      forest.fillkinMVA(data, channel, HZgvar, R9, phores,isSig);      
      if(isbug==true) cout<<"fill kinmva tree"<<endl;
      //forest.fillAna(data, channel, aMCatNLO, HZgvar, R9,jetPt, jetEn, isSig,isFSR,isrefit);

      if(isbug==true) cout<<"fill tree"<<endl;
   
      eleID.clear(); phoID.clear(); ZeeID.clear();  Zmm.clear();R9.clear();jetEn.clear();jetPt.clear();phores.clear();
      if(isbug==true)cout<<"all done"<<endl; 	  
    } // event loop end

  cout<<"-------------------------------------------------------"<<endl;
  fprintf(stderr, "Processed all events\n");
  
  cout << "totalev:" <<totalEvents<<"\n"<<"pass PV: "<< N_passPV<<"\n"<<"pass trigger:"<<" "<<N_passtrigger<<"\n"<<"ele:"<<N_passele<<" \n"<<"mu:"<<N_passmu<<"\n"<<"mll:"<<N_mll<<"\n"<<"pho:"<<N_passpho<<"\n"<<"pass all:"<<N_passHpt<<endl;
  if(isData==0){
    cout<<"weighted events: "<<endl;
    cout << "totalev:" <<wei_totalev<<"\n pass PV "<<wei_PV<<"\n"<<"pass trigger:"<<" "<<wei_passtrg<<"\n"<<"pass ele sel:"<<wei_passele<<" "<<"mu"<<wei_passmu<<"\n"<<"mll:"<<wei_mll<<"\n"<<"pass pho :"<<wei_passpho<<"\npass all:"<<wei_passall<<endl;
  }
 
  cout<<"-------------------------------------------------------------"<<endl;
  cout<<"cat"<<"\n"<<"1 = "<<N_cat1<<endl<<"2 = "<<N_cat2<<endl<<"3 = "<<N_cat3<<endl<<"4 = "<<N_cat4<<endl<<"5 = "<<N_cat5<<endl<<"6 = "<<N_cat6<<endl<<"7 = "<<N_cat7<<endl<<"8 = "<<N_cat8<<endl<<"9 ="<<N_cat9<<endl<<"10 ="<<N_cat10<<endl<<"11 = "<<N_cat11<<endl;

  cout<<"Numbers of FSR~~"<<nfsr<<endl;
}
