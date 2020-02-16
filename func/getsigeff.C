 void getsigeff(){
  TChain sig("tZg");
  TChain sig1("tZg");
  //sig.Add("../outfile/mc_Rereco17_newMVAv3_ele_HZg_ggF_125GeV.root"); 
  //sig.Add("../outfile/mc_Rereco17_newMVAv3_ele_HZg_VBF_125GeV.root");
  //sig.Add("../outfile/mc_Rereco17_newMVAv3_ele_HZg_*H_125GeV.root");
  // sig.Add("../outfile/mc_Rereco17_newMVAv3_mu_HZg_ggF_125GeV.root");
  sig.Add("../outfile/mc_Legacy16_newMVA_mu_HZg_VBF_125GeV.root");
  // sig.Add("../outfile/mc_Rereco17_newMVAv3_mu_HZg_*H_125GeV.root");
  TChain bkg("tZg");
  bkg.Add("../outfile/Data_Rereco17_newMVAv3_mu_Mu.root");
  bkg.Add("../outfile/Data_Rereco17_newMVAv3_ele_EG.root");
  TH1F *hsig = new TH1F("hsig","",55,115,170);
  TH1F *hsig_cut = new TH1F("hsig_cut","",55,115,170);
  TH1F *hbkg = new TH1F("hbkg","",55,115,170);
  TH1F *hbkg_cut = new TH1F("hbkg_cut","",55,115,170);
  sig.Draw("mllg>>hsig","(mllg>115&&mllg<170&&(cat<5))*mcwei*genwei*totSF*puwei*ptwei*L1wei");
  //sig.Draw("mllg>>hsig","(mllg>120&&mllg<130&&(cat==5))*mcwei*genwei*totSF*puwei*L1wei*ptwei");
  //sig.Draw("mllg>>hsig","(mllg>115&&mllg<170&&(cat<5))*mcwei*genwei*totSF*puwei*ptwei");
  //sig.DrAw("mllg>>hsig","(HZgVBF!=-99&&mllg>115&&mllg<170)*mcwei*genwei*totSF*puwei*ptwei");
  //sig.Draw("mllg>>hsig","(mllg>115&&mllg<170&&(cat<5||(cat==5&&mllgpt<60.)))*mcwei*genwei*totSF*puwei*ptwei");
  //bkg.Draw("mllg>>hbkg","(mllg>120&&mllg<130&&HZgVBF!=-99)");
  bkg.Draw("mllg>>hbkg","(mllg>120&&mllg<130&&(cat<5||cat==10))");
  //bkg.Draw("mllg>>hbkg","(mllg>120&&mllg<130&&(cat==5))");
  vector<float> sigeff, bkgrej,MVA,signi;sigeff.clear();bkgrej.clear();MVA.clear();signi.clear();
  for (int i = 0 ; i < 2000; i++)
    {
      float cut =  -0.1+0.0001*i;
      /*	sig.Draw("mllg>>hsig_cut",Form("(HZgVBF!=-99&&mllg<170&&mllg>115&&HZgVBF>%f)*mcwei*genwei*totSF*puwei*ptwei",cut));
		sigeff.push_back(hsig_cut->Integral()/hsig->Integral());
		bkg.Draw("mllg>>hbkg_cut",Form("(mllg<170&&mllg>115&&HZgVBF>%f&&HZgVBF!=-99)",cut));
		bkgrej.push_back(1.-hbkg_cut->Integral()/hbkg->Integral());
		//sigeff1.push_back(hsig_cut->Integral()/hsig->Integral());*/
      //bkg.Draw("mllg>>hbkg",Form("(mllg<170&&mllg>115&&(HZgVBF+HZgMVA)/2>%f&&HZgVBF!=-99)",cut));
      //bkgrej1.push_back(1.-hbkg_cut->Integral()/hbkg->Integral());
	
      sig.Draw("mllg>>hsig_cut",Form("(mllg>115&&mllg<170&&(cat<5)&&HZgMVA>%f)*mcwei*genwei*totSF*puwei*ptwei*L1wei",cut));
      //sig.Draw("mllg>>hsig_cut",Form("(mllg>120&&mllg<130&&(cat==5)&&HZgVBF>%f)*mcwei*genwei*totSF*puwei*L1wei*ptwei",cut));
      //sig.Draw("mllg>>hsig_cut",Form("(mllg>120&&mllg<130&&(cat<5||cat==10)&&HZgMVA>%f)*mcwei*genwei*totSF*puwei*ptwei*L1wei",cut));
      //sigeff.push_back(hsig_cut->Integral()/hsig->Integral());    
      //bkg.Draw("mllg>>hbkg_cut",Form("(mllg<130&&mllg>120&&HZgVBF>%f&&cat==5)",cut));                                         
      bkg.Draw("mllg>>hbkg_cut",Form("(mllg<130&&mllg>120&&HZgMVA>%f&&(cat<5||cat==10))",cut)); 
      
      bkgrej.push_back(1.-hbkg_cut->Integral()/hbkg->Integral()); 
      MVA.push_back(cut);
      //if(hbkg_cut->Integral()==0)break;
      signi.push_back(hsig_cut->Integral()/sqrt(fabs(hbkg_cut->Integral())));
      //cout<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.1001&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.999)cout<<"0% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.901&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.899)cout<<"10% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      //if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.801&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.799)cout<<"20% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.701&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.699)cout<<"30% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.601&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.599)cout<<"40% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.501&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.499)cout<<"50% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.401&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.399)cout<<"60% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.301&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.299)cout<<"70% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.201&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.199)cout<<"80% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.101&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.099)cout<<"90% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
      if(hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<0.051&&hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)>0.049)cout<<"95% == " << cut << "\tfrac:"<<hsig_cut->Integral(-1,-1)/hsig->Integral(-1,-1)<<"\tsignificance: "<<hsig_cut->Integral(-1,1)/sqrt(hbkg->Integral(-1,-1))<<endl;
     
    }
      //TFile *f = new TFile("roc_old.root","recreate");
  /*TGraph *g = new TGraph(sigeff.size(),&sigeff[0],&bkgrej[0]);
      gStyle->SetOptStat(0);
      g->SetLineColor(kBlue);
      g->SetLineWidth(2);
      g->GetXaxis()->SetTitle("#epsilon_{sig}");
      g->GetYaxis()->SetTitle("1-#epsilon_{bkg}");
      g->Draw("ac");
      gPad->Print("ROC17.pdf");
      TGraph *g1 = new TGraph(MVA.size(),&MVA[0],&signi[0]);
      g1->SetLineColor(kBlack);
      g1->SetLineWidth(2);
      g1->GetXaxis()->SetTitle("MVA score");
      g1->GetYaxis()->SetTitle("s/#sqrt{b}");
      g1->Draw("ac");
      gPad->Print("signi17.pdf");*/
}
