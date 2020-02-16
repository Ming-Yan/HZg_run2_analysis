read -p "file name" fname
read -p "vername:" vname1 
read -p "vername2:" vname2

for ptype in ele mu
do
    for cat in  1 2 3 4 5 
    do
	./bin/fTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname1}/bkg_${fname}_WS_${ptype}_cat${cat}_2016.root -D /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/ -d /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/bkg_${ptype}_${cat}.dat -t ${ptype}  --isData 1 --runFtestCheckWithToys -v --saveMultiPdf /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname1}/bkg_${ptype}_${cat}.root -f cat${cat}
    done
#    for cat in  10
#    do
#	./bin/fTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname2}/bkg_${fname}_WS_${ptype}_cat${cat}_2016.root -D /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/ -d /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/bkg_${ptype}_${cat}.dat -t ${ptype}  --isData 1 --runFtestCheckWithToys -v --saveMultiPdf /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/bkg_${ptype}_${cat}.root -f cat${cat}
#    done
done
#./bin/fTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname2}/bkg_${fname}_WS_ele_mu_cat6789_2016.root -D /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/ -d /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/bkg_ele_mu_6789.dat -t ele_mu  --isData 1 --runFtestCheckWithToys -v --saveMultiPdf /afs/cern.ch/work/m/milee/MYcode/limit/bkgmodel/${fname}_${vname2}/bkg_ele_mu_6789.root -f cat6789
