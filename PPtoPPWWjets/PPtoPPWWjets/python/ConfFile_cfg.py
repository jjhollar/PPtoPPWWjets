import FWCore.ParameterSet.Config as cms
import re


process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#'/store/user/jjhollar/ExclWWHadronic2018/step3miniaod_gammagammaww_all_xi1pt5to25percent_a0W2pt5e-6_digi_withprotonsfix_20kevents_19jobs_job3.root'
#'file:/tmp/jjhollar/50D30A02-FB08-E811-8D0B-44A842CFD5D8.root'

'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_1.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_2.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_3.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_4.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_5.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_6.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_7.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_8.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_9.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/fpmc_exclww/step3_fpmc_exclww_a0W2point5e-6_alldecays_xi1to30pct_miniaodv2_10.root'

#'file:/tmp/jjhollar/7402ADA9-C609-E811-BCFE-C0BFC0E5686E.root'


#        '/store/user/kshcheli/wwhad/FPMC_Fall17/step3_fpmc_MiniAOD.root'
#'/store/data/Run2016B/JetHT/MINIAOD/07Aug17_ver2-v1/110000/5EF65117-437F-E711-AF5B-0025905A60A8.root'
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/step3_fpmc_ZZ_MINIAODv2.root'
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_1.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_2.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_3.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_4.root',
##'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_5.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_6.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_7.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_8.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_9.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_10.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_11.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_12.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_13.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_14.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_15.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_16.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_17.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_18.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_19.root',
#'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_20.root'
#'file:/tmp/jjhollar/365A165C-0C39-E811-9EFB-984BE164D05E.root'
#'/store/data/Run2017B/JetHT/MINIAOD/31Mar2018-v1/00000/80A71620-AF3A-E811-96AA-0CC47A7452D8.root'
#'/store/mc/RunIISummer16MiniAODv2/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/8274BB36-3DB5-E611-816C-0025907DE266.root'
#'file:/tmp/jjhollar/927116EE-760F-E811-A4BB-484D7E8DF06B.root'

    )
,
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

process.load("PPtoPPWWjets.PPtoPPWWjets.CfiFile_cfi")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag

# Select data or MC - this controls which jet mass corrections are used and whether PU reweighting + GEN info is filled                                                                             
# Currently the only year+era options are 2017 for MC, and 2017BCDEF for data. It also controls which global tag                                                                                    
# is used, which determines the standard set of jet corrections. Currently the options are 94X_mc2017_realistic_v8                                                                                  
# and 94X_dataRun2_v6.                                                                                                                                                                              
         
MC=True
YEAR=2017
ERA="F"

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
        process.GlobalTag.globaltag = '94X_dataRun2_v10'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2016_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR == 2017:
        process.GlobalTag.globaltag ='94X_dataRun2_v11'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")


