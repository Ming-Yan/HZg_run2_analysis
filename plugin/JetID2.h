using namespace std;
void JetID16(TreeReader &data,vector<int> &accepted, HZgVariables &HZgVar,vector<float> &jetPt, vector<float> &tmpjetEn){
  accepted.clear();
	
  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Float_t *NHF  = data.GetPtrFloat("jetNHF");
  Float_t *NEMF = data.GetPtrFloat("jetNEF");
  Int_t   *NNP  = data.GetPtrInt("jetNNP");
  Float_t *CHF  = data.GetPtrFloat("jetCHF");
  Int_t   *CHM  = data.GetPtrInt("jetNCH");
  Float_t *CEMF = data.GetPtrFloat("jetCEF");
	
  bool looseJetID = true;
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
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4) continue;
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4)cout<<"jetid:"<<tmpjet.DeltaR(HZgVar.vec_pho)<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[0])<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[1])<<endl;

      //old jet selections
      accepted.push_back(i);
    }
}

//move to tight jetID
void JetID17(TreeReader &data,vector<int> &accepted, HZgVariables &HZgVar,vector<float> &jetPt, vector<float> &tmpjetEn){
  accepted.clear();
	
  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Float_t *NHF  = data.GetPtrFloat("jetNHF");
  Float_t *NEMF = data.GetPtrFloat("jetNEF");
  Int_t   *NNP  = data.GetPtrInt("jetNNP");
  Float_t *CHF  = data.GetPtrFloat("jetCHF");
  Int_t   *CHM  = data.GetPtrInt("jetNCH");
  Float_t *CEMF = data.GetPtrFloat("jetCEF");
	
  bool tightJetID = true;
  TLorentzVector tmpjet;

  for(Int_t i = 0; i < nJet ; i++)
    {
      if(jetPt[i] < 30.) continue;
      if(fabs(jetEta[i])>4.7) continue;
      Int_t NumConst= CHM[i]+NNP[i];
      if (fabs(jetEta[i]) <= 2.7)
	{
	  tightJetID = (NHF[i]<0.9 && NEMF[i]<0.9 && NumConst>1
	    && (fabs(jetEta[i])<=2.4 && CHF[i]>0 && CHM[i]>0 ));
	}
      else if (fabs(jetEta[i]) <= 3.0)
	{
	  tightJetID = (NEMF[i]>0.02&&NEMF[i]<0.99 && NNP[i]>2);
	}
      else
	{
	  tightJetID = (NEMF[i]<0.90 && NHF[i] > 0.02 &&NNP[i]>10);
	}

      if(tightJetID == false)continue;
      tmpjet.SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4) continue;
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4)cout<<"jetid:"<<tmpjet.DeltaR(HZgVar.vec_pho)<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[0])<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[1])<<endl;

      //old jet selections
      accepted.push_back(i);
    }
}
void JetID18(TreeReader &data,vector<int> &accepted, HZgVariables &HZgVar,vector<float> &jetPt, vector<float> &tmpjetEn){
  accepted.clear();
  
  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Float_t *NHF  = data.GetPtrFloat("jetNHF");
  Float_t *NEMF = data.GetPtrFloat("jetNEF");
  Int_t   *NNP  = data.GetPtrInt("jetNNP");
  Float_t *CHF  = data.GetPtrFloat("jetCHF");
  Int_t   *CHM  = data.GetPtrInt("jetNCH");
  Float_t *CEMF = data.GetPtrFloat("jetCEF");
  
  bool tightJetID = true;
  TLorentzVector tmpjet;

  for(Int_t i = 0; i < nJet ; i++)
    {
      if(jetPt[i] < 30.) continue;
      if(fabs(jetEta[i])>4.7) continue;
      Int_t NumConst= CHM[i]+NNP[i];
      if (fabs(jetEta[i]) <= 2.6)tightJetID = (NHF[i]<0.9 && NEMF[i]<0.9 && NumConst>1&&CHF[i]>0 && CHM[i]>0 );
      else if(fabs(jetEta[i]) <= 2.7)tightJetID = (NHF[i]<0.9 && NEMF[i]<0.9 && CHM[i]>0 );
      else if (fabs(jetEta[i]) <= 3.0)tightJetID = (NEMF[i]>0.02&&NEMF[i]<0.99 && NNP[i]>2);
      else tightJetID = (NEMF[i]<0.90 && NHF[i] > 0.02 &&NNP[i]>10);

      if(tightJetID == false)continue;
      tmpjet.SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4) continue;
      if(fabs(tmpjet.DeltaR(HZgVar.vec_pho)) < 0.4||fabs(tmpjet.DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(tmpjet.DeltaR(HZgVar.vec_lep[1])) < 0.4)cout<<"jetid:"<<tmpjet.DeltaR(HZgVar.vec_pho)<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[0])<<" "<<tmpjet.DeltaR(HZgVar.vec_lep[1])<<endl;

      //old jet selections
      accepted.push_back(i);
    }
}
