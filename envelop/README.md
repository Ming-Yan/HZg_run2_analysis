# This tool is based on flashggfinalfit with adapted HZgamma analysis 

To do envelop method ==> go to Background dir
Plot the uncertainty band from envelop ==> go to plot dir


## Steps 

1. Install the flashggfinalfit tool accordingly (CMSSW747) 
```
cmsrel CMSSW_7_4_7
cd CMSSW_7_4_7/src
cmsenv
git cms-init
# Install Combine as per Twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#ROO
T6_SLC6_release_CMSSW_7_4_X
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd ${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit
git fetch origin
cd ${CMSSW_BASE}/src
# Install Flashgg Final Fit packages
git clone git@github.com:cms-analysis/flashggFinalFit.git
cd ${CMSSW_BASE}/src
cmsenv
scram b -j9
cd ${CMSSW_BASE}/src/flashggFinalFit/
```
2. Go to the background directory and compile(CMSSW747)
```
cd ${CMSSW_BASE}/src/flashggFinalFit/Background
make
```
3. after you compile it, you will see in the bin directory, s a function called **fTest**, and then you run it with this command (this only available for my package, I did some modification)
```   
 ./bin/fTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname1}/bkg_${fname}_WS_${ptype}_cat${cat}_2016.root -D /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/ -d /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/bkg_${ptype}_${cat}.dat -t ${ptype}  --isData 1 --runFtestCheckWithToys -v --saveMultiPdf /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/bkg_${ptype}_${cat}.root -f cat${cat}
    -i input, put the dataset inside the workspace and store it to root file
    -D the output directory of plots
    -d the .dat file of the outcome of fTest
    -t channel(electron / muon)
    --isData set it to 1 for our case(0 means the pseudo data cases)
    --runFtestCheckWithToys
    -v verbosity
    --saveMultiPdf the output directory of multipdf
    -f category
```
4. After you get the multipdf, implement it to the datacard for bkg
```   
  shapes bgr     cat%d  ../../bkgmodel/%s%s/bkg_%s_%d.root  multipdf:CMS_hzg_%s_cat%d_13TeV_bkgshape
```
5. put the uncertainty in the nuisance parameter part, this option is to quote the uncertainty coming from different function which is the **envelope**
```   
 pdfindex_%s_cat%d_13TeV discrete 
```
6. run the combine tool with this option (run this on 80X combine tool)
```   
 combine -M Asymptotic card.txt --run=blind  --cminDefaultMinimizerStrategy 0
```



