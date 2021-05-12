#!/bin/bash
if [ $# -lt 2 ]
then
    echo "At least two arguments required. Nothing done."
else
	export CMSSW_BASE=${1}
	export SCRAM_ARCH=slc7_amd64_gcc700
	cd $CMSSW_BASE/src/PPtoPPWWjets/PPtoPPWWjets/test
	eval `scramv1 runtime -sh`
	if [ $# -eq 2 ]
	then
		root -l -q "runHadronicWWCuts.C(${2})"
	else
		if [ $3 == "protonSystematics" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},true)"
		fi
		if [ $3 == "JECSystematicsUp" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,true)"
		fi
		if [ $3 == "JECSystematicsDown" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,false,true)"
		fi
	fi
fi