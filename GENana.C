/// code for Generator level study
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"

#include "plugin/untuplizer_07.h"
#include "TH1F.h"
#include "plugin/MCSelections1.h"
//#include "plugin/dR.h"
//#include "plugin/Matching.h"


using namespace std;

void GENana2(const char* inpaths,  TString outpath = "minitree.root", Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0)
//void GENana(Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0)
{

  /// inpaths  = array of paths to files with ggNtuplizer's TTrees;
  /// npaths   = size of inpaths;
  /// outpath  = path to output root file;
  /// channel  = 0 : electron, 1 : muon
  /// xs       = cross section
  /// lumi     = luminosity
  /// aMCatNLO = 0 : not aMC@NLO, 1 : aMC@NLO (with negative weight)KKKILL,LPKKKKK

  // open tree(s) with events to be processed
  TreeReader data(inpaths);
  //     TreeReader data("/data6/ggNtuples/V08_00_11_01/job_spring16_HZg_ttH_125GeV.root");
  Int_t cat1,cat2,cat3,cat4;
  cat1=cat2=cat3=cat4=0;
  int totalpho, relpho;
  totalpho = relpho = 0;
  Int_t    run_, lumis_, nVtx_,cat,catmom, alepmatch,isEB;
  Float_t  puwei_  = 1.;
  Float_t  mcwei_  = 1.;
  Float_t  genwei_ = 1.;
  Long64_t event_;
  Float_t mclepPt[2], mclepEta[2], mclepPhi[2], mcphodR,mcalepdR[2], mcphoPhi, mcphoEta, mcphoPt, mcalepPt[2], mcalepEta[2], mcalepPhi[2], mcmllg, mcmll, mcphoZdR,mcmllgpt;

  // prepare output tree
  TTree *outtreemc = new TTree("tMC","Generator level tree");
  outtreemc->Branch("run",        &run_,          "run/I");
  outtreemc->Branch("lumis",      &lumis_,        "lumis/I");
  outtreemc->Branch("nVtx",       &nVtx_,         "nVtx/I");
  outtreemc->Branch("event",      &event_,        "event/L");
  outtreemc->Branch("mcwei",      &mcwei_,        "mcwei/F");
  outtreemc->Branch("mclepPt",    mclepPt,        "mclepPt[2]/F");
  outtreemc->Branch("mclepEta",   mclepEta,       "mclepEta[2]/F");
  outtreemc->Branch("mclepPhi",   mclepPhi,       "mclepPhi[2]/F");
  //outtreemc->Branch("mcqPt",    mcqPt,        "mcqPt[2]/F");
  //outtreemc->Branch("mcqEta",   mcqEta,       "mcqEta[2]/F");
  //outtreemc->Branch("mcqPhi",   mcqPhi,       "mcqPhi[2]/F");
  outtreemc->Branch("mcalepPt",   &mcalepPt,      "mcalepPt/F");
  outtreemc->Branch("mcalepEta",  &mcalepEta,     "mcalepEta/F");
  outtreemc->Branch("mcalepPhi",  &mcalepPhi,     "mcalepPhi/F");
  //outtreemc->Branch("mcaqPt",   &mcaqPt,      "mcaqPt/F");
  //outtreemc->Branch("mcaqEta",  &mcaqEta,     "mcaqEta/F");
  //outtreemc->Branch("mcaqPhi",  &mcaqPhi,     "mcaqPhi/F");
  outtreemc->Branch("cat",        &cat,           "cat/I");
  outtreemc->Branch("isEB",        &isEB,           "isEB/I");
  outtreemc->Branch("catmom",     &catmom,        "catmom/I");
  outtreemc->Branch("mcphoEta",   &mcphoEta,      "mcphoEta/F");
  outtreemc->Branch("mcphoPhi",   &mcphoPhi,      "mcphoPhi/F");
  outtreemc->Branch("mcphoPt",    &mcphoPt,       "mcphoPt/F");
  outtreemc->Branch("mcmll",      &mcmll,         "mcmll/F");
  outtreemc->Branch("mcmllg",     &mcmllg,        "mcmllg/F");
  outtreemc->Branch("mcmllgpt",   &mcmllgpt,      "mcmllgpt/F");
  outtreemc->Branch("mcphodR",    &mcphodR,       "mcphodR/F");
  outtreemc->Branch("mcphoZdR",    &mcphoZdR,       "mcphoZdR/F");
  outtreemc->Branch("mcalepdR",   mcalepdR,       "mcalepdR[2]/F");
  /*      TFile *fo = new TFile("MCWminusH.root", "RECREATE");
	  fo->cd();*/
  TFile* fo = TFile::Open(outpath.Data(), "RECREATE");
  if (!fo || fo->IsZombie())  FATAL("TFile::Open() failed");
  fo->cd();


  // pileup reweighting for MC
  /*  PUWeightCalculator puCalc;
      if (data.HasMC()) puCalc.Init("puweights/PU_histo_13TeV_SilverJSON.root");
  */
  // compute mc weights
  //  data.Print();

  if (aMCatNLO == 1)
    {
      Float_t totalEvents = 0;
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
      mcwei_ = (totalEvents != 0) ? xs * lumi / totalEvents : 1;
      cout<<"total events : "<<totalEvents<<endl;
    }
  else
    {
      //      cout<<xs<<" "<<lumi<<" "<<data.GetEntriesFast()<<endl;
      mcwei_ = xs * lumi / data.GetEntriesFast();
    }

  Int_t counts = 0;
  Int_t countNoPho = 0;
  TLorentzVector lep[2], alep[2],pho, higgs, Z;
  Int_t nmu, nele;
  nmu = nele = 0.;
  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
      data.GetEntry(ev);
 
      run_   = data.GetInt("run");
      lumis_ = data.GetInt("lumis");
      event_ = data.GetLong64("event");
      nVtx_  = data.GetInt("nVtx");
      isEB = 0;
      alepmatch = 0;


      /*   if (data.HasMC())
           {
	   float generatorWeight = data.GetFloat("genWeight");

	   if (aMCatNLO == 1) genwei_ = (generatorWeight > 0) ? 1. : -1.;
	   else               genwei_ = generatorWeight;
           }

      */

      if (data.HasMC())
        {

	  Int_t  nMC      = 0;
	  Int_t* mcPID    = NULL;
	  Int_t* mcMomPID = NULL;
	  Int_t* mcGMomPID = NULL;
	  float* mcMomEta = NULL;
	  float* mcMomPt = NULL;
	  float* mcPt     = NULL;
	  float* mcEta    = NULL;
	  float* mcPhi    = NULL;
	  float* mcMass    = NULL;
	  UShort_t* mcStatusFlag = NULL;
	  nMC          = data.GetInt("nMC");
	  mcPID        = data.GetPtrInt("mcPID");
	  mcGMomPID     = data.GetPtrInt("mcGMomPID");
	  mcMomPID     = data.GetPtrInt("mcMomPID");
	  mcMomEta     = data.GetPtrFloat("mcMomEta");
	  mcMomPt    = data.GetPtrFloat("mcMomPt");
	  mcPt         = data.GetPtrFloat("mcPt");
	  mcEta        = data.GetPtrFloat("mcEta");
	  mcPhi        = data.GetPtrFloat("mcPhi");
	  mcMass        = data.GetPtrFloat("mcMass");
	  mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");

	  genwei_ = 1;
	  //photon internal conversion 
	  for(int k = 0; k < nMC; k++)
            {
	      if(mcMomPID[k]!=25||fabs(mcPID[k])!=22) continue;

	      if (((mcStatusFlag[k] >> 0) & 1) == 1&&((mcStatusFlag[k] >> 1) & 1) == 1) relpho++;
            }

	  //lepton selection

	  Int_t mcele = 0;
	  Int_t mcmu = 0;

	  Int_t type[2];
	  for (int i = 0; i <nMC; i++)
	    {
	      if(fabs(mcPID[i])!=11&&fabs(mcPID[i])!=13) continue;
	     
	      if(fabs(mcPID[i])==11)
		{
		  if(fabs(mcEta[i])>2.5) continue;
		  if(mcPt[i]<15.)continue;
		}
	      else
		{
		  if(fabs(mcEta[i])>2.4) continue;
		  if(mcPt[i]<10.)continue;
		}
	  
	      if(mcGMomPID[i]==25&&mcMomPID[i]==23)
		{
		  if(fabs(mcPID[i])==11)
		    {
		      mclepPt[mcele] = mcPt[i];
		      mclepEta[mcele] = mcEta[i];
		      mclepPhi[mcele] = mcPhi[i];
		      lep[mcele].SetPtEtaPhiM(mclepPt[mcele],mclepEta[mcele],mclepPhi[mcele], mcMass[i]);
		      mcele++;       						
		    }
		  else
		    {
		      mclepPt[mcmu] = mcPt[i];
		      mclepEta[mcmu] = mcEta[i];
		      mclepPhi[mcmu] = mcPhi[i];
		      lep[mcmu].SetPtEtaPhiM(mclepPt[mcmu],mclepEta[mcmu],mclepPhi[mcmu], mcMass[i]);
		      mcmu++;		
		    }
		}
	    }
	  if(mcmu < 2 && mcele < 2)   continue; //discard the event without signal
	  if(mcmu>=2) nmu++;
	  if(mcele>=2) nele++;

	  Int_t mcaele = 0;
	  Int_t mcamu = 0;
	  //additional lepton categorization

	  /*	  for (Int_t i = 0 ; i <nMC; i++)
	    {

	      if((mcMomPID[i]==23||fabs(mcMomPID[i])==24)&&mcGMomPID[i]!=25)
		{
		  if(mcaele<2&&mcele>1&&fabs(mcPID[i])==11)
		    {
		      cat = 6;
		      mcalepPt[mcaele] = mcPt[i];
		      mcalepEta[mcaele] = mcEta[i];
		      mcalepPhi[mcaele] = mcPhi[i];
		      alep[mcaele].SetPtEtaPhiM(mcalepPt[mcaele],mcalepEta[mcaele],mcalepPhi[mcaele],mcMass[i]);
		      cat1++;
		      mcaele++;
		    }
		  else if(mcamu<2&&mcele>1&&fabs(mcPID[i])==13)
		    {
		      cat = 7;
		      mcalepPt[mcamu] = mcPt[i];
		      mcalepEta[mcamu] = mcEta[i];
		      mcalepPhi[mcamu] = mcPhi[i];
		      alep[mcamu].SetPtEtaPhiM(mcalepPt[mcamu],mcalepEta[mcamu],mcalepPhi[mcamu],mcMass[i]);
		      cat2++;
		      mcamu++;
		      }
		  else if(mcaele<2&&mcmu>1&&fabs(mcPID[i])==11)
		    {
		      cat = 9;
		      mcalepPt[mcaele] = mcPt[i];
		      mcalepEta[mcaele] = mcEta[i];
		      mcalepPhi[mcaele] = mcPhi[i];
		      alep[mcaele].SetPtEtaPhiM(mcalepPt[mcaele],mcalepEta[mcaele],mcalepPhi[mcaele],mcMass[i]);
		      cat4++;
		      mcaele++;
		    }
		  else if(mcamu<2&&mcmu>1&&fabs(mcPID[i])==13)
		    {
		      cat = 8;
		      mcalepPt[mcamu] = mcPt[i];
		      mcalepEta[mcamu] = mcEta[i];
		      mcalepPhi[mcamu] = mcPhi[i];
		      alep[mcamu].SetPtEtaPhiM(mcalepPt[mcamu],mcalepEta[mcamu],mcalepPhi[mcamu],mcMass[i]);
		      cat3++;
		      mcamu++;
		      }
		  if(mcaele<2||mcamu<2) mcalepPt[1] = mcalepEta[1] = mcalepPhi[1] = 0;
		}
	  */

	
      //photon selection
      vector<int> phoID;
	  MCpho(data, phoID);

	  //photon pt and eta
	  if(phoID.size()<1) continue;

	  mcphoPt = mcPt[phoID[0]];
	  mcphoEta = mcEta[phoID[0]];
	  mcphoPhi = mcPhi[phoID[0]];
	  pho.SetPtEtaPhiM(mcphoPt, mcphoEta, mcphoPhi, 0.);
	  phoID.clear();
	}    

      mcphoZdR = TMath::Min(lep[0].DeltaR(pho),lep[1].DeltaR(pho));
      //mcphodR = TMath::Min(alep[0].DeltaR(pho),alep[1].DeltaR(pho));
      //mcalepdR[0] = TMath::Min(alep[0].DeltaR(lep[0]),alep[1].DeltaR(lep[0]));
      //mcalepdR[1] = TMath::Min(alep[0].DeltaR(lep[1]),alep[1].DeltaR(lep[1]));
      Z = lep[0]+lep[1];
      higgs = Z + pho;
      mcmllg = higgs.M();
      mcmllgpt = higgs.Pt();
      mcmll = Z.M();
      outtreemc->Fill();
      counts++;

     // event loop
    }
  cout <<"processed "<<counts<<" events !"<<endl;
  //cout<<"no photon events : "<<countNoPho<<endl;
  cout<<cat1<<" "<<cat2<<" "<<cat3<<" "<<cat4<<endl;
  cout<<"frac:"<<relpho<<" "<<data.GetEntriesFast()<<endl;
  outtreemc->Write();
  //WplusH->Write();
  fo->Write();
  fo->Close();
  cout<<nele<<" "<<nmu<<endl;
  delete fo;

}
