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
double readMVA(int period, float phoR9, float phoMVA, float phores,float costheta,float cosTheta, float mllgptdmllg, float lepEta1, float lepEta2, float gEta_, float Phi,float dRlg, float maxdRlg)
{
  static float _mllgptdmllg,_cosTheta, _costheta, _Phi,_gdmllg,_lepEta1,_lepEta2,_phoEta,_phoMVA,_phoR9,_Zdmllg,_ZgPTt,_dEtaZg,_phores,_mllmllg, _dRlg,_maxdRlg;
  static TMVA::Reader* reader = NULL;
  if(!reader)
    {
      reader = new TMVA::Reader("!Color:Silent");
      reader->AddVariable("costheta", &_costheta );
      reader->AddVariable("cosTheta", &_cosTheta );
      reader->AddVariable("mllgptdmllg",        &_mllgptdmllg);
      reader->AddVariable("lepEta1",&_lepEta1 );
      reader->AddVariable("lepEta2",&_lepEta2);
      reader->AddVariable("phoEta",     &_phoEta);
      reader->AddVariable("Phi",      &_Phi );
      reader->AddVariable("phoR9",     &_phoR9);
      reader->AddVariable("phoMVA",    &_phoMVA );
      if(period==2016)reader->AddVariable("phores",    &_phores );
      //reader->AddVariable("mllmllg",   &_mllmllg);                                                             
      reader->AddVariable("dRlg",   &_dRlg);
      reader->AddVariable("maxdRlg",   &_maxdRlg);
      string file;
      if  (period==2016)file = "../MVAout/discr_Legacy16_HLT__HZg__tree1500_lrate0.5_depth4__BDT.weights.xml";
      //File- = "MVAout/discr_VBFMVA_v3__HZg__tree1000_lrate0.6_depth5__BDT.weights.xml";                          
      else if(period==2017) file = "../MVAout/discr_Rereco17_HLT__HZg__tree1500_lrate0.5_depth4__BDT.weights.xml";
      else if(period==2018) file = "../MVAout/discr_Rereco18_HLT__HZg__tree1500_lrate0.5_depth4__BDT.weights.xml";
      reader->BookMVA("BDT method", file.c_str());
    }
  _costheta = costheta;
  _cosTheta = cosTheta;
  _Phi = Phi;
  _mllgptdmllg = mllgptdmllg;
  _lepEta1 = lepEta1;
  _lepEta2 = lepEta2;
  _phoMVA = phoMVA;
  _phoR9 = phoR9;
  _phoEta = gEta_;
  _phores = phores;
  //  _mllmllg = mllmllg;
  _dRlg = dRlg;
  _maxdRlg = maxdRlg;
  return reader->EvaluateMVA("BDT method");
}
