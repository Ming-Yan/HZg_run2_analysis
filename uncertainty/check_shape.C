void check_shape()
{
 string type[2] = {"ele","mu"};
 int cat[9] = {6789, 501, 502, 10,1,2,3,4,5};
 string cuts[9] = 
    {
      "(cat>5&&cat<10)",
      "HZgVBF>0.05&&cat==5",
      "HZgVBF<=0.05&&HZgVBF>-0.05&&cat==5",
      "HZgVBF<=-0.05&&mllgpt>60.",
      "HZgVBF<=-0.05&&HZgMVA>0.123&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.123&&HZgMVA>0.0956&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.0956&&HZgMVA>0.0545&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.0545&&HZgMVA>0.004&&mllgpt<=60",
      "HZgVBF<=-0.05&&HZgMVA<=0.004&&HZgMVA>-0.0395&&mllgpt<=60"
    };
   string channel[4] = {"ggF","VBF","ttH", "ZH"};
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
     for (int tt = 0; tt < 1 ; tt++){
for (int m = 120; m < 131; m = m+5){
     for (int ch = 0 ; ch < 9; ch++){
         for (int c = 0 ; c < 1; c++){
     for (int u = 0 ; u < 11; u++){
	  string vername;
      c1->cd();
	  vername=(u<10)? "_eleshape"+std::to_string(u):"";
      TFile *fnom = TFile::Open(Form("/eos/user/m/milee/unc_files/mc_VBFMVA_v2%s_%s_HZg_%s_%dGeV.root",vername.c_str(),type[tt].c_str(),channel[c].c_str(),m));
      TTree *t = (TTree*)fnom->Get("tZg");
     TH1F  *h = new TH1F("h","",50,90,140);
     t->Draw("REFITmllg>>h",Form("(mllg>115&&mllg<170&&(%s))*puwei*totSF*genwei*mcwei",cuts[ch].c_str()));
	  h->SetLineColor(u);
       if(u==0)h->Draw("hist");
       else h->Draw("histsame");
      if(u==10) c1->Print(Form("ele_%s_cat%d_ch%s_m%d.png",type[tt].c_str(),cat[ch],channel[c].c_str(),m));
	  fnom->Close();
      delete fnom; delete t; delete h;
      // delete h1; delete t1; delete f;
     }
     }
}
}
}
}
