#!/bin/bash
if [ $# -lt 6 ]
then
    echo "At least six arguments required. Nothing done."
else
	export CMSSW_BASE=${1}
	export SCRAM_ARCH=slc7_amd64_gcc700
	cd $CMSSW_BASE/src/PPtoPPWWjets/PPtoPPWWjets/test
	eval `scramv1 runtime -sh`
	if [ $# -eq 6 ]
	then
		addMvvCuts=",$3,$4,$5,$6"
		root -l -q "runHadronicWWCuts.C(${2},false,false,false$addMvvCuts)"
	else
		addMvvCuts=",$4,$5,$6,$7"
		if [ $3 == "protonSystematics" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},true,false,false$addMvvCuts)"
		fi
		if [ $3 == "JECSystematicsUp" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,true,false$addMvvCuts)"
		fi
		if [ $3 == "JECSystematicsDown" ]
		then
		root -l -q "runHadronicWWCuts.C(${2},false,false,true$addMvvCuts)"
		fi
	fi
fi