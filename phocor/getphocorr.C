void getphocorr(int period)
{  
  TFile *f = TFile::Open(Form("data_%d_photonTnP.root",period));
  TChain tmc("tnp");
  tmc.Add(Form("MC_%d_photonTnP.root",period));
  tmc.Add(Form("TT_%d_photonTnP.root",period));
  //tmc.Add(Form("WJets_%d_photonTnP.root",period));
  //TFile *fmc = TFile::Open(Form("MC_%d_photonTnP.root",period));
  TTree *t = (TTree*)f->Get("tnp");
  //TTree *tmc = (TTree*)fmc->Get("tnp");

  TH1F *hr9e = new TH1F("hr9e","",1050,0.4,1.1);
  TH1F *hr9_mce = new TH1F("hr9_mce","",1050,0.4,1.1);
  TH1F *hr9b = new TH1F("hr9b","",1050,0.4,1.1);
  TH1F *hr9_mcb = new TH1F("hr9_mcb","",1050,0.4,1.1);
  TH1F *hr9b2 = new TH1F("hr9b2","",140,0.5,1);
  TH1F *hr9_mcb2 = new TH1F("hr9_mcb2","",140,0.5,1);
  TH1F *hrese = new TH1F("hrese","",100,0.0,0.16);
  TH1F *hres_mce = new TH1F("hres_mce","",100,0.0,0.16);
  TH1F *hresb = new TH1F("hresb","",100,0.0,0.16);
  TH1F *hres_mcb = new TH1F("hres_mcb","",100,0,0.16);
  TH1F *hptb = new TH1F("hptb", "",1000,0,200);
  TH1F *hpte = new TH1F("hpte", "",1000,0,200);
  TH1F *hpt_mcb = new TH1F("hpt_mcb", "",1000,0,200);
  TH1F *hpt_mce = new TH1F("hpt_mce", "",1000,0,200);
  TH1F *pt = new TH1F("pt", "",1000,0,200);

  float phores, phoR9, phoEta,phoPt,genwei,mcwei,puwei;
  //tmc.SetBranchAddress("phores", &phores); 
  tmc.SetBranchAddress("phoR9", &phoR9); 
  tmc.SetBranchAddress("phoEta", &phoEta); 
  tmc.SetBranchAddress("phoPt",  &phoPt);
  tmc.SetBranchAddress("mcwei",  &mcwei);
  tmc.SetBranchAddress("genwei",  &genwei);
  tmc.SetBranchAddress("puwei",  &puwei);
  //t->SetBranchAddress("phores", &phores); 
  t->SetBranchAddress("phoR9", &phoR9); 
  t->SetBranchAddress("phoEta", &phoEta); 
  t->SetBranchAddress("phoPt",  &phoPt);  

 for(Long64_t ev = 0; ev < tmc.GetEntriesFast(); ev++)
  {
    tmc.GetEntry(ev);
    if(ev%2==0) continue;
    //puwei =1.;
    if(fabs(phoEta)>1.566){
      hr9_mce->Fill(phoR9,mcwei*genwei*puwei);//,ptwei_mce->GetBinContent(ptwei_mce->FindBin(phoPt)));
      hres_mce->Fill(phores);//,ptwei_mce->GetBinContent(ptwei_mce->FindBin(phoPt)));
        }
    else if(fabs(phoEta)<1.4442) {
      //if(fabs(phoEta)<1.)hr9_mcb->Fill(phoR9);//,ptwei_mcb->GetBinContent(ptwei_mcb->FindBin(phoPt)));
      //else
      hr9_mcb->Fill(phoR9,mcwei*genwei*puwei);
      hres_mcb->Fill(phores);//,ptwei_mcb->GetBinContent(ptwei_mcb->FindBin(phoPt)));        
    }
  }  

   for(Long64_t ev1 = 0; ev1 < t->GetEntriesFast(); ev1++)
  {
    t->GetEntry(ev1);
    if(ev1%2==0) continue;
    if(fabs(phoEta)>1.566){
      hr9e->Fill(phoR9);//,ptweie->GetBinContent(ptweie->FindBin(phoPt))); 
      hrese->Fill(phores);//,ptweie->GetBinContent(ptweie->FindBin(phoPt)));
    }
    else if(fabs(phoEta)<1.4442){
//        cout<<phoPt<<" "<<ptweib->GetBinContent(1)<<" "<<ptweib->FindBin(phoPt)<<endl;
      //pt->Fill(phoPt,ptweib->GetBinContent(ptweib->FindBin(phoPt)));
      //if(fabs(phoEta)<1.)hr9b->Fill(phoR9);//,ptwei_mcb->GetBinContent(ptwei_mcb->FindBin(phoPt)));
      //else hr9b2->Fill(phoR9);
      hr9b->Fill(phoR9);
      hresb->Fill(phores);//,ptweib->GetBinContent(ptweib->FindBin(phoPt)));
    }
  }  
   const int n=1050;
  double x[n],y[n],xmc[n],ymc[n];
  for(int i=0 ; i<n;i++)
  {
    x[i]=float(i+1.)/n;
    xmc[i] = float(i+1.)/n;
  }

  hr9e->GetQuantiles(n,y,x);
  hr9_mce->GetQuantiles(n,ymc,xmc);
  TGraph *gR9_EE = new TGraph(n,ymc,y);
  gR9_EE->SetName("gR9_EE");
  const int n2=1050;
   double x1[n2],y1[n2],xmc1[n2],ymc1[n2];
   for(int i=0 ; i<n2;i++)
  {
    x1[i]=float(i+1)/n;
    xmc1[i] = x1[i];
  }

   hr9b->GetQuantiles(n2,y1,x1);
   hr9_mcb->GetQuantiles(n2,ymc1,xmc1);
   for(int i=0 ; i<n;i++)
    {
      cout<<y1[i]<<" "<<x1[i]<<" "<<ymc1[i]<<" "<<xmc1[i]<<endl;
    }
   
   TGraph *gR9_EB = new TGraph(n2,ymc1,y1);
   gR9_EB->SetName("gR9_EB");
   //double x4[n2-1],y4[n2-1],xmc4[n2-1],ymc4[n2-1];
   /*for(int i=0 ; i<100;i++)
     {
    x4[i]=float(i+1)/n;
    xmc4[i] = x4[i];
  }
   hr9b2->GetQuantiles(n2-1,y4,x4);
   hr9_mcb2->GetQuantiles(n2-1,ymc4,xmc4);
      TGraph *gR9_EB2 = new TGraph(n2-1,ymc4,y4);
	gR9_EB2->SetName("gR9_EB2");*/
  //phores EE
   /*const int n1=100;
  double x2[n1],y2[n1],xmc2[n1],ymc2[n1];
  for(int i=0 ; i<100;i++)
  {
    x2[i]=float(i+1)/n1;
    xmc2[i] = x[i];
  }
   hrese->GetQuantiles(n1,y2,x2);
   hres_mce->GetQuantiles(n1,ymc2,xmc2);
   TGraph *gres_EE = new TGraph(n1,ymc2,y2);
   gres_EE->SetName("gres_EE");

    //phores EB
  double x3[n1],y3[n1],xmc3[n1],ymc3[n1];
  for(int i=0 ; i<100;i++)
  {
    x3[i]=float(i+1)/n1;
    xmc3[i] = x[i];
  }
  cout<<hres_mcb->Integral()<<endl;
   hresb->GetQuantiles(n1,y3,x3);
   hres_mcb->GetQuantiles(n1,ymc3,xmc3);
   TGraph *gres_EB = new TGraph(n1,ymc3,y3);
   gres_EB->SetName("gres_EB");*/
   hr9_mcb->DrawNormalized("hist");
   hr9b->DrawNormalized("epsame");
   gPad->Print("r9.pdf");
  TFile *cor = new TFile(Form("../external/%d_phocorr_noTT.root",period),"recreate");
  cor->cd();
  gR9_EE->Write();
  gR9_EB->Write();
  //  gR9_EB2->Write();
  //gres_EB->Write();
  //gres_EE->Write();
  
  
}
