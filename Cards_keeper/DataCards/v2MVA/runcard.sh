for m in $(seq 120 130)
do
    combine -M Asymptotic card_VBFMVA_v2_ele_mu_all_${m}_env.txt -m ${m} -n VBFMVA_v2_ele_mu_all 
    combine -M Asymptotic card_VBFMVA_v2_ele_mu_nm1_all_${m}_env.txt -m ${m} -n VBFMVA_v2_ele_mu_nm1_all 
done