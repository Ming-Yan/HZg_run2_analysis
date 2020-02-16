#/!bin/bash
echo "===========Make Cards========="
read -p "fname:" fname
read -p "version name:" vername
#read -p "mva cut:" kinMVA
#kinMVA=-0.01
#string fin,string type, bool makedir, bool isboost, int cat = 1, float kinup = 1.0, float kindown = -1.0, float kincut=-0.01,float VBFcut=-0.01,string vername="_wboost"
#VBAMVA=-0.02
# string fin,string type, bool makedir, bool isboost, int cat = 1, float kincut=-0.01,float VBFcut=-0.01,string vername="_wboost"
for ptype in  mu
do
    #root -l -b -q make_Cards2_sep.C\(\"${vername}\"\,\"${fname}\"\,\"${ptype}\"\,\"${cat}\"\,true\,${kinMVA}\,${VBFMVA}\)
    for cat in 1 2 3 4 501 502 10 #501 502 10
    do
	root -l -b -q make_Cards2_sep.C\(\"${fname}\"\,\"${ptype}\"\,true\,true\,${cat}\,1.0\,-1.0\,-0.01\,0.08\,\"${vername}\"\)
    done
done

#root -l -b -q make_Cards2_sep.C\(\"${fname}\"\,\"ele_mu\"\,true\,true\,6789\,1.0\,-1.0\,-0.01\,0.08\,\"${vername}\"\)
