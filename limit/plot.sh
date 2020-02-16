read -p "file name:" fname
read -p "ver name:" vername

for ptype in ele mu
do 
    for cat in 501 502 1 2 3 4 10 #1234 12345 1234510 10
    do
	root -l -b -q limitplot.C\(\"${vername}\"\,\"${fname}\"\,\"${ptype}\"\,\"${cat}\"\)
    done
done
root -l -b -q limitplot.C\(\"${vername}\"\,\"${fname}\"\,\"ele_mu\"\,\"6789\"\)
root -l -b -q limitplot.C\(\"${vername}\"\,\"${fname}\"\,\"ele_mu\"\,\"12345678910\"\)