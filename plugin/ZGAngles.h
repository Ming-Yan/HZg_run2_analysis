//boosted to Z,Higgs frame for H->Zg analysis(compute the angle for arXiv::1112.1405)
#include "TLorentzVector.h"
#include "TVector3.h"
void ZGAngles(TLorentzVector &lep[2], TLorentzVector &Z, TLorentzVector &higgs, Float_t cosTheta, Float_t costheta[2], Float_t Phi[2])
{
	TVector3 beta_Zg = -1*higgs.BoostVector();
		
	  // Maxim's method
	  Z.Boost(beta_Zg);
	  lep[0].Boost(beta_Zg);
	  lep[1].Boost(beta_Zg);
	  lep[0].Boost(-1*Z.BoostVector());
	  lep[1].Boost(-1*Z.BoostVector());
	  TVector3 ppAxis(0, 0, 1);
	  costheta[0] = cos(Z.Angle(lep[0].Vect()));
	  costheta[1] = cos(Z.Angle(lep[1].Vect()));
	  cosTheta = cos(Z.Angle(higgs.Vect()));
				
	  TVector3 zAxis = Z.Vect().Unit();

	  // unit vector perpendicular to pp and Z directions (y axis)
	  TVector3 yAxis = ppAxis.Cross(zAxis.Unit()).Unit();

	  // unit vector perpendicular to Z direction in the ppZ plane (x axis)
	  TVector3 xAxis = (yAxis.Unit().Cross(zAxis.Unit())).Unit();
		   
	  TRotation rotation;
	  rotation = rotation.RotateAxes(xAxis,yAxis,zAxis ).Inverse();
	  // phi
	  Z.Transform(rotation);
	  lep[0].Transform(rotation);
	  lep[1].Transform(rotation);
		  
	  // double phi = xAxis.Angle(proj);
	  // if (zAxis.Dot(proj) < 0) phi = TMath::TwoPi() - phi;
		   
	  Phi[0] = lep[0].Phi(); 
	  Phi[1] = lep[1].Phi(); 
}		