#!/bin/bash

cmsdir=$1
builddir=$2
file=$3
eosfolder=$4
outfolder=$5

eosfolder=/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/HighPtJet80/Samples/160522_083815/0000/
#eosfolder=/store/user/jlawhorn/HighPtJet80/Samples/160516_071301/0000/
#eosfolder=/store/group/phys_susy/razor/HCALDPG/HcalNtuple/HighPtJet80/Samples/160522_083815/0001/
#outfolder=/afs/cern.ch/work/j/jlawhorn/ZeroBiasD/
#outfolder=/afs/cern.ch/work/j/jlawhorn/HighPtJet80/
outfolder=/afs/cern.ch/user/j/jlawhorn/MAHI/covMatrices/jobs/

for file in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${eosfolder} | grep root`
do
    #if [[ -e ${outfolder}/${file} ]]; then
    #echo "Output file exists. Not submitting."
    #else
    #echo run.sh `pwd` $file $eosfolder $outfolder
    bsub -q 1nh run.sh ${CMSSW_BASE} `pwd` $file $eosfolder $outfolder
    #fi

done