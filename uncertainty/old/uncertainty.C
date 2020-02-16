//use for synchronization
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"

#include "plugin/puweicalc.h"
#include "plugin/untuplizer.h"
#include "plugin/dR.h"
#include "plugin/MCSelection.h"
//#include "plugin/Matching.h"
#include "plugin/ElectronSelections2.h"
#include "plugin/MuonSelections1.h"
#include "plugin/PhotonSelections.h"

#include "plugin/rochcor2016.h"
#include "plugin/RoccoR.h"

using namespace std;

void mana2(const char* inpath, TString outpath = "minitree.root", Int_t channel=0, Float_t xs=1, Float_t lumi=1, Int_t aMCatNLO=0, Int_t photonRemoval=0, int isGH = 0, Int_t processID=0)


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
    //    TreeReader data("/data6/ggNtuples/V08_00_11_01/job_spring16_HZg_WplusH_125GeV.root");
    //  TreeReader data("/data1/ggNtuples/V08_00_11_01/job_DoubleEG_Run2016B_PRv2.root");
    TreeReader data(inpath);
    //           data.Print();
    // read in SFs and uncertainties
    TFile *fe_GSF = new TFile("external/Trigger_eff_Moriond17_SFs.root");
    TFile *fe_ID  = new TFile("external/eleMVA_WP90_Moriond17_SFs.root");
    TFile *fg_ID  = new TFile("external/phoMVA_WP90_Moriond17_SFs.root");
    TFile *fm_Trk = new TFile("external/muTrkEff_above10.root");
    TFile *fm_ID  = new TFile("external/Muon_ID_Moriond17_SFs.root");
    TFile *fm_Iso = new TFile("external/Muon_Iso_Moriond17_SFs.root");

    TH2F              *he_GSF = (TH2F*) fe_GSF->Get("EGamma_SF2D");
    TH2F              *he_ID  = (TH2F*) fe_ID->Get("EGamma_SF2D");
    TH2F              *hg_ID  = (TH2F*) fg_ID->Get("EGamma_SF2D");
    TGraphAsymmErrors *gm_Trk = (TGraphAsymmErrors*) fm_Trk->Get("ratio_eta");
    TH2F              *hm_ID  = (TH2F*) fm_ID->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
    TH2F              *hm_Iso = (TH2F*) fm_Iso->Get("LooseISO_TightID_pt_eta/abseta_pt_ratio");

    // prepare output tree
    TFile* fo = TFile::Open(outpath.Data(),"RECREATE");
    if (!fo || fo->IsZombie())  FATAL("TFile::Open() failed");
    fo->cd();

    ///counters
    Int_t N_totalev = 0;// total event #
    Int_t N_passtrigger = 0;//pass trigger #
    Int_t N_passele = 0;//pass particle selection:ele
    Int_t N_passmu = 0;//pass particle selection:mu
    Int_t N_passpho = 0;//pass particle selection:pho
    Int_t N_mll = 0; //pass mll>50 #
    Int_t N_dR = 0;//dR>0.4 #
    Int_t N_rmelepho = 0;//remove fake ele #
    Int_t N_mllgmll = 0; //pass mllg&mll #
    Int_t N_passH = 0;//passing Higgs mass #
    Int_t N_passHpt = 0;//passing higgs mass /pt
    Int_t N_cat1, N_cat2, N_cat3, N_cat4, N_cat5, N_cat6, N_cat7,  N_cat8, N_cat9, N_cat10;
    N_cat1 = N_cat2 = N_cat3 = N_cat4 = N_cat5 = N_cat6 = N_cat7 = N_cat8 = N_cat9 = N_cat10 = 0;
    Int_t t1, t2, t3, t4, t5 ,t6;
    t1 = t2 = t3 =t4 = t5 =t6 =0;
