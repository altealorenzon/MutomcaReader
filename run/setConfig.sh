#!/bin/bash
if [ $# -eq 0 ]
then
    echo "Please give run file name (without 1_ or 2_ or 3_ or 4_)"
    return
fi

if [ $# -eq 1 ]
then
    echo "Run file name is " ${1}
    echo "Please give also run number "
    return
fi

if [ $# -eq 2 ]
then
    echo "Run file name is " ${1}
    echo "Run number is " ${2}
    echo "Please give also a number of events to analyze "
    return
fi

echo "----------------------------------------"
echo "*** Setting MutomcaReader/run/config.ini for run " ${2} " with name " ${1} " maxEventNumber " ${3}
echo "----------------------------------------"

cp -f ./config.ini ./config.ini.bck
cp -f ../utils/config-example.ini ./config.ini
#Changing the 4 file names
perl -i.bak -p -e "s/rawFileNameTubes_1 1_/rawFileNameTubes_1 1_${1}/ig" ./config.ini
perl -i.bak -p -e "s/rawFileNameTubes_2 2_/rawFileNameTubes_2 2_${1}/ig" ./config.ini
perl -i.bak -p -e "s/rawFileNamePhi_3 3_/rawFileNamePhi_3 3_${1}/ig" ./config.ini
perl -i.bak -p -e "s/rawFileNamePhi_4 4_/rawFileNamePhi_4 4_${1}/ig" ./config.ini
perl -i.bak -p -e "s/maxEventNumber 10/maxEventNumber ${3}/ig" ./config.ini
echo "*** FINISHED "
