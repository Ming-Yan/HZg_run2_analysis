class storeSF
{
  TFile*fe_GSF, *fe_LowGSF, *fe_LowID, *fe_ID, *fe_trg1, *fe_trg2,*fe_dZ, *fm_trg1_09to12, *fm_trg1_0to09, *fm_trg1_12to21, *fm_trg1_21to24, *fm_trg2_0to09, *fm_trg2_09to12, *fm_trg2_12to21, *fm_trg2_21to24,*fg_ID,*fm_HZZ;
  TH2F *he_GSF,*he_LowGSF, *he_ID, *he_LowID, *he_dZ, *he_trg1, *he_trg2, *hg_ID, *gg_R9EB, *hm_ZZSF, *hm_ZZSFErr;
  TH1F *hm_trg1_0to09, *hm_trg1_09to12, *hm_trg1_12to21, *hm_trg1_21to24, *hm_trg2_0to09, *hm_trg2_09to12, *hm_trg2_12to21, *hm_trg2_21to24;
  Float_t gVeto[6],gVetoun[6],edZ,edZun;
 public:
  storeSF(){};
  ~storeSF()
    {
      
      delete fe_trg1;  delete fe_trg2;  // delete fe_dZ; 
      delete fe_LowGSF;  delete fe_GSF; delete fe_ID;
      delete fe_LowID;   delete fg_ID;  
      delete fm_trg1_0to09; delete fm_trg1_09to12; delete fm_trg1_12to21;delete fm_trg1_21to24; 
      delete fm_trg2_0to09; delete fm_trg2_09to12; delete fm_trg2_12to21; delete fm_trg2_21to24;
      delete fm_HZZ;	

    }; 
  void Setup16();
  void Setup17();
  void Setup18();
  void eleSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel);
  void muSF(TreeReader &data,HZgVariables &HZgvar, Int_t category, Int_t channel);
  void phoSF(TreeReader &data,HZgVariables &HZgvar, vector<float> &phoR9,int period);
};
void storeSF::Setup16()
{
  fe_trg1 = TFile::Open("external/Legacy16_trg1_egammaEffi.txt_EGM2D.root");
  fe_trg2 = TFile::Open("external/Legacy16_trg2_egammaEffi.txt_EGM2D.root");
  fe_dZ = TFile::Open("external/eleDz_Ele23_Ele12_vsAbsEta_NonDZ_DZ_Moriond17_SFs.root");
  fe_LowGSF = TFile::Open("external/EGM2D_BtoH_low_RecoSF_Legacy2016.root");
  fe_GSF = TFile::Open("external/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");
  fe_ID  = TFile::Open("external/Legacy16_egammaEffi.txt_EGM2D.root");
  fe_LowID  = TFile::Open("external/Legacy16_egammaEffi.txt_EGM2D.root");
  fg_ID  = TFile::Open("external/legacy16v2ID_phomvawp90_addlow.root");
  fm_trg2_0to09 = TFile::Open("external/80X_mutrgsf_Mu8Leg_Eta0to09.root");
  fm_trg2_09to12 = TFile::Open("external/80X_mutrgsf_Mu8Leg_Eta09to12.root");
  fm_trg2_12to21  = TFile::Open("external/80X_mutrgsf_Mu8Leg_Eta12to21.root");
  fm_trg2_21to24 = TFile::Open("external/80X_mutrgsf_Mu8Leg_Eta21to24.root");
  fm_trg1_0to09 = TFile::Open("external/80X_mutrgsf_Mu17Leg_Eta0to09.root");
  fm_trg1_09to12 = TFile::Open("external/80X_mutrgsf_Mu17Leg_Eta09to12.root");
  fm_trg1_12to21  = TFile::Open("external/80X_mutrgsf_Mu17Leg_Eta12to21.root");
  fm_trg1_21to24 = TFile::Open("external/80X_mutrgsf_Mu17Leg_Eta21to24.root");
  fm_HZZ = TFile::Open("external/final_HZZ_SF_2016_legacy_mupogsysts_newLoose_noTracking_1910.root");
  he_GSF = (TH2F*) fe_GSF->Get("EGamma_SF2D");
  he_LowGSF = (TH2F*) fe_LowGSF->Get("EGamma_SF2D");
  he_ID  = (TH2F*) fe_ID->Get("EGamma_SF2D");
  he_LowID  = (TH2F*) fe_LowID->Get("EGamma_SF2D");
  he_trg1= (TH2F*) fe_trg1->Get("EGamma_SF2D");
  he_trg2= (TH2F*) fe_trg2->Get("EGamma_SF2D");
  he_dZ= (TH2F*) fe_dZ->Get("hEta1_Eta2_SF");
  hg_ID  = (TH2F*) fg_ID->Get("EGamma_SF2D");
  hm_trg1_0to09  = (TH1F*) fm_trg1_0to09->Get("h1");
  hm_trg2_0to09  = (TH1F*) fm_trg2_0to09->Get("h1");
  hm_trg1_09to12  = (TH1F*) fm_trg1_09to12->Get("h1");
  hm_trg2_09to12  = (TH1F*) fm_trg2_09to12->Get("h1");
  hm_trg1_12to21  = (TH1F*) fm_trg1_12to21->Get("h1");
  hm_trg2_12to21  = (TH1F*) fm_trg2_12to21->Get("h1");
  hm_trg1_21to24  = (TH1F*) fm_trg1_21to24->Get("h1");
  hm_trg2_21to24  = (TH1F*) fm_trg2_21to24->Get("h1");
  hm_ZZSF = (TH2F*) fm_HZZ->Get("FINAL");
  hm_ZZSFErr = (TH2F*) fm_HZZ->Get("ERROR");
  //edZun =  he_dZ->GetBinError(he_dZ->FindBin(1.2,1.2));
  //edZ = he_dZ->GetBinContent(he_dZ->FindBin(1.2,1.2));
  edZun = 0.;
  edZ = 1.;
  
  gVeto[0] = 0.9875;//EE
  gVeto[1] = 0.9938;//EB
  gVetoun[0] = 0.0044;//EE
  gVetoun[1] = 0.0119;//EB
  /*fe_trg1->Close();fe_trg2->Close();fe_dZ->Close();fe_GSF->Close();fe_LowGSF->Close();fe_ID->Close();fe_LowID->Close();
   fg_ID->Close();fm_HZZ->Close();
   fm_trg1_0to09->Close();fm_trg1_09to12->Close();fm_trg1_12to21->Close();fm_trg1_21to24->Close();
   fm_trg2_0to09->Close();fm_trg2_09to12->Close();fm_trg2_12to21->Close();fm_trg2_21to24->Close();	  */
}
void storeSF::Setup17()//todo
{
  fe_trg1 = TFile::Open("external/17trg1_egammaEffi.txt_EGM2D.root");
  fe_trg2 = TFile::Open("external/17trg2_egammaEffi.txt_EGM2D.root");
  fe_LowGSF = TFile::Open("external/egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root");
  fe_dZ = TFile::Open("external/eleDz_Ele23_Ele12_vsAbsEta_NonDZ_DZ_Moriond17_SFs.root");
  fe_GSF = TFile::Open("external/egammaEffi.txt_EGM2D_run17BCDEF_passingRECO.root");
  fe_ID  = TFile::Open("external/17eleID_egammaEffi.txt_EGM2D.root");
  fe_LowID  = TFile::Open("external/17eleID_egammaEffi.txt_EGM2D.root");
  fg_ID  = TFile::Open("external/rereco17v2ID_phomvawp90_addlow.root");
  fm_trg2_0to09 = TFile::Open("external/94X_mutrgsf_Mu8Leg_Eta0to09.root");
  fm_trg2_09to12 = TFile::Open("external/94X_mutrgsf_Mu8Leg_Eta09to12.root");
  fm_trg2_12to21  = TFile::Open("external/94X_mutrgsf_Mu8Leg_Eta12to21.root");
  fm_trg2_21to24 = TFile::Open("external/94X_mutrgsf_Mu8Leg_Eta21to24.root");
  fm_trg1_0to09 = TFile::Open("external/94X_mutrgsf_Mu17Leg_Eta0to09.root");
  fm_trg1_09to12 = TFile::Open("external/94X_mutrgsf_Mu17Leg_Eta09to12.root");
  fm_trg1_12to21  = TFile::Open("external/94X_mutrgsf_Mu17Leg_Eta12to21.root");
  fm_trg1_21to24 = TFile::Open("external/94X_mutrgsf_Mu17Leg_Eta21to24.root");
  fm_HZZ = TFile::Open("external/final_HZZ_SF_2017_rereco_mupogsysts_3010.root");
  he_GSF = (TH2F*) fe_GSF->Get("EGamma_SF2D");
  he_LowGSF = (TH2F*) fe_LowGSF->Get("EGamma_SF2D");
  he_ID  = (TH2F*) fe_ID->Get("EGamma_SF2D");
  he_LowID  = (TH2F*) fe_LowID->Get("EGamma_SF2D");
  he_trg1= (TH2F*) fe_trg1->Get("EGamma_SF2D");
  he_trg2= (TH2F*) fe_trg2->Get("EGamma_SF2D");
  hg_ID  = (TH2F*) fg_ID->Get("EGamma_SF2D");
  hm_trg1_0to09  = (TH1F*) fm_trg1_0to09->Get("h1");
  hm_trg2_0to09  = (TH1F*) fm_trg2_0to09->Get("h1");
  hm_trg1_09to12  = (TH1F*) fm_trg1_09to12->Get("h1");
  hm_trg2_09to12  = (TH1F*) fm_trg2_09to12->Get("h1");
  hm_trg1_12to21  = (TH1F*) fm_trg1_12to21->Get("h1");
  hm_trg2_12to21  = (TH1F*) fm_trg2_12to21->Get("h1");
  hm_trg1_21to24  = (TH1F*) fm_trg1_21to24->Get("h1");
  hm_trg2_21to24  = (TH1F*) fm_trg2_21to24->Get("h1");
  hm_ZZSF = (TH2F*) fm_HZZ->Get("FINAL");
  hm_ZZSFErr = (TH2F*) fm_HZZ->Get("ERROR");
  edZ = 1.;
  edZun = 0.;
  gVeto[0] = 0.915;//EE
  gVeto[1] = 0.967;//EB
  gVetoun[0] = 0.0120;//EE
  gVetoun[1] = 0.0037;//EB
  // fe_trg1->Close();fe_trg2->Close();fe_dZ->Close();fe_GSF->Close();fe_LowGSF->Close();fe_ID->Close();fe_LowID->Close();
  // fg_ID->Close();fm_HZZ->Close();
  // fm_trg1_0to09->Close();fm_trg1_09to12->Close();fm_trg1_12to21->Close();fm_trg1_21to24->Close();
  // fm_trg2_0to09->Close();fm_trg2_09to12->Close();fm_trg2_12to21->Close();fm_trg2_21to24->Close();
	  
}
void storeSF::Setup18()//todo
{
  fe_trg1 = TFile::Open("external/18trg1_egammaEffi.txt_EGM2D.root");//tbd
  fe_trg2 = TFile::Open("external/18trg2_egammaEffi.txt_EGM2D.root");//tbd
  fe_dZ = TFile::Open("external/eleDz_Ele23_Ele12_vsAbsEta_NonDZ_DZ_Moriond17_SFs.root");
  fe_LowGSF = TFile::Open("external/egammaEffi.txt_EGM2D_updatedAll_18.root");
  fe_GSF = TFile::Open("external/egammaEffi.txt_EGM2D_updatedAll_18.root");
  fe_ID  = TFile::Open("external/18eleID_egammaEffi.txt_EGM2D.root");//tbd
  fe_LowID  = TFile::Open("external/18eleID_egammaEffi.txt_EGM2D.root");//tbd
  fg_ID  = TFile::Open("external/early18v2ID_phomvawp90_addlow.root");
  fm_trg2_0to09 = TFile::Open("external/sf_Mu8Leg_Eta0to09.root");//tbd
  fm_trg2_09to12 = TFile::Open("external/sf_Mu8Leg_Eta09to12.root");//tbd
  fm_trg2_12to21  = TFile::Open("external/sf_Mu8Leg_Eta12to21.root");//tbd
  fm_trg2_21to24 = TFile::Open("external/sf_Mu8Leg_Eta21to24.root");//tbd
  fm_trg1_0to09 = TFile::Open("external/sf_Mu17Leg_Eta0to09.root");//tbd
  fm_trg1_09to12 = TFile::Open("external/sf_Mu17Leg_Eta09to12.root");//tbd
  fm_trg1_12to21  = TFile::Open("external/sf_Mu17Leg_Eta12to21.root");//tbd
  fm_trg1_21to24 = TFile::Open("external/sf_Mu17Leg_Eta21to24.root");//tbd
  fm_HZZ = TFile::Open("external/final_HZZ_SF_2018_rereco_mupogsysts_3010.root");
  he_GSF = (TH2F*) fe_GSF->Get("EGamma_SF2D");
  he_LowGSF = (TH2F*) fe_LowGSF->Get("EGamma_SF2D");
  he_ID  = (TH2F*) fe_ID->Get("EGamma_SF2D");
  he_LowID  = (TH2F*) fe_LowID->Get("EGamma_SF2D");
  he_trg1= (TH2F*) fe_trg1->Get("EGamma_SF2D");
  he_trg2= (TH2F*) fe_trg2->Get("EGamma_SF2D");
  hg_ID  = (TH2F*) fg_ID->Get("EGamma_SF2D");
  hm_trg1_0to09  = (TH1F*) fm_trg1_0to09->Get("scale_factor");
  hm_trg2_0to09  = (TH1F*) fm_trg2_0to09->Get("scale_factor");
  hm_trg1_09to12  = (TH1F*) fm_trg1_09to12->Get("scale_factor");
  hm_trg2_09to12  = (TH1F*) fm_trg2_09to12->Get("scale_factor");
  hm_trg1_12to21  = (TH1F*) fm_trg1_12to21->Get("scale_factor");
  hm_trg2_12to21  = (TH1F*) fm_trg2_12to21->Get("scale_factor");
  hm_trg1_21to24  = (TH1F*) fm_trg1_21to24->Get("scale_factor");
  hm_trg2_21to24  = (TH1F*) fm_trg2_21to24->Get("scale_factor");
  hm_ZZSF = (TH2F*) fm_HZZ->Get("FINAL");
  hm_ZZSFErr = (TH2F*) fm_HZZ->Get("ERROR");
  edZ = 1.;
  edZun = 0.;
  gVeto[0] = 0.95461;//EE-0-30
  gVeto[1] = 0.987613;//EB-0-30
  gVeto[2] = 0.962451;//EE-30-60                                                                                  
  gVeto[3] = 0.98895;//EB-30-60
  gVeto[4] = 0.99791;//EE-60-200                                                                                 
  gVeto[5] = 1.00006;//EB-60-200
  gVetoun[0] = 0.00515085;//EE-0-30
  gVetoun[1] = 0.00275259;//EB-0-30
  gVetoun[2] = 0.00967545;//EE-30-60                                                       
  gVetoun[3] = 0.00937395;//EB-30-60
  gVetoun[4] = 0.00458169;//EE-60-200                                                         
  gVetoun[5] = 0.00307986;//EB-60-200

  // fe_trg1->Close();fe_trg2->Close();fe_dZ->Close();fe_GSF->Close();fe_LowGSF->Close();fe_ID->Close();fe_LowID->Close();
  // fg_ID->Close();fm_HZZ->Close();
  // fm_trg1_0to09->Close();fm_trg1_09to12->Close();fm_trg1_12to21->Close();fm_trg1_21to24->Close();
  // fm_trg2_0to09->Close();fm_trg2_09to12->Close();fm_trg2_12to21->Close();fm_trg2_21to24->Close();
    
}

