///this electron selection is with HZZ iso+HZZMVA to all Z
using namespace std;
  
///preselection for triggering electrons--from Shilpi(for simulate trigger)
void  ElectronIDPreselRunII(TreeReader &data, vector<int> &goodElectrons)
{
  goodElectrons.clear();
  // load necessary tree branches

  const Int_t    nEle             = data.GetInt("nEle");
  const float* elePt            = data.GetPtrFloat("eleCalibPt");
  const float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  const float* eledEtaAtVtx     = data.GetPtrFloat("eledEtaAtVtx");
  const float* eledPhiAtVtx     = data.GetPtrFloat("eledPhiAtVtx");
  const float* eleSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5");
  const float* eleHoverE        = data.GetPtrFloat("eleHoverE");
  const float* elePFClusEcalIso = data.GetPtrFloat("elePFClusEcalIso");
  const float* elePFClusHcalIso = data.GetPtrFloat("elePFClusHcalIso");
  const float* eleDr03TkSumPt   = data.GetPtrFloat("eleDr03TkSumPt");



  for( int ie = 0; ie <nEle ; ie++ )
    {

      if( fabs(eleSCEta[ie]) < 1.479 )  // barral
        {

	  if( elePt[ie] < 15 )                        continue; // pT
	  if( fabs(eledEtaAtVtx[ie]) >= 0.0095 )      continue; // dEtaIn
	  if( fabs(eledPhiAtVtx[ie]) >= 0.065 )       continue; // dPhiIn
	  if( eleSigmaIEtaIEtaFull5x5[ie] >= 0.012 )  continue; // sigmaIEtaIEta
	  if( eleHoverE[ie] >= 0.09 )                 continue; // HCAL/ECAL
	  if( elePFClusEcalIso[ie]/elePt[ie] >= 0.37 ) continue; // ECAL PF isolation with pT
	  if( elePFClusHcalIso[ie]/elePt[ie] >= 0.25 ) continue; // HCAL PF isolation with pT
	  if( eleDr03TkSumPt[ie]/elePt[ie] >= 0.18 )   continue; // tracker isolation with pT

        }

      else  // endcaps
        {

	  if( elePt[ie] < 15 )                        continue;
	  if( fabs(eledEtaAtVtx[ie]) >= 999 )         continue;
	  if( fabs(eledPhiAtVtx[ie]) >= 999 )         continue;
	  if( eleSigmaIEtaIEtaFull5x5[ie] >= 0.033 )  continue;
	  if( eleHoverE[ie] >= 0.09 )                 continue;
	  if( elePFClusEcalIso[ie]/elePt[ie] >= 0.45 ) continue;
	  if( elePFClusHcalIso[ie]/elePt[ie] >= 0.28 ) continue;
	  if( eleDr03TkSumPt[ie]/elePt[ie] >= 0.18 )   continue;

        }
      goodElectrons.push_back(ie);
    }
  // end of electron loop
}

