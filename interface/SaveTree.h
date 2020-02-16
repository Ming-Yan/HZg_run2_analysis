#include "TMVA/Reader.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TString.h"
//user included
#include "../plugin/puweicalc.h"
#include "GENsel.h"
class AForest
{
  TFile *fo;
  TTree *outtreeZg_;
  TTree *MVAtree;
  TTree *tVBF;
  TTree *tFSR;
  Int_t njets;
  Int_t run_, lumis_, nVtx_;
  Long64_t event_;
  Int_t  cat, totalev_, alepCh, totmatch, lepCh_[2],isEcalDriven[2];
  Int_t nFSR;
  vector<int> photype; vector<float> tphoPt,tphoEta,tphoPhi,dR,mllgmll,ratio, res,MVA;
  Float_t puwei_,puweiUp_, puweiDown_, mcwei_,genwei_,totwei_;
  Float_t genphoPt, genphoEta, genphoPhi, genlepPt[2], genlepEta[2], genlepPhi[2],genmll;
  Float_t lepPt_[2], lepEta_[2], lepPhi_[2], lepSCEta_[2],lepSCPhi_[2], lepR9_[2], lepPhoMVA_[2], mll_,mllerr_;//lepton related variables
  Float_t REFITlepPt_[2], REFITlepPtErr_[2], REFITmll_, REFITmllg_;//Kinematic Refit
  Float_t afsrPt_[2], afsrEta_[2], afsrPhi_[2], afsrdRlg_[2], afsrdRratio_[2],afsrmll_, afsrmllg_; //FSR_atlas version
  Float_t sfsrPt_[2], sfsrEta_[2], sfsrPhi_[2], sfsrdRlg_[2], sfsrdRratio_[2],sfsrmll_, sfsrmllg_; //FSR_SMPZZ version
  Int_t samefsr[2],isafsr[2],issfsr[2];
  Float_t gPt_, gEta_, gPhi_, gSCEta_,  gMVA_, gSSMVA_;//photon related variables
  Float_t maxdRlg_,dRlg_, mllg_,mg_, gdmllg,mllgpt; //three body variables
  Float_t alepPt,alepEta,alepPhi, alepSCEta, alepR9, alepphodR,aleplepdR, // lepton tag variables
    bjetPt, bjetEta, bjetPhi, bjetEn,bjetphodR ,bjetlepdR, bCsv2,//b-tag variables
    dbjetPt[2], dbjetEta[2], dbjetPhi[2], dbjetEn[2],dbjetphodR[2], dbjetlepdR[2],dbCsv2[2],//double b-tag variables
    VBFPt[2], VBFEta[2],VBFPhi[2], VBFEn[2], VBFphodR[2], VBFlepdR[2];// VBF tag variables
  Int_t isLep, isVBF, isboost, isbtag, isdbtag;//use to tag the category--NO STORED IN TREE!!!!
  Float_t totSF_, sfGSF_[3], sfeID_[3],sfetrg_[2], sfmutrg_[2], sfmuTrk_[3], sfmuID_[3], sfmuIso_[3], sfgVeto_,sfgID_;//SFs
  Float_t unGSF_[3], uneID_[3], unetrg_[2],unedz_[2],unmutrg_[2], unmuTrk_[3], unmuID_[3], unmuIso_[3], ungVeto_,ungID_;//uncertainty of SFs
  Float_t  lep1res,lep2res, mllres, phores,costheta,cosTheta,Phi, mllgptdmllg,mllmllg,ZgPTt, gR9_, lepEta1, lepEta2,dEtaZg;//variables for kinematic MVA
  Float_t VBFPt1, VBFPt2, mjj, CZg, dEta_jj,dPhi_jj,dPhi_Zgjj,dR_phojet,Zeppen,absdEta_jj,absdPhi_jj,absdPhi_Zgjj,absZeppen, theta;
  Float_t HZgMVA, HZgVBF;

 public:
  AForest(){};
  AForest(TString outpath)
    {
      fo = TFile::Open(outpath.Data(),"RECREATE");
      if (!fo || fo->IsZombie())  FATAL("TFile::Open() failed");
      fo->cd();
    };
  ~AForest()
    {
      outtreeZg_->Write("",TObject::kOverwrite);
      tVBF->Write("",TObject::kOverwrite);
      MVAtree->Write("",TObject::kOverwrite);
      //tFSR->Write("",TObject::kOverwrite);
      cout<<"===>finished trees<===="<<endl;
      delete outtreeZg_;
      delete MVAtree;
      delete tVBF;
      //delete tFSR;
      delete fo;
    };
  void setAnaTree();
  void setkinMVAtree();
  void setVBFMVAtree();
  void refresh();
  void fillAna(TreeReader &data,Int_t channel, Int_t aMCatNLO, HZgVariables &HZgVar, vector<float> &phoR9, vector<float> &jetPt, vector<float> &jetEn, bool isSig, bool isFSR, bool isrefit, bool isdebug);
  void fillkinMVA(TreeReader &data, Int_t channel, HZgVariables &HZgVar, vector<float> &phoR9);
  void fillVBFMVA(TreeReader &data, Int_t channel,HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &jetEn);
};

