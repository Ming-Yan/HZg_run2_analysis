read -p "filename:" fname
read -p "vername:" vname1 
read -p "vername2:" vname2
for ptype in ele mu
do
    for proc in ggF #VBF 
    do
	for cat in 1 #2 3 4 5 
	do
	    ./bin/signalFTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname1}/WS_${fname}_${ptype}_${proc}_${cat}_125.root   -m 125 -p ${proc} -f cat${cat} -c ${ptype} -d /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname1}/${ptype}_${proc}_${cat}_test.dat -o /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname1}/
	done
	for cat in 501 #502
	do
	    ./bin/signalFTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname2}/WS_${fname}_${ptype}_${proc}_${cat}_125.root   -m 125 -p ${proc} -f cat${cat} -c ${ptype} -d /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname2}/${ptype}_${proc}_${cat}_test.dat -o /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname2}/
	done

    done
done
#for proc in ttH ZH WH
#do
#    ./bin/signalFTest -i /afs/cern.ch/work/m/milee/MYcode/limit/PDFs/${fname}_${vname2}/WS_${fname}_ele_mu_${proc}_6789_125.root   -m 125 -p ${proc} -f cat6789 -c ele_mu -d /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname2}/ele_mu_${proc}_6789_test.dat -o /afs/cern.ch/work/m/milee/MYcode/limit/${fname}_${vname2}/
#done