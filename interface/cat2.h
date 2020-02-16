// #include "../plugin/ElectronSelections1.h"
#include "../plugin/JetID2.h"

bool VBFtag(TreeReader &data, HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &tmpjetEn,bool dijetMVA, int period)
{
  vector<int>jetID;
  jetID.clear();
  if(period==16||period==161)JetID16(data,jetID,HZgVar,jetPt,tmpjetEn);
  else if(period==17)JetID17(data,jetID,HZgVar,jetPt,tmpjetEn);
  else if(period==18)JetID18(data,jetID,HZgVar,jetPt,tmpjetEn);

  Int_t nJet = data.GetInt("nJet");
  float *jetEta = data.GetPtrFloat("jetEta");
  float *jetPhi = data.GetPtrFloat("jetPhi");
  Long64_t event = data.GetLong64("event");
  Int_t nj =  0;

  int   tjet = -99;
  int   ljet = -99;
  float  tmpjetpt1=0.,tmpjetpt2=0.;
  TLorentzVector jet[2],dijet;
  float tmpdijetm = 0.;
  if(jetID.size()<2) return 0;
  else{
    for(unsigned int i = 0; i<jetID.size(); i++)
      {
	
	jet[0].SetPtEtaPhiE(jetPt[jetID[i]],jetEta[jetID[i]],jetPhi[jetID[i]],tmpjetEn[jetID[i]]);

          if(jet[0].Pt()<30.) continue;
	for(unsigned int j = i+1; j < jetID.size(); j++)
	  {
         
	    if(jetID[j] == ljet) continue;

	    jet[1].SetPtEtaPhiE(jetPt[jetID[j]],jetEta[jetID[j]],jetPhi[jetID[j]],tmpjetEn[jetID[j]]);
	    if(event==12)cout<<jet[1].Pt()<<endl;
           if(jet[1].Pt()<30.) continue;
	   if(event==12)cout<<"both greater than30"<<endl;
	   dijet = jet[0]+jet[1];
	    float Zeppen = HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
	    if(dijetMVA==false)
	      {
		    if(dijet.M()<500)continue;
		if(fabs(jet[1].Eta()-jet[0].Eta()) < 3.5) continue;
		if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;		
		if(fabs(Zeppen) > 2.5) continue;
		if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
		if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
	      }
	    else 
	      {
		//purity ranking
		/*if(dijet.M()>=500&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4&&fabs(Zeppen) <= 2.5)
		  {
		    //HZgVar.jets.push_back(jetID[j])
		    //if((dijet.M())>tmpdijetm){tmpdijetm=dijet.M()+fabs(jet[1].Eta()-jet[0].Eta());ljet=jetID[i];tjet=jetID[j];}		     
		    if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
		    if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
		    }
		/*
		else if(dijet.M()>=500&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
		  {
		    if(dijet.M()+500*fabs(jet[1].Eta()-jet[0].Eta())>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
		}
		else if(fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
		  {
		    HZgVar.jets.push_back(jetID[j]);
		    if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
      }

		else if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
		  {
		    HZgVar.jets.push_back(jetID[j]);
		    if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}		   
		    }*/
		//else 
		//if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
		//else 
		//{
		if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
		if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
		    //		  }
		// if(fabs(jet[1].Eta()-jet[0].Eta())<1.0)continue;
		// if(dijet.M()<200)continue;
		//if(2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt()>80) continue;
		//if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;
		
	      }
		
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

bool VBFtag_sb(TreeReader &data, HZgVariables &HZgVar, vector<float> &jetPt, vector<float> &tmpjetEn,bool dijetMVA, int period)
{
    vector<int>jetID;
    jetID.clear();
    if(period==16||period==161)JetID16(data,jetID,HZgVar,jetPt,tmpjetEn);
    else if(period==17)JetID17(data,jetID,HZgVar,jetPt,tmpjetEn);
    else if(period==18)JetID18(data,jetID,HZgVar,jetPt,tmpjetEn);
    
    Int_t nJet = data.GetInt("nJet");
    float *jetEta = data.GetPtrFloat("jetEta");
    float *jetPhi = data.GetPtrFloat("jetPhi");
    Long64_t event = data.GetLong64("event");
    Int_t nj =  0;
    
    int   tjet = -99;
    int   ljet = -99;
    float  tmpjetpt1=0.,tmpjetpt2=0.;
    TLorentzVector jet[2],dijet;
    float tmpdijetm = 0.;
    if(jetID.size()<2) return 0;
    else{
        for(unsigned int i = 0; i<jetID.size(); i++)
        {
            jet[0].SetPtEtaPhiE(jetPt[jetID[i]],jetEta[jetID[i]],jetPhi[jetID[i]],tmpjetEn[jetID[i]]);
            for(unsigned int j = i+1; j < jetID.size(); j++)
            {
                
                if(jetID[j] == ljet) continue;
                jet[1].SetPtEtaPhiE(jetPt[jetID[j]],jetEta[jetID[j]],jetPhi[jetID[j]],tmpjetEn[jetID[j]]);
                if(jet[1].Pt()>30.&&jet[0].Pt()>30.) continue;
                dijet = jet[0]+jet[1];
                float Zeppen = HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
                if(dijetMVA==false)
                {
                    if(dijet.M()<500)continue;
                    if(fabs(jet[1].Eta()-jet[0].Eta()) < 3.5) continue;
                    if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;
                    if(fabs(Zeppen) > 2.5) continue;
                    if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
                    if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
                }
                else
                {
                    //purity ranking
                    if(dijet.M()>=500&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4&&fabs(Zeppen) <= 2.5)
                    {
                        //HZgVar.jets.push_back(jetID[j])
                        //if((dijet.M())>tmpdijetm){tmpdijetm=dijet.M()+fabs(jet[1].Eta()-jet[0].Eta());ljet=jetID[i];tjet=jetID[j];}
                        if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
                        if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
                    }
                    /*
                     else if(dijet.M()>=500&&fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
                     {
                     if(dijet.M()+500*fabs(jet[1].Eta()-jet[0].Eta())>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
                     }
                     else if(fabs(jet[1].Eta()-jet[0].Eta()) >= 3.5&&fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
                     {
                     HZgVar.jets.push_back(jetID[j]);
                     if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
                     }
                     
                     else if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) >= 2.4)
                     {
                     HZgVar.jets.push_back(jetID[j]);
                     if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
                     }*/
                    //else
                    //if(dijet.M()>tmpdijetm){tmpdijetm=dijet.M();ljet=jetID[i];tjet=jetID[j];}
                    //else
                    //{
                    if(tmpjetpt1<jet[0].Pt()){tmpjetpt1= jet[0].Pt();ljet=jetID[i];}
                    if(tmpjetpt2<jet[1].Pt()){tmpjetpt2= jet[1].Pt();tjet=jetID[j];}
                    //          }
                    // if(fabs(jet[1].Eta()-jet[0].Eta())<1.0)continue;
                    // if(dijet.M()<200)continue;
                    //if(2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt()>80) continue;
                    //if(fabs(dijet.DeltaPhi(HZgVar.vec_higgs)) < 2.4) continue;
                    
                }
                
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

bool leptag(TreeReader &data, Int_t channel, vector<int> &muID, vector<float> &muPt, HZgVariables &HZgVar, int period)
{
  vector<int> eleID;
  float* elePt     = data.GetPtrFloat("eleCalibPt");
  float *eleEta    = data.GetPtrFloat("eleEta");
  float *elePhi    = data.GetPtrFloat("elePhi");

  float* muEta 		 = data.GetPtrFloat("muEta");
  float* muPhi 		 = data.GetPtrFloat("muPhi");
	
  //if(period==16)AddEle16Selections(data,98, eleID, HZgVar.lepPt[0],HZgVar.lepPt[1],channel);
  //else if(period==17)AddEle17Selections(data,98, eleID, HZgVar.lepPt[0],HZgVar.lepPt[1],channel);
  //else if(period==161
  //else
  AddEleIDv2(data,98, eleID, HZgVar.lepPt[0],HZgVar.lepPt[1],channel);
  TLorentzVector alep;
  if(channel==0)
    {
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
      else if(eleID.size()>0)
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
    }

  if(channel==1)
    {
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
      else if(muID.size()>0)
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
bool VHtag(TreeReader &data, HZgVariables &HZgVar, vector<float> &jetPt,vector<float> &tmpjetEn)
{
    HZgVar.Vj.clear();
    Int_t nJet = data.GetInt("nJet");
    float *jetEta = data.GetPtrFloat("jetEta");
    float *jetPhi = data.GetPtrFloat("jetPhi");
    TLorentzVector jet[2],djet;
    bool isVH = false;
    for (int i = 0; i < nJet;i++)
    {
        if(isVH==true) break;
        if(jetPt[i]<30.)continue;
        if(fabs(jetEta[i])>2.4)continue;
        jet[0].SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
	if(jet[0].DeltaR(HZgVar.vec_pho)<0.4||jet[0].DeltaR(HZgVar.vec_lep[0])<0.4||jet[0].DeltaR(HZgVar.vec_lep[1])<0.4) continue;
        for (int j = i+1; j < nJet;j++)
        {
            if(jetPt[j]<30.)continue;
            if(fabs(jetEta[j])>2.4)continue;
            jet[1].SetPtEtaPhiE(jetPt[j],jetEta[j],jetPhi[j],tmpjetEn[i]);
            djet= jet[0]+jet[1];
            if(djet.M()<60.||djet.M()>120.) continue;
	    if(jet[1].DeltaR(HZgVar.vec_pho)<0.4||jet[1].DeltaR(HZgVar.vec_lep[0])<0.4||jet[1].DeltaR(HZgVar.vec_lep[1])<0.4) continue;
            if(jetPt[i]>jetPt[j]){HZgVar.Vj.push_back(i);HZgVar.Vj.push_back(j);}
	    else{HZgVar.Vj.push_back(j);HZgVar.Vj.push_back(i);}
            isVH= true;
        }
    }
    if(isVH)return true;
    else return false;
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
  float tmppt[2],tmpcsv[2];
  tmpjetid[0] = tmpjetid[1] = -99;
  tmppt[0] = tmppt[1] = tmpcsv[0] = tmpcsv[1]= 0.;
  for(int i = 0; i<nJet; i++)
    {
      if(jetPt[i] < 25.) continue;
      if(fabs(jetEta[i])>2.4) continue;
      //if(jetBtag[i]<0.8484) continue;
      if(jetBtag[i]<0.5426) continue;
      //if(jetBtag[i]<0.5426||jetBtag[i]>0.8484) continue;
      if(tmpcsv[0]>jetBtag[i])continue;
      dbjet[0].SetPtEtaPhiE(jetPt[i],jetEta[i],jetPhi[i],tmpjetEn[i]);
      if(fabs(dbjet[0].DeltaR(HZgVar.vec_pho)) < 0.4||fabs(dbjet[0].DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(dbjet[0].DeltaR(HZgVar.vec_lep[1])) < 0.4) continue;
      tmpjetid[0] = i;
      tmpcsv[0] = jetBtag[i];

      for(int j = i+1; j < nJet; j++)
	{
	  if(jetPt[j] < 25.) continue;
	   if(fabs(jetEta[j])>2.4) continue;
	   //if(jetBtag[j]<0.8484) continue;
	   if(jetBtag[j]<0.5426) continue;
	   //if(jetBtag[j]<0.5426||jetBtag[j]>0.8484) continue;
	   if(j == tmpjetid[0]) continue;
	  if(tmpcsv[1]>jetBtag[j])continue;
	  dbjet[1].SetPtEtaPhiE(jetPt[j],jetEta[j],jetPhi[j],tmpjetEn[j]);
	  if(fabs(dbjet[1].DeltaR(HZgVar.vec_pho)) < 0.4||fabs(dbjet[1].DeltaR(HZgVar.vec_lep[0])) < 0.4 || fabs(dbjet[1].DeltaR(HZgVar.vec_lep[1])) < 0.4 || fabs(dbjet[1].DeltaR(dbjet[0]))<0.4)continue;
	  tmpjetid[1] = j;
	  tmpcsv[1] = jetBtag[j];
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
  float bjetPt =0.,bcsv2 = 0;
  for(int i = 0 ; i <nJet ; i++)
    {
      if(jetPt[i] < 25.) continue;
      if(fabs(jetEta[i])>2.4) continue;
      //if(bjetPt > jetPt[i]) continue;
      if(bcsv2>jetBtag[i])continue;
      bjet.SetPtEtaPhiE(jetPt[i], jetEta[i], jetPhi[i], tmpjetEn[i]);
      if(bjet.DeltaR(HZgVar.vec_pho) < 0.4 || bjet.DeltaR(HZgVar.vec_lep[0])<0.4||bjet.DeltaR(HZgVar.vec_lep[1])<0.4) continue;
      //if (jetBtag[i]<0.8484) continue;
      if(jetBtag[i]<0.5426) continue;
      //if(jetBtag[i]<0.5426||jetBtag[i]>0.8484) continue;
      bjetPt = jetPt[i];
      bcsv2 = jetBtag[i];
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
