// -*- C++ -*-
//
// Package:    PPtoPPWWjets/PPtoPPWWjets
// Class:      PPtoPPWWjets
// 
/**\class PPtoPPWWjets PPtoPPWWjets.cc PPtoPPWWjets/PPtoPPWWjets/plugins/PPtoPPWWjets.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jonathan Jason Hollar
//         Created:  Wed, 01 Aug 2018 09:05:47 GMT
//
//


// system include files
#include <memory>

#include "TTree.h"
#include "TLorentzVector.h"

#include <iostream>       // std::cout
#include <string>         // std::string


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSDetId.h"
#include "DataFormats/ProtonReco/interface/ProtonTrack.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "GeneratorInterface/LHEInterface/interface/LHEEvent.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// For uncorrected jets
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PPtoPPWWjets : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PPtoPPWWjets(const edm::ParameterSet&);
      ~PPtoPPWWjets();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  boost::shared_ptr<FactorizedJetCorrector> jecAK8_;
  std::string jerAK8chsName_res_ ;
  std::string jerAK8chsName_sf_ ;
  edm::EDGetTokenT<edm::View<pat::Jet>> jet_token_;
  edm::EDGetTokenT<std::vector<CTPPSLocalTrackLite> > pps_token_;
  edm::EDGetTokenT<std::vector<reco::ProtonTrack>> reco_protons_token_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertex_token_;
  edm::EDGetTokenT<double> rho_token_;
  edm::EDGetTokenT<edm::TriggerResults> hlt_token_;
  edm::EDGetTokenT<std::vector< PileupSummaryInfo > > pu_token_;
  edm::EDGetTokenT<reco::GenParticleCollection> gen_part_token_;
  edm::EDGetTokenT<reco::GenJetCollection> gen_jet_token_;
  edm::EDGetTokenT< GenEventInfoProduct > geneventToken_; 
  edm::EDGetTokenT<LHEEventProduct > lheEventProductToken_;

  TTree * tree_;


  std::vector<float> * jet_pt_;
  std::vector<float> * jet_energy_;
  std::vector<float> * jet_phi_;
  std::vector<float> * jet_eta_;
  std::vector<float> * jet_uncorr_pt_;
  std::vector<float> * jet_uncorr_energy_;
  std::vector<float> * jet_uncorr_phi_;
  std::vector<float> * jet_uncorr_eta_;

  std::vector<float> * jet_mass_;
  std::vector<float> * jet_tau1_;
  std::vector<float> * jet_tau2_;
  std::vector<float> * jet_corrmass_;
  std::vector<float> * jet_vertexz_;

  std::vector<float> * subjet_ptratio_;
  std::vector<float> * subjet_deltaR_;

  std::vector<float> * dijet_mass_;
  std::vector<float> * dijet_pt_;
  std::vector<float> * dijet_y_;
  std::vector<float> * dijet_phi_;
  std::vector<float> * dijet_dphi_;

  std::vector<float> * pps_track_x_;
  std::vector<float> * pps_track_y_;
  std::vector<int> * pps_track_rpid_;

  std::vector<float> * proton_xi_;
  std::vector<float> * proton_thy_;
  std::vector<float> * proton_thx_;
  std::vector<float> * proton_t_;
  std::vector<int> * proton_ismultirp_;
  std::vector<int> * proton_rpid_;
  std::vector<int> * proton_arm_;

  std::vector<float> * gen_proton_px_;
  std::vector<float> * gen_proton_py_;
  std::vector<float> * gen_proton_pz_;
  std::vector<float> * gen_proton_xi_;
  std::vector<float> * gen_proton_t_;
  std::vector<float> * gen_jet_pt_;
  std::vector<float> * gen_jet_eta_;
  std::vector<float> * gen_jet_phi_;
  std::vector<float> * gen_jet_energy_;
  std::vector<float> * gen_dijet_mass_;
  std::vector<float> * gen_dijet_y_;
  std::vector<float> * jet_jer_res_;
  std::vector<float> * jet_jer_sf_;
  std::vector<float> * jet_jer_sfup_;
  std::vector<float> * jet_jer_sfdown_;

  std::vector<string> * hlt_;

  int  ngenmu_;
  int  ngene_;
  int  ngentau_;

  double genweightFacUp_; 
  double genweightFacDown_;
  double genweightRenUp_; 
  double genweightRenDown_; 
  double genweightFacRenUp_; 
  double genweightFacRenDown_;
  double genpdfRMS_;
  double genweight_;
  double genqscale_;


  int * run_;
  long int * ev_;
  int * lumiblock_;
  int * nVertices_;
  float * pileupWeight_;
  int * mc_pu_trueinteractions_;

  std::string mcPileupFile;
  std::string dataPileupFile;

  HLTConfigProvider hltConfig_;
  HLTPrescaleProvider hltPrescaleProvider_;
  edm::LumiReWeighting *LumiWeights;

  bool isMC;
  int year;
  std::string era;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PPtoPPWWjets::PPtoPPWWjets(const edm::ParameterSet& iConfig) : 
  jet_token_(consumes<edm::View<pat::Jet>>(iConfig.getParameter<edm::InputTag>( "jetAK8CHSCollection" ))),
  // New with jet toolbox
  //  jet_token_(consumes<edm::View<pat::Jet>>(edm::InputTag(("selectedPatJetsAK8PFCHS")))),
  // March 8, 2019 - old default before using jet toolbox for AK8 CHS jets:
  //  jet_token_(consumes<edm::View<pat::Jet>>(edm::InputTag(("slimmedJetsAK8JetId")))),
  pps_token_(consumes<std::vector<CTPPSLocalTrackLite>>(edm::InputTag(("ctppsLocalTrackLiteProducer")))),
  //  pps_token_(consumes<std::vector<CTPPSLocalTrackLite>>(edm::InputTag(("ctppsFastProtonSimulationWithBeamSm")))),
  // 2016 full reco
  //  reco_protons_token_(consumes<std::vector<reco::ProtonTrack>>(edm::InputTag("ctppsProtonReconstruction"))),
  // 2017 full reco
  //  reco_protons_token_(consumes<std::vector<reco::ProtonTrack>>(edm::InputTag("ctppsProtonReconstructionOF"))),
  //  reco_protons_token_(consumes<std::vector<reco::ProtonTrack>>(edm::InputTag("ctppsProtonReconstructionOFDB"))),
  reco_protons_token_(consumes<std::vector<reco::ProtonTrack>>(iConfig.getParameter<edm::InputTag>( "recoProtonsCollection" ))),
  vertex_token_(consumes<std::vector<reco::Vertex>>(edm::InputTag("offlineSlimmedPrimaryVertices"))),
  rho_token_(consumes<double>(edm::InputTag(("fixedGridRhoAll")))),
  hlt_token_(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","","HLT"))),
  pu_token_(consumes<std::vector< PileupSummaryInfo > >(edm::InputTag("slimmedAddPileupInfo"))),
  gen_part_token_(consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"))),
  gen_jet_token_(consumes<reco::GenJetCollection>(edm::InputTag("slimmedGenJetsAK8"))),
  geneventToken_            (consumes<GenEventInfoProduct>(edm::InputTag("generator"))),     
  lheEventProductToken_       (consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"))),     
  hltPrescaleProvider_(iConfig, consumesCollector(), *this)

{
   //now do what ever initialization is needed
   usesResource("TFileService");

   //now do what ever initialization is needed                                                                                                                     

   isMC = iConfig.getParameter<bool>("isMC");
   year = iConfig.getParameter<int>("year");
   era = iConfig.getParameter<std::string>("era");

   if(isMC == true)
     {
       mcPileupFile = iConfig.getParameter<std::string>("mcPileupFile");
       dataPileupFile = iConfig.getParameter<std::string>("dataPileupFile");
       LumiWeights = new edm::LumiReWeighting(mcPileupFile, dataPileupFile, "pileup", "pileup");
     }
                                  
   std::vector<std::string> jecAK8PayloadNames_;

   /* 2017 */
   if(isMC==false && year==2017 && era == "B")
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017B_V32_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017B_V32_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017B_V32_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2017 && era == "C")
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017C_V32_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017C_V32_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017C_V32_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2017 && era == "D")
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2017 && era == "E")
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2017 && era == "F")
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017F_V32_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017F_V32_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017F_V32_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==true && year==2017)
     {
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017_V32_MC_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Fall17_17Nov2017_V32_MC_L3Absolute_AK8PFchs.txt");
     }

   /* 2016 */
   if(isMC==true && year==2016)
     {
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017_V11_MC_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017_V11_MC_L3Absolute_AK8PFchs.txt");
     }
   if(isMC==false && year==2016 && (era == "B" || era == "C" || era == "D"))
     {
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017BCD_V11_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017BCD_V11_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017BCD_V11_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2016 && (era == "E" || era == "F"))
     {
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017EF_V11_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017EF_V11_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017EF_V11_DATA_L2L3Residual_AK8PFchs.txt");
     }
   if(isMC==false && year==2016 && (era == "G" || era == "H"))
     {
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017GH_V11_DATA_L2Relative_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017GH_V11_DATA_L3Absolute_AK8PFchs.txt");
       jecAK8PayloadNames_.push_back("Summer16_07Aug2017GH_V11_DATA_L2L3Residual_AK8PFchs.txt");
     }

   std::vector<JetCorrectorParameters> vPar;
   for ( std::vector<std::string>::const_iterator payloadBegin = jecAK8PayloadNames_.begin(),
	   payloadEnd = jecAK8PayloadNames_.end(),
	   ipayload = payloadBegin; ipayload != payloadEnd; ++ipayload ) {
     JetCorrectorParameters pars(*ipayload);
     vPar.push_back(pars);
   }


   // Make the FactorizedJetCorrector                                                                                                                            
   jecAK8_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );

   // Get JER smearing                                                                                                                                               
   if(isMC==true && year==2017) // Note - here we're using Summer16 for 2017 MC, until the 2017 version is ready
     {                                     
       jerAK8chsName_res_ = "Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt";
       jerAK8chsName_sf_ = "Summer16_25nsV1_MC_SF_AK8PFchs.txt";
     }
   if(isMC==true && year==2016)
     {
       jerAK8chsName_res_ = "Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt";
       jerAK8chsName_sf_ = "Summer16_25nsV1_MC_SF_AK8PFchs.txt";
     }
}


