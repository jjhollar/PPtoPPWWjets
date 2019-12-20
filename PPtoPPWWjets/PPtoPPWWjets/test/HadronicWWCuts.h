/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 15 11:22:53 2018 by ROOT version 6.10/09
// from TTree ntp1/ntp1
// found on file: WWhadronic_JetHT_2017Cv1_merge.root
//////////////////////////////////////////////////////////

#ifndef HadronicWWCuts_h
#define HadronicWWCuts_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class HadronicWWCuts {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   Int_t samplenumber = 6;

   // Declaration of leaf types
   vector<float>   *jet_pt;
   vector<float>   *jet_energy;
   vector<float>   *jet_phi;
   vector<float>   *jet_eta;
   vector<float>   *jet_mass;
   vector<float>   *jet_tau1;
   vector<float>   *jet_tau2;
   vector<float>   *jet_corrmass;
   vector<float>   *jet_vertexz;
   vector<float>   *jet_jer_res;
   vector<float>   *jet_jer_sf;
   vector<float>   *dijet_mass;
   vector<float>   *dijet_pt;
   vector<float>   *dijet_y;
   vector<float>   *dijet_phi;
   vector<float>   *dijet_dphi;
   vector<float>   *pps_track_x;
   vector<float>   *pps_track_y;
   vector<int>     *pps_track_rpid;
   vector<float>   *pps_track_time;
   vector<float>   *proton_xi;
   vector<float>   *proton_thy;
   vector<float>   *proton_thx;
   vector<float>   *proton_t;
   vector<int>     *proton_ismultirp;
   vector<int>     *proton_rpid;
   vector<int>     *proton_arm;
   vector<float>   *proton_time;
   vector<float>   *proton_trackx1;
   vector<float>   *proton_tracky1;
   vector<float>   *proton_trackx2;
   vector<float>   *proton_tracky2;
   vector<int>     *proton_trackpixshift1;
   vector<int>     *proton_trackpixshift2;
   vector<int>     *proton_rpid1;
   vector<int>     *proton_rpid2;
   vector<float>   *gen_jet_pt;
   vector<float>   *gen_jet_energy;
   vector<float>   *gen_jet_phi;
   vector<float>   *gen_jet_eta;
   vector<float>   *gen_proton_xi;
   vector<float>   *gen_proton_pz;
   vector<float>   *gen_puproton_xi;
   vector<float>   *gen_puproton_pz;
   vector<string>  *hlt;

   UInt_t          nVertices;
   Float_t         pileupWeight;
   UInt_t          mc_pu_trueinteractions_;
   Int_t           run;
   Long64_t        event;
   Int_t           lumiblock;
   Float_t         crossingangle;

   // List of branches
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_energy;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_mass;   //!
   TBranch        *b_jet_tau1;   //!
   TBranch        *b_jet_tau2;   //!
   TBranch        *b_jet_corrmass;   //!
   TBranch        *b_jet_vertexz;   //!
   TBranch        *b_jet_jer_res;  //!
   TBranch        *b_jet_jer_sf;  //!
   TBranch        *b_dijet_mass;   //!
   TBranch        *b_dijet_pt;   //!
   TBranch        *b_dijet_y;   //!
   TBranch        *b_dijet_phi;   //!
   TBranch        *b_dijet_dphi;   //!
   TBranch        *b_pps_track_x;   //!
   TBranch        *b_pps_track_y;   //!
   TBranch        *b_pps_track_rpid;   //!
   TBranch        *b_pps_track_time;   //!                                                                                                 
   TBranch        *b_proton_xi;   //!                                                                                                      
   TBranch        *b_proton_thy;   //!                                                                                                     
   TBranch        *b_proton_thx;   //!                                                                                                     
   TBranch        *b_proton_t;   //!                                                                                                       
   TBranch        *b_proton_ismultirp;   //!                                                                                               
   TBranch        *b_proton_rpid;   //!                                                                                                    
   TBranch        *b_proton_arm;   //!                                                                                                     
   TBranch        *b_proton_time;   //!                                                                                                    
   TBranch        *b_proton_trackx1;   //!                                                                                                 
   TBranch        *b_proton_tracky1;   //!                                                                                                 
   TBranch        *b_proton_trackx2;   //!                                                                                                 
   TBranch        *b_proton_tracky2;   //!                                                                                                 
   TBranch        *b_proton_trackpixshift1;   //!                                                                                          
   TBranch        *b_proton_trackpixshift2;   //!                                                                                          
   TBranch        *b_proton_rpid1;   //!                                                                                                   
   TBranch        *b_proton_rpid2;   //!                                                                                                   
   TBranch        *b_gen_jet_pt;   //!                                                                                                         
   TBranch        *b_gen_jet_energy;   //!                                                                                                     
   TBranch        *b_gen_jet_phi;   //!                                                                                                        
   TBranch        *b_gen_jet_eta;   //!
   TBranch        *b_gen_proton_xi;  //!
   TBranch        *b_gen_proton_pz;  //!                                                                                                                              
   TBranch        *b_gen_puproton_xi;  //!                                                                                                                                
   TBranch        *b_gen_puproton_pz;  //!                                                                                                                                
   TBranch        *b_hlt;   //!
   TBranch        *b_nVertices;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_mc_pu_trueinteractions;   //!                                                                                         
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumiblock;   //!
   TBranch        *b_crossingangle;   //!                                                                                                  

   // Efficiency correction histograms
   TH2F *hpixeffB45, *hpixeffC145, *hpixeffE45, *hpixeffF145;
   TH2F *hpixeffB56, *hpixeffC156, *hpixeffE56, *hpixeffF156;
   TH2F *hpixeff2017PreTS245, *hpixeff2017PostTS245;
   TH2F *hpixeff2017PreTS256, *hpixeff2017PostTS256;

   TH2F *hstreffB45, *hstreffC45, *hstreffD45, *hstreffE45, *hstreffF45;
   TH2F *hstreffB56, *hstreffC56, *hstreffD56, *hstreffE56, *hstreffF56;
   TH2F *hstreff2017PreTS245, *hstreff2017PostTS245;
   TH2F *hstreff2017PreTS256, *hstreff2017PostTS256;

   TH1F *hmultistreffB45, *hmultistreffC45, *hmultistreffD45, *hmultistreffE45, *hmultistreffF45;
   TH1F *hmultistreffB56, *hmultistreffC56, *hmultistreffD56, *hmultistreffE56, *hmultistreffF56;
   TH1F *hmultistreff2017PreTS245, *hmultistreff2017PostTS245;
   TH1F *hmultistreff2017PreTS256, *hmultistreff2017PostTS256;

   TRandom *rnd;


   HadronicWWCuts(Int_t mysample = 6, TTree *tree=0);
   virtual ~HadronicWWCuts();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Float_t  Aperture(Float_t xangle, Int_t arm, TString era);
   virtual Bool_t   PixelFiducial(Float_t trackx, Float_t tracky, Int_t arm, Int_t thesample);
   virtual Bool_t  SingleRPEffCorr(Float_t trackx220, Float_t tracky220, Int_t arm, Int_t thesample);
   virtual Bool_t  MultiRPEffCorr(Float_t trackx210, Float_t tracky210, Float_t trackx220, Float_t tracky220, Int_t arm, Int_t thesample);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HadronicWWCuts_cxx
