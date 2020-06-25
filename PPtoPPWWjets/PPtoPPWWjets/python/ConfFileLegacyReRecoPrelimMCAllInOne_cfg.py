import FWCore.ParameterSet.Config as cms

MC=True
YEAR=2017
ERA="B"
MINIAOD=False
DoTheorySystematics=True
UseMCProtons=True

# load common code
if MC == True and YEAR == 2016 and (ERA == "B" or ERA == "C" or ERA == "G"):
   from direct_simu_reco_2016preTS2_cff import *
if MC == True and YEAR == 2016 and (ERA == "H"):
   from direct_simu_reco_2016postTS2_cff import *
if MC == True and YEAR == 2017 and (ERA == "B" or ERA == "C" or ERA == "D"):
   from direct_simu_reco_2017preTS2_cff import *
if MC == True and YEAR == 2017 and (ERA == "E" or ERA == "F"):
   from direct_simu_reco_2017postTS2_cff import *
if MC == True and YEAR == 2018:
   from direct_simu_reco_2018_cff import *

process = cms.Process('CTPPSTestAcceptance', era)
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag

##KS added GT splitting by year
if MC == True and YEAR == 2016:
   # JH - change this for AOD instead of MiniAOD, according to PDMV twiki                                                                                                         
   process.GlobalTag.globaltag ='80X_mcRun2_asymptotic_2016_TrancheIV_v8'
   #   process.GlobalTag.globaltag ='94X_mcRun2_asymptotic_v3,' # This one is for Summer16 MC campaign
if MC == True and YEAR == 2017:
   process.GlobalTag.globaltag ='94X_mc2017_realistic_v17' # this one for 94X MC
if MC == True and YEAR == 2018:
   process.GlobalTag.globaltag ='102X_upgrade2018_realistic_v20' # this one is for Autumn18 MC campaign


if MC == True and YEAR == 2016 and (ERA == "B" or ERA == "C" or ERA == "G"):
    process.load("direct_simu_reco_2016preTS2_cff")
if MC == True and YEAR == 2016 and (ERA == "H"):
    process.load("direct_simu_reco_2016postTS2_cff")
if MC == True and YEAR == 2017 and (ERA == "B" or ERA == "C" or ERA == "D"):
    process.load("direct_simu_reco_2017preTS2_cff")
if MC == True and YEAR == 2017 and (ERA == "E" or ERA == "F"):
    process.load("direct_simu_reco_2017postTS2_cff")
if MC == True and YEAR == 2018:
    process.load("direct_simu_reco_2018_cff")

SetDefaults(process)

# minimal logger settings
process.MessageLogger = cms.Service("MessageLogger",
  statistics = cms.untracked.vstring(),
  destinations = cms.untracked.vstring('cerr'),
  cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('WARNING')
  )
)

# number of events
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/group/phys_pps/MC/requests_2017mcv2/private/AAZZ_bSM//AODSIM/GGToZZ_bSM_A0Z_0E0_ACZ_5E-5_13TeV-fpmc_AODSIM.root'
    )
)

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
            addPrunedSubjets=False, addSoftDropSubjets=False,
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
###  PT CUT 
#################################
process.goodJets = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("selectedPatJetsAK8PFCHS"),
    cut = cms.string("pt > 30.0"),
    filter = cms.bool(True)
  )


#################################                                                                                                                                                   
###  JER SMEARING ###                                                                                                                                                          
#################################                                                                                                                                                    
 
from RecoMET.METProducers.METSigParams_cfi import *
process.slimmedAK8JetsSmeared = cms.EDProducer('SmearedPATJetProducer',
        src = cms.InputTag("slimmedJetsAK8JetId"),
                                               enabled = cms.bool(True),
        rho = cms.InputTag("fixedGridRhoFastjetAll"),
        algo = cms.string('AK8PFchs'),
        algopt = cms.string('AK8PFchs_pt'),
        genJets = cms.InputTag('ak8GenJets'),
                                               #        genJets = cms.InputTag('slimmedGenJetsAK8'),                                                                                
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
                                           src = cms.InputTag("selectedPatJetsAK8PFCHS"),
                                           filter = cms.bool(True)
                                           )


#########################                                                                                                                                                  
# override LHCInfo source
# for direct sim                                                                                                                                                           
#########################                   
process.load("CalibPPS.ESProducers.ctppsLHCInfoRandomXangleESSource_cfi")
process.ctppsLHCInfoRandomXangleESSource.generateEveryNEvents = 1
if MC == True and YEAR == 2016:
    process.ctppsLHCInfoRandomXangleESSource.xangleHistogramFile = "CrossingAngles2016.root"
if MC == True and YEAR == 2017:
    process.ctppsLHCInfoRandomXangleESSource.xangleHistogramFile = "CrossingAngles2017.root"
if MC == True and YEAR == 2018:
    process.ctppsLHCInfoRandomXangleESSource.xangleHistogramFile = "CrossingAngles2018.root"

process.ctppsLHCInfoRandomXangleESSource.xangleHistogramObject = "hxang"
process.ctppsLHCInfoRandomXangleESSource.beamEnergy = 6500.
process.ctppsLHCInfoRandomXangleESSource.betaStar = 0.40

