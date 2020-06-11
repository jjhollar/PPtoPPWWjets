import FWCore.ParameterSet.Config as cms
import copy

# Trigger                                                                                                                                                                     
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
hltFilter = copy.deepcopy(hltHighLevel)
hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
hltFilter.HLTPaths = ['HLT_PFHT1050_v*',
                      'HLT_AK8PFJet500_v*',
                      'HLT_AK8PFHT800_TrimMass50_v*',
                      'HLT_AK8PFJet400_TrimMass30_v*']

hltFilter.throw = cms.bool(False)
