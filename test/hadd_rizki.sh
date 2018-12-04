#!/bin/bash

folder=root://cmseos.fnal.gov//store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer

hadd -f $folder/Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2018A-D.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer | grep "/Data"`


hadd -f $folder/NonPromptData_MuCBTightMiniIsoTight_ElMVA2016TightRC_2018A-D.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer | grep "NonPrompt"`


# hadd -f $folder/ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2018A-D.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer | grep "Charge"`
# 
# 
# hadd -f $folder/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2018A-D.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer | grep "TTZ"`

# 

# hadd -f $folder/NonPromptData_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# 
# $folder/NonPromptDataElEl2017B_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElEl2017C_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElEl2017D_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElEl2017E_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElEl2017F_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElMu2017B_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElMu2017C_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElMu2017D_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElMu2017E_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataElMu2017F_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataMuMu2017B_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataMuMu2017C_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataMuMu2017D_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataMuMu2017E_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/NonPromptDataMuMu2017F_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root



# hadd -f $folder/ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# 
# $folder/ChargeMisIDElEl2017B_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElEl2017C_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElEl2017D_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElEl2017E_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElEl2017F_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElMu2017B_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElMu2017C_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElMu2017D_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElMu2017E_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root \
# $folder/ChargeMisIDElMu2017F_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root



# Missing:
