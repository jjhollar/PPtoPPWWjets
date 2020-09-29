import FWCore.ParameterSet.Config as cms

MC=True
YEAR=2016
ERA="B"
MINIAOD=False
DoTheorySystematics=True
UseMCProtons=True


# load common code
if MC == True and YEAR == 2016 and (ERA == "B" or ERA == "C" or ERA == "G"):
   from Validation.CTPPS.simu_config.year_2016_preTS2_cff import *
if MC == True and YEAR == 2016 and (ERA == "H"):
   from Validation.CTPPS.simu_config.year_2016_postTS2_cff import *
if MC == True and YEAR == 2017 and (ERA == "B" or ERA == "C" or ERA == "D"):
   from Validation.CTPPS.simu_config.year_2017_preTS2_cff import *
if MC == True and YEAR == 2017 and (ERA == "E" or ERA == "F"):
   from Validation.CTPPS.simu_config.year_2017_postTS2_cff import *
if MC == True and YEAR == 2018:
   from Validation.CTPPS.simu_config.year_2018_cff import *

from Configuration.ProcessModifiers.run2_miniAOD_UL_cff import run2_miniAOD_UL
process = cms.Process('CTPPSTestAcceptance', era,run2_miniAOD_UL)

if MC == True and YEAR == 2016 and (ERA == "B" or ERA == "C" or ERA == "G"):
   process.load("Validation.CTPPS.simu_config.year_2016_preTS2_cff")
if MC == True and YEAR == 2016 and (ERA == "H"):
   process.load("Validation.CTPPS.simu_config.year_2016_postTS2_cff")
if MC == True and YEAR == 2017 and (ERA == "B" or ERA == "C" or ERA == "D"):
   process.load("Validation.CTPPS.simu_config.year_2017_preTS2_cff")
if MC == True and YEAR == 2017 and (ERA == "E" or ERA == "F"):
   process.load("Validation.CTPPS.simu_config.year_2017_postTS2_cff")
if MC == True and YEAR == 2018:
   process.load("Validation.CTPPS.simu_config.year_2018_cff")

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


SetDefaults(process)

# add pre-mixing of recHits


process.load("protonPreMix.protonPreMix.CTPPSPreMixProducer_cfi")
process.CTPPSPreMixProducer.PUFilesList = cms.vstring()

# rng service for premixing
process.RandomNumberGeneratorService.CTPPSPreMixProducer = cms.PSet(initialSeed = cms.untracked.uint32(42))

process.CTPPSPreMixProducer.Sim_CTPPSPixelRecHitTag = cms.InputTag("ctppsDirectProtonSimulation")
process.CTPPSPreMixProducer.Sim_TotemRPRecHitTag = cms.InputTag("ctppsDirectProtonSimulation")

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
       ########
       # a0W=1
       ########
       # 2017 preTS2 conditions (13900+13900+13900+4700+8900 events)                                                                                                                         
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/FAB1B549-E128-E911-A65A-00266CF3E3C4.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/9C913C20-C128-E911-AA20-0CC47A7FC74A.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/DCA44DDD-0829-E911-B529-3417EBE7002A.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/D885C77E-9729-E911-86ED-002590DD7E50.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/98CCB2F2-F429-E911-8537-002590DD7C9E.root'
       # 2017 postTS2 conditions (4900+3900+13900+13900+12000 events)
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/8A6E7948-3F2A-E911-AA0A-003048C446B8.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/FCCD54D5-6E2A-E911-8E9E-40F2E9C6ADD2.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/605F2A99-8129-E911-A94B-A0369F7FC770.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/BA7C4BA6-8129-E911-8481-549F35AC7E3C.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/7C4BD408-002A-E911-B157-A0369F7FC770.root'
       # 2018 conditions (8900+13900+8900+3900+13900+1000+6900+13900+7800+13900
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/7ED25E4C-F429-E911-8911-44A842CFD5D8.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/C08A9140-A629-E911-8422-00259073E51E.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/30487E78-F929-E911-9E65-44A84225D36F.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/6C82900E-D129-E911-959E-A4BF0112DCAC.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/B0095FE6-6B27-E911-A001-1866DA879B75.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/1C6A1B56-6D28-E911-A6CB-1866DA890B94.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/444F67F1-5F28-E911-9ABC-1866DA87A7E7.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/52577878-6128-E911-B2F5-0CC47A7EEF1A.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/CE197716-A928-E911-9D92-0CC47A7EEE96.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/40B84092-8028-E911-85F8-1866DA890574.root'
       # 2016 preTS2 conditions 13900+13900+13900+ 13900+13900
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/00ECF9DB-8928-E911-AB93-1866DA87C2CD.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/481190FB-8928-E911-A62E-D4AE526A0B29.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/D24455FB-8928-E911-BB89-D4AE526A0B29.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/F460A406-2829-E911-97D0-D4AE526A1654.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/7AE0D7DC-DC28-E911-91B4-1866DA890574.root'


       ########
       # a0W=2
       ########
