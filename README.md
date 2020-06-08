# PPtoPPWWjets
This version is tested in CMSSW_10_6_12, for the workflow:
     - Starting from CMSSW 94X AOD (data+MC)
     - Rerunning the PPS proton reconstruction with the Ultra-Legacy + re-MiniAOD settings on signal MC

Dependencies:
     - Last version of the JetToolbox. Setup recipe as of June 2020:
       	    git cms-init
	    git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_102X_v3
	    scram b -j 18

     - Proton direct simulation. Setup recipe as of June 2020 (pps_zx_mc_10_6 tag):
            https://twiki.cern.ch/twiki/bin/viewauth/CMS/TaggedProtonsDirectSimulation#Full_step_by_step_recipe_to_setu

