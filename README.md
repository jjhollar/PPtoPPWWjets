# PPtoPPWWjets
This version is tested in CMSSW_10_6_12, for the workflow:
     - Starting from CMSSW 94X AOD (data+MC)
     - Rerunning the PPS proton reconstruction with the Ultra-Legacy + re-MiniAOD settings on data 
     - Running the proton direct simulation + reconstruction on signal MC

Step-by-step instructions to setup a working environment, including the proton direct simulation for signal MC

	     cmsrel CMSSW_10_6_12
	     cd CMSSW_10_6_12/src
	     cmsenv

	     git cms-init
	     git remote add ctpps git@github.com:CTPPS/cmssw.git
	     git fetch ctpps pps_zx_mc_10_6
	     git checkout -b test ctpps/pps_zx_mc_10_6
	     git cms-addpkg IOMC/EventVertexGenerators SimCTPPS/Generators
	     scram b -r -j8
	     git clone https://github.com/jan-kaspar/proton_simulation_validation.git

	     git clone https://github.com/jjhollar/PPtoPPWWjets.git

	     git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_102X_v3
	     cp /afs/cern.ch/work/k/kshcheli/public/jonathan/toolboxstuff JMEAnalysis/JetToolbox/python/jetToolbox_cff.py
	     scram b -j 18

	     cd PPtoPPWWjets/PPtoPPWWjets/python
	     	 (copy relevant JEC files from subdirectories JEC2016, JEC2017, or JECAUTUMN18 to this directory)

             cmsRun ConfFileLegacyReRecoPrelim_cfg.py
	     	 (for data)
	     cmsRun ConfFileLegacyReRecoPrelimMCAllInOne_cfg.py 
	     	 (for signal MC with proton direct sim)

References:
	https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox#How_to_run_the_jetToolbox
	https://twiki.cern.ch/twiki/bin/viewauth/CMS/TaggedProtonsDirectSimulation#Full_step_by_step_recipe_to_setu
