# Code for H->Zg analysis 

Update all files to full run2 dataset version - 20190807



# Directory

|name|contents|
|----|--------|
|puwei|pileup weight histogram|
|GEN|Gen level study|
|external|files for SFs|
|limit|codes and plot for limit setting, see details in limit directory|
|plot|plots for study|
|plugin|codes for particle selection, correction|
|syn|synchronization file|
|uncertainty|uncertainty study|
|interface|function|
|scikit|MVA from scikit toolkit|
|MVAout|xml file for TMVA|
|KinZfitter|modified package from HZZ for the kinematic refit|
|envelop|modified flashggfinalfit package|

# Analysis code  
 **ana_v2.C** including MVA, already synchronized

# MVA xml file:

  ## Kinematic MVA :
  - **2016:** MVAout/
  
  ## VBF MVA : MVAout/VBF_discr_VBFMVA_update0811__HZg___BDTRT.weights.xml
  
# Functional code

- Uncertainty producing analysis and run.C: **runMucorr.C**.**runEn.C**.**runUEPS.C**.**UEPS.C**.**Ele_mana.C**
- Plot : code for plot, MC&Data comparison, variable distribution, efficiency, effective sigma(**sigmaEff.h**), use **plot.C** and **plot.h**
- Synchronization : **syn.C**
- Angle study : used to boost and rotation to Z or Higgs frame **HZg_var.h**
- Kinematic refit on Z : use the info from **KinZfitter**, **Helperfunction** ==> modified by HZZ group, run standalone
- FSR study : **HZg_FSR.h** selection tests from HZZ & Atlas

----------------------------------------------------

# Things need to update
- uncertainty & correlation between years

# Check filter 

1. Find sample from McM
2. Press the **"Get Setup command "** in Action column
3. Find the grid pack or the LHE file then check the cards
--> both cards and python files might applied filters, and the filter efficiency cannot trust.



# Check the filter information
1. Find the sample in McM
2. Press the **Get Setup command** buttom in Action
3. Find the grid pack or the LHE file then check the cards
--> both cards and python files might applied filters, and the filter efficiency cannot trust.




# Useful link

[ming]: https://twiki.cern.ch/twiki/bin/view/Main/MingRun2WorkBook
[mcm]: https://cms-pdmv.cern.ch/mcm/
[SM]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
[higgs]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
[egmID]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipesRun2
[muonSF]: https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults
[muID]: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2
[jetID]: https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
[btag]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
[HZZ]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsZZ4l2017
[Genproduction]:https://github.com/cms-sw/genproductions/
- **xsection** can found in [Ming's workbook][ming], [McM][mcm], [SM xsection][SM], [higgs related][higgs]
- **EGM related** : such as Scaling factor, ID information [here][egmID]
- **Muon related** :[scaling factor][muonSF], [ID][muID]
- **Jet**: [jetID][jetID], [b/c tag][btag]
- **ZG related** : [HZZ twiki][HZZ]
- **Generator production information** : some information about gen production, the cards and python files are [here][Genproduction]



