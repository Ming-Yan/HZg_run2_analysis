class storeSF
{
  TFile*fe_GSF, *fe_LowGSF, *fe_LowID, *fe_ID, *fe_trg1, *fe_trg2,*fe_dZ, *fm_trg1_09to12, *fm_trg1_0to09, *fm_trg1_12to21, *fm_trg1_21to24, *fm_trg2_0to09, *fm_trg2_09to12, *fm_trg2_12to21, *fm_trg2_21to24,*fg_ID,*fm_HZZ;
  TH2F *he_GSF,*he_LowGSF, *he_ID, *he_LowID, *he_dZ, *he_trg1, *he_trg2, *hg_ID, *gg_R9EB, *hm_ZZSF, *hm_ZZSFErr;
  TH1F *hm_trg1_0to09, *hm_trg1_09to12, *hm_trg1_12to21, *hm_trg1_21to24, *hm_trg2_0to09, *hm_trg2_09to12, *hm_trg2_12to21, *hm_trg2_21to24;
  
 public:
  storeSF(){};
  ~storeSF()
    {
      delete fe_trg1;  delete fe_trg2;  delete fe_dZ; delete fe_LowGSF;  delete fe_GSF; delete fe_ID;
      delete fe_LowID;   delete fg_ID;  
      delete fm_trg1_0to09; delete fm_trg1_09to12; delete fm_trg1_12to21;delete fm_trg1_21to24; 
      delete fm_trg2_0to09; delete fm_trg2_09to12; delete fm_trg2_12to21; delete fm_trg2_21to24;
      delete fm_HZZ;	
    }; 
  void Setup();
  void eleSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel);
  void muSF(TreeReader &data,HZgVariables &HZgvar, Int_t category, Int_t channel);
  void phoSF(TreeReader &data,HZgVariables &HZgvar, vector<float> &phoR9);
};
void storeSF::Setup()
{
	  fe_trg1 = TFile::Open("external/SFs_Leg1_Ele23_HZZSelection_Tag35.root");
      fe_trg2 = TFile::Open("external/SFs_NoRefit.root");
      fe_dZ = TFile::Open("external/eleDz_Ele23_Ele12_vsAbsEta_NonDZ_DZ_Moriond17_SFs.root");
      fe_LowGSF = TFile::Open("external/eleReco_HZZ_Moriond17_SFs.root");
      fe_GSF = TFile::Open("external/eleReco_Moriond17_SFs.root");
      fe_ID  = TFile::Open("external/eleMVA_WP90_Moriond17_SFs.root");
      fe_LowID  = TFile::Open("external/eleSelectionSF_HZZ_Moriond17.root");
      fg_ID  = TFile::Open("external/phoMVA_WP90_Moriond17_SFs.root");
      fm_trg2_0to09 = TFile::Open("external/sf_Mu8Leg_Eta0to09.root");
      fm_trg2_09to12 = TFile::Open("external/sf_Mu8Leg_Eta09to12.root");
      fm_trg2_12to21  = TFile::Open("external/sf_Mu8Leg_Eta12to21.root");
      fm_trg2_21to24 = TFile::Open("external/sf_Mu8Leg_Eta21to24.root");
      fm_trg1_0to09 = TFile::Open("external/sf_Mu17Leg_Eta0to09.root");
      fm_trg1_09to12 = TFile::Open("external/sf_Mu17Leg_Eta09to12.root");
      fm_trg1_12to21  = TFile::Open("external/sf_Mu17Leg_Eta12to21.root");
      fm_trg1_21to24 = TFile::Open("external/sf_Mu17Leg_Eta21to24.root");
      fm_HZZ = TFile::Open("external/muSelectionAndRecoSF_HZZ_Moriond17.root");
      he_GSF = (TH2F*) fe_GSF->Get("EGamma_SF2D");
      he_LowGSF = (TH2F*) fe_LowGSF->Get("EGamma_SF2D");
      he_ID  = (TH2F*) fe_ID->Get("EGamma_SF2D");
      he_LowID  = (TH2F*) fe_LowID->Get("EGamma_SF2D");
      he_trg1= (TH2F*) fe_trg1->Get("EGamma_SF2D");
      he_trg2= (TH2F*) fe_trg2->Get("EGamma_SF2D");
      he_dZ= (TH2F*) fe_dZ->Get("hEta1_Eta2_SF");
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
	  // fe_trg1->Close();fe_trg2->Close();fe_dZ->Close();fe_GSF->Close();fe_LowGSF->Close();fe_ID->Close();fe_LowID->Close();
	  // fg_ID->Close();fm_HZZ->Close();
	  // fm_trg1_0to09->Close();fm_trg1_09to12->Close();fm_trg1_12to21->Close();fm_trg1_21to24->Close();
	  // fm_trg2_0to09->Close();fm_trg2_09to12->Close();fm_trg2_12to21->Close();fm_trg2_21to24->Close();
	  
}
void storeSF::phoSF(TreeReader &data,HZgVariables &HZgvar, vector<float> &phoR9)
{
  float *phoSCEta = data.GetPtrFloat("phoSCEta");
  float *phoEt = data.GetPtrFloat("phoEt");
  
  HZgvar.SFgID_ = hg_ID->GetBinContent(hg_ID->FindBin(phoSCEta[HZgvar.phoID_], phoEt[HZgvar.phoID_]));
  HZgvar.UNgID_ = hg_ID->GetBinError(hg_ID->FindBin(phoSCEta[HZgvar.phoID_], phoEt[HZgvar.phoID_]));
  HZgvar.SFgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? 0.9875:0.9938;
  HZgvar.UNgVeto_ = (fabs(phoSCEta[HZgvar.phoID_]) > 1.49) ? 0.0044:0.0119;
}	  
void storeSF::eleSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel)
{
  float *eleSCEta = data.GetPtrFloat("eleSCEta");
  float *elePt = data.GetPtrFloat("elePt");
  float *muEta = data.GetPtrFloat("muEta");
  
  if(channel==0)
  {
	  
    for(Int_t j = 0; j < 2 ; j++)
      {
	HZgvar.SFGSF_[j] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.lepID_[j]], 50));
	HZgvar.UNGSF_[j] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.lepID_[j]], 50));
	Float_t tmpElePt = (elePt[HZgvar.lepID_[j]]< 200) ? elePt[HZgvar.lepID_[j]]: 199;
	HZgvar.SFeID_[j] = he_LowID->GetBinContent(he_LowID->FindBin(fabs(eleSCEta[HZgvar.lepID_[j]]), tmpElePt));
	HZgvar.UNeID_[j] = he_LowID->GetBinError(he_LowID->FindBin(fabs(eleSCEta[HZgvar.lepID_[j]]), tmpElePt));
	HZgvar.UNedz_[j] = he_dZ->GetBinError(he_dZ->FindBin(1.2,1.2));
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
    HZgvar.totSF = HZgvar.SFGSF_[0]*HZgvar.SFGSF_[1]*HZgvar.SFetrg_[0]*HZgvar.SFetrg_[1]*HZgvar.SFeID_[0]*HZgvar.SFeID_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_;	
  }
  if(HZgvar.cat<6||HZgvar.cat>9) HZgvar.SFGSF_[2] = HZgvar.SFeID_[2]  = HZgvar.SFmuID_[2] = HZgvar.SFmuTrk_[2] = 1.; //set the HZgvar.SFs for no lepton tag cat
  else
    {
      if(HZgvar.cat==6)
	{
	  Float_t tmpElePt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;

	  HZgvar.SFeID_[2] = he_LowID->GetBinContent(he_LowID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.UNeID_[2] = he_LowID->GetBinError(he_LowID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.SFGSF_[2] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]], 50));
	  HZgvar.UNGSF_[2] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]], 50));
	  HZgvar.SFmuID_[2] = HZgvar.SFmuTrk_[2] = 1.;
	}
      // cat7 SFs
      else
	{
	  Float_t tmpMuPt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;
	  HZgvar.SFmuID_[2] = hm_ZZSF->GetBinContent(hm_ZZSF->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.UNmuID_[2] = hm_ZZSFErr->GetBinContent(hm_ZZSFErr->FindBin(muEta[HZgvar.alep[0]],tmpMuPt));
	  HZgvar.SFeID_[2] = HZgvar.SFGSF_[2] = 1.;
	}
    }
}
void storeSF::muSF(TreeReader &data,HZgVariables &HZgvar, Int_t category,Int_t channel)
{
  float *muEta = data.GetPtrFloat("muEta");
  float *eleSCEta = data.GetPtrFloat("eleSCEta");
  Float_t tmpMuPt1 = (HZgvar.vec_lep[0].Pt() < 200) ? HZgvar.vec_lep[0].Pt() : 199;
  Float_t tmpMuPt2= (HZgvar.vec_lep[1].Pt() < 200) ? HZgvar.vec_lep[1].Pt() : 199;
  if(HZgvar.vec_lep[1].Pt()<20)
    {
				
      if (fabs(HZgvar.vec_lep[0].Eta())<=0.9||fabs(HZgvar.vec_lep[1].Eta())<=0.9)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_0to09->GetBinError(hm_trg1_0to09->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_0to09->GetBinError(hm_trg2_0to09->FindBin(tmpMuPt2));
	}
      else if((fabs(HZgvar.vec_lep[0].Eta())>0.9&&fabs(HZgvar.vec_lep[0].Eta())<=1.2)||(fabs(HZgvar.vec_lep[1].Eta())>0.9&&fabs(HZgvar.vec_lep[1].Eta())<=1.2))
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_09to12->GetBinError(hm_trg1_09to12->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_09to12->GetBinError(hm_trg2_09to12->FindBin(tmpMuPt2));
	}
      else if ((fabs(HZgvar.vec_lep[0].Eta())>1.2&&fabs(HZgvar.vec_lep[0].Eta())<=2.1)||(fabs(HZgvar.vec_lep[1].Eta())>1.2&&fabs(HZgvar.vec_lep[1].Eta())<=2.1))
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_12to21->GetBinError(hm_trg1_12to21->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_12to21->GetBinError(hm_trg2_12to21->FindBin(tmpMuPt2));
	}
      else
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt1));
	  HZgvar.UNmutrg_[0] = hm_trg1_21to24->GetBinError(hm_trg1_21to24->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt2));
	  HZgvar.UNmutrg_[1] = hm_trg2_21to24->GetBinError(hm_trg2_21to24->FindBin(tmpMuPt2));
	}
    }
  else 
    {
      float tmpsf1 = 0;
      float tmpsf2 = 0;
				
      if (fabs(HZgvar.vec_lep[0].Eta())<=0.9||fabs(HZgvar.vec_lep[1].Eta())<=0.9)
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt2));
	}
      else if ((fabs(HZgvar.vec_lep[0].Eta())>0.9&&fabs(HZgvar.vec_lep[0].Eta())<=1.2)||(fabs(HZgvar.vec_lep[1].Eta())>0.9&&fabs(HZgvar.vec_lep[1].Eta())<=1.2))
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt2));
	}
      else if ((fabs(HZgvar.vec_lep[0].Eta())>1.2&&fabs(HZgvar.vec_lep[0].Eta())<=2.1)||(fabs(HZgvar.vec_lep[1].Eta())>1.2&&fabs(HZgvar.vec_lep[1].Eta())<=2.1))
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt2));
	}
      else
	{
	  HZgvar.SFmutrg_[0] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt2));
	}
      tmpsf1 = HZgvar.SFmutrg_[0];
      tmpsf2 = HZgvar.SFmutrg_[1];
      //another set
      if (fabs(HZgvar.vec_lep[0].Eta())<=0.9||fabs(HZgvar.vec_lep[1].Eta())<=0.9)
	{
	  HZgvar.SFmutrg_[0] = hm_trg2_0to09->GetBinContent(hm_trg2_0to09->FindBin(tmpMuPt1));
	  HZgvar.SFmutrg_[1] = hm_trg1_0to09->GetBinContent(hm_trg1_0to09->FindBin(tmpMuPt2));
	}
      else if ((fabs(HZgvar.vec_lep[0].Eta())>0.9&&fabs(HZgvar.vec_lep[0].Eta())<=1.2)||(fabs(HZgvar.vec_lep[1].Eta())>0.9&&fabs(HZgvar.vec_lep[1].Eta())<=1.2))
	{
	  HZgvar.SFmutrg_[1] = hm_trg1_09to12->GetBinContent(hm_trg1_09to12->FindBin(tmpMuPt2));
	  HZgvar.SFmutrg_[0] = hm_trg1_09to12->GetBinContent(hm_trg2_09to12->FindBin(tmpMuPt1));
	}
      else if((fabs(HZgvar.vec_lep[0].Eta())>1.2&&fabs(HZgvar.vec_lep[0].Eta())<=2.1)||(fabs(HZgvar.vec_lep[1].Eta())>1.2&&fabs(HZgvar.vec_lep[1].Eta())<=2.1))
	{
	  HZgvar.SFmutrg_[1] = hm_trg1_12to21->GetBinContent(hm_trg1_12to21->FindBin(tmpMuPt2));
	  HZgvar.SFmutrg_[0] = hm_trg2_12to21->GetBinContent(hm_trg2_12to21->FindBin(tmpMuPt1));
	}
      else
	{
	  HZgvar.SFmutrg_[1] = hm_trg1_21to24->GetBinContent(hm_trg1_21to24->FindBin(tmpMuPt2));
	  HZgvar.SFmutrg_[0] = hm_trg2_21to24->GetBinContent(hm_trg2_21to24->FindBin(tmpMuPt1));
	}
      if(tmpsf1*tmpsf2>HZgvar.SFmutrg_[1]*HZgvar.SFmutrg_[0])
	{
	  HZgvar.SFmutrg_[0] = tmpsf1; HZgvar.SFmutrg_[1] = tmpsf2;
	}
    }
  for(Int_t i = 0 ; i <2 ; i++)
    {
      Float_t tmpMuPt = (HZgvar.vec_lep[0].Pt() < 200) ? HZgvar.vec_lep[i].Pt() : 199;
      HZgvar.SFmuID_[i] = hm_ZZSF->GetBinContent(hm_ZZSF->FindBin(HZgvar.vec_lep[i].Eta(),tmpMuPt));
      HZgvar.UNmuID_[i] = hm_ZZSFErr->GetBinContent(hm_ZZSFErr->FindBin(HZgvar.vec_lep[i].Eta(),tmpMuPt));
    }
  HZgvar.totSF = HZgvar.SFmuID_[0]*HZgvar.SFmuID_[1]*HZgvar.SFmutrg_[0]*HZgvar.SFmutrg_[1]*HZgvar.SFgVeto_*HZgvar.SFgID_;	 
	     
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
      else
	{
	  Float_t tmpElePt = (HZgvar.alepPt < 200) ? HZgvar.alepPt : 199;

	  HZgvar.SFeID_[2] = he_LowID->GetBinContent(he_LowID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.UNeID_[2] = he_LowID->GetBinError(he_LowID->FindBin(eleSCEta[HZgvar.alep[0]], tmpElePt));
	  HZgvar.SFGSF_[2] = he_LowGSF->GetBinContent(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]], 50));
	  HZgvar.UNGSF_[2] = he_LowGSF->GetBinError(he_LowGSF->FindBin(eleSCEta[HZgvar.alep[0]], 50));
	  HZgvar.SFmuID_[2] =  HZgvar.SFmuTrk_[2] = 1.;
	}
    }
}
