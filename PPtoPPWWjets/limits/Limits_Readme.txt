Starting to collect data cards for Higgs combine (http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/)

- CMSSW_10_2_13 version with recommended tags

   - plus "CombineHarvester" (http://cms-analysis.github.io/CombineHarvester/) to plot impacts/limits

- Example for a simple multi-bin experiment, with 3 year bins (2016, 2017, 2018), 2 signal region bins ("A" and "B"), and 2 mass bins (WW and ZZ), 
  for WW and ZZ signals assuming all other AQGCs fixed to 0


   1) Download a .csv formatted file from the "results" section of the spreadsheet at: 
      https://docs.google.com/spreadsheets/d/1kG30Jn0RKLfVLNAH6gFYuPkeKnr22FPguiAphAZInl8/edit#gid=863852750

   2) Edit MorePointsNewRegionsMakeDataCards.py to point to the name of the .csv file from step 1) (currently "PPtoPPWWjets_MC_Results_v6e.csv")

   3) Run 
      	  python MorePointsNewRegionsMakeDataCards.py

      to create combine datacards for all points/years, with proton xi/JEC/MC stats systematics from the spreadsheet, plus 
      bkg. shape, bkg. normalization, proton efficiency, luminosity, and survival probability uncertainties added by the script. 
      A text file called "RunAllLimitsFromCardsNewRegions.txt" will also be created, containing all the relevant combine commands to 
      do expected/blind limits, fit diagnostics, and plots of the expected limits and nuisance impacts.

   4) Run all combine commands in "RunAllLimitsFromCardsNewRegions.txt"

      -> Note that several of the plotting commands depend on the CombineHarvester. A slightly modified version of the plotLimits.py, 
         called plotLimitsAQGC.py (adding the horizontal line at 1, and AQGC labels on the axes), is included here. The commands in 
	 RunAllLimitsFromCardsNewRegions.txt expect it to be placed in the bin/ directory, together with the original plotLimits.py. 