//limit settings for 5GeV
    Int_t nsig1 = 0;
    float sig1 = 2.12469;

    //prepare tree branch
    Int_t run_, lumis_, nVtx_, lepCh_[2], isEBEE_,nMC_;
    Float_t puwei_     = 1.;
    Float_t puweiUp_   = 1.;
    Float_t puweiDown_ = 1.;
    Float_t mcwei_     = 1.;
    Float_t genwei_    = 1.;
    Float_t lepPt_[2], lepEta_[2], lepPhi_[2], lepSCEta_[2],lepSCPhi_[2], lepR9_[2], lepPhoMVA_[2], mll_;
    Float_t mcLepPt_[2], mcLepEta_[2], mcLepPhi_[2], mcmindR_,mcPhoPhi_,mcPhoEta_, mcPhoPt_,mcmllg_,mcmll_, mcaLepPt_, mcaLepEta_;
    Int_t mcLepCh_[2], mcaLepCh_,mcMatch;
    Long64_t event_;
    Int_t   processID_ = processID;

    /*    TTree *outtreeMC_ = new TTree("tMC", "mini tree for acc x eff");
    outtreeMC_->Branch("run",       &run_,       "run/I");
    outtreeMC_->Branch("lumis",     &lumis_,     "lumis/I");
    outtreeMC_->Branch("event",     &event_,     "event/L");
    outtreeMC_->Branch("nVtx",      &nVtx_,      "nVtx/I");
    outtreeMC_->Branch("puwei",     &puwei_,     "puwei/F");
    outtreeMC_->Branch("mcwei",     &mcwei_,     "mcwei/F");
    outtreeMC_->Branch("genwei",    &genwei_,    "genwei/F");
    outtreeMC_->Branch("processID", &processID_, "processID/I");
    outtreeMC_->Branch("mcLepEta",  mcLepEta_,   "mcLepEta[2]/F");
    outtreeMC_->Branch("mcLepPt",   mcLepPt_,    "mcLepPt[2]/F");
    outtreeMC_->Branch("mcLepPhi",  mcLepPhi_,   "mcLepPhi[2]/F");
    outtreeMC_->Branch("mcLepCh",   mcLepCh_,    "mcLepCh[2]/I");
    outtreeMC_->Branch("mcaLepEta", &mcaLepEta_,  "mcaLepEta[2]/F");
    outtreeMC_->Branch("mcaLepPt",  &mcaLepPt_,   "mcaLepPt[2]/F");
    outtreeMC_->Branch("mcaLepCh",  &mcaLepCh_,  "mcaLepCh/I");
    outtreeMC_->Branch("mcPhoPhi", &mcPhoPhi_,   "mcPhoPhi/F");
    outtreeMC_->Branch("mcPhoPt",  &mcPhoPt_,    "mcPhoPt/F");
    outtreeMC_->Branch("mcPhoEta", &mcPhoEta_,   "mcPhoEta/F");
    outtreeMC_->Branch("mcmindR",  &mcmindR_,    "mcmindR/F");
    outtreeMC_->Branch("mcmll",    &mcmll_,      "mcmll/F");
    outtreeMC_->Branch("mcmllg",   &mcmllg_,     "mcmllg/F");
    outtreeMC_->Branch("mcMatch",  &mcMatch,     "mcMatch/I");*/

    TTree *outtreeZ_ = new TTree("tZ", "mini tree for Z->ll");
    outtreeZ_->Branch("run",       &run_,       "run/I");
    outtreeZ_->Branch("lumis",     &lumis_,     "lumis/I");
    outtreeZ_->Branch("event",     &event_,     "event/L");
    outtreeZ_->Branch("nVtx",      &nVtx_,      "nVtx/I");
    outtreeZ_->Branch("lepCh",      lepCh_,     "lepCh[2]/I");
    outtreeZ_->Branch("lepPt",      lepPt_,     "lepPt[2]/F");
    outtreeZ_->Branch("lepEta",     lepEta_,    "lepEta[2]/F");
    outtreeZ_->Branch("lepPhi",     lepPhi_,    "lepPhi[2]/F");
    outtreeZ_->Branch("lepSCEta",   lepSCEta_,  "lepSCEta[2]/F");
    outtreeZ_->Branch("lepR9",      lepR9_,     "lepR9[2]/F");
    outtreeZ_->Branch("lepPhoMVA",  lepPhoMVA_, "lepPhoMVA[2]/F");
    /*  outtreeZ_->Branch("mcLepPt",    mcLepPt_,   "mcLepPt[2]/F");
      outtreeZ_->Branch("mcLepEta",   mcLepEta_,  "mcLepEta[2]/F");
      outtreeZ_->Branch("mcLepPhi",   mcLepPhi_,  "mcLepPhi[2]/F");*/
    outtreeZ_->Branch("mll",       &mll_,       "mll/F");
    outtreeZ_->Branch("puwei",     &puwei_,     "puwei/F");
    //outtreeZ_->Branch("mcwei",     &mcwei_,     "mcwei/F");
    // outtreeZ_->Branch("genwei",    &genwei_,    "genwei/F");
    outtreeZ_->Branch("processID", &processID_, "processID/I");

    Float_t gPt_, gEta_, gPhi_, gSCEta_, gR9_, gMVA_, gSSMVA_, dRlg_, mllg_, gPFChIso_;
    Int_t   isReal_, isEle_, isSig_, isSB_, mcPhoMom_;
    Float_t alepPt,alepEta,alepPhi, alepSCEta, alepR9, MET, MET_Phi, VBFPt[2], VBFEta[2],VBFPhi[2], VBFEn[2],Zeppen;
    Int_t  cat, totalev_, alepCh, totmatch;
    Int_t isLep, isVBF, isMET;//use to tag the category
    //Float_t mcPhoPt_, mcPhoEta_, mcPhoPhi_;
    Float_t totSF_, sfGSF_[3], sfeID_[3], sfmuTrk_[3], sfmuID_[3], sfmuIso_[3], sfeVeto_[3],sfgID_;//SFs
    ///-*-*-*-*-*-*-*-*-*-*-*-*-*uncertainty-*-*-*-*-*-*-*-*-*-*-*-*-//
    Float_t unGSF_[3], uneID_[3], uneVeto_[3],unmuTrk_[3], unmuIso_[3],unmuID_[3],ungID_;

    TTree *outtreeZg_ = new TTree("tZg", "mini tree for Z->ll + gamma");
    outtreeZg_->Branch("totalev",   &totalev_,       "totalev/I");
    outtreeZg_->Branch("run",       &run_,       "run/I");
    outtreeZg_->Branch("lumis",     &lumis_,     "lumis/I");
    outtreeZg_->Branch("event",     &event_,     "event/L");
    outtreeZg_->Branch("nVtx",      &nVtx_,      "nVtx/I");
    outtreeZg_->Branch("lepCh",      lepCh_,     "lepCh[2]/I");
    outtreeZg_->Branch("lepPt",      lepPt_,     "lepPt[2]/F");
    outtreeZg_->Branch("lepEta",     lepEta_,    "lepEta[2]/F");
    outtreeZg_->Branch("lepPhi",     lepPhi_,    "lepPhi[2]/F");
    outtreeZg_->Branch("lepSCEta",   lepSCEta_,  "lepSCEta[2]/F");
    outtreeZg_->Branch("lepR9",      lepR9_,     "lepR9[2]/F");
    outtreeZg_->Branch("lepPhoMVA",  lepPhoMVA_, "lepPhoMVA[2]/F");
    outtreeZg_->Branch("mcLepPt",    mcLepPt_,   "mcLepPt[2]/F");
    outtreeZg_->Branch("mcLepEta",   mcLepEta_,  "mcLepEta[2]/F");
    outtreeZg_->Branch("mcLepPhi",   mcLepPhi_,  "mcLepPhi[2]/F");
    outtreeZg_->Branch("VBFPt",      VBFPt,      "VBFPt[2]/F");
    outtreeZg_->Branch("VBFPhi",     VBFPhi,     "VBFPhi[2]/F");
    outtreeZg_->Branch("VBFEn",      VBFEn,      "VBFEn[2]/F");
    outtreeZg_->Branch("VBFEta",      VBFEta,      "VBFEta[2]/F");
    //-----------------------------------------------------//
    outtreeZg_->Branch("mll",       &mll_,       "mll/F");
    outtreeZg_->Branch("phoPt",     &gPt_,       "phoPt/F");
    outtreeZg_->Branch("phoEta",    &gEta_,      "phoEta/F");
    outtreeZg_->Branch("phoPhi",    &gPhi_,      "phoPhi/F");
    outtreeZg_->Branch("phoSCEta",  &gSCEta_,    "phoSCEta/F");
    outtreeZg_->Branch("phoR9",     &gR9_,       "phoR9/F");
    outtreeZg_->Branch("phoMVA",    &gMVA_,      "phoMVA/F");
    //outtreeZg_->Branch("phoSSMVA",  &gSSMVA_,    "phoSSMVA/F");
    outtreeZg_->Branch("phoChIso",  &gPFChIso_,  "phoChIso/F");
    outtreeZg_->Branch("dRlg",      &dRlg_,      "dRlg/F");
    outtreeZg_->Branch("mllg",      &mllg_,      "mllg/F");
    outtreeZg_->Branch("puwei",     &puwei_,     "puwei/F");
    outtreeZg_->Branch("puweiUp",   &puweiUp_,   "puweiUp/F");
    outtreeZg_->Branch("puweiDown", &puweiDown_, "puweiDown/F");
    outtreeZg_->Branch("mcwei",     &mcwei_,     "mcwei/F");
    outtreeZg_->Branch("genwei",    &genwei_,    "genwei/F");
    outtreeZg_->Branch("isReal",    &isReal_,    "isReal/I");
    outtreeZg_->Branch("isEle",     &isEle_,     "isEle/I");
    outtreeZg_->Branch("mcPhoMom",  &mcPhoMom_,  "mcPhoMom/I");
    outtreeZg_->Branch("mcPhoPt",   &mcPhoPt_,   "mcPhoPt/F");
    outtreeZg_->Branch("mcPhoEta",  &mcPhoEta_,  "mcPhoEta/F");
    outtreeZg_->Branch("mcPhoPhi",  &mcPhoPhi_,  "mcPhoPhi/F");
    outtreeZg_->Branch("isEBEE",    &isEBEE_,    "isEBEE/I");
    ///------------------SFs----------------------///
    outtreeZg_->Branch("totSF",     &totSF_,     "totSF/F");
    outtreeZg_->Branch("sfGSF",      sfGSF_,     "sfGSF[3]/F");
    outtreeZg_->Branch("sfeID",      sfeID_,     "sfeID[3]/F");
    outtreeZg_->Branch("sfeVeto",    sfeVeto_,   "sfeVeto[3]/F");
    outtreeZg_->Branch("sfgID",     &sfgID_,     "sfgID/F");
    outtreeZg_->Branch("sfmuTrk",    sfmuTrk_,   "sfmuTrk[3]/F");
    outtreeZg_->Branch("sfmuID",     sfmuID_,    "sfmuID[3]/F");
    outtreeZg_->Branch("sfmuIso",    sfmuIso_,   "sfmuIso[3]/F");
    outtreeZg_->Branch("unGSF",      unGSF_,     "unGSF[3]/F");
    outtreeZg_->Branch("uneID",      uneID_,     "uneID[3]/F");
    outtreeZg_->Branch("uneVeto",    uneVeto_,   "uneVeto[3]/F");
    outtreeZg_->Branch("unmuID",     unmuID_,    "unmuID[3]/F");
    outtreeZg_->Branch("unmuIso",    unmuIso_,   "unmuIso[3]/F");
    outtreeZg_->Branch("ungID",     &ungID_,     "ungID/F");
    outtreeZg_->Branch("alepPt",    &alepPt,     "alepPt/F");
    outtreeZg_->Branch("alepPhi",   &alepPhi,    "alepPhi/F");
    outtreeZg_->Branch("alepEta",   &alepEta,    "alepEta/F");
    outtreeZg_->Branch("alepSCEta", &alepSCEta,  "alepSCEta/F");
    outtreeZg_->Branch("alepR9",    &alepR9,     "alepR9/F");
    outtreeZg_->Branch("isLep",     &isLep,      "isLep/I");
    outtreeZg_->Branch("totmatch",  &totmatch,   "totmatch/I");
    outtreeZg_->Branch("alepCh",    &alepCh,     "alepCh/I");
    ///0 is ele, 1 is muon,2 is nothing
    outtreeZg_->Branch("cat",       &cat,        "cat/I");
    ///cat = 0, no additional leptons
    ///cat1~cat4 ->run-I cat
    ///cat = 5, VBF
    ///cat = 6, ee+e
    ///cat = 7, ee+mu
    ///cat = 8, mumu+mu
    ///cat = 9, mumu+e
    ///cat = 10,MET

