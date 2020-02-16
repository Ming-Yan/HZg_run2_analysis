// root -l -b -q TrainMVA_VBF.C\(\"BDTG,BDT,BDTRT\"\,\"MVA\"\,\"all\"\,\"newvar\"\)  
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
void TrainMVA_VBF(TString myMethodList, TString vername, TString _bgName, TString addout, string tree, string rate, string depth)  
{

  std::cout << "==> Starting TrainMva " << std::endl;
  // subdirectory where output weights for classifiers will go


  // Common weights for the entire sample
  // use with event weights that do not account for x-section,
  // or with fullWeight to avoid too small weights due to small sample scale factors (if such issues occur)
  double mcwei[10] =
    {
      ////2016
      /*0.0006749,//ggF 16-0                                                             
      0.0001052,//VBF 16-1                                                          
      6.102e-05,//ttH 16-2                                                                                        
      1.836e-05,//ZH 16-3                                                                                        
      1.704e-05,//W+H 16-4                                                                                        
      1.078e-05,//W-H 16-5                                                             
      2.6071736,//DY+jet 16(aMC@NLO)-6                                                                     
      0.4255616,//SM Zg 16(aMC@NLO)-7      
      0.012981166,//EWK Zg 16 -8
      0.3838948,  //TTbar 16
      ///2017
      0.0007938,//ggF 17
      8.166e-05,//VBF 17
      6.698e-05,//ttH 17
      0.0001220,//ZH 17
      0.0001155,//W+H 17
      7.289e-05,//W-H 17
      1.7569726,//DY jets 2017
      0.5022826,//Zg 17
      0.0153214,//EWK Zg 17
      0.608155,//TTbar 17*/
      //2018
      0.0010976,//ggF 18 rewei
      0.000114885,//VBF 18  rewei
      9.264e-05,//ttH 18 
      0.0001702,//ZH 18                                                                                           
      0.0001593,//W+H 18                                                                                         
      0.0001004,//W-H 18                                                                                          
      2.60999,//DY 18 
      0.6928863,//Zg 18 rewei           
      0.0220621,//EWK Zg 18                                                                                     
      0.8921560,//TTbar 18
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

  // 
  // --- Boosted Decision Trees
  Use["BDT"] = 1; // uses Adaptive Boost
  Use["BDTG"] = 1; // uses Gradient Boost
  Use["BDTRT"] = 1; //Random Forest
  Use["BDTB"] = 1; // uses Bagging
  Use["BDTD"] = 1; // decorrelation + Adaptive Boost
  Use["BDTF"] = 1; // allow usage of fisher discriminant for node splitting 
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
  TFile* outputFile = TFile::Open(Form("VBF_%s",outFileName.Data()), "RECREATE");
  TString classificationBaseName = TString("VBF_discr_") + sampleNames + "_tree" + tree + "_lrate" +rate+"_depth" +depth+"_" +addout;

 TMVA::Factory *factory = new TMVA::Factory(classificationBaseName, outputFile,
					     "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

  (TMVA::gConfig().GetIONames()).fWeightFileDir = outputWeightsDir;

  // Define the input variables that shall be used for the MVA training
  //factory->AddVariable("CZg","C_{Zg}","",'F');
  //if(addout!="mjj")factory->AddVariable("mjj","m_{jj}","",'F');
  //if(addout!="zeppen")factory->AddVariable("absZeppen","Zeppenfeld","",'F');
  if(addout!="eta")factory->AddVariable("absdEta_jj","#Delta#eta_{jj}","",'F');
  if(addout!="phijj")factory->AddVariable("absdPhi_jj","#Delta#phi_{jj}","",'F');
  if(addout!="phizgjj")factory->AddVariable("absdPhi_Zgjj","#Delta#phi_{Z#gammajj}","",'F');
  if(addout!="dr")factory->AddVariable("dR_phojet","#Delta R(#gamma,j)","",'F');
  if(addout!="ptt")factory->AddVariable("ZgPTt","pT_{t}^{Z#gamma}","",'F');
  if(addout!="jetpt")factory->AddVariable("VBFPt1","pT_{j1}","",'F');
  if(addout!="jetpt")factory->AddVariable("VBFPt2","pT_{j2}","",'F');
  if(addout!="zgmva")factory->AddVariable("HZgMVA", "kinematic MVA","",'F');
  if(addout!="abssysbal")factory->AddVariable("abssysbal","system balance","",'F');
  //if(addout!="absdijetbal")factory->AddVariable("absdijetbal","dijet balance","",'F');
  if(addout!="zeppenpho")factory->AddVariable("absZeppen_pho","Zeppenfeld #gamma","",'F');
  //if(addout!="zeppenZ")factory->AddVariable("absZeppen_Z","Zeppenfeld Z","",'F');
  //factory->AddVariable("theta","WV ana",'F');
  
  cout<<"==>input variables"<<endl;
  

  // if (!USE_SEPARATE_TRAIN_TEST_FILES) 
  // {
  TFile *VBF = TFile::Open(Form("%smc_%s_HZg_VBF_125GeV.root",inputFilesDir.Data(),vername.Data()));
  TFile *VBFt = TFile::Open(Form("%smc_%s_HZg_VBF_125GeV_t.root",inputFilesDir.Data(),vername.Data()));
  
  cout<<"input signal file"<<endl;
  //bkg objects
  TFile *bgFile1;
  TFile *bgFile2;
  TFile *bgFile3;
  TFile *bgFile4;
  TFile *bgFile5;
  TFile *bgFile1t;
  TFile *bgFile2t;
  TFile *bgFile3t;
  TFile *bgFile4t;
  TFile *bgFile5t;
  
  bgFile1 = TFile::Open(Form("%smc_%s_HZg_ggF_125GeV.root",inputFilesDir.Data(),vername.Data()));
  bgFile2 = TFile::Open(Form("%smc_%s_DYJetsToLL_m50_aMCatNLO.root",inputFilesDir.Data(),vername.Data())); 
  bgFile3 = TFile::Open(Form("%smc_%s_Zg_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));      
  bgFile4 = TFile::Open(Form("%smc_%s_Zg_EWK.root",inputFilesDir.Data(),vername.Data()));
  bgFile5 = TFile::Open(Form("%smc_%s_TT_aMCatNLO.root",inputFilesDir.Data(),vername.Data()));
  bgFile1t = TFile::Open(Form("%smc_%s_HZg_ggF_125GeV_t.root",inputFilesDir.Data(),vername.Data()));
  bgFile2t = TFile::Open(Form("%smc_%s_DYJetsToLL_m50_aMCatNLO_t.root",inputFilesDir.Data(),vername.Data())); 
  bgFile3t = TFile::Open(Form("%smc_%s_Zg_aMCatNLO_t.root",inputFilesDir.Data(),vername.Data()));      
  bgFile4t = TFile::Open(Form("%smc_%s_Zg_EWK_t.root",inputFilesDir.Data(),vername.Data()));
  bgFile5t = TFile::Open(Form("%smc_%s_TT_aMCatNLO_t.root",inputFilesDir.Data(),vername.Data()));
  
  
  std::cout << "--- TrainMva       : Using input files version: " << vername << " \n BKG:  " << _bgName<< std::endl;
  // --- Register the training and test trees
  //TTree *sig_ggF = (TTree*) ggF->Get("tVBF");//put the tree name used in trainning
  TTree *sig_VBF = (TTree*) VBF->Get("sVBF");//put the tree name used in trainning
  TTree *sig_VBFt = (TTree*) VBFt->Get("sVBF");//put the tree name used in trainning
  /*TTree *sig_ttH = (TTree*) ttH->Get("tVBF");//put the tree name used in trainning
  TTree *sig_ZH  = (TTree*) ZH->Get("tVBF");//put the tree name used in trainning
  TTree *sig_WplusH  = (TTree*) WplusH->Get("tVBF");//put the tree name used in trainning
  TTree *sig_WminusH  = (TTree*) WminusH->Get("tVBF");//put the tree name used in trainning
  */

  TTree *bkg1 = (TTree*) bgFile1->Get("tVBF");
  TTree *bkg2 = (TTree*) bgFile2->Get("tVBF");
  TTree *bkg3 = (TTree*) bgFile3->Get("tVBF");
  TTree *bkg4 = (TTree*) bgFile4->Get("tVBF");
  TTree *bkg5 = (TTree*) bgFile5->Get("tVBF");

  
  TTree *bkg1t = (TTree*) bgFile1t->Get("tVBF");
  TTree *bkg2t = (TTree*) bgFile2t->Get("tVBF");
  TTree *bkg3t = (TTree*) bgFile3t->Get("tVBF");
  TTree *bkg4t = (TTree*) bgFile4t->Get("tVBF");
  TTree *bkg5t = (TTree*) bgFile5t->Get("tVBF");

  factory->AddSignalTree(sig_VBFt, mcwei[1]*2);
  factory->AddSignalTree(sig_VBF, mcwei[1]*2);
  /*factory->AddSignalTree(sig_ttH, mcwei[2]);
  factory->AddSignalTree(sig_ZH, mcwei[3]);
  factory->AddSignalTree(sig_WplusH, mcwei[4]);
  factory->AddSignalTree(sig_WminusH, mcwei[5]);*/
  factory->AddBackgroundTree(bkg1, mcwei[0]*2);
  factory->AddBackgroundTree(bkg2, mcwei[6]*2);
  factory->AddBackgroundTree(bkg3, mcwei[7]*2);
  factory->AddBackgroundTree(bkg4, mcwei[8]*2);
  factory->AddBackgroundTree(bkg5, mcwei[9]*2);
  factory->AddBackgroundTree(bkg1t, mcwei[0]*2);
  factory->AddBackgroundTree(bkg2t, mcwei[6]*2);
  factory->AddBackgroundTree(bkg3t, mcwei[7]*2);
  factory->AddBackgroundTree(bkg4t, mcwei[8]*2);
  factory->AddBackgroundTree(bkg5t, mcwei[9]*2);

  
  // Weights stored in the input ntuples to be used for event weighting.
  // For mixed bg samples these will contain scaling factors that ensure the 
  // different components are mixed according to the xsections.
  // Vertex multiplicity weighting (where applicable) should also be included.

  factory->SetSignalWeightExpression("totSF*puwei");
  factory->SetBackgroundWeightExpression("totSF*puwei");
  cout<<"before preparing traing and test"<<endl;
  factory->PrepareTrainingAndTestTree(TCut(""),TCut(""), "SplitMode=Random:NormMode=NumEvents:!V");

  //factory->PrepareTrainingAndTestTree(TCut(""),0, 0, 0, 0,"SplitMode=Random:NormMode=NumEvents:!V");
  std::cout << "==> Booking the methods " << std::endl;
  // ---- Book MVA methods
  //
  // Please lookup the various method configuration options in the corresponding cxx files, eg:
  // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
  // it is possible to preset ranges in the option string in which the cut optimisation should be done:
  // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

 

  // Boosted Decision Trees - DEFAULT
  if (Use["BDTG"]) // Gradient Boost -> Default parameters
    factory->BookMethod(TMVA::Types::kBDT, "BDTG",Form("!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:BoostType=Grad:Shrinkage=%.2f:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5:PruningValFraction=0.6",tree.c_str(),atof(rate.c_str())-0.3));


  if (Use["BDT"]) // Adaptive Boost
    factory->BookMethod(TMVA::Types::kBDT, "BDT",Form("!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:nEventsMin=40:MaxDepth=%s:BoostType=AdaBoost:AdaBoostBeta=%s:SeparationType=GiniIndex:nCuts=20:PruningValFraction=0.6",tree.c_str(),depth.c_str(),rate.c_str()));
  if (Use["BDTRT"]) // random forest
    factory->BookMethod(TMVA::Types::kBDT, "BDTRT",Form("!H:!V:IgnoreNegWeightsInTraining:NTrees=%s:nEventsMin=40:MaxDepth=%s:UseRandomisedTrees=True:PruneMethod=ExpectedError:PruneStrength=4:PruningValFraction=0.6:BoostType=AdaBoost:AdaBoostBeta=%s:SeparationType=GiniIndex:nCuts=20",tree.c_str(),depth.c_str(),rate.c_str()));

  if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    factory->BookMethod(TMVA::Types::kBDT, "BDTD",Form("!H:!V:NTrees=%s:nEventsMin=400:MaxDepth=%s:BoostType=AdaBoost:AdaBoostBeta=%s:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate:PruningValFraction=0.6",tree.c_str(),depth.c_str(),rate.c_str()));

  // For an example of the category classifier usage, see: TMVAClassificationCategory

  // --------------------------------------------------------------------------------------------------

  // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

  // factory->OptimizeAllMethods("SigEffAt001","Scan");
  // factory->OptimizeAllMethods("ROCIntegral","GA");

  // --------------------------------------------------------------------------------------------------

  // ---- Now you can tell the factory to train, test, and evaluate the MVAs

  // Train MVAs using the set of training events
  factory->TrainAllMethods();
  // TMVA::IMethod* method = factory->GetMethod( "BDTRT" );
  // const TMVA::Ranking* ranking = method->CreateRanking();
  // ranking->Print();
  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  // --------------------------------------------------------------

  // Save the output
  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TrainMva is done!" << std::endl;

  delete factory;

}