HadronicWWCuts::HadronicWWCuts(Int_t mysample, TTree *tree) : fChain(0) 
{
  samplenumber = mysample;
  cout << "Opening sample = " << samplenumber << endl;

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f;
    if(samplenumber == -1)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD_merge.root");
    if(samplenumber == -2)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Cv1_17Nov2017_LegacyFromAOD_merge.root");
    if(samplenumber == -3)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Dv1_17Nov2017_LegacyFromAOD_merge.root");
    if(samplenumber == -4)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Ev1_17Nov2017_LegacyFromAOD_merge.root");
    if(samplenumber == -5)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Fv1_17Nov2017_LegacyFromAOD_merge.root");

    if(samplenumber == -6)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("ExclWWjets_Run2016B-07Aug2017-ver2-v1_all.root");
    if(samplenumber == -7)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("ExclWWjets_Run2016C-07Aug2017-v1_all.root");
    if(samplenumber == -8)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("ExclWWjets_Run2016G-07Aug2017-v1_all.root");
    if(samplenumber == -9)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("ExclWWjets_Run2016H-07Aug2017-v1_all.root");


    if(samplenumber == 1)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 2)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 3)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_merge.root");   
    if(samplenumber == 4)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_merge.root"); 
    if(samplenumber == 5)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 6)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 7)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_merge.root");
    if(samplenumber == 8)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root");
    if(samplenumber == 9)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root");
    if(samplenumber == 10)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 11)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8_merge.root");
    if(samplenumber == 12)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8_merge.root");

    if(samplenumber == 20)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("WWhadronic_ExclusiveWW_AllDecays_SM_xi1to30percent_ntuplesv2.root");
    if(samplenumber == 21)
      f = (TFile *)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root"); 
    if(samplenumber == 22)
      f = (TFile *)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root");
    if(samplenumber == 24)
      f = (TFile *)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root");
    if(samplenumber == 25)
      f = (TFile *)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W5E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6//WWhadronic_ExclusiveWW_AllDecays_a0W5point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root");
    if(samplenumber == 27)
      f = (TFile *)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/WWhadronic/WWaCW2E5_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/WWhadronic_ExclusiveWW_AllDecays_aCW2point2e-5_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root");

    if(samplenumber == 31)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZZhadronic_FPMC_a0Z5E-5_Fall2017_LegacyFromAOD_10kevents2017preTS2_NoPUprotons_job1.root");

    if(samplenumber == 41)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/jjhollar/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv1_50kevents2017postTS2_NoPUprotons_job1.root");

    if(samplenumber == 99)
      f = (TFile*)gROOT->GetListOfFiles()->FindObject("WWhadronic_aCW2E-5_PileupProtonsOnly.root");

    if (!f || !f->IsOpen()) {
      if(samplenumber == -1)
        f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD_merge.root");
      if(samplenumber == -2)
	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Cv1_17Nov2017_LegacyFromAOD_merge.root");
      if(samplenumber == -3)
        f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Dv1_17Nov2017_LegacyFromAOD_merge.root");
      if(samplenumber == -4)
        f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Ev1_17Nov2017_LegacyFromAOD_merge.root");
      if(samplenumber == -5)
        f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Fv1_17Nov2017_LegacyFromAOD_merge.root");

      if(samplenumber == -6)
        f = new TFile("ExclWWjets_Run2016B-07Aug2017-ver2-v1_all.root");
      if(samplenumber == -7)
	f = new TFile("ExclWWjets_Run2016C-07Aug2017-v1_all.root");
      if(samplenumber == -8)
	f = new TFile("ExclWWjets_Run2016G-07Aug2017-v1_all.root");
      if(samplenumber == -9)
	f = new TFile("ExclWWjets_Run2016H-07Aug2017-v1_all.root");

      
      if(samplenumber == 1)
	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 2)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 3)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 4)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 5)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 6)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 7)
	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_merge.root");
      if(samplenumber == 8)
	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root");
      if(samplenumber == 9)
        f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root");
      if(samplenumber == 10)
	f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 11)
        f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8_merge.root");
      if(samplenumber == 12)
        f = new TFile("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8_merge.root");

      if(samplenumber == 20)
	f = new TFile("WWhadronic_ExclusiveWW_AllDecays_SM_xi1to30percent_ntuplesv2.root");
      if(samplenumber == 21)
	//	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_FPMC_a0W2E-6_Fall2017_LegacyFromAOD_2017crossingangles_test14kevents.root");
	//	f = new TFile("/tmp/jjhollar/WWhadronic_FPMC_a0W1E-6_Fall2017_LegacyFromAOD_2017crossingangles_test10kevents_WithPU.root");
	//	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_FPMC_a0W1E-6_Fall2017_LegacyFromAOD_2017crossingangles_test10kevents_NoPU_new.root");
	//	f = new TFile("WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv1_20kevents2017postTS2_SignalPlusPU_new.root");
	f = new TFile("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root"); 
      if(samplenumber == 22)
	f = new TFile("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W2e-6_13TeV-fpmc-herwig6/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root");
      if(samplenumber == 24)
	f = new TFile("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root");
      if(samplenumber == 25)
	f = new TFile("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W5E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6//WWhadronic_ExclusiveWW_AllDecays_a0W5point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root");
      if(samplenumber == 27)
	f = new TFile("/eos/cms/store/user/jjhollar/WWhadronic/WWaCW2E5_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/WWhadronic_ExclusiveWW_AllDecays_aCW2point2e-5_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root");

      if(samplenumber == 31)
	f = new TFile("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZZhadronic_FPMC_a0Z5E-5_Fall2017_LegacyFromAOD_10kevents2017preTS2_NoPUprotons_job1.root");

      if(samplenumber == 41)
	f = new TFile("/tmp/jjhollar/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv1_50kevents2017postTS2_NoPUprotons_job1.root");

      if(samplenumber == 99)
	f = new TFile("WWhadronic_aCW2E-5_PileupProtonsOnly.root");
    }
    TDirectory * dir;

    if(samplenumber == -1)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Bv1_17Nov2017_LegacyFromAOD_merge.root:/demo");
    if(samplenumber == -2)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_JetHT_2017Cv1_17Nov2017_LegacyFromAOD_merge.root:/demo");
    if(samplenumber == -3)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Dv1_17Nov2017_LegacyFromAOD_merge.root:/demo");
    if(samplenumber == -4)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Ev1_17Nov2017_LegacyFromAOD_merge.root:/demo");
    if(samplenumber == -5)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/WWhadronic_JetHT_2017Fv1_17Nov2017_LegacyFromAOD_merge.root:/demo");

    if(samplenumber == -6)
      dir = (TDirectory*)f->Get("ExclWWjets_Run2016B-07Aug2017-ver2-v1_all.root");
    if(samplenumber == -7)
      dir = (TDirectory*)f->Get("ExclWWjets_Run2016C-07Aug2017-v1_all.root");
    if(samplenumber == -8)
      dir = (TDirectory*)f->Get("ExclWWjets_Run2016G-07Aug2017-v1_all.root");
    if(samplenumber == -9)
      dir = (TDirectory*)f->Get("ExclWWjets_Run2016H-07Aug2017-v1_all.root");
    
    if(samplenumber == 1)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 2)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 3)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 4)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 5)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 6)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 7)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_merge.root:/demo");
    if(samplenumber == 8)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root:/demo");
    if(samplenumber == 9)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8_merge.root:/demo");
    if(samplenumber == 10)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 11)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8_merge.root:/demo");
    if(samplenumber == 12)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/PPtoPPWW_UL/QCD/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8_merge.root:/demo");

    if(samplenumber == 20)
      dir = (TDirectory*)f->Get("WWhadronic_ExclusiveWW_AllDecays_SM_xi1to30percent_ntuplesv2.root:/demo");
    if(samplenumber == 21)
      //      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_FPMC_a0W2E-6_Fall2017_LegacyFromAOD_2017crossingangles_test14kevents.root:/demo");
      //      dir = (TDirectory*)f->Get("/tmp/jjhollar/WWhadronic_FPMC_a0W1E-6_Fall2017_LegacyFromAOD_2017crossingangles_test10kevents_WithPU.root:/demo");
      //      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/WWhadronic_FPMC_a0W1E-6_Fall2017_LegacyFromAOD_2017crossingangles_test10kevents_NoPU_new.root:/demo");
      //      dir = (TDirectory*)f->Get("WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv1_20kevents2017postTS2_SignalPlusPU_new.root:/demo");
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W1e-6_13TeV-fpmc-herwig6/WWa0W1E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root:/demo");

    if(samplenumber == 22)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGTo\
