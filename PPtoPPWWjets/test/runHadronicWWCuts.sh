#!/bin/bash
if [ $# -lt 3 ]
then
    echo "At least three arguments required. Nothing done."
else
	export CMSSW_BASE=${1}
	export SCRAM_ARCH=slc7_amd64_gcc700
	cd $CMSSW_BASE/src/PPtoPPWWjets/PPtoPPWWjets/test
	eval `scramv1 runtime -sh`
	if [ $# -eq 3 ]
	then
		addUnitarityCut=",$3"
		root -l -q "runHadronicWWCuts.C(${2},false,false,false$addUnitarityCut)"
	else
		addUnitarityCut=",$4"
		if [ $3 == "protonSystematics" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},true,false,false$addUnitarityCut)"
		fi
		if [ $3 == "JECSystematicsUp" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,true,false$addUnitarityCut)"
		fi
		if [ $3 == "JECSystematicsDown" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,false,true$addUnitarityCut)"
		fi
	fi
fi