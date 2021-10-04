#!/usr/bin/env python

import os, string, sys, posix, tokenize, array, getopt

# Make combine datacards for a counting experiment with 6 bins (3 years * 2 channels, WW+ZZ)
# This assumes a csv file produced from the Google spreadsheet is present in the current directory, named PPtoPPWWjets_MC_Results_v6e.csv
# Currently the background numbers and uncertainties are hard-coded, while on the MC statisitical errors are used for the signal systematics
# This generates all possible combinations of couplings + values, including some invalid ones where we don't have MC samples (to be improved)

def main(argv):

    # default to do all combinations declared here, unless command line option is given                                                                                  
    mychannels = ["A0W","ACW","A0Z","ACZ"]
    mycouplings = ["5e-7","1e-6","2e-6","3_5e-6","5e-6","5e-6","8e-6","1e-5","1_4e-5","2e-5","5e-5"]

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

    #    infile = "PPtoPPWWjets_MC_Results_v6e.csv"
    infile = "PPtoPPWWjets_MC_ResultsAllCombined_v6e.csv"
    infilehandle = open(infile)
    lines = infilehandle.readlines()

    # Create the combine card file
    outfilename = "pps-multichannel-hadronic" + channel + "_" + coupling + "_newregions.txt"
    outfilehandle = open(outfilename,'w')
    

    signalsvector = [-1] * 24
    staterrorsvector = [None] * 24
    xiscale = [None] * 24
    jecscale = [None] * 24
    survprobvector = [None] * 24

    # Hardcoded for now - backgrounds and stat. uncertainties from the anti-acoplanarity SB
    # Order of regions is 2016wwa, 2017wwa, 2018wwa, 2016zza, 2017zza, 2018zza, 2016wwb, 2017wwb, 2018wwb, 2016zzb, 2017zzb, 2018zzb
    bgs = [0.36,1.58,11.56,1.5,1.56,14.16,1.44,9.98,41.42,1.5,3.74,37.43]
    bgerrs = ["-",2.07,"-",1.62,"-",1.22,"-",1.74,"-",1.52,"-",1.21,"-",1.63,"-",1.32,"-",1.14,"-",1.74,"-",1.39,"-",1.15]
    staterrorsvector[1] = "-"
    staterrorsvector[3] = "-"
    staterrorsvector[5] = "-"
    staterrorsvector[7] = "-"
    staterrorsvector[9] = "-"
    staterrorsvector[11] = "-"
    staterrorsvector[13] = "-"
    staterrorsvector[15] = "-"
    staterrorsvector[17] = "-"
    staterrorsvector[19] = "-"
    staterrorsvector[21] = "-"
    staterrorsvector[23] = "-"

    survprobvector = [1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-",1.10,"-"]

    xiscale[1] = "-"
    xiscale[3] = "-"
    xiscale[5] = "-"
    xiscale[7] = "-"
    xiscale[9] = "-"
    xiscale[11] = "-"
    xiscale[13] = "-"
    xiscale[15] = "-"
    xiscale[17] = "-"
    xiscale[19] = "-"
    xiscale[21] = "-"
    xiscale[23] = "-"

    jecscale[1] = "-"
    jecscale[3] = "-"
    jecscale[5] = "-"
    jecscale[7] = "-"
    jecscale[9] = "-"
    jecscale[11] = "-"
    jecscale[13] = "-"
    jecscale[15] = "-"
    jecscale[17] = "-"
    jecscale[19] = "-"
    jecscale[21] = "-"
    jecscale[23] = "-"


    # Proton efficiency systematics, for signal
    efferrs = [1.141,"-",1.0396,"-",1.0302,"-",1.141,"-",1.0396,"-",1.0302,"-",1.141,"-",1.0396,"-",1.0302,"-",1.141,"-",1.0396,"-",1.0302,"-"]

    # Background model errors - difference between acoplanarity and mass sidebands
    bkgshapeerrs = ["-",1.26,"-",1.07,"-",1.02,"-",1.77,"-",1.45,"-",1.30,"-",1.75,"-",1.29,"-",1.04,"-",1.43,"-",1.45,"-",1.11]

    # Luminosity - applied to non-data driven yields (signal MC)
    lumis = [1.025,"-",1.023,"-",1.025,"-",1.025,"-",1.023,"-",1.025,"-",1.025,"-",1.023,"-",1.025,"-",1.025,"-",1.023,"-",1.025,"-"]

    # xi scale systematics
    signalsvector[1] = bgs[0]
    signalsvector[3] = bgs[1]
    signalsvector[5] = bgs[2]
    signalsvector[7] = bgs[3]
    signalsvector[9] = bgs[4]
    signalsvector[11] = bgs[5]
    signalsvector[13] = bgs[6]
    signalsvector[15] = bgs[7]
    signalsvector[17] = bgs[8]
    signalsvector[19] = bgs[9]
    signalsvector[21] = bgs[10]
    signalsvector[23] = bgs[11]


    for line in lines:
        linenum += 1
        if(linenum > 2):
            tokens = line.split(",")

            year = tokens[0]
            point = tokens[1]

            #            print "year, point = " + str(year) + ", " + str(point)

            if(point.find(channel) != -1 and point.find(coupling) != -1):
                # Region "A"
                wwexpect = tokens[27]
                zzexpect = tokens[28]
                wwerror = tokens[29].rstrip()
                zzerror = tokens[30].rstrip()
                wwprotxierr = tokens[37].rstrip()
                zzprotxierr = tokens[38].rstrip()
                wwjecuperr = tokens[39].rstrip()
                wwjecdownerr = tokens[41].rstrip()
                zzjecuperr = tokens[40].rstrip()
                zzjecdownerr = tokens[42].rstrip()

                # Region "B"
                wwexpectb = tokens[27+16]
                zzexpectb = tokens[28+16]
                wwerrorb = tokens[29+16].rstrip()
                zzerrorb = tokens[30+16].rstrip()
                wwprotxierrb = tokens[37+16].rstrip()
                zzprotxierrb = tokens[38+16].rstrip()
                wwjecuperrb = tokens[39+16].rstrip()
                wwjecdownerrb = tokens[41+16].rstrip()
                zzjecuperrb = tokens[40+16].rstrip()
                zzjecdownerrb = tokens[42+16].rstrip()



                # Convert from Andrea->combine convention for 1-sided errors decreasing yield
                print year + ", " + channel + ", " + coupling
                print wwjecdownerr
                if(float(wwjecdownerr)) < 1.0:
                    wwjecdownerr = str(2.0 -float(wwjecdownerr))
                if(float(wwjecuperr)) < 1.0:
                    wwjecuperr = str(2.0 -float(wwjecuperr))
                if(float(zzjecdownerr)) < 1.0:
                    zzjecdownerr = str(2.0 -float(zzjecdownerr))
                if(float(zzjecuperr)) < 1.0:
                    zzjecuperr = str(2.0 -float(zzjecuperr))


                if(year == "2016"):
                    signalsvector[0] = round(float(wwexpect),3)
                    signalsvector[6] = round(float(zzexpect),3)
                    staterrorsvector[0] = round(float(wwerror),3)
                    staterrorsvector[6] = round(float(zzerror),3)
                    xiscale[0] = round(float(wwprotxierr),3)
                    xiscale[6] = round(float(zzprotxierr),3)
                    jecscale[0] = round(max(float(wwjecuperr),float(wwjecdownerr)),3)
                    jecscale[6] = round(max(float(zzjecuperr),float(zzjecdownerr)),3)
                    signalsvector[12] = round(float(wwexpectb),3)
                    signalsvector[18] = round(float(zzexpectb),3)
                    staterrorsvector[12] = round(float(wwerrorb),3)
                    staterrorsvector[18] = round(float(zzerrorb),3)
                    xiscale[12] = round(float(wwprotxierrb),3)
                    xiscale[18] = round(float(zzprotxierrb),3)
                    jecscale[12] = round(max(float(wwjecuperrb),float(wwjecdownerrb)),3)
                    jecscale[18] = round(max(float(zzjecuperrb),float(zzjecdownerrb)),3)


                if(year == "2017"):
                    signalsvector[2] = round(float(wwexpect),3)
                    signalsvector[8] = round(float(zzexpect),3)
                    staterrorsvector[2] = round(float(wwerror),3)
                    staterrorsvector[8] = round(float(zzerror),3)
                    xiscale[2] = round(float(wwprotxierr),3)
                    xiscale[8] = round(float(zzprotxierr),3)
                    jecscale[2] = round(max(float(wwjecuperr),float(wwjecdownerr)),3)
                    jecscale[8] = round(max(float(zzjecuperr),float(zzjecdownerr)),3)
                    signalsvector[14] = round(float(wwexpectb),3)
                    signalsvector[20] = round(float(zzexpectb),3)
                    staterrorsvector[14] = round(float(wwerrorb),3)
                    staterrorsvector[20] = round(float(zzerrorb),3)
                    xiscale[14] = round(float(wwprotxierrb),3)
                    xiscale[20] = round(float(zzprotxierrb),3)
                    jecscale[14] = round(max(float(wwjecuperrb),float(wwjecdownerrb)),3)
                    jecscale[20] = round(max(float(zzjecuperrb),float(zzjecdownerrb)),3)


                if(year == "2018"):
                    signalsvector[4] = round(float(wwexpect),3)
                    signalsvector[10] = round(float(zzexpect),3)
                    staterrorsvector[4] = round(float(wwerror),3)
                    staterrorsvector[10] = round(float(zzerror),3)
                    xiscale[4] = round(float(wwprotxierr),3)
                    xiscale[10] = round(float(zzprotxierr),3)
                    jecscale[4] = round(max(float(wwjecuperr),float(wwjecdownerr)),3)
                    jecscale[10] = round(max(float(zzjecuperr),float(zzjecdownerr)),3)
                    signalsvector[16] = round(float(wwexpectb),3)
                    signalsvector[22] = round(float(zzexpectb),3)
                    staterrorsvector[16] = round(float(wwerrorb),3)
                    staterrorsvector[22] = round(float(zzerrorb),3)
                    xiscale[16] = round(float(wwprotxierrb),3)
                    xiscale[22] = round(float(zzprotxierrb),3)
                    jecscale[16] = round(max(float(wwjecuperrb),float(wwjecdownerrb)),3)
                    jecscale[22] = round(max(float(zzjecuperrb),float(zzjecdownerrb)),3)


    # Default boilerplate stuff, same for all channels                                                                                                                                 
    outfilehandle.write("# Counting experiment with multiple channels\n")
    outfilehandle.write("imax *  number of channels\n")
    outfilehandle.write("jmax *  number of processes-1\n")
    outfilehandle.write("kmax *  number of nuisance parameters (sources of systematical uncertainties)\n")
    outfilehandle.write("------------\n")
    outfilehandle.write("# three channels (2016, 2017, 2018); 1 observed event in the first, 0 in the second\n")
    outfilehandle.write("bin            y2016ww        y2017ww    y2018ww    y2016zz  y2017zz  y2018zz y2016wwb        y2017wwb   y2018wwb    y2016zzb  y2017zzb  y2018zzb\n")
    #    outfilehandle.write("observation     0             0          1          0        0        1 0             0          1          0        0        1\n")
    outfilehandle.write("observation      " + str(signalsvector[0]+signalsvector[1]) + " " + str(signalsvector[2]+signalsvector[3]) + " " + str(signalsvector[4]+signalsvector[5]) + " " + str(signalsvector[6]+signalsvector[7]) + " " + str(signalsvector[8]+signalsvector[9]) + " " + str(signalsvector[10]+signalsvector[11]) + " " + str(signalsvector[12]+signalsvector[13]) + " " + str(signalsvector[14]+signalsvector[15]) + " " + str(signalsvector[16]+signalsvector[17]) + " " + str(signalsvector[18]+signalsvector[19]) + " " + str(signalsvector[20]+signalsvector[21]) + " " + str(signalsvector[22]+signalsvector[23]) + "\n")
    outfilehandle.write("------------\n")
    outfilehandle.write("# now we list the expected events for signal and all backgrounds in that bin\n")
    outfilehandle.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
    outfilehandle.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
    outfilehandle.write("# on each process and bin\n")
    outfilehandle.write("bin            y2016ww   y2016ww  y2017ww y2017ww  y2018ww   y2018ww  y2016zz y2016zz y2017zz y2017zz y2018zz y2018zz y2016wwb   y2016wwb  y2017wwb y2017wwb  y2018wwb   y2018wwb  y2016zzb y2016zzb y2017zzb y2017zzb y2018zzb y2018zzb\n")
    outfilehandle.write("process        vvsig     vvbg     vvsig   vvbg     vvsig     vvbg     vvsig   vvbg   vvsig   vvbg   vvsig     vvbg vvsig     vvbg     vvsig   vvbg     vvsig     vvbg     vvsig   vvbg   vvsig   vvbg   vvsig     vvbg\n")
    outfilehandle.write("process        0         1        0       1        0         1        0       1       0       1       0       1 0         1        0       1        0         1        0       1       0       1       0       1\n")


    outfilehandle.write("rate    ",)
    for entry in signalsvector:
        outfilehandle.write(str(entry) + " ",)

    # Signal efficiency systematics - MC statistics
    outfilehandle.write("\n\n------------\n")
    outfilehandle.write("signal_mcstat lnN  ",)
    for sigerror in staterrorsvector:
        outfilehandle.write(str(sigerror) + " ",)
    outfilehandle.write("   # signal MC statistics")
    outfilehandle.write("\n")

    # Signal efficiency systematics - proton efficiency/shower
    outfilehandle.write("signal_peff lnN  ",)
    for ppsefferror in efferrs:
        outfilehandle.write(str(ppsefferror) + " ",)
    outfilehandle.write("   # proton eff")
    outfilehandle.write("\n")

    # Signal normalization systematics - luminosity
    outfilehandle.write("signal_lumi lnN  ",)
    for lumierror in lumis:
        outfilehandle.write(str(lumierror) + " ",)
    outfilehandle.write("   # lumi")
    outfilehandle.write("\n")

    # Signal xi scale systematics
    outfilehandle.write("signal_xi lnN  ",)
    for xiscaleerr in xiscale:
        outfilehandle.write(str(xiscaleerr)  + " ",)
    outfilehandle.write("   # xi systematcs")
    outfilehandle.write("\n")

    # Signal JEC systematics
    outfilehandle.write("signal_jec lnN  ",)
    for jecscaleerr in jecscale:
        outfilehandle.write(str(jecscaleerr)  + " ",)
    outfilehandle.write("   # JEC systematics")
    outfilehandle.write("\n")

    # Signal survival probability - 10% systematic on all channels
    outfilehandle.write("signal_survprob lnN  ",)
    for survprob in survprobvector:
        outfilehandle.write(str(survprob)   + " ",)
    outfilehandle.write("   # Survival probability")
    outfilehandle.write("\n")

    # Background systematics - statistical error on sidebands
    outfilehandle.write("bkg_stat lnN   ",)
    for bkgerror in bgerrs:
        outfilehandle.write(str(bkgerror) + " ",)
    outfilehandle.write("   # bkg statistics")
    outfilehandle.write("\n")

    # Background systematics - shape variation (acoplanarity vs. pruned mass sideband regions)
    outfilehandle.write("bkg_shape lnN   ",)
    for bkgshapeerr in bkgshapeerrs:
        outfilehandle.write(str(bkgshapeerr) + " ",)
    outfilehandle.write("   # bkg shape variation")
    outfilehandle.write("\n")

                            
    outfilehandle.close()

    # Fill a text file with all combine commands for simple asymptotic limits, fit diagnostics, and plots. Only use valid ones (where samples currently exist).
    runallfilename = "RunAllLimitsFromCardsNewRegions.txt"
    runallfilehandle = open(runallfilename,'w')

    #
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_5e-7_newregions.txt --run blind --name a0W5e7 -m 5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_1e-6_newregions.txt --run blind --name a0W1e6 -m 10\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_2e-6_newregions.txt --run blind --name a0W2e6 -m 20\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_3_5e-6_newregions.txt --run blind --name a0W3_5e6 -m 35\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0W_5e-6_newregions.txt --run blind --name a0W5e6 -m 50\n")
    #
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_2e-6_newregions.txt --run blind --name aCW2e6 -m 20\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_5e-6_newregions.txt --run blind --name aCW5e6 -m 50\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_8e-6_newregions.txt --run blind --name aCW8e6 -m 80\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_1_4e-5_newregions.txt --run blind --name aCW1_4e5 -m 140\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACW_2e-5_newregions.txt --run blind --name aCW2e5 -m 200\n")
    #
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_5e-7_newregions.txt --run blind --name a0Z5e7 -m 5\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_1e-6_newregions.txt --run blind --name a0Z1e6 -m 10\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_2e-6_newregions.txt --run blind --name a0Z2e6 -m 20\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_3_5e-6_newregions.txt --run blind --name a0Z3_5e6 -m 35\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_5e-6_newregions.txt --run blind --name a0Z5e6 -m 50\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_1e-5_newregions.txt --run blind --name a0Z1e5 -m 100\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_2e-5_newregions.txt --run blind --name a0Z2e5 -m 200\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicA0Z_5e-5_newregions.txt --run blind --name a0Z5e5 -m 500\n")
    #
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_2e-6_newregions.txt --run blind --name aCZ2e6 -m 20\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_5e-6_newregions.txt --run blind --name aCZ5e6 -m 50\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_8e-6_newregions.txt --run blind --name aCZ8e6 -m 80\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_1e-5_newregions.txt --run blind --name aCZ1e5 -m 100\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_1_4e-6_newregions.txt --run blind --name aCZ1_4e6 -m 140\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_2e-5_newregions.txt --run blind --name aCZ2e5 -m 200\n")
    runallfilehandle.write("combine -M AsymptoticLimits pps-multichannel-hadronicACZ_5e-5_newregions.txt --run blind --name aCZ5e5 -m 500\n")

    runallfilehandle.write("\n")

    runallfilehandle.write("python ../../../../../../bin/slc7_amd64_gcc700/combineTool.py -M CollectLimits *a0W*AsymptoticLimits* --use-dirs -o limits.json; mv limits_default.json limits_a0W.json\n")
    runallfilehandle.write("python ../../../../../../bin/slc7_amd64_gcc700/combineTool.py -M CollectLimits *aCW*AsymptoticLimits* --use-dirs -o limits.json; mv limits_default.json limits_aCW.json\n")
    runallfilehandle.write("python ../../../../../../bin/slc7_amd64_gcc700/combineTool.py -M CollectLimits *a0Z*AsymptoticLimits* --use-dirs -o limits.json; mv limits_default.json limits_a0Z.json\n")
    runallfilehandle.write("python ../../../../../../bin/slc7_amd64_gcc700/combineTool.py -M CollectLimits *aCZ*AsymptoticLimits* --use-dirs -o limits.json; mv limits_default.json limits_aCZ.json\n")

    runallfilehandle.write("\n")

    # Note - here I modified a bit the default plotLimits.py, just to draw a horizontal line and to set useful defaults so we don't have to pass everything by 
    # command line
    runallfilehandle.write("../../../../../../bin/slc7_amd64_gcc700/plotLimitsAQGC.py limits_a0W.json --show exp --logy --x-title 'a^{0}_{W}/#Lambda^{2} (#times 10^{-7} GeV^{-2})'; mv limit.png limit_a0W.png; mv limit.pdf limit_a0W.pdf\n")
    runallfilehandle.write("../../../../../../bin/slc7_amd64_gcc700/plotLimitsAQGC.py limits_aCW.json --show exp --logy --x-title 'a^{C}_{W}/#Lambda^{2} (#times 10^{-7} GeV^{-2})'; mv limit.png limit_aCW.png; mv limit.pdf limit_aCW.pdf\n")
    runallfilehandle.write("../../../../../../bin/slc7_amd64_gcc700/plotLimitsAQGC.py limits_a0Z.json --show exp --logy --x-title 'a^{0}_{Z}/#Lambda^{2} (#times 10^{-7} GeV^{-2})'; mv limit.png limit_a0Z.png; mv limit.pdf limit_a0Z.pdf\n")
    runallfilehandle.write("../../../../../../bin/slc7_amd64_gcc700/plotLimitsAQGC.py limits_aCZ.json --show exp --logy --x-title 'a^{C}_{Z}/#Lambda^{2} (#times 10^{-7} GeV^{-2})'; mv limit.png limit_aCZ.png; mv limit.pdf limit_aCZ.pdf\n")

    runallfilehandle.write("\n")

    #
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0W_5e-7_newregions.txt -m 5 -o workspace_hadronicA0W_5e-7.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0W_1e-6_newregions.txt -m 10 -o workspace_hadronicA0W_1e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0W_2e-6_newregions.txt -m 20 -o workspace_hadronicA0W_2e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0W_3_5e-6_newregions.txt -m 35 -o workspace_hadronicA0W_3_5e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0W_5e-6_newregions.txt -m 50 -o workspace_hadronicA0W_5e-6.root\n')
    #
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACW_2e-6_newregions.txt -m 20 -o workspace_hadronicACW_5e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACW_5e-6_newregions.txt -m 50 -o workspace_hadronicACW_5e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACW_8e-6_newregions.txt -m 80 -o workspace_hadronicACW_8e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACW_1_4e-5_newregions.txt -m 140 -o workspace_hadronicACW_1_4e-5.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACW_2e-5_newregions.txt -m 200 -o workspace_hadronicACW_2e-5.root\n')
    #
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0Z_5e-6_newregions.txt -m 50 -o workspace_hadronicA0Z_5e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0Z_1e-5_newregions.txt -m 100 -o workspace_hadronicA0Z_1e-5.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0Z_2e-5_newregions.txt -m 200 -o workspace_hadronicA0Z_2e-5.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicA0Z_5e-5_newregions.txt -m 500 -o workspace_hadronicA0Z_5e-5.root\n')
    #
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACZ_5e-6_newregions.txt -m 50 -o workspace_hadronicACZ_5e-6.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACZ_1e-5_newregions.txt -m 100 -o workspace_hadronicACZ_1e-5.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACZ_2e-5_newregions.txt -m 200 -o workspace_hadronicACZ_2e-5.root\n')
    runallfilehandle.write('text2workspace.py pps-multichannel-hadronicACZ_5e-5_newregions.txt -m 500 -o workspace_hadronicACZ_5e-5.root\n')

    runallfilehandle.write("\n")

    # Fit diagnostics, expectedSignal=0
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_5e-7_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL  --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0W_5e-7.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_1e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL  --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0W_1e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_2e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL  --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0W_2e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_3_5e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0W_3_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_5e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0W_5e-6.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_2e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACW_2e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_5e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACW_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_8e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACW_8e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_1_4e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACW_1_4e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_2e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACW_2e-5.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_5e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0Z_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_1e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0Z_1e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_2e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0Z_2e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_5e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicA0Z_5e-5.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_5e-6_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACZ_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_1e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACZ_1e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_2e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACZ_2e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_5e-5_newregions.txt -t -1 --expectSignal 0 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s0_hadronicACZ_5e-5.root\n")

    runallfilehandle.write("\n")

    # Fit diagnostics, expectedSignal=1                                                                                                                                                                           
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_5e-7_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0W_5e-7.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_1e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0W_1e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_2e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0W_2e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_3_5e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0W_3_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0W_5e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0W_5e-6.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_2e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACW_2e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_5e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACW_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_8e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACW_8e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_1_4e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACW_1_4e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACW_2e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACW_2e-5.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_5e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0Z_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_1e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0Z_1e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_2e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0Z_2e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicA0Z_5e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicA0Z_5e-5.root\n")
    #
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_5e-6_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACZ_5e-6.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_1e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACZ_1e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_2e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACZ_2e-5.root\n")
    runallfilehandle.write("combine -M FitDiagnostics pps-multichannel-hadronicACZ_5e-5_newregions.txt -t -1 --expectSignal 1 --forceRecreateNLL --rMin -1 --rMax 2; mv fitDiagnostics.root fitDiagnostics_s1_hadronicACZ_5e-5.root\n")

    runallfilehandle.write("\n")

    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0W_5e-7.root --all -g plots_a0w5e7_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0W_1e-6.root --all -g plots_a0w1e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0W_2e-6.root --all -g plots_a0w2e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0W_3_5e-6.root --all -g plots_a0w3_5e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0W_5e-6.root --all -g plots_a0w5e6_s0.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACW_2e-6.root --all -g plots_aCw2e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACW_5e-6.root --all -g plots_aCw5e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACW_8e-6.root --all -g plots_aCw8e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACW_1_4e-5.root --all -g plots_aCw1_4e5_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACW_2e-5.root --all -g plots_aCw2e5_s0.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0Z_5e-6.root --all -g plots_a0z5e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0Z_1e-5.root --all -g plots_a0z1e5_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0Z_2e-5.root --all -g plots_a0z1e5_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicA0Z_5e-5.root --all -g plots_a0z5e5_s0.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACZ_5e-6.root --all -g plots_aCz5e6_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACZ_1e-5.root --all -g plots_aCz1e5_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACZ_2e-5.root --all -g plots_aCz2e5_s0.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s0_hadronicACZ_5e-5.root --all -g plots_aCz5e5_s0.root\n")


    runallfilehandle.write("\n")

    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0W_5e-7.root --all -g plots_a0w5e7_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0W_1e-6.root --all -g plots_a0w1e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0W_2e-6.root --all -g plots_a0w2e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0W_3_5e-6.root --all -g plots_a0w3_5e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0W_5e-6.root --all -g plots_a0w5e6_s1.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACW_2e-6.root --all -g plots_aCw2e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACW_5e-6.root --all -g plots_aCw5e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACW_8e-6.root --all -g plots_aCw8e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACW_1_4e-5.root --all -g plots_aCw1_4e5_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACW_2e-5.root --all -g plots_aCw2e5_s1.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0Z_5e-6.root --all -g plots_a0z5e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0Z_1e-5.root --all -g plots_a0z1e5_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0Z_2e-5.root --all -g plots_a0z2e5_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicA0Z_5e-5.root --all -g plots_a0z5e5_s1.root\n")
    #
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACZ_5e-6.root --all -g plots_aCz5e6_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACZ_1e-5.root --all -g plots_aCz1e5_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACZ_2e-5.root --all -g plots_aCz2e5_s1.root\n")
    runallfilehandle.write("python ../../../test/diffNuisances.py fitDiagnostics_s1_hadronicACZ_5e-5.root --all -g plots_aCz5e5_s1.root\n")


    runallfilehandle.write("\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1  --expectSignal 0 --robustFit 1 --doInitialFit --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1 --expectSignal 0 --robustFit 1 --doFits --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1 --expectSignal 0 --robustFit 1 --rMin -1 --rMax 2 --output impacts_hadronicA0W_5e-6_azimov0.json\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts_hadronicA0W_5e-6_azimov0.json -o impacts_hadronicA0W_5e-6_azimov0\n")

    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --doInitialFit --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --doFits --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0W_5e-6.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --rMin -1 --rMax 2 --output impacts_hadronicA0W_5e-6_azimov1.json\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts_hadronicA0W_5e-6_azimov1.json -o impacts_hadronicA0W_5e-6_azimov1\n")

    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 0 --robustFit 1 --doInitialFit --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 0 --robustFit 1 --doFits --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 0 --robustFit 1 --rMin -1 --rMax 2 --output impacts_hadronicA0Z_1e-5_azimov0.json\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts_hadronicA0Z_1e-5_azimov0.json -o impacts_hadronicA0Z_1e-5_azimov0\n")

    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --doInitialFit --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --doFits --rMin -1 --rMax 2\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d workspace_hadronicA0Z_1e-5.root -m 200 -t -1 --expectSignal 1 --robustFit 1 --rMin -1 --rMax 2 --output impacts_hadronicA0Z_1e-5_azimov1.json\n")
    runallfilehandle.write("python ../../../../../CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts_hadronicA0Z_1e-5_azimov1.json -o impacts_hadronicA0Z_1e-5_azimov1\n")


    runallfilehandle.close()

if __name__ == "__main__":
    main(sys.argv[1:])

