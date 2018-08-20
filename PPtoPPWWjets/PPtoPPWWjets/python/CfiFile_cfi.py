import FWCore.ParameterSet.Config as cms
import os

TFileService = cms.Service("TFileService", fileName = cms.string("/tmp/jjhollar/ExclWWjets.root") )

print os.getcwd()

demo = cms.EDAnalyzer('PPtoPPWWjets'
)
