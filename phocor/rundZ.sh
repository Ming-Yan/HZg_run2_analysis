#nohup root -l -b -q EGMTnP_cut.C\(\"/data5/ggNtuples/V09_04_13_03/job_SingleEle_Run2016*_Legacy\"\,\"data_16\"\,1.\) &>log/egmdata  &
# nohup root -l -b -q EGMTnP_cut.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_DYJetsToLL_m50_aMCatNLO_ext2\"\,\"MC_16\"\,6077.22\) &>log/egm &

#nohup root -l -b -q phocor_mmg.C\(\"/data1/ggNtuples/V09_04_13_03/job_DoubleMu_Run2016*\"\,\"data_16\"\,1\) &>mmg16&
#nohup root -l -b -q phocor_mmg.C\(\"/data1/ggNtuples/V09_04_13_03/job_DoubleMu_Run2017*\"\,\"data_17\"\,1\) &>mmg17&
#nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_fall17_DYJetsToLL_m50_aMCatNLO*\"\,\"MC_17\\,6077.22\) &>mc17&
nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V10_02_10_04/job_autumn18_DYJetsToLL_m50_aMCatNLO*\"\,\"MC_18\",6077.22\) &>mc18&
#nohup root -l -b -q phocor_mmg.C\(\"/data3/ggNtuples/V10_02_10_04/job_DoubleMu_Run2018*\"\,\"data_18\"\,1\) &>mmg18&

#nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_DYJetsToLL_m50_aMCatNLO_ext2\"\,\"MC_16\",6077.22\) &>mmg16mc&
#nohup root -l -b -q EGMTnP_cut.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_TT_aMCatNLO\"\,\"TT_16\"\,831.76\) &>tt16 &
#nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_TT_aMCatNLO\"\,\"TT_16\"\,831.76\) &>tt16&
#nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_fall17_TT_aMCatNLO\"\,\"TT_17\"\,831.76\) &>tt17&
nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V10_02_10_04/job_autumn18_TT_aMCatNLO*\"\,\"TT_18\"\,831.76\) &>tt18&
# nohup root -l -b -q EGMTnP_cut.C\(\"/data6/ggNtuples/V09_04_13_04/job_fall17_TT_aMCatNLO\"\,\"TT_17\"\,831.76\) &>log/tt17  &
# nohup root -l -b -q EGMTnP_cut.C\(\"/data6/ggNtuples/V10_02_10_04/job_autumn18_TT_aMCatNLO\"\,\"TT_18\"\,831.76\) &>log/tt18 &
#nohup root -l -b -q EGMTnP_cut.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_WJets_madgraph*\"\,\"WJets_16\"\,61526.7\) &>log/wj16 &
#nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_summer16_WJets_madgraph*\"\,\"WJets_16\"\,61526.7\) &>log/wj16mmg &
# nohup root -l -b -q phocor_mmg.C\(\"/data6/ggNtuples/V09_04_13_04/job_fall17_WJets_madgraph*\"\,\"WJets_17\"\,61526.7\) &>log/wj16 &
# nohup root -l -b -q EGMTnP_cut.C\(\" /eos/cms/store/group/phys_smp/ggNtuples/13TeV/mc/V09_04_13_04/job_fall17_WJetsToLNu_MG/*/*/*/*\"\,\"WJets_17\"\,61526.7\) &>log/wj17 &

# nohup root -l -b -q EGMTnP_cut18.C\(\"/eos/cms/store/group/phys_egamma/soffi/TnP/ntuples_01162018/Moriond18_V1/mc/TnPTree_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_all\"\,\"/eos/cms/store/group/phys_egamma/soffi/TnP/ntuples_01162018/Moriond18_V1/PU/mc-V2-wRUNC/DY_madgraph_pho.pu.puTree\"\,\"weights_2017_runBCDEF\"\,\"MC_17\"\,1\) &>log/egm17 &
# nohup root -l -b -q EGMTnP_cut18.C\(\"/eos/cms/store/group/phys_egamma/soffi/TnP/ntuples_01162018/Moriond18_V1/data/TnPTree_17Nov2017_RunBCDEF\"\,\"data_17\"\) &>log/egm17d &
# nohup root -l -b -q EGMTnP_cut18.C\(\"/eos/cms/store/group/phys_egamma/swmukher/NtupleForRecoSF/Rereco2018Data_Autumn18MC_AOD/DYJetsToLLM50madgraphMLM\"\,\"/eos/cms/store/group/phys_egamma/swmukher/NtupleForRecoSF/Rereco2018Data_Autumn18MC_AOD/DY_MG_pho.pu.puTree\"\,\"weights_2018_runABCD\"\,\"MC_18\"\)  &>log/egm18 &
#nohup root -l -b -q EGMTnP_cut18.C\(\"/eos/cms/store/group/phys_egamma/swmukher/NtupleForRecoSF/Rereco2018Data_Autumn18MC_AOD/RunABCD\"\,\"data_18\"\)  &>log/egm18d &
#nohup root -l -b -q EGMTnP_cut18.C\(\"/eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V10_02_10_04/job_DoubleEG*_Run2018*/*\"\,\"dataabc_18\"\,1\) &>log/egmdata18  &
