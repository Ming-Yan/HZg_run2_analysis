#!/bin/bash
read -p "min: " min
read -p "max: " max
for ((i=${min}; i<${max}; i++))
do
    sh catjob${i}.sh &>jobout${i}.txt &
    #chmod +x  catjob${i}.sh
    #bsub -q 1nh -J "limitjob${i}" < catjob${i}.sh
done
echo "done job${min} to job${max}"