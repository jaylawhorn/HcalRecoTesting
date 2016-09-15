#!/bin/bash

cmsdir=$1
builddir=$2
file=$3
eosfolder=$4
outfolder=$5

workDir=`pwd`
echo `hostname`
echo "args:    $*"

SCRAM_ARCH=slc6_amd64_gcc491

cd ${cmsdir}
eval `scramv1 runtime -sh`
#cmsenv
cd ${workDir}
which root

cp ${builddir}/make_data_cov.C .

root -l -b -q make_data_cov.C+\(\"root://eoscms/${eosfolder}${file}\",\"${outfolder}${file}\"\)

#cp Output.root ${outfolder}${file}
#xrdcp Output.root root://eoscms/${outfolder}${file}

status=`echo $?`
echo "Status - $status"

exit $status