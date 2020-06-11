import FWCore.ParameterSet.Config as cms
import re

MC=False
YEAR=2017
ERA="C"
MINIAOD=False
DoTheorySystematics=False
UseMCProtons=False

from Configuration.StandardSequences.Eras import eras
if YEAR == 2016:
    process = cms.Process('Demo', eras.Run2_2016, eras.run2_miniAOD_devel)
if YEAR == 2017:
    process = cms.Process('Demo', eras.Run2_2017, eras.run2_miniAOD_devel)
if YEAR == 2018:
    process = cms.Process('Demo', eras.Run2_2018, eras.run2_miniAOD_devel)


#process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
# Test file - 2017C 94X AOD
'/store/data/Run2017C/JetHT/AOD/17Nov2017-v1/30004/9A36D46F-01D8-E711-93DA-A4BF0112BE4C.root'
    )
                            #,
                            #duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

process.load("PPtoPPWWjets.PPtoPPWWjets.CfiFile_cfi")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
from CondCore.CondDB.CondDB_cfi import *

# Select data or MC - this controls which jet mass corrections are used and whether PU reweighting + GEN info is filled                                          
# It also controls which global tag is used, which determines the standard set of jet corrections. 

                                   
         
if MC:
    DOSMEARING=True
    if YEAR==2016:
        process.GlobalTag.globaltag = '94X_mcRun2_asymptotic_v3'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2016_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR==2017:
        process.GlobalTag.globaltag ='94X_mc2017_realistic_v17'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
else:
    DOSMEARING=False
    if YEAR == 2016:
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2016_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR == 2017:
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR == 2018:
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2018_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR == 2016 or YEAR == 2017 or YEAR == 2018:
        # For legacy re-reco, for now using standard GT for 2016 or 2017                                                                                     
        #        process.GlobalTag = GlobalTag(process.GlobalTag, "106X_dataRun2_v15")
        process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v26')

        # Begin overrides for 2020 re-MiniAOD conditions                                                                                                          
        # Alignment                                                                                                                                              
        process.CondDBAlignment = CondDB.clone( connect = "frontier://FrontierProd/CMS_CONDITIONS" )
        process.PoolDBESSourceAlignment = cms.ESSource("PoolDBESSource",
                                                       process.CondDBAlignment,
                                                       toGet = cms.VPSet(cms.PSet(
                                                           record = cms.string('RPRealAlignmentRecord'),
                                                           tag = cms.string("CTPPSRPAlignment_real_offline_v8")
                                                       ))
                                                   )

        process.esPreferDBFileAlignment = cms.ESPrefer("PoolDBESSource", "PoolDBESSourceAlignment")
        
        # Optics                                                                                                                                                 
        process.CondDBOptics = CondDB.clone( connect = "frontier://FrontierProd/CMS_CONDITIONS" )
        process.PoolDBESSourceOptics = cms.ESSource("PoolDBESSource",
                                                    process.CondDBOptics,
                                                    DumpStat = cms.untracked.bool(False),
                                                    toGet = cms.VPSet(cms.PSet(
                                                        record = cms.string('CTPPSOpticsRcd'),
                                                        tag = cms.string("PPSOpticalFunctions_offline_v7")
                                                    )),
                                                )
        
        process.esPreferDBFileOptics = cms.ESPrefer("PoolDBESSource", "PoolDBESSourceOptics")
        # End of overrides for testing 2020 re-MiniAOD conditions                                                                                                 

### ADD SOME NEW JET COLLECTIONS                                                                                                              
# New (March 8, 2019) - to recover ak8 CHS jets with 2017 MiniAOD
#################################
  ###  JET TOOLBOX FOR CHS ###
#################################
# AK R=0.8 jets from CHS inputs with basic grooming, W tagging, and top tagging                                                            
from JMEAnalysis.JetToolbox.jetToolbox_cff import *

jetToolbox( process, 'ak8', 'ak8JetSubs', 'noOutput',
            PUMethod='CHS',
            addPruning=True, addSoftDrop=False ,           # add basic grooming                                                            
            addTrimming=False, addFiltering=False,
            addPrunedSubjets=True, addSoftDropSubjets=False,
            addNsub=True, maxTau=4,                       # add Nsubjettiness tau1, tau2, tau3, tau4                                      
            #miniAOD = MINIAOD, 
            dataTier = 'AOD',
            runOnMC=MC, 
            bTagDiscriminators = None,  # blank means default list of discriminators, None means none
            bTagInfos = None,
            subjetBTagDiscriminators = None,
            subjetBTagInfos = None,
            # added L1FastJet on top of the example config file
            JETCorrPayload = 'AK8PFchs', JETCorrLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']
)

#################################
    ###  RECORRECTING JETS ###
#################################
     # New from Ksenia+Finn - update jet corrections
#from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
#updateJetCollection(
#                   process,
#                   jetSource = cms.InputTag('slimmedJetsAK8'),
#                   labelName = 'UpdatedJECAK8',
#                   jetCorrections = ('AK8PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'NONE')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
#                    )
################################
# DEFINE COLLECTION TO BE PASSED FURTHER
###############################
#if YEAR == 2017:
#COLLECTIONTOSMEAR="packedPatJetsAK8PFCHSPrunedSubjets" ## toolbox output