#       # 2017 preTS2 conditions
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/90000/B2416746-4E2A-E911-9BD9-24BE05C3CBD1.root',
#      '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/90000/A0C43183-4E2A-E911-8E96-24BE05C63791.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/90000/A4781A5B-4E2A-E911-B0AA-EC0D9A8221E6.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/90000/2AEA1879-4E2A-E911-A9FB-44A8421293A8.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/90000/D80A77B1-4D2A-E911-9200-842B2B6F5ED7.root'
       # 2017 postTS2 conditions                                                                                                                                                             
   
       # 2018

       # 2016 preTS2 conditions

       ########
       # A0W=5E-6
       ########
       # 2017 preTS2 conditions (12800+13900+13900+13900+13700)
      # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/5E2364A2-8129-E911-8830-D8D385AF8B02.root',
      # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/82ECCABC-8129-E911-ABD9-D4AE526A0CFB.root',
      # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/94C668B7-CE2A-E911-A7AF-00259075D708.root',
      # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/EA3A3DC6-8129-E911-A5A8-44A842B4B3F1.root',
      # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/6A34DDBB-8129-E911-A290-405CFDE57581.root'
       # 2017 postTS2 conditions (13900+13900+13900+13900+13900)
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/607EBFC6-8129-E911-AB8C-10983627C3DB.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/AA2C55CA-8129-E911-97CA-000E1EB004E0.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/CCB642C7-8129-E911-B9B9-44A842B420F1.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/B42CE2BA-8129-E911-9E43-44A842B45218.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/682C0277-0D27-E911-9F43-0CC47A57D13E.root'
       # 2018 conditions (13900+7900+10900+7800+12800+13900+13900+13900+7800+12800)
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/80147D50-1827-E911-942D-0CC47A57CEB4.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/9EE63030-5327-E911-A4A8-002590D9D8B6.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/246EE615-2827-E911-A1EF-0CC47AD24CD8.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/D8071C21-5D27-E911-82CD-003048CB87DE.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/1C174898-3427-E911-83E3-0CC47AA53D6A.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/F4DBA7F9-3527-E911-9737-0CC47A57CC42.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/12A16111-3627-E911-BAD0-002590FD5694.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/0A86282D-3F27-E911-97FD-AC1F6BB17570.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/1E22FD16-7627-E911-9D87-AC1F6BB177EE.root',
#       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/AE4751BD-3E27-E911-AE1C-0CC47A0AD780.root'
       # 2016preTS2 conditions (13900+13900+13900+7900+8100)
       # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/C091C041-3F27-E911-B9DF-0CC47A57D164.root',
       # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/06267A65-2827-E911-84CD-00259029E714.root',
       # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/3E42A8A0-3827-E911-99CD-002590D9D980.root',
       # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/9A028E0C-9327-E911-B265-0CC47AA53D86.root',
       # '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/40000/DCDB5EBB-7A27-E911-9168-002590FD5694.root'



       ########                                                                                                                                                                     
       # aCW=2E-5                                                                                                                                                                   
       ########                                                                                                                                                                     

       # 2017 preTS2 conditions (13900+9700+13900+8900+7900)
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/066FBB76-FC2A-E911-B414-FA163EEBE295.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/F62CC6E2-132B-E911-858F-FA163E5609EE.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/F8DBDE12-012B-E911-BAF7-FA163EDADC7B.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/20B98A5F-3F2B-E911-BFA0-FA163EEBE295.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/F8A3AC71-252B-E911-BC46-0CC47A4C8F30.root'

       # 2017 postTS2 conditions 13900+13900+3900+11100+6100                                                                                                                        
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/42DE3465-252B-E911-8584-0CC47A7C3404.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/C6D334DF-402B-E911-90C6-0CC47A7C34D0.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/50000/2E85FA04-7D2B-E911-8080-0CC47A4D7646.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/A6F6C349-4827-E911-8F2D-FA163E614239.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/6219EB0E-6E27-E911-B416-FA163E1AAE3A.root'

       # 2018 (13900+7800+13900+13900+13900+13900+11700+13900+9500+10600) 
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/4A9F16E5-4927-E911-85F6-FA163E0959C0.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/96625B83-6B27-E911-B01D-FA163E6A8980.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/E442C22F-6127-E911-8004-FA163E63CDB5.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/820A78B8-6727-E911-BE24-FA163EBE4CE4.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/18DB385C-5627-E911-84CB-FA163E2BE632.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/F069DFEC-6227-E911-9ED2-FA163E5598C7.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/821B8C47-6327-E911-B061-FA163E14F11E.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/A4DC0FED-6A27-E911-86E2-FA163E8FF902.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/4C663FD1-8427-E911-B4AC-02163E019EEC.root',
       #       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/DEBEFE79-6927-E911-B475-FA163EE69449.root'

       # 2016 preTS2 conditions (13900+7800+13900+13900+13900 )
       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/3ED6A08F-6C27-E911-8D6A-FA163E1F999C.root',
       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/C0C4FB0E-7227-E911-A53E-FA163E1DC155.root',
       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/CC6F2015-6327-E911-8B30-FA163ED0D5AA.root',
       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/6A10005B-6327-E911-9AE0-FA163EE4A297.root',
       '/store/mc/RunIIFall17DRPremix/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/AODSIM/PU2017_94X_mc2017_realistic_v11-v2/80000/E464766B-6327-E911-8266-FA163E777760.root'


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

