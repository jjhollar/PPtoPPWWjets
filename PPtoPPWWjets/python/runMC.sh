#!/bin/bash
if [ $# -lt 4 ]
then
    echo "At least four arguments are required. Nothing done."
    echo "Usage: CMSSW_BASE year cms_era sampleTag <partNumber> <nParts>"
    echo "Arguments in angular brackets are optional"
else
	output_dir="/afs/cern.ch/work/a/abellora/Work/PPtoPPWWjets_analysis/newInstall/CMSSW_10_6_17/src/PPtoPPWWjets/PPtoPPWWjets/python/signalNTuples_v5"
	export CMSSW_BASE=${1}
	export SCRAM_ARCH=slc7_amd64_gcc700
	cd $CMSSW_BASE/src/PPtoPPWWjets/PPtoPPWWjets/python
	eval `scramv1 runtime -sh`
	mkdir -p ${output_dir}/${2}/${3}
	file_dir=${output_dir}/${2}/${3}/
	if [ $# -eq 6 ]
	then
		echo "cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir} partNumber=${5} nParts=${6}"
		cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir} partNumber=${5} nParts=${6}
	else
		echo "cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir}"
		cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir}
	fi
fi