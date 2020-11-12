import FWCore.ParameterSet.Config as cms
import os

TFileService = cms.Service("TFileService", fileName = cms.string("ExclWWjets.root") )

print os.getcwd()

demo = cms.EDAnalyzer('PPtoPPWWjets'
)