PPtoPPWWjets::~PPtoPPWWjets()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PPtoPPWWjets::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // HLT
   edm::Handle<edm::TriggerResults> hltResults;
   iEvent.getByToken(hlt_token_,hltResults);
   const edm::TriggerNames & trigNames = iEvent.triggerNames(*hltResults);
   for(unsigned int i=0; i<trigNames.size();i++)
     {
       int prescale_value=hltPrescaleProvider_.prescaleValue(iEvent, iSetup,trigNames.triggerName(i));
       //       int result = hltResults->accept(i);
       std::string TriggerName = trigNames.triggerName(i);
       if((hltResults->accept(i)>0)&&(prescale_value==1))
	 {
	   (*hlt_).push_back(TriggerName);
	 }
     }
   

   //Get Vertices and rho                                                                                                                                        
   edm::Handle< std::vector<reco::Vertex> > vertices_;
   iEvent.getByToken(vertex_token_, vertices_);

   edm::Handle<double> rhoHandle;
   iEvent.getByToken(rho_token_,rhoHandle);
   double rho = *rhoHandle; 


   // Get ak8Jets
   edm::Handle<edm::View<pat::Jet>> jets;
   iEvent.getByToken(jet_token_, jets);
   unsigned int collSize=jets->size();
   TLorentzVector jet1, jet2, jj;

   JME::JetResolution resolution_ak8;
   JME::JetResolutionScaleFactor resolution_ak8_sf;
   if(isMC == true)
     {
       resolution_ak8 = JME::JetResolution(jerAK8chsName_res_);
       resolution_ak8_sf = JME::JetResolutionScaleFactor(jerAK8chsName_sf_);
     }

   for (unsigned int ijet=0; ijet<collSize; ijet++) 
     {
       pat::Jet jet = (*jets)[ijet];;

       if(jet.pt() < 200)
	 continue;

       // CMSSW_8_X samples
       //       double pruned_mass = (*jets)[ijet].userFloat("ak8PFJetsCHSPrunedMass");
       //       double tau1         = (*jets)[ijet].userFloat("NjettinessAK8:tau1");
       //       double tau2         = (*jets)[ijet].userFloat("NjettinessAK8:tau2");

       // CMSSW_9_4_X
       double pruned_mass = 0.0;
       double tau1 = 0.0;
       double tau2 = 0.0;
       if(year == 2017)
	 {
	   // V8 JEC, V32?
	   //	   pruned_mass       = (*jets)[ijet].userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass");
	   //	   tau1         = (*jets)[ijet].userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau1");
	   //	   tau2         = (*jets)[ijet].userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau2");
	   // March 8, 2019 - From jet toolbox
	   pruned_mass       = (*jets)[ijet].userFloat("ak8PFJetsCHSPrunedMass");
	   tau1              = (*jets)[ijet].userFloat("NjettinessAK8CHS:tau1");
	   tau2              = (*jets)[ijet].userFloat("NjettinessAK8CHS:tau2");
	 }
       if(year == 2016)
	 {
	   pruned_mass       = (*jets)[ijet].userFloat("ak8PFJetsCHSPrunedMass");
	   tau1         = (*jets)[ijet].userFloat("NjettinessAK8:tau1");
	   tau2         = (*jets)[ijet].userFloat("NjettinessAK8:tau2");
	 }

       (*jet_pt_).push_back(jet.pt());
       (*jet_phi_).push_back(jet.phi());
       (*jet_eta_).push_back(jet.eta());
       (*jet_energy_).push_back(jet.energy());
       (*jet_mass_).push_back(pruned_mass);
       (*jet_tau1_).push_back(tau1);
       (*jet_tau2_).push_back(tau2);
       (*jet_vertexz_).push_back(jet.vz());

       // Now apply pruned mass corrections to the uncorrected jets!
       //       const LorentzVector uncorrJet = (*jets)[ijet].correctedP4(0);
       LorentzVector uncorrJet = (*jets)[ijet].correctedP4(0);
       double pruned_masscorr = 0;
       double corr = 0;

       (*jet_uncorr_pt_).push_back(uncorrJet.pt());
       (*jet_uncorr_phi_).push_back(uncorrJet.phi());
       (*jet_uncorr_eta_).push_back(uncorrJet.eta());
       (*jet_uncorr_energy_).push_back(uncorrJet.energy());


       jecAK8_->setJetEta( uncorrJet.eta() );
       jecAK8_->setJetPt ( uncorrJet.pt() );
       jecAK8_->setJetE  ( uncorrJet.energy() );
       jecAK8_->setJetA  ( jet.jetArea() );
       jecAK8_->setRho   ( rho );
       jecAK8_->setNPV   ( vertices_->size() );
       corr = jecAK8_->getCorrection();
       pruned_masscorr = corr*pruned_mass;
       (*jet_corrmass_).push_back(pruned_masscorr);

       // JER
       if(isMC == true)
	 {
	   JME::JetParameters parameters_ak8;
	   parameters_ak8.setJetPt(jet.pt());
	   parameters_ak8.setJetEta(jet.eta());
	   parameters_ak8.setRho(rho);
      
	   float jer_res= resolution_ak8.getResolution(parameters_ak8);
	   float jer_sf = resolution_ak8_sf.getScaleFactor(parameters_ak8);
	   float jer_sf_up = resolution_ak8_sf.getScaleFactor(parameters_ak8, Variation::UP);
	   float jer_sf_down = resolution_ak8_sf.getScaleFactor(parameters_ak8, Variation::DOWN);

	   (*jet_jer_res_).push_back(jer_res);
	   (*jet_jer_sf_).push_back(jer_sf);
	   (*jet_jer_sfup_).push_back(jer_sf_up);
           (*jet_jer_sfdown_).push_back(jer_sf_down);
	 }

       // Now access subjet variables for this jet
       int nsj = 0;  
       TLorentzVector sja,sjb;
       
       auto wSubjets = jet.subjets("Pruned");
       for ( auto const & iw : wSubjets ) 
	 {
	   if(nsj==0 ){
	     sja.SetPtEtaPhiE(iw->correctedP4(0).pt(),iw->correctedP4(0).eta(),iw->correctedP4(0).phi(),iw->correctedP4(0).e());
	   }
	   if(nsj==1 )
	     {
	       sjb.SetPtEtaPhiE(iw->correctedP4(0).pt(),iw->correctedP4(0).eta(),iw->correctedP4(0).phi(),iw->correctedP4(0).e());
	       (*subjet_ptratio_).push_back(sja.Pt()/sjb.Pt());
	       (*subjet_deltaR_).push_back(sja.DeltaR(sjb));
	     }
	   nsj++;
	 }

     }

   // If at least 2 jets, make dijet pairs of the leading 2
   if(collSize >= 2)
     {
       jet1.SetPtEtaPhiM((*jet_pt_)[0],(*jet_eta_)[0],(*jet_phi_)[0],(*jet_corrmass_)[0]);
       jet2.SetPtEtaPhiM((*jet_pt_)[1],(*jet_eta_)[1],(*jet_phi_)[1],(*jet_corrmass_)[1]);
       jj = jet1+jet2;


       (*dijet_mass_).push_back(jj.M());
       (*dijet_y_).push_back(jj.Rapidity());
       (*dijet_pt_).push_back(jj.Pt());
       (*dijet_phi_).push_back(jj.Phi());
       float dphi = (*dijet_phi_)[0]-(*dijet_phi_)[1];
       if(dphi < 3.14159)
	 (*dijet_dphi_).push_back(dphi);
       else
	 (*dijet_dphi_).push_back((2*3.14159)-dphi);
     }

   // Proton lite tracks
   //   if((isMC==false) || (year!=2016))
   if(isMC==false)
     {
       edm::Handle<std::vector<CTPPSLocalTrackLite> > ppsTracks;
       iEvent.getByToken( pps_token_, ppsTracks );
       
       for ( const auto& trk : *ppsTracks ) 
	 {
	   const CTPPSDetId detid( trk.getRPId() );
	   
	   // transform the raw, 32-bit unsigned integer detId into the TOTEM "decimal" notation
	   const unsigned short raw_id = 100*detid.arm()+10*detid.station()+detid.rp();

	   (*pps_track_x_).push_back(trk.getX());
	   (*pps_track_y_).push_back(trk.getY());
	   (*pps_track_rpid_).push_back(raw_id);
	 }
       
       // Full reco protons
       edm::Handle<vector<reco::ProtonTrack>> recoProtons;
       iEvent.getByToken(reco_protons_token_, recoProtons);
       
       // make single-RP-reco plots                                                                                                                                         
       for (const auto & proton : *recoProtons)
	 {
	   int ismultirp = -999;
	   unsigned int decRPId = -999;
	   unsigned int armId = -999;
	   float th_y = -999;
	   float th_x = -999;
	   float t = -999;
	   float xi = -999;
	   
	   if (proton.valid())
	     {
	       th_y = (proton.direction().y()) / (proton.direction().mag());
	       th_x = (proton.direction().x()) / (proton.direction().mag());
	       xi = proton.xi();
	       
	       // t
	       const double m = 0.938; // GeV                                                                                                                                               
	       const double p = 6500.; // GeV                                                                                                                                               
	       
	       float t0 = 2.*m*m + 2.*p*p*(1.-xi) - 2.*sqrt( (m*m + p*p) * (m*m + p*p*(1.-xi)*(1.-xi)) );
	       float th = sqrt(th_x * th_x + th_y * th_y);
	       float S = sin(th/2.);
	       t = t0 - 4. * p*p * (1.-xi) * S*S;
	       
	       if (proton.method == reco::ProtonTrack::rmSingleRP)
		 {
		   CTPPSDetId rpId(* proton.contributingRPIds.begin());
		   decRPId = rpId.arm()*100 + rpId.station()*10 + rpId.rp();                                                                
		   ismultirp = 0;
		 }
	       if (proton.method == reco::ProtonTrack::rmMultiRP)
		 {
		   CTPPSDetId rpId(* proton.contributingRPIds.begin());
		   armId = rpId.arm();                                                                                                      
		   ismultirp = 1;
		 }

	       (*proton_xi_).push_back(proton.xi());
	       (*proton_thy_).push_back(th_y);
	       (*proton_thx_).push_back(th_x);
	       (*proton_t_).push_back(t);
	       (*proton_ismultirp_).push_back(ismultirp);
	       (*proton_rpid_).push_back(decRPId);
	       (*proton_arm_).push_back(armId);
	     }
	 }
     }

   // Run and vertex multiplicity info
   *run_ = iEvent.id().run();
   *ev_ = iEvent.id().event();
   *lumiblock_ = iEvent.luminosityBlock();

   *nVertices_=-1;
   *nVertices_=vertices_->size();

   // Fill pileup reweighting info if running on MC
   *pileupWeight_=1;
   *mc_pu_trueinteractions_=-1;
   if(isMC == true)
     {
       float trueInteractions=0;
       edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
       iEvent.getByToken(pu_token_, PupInfo);
       std::vector<PileupSummaryInfo>::const_iterator PVI;
       //cout<<"True num interactions is: "<<PupInfo->begin()->getTrueNumInteractions()<<endl;                                                              
       trueInteractions=PupInfo->begin()->getTrueNumInteractions();
       *pileupWeight_ = LumiWeights->weight( trueInteractions );
       *mc_pu_trueinteractions_ = trueInteractions;
     }

   // Fill GEN infor if running on MC
   if(isMC == true)
     {
       ngenmu_ = 0;
       ngene_ = 0;
       ngentau_ = 0;

       genweightFacUp_ = 0;
       genweightFacDown_ = 0;
       genweightRenUp_ = 0;
       genweightRenDown_ = 0;
       genweightFacRenUp_ = 0;
       genweightFacRenDown_ = 0;
       genpdfRMS_ = 0;
       genweight_ = 0;
       genqscale_ = 0;


       edm::Handle<reco::GenParticleCollection> genP;
       iEvent.getByLabel("prunedGenParticles",genP);

       for (reco::GenParticleCollection::const_iterator mcIter=genP->begin(); mcIter != genP->end(); mcIter++ ) {
	 if((mcIter->pdgId() == 2212) && (fabs(mcIter->pz()) > 3000) && (mcIter->status() == 1))
	   {
	     double thexi = 1 - ((mcIter->energy())/(13000.0/2.0));
	     double thet = -(std::pow(mcIter->pt(), 2));
	     double thepz = mcIter->pz();
	     double thepx = mcIter->px();
	     double thepy = mcIter->py();

	     (*gen_proton_xi_).push_back(thexi);
	     (*gen_proton_t_).push_back(thet);
	     (*gen_proton_pz_).push_back(thepz);
	     (*gen_proton_py_).push_back(thepy);
	     (*gen_proton_px_).push_back(thepx);
	   }
	 
	 if(fabs(mcIter->pdgId()) == 11 && fabs(mcIter->mother()->pdgId()) == 24)
	   ngene_++;
         if(fabs(mcIter->pdgId()) == 13 && fabs(mcIter->mother()->pdgId()) == 24)
	   ngenmu_++;
         if(fabs(mcIter->pdgId()) == 15 && fabs(mcIter->mother()->pdgId()) == 24)
	   ngentau_++;
       }

       edm::Handle<reco::GenJetCollection> genJet;
       iEvent.getByLabel("slimmedGenJetsAK8",genJet);

       TLorentzVector genjet1, genjet2, genjj;

       for (reco::GenJetCollection::const_iterator genJetIter=genJet->begin(); genJetIter != genJet->end(); genJetIter++ ) {
	 (*gen_jet_pt_).push_back(genJetIter->pt());
	 (*gen_jet_phi_).push_back(genJetIter->phi());
	 (*gen_jet_eta_).push_back(genJetIter->eta());
	 (*gen_jet_energy_).push_back(genJetIter->energy());
       }
       genjet1.SetPtEtaPhiE((*gen_jet_pt_)[0],(*gen_jet_eta_)[0],(*gen_jet_phi_)[0],(*gen_jet_energy_)[0]);
       genjet2.SetPtEtaPhiE((*gen_jet_pt_)[1],(*gen_jet_eta_)[1],(*gen_jet_phi_)[1],(*gen_jet_energy_)[1]);
       genjj = genjet1+genjet2;
       (*gen_dijet_mass_).push_back(genjj.M());
       (*gen_dijet_y_).push_back(genjj.Rapidity());

       // JH - not in MiniAOD?
       if(0)
	 {
	   // GEN Event info for pdf/scale/etc. systematics - from https://github.com/UZHCMS/EXOVVNtuplizerRunII
	   edm::Handle< GenEventInfoProduct >  geneventInfo_;
	   edm::Handle<LHEEventProduct> lheEventProduct_;
	   iEvent.getByToken(lheEventProductToken_, lheEventProduct_);
	   iEvent.getByToken(geneventToken_, geneventInfo_);  
	   genweight_ = geneventInfo_->weight();
	   genqscale_ = geneventInfo_->qScale();
	   
	   const LHEEventProduct* Product = lheEventProduct_.product();
	   
	   if(Product->weights().size() >= 9) {
	     genweightFacUp_ = Product->weights()[1].wgt / Product->originalXWGTUP();
	     genweightFacDown_ = Product->weights()[2].wgt / Product->originalXWGTUP();
	     genweightRenUp_ = Product->weights()[3].wgt / Product->originalXWGTUP();
	     genweightRenDown_ = Product->weights()[6].wgt / Product->originalXWGTUP();
	     genweightFacRenUp_ = Product->weights()[4].wgt / Product->originalXWGTUP();
	     genweightFacRenDown_ = Product->weights()[8].wgt / Product->originalXWGTUP();
	   }    
	   std::vector<double> pdfWeights;
	   for(unsigned int i = 10; i <= 110 && i < Product->weights().size(); i++) {
	     pdfWeights.push_back(Product->weights()[i].wgt / Product->originalXWGTUP());
	   }
	   // Calculate RMS
	   if(pdfWeights.size() > 0) {
	     double sum = std::accumulate(pdfWeights.begin(), pdfWeights.end(), 0.0);
	     double mean = sum / pdfWeights.size();
	     
	     double sq_sum = std::inner_product(pdfWeights.begin(), pdfWeights.end(), pdfWeights.begin(), 0.0);
	     genpdfRMS_ = std::sqrt(sq_sum / pdfWeights.size() - mean * mean);
	   }
	 }
     }

   

   /*
   std::cout << "JH: Filling tree!" << std::endl;
   std::cout << "\tJH: pps_track_rpid_.size() = " << pps_track_rpid_->size() << std::endl
	     << "\tJH: jet_pt_.size() = " << jet_pt_->size() << std::endl
	     << "\tJH: dijet_phi_.size() = " << dijet_phi_->size() << std::endl;
   */

   tree_->Fill();

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif

   (*jet_pt_).clear();
   (*jet_energy_).clear();
   (*jet_phi_).clear();
   (*jet_eta_).clear();
   (*jet_uncorr_pt_).clear();
   (*jet_uncorr_energy_).clear();
   (*jet_uncorr_phi_).clear();
   (*jet_uncorr_eta_).clear();

   (*jet_mass_).clear();
   (*jet_tau1_).clear();
   (*jet_tau2_).clear();
   (*jet_corrmass_).clear();
   (*jet_vertexz_).clear();

   (*subjet_ptratio_).clear();
   (*subjet_deltaR_).clear();

   (*dijet_mass_).clear();
   (*dijet_y_).clear();
   (*dijet_phi_).clear();
   (*dijet_pt_).clear();
   (*dijet_dphi_).clear();

   (*pps_track_x_).clear();
   (*pps_track_y_).clear();
   (*pps_track_rpid_).clear();

   (*proton_xi_).clear();
   (*proton_thy_).clear();
   (*proton_thx_).clear();
   (*proton_t_).clear();
   (*proton_ismultirp_).clear();
   (*proton_rpid_).clear();
   (*proton_arm_).clear();

   if(isMC == true)
     {
       (*gen_proton_px_).clear();
       (*gen_proton_py_).clear();
       (*gen_proton_pz_).clear();
       (*gen_proton_xi_).clear();
       (*gen_proton_t_).clear();
       (*gen_jet_pt_).clear();
       (*gen_jet_eta_).clear();
       (*gen_jet_phi_).clear();
       (*gen_jet_energy_).clear();
       (*gen_dijet_mass_).clear();
       (*gen_dijet_y_).clear();

       (*jet_jer_res_).clear();
       (*jet_jer_sf_).clear();
       (*jet_jer_sfup_).clear();
       (*jet_jer_sfdown_).clear();
     }

   (*hlt_).clear();

}