process.esPreferLHCInfo = cms.ESPrefer("CTPPSLHCInfoRandomXangleESSource", "ctppsLHCInfoRandomXangleESSource")

# override beam-parameter source                                                                                                                                                                       
process.load("CalibPPS.ESProducers.ctppsBeamParametersFromLHCInfoESSource_cfi")

process.ctppsBeamParametersFromLHCInfoESSource.beamDivX45 = process.ctppsBeamParametersESSource.beamDivX45
process.ctppsBeamParametersFromLHCInfoESSource.beamDivX56 = process.ctppsBeamParametersESSource.beamDivX56
process.ctppsBeamParametersFromLHCInfoESSource.beamDivY45 = process.ctppsBeamParametersESSource.beamDivY45
process.ctppsBeamParametersFromLHCInfoESSource.beamDivY56 = process.ctppsBeamParametersESSource.beamDivY56

process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetX45 = process.ctppsBeamParametersESSource.vtxOffsetX45
process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetX56 = process.ctppsBeamParametersESSource.vtxOffsetX56
process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetY45 = process.ctppsBeamParametersESSource.vtxOffsetY45
process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetY56 = process.ctppsBeamParametersESSource.vtxOffsetY56
process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetZ45 = process.ctppsBeamParametersESSource.vtxOffsetZ45
process.ctppsBeamParametersFromLHCInfoESSource.vtxOffsetZ56 = process.ctppsBeamParametersESSource.vtxOffsetZ56

process.ctppsBeamParametersFromLHCInfoESSource.vtxStddevX = process.ctppsBeamParametersESSource.vtxStddevX
process.ctppsBeamParametersFromLHCInfoESSource.vtxStddevY = process.ctppsBeamParametersESSource.vtxStddevY
process.ctppsBeamParametersFromLHCInfoESSource.vtxStddevZ = process.ctppsBeamParametersESSource.vtxStddevZ

# do not apply vertex smearing again                                                                                                                                                                 
process.ctppsBeamParametersESSource.vtxStddevX = 0
process.ctppsBeamParametersESSource.vtxStddevY = 0
process.ctppsBeamParametersESSource.vtxStddevZ = 0

# undo CMS vertex shift                                                                                                                                                             
process.ctppsBeamParametersESSource.vtxOffsetX45 = +0.2475 * 1E-1
process.ctppsBeamParametersESSource.vtxOffsetY45 = -0.6924 * 1E-1
process.ctppsBeamParametersESSource.vtxOffsetZ45 = -8.1100 * 1E-1

process.beamDivergenceVtxGenerator.src = cms.InputTag("")
process.beamDivergenceVtxGenerator.srcGenParticle = cms.VInputTag(
    # Don't propagate PU protons
#    cms.InputTag("genPUProtons","genPUProtons"),
    cms.InputTag("genParticles")
)


#########################                                                                                                                                                           
# Configure Analyzer
#########################                                                                                                                                                           
process.load("PPtoPPWWjets.PPtoPPWWjets.CfiFile_cfi")

process.demo = cms.EDAnalyzer('PPtoPPWWjets')

if YEAR == 2016:
    process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2016_cfi")
    process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
if YEAR==2017:
    process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter_cfi")
    process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
if YEAR==2018:
    process.load("PPtoPPWWjets.PPtoPPWWjets.HLTFilter2018_cfi")
    process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")


if MC == True and YEAR == 2016:
    process.demo.dataPileupFile = cms.string("PUHistos_data_2016.root")
    process.demo.mcPileupFile = cms.string("PUHistos_mc_2016.root")
if MC == True and YEAR == 2017:
    process.demo.dataPileupFile = cms.string("PUHistos_data_2017.root")
    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017.root")
    # Special cases for buggy datasets in 2017 MC                                                                                                
   #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt300to470.root")
   #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt600to800.root")
   #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_QCDPt1000to1400.root")                                                         
   #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Wjets.root")
   #    process.demo.mcPileupFile = cms.string("PUHistos_mc_2017_Zjets.root")     
if MC == True and YEAR == 2018:
    process.demo.dataPileupFile = cms.string("PUHistos_data_2018.root")
    process.demo.mcPileupFile = cms.string("PUHistos_mc_2018.root")


process.demo.jetAK8CHSCollection = cms.InputTag("slimmedJetsAK8JetId")
process.demo.ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP")
process.demo.ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP")
process.demo.isMC = cms.bool(MC)
process.demo.doMCTheorySystematics = cms.bool(DoTheorySystematics)
process.demo.useMCProtons = cms.bool(UseMCProtons)
process.demo.year = cms.int32(YEAR)
process.demo.era = cms.string(ERA)



# processing path
process.p = cms.Path(
    process.hltFilter
    * process.beamDivergenceVtxGenerator
    * process.ctppsDirectProtonSimulation
    * process.reco_local
    * process.ctppsProtons
    * process.genParticlesForJetsNoNu 
    * process.goodOfflinePrimaryVertices  
    * process.slimmedJetsAK8JetId 
    * process.demo
)