process.beamDivergenceVtxGenerator.src = cms.InputTag("")
process.beamDivergenceVtxGenerator.srcGenParticle = cms.VInputTag(
    # Don't propagate PU protons
    # cms.InputTag("genPUProtons","genPUProtons")
    cms.InputTag("genParticles")
)

# remove timing tracks from trackLites, they are not produced by protonPreMix
process.ctppsLocalTrackLiteProducer.includeDiamonds = False

# point the track producers to the correct products
process.ctppsPixelLocalTracks.label = "CTPPSPreMixProducer"
process.totemRPUVPatternFinder.tagRecHit = cms.InputTag("CTPPSPreMixProducer")

# reconstruction (if 2016 data, remove modules for RPs which did not exist at that time)
def RemoveModules(pr):
  pr.reco_local.remove(pr.ctppsPixelLocalTracks)
  pr.ctppsLocalTrackLiteProducer.includePixels = False
  pr.CTPPSPreMixProducer.includePixels = False

(ctpps_2016 & ~ctpps_2017 & ~ctpps_2018).toModify(process, RemoveModules)


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
    * process.CTPPSPreMixProducer
    * process.reco_local
    * process.ctppsProtons
    * process.genParticlesForJetsNoNu 
    * process.goodOfflinePrimaryVertices  
    * process.slimmedJetsAK8JetId 
    * process.demo
)
