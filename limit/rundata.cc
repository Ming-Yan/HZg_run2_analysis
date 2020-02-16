//code for run all
void rundata(string fname, int cat, string ptype, string pdf,int order){
  gSystem->SetBuildDir("tmpdir", kTRUE);
  gROOT->LoadMacro("datapdf.C++");
  gROOT->ProcessLine(Form(".x datapdf.C(\"%s\",%d,\"%s\",\"%s\",%d)",fname.c_str(),cat,ptype.c_str(),pdf.c_str(),order));
  gROOT->ProcessLine("gSystem->Load(\"libBackgroundProfileFitting\")");
  gROOT->ProcessLine(Form(".x datapdf.C(\"%s\",%d,\"%s\",\"%s\",%d)",fname.c_str(),cat,ptype.c_str(),pdf.c_str(),order));
  gROOT->ProcessLine(".q");
}
