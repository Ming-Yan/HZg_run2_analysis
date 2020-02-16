#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
using namespace TMVA;
Float_t HZgkin_MVA(TreeReader &data, Int_t channel, int period, HZgVariables &HZgVar, vector<float> &phoR9, vector<float> &res)
{
  //define
  Long64_t event = data.GetLong64("event");
  float* muEta = data.GetPtrFloat("muEta");
  float* eleEta = data.GetPtrFloat("eleEta");
  float* phoEta = data.GetPtrFloat("phoEta");
  float* phoIDMVA   = data.GetPtrFloat("phoIDMVA");

  float gEta_		= phoEta[HZgVar.phoID_];
  float lepEta1  = (channel==0) ? eleEta[HZgVar.lepID_[0]]:muEta[HZgVar.lepID_[0]];
  float lepEta2  = (channel==0) ? eleEta[HZgVar.lepID_[1]]:muEta[HZgVar.lepID_[1]];
  float mllgptdmllg = HZgVar.vec_higgs.Pt()/HZgVar.vec_higgs.M();
  float ZgPTt 		= 2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt();
  float gR9_		= phoR9[0];
  //cout<<gR9_<<endl;
  float gMVA_		= phoIDMVA[HZgVar.phoID_];
  float costheta    = HZgVar.HZgcostheta;
  float cosTheta    = HZgVar.HZgcosTheta;
  float Phi    		= HZgVar.HZgPhi;
  float dEtaZg = fabs(HZgVar.vec_higgs.Eta()-HZgVar.vec_pho.Eta());
  float phores = res[0];
  float mllmllg = HZgVar.vec_Z.M() + HZgVar.vec_higgs.M();
  float dRlg = TMath::Min(HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[0]),HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[1]));
  float maxdRlg = TMath::Max(HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[0]),HZgVar.vec_pho.DeltaR(HZgVar.vec_lep[1]));
  //define reader params
  static float _mllgptdmllg,_cosTheta, _costheta, _Phi, _gdmllg,_lepEta1,_lepEta2,_phoEta,_phoMVA,_phoR9,_Zdmllg,_ZgPTt,_dEtaZg,_phores,_mllmllg, _dRlg,_maxdRlg;
  static TMVA::Reader* reader = NULL;
  string method = (period==16) ?"BDT method" : "BDT method";
  if(!reader)
    {
      reader = new TMVA::Reader("!Color:Silent");
      reader->AddVariable("costheta", &_costheta );
      reader->AddVariable("cosTheta", &_cosTheta );
      reader->AddVariable("mllgptdmllg",	&_mllgptdmllg);
      reader->AddVariable("lepEta1",&_lepEta1 );
      reader->AddVariable("lepEta2",&_lepEta2);
      reader->AddVariable("phoEta", 	&_phoEta);
      reader->AddVariable("Phi",      &_Phi );
      reader->AddVariable("phoR9",     &_phoR9);
      //      if(period==18)reader->AddVariable("phoMVA",    &_phoMVA );
      reader->AddVariable("phores",    &_phores );
      //reader->AddVariable("mllmllg",   &_mllmllg);
      reader->AddVariable("dRlg",   &_dRlg);
      reader->AddVariable("maxdRlg",   &_maxdRlg);
      string file;
      //if  (period==16)file = "MVAout/discr_Legacy16_HLT__HZg_newMVA_tree1500_lrate0.5_depth4__BDT.weights.xml";//v1-Nov15ver
      //if  (period==16)file = "MVAout/discr_Legacy16_MVA1130__HZg_rmmva_tree1500_lrate0.5_depth4__BDT.weights.xml";
      if  (period==16)file = "MVAout/discr_Legacy16_MVA1130__HZg_mva_swap_tree1500_lrate0.6_depth4__BDT.weights.xml";
      //File- = "MVAout/discr_VBFMVA_v3__HZg__tree1000_lrate0.6_depth5__BDT.weights.xml";
      else if(period==17) file = "MVAout/discr_Rereco17_MVA1130__HZg_rmmva_tree1500_lrate0.6_depth4__BDT.weights.xml";
      //else if(period==17) file = "MVAout/discr_Rereco17_newMVAv2__HZg_all_tree1500_lrate0.5_depth4__BDT.weights.xml";
      else if(period==18) file = "MVAout/discr_Rereco18_MVA1130__HZg_mva_tree1500_lrate0.6_depth4__BDT.weights.xml";
      reader->BookMVA(method.c_str(), file.c_str());
      //reader->BookMVA("BDT method", "MVAout/discr_2017__HZg__tree1000_lrate0.6_depth5__BDT.weights.xml");
    }
  _costheta = costheta;
  _cosTheta = cosTheta;
  _Phi = Phi;
  _mllgptdmllg = mllgptdmllg;
  _lepEta1 = lepEta1;
  _lepEta2 = lepEta2;
  _phoMVA = gMVA_;
  _phoR9 = gR9_;
  _phoEta = gEta_;
  _phores = phores;
  _mllmllg = mllmllg;
  _dRlg = dRlg;
  _maxdRlg = maxdRlg;
  //cout<<"inside: "<<_costheta<<" "<<_cosTheta<<" "<<_Phi<<" "<<_mllgptdmllg<<" "<<_lepEta1<<" "<<_lepEta2<<" "<<_phoMVA<<" "<<_phoR9<<" "<<_phoEta<<" "<<_phores<<" "<<" "<<_dRlg<<" "<<_maxdRlg<<endl;
  return reader->EvaluateMVA(method.c_str());
}
Float_t HZgVBF_MVA(TreeReader &data, HZgVariables &HZgVar, Int_t channel, int period, vector<float> &jetPt, vector<float> &jetEn)
{

  float* jetEta = data.GetPtrFloat("jetEta");
  float* jetPhi = data.GetPtrFloat("jetPhi");
  TLorentzVector jet[2],dijet;
  jet[0].SetPtEtaPhiE(jetPt[HZgVar.VBFjet[0]],jetEta[HZgVar.VBFjet[0]],jetPhi[HZgVar.VBFjet[0]],jetEn[HZgVar.VBFjet[0]]);
  jet[1].SetPtEtaPhiE(jetPt[HZgVar.VBFjet[1]],jetEta[HZgVar.VBFjet[1]],jetPhi[HZgVar.VBFjet[1]],jetEn[HZgVar.VBFjet[1]]);
  dijet = jet[0]+jet[1];
  float VBFPt1_ = jet[0].Pt();
  float VBFPt2_ = jet[1].Pt();
  float mjj_ = dijet.M();
  float CZg_ = exp(-4/pow(jet[0].Eta()-jet[1].Eta(),2)*pow(HZgVar.vec_higgs.Eta()-((jet[0].Eta()+jet[1].Eta())/2),2));
  float dEta_jj_ = jet[1].Eta()-jet[0].Eta();
  float absdEta_jj_ = fabs(jet[1].Eta()-jet[0].Eta());
  float dPhi_Zgjj_ = dijet.DeltaPhi(HZgVar.vec_higgs);
  float absdPhi_Zgjj_ = fabs(dijet.DeltaPhi(HZgVar.vec_higgs));
  float dPhi_jj_ = jet[1].DeltaPhi(jet[0]);
  float absdPhi_jj_ = fabs(jet[1].DeltaPhi(jet[0]));
  float ZgPTt_ 		= 2*fabs(HZgVar.vec_Z.Px()*HZgVar.vec_pho.Py()-HZgVar.vec_Z.Py()*HZgVar.vec_pho.Px())/HZgVar.vec_higgs.Pt();
  float Zeppen_ = HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2;
  float absZeppen_ = fabs(HZgVar.vec_higgs.Eta()-(jet[0].Eta()+jet[1].Eta())/2);  
  float absZeppen_pho_ = fabs(HZgVar.vec_pho.Eta()-(jet[0].Eta()+jet[1].Eta())/2);
  float dR_phojet_ = min(jet[1].DeltaR(HZgVar.vec_pho),jet[0].DeltaR(HZgVar.vec_pho));
  float HZgMVA_ = HZgVar.kinMVA;
  float abssysbal_ = fabs((HZgVar.vec_pho.Px()+ HZgVar.vec_Z.Px()+jet[0].Px()+jet[1].Px()+HZgVar.vec_pho.Py()+ HZgVar.vec_Z.Py()+ jet[0].Py()+jet[1].Py())/(HZgVar.vec_pho.Pt()+HZgVar.vec_Z.Pt()+jet[0].Pt()+jet[1].Pt()));
  static float _mjj,_CZg, _absdEta_jj,_absdPhi_Zgjj,_absdPhi_jj,_ZgPTt, _VBFPt1, _VBFPt2,_absZeppen,_dR_phojet,_HZgMVA,_absZeppen_pho,_abssysbal;

 static TMVA::Reader* readerVBF = NULL;
  string method = (period==16) ?"BDT method" : "BDT method";
  if(!readerVBF)
    {
      readerVBF = new TMVA::Reader("!Color:Silent");
      //readerVBF->AddVariable("mjj",		&_mjj);

      readerVBF->AddVariable("absdEta_jj",	&_absdEta_jj);
      readerVBF->AddVariable("absdPhi_jj",	&_absdPhi_jj);
      readerVBF->AddVariable("absdPhi_Zgjj",&_absdPhi_Zgjj);
      readerVBF->AddVariable("dR_phojet",&_dR_phojet);
      readerVBF->AddVariable("ZgPTt",	&_ZgPTt);
      readerVBF->AddVariable("VBFPt1",&_VBFPt1);
      readerVBF->AddVariable("VBFPt2",&_VBFPt2);
      readerVBF->AddVariable("HZgMVA",&_HZgMVA);
      readerVBF->AddVariable("abssysbal", &_abssysbal);
      readerVBF->AddVariable("absZeppen_pho", &_absZeppen_pho);

      string file;

      //if(period==16)file = "MVAout/VBF_discr_Legacy16_newMVA__HZg__tree1000_lrate0.5_depth4_newMVA_BDT.weights.xml";
      if(period==16)file = "MVAout/VBF_discr_Legacy16_MVA1130__HZg__tree1000_lrate0.5_depth4_rmmva_BDT.weights.xml";
      //if(period==17)file = "MVAout/VBF_discr_Rereco17_VBFjet__HZg__tree1000_lrate0.6_depth4_mva_BDT.weights.xml";
      if(period==17)file = "MVAout/VBF_discr_Rereco17_MVA1130__HZg__tree1000_lrate0.6_depth4_rmmva_BDT.weights.xml";
      if(period==18)file = "MVAout/VBF_discr_Rereco18_MVA1130__HZg__tree1000_lrate0.6_depth4_mva_BDT.weights.xml";
      readerVBF->BookMVA(method.c_str(), file.c_str());
    }	  
  _mjj = mjj_; 
  _dR_phojet = dR_phojet_;
  _absZeppen = absZeppen_;
  _absdEta_jj = absdEta_jj_;
  _absdPhi_Zgjj = absdPhi_Zgjj_;
  _absdPhi_jj = absdPhi_jj_;
  _ZgPTt = ZgPTt_;
  _VBFPt1 = VBFPt1_;
  _VBFPt2 = VBFPt2_;
  _HZgMVA = HZgMVA_;
  _absZeppen_pho = absZeppen_pho_;
  _abssysbal = abssysbal_;
  return readerVBF->EvaluateMVA(method.c_str());
}