void AForest::refresh()
{
  photype.clear();tphoPt.clear();tphoEta.clear(); tphoPhi.clear(); ratio.clear();dR.clear();mllgmll.clear();res.clear();MVA.clear();
  njets = run_ = lumis_ = nVtx_ = totalev_ = 0; 
  nFSR= event_ = 0;
  puwei_= puweiUp_ = mcwei_ = genwei_ = totwei_ =  totSF_ = 0.;
  genmll = genphoEta = genphoPhi = genphoPt = lepEta1 = lepEta2 = VBFPt1 = VBFPt2 = 0.;
  afsrmll_ = sfsrmll_ = afsrmllg_ = sfsrmllg_ = mll_ = mllerr_ = gPt_ = gEta_ = gPhi_ = gSCEta_ = gR9_ = gMVA_ = gSSMVA_ = dRlg_ = mllg_ =mg_ = alepPt =alepEta =alepPhi = alepSCEta   = alepR9 = aleplepdR = alepphodR = bjetphodR = bjetlepdR = 0.;
  REFITmll_ = REFITmllg_ = bjetPt = bjetEta = bjetPhi = bjetEn =bjetphodR = bCsv2 = sfgVeto_ = sfgID_  = 1.;//b-tag variables
  ungVeto_ = ungID_ = theta = 0 ; 
  //double b-tag variables
  isLep = isVBF = isboost = isbtag = isdbtag = -99;
  mllres = lep1res = lep2res = mllgpt = cosTheta = gdmllg = mllgptdmllg = mllmllg = ZgPTt = dEtaZg = 0.;//kin mva
  phores = Zeppen = Phi = costheta = mjj = CZg = dEta_jj = dPhi_jj = dPhi_Zgjj = dR_phojet = absZeppen = absdEta_jj = absdPhi_jj = absdPhi_Zgjj = 0.;//vbf mva
  HZgMVA  = HZgVBF = -99.;

  alepCh = cat = isLep = isVBF = isboost = isbtag = isdbtag = totmatch = -99;
  for(int i = 0; i < 3; i++)
    {
      if(i<2)
	{
	  afsrdRlg_[i] = afsrdRratio_[i] = sfsrdRlg_[i] = sfsrdRratio_[i] = afsrPt_[i] = afsrEta_[i] = afsrPhi_[i] = sfsrPt_[i] = sfsrEta_[i] = sfsrPhi_[i] = REFITlepPt_[i] = REFITlepPtErr_[i] = genlepPhi[i] = genlepEta[i] = genlepPt[i] = lepPt_[i] = lepEta_[i] = lepPhi_[i] = lepSCEta_[i] =lepSCPhi_[i] = lepR9_[i] = lepPhoMVA_[i] = dbjetPt[i] = dbjetEta[i] = dbjetPhi[i] = dbjetEn[i] = dbjetphodR[i] = dbjetlepdR[i] = dbCsv2[i] = VBFPt[i] = VBFEta[i] = VBFphodR[i] =  VBFlepdR[i] = VBFPhi[i] = VBFEn[i] = unetrg_[i] =unedz_[i] =unmutrg_[i] =  0.;
	  sfetrg_[i] = sfmutrg_[i] = 1.;
	  lepCh_[i] = isEcalDriven[i] = samefsr[i] = isafsr[i] = issfsr[i] = -99;
	}
      sfGSF_[i] = sfeID_[i] = sfmuTrk_[i] = sfmuID_[i] = sfmuIso_[i] = 1. ;
      unGSF_[i] = uneID_[i] = unmuTrk_[i] = unmuID_[i] = unmuIso_[i] = 0.;
    }
}
void AForest::setAnaTree()
{
  outtreeZg_ = new TTree("tZg","mini tree for Z->ll + gamma");
  outtreeZg_->Branch("totalev",   &totalev_,       "totalev/I");
  outtreeZg_->Branch("run",       &run_,       "run/I");
  outtreeZg_->Branch("lumis",     &lumis_,     "lumis/I");
  outtreeZg_->Branch("event",     &event_,     "event/L");
  outtreeZg_->Branch("nVtx",      &nVtx_,      "nVtx/I");
  outtreeZg_->Branch("puwei",     &puwei_,     "puwei/F");
  outtreeZg_->Branch("puweiUp",   &puweiUp_,   "puweiUp/F");
  outtreeZg_->Branch("puweiDown", &puweiDown_, "puweiDown/F");
  outtreeZg_->Branch("mcwei",     &mcwei_,     "mcwei/F");
  outtreeZg_->Branch("genwei",    &genwei_,    "genwei/F");
  outtreeZg_->Branch("njets",     &njets,      "njets/I");
  //gen objects
  outtreeZg_->Branch("genmll",    &genmll,     "genmll/F");
  outtreeZg_->Branch("genphoPt",  &genphoPt,   "genphoPt/F");
  outtreeZg_->Branch("genphoEta", &genphoEta,  "genphoEta/F");
  outtreeZg_->Branch("genphoPhi", &genphoPhi,  "genphoPhi/F");
  outtreeZg_->Branch("genlepPt",  genlepPt,    "genlepPt[2]/F");
  outtreeZg_->Branch("genlepPhi", genlepPhi,   "genlepPhi[2]/F");
  outtreeZg_->Branch("genlepEta", genlepEta,   "genlepEta[2]/F");
  //objects for Zgamma
  outtreeZg_->Branch("lepCh",      lepCh_,     "lepCh[2]/I");
  outtreeZg_->Branch("lepPt",      lepPt_,     "lepPt[2]/F");
  outtreeZg_->Branch("lepEta",     lepEta_,    "lepEta[2]/F");
  outtreeZg_->Branch("lepPhi",     lepPhi_,    "lepPhi[2]/F");
  outtreeZg_->Branch("lepSCEta",   lepSCEta_,  "lepSCEta[2]/F");
  outtreeZg_->Branch("lepR9",      lepR9_,     "lepR9[2]/F");
  outtreeZg_->Branch("lepPhoMVA",  lepPhoMVA_, "lepPhoMVA[2]/F");
  outtreeZg_->Branch("dRlg",      &dRlg_,      "dRlg/F");
  outtreeZg_->Branch("phoPt",     &gPt_,       "phoPt/F");
  outtreeZg_->Branch("phoEta",    &gEta_,      "phoEta/F");
  outtreeZg_->Branch("phoPhi",    &gPhi_,      "phoPhi/F");
  outtreeZg_->Branch("phoSCEta",  &gSCEta_,    "phoSCEta/F");
  outtreeZg_->Branch("phoR9",     &gR9_,       "phoR9/F");
  outtreeZg_->Branch("mllg",      &mllg_,      "mllg/F");
  outtreeZg_->Branch("mll",       &mll_,       "mll/F");
  outtreeZg_->Branch("mllerr",    &mllerr_,    "mllerr/F");
  //REFIT vars
  outtreeZg_->Branch("REFITlepPt",    REFITlepPt_,   "REFITlepPt_/F");
  outtreeZg_->Branch("REFITlepPtErr", REFITlepPtErr_,"REFITlepPtErr/F");
  outtreeZg_->Branch("REFITmll",	 &REFITmll_,     "REFITmll/F");
  outtreeZg_->Branch("REFITmllg",	 &REFITmllg_,    "REFITmllg/F");
  //FSR vars
  outtreeZg_->Branch("afsrPt",		 afsrPt_, 		  "afsrPt[2]/F");
  outtreeZg_->Branch("sfsrPt",		 sfsrPt_, 		  "sfsrPt[2]/F");
  outtreeZg_->Branch("afsrEta",		 afsrEta_, 		  "afsrEta[2]/F");
  outtreeZg_->Branch("sfsrEta",		 sfsrEta_, 		  "sfsrEta[2]/F");
  outtreeZg_->Branch("afsrPhi",		 afsrPhi_, 		  "afsrPhi[2]/F");
  outtreeZg_->Branch("sfsrPhi",		 sfsrPhi_, 		  "sfsrPhi[2]/F");
  outtreeZg_->Branch("afsrdRlg",	 afsrdRlg_,		  "afsrdRlg[2]/F");
  outtreeZg_->Branch("sfsrdRlg",	 sfsrdRlg_,		  "sfsrdRlg[2]/F");
  outtreeZg_->Branch("afsrdRratio",	 afsrdRratio_,	  "afsrdRratio[2]/F");
  outtreeZg_->Branch("sfsrdRratio",	 sfsrdRratio_,		  "sfsrdRratio[2]/F");
  outtreeZg_->Branch("afsrmll",	 	&afsrmll_,		  "afsrmll/F");
  outtreeZg_->Branch("sfsrmll",	 	&sfsrmll_,		  "sfsrmll/F");
  outtreeZg_->Branch("afsrmllg",	&afsrmllg_,		  "afsrmllg/F");
  outtreeZg_->Branch("sfsrmllg",	&sfsrmllg_,		  "sfsrmllg/F");
  outtreeZg_->Branch("isafsr",		 isafsr,		  "isafsr[2]/I");//put type 1 : true photon, 2 : FSR , 3 : Fake
  outtreeZg_->Branch("issfsr",		 issfsr,		  "issfsr[2]/I");
  outtreeZg_->Branch("samefsr",		 samefsr,		  "samefsr[2]/I");

  //-----------------------------------------------------//
  //tag variables
  outtreeZg_->Branch("bjetPt",	  &bjetPt, 	   "bjetPt");
  outtreeZg_->Branch("bjetPhi",	  &bjetPhi,    "bjetPhi");
  outtreeZg_->Branch("bjetEta",	  &bjetEta,    "bjetEta");
  outtreeZg_->Branch("bjetEn",	  &bjetEn,     "bjetEn");
  outtreeZg_->Branch("bjetphodR", &bjetphodR,  "bjetphodR");
  outtreeZg_->Branch("bjetlepdR", &bjetlepdR,  "bjetlepdR");
  outtreeZg_->Branch("bCsv2",	  &bCsv2,      "bCsv2");
  outtreeZg_->Branch("dbjetPt",	  dbjetPt, 	   "dbjetPt[2]/F");
  outtreeZg_->Branch("dbjetPhi",  dbjetPhi,    "dbjetPhi[2]/F");
  outtreeZg_->Branch("dbjetEta",  dbjetEta,    "dbjetEta[2]/F");
  outtreeZg_->Branch("dbjetEn",	  dbjetEn,     "dbjetEn[2]/F");
  outtreeZg_->Branch("dbjetphodR",dbjetphodR,  "dbjetphodR[2]/F");
  outtreeZg_->Branch("dbjetlepdR",dbjetlepdR,  "dbjetlepdR[2]/F");
  outtreeZg_->Branch("dbCsv2",	  dbCsv2,      "dbCsv2[2]/F");
  outtreeZg_->Branch("isdbtag",	  &isdbtag,    "isdbtag/I");
  outtreeZg_->Branch("isbtag",    &isbtag,     "isbtag/I");
  outtreeZg_->Branch("alepPt",    &alepPt,     "alepPt/F");
  outtreeZg_->Branch("alepPhi",   &alepPhi,    "alepPhi/F");
  outtreeZg_->Branch("alepEta",   &alepEta,    "alepEta/F");
  outtreeZg_->Branch("alepSCEta", &alepSCEta,  "alepSCEta/F");
  outtreeZg_->Branch("alepR9",    &alepR9,     "alepR9/F");
  outtreeZg_->Branch("VBFPt",     VBFPt,       "VBFPt[2]/F");
  outtreeZg_->Branch("VBFPhi",    VBFPhi,      "VBFPhi[2]/F");
  outtreeZg_->Branch("VBFEn",     VBFEn,       "VBFEn[2]/F");
  outtreeZg_->Branch("VBFEta",    VBFEta,      "VBFEta[2]/F");
  outtreeZg_->Branch("VBFphodR",  VBFphodR,    "VBFphodR[2]/F");
  outtreeZg_->Branch("VBFlepdR",  VBFlepdR,    "VBFlepdR[2]/F");
  outtreeZg_->Branch("mllgpt",	  &mllgpt,     "mllgpt/F");
  outtreeZg_->Branch("totmatch",  &totmatch,   "totmatch/I");
  outtreeZg_->Branch("alepCh",    &alepCh,     "alepCh/I");
  outtreeZg_->Branch("cat",       &cat,        "cat/I");
  ///cat = 0, no additional leptons
  ///cat1~cat4 ->run-I cat
  ///cat = 5, VBF
  ///cat = 6, ee+e
  ///cat = 7, ee+mu
  ///cat = 8, mumu+mu
  ///cat = 9, mumu+e
  ///cat = 10, will be boosted jet tag
  ///------------------SFs----------------------///
  outtreeZg_->Branch("totSF",     &totSF_,     "totSF/F");
  outtreeZg_->Branch("sfGSF",     sfGSF_,     "sfGSF[3]/F");
  outtreeZg_->Branch("sfetrg",    sfetrg_,    "sfetrg[2]/F");
  outtreeZg_->Branch("sfmutrg",    sfmutrg_,    "sfmutrg[2]/F");
  outtreeZg_->Branch("sfeID",     sfeID_,     "sfeID[3]/F");
  outtreeZg_->Branch("sfgVeto",   &sfgVeto_,   "sfgVeto/F");
  outtreeZg_->Branch("sfgID",     &sfgID_,     "sfgID/F");
  outtreeZg_->Branch("sfmuID",     sfmuID_,    "sfmuID[3]/F");
  outtreeZg_->Branch("unGSF",      unGSF_,     "unGSF[3]/F");
  outtreeZg_->Branch("uneID",      uneID_,     "uneID[3]/F");
  outtreeZg_->Branch("unedz",      unedz_,     "unedz[2]/F");
  outtreeZg_->Branch("unetrg",     unetrg_,    "unetrg[2]/F");
  outtreeZg_->Branch("ungVeto",   &ungVeto_,   "ungVeto/F");
  outtreeZg_->Branch("ungID",     &ungID_,     "ungID/F");
  outtreeZg_->Branch("unmutrg",    unmutrg_,   "unmutrg[2]/F");
  outtreeZg_->Branch("unmuID",     unmuID_,    "unmuID[3]/F");
  outtreeZg_->Branch("HZgMVA",    &HZgMVA,     "HZgMVA/F");
  outtreeZg_->Branch("HZgVBF",    &HZgVBF,     "HZgVBF/F");
  outtreeZg_->Branch("gdmllg",			&gdmllg,	 "gdmllg/F");
  outtreeZg_->Branch("ZgPTt", 			&ZgPTt,		 "ZgPTt/F");  
}
void AForest::setkinMVAtree()
{
  MVAtree = new TTree("tMVA", "tree for MVA variables");
  MVAtree->Branch("mcwei",		&mcwei_,	 "mcwei/F");
  MVAtree->Branch("puwei",		&puwei_,	 "puwei/F");
  MVAtree->Branch("genwei",		&genwei_,	 "genwei/F");
  MVAtree->Branch("totSF",		&totSF_,	 "totSF/F");
  MVAtree->Branch("phoEta",		&gEta_,		 "phoEta/F");
  MVAtree->Branch("phoR9",		&gR9_,		 "phoR9/F");
  MVAtree->Branch("phoMVA",		&gMVA_,		 "phoMVA/F");
  MVAtree->Branch("lepEta1",		&lepEta1,	 "lepEta1/F");
  MVAtree->Branch("lepEta2",	  	&lepEta2,	 "lepEta2/F");
  MVAtree->Branch("cosTheta",		&cosTheta,	 "cosTheta/F");
  MVAtree->Branch("costheta",		&costheta,	 "costheta/F");
  MVAtree->Branch("Phi",		&Phi,		 "Phi/F");
  MVAtree->Branch("mllgptdmllg", 	&mllgptdmllg,    "mllgptdmllg/F");
  MVAtree->Branch("mllmllg", 		&mllmllg,        "mllmllg/F");
  MVAtree->Branch("dRlg",               &dRlg_,          "dRlg/F");
  MVAtree->Branch("maxdRlg",            &maxdRlg_,       "maxdRlg/F");
  MVAtree->Branch("mllg",               &mllg_,          "mllg/F");
  MVAtree->Branch("ZgPTt", 		&ZgPTt,		 "ZgPTt/F");  
  MVAtree->Branch("dEtaZg", 		&dEtaZg,	 "dEtaZg/F");  
  MVAtree->Branch("phores", 		&phores,	 "phores/F"); 
  MVAtree->Branch("lep1res", 		&lep1res,	 "lep1res/F");    
  MVAtree->Branch("lep2res", 		&lep2res,	 "lep2res/F");  
  MVAtree->Branch("mllres", 		&mllres,	 "mllres/F");  
  MVAtree->Branch("HZgMVA", 		&HZgMVA,	 "HZgMVA/F");  
}
void AForest::setVBFMVAtree()
{ 
  tVBF = new TTree("tVBF", "tree for VBF MVA");
  tVBF->Branch("mjj", 			&mjj,			"mjj/F");
  tVBF->Branch("CZg", 			&CZg,			"CZg/F");
  tVBF->Branch("dEta_jj", 		&dEta_jj,		"dEta_jj/F");
  tVBF->Branch("absdEta_jj", 	&absdEta_jj,	"absdEta_jj/F");
  tVBF->Branch("dPhi_Zgjj",     &dPhi_Zgjj,		"dPhi_Zgjj/F");
  tVBF->Branch("absdPhi_Zgjj",  &absdPhi_Zgjj,	"absdPhi_Zgjj/F");
  tVBF->Branch("dR_phojet",	 	&dR_phojet,		"dR_phojet/F");
  tVBF->Branch("dPhi_jj", 		&dPhi_jj,		"dPhi_jj/F");
  tVBF->Branch("absdPhi_jj", 	&absdPhi_jj,	"absdPhi_jj/F");
  tVBF->Branch("ZgPTt", 		&ZgPTt,			"ZgPTt/F");
  tVBF->Branch("VBFPt1", 		&VBFPt1, 		"tVBFPt1/F");
  tVBF->Branch("VBFPt2", 		&VBFPt2, 		"tVBFPt2/F");
  tVBF->Branch("Zeppen",        &Zeppen,        "Zeppen/F");
  tVBF->Branch("absZeppen",     &absZeppen,     "absZeppen/F");
  tVBF->Branch("mcwei",         &mcwei_,        "mcwei/F");
  tVBF->Branch("puwei",		    &puwei_,        "puwei/F");
  tVBF->Branch("genwei",		&genwei_,       "genwei/F");
  tVBF->Branch("totSF",			&totSF_,		"totSF/F");
  tVBF->Branch("mllg",          &mllg_,         "mllg/F");
  tVBF->Branch("phores", 		&phores,		"phores/F");  
  tVBF->Branch("theta",         &theta,         "theta/F");
  tVBF->Branch("HZgVBF",        &HZgVBF,        "HZgVBF/F");
  tVBF->Branch("HZgMVA",        &HZgMVA,        "HZgMVA/F");
}
void AForest::fillAna(TreeReader &data,Int_t channel, Int_t aMCatNLO, HZgVariables &HZgVar, vector<float> &phoR9, vector<float> &jetPt, vector<float> &jetEn, bool isSig, bool isFSR, bool isrefit, bool isdebug=false)
{
 
  refresh();	
  // compute mc weights
  totalev_ = HZgVar.totalev;
  mcwei_   = HZgVar.mcwei;
  puwei_   = HZgVar.puwei;
  puweiUp_   = HZgVar.puweiUp;

  puweiDown_   = HZgVar.puweiDown;
  genwei_   = HZgVar.genwei;
  run_   = data.GetInt("run");
  lumis_ = data.GetInt("lumis");
  event_ = data.GetLong64("event");
  nVtx_  = data.GetInt("nVtx");

  //lepton selection

  float* elePt     = data.GetPtrFloat("eleCalibPt");
  float* eleEta    = data.GetPtrFloat("eleEta");
  float* elePhi    = data.GetPtrFloat("elePhi");
  float* eleSCEta  = data.GetPtrFloat("eleSCEta");//use for categorization
  float* eleSCPhi  = data.GetPtrFloat("eleSCPhi");//use for categorization
  float* eleR9     = data.GetPtrFloat("eleR9");//use for categorization
  Int_t* eleCharge = data.GetPtrInt("eleCharge");
  Int_t *eleEcalDrivenSeed = data.GetPtrInt("eleEcalDrivenSeed");
  Int_t  nMu         = data.GetInt("nMu");
  float* muEta       = data.GetPtrFloat("muEta");
  float* muPhi       = data.GetPtrFloat("muPhi");
  Int_t* muCharge 	 = data.GetPtrInt("muCharge");
  TLorentzVector lep[2];
  for(int i = 0 ; i < 2; i++)
    {
      lepPt_[i] = HZgVar.lepPt[i]; 
      lepEta_[i] = (channel==0)? eleEta[HZgVar.lepID_[i]]:muEta[HZgVar.lepID_[i]]; 
      lepPhi_[i] = (channel==0)? elePhi[HZgVar.lepID_[i]]:muPhi[HZgVar.lepID_[i]]; 
      lepR9_[i] = (channel==0)? eleR9[HZgVar.lepID_[i]]:-1;
      lepSCEta_[i] = (channel==0)? eleSCEta[HZgVar.lepID_[i]]:-5.;
      lepCh_[i] = (channel==0)? eleCharge[HZgVar.lepID_[i]]:muCharge[HZgVar.lepID_[i]];
      isEcalDriven[i] = (channel==0)? eleEcalDrivenSeed[HZgVar.lepID_[i]]:-99;
    }
  mll_ = HZgVar.vec_Z.M();
  if(isdebug)cout<<"fill lep"<<endl;
  Int_t  nPho     = data.GetInt("nPho");
  float* phoEt      = data.GetPtrFloat("phoCalibEt");//use this for analysis
  float* phoEta     = data.GetPtrFloat("phoEta");
  float* phoPhi     = data.GetPtrFloat("phoPhi");
  float* phoSCEta   = data.GetPtrFloat("phoSCEta");
  float* phoSCPhi   = data.GetPtrFloat("phoSCPhi");
  float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
  float* phoPFChIso = data.GetPtrFloat("phoPFChIso");
  float* phoSigmaE = data.GetPtrFloat("phoSigmaE");
  float* phoE = data.GetPtrFloat("phoE");
  //photon selection end
  gPt_      = phoEt[HZgVar.phoID_];
  gEta_     = phoEta[HZgVar.phoID_];
  gPhi_     = phoPhi[HZgVar.phoID_];
  mg_		= HZgVar.vec_pho.M();
  gSCEta_   = phoSCEta[HZgVar.phoID_];
  gR9_      = phoR9[0];
  gMVA_     = phoIDMVA[HZgVar.phoID_];
  mllg_     = HZgVar.vec_higgs.M();
  gdmllg 	= HZgVar.vec_pho.Pt()/HZgVar.vec_higgs.M();
  dRlg_     = TMath::Min(HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[0]), HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[1]));
  mllmllg 	= HZgVar.vec_higgs.M()+HZgVar.vec_Z.M();  
  HZgMVA 	= HZgVar.kinMVA;
  mllgpt = HZgVar.vec_higgs.Pt();
  ZgPTt           = 2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt();
  if(isdebug)cout<<"fill pho"<<endl;
  
   Int_t  nMC      = 0;
   Int_t* mcPID	  = NULL;
   Int_t* mcMomPID	  = NULL;
   Int_t* mcGMomPID	  = NULL;
   float* mcPt		  = NULL;
   float* mcMass	  = NULL;
   float* mcEta 	  = NULL;
   float* mcPhi 	  = NULL;
   UShort_t* mcStatusFlag = NULL;
  if (data.HasMC()&&isSig==1)
    {
      TLorentzVector genlep[2], genpho,genZ;
      nMC 	  = data.GetInt("nMC");
      mcPt     = data.GetPtrFloat("mcPt");
      mcEta    = data.GetPtrFloat("mcEta");
      mcPhi    = data.GetPtrFloat("mcPhi");
      mcMass = data.GetPtrFloat("mcMass");
      mcPID    = data.GetPtrInt("mcPID");
      mcMomPID = data.GetPtrInt("mcMomPID");
      mcGMomPID = data.GetPtrInt("mcGMomPID");
      mcStatusFlag =  (UShort_t*) data.GetPtrShort("mcStatusFlag");

      if(GENsel(data,channel,HZgVar))
	  {
		genphoPt = mcPt[HZgVar.genphoID];
		genphoEta = mcEta[HZgVar.genphoID];
		genphoPhi = mcPhi[HZgVar.genphoID];
		genpho.SetPtEtaPhiM(genphoPt, genphoEta,genphoPhi,0.);
		genlepPt[0] = mcPt[HZgVar.genlepID[0]];
		genlepEta[0] = mcEta[HZgVar.genlepID[0]];
		genlepPhi[0] = mcPhi[HZgVar.genlepID[0]];
		genlep[0].SetPtEtaPhiM(genlepPt[0],genlepEta[0],genlepPhi[0],mcMass[HZgVar.genlepID[0]]);
		genlepPt[1] = mcPt[HZgVar.genlepID[1]];
		genlepEta[1] = mcEta[HZgVar.genlepID[1]];
		genlepPhi[1] = mcPhi[HZgVar.genlepID[1]];
		genlep[1].SetPtEtaPhiM(genlepPt[1],genlepEta[1],genlepPhi[1],mcMass[HZgVar.genlepID[1]]);	
		genZ=genlep[0]+genlep[1];
		genmll=  genZ.M();
		if(HZgVar.vec_lep[0].DeltaR(genlep[0])<0.1&&HZgVar.vec_lep[1].DeltaR(genlep[1])<0.1&&HZgVar.vec_pho.DeltaR(genpho)<0.1)totmatch=1;
      }
    }
  if(isdebug)cout<<"fill gen"<<endl;
  //kinematic refit
  if(isrefit)
  {
	for(int i = 0 ; i < 2 ; i++)
    {
      REFITlepPt_[i] = HZgVar.REFIT_lepPt[i];
      REFITlepPtErr_[i] = HZgVar.REFIT_lepPtErr[i];
    }
	  REFITmll_ = HZgVar.REFIT_mll;
	  REFITmllg_ = HZgVar.REFIT_mllg;
	  mllerr_ =  HZgVar.mllerr;
	  if(isdebug)cout<<"fill refit"<<endl;	
  }
  
  ///-------------------store FSR variables-----------------------///
  if(isFSR){
    Int_t  npfPho			= data.GetInt("npfPho");
    float* pfPhoEt 			= data.GetPtrFloat("pfPhoEt");
    float* pfPhoEta 		= data.GetPtrFloat("pfPhoEta");
    float* pfPhoPhi 		= data.GetPtrFloat("pfPhoPhi");
	if(data.HasMC())mcPt     = data.GetPtrFloat("mcPt");
    if(data.HasMC())mcEta    = data.GetPtrFloat("mcEta");
    if(data.HasMC())mcPhi    = data.GetPtrFloat("mcPhi");
	if(data.HasMC())mcPID    = data.GetPtrInt("mcPID");
    if(data.HasMC())mcMomPID = data.GetPtrInt("mcMomPID");
	if(data.HasMC())mcGMomPID = data.GetPtrInt("mcGMomPID");
    if(data.HasMC())mcStatusFlag =  (UShort_t*) data.GetPtrShort("mcStatusFlag");
	
	TLorentzVector sfsr[2],sfsrZ, sfsrH, afsr[2],afsrZ, afsrH;
	//match the FSR purity
	TLorentzVector genpho;    vector <TLorentzVector> genfsr;
	genfsr.clear();
	genpho.SetPtEtaPhiM(0.,0.,0.,0.);//NULL value
	if(data.HasMC())
	{
		
		if(isSig==1)genpho.SetPtEtaPhiM(mcPt[HZgVar.genphoID],mcEta[HZgVar.genphoID],mcPhi[HZgVar.genphoID],0.);
		for(int l = 0; l < nMC ; l++)
      {	      	      
		if(mcPID[l]==22&&(fabs(mcMomPID[l])==11||fabs(mcMomPID[l])==13||mcMomPID[l]==23)&&((mcStatusFlag[l] >> 1) & 1) == 1&&isSig==1)
		  {
			TLorentzVector tmp;
			tmp.SetPtEtaPhiM(mcPt[l],mcEta[l],mcPhi[l],0.);
			genfsr.push_back(tmp);
		  } 
		else if(isSig!=1&&mcPID[l]==22&&(fabs(mcMomPID[l])==11||fabs(mcMomPID[l])==13||mcMomPID[l]==23)&&((mcStatusFlag[l] >> 1) & 1)==1)
		  {
			TLorentzVector tmp;
			tmp.SetPtEtaPhiM(mcPt[l],mcEta[l],mcPhi[l],0.);
			genfsr.push_back(tmp);
		  }
      }
	}
	
    for(int i = 0 ; i < 2 ;i ++)
      {
	if(channel == 0 )issfsr[i] = isafsr[i] = -99;
	issfsr[i] = HZgVar.sfsrID_[i];
	isafsr[i] = HZgVar.afsrID_[i];
	sfsr[i].SetPtEtaPhiM(0.,0.,0.,0.);
	afsr[i].SetPtEtaPhiM(0.,0.,0.,0.);
	if(HZgVar.sfsrID_[i]!=-99)
	  {
	    sfsrPt_[i] = pfPhoEt[HZgVar.sfsrID_[i]];
	    sfsrEta_[i] = pfPhoEta[HZgVar.sfsrID_[i]];
	    sfsrPhi_[i] = pfPhoPhi[HZgVar.sfsrID_[i]];
	    sfsr[i].SetPtEtaPhiM(sfsrPt_[i],sfsrEta_[i],sfsrPhi_[i],0.);
	    sfsrdRlg_[i] = sfsr[i].DeltaR(HZgVar.vec_lep[i]);
	    sfsrdRratio_[i] = sfsr[i].DeltaR(HZgVar.vec_lep[i])/(sfsrPt_[i]*sfsrPt_[i]);
		if(data.HasMC()){
		issfsr[i] = (sfsr[i].DeltaR(genpho)<0.1) ? 1 : 3;
		for(unsigned int j = 0; j < genfsr.size() ; j++)
		{
			issfsr[i] = (sfsr[i].DeltaR(genfsr[j])<0.1) ? 2 : 3;
		}	
		}
		else issfsr[i] = HZgVar.sfsrID_[i];
		
	  }
	  
	if(HZgVar.afsrID_[i]!=-99)
	  {
	    afsrPt_[i] = pfPhoEt[HZgVar.afsrID_[i]];
	    afsrEta_[i] = pfPhoEta[HZgVar.afsrID_[i]];
	    afsrPhi_[i] = pfPhoPhi[HZgVar.afsrID_[i]];
	    afsr[i].SetPtEtaPhiM(afsrPt_[i],afsrEta_[i],afsrPhi_[i],0.);
	    afsrdRlg_[i] = afsr[i].DeltaR(HZgVar.vec_lep[i]);
	    afsrdRratio_[i] = afsr[i].DeltaR(HZgVar.vec_lep[i])/(afsrPt_[i]*afsrPt_[i]);
		if(data.HasMC()){
		isafsr[i] = (afsr[i].DeltaR(genpho)<0.1) ? 1 : 3;
		for(unsigned int j = 0; j < genfsr.size() ; j++)
		{
			isafsr[i] = (afsr[i].DeltaR(genfsr[j])<0.1) ? 2 : 3;
		}
		}
		else isafsr[i] = HZgVar.afsrID_[i];
	  }
      }
    if(HZgVar.sfsrID_[0]!=-99&&HZgVar.sfsrID_[1]!=-99)sfsrZ = sfsr[0]+ sfsr[1] + HZgVar.vec_Z;
    if(HZgVar.sfsrID_[0]!=-99)sfsrZ = sfsr[0]+ HZgVar.vec_Z;
    if(HZgVar.sfsrID_[1]!=-99)sfsrZ = sfsr[1]+ HZgVar.vec_Z;
    if(HZgVar.afsrID_[0]!=-99&&HZgVar.afsrID_[1]!=-99)afsrZ = afsr[0]+ afsr[1] + HZgVar.vec_Z;
    if(HZgVar.afsrID_[0]!=-99)afsrZ = afsr[0]+ HZgVar.vec_Z;
    if(HZgVar.afsrID_[1]!=-99)afsrZ = afsr[1]+ HZgVar.vec_Z;
	sfsrmll_ = sfsrZ.M();
    sfsrH = sfsrZ + HZgVar.vec_pho;
    sfsrmllg_ = sfsrH.M();
    afsrmll_ = afsrZ.M();
    afsrH = afsrZ + HZgVar.vec_pho;
    afsrmllg_ = afsrH.M();
  }
 
 ///--------------------Categorization vars-------------------------///
  cat = HZgVar.cat;
  float* jetPhi = data.GetPtrFloat("jetPhi");
  float* jetEta = data.GetPtrFloat("jetEta");
  Float_t*	jetBtag		=	data.GetPtrFloat("jetCSV2BJetTags");
  if(HZgVar.isdbtag==1)
    {
      TLorentzVector dbjet_[2];
      for(int i = 0; i <2; i++)
	{
	  dbjetEn[i]  = jetEn[HZgVar.dbjet[i]];
	  dbjetPt[i]  = jetPt[HZgVar.dbjet[i]];
	  dbjetPhi[i] = jetPhi[HZgVar.dbjet[i]];
	  dbjetEta[i] = jetEta[HZgVar.dbjet[i]];
	  dbjet_[i].SetPtEtaPhiE(dbjetPt[i],dbjetEta[i],dbjetPhi[i],dbjetEn[i]);
	  dbjetlepdR[i] = min(dbjet_[i].DeltaR(HZgVar.vec_lep[0]),dbjet_[i].DeltaR(HZgVar.vec_lep[1]));
	  dbjetphodR[i] = dbjet_[i].DeltaR(HZgVar.vec_pho);
	  dbCsv2[i] = jetBtag[HZgVar.dbjet[i]];
	}
      isdbtag = HZgVar.isdbtag;
    }
  if(HZgVar.isLep==1)
    {
      TLorentzVector alep;
      alepPt = HZgVar.alepPt;
      if(HZgVar.cat == 6 || HZgVar.cat == 9)
	{
	  alepEta = eleEta[HZgVar.alep[0]];
	  alepPhi = elePhi[HZgVar.alep[0]];
	  alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 0.511*0.001);
	}
      else 
	{
	  alepEta = muEta[HZgVar.alep[0]];
	  alepPhi = muPhi[HZgVar.alep[0]];
	  alep.SetPtEtaPhiM(alepPt, alepEta, alepPhi, 105.7*0.001);
	}
      alepphodR = alep.DeltaR(HZgVar.vec_pho);
      aleplepdR = min(alep.DeltaR(HZgVar.vec_lep[0]),alep.DeltaR(HZgVar.vec_lep[1]));
    }
  if(HZgVar.isVBF==1)
    {
      Int_t nJet = data.GetInt("nJet");
      njets = HZgVar.jets.size();
      TLorentzVector jet[2];
      for(int i = 0; i <2; i++)
	{
	  VBFEn[i]  = jetEn[HZgVar.VBFjet[i]];
	  VBFPt[i]  = jetPt[HZgVar.VBFjet[i]];
	  VBFPhi[i] = jetPhi[HZgVar.VBFjet[i]];
	  VBFEta[i] = jetEta[HZgVar.VBFjet[i]];
	  jet[i].SetPtEtaPhiE(VBFPt[i],VBFEta[i],VBFPhi[i],VBFEn[i]);
	  VBFlepdR[i] = min(jet[i].DeltaR(HZgVar.vec_lep[0]),jet[i].DeltaR(HZgVar.vec_lep[1]));
	  VBFphodR[i] = jet[i].DeltaR(HZgVar.vec_pho);
	}
      HZgVBF = HZgVar.VBFMVA;
    }
  if(HZgVar.isbtag==1)
    {
      TLorentzVector bjet_;
      bjetPt  = jetPt[HZgVar.bjet[0]];
      bjetEta = jetEta[HZgVar.bjet[0]];
      bjetPhi = jetPhi[HZgVar.bjet[0]];
      bjetEn  = jetEn[HZgVar.bjet[0]];
      bCsv2 	= jetBtag[HZgVar.bjet[0]];
      bjet_.SetPtEtaPhiE(bjetPt,bjetEta,bjetPhi,bjetEn);
      bjetphodR = bjet_.DeltaR(HZgVar.vec_pho);
      bjetlepdR = min(bjet_.DeltaR(HZgVar.vec_lep[0]),bjet_.DeltaR(HZgVar.vec_lep[1]));
      isbtag = HZgVar.isbtag;
    }
  

  ///---------------------------SFs----------------------------///
  if(data.HasMC())
  {
	  for(int i = 0 ; i < 3 ; i++)
    {
      if(i<2)
	{
	  sfetrg_[i] = HZgVar.SFetrg_[i];
	  sfmutrg_[i] = HZgVar.SFmutrg_[i];
	  unetrg_[i] = HZgVar.UNetrg_[i];
	  unmutrg_[i] = HZgVar.UNmutrg_[i];
	  unedz_[i] = HZgVar.UNedz_[i];

	}
      sfGSF_[i] = HZgVar.SFGSF_[i];
      unGSF_[i] = HZgVar.UNGSF_[i];
      sfeID_[i] = HZgVar.SFeID_[i];
      uneID_[i] = HZgVar.UNeID_[i];
      sfmuID_[i] = HZgVar.SFmuID_[i];
      unmuID_[i] = HZgVar.UNmuID_[i];
      sfmuTrk_[i] = HZgVar.SFmuTrk_[i];
      unmuTrk_[i] = HZgVar.UNmuTrk_[i];
    }
  sfgID_ = HZgVar.SFgID_;
  ungID_ = HZgVar.UNgID_;
  sfgVeto_ = HZgVar.SFgVeto_;
  ungVeto_ = HZgVar.UNgVeto_;
  totSF_ = (channel==0)? sfGSF_[0]*sfGSF_[1]*sfGSF_[2]*sfetrg_[0]*sfetrg_[1]*sfeID_[0]*sfeID_[1]*sfeID_[2]*sfgVeto_*sfgID_*sfmuID_[2]:sfmutrg_[0]* sfmutrg_[1]*sfmuID_[0]*sfmuID_[1]*sfmuID_[2]*sfgVeto_*sfgID_*sfGSF_[2]*sfeID_[2];	 
  }
  outtreeZg_->Fill();
}
void AForest::fillkinMVA(TreeReader &data, Int_t channel, HZgVariables &HZgVar, vector<float> &phoR9)
{
  refresh();
  float* muEta = data.GetPtrFloat("muEta");
  float* eleEta = data.GetPtrFloat("eleEta");
  float* phoEta = data.GetPtrFloat("phoEta");
  float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
  float* phoSigmaE = data.GetPtrFloat("phoSigmaE");
  float* phoE = data.GetPtrFloat("phoE");
  mcwei_   	= HZgVar.mcwei;
  totSF_ = (channel==0)? HZgVar.SFGSF_[0]*HZgVar.SFGSF_[1]*HZgVar.SFGSF_[2]*HZgVar.SFetrg_[0]*HZgVar.SFetrg_[1]*HZgVar.SFeID_[0]*HZgVar.SFeID_[1]*HZgVar.SFeID_[2]*HZgVar.SFgVeto_*HZgVar.SFgID_*HZgVar.SFmuID_[2]:sfmutrg_[0]* sfmutrg_[1]*HZgVar.SFmuID_[0]*HZgVar.SFmuID_[1]*HZgVar.SFmuID_[2]*HZgVar.SFgVeto_*HZgVar.SFgID_*HZgVar.SFGSF_[2]*HZgVar.SFeID_[2];
  puwei_        = HZgVar.puwei;
  genwei_        = HZgVar.genwei;
  gEta_		= phoEta[HZgVar.phoID_];
  lepEta1  = (channel==0) ? eleEta[HZgVar.lepID_[0]]:muEta[HZgVar.lepID_[0]];
  lepEta2  = (channel==0) ? eleEta[HZgVar.lepID_[1]]:muEta[HZgVar.lepID_[1]];
  mllgptdmllg = HZgVar.vec_higgs.Pt()/HZgVar.vec_higgs.M();
  ZgPTt 		= 2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt();
  dEtaZg = fabs(HZgVar.vec_Z.Eta()-HZgVar.vec_pho.Eta());
  dRlg_       = TMath::Min(HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[0]), HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[1]));
  maxdRlg_      =TMath::Max(HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[0]), HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[1]));
  mllmllg 	= HZgVar.vec_higgs.M()+HZgVar.vec_Z.M();
  gR9_		= phoR9[0];
  gMVA_		= phoIDMVA[HZgVar.phoID_];
  mllg_           = HZgVar.vec_higgs.M();
  costheta    = HZgVar.HZgcostheta;
  cosTheta    = HZgVar.HZgcosTheta;
  Phi    		= HZgVar.HZgPhi;
  phores = phoSigmaE[HZgVar.phoID_]/phoE[HZgVar.phoID_];
  mllres = HZgVar.mllerr/HZgVar.vec_Z.Pt();
  lep1res = HZgVar.REFIT_lepPtErr[0]/HZgVar.vec_lep[0].Pt();
  lep2res = HZgVar.REFIT_lepPtErr[1]/HZgVar.vec_lep[1].Pt();
  //cout<<"fill mva: "<<costheta<<" "<<cosTheta<<" "<<Phi<<" "<<mllgptdmllg<<" "<<lepEta1<<" "<<lepEta2<<" "<<gMVA_<<" "<<gR9_<<" "<<gEta_<<" "<<phores<<" "<<dRlg_<<" "<<maxdRlg_<<endl;
  HZgMVA = HZgVar.kinMVA;
  MVAtree->Fill();
}
void AForest::fillVBFMVA(TreeReader &data, Int_t channel, HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &jetEn)
{
  float* phoSigmaE = data.GetPtrFloat("phoSigmaE");
  float* phoE = data.GetPtrFloat("phoE");
  float* jetEta = data.GetPtrFloat("jetEta");
  float* jetPhi = data.GetPtrFloat("jetPhi");
  TLorentzVector jet[2],dijet;
  jet[0].SetPtEtaPhiE(jetPt[HZgVar.VBFjet[0]],jetEta[HZgVar.VBFjet[0]],jetPhi[HZgVar.VBFjet[0]],jetEn[HZgVar.VBFjet[0]]);
  jet[1].SetPtEtaPhiE(jetPt[HZgVar.VBFjet[1]],jetEta[HZgVar.VBFjet[1]],jetPhi[HZgVar.VBFjet[1]],jetEn[HZgVar.VBFjet[1]]);
  dijet = jet[0]+jet[1];
  mcwei_   	= HZgVar.mcwei;
  totSF_  	= (channel == 0)? HZgVar.SFGSF_[0]*HZgVar.SFGSF_[1]*HZgVar.SFetrg_[0]*HZgVar.SFetrg_[1]*HZgVar.SFeID_[0]*HZgVar.SFeID_[1]*HZgVar.SFgVeto_*HZgVar.SFgID_: HZgVar.SFmutrg_[0]*HZgVar.SFmutrg_[1]*HZgVar.SFmuID_[0]*HZgVar.SFmuID_[1]*HZgVar.SFgVeto_*HZgVar.SFgID_;
  puwei_        = HZgVar.puwei;
  genwei_        = HZgVar.genwei;
  VBFPt1 = jet[0].Pt();
  VBFPt2 = jet[1].Pt();
  mjj = dijet.M();
  CZg = exp(-4/pow(jet[0].Eta()-jet[1].Eta(),2)*pow(HZgVar.vec_higgs.Eta()-((jet[0].Eta()+jet[1].Eta())/2),2));
  dEta_jj = jet[1].Eta()-jet[0].Eta();
  absdEta_jj = fabs(jet[1].Eta()-jet[0].Eta());
  dPhi_Zgjj = dijet.DeltaPhi(HZgVar.vec_higgs);
  absdPhi_Zgjj = fabs(dijet.DeltaPhi(HZgVar.vec_higgs));
  dPhi_jj = jet[1].DeltaPhi(jet[0]);
  absdPhi_jj = fabs(jet[1].DeltaPhi(jet[0]));
  dR_phojet = min(HZgVar.vec_pho.DeltaR(jet[0]),HZgVar.vec_pho.DeltaR(jet[1]));
  ZgPTt 		= 2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt();
  mllg_           = HZgVar.vec_higgs.M();
  Zeppen = HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
  absZeppen = fabs(HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2);
  phores = phoSigmaE[HZgVar.phoID_]/phoE[HZgVar.phoID_];
  theta = min((min(jet[0].Eta(),jet[1].Eta())-min(HZgVar.vec_Z.Eta(),HZgVar.vec_higgs.Eta())),(min(HZgVar.vec_Z.Eta(),HZgVar.vec_higgs.Eta())-min(jet[0].Eta(),jet[1].Eta())));
  HZgMVA = HZgVar.kinMVA;
  HZgVBF = HZgVar.VBFMVA;
  tVBF->Fill();
}