// ------------ method called once each job just before starting event loop  ------------
void 
PPtoPPWWjets::beginJob()
{

  edm::Service<TFileService> fs;
  tree_=fs->make<TTree>("ntp1","ntp1");


  jet_pt_ = new std::vector<float>;
  jet_energy_ = new std::vector<float>;
  jet_phi_ = new std::vector<float>;
  jet_eta_ = new std::vector<float>;
  jet_mass_ = new std::vector<float>;
  jet_tau1_ = new std::vector<float>;
  jet_tau2_ = new std::vector<float>;
  jet_corrmass_ = new std::vector<float>;
  jet_vertexz_ = new std::vector<float>;
  jet_uncorr_pt_ = new std::vector<float>;
  jet_uncorr_energy_ = new std::vector<float>;
  jet_uncorr_phi_ = new std::vector<float>;
  jet_uncorr_eta_ = new std::vector<float>;

  subjet_ptratio_ = new std::vector<float>;
  subjet_deltaR_ = new std::vector<float>;

  dijet_mass_ = new std::vector<float>;
  dijet_pt_ = new std::vector<float>;
  dijet_y_ = new std::vector<float>;
  dijet_phi_ = new std::vector<float>;
  dijet_dphi_ = new std::vector<float>;

  pps_track_x_ = new std::vector<float>;
  pps_track_y_ = new std::vector<float>;
  pps_track_rpid_ = new std::vector<int>;

  proton_xi_ = new std::vector<float>;
  proton_thy_ = new std::vector<float>;
  proton_thx_ = new std::vector<float>;
  proton_t_ = new std::vector<float>;
  proton_ismultirp_ = new std::vector<int>;
  proton_rpid_ = new std::vector<int>;
  proton_arm_ = new std::vector<int>;

  gen_proton_px_ = new std::vector<float>;
  gen_proton_py_ = new std::vector<float>;
  gen_proton_pz_ = new std::vector<float>;
  gen_proton_xi_ = new std::vector<float>;
  gen_proton_t_ = new std::vector<float>;
  gen_jet_pt_ = new std::vector<float>;
  gen_jet_eta_ = new std::vector<float>;
  gen_jet_phi_ = new std::vector<float>;
  gen_jet_energy_ = new std::vector<float>;
  gen_dijet_mass_ = new std::vector<float>;
  gen_dijet_y_ = new std::vector<float>;

  jet_jer_res_ = new std::vector<float>;
  jet_jer_sf_ = new std::vector<float>;
  jet_jer_sfup_ = new std::vector<float>;
  jet_jer_sfdown_ = new std::vector<float>;

  hlt_ = new std::vector<string>;

  ev_ = new long int;
  run_ = new int;
  lumiblock_ = new int;
  nVertices_ = new int;
  pileupWeight_ = new float;
  mc_pu_trueinteractions_ = new int;

  tree_->Branch("jet_pt",&jet_pt_);
  tree_->Branch("jet_energy",&jet_energy_);
  tree_->Branch("jet_phi",&jet_phi_);
  tree_->Branch("jet_eta",&jet_eta_);
  tree_->Branch("jet_uncorr_pt",&jet_uncorr_pt_);
  tree_->Branch("jet_uncorr_energy",&jet_uncorr_energy_);
  tree_->Branch("jet_uncorr_phi",&jet_uncorr_phi_);
  tree_->Branch("jet_uncorr_eta",&jet_uncorr_eta_);
  tree_->Branch("jet_mass",&jet_mass_);
  tree_->Branch("jet_tau1",&jet_tau1_);
  tree_->Branch("jet_tau2",&jet_tau2_);
  tree_->Branch("jet_corrmass",&jet_corrmass_);
  tree_->Branch("jet_vertexz",&jet_vertexz_);
  tree_->Branch("subjet_ptratio",&subjet_ptratio_);
  tree_->Branch("subjet_deltaR",&subjet_deltaR_);
  tree_->Branch("dijet_mass",&dijet_mass_);
  tree_->Branch("dijet_pt",&dijet_pt_);
  tree_->Branch("dijet_y",&dijet_y_);
  tree_->Branch("dijet_phi",&dijet_phi_);
  tree_->Branch("dijet_dphi",&dijet_dphi_);
  tree_->Branch("pps_track_x",&pps_track_x_);
  tree_->Branch("pps_track_y",&pps_track_y_);
  tree_->Branch("pps_track_rpid",&pps_track_rpid_);
  tree_->Branch("proton_xi",&proton_xi_);
  tree_->Branch("proton_thy",&proton_thy_);
  tree_->Branch("proton_thx",&proton_thx_);
  tree_->Branch("proton_t",&proton_t_);
  tree_->Branch("proton_ismultirp",&proton_ismultirp_);
  tree_->Branch("proton_rpid",&proton_rpid_);
  tree_->Branch("proton_arm",&proton_arm_);

  tree_->Branch("hlt",&hlt_);

  if(isMC == true)
    {
      tree_->Branch("gen_proton_px",&gen_proton_px_);
      tree_->Branch("gen_proton_py",&gen_proton_py_);
      tree_->Branch("gen_proton_pz",&gen_proton_pz_);
      tree_->Branch("gen_proton_xi",&gen_proton_xi_);
      tree_->Branch("gen_proton_t",&gen_proton_t_);
      tree_->Branch("gen_jet_pt",&gen_jet_pt_);
      tree_->Branch("gen_jet_eta",&gen_jet_eta_);
      tree_->Branch("gen_jet_phi",&gen_jet_phi_);
      tree_->Branch("gen_jet_energy",&gen_jet_energy_);
      tree_->Branch("gen_dijet_mass",&gen_dijet_mass_);
      tree_->Branch("gen_dijet_y",&gen_dijet_y_);

      tree_->Branch("jet_jer_res",&jet_jer_res_);
      tree_->Branch("jet_jer_sf",&jet_jer_sf_);
      tree_->Branch("jet_jer_sfup",&jet_jer_sfup_);
      tree_->Branch("jet_jer_sfdown",&jet_jer_sfdown_);

      tree_->Branch("gen_n_e",&ngene_,"gen_n_e/I");
      tree_->Branch("gen_n_mu",&ngenmu_,"gen_n_mu/I");
      tree_->Branch("gen_n_tau",&ngentau_,"gen_n_tau/I");

      tree_->Branch("gen_weight_FacUp",&genweightFacUp_,"gen_weight_FacUp/D");
      tree_->Branch("gen_weight_FacDown",&genweightFacDown_,"gen_weight_FacDown/D");
      tree_->Branch("gen_weight_RenUp",&genweightRenUp_,"gen_weight_RenUp/D");
      tree_->Branch("gen_weight_RenDown",&genweightRenDown_,"gen_weight_RenDown/D");
      tree_->Branch("gen_weight_FacRenUp",&genweightFacRenUp_,"gen_weight_FacRenUp/D");
      tree_->Branch("gen_weight_FacRenDown",&genweightFacRenDown_,"gen_weight_FacRenDown/D");
      tree_->Branch("gen_pdf_RMS",&genpdfRMS_,"gen_pdf_RMS/D");
      tree_->Branch("gen_weight",&genweight_,"gen_weight/D");
      tree_->Branch("gen_q_scale",&genqscale_,"gen_q_scale/D");

    }

  tree_->Branch("nVertices",nVertices_,"nVertices/i");
  tree_->Branch("pileupWeight",pileupWeight_,"pileupWeight/f");
  tree_->Branch("mc_pu_trueinteractions_",mc_pu_trueinteractions_,"mc_pu_trueinteractions/i");
  tree_->Branch("run",run_,"run/I");
  tree_->Branch("event",ev_,"event/L");
  tree_->Branch("lumiblock",lumiblock_,"lumiblock/I");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
PPtoPPWWjets::endJob() 
{
  delete jet_pt_;
  delete jet_energy_;
  delete jet_phi_;
  delete jet_eta_;
  delete jet_uncorr_pt_;
  delete jet_uncorr_energy_;
  delete jet_uncorr_phi_;
  delete jet_uncorr_eta_;
  delete jet_mass_;
  delete jet_tau1_;
  delete jet_tau2_;
  delete jet_corrmass_;
  delete jet_vertexz_;
  delete subjet_ptratio_;
  delete subjet_deltaR_;
  delete dijet_mass_;
  delete dijet_pt_;
  delete dijet_y_;
  delete dijet_phi_;
  delete dijet_dphi_;
  delete pps_track_x_;
  delete pps_track_y_;
  delete pps_track_rpid_;
  delete proton_xi_;
  delete proton_thy_;
  delete proton_thx_;
  delete proton_t_;
  delete proton_ismultirp_;
  delete proton_rpid_;
  delete proton_arm_;
  delete gen_proton_px_;
  delete gen_proton_py_;
  delete gen_proton_pz_;
  delete gen_proton_xi_;
  delete gen_proton_t_;
  delete gen_jet_pt_;
  delete gen_jet_eta_;
  delete gen_jet_phi_;
  delete gen_jet_energy_;
  delete gen_dijet_mass_;
  delete gen_dijet_y_;
  delete jet_jer_res_;
  delete jet_jer_sf_;
  delete jet_jer_sfup_;
  delete jet_jer_sfdown_;

  delete hlt_;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PPtoPPWWjets::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PPtoPPWWjets);
