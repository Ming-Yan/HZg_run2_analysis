void pvalueplot()
{
	
	
	vector<double> mass, siginject, nosig;
	mass.clear();siginject.clear(); nosig.clear();	
	
	for(int i = 120; i < 131 ; i++)
	{
		mass.push_back(i*1.);
		TFile *f = TFile::Open(Form("DataCards/VBFMVA_phores_comb/higgsCombineMVAcomb.ProfileLikelihood.mH%d.root",i));
		TFile *f1 = TFile::Open(Form("DataCards/VBFMVA_phores_comb/higgsCombineMVAcomb_nosig.ProfileLikelihood.mH%d.root",i));
		Double_t limit = -1;
		TTree *t = (TTree*)f->Get("limit");
		TTree *t1 = (TTree*)f1->Get("limit");
		t->SetBranchAddress("limit", &limit);
		t1->SetBranchAddress("limit", &limit);
		for (Long64_t j = 0; j < t->GetEntriesFast(); j++) 
		{
			t->GetEntry(j);
			siginject.push_back(limit);
			cout<<limit<<endl;
		}
		for (Long64_t j = 0; j < t1->GetEntriesFast(); j++) 
		{
			t1->GetEntry(j);
			nosig.push_back(limit);
			cout<<limit<<endl;
		}
	}
	TGraph* g_sig = new TGraph(mass.size(), &mass[0], &siginject[0]);
	TGraph* g_nosig = new TGraph(mass.size(), &mass[0], &nosig[0]);
	g_sig->Draw("al");
	g_sig->SetMaximum(0.8);
	g_sig->SetMinimum(0.0000001);
	g_sig->GetXaxis()->SetTitle("Mass[GeV/c^{2}]");
	g_sig->GetYaxis()->SetTitle("p-value");
	g_sig->SetLineColor(kRed);
	g_sig->SetLineWidth(2);
	g_nosig->SetLineColor(kBlue);
	g_nosig->SetLineWidth(2);
	TLine *sig1 = new TLine(120,0.158655,130,0.158655);
	TLine *sig2 = new TLine(120,0.02275,130,0.02275);
	TLine *sig3 = new TLine(120,0.00135,130,0.00135);
    
	sig1->SetLineStyle(2);
	sig2->SetLineStyle(2);
	sig3->SetLineStyle(2);

	sig1->Draw();
	sig2->Draw();
	sig3->Draw();
	gPad->SetLogy();
	g_sig->Draw("lsame");
	g_nosig->Draw("lsame");
	gPad->Print("pvalue.png");
}
