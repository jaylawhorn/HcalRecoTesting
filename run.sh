#!/bin/bash

builddir=$1
file=$2
eosfolder=$3
outfolder=$4

workDir=`pwd`
echo `hostname`
echo "args:    $*"

SCRAM_ARCH=slc6_amd64_gcc491

cd ${builddir}
eval `scramv1 runtime -sh`
#cmsenv
cd ${workDir}
which root

echo "root://eoscms//eos/cms/"${eosfolder}${file} > Files.txt

cp ${builddir}/src/HcalRecoTesting2/Analysis .
cp ${builddir}/src/HcalRecoTesting2/Inputs.txt .

./Analysis Inputs.txt

cp Output.root ${outfolder}${file}

status=`echo $?`
echo "Status - $status"

exit $status