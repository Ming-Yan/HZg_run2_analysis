void SMPZZ_FSR(TreeReader &data, HZgVariables &HZgVar, vector<int> &accepted,int channel, int lt)
{
  static vector<float> fsrdr;	fsrdr.clear();
  static vector<int> tmpfsr;	tmpfsr.clear(); 
  static vector<int> tmpfsr_;	tmpfsr_.clear(); 

  //vector<int>accepted;
  accepted.clear();
  Int_t  npfPho			= data.GetInt("npfPho");
  float* pfphoEt 		= data.GetPtrFloat("pfPhoEt");
  float* pfphoEta 		= data.GetPtrFloat("pfPhoEta");
  float* pfphoPhi 		= data.GetPtrFloat("pfPhoPhi");
  float* pfPhoChIso 	= data.GetPtrFloat("pfPhoChIso");
  float* pfPhoPhoIso	= data.GetPtrFloat("pfPhoPhoIso");
  float* pfPhoNeuIso 	= data.GetPtrFloat("pfPhoNeuIso");
  int*   pfPhoPhoIndex  = data.GetPtrInt("pfPhoPhoIndex");
  HZgVar.sfsrID_[lt] = -99;
  float diffZ = 1000000.;
  for (int i = 0 ; i < npfPho ; i++)
    {
      if (pfphoEt[i] < 2.) continue;//kincut
      if (abs(pfphoEta[i])>2.4) continue;//kin cut
      if (pfPhoPhoIndex[i]==HZgVar.phoID_) continue;
      TLorentzVector fsrpho,tmpZ;
      fsrpho.SetPtEtaPhiM(pfphoEt[i],pfphoEta[i],pfphoPhi[i],0.);
      if(lt==1&&HZgVar.sfsrID_[0]==i) continue;
      //if(pfPhoPhoIndex[HZgVar.sfsrID_[1]]==i&&HZgVar.sfsrID_[1]!=-99) continue;
      tmpfsr_.push_back(i);
      if (fsrpho.DeltaR(HZgVar.vec_lep[lt])>0.4) continue;  

      if (((pfPhoChIso[i] +  pfPhoPhoIso[i] + pfPhoNeuIso[i] ) / pfphoEt[i]) >= 1.8) continue;//1.
      if (fsrpho.DeltaR(HZgVar.vec_lep[lt])/(pfphoEt[i]*pfphoEt[i])>0.012) continue;
      TLorentzVector Zfsr = HZgVar.vec_lep[0]+HZgVar.vec_lep[1]+fsrpho;
      if(fabs(Zfsr.M()-91.18)>fabs(HZgVar.vec_Z.M()-91.18)) continue;
      //else continue;
      fsrdr.push_back(fsrpho.DeltaR(HZgVar.vec_lep[lt])/(pfphoEt[i]*pfphoEt[i]));
      tmpfsr.push_back(i);      
      /* Float_t cut_effA[7] = {0.1703, 0.1715, 0.1213, 0.1230, 0.1635, 0.1937, 0.2393};
	 Int_t eta_bit = -1;
	 if (fabs(pfphoEta[i]) >= 0.000 && fabs(pfphoEta[i]) < 1.000) eta_bit = 0;
	 if (fabs(pfphoEta[i]) >= 1.000 && fabs(pfphoEta[i]) < 1.479) eta_bit = 1;
	 if (fabs(pfphoEta[i]) >= 1.479 && fabs(pfphoEta[i]) < 2.000) eta_bit = 2;
	 if (fabs(pfphoEta[i]) >= 2.000 && fabs(pfphoEta[i]) < 2.200) eta_bit = 3;
	 if (fabs(pfphoEta[i]) >= 2.200 && fabs(pfphoEta[i]) < 2.300) eta_bit = 4;
	 if (fabs(pfphoEta[i]) >= 2.300 && fabs(pfphoEta[i]) < 2.400) eta_bit = 5;
	 if (fabs(pfphoEta[i]) >= 2.400 && fabs(pfphoEta[i]) < 5.000) eta_bit = 6; */
      
      //electron channel has tighter cut
      // if(channel==0)
      // {
      // if(fsrpho.DeltaR(HZgVar.vec_lep[0])<0.15||fsrpho.DeltaR(HZgVar.vec_lep[1])<0.15) continue;
      // if(fsrpho.DeltaPhi(HZgVar.vec_lep[0])<2.||fsrpho.DeltaPhi(HZgVar.vec_lep[1])<2.) continue;
      // if(fabs(fsrpho.Eta()-HZgVar.vec_lep[0].Eta())<0.05||fabs(fsrpho.Eta()-HZgVar.vec_lep[0].Eta())<0.05) continue;
      // }      
    }

  int siz = (int) tmpfsr.size();
  if (siz<1) HZgVar.sfsrID_[lt] = -99;
  if (siz < 1) return;
  int ind[siz];
  TMath::Sort(siz, &fsrdr.front(), ind, kFALSE);
  for (int i = 0; i < siz; i++)
    {
      accepted.push_back(tmpfsr[ind[i]]);
    }
    HZgVar.sfsrID_[lt] = accepted[0];
    accepted.clear();
    accepted.assign(tmpfsr_.begin(),tmpfsr_.end());
    //if(HZgVar.sfsrID_[lt]!=-99)cout<<accepted.size()<<endl;  
}

void Atlas_FSR(TreeReader &data, HZgVariables &HZgVar, int lt)
{
  vector<float> fsrpt;	fsrpt.clear();
  vector<int> tmpfsr;	tmpfsr.clear(); 
  Int_t  npfPho			= data.GetInt("npfPho");
  float* phoEt 			= data.GetPtrFloat("pfPhoEt");
  float* phoEta 		= data.GetPtrFloat("pfPhoEta");
  float* phoPhi 		= data.GetPtrFloat("pfPhoPhi");
  //int*   pfPhoPhoIndex  = data.GetPtrInt("pfPhoPhoIndex");
  for(int i = 0 ; i < npfPho ; i++)
    {
      // if (i==HZgVar.phoID_) continue;
	
      if (HZgVar.vec_Z.M()<66.) continue;
      if (HZgVar.vec_Z.M()>89.) continue;
      if (phoEt[i]<1.5) continue;
      if (fabs(phoEta[i])>2.4) continue;
      //if (pfPhoPhoIndex[i]==HZgVar.phoID_) continue;
      TLorentzVector fsrpho;
      fsrpho.SetPtEtaPhiM(phoEt[i],phoEta[i],phoPhi[i],0.);
      if(fsrpho.DeltaR(HZgVar.vec_lep[lt])>0.15) continue;
      if (HZgVar.vec_pho.DeltaR(fsrpho)<0.1) continue;
      tmpfsr.push_back(i);
      fsrpt.push_back(fsrpho.DeltaR(HZgVar.vec_lep[lt]));
    }
  
  int siz = (int) tmpfsr.size();
  if(siz<1) HZgVar.afsrID_[lt] = -99;
  if (siz < 1) return;
  int ind[siz];
  TMath::Sort(siz, &fsrpt.front(), ind);
  vector<int> accepted;
  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(tmpfsr[ind[i]]);
    }
  HZgVar.afsrID_[lt] = accepted[siz-1];
}
