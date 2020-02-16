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

# Process pre-minitrees and create output/minitrees.root.
#
# Previous version (if any) of the directory ./output will be removed.
#
# Actual configuration for the code is given in the mkminitrees() steering
# function at the end of mkminitrees.cc file.
#root -b -l -q mkminitrees.cc+

# Draw comparison of data/MC 3-particle invariant mass shapes.
#
# cd auxiliary
# python -i combine_backgrounds.py
# cd ..

# 1. Process text files with cross-sections, branching ratios and uncertainties
# for the SM Higgs and produce theoretical_uncertainties_SM_Higgs.txt with lines
# ready-to-be-used in the HZg analysis datacards.
#
# 2. Evaluate and print out a few numbers of expected H=>Zg=>eeg yields.
#
# 3. Extract numbers of events from ggNtuplizer's ntuples with HZg signal
# samples, evaluate and print out normalization factors which adapt MC scales to
# real data. For this step to succeed, the signal ntuples must be accessible.
# The printed arrays with normalization factors must be added to mkdatacards.C
# by hand.
#
# Those three steps were already done, this is just for documentation.
#
# cd auxiliary/normfactors_and_theoretical_uncertainties
# python normfactors_and_theoretical_uncertainties.py
# mv theoretical_uncertainties_SM_Higgs.txt ../..
# cd ../..

# Print out expected H=>Zg=>eeg yields for sqrt(s) = 14TeV.
#
# cd auxiliary/normfactors_and_theoretical_uncertainties/14TeV
# python yields_14TeV.py
# cd ../../..

# Process minitrees from output/minitrees.root: perform unbinned fitting of
# invariant mass shapes, create text datacards and corresponding root files with
# PDFs and observed mass points.
#
# Output: output/datacards/* and output/for_visualizations.root. The latter
# contains objects for easy drawing.
#
# Actual configuration is encoded in the macro itself.
#root -b -l -q mkdatacards.C
#root -b -l -q mkdatacards_2categories.C

# Draw many interesting plots.
#
# Actual configuration on what to draw can be changed in a steering function of
# every python script or root macro.
#
# cd auxiliary
# python -i draw_params_background.py
# python -i draw_fits.py
# python -i draw_params_signal.py
# root -l combine_signal_pdfs.cc+
# cd ..


#
# Run the combine tool from the HiggsAnalysis/CombinedLimit package.
#

# maximum number of jobs to run in parallel
nparallel=8

#echo "Spawning per-datacard jobs, waiting for their termination:"


#LeptonComboCard_hzg_eeg_mmg_cat12345678910_13TeV_mH129.txt#
#######
#for ch in MegaComboCard_HZG_Dalitz; do
#for ch in LeptonComboCard_hzg_eeg_mmg_cat12345678910; do
#for ch in comboCard_Dalitz ; do
for num in   150 300 1000 1500 2000 2500 3000
do
    cd /afs/cern.ch/work/m/milee/MYcode/limit/
    cd DataCards/kinMVA_nompho_${num}
    combine -M GenerateOnly card_kinMVA_nompho_ele_mu_12345678910_125.txt  -t -1 --saveToys --expectSignal=0 --expectSignalMass=125 -m 125 -n "cutcomb_nosig"
    combine -M GenerateOnly card_kinMVA_nompho_ele_mu_12345678910_125.txt  -t -1 --saveToys --expectSignal=1 --expectSignalMass=125 -m 125 -n "cutcomb"
    
    

    for ((mass=120;mass<131;mass++)); do
	
        echo "Spawning job for $card (`date`) ..."

	
	
            # NOTE: "tee" forbids the combine tool to delete its own output
            #nice combine -v1 -U -M Asymptotic -m $mass -n "_${ch}_cat${cat}_13TeV" \
#	    //higgsCombinecat1.GenerateOnly.mH125.123456.root
	    #nice combine -M ProfileLikelihood -m $mass -n "_${ch}_cat${cat}_13TeV_sigInj" \
	
	#nice combine -M ProfileLikelihood -v 1 --significance --pvalue card_kinMVA_nompho_ele_mu_12345678910_${mass}.txt -t -1 --toysFile higgsCombineMVAcomb_nosig.GenerateOnly.mH125.123456.root -m ${mass} -n "MVAcomb_nosig"
	nice combine -M ProfileLikelihood -v 1 --significance --pvalue card_kinMVA_nompho_ele_mu_12345678910_${mass}.txt -t -1 --toysFile higgsCombinecutcomb.GenerateOnly.mH125.123456.root -m ${mass} -n "MVAcomb"
	# nice combine -M ProfileLikelihood -v 1 --significance --pvalue card_kinMVA_nompho_ele_mu_12345678910_${mass}.txt  -m ${mass} -n "MVAcomb_nosig_observed"
	#nice combine -M Asymptotic -v 1 --significance --pvalue ../results/${ch}_13TeV_mH${mass}.txt  -m ${mass} -n "$_${ch}_observed"
	
##NOTE 0 : if lumi is n fb else 20 is fine

            # do not execute more than $nparallel jobs in parallel
    done
done
####

echo "All jobs spawned. Waiting for all jobs to terminate ..."
wait


# Merge per-mass point results together.
#for ch in comboCard_Dalitz LeptonComboCard_hzg_eeg_mmg_cat12345678910 MegaComboCard_HZG_Dalitz; do
#for ch in  MegaComboCard_HZG_Dalitz; do
#for ch in comboCard_Dalitz; do
#        # do not iterate over categories if ch=eemmg
#        #[ "$ch" == "eemmg" ] && [ "$cat" != "1234" ] && continue

#    outdir="results_${ch}_13TeV_pval"

#higgsCombinecomboCard_Dalitz.ProfileLikelihood.mH120.root

 #   hadd -v 1 higgsCombine${ch}_sigInj.ProfileLikelihood.merged.root \
 #       $outdir/higgsCombine${ch}.ProfileLikelihood.mH*.root

#    hadd -v 1 higgsCombine${ch}.ProfileLikelihood.merged.root \
#        $outdir/higgsCombine${ch}${ch}_observed.ProfileLikelihood.mH*.root

#done

#echo "Finished (`date`)."

# Draw final limit setting plot.
# cd ../auxiliary
# python -i plot_exclusion_limits.py