//Rochester muon correction
    rochcor2016 *mucor = new rochcor2016();


    // pileup reweighting for MC
    PUWeightCalculator puCalc;
    PUWeightCalculator puCalcUp;
    PUWeightCalculator puCalcDown;
    if (data.HasMC())
    {
        puCalc.Init("80X_puwei/36p0_invfb/PU_histo_13TeV_GoldenJSON_63000nb.root");
        puCalcUp.Init("80X_puwei/36p0_invfb/PU_histo_13TeV_GoldenJSON_66150nb.root");
        puCalcDown.Init("80X_puwei/36p0_invfb/PU_histo_13TeV_GoldenJSON_59850nb.root");
    }

    // compute mc weights
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

    }
    else
    {
        mcwei_ = xs * lumi / data.GetEntriesFast();
    }
    cout<<mcwei_<<endl;
    cout<<"----------------------------------------------"<<endl;

    TLorentzVector pho, lep[2], zll, higgs,jet[2], dijet, mcpho, mclep[2], mcll, mcllg, alep;
    Int_t n1sig = 0;
    Int_t n2sig = 0;
    Int_t alepmatch, lepmatch[2], phomatch;
    alepmatch = lepmatch[0] = lepmatch[1] = phomatch = totmatch = 0;
//event loop
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        //default value
        N_totalev = data.GetEntriesFast();
        isLep= -1;
        isMET = -1;
        isVBF = -1;
        cat = -1;

        data.GetEntry(ev);
        if (ev % 5000000 == 0)
        {
            fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
        }
        totalev_ = data.GetEntriesFast();
        run_   = data.GetInt("run");
        lumis_ = data.GetInt("lumis");
        event_ = data.GetLong64("event");
        nVtx_  = data.GetInt("nVtx");

        // histograms for acceptance times efficiency
        Int_t  nMC      = 0;
        Int_t* mcPID    = NULL;
        Int_t* mcMomPID = NULL;
        Int_t* mcGMomPID = NULL;
        float* mcMass   = NULL;
        float* mcPt     = NULL;
        float* mcEta    = NULL;
        float* mcPhi    = NULL;
        UShort_t* mcStatusFlag = NULL;
        Int_t goodMCZg = 0;
        if (data.HasMC())
        {
            nMC          = data.GetInt("nMC");
            mcPID        = data.GetPtrInt("mcPID");
            mcMomPID     = data.GetPtrInt("mcMomPID");
            mcGMomPID    = data.GetPtrInt("mcGMomPID");
            mcMass       = data.GetPtrFloat("mcMass");
            mcPt         = data.GetPtrFloat("mcPt");
            mcEta        = data.GetPtrFloat("mcEta");
            mcPhi        = data.GetPtrFloat("mcPhi");
            mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");
        }


        // trigger
        if(!data.HasMC())
        {
            Long64_t HLTEleMuX = (Long64_t) data.GetLong64("HLTEleMuX");
            ULong64_t   HLTEleMuXIsPrescaled  = (ULong64_t)data.GetLong64("HLTEleMuXIsPrescaled");
            // HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v

            if(channel==0)
            {
                if ((HLTEleMuX >>  5 & 1) == 0) continue;
            }
            if (channel == 1)
            {
                // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v OR HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v
                if ((HLTEleMuX >> 14 & 1) == 0 && (HLTEleMuX >> 15 & 1) == 0) continue;
                //if ((HLTEleMuX >> 20 & 1) == 0) continue;

            }
            N_passtrigger++;
        }

        /*	 if(channel==0){
        ElectronIDPreselRunII(data, eleID);
        if(eleID.size()<2) continue;
        }*/
        //trigger end
