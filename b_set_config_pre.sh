#!/bin/bash
if [ $# -eq 0 ]
  then
  echo "Please give run file name (without 1_ or 2_ or 3_ or 4_)"
#  echo "e.g. C_V150_phi2_40_trgandphi4L_pos1"
  return
fi

if [ $# -eq 1 ]
  then
  echo "Run file name is " ${1}
  echo "Please give also run number "
  return
fi

echo "----------------------------------------"
echo "*** Setting MutomcaReader/run/config.ini for run " ${2} " with name " ${1}
echo "----------------------------------------"

cp -f ./run/config.ini ./run/config.ini.bck
cp -f ./utils/config-example.ini ./run/config.ini
#Changing the 4 file names
perl -i.bak -p -e "s/rawFileNameTubes_1 1_/rawFileNameTubes_1 1_${1}/ig" ./run/config.ini
perl -i.bak -p -e "s/rawFileNameTubes_2 2_/rawFileNameTubes_2 2_${1}/ig" ./run/config.ini
perl -i.bak -p -e "s/rawFileNamePhi_3 3_/rawFileNamePhi_3 3_${1}/ig" ./run/config.ini
perl -i.bak -p -e "s/rawFileNamePhi_4 4_/rawFileNamePhi_4 4_${1}/ig" ./run/config.ini
echo "*** FINISHED "