//electron MVA selection
void ElectronID16NonTrgMVA(TreeReader &data, Int_t WP, vector<int> &Zee, vector<TLorentzVector> &multz, vector<float> &elePt)
{

  multz.clear();
  Zee.clear();
  vector<int> accepted;
  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> elePtUnsorted;
  elePtUnsorted.clear();

  Int_t  nEle             = data.GetInt("nEle");
  Long64_t event_         = data.GetLong64("event");
  float* eleEta           = data.GetPtrFloat("eleEta");
  float* elePhi           = data.GetPtrFloat("elePhi");
  float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  //float* elePt            = data.GetPtrFloat("eleCalibPt");
  float* eleIDMVA         = data.GetPtrFloat("eleIDMVA");//11_01 ver. origin eleIDMVANonTrg
  float* eleIDMVAHZZ      = data.GetPtrFloat("eleIDMVAHZZ");
  float* elePFChIso       = data.GetPtrFloat("elePFChIso");//sumChargedHadronPt
  float* elePFNeuIso      = data.GetPtrFloat("elePFNeuIso");//sumNeutralHadronEt
  float* elePFPhoIso      = data.GetPtrFloat("elePFPhoIso");//sumPhotonEt
  float  rho              = data.GetFloat("rho");

  float* eleD0 = data.GetPtrFloat("eleD0");
  float* eleDz = data.GetPtrFloat("eleDz");
  float* eleSIP = data.GetPtrFloat("eleSIP");
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta

  //---MVA cut---//

  //effective area
  Float_t cut_effA[7] = {0.1703, 0.1715, 0.1213, 0.1230, 0.1635, 0.1937, 0.2393};

  //2016 MVA cut
  Float_t cut_mva_WP90[3] = {0.837, 0.715, 0.357};
  Float_t cut_mva_WP80[3] = {0.941, 0.899, 0.758};
  Float_t cut_mva_HZZ[3]  = {-0.870,-0.838,-0.763};
  Float_t lowcut_mva_HZZ[3]  = {-0.211,-0.396,-0.215};

  //impact parameter cuts-- from EGM
  //  Float_t cut_d0[2] = {0.05,0.10};
  //Float_t cut_dz[2] = {0.10,0.20};
  //impact parameter cut--from HZZ
  Float_t cut_d0[2] = {0.5,0.5};
  Float_t cut_dz[2] = {1.0,1.0};
 


  //---------------ele loop----------------//
  for (Int_t i=0; i<nEle; ++i)
    {
      ///loose the ele pT cut for additional lepton
      if (elePt[i] < 15.) continue;//move to SMP-HZZ group cut
      
      //  if (fabs(eleEta[i]) > 2.5) continue;//removed on 5th dec 2016
      if (fabs(eleSCEta[i]) > 2.5) continue;
      //    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;//only exclude for ele


      //impact parameter cut
      Int_t iEB = (fabs(eleSCEta[i]) <= 1.479) ? 0 : 1;
      
      if (fabs(eleD0[i]) > cut_d0[iEB]) continue;
      if (fabs(eleDz[i]) > cut_dz[iEB]) continue;
      if (eleSIP[i] >= 4.) continue;

      //effective area bit category
      Int_t eta_bit = -1;
      if (fabs(eleSCEta[i]) >= 0.000 && fabs(eleSCEta[i]) < 1.000) eta_bit = 0;
      if (fabs(eleSCEta[i]) >= 1.000 && fabs(eleSCEta[i]) < 1.479) eta_bit = 1;
      if (fabs(eleSCEta[i]) >= 1.479 && fabs(eleSCEta[i]) < 2.000) eta_bit = 2;
      if (fabs(eleSCEta[i]) >= 2.000 && fabs(eleSCEta[i]) < 2.200) eta_bit = 3;
      if (fabs(eleSCEta[i]) >= 2.200 && fabs(eleSCEta[i]) < 2.300) eta_bit = 4;
      if (fabs(eleSCEta[i]) >= 2.300 && fabs(eleSCEta[i]) < 2.400) eta_bit = 5;
      if (fabs(eleSCEta[i]) >= 2.400 && fabs(eleSCEta[i]) < 5.000) eta_bit = 6;


      //MVA cut category
      Int_t cat = -1;

      if (fabs(eleSCEta[i]) < 0.8) cat = 0;
      if (fabs(eleSCEta[i]) >= 0.8 && fabs(eleSCEta[i]) < 1.479) cat = 1;
      if (fabs(eleSCEta[i]) >= 1.479) cat = 2;

      //MVA cut

      if (WP == 98&& elePt[i] >= 10. && eleIDMVAHZZ[i] < cut_mva_HZZ[cat]) continue;
      if (WP == 90&& elePt[i] >= 10. && eleIDMVA[i] < cut_mva_WP90[cat]) continue;
      if (WP == 80&& elePt[i] >= 10. && eleIDMVA[i] < cut_mva_WP80[cat]) continue;
      //pass low pt requirement
      if (elePt[i] <= 10. &&eleIDMVAHZZ[i] < lowcut_mva_HZZ[cat]) continue;

      //relative isolation from HZZ group
      if (((elePFChIso[i] + std::max(0.0f, elePFNeuIso[i] + elePFPhoIso[i] - rho*cut_effA[eta_bit])) / elePt[i]) >= 0.35) continue;


      //pass low pt requirement
      passUnsorted.push_back(i);
      elePtUnsorted.push_back(elePt[i]);
    }
  //select Z with closest to nominal Z mass

  if(passUnsorted.size() >=2)
    {
      TLorentzVector  t1,t2,tz, ele1,ele2,z;

      ele1.SetPtEtaPhiM(elePt[passUnsorted[0]],eleEta[passUnsorted[0]],elePhi[passUnsorted[0]],0.511*0.001);
      ele2.SetPtEtaPhiM(elePt[passUnsorted[1]],eleEta[passUnsorted[1]],elePhi[passUnsorted[1]],0.511*0.001);
      int ie = passUnsorted[0];
      int je = passUnsorted[1];
      z = ele1+ele2;
      for(unsigned int i = 0; i < passUnsorted.size(); ++i)
        {
	  if(elePt[passUnsorted[i]]<15.)continue;
	  t1.SetPtEtaPhiM(elePt[passUnsorted[i]],eleEta[passUnsorted[i]],elePhi[passUnsorted[i]],0.511*0.001);
	  for(unsigned int j = 0 ; j < i; ++j)
            {
	      if(passUnsorted[j]==passUnsorted[i])continue;
	      if(elePt[passUnsorted[j]]<15.)continue;
	      t2.SetPtEtaPhiM(elePt[passUnsorted[j]],eleEta[passUnsorted[j]],elePhi[passUnsorted[j]],0.511*0.001);

	      tz = t1 + t2;
	      if(tz.M()>50&&(t1.Pt()>25||t2.Pt()>25))multz.push_back(tz);
	      if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
                {
		  ele1 = t1;
		  ele2 = t2;
		  z = ele1+ele2;
		  ie = passUnsorted[i];
		  je = passUnsorted[j];
                }
            }
        }
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? ie : je );
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? je : ie );
    }
  
  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &elePtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(passUnsorted[ind[i]]);
    }
}
//electron MVA selection
void ElectronID16NonTrgMVA_mod(TreeReader &data, Int_t WP, vector<int> &accepted, vector<TLorentzVector> &multz)
{
  multz.clear();
  // Zee.clear();
  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> elePtUnsorted;
  elePtUnsorted.clear();
  vector <int> eepair(2);
  eepair.clear();

  Int_t  nEle             = data.GetInt("nEle");
  Long64_t event_         = data.GetLong64("event");
  float* eleEta           = data.GetPtrFloat("eleEta");
  float* elePhi           = data.GetPtrFloat("elePhi");
  float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  float* elePt            = data.GetPtrFloat("eleCalibPt");
  float* eleIDMVA         = data.GetPtrFloat("eleIDMVA");//11_01 ver. origin eleIDMVANonTrg
  float* eleIDMVAHZZ      = data.GetPtrFloat("eleIDMVAHZZ");
  float* elePFChIso       = data.GetPtrFloat("elePFChIso");//sumChargedHadronPt
  float* elePFNeuIso      = data.GetPtrFloat("elePFNeuIso");//sumNeutralHadronEt
  float* elePFPhoIso      = data.GetPtrFloat("elePFPhoIso");//sumPhotonEt
  float  rho              = data.GetFloat("rho");

  float* eleD0 = data.GetPtrFloat("eleD0");
  float* eleDz = data.GetPtrFloat("eleDz");
  float* eleSIP = data.GetPtrFloat("eleSIP");
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta

  //---MVA cut---//

  //effective area
  Float_t cut_effA[7] = {0.1703, 0.1715, 0.1213, 0.1230, 0.1635, 0.1937, 0.2393};

  //2016 MVA cut
  Float_t cut_mva_WP90[3] = {0.837, 0.715, 0.357};
  Float_t cut_mva_WP80[3] = {0.941, 0.899, 0.758};
  Float_t cut_mva_HZZ[3]  = {-0.870,-0.838,-0.763};
  Float_t lowcut_mva_HZZ[3]  = {-0.211,-0.396,-0.215};

  //impact parameter cuts-- from EGM
  //  Float_t cut_d0[2] = {0.05,0.10};
  //Float_t cut_dz[2] = {0.10,0.20};
  //impact parameter cut--from HZZ
  Float_t cut_d0[2] = {0.5,0.5};
  Float_t cut_dz[2] = {1.0,1.0};

  //---------------ele loop----------------//
  for (Int_t i=0; i<nEle; ++i)
    {
      ///loose the ele pT cut for additional lepton
      if (elePt[i] < 15.) continue;//move to SMP-HZZ group cut
      
      //  if (fabs(eleEta[i]) > 2.5) continue;//removed on 5th dec 2016
      if (fabs(eleSCEta[i]) > 2.5) continue;
      //    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;//only exclude for ele


      //impact parameter cut
      Int_t iEB = (fabs(eleSCEta[i]) <= 1.479) ? 0 : 1;
      
      if (fabs(eleD0[i]) > cut_d0[iEB]) continue;
      if (fabs(eleDz[i]) > cut_dz[iEB]) continue;
      if (eleSIP[i] >= 4.) continue;

      //effective area bit category
      Int_t eta_bit = -1;
      if (fabs(eleSCEta[i]) >= 0.000 && fabs(eleSCEta[i]) < 1.000) eta_bit = 0;
      if (fabs(eleSCEta[i]) >= 1.000 && fabs(eleSCEta[i]) < 1.479) eta_bit = 1;
      if (fabs(eleSCEta[i]) >= 1.479 && fabs(eleSCEta[i]) < 2.000) eta_bit = 2;
      if (fabs(eleSCEta[i]) >= 2.000 && fabs(eleSCEta[i]) < 2.200) eta_bit = 3;
      if (fabs(eleSCEta[i]) >= 2.200 && fabs(eleSCEta[i]) < 2.300) eta_bit = 4;
      if (fabs(eleSCEta[i]) >= 2.300 && fabs(eleSCEta[i]) < 2.400) eta_bit = 5;
      if (fabs(eleSCEta[i]) >= 2.400 && fabs(eleSCEta[i]) < 5.000) eta_bit = 6;


      //MVA cut category
      Int_t cat = -1;

      if (fabs(eleSCEta[i]) < 0.8) cat = 0;
      if (fabs(eleSCEta[i]) >= 0.8 && fabs(eleSCEta[i]) < 1.479) cat = 1;
      if (fabs(eleSCEta[i]) >= 1.479) cat = 2;

      //MVA cut

      if (WP == 98&& elePt[i] >= 10. && eleIDMVAHZZ[i] < cut_mva_HZZ[cat]) continue;
      if (WP == 90&& elePt[i] >= 10. && eleIDMVA[i] < cut_mva_WP90[cat]) continue;
      if (WP == 80&& elePt[i] >= 10. && eleIDMVA[i] < cut_mva_WP80[cat]) continue;
      //pass low pt requirement
      if (elePt[i] <= 10. &&eleIDMVAHZZ[i] < lowcut_mva_HZZ[cat]) continue;

      //relative isolation from HZZ group
      if (((elePFChIso[i] + std::max(0.0f, elePFNeuIso[i] + elePFPhoIso[i] - rho*cut_effA[eta_bit])) / elePt[i]) >= 0.35) continue;


      //pass low pt requirement
      passUnsorted.push_back(i);
      elePtUnsorted.push_back(elePt[i]);
    }
  //select Z with closest to nominal Z mass

 /*  if(passUnsorted.size() >=2)
    {
      TLorentzVector  t1,t2,tz, ele1,ele2,z;

      ele1.SetPtEtaPhiM(elePt[passUnsorted[0]],eleEta[passUnsorted[0]],elePhi[passUnsorted[0]],0.511*0.001);
      ele2.SetPtEtaPhiM(elePt[passUnsorted[1]],eleEta[passUnsorted[1]],elePhi[passUnsorted[1]],0.511*0.001);
      int ie = passUnsorted[0];
      int je = passUnsorted[1];
      z = ele1+ele2;
      for(unsigned int i = 0; i < passUnsorted.size(); ++i)
        {
	  if(elePt[passUnsorted[i]]<15.)continue;
	  t1.SetPtEtaPhiM(elePt[passUnsorted[i]],eleEta[passUnsorted[i]],elePhi[passUnsorted[i]],0.511*0.001);
	  for(unsigned int j = 0 ; j < i; ++j)
            {
	      if(passUnsorted[j]==passUnsorted[i])continue;
	      if(elePt[passUnsorted[j]]<15.)continue;
	      t2.SetPtEtaPhiM(elePt[passUnsorted[j]],eleEta[passUnsorted[j]],elePhi[passUnsorted[j]],0.511*0.001);

	      tz = t1 + t2;
	      if(tz.M()>50&&(t1.Pt()>25||t2.Pt()>25))multz.push_back(tz);
	      if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
                {
		  ele1 = t1;
		  ele2 = t2;
		  z = ele1+ele2;
		  ie = passUnsorted[i];
		  je = passUnsorted[j];
                }
            }
        }
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? ie : je );
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? je : ie );
    }
   */
  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &elePtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(passUnsorted[ind[i]]);
    }
}


