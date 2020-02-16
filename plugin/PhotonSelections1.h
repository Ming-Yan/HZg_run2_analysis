using namespace std;

/*void PhotonPreselections(TreeReader &data, vector<int>&accepted) {

  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> phoEtUnsorted;
  phoEtUnsorted.clear();

  Int_t  nPho                    = data.GetInt("nPho");
  //float* phoEt                   = data.GetPtrFloat("phoEt");
  float* phoEt                   = data.GetPtrFloat("phoCalibEt");
  float* phoSCEta                = data.GetPtrFloat("phoSCEta");
  float* phoHoverE               = data.GetPtrFloat("phoHoverE");
  float* phoSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  float* phoPFPhoIso             = data.GetPtrFloat("phoPFPhoIso");
  float* phoPFChWorstIso         = data.GetPtrFloat("phoPFChWorstIso");
  Int_t* phoEleVeto              = data.GetPtrInt("phoEleVeto");

  Float_t cut_hoe[2]       = {0.08,  0.05};
  Float_t cut_sieie[2]     = {0.015, 0.045};
  Float_t cut_phoIso[2]    = {15,    15};
  Float_t cut_worsCHIso[2] = {15,    15};

  for (Int_t i=0; i<nPho; ++i) {

    if (phoEt[i] < 10) continue;
    if (fabs(phoSCEta[i]) > 2.5) continue;
    if (fabs(phoSCEta[i]) > 1.4442 && fabs(phoSCEta[i]) < 1.566) continue;

    if (phoEleVeto[i] == 0) continue;

    Int_t iEB = (fabs(phoSCEta[i]) < 1.4442) ? 0 : 1;

    if (phoHoverE[i]               > cut_hoe[iEB])       continue;
    if (phoSigmaIEtaIEtaFull5x5[i] > cut_sieie[iEB])     continue;
    if (phoPFPhoIso[i]             > cut_phoIso[iEB])    continue;
    if (phoPFChWorstIso[i]         > cut_worsCHIso[iEB]) continue;

    //accepted.push_back(i);
    passUnsorted.push_back(i);
    phoEtUnsorted.push_back(phoEt[i]);
  }

  // sort accepted photons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &phoEtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i) {
    accepted.push_back(passUnsorted[ind[i]]);
  }


}*/

/*Int_t PassPhotonPreselections(TreeReader &data, Int_t i) {

  Int_t pass = 1;

  Int_t  nPho                    = data.GetInt("nPho");
  //float* phoEt                   = data.GetPtrFloat("phoEt");
  float* phoEt                   = data.GetPtrFloat("phoCalibEt");
  float* phoSCEta                = data.GetPtrFloat("phoSCEta");
  float* phoHoverE               = data.GetPtrFloat("phoHoverE");
  float* phoSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  float* phoPFPhoIso             = data.GetPtrFloat("phoPFPhoIso");
  float* phoPFChWorstIso         = data.GetPtrFloat("phoPFChWorstIso");
  Int_t* phoEleVeto              = data.GetPtrInt("phoEleVeto");

  Float_t cut_hoe[2]       = {0.08,  0.05};
  Float_t cut_sieie[2]     = {0.015, 0.045};
  Float_t cut_phoIso[2]    = {15,    15};
  Float_t cut_worsCHIso[2] = {15,    15};

  if (phoEt[i] < 10) pass = 0;;
  if (fabs(phoSCEta[i]) > 2.5) pass = 0;;
  if (fabs(phoSCEta[i]) > 1.4442 && fabs(phoSCEta[i]) < 1.566) pass = 0;;

  if (phoEleVeto[i] == 0) pass = 0;;

  Int_t iEB = (fabs(phoSCEta[i]) < 1.4442) ? 0 : 1;

  if (phoHoverE[i]               > cut_hoe[iEB])       pass = 0;;
  if (phoSigmaIEtaIEtaFull5x5[i] > cut_sieie[iEB])     pass = 0;;
  if (phoPFPhoIso[i]             > cut_phoIso[iEB])    pass = 0;;
  if (phoPFChWorstIso[i]         > cut_worsCHIso[iEB]) pass = 0;;

  return pass;
}*/

