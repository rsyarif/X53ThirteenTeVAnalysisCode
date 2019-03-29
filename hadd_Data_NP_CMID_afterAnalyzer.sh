#!/bin/bash

# common_eos='root://cmseos.fnal.gov://eos/uscms/store/group/lpcljm/LJMet94x_2lepTT_2017datasets_2019_1_13_rizki_hadds_Analyzer_elID2017'
# common_eos='root://cmseos.fnal.gov://eos/uscms/store/group/lpcljm/LJMet94x_2lepTT_2017datasets_2019_2_18_rizki_hadds_Analyzer_elID2017_nonIsoHTtrig'
common_eos='root://cmseos.fnal.gov://eos/uscms/store/group/lpcljm/LJMet94x_2lepTT_2017datasets_2019_3_15_rizki_hadds_Analyzer_elIDv2_nonIsoHTtrig'

# for eosdir in ${common_eos}_IsoTrig ${common_eos}_NonIsoTrig
for eosdir in ${common_eos}
do
    hadd -f $eosdir/Data_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElEl2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElEl2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElEl2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElEl2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElMu2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElMu2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElMu2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataElMu2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataMuMu2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataMuMu2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataMuMu2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/DataMuMu2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root
#    $eosdir/DataElEl2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
#    $eosdir/DataElMu2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
#    $eosdir/DataMuMu2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \

    hadd -f $eosdir/NonPromptData_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElEl2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElEl2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElEl2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElEl2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElMu2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElMu2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElMu2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataElMu2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataMuMu2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataMuMu2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataMuMu2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/NonPromptDataMuMu2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root
#    $eosdir/NonPromptDataElEl2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
#    $eosdir/NonPromptDataElMu2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
#    $eosdir/NonPromptDataMuMu2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \

    hadd -f $eosdir/ChargeMisID_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElEl2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElEl2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElEl2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElEl2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElMu2017C_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElMu2017D_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElMu2017E_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
    $eosdir/ChargeMisIDElMu2017F_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root
#    $eosdir/ChargeMisIDElEl2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \
#    $eosdir/ChargeMisIDElMu2017B_MuCBTightMiniIsoTight_ElMVA2017TightRC_2017C-F.root \

done
