import FWCore.ParameterSet.Config as cms
import sys

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ()
options.register('year',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.int,
  "year")
options.register('era',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.string,
  "CMS era")
options.register('sampleTag',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.string,
  "Tag of the sample to analyze")
options.register('outputDir',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.string,
  "Output directory")
options.register('partNumber',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.int,
  "Number of the part")
options.register('nParts',
  '',
  VarParsing.VarParsing.multiplicity.singleton,
  VarParsing.VarParsing.varType.int,
  "Number of parts")
options.partNumber = 0
options.nParts = 0
options.parseArguments() 

if ((options.partNumber == 0) ^ (options.nParts == 0)):
  print "ERROR: either none or both partNumber and nParts must be set"
  sys.exit(1)
elif ((options.partNumber == 0) & (options.nParts == 0)):
  options.partNumber = 1
  options.nParts = 1

################################################################
# possible sampleTags:                                         #
# WW_A0W5e-7, WW_A0W1e-6, WW_A0W2e-6, WW_A0W3_5E-6, WW_A0W5e-6 #
# WW_ACW5e-6, WW_ACW5e-6, WW_ACW8e-6, WW_ACW1_4E-5, WW_ACW2e-5 #
# ZZ_A0Z5e-6, ZZ_A0Z1e-5, ZZ_A0Z2e-5, ZZ_A0Z5e-5               #
# ZZ_ACZ5e-6, ZZ_ACZ1e-5, ZZ_ACZ2e-5, ZZ_ACZ5e-5               #
################################################################

MC=True
YEAR=options.year
ERA=options.era
MINIAOD=False
SAMPLETAG=options.sampleTag
OUTPUTDIR=options.outputDir
PARTNUMBER=options.partNumber
NPARTS=options.nParts
DoTheorySystematics=True
UseMCProtons=True

process = cms.Process('GenCuts')

print "\nRunning with year = "+str(YEAR)+" era = "+ERA+" sampleTag = "+SAMPLETAG+"\n"

from signalSamples_v2_cfi import *
print "Signal sample file list: "
print "\n".join(signalSamples(YEAR,ERA,SAMPLETAG,PARTNUMBER,NPARTS))
print "\n"
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(*signalSamples(YEAR,ERA,SAMPLETAG,PARTNUMBER,NPARTS))
)

# number of events
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport = cms.untracked.PSet(
  optionalPSet = cms.untracked.bool(True),
  reportEvery = cms.untracked.int32(100),
  limit = cms.untracked.int32(2000)
)
process.MessageLogger.categories.append('PPS')
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')

process.MessageLogger.destinations.append('logFile')
process.MessageLogger.logFile = cms.untracked.PSet(
  output = cms.untracked.string(OUTPUTDIR+"/ExclWWjets_"+SAMPLETAG+"_Part"+str(PARTNUMBER)+"of"+str(NPARTS)+".out"),
  optionalPSet = cms.untracked.bool(True),
    INFO = cms.untracked.PSet(
      limit = cms.untracked.int32(0)
     ),
  noTimeStamps = cms.untracked.bool(False),
  FwkReport = cms.untracked.PSet(
    optionalPSet = cms.untracked.bool(True),
    reportEvery = cms.untracked.int32(1000),
    limit = cms.untracked.int32(10000000)
    ),
  default = cms.untracked.PSet(
    limit = cms.untracked.int32(10000000)
    ),
  Root_NoDictionary = cms.untracked.PSet(
    optionalPSet = cms.untracked.bool(True),
    limit = cms.untracked.int32(0)
    ),
  FwkSummary = cms.untracked.PSet(
    optionalPSet = cms.untracked.bool(True),
    reportEvery = cms.untracked.int32(1),
    limit = cms.untracked.int32(10000000)
    ),
  threshold = cms.untracked.string('INFO')
)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.demo = cms.EDAnalyzer('PPtoPPWWjets')


process.maxEvents = cms.untracked.PSet(
  # input = cms.untracked.int32(20)
  input = cms.untracked.int32(-1)
)

process.load("PPtoPPWWjets.PPtoPPWWjets.genCutsFilter_cfi")
process.genCutsFilter.gen_mvv_min = 1000
process.genCutsFilter.gen_mvv_max = 1400
# processing path
process.p = cms.Path(
  process.genCutsFilter
)
