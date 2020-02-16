for p in ele mu
do
    for cat in 1 2 3 4 501 502 10 
    do
	root -l -b -q plot_profile.C\(\"2016_profile\"\,\"${p}\"\,$cat\)
    done
done
root -l -b -q plot_profile.C\(\"2016_profile\"\,\"ele_mu\"\,6789\)
