void getFWHM()
{
  string cat16[12] = 
    {
      ///====ELECTRON====//
      
      //"(cat==10||cat<5)&&HZgMVA<=-0.0671",
      "(cat==10||cat<5)&&HZgMVA>0.0565",
      "(cat==10||cat<5)&&HZgMVA<=0.0565&&HZgMVA>0.0447",
      "(cat==10||cat<5)&&HZgMVA<=0.0447&&HZgMVA>0.0083",
      "(cat==10||cat<5)&&HZgMVA<=0.0083&&HZgMVA>-0.0671",  
      ///====MUON====//
      "(cat==10||cat<5)&&HZgMVA>0.071",
      //"(cat==10||cat<5)&&HZgMVA<=-0.0716",
      "(cat==10||cat<5)&&HZgMVA<=0.071&&HZgMVA>0.0329",
      "(cat==10||cat<5)&&HZgMVA<=0.0329&&HZgMVA>-0.0119",
      "(cat==10||cat<5)&&HZgMVA<=-0.0119&&HZgMVA>-0.0716", 
      ///===>lepton&VBF<===//   
      "HZgVBF>0.122426&&cat==5",
      "HZgVBF<=0.122426&&HZgVBF>0.0436731&&cat==5",
      "HZgVBF<=0.0436731&&cat==5",
      "(cat>5&&cat<10)",
      
    };
  string cat17[12]={
    ///====ELECTRON====//
    //"(cat==10||cat<5)&&HZgMVA<=-0.0582",
    "(cat==10||cat<5)&&HZgMVA>0.0914",
    "(cat==10||cat<5)&&HZgMVA<=0.0914&&HZgMVA>0.0535",
    "(cat==10||cat<5)&&HZgMVA<=0.0535&&HZgMVA>0.0004",
    "(cat==10||cat<5)&&HZgMVA<=0.0004&&HZgMVA>-0.0582",  
    ///====MUON====//
    "(cat==10||cat<5)&&HZgMVA>0.0891",
    //"(cat==10||cat<5)&&HZgMVA<=-0.0645",
    "(cat==10||cat<5)&&HZgMVA<=0.0891&&HZgMVA>0.0521",
    "(cat==10||cat<5)&&HZgMVA<=0.0521&&HZgMVA>0.0133",
    "(cat==10||cat<5)&&HZgMVA<=0.0133&&HZgMVA>-0.0645", 
    ///===>lepton&VBF<===//   
    "HZgVBF>0.133103&&cat==5",
    "HZgVBF<=0.133103&&HZgVBF>0.0318622&&cat==5",
    "HZgVBF<=0.0318622&&cat==5",
    "(cat>5&&cat<10)",
  };
  string cat18[15]={
    ///====ELECTRON====//
    "(cat==10||cat<5)&&HZgMVA>0.1411",
    "(cat==10||cat<5)&&HZgMVA<=0.1411&&HZgMVA>0.102",
    "(cat==10||cat<5)&&HZgMVA<=0.102&&HZgMVA>0.0745",
    "(cat==10||cat<5)&&HZgMVA<=0.0745&&HZgMVA>0.0205",  
    "(cat==10||cat<5)&&HZgMVA<=0.0205&&HZgMVA>-0.0626",  
    ///====MUON====//
    "(cat==10||cat<5)&&HZgMVA>0.1404",
    "(cat==10||cat<5)&&HZgMVA<=0.1404&&HZgMVA>0.0998",
    "(cat==10||cat<5)&&HZgMVA<=0.0998&&HZgMVA>0.0533",
    "(cat==10||cat<5)&&HZgMVA<=0.0533&&HZgMVA>-0.0015", 
    "(cat==10||cat<5)&&HZgMVA<=-0.0015&&HZgMVA>-0.0674", 
    ///===>lepton&VBF<===//   
    "HZgVBF>0.156851&&cat==5",
    "HZgVBF<=0.156851&&HZgVBF>0.0467022&&cat==5",
    "HZgVBF<=0.0467022&&cat==5",
    "HZgVBF<=-0.042305&&cat==5",
    "(cat>5&&cat<10)",
  };

  int cats[10] = {1, 2,3, 4,5, 501, 502, 503, 504,6789};
  int bkgev[6] = {40319,49127,47650,60192,69221,85265};
  string fname[3] = {"Legacy16_newMVA","Rereco17_newMVAv3","Rereco18_newMVAv2"};
  string weight[3] ={"*L1wei","*L1wei*ptwei","*ptwei"};

  TChain sig("tZg"); 
  TChain ggF("tZg");
  TChain VBF("tZg");
  TChain ttH("tZg");
  TChain VH("tZg");
  TChain bkg("tZg"); 
  for(int y = 0; y < 2 ; y++)
    {
      string cat[10];
      for (int c= 0 ; c <10; c++){

  	for (int t = 0 ; t <2 ; t++)
	  {
	    TH1F *h = new TH1F("h","",2200,115,170);
	    TH1F *hggF = new TH1F("hggF","",2200,115,170);
	    TH1F *hVBF = new TH1F("hVBF","",2200,115,170);
	    TH1F *httH = new TH1F("httH","",2200,115,170);
	    TH1F *hVH = new TH1F("hVH","",2200,115,170);

	    //TH1F *h = new TH1F("h","",2400,115,170);
	    TH1F *h1 = new TH1F("h1","",2200,115,170);
	    if(y==0)cat[c] = (c<4)? cat16[t*4+c] : cat16[c+3];
	    if(y==1)cat[c] = (c<4)? cat17[t*4+c] : cat17[c+3] ;
	    if(y<2&&(c==4||c==8)) cat[c] = "HZgMVA==-99";
	    if(y==2)cat[c] = (c<5) ?cat18[t*5+c] : cat18[c+5];
	    if(c==9) cat[c] ="(cat>5&&cat<10)";
	    // if(c==0)cat[c]="(cat==10||cat<5)";
	    // else cat[c]="cat==5";
	    if(c==9) 
	      {
		ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV.root",fname[y].c_str()));
		ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV.root",fname[y].c_str()));
		VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname[y].c_str()));
		VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname[y].c_str()));
		ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ttH_125GeV.root",fname[y].c_str()));
		ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ttH_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_W*H_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_W*H_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ZH_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ZH_125GeV.root",fname[y].c_str()));
  		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ttH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ZH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WplusH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WminusH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ttH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ZH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WplusH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WminusH_125GeV.root",fname[y].c_str()));
		bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_ele_EG.root",fname[y].c_str()));
		bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_mu_Mu.root",fname[y].c_str()));
	      }
	    else if(t==0){
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV.root",fname[y].c_str()));
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname[y].c_str()));
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ttH_125GeV.root",fname[y].c_str()));
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ZH_125GeV.root",fname[y].c_str()));
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WplusH_125GeV.root",fname[y].c_str()));
	      sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_WminusH_125GeV.root",fname[y].c_str()));
	      ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ggF_125GeV.root",fname[y].c_str()));
	      VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_VBF_125GeV.root",fname[y].c_str()));
	      ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ttH_125GeV.root",fname[y].c_str()));
	      VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_W*H_125GeV.root",fname[y].c_str()));
	      VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_ele_HZg_ZH_125GeV.root",fname[y].c_str()));

	      bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_ele_EG.root",fname[y].c_str()));
	    }
	    else if(t==1)
	      {
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ttH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ZH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WplusH_125GeV.root",fname[y].c_str()));
		sig.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_WminusH_125GeV.root",fname[y].c_str()));
		bkg.Add(Form("/afs/cern.ch/work/m/milee/outfile/Data_%s_mu_Mu.root",fname[y].c_str()));
		ggF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ggF_125GeV.root",fname[y].c_str()));
		VBF.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_VBF_125GeV.root",fname[y].c_str()));
		ttH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ttH_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_W*H_125GeV.root",fname[y].c_str()));
		VH.Add(Form("/afs/cern.ch/work/m/milee/outfile/mc_%s_mu_HZg_ZH_125GeV.root",fname[y].c_str()));

	      }	
	    float numb = 0., nums = 0.;
	   
	    sig.Draw("REFITmllg>>h",Form("(%s&&REFITmllg>115&&REFITmllg<170)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),weight[y].c_str()));
	    // sig.Draw("mll>>h",Form("(%s)*mcwei*puwei*genwei%s",cat[c].c_str(),weight[y].c_str()));
	    bkg.Draw("REFITmllg>>h1",Form("%s",cat[c].c_str()));

	    cout<<h->Integral()<<endl;
	    const int n=10000;
	    double x[n],y1[n];
	    for(int i=0 ; i<10000;i++)x[i]=float(i+1)/n;  
	    h->GetQuantiles(n,y1,x);
	    string var= (t==0) ?"ele":"mu";
	    cout<<int(2016+y)<<" "<<var<<cats[c]<<" "<<cat[c]<<endl;
	    cout<<"15.87% :"<<y1[1587]<<endl;
	    cout<<"84.13% :"<<y1[8413]<<endl;
	    cout<<"1 sigma"<<(y1[8413]-y1[1587])/2.<<""<<endl;
	    cout<<"3 sigma"<<(y1[13]-y1[9987])/2.<<""<<endl;
	    cout<<"bkg frac(all range): "<<float(h1->Integral())/float(bkgev[y*2+t])<<endl;; 
	    // cout<<h1->Integral()<<" "<<bkgev[y*2+t]<<endl;
	    // cout<<"signal yield:"<<h->Integral()<<endl;
	    // cout<<"ggF"

	    sig.Draw("REFITmllg>>h",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),y1[13],y1[9987],weight[y].c_str()));
	    bkg.Draw("REFITmllg>>h1",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)",cat[c].c_str(),y1[13],y1[9987]));
	    ggF.Draw("REFITmllg>>hggF",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),y1[1587],y1[8413],weight[y].c_str()));
	    VBF.Draw("REFITmllg>>hVBF",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),y1[1587],y1[8413],weight[y].c_str()));
	    ttH.Draw("REFITmllg>>httH",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),y1[1587],y1[8413],weight[y].c_str()));
	    VH.Draw("REFITmllg>>hVH",Form("(%s&&REFITmllg>%.2f&&REFITmllg<%.2f)*mcwei*puwei*genwei*totSF%s",cat[c].c_str(),y1[1587],y1[8413],weight[y].c_str()));
	    cout<<"ggF\tVBF\tttH+VH"<<endl;
	    cout<<hggF->Integral()/0.969<<"\t"<<hVBF->Integral()/0.969<<"\t"<<(httH->Integral()+hVH->Integral())/0.969<<endl;
     	    cout<<"signal yield:"<<h->Integral()/0.97<<endl;
	    cout<<"bkg events: "<<h1->Integral()<<endl;
	    cout<<"s2/b: "<<h->Integral()*h->Integral()/h1->Integral()<<endl;
	    cout<<"================"<<endl;
	    sig.Reset();
	    bkg.Reset();
	    ggF.Reset();
	    VBF.Reset();
	    ttH.Reset();
	    VH.Reset();
	  }
      }

  		
  
    }
    
}
