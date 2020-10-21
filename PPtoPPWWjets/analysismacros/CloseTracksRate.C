#include <FWCore/Utilities/interface/Exception.h>

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"

using namespace std;

// Compute how often do we get a track in the strips dmg region and another out
// of it
void CloseTracksRate() {

  // Input files
  vector<string> inputFiles = {
      "/afs/cern.ch/user/a/abellora/eosctpps/subsystems/Pixel/"
      "ReMiniAODSkimForEfficiencies/2018ReMiniAODSkimForEff_SingleEle_2018A/"
      "EGamma/ReMiniAODSkimForEff_SingleEle_2018A/200925_171447/0000/"
      "ReMiniAOD_SkimForEfficiency_1.root"

  };

  // Events to be analyzed
  int nEvents = 1e6;

  // x cut for tracks to be analyzed
  double xMin = 2.5; // mm
  double xMax = 5;   // mm
  double yMin = -1;  // mm
  double yMax = 1;   // mm

  // Binnings for maps
  int mapXbins = 200;
  float mapXmin = 0. * TMath::Cos(18.4 / 180. * TMath::Pi());
  float mapXmax = 30. * TMath::Cos(18.4 / 180. * TMath::Pi());
  int mapYbins = 240;
  float mapYmin = -16.;
  float mapYmax = 8.;
  float fitXmin = 45.;
  float fitXmax = 58.;

  // Create event handler
  fwlite::ChainEvent ev(inputFiles);

  // Get the tracklites
  fwlite::Handle<vector<CTPPSLocalTrackLite>> trackLitesHandle;

  TFile *outputFile = new TFile("CloseTracks.root", "RECREATE");

  // Strips radiation efficiency file
  TFile *stripsEfficiencyFile =
      new TFile("/eos/project/c/ctpps/subsystems/Strips/StripsTracking/"
                "PreliminaryEfficiencies_July132020_1D2DMultiTrack.root");
  map<CTPPSPixelDetId, TH2D *> h2StripsEfficiencies = {
      {CTPPSPixelDetId(0, 0, 3), (TH2D *)stripsEfficiencyFile->Get(
                                     "Strips/2017/2017F3/h45_2017F3_all_2D")},

      {CTPPSPixelDetId(1, 0, 3), (TH2D *)stripsEfficiencyFile->Get(
                                     "Strips/2017/2017F3/h56_2017F3_all_2D")},
  };

  // Maps containing histograms
  vector<CTPPSPixelDetId> detIdVector;
  map<CTPPSPixelDetId, TH1D *> h1Mux;
  map<CTPPSPixelDetId, TH2D *> h2TrackHitDistribution;
  map<CTPPSPixelDetId, TH2D *> h2DamageRegionTracks;
  map<CTPPSPixelDetId, TH2D *> h2SecondTracks;

  int eventsWithAtLeastOneTrackPerArm = 0;
  map<CTPPSPixelDetId, int> interestingEvents;

  int eventCounter = 0;
  for (ev.toBegin(); !ev.atEnd(); ++ev) {
    if (eventCounter % 1000 == 0)
      cout << "Events analyzed: " << eventCounter << endl;
    if (nEvents > 0 && eventCounter >= nEvents)
      break;

    map<CTPPSPixelDetId, int> mux;
    map<CTPPSPixelDetId, bool> isInterestingEvent;

    // Get the tracklites in the event
    trackLitesHandle.getByLabel(ev, "ctppsLocalTrackLiteProducer", "",
                                "ReMiniAOD");
    vector<CTPPSLocalTrackLite> trackLites = *(trackLitesHandle.ptr());

    // Iterate over the tracklites of each event
    for (auto trackLite : trackLites) {
      // Exclude timing tracks
      if (CTPPSDetId(trackLite.getRPId()).station() == 1)
        continue;
      CTPPSPixelDetId detId = CTPPSPixelDetId(trackLite.getRPId());
      int arm = detId.arm();
      int station = detId.station();

      double x = trackLite.getX();
      double y = trackLite.getY();

      // Insert the detId in the detId vector and book histograms
      if (find(detIdVector.begin(), detIdVector.end(), detId) ==
          detIdVector.end()) {
        detIdVector.push_back(detId);
        h1Mux[detId] =
            new TH1D(Form("h1Mux_arm%i_st%i", arm, station),
                     Form("h1Mux_arm%i_st%i;Track multiplicity", arm, station),
                     11, 0, 11);
        h2TrackHitDistribution[detId] =
            new TH2D(Form("h2TrackHitDistribution_arm%i_st%i", arm, station),
                     Form("h2TrackHitDistribution_arm%i_st%i;x (mm);y (mm)",
                          arm, station),
                     mapXbins, mapXmin, mapXmax, mapYbins, mapYmin, mapYmax);
        h2DamageRegionTracks[detId] = new TH2D(
            Form("h2DamageRegionTracks_arm%i_st%i", arm, station),
            Form("h2DamageRegionTracks_arm%i_st%i;x (mm);y (mm)", arm, station),
            mapXbins, mapXmin, mapXmax, mapYbins, mapYmin, mapYmax);
        h2SecondTracks[detId] = new TH2D(
            Form("h2SecondTracks_arm%i_st%i", arm, station),
            Form("h2SecondTracks_arm%i_st%i;x (mm);y (mm)", arm, station),
            mapXbins, mapXmin, mapXmax, mapYbins, mapYmin, mapYmax);
      }

      // Analyze events
      mux[detId]++;
      h2TrackHitDistribution[detId]->Fill(trackLite.getX(), trackLite.getY());

      if (x < xMin || x > xMax || y < yMin || y > yMax)
        continue;

      if (station == 0) {

        // Retrieve efficiency
        double stripsEfficiency = h2StripsEfficiencies[detId]->GetBinContent(
            h2StripsEfficiencies[detId]->FindBin(x, y));
        // cout << "Strips efficiency: " << stripsEfficiency << endl;
        if (stripsEfficiency < 0.6) {
          h2DamageRegionTracks[detId]->Fill(x, y);
          // cout << "Looking for other tracks" << endl;
          for (auto trackLite2 : trackLites) {
            double x2 = trackLite2.getX();
            double y2 = trackLite2.getY();

            if (trackLite2.getRPId() == trackLite.getRPId()) {
              // cout << "Found a second track" << endl;
              double stripsEfficiency_2 =
                  h2StripsEfficiencies[detId]->GetBinContent(
                      h2StripsEfficiencies[detId]->FindBin(x2, y2));
              if (stripsEfficiency_2 > 0.6) {
                // Count the event once if it's interesting
                if (!isInterestingEvent[detId])
                  h2SecondTracks[detId]->Fill(x2, y2);
                isInterestingEvent[detId] = true;
              }
            }
          }
        }
      }
    }

    for (auto detId : detIdVector) {
      h1Mux[detId]->Fill(mux[detId]);
      // If there were more than 2 tracks the event was not interesting
    }

    CTPPSPixelDetId arm0_st0_id(0, 0, 3);
    CTPPSPixelDetId arm1_st0_id(1, 0, 3);
    if (mux[arm0_st0_id] > 0 && mux[arm1_st0_id] > 0) {
      eventsWithAtLeastOneTrackPerArm++;
      if (mux[arm0_st0_id] < 3 && isInterestingEvent[arm0_st0_id])
        interestingEvents[arm0_st0_id]++;
      if (mux[arm1_st0_id] < 3 && isInterestingEvent[arm1_st0_id])
        interestingEvents[arm1_st0_id]++;
    }

    eventCounter++;
  }

  // Write histograms
  for (auto detId : detIdVector) {
    outputFile->mkdir(Form("Arm%i_st%i", detId.arm(), detId.station()));
    outputFile->cd(Form("Arm%i_st%i", detId.arm(), detId.station()));
    h1Mux[detId]->Write();
    h2TrackHitDistribution[detId]->Write();
    h2DamageRegionTracks[detId]->Write();
    h2SecondTracks[detId]->Write();

    if (detId.station() == 0) {
      h2StripsEfficiencies[detId]->SetNameTitle(
          Form("h2StripsEfficiencies_arm%i_st%i", detId.arm(), detId.station()),
          Form("h2StripsEfficiencies_arm%i_st%i;x (mm);y (mm)", detId.arm(),
               detId.station()));
      h2StripsEfficiencies[detId]->Write();
    }

    delete h1Mux[detId];
    delete h2TrackHitDistribution[detId];
    delete h2DamageRegionTracks[detId];
    delete h2SecondTracks[detId];
  }

  outputFile->Close();
  stripsEfficiencyFile->Close();
  cout << "Saving results in: " << outputFile->GetName() << endl;
  cout << "Sector 45-210F: "
       << (float)interestingEvents[CTPPSPixelDetId(0, 0, 3)] /
              eventsWithAtLeastOneTrackPerArm * 100
       << "\% of the events with at least one track per arm, there was a track "
          "going through the damaged region and another elsewhere"
       << endl;
  cout << "Sector 56-210F: "
       << (float)interestingEvents[CTPPSPixelDetId(1, 0, 3)] /
              eventsWithAtLeastOneTrackPerArm * 100
       << "\% of the events with at least one track per arm, there was a track "
          "going through the damaged region and another elsewhere"
       << endl;
  cout << "Events with at least one track per arm: "
       << eventsWithAtLeastOneTrackPerArm << endl;

  delete outputFile;
  delete stripsEfficiencyFile;
}