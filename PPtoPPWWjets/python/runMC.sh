#!/bin/bash
if [ $# -lt 4 ]
then
    echo "At least four arguments are required. Nothing done."
    echo "Usage: CMSSW_BASE year cms_era sampleTag <partNumber> <nParts>"
    echo "Arguments in angular brackets are optional"
else
	output_dir="/afs/cern.ch/user/a/abellora/workarea/Work/PPtoPPWWjets_analysis/newInstall/CMSSW_10_6_17/src/PPtoPPWWjets/PPtoPPWWjets/python"
	export CMSSW_BASE=${1}
	export SCRAM_ARCH=slc7_amd64_gcc700
	cd $CMSSW_BASE/src/PPtoPPWWjets/PPtoPPWWjets/python
	eval `scramv1 runtime -sh`
	mkdir -p ${output_dir}/${2}/${3}
	file_dir=${output_dir}/${2}/${3}/
	if [ $# -eq 6 ]
	then
		set -x
		cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir} partNumber=${5} nParts=${6}
		set +x
	else
		set -x
		cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py year=${2} era=${3} sampleTag=${4} outputDir=${file_dir}
		set +x
	fi
fi

