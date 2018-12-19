import FWCore.ParameterSet.Config as cms
import re


process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
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
'file:/tmp/jjhollar/365A165C-0C39-E811-9EFB-984BE164D05E.root'
#'/store/mc/RunIISummer16MiniAODv2/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/8274BB36-3DB5-E611-816C-0025907DE266.root'

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
         
MC=False
YEAR=2017
ERA="C"

if MC:
    if YEAR==2016:
        process.GlobalTag.globaltag = '94X_mcRun2_asymptotic_v3'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2016_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
    if YEAR==2017:
        process.GlobalTag.globaltag ='94X_mc2017_realistic_v14'
        process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
        process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
else:
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


# New from Ksenia+Finn - update jet corrections
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJetsAK8'),
   labelName = 'UpdatedJECAK8',
   jetCorrections = ('AK8PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'NONE')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
)

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJets'),
   labelName = 'UpdatedJEC',
   jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'NONE')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
)

from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.slimmedJetsAK8JetId = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                                           filterParams = pfJetIDSelector.clone(),
                                           #src = cms.InputTag("slimmedJetsAK8"),
                                           src = cms.InputTag("updatedPatJetsUpdatedJECAK8"),
                                           filter = cms.bool(True)
                                           )
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
process.slimmedJetsJetId = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                                           filterParams = pfJetIDSelector.clone(),
                                           #src = cms.InputTag("slimmedJets"),
                                           src = cms.InputTag("updatedPatJetsUpdatedJEC"), 
                                           filter = cms.bool(True)

                                           )


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

    if YEAR == 2017:
        process.demo.dataPileupFile = cms.string("PUHistos_data_2017.root")
        
        # Standard 2017 central production input distribution                                                                                                    
        process.demo.mcPileupFile = cms.string("PUHistos_mc_2017.root")                                                                                     

        # Special cases for buggy datasets in 2017 MC                                                                                                            
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt300to470.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt600to800.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt1000to1400.root")                                                                     
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Wjets.root")
        #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Zjets.root")     

else:
    process.demo.isMC = cms.bool(False)

process.demo.year = cms.int32(YEAR)
process.demo.era = cms.string(ERA)

process.p = cms.Path(process.hltFilter * 
                     process.patJetCorrFactorsUpdatedJEC * 
                     process.updatedPatJetsUpdatedJEC *
                     process.patJetCorrFactorsUpdatedJECAK8 *
                     process.updatedPatJetsUpdatedJECAK8 *
                     process.slimmedJetsAK8JetId *
                     process.slimmedJetsJetId *
#                     process.ctppsProtonReconstruction *
#                     process.ctppsProtonReconstructionOF * 
                     process.ctppsProtonReconstructionOFDB *
                     process.demo)

print process.dumpPython()
