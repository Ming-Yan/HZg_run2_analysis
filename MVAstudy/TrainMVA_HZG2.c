// how to run: root -l -b -q TrainMVA_HZG2.c\(\"BDTG,BDT\"\,\"MVA\"\,\"all\"\,\"\"\)
// Modified from TMVAClassification.C 

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

// temporary comment out for batch jobs
// to launch it at the end of the job, put back the call at the end of this file
//#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

#endif


TString inputFilesDir = "../outfile/";
//TString inputFilesDir = "mvaInputs_v69/muon/";
TString outputWeightsDir = "MVAout";



//Bool_t USE_SEPARATE_TRAIN_TEST_FILES = false;
// if selecting training and testing events from the same file
// one has to enter specify the number of events

//vername : version name
void TrainMVA_HZG2(TString myMethodList, TString vername, TString _bgName, TString addout, string tree, string rate, string depth) 
{

  std::cout << "==> Starting TrainMva " << std::endl;
  // subdirectory where output weights for classifiers will go


  // Common weights for the entire sample
  // use with event weights that do not account for x-section,
  // or with fullWeight to avoid too small weights due to small sample scale factors (if such issues occur)
double mcwei[8] =
  {
    /*0.0006749,//ggF 16-0                                                                                
    0.0001052,//VBF 16-1                                                                                
    1.462e-05 ,//ttH 16-2                                                                                
    1.836e-05,//ZH 16-3                                                                                 
    1.704e-05,//W+H 16-4                                                                                
    1.078e-05,//W-H 16-5                                                                                
    2.6071736,//DY+jet 16(aMC@NLO)-6                                                                    
    0.4255616,//SM Zg 16(aMC@NLO)-7  
    0.0008090,//ggF 17-8                                                                                
    8.323e-05,//VBF 17-9                                                                                
    7.241e-05,//ttH 17-10                                                                               
    0.0001299,//ZH 17-11                                                                                
    0.0001179,//W+H 17-12                                                                               
    7.454e-05,//W-H 17-13                                                                               
    2.0486409,//DY jets 2017-14                                                                         
    0.5022826,//Zg 17 rewei*/
    0.0010976,//ggF 18 rewei
    0.000114885,//VBF 18 rewei
    9.264e-05,//ttH 18
    0.0001702,//ZH 18
    0.0001593,//W+H 18
    0.0001004,//W-H 18
    2.60999,//DY 18
    0.6928863//Zg 18 rewei
  };


 
  TString sampleNames = vername+"_"+ _bgName+"_HZg_";

  // contains the performance histograms from the training
  // and the input variables
  TString outFileName = sampleNames + addout + "_tree" + tree + "_lrate" +rate+"_depth" +depth+"_" "TMVA.root";

  //-----------------------------------------------------------

  TMVA::Tools::Instance();

  // Default MVA methods to be trained + tested
  std::map<std::string, int> Use;

  // See available methods below. 
  // If the list of methods passed to TrainMva is empty (=""), the switches below determine what methods are used
  // else they are ignored.


  // --- Boosted Decision Trees
  Use["BDT"] = 1; // uses Adaptive Boost
  Use["BDTG"] = 1; // uses Gradient Boost
  Use["BDTRT"] = 1; //Random Forest
  Use["BDTB"] = 1; // uses Bagging
  Use["BDTD"] = 1; // decorrelation + Adaptive Boost
  Use["BDTF"] = 0; // allow usage of fisher discriminant for node splitting 
  // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
  Use["MLP"] = 1; // Recommended ANN
  Use["MLPBFGS"] = 1; // Recommended ANN with optional training method
  Use["MLPBNN"] = 1; // Recommended ANN with BFGS training method and bayesian regulator
  Use["CFMlpANN"] = 1;// Depreciated ANN from ALEPH
  Use["TMlpANN"] = 1; // ROOT's own ANN
  //  // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
  //

  std::cout << std::endl;
  std::cout << "==> Start TrainMva" << std::endl;

  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") 
    {
      for (std::map<std::string, int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString(myMethodList, ',');
      for (UInt_t i = 0; i < mlist.size(); i++) {
	std::string regMethod(mlist[i]);

	if (Use.find(regMethod) == Use.end()) {
	  std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
	  for (std::map<std::string, int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
	  std::cout << std::endl;
	  return;
	}
	Use[regMethod] = 1;
      }
    }
  // --------------------------------------------------------------------------------------------------

  // --- Here the preparation phase begins

  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TFile* outputFile = TFile::Open(outFileName, "RECREATE");
  TString classificationBaseName = TString("discr_") + sampleNames + addout + TString("_")+ "tree" + tree + "_lrate" +rate+"_depth" +depth+"_";

  TMVA::Factory *factory = new TMVA::Factory(classificationBaseName, outputFile,
					     "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;G,D:AnalysisType=Classification");

  (TMVA::gConfig().GetIONames()).fWeightFileDir = outputWeightsDir;

  // Define the input variables that shall be used for the MVA training


  //factory->AddVariable("rho","#rho","",'F');
  factory->AddVariable("costheta","cos(#theta)","",'F');
  factory->AddVariable("cosTheta","cos(#Theta)","",'F');
  //factory->AddVariable("ZgPTt", "pT_{t}^{Z#gamma}",'F');
  factory->AddVariable("mllgptdmllg","mllgpt/mllg","",'F');
  factory->AddVariable("lepEta1","lep1 #eta","",'F');
  factory->AddVariable("lepEta2","lep2 #eta","",'F');
  factory->AddVariable("phoEta","pho #eta","",'F');
  factory->AddVariable("Phi","#phi","rad",'F');
  factory->AddVariable("phoR9","pho r9","",'F');
  factory->AddVariable("phoMVA", "photon MVA","",'F');
  //factory->AddVariable("phores", "photon resol.","",'F');
  //factory->AddVariable("lep1res", "lep1 resol.","",'F');
  //factory->AddVariable("lep2res", "lep2 resol.","",'F');
  //factory->AddVariable("mllres", "mll resol.","",'F');
  //factory->AddVariable("mllmllg","M_{ll}+M_{ll#gamma}","",'F');
  factory->AddVariable("dRlg","min(#DeltaR(l,#gamma))","",'F');
  factory->AddVariable("maxdRlg","max(#DeltaR(l,#gamma))","",'F');
  //factory->AddVariable("mllg","mass","",'F');
  
  
  cout<<"==>input variables"<<endl;
  
  //sampleChain->AddVariable("totSF",&totSF_,"totSF/F");//(TMVA::gConfig().GetIONames()).fWeightFileDir;
  //sampleChain->AddVariable("puwei",&puwei_,"puwei/F");//(TMVA::gConfig().GetIONames()).fWeightFileDir;

  
  // if (!USE_SEPARATE_TRAIN_TEST_FILES) 
  // {
  TFile *ggF = TFile::Open(Form("%smc_%s_HZg_ggF_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *VBF = TFile::Open(Form("%smc_%s_HZg_VBF_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *ttH = TFile::Open(Form("%smc_%s_HZg_ttH_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *ZH = TFile::Open(Form("%smc_%s_HZg_ZH_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *WplusH = TFile::Open(Form("%smc_%s_HZg_WplusH_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *WminusH = TFile::Open(Form("%smc_%s_HZg_WminusH_125GeV.root",inputFilesDir.Data(),vername.Data()));
  cout<<"input signal file"<<endl;
  //bkg objects
  TFile *bgFile1;
  TFile *bgFile2;
  TFile *bgFile3;
	
  if (_bgName == "Zg") bgFile1 = TFile::Open(Form("%smc_%s_Zg_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));
  else if (_bgName == "DYjets") bgFile1 = TFile::Open(Form("%smc_%s_DYJetsToLL_m50_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));
  else if (_bgName == "TTto2l2n") bgFile1 = TFile::Open(Form("%smc_%s_TTTo2L2Nu_powheg.root",inputFilesDir.Data(),vername.Data()));
  else 
    {
      bgFile1 = TFile::Open(Form("%smc_%s_Zg_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));
      bgFile2 = TFile::Open(Form("%smc_%s_DYJetsToLL_m50_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));
      //bgFile3 = TFile::Open(Form("%smc_%s_TTTo2L2Nu_powheg.root",inputFilesDir.Data(),vername.Data()));
    }
    
  std::cout << "--- TrainMva       : Using input files version: " << vername << " \n BKG:  " << _bgName<< std::endl;
  // --- Register the training and test trees
  TTree *sig_ggF = (TTree*) ggF->Get("tMVA");//put the tree name used in trainning
  TTree *sig_VBF = (TTree*) VBF->Get("tMVA");//put the tree name used in trainning
  TTree *sig_ttH = (TTree*) ttH->Get("tMVA");//put the tree name used in trainning
  TTree *sig_ZH  = (TTree*) ZH->Get("tMVA");//put the tree name used in trainning
  TTree *sig_WplusH  = (TTree*) WplusH->Get("tMVA");//put the tree name used in trainning
  TTree *sig_WminusH  = (TTree*) WminusH->Get("tMVA");//put the tree name used in trainning
  
  TTree *bkg1 = (TTree*) bgFile1->Get("tMVA");
  TTree *bkg2 = (TTree*) bgFile2->Get("tMVA");
  //TTree *bkg3 = (TTree*) bgFile3->Get("tMVA");

  // You can add an arbitrary number of signal or background trees
  factory->AddSignalTree(sig_ggF, mcwei[0]);
  factory->AddSignalTree(sig_VBF, mcwei[1]);
  factory->AddSignalTree(sig_ttH, mcwei[2]);
  factory->AddSignalTree(sig_ZH, mcwei[3]);
  factory->AddSignalTree(sig_WplusH, mcwei[4]);
  factory->AddSignalTree(sig_WminusH, mcwei[5]);
  if(_bgName == "DYjets")factory->AddBackgroundTree(bkg1, mcwei[6]);
  else if(_bgName == "Zg")factory->AddBackgroundTree(bkg1,mcwei[7]);

  else 
    {
      factory->AddBackgroundTree(bkg1 ,mcwei[6]);
      factory->AddBackgroundTree(bkg2 ,mcwei[7]);
      //factory->AddBackgroundTree(bkg3, mcwei[8]);
    }
 

  // Weights stored in the input ntuples to be used for event weighting.
  // For mixed bg samples these will contain scaling factors that ensure the 
  // different components are mixed according to the xsections.
  // Vertex multiplicity weighting (where applicable) should also be included.

  factory->SetSignalWeightExpression("totSF*genwei*puwei");
  factory->SetBackgroundWeightExpression("genwei*puwei*totSF");
  factory->PrepareTrainingAndTestTree(TCut(""),TCut(""), "SplitMode=Random:NormMode=NumEvents:!V");


  std::cout << "==> Booking the methods " << std::endl;
  // ---- Book MVA methods
  //
  // Please lookup the various method configuration options in the corresponding cxx files, eg:
  // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
  // it is possible to preset ranges in the option string in which the cut optimisation should be done:
  // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

 

  // Boosted Decision Trees - DEFAULT
  if (Use["BDTG"]) // Gradient Boost -> Default parameters
    factory->BookMethod(TMVA::Types::kBDT, "BDTG",
		Form(	"!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:BoostType=Grad:Shrinkage=%.2f:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5",tree.c_str(),atof(rate.c_str())-0.3));//origin 0.1 for shrinnkage
 
 // here is a version with modified parameters
  if (Use["BDT"]) // Adaptive Boost
    factory->BookMethod(TMVA::Types::kBDT, "BDT",
		Form(	"!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:nEventsMin=40:MaxDepth=%s:BoostType=AdaBoost:AdaBoostBeta=%s:SeparationType=GiniIndex:nCuts=20",tree.c_str(),depth.c_str(),rate.c_str()));
  if (Use["BDTRT"]) // random forest
    factory->BookMethod(TMVA::Types::kBDT, "BDTRT",
			Form("!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:nEventsMin=40:MaxDepth=%s:UseRandomisedTrees=True:BoostType=AdaBoost:AdaBoostBeta=%s:SeparationType=GiniIndex:nCuts=20:NNodesMax=5",tree.c_str(),depth.c_str(),rate.c_str()));

  if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    factory->BookMethod(TMVA::Types::kBDT, "BDTD",
		Form(	"!H:!V:NTrees=%s:nEventsMin=400:MaxDepth=%s:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate:AdaBoostBeta=%s",tree.c_str(),depth.c_str(),rate.c_str()));


  // For an example of the category classifier usage, see: TMVAClassificationCategory

  // --------------------------------------------------------------------------------------------------

  // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

  // factory->OptimizeAllMethods("SigEffAt001","Scan");
  // factory->OptimizeAllMethods("ROCIntegral","GA");

  // --------------------------------------------------------------------------------------------------

  // ---- Now you can tell the factory to train, test, and evaluate the MVAs

  // Train MVAs using the set of training events
  factory->TrainAllMethods();
  //  TMVA::IMethod* method = factory->GetMethod( "BDTRT" );
  //const TMVA::Ranking* ranking = method->CreateRanking();
  //ranking->Print();
  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();
  cout<<"?"<<endl;
  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  // --------------------------------------------------------------

  // Save the output
  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TrainMva is done!" << std::endl;

  delete factory;

  // Launch the GUI for the root macro
  // make it lightweight for batch jobs and skip loading this script -> for interactive include
  // TMVAGui.C which is currently commented out.
  // if (!gROOT->IsBatch()) TMVAGui(outFileName);

}
