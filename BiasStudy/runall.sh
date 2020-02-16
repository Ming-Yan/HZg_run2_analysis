#!/bin/bash
cd /afs/cern.ch/user/m/milee/CMSSW_8_1_0/src
eval `scramv1 runtime -sh` 
cd /afs/cern.ch/work/m/milee/BiasStudy/
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

outdir="results_2016_13TeV_INDEX"
echo "dir is "$outdir
mkdir  -p ${outdir}
cd ${outdir}
set1=("bern1"  "exp1" "pow1" "lau1")##ele501,mu501
set2=("bern1" "bern2" "exp1" "pow1" "lau1")#same with ele1,ele2, mu1, ele502,mu502,elemu6789
set3=("bern1" "bern2" "bern3" "exp1" "pow1" "lau2")#ele10
set4=("bern1" "bern2" "exp1" "pow1" "lau2")#mu10
set5=("bern3" "exp1" "pow1" "lau1")#ele4
set6=("bern1" "bern2" "bern3" "exp1" "pow1" "lau1")#mu2
set7=("bern2" "bern3" "exp1" "pow1" "lau1")#mu3,ele3,ele5
set8=("bern3" "bern4" "exp1" "pow1" "lau1)"#mu4
set9=("bern2" "bern3" "bern4" "exp1" "pow1" "lau1")#mu5


for ptype in ele mu ele_mu;do
    for cat in  1 502 6789; do
	if [ "$ptype" == "ele_mu" ] && [ "$cat" != "6789" ] ; then
            continue
        fi
	card="card_VBFMVA_v2_${ptype}_${cat}_125_env" 

	text2workspace.py /afs/cern.ch/work/m/milee/MYcode/limit/DataCards/VBFMVA_v2_refit_wboost_comb_newcat01379/${card}.txt -o /afs/cern.ch/work/m/milee/BiasStudy/${outdir}/${card}.root
	echo $ptype
	for ((ipdf=0;ipdf<${#set2[@]};ipdf++)); do
	    pwd
	    combine ${card}.root -M GenerateOnly --expectSignal 1 -t -1 -s INDEX --setParameters pdfindex_${ptype}_cat${cat}_13TeV=${ele_cat1[$ipdf]} --saveToys --name _${ptype}_cat${cat}_pdfindex${ipdf}_mu1 -m 125
	    combine ${card}.root -M GenerateOnly --expectSignal 0 -t -1 -s INDEX --setParameters pdfindex_${ptype}_cat${cat}_13TeV=${ele_cat1[$ipdf]} --saveToys --name _${ptype}_cat${cat}_pdfindex${ipdf}_mu0 -m 125
	    
	    for ((jpdf=0;jpdf<${#set2[@]};jpdf++)); do	
		
		combine /afs/cern.ch/work/m/milee/BiasStudy/${outdir}/card_VBFMVA_v2_${ptype}_${cat}_125_env.root  -M MultiDimFit --toysFile=higgsCombine_${ptype}_cat${cat}_pdfindex${ipdf}_mu1.GenerateOnly.mH125.INDEX.root --setParameters pdfindex_${ptype}_cat${cat}_13TeV=${ele_cat1[$jpdf]} --freezeParameters pdfindex_${ptype}_cat${cat}_13TeV -P  r --expectSignal 1 -t -1 --saveSpecifiedIndex pdfindex_${ptype}_cat${cat}_13TeV -m 125 --cminDefaultMinimizerStrategy 0 --name  _${ptype}_cat${cat}_pdf${ipdf}_pdf${jpdf}_mu1
		combine /afs/cern.ch/work/m/milee/BiasStudy/${outdir}/card_VBFMVA_v2_${ptype}_${cat}_125_env.root  -M MultiDimFit --toysFile=higgsCombine_${ptype}_cat${cat}_pdfindex${ipdf}_mu0.GenerateOnly.mH125.INDEX.root --setParameters pdfindex_${ptype}_cat${cat}_13TeV=${ele_cat1[$jpdf]} --freezeParameters pdfindex_${ptype}_cat${cat}_13TeV -P  r --expectSignal 0 -t -1 --saveSpecifiedIndex pdfindex_${ptype}_cat${cat}_13TeV -m 125 --cminDefaultMinimizerStrategy 0 --name  _${ptype}_cat${cat}_pdf${ipdf}_pdf${jpdf}_mu0

    #ls -ltr 
    #cd ..

		while [ "`jobs -p | wc -l`" -ge "$nparallel" ]; do
		    sleep 2
		    
		done
	    done
	done
    done
done
cd ..

echo "Finished (`date`)."
