for m in $(seq 0 10)
do
    sed -i s/m${m}_//g  *.txt
done
sed -i s/llg/hzg/g  *.txt
sed -i s/chan0/ZH/g  *.txt
sed -i s/chan1/ggF/g  *.txt
sed -i s/chan2/WH/g  *.txt
sed -i s/chan3/VBF/g  *.txt
sed -i s/chan4/ttH/g  *.txt
