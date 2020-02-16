void make_theo()
{
	float sc_ggF[22] = {4.7,-6.9,4.6,-6.9,4.6,-6.8,4.6,-6.8,4.6,-6.7,4.5,-6.7,4.5,-6.7,4.5,-6.6,4.5,-6.6,4.5,-6.6};
	float pdf_ggF = 3.2;
	float sc_VBF[2] = {0.4,-0.3};
	float pdf_VBF = 2.1;
	float sc_ttH[22] = {5.9,-9.3,5.9,-9.3,5.9,-9.3,5.8,-9.2,5.9,-9.2,5.8,-9.2,5.8,-9.2,5.8,-9.2,5.8,-9.2,5.8,-9.3,5.8,-9.3};
	float pdf_ttH=3.6;
	float sc_WH[22] = {0.5,-0.6,0.5,-0.7,0.4,-0.7,0.6,-0.7,0.6,-0.6,0.5,-0.7,0.6,-0.8,0.5,-0.7,0.5,-0.7,0.5,-0.7,0.4,-0.7};
	float pdf_WH[11] = {1.8,1.8,1.8,1.9,1.9,1.9,1.9,1.8,1.8,1.8};
	float sc_ZH[22] = {3.4,-3.0,3.5,-3.0,3.6,-3.0,3.6,-3.1,3.8,-3.1,3.8,-3.1,3.7,-3.2,3.9,-3.1,3.8,-3.2,3.9,-3.2};
	float pdf_ZH = 1.6;
    for (int m = 0 ; m <11 ; m ++)
    {
        string fname = "/afs/cern.ch/work/m/milee/MYcode/limit/uncer/theo_m" + std::to_string(120+m) + ".txt";
        ofstream out(fname.c_str());
        out<<"QCDscale_VH   	lnN	-	-	-	"<<1.+0.01*sc_ZH[2*m]<<"/"<<1.+0.01*sc_ZH[2*m+1]<<"	"<<1.+0.01*sc_WH[2*m]<<"/"<<1.+0.01*sc_WH[2*m+1]<<"	-"<<endl;
        out<<"QCDscale_ggH	lnN	"<<1.+0.01*sc_ggF[2*m]<<"/"<<1.+0.01*sc_ggF[2*m+1]<<"	-	-	-	-	-"<<endl;
        out<<"QCDscale_qqH	lnN	-	"<<1.+0.01*sc_VBF[0]<<"/"<<1.+0.01*sc_VBF[1]<<"	-	-	-	-"<<endl;
        out<<"QCDscale_ttH	lnN	-	-	"<<1.+0.01*sc_ttH[2*m]<<"/"<<1.+0.01*sc_ttH[2*m+1]<<"	-	-	-"<<endl;
        out<<"pdf_Higgs_gg	lnN	"<<1.-0.01*pdf_ggF<<"/"<<1.+0.01*pdf_ggF<<"	-	-	-	-	-"<<endl;
        out<<"pdf_Higgs_qqbar	lnN	-	"<<1-0.01*pdf_VBF<<"/"<<1+0.01*pdf_VBF<<"	-	"<<1-0.01*pdf_ZH<<"/"<<1+0.01*pdf_ZH<<"	"<<1-0.01*pdf_WH[m]<<"/"<<1+0.01*pdf_WH[m]<<"	-"<<endl;
        out<<"pdf_Higgs_ttH	lnN	-	-	"<<1-0.01*pdf_ttH<<"/"<<1+0.01*pdf_ttH<<"	-	-	-"<<endl;
    }
}   
