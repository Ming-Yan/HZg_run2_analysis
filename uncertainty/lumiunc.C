void lumiunc()
{
  float uncor[3]={2.2,2.0,1.5};
  float xy[3] = {0.9,0.8,2.0};
  float scale[3] = {0.0,0.3,0.2};
  float deflect[3] = {0.4,0.4,0.0};
  float dyna[3]={0.5,0.5,0.0};
  float calib[3]={0.0,0.3,0.2};
  float sat[3]={0.4,0.1,0.0 };
  for(int y = 0 ; y < 4; y++)
    {

      string fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/lumi_"+std::to_string(y+2016)+".txt";
      ofstream out(fname.c_str());
      out<<"lumi_13TeV_"<<std::to_string(y+2016)<<"	lnN	"<<std::to_string(1+0.01*uncor[y])<<"\t"<<std::to_string(1+0.01*uncor[y])<<"\t"<<std::to_string(1+0.01*uncor[y])<<"\t"<<std::to_string(1+0.01*uncor[y])<<"\t"<<std::to_string(1+0.01*uncor[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_xy	lnN	"<<std::to_string(1+0.01*xy[y])<<"\t"<<std::to_string(1+0.01*xy[y])<<"\t"<<std::to_string(1+0.01*xy[y])<<"\t"<<std::to_string(1+0.01*xy[y])<<"\t"<<std::to_string(1+0.01*xy[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_sc	lnN	"<<std::to_string(1+0.01*scale[y])<<"\t"<<std::to_string(1+0.01*scale[y])<<"\t"<<std::to_string(1+0.01*scale[y])<<"\t"<<std::to_string(1+0.01*scale[y])<<"\t"<<std::to_string(1+0.01*scale[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_deflect	lnN	"<<std::to_string(1+0.01*deflect[y])<<"\t"<<std::to_string(1+0.01*deflect[y])<<"\t"<<std::to_string(1+0.01*deflect[y])<<"\t"<<std::to_string(1+0.01*deflect[y])<<"\t"<<std::to_string(1+0.01*deflect[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_dynamic	lnN	"<<std::to_string(1+0.01*dyna[y])<<"\t"<<std::to_string(1+0.01*dyna[y])<<"\t"<<std::to_string(1+0.01*dyna[y])<<"\t"<<std::to_string(1+0.01*dyna[y])<<"\t"<<std::to_string(1+0.01*dyna[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_calib	lnN	"<<std::to_string(1+0.01*calib[y])<<"\t"<<std::to_string(1+0.01*calib[y])<<"\t"<<std::to_string(1+0.01*calib[y])<<"\t"<<std::to_string(1+0.01*calib[y])<<"\t"<<std::to_string(1+0.01*calib[y])<<"\t"<<"-"<<endl;
      out<<"lumi_13TeV_sat	lnN	"<<std::to_string(1+0.01*sat[y])<<"\t"<<std::to_string(1+0.01*sat[y])<<"\t"<<std::to_string(1+0.01*sat[y])<<"\t"<<std::to_string(1+0.01*sat[y])<<"\t"<<std::to_string(1+0.01*sat[y])<<"\t"<<"-"<<endl;

    }
}
