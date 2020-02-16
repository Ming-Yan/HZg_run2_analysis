void mkfile()
{
  char outname[150];
  int njob[5] = {6,15,20,15,6};
  char command[120];
  int jobnum = 0;
  for(int i = 2; i < 7 ; i++)
    {
      for(int j = 0; j < njob[i-2] ; j++)
	{

	  sprintf(outname,"catjob%d.sh",jobnum);
	   ofstream fout(outname);
	  fout<<"#!/bin/csh"<<endl;
	  fout<<"cd /afs/cern.ch/user/m/milee/CMSSW_7_4_7/src/"<<endl;
	  fout<<"eval `scramv1 runtime -sh`"<<endl;
	  fout<<"cd /afs/cern.ch/work/m/milee/MYcode/limit/"<<endl;
	  sprintf(command,"root -l -b -q runall2.cc\\(\\\"VBFMVA_phores\\\"\\,1\\,0\\,%d\\,%d\\)",i,j);
	  fout<<command<<endl;
	  sprintf(command,"root -l -b -q runall2.cc\\(\\\"VBFMVA_phores\\\"\\,1\\,1\\,%d\\,%d\\)",i,j);
	  fout<<command<<endl;
	  cout<<outname<<endl;
	  jobnum++;
	}
    }
}
