#/!bin/bash
echo "===combine cards====="
read -p "fname:" fname
read -p "mode:" mode

if [ "${mode}" != "all" ]; then
    read -p "ftype1:ftype2:" ftype1 ftype2
    read -p "cat1:cat2->" cat1 cat2
    for ((mass = 120 ; mass<131; mass++));
    do 
	if [ "${cat1}" == "501" -o "${cat2}" == "501" ]; then
	    combineCards.py card_${fname}_${ftype1}_${cat1}_${mass}.txt card_${fname}_${ftype2}_${cat2}_${mass}.txt >card_${fname}_${ftype1}_5_${mass}.txt 
	else 
	    combineCards.py card_${fname}_${ftype1}_${cat1}_${mass}.txt card_${fname}_${ftype2}_${cat2}_${mass}.txt >card_${fname}_${ftype1}_${ftype2}_${cat1}${cat2}_${mass}.txt
	fi
    done
else 
    for ((mass = 120 ; mass<131; mass++));
    do
        #combineCards.py card_${fname}_mu_1_${mass}.txt card_${fname}_mu_2_${mass}.txt card_${fname}_mu_3_${mass}.txt card_${fname}_mu_4_${mass}.txt  >card_${fname}_mu_1234_${mass}.txt
        combineCards.py card_${fname}_ele_1_${mass}.txt card_${fname}_ele_2_${mass}.txt card_${fname}_ele_3_${mass}.txt card_${fname}_ele_4_${mass}.txt  >card_${fname}_ele_1234_${mass}.txt
	combineCards.py card_${fname}_ele_1234_${mass}.txt card_${fname}_ele_5_${mass}.txt > card_${fname}_ele_12345_${mass}.txt
	combineCards.py card_${fname}_ele_12345_${mass}.txt card_${fname}_ele_10_${mass}.txt >  card_${fname}_ele_1234510_${mass}.txt

	combineCards.py card_${fname}_mu_1_${mass}.txt card_${fname}_mu_2_${mass}.txt card_${fname}_mu_3_${mass}.txt card_${fname}_mu_4_${mass}.txt  >card_${fname}_mu_1234_${mass}.txt
	combineCards.py card_${fname}_mu_1234_${mass}.txt card_${fname}_mu_5_${mass}.txt >card_${fname}_mu_12345_${mass}.txt
	
	combineCards.py card_${fname}_mu_12345_${mass}.txt card_${fname}_mu_10_${mass}.txt >  card_${fname}_mu_1234510_${mass}.txt
	
	combineCards.py card_${fname}_ele_1234510_${mass}.txt card_${fname}_mu_1234510_${mass}.txt card_${fname}_ele_mu_6789_${mass}.txt >card_${fname}_ele_mu_12345678910_${mass}.txt
    done
fi