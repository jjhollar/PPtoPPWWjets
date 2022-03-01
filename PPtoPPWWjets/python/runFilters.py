#!/cvmfs/cms.cern.ch/slc7_amd64_gcc820/cms/cmssw/CMSSW_10_6_17/external/slc7_amd64_gcc820/bin/python3
import subprocess
from tqdm import tqdm

def process_stderr(stderr):
	stderr = stderr.decode('UTF-8').split(sep='\n')
	summary_line = ""
	for line in stderr:
		if ('Event' in line) and ('Summary' in line) and ('TrigReport' in line):
			summary_line = stderr[stderr.index(line)+1]
	summary_line = summary_line.split()
	fraction = float(summary_line[7]) / float(summary_line[4])
	return fraction

if __name__ == "__main__":
	sampleTags = [
		"SM_WW"
	    # "WW_A0W5e-7",
	    # "WW_A0W1e-6",  
	    # "WW_A0W2e-6",  
	    # "WW_A0W3_5e-6",
	    # "WW_A0W5e-6", 
	    # "WW_ACW2e-6", 
	    # "WW_ACW5e-6", 
	    # "WW_ACW8e-6", 
	    # "WW_ACW1_4e-5", 
	    # "WW_ACW2e-5", 
	    # "ZZ_A0Z5e-6", 
	    # "ZZ_A0Z1e-5", 
	    # "ZZ_A0Z2e-5", 
	    # "ZZ_A0Z5e-5", 
	    # "ZZ_ACZ5e-6", 
	    # "ZZ_ACZ1e-5", 
	    # "ZZ_ACZ2e-5", 
	    # "ZZ_ACZ5e-5", 
	]
	xsec = {
		"SM_WW" : 4.1070554496641876E-002,
	    "WW_A0W5e-7" : 4.2163316591838605E-002,
	    "WW_A0W1e-6" : 4.5394743649008480E-002, 
	    "WW_A0W2e-6" : 5.8315830794403188E-002, 
	    "WW_A0W3_5e-6" : 9.3485285081663066E-002,
	    "WW_A0W5e-6" : 0.14813204760228599,
	    "WW_ACW2e-6" : 4.2455694489743553E-002,
	    "WW_ACW5e-6" : 0.48745879E-01,
	    "WW_ACW8e-6" : 6.1402256541154263E-002,
	    "WW_ACW1_4e-5" : 0.10203597076732003,
	    "WW_ACW2e-5" : 0.16476237329000343,
	    "ZZ_A0Z5e-6" : 1.7859991686475674E-002,
	    "ZZ_A0Z1e-5" : 7.1475868923898941E-002,
	    "ZZ_A0Z2e-5" : 0.28575986698361078,
	    "ZZ_A0Z5e-5" : 1.7867409824379850,
	    "ZZ_ACZ5e-6" : 1.2752931559334658E-003,
	    "ZZ_ACZ1e-5" : 5.1004960918855750E-003,
	    "ZZ_ACZ2e-5" : 2.0404690494935453E-002,
	    "ZZ_ACZ5e-5" : 0.12751240229708516,
	}
	command = "scramv1 runtime -sh; cmsRun ConfFileGenCutsFilter_cfg.py year={year} era={era} sampleTag={sampleTag}"
	results = []
	for sampleTag in tqdm(sampleTags):
		completed_process = subprocess.run(command.format(year=2016,era="B",sampleTag=sampleTag),shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
		print(completed_process.stderr)
		fraction = process_stderr(completed_process.stderr)
		results.append(sampleTag+" sigmaGEN/sigmaAQGC="+str(fraction)+" sigmaGEN="+str(fraction*xsec[sampleTag]*1000)+" fb "+" sigmaAQGC="+str(xsec[sampleTag]*1000)+" fb ")
	for result in results:
		print(result)

"""
Output for 2016 B
SM_WW sigmaGEN/sigmaAQGC=0.059898746099958794 sigmaGEN=2.4600747159788727 fb  sigmaAQGC=41.070554496641876 fb
WW_A0W5e-7 sigmaGEN/sigmaAQGC=0.08001300543863797 sigmaGEN=3.373613679773797 fb  sigmaAQGC=42.16331659183861 fb 
WW_A0W1e-6 sigmaGEN/sigmaAQGC=0.1380013596193066 sigmaGEN=6.264536343133053 fb  sigmaAQGC=45.39474364900848 fb 
WW_A0W2e-6 sigmaGEN/sigmaAQGC=0.31085937024179305 sigmaGEN=18.12802243587514 fb  sigmaAQGC=58.31583079440319 fb 
WW_A0W3_5e-6 sigmaGEN/sigmaAQGC=0.5324411764705882 sigmaGEN=49.775415171569016 fb  sigmaAQGC=93.48528508166306 fb 
WW_A0W5e-6 sigmaGEN/sigmaAQGC=0.6720952915792274 sigmaGEN=99.55885172548639 fb  sigmaAQGC=148.13204760228598 fb 
WW_ACW2e-6 sigmaGEN/sigmaAQGC=0.08301610987605446 sigmaGEN=3.524506598624751 fb  sigmaAQGC=42.45569448974355 fb 
WW_ACW5e-6 sigmaGEN/sigmaAQGC=0.19170632222977566 sigmaGEN=9.344893186947653 fb  sigmaAQGC=48.745879 fb 
WW_ACW8e-6 sigmaGEN/sigmaAQGC=0.33192445245765967 sigmaGEN=20.380910382087382 fb  sigmaAQGC=61.402256541154266 fb 
WW_ACW1_4e-5 sigmaGEN/sigmaAQGC=0.5572058823529412 sigmaGEN=56.855043123143474 fb  sigmaAQGC=102.03597076732004 fb 
WW_ACW2e-5 sigmaGEN/sigmaAQGC=0.6872875594833446 sigmaGEN=113.23912943317026 fb  sigmaAQGC=164.76237329000344 fb 
ZZ_A0Z5e-6 sigmaGEN/sigmaAQGC=0.9150588235294118 sigmaGEN=16.342942980871506 fb  sigmaAQGC=17.859991686475674 fb 
ZZ_A0Z1e-5 sigmaGEN/sigmaAQGC=0.9162334593572778 sigmaGEN=65.48858264471127 fb  sigmaAQGC=71.47586892389894 fb 
ZZ_A0Z2e-5 sigmaGEN/sigmaAQGC=0.9161765140543257 sigmaGEN=261.80647878967227 fb  sigmaAQGC=285.7598669836108 fb 
ZZ_A0Z5e-5 sigmaGEN/sigmaAQGC=0.9162334593572778 sigmaGEN=1637.0718713145761 fb  sigmaAQGC=1786.740982437985 fb 
ZZ_ACZ5e-6 sigmaGEN/sigmaAQGC=0.9126764705882353 sigmaGEN=1.1639300565226876 fb  sigmaAQGC=1.275293155933466 fb 
ZZ_ACZ1e-5 sigmaGEN/sigmaAQGC=0.9140890425123341 sigmaGEN=4.662307588969588 fb  sigmaAQGC=5.100496091885575 fb 
ZZ_ACZ2e-5 sigmaGEN/sigmaAQGC=0.9140484142700913 sigmaGEN=18.650874990567754 fb  sigmaAQGC=20.404690494935455 fb 
ZZ_ACZ5e-5 sigmaGEN/sigmaAQGC=0.9170826810031607 sigmaGEN=116.93941575976444 fb  sigmaAQGC=127.51240229708516 fb 
"""

"""
Output for 2016 B - FXS cuts added
SM_WW sigmaGEN/sigmaAQGC=0.042179313592747396 sigmaGEN=1.7323277975418794 fb  sigmaAQGC=41.070554496641876 fb
WW_A0W5e-7 sigmaGEN/sigmaAQGC=0.045607708678174506 sigmaGEN=1.9229722600262167 fb  sigmaAQGC=42.16331659183861 fb 
WW_A0W1e-6 sigmaGEN/sigmaAQGC=0.05441432920521384 sigmaGEN=2.470124525103438 fb  sigmaAQGC=45.39474364900848 fb 
WW_A0W2e-6 sigmaGEN/sigmaAQGC=0.08310493939947622 sigmaGEN=4.8463335841989865 fb  sigmaAQGC=58.31583079440319 fb 
WW_A0W3_5e-6 sigmaGEN/sigmaAQGC=0.1141764705882353 sigmaGEN=10.673819902559297 fb  sigmaAQGC=93.48528508166306 fb 
WW_A0W5e-6 sigmaGEN/sigmaAQGC=0.13625750007389234 sigmaGEN=20.184102487114306 fb  sigmaAQGC=148.13204760228598 fb 
WW_ACW2e-6 sigmaGEN/sigmaAQGC=0.047720559125376864 sigmaGEN=2.026009479106744 fb  sigmaAQGC=42.45569448974355 fb 
WW_ACW5e-6 sigmaGEN/sigmaAQGC=0.06484792953625158 sigmaGEN=3.1610693265746455 fb  sigmaAQGC=48.745879 fb 
WW_ACW8e-6 sigmaGEN/sigmaAQGC=0.08615848432004256 sigmaGEN=5.290325357416269 fb  sigmaAQGC=61.402256541154266 fb 
WW_ACW1_4e-5 sigmaGEN/sigmaAQGC=0.1176764705882353 sigmaGEN=12.007232912942571 fb  sigmaAQGC=102.03597076732004 fb 
WW_ACW2e-5 sigmaGEN/sigmaAQGC=0.14128218012000118 sigmaGEN=23.277987300157136 fb  sigmaAQGC=164.76237329000344 fb 
"""