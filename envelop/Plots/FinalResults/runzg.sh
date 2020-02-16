p=0 ; while (( $p<20 )); do bsub -q 1nh scripts/s_sb_errorbands.sh $p test 125.97 0.95 5 ; (( p=$p+1 )) ; done
../../Background/bin/plotweightedbands -i inputfile.root --name example --lumi 35.9
