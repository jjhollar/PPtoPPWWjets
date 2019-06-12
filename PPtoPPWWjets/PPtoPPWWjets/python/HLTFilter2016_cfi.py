import FWCore.ParameterSet.Config as cms
import copy

# Trigger                                                                                                                                                                     
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
hltFilter = copy.deepcopy(hltHighLevel)
hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltFilter.HLTPaths = ['HLT PFHT800_v*',
                      'HLT PFHT900_v*',
                      'HLT PFJet450_v*',
                      'HLT PFJet500_v*',
                      'HLT_AK8PFJet450_v*',
                      'HLT_AK8PFJet500_v*',
                      'HLT AK8PFJet360 TrimMass30_v*',
                      'HLT AK8PFHT700 TrimR0p1PT0p03Mass50_v*',
                      'HLT PFHT650 WideJetMJJ900DEtaJJ1p5_v*',
                      'HLT PFHT650 WideJetMJJ950DEtaJJ1p5_v*']

hltFilter.throw = cms.bool(False)
