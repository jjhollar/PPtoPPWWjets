/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 15 11:22:53 2018 by ROOT version 6.10/09
// from TTree ntp1/ntp1
// found on file: WWhadronic_JetHT_2017Cv1_merge.root
//////////////////////////////////////////////////////////

#ifndef HadronicWWCuts_h
#define HadronicWWCuts_h

#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

#include "PPSProtonSelector.C"

// gROOT->ProcessLine(".L
// ../../../jecsys/CondFormats/JetMETObjects/src/JetCorrectionUncertainty_cc.so");

class HadronicWWCuts {
public:
  TTree *fChain;  //! pointer to the analyzed TTree or TChain
  Int_t fCurrent; //! current Tree number in a TChain
  bool protonSyst;
  bool JECSystUp;
  bool JECSystDown;
  double unitarityCut;
  double min_mvvCut;
  double gen_xi_min;
  double gen_xi_max;

  // Fixed size dimensions of array or collections stored in the TTree if any.

  Int_t samplenumber = 6;

  // Declaration of leaf types
  vector<float> *jet_pt;
  vector<float> *jet_energy;
  vector<float> *jet_phi;
  vector<float> *jet_eta;
  vector<float> *jet_mass;
  vector<float> *jet_tau1;
  vector<float> *jet_tau2;
  vector<float> *jet_corrmass;
  vector<float> *jet_vertexz;
  vector<float> *jet_jer_res;
  vector<float> *jet_jer_sf;
  vector<float> *dijet_mass;
  vector<float> *dijet_pt;
  vector<float> *dijet_y;
  vector<float> *dijet_phi;
  vector<float> *dijet_dphi;
  vector<float> *pps_track_x;
  vector<float> *pps_track_y;
  vector<int> *pps_track_rpid;
  vector<float> *pps_track_time;
  vector<float> *proton_xi;
  vector<float> *proton_thy;
  vector<float> *proton_thx;
  vector<float> *proton_t;
  vector<int> *proton_ismultirp;
  vector<int> *proton_rpid;
  vector<int> *proton_arm;
  vector<float> *proton_time;
  vector<float> *proton_trackx1;
  vector<float> *proton_tracky1;
  vector<float> *proton_trackx2;
  vector<float> *proton_tracky2;
  vector<int> *proton_trackpixshift1;
  vector<int> *proton_trackpixshift2;
  vector<int> *proton_rpid1;
  vector<int> *proton_rpid2;
  vector<float> *gen_jet_pt;
  vector<float> *gen_jet_energy;
  vector<float> *gen_jet_phi;
  vector<float> *gen_jet_eta;
  vector<float> *gen_proton_xi;
  vector<float> *gen_proton_pz;
  vector<float> *gen_puproton_xi;
  vector<float> *gen_puproton_pz;
  vector<string> *hlt;

  UInt_t nVertices;
  Float_t pileupWeight;
  UInt_t mc_pu_trueinteractions_;
  Int_t run;
  Long64_t event;
  Int_t lumiblock;
  Float_t crossingangle;

  // List of branches
  TBranch *b_jet_pt;                 //!
  TBranch *b_jet_energy;             //!
  TBranch *b_jet_phi;                //!
  TBranch *b_jet_eta;                //!
  TBranch *b_jet_mass;               //!
  TBranch *b_jet_tau1;               //!
  TBranch *b_jet_tau2;               //!
  TBranch *b_jet_corrmass;           //!
  TBranch *b_jet_vertexz;            //!
  TBranch *b_jet_jer_res;            //!
  TBranch *b_jet_jer_sf;             //!
  TBranch *b_dijet_mass;             //!
  TBranch *b_dijet_pt;               //!
  TBranch *b_dijet_y;                //!
  TBranch *b_dijet_phi;              //!
  TBranch *b_dijet_dphi;             //!
  TBranch *b_pps_track_x;            //!
  TBranch *b_pps_track_y;            //!
  TBranch *b_pps_track_rpid;         //!
  TBranch *b_pps_track_time;         //!
  TBranch *b_proton_xi;              //!
  TBranch *b_proton_thy;             //!
  TBranch *b_proton_thx;             //!
  TBranch *b_proton_t;               //!
  TBranch *b_proton_ismultirp;       //!
  TBranch *b_proton_rpid;            //!
  TBranch *b_proton_arm;             //!
  TBranch *b_proton_time;            //!
  TBranch *b_proton_trackx1;         //!
  TBranch *b_proton_tracky1;         //!
  TBranch *b_proton_trackx2;         //!
  TBranch *b_proton_tracky2;         //!
  TBranch *b_proton_trackpixshift1;  //!
  TBranch *b_proton_trackpixshift2;  //!
  TBranch *b_proton_rpid1;           //!
  TBranch *b_proton_rpid2;           //!
  TBranch *b_gen_jet_pt;             //!
  TBranch *b_gen_jet_energy;         //!
  TBranch *b_gen_jet_phi;            //!
  TBranch *b_gen_jet_eta;            //!
  TBranch *b_gen_proton_xi;          //!
  TBranch *b_gen_proton_pz;          //!
  TBranch *b_gen_puproton_xi;        //!
  TBranch *b_gen_puproton_pz;        //!
  TBranch *b_hlt;                    //!
  TBranch *b_nVertices;              //!
  TBranch *b_pileupWeight;           //!
  TBranch *b_mc_pu_trueinteractions; //!
  TBranch *b_run;                    //!
  TBranch *b_event;                  //!
  TBranch *b_lumiblock;              //!
  TBranch *b_crossingangle;          //!