//lepton

        vector<int> eleID;
        vector<int> ZeeID;
        Int_t nLep = 0;
        Int_t nmcLep = 0;
        ElectronIDNonTrgMVA(data, 90, ZeeID);

        float* elePt     = data.GetPtrFloat("eleCalibPt");
        float* eleEta    = data.GetPtrFloat("eleEta");
        float* elePhi    = data.GetPtrFloat("elePhi");
        float* eleSCEta  = data.GetPtrFloat("eleSCEta");
        float* eleSCPhi  = data.GetPtrFloat("eleSCPhi");
        float* eleR9     = data.GetPtrFloat("eleR9");
        Int_t* eleCharge = data.GetPtrInt("eleCharge");
        float* eleD0 = data.GetPtrFloat("eleD0");
        float* eleDz = data.GetPtrFloat("eleDz");
        UShort_t* eleIDbit = (UShort_t*) data.GetPtrShort("eleIDbit");

        vector<int> muID;
        vector<int>Zmm;
        vector<float> mucorrPt;

        Int_t  nMu         = data.GetInt("nMu");
        float* muPt        = data.GetPtrFloat("muPt");
        float* muEta       = data.GetPtrFloat("muEta");
        float* muPhi       = data.GetPtrFloat("muPhi");
        Int_t* muCharge    = data.GetPtrInt("muCharge");
        Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");

        // do Rochester muon correction
        for (Int_t i = 0; i < nMu ; i++)
        {
            TLorentzVector *mucorr = new TLorentzVector();
            mucorr->SetPtEtaPhiM(muPt[i], muEta[i], muPhi[i], 105.7*0.001);
            float qter = 1.0;
            if (data.HasMC()) mucor->momcor_mc(*mucorr, muCharge[i], muTrkLayers[i], qter);
            else mucor->momcor_data(*mucorr, muCharge[i], 0, qter);
            mucorrPt.push_back(mucorr->Pt());
        }
        TightMuons2015(data, muID, Zmm, mucorrPt, channel);

        if (channel == 0)//electron loop
        {
            /*	    if(data.HasMC()){
              ElectronIDPreselRunII(data, eleID);
              }*/

            if (ZeeID.size() < 2) continue;
            if (elePt[ZeeID[0]] < 25.) continue;
            if (elePt[ZeeID[1]] < 15.) continue;

            //mc particle selection
            for (Int_t j=0; j<nMC; ++j)
            {
                if(nmcLep ==2) break;
                if(mcPt[j]==0) continue;
                if (fabs(mcPID[j]) != 11) continue;
                if (fabs(mcGMomPID[j]) != 25) continue;
                mclep[nmcLep].SetPtEtaPhiM(mcPt[j],mcEta[j],mcPhi[j],mcMass[j]);
            }

            for (Int_t j=0; j< 2; ++j)
            {
                lepSCEta_[j] = eleSCEta[ZeeID[j]];
                lepR9_[j]    = eleR9[ZeeID[j]];
                lepCh_[j]    = eleCharge[ZeeID[j]];
                lep[j].SetPtEtaPhiM(elePt[ZeeID[j]], eleEta[ZeeID[j]], elePhi[ZeeID[j]], 0.511*0.001);
                lepEta_[j] = eleEta[ZeeID[j]];
                lepPt_[j] = elePt[ZeeID[j]];
                lepPhi_[j] = elePhi[ZeeID[j]];
                nLep++;
                if(mclep[j].DeltaR(lep[j])<0.1) lepmatch[j] = 1;
            }
            N_passele++;
        }


        else if (channel == 1) //muon loop
        {

            if (Zmm.size() < 2) continue;
            if (mucorrPt[Zmm[0]] < 20.) continue;
            if (mucorrPt[Zmm[1]] < 10.) continue;

            for (Int_t j=0; j<nMC; ++j)
            {
                if(nmcLep ==2) break;
                if(mcPt[j]==0) continue;
                if (fabs(mcPID[j]) != 13) continue;
                if (fabs(mcGMomPID[j]) != 25) continue;
                mclep[nmcLep].SetPtEtaPhiM(mcPt[j],mcEta[j],mcPhi[j],mcMass[j]);
            }
            for (Int_t i=0; i< 2; ++i)
            {
                lepCh_[i] = muCharge[Zmm[i]];
                lepPt_[i] = mucorrPt[Zmm[i]];
                lepEta_[i] = muEta[Zmm[i]];
                lepPhi_[i] = muPhi[Zmm[i]];
                lep[i].SetPtEtaPhiM(mucorrPt[Zmm[i]], muEta[Zmm[i]], muPhi[Zmm[i]], 105.7*0.001);
                nLep++;

                if(mclep[i].DeltaR(lep[i])<0.1) lepmatch[i] = 1;
                //mcLepPt_[i]  = -99.;
                //mcLepEta_[i] = -99.;
                //mcLepPhi_[i] = -99.;
            }
            N_passmu++;
        }

        if (nLep < 2) continue;
        zll   = lep[0] + lep[1];
        //        mcll  = mclep[0] + mclep[1];
        //        mcmll_ = mcll.M();

        if (zll.M() < 50) continue;
        N_mll++;

        //electron photon veto
        Int_t  nPho     = data.GetInt("nPho");
        //float* phoEt    = data.GetPtrFloat("phoEt");
        float* phoEt      = data.GetPtrFloat("phoCalibEt");
        float* phoEta     = data.GetPtrFloat("phoEta");
        float* phoPhi     = data.GetPtrFloat("phoPhi");
        float* phoSCEta   = data.GetPtrFloat("phoSCEta");
        float* phoSCPhi   = data.GetPtrFloat("phoSCPhi");
        float* phoR9      = data.GetPtrFloat("phoR9");
        float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
        float* phoPFChIso = data.GetPtrFloat("phoPFChIso");

        mll_ = zll.M();
        outtreeZ_->Fill();

        //Z selection end
        //photon selection
        vector<int> phoID;
        //PhotonPreselections(data, phoID);
        PhotonIDMVA2016(data, phoID);
        N_passpho++;
        if (phoID.size() == 0) continue;
        int phoIndex = -1;
        Int_t nSelPho  = 0;
        isSig_ = 0;
        isSB_  = 0;
        bool selpho = false;

        for (size_t j=0; j<phoID.size(); ++j)
        {
            if (phoEt[phoID[j]] < 15.) continue;
            pho.SetPtEtaPhiM(phoEt[phoID[j]], phoEta[phoID[j]], phoPhi[phoID[j]], 0.);

            if (pho.DeltaR(lep[0]) < 0.4 || pho.DeltaR(lep[1]) < 0.4) continue;

            higgs = pho + zll;
            if (higgs.M() + zll.M() < 185.) continue;
            if (higgs.M() > 180.|| higgs.M()<100.) continue;
            if (pho.Pt()/higgs.M() < 15./110.) continue;

            phoIndex =  phoID[j];
            //double counting photon removal
            Int_t isPromptPhoton = 0;
            if (data.HasMC() && photonRemoval == 1)
            {
                for (Int_t i=0; i<nMC; ++i)
                {
                    if (mcPID[i] != 22) continue;
                    if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
                    mcpho.SetPtEtaPhiM(mcPt[i], mcEta[i], mcPhi[i], 0.);
                    if (mcpho.DeltaR(pho) < 0.1) isPromptPhoton = 1;
                }
            }

            if (isPromptPhoton == 1) continue;

            for (Int_t i=0; i<nMC; ++i)
            {
                if (mcPID[i] != 22) continue;
                if (((mcStatusFlag[i] >> 0) & 1) == 0 && ((mcStatusFlag[i] >> 1) & 1) == 0) continue;
                mcpho.SetPtEtaPhiM(mcPt[i], mcEta[i], mcPhi[i], 0.);
                if (mcpho.DeltaR(pho) < 0.1) phomatch = 1;
            }


            selpho = true;
            if(selpho==true) break;
        }


        if (phoIndex == -1) continue;


        /*

        pho.SetPtEtaPhiM(phoEt[phoIndex], phoEta[phoIndex], phoPhi[phoIndex], 0.);
        higgs = pho + zll;
           if (higgs.M() + zll.M() < 185.) continue;
        //        N_mllgmll++;
            if (higgs.M() > 180.|| higgs.M()<100.) continue;
            N_passH++;
            if (pho.Pt()/higgs.M() < 15./110.) continue;*/
        N_passHpt++;

        //photon selection end


        gPt_      = pho.Pt();
        gEta_     = pho.Eta();
        gPhi_     = pho.Phi();
        gSCEta_   = phoSCEta[phoIndex];
        gR9_      = phoR9[phoIndex];
        gMVA_     = phoIDMVA[phoIndex];
        //  gSSMVA_   = PhotonSSMVA(data, phoIndex);
        gPFChIso_ = phoPFChIso[phoIndex];
        dRlg_     = TMath::Min(pho.DeltaR(lep[0]), pho.DeltaR(lep[1]));
        mllg_     = higgs.M();

        isEBEE_ = -1;
        if (fabs(gSCEta_) < 1.4442) isEBEE_ = 0;
        else if (fabs(gSCEta_) > 1.4442 && fabs(gSCEta_) < 2.5) isEBEE_ = 1;



        ///lepton tagged category(cat6~9)

        AddEleSelections(data,90, eleID, lep[0].Pt(),lep[1].Pt(),channel);


        Int_t nalep = 0;
        Int_t  match = 0;
        TLorentzVector mcalep;

        if(channel==0)
        {
            //class ee+e
            if(eleID.size()>0)
            {

                for(unsigned int i = 0; i < eleID.size(); i++)
                {
                    if(nalep==1) break;
                    alepPt = elePt[eleID[i]];
                    alepEta = eleEta[eleID[i]];
                    alepPhi = elePhi[eleID[i]];
                    alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 0.511*0.001);
                    if(alep.DeltaR(pho)<0.4||alep.DeltaR(lep[0])<0.4||alep.DeltaR(lep[1])<0.4) continue;
                    alepCh = eleCharge[eleID[i]];
                    isLep = 1;
                    cat = 6;
                    nalep++;
                }

                if(isLep==1)
                {
                    match = 0;
                    for(Int_t k = 0 ; k <nMC; k++)
                    {
                        if(match == 1) break;
                        if (fabs(mcPID[k])!=11) continue;
                        mcalep.SetPtEtaPhiM(mcPt[k],mcEta[k],mcPhi[k],mcMass[k]);
                        if(mcalep.DeltaR(alep)<0.1)
                        {
                            match++;
                            alepmatch = 1;
                        }
                    }
                }

            }

            //class ee+mu
            else if(muID.size()>0)
            {
                nalep = 0;//reset counter
                for(unsigned int i = 0; i < muID.size(); i++)
                {
                    if(nalep==1) break;

                    alepPt = mucorrPt[muID[i]];
                    alepEta = muEta[muID[i]];
                    alepPhi = muPhi[muID[i]];
                    alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 105.7*0.001);
                    if(alep.DeltaR(pho)<0.4||alep.DeltaR(lep[0])<0.4||alep.DeltaR(lep[1])<0.4) continue;
                    alepCh = muCharge[muID[i]];
                    isLep = 1;
                    cat = 7;
                    nalep++;
                }
                if(isLep==1)
                {
                    match = 0;
                    for(Int_t k = 0 ; k <nMC; k++)
                    {
                        if(match == 1) break;
                        if (fabs(mcPID[k])!=13) continue;
                        mcalep.SetPtEtaPhiM(mcPt[k],mcEta[k],mcPhi[k],mcMass[k]);
                        if(mcalep.DeltaR(alep)<0.1)
                        {
                            match++;
                            alepmatch = 1;
                        }

                    }
                }
            }
        }

        if(channel==1)
        {
            if(muID.size()>0)
            {
                nalep = 0;
                for(unsigned int i = 2; i < muID.size(); i++)
                {
                    if(nalep==1) break;
                    alepPt = mucorrPt[muID[i]];
                    alepEta = muEta[muID[i]];
                    alepPhi = muPhi[muID[i]];
                    alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 105.7*0.001);
                    if(alep.DeltaR(pho)<0.4||alep.DeltaR(lep[0])<0.4||alep.DeltaR(lep[1])<0.4) continue;
                    alepCh = muCharge[muID[i]];
                    isLep = 1;
                    cat = 8;

                    nalep++;
                }
                if(isLep==1)
                {
                    match = 0;
                    for(Int_t k = 0 ; k <nMC; k++)
                    {
                        if(match == 1) break;
                        if (fabs(mcPID[k])!=13) continue;
                        mcalep.SetPtEtaPhiM(mcPt[k],mcEta[k],mcPhi[k],mcMass[k]);
                        if(mcalep.DeltaR(alep)<0.1)
                        {
                            match++;
                            alepmatch = 1;
                        }
                    }
                }
            }
            else if(eleID.size()>0)
            {
                nalep = 0;
                for(unsigned int i = 0; i < eleID.size(); i++)
                {
                    if(nalep==1) break;
                    alepPt = elePt[eleID[i]];
                    alepEta = eleEta[eleID[i]];
                    alepPhi = elePhi[eleID[i]];
                    alepR9 = eleR9[eleID[i]];
                    alepSCEta = eleSCEta[eleID[i]];
                    alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 0.511*0.001);
                    if(alep.DeltaR(pho)<0.4||alep.DeltaR(lep[0])<0.4||alep.DeltaR(lep[1])<0.4) continue;
                    alepCh = eleCharge[eleID[0]];
                    isLep = 1;
                    cat = 9;
                    nalep++;
                }

                if(isLep==1)
                {
                    match = 0;
                    for(Int_t k = 0 ; k <nMC; k++)
                    {
                        if(match == 1) break;
                        if (fabs(mcPID[k])!=11) continue;
                        mcalep.SetPtEtaPhiM(mcPt[k],mcEta[k],mcPhi[k],mcMass[k]);
                        if(mcalep.DeltaR(alep)<0.1)
                        {
                            match++;
                            alepmatch = 1;
                        }
                    }
                }
            }
        }

        //deltaR cut
        /*
            if(alep.DeltaR(pho)<=0.4||alep.DeltaR(lep[0])<=0.4||alep.DeltaR(lep[1])<=0.4)
            {
                isLep = -1;
                cat = -1;
            }*/

        ///pairing three lepton ---remove before Moriond, but KEEP it!!!!
        /*        if(cat==6||cat==8)
            {
                if(lepCh_[0]*lepCh_[1]>0) //if the original pair is not correct
                {

                    zll = alep + lep[0];
                    higgs = alep+lep[0]+pho;

                    //test the requirement of other cuts
                    if(higgs.M()<=180&&higgs.M()>=100&&zll.M()>=50&&(higgs.M()+zll.M()>=185)&&(pho.Pt()/higgs.M() >= 15./110.))
                    {
                        //update lep information
                        if(channel==0)
                        {
                            lepR9_[1] = eleR9[eleID[0]];
                        }
                        float tmpalepPt, tmpalepEta, tmpalepPhi;
                        int tmpalepCh;//temperary store
                        tmpalepPt  = alepPt;
                        tmpalepEta = alepEta;
                        tmpalepPhi = alepPhi;
                        tmpalepCh = alepCh;
                        alepPt = lepPt_[1];
                        alepEta = lepEta_[1];
                        alepPhi = lepPhi_[1];
                        alepCh = lepCh_[1];
                        lepPt_[1] = tmpalepPt;
                        lepEta_[1] = tmpalepEta;
                        lepPhi_[1] = tmpalepPhi;
                        lepCh_[1] = tmpalepCh;
                        mll_ = zll.M();
                        mllg_ = higgs.M();
                    }
                    else
                    {
                        cat = -1;
                        isLep = -1;
                    }
                }
            }
        */

        if(cat==6) N_cat6++;
        if(cat==7) N_cat7++;
        if(cat==8) N_cat8++;
        if(cat==9) N_cat9++;

        ///jet selection , VBF tagged
        if(isLep!=1)
        {

            vector<int>jetID;
            jetID.clear();
            float zeppen;//Zeppenfeld variables : |Eta_llg-(Eta_j1+Eta_j2)/2|
            float jetEn[2];

            Int_t nJet = data.GetInt("nJet");
            float *jetPt = data.GetPtrFloat("jetPt");
            float *jetEta = data.GetPtrFloat("jetEta");
            float *tmpjetEn = data.GetPtrFloat("jetEn");
            //float jetEn;
            float *jetPhi = data.GetPtrFloat("jetPhi");

            Float_t *NHF  = data.GetPtrFloat("jetNHF");
            Float_t *NEMF = data.GetPtrFloat("jetNEF");
            Int_t   *NNP  = data.GetPtrInt("jetNNP");
            Float_t *CHF  = data.GetPtrFloat("jetCHF");
            Int_t   *CHM  = data.GetPtrInt("jetNCH");
            Float_t *CEMF = data.GetPtrFloat("jetCEF");

            bool looseJetID = false;
            Int_t nj =  0;
            TLorentzVector tmpjet;


            for(Int_t i = 0; i < nJet ; i++)
            {
                if(jetPt[i] < 30.) continue;
                if(fabs(jetEta[i])>4.7) continue;

                Int_t NumConst= CHM[i]+NNP[i];
                if (fabs(jetEta[i]) <= 2.7)
                {
                    looseJetID = (NHF[i]<0.99 && NEMF[i]<0.99 && NumConst>1)
                                 && ((fabs(jetEta[i])<=2.4 && CHF[i]>0 && CHM[i]>0 && CEMF[i]<0.99) || fabs(jetEta[i])>2.4);
                }
                else if (fabs(jetEta[i]) <= 3.0)
                {
                    looseJetID = (NEMF[i]<0.90 && NNP[i]>2);
                }
                else
                {
                    looseJetID = (NEMF[i]<0.90 && NNP[i]>10);
                }

                if(looseJetID == false)continue;
                tmpjet.SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
                if(fabs(tmpjet.DeltaR(pho)) < 0.5||fabs(tmpjet.DeltaR(lep[0])) < 0.5 || fabs(tmpjet.DeltaR(lep[1])) < 0.5) continue;

                //old jet selections
                jetID.push_back(i);
            }

            int   ljet =0;
            int tjet = 0;
            for(unsigned int i = 0; i<jetID.size(); i++)
            {
                jet[0].SetPtEtaPhiE(jetPt[jetID[i]],jetEta[jetID[i]],jetPhi[jetID[i]],tmpjetEn[jetID[i]]);
                ljet = jetID[i];
                for(unsigned int j = i+1; j < jetID.size(); j++)
                {

                    jet[1].SetPtEtaPhiE(jetPt[jetID[j]],jetEta[jetID[j]],jetPhi[jetID[j]],tmpjetEn[jetID[j]]);

                    dijet = jet[0]+jet[1];
                    zeppen = higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
                    if(dijet.M()<500)continue;
                    if(fabs(jet[1].Eta()-jet[0].Eta()) < 3.5) continue;
		    if(fabs(dijet.DeltaPhi(higgs)) < 2.4) continue;
                    if(fabs(zeppen) > 2.5) continue;
                    isVBF = 1;
                    tjet = jetID[j];
                    if(isVBF ==1)break;
                }
                if(isVBF ==1)break;
            }
            /*            dijet = jet[0] + jet[1];
            zeppen = higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
            if(event_==159456)		cout<<lep[0].Pt()<<" "<<lep[1].Pt()<<" "<<jet[0].Pt()<<" "<<jet[1].Pt()<<" "<<jet[1].Eta()-jet[0].Eta()<<" "<<zeppen<<" "<<dijet.M()<<" "<<dijet.DeltaPhi(higgs)<<endl;
            if(nj>=2){
                if(dijet.M()>=500.)
                {
                    if(fabs(jet[1].Eta()-jet[0].Eta())>=3.5)
                    {
                        if(fabs(dijet.DeltaPhi(higgs)) >= 2.4)
                        {

                            if(fabs(zeppen)<=2.5)
                            {
                                isVBF = 1;
                            }
                        }
                    }
            }
            }*/
            //fill the branch of VBF tagged
            if(isVBF == 1)
            {
                for(Int_t n = 0; n < 2; n++)
                {
                    VBFPt[n] = jet[n].Pt();
                    VBFEta[n] = jet[n].Eta();
                    VBFPhi[n] = jet[n].Phi();
                    VBFEn[n] = jet[n].E();
                }
                cat =5 ;
                N_cat5++;
            }
            //end fill branch
        }

