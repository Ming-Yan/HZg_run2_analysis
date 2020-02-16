#include "TMVA/Reader.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TLorentzVector.h"
struct HZgVariables
{
  Int_t genphoID, genlepID[2];
  Int_t lepID_[2] ,phoID_, sfsrID_[2],afsrID_[2];
  Float_t lepPt[2], alepPt,lepR9[2],alepR9,phoR9; // nominal var
  Float_t REFIT_lepPt[2], REFIT_lepPtErr[2], REFIT_mll,REFIT_mllg, mllerr,REFIT_mllerr;
  vector<int> VBFjet, alep, dbjet, bjet, jets, allpho,fsr,Vj; 	
  Int_t VBFPID[2];
  Int_t cat,totalev, isLep, isVBF, isboost, isbtag, isdbtag,isVH;
  Float_t mcwei,puwei,genwei,puweiUp,puweiDown,ptwei;
  TLorentzVector vec_lep[2], vec_pho, vec_Z,vec_higgs, vec_oldZ, vec_oldH;
  Float_t  SFGSF_[3], SFeID_[3],SFetrg_[2], SFedz_[2],SFmutrg_[2], SFmuTrk_[3], SFmuID_[3], SFgVeto_,SFgID_;//SFs
  Float_t UNGSF_[3], UNeID_[3], UNetrg_[2],UNedz_[2],UNmutrg_[2], UNmuTrk_[3], UNmuID_[3], UNgVeto_,UNgID_;//UNcertainty of SFs
  Float_t HZgPhi, HZgcostheta, HZgcosTheta,kinMVA,VBFMVA;
  vector<int> Z;
};

void HZgAngles(HZgVariables &HZgVar)
{
  TLorentzVector lep[2], zll, higgs;
  higgs = HZgVar.vec_higgs;
  zll 	= HZgVar.vec_Z;
  lep[0] = HZgVar.vec_lep[0];
  lep[1] = HZgVar.vec_lep[1];
  TVector3 beta_Zg = -1*higgs.BoostVector();
   // Maxim's method
   zll.Boost(beta_Zg);
   lep[0].Boost(beta_Zg);
   lep[0].Boost(-1*zll.BoostVector());
   TVector3 ppAxis(0, 0, 1);
   HZgVar.HZgcostheta = cos(zll.Angle(lep[0].Vect()));
   HZgVar.HZgcosTheta = cos(zll.Angle(higgs.Vect()));

   TVector3 zAxis = zll.Vect().Unit();

   // unit vector perpendicular to pp and Z directions (y axis)
   TVector3 yAxis = ppAxis.Cross(zAxis.Unit()).Unit();

   // unit vector perpendicular to Z direction in the ppZ plane (x axis)
   TVector3 xAxis = (yAxis.Unit().Cross(zAxis.Unit())).Unit();

   TRotation rotation;
   rotation = rotation.RotateAxes(xAxis,yAxis,zAxis ).Inverse();
   // phi
   zll.Transform(rotation);
   lep[0].Transform(rotation);

   // double phi = xAxis.Angle(proj);
   // if (zAxis.Dot(proj) < 0) phi = TMath::TwoPi() - phi;
   HZgVar.HZgPhi = lep[0].Phi();
   } 
 
