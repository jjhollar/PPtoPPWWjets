Starting to collect data cards for Higgs combine (http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/)

- CMSSW_10_2_13 version with recommended tags

- Example for a simple counting experiment, with 3 bins (2016, 2017, 2018) and only WW signal and background in the WW region (e.g. the ZZ 
  signal region, and any ZZ signal cross-feed into the WW signal region, is ignored)

  	  pps-multichannel-hadronicww_fixzz0.txt

	  * This example includes the up-to-date reMiniAOD signal expectations for a0W=2E-6 and anti-acoplanarity backgrounds. 
	    The systematics/nuisances are basically just a placeholder (stat. error on the background, and 20% on the signal)

- Simple/fast asymptotic profile likelihood expected limit on the signal strength (): 

	combine -M AsymptoticLimits pps-multichannel-hadronicww_fixzz0.txt -t -1

- ...