  // Efficiency correction histograms
  TH2F *hpixeffB45, *hpixeffC145, *hpixeffC245, *hpixeffD45, *hpixeffE45,
      *hpixeffF145, *hpixeffF245, *hpixeffF345;
  TH2F *hpixeffB56, *hpixeffC156, *hpixeffC256, *hpixeffD56, *hpixeffE56,
      *hpixeffF156, *hpixeffF256, *hpixeffF356;
  TH2F *hpixeff2017PreTS245, *hpixeff2017PostTS245;
  TH2F *hpixeff2017PreTS256, *hpixeff2017PostTS256;

  TH2F *hstreffB45, *hstreffC45, *hstreffD45, *hstreffE45, *hstreffF45;
  TH2F *hstreffB56, *hstreffC56, *hstreffD56, *hstreffE56, *hstreffF56;
  TH2F *hstreff2017PreTS245, *hstreff2017PostTS245;
  TH2F *hstreff2017PreTS256, *hstreff2017PostTS256;

  TH1F *hmultistreffB45, *hmultistreffC45, *hmultistreffD45, *hmultistreffE45,
      *hmultistreffF45;
  TH1F *hmultistreffB56, *hmultistreffC56, *hmultistreffD56, *hmultistreffE56,
      *hmultistreffF56;
  TH1F *hmultistreff2017PreTS245, *hmultistreff2017PostTS245;
  TH1F *hmultistreff2017PreTS256, *hmultistreff2017PostTS256;

  TRandom *rnd;

  TFile *prefiring2016;
  TFile *prefiring2017;
  TH2F *prefiringmap2016;
  TH2F *prefiringmap2017;

  TString erastring;

