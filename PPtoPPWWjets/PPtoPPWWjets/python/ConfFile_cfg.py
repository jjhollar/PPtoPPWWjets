import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/kshcheli/wwhad/FPMC_Fall17/step3_fpmc_MiniAOD.root'
    )
)

process.load("PPtoPPWWjets.PPtoPPWWjets.CfiFile_cfi")

process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag


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
# Select data or MC - this controls which jet mass corrections are used and whether PU reweighting + GEN info is filled                                                          
# Currently the only year+era options are 2017 for MC, and 2017BCDEF for data. It also controls which global tag 
# is used, which determines the standard set of jet corrections. Currently the options are 94X_mc2017_realistic_v8 
# and 94X_dataRun2_v6.                                                                                           
MC=True
if MC:
    process.GlobalTag.globaltag ='94X_mc2017_realistic_v8'
    process.demo.isMC = cms.bool(True)
else:
    process.GlobalTag.globaltag ='94X_dataRun2_v6'
    process.demo.isMC = cms.bool(False)

process.demo.year = cms.int32(2017)
process.demo.era = cms.string("D")

process.p = cms.Path(process.hltFilter * 
                     process.patJetCorrFactorsUpdatedJEC * 
                     process.updatedPatJetsUpdatedJEC *
                     process.patJetCorrFactorsUpdatedJECAK8 *
                     process.updatedPatJetsUpdatedJECAK8 *
                     process.slimmedJetsAK8JetId *
                     process.slimmedJetsJetId *
                     process.demo)
