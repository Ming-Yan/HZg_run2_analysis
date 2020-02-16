///read the numbers of event
#include "plugin/untuplizer_07.h"
#include <vector>
#include <iostream>

using namespace std;

//void event(const char** inpaths, int npaths, TString outpath = "minitree.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, Int_t processID=0)
void out_tree()
{
    TString insample[14] =
    {
        "ele_HZg_ggF_125GeV.root",
        "ele_HZg_VBF_125GeV.root",
        "ele_HZg_ttH_125GeV.root",
        "ele_HZg_ZH_125GeV.root",
        "ele_HZg_WplusH_125GeV.root",
        "ele_HZg_WminusH_125GeV.root",
        "mu_HZg_ggF_125GeV.root",
        "mu_HZg_VBF_125GeV.root",
        "mu_HZg_ttH_125GeV.root",
        "mu_HZg_ZH_125GeV.root",
        "mu_HZg_WplusH_125GeV.root",
        "mu_HZg_WminusH_125GeV.root",
        "ele_EG.root",
        "mu_Mu.root",
    };
    for (Int_t i= 12 ; i<14; ++i)
    {
        //prepare input tree
        TString inpathmc  = "/home/mingyan/output/mc/mc_Moriond17_skim_update0322_"+insample[i];
        TString inpathdata  = "/home/mingyan/output/Data_Moriond17_skim_update0322_"+insample[i];
	//TFile *f = TFile::Open(inpathmc);
	TFile *f = TFile::Open(inpathdata);
        TTree *tzg = (TTree*)f->Get("tZg");
        TTree *tz = (TTree*)f->Get("tZ");
        Int_t cat;
        Int_t run_,lumis_;
        Long64_t  event_;
        Float_t lepPt_[2], lepEta_[2], lepPhi_[2], gPt_, gEta_, gPhi_,mllg_,mll_,puwei_,mcwei_;
        tzg->SetBranchAddress("run",      &run_);
        tzg->SetBranchAddress("event",    &event_);
        tzg->SetBranchAddress("lumis",    &lumis_);
        tzg->SetBranchAddress("puwei",    &puwei_);
        tzg->SetBranchAddress("mcwei",    &mcwei_);
        tzg->SetBranchAddress("cat",      &cat);
        tzg->SetBranchAddress("lepPt",    lepPt_);
        tzg->SetBranchAddress("lepEta",   lepEta_);
        tzg->SetBranchAddress("lepPhi",   lepPhi_);
        tzg->SetBranchAddress("phoPt",      &gPt_);
        tzg->SetBranchAddress("phoEta",     &gEta_);
        tzg->SetBranchAddress("phoPhi",    &gPhi_);
        tzg->SetBranchAddress("mllg",     &mllg_);
        tz->SetBranchAddress("mll",       &mll_);

        TString outpath  = "/home/mingyan/output/bias/minitree_"+insample[i];
        TFile *fout = new TFile(outpath,"recreate");
        TTree *ts = new TTree ("minitree", "lepton tag tree");

        //prepare out tree
        Int_t run, category;
        Long64_t event;
        Float_t lumi, hzg_mass, hz_mass,lep1Pt, lep2Pt, lep1Eta, lep2Eta, lep1Phi, lep2Phi, phoPt, phoEta, phoPhi,mcwei,puwei;
	ts->Branch("run",      &run,     "run/I");
        ts->Branch("category",      &category,     "category/I");
        ts->Branch("event",    &event,   "event/L");
        ts->Branch("lumi",     &lumi,    "lumi/F");
        ts->Branch("lep1Pt",   &lep1Pt,  "lep1Pt/F");
        ts->Branch("lep1Eta",  &lep1Eta, "lep1Eta/F");
        ts->Branch("lep1Phi",  &lep1Phi, "lep1Phi/F");
        ts->Branch("lep2Pt",   &lep2Pt,  "lep2Pt/F");
        ts->Branch("lep2Eta",  &lep2Eta, "lep2Eta/F");
        ts->Branch("lep2Phi",  &lep2Phi, "lep2Phi/F");
        ts->Branch("phoPt",    &phoPt,   "phoPt/F");
        ts->Branch("phoEta",   &phoEta,  "phoEta/F");
        ts->Branch("phoPhi" ,  &phoPhi,  "phoPhi/F");
        ts->Branch("hzg_mass", &hzg_mass,"hzg_mass/F");
        ts->Branch("hz_mass",  &hz_mass, "hz_mass/F");

        for ( Long64_t ev = 0; ev < tzg->GetEntriesFast(); ev++)
        {
            tzg->GetEntry(ev);
            run = run_;
            event = event_;
            lumi = lumis_;
            lep1Pt = lepPt_[0];
            lep1Eta = lepEta_[0];
            lep1Phi = lepPhi_[0];
            lep2Pt  = lepPt_[1];
            lep2Eta = lepEta_[1];
            lep2Phi = lepPhi_[1];
            phoPt = gPt_;
            phoEta = gEta_;
            phoPhi = gPhi_;
            hzg_mass = mllg_;
	    category = cat;
	    tz->GetEntry(ev);
	    hz_mass = mll_;
            ts->Fill();

        }
	/*	for ( Long64_t ev = 0; ev < tz->GetEntriesFast(); ev++)
	  {
	    tz->GetEntry(ev);
            hz_mass = mll_;
	    ts->Fill();
	    //	    cout<<hz_mass<<endl;
	  }
	*/
        ts->Write("", TObject::kOverwrite);
	cout<<"process:"<<outpath<<endl;
    }

}
