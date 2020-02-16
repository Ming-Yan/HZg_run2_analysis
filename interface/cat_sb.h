// #include "../plugin/ElectronSelections1.h"
#include "../plugin/JetID_sb.h"

bool VBFtag(TreeReader &data, HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &tmpjetEn,bool dijetMVA)
{
  vector<int>jetID;
  jetID.clear();
  JetID(data,jetID,HZgVar,jetPt,tmpjetEn);

  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");

  Int_t nj =  0;

  int   tjet = -99;
  int   ljet = -99;
  TLorentzVector jet[2],dijet;
  if(jetID.size()<2) return 0;
  else{
    for(unsigned int i = 0; i<jetID.size(); i++)
      {
	jet[0].SetPtEtaPhiE(jetPt[jetID[i]],jetEta[jetID[i]],jetPhi[jetID[i]],tmpjetEn[jetID[i]]);
	for(unsigned int j = i+1; j < jetID.size(); j++)
	  {
	    if(jetID[j] == ljet) continue;
	    jet[1].SetPtEtaPhiE(jetPt[jetID[j]],jetEta[jetID[j]],jetPhi[jetID[j]],tmpjetEn[jetID[j]]);
	    dijet = jet[0]+jet[1];
		float Zeppen = HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
	    if(dijetMVA==false)
	      {
		if(dijet.M()<500)continue;
		if(fabs(jet[1].Eta()-jet[0].Eta()) < 3.5) continue;
		if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;
		if(fabs(Zeppen) > 2.5) continue;
	      }
	    else 
	      {
			  //purity ranking
			if(dijet.M()>=200&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4&&fabs(Zeppen) <= 2.5)HZgVar.jets.push_back(jetID[j]);
			else if(dijet.M()>=200&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)HZgVar.jets.push_back(jetID[j]);
			else if(fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)HZgVar.jets.push_back(jetID[j]);
			else if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)HZgVar.jets.push_back(jetID[j]);
			else  HZgVar.jets.push_back(jetID[j]);
			// if(fabs(jet[1].Eta()-jet[0].Eta())<1.0)continue;
			// if(dijet.M()<200)continue;
		//if(2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt()>80) continue;
		//if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;
		
	      }
	    ljet = jetID[i];
	    tjet = jetID[j];
	  }
      }
  }  
  if(ljet!=-99&&tjet!=-99)
    {
      HZgVar.VBFjet.push_back(jetPt[ljet] > jetPt[tjet] ? ljet : tjet);
      HZgVar.VBFjet.push_back(jetPt[ljet] > jetPt[tjet] ? tjet : ljet);
      HZgVar.cat = 5;
      HZgVar.isVBF = 1;
      return 1;
    }
  else return 0;
}    


