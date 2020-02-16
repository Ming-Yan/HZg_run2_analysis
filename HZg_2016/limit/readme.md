# Resource for Combination related

[official]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit
[bias]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsWG/SWGuideNonStandardCombineUses
[flashgg]: https://github.com/cms-analysis/flashggFinalFit

- for combine limit usage see [here][official]
- for nonstandard usage(e.g. bias study) see [here][bias]
- flashgg Fit [web][flashgg]


# Codes and Files for seeting limit

|**directory**|**content**|
|-------------|-----------|
|Datacards|datacard for 2016 full dataset|
|PDFs|all PDFs for setting limit|
|sig|signal events txt|

# Current using file : 
 - **make_sig.C** for making signal txt
 - **make_bkg.C** for making bkg txt
 - **make_Cards2_sep.C** making signal PDF  and datacards with 2PDF
 - **pairs.C** making bkg PDF	   
 - **plotparams.C** code for ploting variables in tree
 - **limitplot.C** code for plotting limit

======================================

# Combine tool usage for uncertainty study

[id]: https://twiki.cern.ch/twiki/bin/view/CMS/HiggsWG/SWGuideNonStandardCombineUses#Nuisance_parameter_impacts  "Optional Title Here"
**This is [twiki page][id] by using this method**

1.  combine your datacard with **MultiDimFit** with each parameter

``combine datacard_hzg_eeg_cat3_13TeV_125.txt --algo impact -P pdf_Higgs_gg -M MultiDimFit -m 125  ``

2.  
 

