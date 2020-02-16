#include "../plugin/CMS_lumi.C"
#include "../plugin/tdrstyle.C"
void readcatall(int ncat = 2, bool plot=true)
{
  setTDRStyle();
  //read in the the combination
  int combnum[5] = {6, 15, 20, 15, 6};
  char cats[10];string catname;
  sprintf(cats,"ncat%d.txt",ncat);
  ifstream fcat(cats);
  vector<int> catvec;catvec.clear();
  int category;
  while (fcat>>category)catvec.push_back(category);
  cout<<catvec.size()<<endl;
  //define the limit related
  vector<double> medlimit, upper1s, lower1s, upper2s, lower2s;
  vector<double> mass;
  TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };    
  string vername[2] = {"_wboost_comb","woboost_comb"};
  //use to rank the limit
  vector<float> limit125_w,limit125_wo;
  limit125_w.clear();
  limit125_wo.clear();
  vector<int> numw,numwo;numw.clear();numwo.clear();
  vector<string> catcat;
  TH1F *h_w = new TH1F("h_w", "",combnum[ncat-2],0,combnum[ncat-2]);
  TH1F *h_wo = new TH1F("h_wo", "",combnum[ncat-2],0,combnum[ncat-2]);

  for (int nfile = 0; nfile < 2; nfile++)
    {
      for(int q = 0 ; q < combnum[ncat-2]  ; q++)
	{
	  for(int k = 0; k < ncat-1; k++){catname += std::to_string(catvec[k+q*(ncat-1)]);}
	  medlimit.clear();  upper1s.clear();  lower1s.clear();  upper2s.clear();  lower2s.clear();
	  mass.clear();
	  cout<<catname<<endl;
	  catcat.push_back(catname);
	  for (int i = 0; i < 11; i++)
	    {	
	      Double_t masspt = 120+i;
	      char fname[200];
	      sprintf(fname,"DataCards/VBFMVA_phores%s%s/higgsCombineVBFMVA_phores_ele_mu_all.Asymptotic.mH%s.root",vername[nfile].c_str(),catname.c_str(),name[i].Data());	      
	      TFile* f= TFile::Open(fname);
	      TTree *t = (TTree*)f->Get("limit");
	      Double_t limit;
	      Float_t quantileExpected;
	      t->SetBranchAddress("limit", &limit);
	      t->SetBranchAddress("quantileExpected", &quantileExpected);
	      for (Long64_t j = 0; j < t->GetEntriesFast(); j++)
		{
		  t->GetEntry(j);
		  if (j == 0) lower2s.push_back(limit);
		  if (j == 1) lower1s.push_back(limit);
		  if (j == 2) medlimit.push_back(limit);
		  if (j == 2 && i == 5  && nfile == 0)
		    {
		      limit125_w.push_back(limit);
		      numw.push_back(q);
		      cout<<limit<<endl;
		      h_w->SetBinContent(q+1,limit);
		      h_w->GetXaxis()->SetBinLabel(q+1,Form("cat%s",catname.c_str()));
		    }
		  if (j == 2 && i == 5  && nfile == 1) 
		    {
		      h_wo->SetBinContent(q+1,limit); 
		      cout<<limit<<endl;
		      limit125_wo.push_back(limit);
		      numwo.push_back(q);
		      }
		  if (j == 3) upper1s.push_back(limit);
		  if (j == 4) upper2s.push_back(limit);
		}
	      mass.push_back(masspt);
	      delete t;
	      f->Close();
	      delete f;
	    }
	  if(plot==true)
	    {
		
	      TGraph* g_upper2s = new TGraph(mass.size(), &mass[0], &upper2s[0]);
	      TGraph* g_upper1s = new TGraph(mass.size(), &mass[0], &upper1s[0]);
	      TGraph* g_medlimit = new TGraph(mass.size(), &mass[0], &medlimit[0]);
	      TGraph* g_lower1s = new TGraph(mass.size(), &mass[0], &lower1s[0]);
	      TGraph* g_lower2s = new TGraph(mass.size(), &mass[0], &lower2s[0]);
	      TGraph* g_1s = new TGraph(2*mass.size());
	      TGraph* g_2s = new TGraph(2*mass.size());
	      int n = mass.size();
	      g_1s->SetFillColor(kGreen);
	      g_2s->SetFillColor(kYellow);
	      g_medlimit->SetLineStyle(9);
	      g_medlimit->SetLineWidth(2);
	      for (int k = 0; k < mass.size(); k++) {
		g_1s->SetPoint(k, mass[k], upper1s[k]);
		g_1s->SetPoint(n + k, mass[n-k-1], lower1s[n-k-1]);
		g_2s->SetPoint(k, mass[k], upper2s[k]);
		g_2s->SetPoint(n + k, mass[n-k-1], lower2s[n-k-1]);
	      }
	      
	      g_2s->SetMaximum(upper2s[0]*1.1);
	      g_2s->SetMinimum(0);
	      g_2s->GetXaxis()->SetTitle("Mass[GeV]");
	      g_2s->GetYaxis()->SetTitle("95% CL UL #sigma/#sigma_{SM}");
	      TLegend *l = new TLegend(0.65, 0.75, 0.88, 0.9);
	      l->AddEntry(g_medlimit, "Expected", "l");
	      l->AddEntry(g_1s, "#pm 1#sigma band", "f");
	      l->AddEntry(g_2s, "#pm 2#sigma band", "f");
	      l->SetShadowColor(0);
	      TCanvas *c = new TCanvas("c", "c", 800, 600);
	      c->cd();
	      g_2s->Draw("af");
	      g_1s->Draw("fsame");
	      g_medlimit->Draw("lsame");
	      l->Draw();
	      gPad->Update();
	      TLine *la1 = new TLine(gPad->GetUxmin(), 1.0, gPad->GetUxmax(), 1.0);
	      la1->SetLineColor(kRed);
	      la1->Draw();
	      TLatex tex;
	      tex.SetTextAlign(12); //centered                                                          
	      tex.SetTextSize(0.03);
	      tex.DrawLatex(.2,.96,Form("combine_ncat%d_%d",ncat,q));
	      extraText  = "Work in Progress";
	      lumi_13TeV = "35.9fb^{-1}";
	      CMS_lumi(c, 4, 0);
	      if(nfile==0)c->Print(Form("plot/catstudy/wboost_limit_ncat%d_%d.png",ncat,q));
	      else c->Print(Form("plot/catstudy/woboost_limit_ncat%d_%d.png",ncat,q));
	    }	  
	  catname.clear();
	}
    }
  
  vector<int>numw_,numwo_;
  int siz = (int) numw.size();
  if (siz < 1) return;   
  int ind[siz];   
  TMath::Sort(siz, &limit125_w.front(), ind);
  for (int i = 0; i < siz; ++i)     {      numw_.push_back(numw[ind[i]]);     }
  int siz1 = (int) numwo.size();
    if (siz1 < 1) return;   
  int ind1[siz1];   
  TMath::Sort(siz1, &limit125_wo.front(), ind1);
  for (int i = 0; i < siz1; ++i)     {      numwo_.push_back(numwo[ind1[i]]);     }
  for(unsigned int j = 0 ; j < numw_.size(); j++)
    {
      cout<<j<<endl;
      cout<<"boosted: "<<catcat[numw_[j]]<<" "<<limit125_w[numw_[j]]<<endl;
      cout<<"w/o boosted: "<<catcat[numwo_[j]]<<" "<<limit125_wo[numwo_[j]]<<endl;
    }
      TCanvas *c1 = new TCanvas("c1", "c1", 1200, 800);
      c1->cd();
      //h_w->Draw("apl");
      h_w->GetYaxis()->SetTitle("95%UL@125GeV");
      //h_w->GetXaxis()->SetLabelSize(0.03);
      h_w->SetMaximum(6);
      h_w->SetMinimum(3);
      h_w->SetLineColor(kRed);
      h_w->SetMarkerColor(kRed);
      h_wo->SetLineColor(kBlue);
      h_wo->SetMarkerColor(kBlue);
      h_w->SetMarkerStyle(20);
      h_wo->SetMarkerStyle(20);

      h_w->Draw("pl");      h_wo->Draw("plsame");

      extraText  = "Work in Progress";
      lumi_13TeV = "35.9fb^{-1}";
      CMS_lumi(c1, 4, 0);
      //c1->Update();
      //c1->RedrawAxis();
      //c1->GetFrame()->Draw();
      c1->SaveAs(Form("plot/catstudy/limit125_comb_ncat%d.png",ncat));
}
