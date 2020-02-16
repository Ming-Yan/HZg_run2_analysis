#!/bin/bash

totjobs=1000;

for ((i=502; i<=$totjobs; i++))
do
    index=123$i
    echo $index
    cp runallx.sh runall_$i.sh
    sed -i s/'INDEX'/${index}/g runall_$i.sh
    cp test.sub jobs_$i.sub
    sed -i s/'runall_x'/runall_${i}/g jobs_$i.sub
    chmod +x jobs_$i.sub
    chmod +x runall_${i}.sh
    echo "submitted the jobs" 
    condor_submit jobs_${i}.sub &
    #sh runall_${i}.sh
done

