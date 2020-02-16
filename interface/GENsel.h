bool GENsel(TreeReader &data, Int_t channel, HZgVariables &HZgVar)
{
 
  Int_t  nMC      = 0;
  Int_t* mcPID    = NULL;
  Int_t* mcMomPID = NULL;
  Int_t* mcGMomPID = NULL;
  float* mcMomEta = NULL;
  float* mcMomPt = NULL;
  float* mcPt     = NULL;
  float* mcEta    = NULL;
  float* mcPhi    = NULL;
  float* mcMass    = NULL;
  UShort_t* mcStatusFlag = NULL;
  nMC          = data.GetInt("nMC");
  mcPID        = data.GetPtrInt("mcPID");
  mcGMomPID     = data.GetPtrInt("mcGMomPID");
  mcMomPID     = data.GetPtrInt("mcMomPID");
  mcMomEta     = data.GetPtrFloat("mcMomEta");
  mcMomPt    = data.GetPtrFloat("mcMomPt");
  mcPt         = data.GetPtrFloat("mcPt");
  mcEta        = data.GetPtrFloat("mcEta");
  mcPhi        = data.GetPtrFloat("mcPhi");
  mcMass        = data.GetPtrFloat("mcMass");
  mcStatusFlag = (UShort_t*) data.GetPtrShort("mcStatusFlag");
 int nmclep, nmcpho;
  nmclep = nmcpho = 0;
  for(int i = 0 ; i <nMC; i++)
    { 
      if(/*mcMomPID[i]==25&&*/mcPID[i]==22&&mcPt[i]>15.&&(((mcStatusFlag[i] >> 0) & 1) == 1&&((mcStatusFlag[i] >> 1) & 1) == 1)){HZgVar.genphoID = i;nmcpho++;} 
      if(channel==0&&mcPt[i]>15.&&mcMomPID[i]==23/*&&mcGMomPID[i]==25*/&&fabs(mcPID[i])==11&&((mcStatusFlag[i] >> 0) & 1) == 1&&((mcStatusFlag[i] >> 1) & 1) == 1){HZgVar.genlepID[nmclep] = i;nmclep++;}
      else if(channel==1&&mcPt[i]>10.&&mcMomPID[i]==23/*&&mcGMomPID[i]==25*/&&fabs(mcPID[i])==13&((mcStatusFlag[i] >> 0) & 1) == 1&&((mcStatusFlag[i] >> 1) & 1) == 1){HZgVar.genlepID[nmclep] = i;nmclep++;}
}
  if(nmcpho==1&&nmclep==2) return 1;
  else return 0;	  	  
}

