Starting to collect data cards for Higgs combine (http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/)

- CMSSW_10_2_13 version with recommended tags

- Example for a simple counting experiment, with 3 bins (2016, 2017, 2018) and WW and ZZ signals in both the WW and ZZ signal regions, assuming all 
  other AQGCs fixed to 0


   1) Download a .csv formatted file from the "results" section of the spreadsheet at: 
      https://docs.google.com/spreadsheets/d/1kG30Jn0RKLfVLNAH6gFYuPkeKnr22FPguiAphAZInl8/edit#gid=863852750

   2) Edit MakeDataCards.py to point to the name of the .csv file from step 1) (currently "PPtoPPWWjets_MC_Results_v3.csv")


   3) Run 
      	  python MakeDataCards.py

      to create combine datacards for all points/years, with proton xi/JEC/MC stats systematics from the spreadsheet, plus 
      bkg. shape/statistics, proton efficiency, luminosity systematics added by the script. All combine commands for blind 
      expected asymptotic profile likelihood limits will be in "RunAllLimits.txt"


   4) Run all combine commands in "RunAllLimits.txt"

   5) Run "PlotLimitsFinalReMiniAOD.C" to make all Brazilian flag plots (assumes 6 WW and 4 ZZ AQGC points are available - may crash otherwise)



