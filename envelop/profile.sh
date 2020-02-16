#!/bin/bash
cd /afs/cern.ch/user/m/milee/CMSSW_10_2_13/src
eval `scramv1 runtime -sh` 
cd /afs/cern.ch/work/m/milee/MYcode/limit/
#!/bin/bash
#
# This script obtains limit setting plots for the HZg analysis in one shot and
# serves as a source of documentation.
#
# NOTE: there is a bug in python's interface to ROOT due to which canvases are
# drawn with empty contents. Just force such a canvas to be redrawn by resizing
# it (e.g. by maximizing/restoring the canvas size).

# stop on first error
set -e
#
# Run the combine tool from the HiggsAnalysis/CombinedLimit package.
#

# maximum number of jobs to run in parallel
nparallel=10

echo "Spawning per-datacard jobs, waiting for their termination:"

outdir="2016_profile"
echo "dir is "$outdir
mkdir  -p ${outdir}
cd ${outdir}
set1=("bern1"  "exp1" "pow1" "lau1") ##ele501,mu501
set2=("bern1" "bern2" "exp1" "pow1" "lau1") #ele502,mu502,elemu6789
set3=("bern1" "bern2" "bern3" "exp1" "pow1" "lau2") #ele10
set4=("bern1" "bern2" "exp1" "pow1" "lau2") #mu10
set5=("bern3" "exp1" "pow1" "lau1") #ele4
set6=("bern1" "bern2" "bern3" "exp1" "pow1" "lau1") #mu1,ele1
set7=("bern2" "bern3" "exp1" "pow1" "lau1") #mu3,ele3,ele5
set8=("bern3" "bern4" "exp1" "pow1" "lau1") #mu4
set9=("bern2" "bern3" "bern4" "exp1" "pow1" "lau1") #mu5

 
for ptype in ele ;do
   for cat in  1 ; do
	
	card="card_VBFMVA_v3_${ptype}_${cat}_125_env" 
	for ((i=0;i<6;i++)); do		
	    combine -M MultiDimFit -d ${card}.txt --algo grid --points=20 --setParameterRanges r=-5,5  --cminDefaultMinimizerStrategy 0 --keepFailures   --saveNLL  --freezeParameters pdfindex_${ptype}_cat${cat}_13TeV --setParameters pdfindex_${ptype}_cat${cat}_13TeV=${i} -n _${ptype}_cat${cat}_pdf${i}_mu1 -m 125 --saveSpecifiedIndex pdfindex_${ptype}_cat${cat}_13TeV  --X-rtd REMOVE_CONSTANT_ZERO_POINT=1   
	done
	combine -M MultiDimFit -d ${card}.txt --algo grid --points=20  --setParameterRanges r=-5,5 --cminDefaultMinimizerStrategy 0 --keepFailures   --saveNLL  -n _${ptype}_cat${cat}_pdf_mu1 -m 125 --saveSpecifiedIndex pdfindex_${ptype}_cat${cat}_13TeV  --X-rtd REMOVE_CONSTANT_ZERO_POINT=1
    done
done
cd ..

echo "Finished (`date`)."