void AddEle16Selections(TreeReader &data, Int_t WP, vector<int> &accepted, float lep1Pt, float lep2Pt, Int_t channel)
{
  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> elePtUnsorted;
  elePtUnsorted.clear();

  Int_t  nEle             = data.GetInt("nEle");
  float* eleEta           = data.GetPtrFloat("eleEta");
  float* elePhi           = data.GetPtrFloat("elePhi");
  float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  float* elePt            = data.GetPtrFloat("eleCalibPt");
  float* eleIDMVA         = data.GetPtrFloat("eleIDMVA");//11_01 ver. origin eleIDMVANonTrg
  float* eleIDMVAHZZ      = data.GetPtrFloat("eleIDMVAHZZ");
  float* elePFChIso       = data.GetPtrFloat("elePFChIso");//sumChargedHadronPt
  float* elePFNeuIso      = data.GetPtrFloat("elePFNeuIso");//sumNeutralHadronEt
  float* elePFPhoIso      = data.GetPtrFloat("elePFPhoIso");//sumPhotonEt
  float  rho              = data.GetFloat("rho");
  UShort_t* eleIDbit      = (UShort_t*) data.GetPtrShort("eleIDbit");
  Long64_t  event_        = data.GetLong64("event");
  float* eleD0 = data.GetPtrFloat("eleD0");
  float* eleDz = data.GetPtrFloat("eleDz");
  float* eleSIP = data.GetPtrFloat("eleSIP");

  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta
  //effective area
  Float_t cut_effA[7] = {0.1703, 0.1715, 0.1213, 0.1230, 0.1635, 0.1937, 0.2393};

  //2016 MVA cut
  Float_t cut_mva_WP90[3] = {0.837, 0.715, 0.357};
  Float_t cut_mva_WP80[3] = {0.941, 0.899, 0.758};
  Float_t cut_mva_HZZ[3]  = {-0.870,-0.838,-0.763};
  Float_t lowcut_mva_HZZ[3]  = {-0.211,-0.396,-0.215};

  //impact parameter cuts--from EGM
  //  Float_t cut_d0[2] = {0.05,0.10};
  //Float_t cut_dz[2] = {0.10,0.20};

  //impact parameter cut--from HZZ
  Float_t cut_d0[2] = {0.5,0.5};
  Float_t cut_dz[2] = {1.0,1.0};


  //---------------ele loop----------------//
  for (Int_t i=0; i<nEle; ++i)
    {
      ///loose the ele pT cut for additional lepton

      if (elePt[i] < 7.) continue;//move to SMP-HZZ group cut
      if (fabs(eleSCEta[i]) > 2.5) continue;

      if(channel==0)
	{
	  if(elePt[i] == lep1Pt ||elePt[i] == lep2Pt) continue;
	}
      //  if (fabs(eleEta[i]) > 2.5) continue;//removed on 5th dec 2016
      if (eleSIP[i] >= 4.) continue;

      //    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;//only exclude for ele

      //impacter parameter cut
      Int_t iEB = (fabs(eleSCEta[i]) <= 1.479) ? 0 : 1;

      if (fabs(eleD0[i]) > cut_d0[iEB]) continue;
      if (fabs(eleDz[i]) > cut_dz[iEB]) continue;
      //remove HLT safe and tight selection for AN v7
      /*        if(elePt[i]<15.)
		{
		if ((eleIDbit[i] >> 5 & 1 ) ==0) continue;//HLT safe selection, selection is re-tuned
		}
      */
      //effective area bit category
      Int_t eta_bit = -1;
      if (fabs(eleSCEta[i]) >= 0.000 && fabs(eleSCEta[i]) < 1.000) eta_bit = 0;
      if (fabs(eleSCEta[i]) >= 1.000 && fabs(eleSCEta[i]) < 1.479) eta_bit = 1;
      if (fabs(eleSCEta[i]) >= 1.479 && fabs(eleSCEta[i]) < 2.000) eta_bit = 2;
      if (fabs(eleSCEta[i]) >= 2.000 && fabs(eleSCEta[i]) < 2.200) eta_bit = 3;
      if (fabs(eleSCEta[i]) >= 2.200 && fabs(eleSCEta[i]) < 2.300) eta_bit = 4;
      if (fabs(eleSCEta[i]) >= 2.300 && fabs(eleSCEta[i]) < 2.400) eta_bit = 5;
      if (fabs(eleSCEta[i]) >= 2.400 && fabs(eleSCEta[i]) < 5.000) eta_bit = 6;

      //MVA cut category
      Int_t cat = -1;

      if (fabs(eleSCEta[i]) < 0.8) cat = 0;
      if (fabs(eleSCEta[i]) >= 0.8 && fabs(eleSCEta[i]) < 1.479) cat = 1;
      if (fabs(eleSCEta[i]) >= 1.479) cat = 2;
	   

      //relative isolation from HZZ group
      if (((elePFChIso[i] + std::max(0.0f, elePFNeuIso[i] + elePFPhoIso[i] - rho*cut_effA[eta_bit])) / elePt[i]) > 0.35) continue;
      //MVA cut
      if (WP == 98&& elePt[i] > 10. && eleIDMVAHZZ[i] < cut_mva_HZZ[cat]) continue;//no WP (i can just use HZZ)
      if (WP == 90&& elePt[i] > 10. && eleIDMVA[i] < cut_mva_WP90[cat]) continue;
      if (WP == 80&& elePt[i] > 10. && eleIDMVA[i] < cut_mva_WP80[cat]) continue;

      //pass low pt requirement
      if (elePt[i] <= 10. &&eleIDMVAHZZ[i] < lowcut_mva_HZZ[cat]) continue;

      //accepted.push_back(i);
      passUnsorted.push_back(i);
      elePtUnsorted.push_back(elePt[i]);
    }

  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &elePtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(passUnsorted[ind[i]]);
    }

}


