//root -l -b -q runall2.cc\(\"VBFMVA_phores\"\,1\,1\,2\)
void runall2(string fin,bool makedir,  bool isboost, int ncat, int njob, string pdf = "bern",int pdforder =4)
{
  float kinup = 1.0, kindown = -1.0;
  const float MVAWP_ele[6] = {0.1145,0.1025,0.0855,0.071,0.045,0.034};//95-90-80-70-60-40% signal eff
  const float MVAWP_mu[6] = {0.0835,0.063,0.044,0.0325,0.024,0.006};//95-90-80-70-60-40% signal eff
  //nsets = 6, 15, 20, 15, 6
  string vername,catname;
  gSystem->SetBuildDir("tmpdir", kTRUE);
  char combdir[100];
  string channel[2] = {"ele", "mu"};
  //gROOT->LoadMacro("make_Cards2_sep.C");
  //gROOT->LoadMacro("datapdf.C++");
  char cats[10];
  sprintf(cats,"ncat%d.txt",ncat);
  ifstream fcat(cats);
  vector<int> catvec;  catvec.clear();
  vector<int> thiscat;  thiscat.clear();
  int category; 
  char test[300]; 
  int setnum = 0;
  while (fcat>>category)catvec.push_back(category);

  for(int i = njob ; i < njob+1  ; i++)
    {
      for(int k = 0; k < ncat-1; k++)
	{
	  catname += std::to_string(catvec[k+i*(ncat-1)]);
	  thiscat.push_back(catvec[k+i*(ncat-1)]);
	}
      if(isboost==1)vername = "_wboost_comb"+catname;
      else vername = "woboost_comb"+catname;
      for(int ii = 0; ii < ncat; ii++)
	{
	  for (int elem = 0 ; elem < 2; elem++)
	    {
	      if(elem == 0)
		{
		  kinup = (ii==0) ? 1.0: MVAWP_ele[thiscat[ii-1]];
		  kindown = (ii==ncat-1) ? -1.0: MVAWP_ele[thiscat[ii]];
		}
	      else
		{
		  kinup = (ii==0) ? 1.0: MVAWP_mu[thiscat[ii-1]];
		  kindown = (ii==ncat-1) ? -1.0: MVAWP_mu[thiscat[ii]];
		}
	      cout<<ii+1<<" "<<kinup<<" "<<kindown<<endl;
	      gROOT->ProcessLine(Form(".x make_Cards2_sep.C(\"%s\",\"%s\",1,%d,%d,%f,%f,-0.001,0.08,\"%s\")",fin.c_str(), channel[elem].c_str(),isboost, ii+1, kinup, kindown, vername.c_str()));
	      sprintf(test,"root -l -b rundata.cc\\(\\\"%s\\\",\\\"%s\\\",\\\"bern\\\",4,%d,%d,%d,%f,%f,-0.001,0.08,\\\"%s\\\"\\)", fin.c_str(), channel[elem].c_str(), makedir, isboost, ii+1,  kinup, kindown, vername.c_str());
	      cout<<test<<endl;
	      system(test);
	    }
	}
      gSystem->cd(Form("/afs/cern.ch/work/m/milee/MYcode/limit/DataCards/VBFMVA_phores%s/",vername.c_str()));

      char combcard[300]; char finalize[500];char setlimit[100];
      string cards_e,cards_m;
      for(int m = 120; m < 131 ; m++)
	{
	  gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_ele_mu_6789_%d.txt",m),Form("card_VBFMVA_phores_ele_mu_6789_%d.txt",m));
	  gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_ele_501_%d.txt",m),Form("card_VBFMVA_phores_ele_501_%d.txt",m));
	  gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_mu_501_%d.txt",m),Form("card_VBFMVA_phores_mu_501_%d.txt",m));
	  gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_ele_502_%d.txt",m),Form("card_VBFMVA_phores_ele_502_%d.txt",m));
	  gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_mu_502_%d.txt",m),Form("card_VBFMVA_phores_mu_502_%d.txt",m));
	  if(isboost==1)gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_ele_10_%d.txt",m),Form("card_VBFMVA_phores_ele_10_%d.txt",m));
	  if(isboost==1)gSystem->CopyFile(Form("../VBFMVA_phores_comb/card_VBFMVA_phores_mu_10_%d.txt",m),Form("card_VBFMVA_phores_mu_10_%d.txt",m));
	  for(int i = 0 ; i <ncat; i++)
	    {
	      cards_e += " card_VBFMVA_phores_ele_"+std::to_string(i+1)+"_"+std::to_string(m) +".txt";
	      cards_m += " card_VBFMVA_phores_mu_"+std::to_string(i+1)+"_"+std::to_string(m)+".txt";
	    }
	  ///cout<<cards_e<<" "<<cards_m<<endl;
	  gSystem->Exec("pwd");
	  //gSystem->Exec("ls");
	  if(isboost==1)
	    {
	      sprintf(combcard,"combineCards.py %s card_VBFMVA_phores_ele_501_%d.txt card_VBFMVA_phores_ele_502_%d.txt card_VBFMVA_phores_ele_10_%d.txt >card_VBFMVA_phores_ele_all_%d.txt", cards_e.c_str(),m,m,m,m);
	      system(combcard);		
	      sprintf(combcard,"combineCards.py %s card_VBFMVA_phores_mu_501_%d.txt card_VBFMVA_phores_mu_502_%d.txt card_VBFMVA_phores_mu_10_%d.txt >card_VBFMVA_phores_mu_all_%d.txt", cards_e.c_str(),m,m,m,m);
	      system(combcard);		
	    }
	  else 
	    {
	      sprintf(combcard,"combineCards.py %s card_VBFMVA_phores_ele_501_%d.txt card_VBFMVA_phores_ele_502_%d.txt >card_VBFMVA_phores_ele_all_%d.txt", cards_e.c_str(),m,m,m);
	      system(combcard);		
	      sprintf(combcard,"combineCards.py %s card_VBFMVA_phores_mu_501_%d.txt card_VBFMVA_phores_mu_502_%d.txt >card_VBFMVA_phores_mu_all_%d.txt", cards_e.c_str(),m,m,m);
	      system(combcard);		
	    }
	  sprintf(combcard," combineCards.py  card_VBFMVA_phores_mu_all_%d.txt card_VBFMVA_phores_ele_all_%d.txt card_VBFMVA_phores_ele_mu_6789_%d.txt >card_VBFMVA_phores_all_%d",m,m,m,m);
	  //cout<<combcard <<endl;
	  system(combcard);		
	  sprintf(setlimit,"combine -M  Asymptotic  card_VBFMVA_phores_all_%d -m %d --run=blind -n VBFMVA_phores_ele_mu_all", m,m);
	  system(setlimit);
	  cards_e.clear();
	  cards_m.clear();
	  }
      cout<<vername<<endl;
      system("cd /afs/cern.ch/work/m/milee/MYcode/limit/");
      catname.clear();
      thiscat.clear();
    }
    
}