# JH - modified Dec 10, 2018
# JEC, if using from sqlite file instead of global tag. 
############################### JEC #####################
#### Load from a sqlite db, if not read from the global tag
#process.load("CondCore.DBCommon.CondDBCommon_cfi")
#from CondCore.DBCommon.CondDBSetup_cfi import *
#
#if MC == True:
#    connectString = cms.string('sqlite:JEC2017/Fall17_17Nov2017_V32_94X_MC.db')
#    #JetCorrectorParametersCollection_Fall17_17Nov2017_V32_94X_MC_AK4PFPuppi                                                                               
#    tagName = 'Fall17_17Nov2017_V32_94X_MC_AK4PFchs'
#    tagNamePuppi = 'Fall17_17Nov2017_V32_94X_MC_AK4PFPuppi'
#else:
#    connectString = cms.string('sqlite:JEC2017/Fall17_17Nov2017_V32_94X_DATA.db')
#    # B C DE F
#    tagName = 'Fall17_17Nov2017_V32_94X_DATA_AK4PFchs'
#    tagNamePuppi = 'Fall17_17Nov2017_V32_94X_DATA_AK4PFPuppi'
#
#data only, mc hard coded. Need to be fixed per Run
#
#
#process.jec = cms.ESSource("PoolDBESSource",
#      DBParameters = cms.PSet(
#        messageLevel = cms.untracked.int32(0)
#        ),
#      timetype = cms.string('runnumber'),
#      toGet = cms.VPSet(
#      cms.PSet(
#            record = cms.string('JetCorrectionsRecord'),
#            tag    = cms.string('JetCorrectorParametersCollection_%s'%tagName),
#            label  = cms.untracked.string('AK4PFchs')
#            ),
#      cms.PSet( ## AK8
#            record = cms.string('JetCorrectionsRecord'),
#            tag    = cms.string('JetCorrectorParametersCollection_%s'%re.sub('AK4','AK8',tagName)),
#            label  = cms.untracked.string('AK8PFchs')
#            ),
#      cms.PSet(#puppi
#            record = cms.string('JetCorrectionsRecord'),
#            tag    = cms.string('JetCorrectorParametersCollection_%s'%tagNamePuppi),
#            label  = cms.untracked.string('AK4PFPuppi')
#            ),
#      cms.PSet( ## AK8 puppi
#            record = cms.string('JetCorrectionsRecord'),
#            tag    = cms.string('JetCorrectorParametersCollection_%s'%re.sub('AK4','AK8',tagNamePuppi)),
#            label  = cms.untracked.string('AK8PFPuppi')
#            ),
#      ## here you add as many jet types as you need
#      ## note that the tag name is specific for the particular sqlite file 
#      ), 
#      connect = connectString
#     # uncomment above tag lines and this comment to use MC JEC
#)
### add an es_prefer statement to resolve a possible conflict from simultaneous connection to a global tag
#process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')
# end JH - JEC, if using from sqlite file instead of global tag.                                                                              

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


# If using full proton reco (2016 style)
#process.load("RecoCTPPS.ProtonReconstruction.year_2016.ctppsProtonReconstruction_cfi")

# If using full proton reco (2017 style) 
process.load("RecoCTPPS.ProtonReconstruction.year_2017_OF.ctppsProtonReconstructionOF_cfi")
#from RecoCTPPS.ProtonReconstruction.year_2017_OF.ctppsProtonReconstructionOF_cfi import *
#process.ctppsProtonReconstructionOF = ctppsProtonReconstructionOF
#process.ctppsProtonReconstructionOF.alignmentFiles = cms.vstring("RecoCTPPS/ProtonReconstruction/data/alignment/2017_preTS2/collect_alignments_$alignment.out")

process.demo = cms.EDAnalyzer('PPtoPPWWjets')

if MC:
    process.demo.isMC = cms.bool(True)

    if YEAR == 2016:
        process.demo.dataPileupFile = cms.string("PUHistos_data_2016.root")
        process.demo.mcPileupFile = cms.string("PUHistos_mc_2016.root")
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")

        process.demo.recoProtonsCollection = cms.InputTag("ctppsProtonReconstruction")

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

        process.demo.recoProtonsCollection = cms.InputTag("ctppsProtonReconstructionOFDB")

else:
    process.demo.isMC = cms.bool(False)
    if YEAR == 2016:
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")
        process.demo.recoProtonsCollection = cms.InputTag("ctppsProtonReconstruction")
    if YEAR == 2017:
#        process.demo.jetAK8CHSCollection = cms.InputTag("selectedPatJetsAK8PFCHS")
#        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedAK8JetsSmearedJetID")
        process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")

        process.demo.recoProtonsCollection = cms.InputTag("ctppsProtonReconstructionOFDB")

process.demo.year = cms.int32(YEAR)
process.demo.era = cms.string(ERA)



process.p = cms.Path(process.hltFilter *           
                    # process.patJetCorrFactorsUpdatedJECAK8 *
                    # process.updatedPatJetsUpdatedJECAK8 * 
                     process.slimmedJetsAK8JetId *
                     process.slimmedAK8JetsSmeared *
                  #process.ctppsProtonReconstruction *
                  #  process.ctppsProtonReconstructionOF * 
                 #     process.ctppsProtonReconstructionOFDB *
                     process.demo)

print process.dumpPython()

