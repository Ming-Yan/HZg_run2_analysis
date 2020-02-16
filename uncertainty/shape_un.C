//--------Usage------//
//making signal pdf-interpolation and datacards
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../plugin/tdrstyle.C"
//#include "../plugin/CMS_lumi.C"
#include "unc_fit.h"
using namespace RooFit ;
using namespace std;

void shape_uns(string fin,string type, bool makedir, bool isboost, int period, int cat, vector<vector<float>> &un_means, vector<vector<float>> &un_reses ,string vername="_wboost_comb_newcat01379",bool isres = false, float kinup = 1.0, float kindown = -1.0, float kincut=-0.001,float VBFcut=0.08)
{
  //if(isres)cout<<"============================="<<endl;

  // gROOT->ProcessLine( "gErrorIgnoreLevel = 2001;");

  string dirname = "mkdir -p sig/" +fin+vername;
  system(dirname.c_str());
  dirname = "mkdir -p plot/" +fin+vername;
  system(dirname.c_str());
  un_means.clear(); un_reses.clear();
  string channel[5] = {"ggF", "VBF","ttH", "ZH", "WH"};

  // do intepolation
  for(int n = 0; n < 5; n++) {  
    if(cat<503&&n>1)continue;
    else if(cat==6789&&n<2) continue;
    vector <float> un_mean, un_res;un_mean.clear();un_res.clear();
    for (int ma = 0; ma < 3 ; ma++){
      int m = 120+ma*5;
      float un_mean_= 0, un_res_=0;
      string txtname = "sig/"+ fin  + vername  + "/HiggsMass_signal_" + fin+ "_" +type + "_" + channel[n] + "_" + std::to_string(cat) + "_" + std::to_string(m) + "_" + std::to_string(period) + ".txt";
      cout<<txtname<<endl;
      make_Sig(vername, fin, channel[n],period, m, type , cat, isboost, kinup, kindown, kincut, VBFcut);
      unc_fit(txtname, m,period, channel[n], type, cat, fin,vername, &un_mean_, &un_res_,isres);
      un_mean.push_back(un_mean_);
      un_res.push_back(un_res_);    
    }
    un_reses.push_back(un_res);
    un_means.push_back(un_mean);
  }
}
void shape_un(int nsource )
{
  string type[2] = {"ele","mu"};
  string outname;
  if(nsource==10) outname = "phoshape_";
  if(nsource==1) outname = "lepres_";
  if(nsource==2) outname = "lepsc_";
  int cat[8] = {6789, 501, 502, 1,2,3,4,5};
  string fname[3] = {"Legacy16_newMVA","Rereco17_newMVA","Rereco18_newMVA"};
  float mvacuts[15] = 
    {
      //2016
      0.0832,
      0.0649,
      0.0517,
      0.0136,
      -0.0645,
      //2017
      0.1036,
      0.07,
      0.0505,
      -0.0154,
      -0.0884,
      //2018
      0.1619,
      0.1192,
      0.0649,
      0.0072,
      -0.0601
    };
  for(int p = 0; p < 3; p++)//period
    {
      for (int t =0; t < 2 ; t++)//type electron or muon
	{
	  for (int c = 0 ; c < 8; c++)//categories
	    {
	      float tmpun_res[15] = {0}, tmpun_mean[15] = {0.}, err_sigma[15] = {0},err_mean[15] = {0};
	      vector<TH1F*> hres, hmean; hres.clear(); hmean.clear();
	      vector<float> fmean, fsigma; fmean.clear(); fsigma.clear();
	      for (int u = 0 ; u < nsource; u++)//different sources
		{
		  string vername;
		  bool isboost = false;
		  if(nsource==10)vername = "_pho"+std::to_string(u);  
		  else if(nsource==1)vername = "_nocorr";
		  else if(nsource==2)vername = "_refitlep"+std::to_string(u); 
		  vector<vector<float>> un_mean; un_mean.clear();
		  vector<vector<float>> un_res; un_res.clear();
		  bool issig = false;

		  if(u>5||nsource==2) issig= true;
		  if(c<3)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig);
		  else if(c==3)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig,1.0,mvacuts[p*5]);
		  else if(c==4)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig,mvacuts[p*5],mvacuts[p*5+1]);
		  else if(c==5)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig,mvacuts[p*5+1],mvacuts[p*5+2]);
		  else if(c==6)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig,mvacuts[p*5+2],mvacuts[p*5+3]);
		  else if(c==7)shape_uns(fname[p],type[t],1,isboost,p+2016,cat[c],un_mean,un_res,vername,issig,mvacuts[p*5+3],mvacuts[p*5+4]);
        
            //for electron, photon only

		  for (int ch = 0 ; ch < un_mean.size(); ch++)
		    {
		      for (int m = 0 ; m < un_mean[ch].size(); m++)
			{
			  //photon / electron uncertainties
			  if(nsource==10){
			    if(u==0){err_mean[3*ch+m]=err_sigma[3*ch+m]=0.;}		    
			    if(u<6){

			      if(u%2==0)
				{
				  tmpun_mean[3*ch+m] = 0.;
				  tmpun_mean[3*ch+m] = fabs(un_mean[ch][m]);
				}
			      else if(fabs(un_mean[ch][m])>tmpun_mean[3*ch+m]) tmpun_mean[3*ch+m] =fabs(un_mean[ch][m]);
			      err_mean[3*ch+m] = err_mean[3*ch+m] + tmpun_mean[3*ch+m];
			      if(u==5){fmean.push_back(err_mean[3*ch+m]+1.);cout<<err_mean[3*ch+m]<<endl;}
			    }
			    else
			      {
				if(u%2==0)
				  {
				    tmpun_res[3*ch+m] = 0.;
				    tmpun_res[3*ch+m] = fabs(un_res[ch][m]);
				  }
				else if(fabs(un_res[ch][m])) tmpun_res[3*ch+m] = fabs(un_res[ch][m]);
				cout<<tmpun_res[3*ch+m]<<endl;
				err_sigma[3*ch+m] = err_sigma[3*ch+m] + tmpun_res[3*ch+m];
				if(u==9){fsigma.push_back(err_sigma[3*ch+m]+1.);cout<<err_sigma[3*ch+m]<<endl;}
			      }  
			  }
			  else if(nsource==2)
			    {
		    	
			      if(u%2==0)
				{
				  tmpun_mean[3*ch+m] = 0.;
				  tmpun_mean[3*ch+m] = fabs(un_mean[ch][m]);
				}
			      else if(fabs(un_mean[ch][m])>tmpun_mean[3*ch+m]) tmpun_mean[3*ch+m] =fabs(un_mean[ch][m]);
			      err_mean[3*ch+m] = tmpun_mean[3*ch+m];
			      if(u==1){fmean.push_back(err_mean[3*ch+m]);cout<<err_mean[3*ch+m]<<endl;}
			    }
			  else if(nsource==1)
			    {
                    err_sigma[3*ch+m] = fabs(un_res[ch][m]);
                    fsigma.push_back(err_sigma[3*ch+m]);
                    cout<<err_sigma[3*ch+m]<<endl;
                }
			}
		    }
        }
		  for (int m = 0 ; m < 3; m++)
		    {
		      string fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/"+outname+ "_"+ type[t]+ "_cat" + std::to_string(cat[c])+"_m"+  std::to_string(120+m*5)+ "_"+std::to_string(2016+p) +".txt";
		      ofstream out(fname.c_str(), std::ios_base::out);
		      if(nsource==10){
                  if(c!=0){
		    out<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[m]<<endl;
		    cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[3+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[3+m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[3+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[3+m]<<endl;
			}
			else{
                cout<<type[t]<<" "<<cat[c]<<" "<<fmean[m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[3+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[3+m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[6+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fmean[6+m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[3+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[3+m]<<endl;
			  out<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[6+m]<<endl;
			  cout<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  1	"<<fsigma[6+m]<<endl;
			}
		}
		      else if(nsource==2)
			{
			  if(c!=0){
			    out<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[m]<<endl;
			    cout<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[m]<<endl;	
			    out<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[3+m]<<endl;
			    cout<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[3+m]<<endl;	
			  }
			  else
			    {
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[m]<<endl;
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[3+m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[3+m]<<endl;
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[6+m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fmean[6+m]<<endl;
			    }
			}
		      else if(nsource==1)
			{
			  if(c!=0){
			    out<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[m]<<endl;
			    cout<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ggF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[m]<<endl;	
			    out<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[3+m]<<endl;
			    cout<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_VBF_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[3+m]<<endl;	
			  }
			  else
			    {
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ttH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[m]<<endl;
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[3+m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ZH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[3+m]<<endl;
//                    cout<<fsigma[6+m]<<endl;
			      out<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[6+m]<<endl;
			      cout<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_WH_m"<<std::to_string(120+m*5)<<"_cat"<<cat[c]<<"  param  0	"<<fsigma[6+m]<<endl;
			    }
			}
		      if(m>0){
			for(int m1 = 0; m1 < 4; m1++)
            {
	      string fname2 = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/"+outname+ "_"+ type[t]+ "_cat"  + std::to_string(cat[c])+"_m"+  std::to_string(121+(m-1)*5+m1)+ "_"+std::to_string(2016+p) +".txt";

			    ofstream out2(fname2.c_str(), std::ios_base::out);
			    if(nsource==10){
			      if(c!=0){
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ggF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fmean[m-1]+float(4-m1)/5.*fmean[m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_VBF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fmean[3+m-1]+float(4-m1)/5.*fmean[3+m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ggF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fsigma[m-1]+float(4-m1)/5.*fsigma[m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_VBF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fsigma[3+m-1]+float(4-m1)/5.*fsigma[3+m]<<endl;
                      
                  }
			      else{
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ttH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fmean[m-1]+float(4-m1)/5.*fmean[m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_ZH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fmean[3+m-1]+float(4-m1)/5.*fmean[3+m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_mean_WH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fmean[6+m-1]+float(4-m1)/5.*fmean[6+m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ttH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fsigma[m-1]+float(4-m1)/5.*fsigma[m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_ZH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fsigma[3+m-1]+float(4-m1)/5.*fsigma[3+m]<<endl;
				out2<<"CMS_hzg_delta_"<<type[t]<<"Pho_sigma_WH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  1	"<<float(m1+1)/5.*fsigma[6+m-1]+float(4-m1)/5.*fsigma[6+m]<<endl;
			      }
			    }
			    else if(nsource==1)
			      {
				if(c!=0)
				  {
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ggF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fsigma[m-1]+float(4-m1)/5.*fsigma[m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_VBF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fsigma[3+m-1]+float(4-m1)/5.*fsigma[3+m]<<endl;
				  }
				else 
				  {
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ttH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fsigma[m-1]+float(4-m1)/5.*fsigma[m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_ZH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fsigma[3+m-1]+float(4-m1)/5.*fsigma[3+m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_sigma_WH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fsigma[6+m-1]+float(4-m1)/5.*fsigma[6+m]<<endl;
				    }
			      }
			    else if(nsource==2)
			      {
				if(c!=0)
				  {
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ggF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fmean[m-1]+float(4-m1)/5.*fmean[m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_VBF_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fmean[3+m-1]+float(4-m1)/5.*fmean[3+m]<<endl;
				  }
				else 
				  {
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ttH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fmean[m-1]+float(4-m1)/5.*fmean[m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_ZH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fmean[3+m-1]+float(4-m1)/5.*fmean[3+m]<<endl;
				    out2<<"CMS_hzg_delta_"<<type[t]<<"lep_mean_WH_m"<<std::to_string(121+(m-1)*5+m1)<<"_cat"<<cat[c]<<"  param  0	"<<float(m1+1)/5.*fmean[6+m-1]+float(4-m1)/5.*fmean[6+m]<<endl;
				  }
			      }
			  }
		      }
		    }
        
	    }
	}
    }
}

  //  LocalWords:  issig
