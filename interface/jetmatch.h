int VBFmatch(TreeReader &data,  HZgVariables &HZgVar)
{
  Int_t nLHE = data.GetInt("nLHE");
  int * lhePID = data.GetPtrInt("lhePID");
  float *lhePx = data.GetPtrFloat("lhePx");
  float *lhePy = data.GetPtrFloat("lhePy");
  float *lhePz = data.GetPtrFloat("lhePz");
  float *lheE = data.GetPtrFloat("lheE");
  Int_t nJet = data.GetInt("nJet");
  float *jetGenEn = data.GetPtrFloat("jetGenEn");
  float *jetGenPt = data.GetPtrFloat("jetGenPt");
  float *jetGenEta = data.GetPtrFloat("jetGenEta");
  float *jetGenPhi = data.GetPtrFloat("jetGenPhi");
  int   *jetGenPartonID = data.GetPtrInt("jetGenPartonID");
  TLorentzVector recojet[2],genjet[2];
  genjet[0].SetPxPyPzE(lhePx[1],lhePy[1],lhePz[1],lheE[1]);
  genjet[1].SetPxPyPzE(lhePx[2],lhePy[2],lhePz[2],lheE[2]);
  recojet[0].SetPtEtaPhiE(jetGenPt[HZgVar.VBFjet[0]],jetGenEta[HZgVar.VBFjet[0]],jetGenPhi[HZgVar.VBFjet[0]],jetGenEn[HZgVar.VBFjet[0]]);
  recojet[1].SetPtEtaPhiE(jetGenPt[HZgVar.VBFjet[1]],jetGenEta[HZgVar.VBFjet[1]],jetGenPhi[HZgVar.VBFjet[1]],jetGenEn[HZgVar.VBFjet[1]]);
  //cout<<"LHE: "<<lhePID[1]<<" "<<lhePID[2]<<" "<<genjet[0].Pt()<<" "<<genjet[1].Pt()<<endl;
  //cout<<"parton:" <<jetGenPartonID[HZgVar.VBFjet[0]]<<" "<<jetGenPartonID[HZgVar.VBFjet[1]]<<" "<<recojet[0].Pt()<<" "<<recojet[1].Pt()<<endl;

  if(fabs(genjet[0].Pt()-recojet[0].Pt())<0.001&&fabs(genjet[1].Pt()-recojet[1].Pt())<0.001)return 1;
  if(fabs(genjet[1].Pt()-recojet[0].Pt())<0.001&&fabs(genjet[0].Pt()-recojet[1].Pt())<0.001)return 1;
    //if(genjet[0].DeltaR(recojet[0])<0.2&&genjet[1].DeltaR(recojet[1])<0.2)return 1;
  //else if (genjet[1].DeltaR(recojet[0])<0.2&&genjet[0].DeltaR(recojet[1])<0.2)return 1;
  else {HZgVar.VBFPID[0]= jetGenPartonID[HZgVar.VBFjet[0]];
    HZgVar.VBFPID[1]= jetGenPartonID[HZgVar.VBFjet[1]];return -99;}
}
 
