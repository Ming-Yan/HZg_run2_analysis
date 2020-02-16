using namespace std;


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
    if(phoIDMVA[i] < 0.2) continue; //--2016MVA 25ns WP90    

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
void PhotonIDMVA2016_mod(TreeReader &data, vector<int>&accepted,HZgVariables &HZgVar,int channel) {

  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> phoEtUnsorted;
  phoEtUnsorted.clear();

  Int_t  nPho       = data.GetInt("nPho");
  //float* phoEt      = data.GetPtrFloat("phoEt");
  float *phoEt      = data.GetPtrFloat("phoCalibEt");
  float *phoEta     = data.GetPtrFloat("phoEta");
  float *phoPhi     = data.GetPtrFloat("phoPhi");
  float* phoSCEta   = data.GetPtrFloat("phoSCEta");
  float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");
  Int_t* phoEleVeto = data.GetPtrInt("phoEleVeto");
  int*   pfPhoPhoIndex  = data.GetPtrInt("pfPhoPhoIndex");

  TLorentzVector tmppho;
  for (Int_t i=0; i<nPho; ++i) 
    {
      if (channel==1&&((HZgVar.sfsrID_[0]!=-99&&pfPhoPhoIndex[HZgVar.sfsrID_[0]]==i)||(HZgVar.sfsrID_[1]!=-99&&pfPhoPhoIndex[HZgVar.sfsrID_[1]]==i))) continue;
      if (phoEt[i] < 15) continue;
      if (fabs(phoSCEta[i]) > 2.5) continue;
      if (fabs(phoSCEta[i]) >= 1.4442 && fabs(phoSCEta[i]) <= 1.566) continue;
      // tmppho.SetPtEtaPhiM(phoEt[i], phoEta[i], phoPhi[i], 0.);
      // if (tmppho.DeltaR(HZgVar.vec_lep[0]) < 0.4 || tmppho.DeltaR(HZgVar.vec_lep[1]) < 0.4) continue;
      if (phoEleVeto[i] == 0) continue;
      if(phoIDMVA[i] < 0.2) continue; //--2016MVA 25ns WP90    

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
void PhotonIDMVA2017_mod(TreeReader &data, vector<int>&accepted, HZgVariables &HZgVar,int channel) {

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
  int*   pfPhoPhoIndex  = data.GetPtrInt("pfPhoPhoIndex");

  for (Int_t i=0; i<nPho; ++i) {

    if (phoEt[i] < 15) continue;
    if (channel==1&&((HZgVar.sfsrID_[0]!=-99&&pfPhoPhoIndex[HZgVar.sfsrID_[0]]==i)||(HZgVar.sfsrID_[1]!=-99&&pfPhoPhoIndex[HZgVar.sfsrID_[1]]==i))) continue;
    if (fabs(phoSCEta[i]) > 2.5) continue;
    if (fabs(phoSCEta[i]) >= 1.4442 && fabs(phoSCEta[i]) <= 1.566) continue;
    if (phoEleVeto[i] == 0) continue;
    if (fabs(phoSCEta[i]) <= 1.4442 &&phoIDMVA[i] < 0.27) continue; //--2016MVA 25ns WP90    
    if (fabs(phoSCEta[i]) > 1.566 &&phoIDMVA[i] < 0.14) continue; //--2016MVA 25ns WP90    
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
void HZgMVAphoIDcut(TreeReader &data, vector<int>&accepted) {

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
    
    if (fabs(phoSCEta[i]) < 1.4442 && phoIDMVA[i] < 0) continue;
    if (fabs(phoSCEta[i]) > 1.566 && phoIDMVA[i] < -0.1) continue;
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




