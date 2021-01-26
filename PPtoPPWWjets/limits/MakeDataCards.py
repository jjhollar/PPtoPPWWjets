#!/usr/bin/env python

import os, string, sys, posix, tokenize, array, getopt

# Make combine datacards for a counting experiment with 6 bins (3 years * 2 channels, WW+ZZ)
# This assumes a csv file produced from the Google spreadsheet is present in the current directory, named PPtoPPWWjets_MC_Results.csv
# Currently the background numbers and uncertainties are hard-coded, while on the MC statisitical errors are used for the signal systematics
# This generates all possible combinations of couplings + values, including some invalid ones where we don't have MC samples (to be improved)

def main(argv):

    # default to do all combinations, unless command line option is given                                                                                  
    mychannels = ["A0W","ACW","A0Z","ACZ"]
    mycouplings = ["1e-6","2e-6","5e-6","5e-6","8e-6","2e-5","1e-5","5e-5"]

    mychannel = "A0W"
    mycoupling = "1e-6"

    if(len(argv) > 0):
       mychannel = argv[0]
       mycoupling = argv[1]
       makecard(mychannel, mycoupling)
    else:
        for mychannel in mychannels:
            for mycoupling in mycouplings:
                makecard(mychannel, mycoupling)
        

def makecard(channel, coupling):
    linenum = 0

    infile = "PPtoPPWWjets_MC_Results.csv"
    infilehandle = open(infile)
    lines = infilehandle.readlines()

    # Create the combine card file
    outfilename = "pps-multichannel-hadronic" + channel + "_" + coupling + "_fixotherszero_twomassbins.txt"
    outfilehandle = open(outfilename,'w')
    
    # Default boilerplate stuff, same for all channels
    outfilehandle.write("# Counting experiment with multiple channels\n")
    outfilehandle.write("imax 6  number of channels\n")
    outfilehandle.write("jmax 1  number of processes-1\n")
    outfilehandle.write("kmax 5  number of nuisance parameters (sources of systematical uncertainties)\n")
    outfilehandle.write("------------\n")
    outfilehandle.write("# three channels (2016, 2017, 2018); 1 observed event in the first, 0 in the second\n")
    outfilehandle.write("bin            y2016ww        y2017ww    y2018ww    y2016zz  y2017zz  y2018zz\n")
    outfilehandle.write("observation     0             0          1          0        0        1\n")
    outfilehandle.write("------------\n")
    outfilehandle.write("# now we list the expected events for signal and all backgrounds in that bin\n")
    outfilehandle.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
    outfilehandle.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
    outfilehandle.write("# on each process and bin\n")
    outfilehandle.write("bin            y2016ww   y2016ww  y2017ww y2017ww  y2018ww   y2018ww  y2016zz y2016zz y2017zz y2017zz y2018zz y2018zz\n")
    outfilehandle.write("process        zzsig     zzbg     zzsig   zzbg     zzsig     zzbg     zzsig   zzbg   zzsig   zzbg   zzsig     zzbg\n")
    outfilehandle.write("process        0         1        0       1        0         1        0       1       0       1       0       1\n")

    signalsvector = [None] * 12
    staterrorsvector = [None] * 12

    # Hardcoded for now - backgrounds and stat. uncertainties from the anti-acoplanarity SB
    # Order of regions is 2016ww, 2017ww, 2018ww, 2016zz, 2017zz, 2018zz
    bgs = [0.8,3.2,18.3,2.0,2.8,23.3]
    bgerrs = ["-",1.88,"-",1.47,"-",1.18,"-",1.75,"-",1.43,"-",1.18]
    staterrorsvector[1] = "-"
    staterrorsvector[3] = "-"
    staterrorsvector[5] = "-"
    staterrorsvector[7] = "-"
    staterrorsvector[9] = "-"
    staterrorsvector[11] = "-"

    # Proton efficiency systematics, for signal
    efferrs = [1.141,"-",1.141,"-",1.0374,"-",1.0374,"-",1.0302,"-",1.0302,"-"]

    # Background model errors - difference between acoplanarity and mass sidebands
    bkgshapeerrs = ["-",1.25,"-",1.19,"-",1.10,"-",1.70,"-",1.50,"-",1.27]
    
    # Luminosity - applied to non-data driven yields (signal MC)
    lumis = [1.025,"-",1.023,"-",1.025,"-",1.025,"-",1.023,"-",1.025,"-"]

    signalsvector[1] = bgs[0]
    signalsvector[3] = bgs[1]
    signalsvector[5] = bgs[2]
    signalsvector[7] = bgs[3]
    signalsvector[9] = bgs[4]
    signalsvector[11] = bgs[5]


    for line in lines:
        linenum += 1
        if(linenum > 2):
            tokens = line.split(",")

            year = tokens[0]
            point = tokens[1]

            if(point.find(channel) != -1 and point.find(coupling) != -1):
                wwexpect = tokens[11]
                zzexpect = tokens[12]
                wwerror = tokens[13].rstrip()
                zzerror = tokens[14].rstrip()

                if(year == "2016"):
                    signalsvector[0] = round(float(wwexpect),3)
                    signalsvector[6] = round(float(zzexpect),3)
                    staterrorsvector[0] = round(float(wwerror),3)
                    staterrorsvector[6] = round(float(zzerror),3)
                if(year == "2017"):
                    signalsvector[2] = round(float(wwexpect),3)
                    signalsvector[8] = round(float(zzexpect),3)
                    staterrorsvector[2] = round(float(wwerror),3)
                    staterrorsvector[8] = round(float(zzerror),3)
                if(year == "2018"):
                    signalsvector[4] = round(float(wwexpect),3)
                    signalsvector[10] = round(float(zzexpect),3)
                    staterrorsvector[4] = round(float(wwerror),3)
                    staterrorsvector[10] = round(float(zzerror),3)

    outfilehandle.write("rate    ",)
    for entry in signalsvector:
        outfilehandle.write(str(entry) + " ",)

    # Signal efficiency systematics - MC statistics
    outfilehandle.write("\n\n------------\n")
    outfilehandle.write("signal lnN  ",)
    for sigerror in staterrorsvector:
        outfilehandle.write(str(sigerror) + " ",)
    outfilehandle.write("\n")

    # Signal efficiency systematics - proton efficiency/shower
    outfilehandle.write("signal lnN  ",)
    for ppsefferror in efferrs:
        outfilehandle.write(str(ppsefferror) + " ",)
    outfilehandle.write("\n")

    # Signal normalization systematics - luminosity
    outfilehandle.write("signal lnN  ",)
    for lumierror in lumis:
        outfilehandle.write(str(lumierror) + " ",)
    outfilehandle.write("\n")

    # Background systematics - statistical error on sidebands
    outfilehandle.write("bkg lnN   ",)
    for bkgerror in bgerrs:
        outfilehandle.write(str(bkgerror) + " ",)
    outfilehandle.write("\n")

    # Background systematics - shape variation (acoplanarity vs. pruned mass sideband regions)
    outfilehandle.write("bkg lnN   ",)
    for bkgshapeerr in bkgshapeerrs:
        outfilehandle.write(str(bkgshapeerr) + " ",)
    outfilehandle.write("\n")

                            
    outfilehandle.close()

    # Fill file with all combine commands for simple aymptotic limits. Only use valid ones (where samples currently exist).
    runallfilename = "RunAllLimits.txt"
    runallfilehandle = open(runallfilename,'w')

    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_1e-6_fixotherszero_twomassbins.txt --run blind --name a0W1e6\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_2e-6_fixotherszero_twomassbins.txt --run blind --name a0W2e6\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_5e-6_fixotherszero_twomassbins.txt --run blind --name a0W5e6\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_5e-6_fixotherszero_twomassbins.txt --run blind --name aCW5e6\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_8e-6_fixotherszero_twomassbins.txt --run blind --name aCW8e6\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_2e-5_fixotherszero_twomassbins.txt --run blind --name aCW2e5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_1e-5_fixotherszero_twomassbins.txt --run blind --name a0Z1e5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_5e-5_fixotherszero_twomassbins.txt --run blind --name a0Z5e5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_1e-5_fixotherszero_twomassbins.txt --run blind --name aCZ1e5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_5e-5_fixotherszero_twomassbins.txt --run blind --name aCZ5e5\n")
    runallfilehandle.write("\n")
    runallfilehandle.close()

if __name__ == "__main__":
    main(sys.argv[1:])

