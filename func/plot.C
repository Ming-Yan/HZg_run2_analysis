#include "interface/plot/plotDataMC.h"
#include "interface/plot/purity.h"
#include "interface/plot/plotvar.h"
//#include "interface/plot/eff.h"
//#include "interface/plot/vans.h"
//#include "effCal.h"
void plot()
{
  //plotDataMC("Legacy16_allMVA",1,"plot/mu_VBF_BDT_valid_Legacy16_allMVA.pdf","(HZgVBF!=-99)",true,24,-0.8,0.4,"HZgVBF","BDT score","tZg");  
  //plotDataMC("Legacy_allMVA2",1,"plot/mu_VBF_BDT_valid_Legacy_allMVA2.pdf","(HZgVBF!=-99)",true,24,-0.8,0.4,"HZgVBF","BDT score","tZg");  
  //plotDataMC("Rereco17_newpt",0,"plot/ele_VBF_BDT_valid_Rereco17_newpt.pdf","1.",true,50,-1,1,"HZgMVA","BDT score","tZg");  
  
  //plotDataMC("Legacy16_allMVA2",1,"plot/mu_VBFkin_BDT_valid_Legacy16_allMVA2.pdf","(HZgVBF!=-99)",true,18,-0.5,0.4,"(HZgVBF+HZgMVA)/2","BDT score","tZg");  
  //plotDataMC("Legacy16_allMVA2",0,"plot/ele_VBFkin_BDT_valid_Legacy16_allMVA2.pdf","(HZgVBF!=-99)",true,18,-0.5,0.4,"(HZgVBF+HZgMVA)/2","BDT score","tZg");  
  /*plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_BDT_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,18,-0.7,0.2,"HZgVBF","BDT score","tZg");  
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_VBFPt2_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,12,30,150,"VBFPt2","pT_{j2}","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_VBFPt1_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,18,30,210,"VBFPt1","pT_{j1}","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_Zeppen_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,12,0,6,"absZeppen","Zeppen","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_dEtajj_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,18,0,9,"absdEta_jj","#Delta#eta_{jj}","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_dPhijj_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,15,0,3,"absdPhi_jj","#Delta#phi_{jj}","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_dPhiZgjj_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,15,0,3,"absdPhi_Zgjj","#Delta#phi_{Zgjj}","tVBF"); 
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_PTt_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,20,0,140,"ZgPTt","PTt","tVBF");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_dR_phojet_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,20,0.4,6.4,"dR_phojet","#DeltaR(#gamma,j)","tVBF"); 

  plotDataMC("Legacy16_newpt",0,"plot/ele_mllgmllgpt_valid_Legacy16_newpt.pdf","1.",true,40,0,2,"mllgptdmllg","pT_{H}/m_{H}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kinvbf_BDT_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,22,-0.6,0.5,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kinvbf_BDT_valid_Legacy16_newpt.pdf","1.",true,22,-0.6,0.5,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_mllgmllgpt_valid_Legacy16_newpt.pdf","1.",true,40,0,2,"mllgptdmllg","pT_{H}/m_{H}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_mll_valid_Legacy16_newpt.pdf","1.",true,70,50,120,"mll","M_{ll}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_lldmllg_valid_Legacy16_newpt.pdf","1.",true,30,0,1.5,"lldmllg","pT_{ll}/m_{H}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_mll_valid_Legacy16_newpt.pdf","1.",true,70,50,120,"mll","M_{ll}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_mllgmllgpt_valid_Legacy16_newpt.pdf","1.",true,40,0,2,"mllgptdmllg","pT_{H}/m_{H}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_BDT_valid_Legacy16_newpt.pdf","1.",true,40,-0.6,0.2,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_BDT_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_mllg_valid_Legacy16_newpt.pdf","1.",true,40,100,180,"mllg","M_{ll#gamma}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_gdmllg_valid_Legacy16_newpt.pdf","1.",true,25,0.1,0.6,"gdmllg","M_{ll#gamma}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_BDT_valid_Legacy16_newpt.pdf","1.",true,48,-0.8 ,0.4,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_mll_valid_Legacy16_newpt.pdf","1.",true,70,50,120,"mll","M_{ll}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_lepPt2_valid_Legacy16_newpt.pdf","1.",true,50,10,300,"lepPt[1]","pT_{l2}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_lepPt1_valid_Legacy16_newpt.pdf","1.",true,50,20,300,"lepPt[0]","pT_{l1}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_phoPt_valid_Legacy16_newpt.pdf","1.",true,50,0,300,"phoPt","pT_{#gamma}","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_lepeta1_valid_Legacy16_newpt.pdf","1.",true,12,-3,3,"lepEta1","#eta_{l1}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_lepeta2_valid_Legacy16_newpt.pdf","1.",true,12,-3,3,"lepEta2","#eta_{l2}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_phoeta_valid_Legacy16_newpt.pdf","1.",true,12,-3,3,"phoEta","#eta_{#gamma}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_phi_valid_Legacy16_newpt.pdf","1.",true,12,-3,3,"Phi","#phi","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_dEtaZg_valid_Legacy16_newpt.pdf","1.",true,30,0,6,"dEtaZg","#Delta#eta_{Z#gamma}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_costheta_valid_Legacy16_newpt.pdf","1.",true,20,0,1,"costheta","cos(#theta)","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_coscaptheta_valid_Legacy16_newpt.pdf","1.",true,20,0,1,"cosTheta","cos(#Theta)","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_phomva_valid_Legacy.pdf","1.",true,50,-1,1,"phoMVA","phoMVA","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_r9_valid_Legacy16_newpt.pdf","1.",true,20,0,1,"phoR9","phoR9","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_phores_valid_Legacy16_newpt.pdf","1.",true,19,0.01,0.2,"phores","#sigma_{#gamma}","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_dRlg1_valid_Legacy16_newpt.pdf","1.",true,20,0.,2.,"dRlg","min #DeltaR(l,#gamma)","tMVA");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_dRlg2_valid_Legacy16_newpt.pdf","1.",true,20,0.,2.,"maxdRlg","max #DeltaR(l,#gamma)","tMVA");
  //plotDataMC("Legacy16_newpt2_sb",1,"plot/mu_kin_lepPt1_valid_Legacy16_newpt2_sb.pdf","1.",true,50,0,200,"lepPt[0]","pT_{l1}","tZg");
  ///plotDataMC("Legacy16_newpt2",1,"plot/mu_kin_r9_valid_Legacy16_newpt2.pdf","1.",true,20,0,1,"phoR9","phoR9","tMVA");
  //plotDataMC("Rereco17y",0,"plot/ele_kin_BDT_valid_Rereco17_newpt_cut.pdf","1.",true,40,-0.6,0.2,"HZgMVA","BDT score","tZg");*/
  //plotDataMC("Rereco18_16MVA",0,"plot/ele_kin_BDT_valid_Rereco18.pdf","1.",true,40,-0.6,0.4,"HZgMVA","BDT score","tZg");
  //
  //plotDataMC("Rereco18_HLT",0,"plot/ele_kin_nVtx_valid_Rereco18_16MVA.pdf","1.",true,60,0,60,"nVtx","BDT score","tZg");
  /*  plotDataMC("Rereco17_HLT",0,"plot/ele_kin_nVtx_valid_Rereco17_HLT.pdf","1.",true,60,0,60,"nVtx","BDT score","tZg");
  plotDataMC("Rereco18_HLT",0,"plot/ele_kin_nVtx_valid_Rereco18_HLT.pdf","1.",true,60,0,60,"nVtx","BDT score","tZg");

  plotDataMC("Rereco17_HLT",0,"plot/ele_kin_rho_valid_Reco17_HLT.pdf","1.",true,60,0,60,"rho","#rho","tZg");*/
  //plotDataMC("Rereco17_HLT",0,"plot/ele_kin_njet_valid_Reco17_HLT.pdf","1.",true,8,4,20,"njets","nJet","tVBF");
  //plotDataMC("Rereco18_16MVA",0,"plot/ele_kin_BDT_valid_Rereco18.pdf","58.8/35.5",true,40,-0.6,0.4,"HZgMVA","BDT score","tZg");
  //plotDataMC("Rereco18_16MVA",0,"plot/ele_VBF_BDT_valid_Rereco18_16MVA.pdf","(HZgVBF!=-99)*1.",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");
  //plotDataMC("Rereco18_16MVA",0,"plot/ele_VBF_BDT_valid_Rereco18_16MVA.pdf","(HZgVBF!=-99)*58.8/35.5",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");
   //plotDataMC("Rereco18_newpt_cut",0,"plot/ele_mllgmllgpt_valid_18_ptcut.pdf","1.",true,40,0,2,"mllgptdmllg","pT_{H}/m_{H}","tMVA");     
  /*plotDataMC("Legacy16_newpt",1,"plot/mu_kin_BDT_valid_Legacy16_newpt.pdf","1.",true,40,-0.6,0.4,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_kin_BDT_valid_Legacy16_newpt.pdf","1.",true,40,-0.6,0.4,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt_sb",1,"plot/mu_kin_BDT_valid_Legacy16_newpt_sb.pdf","1.",true,20,-0.6,0.4,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt_sb",0,"plot/ele_kin_BDT_valid_Legacy16_newpt_sb.pdf","1.",true,20,-0.6,0.4,"HZgMVA","BDT score","tZg");
  plotDataMC("Legacy16_newpt",1,"plot/mu_VBF_BDT_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");
  plotDataMC("Legacy16_newpt",0,"plot/ele_VBF_BDT_valid_Legacy16_newpt.pdf","(HZgVBF!=-99)",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");
  plotDataMC("Legacy16_newpt_sb",1,"plot/mu_VBF_BDT_valid_Legacy16_newpt_sb.pdf","(HZgVBF!=-99)",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");  
  plotDataMC("Legacy16_newpt_sb",0,"plot/ele_VBF_BDT_valid_Legacy16_newpt_sb.pdf","(HZgVBF!=-99)",true,16,-0.8,0.8,"HZgVBF","BDT score","tZg");*/

  const int nf = 2;
  string fin[nf] =
    {
      //"../outfile/mc_Legacy16_old_ele_Zg_aMCatNLO.root",
      //"../outfile/mc_Legacy16_new_ele_Zg_aMCatNLO.root"
      "../outfile/Data_Rereco18_old_mu_Mu_Run2018A_EarlyRereco.root",
      "../outfile/Data_Rereco18_new_mu_Mu_Run2018A_EarlyRereco.root"
      //"../outfile/mc_Rereco17_HLT_HZg_VBF_125GeV.root",
      //"../outfile/mc_Rereco17_HLT_HZg_VBF_125GeV.root"
    };
  string cuttype[nf] =
    {
      //"fabs(Particle.PID)==11||fabs(Particle.PID)==13","fabs(Particle.PID)==11||fabs(Particle.PID)==13","fabs(Particle.PID)==11||fabs(Particle.PID)==13"
      //"mcmllg>30&&mcmll>30",""
      //"issfsr==2","issfsr==3"
      //"isVBFmatch==1","isVBFmatch!=1&&VBFPID!=-99&&VBFPID!=21","isVBFmatch!=1&&VBFPID==21","isVBFmatch!=1&&VBFPID==-99"
      "",""
      //"issfsr==2&&issfsr","issfsr==3&&issfsr==-99"//,"issfsr[1]==3","issfsr[1]==3"
      ///"HZgVBF!=-99","HZgVBF!=-99","HZgVBF!=-99","HZgVBF!=-99"
      //"HZgVBF!=-99","HZgVBF!=-99","HZgVBF!=-99"
      //"","mcmllg>30&&mcmll>30"
      //"cat==1","cat==2","cat==3","cat==4"
      //"","",""
      //"issfsr"
      //"issfsr!=-99","issfsr!=-99"

    };
  string label[nf] = 
    {
      "old","new"
      //"ggF","VBF","ttH","VH","Z#gamma","Z+jets","TTbar"
      //"origin","+FSR"//,"new FSR(Z)"
      //"all","fsr","fake"
      //"VBF jet","NLO VBFjet(w/o g)","NLO VBFjet(g)","PUJet"
      //"ele","mu"      
      //"Madgraph","aMC@NLO"
      //"original","new"
      //"E_{T}/#DeltaR(l,#gamma)^{2}","Z mass"
      //"original","SMP-ZZ","atlas"
      ///"ggF new","ggF old","data new","data old"
      //"VBF new","VBF old","data new","data old"
      //"cat 1","cat 2","cat 3","cat 4"
      //"ggF","VBF","data"
      //"FSR","fake"
      //"new signal","old signal","new data","old data"
      //"ggF","VBF","Z#gamma","Z+jets"
      //"SIP3_Loose","SIP4_Loose","SIP5_Loose","SIP6_Loose", "SIP3_ZZ","SIP4_ZZ","SIP5_ZZ","SIP6_ZZ"
      //"MG261 w/ 30GeV cut","MG261","MG255"
      //"ele","mu"
      //"efore FSR","no FSR recover","add FSR"
    };
	
  //string var[nf]={"mll","REFITmll"};// = {"HZgVBF","HZgVBF","HZgVBF","HZgVBF"};//,"HZgVBF","HZgVBF","HZgVBF"};	
  //string var[nf] = {"bCsv2","bCsv2","bCsv2","bCsv2","bCsv2","bCsv2","bCsv2"};
  //string var[nf] = {"sfsrPt","sfsrPt"};
  //string var[nf]= {"REFITmllg","REFITmllg","REFITmllg"};
  string var[nf] = {"mll","sfsrmll"};
  string outname="plot/fsr_mllcompare2.pdf";
  //string outname = "plot/FSRPt.pdf";
  //= "plot/test_VBFMVA.pdf";
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype,15 ,25,250, "bjetPt","A.U.",true,false,2);
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype,24 ,0.,0.012, "#DeltaR(FSR,l)/E^{2}","A.U.",true,false,2);
	
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 85,-(bjetPt!=1.)0,0.7, "BDT score","Event",true,efalse,2);
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 15,-3,3., "MET #phi","Event",true,false,2);
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 60,100,160, "Mass","Event",true,false,2);
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 20,70,110, "Mass","Event",true,false,2);55
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 20,0,40, "Pt","Event",true,false,2);
  //plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 10,0,10, "nJet","Event",true,false,2);
	
  for(int i = 0 ; i < 15 ; i++)
    {
      for(int j = 0 ; j < nf ; j++)
	{
	  /*if(i==0)var[j] = "mclepPt[0]";
	    else if(i==1)var[j] = "mclepPt[1]";
	  else if(i==2)var[j] = "mcmllpt";
	  else if(i==3)var[j] = "mcmllgpt";
	  else if(i==4)var[j] = "mcphoPt";
	  else if(i==5)var[j] = "mcmllPhi";
	  else if(i==6)var[j] = "mcphoPhi";
	  else if(i==7)var[j] = "mclepPhi[0]";
	  else if(i==8)var[j] = "mclepPhi[1]";
	  else if(i==9)var[j] = "mcmllEta";
	  else if(i==10)var[j] = "mcphoEta";
	  else if(i==11)var[j] = "mclepEta[0]";
	  else if(i==12)var[j] = "mclepEta[1]";
	  else if(i==13)var[j] = "mcmll";
	  else if(i==14)var[j] = "mcmllg";
	  else if(i==15)var[j] = "mcphodR";*/
	  //if(i==0Particle.PT
	  if(i==0)var[j] = "absZeppen";
	  if(i==1)var[j] = "absdPhi_Zgjj";
	  if(i==2)var[j] = "absdPhi_jj";
	  if(i==3)var[j] = "absdEta_jj";
	  if(i==4)var[j] = "dR_phojet";
	  if(i==5)var[j] = "ZgPTt";
	    if(i==6)var[j] = "VBFPt1";
	    if(i==7)var[j] = "VBFPt2";
	    if(i==8)var[j] = "mjj";
	    if(i==9)var[j] = "HZgVBF";
	    if(i==10) var[j] = "HZgMVA";
	    if(i==11) var[j] = "VBFPUID1";
	    if(i==12) var[j] = "VBFPUID2";
	    if(i==13) var[j] = "njets";
	    if(i==14) var[j] = "rho";
	  /*if(i==0)var[j] = "NNP";
	    if(i==1)var[j] = "NCH";
	    if(i==2)var[j] = "CHF";
	    if(i==3)var[j] = "NHF";
	    if(i==4)var[j] = "CEF";
	    if(i==5)var[j] = "NEF";
	    if(i==6)var[j] = "MUF";*/
	    /*
	  if(i==0)var[j] = "lepEta1";
	    else if(i==1)var[j] = "lepEta2";
	    else if(i==2) var[j] = "phores";
	    else if(i==3) var[j] = "phoR9";
	    else if(i==4) var[j] = "phoMVA";
	    else if(i==5) var[j] = "cosTheta";
	    else if(i==6) var[j] = "costheta";
	    else if(i==7) var[j] = "Phi";
	    else if(i==8) var[j] = "mllgptdmllg";
	    else if(i==9) var[j] = "dRlg";
	    else if(i==10) var[j] = "phoEta";
	    else if(i==11)var[j] = "phoPt";
	    else if(i==12)var[j] = "lepPt[0]";
	    else if(i==13)var[j] = "lepPt[1]";
	    else if(i==14)var[j] = "HZgMVA";
	    */	  
	}

      outname = "plot/"+ var[0]+"_VBFdijet.pdf";
      //cout<<outname.c_str()<<endl;
      /*if(i<5)plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype, 95 ,10,200, var[0].c_str(),"Event",true,false,2); 
	else if(i<9) plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype, 20,-5,5, var[0].c_str(),"Event",true,false,2); 
	else  if(i<13)plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype, 15,-3,3, var[0].c_str(),"Event",true,false,2); 
	else if(i==13)plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype, 60,60,120, var[0].c_str(),"Event",true,false,2); 
	else if(i==14)plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype,75,50,200, var[0].c_str(),"Event",true,false,2); 
	else plotvar(nf, "tMC", var ,label, fin, outname.c_str(),cuttype,28,0.4,6, var[0].c_str(),"Event",true,false,2); */
      //if(i<2)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 35 ,0,35, var[0].c_str(),"Event",true,false,2); 
      //else plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 25 ,0,1, var[0].c_str(),"Event",true,false,1); 
      /*if(i==0||i==1||i==10||i==7)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 15 ,-3,3, var[0].c_str(),"Event",true,false,2);
      else if(i==2)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 30,0,0.15, var[0].c_str(),"Event",true,false,2);
      else if(i==3||i==4)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 25,0,1, var[0].c_str(),"Event",true,false,2);
	else if(i==5||i==6)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 20,-1,1, var[0].c_str(),"Event",true,false,2);
	else if(i==8)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 40,0,2, var[0].c_str(),"Event",true,false,2);
	else if(i==9)plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 18 ,0.4,4.0, var[0].c_str(),"Event",true,false,2);
	else if(i>10&&i<14)plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 95 ,10,200, var[0].c_str(),"Event",true,false,2);
	else  plotvar(nf, "tMVA", var ,label, fin, outname.c_str(),cuttype, 50,-0.5,0.5, var[0].c_str(),"Event",true,false,2);*/
       //if(i==0)plotvar(nf, "tZg", var ,label, fin, outname.c_str(),cuttype, 30 ,1,30, var[0].c_str(),"Event",true,false,1);
      if(i==0)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 20 ,0,6, var[0].c_str(),"Event",true,false,2);
       else if(i==1||i==2)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 20,0,4, var[0].c_str(),"Event",true,false,2);
	else if(i==3||i==0)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 30,0,9, var[0].c_str(),"Event",true,false,2);
	else if(i==4)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 18 ,0.4,6.0, var[0].c_str(),"Event",true,false,2);
	else if(i==5)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 28 ,0,140., var[0].c_str(),"Event",true,false,2);
	else if(i==6||i==7)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 27 ,30,300., var[0].c_str(),"Event",true,false,2);
	else if(i==8)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 20 ,200,1000., var[0].c_str(),"Event",true,false,2);
	else if(i<13)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype,25 ,-1,1., var[0].c_str(),"Event",true,false,2);
	else if(i==13)plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype,8 ,4,20., var[0].c_str(),"Event",true,false,2);
	else plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype,30 ,0,60., var[0].c_str(),"Event",true,false,2);

      //if(i==9) plotvar(nf, "tVBF", var ,label, fin, outname.c_str(),cuttype, 100,-0.5,0.5, var[0].c_str(),"Event",true,false,2); 

      //cout<<"?"<<endl;
    }
  //void plotvar(int nplot,const char*tree, const char* var ,string *histname, string* finname,  const char *outname, string* cuttype, int hrange, float bin1, float bin2, const char* xaxis, const char* yaxis, bool shape,bool chain,int logxy)

  //effCal("kinMVA_nompho_new","ele","cat==1");
  /*effCal("kinMVA_nompho_new","ele","cat==1");
  effCal("kinMVA_nompho_new","ele","cat==2");
  effCal("kinMVA_nompho_new","ele","cat==3");
  effCal("kinMVA_nompho_new","ele","cat==4");
  effCal("kinMVA_nompho_new","ele","HZgVBF!=-99");
      effCal("kinMVA_nompho_new","ele","cat==6");
      effCal("kinMVA_nompho_new","ele","cat==10");*/
  //effCal(fin[1],"");
  /*effCal(fin[2],"");
    vector<float>bin;
    float max = 2.;
    float min = -5.;
    int i = 0;
    //create unequal bin
    while (min<250)
    {
    if(min<80) min = min +5.;
    else if(min>=80&&min<120) min = min +10.;
    else min = min+13.;
    bin.push_back(min);
    i++;
    //cout<<min<<endl;
    }*/
  //std::copy(bin.begin(),bin.end(),bins);
  //cout<<bins[0]<<" "<<bins[1]<<endl;
  //int nplot,const char*tree, const char* var, string* finname,  const char *outname, string* cuttype, int hrange, float bin1, float bin2, const char* xaxis, const char* yaxis, string label
  //  eff(3,"tZg","Zpt",fin,"trueIP_Zpt_eff_ele.pdf",cuttype,50,0,250,"Z_{p_{T}}[GeV/c]","Eff",label);
  //string cat[] = {"Untagged 1","Untagged 2", "Untagged 3", "Untagged 4","VBF Tag", "lepton Tag", "Boosted Tag", "B Tag","Total","double B Tag"};
  //string cat[] = {"Lepton","VBF-VBF ","VH","VBF-ggF ","boosted","Untagged 1","Untagged 2", "Untagged 3", "Untagged 4"};
  string cat[] = {"Lepton","VBF-VBF ","VBF-ggF","Boosted","Untagged 1","Untagged 2", "Untagged 3", "Untagged 4"};
  //string cat[] = {"Lepton","VBF","Boost","Untagged 1","Untagged 2", "Untagged 3", "Untagged 4"};
  //purity("Legacy16_newpt","purity_MVA16",cat,8);
}

//  LocalWords:  cuttype png
