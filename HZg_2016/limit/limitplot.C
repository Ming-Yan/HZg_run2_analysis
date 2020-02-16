//code for getting limit plot//
//USAGE::  root -l -b -q limitplot.C\(\"btag\"\,\"ele_mu\"\,\"1112\"\)
#include "../plugin/tdrstyle.C"
#include "../plugin/CMS_lumi.C"

using namespace RooFit;
using namespace RooStats;
using namespace std;

void limitplot(TString fin, TString type, TString cat){
	setTDRStyle();
	vector<double> medlimit, upper1s, lower1s, upper2s, lower2s;
	vector<double> mass;
	medlimit.clear();
	upper1s.clear();
	lower1s.clear();
	upper2s.clear();
	lower2s.clear();
	mass.clear();
	TString name[11] {"120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" };
	for (int i = 0; i < 11; i++){
	  //	  if(i==1)continue;
	Double_t masspt = 120 + i;

	TString fname = "DataCards/higgsCombine" + fin + "_" + type + "_" + cat +".Asymptotic.mH" + name[i] + ".root" ;
	TFile *f = new TFile(fname);
		TTree *t = (TTree*)f->Get("limit");
		Double_t limit;
		Float_t quantileExpected;
		t->SetBranchAddress("limit", &limit);
		t->SetBranchAddress("quantileExpected", &quantileExpected);
		Long64_t nentries = t->GetEntries();
		Long64_t nbytes = 0;
		for (Long64_t j = 0; j < nentries; j++) {
			nbytes += t->GetEntry(j);
			if (j == 0) lower2s.push_back(limit);
			if (j == 1) lower1s.push_back(limit);
			if (j == 2) medlimit.push_back(limit);
			if (j == 3) upper1s.push_back(limit);
			if (j == 4) upper2s.push_back(limit);
			if(j==2)cout << quantileExpected << " " << limit << " " << masspt << endl;
		}
		mass.push_back(masspt);

	}
	TGraph* g_upper2s = new TGraph(mass.size(), &mass[0], &upper2s[0]);
	TGraph* g_upper1s = new TGraph(mass.size(), &mass[0], &upper1s[0]);
	TGraph* g_medlimit = new TGraph(mass.size(), &mass[0], &medlimit[0]);
	TGraph* g_lower1s = new TGraph(mass.size(), &mass[0], &lower1s[0]);
	TGraph* g_lower2s = new TGraph(mass.size(), &mass[0], &lower2s[0]);
	
	TGraph* g_1s = new TGraph(2*mass.size());
	TGraph* g_2s = new TGraph(2*mass.size());
	int n = mass.size();
	//cout << n << endl;
	//double px, py;
	//g_upper2s->GetPoint(1, px, py);
	//cout << px << " " << py << endl;
	for (int k = 0; k < mass.size(); k++) {
	  g_1s->SetPoint(k, mass[k], upper1s[k]);
	  g_1s->SetPoint(n + k, mass[n-k-1], lower1s[n-k-1]);
	  g_2s->SetPoint(k, mass[k], upper2s[k]);
	  g_2s->SetPoint(n + k, mass[n-k-1], lower2s[n-k-1]);
	
	}
	g_1s->SetFillColor(kGreen);
	g_2s->SetFillColor(kYellow);
	g_medlimit->SetLineStyle(9);
	g_2s->SetMaximum(320);
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
	extraText  = "Preliminary";
	lumi_13TeV = "35.9fb^{-1}";
	CMS_lumi(c, 4, 0);
	c->Update();
	c->RedrawAxis();
	c->GetFrame()->Draw();
	TString pname  = "plot/limit_" + fin + "_" + type + "_" + cat + ".png";
	c->Print(pname);
	pname  = "plot/limit_" + fin + "_" + type + "_" + cat + ".pdf";
	c->Print(pname);
	//c->Print("limit_shape_medium_btag.png");
	//c->Print("limit_shape_0709.pdf");
}