bool leptag(TreeReader &data, Int_t channel, vector<int> &muID, vector<float> &muPt, HZgVariables &HZgVar)
{
  vector<int> eleID;
  float* elePt     = data.GetPtrFloat("eleCalibPt");
  float *eleEta    = data.GetPtrFloat("eleEta");
  float *elePhi    = data.GetPtrFloat("elePhi");

  float* muEta 		 = data.GetPtrFloat("muEta");
  float* muPhi 		 = data.GetPtrFloat("muPhi");
	
  AddEleSelections(data,98, eleID, HZgVar.lepPt[0],HZgVar.lepPt[1],channel);
  TLorentzVector alep;
  if(channel==0)
    {
      if(eleID.size()>0)
	{
	  HZgVar.alepPt = 0;//reset 
	  for(unsigned int i = 0; i < eleID.size(); i++)
	    {
	      // if(elePt[eleID[i]]<HZgVar.alepPt) continue;
	      alep.SetPtEtaPhiM(elePt[eleID[i]], eleEta[eleID[i]], elePhi[eleID[i]], 0.511*0.001);
	      if(alep.DeltaR(HZgVar.vec_pho)<0.4||alep.DeltaR(HZgVar.vec_lep[0])<0.4||alep.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
	      HZgVar.alepPt = elePt[eleID[i]];
	      HZgVar.alep.push_back(eleID[i]);
	      HZgVar.isLep = 1;
	      HZgVar.cat = 6;
	    }
	}

      // else if(muID.size()>0&&HZgVar.isLep!=1)
      if(muID.size()>0/* &&HZgVar.isLep!=1 */)
	{
			 
	  HZgVar.alepPt = 0;//reset 
	  for(unsigned int i = 0; i < muID.size(); i++)
	    {
	      alep.SetPtEtaPhiM(muPt[muID[i]], muEta[muID[i]], muPhi[muID[i]], 105.7*0.001);
	      if(alep.DeltaR(HZgVar.vec_pho)<0.4||alep.DeltaR(HZgVar.vec_lep[0])<0.4||alep.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
	      // if(muPt[muID[i]]<HZgVar.alepPt) continue;
	      HZgVar.alepPt = muPt[muID[i]];
	      HZgVar.alep.push_back(muID[i]);
	      HZgVar.isLep = 1;
	      HZgVar.cat = 7;
	    }
	}
    }

  if(channel==1)
    {
      if(muID.size()>0)
	{
	  HZgVar.alepPt = 0;//reset 
	  for(unsigned int i = 0; i < muID.size(); i++)
	    {
	      // if(muPt[muID[i]]<HZgVar.alepPt) continue;
	      alep.SetPtEtaPhiM(muPt[muID[i]], muEta[muID[i]], muPhi[muID[i]], 105.7*0.001);
	      if(alep.DeltaR(HZgVar.vec_pho)<0.4||alep.DeltaR(HZgVar.vec_lep[0])<0.4||alep.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
	      HZgVar.alepPt = muPt[muID[i]];
	      HZgVar.alep.push_back(muID[i]);
	      HZgVar.isLep = 1;
	      HZgVar.cat = 8;
	    }
	}
      // else if(eleID.size()>0&&HZgVar.isLep!=1)
      if(eleID.size()>0&&HZgVar.isLep!=1 )
	{
	  HZgVar.alepPt = 0;//reset 
	  for(unsigned int i = 0; i < eleID.size(); i++)
	    {
	      // if(elePt[eleID[i]]<HZgVar.alepPt) continue;
	      alep.SetPtEtaPhiM(elePt[eleID[i]], eleEta[eleID[i]], elePhi[eleID[i]],  0.511*0.001);
	      if(alep.DeltaR(HZgVar.vec_pho)<0.4||alep.DeltaR(HZgVar.vec_lep[0])<0.4||alep.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
		  
	      HZgVar.isLep = 1;
	      HZgVar.cat = 9;
	      HZgVar.alepPt = elePt[eleID[i]];
	      HZgVar.alep.push_back(eleID[i]);
	    }
	}
    }
  if(HZgVar.isLep==1) return 1;
  else return 0;
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
  eleID.clear();
}
bool dbtag (TreeReader &data,HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &tmpjetEn)
{
  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Float_t*	jetBtag		=	data.GetPtrFloat("jetCSV2BJetTags");

  TLorentzVector dbjet[2];
  int nbjets = 0;
  int tmpjetid[2];
  float tmppt[2];
  tmpjetid[0] = tmpjetid[1] = -99;
  tmppt[0] = tmppt[1] = 0.;
  for(int i = 0; i<nJet; i++)
    {
      if(jetPt[i] < 25.) continue;
      if(fabs(jetEta[i])>2.4) continue;
      if(jetBtag[i]<0.8484) continue;
      dbjet[0].SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
      tmpjetid[0] = i;
      if(fabs(dbjet[0].DeltaR(HZgVar.vec_pho)) < 0.4||fabs(dbjet[0].DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(dbjet[0].DeltaR(HZgVar.vec_lep[1])) < 0.4) continue;
      for(int j = i+1; j < nJet; j++)
	{
	  if(jetPt[j] < 25.) continue;
	  if(fabs(jetEta[j])>2.4) continue;
	  if(jetBtag[j]<0.8484) continue;
	  if(j == tmpjetid[0]) continue;
	  dbjet[1].SetPtEtaPhiE(jetPt[j],jetEta[j],jetPhi[j],tmpjetEn[j]);
	  if(fabs(dbjet[1].DeltaR(HZgVar.vec_pho)) < 0.4||fabs(dbjet[1].DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(dbjet[1].DeltaR(HZgVar.vec_lep[1])) < 0.4 || fabs(dbjet[1].DeltaR(dbjet[0]))<0.4)continue;
	  tmpjetid[1] = j;
	}
    }
  if(tmpjetid[0]!=-99&&tmpjetid[1]!=-99)
    {
      HZgVar.dbjet.push_back((tmpjetEn[0]>tmpjetEn[1])? tmpjetid[0]:tmpjetid[1]);
      HZgVar.dbjet.push_back((tmpjetEn[0]>tmpjetEn[1])? tmpjetid[1]:tmpjetid[0]);
      return 1;
    }
  else return 0;
}
bool btag(TreeReader &data, HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &tmpjetEn)
{
  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Float_t*	jetBtag		=	data.GetPtrFloat("jetCSV2BJetTags");
  TLorentzVector bjet;
  float bjetPt =0.;
  for(int i = 0 ; i <nJet ; i++)
    {
      if(jetPt[i] < 25.) continue;
      if(fabs(jetEta[i])>2.4) continue;
      if(bjetPt > jetPt[i]) continue;
      bjet.SetPtEtaPhiE(jetPt[i], jetEta[i], jetPhi[i], tmpjetEn[i]);
      if(bjet.DeltaR(HZgVar.vec_pho) < 0.4 || bjet.DeltaR(HZgVar.vec_lep[0])<0.4||bjet.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
      if (jetBtag[i]<0.8484) continue;
      bjetPt = jetPt[i];
      HZgVar.bjet.push_back(i);
      HZgVar.cat = 11;
    }	
  if(HZgVar.cat==11) return 1;
  else return 0;
}
bool boosttag(TreeReader &data,HZgVariables &HZgVar)
{
  if(HZgVar.vec_higgs.Pt()>=60.)
    {
      HZgVar.cat = 10;
      return 1;
    }
  else return 0;
}
int inclusive(TreeReader &data, Int_t channel, vector<float> &gR9_, HZgVariables &HZgVar)
{
  float* phoSCEta = data.GetPtrFloat("phoSCEta");
  float* eleSCEta = data.GetPtrFloat("eleSCEta");
  float* muEta 	 = data.GetPtrFloat("muEta");
	

  //electron channel
  if(channel==0)
    {
      if(fabs(phoSCEta[HZgVar.phoID_]) > 0 && fabs(phoSCEta[HZgVar.phoID_]) <= 1.4442)
        {
	  if(fabs(eleSCEta[HZgVar.lepID_[0]]) > 0 &&fabs(eleSCEta[HZgVar.lepID_[1]]) > 0 &&fabs(eleSCEta[HZgVar.lepID_[0]]) <= 1.4442 & fabs(eleSCEta[HZgVar.lepID_[1]]) <= 1.4442)
	    {
	      if(gR9_[0] > 0.94)return 1;
	      else return 2;
	    }//electron in EB
	  else if ((fabs(eleSCEta[HZgVar.lepID_[0]]) > 1.4442 &&fabs(eleSCEta[HZgVar.lepID_[0]] <= 2.5))||(fabs(eleSCEta[HZgVar.lepID_[1]]) > 1.4442 && fabs(eleSCEta[HZgVar.lepID_[1]]) <= 2.5)) return 3;
        }//gSCEta in EB
      else if(fabs(phoSCEta[HZgVar.phoID_]) <= 2.5&&fabs(phoSCEta[HZgVar.phoID_]) > 1.566)
        {
	  if(fabs(eleSCEta[HZgVar.lepID_[0]]) > 0 && fabs(eleSCEta[HZgVar.lepID_[1]]) > 0 &&fabs(eleSCEta[HZgVar.lepID_[0]]) <= 2.5 && fabs(eleSCEta[HZgVar.lepID_[1]]) <= 2.5)return 4;
        }//gSCEta in EE
    }
  //muon channel
  if(channel==1)
    {
      if(fabs(phoSCEta[HZgVar.phoID_]) > 0 && fabs(phoSCEta[HZgVar.phoID_]) <= 1.4442)
        {
	  if(fabs(muEta[HZgVar.lepID_[0]]) > 0 &&fabs(muEta[HZgVar.lepID_[1]]) > 0 &&fabs(muEta[HZgVar.lepID_[0]]) <= 2.1 & fabs(muEta[HZgVar.lepID_[1]]) <= 2.1)
            {
	      if(fabs(muEta[HZgVar.lepID_[0]]) <= 0.9 || fabs(muEta[HZgVar.lepID_[1]]) <=  0.9)
                {
		  if(gR9_[0] > 0.94) return 1;
		  else return 2;
                }//one muon <0.9
            }//both muon <2.1

	  if ((fabs(muEta[HZgVar.lepID_[0]]) > 0.9 &&fabs(muEta[HZgVar.lepID_[1]]) > 0.9)||((fabs(muEta[HZgVar.lepID_[0]]) > 2.1 &&fabs(muEta[HZgVar.lepID_[0]]) <= 2.4)||(fabs(muEta[HZgVar.lepID_[1]]) > 2.1 &&fabs(muEta[HZgVar.lepID_[1]]) <= 2.4)))return 3;
        }//gSCEta in EB
      else if(fabs(phoSCEta[HZgVar.phoID_]) <= 2.5&&fabs(phoSCEta[HZgVar.phoID_]) > 1.566)
        {
	  if(fabs(muEta[HZgVar.lepID_[0]]) > 0 && fabs(muEta[HZgVar.lepID_[1]]) > 0 && fabs(muEta[HZgVar.lepID_[0]]) <= 2.4 &&fabs(muEta[HZgVar.lepID_[1]]) <=  2.4) return 4;
        }// photon in EE
    }//muon channel end
}

int cat_limit(Int_t channel, float gR9_,float phoSCEta, float lepEta0, float lepEta1, float mllgpt)
{
  if (mllgpt>60.) return 10;
  //electron channel
  if(channel==0)
    {
      if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442)
        {
	  if(fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 1.4442 & fabs(lepEta1) <= 1.4442)
	    {
	      if(gR9_ > 0.94)return 1;
	      else return 2;
	    }//electron in EB
	  else if ((fabs(lepEta0) > 1.4442 &&fabs(lepEta0 <= 2.5))||(fabs(lepEta1) > 1.4442 && fabs(lepEta1) <= 2.5)) return 3;
        }//gSCEta in EB
      else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)
        {
	  if(fabs(lepEta0) > 0 && fabs(lepEta1) > 0 &&fabs(lepEta0) <= 2.5 && fabs(lepEta1) <= 2.5)return 4;
        }//gSCEta in EE
    }
  //muon channel
  if(channel==1)
    {
      if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442)
        {
	  if(fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 2.1 & fabs(lepEta1) <= 2.1)
            {
	      if(fabs(lepEta0) <= 0.9 || fabs(lepEta1) <=  0.9)
                {
		  if(gR9_ > 0.94) return 1;
		  else return 2;
                }//one muon <0.9
            }//both muon <2.1

	  if ((fabs(lepEta0) > 0.9 &&fabs(lepEta1) > 0.9)||((fabs(lepEta0) > 2.1 &&fabs(lepEta0) <= 2.4)||(fabs(lepEta1) > 2.1 &&fabs(lepEta1) <= 2.4)))return 3;
        }//gSCEta in EB
      else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)
        {
	  if(fabs(lepEta0) > 0 && fabs(lepEta1) > 0 && fabs(lepEta0) <= 2.4 &&fabs(lepEta1) <=  2.4) return 4;
        }// photon in EE
    }//muon channel end
}
