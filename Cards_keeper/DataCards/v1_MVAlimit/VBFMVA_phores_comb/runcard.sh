#/!bin/bash
echo "====Asymptotic limit===="
read -p "fname:" fname
read -p "mode(all/ele/mu):" ptype
if [ "${ptype}" == "all"  ]; then
    for alltype in ele mu 
    do 
	echo "run all"
	for both in  1 2 3 4 501 502 10 #1234 12345 123456789 12345678910
        do
            echo "run all eeg mmg"
            for ((mass = 120 ; mass<131; mass++))
	    do
                combine -M  Asymptotic  card_${fname}_${alltype}_${both}_${mass}.txt -m ${mass} --run=blind -n ${fname}_${alltype}_${both}
            done
	done
    done 
    for eegmmg in 6789 #123456789 #13 6789 
    do
	echo "eeg+mmg"
	for ((mass = 120 ; mass<131; mass++));  
	do
            combine -M  Asymptotic  card_${fname}_ele_mu_${eegmmg}_${mass}.txt -m ${mass} --run=blind -n ${fname}_ele_mu_${eegmmg}
	done
    done
else 
    read -p "category:" cat
    if [ "${cat}" == "all" ]; then
	for allcat in 1 2 3 4 5 6789 10 #11 12 13
	do 
	    echo "run all"
	    for ((mass = 120 ; mass<131; mass++));  
	    do
		combine -M  Asymptotic  card_${fname}_${ptype}_${allcat}_${mass}.txt -m ${mass} --run=blind -n ${fname}_${ptype}_${allcat}
	    done
	done
    else 
	for ((mass = 120 ; mass<131; mass++))
	do
	    combine -M  Asymptotic  card_${fname}_${ptype}_${cat}_${mass}.txt -m ${mass} --run=blind -n ${fname}_${ptype}_${cat} 
	done
    fi

fi
