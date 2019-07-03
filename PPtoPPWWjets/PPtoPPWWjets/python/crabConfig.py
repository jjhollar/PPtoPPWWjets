from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD'                                                                               
config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD'                                                                    

config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFileLegacyReRecoPrelim_cfg.py'
config.JobType.outputFiles = ['ExclWWjets.root']
config.JobType.inputFiles = [
    'JEC2017/Fall17_17Nov2017B_V32_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017B_V32_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017B_V32_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017C_V32_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017C_V32_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017C_V32_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017DE_V32_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017F_V32_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017F_V32_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017F_V32_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017_V32_MC_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017_V32_MC_L3Absolute_AK8PFchs.txt',
    'Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt',
    'Summer16_25nsV1_MC_SF_AK8PFchs.txt',
    'PUHistos_data.root',
    'PUHistos_mc.root'
]

# 2017 AOD data, for legacy 
config.Data.inputDataset = '/JetHT/Run2017B-17Nov2017-v1/AOD'
#config.Data.inputDataset = '/JetHT/Run2017C-17Nov2017-v1/AOD'
#config.Data.inputDataset = '/JetHT/Run2017D-17Nov2017-v1/AOD'
#config.Data.inputDataset = '/JetHT/Run2017E-17Nov2017-v1/AOD'
#config.Data.inputDataset = '/JetHT/Run2017F-17Nov2017-v1/AOD'

config.Data.inputDBS = 'global'
# for data
config.Data.splitting = 'Automatic'
# for MC
#config.Data.splitting = 'FileBased'                                                                                               
#config.Data.unitsPerJob = 25                                                                                                       
                              
    
config.Data.lumiMask = 'combined_RPIN_CMS_2017.json'
#config.Data.lumiMask = 'Cert_13TeV_PromptReco_Collisions17_RPIN_JSON_all.txt'


config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Cv1_17Nov2017_LegacyFromAOD'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Dv1_17Nov2017_LegacyFromAOD'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Ev1_17Nov2017_LegacyFromAOD'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Fv1_17Nov2017_LegacyFromAOD'


config.Data.publication = False

config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Cv1_17Nov2017_LegacyFromAOD'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Dv1_17Nov2017_LegacyFromAOD'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Ev1_17Nov2017_LegacyFromAOD'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Fv1_17Nov2017_LegacyFromAOD'


config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
#config.Site.blacklist = ['T2_US_Caltech','T2_US_UCSD']

config.Site.storageSite = 'T2_CH_CERN'
