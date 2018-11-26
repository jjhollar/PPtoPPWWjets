from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()


#config.General.requestName = 'WWhadronic_JetHT_2016Bver2v1_07Aug2017'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2016Bver2v1_07Aug2017'
#config.General.requestName = 'WWhadronic_JetHT_2016Gv1_07Aug2017'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2016Gv1_07Aug2017'

config.General.requestName = 'WWhadronic_Summer16_QCDPt170to300_Pythia8'                                                                                       
config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt170to300_Pythia8'                                                                            
#config.General.requestName = 'WWhadronic_Summer16_QCDPt300to470_Pythia8'                                                 
#config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt300to470_Pythia8'                                      
#config.General.requestName = 'WWhadronic_Summer16_QCDPt470to600_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt470to600_Pythia8'
#config.General.requestName = 'WWhadronic_Summer16_QCDPt600to800_Pythia8'                                                 
#config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt600to800_Pythia8'                                      
#config.General.requestName = 'WWhadronic_Summer16_QCDPt800to1000_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt800to1000_Pythia8'                  
#config.General.requestName = 'WWhadronic_Summer16_QCDPt1000to1400_Pythia8'                                                
#config.General.workArea = '/tmp/jjhollar/WWhadronic_Summer16_QCDPt1000to1400_Pythia8'                                     

config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['ExclWWjets.root']
config.JobType.inputFiles = [
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L1RC_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L2Relative_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L2Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_Uncertainty_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017BCD_V11_DATA_UncertaintySources_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L1FastJet_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L1RC_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L2Relative_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L2Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_Uncertainty_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017EF_V11_DATA_UncertaintySources_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L1FastJet_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L1RC_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L2Relative_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L2Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_Uncertainty_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017GH_V11_DATA_UncertaintySources_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L1FastJet_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L1RC_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L2L3Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L2Relative_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L2Residual_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_L3Absolute_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFchs.txt',
    'JEC2016/Summer16_07Aug2017_V11_MC_UncertaintySources_AK8PFchs.txt',

    'Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt',
    'Summer16_25nsV1_MC_SF_AK8PFchs.txt',
    'PUHistos_data_2017.root',
    'PUHistos_mc_2017.root',
    'PUHistos_data_2016.root',  
    'PUHistos_mc_2016.root'
]

# 07Aug2017 MiniAOD -ver2v1
#config.Data.inputDataset = '/JetHT/Run2016B-07Aug17_ver2-v1/MINIAOD' 
#config.Data.inputDataset = '/JetHT/Run2016G-07Aug17-v1/MINIAOD'

# Summer16 2016 MC
config.Data.inputDataset = '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'   
#config.Data.inputDataset = '/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM' 
#config.Data.inputDataset = '/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
# for data
#config.Data.splitting = 'Automatic'
# for MC
config.Data.splitting = 'FileBased'                                                                                               
config.Data.unitsPerJob = 9                                                                                                       
                              
#config.Data.lumiMask = 'Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON_PPSruns.txt'

#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2016Bver2v1_07Aug2017/'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2016Gv1_07Aug2017/'

config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt170to300_Pythia8'                                                                   
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt300to470_Pythia8'                             
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt600to800_Pythia8'                             
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt470to600_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt800to1000_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_Summer16_QCDPt1000to1400_Pythia8'

config.Data.publication = False
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2016Bver2v1_07Aug2017'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2016Gv1_07Aug2017'                                                         

config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt170to300_Pythia8'                                                                                     
#config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt300to470_Pythia8'                                               
#config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt600to800_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt470to600_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt800to1000_Pythia8'                                              
#config.Data.outputDatasetTag = 'WWhadronic_Summer16_QCDPt1000to1400_Pythia8'                                         

                                                

config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
config.Site.blacklist = ['T2_US_Caltech','T2_US_UCSD']

config.Site.storageSite = 'T2_US_Wisconsin'
