for i in ele mu
do 
    for m in $(seq 120 130)
    do
	cp cat5_${i}_m${m}.txt cat501_${i}_m${m}.txt 	
	cp cat10_${i}_m${m}.txt cat502_${i}_m${m}.txt 
#	for cat in 1 2 3 4 501 502 6789 10 5#
#	do	    
#	    mv cat${cat}_${i}_m${m}.txt cat${cat}_${i}_m${m}_2016.txt 
#	    rm cat${cat}_${i}_m${m}.txt
#	    sed -i s/cat${cat}/cat${cat}_2016/g  cat${cat}_${i}_m${m}_2016.txt
#	done
    done
done
