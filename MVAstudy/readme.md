### Current setup of MVA
    
## Kinematic MVA
    
# input variales
| variable      | description     | 
| ---------- | :-----------  | 
|  phi | angles of final state particles|
  | cosTheta | angles of the final state particles | 
  | costheta | angles of the final state particles | 
  | photon resolution | photon energy err / photon energy |
  | lep1,2 Eta | |
  | pho Eta | |
  | pho R9 | |
  | pho MVA| |
  | pT_h/m_h| boosted| 
  
#  Preselection : use 2016 analysis cut
# CR validation by inverse the mllg+mll cut
  
## VBFMVA 
  
# input varibles

| variable      | description     | 
| ---------- | :-----------  | 
  | deltaR_phojet | delta R between jet and photon |
  | mjj | dijet mass |
  | dEta_jj | dijet delta eta separation |
  | dPhi_jj | dijet delta phi separation |
  | jetpt1,2 | 
  | lep2 Eta | |
  | PTt | correlate to higgs pT, use to seperate signal & bkg=> but cause turn on |
  | HZgMVA | kinematic MVA training |
  | Zeppen | Zeppenfeld variable |
  
  # preselection : 
  
  1. Require jet pT >30GeV, jet |eta| < 2.4, dR(l,j).dR(pho,j) >0.4, pass CMS loose JetID
  2. Select dijet pair with tightest cuts -> if two more pairs, pick higher pT one

  # 
  