//end of VBF tagged


//Run-I category
        if(isVBF!=1&&isLep!=1)
        {

//electron channel
            if(channel==0)
            {
                if(fabs(gSCEta_) > 0 && fabs(gSCEta_) <= 1.4442)
                {
                    if(fabs(lepSCEta_[0]) > 0 &&fabs(lepSCEta_[1]) > 0 &&fabs(lepSCEta_[0]) <= 1.4442 & fabs(lepSCEta_[1]) <= 1.4442)
                    {
                        if(gR9_ > 0.94)
                        {
                            cat = 1;
                            N_cat1++;
                        }
                        else if (gR9_ <= 0.94)
                        {
                            cat = 2;
                            N_cat2++;
                        }
                    }//electron in EB
                    else if ((fabs(lepSCEta_[0]) > 1.4442 &&fabs(lepSCEta_[0] <= 2.5))||(fabs(lepSCEta_[1]) > 1.4442 && fabs(lepSCEta_[1]) <= 2.5))
                    {
                        cat = 3;
                        N_cat3++;
                    }//electron in EE
                }//gSCEta in EB
                else if(fabs(gSCEta_) <= 2.5&&fabs(gSCEta_) > 1.566)
                {
                    if(fabs(lepSCEta_[0]) > 0 && fabs(lepSCEta_[1]) > 0 &&fabs(lepSCEta_[0]) <= 2.5 && fabs(lepSCEta_[1]) <= 2.5)
                    {
                        cat = 4;
                        N_cat4++;
                    }//lepton in EE+EB
                }//gSCEta in EE
            }
//electron channel end
//muon channel
            if(channel==1)
            {
                if(fabs(gSCEta_) > 0 && fabs(gSCEta_) <= 1.4442)
                {
                    if(fabs(lepEta_[0]) > 0 &&fabs(lepEta_[1]) > 0 &&fabs(lepEta_[0]) <= 2.1 & fabs(lepEta_[1]) <= 2.1)
                    {
                        if(fabs(lepEta_[0]) <= 0.9 || fabs(lepEta_[1]) <=  0.9)
                        {
                            if(gR9_ > 0.94)
                            {
                                cat = 1;
                                N_cat1++;
                            }

                            else if (gR9_ <= 0.94)
                            {
                                cat = 2;
                                N_cat2++;
                            }
                        }//one muon <0.9
                    }//both muon <2.1

                    if ((fabs(lepEta_[0]) > 0.9 &&fabs(lepEta_[1]) > 0.9)||
                            ((fabs(lepEta_[0]) > 2.1 &&fabs(lepEta_[0]) <= 2.4)||(fabs(lepEta_[1]) > 2.1 &&fabs(lepEta_[1]) <= 2.4)))
                    {
                        cat = 3;
                        N_cat3++;
                    }//both muon >0.9 or one muon in 2.1~2.4*/
                }//gSCEta in EB
                else if(fabs(gSCEta_) <= 2.5&&fabs(gSCEta_) > 1.566)
                {
                    if(fabs(lepEta_[0]) > 0 && fabs(lepEta_[1]) > 0 && fabs(lepEta_[0]) <= 2.4 &&fabs(lepEta_[1]) <=  2.4)
                    {
                        cat = 4;
                        N_cat4++;
                    }
                }// photon in EE
            }//muon channel end

        }	//end for category

        //clear the wrong information
        if(isLep!=1)
        {
            alepPt = 0;
            alepEta = 0;
            alepCh = 0;
            alepPhi = 0;
            alepmatch = 0;
            if(cat==7||cat==8) alepR9 = alepSCEta = -999;
        }

        if(isVBF!=1)
        {
            Zeppen = 0;
            for(Int_t i = 0; i<2; i++)
            {
                VBFPt[i] = 0;
                VBFEn[i] = 0;
                VBFPhi[i] = -999.;
                VBFEta[i] = -999.;
            }
        }
        //end for clear wrong information

        // PU reweighting
        if (data.HasMC())
        {
            float* puTrue = data.GetPtrFloat("puTrue");
            puwei_     = (float) puCalc.GetWeight(run_, puTrue[1]); // in-time PU
            puweiUp_   = (float) puCalcUp.GetWeight(run_, puTrue[1]); // in-time PU
            puweiDown_ = (float) puCalcDown.GetWeight(run_, puTrue[1]); // in-time PU

            float generatorWeight = data.GetFloat("genWeight");
            if (aMCatNLO == 1) genwei_ = (generatorWeight > 0) ? 1. : -1.;
            else               genwei_ = 1.;
        }


        //calculate acc*eff of lepton tag

        if(alepmatch==1&&lepmatch[1]==1&&lepmatch[0]==1&&phomatch==1) totmatch = 1;

        ///---------------------------SFs----------------------------///

        //photon SFs
        Float_t tmpPhoEt = (gPt_ < 20) ? 21 :gPt_ ;
        sfgID_ = hg_ID->GetBinContent(hg_ID->FindBin(gSCEta_, gPt_));
        ungID_ = hg_ID->GetBinError(hg_ID->FindBin(gSCEta_, gPt_));

        if(channel == 0)//ele channel SFs
        {
            for(Int_t j = 0; j < 2 ; j++)
            {
            sfeVeto_[j] = (lepR9_[j] > 1.479) ? 0.9875:0.9938;
            uneVeto_[j] = (lepR9_[j] > 1.479) ? 0.0044:0.0119;

            sfGSF_[j] = he_GSF->GetBinContent(he_GSF->FindBin(lepSCEta_[j], 50));
            Float_t tmpElePt = (lepPt_[j] < 500) ? lepPt_[j] : 499;
            sfeID_[j] = he_ID->GetBinContent(he_ID->FindBin(lepSCEta_[j], tmpElePt));
            unGSF_[j] = he_GSF->GetBinError(he_GSF->FindBin(lepSCEta_[j], 50));
            uneID_[j] = he_ID->GetBinError(he_ID->FindBin(lepSCEta_[j], tmpElePt));
            }
	    if(cat<6) sfGSF_[2] = sfeID_[2] = sfmuID_[2] = sfmuIso_[2] = sfmuTrk_[2] = 1.; //set the SFs for no lepton tag cat
	    else
	      {	   
		sfeVeto_[2] = (alepR9 > 1.479) ? 0.9875:0.9938;
		uneVeto_[2] = (alepR9 > 1.479) ? 0.0044:0.0119;	
		sfGSF_[2] = he_GSF->GetBinContent(he_GSF->FindBin(alepSCEta, 50));
		Float_t tmpElePt = (alepPt < 500) ? alepPt : 499;
		sfeID_[2] = he_ID->GetBinContent(he_ID->FindBin(alepSCEta, tmpElePt));
		unGSF_[2] = he_GSF->GetBinError(he_GSF->FindBin(alepSCEta, 50));
		uneID_[2] = he_ID->GetBinError(he_ID->FindBin(alepSCEta, tmpElePt));
	      }
	    totSF_ = sfGSF_[0]*sfGSF_[1]*sfGSF_[2]*sfeID_[0]*sfeID_[1]*sfeID_[2];
        }




        else //muon channel SFs
        {
	  for(Int_t i = 0 ; i <2 ; i++)
	    {
	      //                sfmuTrk_[i] = gm_Trk->Eval(lepEta_[i]);
                Float_t tmpMuPt = (lepPt_[i] < 200) ? lepPt_[i] : 199;
                if (lepPt_[i] < 20) tmpMuPt = 21;
                sfmuID_[i]  = hm_ID->GetBinContent(hm_ID->FindBin(fabs(lepEta_[i]), tmpMuPt));
                unmuID_[i]  = hm_ID->GetBinError(hm_ID->FindBin(fabs(lepEta_[i]), tmpMuPt));
                sfmuIso_[i] = hm_Iso->GetBinContent(hm_Iso->FindBin(fabs(lepEta_[i]), tmpMuPt));
                unmuIso_[i] = hm_Iso->GetBinError(hm_Iso->FindBin(fabs(lepEta_[i]), tmpMuPt));
	    }
	    if(cat<6) sfGSF_[2] = sfeID_[2] = sfmuID_[2] = sfmuIso_[2] = sfmuTrk_[2] = 1.; //set the SFs for no lepton tag cat
                Float_t tmpMuPt = (alepPt < 200) ? alepPt : 199;
                if (alepPt < 20) tmpMuPt = 21;
                sfmuID_[2]  = hm_ID->GetBinContent(hm_ID->FindBin(fabs(alepEta), tmpMuPt));
                unmuID_[2]  = hm_ID->GetBinError(hm_ID->FindBin(fabs(alepEta), tmpMuPt));
                sfmuIso_[2] = hm_Iso->GetBinContent(hm_Iso->FindBin(fabs(alepEta), tmpMuPt));
                unmuIso_[2] = hm_Iso->GetBinError(hm_Iso->FindBin(fabs(alepEta), tmpMuPt));

            totSF_ = sfmuTrk_[0]*sfmuTrk_[1]*sfmuTrk_[2]*sfmuID_[0]*sfmuID_[1]*sfmuID_[2]*sfmuIso_[0]*sfmuIso_[1]*sfmuIso_[2];
        }


        outtreeZg_->Fill();
        //clear the vectors
        eleID.clear();
        muID.clear();
        phoID.clear();

    } // event loop end

    cout<<"-------------------------------------------------------"<<endl;
    cout<<"Number of selected events : "<<N_passHpt<<endl;
    fprintf(stderr, "Processed all events\n");

    ///counter for eff
    cout << "totalev:" <<N_totalev<<"\n"<<"pass trigger:"<<" "<<N_passtrigger<<"\n"<<"ele:"<<N_passele<<" "<<"mu"<<N_passmu<<" "<<"pho:"
         <<N_passpho<<"\n"<<"mll:"<<N_mll<<"\n"<<"dR(pho,lep):"<<N_dR<<"\n"<<"remove fake ele:"<<N_rmelepho<<"\n"<<
         "mllg+mll:"<<N_mllgmll<<"\n"<<"Hmass cut:"<<N_passH<<"\n"<<"Hmass/phopt:"<<N_passHpt<<endl;

    cout<<"-------------------------------"<<endl;

    cout<<"cat"<<"\n"<<"1 = "<<N_cat1<<endl<<"2 = "<<N_cat2<<endl<<"3 = "<<N_cat3<<endl<<"4 = "<<N_cat4<<endl<<"5 = "<<N_cat5<<endl<<
        "6 = "<<N_cat6<<endl<<"7 = "<<N_cat7<<endl<<"8 = "<<N_cat8<<endl<<"9 ="<<N_cat9<<endl<<"10 ="<<N_cat10<<endl;
    cout<<"in 1 sig:"<<nsig1<<endl;

// flush caches, close the output
    outtreeZ_->Write("", TObject::kOverwrite);
    outtreeZg_->Write("", TObject::kOverwrite);

    delete outtreeZ_;
    delete outtreeZg_;
    delete fo;

}
