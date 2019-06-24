#!/bin/bash

# postStr=nonIsoHTTrig
# postStr=nonIsoHTTrig_AllPt
# postStr=isoTrig_forTrilep
postStr=isoTrig_forTrilep_AllPt


workDir=FakeRate_${postStr}


hadd -f ${workDir}/FakeRate_Data_AllElectrons_MVA2017TightV2RC_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017CElectrons_MVA2017TightV2RC_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017DElectrons_MVA2017TightV2RC_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017EElectrons_MVA2017TightV2RC_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017FElectrons_MVA2017TightV2RC_2017dataset_${postStr}.root \


hadd -f ${workDir}/FakeRate_Data_2017FMuons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_1Muons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_2_1Muons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_2_2Muons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_2_3Muons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_2_4Muons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017F_2_5Muons_CBTightMiniIso_2017dataset_${postStr}.root


hadd -f ${workDir}/FakeRate_Data_AllMuons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017CMuons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017DMuons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017EMuons_CBTightMiniIso_2017dataset_${postStr}.root \
${workDir}/FakeRate_Data_2017FMuons_CBTightMiniIso_2017dataset_${postStr}.root \


