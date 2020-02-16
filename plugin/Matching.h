void EleMatching(TreeReader &data, vector<int>&accepted, Float_t eleEta, Float_t elePhi){

  accepted.clear();


  for (int i=0 ; i<nEle ; ++i){
    if(elePt[i] < 5 )continue;
    if (deltaR(eleEta[i], elePhi[i], mcEta, mcPhi) > 0.1 ) continue;
    accepted.push_back(i);
  }


} // end of function

void MuMatching(TreeReader &data, vector<int>&accepted, Float_t mcEta, Float_t mcPhi){

  accepted.clear();
    Int_t  nMu      = data.GetInt("nMu");
    float* muEta    = data.GetPtrFloat("muEta");
    float* muPhi    = data.GetPtrFloat("muPhi");
    float* muPt     = data.GetPtrFloat("muPt");


  for (int i=0 ; i<nMu ; ++i){
    if(muPt[i] < 5) continue;
    if (deltaR(muEta[i], muPhi[i], mcEta, mcPhi) > 0.1 ) continue;
    accepted.push_back(i);
  }


} // end of function

void PhoZgMatching(TreeReader &data, vector<int>&accepted, Float_t mcEta, Float_t mcPhi){

  accepted.clear();
    Int_t  nPho      = data.GetInt("nPho");
    float* phoEta    = data.GetPtrFloat("phoEta");
    float* phoPhi    = data.GetPtrFloat("phoPhi"); 
    float* phoPt    = data.GetPtrFloat("phoPt");


  for (int i=0 ; i<nPho ; ++i){
    if(phoPt[i] < 5 ) continue;
    if (deltaR(phoEta[i], phoPhi[i], mcEta, mcPhi) > 0.1 ) continue;
    accepted.push_back(i);
  }


} // end of function