WW_bSM-A0W2e-6_13TeV-fpmc-herwig6/WWa0W2E6_2017preTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root:/demo");
    if(samplenumber == 24)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W2E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/WWhadronic_ExclusiveWW_AllDecays_a0W2point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root:/demo");
    if(samplenumber == 25)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/WWhadronic/WWa0W5E6_2017postTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-A0W5e-6_13TeV-fpmc-herwig6//WWhadronic_ExclusiveWW_AllDecays_a0W5point0e-6_ntuplesULv2_2017postTS2_OnlySignalprotons_merge.root:/demo");
    if(samplenumber == 27)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/WWhadronic/WWaCW2E5_2017preTS2_LegacyFromAOD_SingalProtons_Only/GGToWW_bSM-ACW2e-5_13TeV-fpmc-herwig6/WWhadronic_ExclusiveWW_AllDecays_aCW2point2e-5_ntuplesULv2_2017preTS2_OnlySignalprotons_merge.root:/demo");

    if(samplenumber == 31)
      dir = (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/ZZhadronic_FPMC_a0Z5E-5_Fall2017_LegacyFromAOD_10kevents2017preTS2_NoPUprotons_job1.root:/demo");

    if(samplenumber == 41)
      dir = (TDirectory*)f->Get("/tmp/jjhollar/WWhadronic_ExclusiveWW_AllDecays_a0W1point0e-6_ntuplesULv1_50kevents2017postTS2_NoPUprotons_job1.root:/demo");
    
    if(samplenumber == 99)
      dir = (TDirectory*)f->Get("WWhadronic_aCW2E-5_PileupProtonsOnly.root:/demo");

    dir->GetObject("ntp1",tree);

  }
  Init(tree);

  // Setup for efficiency corrections ("killing")
  rnd = new TRandom();
  rnd->SetSeed(123456);

  Float_t lumiB = 2.361; 
  Float_t lumiC1 = 5.3;
  Float_t lumiC = 8.577;
  Float_t lumiD = 4.075;
  Float_t lumiE = 8.959;
  Float_t lumiF1 = 1.7;
  Float_t lumiF = 13.214;

  // Pixels - lumi-weighted averages for pre- and post-TS2
  TFile *fpixeff = TFile::Open("pixelEfficiencies.root");
  hpixeffB45 = (TH2F *)fpixeff->Get("Pixel/2017/2017B/h45_220_2017B_all_2D"); // 2.4fb
  hpixeffB56 = (TH2F *)fpixeff->Get("Pixel/2017/2017B/h56_220_2017B_all_2D");
  hpixeffC145 = (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h45_220_2017C1_all_2D"); // 5.3fb
  hpixeffC156 = (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h56_220_2017C1_all_2D");
  hpixeffE45 = (TH2F *)fpixeff->Get("Pixel/2017/2017E/h45_220_2017E_all_2D"); // 9fb
  hpixeffE56 = (TH2F *)fpixeff->Get("Pixel/2017/2017E/h56_220_2017E_all_2D");
  hpixeffF145 = (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h45_220_2017F1_all_2D"); // 1.7fb
  hpixeffF156 = (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h56_220_2017F1_all_2D");

  hpixeffB45->Scale(lumiB/(lumiB+lumiC1));
  hpixeffB56->Scale(lumiB/(lumiB+lumiC1));
  hpixeffC145->Scale(lumiC1/(lumiB+lumiC1));
  hpixeffC156->Scale(lumiC1/(lumiB+lumiC1));
  hpixeff2017PreTS245 = (TH2F *)hpixeffB45->Clone("hpixeff2017PreTS245");
  hpixeff2017PreTS256 = (TH2F *)hpixeffB56->Clone("hpixeff2017PreTS256");
  hpixeff2017PreTS245->Add(hpixeffC145);
  hpixeff2017PreTS256->Add(hpixeffC156);

  hpixeffE45->Scale(lumiE/(lumiE+lumiF1));
  hpixeffE56->Scale(lumiE/(lumiE+lumiF1));
  hpixeffF145->Scale(lumiF1/(lumiE+lumiF1));
  hpixeffF156->Scale(lumiF1/(lumiE+lumiF1));
  hpixeff2017PostTS245 = (TH2F *)hpixeffE45->Clone("hpixeff2017PostTS245");
  hpixeff2017PostTS256 = (TH2F *)hpixeffE56->Clone("hpixeff2017PostTS256");
  hpixeff2017PostTS245->Add(hpixeffF145);
  hpixeff2017PostTS256->Add(hpixeffF156);

  // Strips - lumi-weighted averages for pre- and post-TS2                                                                                                                                                                     
  TFile *fstripeff = TFile::Open("PreliminaryEfficiencies_October92019_1D2DMultiTrack.root");
  hstreffB45 = (TH2F *)fstripeff->Get("Strips/2017/2017B/h45_2017B_all_2D");
  hstreffC45 = (TH2F *)fstripeff->Get("Strips/2017/2017C/h45_2017C_all_2D");
  hstreffD45 = (TH2F *)fstripeff->Get("Strips/2017/2017D/h45_2017D_all_2D");
  hstreffE45 = (TH2F *)fstripeff->Get("Strips/2017/2017E/h45_2017E_all_2D");
  hstreffF45 = (TH2F *)fstripeff->Get("Strips/2017/2017F/h45_2017F_all_2D");
  hstreffB56 = (TH2F *)fstripeff->Get("Strips/2017/2017B/h56_2017B_all_2D");
  hstreffC56 = (TH2F *)fstripeff->Get("Strips/2017/2017C/h56_2017C_all_2D");
  hstreffD56 = (TH2F *)fstripeff->Get("Strips/2017/2017D/h56_2017D_all_2D");
  hstreffE56 = (TH2F *)fstripeff->Get("Strips/2017/2017E/h56_2017E_all_2D");
  hstreffF56 = (TH2F *)fstripeff->Get("Strips/2017/2017F/h56_2017F_all_2D");

  hstreffB45->Scale(lumiB/(lumiB+lumiC+lumiD));
  hstreffB56->Scale(lumiB/(lumiB+lumiC+lumiD));
  hstreffC45->Scale(lumiC/(lumiB+lumiC+lumiD));
  hstreffC56->Scale(lumiC/(lumiB+lumiC+lumiD));
  hstreffD45->Scale(lumiD/(lumiB+lumiC+lumiD));
  hstreffD56->Scale(lumiD/(lumiB+lumiC+lumiD));
  hstreff2017PreTS245 = (TH2F *)hstreffB45->Clone("hstreff2017PreTS245");
  hstreff2017PreTS256 = (TH2F *)hstreffB56->Clone("hstreff2017PreTS256");
  hstreff2017PreTS245->Add(hstreffC45); hstreff2017PreTS245->Add(hstreffD45);
  hstreff2017PreTS256->Add(hstreffC56); hstreff2017PreTS256->Add(hstreffD56);

  hstreffE45->Scale(lumiE/(lumiE+lumiF));
  hstreffE56->Scale(lumiE/(lumiE+lumiF));
  hstreffF45->Scale(lumiF/(lumiE+lumiF));
  hstreffF56->Scale(lumiF/(lumiE+lumiF));
  hstreff2017PostTS245 = (TH2F *)hstreffE45->Clone("hstreff2017PostTS245");
  hstreff2017PostTS256 = (TH2F *)hstreffE56->Clone("hstreff2017PostTS256");
  hstreff2017PostTS245->Add(hstreffF45);
  hstreff2017PostTS256->Add(hstreffF56);

  // Multi-track for strips
  hmultistreffB45 = (TH1F *)fstripeff->Get("Strips/2017/2017B/h45multitrackeff_2017B_avg_RP3");
  hmultistreffC45 = (TH1F *)fstripeff->Get("Strips/2017/2017C/h45multitrackeff_2017C_avg_RP3");
  hmultistreffD45 = (TH1F *)fstripeff->Get("Strips/2017/2017D/h45multitrackeff_2017D_avg_RP3");
  hmultistreffE45 = (TH1F *)fstripeff->Get("Strips/2017/2017E/h45multitrackeff_2017E_avg_RP3");
  hmultistreffF45 = (TH1F *)fstripeff->Get("Strips/2017/2017F/h45multitrackeff_2017F_avg_RP3");
  hmultistreffB56 = (TH1F *)fstripeff->Get("Strips/2017/2017B/h56multitrackeff_2017B_avg_RP103");
  hmultistreffC56 = (TH1F *)fstripeff->Get("Strips/2017/2017C/h56multitrackeff_2017C_avg_RP103");
  hmultistreffD56 = (TH1F *)fstripeff->Get("Strips/2017/2017D/h56multitrackeff_2017D_avg_RP103");
  hmultistreffE56 = (TH1F *)fstripeff->Get("Strips/2017/2017E/h56multitrackeff_2017E_avg_RP103");
  hmultistreffF56 = (TH1F *)fstripeff->Get("Strips/2017/2017F/h56multitrackeff_2017F_avg_RP103");

  hmultistreffB45->Scale(lumiB/(lumiB+lumiC+lumiD));
  hmultistreffB56->Scale(lumiB/(lumiB+lumiC+lumiD));
  hmultistreffC45->Scale(lumiC/(lumiB+lumiC+lumiD));
  hmultistreffC56->Scale(lumiC/(lumiB+lumiC+lumiD));
  hmultistreffD45->Scale(lumiD/(lumiB+lumiC+lumiD));
  hmultistreffD56->Scale(lumiD/(lumiB+lumiC+lumiD));
  hmultistreff2017PreTS245 = (TH1F *)hmultistreffB45->Clone("hmultistreff2017PreTS245");
  hmultistreff2017PreTS256 = (TH1F *)hmultistreffB56->Clone("hmultistreff2017PreTS256");
  hmultistreff2017PreTS245->Add(hmultistreffC45); hmultistreff2017PreTS245->Add(hmultistreffD45);
  hmultistreff2017PreTS256->Add(hmultistreffC56); hmultistreff2017PreTS256->Add(hmultistreffD56);

  hmultistreffE45->Scale(lumiE/(lumiE+lumiF));
  hmultistreffE56->Scale(lumiE/(lumiE+lumiF));
  hmultistreffF45->Scale(lumiF/(lumiE+lumiF));
  hmultistreffF56->Scale(lumiF/(lumiE+lumiF));
  hmultistreff2017PostTS245 = (TH1F *)hmultistreffE45->Clone("hmultistreff2017PostTS245");
  hmultistreff2017PostTS256 = (TH1F *)hmultistreffE56->Clone("hmultistreff2017PostTS256");
  hmultistreff2017PostTS245->Add(hmultistreffF45);
  hmultistreff2017PostTS256->Add(hmultistreffF56);

}

HadronicWWCuts::~HadronicWWCuts()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HadronicWWCuts::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HadronicWWCuts::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HadronicWWCuts::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_pt = 0;
   jet_energy = 0;
   jet_phi = 0;
   jet_eta = 0;
   jet_mass = 0;
   jet_tau1 = 0;
   jet_tau2 = 0;
   jet_corrmass = 0;
   jet_vertexz = 0;
   jet_jer_res = 0;
   jet_jer_sf = 0;
   dijet_mass = 0;
   dijet_pt = 0;
   dijet_y = 0;
   dijet_phi = 0;
   dijet_dphi = 0;
   pps_track_x = 0;
   pps_track_y = 0;
   pps_track_rpid = 0;
   pps_track_time = 0;
   proton_xi = 0;
   proton_thy = 0;
   proton_thx = 0;
   proton_t = 0;
   proton_ismultirp = 0;
   proton_rpid = 0;
   proton_arm = 0;
   proton_time = 0;
   proton_trackx1 = 0;
   proton_tracky1 = 0;
   proton_trackx2 = 0;
   proton_tracky2 = 0;
   proton_trackpixshift1 = 0;
   proton_trackpixshift2 = 0;
   proton_rpid1 = 0;
   proton_rpid2 = 0;
   gen_jet_pt = 0;
   gen_jet_energy = 0;
   gen_jet_phi = 0;
   gen_jet_eta = 0;
   gen_proton_xi = 0;
   gen_proton_pz = 0;
   gen_puproton_xi = 0;
   gen_puproton_pz = 0;
   hlt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_energy", &jet_energy, &b_jet_energy);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_mass", &jet_mass, &b_jet_mass);
   fChain->SetBranchAddress("jet_tau1", &jet_tau1, &b_jet_tau1);
   fChain->SetBranchAddress("jet_tau2", &jet_tau2, &b_jet_tau2);
   fChain->SetBranchAddress("jet_corrmass", &jet_corrmass, &b_jet_corrmass);
   fChain->SetBranchAddress("jet_vertexz", &jet_vertexz, &b_jet_vertexz);
   fChain->SetBranchAddress("jet_jer_res", &jet_jer_res, &b_jet_jer_res);
   fChain->SetBranchAddress("jet_jer_sf", &jet_jer_sf, &b_jet_jer_sf);
   fChain->SetBranchAddress("dijet_mass", &dijet_mass, &b_dijet_mass);
   fChain->SetBranchAddress("dijet_pt", &dijet_pt, &b_dijet_pt);
   fChain->SetBranchAddress("dijet_y", &dijet_y, &b_dijet_y);
   fChain->SetBranchAddress("dijet_phi", &dijet_phi, &b_dijet_phi);
   fChain->SetBranchAddress("dijet_dphi", &dijet_dphi, &b_dijet_dphi);
   fChain->SetBranchAddress("pps_track_x", &pps_track_x, &b_pps_track_x);
   fChain->SetBranchAddress("pps_track_y", &pps_track_y, &b_pps_track_y);
   fChain->SetBranchAddress("pps_track_rpid", &pps_track_rpid, &b_pps_track_rpid);
   fChain->SetBranchAddress("pps_track_time", &pps_track_time, &b_pps_track_time);
   fChain->SetBranchAddress("proton_xi", &proton_xi, &b_proton_xi);
   fChain->SetBranchAddress("proton_thy", &proton_thy, &b_proton_thy);
   fChain->SetBranchAddress("proton_thx", &proton_thx, &b_proton_thx);
   fChain->SetBranchAddress("proton_t", &proton_t, &b_proton_t);
   fChain->SetBranchAddress("proton_ismultirp", &proton_ismultirp, &b_proton_ismultirp);
   fChain->SetBranchAddress("proton_rpid", &proton_rpid, &b_proton_rpid);
   fChain->SetBranchAddress("proton_arm", &proton_arm, &b_proton_arm);
   fChain->SetBranchAddress("proton_time", &proton_time, &b_proton_time);
   fChain->SetBranchAddress("proton_trackx1", &proton_trackx1, &b_proton_trackx1);
   fChain->SetBranchAddress("proton_tracky1", &proton_tracky1, &b_proton_tracky1);
   fChain->SetBranchAddress("proton_trackx2", &proton_trackx2, &b_proton_trackx2);
   fChain->SetBranchAddress("proton_tracky2", &proton_tracky2, &b_proton_tracky2);
   fChain->SetBranchAddress("proton_trackpixshift1", &proton_trackpixshift1, &b_proton_trackpixshift1);
   fChain->SetBranchAddress("proton_trackpixshift2", &proton_trackpixshift2, &b_proton_trackpixshift2);
   fChain->SetBranchAddress("proton_rpid1", &proton_rpid1, &b_proton_rpid1);
   fChain->SetBranchAddress("proton_rpid2", &proton_rpid2, &b_proton_rpid2);
   fChain->SetBranchAddress("gen_jet_pt", &gen_jet_pt, &b_gen_jet_pt);
   fChain->SetBranchAddress("gen_jet_energy", &gen_jet_energy, &b_gen_jet_energy);
   fChain->SetBranchAddress("gen_jet_phi", &gen_jet_phi, &b_gen_jet_phi);
   fChain->SetBranchAddress("gen_jet_eta", &gen_jet_eta, &b_gen_jet_eta);
   fChain->SetBranchAddress("gen_proton_xi", &gen_proton_xi, &b_gen_proton_xi);  
   fChain->SetBranchAddress("gen_proton_pz", &gen_proton_pz, &b_gen_proton_pz);
   fChain->SetBranchAddress("gen_puproton_xi", &gen_puproton_xi, &b_gen_puproton_xi);
   fChain->SetBranchAddress("gen_puproton_pz", &gen_puproton_pz, &b_gen_puproton_pz);
   fChain->SetBranchAddress("hlt", &hlt, &b_hlt);
   fChain->SetBranchAddress("nVertices", &nVertices, &b_nVertices);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("mc_pu_trueinteractions_", &mc_pu_trueinteractions_, &b_mc_pu_trueinteractions);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumiblock", &lumiblock, &b_lumiblock);
   fChain->SetBranchAddress("crossingangle", &crossingangle, &b_crossingangle);
   Notify();
}

Bool_t HadronicWWCuts::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HadronicWWCuts::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HadronicWWCuts::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HadronicWWCuts_cxx
