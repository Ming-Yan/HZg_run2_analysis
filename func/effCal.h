#include "plugin/sigmaEff.h"
#include <TChain.h>
#include <TBranch.h>
#include <TString.h>
#include <TTree.h>
void effCal(string signal,string addcut)
{
  TChain ch("tZg");
  /*int fsize = sizeof(signal)/sizeof(signal[0]); 
  for(int j = 0;j < fsize;j++)
    {
      ch.Add(signal[j].c_str());
      cout<<signal[j]<<endl;
      }*/
  ch.Add(signal.c_str());
  Int_t cat,isbtag;
  float mllg_;
  ch.SetBranchAddress("cat", &cat);
  ch.SetBranchAddress("mllg", &mllg_);
  if(addcut.c_str()=="&&isbtag==0"||addcut.c_str()=="&&isbtag==1")ch.SetBranchAddress("isbtag", &isbtag);
  vector<float> sig;
  for ( Long64_t ev = 0; ev < ch.GetEntriesFast(); ev++)
    {
      ch.GetEntry(ev);
      
      if(addcut.c_str()=="&&isbtag==0"&&isbtag==0) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&isbtag==1"&&isbtag==1) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat>5&&cat<10"&&cat>5&&cat<10) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==1"&&cat==1) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==2"&&cat==2) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==3"&&cat==3) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==4"&&cat==4) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==5"&&cat==5) sig.push_back(mllg_);
      else if(addcut.c_str()=="&&cat==10"&&cat==10) sig.push_back(mllg_);
      else sig.push_back(mllg_);
    }
  float min = 115.;
  float max = 170.;
  float Zeffsigma = sigmaEff(sig, 0.68, min, max);
  cout<< min << " " << max << " " <<Zeffsigma<<endl;
}
