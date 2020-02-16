void fit(int j,string type,int cat,int pdf,int mu)
{
  TFile *fin =TFile::Open(Form("results_2016_13TeV_123%d/higgsCombine_%s_cat%d_env_pdf%d_mu%d.MultiDimFit.mH125.123456.root",j,type.c_str(),cat,pdf,mu));
  RooWorkspace *win = (RooWorkspace*)fin->Get("w");   RooRealVar *mass = win->var("CMS_hzg_mass"); 
  RooWorkspace *win2 = win;    
  //win->loadSnapshot("MultiDimFit"); 
  RooFitResult *fit_s = 0;
  RooCategory *chan = win->cat("CMS_channel");
  RooAbsData *datain = win2->data("data_obs");

  RooDataSet *data = new RooDataSet("data_obs_unbinned","",*datain->get());
  RooRealVar *r = win->var("r");
  std::cout << " VALUES OF r " << r->getVal() <<std::endl;

  RooSimultaneous *sbpdf = (RooSimultaneous*)win->pdf("model_s");
  RooSimultaneous *bpdf = (RooSimultaneous*)win->pdf("model_b");
  std::cout << "[INFO]  get pdfs " << sbpdf << " " << bpdf << std::endl; 
  RooAbsPdf *bcatpdf = bpdf->getPdf(chan->getLabel());
  RooAbsPdf *sbcatpdf = sbpdf->getPdf(chan->getLabel());
  bcatpdf->Print();
  sbcatpdf->Print();
  mass->SetTitle("#m_{Z#gamma}");
  mass->setUnit("GeV");

  RooPlot *catplot = mass->frame(115.,170.,220);
  datain->plotOn(catplot);
  bcatpdf->plotOn(catplot);//,Normalization(bcatpdf->expectedEvents(data->get()),RooAbsPdf::NumEvent),LineColor(kRed),LineStyle(kDashed));
  sbcatpdf->plotOn(catplot);//,Normalization(sbcatpdf->expectedEvents(data->get()),RooAbsPdf::NumEvent),LineColor(kBlue));
  catplot->Draw();
  gPad->Print(Form("results_2016_13TeV_123%d/%s_cat%d_pdf%d_mu%d.png",j,type.c_str(),cat,pdf,mu)); 
  fin->Close();
  //delete fin; delete win; delete win2; delete fit_s; delete datain; delete r; delete sbpdf; delete bpdf; delete catplot; delete mass;
  }
  
  void getfit()
  {
      //ele1-
      int pdfs[15] = {6,5,5,4,4,5,6,5,6,5,5,4,5,5,5}; 
      int cats[8] = {1,3,4,5,10,501,502,6789};
      for (int j =0 ; j < 50; j++)
      {
          for (int mu = 0 ; mu < 2; mu++)
          {
   
           for (int cat = 0; cat < 5 ; cat++)
           {
               for(int pdf = 0 ; pdf < pdfs[cat]; pdf++){
		 TFile *fin =TFile::Open(Form("results_2016_13TeV_123%d/higgsCombine_ele_cat%d_env_pdf%d_mu%d.MultiDimFit.mH125.123456.root",j,cats[cat],pdf,mu));
		 fin->Print();
		 if (!fin->IsZombie())fit(j,"ele",cats[cat],pdf,mu);
		 else continue;
		 fin->Close();
		 delete fin;
	       }
	       for(int pdf = 0 ; pdf < pdfs[cat+8]; pdf++){
		 TFile *fin1 =TFile::Open(Form("results_2016_13TeV_123%d/higgsCombine_mu_cat%d_env_pdf%d_mu%d.MultiDimFit.mH125.123456.root",j,cats[cat],pdf,mu));
		 if (!fin1->IsZombie()){cout<<"HIHI"<<endl;fit(j,"mu",cats[cat],pdf,mu);}
		 else continue;
		 fin1->Close();
		 delete fin1;
	       }               
             
          }
      }
          
  }
  }