void ElectronID17NonTrgMVA(TreeReader &data, Int_t WP, vector<int> &Zee,vector<float> &elePt)
{

  Zee.clear();
  vector<int> accepted;
  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> elePtUnsorted;
  elePtUnsorted.clear();

  Int_t  nEle             = data.GetInt("nEle");
  Long64_t event_         = data.GetLong64("event");
  float* eleEta           = data.GetPtrFloat("eleEta");
  float* elePhi           = data.GetPtrFloat("elePhi");
  float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  //float* elePt            = data.GetPtrFloat("eleCalibPt");
  float* eleIDMVAIso      = data.GetPtrFloat("eleIDMVAIso");
  float* eleD0 = data.GetPtrFloat("eleD0");
  float* eleDz = data.GetPtrFloat("eleDz");
  float* eleSIP = data.GetPtrFloat("eleSIP");
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta


  //2017 MVA cut -w/ ISO
  Float_t cut_mva_HZZ_ISO[3]  = {0.833466688584422,-0.7677000247570116,-0.6917305995653829};
  Float_t lowcut_mva_HZZ_ISO[3]  = {-0.09564086146419018,-0.28229916981926795,-0.05466682296962322};
  //impact parameter cut--from HZZ
  Float_t cut_d0[2] = {0.5,0.5};
  Float_t cut_dz[2] = {1.0,1.0};
 
  //---------------ele loop----------------//
  for (Int_t i=0; i<nEle; ++i)
    {
      ///loose the ele pT cut for additional lepton
      if (elePt[i] < 15.) continue;//move to SMP-HZZ group cut
      
      //  if (fabs(eleEta[i]) > 2.5) continue;//removed on 5th dec 2016
      if (fabs(eleSCEta[i]) > 2.5) continue;
      //    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;//only exclude for ele

      //impact parameter cut
      Int_t iEB = (fabs(eleSCEta[i]) <= 1.479) ? 0 : 1;
      
      if (fabs(eleD0[i]) > cut_d0[iEB]) continue;
      if (fabs(eleDz[i]) > cut_dz[iEB]) continue;
      if (eleSIP[i] >= 4.) continue;

      //MVA cut category
      Int_t cat = -1;

      if (fabs(eleSCEta[i]) < 0.8) cat = 0;
      if (fabs(eleSCEta[i]) >= 0.8 && fabs(eleSCEta[i]) < 1.479) cat = 1;
      if (fabs(eleSCEta[i]) >= 1.479) cat = 2;

      //MVA cut
      if (elePt[i] >= 10. && eleIDMVAIso[i] < cut_mva_HZZ_ISO[cat]) continue;
      if (elePt[i] <= 10. &&eleIDMVAIso[i] < lowcut_mva_HZZ_ISO[cat]) continue;

      //pass low pt requirement
      passUnsorted.push_back(i);
      elePtUnsorted.push_back(elePt[i]);
    }
  //select Z with closest to nominal Z mass

  if(passUnsorted.size() >=2)
    {
      TLorentzVector  t1,t2,tz, ele1,ele2,z;

      ele1.SetPtEtaPhiM(elePt[passUnsorted[0]],eleEta[passUnsorted[0]],elePhi[passUnsorted[0]],0.511*0.001);
      ele2.SetPtEtaPhiM(elePt[passUnsorted[1]],eleEta[passUnsorted[1]],elePhi[passUnsorted[1]],0.511*0.001);
      int ie = passUnsorted[0];
      int je = passUnsorted[1];
      z = ele1+ele2;
      for(unsigned int i = 0; i < passUnsorted.size(); ++i)
        {
	  t1.SetPtEtaPhiM(elePt[passUnsorted[i]],eleEta[passUnsorted[i]],elePhi[passUnsorted[i]],0.511*0.001);
	  for(unsigned int j = 0 ; j < i; ++j)
            {
	      if(passUnsorted[j]==passUnsorted[i])continue;
	      t2.SetPtEtaPhiM(elePt[passUnsorted[j]],eleEta[passUnsorted[j]],elePhi[passUnsorted[j]],0.511*0.001);

	      tz = t1 + t2;
	      if(fabs(91.18-tz.M())<fabs(91.18-z.M()))
                {
		  ele1 = t1;
		  ele2 = t2;
		  z = ele1+ele2;
		  ie = passUnsorted[i];
		  je = passUnsorted[j];
                }
            }
        }
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? ie : je );
      Zee.push_back( (ele1.Pt() > ele2.Pt()) ? je : ie );
    }
  
  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &elePtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(passUnsorted[ind[i]]);
    }

}