void storeSF::phoSF(TreeReader &data,HZgVariables &HZgvar, vector<float> &phoR9,int period)
{
  float *phoSCEta = data.GetPtrFloat("phoSCEta");
  float *phoEt = data.GetPtrFloat("phoCalibEt");
  
  HZgvar.SFgID_ = hg_ID->GetBinContent(hg_ID->FindBin(phoSCEta[HZgvar.phoID_], phoEt[HZgvar.phoID_]));
  HZgvar.UNgID_ = hg_ID->GetBinError(hg_ID->FindBin(phoSCEta[HZgvar.phoID_], phoEt[HZgvar.phoID_]));
  HZgvar.SFgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVeto[0]:gVeto[1];
  HZgvar.UNgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVetoun[0]:gVetoun[1];
  if(period==18)
    {
      if(phoEt[HZgvar.phoID_]<30)
	{
	  HZgvar.SFgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVeto[0]:gVeto[1];
	  HZgvar.UNgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVetoun[0]:gVetoun[1];
	}
      else if(phoEt[HZgvar.phoID_]<60)
	{
	  HZgvar.SFgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVeto[2]:gVeto[3];
	  HZgvar.UNgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVetoun[2]:gVetoun[3];
	}
      else 
        {
          HZgvar.SFgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVeto[4]:gVeto[5];
          HZgvar.UNgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? gVetoun[4]:gVetoun[5];
        }
    }
  if(HZgvar.SFgID_==0||HZgvar.SFgVeto_==0)cout<<"phoSF ==0!!!"<<"ID: "<<HZgvar.SFgID_<<" veto: "<<HZgvar.SFgVeto_<<endl;
}	  
void storeSF::eleSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel)
{
  float *eleSCEta = data.GetPtrFloat("eleSCEta");
  //float *elePt = data.GetPtrFloat("eleCalibPt");
  float *muEta = data.GetPtrFloat("muEta");
  
  if(channel==0)
    {
	  
      for(Int_t j = 0; j < 2 ; j++)
	{
	  Float_t tmpElePt = (HZgvar.vec_lep[j].Pt()< 200) ? HZgvar.vec_lep[j].Pt(): 199;
	  HZgvar.SFGSF_[j] = he_GSF->GetBinContent(he_GSF->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	  HZgvar.UNGSF_[j] = he_GSF->GetBinError(he_GSF->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	  HZgvar.SFeID_[j] = he_ID->GetBinContent(he_ID->FindBin(fabs(eleSCEta[HZgvar.lepID_[j]]), tmpElePt));
	  HZgvar.UNeID_[j] = he_ID->GetBinError(he_ID->FindBin(fabs(eleSCEta[HZgvar.lepID_[j]]), tmpElePt));
	  if(tmpElePt<20)
	    {
	      HZgvar.SFGSF_[j] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.lepID_[j]],15));
	      HZgvar.UNGSF_[j] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.lepID_[j]],15));
	    }
	  HZgvar.UNedz_[j] = edZun;
	  HZgvar.SFedz_[j] = edZ;
	  if(j==0)
	    {
	      HZgvar.SFetrg_[j] = he_trg1->GetBinContent(he_trg1->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	      HZgvar.UNetrg_[j] = he_trg1->GetBinError(he_trg1->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	    }
	  else
    {
	      HZgvar.SFetrg_[j] = he_trg2->GetBinContent(he_trg2->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	      HZgvar.UNetrg_[j] = he_trg2->GetBinError(he_trg2->FindBin(eleSCEta[HZgvar.lepID_[j]], tmpElePt));
	    }
	}
    }
  if(HZgvar.cat<6||HZgvar.cat>9) HZgvar.SFGSF_[2] = HZgvar.SFeID_[2]  = HZgvar.SFmuID_[2] = HZgvar.SFmuTrk_[2] = 1.; //set the HZgvar.SFs for no lepton tag cat
  else
    {
      if(HZgvar.cat==6)
	{
	  Float_t tmpElePt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;

	  HZgvar.SFeID_[2] = he_ID->GetBinContent(he_ID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.UNeID_[2] = he_ID->GetBinError(he_ID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.SFGSF_[2] = he_GSF->GetBinContent(he_GSF->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.UNGSF_[2] = he_GSF->GetBinError(he_GSF->FindBin(eleSCEta[HZgvar.alep[0]],tmpElePt));
	  if(tmpElePt<20)
	    {
	      HZgvar.SFGSF_[2] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]],15));
	      HZgvar.UNGSF_[2] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]],15));
	    }
	  HZgvar.SFmuID_[2] = HZgvar.SFmuTrk_[2] = 1.;
	}
      // cat7 SFs
      else if(HZgvar.cat==7)
	{
	  Float_t tmpMuPt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;
	  HZgvar.SFmuID_[2] = hm_ZZSF->GetBinContent(hm_ZZSF->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.UNmuID_[2] = hm_ZZSFErr->GetBinContent(hm_ZZSFErr->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.SFeID_[2] = HZgvar.SFGSF_[2] = 1.;
	}
    }
  if(channel==0&&(HZgvar.SFetrg_[0]==0||HZgvar.SFetrg_[1]==0.||HZgvar.SFeID_[2]==0||HZgvar.SFeID_[1]==0||HZgvar.SFeID_[2]==0||HZgvar.SFGSF_[0]==0||HZgvar.SFGSF_[1]==0||HZgvar.SFGSF_[2]==0))cout<<"ELECTRON SFs is 0"<<endl;
  if(channel==0&&(HZgvar.SFetrg_[0]==0||HZgvar.SFetrg_[1]==0.||HZgvar.SFeID_[2]==0||HZgvar.SFeID_[1]==0||HZgvar.SFeID_[2]==0||HZgvar.SFGSF_[0]==0||HZgvar.SFGSF_[1]==0||HZgvar.SFGSF_[2]==0))cout<<HZgvar.SFetrg_[0]<<" "<<HZgvar.vec_lep[0].Pt()<<endl;
}
void storeSF::muSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel)
{
  float *muEta = data.GetPtrFloat("muEta");
  float *eleSCEta = data.GetPtrFloat("eleSCEta");
  Float_t tmpMuPt1 = (HZgvar.lepPt[0] < 200) ? HZgvar.lepPt[0] : 199;
  Float_t tmpMuPt2= (HZgvar.lepPt[1] < 200) ? HZgvar.lepPt[1] : 199;
  if(channel==1){
  if(tmpMuPt2<20)
    {
      if (fabs(muEta[HZgvar.lepID_[0]])<=0.9)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_0to09->GetBinError(hm_trg1_0to09->FindBin(tmpMuPt1));
	}
      if(fabs(muEta[HZgvar.lepID_[1]])<=0.9)
	{
	  HZgvar.SFmutrg_[1] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_0to09->GetBinError(hm_trg2_0to09->FindBin(tmpMuPt2));
	}
       if(fabs(muEta[HZgvar.lepID_[0]])>0.9&&fabs(muEta[HZgvar.lepID_[0]])<=1.2)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_09to12->GetBinError(hm_trg1_09to12->FindBin(tmpMuPt1));
	}
       if(fabs(muEta[HZgvar.lepID_[1]])>0.9&&fabs(muEta[HZgvar.lepID_[1]])<=1.2)
	{
	  HZgvar.SFmutrg_[1] = hm_trg2_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_09to12->GetBinError(hm_trg2_09to12->FindBin(tmpMuPt2));
	}
       if (fabs(muEta[HZgvar.lepID_[0]])>1.2&&fabs(muEta[HZgvar.lepID_[0]])<=2.1)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_12to21->GetBinError(hm_trg1_12to21->FindBin(tmpMuPt1));
	}
       if(fabs(muEta[HZgvar.lepID_[1]])>1.2&&fabs(muEta[HZgvar.lepID_[1]])<=2.1)
	 {
	  HZgvar.SFmutrg_[1] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_12to21->GetBinError(hm_trg2_12to21->FindBin(tmpMuPt2));
	 }
       if(fabs(muEta[HZgvar.lepID_[0]])>2.1&&fabs(muEta[HZgvar.lepID_[0]])<=2.4)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_21to24->GetBinError(hm_trg1_21to24->FindBin(tmpMuPt1));
	}
       if(fabs(muEta[HZgvar.lepID_[1]])>2.1&&fabs(muEta[HZgvar.lepID_[1]])<=2.4){
	 HZgvar.SFmutrg_[1] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt2));
	 HZgvar.UNmutrg_[1] = hm_trg2_21to24->GetBinError(hm_trg2_21to24->FindBin(tmpMuPt2));
       }
    }
  else 
    {
      float tmpsf1 = 0;
      float tmpsf2 = 0;
				
      if (fabs(muEta[HZgvar.lepID_[0]])<=0.9) HZgvar.SFmutrg_[0] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt1));
      if (fabs(muEta[HZgvar.lepID_[1]])<=0.9)HZgvar.SFmutrg_[1] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[0]])>0.9&&fabs(muEta[HZgvar.lepID_[0]])<=1.2))HZgvar.SFmutrg_[0] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt1));
      if(fabs(muEta[HZgvar.lepID_[1]])>0.9&&fabs(muEta[HZgvar.lepID_[1]])<=1.2) HZgvar.SFmutrg_[1] = hm_trg2_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[0]])>1.2&&fabs(muEta[HZgvar.lepID_[0]])<=2.1))HZgvar.SFmutrg_[0] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt1));
      if ((fabs(muEta[HZgvar.lepID_[0]])>2.1&&fabs(muEta[HZgvar.lepID_[0]])<=2.4))HZgvar.SFmutrg_[0] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt1));
      if(fabs(muEta[HZgvar.lepID_[1]])>1.2&&fabs(muEta[HZgvar.lepID_[1]])<=2.1) HZgvar.SFmutrg_[1] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[1]])>2.1&&fabs(muEta[HZgvar.lepID_[1]])<=2.4)) HZgvar.SFmutrg_[1] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt2));
  
      tmpsf1 = HZgvar.SFmutrg_[0];
      tmpsf2 = HZgvar.SFmutrg_[1];
      //another set
      if (fabs(muEta[HZgvar.lepID_[0]])<=0.9) HZgvar.SFmutrg_[0] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt1));
      if (fabs(muEta[HZgvar.lepID_[1]])<=0.9)HZgvar.SFmutrg_[1] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[0]])>0.9&&fabs(muEta[HZgvar.lepID_[0]])<=1.2))HZgvar.SFmutrg_[0] = hm_trg2_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt1));
      if(fabs(muEta[HZgvar.lepID_[1]])>0.9&&fabs(muEta[HZgvar.lepID_[1]])<=1.2) HZgvar.SFmutrg_[1] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[0]])>1.2&&fabs(muEta[HZgvar.lepID_[0]])<=2.1))HZgvar.SFmutrg_[0] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt1));
      if ((fabs(muEta[HZgvar.lepID_[0]])>2.1&&fabs(muEta[HZgvar.lepID_[0]])<=2.4))HZgvar.SFmutrg_[0] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt1));
      if(fabs(muEta[HZgvar.lepID_[1]])>1.2&&fabs(muEta[HZgvar.lepID_[1]])<=2.1) HZgvar.SFmutrg_[1] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt2));
      if ((fabs(muEta[HZgvar.lepID_[1]])>2.1&&fabs(muEta[HZgvar.lepID_[1]])<=2.4)) HZgvar.SFmutrg_[1] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt2));
      if(tmpsf1*tmpsf2>HZgvar.SFmutrg_[1]*HZgvar.SFmutrg_[0])
	{
	  HZgvar.SFmutrg_[0] = tmpsf1; HZgvar.SFmutrg_[1] = tmpsf2;
	}      
    }


  for(Int_t i = 0 ; i <2 ; i++)
    {
      Float_t tmpMuPt = (HZgvar.lepPt[i] < 200) ? HZgvar.lepPt[i] : 199;
      HZgvar.SFmuID_[i] = hm_ZZSF->GetBinContent(hm_ZZSF->FindBin(muEta[HZgvar.lepID_[i]],tmpMuPt));
      HZgvar.UNmuID_[i] = hm_ZZSFErr->GetBinContent(hm_ZZSFErr->FindBin(muEta[HZgvar.lepID_[i]],tmpMuPt));
    }
  }	     
  if(HZgvar.cat<6||HZgvar.cat>9) HZgvar.SFGSF_[2] = HZgvar.SFeID_[2]  = HZgvar.SFmuID_[2] = HZgvar.SFmuTrk_[2] = 1.; //set the HZgvar.SFs for no HZgvar.vec_lepton tag cat
  else
    {
      if(HZgvar.cat ==8)
	{
	  Float_t tmpMuPt = (HZgvar.alepPt< 200) ? HZgvar.alepPt : 199;
	  HZgvar.SFmuID_[2] = hm_ZZSF->GetBinContent(hm_ZZSF->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.UNmuID_[2] = hm_ZZSFErr->GetBinContent(hm_ZZSFErr->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.SFGSF_[2] = HZgvar.UNGSF_[2] = HZgvar.SFeID_[2] = HZgvar.UNeID_[2] =1.;
	}
      // cat9
      else if(HZgvar.cat==9)
	{
	  Float_t tmpElePt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;

	  HZgvar.SFeID_[2] = he_ID->GetBinContent(he_ID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.UNeID_[2] = he_ID->GetBinError(he_ID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.SFGSF_[2] = he_GSF->GetBinContent(he_GSF->FindBin(eleSCEta[HZgvar.alep[0]],tmpElePt));
	  HZgvar.UNGSF_[2] = he_GSF->GetBinError(he_GSF->FindBin(eleSCEta[HZgvar.alep[0]],tmpElePt));
	  if(tmpElePt<20)
	    {
	      HZgvar.SFGSF_[2] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]],15));
	      HZgvar.UNGSF_[2] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]],15));
	    }
	  HZgvar.SFmuID_[2] =  HZgvar.SFmuTrk_[2] = 1.;
	}
    }
  if(channel==1&&(HZgvar.SFmutrg_[0]==0||HZgvar.SFmutrg_[0]==0||HZgvar.SFmuID_[2]==0||HZgvar.SFmuID_[1]==0||HZgvar.SFmuID_[0]==0))cout<<"MUON SFs is 0"<<endl;
}