  HadronicWWCuts(Int_t mysample = 500, bool protonSyst = false,
                 bool JECSystUp = false, bool JECSystDown = false, 
                 double unitarityCut=999999,double min_mvvCut=0,
                 double gen_xi_min=0,double gen_xi_max=0.4,
                 TTree *tree = 0);
  virtual ~HadronicWWCuts();
  virtual Int_t Cut(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void Init(TTree *tree);
  virtual void Loop();
  virtual Bool_t Notify();
  virtual void Show(Long64_t entry = -1);
};

#endif

#ifdef HadronicWWCuts_cxx
HadronicWWCuts::HadronicWWCuts(Int_t mysample, bool protonSyst,
                 bool JECSystUp, bool JECSystDown, double unitarityCut=999999,double min_mvvCut=0,double gen_xi_min=0,double gen_xi_max=0.4,TTree *tree) : fChain(0) {
  samplenumber = mysample;
  cout << "Opening sample = " << samplenumber << endl;
  this->protonSyst = protonSyst;
  this->JECSystUp = JECSystUp;
  this->JECSystDown = JECSystDown;
  this->unitarityCut = unitarityCut;
  this->min_mvvCut = min_mvvCut;
  this->gen_xi_min = gen_xi_min;
  this->gen_xi_max = gen_xi_max;
  TString mcNtuplesFolder =
      "/eos/cms/store/group/phys_smp/HadronicVV/signalNTuples_v4";

  // TString mcNtuplesFolder =
  //     "/afs/cern.ch/work/a/abellora/Work/PPtoPPWWjets_analysis/newInstall/"
  //     "CMSSW_10_6_17/src/PPtoPPWWjets/PPtoPPWWjets/python/signalNTuples_v4";
  // TString mcNtuplesFolder =
  // "/afs/cern.ch/work/a/abellora/Work/PPtoPPWWjets_analysis/newInstall/CMSSW_10_6_17/src/PPtoPPWWjets/PPtoPPWWjets/python/testrun";

  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = nullptr;
    if (!f || !f->IsOpen()) {
      if (samplenumber == -1)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2017Bv1_17Nov2017_merge.root");
      if (samplenumber == -2)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2017Cv1_17Nov2017_merge.root");
      if (samplenumber == -3)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2017Dv1_17Nov2017_merge.root");
      if (samplenumber == -4)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2017Ev1_17Nov2017_merge.root");
      if (samplenumber == -5)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2017Fv1_17Nov2017_merge.root");

      if (samplenumber == -6)
	f = new TFile("/eos/cms/store/user/kshcheli/16hltfix/"
		      "WWhadronic_JetHT_2016Bver2v1_07Aug2017.root");
      if (samplenumber == -7)
	f = new TFile("/eos/cms/store/user/kshcheli/16hltfix/"
		      "WWhadronic_JetHT_2016Cver2v1_07Aug2017.root");
      if (samplenumber == -8)
        f = new TFile("/eos/cms/store/user/kshcheli/16hltfix/"
                      "WWhadronic_JetHT_2016Gver2v1_07Aug2017.root");
      if (samplenumber == -9)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2016H_v1_07Aug17_merge.root");

      if (samplenumber == -10)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2018A_v1_17Sep2018_merge.root");
      if (samplenumber == -11)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2018B_v1_17Sep2018_merge.root");
      if (samplenumber == -12)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2018C_v1_17Sep2018_merge.root");
      if (samplenumber == -13)
        f = new TFile("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/"
                      "WWhadronic_JetHT_2018D_PromptReco_v2_merge.root");

      // 2017 BG samples

      if (samplenumber == 1)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/"
            "QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root");
      if (samplenumber == 2)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2017_merge.root");
      if (samplenumber == 3)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2017_merge.root");
      if (samplenumber == 4)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2017_merge.root");
      if (samplenumber == 5)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2017_merge.root");
      if (samplenumber == 6)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2017_merge.root");
      if (samplenumber == 7)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "TTbarHadronic_PowhegPythia8_merge.root");
      if (samplenumber == 8)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "WJetsToQQ_HT_800toInf_qc19_3j_TuneCP5_13TeV_MadgraphMLMPythia8."
            "root");
      if (samplenumber == 9)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_MadgraphMLMPythia8.root");
      if (samplenumber == 10)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2017_merge.root");

      // 2017 signal samples

      // 2017 PreTS2
      // SM_WW
      if (samplenumber == 900)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 901)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 902)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_SM_WW_Part1of1.root");
      // WW_A0W5e-7
      if (samplenumber == 400)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 401)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 402)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      // WW_A0W1e-6
      if (samplenumber == 20)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 21)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 22)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      // WW_A0W2e-6
      if (samplenumber == 23)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 24)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 25)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      // WW_A0W3_5e-6
      if (samplenumber == 412)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 413)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 414)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      // WW_A0W5e-6
      if (samplenumber == 26)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 27)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 28)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      // WW_ACW2e-6
      if (samplenumber == 403)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 404)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 405)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      // WW_ACW5e-6
      if (samplenumber == 32)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 33)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 34)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      // WW_ACW8e-6
      if (samplenumber == 35)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 36)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 37)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      // WW_ACW1_4e-5
      if (samplenumber == 415)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 416)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 417)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      // WW_ACW2e-5
      if (samplenumber == 29)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 30)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 31)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      // ZZ_A0Z5e-6
      if (samplenumber == 418)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 419)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 420)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 512)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 513)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      // ZZ_A0Z1e-5
      if (samplenumber == 41)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 66)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 67)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 68)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 69)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      // ZZ_A0Z2e-5
      if (samplenumber == 406)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 407)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 408)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 504)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 505)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      // ZZ_A0Z5e-5
      if (samplenumber == 42)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 70)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 71)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 72)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 73)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      // ZZ_ACZ5e-6
      if (samplenumber == 421)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 422)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 423)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 514)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 515)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      // ZZ_ACZ1e-5
      if (samplenumber == 44)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 78)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 79)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 80)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 81)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      // ZZ_ACZ2e-5
      if (samplenumber == 409)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 410)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 411)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 506)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 507)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      // ZZ_ACZ5e-5
      if (samplenumber == 45)
        f = new TFile(mcNtuplesFolder +
                      "/2017/B/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 82)
        f = new TFile(mcNtuplesFolder +
                      "/2017/C/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 83)
        f = new TFile(mcNtuplesFolder +
                      "/2017/D/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 84)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 85)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");

      // 2017 PostTS2
      // SM_WW
      if (samplenumber == 903)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 904)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_SM_WW_Part1of1.root");
      // WW_A0W5e-7
      if (samplenumber == 500)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 501)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      // WW_A0W1e-6
      if (samplenumber == 50)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 51)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      // WW_A0W2e-6
      if (samplenumber == 52)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 53)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      // WW_A0W3_5e-6
      if (samplenumber == 508)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 509)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      // WW_A0W5e-6
      if (samplenumber == 54)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 55)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      // WW_ACW2e-6
      if (samplenumber == 502)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 503)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      // WW_ACW5e-6
      if (samplenumber == 58)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 59)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      // WW_ACW8e-6
      if (samplenumber == 60)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 61)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      // WW_ACW1_4e-5
      if (samplenumber == 510)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 511)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      // WW_ACW2e-5
      if (samplenumber == 56)
        f = new TFile(mcNtuplesFolder +
                      "/2017/E/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 57)
        f = new TFile(mcNtuplesFolder +
                      "/2017/F/ExclWWjets_WW_ACW2e-5_Part1of1.root");

      // 2016 BG samples

      if (samplenumber == 101)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/"
            "QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root");
      if (samplenumber == 102)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2016_ext_merge.root");
      if (samplenumber == 103)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2016_merge.root");
      if (samplenumber == 104)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2016_merge.root");
      if (samplenumber == 105)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2016_merge.root");
      if (samplenumber == 106)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2016_merge.root");
      if (samplenumber == 107)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "TTbarHadronic_PowhegPythia8_mTT1000toInf_2016_merge.root");
      if (samplenumber == 108)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "WJetsToQQ_HT_600toInf_TuneCP5_13TeV_MadgraphMLMPythia8_2016_merge."
            "root");
      if (samplenumber == 109)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2016_merge.root");
      if (samplenumber == 110)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2016_merge.root");
      if (samplenumber == 111)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinalHLTFix/"
            "TTbarHadronic_PowhegPythia8_mTT700to1000_2016_merge.root");

      // 2016 signal samples

      // 2016 PreTS2
      // SM_WW
      if (samplenumber == 905)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 906)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 907)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_SM_WW_Part1of1.root");
      // WW_A0W5e-7
      if (samplenumber == 300)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 301)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 302)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      // WW_A0W1e-6
      if (samplenumber == 120)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 121)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 122)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      // WW_A0W2e-6
      if (samplenumber == 123)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 124)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 125)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      // WW_A0W3_5e-6
      if (samplenumber == 312)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 313)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 314)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      // WW_A0W5e-6
      if (samplenumber == 126)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 127)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 128)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      // WW_ACW2e-6
      if (samplenumber == 303)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 304)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 305)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      // WW_ACW5e-6
      if (samplenumber == 132)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 133)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 134)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      // WW_ACW8e-6
      if (samplenumber == 135)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 136)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 137)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      // WW_ACW1_4e-5
      if (samplenumber == 315)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 316)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 317)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      // WW_ACW2e-5
      if (samplenumber == 129)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 130)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 131)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      // ZZ_A0Z5e-6
      if (samplenumber == 318)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 319)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 320)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      // ZZ_A0Z1e-5
      if (samplenumber == 141)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 148)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 149)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      // ZZ_A0Z2e-5
      if (samplenumber == 306)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 307)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 308)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      // ZZ_A0Z5e-5
      if (samplenumber == 142)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 150)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 151)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      // ZZ_ACZ5e-6
      if (samplenumber == 321)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 322)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 323)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      // ZZ_ACZ1e-5
      if (samplenumber == 144)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 154)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 155)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      // ZZ_ACZ2e-5
      if (samplenumber == 309)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 310)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 311)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      // ZZ_ACZ5e-5
      if (samplenumber == 145)
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 156)
        f = new TFile(mcNtuplesFolder +
                      "/2016/C/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 157)
        f = new TFile(mcNtuplesFolder +
                      "/2016/G/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");

      // 2018 BG samples

      if (samplenumber == 201)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/"
            "QCD_Pt_170to300_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 202)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 203)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 204)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 205)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 206)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2018_merge.root");
      if (samplenumber == 207)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "TTbarHadronic_PowhegPythia8_2018_merge.root");
      if (samplenumber == 208)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "WJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2018_merge.root");
      if (samplenumber == 209)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2018_merge.root");
      if (samplenumber == 210)
        f = new TFile(
            "/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/"
            "QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2018_merge.root");

      // 2018 signal samples

      // SM_WW
      if (samplenumber == 908)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 909)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 910)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_SM_WW_Part1of1.root");
      if (samplenumber == 911)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_SM_WW_Part1of1.root");
      // WW_A0W5e-7
      if (samplenumber == 600)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 601)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 602)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      if (samplenumber == 603)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_A0W5e-7_Part1of1.root");
      // WW_A0W1e-6
      if (samplenumber == 220)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 221)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 222)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      if (samplenumber == 223)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_A0W1e-6_Part1of1.root");
      // WW_A0W2e-6
      if (samplenumber == 224)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 225)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 226)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      if (samplenumber == 227)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_A0W2e-6_Part1of1.root");
      // WW_A0W3_5e-6
      if (samplenumber == 616)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 617)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 618)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      if (samplenumber == 619)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_A0W3_5e-6_Part1of1.root");
      // WW_A0W5e-6
      if (samplenumber == 228)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 229)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 230)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      if (samplenumber == 231)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_A0W5e-6_Part1of1.root");
      // WW_ACW2e-6
      if (samplenumber == 604)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 605)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 606)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      if (samplenumber == 607)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_ACW2e-6_Part1of1.root");
      // WW_ACW5e-6
      if (samplenumber == 236)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 237)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 238)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      if (samplenumber == 239)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_ACW5e-6_Part1of1.root");
      // WW_ACW5e-6
      if (samplenumber == 240)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 241)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 242)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      if (samplenumber == 243)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_ACW8e-6_Part1of1.root");
      // WW_ACW1_4e-5
      if (samplenumber == 620)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 621)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 622)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      if (samplenumber == 623)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_ACW1_4e-5_Part1of1.root");
      // WW_ACW2e-5
      if (samplenumber == 232)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 233)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 234)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      if (samplenumber == 235)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_WW_ACW2e-5_Part1of1.root");
      // ZZ_A0Z5e-6
      if (samplenumber == 624)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 625)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 626)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      if (samplenumber == 627)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_A0Z5e-6_Part1of1.root");
      // ZZ_A0Z1e-5
      if (samplenumber == 251)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 259)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 260)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      if (samplenumber == 261)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_A0Z1e-5_Part1of1.root");
      // ZZ_A0Z2e-5
      if (samplenumber == 608)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 609)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 610)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      if (samplenumber == 611)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_A0Z2e-5_Part1of1.root");
      // ZZ_A0Z5e-5
      if (samplenumber == 252)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 262)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 263)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      if (samplenumber == 264)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_A0Z5e-5_Part1of1.root");
      // ZZ_ACZ5e-6
      if (samplenumber == 628)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 629)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 630)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      if (samplenumber == 631)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_ACZ5e-6_Part1of1.root");
      // ZZ_ACZ1e-5
      if (samplenumber == 254)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 268)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 269)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      if (samplenumber == 270)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_ACZ1e-5_Part1of1.root");
      // ZZ_ACZ2e-5
      if (samplenumber == 612)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 613)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 614)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      if (samplenumber == 615)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_ACZ2e-5_Part1of1.root");
      // ZZ_ACZ5e-5
      if (samplenumber == 255)
        f = new TFile(mcNtuplesFolder +
                      "/2018/A/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 271)
        f = new TFile(mcNtuplesFolder +
                      "/2018/B/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 272)
        f = new TFile(mcNtuplesFolder +
                      "/2018/C/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");
      if (samplenumber == 273)
        f = new TFile(mcNtuplesFolder +
                      "/2018/D/ExclWWjets_ZZ_ACZ5e-5_Part1of1.root");

      if (samplenumber == 999)
        //	f = new
        // TFile(mcNtuplesFolder+"/2017/B/ExclWWjets_WW_A0W1e-6_Part1of1.root");
        //	f = new
        // TFile(mcNtuplesFolder+"/2018/A/ExclWWjets_WW_A0W1e-6_Part1of1.root");
        f = new TFile(mcNtuplesFolder +
                      "/2016/B/ExclWWjets_WW_A0W1e-6_Part1of1.root");
    }

    if (f->IsOpen())
      cout << "Opened file: " << f->GetName() << endl;
    else{
      cout << "ERROR: file could not be opened"<<endl;
      return 1;
    }

    TDirectory *dir = (TDirectory *)f->Get((TString)f->GetName() + ":/demo");

    // if(samplenumber == -1)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2017Bv1_17Nov2017_merge.root:/demo");
    // if(samplenumber == -2)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2017Cv1_17Nov2017_merge.root:/demo");
    // if(samplenumber == -3)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2017Dv1_17Nov2017_merge.root:/demo");
    // if(samplenumber == -4)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2017Ev1_17Nov2017_merge.root:/demo");
    // if(samplenumber == -5)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2017Fv1_17Nov2017_merge.root:/demo");

    // if(samplenumber == -6)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2016B_ver2v1_07Aug17_merge.root:/demo");
    // if(samplenumber == -7)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2016C_v1_07Aug17_merge.root:/demo");
    // if(samplenumber == -8)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2016G_v1_07Aug17_merge.root:/demo");
    // if(samplenumber == -9)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2016H_v1_07Aug17_merge.root:/demo");

    // if(samplenumber == -10)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2018A_v1_17Sep2018_merge.root:/demo");
    // if(samplenumber == -11)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2018B_v1_17Sep2018_merge.root:/demo");
    // if(samplenumber == -12)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2018C_v1_17Sep2018_merge.root:/demo");
    // if(samplenumber == -13)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/WWhadronic_JetHT_2018D_PromptReco_v2_merge.root:/demo");

    // if(samplenumber == 1)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root:/demo");
    // if(samplenumber == 2)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");
    // if(samplenumber == 3)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");
    // if(samplenumber == 4)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");
    // if(samplenumber == 5)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");
    // if(samplenumber == 6)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");
    // if(samplenumber == 7)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/TTbarHadronic_PowhegPythia8_merge.root:/demo");
    // if(samplenumber == 8)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/WJetsToQQ_HT_800toInf_qc19_3j_TuneCP5_13TeV_MadgraphMLMPythia8.root:/demo");
    // if(samplenumber == 9)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_MadgraphMLMPythia8.root:/demo");
    // if(samplenumber == 10)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2017_merge.root:/demo");

    // if(samplenumber == 20)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W1e-6_2017_preTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 21)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/kshcheli/94X_reMiniAODprotonsJSON/SIGNAL/ExclWWjets_A0W2e-6_2017_preTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 22)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W5e-6_2017_preTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 23)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_ACW2e-5_2017_preTS2_NoPUProtons_Fall17.root:/demo");

    // if(samplenumber == 40)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W1e-6_2017_postTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 42)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W5e-6_2017_postTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 43)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_ACW2e-5_2017_postTS2_NoPUProtons_Fall17.root:/demo");

    // if(samplenumber == 101)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_merge.root:/demo");
    // if(samplenumber == 102)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2016_ext_merge.root:/demo");
    // if(samplenumber == 103)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2016_merge.root:/demo");
    // if(samplenumber == 104)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2016_merge.root:/demo");
    // if(samplenumber == 105)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2016_merge.root:/demo");
    // if(samplenumber == 106)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2016_merge.root:/demo");
    // if(samplenumber == 107)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/TTbarHadronic_PowhegPythia8_mTT1000toInf_2016_merge.root:/demo");
    // if(samplenumber == 108)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/WJetsToQQ_HT_600toInf_TuneCP5_13TeV_MadgraphMLMPythia8_2016_merge.root:/demo");
    // if(samplenumber == 109)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2016_merge.root:/demo");
    // if(samplenumber == 110)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2016_merge.root:/demo");
    // if(samplenumber == 111)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/TTbarHadronic_PowhegPythia8_mTT700to1000_2016_merge.root:/demo");

    // if(samplenumber == 120)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ExclWWjets_A0W1e-6_2016_preTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 122)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ExclWWjets_A0W5e-6_2016preTS2_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 123)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ExclWWjets_ACW2e-5_2016_preTS2_NoPUProtons_Fall17.root:/demo");

    // if(samplenumber == 201)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAOD/QCD_Pt_170to300_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 202)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_300to470_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 203)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_470to600_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 204)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 205)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 206)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");
    // if(samplenumber == 207)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/TTbarHadronic_PowhegPythia8_2018_merge.root:/demo");
    // if(samplenumber == 208)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/WJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2018_merge.root:/demo");
    // if(samplenumber == 209)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV_Madgraph_2018_merge.root:/demo");
    // if(samplenumber == 210)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8_2018_merge.root:/demo");

    // if(samplenumber == 220)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W1e-6_2018_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 222)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal//ExclWWjets_A0W5e-6_2018_NoPUProtons_Fall17.root:/demo");
    // if(samplenumber == 223)
    //   dir =
    //   (TDirectory*)f->Get("/eos/cms/store/user/jjhollar/ExclWWHadronicRun2LegacyFromAODFinal/ExclWWjets_ACW2e-5_2018_NoPUProtons_Fall17.root:/demo");

    // if(samplenumber == 999)
    //   //      dir =
    //   // (TDirectory*)f->Get(mcNtuplesFolder+"/2017/B/ExclWWjets_WW_A0W1e-6_Part1of1.root:/demo");
    //   //      dir =
    //   // (TDirectory*)f->Get(mcNtuplesFolder+"/2018/A/ExclWWjets_WW_A0W1e-6_Part1of1.root:/demo");
    //   dir =
    //   (TDirectory*)f->Get(mcNtuplesFolder+"/2016/B/ExclWWjets_WW_A0W1e-6_Part1of1.root:/demo");

    dir->GetObject("ntp1", tree);
  }
  Init(tree);

  // Setup for efficiency corrections ("killing")
  rnd = new TRandom();
  rnd->SetSeed(123456);

  prefiring2016 = TFile::Open("L1prefiring_jetpt_2016BtoH.root");
  prefiring2017 = TFile::Open("L1prefiring_jetpt_2017BtoF.root");

  prefiringmap2016 = (TH2F *)prefiring2016->Get("L1prefiring_jetpt_2016BtoH");
  prefiringmap2017 = (TH2F *)prefiring2017->Get("L1prefiring_jetpt_2017BtoF");


  Float_t lumi2017B = 2.361;
  Float_t lumi2017C1 = 5.3;
  Float_t lumi2017C2 = 3.3;
  Float_t lumi2017C = 8.577;
  Float_t lumi2017D = 4.075;
  Float_t lumi2017E = 8.948;
  Float_t lumi2017F1 = 1.7;
  Float_t lumi2017F2 = 7.9;
  Float_t lumi2017F3 = 3.6;
  Float_t lumi2017F = 13.214;

  // Pixels - lumi-weighted averages for pre- and post-TS2
  TFile *fpixeff = TFile::Open("/eos/project-c/ctpps/subsystems/Pixel/"
                               "RPixTracking/pixelEfficiencies_multiRP.root");
  hpixeffB45 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017B/h45_220_2017B_all_2D"); // 2.4fb
  hpixeffB56 = (TH2F *)fpixeff->Get("Pixel/2017/2017B/h56_220_2017B_all_2D");
  hpixeffC145 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h45_220_2017C1_all_2D"); // 5.3fb
  hpixeffC156 = (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h56_220_2017C1_all_2D");
  hpixeffC245 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017C2/h45_220_2017C2_all_2D"); // 3.3fb
  hpixeffC256 = (TH2F *)fpixeff->Get("Pixel/2017/2017C2/h56_220_2017C2_all_2D");
  hpixeffD45 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017D/h45_220_2017D_all_2D"); // 4.075fb
  hpixeffD56 = (TH2F *)fpixeff->Get("Pixel/2017/2017D/h56_220_2017D_all_2D");
  hpixeffE45 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017E/h45_220_2017E_all_2D"); // 9fb
  hpixeffE56 = (TH2F *)fpixeff->Get("Pixel/2017/2017E/h56_220_2017E_all_2D");
  hpixeffF145 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h45_220_2017F1_all_2D"); // 1.7fb
  hpixeffF156 = (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h56_220_2017F1_all_2D");
  hpixeffF245 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017F2/h45_220_2017F2_all_2D"); // 7.9fb
  hpixeffF256 = (TH2F *)fpixeff->Get("Pixel/2017/2017F2/h56_220_2017F2_all_2D");
  hpixeffF345 =
      (TH2F *)fpixeff->Get("Pixel/2017/2017F3/h45_220_2017F3_all_2D"); // 1.7fb
  hpixeffF356 = (TH2F *)fpixeff->Get("Pixel/2017/2017F3/h56_220_2017F3_all_2D");

  hpixeffB45->Scale(lumi2017B /
                    (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeffB56->Scale(lumi2017B /
                    (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeffC145->Scale(lumi2017C1 /
                     (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeffC156->Scale(lumi2017C1 /
                     (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeffC245->Scale(lumi2017C2 /
                     (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeffC256->Scale(lumi2017C2 /
                     (lumi2017B + lumi2017C1 + lumi2017C2 + lumi2017D));
  hpixeff2017PreTS245 = (TH2F *)hpixeffB45->Clone("hpixeff2017PreTS245");
  hpixeff2017PreTS256 = (TH2F *)hpixeffB56->Clone("hpixeff2017PreTS256");
  hpixeff2017PreTS245->Add(hpixeffC145);
  hpixeff2017PreTS256->Add(hpixeffC156);
  hpixeff2017PreTS245->Add(hpixeffC245);
  hpixeff2017PreTS256->Add(hpixeffC256);
  hpixeff2017PreTS245->Add(hpixeffD45);
  hpixeff2017PreTS256->Add(hpixeffD56);

  hpixeffE45->Scale(lumi2017E /
                    (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffE56->Scale(lumi2017E /
                    (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF145->Scale(lumi2017F1 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF156->Scale(lumi2017F1 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF245->Scale(lumi2017F2 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF256->Scale(lumi2017F2 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF345->Scale(lumi2017F3 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeffF356->Scale(lumi2017F3 /
                     (lumi2017E + lumi2017F1 + lumi2017F2 + lumi2017F3));
  hpixeff2017PostTS245 = (TH2F *)hpixeffE45->Clone("hpixeff2017PostTS245");
  hpixeff2017PostTS256 = (TH2F *)hpixeffE56->Clone("hpixeff2017PostTS256");
  hpixeff2017PostTS245->Add(hpixeffF145);
  hpixeff2017PostTS256->Add(hpixeffF156);
  hpixeff2017PostTS245->Add(hpixeffF245);
  hpixeff2017PostTS256->Add(hpixeffF256);
  hpixeff2017PostTS245->Add(hpixeffF345);
  hpixeff2017PostTS256->Add(hpixeffF356);

  // Strips - lumi-weighted averages for pre- and post-TS2
  TFile *fstripeff =
      TFile::Open("/eos/project-c/ctpps/subsystems/Strips/StripsTracking/"
                  "PreliminaryEfficiencies_July132020_1D2DMultiTrack.root");
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

  hstreffB45->Scale(lumi2017B / (lumi2017B + lumi2017C + lumi2017D));
  hstreffB56->Scale(lumi2017B / (lumi2017B + lumi2017C + lumi2017D));
  hstreffC45->Scale(lumi2017C / (lumi2017B + lumi2017C + lumi2017D));
  hstreffC56->Scale(lumi2017C / (lumi2017B + lumi2017C + lumi2017D));
  hstreffD45->Scale(lumi2017D / (lumi2017B + lumi2017C + lumi2017D));
  hstreffD56->Scale(lumi2017D / (lumi2017B + lumi2017C + lumi2017D));
  hstreff2017PreTS245 = (TH2F *)hstreffB45->Clone("hstreff2017PreTS245");
  hstreff2017PreTS256 = (TH2F *)hstreffB56->Clone("hstreff2017PreTS256");
  hstreff2017PreTS245->Add(hstreffC45);
  hstreff2017PreTS245->Add(hstreffD45);
  hstreff2017PreTS256->Add(hstreffC56);
  hstreff2017PreTS256->Add(hstreffD56);

  hstreffE45->Scale(lumi2017E / (lumi2017E + lumi2017F));
  hstreffE56->Scale(lumi2017E / (lumi2017E + lumi2017F));
  hstreffF45->Scale(lumi2017F / (lumi2017E + lumi2017F));
  hstreffF56->Scale(lumi2017F / (lumi2017E + lumi2017F));
  hstreff2017PostTS245 = (TH2F *)hstreffE45->Clone("hstreff2017PostTS245");
  hstreff2017PostTS256 = (TH2F *)hstreffE56->Clone("hstreff2017PostTS256");
  hstreff2017PostTS245->Add(hstreffF45);
  hstreff2017PostTS256->Add(hstreffF56);

  // Multi-track for strips
  hmultistreffB45 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017B/h45multitrackeff_2017B_avg_RP3");
  hmultistreffC45 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017C/h45multitrackeff_2017C_avg_RP3");
  hmultistreffD45 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017D/h45multitrackeff_2017D_avg_RP3");
  hmultistreffE45 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017E/h45multitrackeff_2017E_avg_RP3");
  hmultistreffF45 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017F/h45multitrackeff_2017F_avg_RP3");
  hmultistreffB56 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017B/h56multitrackeff_2017B_avg_RP103");
  hmultistreffC56 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017C/h56multitrackeff_2017C_avg_RP103");
  hmultistreffD56 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017D/h56multitrackeff_2017D_avg_RP103");
  hmultistreffE56 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017E/h56multitrackeff_2017E_avg_RP103");
  hmultistreffF56 = (TH1F *)fstripeff->Get(
      "Strips/2017/2017F/h56multitrackeff_2017F_avg_RP103");

  hmultistreffB45->Scale(lumi2017B / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreffB56->Scale(lumi2017B / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreffC45->Scale(lumi2017C / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreffC56->Scale(lumi2017C / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreffD45->Scale(lumi2017D / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreffD56->Scale(lumi2017D / (lumi2017B + lumi2017C + lumi2017D));
  hmultistreff2017PreTS245 =
      (TH1F *)hmultistreffB45->Clone("hmultistreff2017PreTS245");
  hmultistreff2017PreTS256 =
      (TH1F *)hmultistreffB56->Clone("hmultistreff2017PreTS256");
  hmultistreff2017PreTS245->Add(hmultistreffC45);
  hmultistreff2017PreTS245->Add(hmultistreffD45);
  hmultistreff2017PreTS256->Add(hmultistreffC56);
  hmultistreff2017PreTS256->Add(hmultistreffD56);

  hmultistreffE45->Scale(lumi2017E / (lumi2017E + lumi2017F));
  hmultistreffE56->Scale(lumi2017E / (lumi2017E + lumi2017F));
  hmultistreffF45->Scale(lumi2017F / (lumi2017E + lumi2017F));
  hmultistreffF56->Scale(lumi2017F / (lumi2017E + lumi2017F));
  hmultistreff2017PostTS245 =
      (TH1F *)hmultistreffE45->Clone("hmultistreff2017PostTS245");
  hmultistreff2017PostTS256 =
      (TH1F *)hmultistreffE56->Clone("hmultistreff2017PostTS256");
  hmultistreff2017PostTS245->Add(hmultistreffF45);
  hmultistreff2017PostTS256->Add(hmultistreffF56);


}

HadronicWWCuts::~HadronicWWCuts() {
  if (!fChain)
    return;
  delete fChain->GetCurrentFile();
}

Int_t HadronicWWCuts::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain)
    return 0;
  return fChain->GetEntry(entry);
}
Long64_t HadronicWWCuts::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain)
    return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0)
    return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void HadronicWWCuts::Init(TTree *tree) {
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
  if (!tree)
    return;
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
  fChain->SetBranchAddress("pps_track_rpid", &pps_track_rpid,
                           &b_pps_track_rpid);
  fChain->SetBranchAddress("pps_track_time", &pps_track_time,
                           &b_pps_track_time);
  fChain->SetBranchAddress("proton_xi", &proton_xi, &b_proton_xi);
  fChain->SetBranchAddress("proton_thy", &proton_thy, &b_proton_thy);
  fChain->SetBranchAddress("proton_thx", &proton_thx, &b_proton_thx);
  fChain->SetBranchAddress("proton_t", &proton_t, &b_proton_t);
  fChain->SetBranchAddress("proton_ismultirp", &proton_ismultirp,
                           &b_proton_ismultirp);
  fChain->SetBranchAddress("proton_rpid", &proton_rpid, &b_proton_rpid);
  fChain->SetBranchAddress("proton_arm", &proton_arm, &b_proton_arm);
  fChain->SetBranchAddress("proton_time", &proton_time, &b_proton_time);
  fChain->SetBranchAddress("proton_trackx1", &proton_trackx1,
                           &b_proton_trackx1);
  fChain->SetBranchAddress("proton_tracky1", &proton_tracky1,
                           &b_proton_tracky1);
  fChain->SetBranchAddress("proton_trackx2", &proton_trackx2,
                           &b_proton_trackx2);
  fChain->SetBranchAddress("proton_tracky2", &proton_tracky2,
                           &b_proton_tracky2);
  fChain->SetBranchAddress("proton_trackpixshift1", &proton_trackpixshift1,
                           &b_proton_trackpixshift1);
  fChain->SetBranchAddress("proton_trackpixshift2", &proton_trackpixshift2,
                           &b_proton_trackpixshift2);
  fChain->SetBranchAddress("proton_rpid1", &proton_rpid1, &b_proton_rpid1);
  fChain->SetBranchAddress("proton_rpid2", &proton_rpid2, &b_proton_rpid2);
  fChain->SetBranchAddress("gen_jet_pt", &gen_jet_pt, &b_gen_jet_pt);
  fChain->SetBranchAddress("gen_jet_energy", &gen_jet_energy,
                           &b_gen_jet_energy);
  fChain->SetBranchAddress("gen_jet_phi", &gen_jet_phi, &b_gen_jet_phi);
  fChain->SetBranchAddress("gen_jet_eta", &gen_jet_eta, &b_gen_jet_eta);
  fChain->SetBranchAddress("gen_proton_xi", &gen_proton_xi, &b_gen_proton_xi);
  fChain->SetBranchAddress("gen_proton_pz", &gen_proton_pz, &b_gen_proton_pz);
  fChain->SetBranchAddress("gen_puproton_xi", &gen_puproton_xi,
                           &b_gen_puproton_xi);
  fChain->SetBranchAddress("gen_puproton_pz", &gen_puproton_pz,
                           &b_gen_puproton_pz);
  fChain->SetBranchAddress("hlt", &hlt, &b_hlt);
  fChain->SetBranchAddress("nVertices", &nVertices, &b_nVertices);
  fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
  fChain->SetBranchAddress("mc_pu_trueinteractions_", &mc_pu_trueinteractions_,
                           &b_mc_pu_trueinteractions);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumiblock", &lumiblock, &b_lumiblock);
  fChain->SetBranchAddress("crossingangle", &crossingangle, &b_crossingangle);
  Notify();
}

Bool_t HadronicWWCuts::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void HadronicWWCuts::Show(Long64_t entry) {
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain)
    return;
  fChain->Show(entry);
}
Int_t HadronicWWCuts::Cut(Long64_t entry) {
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef HadronicWWCuts_cxx
