import FWCore.ParameterSet.Config as cms
import copy

# Trigger                                                                                                                                                                     
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
hltFilter = copy.deepcopy(hltHighLevel)
hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltFilter.HLTPaths = ['HLT_PFHT800_v*',
                      'HLT_PFHT900_v*',
                      'HLT_PFJet450_v*',
                      'HLT_PFJet500_v*',
                      'HLT_AK8PFJet450_v*',
                      'HLT_AK8PFJet500_v*',
                      'HLT_AK8PFJet360_TrimMass30_v*',
                      'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v*',
                      'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v*',
                      'HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v*']

hltFilter.throw = cms.bool(False)