void PhotonIDMVA2016(TreeReader &data, vector<int>&accepted) {

  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> phoEtUnsorted;
  phoEtUnsorted.clear();

  Int_t  nPho       = data.GetInt("nPho");
  //float* phoEt      = data.GetPtrFloat("phoEt");
  float *phoEt      = data.GetPtrFloat("phoCalibEt");
  float *phoEta     = data.GetPtrFloat("phoEta");
  float* phoSCEta   = data.GetPtrFloat("phoSCEta");
  float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
  Int_t* phoEleVeto = data.GetPtrInt("phoEleVeto");


  for (Int_t i=0; i<nPho; ++i) {

    if (phoEt[i] < 15) continue;

    if (fabs(phoSCEta[i]) > 2.5) continue;
    if (fabs(phoSCEta[i]) >= 1.4442 && fabs(phoSCEta[i]) <= 1.566) continue;
    if (phoEleVeto[i] == 0) continue;
    
    if (fabs(phoSCEta[i]) < 1.4442 && phoIDMVA[i] < 0.374) continue; //--2015MVA 25ns WP90
    if (fabs(phoSCEta[i]) > 1.566  && phoIDMVA[i] < 0.336) continue; //--2015MVA 25ns WP90
    //if (fabs(phoSCEta[i]) < 1.4442 && phoIDMVA[i] < 0) continue;
    //if (fabs(phoSCEta[i]) > 1.566 && phoIDMVA[i] < -0.1) continue;
    //accepted.push_back(i);
    passUnsorted.push_back(i);
    phoEtUnsorted.push_back(phoEt[i]);
  }

  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &phoEtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i) {
    accepted.push_back(passUnsorted[ind[i]]);
  }

}
//float PhotonSSMVA(TreeReader &data, Int_t i) {

  /* Photon identification with the Zgamma MVA. Returns the MVA evaluated value.
  *
  * Documentation:
  * https://indico.cern.ch/getFile.py/access?contribId=3&resId=0&materialId=slides&confId=298231
  *
  * data = handle providing access to an input event;
  * i = index of a photon candidate to consider.
  */

/*Bool_t  isData             = data.GetBool("isData");
// load necessary tree branches
Float_t* phoEt             = data.GetPtrFloat("phoEt");
Float_t* phoEta            = data.GetPtrFloat("phoEta");
Float_t* phoPhi            = data.GetPtrFloat("phoPhi");
Float_t* phoR9             = data.GetPtrFloat("phoR9");
Float_t* phoSCEta          = data.GetPtrFloat("phoSCEta");
Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
Float_t  rho               = data.GetFloat("rho");*/
/* Float_t* phoPFPhoIso       = data.GetPtrFloat("phoPFPhoIso"); */
/* Float_t* phoPFChIso        = data.GetPtrFloat("phoPFChIso"); */
/* Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso"); */
//Float_t* phoESEn           = data.GetPtrFloat("phoESEn");
//Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");

//Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
//Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
/* Float_t* phoE1x3Full5x5           = data.GetPtrFloat("phoE1x3Full5x5"); */
//Float_t* phoE2x2Full5x5           = data.GetPtrFloat("phoE2x2Full5x5");
//Float_t* phoE5x5Full5x5           = data.GetPtrFloat("phoE5x5Full5x5");
/* Float_t* phoE2x5MaxFull5x5        = data.GetPtrFloat("phoE2x5MaxFull5x5"); */
/*
// classification variables
static float phoEt_, phoEta_, phoPhi_, phoR9_;
static float phoSCEtaWidth_, phoSCPhiWidth_, rho_;
static float phoSCEta_, phoSCRawE_;
//static float phoPFPhoIso_, phoPFChIso_, phoPFChIsoWorst_;
static float phoESEnToRawE_, phoESEffSigmaRR_;

static float sieieFull5x5, sieipFull5x5, s13Full5x5, s4Full5x5, s25Full5x5;

// MVA classifiers for 0=ECAL barrel and 1=ECAL endcaps
static TMVA::Reader* tmvaReader[2] = {NULL, NULL};

// 0=ECAL barrel or 1=ECAL endcaps
int iBE = (fabs(phoSCEta[i]) < 1.479) ? 0 : 1;

// one-time MVA initialization
if (!tmvaReader[iBE]) {
  tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

  // add classification variables
  tmvaReader[iBE]->AddVariable("recoPhi", &phoPhi_);
  tmvaReader[iBE]->AddVariable("r9", &phoR9_);
  tmvaReader[iBE]->AddVariable( "sieieFull5x5",             &sieieFull5x5 );
  tmvaReader[iBE]->AddVariable( "sieipFull5x5",             &sieipFull5x5 );     */
  /* tmvaReader[iBE]->AddVariable( "s13 := e1x3Full5x5/e5x5Full5x5",   &s13Full5x5 );         */
  //  tmvaReader[iBE]->AddVariable( "s4 := e2x2Full5x5/e5x5Full5x5",    &s4Full5x5 );
  /* tmvaReader[iBE]->AddVariable( "s25 := e2x5Full5x5/e5x5Full5x5",   &s25Full5x5 );         */
  /*  tmvaReader[iBE]->AddVariable("recoSCEta", &phoSCEta_);
  tmvaReader[iBE]->AddVariable("rawE", &phoSCRawE_);
  tmvaReader[iBE]->AddVariable("scEtaWidth", &phoSCEtaWidth_);
  tmvaReader[iBE]->AddVariable("scPhiWidth", &phoSCPhiWidth_);
  if (iBE == 1) {
    tmvaReader[iBE]->AddVariable("ESEn := esEn/rawE", &phoESEnToRawE_);
    tmvaReader[iBE]->AddVariable("esRR", &phoESEffSigmaRR_);
  }
  tmvaReader[iBE]->AddVariable("rho", &rho_);*/
  /* tmvaReader[iBE]->AddVariable("phoIsoRaw", &phoPFPhoIso_); */
  /* tmvaReader[iBE]->AddVariable("chIsoRaw", &phoPFChIso_); */
  /* tmvaReader[iBE]->AddVariable("chWorstRaw", &phoPFChIsoWorst_); */

  //tmvaReader[iBE]->AddVariable("recoPt", &phoEt_);
  // FIXME: why do we need this?
  /* tmvaReader[iBE]->AddSpectator("recoPt", &phoEt_); */
  /* tmvaReader[iBE]->AddSpectator("recoEta", &phoEta_); */
  /*
  // read weight files
  if (iBE == 0) tmvaReader[0]->BookMVA("BDT", "/home/cmkuo/work/SMP-ZG/ana/external/EB_v1_ssbdt.xml");
  else tmvaReader[1]->BookMVA("BDT", "/home/cmkuo/work/SMP-ZG/ana/external/EE_v1_ssbdt.xml");

 } // one-time initialization

// set MVA variables
phoPhi_          = phoPhi[i];
phoR9_           = phoR9[i];
phoSCEta_        = phoSCEta[i];
phoSCRawE_       = phoSCRawE[i];
phoSCEtaWidth_   = phoSCEtaWidth[i];
phoSCPhiWidth_   = phoSCPhiWidth[i];
rho_             = rho;
phoESEnToRawE_   = phoESEn[i]/phoSCRawE[i];
phoESEffSigmaRR_ = phoESEffSigmaRR[i];
phoEt_           = phoEt[i];
phoEta_          = phoEta[i];
sieieFull5x5     = phoSigmaIEtaIEtaFull5x5[i];
sieipFull5x5     = phoSigmaIEtaIPhiFull5x5[i];
s4Full5x5        = phoE2x2Full5x5[i]/phoE5x5Full5x5[i];*/
/* s13Full5x5    = phoE1x3Full5x5[i]/phoE5x5Full5x5[i]; */
/* phoPFPhoIso_     = phoPFPhoIso[i]; */
/* phoPFChIso_      = phoPFChIso[i]; */
/* phoPFChIsoWorst_ = phoPFChWorstIso[i]; */
/* s25Full5x5    = phoE2x5MaxFull5x5[i]/phoE5x5Full5x5[i]; */
/*
return tmvaReader[iBE]->EvaluateMVA("BDT");

}*/