void AddEle17Selections(TreeReader &data, Int_t WP, vector<int> &accepted, float lep1Pt, float lep2Pt, Int_t channel)
{
  accepted.clear();
  vector<int> passUnsorted;
  passUnsorted.clear();
  vector<float> elePtUnsorted;
  elePtUnsorted.clear();

  Int_t  nEle             = data.GetInt("nEle");
  float* eleEta           = data.GetPtrFloat("eleEta");
  float* elePhi           = data.GetPtrFloat("elePhi");
  float* eleSCEta         = data.GetPtrFloat("eleSCEta");
  float* elePt            = data.GetPtrFloat("eleCalibPt");
  float* eleIDMVAIso      = data.GetPtrFloat("eleIDMVAIso");
  Long64_t  event_        = data.GetLong64("event");
  float* eleD0 = data.GetPtrFloat("eleD0");
  float* eleDz = data.GetPtrFloat("eleDz");
  float* eleSIP = data.GetPtrFloat("eleSIP");



  //impact parameter cut--from HZZ
  Float_t cut_d0[2] = {0.5,0.5};
  Float_t cut_dz[2] = {1.0,1.0};
  //2017 MVA cut -w/ ISO
  Float_t cut_mva_HZZ_ISO[3]  = {0.833466688584422,-0.7677000247570116,-0.6917305995653829};
  Float_t lowcut_mva_HZZ_ISO[3]  = {-0.09564086146419018,-0.28229916981926795,-0.05466682296962322};
  //---------------ele loop----------------//
  for (Int_t i=0; i<nEle; ++i)
    {
      ///loose the ele pT cut for additional lepton

      if (elePt[i] < 7.) continue;//move to SMP-HZZ group cut
      if (fabs(eleSCEta[i]) > 2.5) continue;

      if(channel==0)
	{
	  if(elePt[i] == lep1Pt ||elePt[i] == lep2Pt) continue;
	}
      //  if (fabs(eleEta[i]) > 2.5) continue;//removed on 5th dec 2016
      if (eleSIP[i] >= 4.) continue;

      //    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;//only exclude for ele

      //impacter parameter cut
      Int_t iEB = (fabs(eleSCEta[i]) <= 1.479) ? 0 : 1;

      if (fabs(eleD0[i]) > cut_d0[iEB]) continue;
      if (fabs(eleDz[i]) > cut_dz[iEB]) continue;

      //MVA cut category
      Int_t cat = -1;

      if (fabs(eleSCEta[i]) < 0.8) cat = 0;
      if (fabs(eleSCEta[i]) >= 0.8 && fabs(eleSCEta[i]) < 1.479) cat = 1;
      if (fabs(eleSCEta[i]) >= 1.479) cat = 2;
	   
	   //MVA cut
      if (elePt[i] > 10. && eleIDMVAIso[i] < cut_mva_HZZ_ISO[cat]) continue;
      //pass low pt requirement
      if (elePt[i] <= 10. &&eleIDMVAIso[i] < lowcut_mva_HZZ_ISO[cat]) continue;

      //accepted.push_back(i);
      passUnsorted.push_back(i);
      elePtUnsorted.push_back(elePt[i]);
    }

  // sort accepted electrons in descending order of their pt
  int siz = (int) passUnsorted.size();
  if (siz < 1) return;

  int ind[siz];
  TMath::Sort(siz, &elePtUnsorted.front(), ind);

  for (int i = 0; i < siz; ++i)
    {
      accepted.push_back(passUnsorted[ind[i]]);
    }

}

