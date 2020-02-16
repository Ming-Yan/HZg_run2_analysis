//--------USAGE------//
//root -l -b -q make_Cards2_sep.C\(\"fin\"\,\"ele\"\,\"11\"\)
//making signal pdf-interpolation and datacards
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../plugin/tdrstyle.C"
//#include "../plugin/CMS_lumi.C"
#include "make_Sig.h"

using namespace RooFit ;
using namespace std;

void make_Cards2_sep(string fin,string type, bool makedir, bool isboost, int period, int cat = 1, float kinup = 1.0, float kindown = -1.0, float kincut=-0.001,float VBFcut=0.08,string vername="_wboost")
{

  ///signal yield for different production channel
  //-----------------------//
  //ggF->VBF->ttH->ZH->WH
  //0-4 120   //
  //5-9 125   //
  //10-14 130 //
  //-----------------------//

  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
  string channel[5] = {"ggF", "VBF","ttH", "ZH", "W*H"};
  char input[1000];
  if(makedir==true)
    {
      char file[200];
      sprintf(file,"mkdir -p /afs/cern.ch/work/m/milee/MYcode/limit/sig/%s%s/",fin.c_str(),vername.c_str());
      system(file);
      sprintf(file,"mkdir -p /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/%s%s/",fin.c_str(),vername.c_str());
      system(file);
      sprintf(file,"mkdir -p /afs/cern.ch/work/m/milee/MYcode/limit/DataCards/%s%s/",fin.c_str(),vername.c_str());
      system(file); 
      sprintf(file,"mkdir -p /afs/cern.ch/work/m/milee/MYcode/limit/plot/fit/%s%s/",fin.c_str(),vername.c_str());
      system(file); 
    }
	  
  
  sprintf(input,"sig/%s%s/Higgs_yield_%s_%s_%d.txt",fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(),cat);
  //wboost_comb_newcat0248
  //sprintf(input,"sig/kinMVA_nompho_nocut/Higgs_yield_kinMVA_nompho_%s_%d.txt",/*fin.c_str(),*/type.c_str(),cat);
  cout<<input<<endl;
  //sprintf(input,"sig/Legacy16_allMVA_refit_wboost_comb_newcat0248/Higgs_yield_Legacy16_allMVA_%s_%d.txt",type.c_str(),cat);//20190120ver
  //sprintf(input,"sig/Legacy16_allMVA_refit_tag/Higgs_yield_Legacy16_allMVA_%s_%d.txt",type.c_str(),cat);//20190120ver
  
  //Yield(vername,fin,type,period,cat,isboost,kinup,kindown,kincut,VBFcut);
  ifstream in;
  in.open(input);
  double total[15];
  float a;
  float phocov = (period==16) ?0.969:0.970;
  for (int i = 0;i<15;i++)
    { 
      in>>a;
      total[i] = a/phocov;
      cout<<total[i]<<endl;
    }
        
  // do intepolation
  double sigRate[55];
  for(int n = 0 ; n < 5 ; n ++)
    {
      for(int m = 0; m < 11; m++)
	{
	  double mass = 120 + m;
			  
	  if (mass < 125) sigRate[n*11+m] = IntSigRate(m, total[n], total[5+n]);
	  if (mass >= 125) sigRate[n*11+m] = IntSigRate(m, total[5+n], total[10+n]);
	}
     }
  for(int n = 0; n < 5; n++) {  
    if(cat != 6789&& n>1) continue;
    else if(cat==6789 &&n<=1) continue;
    make_Sig(vername, fin, channel[n],period, 120, type , cat, isboost, kinup, kindown, kincut, VBFcut);
    make_Sig(vername, fin, channel[n], period, 125, type , cat, isboost, kinup, kindown, kincut, VBFcut);
    make_Sig(vername,fin, channel[n], period,130, type , cat, isboost, kinup, kindown, kincut, VBFcut);
    interpolate2(vername, fin, type, channel[n], cat,period);
    } 
  
		  
	      
  for (int m = 0; m < 11; m++)//loop for different mass point
    {
      TString datacard;
      datacard += "imax 1   number of channels\n";
      datacard += "jmax *   number of process minus 1\n";
      datacard += "kmax *   number of nuisance parameters (sources of systematic uncertainty)\n";
      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("shapes bgr        cat%d  ../../PDFs/%s%s/bkg_%s_WS_%s_cat%d_20%d.root w:BkgPdf_2016_%s_cat%d\n"
      ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,period,type.c_str(),cat,period);
      //datacard += TString::Format("shapes bgr        cat%d  ../../bkgmodel/%s%s/bkg_%s_%d.root  multipdf:CMS_hzg_%s_cat%d_%d_13TeV_bkgshape\n"
      //,cat,fin.c_str(),vername.c_str(),type.c_str(), cat, type.c_str(),cat,period);
      datacard += TString::Format("shapes data_obs   cat%d    ../../PDFs/%s%s/bkg_%s_WS_%s_cat%d_20%d.root w:data_obs_%s_cat%d\n"
      //,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,period,type.c_str(),cat,period);
      datacard += TString::Format("shapes data_obs        cat%d  ../../bkgmodel/%s%s/bkg_%s_%d.root  multipdf:roohist_data_mass_%s_cat%d_%d\n"
      ,cat,fin.c_str(),vername.c_str(),type.c_str(), cat, type.c_str(),cat, period);
      const char* name2 = name[m];
      cout<<name2<<endl;
      if (name[m] != "120" && name[m] != "125" && name[m] != "130")
	{
	  //fin = "kinMVA_nompho_nocut";
	  //fin = "Legacy16_allMVA"; vername = "_refit_wboost_comb_newcat0248";
	  if(cat == 6789)
	    {

	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_WH_%d_%s_%d.root :newPdf_%s_WH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ttH_%d_%s_%d.root :newPdf_%s_ttH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ttH_%d_%s_%d.root :newPdf_%s_ttH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d     ../../PDFs/%s%s/WS_%s_%s_ZH_%d_%s_%d.root :newPdf_%s_ZH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_WH_%d_%s_%d.root :newPdf_%s_WH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	    }
	  else if(cat == 501 || cat == 502)
	    {
	      
	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	    }
	  else 
	    {
	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d     ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(),name2,cat,period);
	    }
	} 
      else
	{
	  //fin = "Legacy16_allMVA"; vername = "_refit_wboost_comb_newcat0248";
	  if(cat==6789)
	    {
	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_WH_%d_%s_%d.root :newPdf_%s_WH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(),cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ttH_%d_%s_%d.root :newPdf_%s_ttH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(),cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ttH_%d_%s_%d.root :newPdf_%s_ttH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d     ../../PDFs/%s%s/WS_%s_%s_ZH_%d_%s_%d.root :newPdf_%s_ZH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_WH_%d_%s_%d.root :newPdf_%s_WH_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	    }
	  else if(cat ==501||cat== 502)
	    {
	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d     ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	    }
	  else 
	    { 
	      datacard += TString::Format("shapes ggH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes qqH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_VBF_%d_%s_%d.root :newPdf_%s_VBF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ttH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat, name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes ZH_hzg        cat%d     ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(), fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	      datacard += TString::Format("shapes WH_hzg        cat%d    ../../PDFs/%s%s/WS_%s_%s_ggF_%d_%s_%d.root :newPdf_%s_ggF_m%s_cat%d_%d\n"
					  ,cat,fin.c_str(),vername.c_str(), fin.c_str(),type.c_str(), cat,name2,period,type.c_str(), name2,cat,period);
	    }
	}

      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("bin               cat%d\n", cat);
      datacard += "observation       -1\n";
      datacard += "--------------------------------------------------------------------------\n";
      datacard += TString::Format("bin              cat%d               cat%d               cat%d               cat%d               cat%d               cat%d\n",cat,cat,cat,cat,cat,cat);
      datacard +=                 "process          ggH_hzg              qqH_hzg             ttH_hzg              ZH_hzg             WH_hzg             bgr\n";
      datacard +=                 "process          -4                  -3                  -2                  -1                  0                   1\n";
      datacard += TString::Format("rate             %f                  %f                  %f                  %f                  %f                  1.000000\n"
				  ,sigRate[m], sigRate[m+11], sigRate[m+22], sigRate[m+33], sigRate[m+44]);//if bkg is normalized;
      datacard += "--------------------------------------------------------------------------\n";
      if(period==16)datacard +="lumi_13TeV  lnN               1.025               1.025               1.025               1.025               1.025               -\n";
      else if(period==17) datacard +="lumi_13TeV  lnN               1.023               1.023               1.023               1.023               1.023               -\n";
      datacard +=    "BR_hzg	  lnN	            0.943/1.057	        0.943/1.057	        0.943/1.057	    0.943/1.057   0.943/1.057	    -\n";
      TString theo = "theo_m"+name[m]+".txt";
      ifstream theoin(theo.Data());
      string tstr;
      while(std::getline(theoin,tstr))
	{
	  datacard+= tstr +"\n";
	}
      string cats = std::to_string(cat);
      TString uncerfile = "uncer/cat" + cats +"_"+ type+ "_m"+name[m] +".txt";

      ifstream in(uncerfile.Data());
      string str; 
      while (std::getline(in,str))
	{
	  datacard+= str +"\n";
	  }
      /*if(cat== 5 || cat >100)
	{
	datacard += TString::Format("BkgPdf_2016_p1_%s_cat%d flatParam \n",type.c_str(),cat);
	}
	else 
	{
	datacard += TString::Format("BkgPdf_2016_p0_%s_cat%d flatParam \n",type.c_str(),cat);
	datacard += TString::Format("BkgPdf_2016_p1_%s_cat%d flatParam \n",type.c_str(),cat);
	datacard += TString::Format("BkgPdf_2016_p2_%s_cat%d flatParam \n",type.c_str(),cat);
	if(cat < 10)
	{
	datacard += TString::Format("BkgPdf_2016_p3_%s_cat%d flatParam \n",type.c_str(),cat);
	}
	}*/
      datacard += TString::Format("pdfindex_%s_cat%d_%d_13TeV discrete \n",type.c_str(),cat,period);
//      datacard += TString::Format("CMS_hzg_%s_cat%d_13TeV_bkgshape_norm flatParam\n",type.c_str(),cat);
      
      //if(type=="ele"||type=="ele_mu")datacard += TString::Format("system group = lumi_13TeV CMS_PU_13TeV CMS_HLTeff_e_13TeV CMS_IDeff_g_13TeV CMS_IDeff_e_13TeV CMS_R9_13TeV CMS_JEC_13TeV CMS_JER_13TeV CMS_UE_13TeV CMS_PS_13TeV CMS_hzg_delta_eleEM_mean_ggF_cat%d CMS_hzg_delta_eleEM_mean_VBF_cat%d CMS_hzg_delta_eleEM_mean_ttH_cat%d CMS_hzg_delta_eleEM_mean_ZH_cat%d CMS_hzg_delta_eleEM_mean_WH_cat%d CMS_hzg_delta_eleEM_sigma_ggF_cat%d CMS_hzg_delta_eleEM_sigma_VBF_cat%d CMS_hzg_delta_eleEM_sigma_ttH_cat%d CMS_hzg_delta_eleEM_sigma_WH_cat%d CMS_hzg_delta_eleEM_sigma_ZH_cat%d",cat,cat,cat,cat,cat,cat,cat,cat,cat,cat);
      //else if(type=="mu"||type=="ele_mu")datacard += TString::Format("ystem group = lumi_13TeV CMS_PU_13TeV CMS_HLTeff_e_13TeV CMS_IDeff_g_13TeV CMS_IDeff_e_13TeV CMS_R9_13TeV CMS_JEC_13TeV CMS_JER_13TeV CMS_UE_13TeV CMS_PS_13TeV  CMS_hzg_delta_muRoch_sigma_ggF_cat%d CMS_hzg_delta_muRoch_sigma_VBF_cat%d CMS_hzg_delta_muRoch_sigma_ttH_cat%d CMS_hzg_delta_muRoch_sigma_ZH_cat%d CMS_hzg_delta_muRoch_sigma_WH_cat%d CMS_hzg_delta_muRoch_mean_ggF_cat%d CMS_hzg_delta_muRoch_mean_VBF_cat%d CMS_hzg_delta_muRoch_mean_ttH_cat%d CMS_hzg_delta_muRoch_mean_ZH_cat%d CMS_hzg_delta_muRoch_mean_WH_cat%d \n",cat,cat,cat,cat,cat,cat,cat,cat,cat,cat);
      //datacard += TString::Format("theory group = BR_hzg QCDscale_VH QCDscale_ggH QCDscale_qqH QCDscale_ttH pdf_Higgs_gg pdf_Higgs_qqbar pdf_Higgs_ttH \n");
      //fin  = "Rereco18_16MVA";
std::ofstream outputFileSEB;
      outputFileSEB.open(TString::Format("DataCards/%s%s/card_%s_%s_%d_%s_env.txt", fin.c_str(),vername.c_str(),fin.c_str(),type.c_str(), cat,name2));
      outputFileSEB << datacard;
      outputFileSEB.close();
    }
}

//  LocalWords:  newcat
