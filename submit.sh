#!/bin/bash

#eosfolder=/store/user/jlawhorn/ZeroBias/Samples/160415_140315/0000/
#eosfolder=/store/user/jlawhorn/HighPtJet80/Samples/160516_071301/0000/
eosfolder=/store/group/phys_susy/razor/HCALDPG/HcalNtuple/HighPtJet80/Samples/160522_083815/0001/
#outfolder=/afs/cern.ch/work/j/jlawhorn/ZeroBiasD/
#outfolder=/afs/cern.ch/work/j/jlawhorn/HighPtJet80/
outfolder=/store/group/phys_susy/razor/HCALDPG/HcalRecoTesting/HighPtJet80/0001/

for file in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${eosfolder} | grep root`
do
    #if [[ -e ${outfolder}/${file} ]]; then
    #echo "Output file exists. Not submitting."
    #else
    #echo run.sh `pwd` $file $eosfolder $outfolder
    bsub -q 1nd run.sh ${CMSSW_BASE} $file $eosfolder $outfolder
    #fi

done