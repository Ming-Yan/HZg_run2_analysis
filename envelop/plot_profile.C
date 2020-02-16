void plot_profile(string dir, string type, int cat)
{
  int catmap=0;

  if(cat<5)catmap = cat-1;
  else if (cat==10)catmap=6;
  else if (cat==501)catmap=4;
  else catmap=5;

  const int ele_ncat[7] = {6,6,5,5,4,5,5};
  const int mu_ncat[7] = {6,5,5,4,4,5,5};
  int size;
  if(type=="ele_mu")size=5;
  else if (type=="ele") size= ele_ncat[catmap];
  else size =mu_ncat[catmap]; 

  string label[6]={"","","","","",""};
 
  string color5[5] = {"#16bac5","#f6511d","#ffb400","#7fb800","#0d2c54"};
  string color8[7] = {"#16bac5","#f6511d","#ffb400","#7fb800","#D359B8","#f57a77","#dca11d"};
  string a1[4]={"bern1",  "exp1", "pow1", "lau1"}; //ele501,mu501                 
  string a2[4]={"bern3",  "exp1", "pow1", "lau1"};//mu4                                           
  string a3[5]={"bern1",  "exp1", "pow1", "lau1","lau2"}; //elemu6789           
  string a4[5]={"bern1", "bern2", "exp1", "pow1", "lau1"}; //ele502,mu502                                  
  string a5[5]={"bern1", "bern2", "exp1", "pow1", "lau2"};//ele10,mu10                              
  string a6[5]={"bern2", "bern3", "exp1", "pow1", "lau1"};//mu2,ele3,ele4                          
  string a7[5]={"bern3", "bern4", "exp1", "pow1" ,"lau1"};//mu3
  string a8[6]={"bern1", "bern2", "bern3", "exp1", "pow1" ,"lau1"};//ele1,mu1  
  string a9[6]={"bern2","bern3", "bern4", "exp1", "pow1" ,"lau1"};//ele2     
  cout<<size<<endl;
  
  if(cat==501){for (int i = 0; i<size;i++){label[i]=a1[i];}}
  if(type=="mu"&&cat==4){for (int i = 0; i<size;i++){label[i]=a2[i];}}
  if(type=="ele_mu"&&cat==6789){for (int i = 0; i<size;i++){label[i]=a3[i];}}
  if(cat==502){for (int i = 0; i<size;i++){label[i]=a4[i];}}
  if(cat==10){for (int i = 0; i<size;i++){label[i]=a5[i];}}
  if(type=="mu"&&cat==2){for (int i = 0; i<size;i++){label[i]=a6[i];}cout<<"?"<<endl;}
  if(type=="ele"&&cat>2&&cat<5){for (int i = 0; i<size;i++){label[i]=a6[i];}cout<<"?"<<endl;}
  if(type=="mu"&&cat==3){for (int i = 0; i<size;i++){label[i]=a7[i];}}
  if(cat==1){for (int i = 0; i<size;i++){label[i]=a8[i];}}
  if(type=="ele"&&cat==2){for (int i = 0; i<size;i++){label[i]=a9[i];}}
  cout<<label[0]<<endl;
  TFile *f_env = TFile::Open(Form("%s/higgsCombine_%s_cat%d_pdf_mu1.MultiDimFit.mH125.root",dir.c_str(),type.c_str(),cat));
  TTree *t_env = (TTree*)f_env->Get("limit");

  float deltaNLL, r;double nll,nll0;
  t_env->SetBranchAddress("deltaNLL",&deltaNLL);
  t_env->SetBranchAddress("nll",&nll);
  t_env->SetBranchAddress("nll0",&nll0);
  t_env->SetBranchAddress("r",&r);
  vector<float> nll_,r_;nll_.clear();r_.clear();
  vector<float> nlls,rs;nlls.clear();rs.clear();
  float min = 100000000;
  for(Long64_t ev = 0 ; ev < t_env->GetEntriesFast();ev++)
    {
      t_env->GetEntry(ev);

      if(ev==0)continue;
      if(min>(deltaNLL+nll+nll0)*2)min = (deltaNLL+nll+nll0)*2;
      nll_.push_back((deltaNLL+nll+nll0)*2);
      //nll_.push_back(deltaNLL);
      r_.push_back(r);
      //nlls.push_back(deltaNLL+nll+nll0);
      //rs.push_back(r);
    
    }
  TCanvas *c = new TCanvas("c","",800,600);
  c->cd();
  TLegend *leg = new TLegend(.1,.12,.3,.3);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  TGraph *g_env = new TGraph(20,&r_[0],&nll_[0]);
  g_env->Draw("AP");
  g_env->SetLineWidth(2);
  g_env->SetTitle("");
  //g_env->SetMaximum(1.5);
  g_env->SetMinimum(min);
  g_env->SetMaximum(min*1.05);
  g_env->GetXaxis()->SetTitle("#mu");
  g_env->GetYaxis()->SetTitle("#DeltaNLL");
  g_env->GetYaxis()->SetTitleOffset(1.2);
  g_env->SetLineColor(kBlack);
  g_env->Draw("AC");
  leg->AddEntry(g_env,"env","l");
  TGraph *h[6];
  for (int i = 0 ;i < size; i++)
    {
      r_.clear();nll_.clear();
      TFile *f_pdf = TFile::Open(Form("%s/higgsCombine_%s_cat%d_pdf%d_mu1.MultiDimFit.mH125.root",dir.c_str(),type.c_str(),cat,i));
      TTree *t_pdf = (TTree*)f_pdf->Get("limit");
      t_pdf->SetBranchAddress("deltaNLL",&deltaNLL);
      t_pdf->SetBranchAddress("nll",&nll);
      t_pdf->SetBranchAddress("nll0",&nll0);
      t_pdf->SetBranchAddress("r",&r);
      float shift = 0.;
      for(Long64_t ev = 0 ; ev < t_pdf->GetEntriesFast();ev++)
	{
	  t_pdf->GetEntry(ev);
	  if(ev==0)continue;
	  //cout<<2*(deltaNLL+nll+nll0)<<endl;
	  nll_.push_back((deltaNLL+nll+nll0)*2);
	  //nll_.push_back(deltaNLL);
	  r_.push_back(r);
	}
      h[i] = new TGraph(20,&r_[0],&nll_[0]);
      h[i]->SetLineWidth(2);
      h[i]->SetLineColor(TColor::GetColor(color8[i].c_str()));
      h[i]->SetLineStyle(9);
      h[i]->Draw("CSAME");
      leg->AddEntry(h[i],label[i].c_str(),"l");
      f_pdf->Close();
      delete f_pdf;
    }
  leg->Draw();
  c->Print(Form("%s/%s_cat%d.pdf",dir.c_str(),type.c_str(),cat));
  c->Print(Form("%s/%s_cat%d.png",dir.c_str(),type.c_str(),cat));
}
