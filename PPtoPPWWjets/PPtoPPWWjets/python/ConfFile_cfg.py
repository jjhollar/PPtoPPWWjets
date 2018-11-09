import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

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
'/store/user/kshcheli/ExclWWHadronic2017Analysis/MCv2/hepmcSM/step3_fpmc_SMWW_miniaodv2_20.root'

    )
,
duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

process.load("PPtoPPWWjets.PPtoPPWWjets.CfiFile_cfi")

process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag

# Select data or MC - this controls which jet mass corrections are used and whether PU reweighting + GEN info is filled                                                                             
# Currently the only year+era options are 2017 for MC, and 2017BCDEF for data. It also controls which global tag                                                                                    
# is used, which determines the standard set of jet corrections. Currently the options are 94X_mc2017_realistic_v8                                                                                  
# and 94X_dataRun2_v6.                                                                                                                                                                              
         
MC=True
YEAR=2017
ERA="G"

if MC:
    if YEAR==2016:
        process.GlobalTag.globaltag = '94X_mcRun2_asymptotic_v3'
    if YEAR==2017:
        process.GlobalTag.globaltag ='94X_mc2017_realistic_v14'
else:
    if YEAR == 2016:
        process.GlobalTag.globaltag = '94X_dataRun2_v10'
    if YEAR == 2017:
        process.GlobalTag.globaltag ='94X_dataRun2_v6'


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


process.demo = cms.EDAnalyzer('PPtoPPWWjets')

if MC:
    process.demo.isMC = cms.bool(True)
    process.demo.dataPileupFile = cms.string("PUHistos_data_2017.root")

    # Standard 2017 central production input distribution                                                                                                    
    #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017.root")                                                                                     

    # Special cases for buggy datasets in 2017 MC                                                                                                            
    #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt300to470.root")
    #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt600to800.root")
    #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt1000to1400.root")                                                                     
    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Wjets.root")
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
                     process.demo)

#print process.dumpPython()
