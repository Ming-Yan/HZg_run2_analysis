#ifndef H_CAT
#define H_CAT
int cat_MVAlimit(Int_t channel, int period, Int_t cat, Float_t gR9_,Float_t phoSCEta, Float_t lepEta0, Float_t lepEta1,Float_t mllgpt,Float_t HZgMVA, Float_t HZgVBF, Float_t kincut, Float_t VBFcut)
{
  //  float VBFcut2= -1.0;
  float VBFcut2 =  (period==16)? 0.09 : 0.18;//nominal cat
  VBFcut =(period==16)? 0.05:0.1;

  //kincut = (period==16) ? -0.01:0.01;
  //if(period==16) VBFcut2  = (channel==0) ?  0.05:0.02;
  if(cat>5&&cat<10)return 6789;  
  //else if (cat == 5&&HZgVBF>VBFcut) {return 5;}
  else if(HZgVBF>VBFcut2&&cat==5) return 501;
  else if(HZgVBF<=VBFcut2&&HZgVBF>VBFcut&&cat==5)return 502;
  //  if(cat==5&&HZgVBF<=VBFcut&&HZgMVA<kincut) return -99;
  //if((cat<5||cat==10)&&HZgMVA<kincut) return -99;
  //fixcut
  /*else if(HZgVBF>0.1&&cat==5) return 501;
  else if(HZgVBF<=0.1&&HZgVBF>-0.01&&cat==5) return 502;
  if(cat==5&&HZgVBF<=-0.01&&HZgMVA<kincut) return -99;
  if((cat<5||cat==10)&&HZgMVA<kincut) return -99;*/
 
  else if (mllgpt>60.) return 10;

  //electron channel
  else if(channel==0){
    if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 1.4442 & fabs(lepEta1) <= 1.4442)
      {
	if(gR9_ > 0.94)return 1;
	else return 2;
      }//electron in EB
    else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 1.4442 &&fabs(lepEta0) <= 2.5)||(fabs(lepEta1) > 1.4442 && fabs(lepEta1) <= 2.5))) return 3;
    else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
  }
  else if(channel==1)
    {      
      if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 2.1 & fabs(lepEta1) <= 2.1&&(fabs(lepEta0) <= 0.9 || fabs(lepEta1) <=  0.9))
	{
	  if(gR9_ > 0.94) return 1;
	  else return 2;
	}//both muon <2.1, and one muon <0.9

      else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 0.9 &&fabs(lepEta1) > 0.9)||((fabs(lepEta0) > 2.1 &&fabs(lepEta0) <= 2.4)||(fabs(lepEta1) > 2.1 &&fabs(lepEta1) <= 2.4))))return 3;
  
      else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
    }//muon channel end
}
int cat_cutbase(Int_t channel, Int_t cat, Float_t gR9_,Float_t phoSCEta, Float_t lepEta0, Float_t lepEta1,Float_t mllgpt)
{

  if(cat>5&&cat<10)return 6789;  
  else if(cat==5) return 5;
  else if (mllgpt>60.) return 10;
  //electron channel
  else if(channel==0){
    if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 1.4442 & fabs(lepEta1) <= 1.4442)
      {
	if(gR9_ > 0.94)return 1;
	else return 2;
      }//electron in EB
    else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 1.4442 &&fabs(lepEta0) <= 2.5)||(fabs(lepEta1) > 1.4442 && fabs(lepEta1) <= 2.5))) return 3;
    else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
  }
  else if(channel==1)
    {      
      if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 2.1 & fabs(lepEta1) <= 2.1&&(fabs(lepEta0) <= 0.9 || fabs(lepEta1) <=  0.9))
	{
	  if(gR9_ > 0.94) return 1;
	  else return 2;
	}//both muon <2.1, and one muon <0.9

      else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 0.9 &&fabs(lepEta1) > 0.9)||((fabs(lepEta0) > 2.1 &&fabs(lepEta0) <= 2.4)||(fabs(lepEta1) > 2.1 &&fabs(lepEta1) <= 2.4))))return 3;
  
      else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
    }//muon channel end
}
int bcat_limit(Int_t channel, Int_t cat, Int_t isbtag, Float_t gR9_,Float_t phoSCEta, Float_t lepEta0, Float_t lepEta1,Float_t mllgpt,Float_t HZgMVA, Float_t HZgVBF/*, Float_t kincut, Float_t VBFcut*/)
{

  if(cat>5&&cat<10) return 6789;
  //else if (cat == 5) return 5;
  else if(HZgVBF>0.08&&cat==5) return 501;
  else if (isbtag==1) return 11; 
  else if(HZgVBF<=0.08&&HZgVBF>-0.01&&cat==5) return 502;  
  if(cat==5&&HZgVBF<=-0.01&&HZgMVA<-0.01) return -99;
  if((cat<5||cat==10)&&HZgMVA<-0.01) return -99;

  
  else if (mllgpt>60.) return 10;

  //electron channel
  else if(channel==0){
    if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 1.4442 & fabs(lepEta1) <= 1.4442)
      {
	if(gR9_ > 0.94)return 1;
	else return 2;
      }//electron in EB
    else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 1.4442 &&fabs(lepEta0) <= 2.5)||(fabs(lepEta1) > 1.4442 && fabs(lepEta1) <= 2.5))) return 3;
    else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
    else return -99;
  }
  else if(channel==1)
    {      

      if(fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&fabs(lepEta0) > 0 &&fabs(lepEta1) > 0 &&fabs(lepEta0) <= 2.1 & fabs(lepEta1) <= 2.1&&(fabs(lepEta0) <= 0.9 || fabs(lepEta1) <=  0.9))
	{
	  if(gR9_ > 0.94) return 1;
	  else return 2;	
	}//both muon <2.1//one muon <0.9
      else if (fabs(phoSCEta) > 0 && fabs(phoSCEta) <= 1.4442&&((fabs(lepEta0) > 0.9 &&fabs(lepEta1) > 0.9)||((fabs(lepEta0) > 2.1 &&fabs(lepEta0) <= 2.4)||(fabs(lepEta1) > 2.1 &&fabs(lepEta1) <= 2.4))))return 3;
      else if(fabs(phoSCEta) <= 2.5&&fabs(phoSCEta) > 1.566)return 4;
    }//muon channel end
}
int cat_MVA(Int_t channel, int period, Int_t cat, bool isboost, float HZgMVA, float HZgVBF, float kincut, float VBFcut, float mllgpt)
{
  float VBFcut2 =  (period==16)? 0.09 : 0.18;
  if(period==16) VBFcut2  = (channel==0) ?  0.05:0.02;
  VBFcut =(period==16)? -0.05:0.1;

  //kincut =  (period==16)? -0.01:0.01; 
  if(cat>5&&cat<10) return 6789;
  else if(HZgVBF>VBFcut2&&cat==5) return 501;
  else if(HZgVBF<=VBFcut2&&HZgVBF>VBFcut&&cat==5) return 502;
  //if(cat==5&&HZgVBF<=VBFcut/*&&HZgMVA<kincut*/) return -99;
  //if((cat<5||cat==10)/*&&HZgMVA<kincut*/) return -99;
  else 
    {  int inclu = (mllgpt>60.&&isboost==true)? 10 : -1;
      return inclu;}
  //else if(mllgpt>60.&&isboost==true&&HZgVBF<=VBFcut) return 10;
  //else return -1;
}
#endif