#if YEAR == 2016:
#     COLLECTIONTOSMEAR="updatedPatJetsUpdatedJECAK8" ## recorrected miniAOD collection

#################################
     ###  JER SMEARING ###
#################################
from RecoMET.METProducers.METSigParams_cfi import *
process.slimmedAK8JetsSmeared = cms.EDProducer('SmearedPATJetProducer',
        src = cms.InputTag("slimmedJetsAK8JetId"),
        enabled = cms.bool(DOSMEARING),
        rho = cms.InputTag("fixedGridRhoFastjetAll"),
        algo = cms.string('AK8PFchs'),
        algopt = cms.string('AK8PFchs_pt'),

        genJets = cms.InputTag('slimmedGenJetsAK8'),
        dRMax = cms.double(0.4),
        dPtMaxFactor = cms.double(3),
        seed = cms.uint32(37428479),
        debug = cms.untracked.bool(False),
    # Systematic variation
    # 0: Nominal
    # -1: -1 sigma (down variation)
    # 1: +1 sigma (up variation)
    variation = cms.int32(0)  # If not specified, default to 0
        )


#################################
        ###  JET ID  ###
#################################
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.slimmedJetsAK8JetId = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                                           filterParams = pfJetIDSelector.clone(),
                                           #src = cms.InputTag("slimmedJetsAK8"),
                                           src = cms.InputTag("packedPatJetsAK8PFCHSPrunedSubjets"),
                                           filter = cms.bool(True)
                                           )
                                           
#################################

# If using full proton re-reco (legacy) - local RP reconstruction chain with standard settings                                                             
process.load("RecoCTPPS.Configuration.recoCTPPS_cff")
process.ctppsLocalTrackLiteProducer.includePixels = cms.bool(True)
process.ctppsLocalTrackLiteProducer.includeStrips = cms.bool(True)
process.ctppsLocalTrackLiteProducer.includeDiamonds = cms.bool(True)
process.ctppsProtons.doSingleRPReconstruction = cms.bool(True)
process.ctppsProtons.doMultiRPReconstruction = cms.bool(True)

# If running on AOD, remake goodOfflinePrimaryVertices for jet stuff
#process.load('CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi')

process.demo = cms.EDAnalyzer('PPtoPPWWjets')

if MC:
    process.demo.isMC = cms.bool(True)
    process.demo.doMCTheorySystematics = cms.bool(False)
    process.demo.useMCProtons = cms.bool(False)

    if DoTheorySystematics:
        process.demo.doMCTheorySystematics = cms.bool(True)

    if UseMCProtons:
        process.demo.useMCProtons = cms.bool(True)

    if YEAR == 2016:
        process.demo.dataPileupFile = cms.string("PUHistos_data_2016.root")
        process.demo.mcPileupFile = cms.string("PUHistos_mc_2016.root")
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")

        process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "Demo")
        process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "Demo")

    if YEAR == 2017:
        process.demo.dataPileupFile = cms.string("PUHistos_data_2017.root")
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedAK8JetsSmeared")
        
        # Standard 2017 central production input distribution                                                                                        
        process.demo.mcPileupFile = cms.string("PUHistos_mc_2017.root")                                                                              

        # Special cases for buggy datasets in 2017 MC                                                                                                
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt300to470.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt600to800.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt1000to1400.root")                                                         
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Wjets.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Zjets.root")     

        process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "Demo")
        process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "Demo")

else:
    process.demo.isMC = cms.bool(False)
    process.demo.useMCProtons = cms.bool(False)
    process.demo.doMCTheorySystematics = cms.bool(False)

    if YEAR == 2016:
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")
        process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "Demo")
        process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "Demo")
    if YEAR == 2017:
#        process.demo.jetAK8CHSCollection = cms.InputTag("selectedPatJetsAK8PFCHS")
#        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedAK8JetsSmearedJetID")
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")
        process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "Demo")
        process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "Demo")
    if YEAR == 2018:
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")
        process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "Demo")
        process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "Demo")


process.demo.year = cms.int32(YEAR)
process.demo.era = cms.string(ERA)



process.p = cms.Path(process.hltFilter *           
                    # process.patJetCorrFactorsUpdatedJECAK8 *
                    # process.updatedPatJetsUpdatedJECAK8 * 
#                     process.goodOfflinePrimaryVertices * 
                     process.slimmedJetsAK8JetId *
                     # Legacy re-reco from AOD sequence
                     process.totemRPUVPatternFinder *
                     process.totemRPLocalTrackFitter *
                     process.ctppsDiamondRecHits *
                     process.ctppsDiamondLocalTracks *
                     process.ctppsPixelLocalTracks *
                     process.ctppsLocalTrackLiteProducer *
                     process.ctppsProtons *
                     # Analyzer
                     process.demo)

print process.dumpPython()

