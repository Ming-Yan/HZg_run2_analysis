#/!bin/bash
echo "===combine cards====="
read -p "fname:" fname
read -p "ftype:" ftype
read -p "cat1:cat2->" cat1 cat2
 for ((mass = 120 ; mass<131; mass++));
 do 
     combineCards.py card_${fname}_${ftype}_${cat1}_${mass}.txt card_${fname}_${ftype}_${cat2}_${mass}.txt >card_${fname}_${ftype}_${cat1}${cat2}_${mass}.txt 
 done