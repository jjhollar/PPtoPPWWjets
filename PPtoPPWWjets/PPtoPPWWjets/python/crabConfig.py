from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()


#config.General.requestName = 'WWhadronic_JetHT_2017Cv1_31Mar2018'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2017Cv1_31Mar2018'
config.General.requestName = 'WWhadronic_JetHT_2017Bv1_31Mar2018'                                                                    
config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2017Bv1_31Mar2018'                                                         
#config.General.requestName = 'WWhadronic_JetHT_2017Dv1_31Mar2018'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_JetHT_2017Dv1_31Mar2018'                           

#config.General.requestName = 'WWhadronic_QCDPt470to600_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt470to600_Pythia8'
#config.General.requestName = 'WWhadronic_QCDPt600to800_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt600to800_Pythia8'
#config.General.requestName = 'WWhadronic_QCDPt800to1000_Pythia8'                                                                 
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt800to1000_Pythia8'                                                      
#config.General.requestName = 'WWhadronic_QCDPt300to470_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt300to470_Pythia8'
#config.General.requestName = 'WWhadronic_QCDPt170to300_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt170to300_Pythia8'
#config.General.requestName = 'WWhadronic_QCDPt1000to1400_Pythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_QCDPt1000to1400_Pythia8'
#config.General.requestName = 'WWhadronic_TTbarHadronic_PowhegPythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_TTbarHadronic_PowhegPythia8'
#config.General.requestName = 'WWhadronic_WJetsToQQ_MadgraphPythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_WJetsToQQ_MadgraphPythia8'
#config.General.requestName = 'WWhadronic_ZJetsToQQ_MadgraphPythia8'
#config.General.workArea = '/tmp/jjhollar/WWhadronic_ZJetsToQQ_MadgraphPythia8'

config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['ExclWWjets.root']
config.JobType.inputFiles = [
    'JEC2017/Fall17_17Nov2017B_V6_DATA_L2L3Residual_AK8PFchs.txt',  
    'JEC2017/Fall17_17Nov2017C_V6_DATA_L2L3Residual_AK8PFchs.txt',  
    'JEC2017/Fall17_17Nov2017D_V6_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017E_V6_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017F_V6_DATA_L2L3Residual_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017_V8_MC_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017_V8_MC_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017B_V6_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017D_V6_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017F_V6_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017C_V6_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017E_V6_DATA_L2Relative_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017B_V6_DATA_L3Absolute_AK8PFchs.txt',  
    'JEC2017/Fall17_17Nov2017D_V6_DATA_L3Absolute_AK8PFchs.txt',  
    'JEC2017/Fall17_17Nov2017F_V6_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017C_V6_DATA_L3Absolute_AK8PFchs.txt',
    'JEC2017/Fall17_17Nov2017E_V6_DATA_L3Absolute_AK8PFchs.txt',
    'Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt',
    'Summer16_25nsV1_MC_SF_AK8PFchs.txt',
    'PUHistos_data.root',
    'PUHistos_mc.root'
]

config.Data.inputDataset = '/JetHT/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017D-17Nov2017-v1/MINIAOD'

#MiniAOD v2
#config.Data.inputDataset = '/JetHT/Run2017B-31Mar2018-v1/MINIAOD'                                                                                                
#config.Data.inputDataset = '/JetHT/Run2017C-31Mar2018-v1/MINIAOD'                                                                                                
#config.Data.inputDataset = '/JetHT/Run2017D-31Mar2018-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017E-31Mar2018-v1/MINIAOD'                                                                                                
#config.Data.inputDataset = '/JetHT/Run2017F-31Mar2018-v1/MINIAOD'                                                                                                

# Fall17 - has buggy PU profile
#config.Data.inputDataset = '/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'    
#config.Data.inputDataset = '/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM' 
#config.Data.inputDataset = '/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'

# Fall17 - possibly corrected PU profile?
#config.Data.inputDataset = '/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM'
#config.Data.inputDataset = '/WJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'                         
#config.Data.inputDataset = '/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'

config.Data.inputDBS = 'global'
# for data
#config.Data.splitting = 'Automatic'
# for MC
config.Data.splitting = 'FileBased'                                                                                               
config.Data.unitsPerJob = 9                                                                                                       
                              
    
#config.Data.lumiMask = 'Cert_13TeV_PromptReco_Collisions17_RPIN_JSON_all.txt'


#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Cv1_31Mar2018/'
config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Bv1_31Mar2018/'                                               
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_JetHT_2017Dv1_31Mar2018/'                        

#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt600to800_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt470to600_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt800to1000_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt300to470_Pythia8'                                              
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt170to300_Pythia8'                                              
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt800to1000_Pythia8'                                
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_QCDPt1000to1400_Pythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_TTbarHadronic_PowhegPythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_WJetsToQQ_MadgraphPythia8'
#config.Data.outLFNDirBase = '/store/user/jjhollar/WWhadronic_ZJetsToQQ_MadgraphPythia8'

config.Data.publication = False
config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Bv1_31Mar2018'                                                                  
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Cv1_31Mar2018'
#config.Data.outputDatasetTag = 'WWhadronic_JetHT_2017Dv1_31Mar2018'

#config.Data.outputDatasetTag = 'WWhadronic_QCDPt600to800_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt470to600_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt800to1000_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt300to470_Pythia8'                                                                
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt170to300_Pythia8'                                                                
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt800to1000_Pythia8'                                 
#config.Data.outputDatasetTag = 'WWhadronic_QCDPt1000to1400_Pythia8'
#config.Data.outputDatasetTag = 'WWhadronic_TTbarHadronic_PowhegPythia8'
#config.Data.outputDatasetTag = 'WWhadronic_WJetsToQQ_MadgraphPythia8'
#config.Data.outputDatasetTag = 'WWhadronic_ZJetsToQQ_MadgraphPythia8'

config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
config.Site.blacklist = ['T2_US_Caltech','T2_US_UCSD']

config.Site.storageSite = 'T2_US_Wisconsin'
