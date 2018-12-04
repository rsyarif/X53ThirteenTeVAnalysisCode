#!/bin/bash

hostname

sample=${1}
era=${2}
decay=${3}
outputdir=${4}

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc700


scramv1 project CMSSW CMSSW_10_2_5
cd CMSSW_10_2_5
eval `scramv1 runtime -sh`
cd -

tar -xf Analyzer.tar
cd Analyzer/test/

#source setup.csh
export LD_LIBRARY_PATH=../lib/:$LD_LIBRARY_PATH 

echo "Executing: ./X53Analyzer.o ${sample} MVA2016TightRC CBTightMiniIsoTight ${era} ${decay}"

./X53Analyzer.o $sample MVA2016TightRC CBTightMiniIsoTight $era $decay

rm Pileup*.root

echo "ROOT Files to transfer:"
ls -l *.root

echo "xrdcp output for condor"
for FILE in *.root
do
  echo "xrdcp -f ${FILE} root://cmseos.fnal.gov/${outputdir}/${FILE}"
  xrdcp -f ${FILE} root://cmseos.fnal.gov/${outputdir}/${FILE} 2>&1
  XRDEXIT=$?
  if [[ $XRDEXIT -ne 0 ]]; then
    rm *.root
    echo "exit code $XRDEXIT, failure in xrdcp"
    exit $XRDEXIT
  fi
  rm ${FILE}
done
