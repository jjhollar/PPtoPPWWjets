#define HadronicWWCuts_cxx
#include "HadronicWWCuts.h"
#include <TCanvas.h>
#include <TH2.h>
#include <TMath.h>
#include <TStyle.h>
#include <stdio.h>
#include <string.h>

void HadronicWWCuts::Loop() {
  //   In a ROOT session, you can do:
  //      root> .L HadronicWWCuts.C
  //      root> HadronicWWCuts t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  // by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0)
    return;
  // Doing proton systematics
  TRandom3 ransource;
  bool DOPROTONSYSTEMATICS = false;
  bool DOJECSYSTEMATICSUP = false;
  bool DOJECSYSTEMATICSDOWN = false;

  TString outputFolder = "testrun";

  // TString outputFolder = "signalSamples_v3";
  // TString outputFolder = "dataRun2";
  // TString outputFolder = "backgroundSamples";
  if (DOPROTONSYSTEMATICS)
    outputFolder += "_protonSystematics";
  if (DOJECSYSTEMATICSUP)
    outputFolder += "_JECSystematicsUp";
  if (DOJECSYSTEMATICSDOWN)
    outputFolder += "_JECSystematicsDown";

  outputFolder += "/";

  // RP ID's
  // 3   strips sector 45  -z, left
  // 103 strips sector 56  +z, right
  // 23  pixels sector 45  -z, left
  // 123 pixels sector 56  +z, right

  Int_t nentries = fChain->GetEntries();
  // Limit bkg MC samples to 1M events for quick tests
  //   if((samplenumber > 1 && samplenumber < 20) || (samplenumber > 100 &&
  //   samplenumber < 120) || (samplenumber > 200 && samplenumber < 220))
  //     nentries = 1000000;

  // Total event weight (PU + anything else)
  Float_t myweight = 1.0;

  TH1F *hxold0 = new TH1F("xiold0", "xiold", 100, 0, 0.2);
  TH1F *hxnew0 = new TH1F("xinew0", "xinew", 100, 0, 0.2);
  TH1F *hxold1 = new TH1F("xiold1", "xiold", 100, 0, 0.2);
  TH1F *hxnew1 = new TH1F("xinew1", "xinew", 100, 0, 0.2);

  // Pre-selection plots
  TH1F *hmjjdat = new TH1F("hmjjdat", "hmjjdat", 250, 0, 5000);
  TH1F *hmjjdatpfjet = new TH1F("hmjjdatpfjet", "hmjjdatpfjet", 250, 0, 5000);
  TH1F *hmjjdatpfhttrim =
      new TH1F("hmjjdatpfhttrim", "hmjjdatpfhttrim", 250, 0, 5000);
  TH1F *hmjjdatpfjettrim =
      new TH1F("hmjjdatpfjettrim", "hmjjdatpfjettrim", 250, 0, 5000);
  TH1F *hyjjdat = new TH1F("hyjjdat", "hyjjdat", 250, -5, 5);

  TH1F *hmppmulti = new TH1F("hmppmulti", "hmppmulti", 250, 0, 5000);
  TH1F *hyppmulti = new TH1F("hyppmulti", "hyppmulti", 250, -5, 5);

  TH2F *hmyppsingle =
      new TH2F("hmyppsingle", "hmyppsingle", 100, 0, 5000, 100, -5, 5);
  TH2F *hmyppmulti =
      new TH2F("hmyppmulti", "hmyppmulti", 100, 0, 5000, 100, -5, 5);
  TH2F *hmyjjdat = new TH2F("hmyjjdat", "hmyjjdat", 100, 0, 5000, 100, -5, 5);

  TH1F *hmjdat1 = new TH1F("hmjdat1", "hmjdat1", 250, 0, 1000);
  TH1F *htau21dat1 = new TH1F("htau21dat1", "htau21dat1", 250, 0, 1);
  TH1F *hmjdat2 = new TH1F("hmjdat2", "hmjdat2", 250, 0, 1000);
  TH1F *htau21dat2 = new TH1F("htau21dat2", "htau21dat2", 250, 0, 1);
  TH1F *htau21ddtdat1 = new TH1F("htau21ddtdat1", "htau21ddtdat1", 250, 0, 1.5);
  TH1F *htau21ddtdat2 = new TH1F("htau21ddtdat2", "htau21ddtdat2", 250, 0, 1.5);
  TH2F *tau21vrhoprime1 =
      new TH2F("tau21vrhoprime1", "tau21vrhoprime1", 100, 0, 5, 100, 0, 1);
  TH2F *tau21vrhoprime2 =
      new TH2F("tau21vrhoprime2", "tau21vrhoprime2", 100, 0, 5, 100, 0, 1);

  TH1F *hptdat1 = new TH1F("hptdat1", "hptdat1", 250, 0, 5000);
  TH1F *hetadat1 = new TH1F("hetadat1", "hetadat1", 250, -5, 5);
  TH1F *hphidat1 = new TH1F("hphidat1", "hphidat1", 200, -4, 4);
  TH1F *hptdat2 = new TH1F("hptdat2", "hptdat2", 250, 0, 5000);
  TH1F *hetadat2 = new TH1F("hetadat2", "hetadat2", 250, -5, 5);
  TH1F *hphidat2 = new TH1F("hphidat2", "hphidat2", 200, -4, 4);
  TH1F *hdeta = new TH1F("hdeta", "hdeta", 150, -7.5, 7.5);
  TH1F *hacopdat = new TH1F("hacopdat", "hacopdat", 250, 0, 1);
  TH1F *hnvtx = new TH1F("hnvtx", "hnvtx", 100, 0, 100);
  TH1F *hptratio = new TH1F("hptratio", "hptratio", 500, 0, 5);
  TH1F *hprunedrotatedjjdat =
      new TH1F("hprunedrotatedjjdat", "hprunedrotatedjjdat", 250, 0, 500);
  TH1F *hprunedrotatedjjprematchingdat =
      new TH1F("hprunedrotatedjjprematchingdat",
               "hprunedrotatedjjprematchingdat", 250, 0, 500);

  TH1F *hxipix45 = new TH1F("hxipix45", "hxipix45", 500, 0, 0.5);
  TH1F *hypix45 = new TH1F("hypix45", "hypix45", 500, -50, 50);
  TH1F *hxipix56 = new TH1F("hxipix56", "hxipix56", 500, 0, 0.5);
  TH1F *hypix56 = new TH1F("hypix56", "hypix56", 500, -50, 50);
  TH1F *hxistrip45 = new TH1F("hxistrip45", "hxistrip45", 500, 0, 0.5);
  TH1F *hystrip45 = new TH1F("hystrip45", "hystrip45", 500, -50, 50);
  TH1F *hxistrip56 = new TH1F("hxistrip56", "hxistrip56", 500, 0, 0.5);
  TH1F *hystrip56 = new TH1F("hystrip56", "hystrip56", 500, -50, 50);
  TH1F *hximult45 = new TH1F("hximult45", "hximult45", 500, 0, 0.5);
  TH1F *hximult56 = new TH1F("hximult56", "hximult56", 500, 0, 0.5);
  TH1F *hthystmult45 =
      new TH1F("hthystmult45", "hthystmult45", 500, -0.001, 0.001);
  TH1F *hthystmult56 =
      new TH1F("hthystmult56", "hthystmult56", 500, -0.001, 0.001);
  TH1F *htmult45 = new TH1F("htmult45", "htmult45", 500, 0, 10);
  TH1F *htmult56 = new TH1F("htmult56", "htmult56", 500, 0, 10);
  TH1F *hdtmulti = new TH1F("hdtmulti", "hdtmulti", 500, -25, 25);

  TH1F *hnmult45 = new TH1F("hnmult45", "hnmult45", 15, 0, 15);
  TH1F *hnmult56 = new TH1F("hnmult56", "hnmult56", 15, 0, 15);

  TH1F *hdxi45 = new TH1F("hdxi45", "hdxi45", 500, -0.2, 0.2);
  TH1F *hdy45 = new TH1F("hdy45", "hdy45", 500, -20, 20);
  TH1F *hdxi56 = new TH1F("hdxi56", "hdxi56", 500, -0.2, 0.2);
  TH1F *hdy56 = new TH1F("hdy56", "hdy56", 500, -20, 20);

  // Sideband control region plots - WW
  TH1F *hmassmatchantiacopmmww = new TH1F(
      "hmassmatchantiacopmmww", "hmassmatchantiacopmmww", 500, -2500, 2500);
  TH1F *hymatchantiacopmmww =
      new TH1F("hymatchantiacopmmww", "hymatchantiacopmmww", 100, -5, 5);
  TH1F *hmassmatchratioantiacopmmww = new TH1F(
      "hmassmatchratioantiacopmmww", "hmassmatchratioantiacopmmww", 100, -5, 5);
  TH1F *hmassmatchantitaummww = new TH1F(
      "hmassmatchantitaummww", "hmassmatchantitaummww", 500, -2500, 2500);
  TH1F *hymatchantitaummww =
      new TH1F("hymatchantitaummww", "hymatchantitaummww", 100, -5, 5);
  TH1F *hmassmatchratioantitaummww = new TH1F(
      "hmassmatchratioantitaummww", "hmassmatchratioantitaummww", 100, -5, 5);
  TH1F *hmassmatchantiptbalmmww = new TH1F(
      "hmassmatchantiptbalmmww", "hmassmatchantiptbalmmww", 500, -2500, 2500);
  TH1F *hymatchantiptbalmmww =
      new TH1F("hymatchantiptbalmmww", "hymatchantiptbalmmww", 100, -5, 5);
  TH1F *hmassmatchratioantiptbalmmww =
      new TH1F("hmassmatchratioantiptbalmmww", "hmassmatchratioantiptbalmmww",
               100, -5, 5);
  TH1F *hmassmatchantiprunedmmww = new TH1F(
      "hmassmatchantiprunedmmww", "hmassmatchantiprunedmmww", 500, -2500, 2500);
  TH1F *hymatchantiprunedmmww =
      new TH1F("hymatchantiprunedmmww", "hymatchantiprunedmmww", 100, -5, 5);
  TH1F *hmassmatchratioantiprunedmmww =
      new TH1F("hmassmatchratioantiprunedmmww", "hmassmatchratioantiprunedmmww",
               100, -5, 5);
  TH1F *hmassmatchantiprunednarrowmmww =
      new TH1F("hmassmatchantiprunednarrowmmww",
               "hmassmatchantiprunednarrowmmww", 500, -2500, 2500);
  TH1F *hymatchantiprunednarrowmmww = new TH1F(
      "hymatchantiprunednarrowmmww", "hymatchantiprunednarrowmmww", 100, -5, 5);
  TH1F *hmassmatchratioantiprunednarrowmmww =
      new TH1F("hmassmatchratioantiprunednarrowmmww",
               "hmassmatchratioantiprunednarrowmmww", 100, -5, 5);

  // Sideband control region plots - ZZ
  TH1F *hmassmatchantiacopmmzz = new TH1F(
      "hmassmatchantiacopmmzz", "hmassmatchantiacopmmzz", 500, -2500, 2500);
  TH1F *hymatchantiacopmmzz =
      new TH1F("hymatchantiacopmmzz", "hymatchantiacopmmzz", 100, -5, 5);
  TH1F *hmassmatchratioantiacopmmzz = new TH1F(
      "hmassmatchratioantiacopmmzz", "hmassmatchratioantiacopmmzz", 100, -5, 5);
  TH1F *hmassmatchantitaummzz = new TH1F(
      "hmassmatchantitaummzz", "hmassmatchantitaummzz", 500, -2500, 2500);
  TH1F *hymatchantitaummzz =
      new TH1F("hymatchantitaummzz", "hymatchantitaummzz", 100, -5, 5);
  TH1F *hmassmatchratioantitaummzz = new TH1F(
      "hmassmatchratioantitaummzz", "hmassmatchratioantitaummzz", 100, -5, 5);
  TH1F *hmassmatchantiptbalmmzz = new TH1F(
      "hmassmatchantiptbalmmzz", "hmassmatchantiptbalmmzz", 500, -2500, 2500);
  TH1F *hymatchantiptbalmmzz =
      new TH1F("hymatchantiptbalmmzz", "hymatchantiptbalmmzz", 100, -5, 5);
  TH1F *hmassmatchratioantiptbalmmzz =
      new TH1F("hmassmatchratioantiptbalmmzz", "hmassmatchratioantiptbalmmzz",
               100, -5, 5);
  TH1F *hmassmatchantiprunedmmzz = new TH1F(
      "hmassmatchantiprunedmmzz", "hmassmatchantiprunedmmzz", 500, -2500, 2500);
  TH1F *hymatchantiprunedmmzz =
      new TH1F("hymatchantiprunedmmzz", "hymatchantiprunedmmzz", 100, -5, 5);
  TH1F *hmassmatchratioantiprunedmmzz =
      new TH1F("hmassmatchratioantiprunedmmzz", "hmassmatchratioantiprunedmmzz",
               100, -5, 5);
  TH1F *hmassmatchantiprunednarrowmmzz =
      new TH1F("hmassmatchantiprunednarrowmmzz",
               "hmassmatchantiprunednarrowmmzz", 500, -2500, 2500);
  TH1F *hymatchantiprunednarrowmmzz = new TH1F(
      "hymatchantiprunednarrowmmzz", "hymatchantiprunednarrowmmzz", 100, -5, 5);
  TH1F *hmassmatchratioantiprunednarrowmmzz =
      new TH1F("hmassmatchratioantiprunednarrowmmzz",
               "hmassmatchratioantiprunednarrowmmzz", 100, -5, 5);

  // 1-D proton-VV matching plots
  TH2F *hgenxinomatch =
      new TH2F("hgenxinomatch", "hgenxinomatch", 500, 0, 0.5, 500, 0, 0.5);
  TH1F *hmassmatchratiosigmcoutofacceptancemm =
      new TH1F("hmassmatchratiosigmcoutofacceptancemm",
               "hmassmatchratiosigmcoutofacceptancemm", 100, -5, 5);
  TH1F *hmassmatchratiosigmcinacceptancemm =
      new TH1F("hmassmatchratiosigmcinacceptancemm",
               "hmassmatchratiosigmcinacceptancemm", 100, -5, 5);
  TH1F *hmassmatchratiosigmcinacceptancenomatchmm =
      new TH1F("hmassmatchratiosigmcinacceptancenomatchmm",
               "hmassmatchratiosigmcinacceptancenomatchmm", 100, -5, 5);
  TH1F *hymatchsigmcoutofacceptancemm =
      new TH1F("hymatchsigmcoutofacceptancemm", "hymatchsigmcoutofacceptancemm",
               500, -5, 5);
  TH1F *hymatchsigmcinacceptancemm = new TH1F(
      "hymatchsigmcinacceptancemm", "hymatchsigmcinacceptancemm", 500, -5, 5);
  TH1F *hymatchsigmcinacceptancenomatchmm =
      new TH1F("hymatchsigmcinacceptancenomatchmm",
               "hymatchsigmcinacceptancenomatchmm", 500, -5, 5);

  // 1-D proton-VV matching plots with systematic shifts
  TH1F *hmassmatchratiosigmcmmshiftupww =
      new TH1F("hmassmatchratiosigmcmmshiftupww",
               "hmassmatchratiosigmcmmshiftupww", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmmshiftdownww =
      new TH1F("hmassmatchratiosigmcmmshiftdownww",
               "hmassmatchratiosigmcmmshiftdownww", 500, -5, 5);
  TH1F *hymatchsigmcmmshiftupww = new TH1F(
      "hymatchsigmcmmshiftupww", "hymatchsigmcmmshiftupww", 500, -5, 5);
  TH1F *hymatchsigmcmmshiftdownww = new TH1F(
      "hymatchsigmcmmshiftdownww", "hymatchsigmcmmshiftdownww", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmmshiftupzz =
      new TH1F("hmassmatchratiosigmcmmshiftupzz",
               "hmassmatchratiosigmcmmshiftupzz", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmmshiftdownzz =
      new TH1F("hmassmatchratiosigmcmmshiftdownzz",
               "hmassmatchratiosigmcmmshiftdownzz", 500, -5, 5);
  TH1F *hymatchsigmcmmshiftupzz = new TH1F(
      "hymatchsigmcmmshiftupzz", "hymatchsigmcmmshiftupzz", 500, -5, 5);
  TH1F *hymatchsigmcmmshiftdownzz = new TH1F(
      "hymatchsigmcmmshiftdownzz", "hymatchsigmcmmshiftdownzz", 500, -5, 5);

  // 2-D proton-VV matching plots
  TH2F *hmassrapiditymatchvetosignalregionww =
      new TH2F("hmassrapiditymatchvetosignalregionww",
               "hmassrapiditymatchvetosignalregionww", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchvetoorsignalregionww = new TH2F(
      "hmassrapiditymatchvetoorsignalregionww",
      "hmassrapiditymatchvetoorsignalregionww", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchvetosignalregionzz =
      new TH2F("hmassrapiditymatchvetosignalregionzz",
               "hmassrapiditymatchvetosignalregionzz", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchvetoorsignalregionzz = new TH2F(
      "hmassrapiditymatchvetoorsignalregionzz",
      "hmassrapiditymatchvetoorsignalregionzz", 500, -5, 5, 500, -5, 5);

  TH2F *hmassrapiditymatchantitaummww =
      new TH2F("hmassrapiditymatchantitaummww", "hmassrapiditymatchantitaummww",
               500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiacopmmww =
      new TH2F("hmassrapiditymatchantiacopmmww",
               "hmassrapiditymatchantiacopmmww", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiptbalmmww =
      new TH2F("hmassrapiditymatchantiptbalmmww",
               "hmassrapiditymatchantiptbalmmww", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiprunedmmww =
      new TH2F("hmassrapiditymatchantiprunedmmww",
               "hmassrapiditymatchantiprunedmmww", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiprunednarrowmmww = new TH2F(
      "hmassrapiditymatchantiprunednarrowmmww",
      "hmassrapiditymatchantiprunednarrowmmww", 500, -5, 5, 500, -5, 5);

  TH2F *hmassrapiditymatchantitaummzz =
      new TH2F("hmassrapiditymatchantitaummzz", "hmassrapiditymatchantitaummzz",
               500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiacopmmzz =
      new TH2F("hmassrapiditymatchantiacopmmzz",
               "hmassrapiditymatchantiacopmmzz", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiptbalmmzz =
      new TH2F("hmassrapiditymatchantiptbalmmzz",
               "hmassrapiditymatchantiptbalmmzz", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiprunedmmzz =
      new TH2F("hmassrapiditymatchantiprunedmmzz",
               "hmassrapiditymatchantiprunedmmzz", 500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchantiprunednarrowmmzz = new TH2F(
      "hmassrapiditymatchantiprunednarrowmmzz",
      "hmassrapiditymatchantiprunednarrowmmzz", 500, -5, 5, 500, -5, 5);

  TH2F *hycorrpreseldatmult = new TH2F(
      "hycorrpreseldatmult", "hycorrpreseldatmult", 100, -5, 5, 100, -5, 5);
  TH2F *hmasscorrpreseldatmult =
      new TH2F("hmasscorrpreseldatmult", "hmasscorrpreseldatmult", 250, 0, 2500,
               250, 0, 2500);
  TH2F *dymassratiocorrpreseldatmult =
      new TH2F("dymassratiocorrpreseldatmult", "dymassratiocorrpreseldatmult",
               500, -5, 5, 500, -5, 5);

  TH2F *hmassrapiditymatchsigmcmmww =
      new TH2F("hmassrapiditymatchsigmcmmww", "hmassrapiditymatchsigmcmmww",
               500, -5, 5, 500, -5, 5);
  TH2F *hmassrapiditymatchsigmcmmzz =
      new TH2F("hmassrapiditymatchsigmcmmzz", "hmassrapiditymatchsigmcmmzz",
               500, -5, 5, 500, -5, 5);
  TH1F *hmvvsigmcsigregionww =
      new TH1F("hmvvsigmcsigregionww", "hmvvsigmcsigregionww", 250, 0, 5000);
  TH1F *hmvvsigmcsigregionzz =
      new TH1F("hmvvsigmcsigregionzz", "hmvvsigmcsigregionzz", 250, 0, 5000);
  TH1F *hyvvsigmcsigregionww =
      new TH1F("hyvvsigmcsigregionww", "hyvvsigmcsigregionww", 250, -5, 5);
  TH1F *hyvvsigmcsigregionzz =
      new TH1F("hyvvsigmcsigregionzz", "hyvvsigmcsigregionzz", 250, -5, 5);
  TH1F *hmppsigmcsigregionww =
      new TH1F("hmppsigmcsigregionww", "hmppsigmcsigregionww", 250, 0, 5000);
  TH1F *hyppsigmcsigregionww =
      new TH1F("hyppsigmcsigregionww", "hyppsigmcsigregionww", 250, -5, 5);
  TH1F *hmppsigmcsigregionzz =
      new TH1F("hmppsigmcsigregionzz", "hmppsigmcsigregionzz", 250, 0, 5000);
  TH1F *hyppsigmcsigregionzz =
      new TH1F("hyppsigmcsigregionzz", "hyppsigmcsigregionzz", 250, -5, 5);

  // Anit-pT balance control plots
  TH1F *hmassvvantiptbalww =
      new TH1F("hmassvvantiptbalww", "hmassvvantiptbalww", 250, 0, 5000);
  TH1F *hmassvvantiptbalzz =
      new TH1F("hmassvvantiptbalzz", "hmassvvantiptbalzz", 250, 0, 5000);

  // Anti-acoplanarity control plots
  TH1F *hmassvvantiacopww =
      new TH1F("hmassvvantiacopww", "hmassvvantiacopww", 250, 0, 5000);
  TH1F *hmj1antiacopww =
      new TH1F("hmj1antiacopww", "hmj1antiacopww", 250, 0, 1000);
  TH1F *htau211antiacopww =
      new TH1F("htau211antiacopww", "htau211antiacopww", 250, 0, 1);
  TH1F *hmj2antiacopww =
      new TH1F("hmj2antiacopww", "hmj2antiacopww", 250, 0, 1000);
  TH1F *htau212antiacopww =
      new TH1F("htau212antiacopww", "htau212antiacopww", 250, 0, 1);
  TH1F *hmassvvantiacopzz =
      new TH1F("hmassvvantiacopzz", "hmassvvantiacopzz", 250, 0, 5000);
  TH1F *hmj1antiacopzz =
      new TH1F("hmj1antiacopzz", "hmj1antiacopzz", 250, 0, 1000);
  TH1F *htau211antiacopzz =
      new TH1F("htau211antiacopzz", "htau211antiacopzz", 250, 0, 1);
  TH1F *hmj2antiacopzz =
      new TH1F("hmj2antiacopzz", "hmj2antiacopzz", 250, 0, 1000);
  TH1F *htau212antiacopzz =
      new TH1F("htau212antiacopzz", "htau212antiacopzz", 250, 0, 1);

  TH1F *hmvvsigmcantiacopsigregionww =
      new TH1F("hmvvsigmcantiacopsigregionww", "hmvvsigmcantiacopsigregionww",
               250, 0, 5000);
  TH1F *hmvvsigmcantiacopsigregionzz =
      new TH1F("hmvvsigmcantiacopsigregionzz", "hmvvsigmcantiacopsigregionzz",
               250, 0, 5000);
  TH1F *hyvvsigmcantiacopsigregionww =
      new TH1F("hyvvsigmcantiacopsigregionww", "hyvvsigmcantiacopsigregionww",
               250, -5, 5);
  TH1F *hyvvsigmcantiacopsigregionzz =
      new TH1F("hyvvsigmcantiacopsigregionzz", "hyvvsigmcantiacopsigregionzz",
               250, -5, 5);
  TH1F *hmppsigmcantiacopsigregionww =
      new TH1F("hmppsigmcantiacopsigregionww", "hmppsigmcantiacopsigregionww",
               250, 0, 5000);
  TH1F *hyppsigmcantiacopsigregionww =
      new TH1F("hyppsigmcantiacopsigregionww", "hyppsigmcantiacopsigregionww",
               250, -5, 5);
  TH1F *hmppsigmcantiacopsigregionzz =
      new TH1F("hmppsigmcantiacopsigregionzz", "hmppsigmcantiacopsigregionzz",
               250, 0, 5000);
  TH1F *hyppsigmcantiacopsigregionzz =
      new TH1F("hyppsigmcantiacopsigregionzz", "hyppsigmcantiacopsigregionzz",
               250, -5, 5);

  // Anti-tau21 control plots
  TH1F *hmassvvantitauww =
      new TH1F("hmassvvantitauww", "hmassvvantitauww", 250, 0, 5000);
  TH1F *hmj1antitauww =
      new TH1F("hmj1antitauww", "hmj1antitauww", 250, 0, 1000);
  TH1F *htau211antitauww =
      new TH1F("htau211antitauww", "htau211antitauww", 250, 0, 1);
  TH1F *hmj2antitauww =
      new TH1F("hmj2antitauww", "hmj2antitauww", 250, 0, 1000);
  TH1F *htau212antitauww =
      new TH1F("htau212antitauww", "htau212antitauww", 250, 0, 1);
  TH1F *hmassvvantitauzz =
      new TH1F("hmassvvantitauzz", "hmassvvantitauzz", 250, 0, 5000);
  TH1F *hmj1antitauzz =
      new TH1F("hmj1antitauzz", "hmj1antitauzz", 250, 0, 1000);
  TH1F *htau211antitauzz =
      new TH1F("htau211antitauzz", "htau211antitauzz", 250, 0, 1);
  TH1F *hmj2antitauzz =
      new TH1F("hmj2antitauzz", "hmj2antitauzz", 250, 0, 1000);
  TH1F *htau212antitauzz =
      new TH1F("htau212antitauzz", "htau212antitauzz", 250, 0, 1);

  // Anti-pruned mass control plots
  TH1F *hmassvvantiprunedww =
      new TH1F("hmassvvantiprunedww", "hmassvvantiprunedww", 250, 0, 5000);
  TH1F *hmj1antiprunedww =
      new TH1F("hmj1antiprunedww", "hmj1antiprunedww", 250, 0, 1000);
  TH1F *htau211antiprunedww =
      new TH1F("htau211antiprunedww", "htau211antiprunedww", 250, 0, 1);
  TH1F *hmj2antiprunedww =
      new TH1F("hmj2antiprunedww", "hmj2antiprunedww", 250, 0, 1000);
  TH1F *htau212antiprunedww =
      new TH1F("htau212antiprunedww", "htau212antiprunedww", 250, 0, 1);
  TH1F *hmassvvantiprunedzz =
      new TH1F("hmassvvantiprunedzz", "hmassvvantiprunedzz", 250, 0, 5000);
  TH1F *hmj1antiprunedzz =
      new TH1F("hmj1antiprunedzz", "hmj1antiprunedzz", 250, 0, 1000);
  TH1F *htau211antiprunedzz =
      new TH1F("htau211antiprunedzz", "htau211antiprunedzz", 250, 0, 1);
  TH1F *hmj2antiprunedzz =
      new TH1F("hmj2antiprunedzz", "hmj2antiprunedzz", 250, 0, 1000);
  TH1F *htau212antiprunedzz =
      new TH1F("htau212antiprunedzz", "htau212antiprunedzz", 250, 0, 1);

  // Anti-pruned mass control plots, narrow mass region
  TH1F *hmassvvantiprunednarrowww = new TH1F(
      "hmassvvantiprunednarrowww", "hmassvvantiprunednarrowww", 250, 0, 5000);
  TH1F *hmj1antiprunednarrowww = new TH1F(
      "hmj1antiprunednarrowww", "hmj1antiprunednarrowww", 250, 0, 1000);
  TH1F *htau211antiprunednarrowww = new TH1F(
      "htau211antiprunednarrowww", "htau211antiprunednarrowww", 250, 0, 1);
  TH1F *hmj2antiprunednarrowww = new TH1F(
      "hmj2antiprunednarrowww", "hmj2antiprunednarrowww", 250, 0, 1000);
  TH1F *htau212antiprunednarrowww = new TH1F(
      "htau212antiprunednarrowww", "htau212antiprunednarrowww", 250, 0, 1);
  TH1F *hmassvvantiprunednarrowzz = new TH1F(
      "hmassvvantiprunednarrowzz", "hmassvvantiprunednarrowzz", 250, 0, 5000);
  TH1F *hmj1antiprunednarrowzz = new TH1F(
      "hmj1antiprunednarrowzz", "hmj1antiprunednarrowzz", 250, 0, 1000);
  TH1F *htau211antiprunednarrowzz = new TH1F(
      "htau211antiprunednarrowzz", "htau211antiprunednarrowzz", 250, 0, 1);
  TH1F *hmj2antiprunednarrowzz = new TH1F(
      "hmj2antiprunednarrowzz", "hmj2antiprunednarrowzz", 250, 0, 1000);
  TH1F *htau212antiprunednarrowzz = new TH1F(
      "htau212antiprunednarrowzz", "htau212antiprunednarrowzz", 250, 0, 1);

  TH1F *hcrossingangle =
      new TH1F("hcrossingangle", "hcrossingangle", 70, 100, 170);

  TH1F *hmppres = new TH1F("hmppres", "hmppres", 100, 0, 2);
  TH1F *hmjjres = new TH1F("hmjjres", "hmjjres", 100, 0, 2);
  TH1F *hmassmatchratiosigmcmultww = new TH1F(
      "hmassmatchratiosigmcmultww", "hmassmatchratiosigmcmultww", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmultzz = new TH1F(
      "hmassmatchratiosigmcmultzz", "hmassmatchratiosigmcmultzz", 500, -5, 5);

  TH1F *xijets45 = new TH1F("xijets45", "xijets45", 250, 0, 0.25);
  TH1F *xijets56 = new TH1F("xijets56", "xijets56", 250, 0, 0.25);
  TH1F *resxijets45 = new TH1F("resxijets45", "resxijets45", 100, 0, 2);
  TH1F *resxijets56 = new TH1F("resxijets56", "resxijets56", 100, 0, 2);
  TH2F *resxijetscorr45 =
      new TH2F("resxijetscorr45", "resxijetscorr45", 300, 0, 0.3, 300, 0, 0.3);
  TH2F *resxijetscorr56 =
      new TH2F("resxijetscorr56", "resxijetscorr56", 300, 0, 0.3, 300, 0, 0.3);

  TH1F *hmassvvsignalww =
      new TH1F("hmassvvsignalww", "hmassvvsignalww", 250, 0, 5000);
  TH1F *hywwsignalww = new TH1F("hywwsignalww", "hywwsignalww", 250, -5, 5);
  TH1F *hmassvvsignalzz =
      new TH1F("hmassvvsignalzz", "hmassvvsignalzz", 250, 0, 5000);
  TH1F *hywwsignalzz = new TH1F("hywwsignalzz", "hywwsignalzz", 250, -5, 5);

  // Signal region plots
  TH1F *hmassmatchsigmcmmww =
      new TH1F("hmassmatchsigmcmmww", "hmassmatchsigmcmmww", 500, -2500, 2500);
  TH1F *hymatchsigmcmmww =
      new TH1F("hymatchsigmcmmww", "hymatchsigmcmmww", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmmww = new TH1F(
      "hmassmatchratiosigmcmmww", "hmassmatchratiosigmcmmww", 500, -5, 5);
  TH1F *hymatchsigmcmultww =
      new TH1F("hymatchsigmcmultww", "hymatchsigmcmultww", 500, -5, 5);
  TH2F *hmasscorrsigmcmultww =
      new TH2F("hmasscorrsigmcmultww", "hmasscorrsigmcmultww", 250, 0, 2500,
               250, 0, 2500);
  TH2F *hycorrsigmcmultww = new TH2F("hycorrsigmcmultww", "hycorrsigmcmultww",
                                     100, -5, 5, 100, -5, 5);
  TH2F *hmasscorrsigmcmulttruthmatchedww =
      new TH2F("hmasscorrsigmcmulttruthmatchedww",
               "hmasscorrsigmcmulttruthmatchedww", 250, 0, 2500, 250, 0, 2500);

  TH1F *hmassmatchsigmcmmzz =
      new TH1F("hmassmatchsigmcmmzz", "hmassmatchsigmcmmzz", 500, -2500, 2500);
  TH1F *hymatchsigmcmmzz =
      new TH1F("hymatchsigmcmmzz", "hymatchsigmcmmzz", 500, -5, 5);
  TH1F *hmassmatchratiosigmcmmzz = new TH1F(
      "hmassmatchratiosigmcmmzz", "hmassmatchratiosigmcmmzz", 500, -5, 5);
  TH1F *hymatchsigmcmultzz =
      new TH1F("hymatchsigmcmultzz", "hymatchsigmcmultzz", 500, -5, 5);
  TH2F *hmasscorrsigmcmultzz =
      new TH2F("hmasscorrsigmcmultzz", "hmasscorrsigmcmultzz", 250, 0, 2500,
               250, 0, 2500);
  TH2F *hycorrsigmcmultzz = new TH2F("hycorrsigmcmultzz", "hycorrsigmcmultzz",
                                     100, -5, 5, 100, -5, 5);
  TH2F *hmasscorrsigmcmulttruthmatchedzz =
      new TH2F("hmasscorrsigmcmulttruthmatchedzz",
               "hmasscorrsigmcmulttruthmatchedzz", 250, 0, 2500, 250, 0, 2500);

  std::vector<float> *mppsmultmult = new std::vector<float>;
  std::vector<float> *yppsmultmult = new std::vector<float>;
  std::vector<float> *xipix45s = new std::vector<float>;
  std::vector<float> *xipix56s = new std::vector<float>;
  std::vector<float> *ypix45s = new std::vector<float>;
  std::vector<float> *ypix56s = new std::vector<float>;
  std::vector<float> *ximulti45s = new std::vector<float>;
  std::vector<float> *ximulti56s = new std::vector<float>;
  std::vector<float> *thystmulti45s = new std::vector<float>;
  std::vector<float> *thystmulti56s = new std::vector<float>;
  std::vector<float> *tmulti45s = new std::vector<float>;
  std::vector<float> *tmulti56s = new std::vector<float>;
  std::vector<float> *timemulti45s = new std::vector<float>;
  std::vector<float> *timemulti56s = new std::vector<float>;
  std::vector<float> *xishiftmultis45 = new std::vector<float>;
  std::vector<float> *xishiftmultis56 = new std::vector<float>;
  std::vector<float> *mppsmultmultshiftup = new std::vector<float>;
  std::vector<float> *mppsmultmultshiftdown = new std::vector<float>;
  std::vector<float> *yppsmultmultshiftup = new std::vector<float>;
  std::vector<float> *yppsmultmultshiftdown = new std::vector<float>;

  // Counters for # of MC events passing cuts
  Float_t npasspresel = 0;
  Float_t npassdijetkine = 0;
  Float_t npassjetsubstr = 0;
  Float_t npassjetxi = 0;
  Float_t npasspps = 0;
  Float_t npassppsbeforecuts = 0;
  Float_t npassppsmatch_A = 0;
  Float_t npassppsmatch_B = 0;
  Float_t npassppsmatchkseniaww_A = 0;
  Float_t npassppsmatchkseniaww_B = 0;
  Float_t npassppsmatchkseniazz_A = 0;
  Float_t npassppsmatchkseniazz_B = 0;

  // Counters for sideband background normalization
  Float_t npassnonblindnormregionww = 0;
  Float_t npassantiacopnormregionww = 0;
  Float_t npassantitaunormregionww = 0;
  Float_t npassantimassnormregionww = 0;
  Float_t npassantimassnarrownormregionww = 0;
  Float_t npassantiacopsigregionww_A = 0;
  Float_t npassantiacopsigregionww_B = 0;
  Float_t npassantitausigregionww_A = 0;
  Float_t npassantitausigregionww_B = 0;
  Float_t npassantimasssigregionww_A = 0;
  Float_t npassantimasssigregionww_B = 0;
  Float_t npassantimassnarrowsigregionww_A = 0;
  Float_t npassantimassnarrowsigregionww_B = 0;

  Float_t npassnonblindnormregionzz = 0;
  Float_t npassantiacopnormregionzz = 0;
  Float_t npassantitaunormregionzz = 0;
  Float_t npassantimassnormregionzz = 0;
  Float_t npassantimassnarrownormregionzz = 0;
  Float_t npassantiacopsigregionzz_A = 0;
  Float_t npassantiacopsigregionzz_B = 0;
  Float_t npassantitausigregionzz_A = 0;
  Float_t npassantitausigregionzz_B = 0;
  Float_t npassantimasssigregionzz_A = 0;
  Float_t npassantimasssigregionzz_B = 0;
  Float_t npassantimassnarrowsigregionzz_A = 0;
  Float_t npassantimassnarrowsigregionzz_B = 0;

  // JEC systematics
  JetCorrectionUncertainty *jectotal;
  // For MC
  if (samplenumber > 0 && samplenumber <= 100)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017_V32_MC_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber > 100 && samplenumber <= 200)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2016/"
        "Summer16_07Aug2017_V11_MC_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber > 200 && samplenumber <= 300)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JECAUTUMN18/Autumn18_V19_MC_UncertaintySources_AK8PFchs.txt",
        "Total")));
  // For Data
  if (samplenumber == -1)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017B_V32_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -2)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017C_V32_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -3)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017D_V32_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -4)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017E_V32_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -5)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2017/"
        "Fall17_17Nov2017F_V32_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -6 || samplenumber == -7)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2016/"
        "Summer16_07Aug2017BCD_V11_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -8 || samplenumber == -9)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JEC2016/"
        "Summer16_07Aug2017GH_V11_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -10)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JECAUTUMN18/"
        "Autumn18_RunA_V19_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -11)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JECAUTUMN18/"
        "Autumn18_RunB_V19_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -12)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JECAUTUMN18/"
        "Autumn18_RunC_V19_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));
  if (samplenumber == -13)
    jectotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters(
        "../python/JECAUTUMN18/"
        "Autumn18_RunD_V19_DATA_UncertaintySources_AK8PFchs.txt",
        "Total")));

  TString outtextfile = outputFolder + "MC_EventsForMixing.txt";

  if (samplenumber == 2)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD300to470_2017.txt";
  if (samplenumber == 3)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD470to600_2017.txt";
  if (samplenumber == 4)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD600to800_2017.txt";
  if (samplenumber == 5)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD800to1000_2017.txt";
  if (samplenumber == 6)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1000to1400_2017.txt";
  if (samplenumber == 10)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1400to1800_2017.txt";
  if (samplenumber == 7)
    outtextfile = outputFolder + "MC_EventsForMixing_ttbar_2017.txt";
  if (samplenumber == 8)
    outtextfile = outputFolder + "MC_EventsForMixing_wjets_2017.txt";
  if (samplenumber == 9)
    outtextfile = outputFolder + "MC_EventsForMixing_zjets_2017.txt";

  if (samplenumber == 20)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2017B.txt";
  if (samplenumber == 21)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2017C.txt";
  if (samplenumber == 22)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2017D.txt";
  if (samplenumber == 23)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2017B.txt";
  if (samplenumber == 24)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2017C.txt";
  if (samplenumber == 25)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2017D.txt";
  if (samplenumber == 26)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2017B.txt";
  if (samplenumber == 27)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2017C.txt";
  if (samplenumber == 28)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2017D.txt";
  if (samplenumber == 29)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2017B.txt";
  if (samplenumber == 30)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2017C.txt";
  if (samplenumber == 31)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2017D.txt";
  if (samplenumber == 32)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2017B.txt";
  if (samplenumber == 33)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2017C.txt";
  if (samplenumber == 34)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2017D.txt";
  if (samplenumber == 35)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2017B.txt";
  if (samplenumber == 36)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2017C.txt";
  if (samplenumber == 37)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2017D.txt";

  if (samplenumber == 40)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z-1E-5_preTS2_2017B.txt";
  if (samplenumber == 41)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z1E-5_preTS2_2017B.txt";
  if (samplenumber == 42)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z5E-5_preTS2_2017B.txt";
  if (samplenumber == 43)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ-1E-5_preTS2_2017B.txt";
  if (samplenumber == 44)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ1E-5_preTS2_2017B.txt";
  if (samplenumber == 45)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ5E-5_preTS2_2017B.txt";

  if (samplenumber == 50)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_postTS2_2017E.txt";
  if (samplenumber == 51)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_postTS2_2017F.txt";
  if (samplenumber == 52)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_postTS2_2017E.txt";
  if (samplenumber == 53)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_postTS2_2017F.txt";
  if (samplenumber == 54)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_postTS2_2017E.txt";
  if (samplenumber == 55)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_postTS2_2017F.txt";
  if (samplenumber == 56)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_postTS2_2017E.txt";
  if (samplenumber == 57)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_postTS2_2017F.txt";
  if (samplenumber == 58)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_postTS2_2017E.txt";
  if (samplenumber == 59)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_postTS2_2017F.txt";
  if (samplenumber == 60)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_postTS2_2017E.txt";
  if (samplenumber == 61)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_postTS2_2017F.txt";

  if (samplenumber == 102)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD300to470_2016.txt";
  if (samplenumber == 103)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD470to600_2016.txt";
  if (samplenumber == 104)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD600to800_2016.txt";
  if (samplenumber == 105)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD800to1000_2016.txt";
  if (samplenumber == 106)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1000to1400_2016.txt";
  if (samplenumber == 110)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1400to1800_2016.txt";
  if (samplenumber == 107)
    outtextfile = outputFolder + "MC_EventsForMixing_ttbar1000inf_2016.txt";
  if (samplenumber == 108)
    outtextfile = outputFolder + "MC_EventsForMixing_wjets_2016.txt";
  if (samplenumber == 109)
    outtextfile = outputFolder + "MC_EventsForMixing_zjets_2016.txt";
  if (samplenumber == 111)
    outtextfile = outputFolder + "MC_EventsForMixing_ttbar700to1000_2016.txt";

  if (samplenumber == 120)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2016B.txt";
  if (samplenumber == 121)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2016C.txt";
  if (samplenumber == 122)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2016G.txt";
  if (samplenumber == 123)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2016B.txt";
  if (samplenumber == 124)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2016C.txt";
  if (samplenumber == 125)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2016G.txt";
  if (samplenumber == 126)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2016B.txt";
  if (samplenumber == 127)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2016C.txt";
  if (samplenumber == 128)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2016G.txt";
  if (samplenumber == 129)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2016B.txt";
  if (samplenumber == 130)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2016C.txt";
  if (samplenumber == 131)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2016G.txt";
  if (samplenumber == 132)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2016B.txt";
  if (samplenumber == 133)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2016C.txt";
  if (samplenumber == 134)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_preTS2_2016G.txt";
  if (samplenumber == 135)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2016B.txt";
  if (samplenumber == 136)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2016C.txt";
  if (samplenumber == 137)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_preTS2_2016G.txt";

  if (samplenumber == 140)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z-1E-5_preTS2_2016B.txt";
  if (samplenumber == 141)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z1E-5_preTS2_2016B.txt";
  if (samplenumber == 142)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z5E-5_preTS2_2016B.txt";
  if (samplenumber == 143)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ-1E-5_preTS2_2016B.txt";
  if (samplenumber == 144)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ1E-5_preTS2_2016B.txt";
  if (samplenumber == 145)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ5E-5_preTS2_2016B.txt";

  if (samplenumber == 202)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD300to470_2018.txt";
  if (samplenumber == 203)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD470to600_2018.txt";
  if (samplenumber == 204)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD600to800_2018.txt";
  if (samplenumber == 205)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD800to1000_2018.txt";
  if (samplenumber == 206)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1000to1400_2018.txt";
  if (samplenumber == 210)
    outtextfile = outputFolder + "MC_EventsForMixing_QCD1400to1800_2018.txt";
  if (samplenumber == 207)
    outtextfile = outputFolder + "MC_EventsForMixing_ttbar_2018.txt";
  if (samplenumber == 208)
    outtextfile = outputFolder + "MC_EventsForMixing_wjets_2018.txt";
  if (samplenumber == 209)
    outtextfile = outputFolder + "MC_EventsForMixing_zjets_2018.txt";

  if (samplenumber == 220)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_2018A.txt";
  if (samplenumber == 221)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_2018B.txt";
  if (samplenumber == 222)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_2018C.txt";
  if (samplenumber == 223)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W1E-6_2018D.txt";
  if (samplenumber == 224)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_2018A.txt";
  if (samplenumber == 225)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_2018B.txt";
  if (samplenumber == 226)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_2018C.txt";
  if (samplenumber == 227)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W2E-6_2018D.txt";
  if (samplenumber == 228)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_2018A.txt";
  if (samplenumber == 229)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_2018B.txt";
  if (samplenumber == 230)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_2018C.txt";
  if (samplenumber == 231)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWA0W5E-6_2018D.txt";
  if (samplenumber == 232)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_2018A.txt";
  if (samplenumber == 233)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_2018B.txt";
  if (samplenumber == 234)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_2018C.txt";
  if (samplenumber == 235)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW2E-5_2018D.txt";
  if (samplenumber == 236)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_2018A.txt";
  if (samplenumber == 237)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_2018B.txt";
  if (samplenumber == 238)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_2018C.txt";
  if (samplenumber == 239)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW5E-6_2018D.txt";
  if (samplenumber == 240)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_2018A.txt";
  if (samplenumber == 241)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_2018B.txt";
  if (samplenumber == 242)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_2018C.txt";
  if (samplenumber == 243)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_WWACW8E-6_2018D.txt";

  if (samplenumber == 250)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z-1E-5_2018A.txt";
  if (samplenumber == 251)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z1E-5_2018A.txt";
  if (samplenumber == 252)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZA0Z5E-5_2018A.txt";
  if (samplenumber == 253)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ-1E-5_2018A.txt";
  if (samplenumber == 254)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ1E-5_2018A.txt";
  if (samplenumber == 255)
    outtextfile =
        outputFolder + "MC_EventsForMixing_signal_ZZACZ5E-5_2018A.txt";

  ofstream ofs(outtextfile);

  // Mapping of sample number to era for data
  if (samplenumber < 0 && samplenumber > -4) {
    erastring = "2017preTS2";
  }
  if (samplenumber < -3 && samplenumber > -6) {
    erastring = "2017postTS2";
  }
  if (samplenumber < -5 && samplenumber > -9) {
    erastring = "2016preTS2";
  }
  if (samplenumber == -9) {
    erastring = "2016postTS2";
  }
  if (samplenumber < -9) {
    erastring = "2018";
  }
  // Mapping of sample number to era for signal MC
  if (samplenumber >= 20 && samplenumber <= 45) {
    erastring = "2017preTS2";
  }
  if (samplenumber >= 50 && samplenumber <= 61) {
    erastring = "2017postTS2";
  }
  if (samplenumber >= 120 && samplenumber < 200) {
    erastring = "2016preTS2";
  }
  if (samplenumber >= 220 && samplenumber < 300) {
    erastring = "2018";
  }

  // JH: "999" is a dummy samplenumber used for testing new ntuples
  if (samplenumber == 999)
    erastring = "2016preTS2";
  //     erastring = "2018";
  //     erastring = "2017preTS2";

  // Proton efficiencies
  PPSProtonEfficiency eff;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry > 500000)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    //       if(jentry % 20000 == 0)
    if (jentry % 200 == 0)
      cout << "Entry " << jentry << "/" << nentries << endl;

    if (jet_pt->size() < 2)
      continue;

    Int_t passht = 0;
    Int_t passpfjet = 0;
    Int_t passpfjettrim = 0;
    Int_t passpfhttrim = 0;

    /* Now filtering on HLT at ntuple-making level!
    for(Int_t j = 0; j < hlt->size(); j++)
      {
        TString myhlt = hlt->at(j);
        if(strstr(myhlt,"HLT_PFHT1050_v")) {passht = 1;}
        if(strstr(myhlt,"HLT_AK8PFJet500_v")) {passpfjet = 1;};
        if(strstr(myhlt,"HLT_AK8PFJet360_TrimMass30_") ||
           strstr(myhlt,"HLT_AK8PFJet380_TrimMass30_") ||
           strstr(myhlt,"HLT_AK8PFJet400_TrimMass30_") ||
           strstr(myhlt,"HLT_AK8PFJet420_TrimMass30_")) {passpfjettrim = 1;}
        if(strstr(myhlt,"HLT_AK8PFHT750_TrimMass50_") ||
           strstr(myhlt,"HLT_AK8PFHT800_TrimMass50_") ||
           strstr(myhlt,"HLT_AK8PFHT850_TrimMass50_") ||
           strstr(myhlt,"HLT_AK8PFHT900_TrimMass50_")) {passpfhttrim = 1;}
      }

    if((passht == 1) || (passpfjet == 1) || (passpfhttrim == 1) ||
    (passpfjettrim == 1))
    */
    if (1) {
      Float_t ptjet1 = 0.0;
      Float_t ptjet2 = 0.0;
      Float_t etajet1 = 0.0;
      Float_t etajet2 = 0.0;
      Float_t phijet1 = 0.0;
      Float_t phijet2 = 0.0;
      Float_t ejet1 = 0.0;
      Float_t ejet2 = 0.0;
      Float_t rotatedprunedmasses = 0.0;
      int indleading = 0;
      int indsecond = 1;

      TLorentzVector jet1;
      TLorentzVector jet2;
      TLorentzVector mydijet;
      float C_JER1 = -999.;
      float C_JER2 = -999.;

      if (samplenumber > 0) {
        myweight = pileupWeight;

        /* Apply JER smearing */
        TLorentzVector recojtmp, genjtmp;
        TRandom3 randomSrc;
        int matchedgen = 0;
        int indmatchedgen = -1;
        float ptleading = 0;
        float ptsecond = 0;
        float C_JER = -999;

        //       cout << "Starting checks on JER" << endl;
        for (int ir = 0; ir < jet_pt->size(); ir++) {
          recojtmp.SetPtEtaPhiE(jet_pt->at(ir), jet_eta->at(ir),
                                jet_phi->at(ir), jet_energy->at(ir));

          for (int ig = 0; ig < gen_jet_pt->size();
               ig++) { // loop over gen jets
            genjtmp.SetPtEtaPhiE(gen_jet_pt->at(ig), gen_jet_eta->at(ig),
                                 gen_jet_phi->at(ig), gen_jet_energy->at(ig));
            if ((recojtmp.DeltaR(genjtmp) < (0.8 / 2.)) &&
                (fabs(recojtmp.Pt() - genjtmp.Pt()) <
                 (3 * jet_jer_res->at(ir) * recojtmp.Pt()))) {
              matchedgen = 1;
              indmatchedgen = ig;
            }
            // 0.8 is cone radius
          }
          if (matchedgen == 1) {
            C_JER = 1 + (jet_jer_sf->at(ir) - 1) *
                            ((recojtmp.Pt() - gen_jet_pt->at(indmatchedgen)) /
                             recojtmp.Pt());
            if (C_JER < 0) {
              C_JER = 0;
            }
          } else {
            C_JER =
                1 + randomSrc.Gaus(0, jet_jer_res->at(ir)) *
                        (sqrt(max(jet_jer_sf->at(ir) * jet_jer_sf->at(ir) - 1.,
                                  0.)));
          }

          // Re-check for the leading and second leading jets after JER
          // correction
          //   cout << "\tChecking " << C_JER*recojtmp.Pt() << " against leading
          //   pT = " << ptleading << ", second leading pT = " << ptsecond <<
          //   endl;
          if (C_JER * recojtmp.Pt() > ptleading) {
            // If we already found 1 jet with lower pT, make that the second
            // leading jet
            if (ptleading > 0) {
              ptsecond = ptleading;
              indsecond = indleading;
              C_JER2 = C_JER1;
            }
            ptleading = C_JER * recojtmp.Pt();
            C_JER1 = C_JER;
            indleading = ir;
            //       cout << "\t\tSetting new leading to pT = " << ptleading <<
            //       ", index = " << indleading << endl;
          }
          if ((C_JER * recojtmp.Pt() > ptsecond) &&
              (C_JER * recojtmp.Pt() < ptleading) && (ir != indleading)) {
            //       cout << "\t\t" << C_JER*recojtmp.Pt() << " is greater than
            //       " << ptsecond << " and less than " << ptleading << endl;
            ptsecond = C_JER * recojtmp.Pt();
            C_JER2 = C_JER;
            indsecond = ir;
            //       cout << "\t\tSetting new second leading to pT = " <<
            //       ptsecond << ", index = " << indsecond << endl;
          }
          //   cout << "\tjet size = " << jet_pt->size() << ", leading index = "
          //   << indleading << ", second leading index = " << indsecond <<
          //   endl;
        }

        ptjet1 = ptleading;
        etajet1 = jet_eta->at(indleading);
        phijet1 = jet_phi->at(indleading);
        ejet1 = jet_energy->at(indleading);

        ptjet2 = ptsecond;
        etajet2 = jet_eta->at(indsecond);
        phijet2 = jet_phi->at(indsecond);
        ejet2 = jet_energy->at(indsecond);
        /* End JER smearing */
      } else {
        ptjet1 = jet_pt->at(0);
        etajet1 = jet_eta->at(0);
        phijet1 = jet_phi->at(0);
        ejet1 = jet_energy->at(0);
        ptjet2 = jet_pt->at(1);
        etajet2 = jet_eta->at(1);
        phijet2 = jet_phi->at(1);
        ejet2 = jet_energy->at(1);
        indleading = 0;
        indsecond = 1;
      }
      // We don't have 2 jets - skip this event
      if (ptjet1 == 0 || ptjet2 == 0)
        continue;

      // JEC systematics
      if (DOJECSYSTEMATICSUP || DOJECSYSTEMATICSDOWN) {
        float jecscale1 = 0.0;
        float jecscale2 = 0.0;
        jectotal->setJetPt(ptjet1);
        jectotal->setJetEta(etajet1);
        if (DOJECSYSTEMATICSUP)
          jecscale1 = (1.0 + jectotal->getUncertainty(true));
        if (DOJECSYSTEMATICSDOWN)
          jecscale1 = (1.0 - jectotal->getUncertainty(true));
        jectotal->setJetPt(ptjet2);
        jectotal->setJetEta(etajet2);
        if (DOJECSYSTEMATICSUP)
          jecscale2 = (1.0 + jectotal->getUncertainty(true));
        if (DOJECSYSTEMATICSDOWN)
          jecscale2 = (1.0 - jectotal->getUncertainty(true));

        ptjet1 *= jecscale1;
        etajet1 *= jecscale1;
        phijet1 *= jecscale1;
        ejet1 *= jecscale1;
        ptjet2 *= jecscale2;
        etajet2 *= jecscale2;
        phijet2 *= jecscale2;
        ejet2 *= jecscale2;
      }

      Float_t xijets1 = (1.0 / 13000.0) * (ptjet1 * TMath::Exp(etajet1) +
                                           ptjet2 * TMath::Exp(etajet2));
      Float_t xijets2 = (1.0 / 13000.0) * (ptjet1 * TMath::Exp(-1 * etajet1) +
                                           ptjet2 * TMath::Exp(-1 * etajet2));

      //	   Float_t genxijets1 =
      //(1.0/13000.0)*(gen_jet_pt->at(0)*TMath::Exp(gen_jet_eta->at(0)) +
      // gen_jet_pt->at(1)*TMath::Exp(gen_jet_eta->at(1))); 	   Float_t
      // genxijets2 =
      //(1.0/13000.0)*(gen_jet_pt->at(0)*TMath::Exp(-1*gen_jet_eta->at(0)) +
      // gen_jet_pt->at(1)*TMath::Exp(-1*gen_jet_eta->at(1)));

      jet1.SetPtEtaPhiE(ptjet1, etajet1, phijet1, ejet1);
      jet2.SetPtEtaPhiE(ptjet2, etajet2, phijet2, ejet2);

      mydijet = jet1 + jet2;

      Float_t mwlowpreselcut = 55.0;
      Float_t mwhipreselcut = 215.0;

      /*
       * Now start preselection cuts
       */
      if (jet1.Pt() > 200 && jet2.Pt() > 200 &&
          fabs(jet_eta->at(indleading)) < 2.5 &&
          fabs(jet_eta->at(indsecond)) < 2.5) {
        if ((fabs(jet_eta->at(indleading) - jet_eta->at(indsecond)) < 1.3)) {
          hmjjdat->Fill(mydijet.M(), myweight);
          hyjjdat->Fill(mydijet.Rapidity(), myweight);
          hmyjjdat->Fill(mydijet.M(), mydijet.Rapidity());
          if (passpfjet == 1)
            hmjjdatpfjet->Fill(mydijet.M(), myweight);
          if (passpfhttrim == 1)
            hmjjdatpfhttrim->Fill(mydijet.M(), myweight);

          if (mydijet.M() > 1126 && mydijet.M() < 2500) {

            Float_t rhoprime1 = 0;
            Float_t taut21ddt1 = 0;
            Float_t rhoprime2 = 0;
            Float_t taut21ddt2 = 0;

            npasspresel += 1.0 * myweight;

            if (jet_corrmass->at(indleading) >= mwlowpreselcut &&
                jet_corrmass->at(indleading) <= mwhipreselcut) {
              htau21dat1->Fill(jet_tau2->at(indleading) /
                                   jet_tau1->at(indleading),
                               myweight);
              hmjdat1->Fill(jet_corrmass->at(indleading), myweight);
              rhoprime1 = TMath::Log(jet_corrmass->at(indleading) *
                                     jet_corrmass->at(indleading) /
                                     jet_pt->at(indleading));
              tau21vrhoprime1->Fill(rhoprime1, jet_tau2->at(indleading) /
                                                   jet_tau1->at(indleading));
              taut21ddt1 =
                  (jet_tau2->at(indleading) / jet_tau1->at(indleading)) -
                  (-0.082 * rhoprime1);
              htau21ddtdat1->Fill(taut21ddt1, myweight);
            }
            if (jet_corrmass->at(indsecond) >= mwlowpreselcut &&
                jet_corrmass->at(indsecond) <= mwhipreselcut) {
              htau21dat2->Fill(
                  jet_tau2->at(indsecond) / jet_tau1->at(indsecond), myweight);
              hmjdat2->Fill(jet_corrmass->at(indsecond), myweight);
              rhoprime2 = TMath::Log(jet_corrmass->at(indsecond) *
                                     jet_corrmass->at(indsecond) /
                                     jet_pt->at(indsecond));
              tau21vrhoprime2->Fill(rhoprime2, jet_tau2->at(indsecond) /
                                                   jet_tau1->at(indsecond));
              taut21ddt2 = (jet_tau2->at(indsecond) / jet_tau1->at(indsecond)) -
                           (-0.082 * rhoprime2);
              htau21ddtdat2->Fill(taut21ddt2, myweight);
            }
            hptdat1->Fill(jet_pt->at(indleading), myweight);
            hptdat2->Fill(jet_pt->at(indsecond), myweight);
            hetadat1->Fill(jet_eta->at(indleading), myweight);
            hetadat2->Fill(jet_eta->at(indsecond), myweight);
            hphidat1->Fill(jet_phi->at(indleading), myweight);
            hphidat2->Fill(jet_phi->at(indsecond), myweight);
            xijets45->Fill(xijets1);
            xijets56->Fill(xijets2);

            // Ksenia's rotation of the pruned mass correlation for WW/ZZ
            // separation
            rotatedprunedmasses =
                (TMath::Cos(TMath::Pi() / 4.0) * jet_corrmass->at(indleading)) +
                (TMath::Sin(TMath::Pi() / 4.0) * jet_corrmass->at(indsecond));
            if (jet_corrmass->at(indleading) >= 55 &&
                jet_corrmass->at(indleading) <= 215 &&
                jet_corrmass->at(indsecond) >= 55 &&
                jet_corrmass->at(indsecond) <= 215)
              hprunedrotatedjjdat->Fill(rotatedprunedmasses, myweight);
            //		       resxijets45->Fill(xijets1/genxijets1);
            //		       resxijets56->Fill(xijets2/genxijets2);
            //		       resxijetscorr45->Fill(xijets1,genxijets1);
            //		       resxijetscorr56->Fill(xijets2,genxijets2);
            hdeta->Fill(fabs(jet_eta->at(indleading) - jet_eta->at(indsecond)),
                        myweight);
            hnvtx->Fill(nVertices, myweight);
            hcrossingangle->Fill(crossingangle, myweight);
            hptratio->Fill(jet1.Pt() / jet2.Pt(), myweight);

            float dphi = fabs(jet_phi->at(indleading) - jet_phi->at(indsecond));
            if (dphi > 3.14159)
              dphi = (2 * 3.14159) - dphi;
            float acop = 1 - (dphi / 3.14159);
            hacopdat->Fill(acop, myweight);
            //		       std::cout << "phi1 = " << jet_phi->at(indleading)
            //<<
            //", phi2 = " << jet_phi->at(indsecond) << ", dphi = " << dphi
            //				 << ", acop = " << acop << std::endl;

            Float_t ptbalcut = 1.3;
            Float_t acopcut = 0.01;
            Float_t mwlowcut = 60.0;
            Float_t mwhicut = 107.0;
            Float_t mrotatedcut = 117.8;
            Float_t tau21cut = 0.75;
            Float_t massmatchcutksenia = 0.11506000;
            Float_t rapiditymatchcutksenia = 0.057220000;
            Float_t massmatchnormregion = 1.0;
            Float_t rapiditymatchnormregion = 0.5;

            // Proton part
            float mpp = 0;
            float ypp = 0;

            float mppmm = 0;
            float yppmm = 0;

            float mppshiftup = 0;
            float mppshiftdown = 0;
            float yppshiftup = 0;
            float yppshiftdown = 0;

            int ismultimulti = 0;
            int nSinglePixelTracks45 = 0;
            int nSinglePixelTracks56 = 0;
            int nMultiTracks45 = 0;
            int nMultiTracks56 = 0;
            int nMultiRP = 0;
            float xigen45 = 0;
            float xigen56 = 0;
            float mppgen = 0;

            // Multiple candidate selection for 2018. Record and select the
            // highest xi protons
            float ximaxmulti45 = -999;
            float ximaxmulti56 = -999;
            int indexmaxmulti45 = -1;
            int indexmaxmulti56 = -1;

            if (proton_xi->size() > 1) {
              float thexi = 0;
              float thethetasty = 0;
              float thethetastx = 0;
              float thet = 0;
              float thetime = -999;
              float thetax1 = 0;
              float thetay1 = 0;
              float thetax2 = 0;
              float thetay2 = 0;
              int rpid1 = 0;
              int rpid2 = 0;
              int thex1 = 0;
              int thex2 = 0;
              int they1 = 0;
              int they2 = 0;
              int theshift1 = -1;
              int theshift2 = -1;
              int thearm = -1;

              float deltaxi = 0;

              float xishiftmag56 = 0;
              float xishiftmag45 = 0;

              /*
               * First loop over all protons to get good multi-RP candidates and
               * apply eff. corrections to MC
               */
              for (int p = 0; p < proton_xi->size(); p++) {
                if (proton_ismultirp->at(p) == 1) {
                  thexi = proton_xi->at(p);

                  thethetasty = proton_thy->at(p);
                  thethetastx = proton_thx->at(p);
                  thet = -1.0 * proton_t->at(p);
                  thetime = proton_time->at(p);
                  rpid1 = proton_rpid1->at(p);
                  rpid2 = proton_rpid2->at(nMultiRP);
                  thex1 = proton_trackx1->at(p);
                  thex2 = proton_trackx2->at(nMultiRP);
                  they1 = proton_tracky1->at(p);
                  they2 = proton_tracky2->at(nMultiRP);
                  theshift1 = proton_trackpixshift1->at(p);
                  theshift2 = proton_trackpixshift2->at(nMultiRP);
                  thearm = proton_arm->at(p);

                  // SYSTEMATICS SMEARING
                  if (DOPROTONSYSTEMATICS) {
                    deltaxi = ransource.Gaus(
                        0., getUncSigma(thearm, erastring, thexi));
                    thexi += deltaxi;
                  }

                  nMultiRP++;

                  // Apply all good proton cuts
                  bool passesselector = false;
                  bool passesprotonefficiency = true;
                  if (samplenumber < 0) {
                    passesselector = TightMultiRPProton(
                        thex1, they1, thex2, they2, thetax1, thetay1, thetax2,
                        thetay2, thearm, rpid1, rpid2, crossingangle, erastring,
                        thexi, thethetasty, theshift1, theshift2);
                  }

                  if (samplenumber > 0) {
                    passesselector = TightMultiRPProton(
                        thex1, they1, thex2, they2, thetax1, thetay1, thetax2,
                        thetay2, thearm, rpid1, rpid2, crossingangle, erastring,
                        thexi, thethetasty, theshift1, theshift2);

                    // Note: As of Nov. 2020, the efficiencies are applied at
                    // the ntuple-making level (A. Bellora). Therefore we do not
                    // re-apply them here, but leave the call commented out in
                    // case it's needed to compare to older studies.
                    // passesprotonefficiency =
                    // eff.GetMultiRPAcceptRejectDecision(thex1, they1, thex2,
                    // they2, rpid1, rpid2, erastring);
                    passesprotonefficiency = true;
                  }

                  if ((passesselector == true) &&
                      (passesprotonefficiency == true) && (thexi >= 0.05)) {
                    if (thearm == 0) {
                      if (thexi > ximaxmulti45) {
                        ximaxmulti45 = thexi;
                        indexmaxmulti45 = nMultiTracks45;
                      }

                      ximulti45s->push_back(thexi);
                      thystmulti45s->push_back(thethetasty);
                      tmulti45s->push_back(thet);
                      timemulti45s->push_back(thetime);

                      nMultiTracks45++;

                      // Apply xi scale systematic shifts for MC
                      // For now comment this out, until systematics ROOT file
                      // is officially released
                      /*
                      if(samplenumber > 0)
                        {
                          xishiftmag45 =
                      eff.GetMultiRPXiScaleUncertainty(thearm, thexi,
                      erastring); xishiftmultis45->push_back(xishiftmag45);
                        }
                      */
                    }
                    if (thearm == 1) {
                      if (thexi > ximaxmulti56) {
                        ximaxmulti56 = thexi;
                        indexmaxmulti56 = nMultiTracks56;
                      }

                      ximulti56s->push_back(thexi);
                      thystmulti56s->push_back(thethetasty);
                      tmulti56s->push_back(thet);
                      timemulti56s->push_back(thetime);

                      nMultiTracks56++;

                      // Apply xi scale systematic shifts for MC
                      // For now comment this out, until systematics ROOT file
                      // is officially released
                      /*
                      if(samplenumber > 0)
                        {
                          xishiftmag56 =
                      eff.GetMultiRPXiScaleUncertainty(thearm, thexi,
                      erastring); xishiftmultis56->push_back(xishiftmag56);
                        }
                      */
                    }
                  }
                }
              }

              /*
               * Now select 2-arm events. Exclude events with >3 tracks/arm in
               * 2018, to reduce showers.
               */
              if (nMultiTracks45 > 0 && nMultiTracks56 > 0 &&
                  nMultiTracks45 < 4 && nMultiTracks56 < 4) {
                // single-arm distributions
                hximult45->Fill(ximulti45s->at(indexmaxmulti45));
                hthystmult45->Fill(thystmulti45s->at(indexmaxmulti45));
                htmult45->Fill(tmulti45s->at(indexmaxmulti45));

                hximult56->Fill(ximulti56s->at(indexmaxmulti56));
                hthystmult56->Fill(thystmulti56s->at(indexmaxmulti56));
                htmult56->Fill(tmulti56s->at(indexmaxmulti56));

                // 2-arm combinations: mass, rapidity, and timing
                mpp = TMath::Sqrt(13000.0 * 13000.0 *
                                  ximulti56s->at(indexmaxmulti56) *
                                  ximulti45s->at(indexmaxmulti45));
                ypp = -0.5 * TMath::Log(ximulti56s->at(indexmaxmulti56) /
                                        ximulti45s->at(indexmaxmulti45));

                // For now comment systematic scale shifts, until official
                // release
                /*
                mppshiftup = TMath::Sqrt(13000.0*13000.0*
                                         (ximulti56s->at(indexmaxmulti56)+xishiftmultis56->at(indexmaxmulti56))*
                                         (ximulti45s->at(indexmaxmulti45)+xishiftmultis45->at(indexmaxmulti45)));
                yppshiftup =
                -0.5*TMath::Log((ximulti56s->at(indexmaxmulti56)+xishiftmultis56->at(indexmaxmulti56))/
                                             (ximulti45s->at(indexmaxmulti45)+xishiftmultis45->at(indexmaxmulti45)));
                mppshiftdown = TMath::Sqrt(13000.0*13000.0*
                                         (ximulti56s->at(indexmaxmulti56)-xishiftmultis56->at(indexmaxmulti56))*
                                           (ximulti45s->at(indexmaxmulti45)-xishiftmultis45->at(indexmaxmulti45)));
                yppshiftdown =
                -0.5*TMath::Log((ximulti56s->at(indexmaxmulti56)-xishiftmultis56->at(indexmaxmulti56))/
                                             (ximulti45s->at(indexmaxmulti45)-xishiftmultis45->at(indexmaxmulti45)));
                */

                mppmm = mpp;
                yppmm = ypp;
                mppsmultmult->push_back(mpp);
                yppsmultmult->push_back(ypp);
                mppsmultmultshiftup->push_back(mppshiftup);
                mppsmultmultshiftdown->push_back(mppshiftdown);
                yppsmultmultshiftup->push_back(yppshiftup);
                yppsmultmultshiftdown->push_back(yppshiftdown);

                hmppmulti->Fill(mpp);
                hyppmulti->Fill(ypp);
                hmyppmulti->Fill(mpp, ypp);

                hmasscorrpreseldatmult->Fill(mpp, mydijet.M());
                hycorrpreseldatmult->Fill(ypp, mydijet.Rapidity());
                dymassratiocorrpreseldatmult->Fill(1 - mydijet.M() / mpp,
                                                   mydijet.Rapidity() - ypp);

                hdtmulti->Fill(timemulti45s->at(indexmaxmulti45) -
                               timemulti56s->at(indexmaxmulti56));
                ismultimulti = 1;
                npassppsbeforecuts += 1.0 * myweight;
              }

              // Old - all combinations
              /*
              for(int a = 0; a < nMultiTracks45; a++)
                {
                  for(int b = 0; b < nMultiTracks56; b++)
                    {
                      mpp =
              TMath::Sqrt(13000.0*13000.0*ximulti56s->at(b)*ximulti45s->at(a));
                      ypp =
              -0.5*TMath::Log(ximulti56s->at(b)/ximulti45s->at(a));

                      mppmm = mpp;
                      yppmm = ypp;
                      mppsmultmult->push_back(mpp);
                      yppsmultmult->push_back(ypp);
                      hmppmulti->Fill(mpp);
                      hyppmulti->Fill(ypp);
                      hmyppmulti->Fill(mpp,ypp);
                      hmasscorrpreseldatmult->Fill(mpp,mydijet.M());
                      hycorrpreseldatmult->Fill(ypp,mydijet.Rapidity());
                      dymassratiocorrpreseldatmult->Fill(1-mydijet.M()/mpp,mydijet.Rapidity()-ypp);
                      hdtmulti->Fill(timemulti45s->at(a) - timemulti56s->at(b));
                      ismultimulti = 1;
                    }
                }
              */
            }

            hnmult45->Fill(nMultiTracks45);
            hnmult56->Fill(nMultiTracks56);

            // Mass/rapidity match cuts
            // Ksenia cuts: straight cuts
            // Andrea cuts: diamond + bands 

            // Average values for different samples
            float slope_1 = 0.792079;
            float intercept_1 = 0.002;
            float sigma_1 = 0.06675;
            float slope_2 = -0.866082;
            float intercept_2 = -0.013625;
            float sigma_2 = 0.058625;

            float nSigmaDiamond = 1.25;
            float nSigmaBands = 0.75;

            float massmatchratio = 999;
            float rapiditydelta = 999;
            if (mppsmultmult->size() > 0) {
              massmatchratio = 1 - (mydijet.M() / mppsmultmult->at(0));
              rapiditydelta = yppsmultmult->at(0) - mydijet.Rapidity();
            }

            bool passkseniacut_signalA =
                (fabs(massmatchratio) <= massmatchcutksenia) &&
                (fabs(rapiditydelta) <= rapiditymatchcutksenia);
            bool passkseniacut_signalB = false;

            bool innormregion = (fabs(massmatchratio) > massmatchnormregion) ||
                                (fabs(rapiditydelta) > rapiditymatchnormregion);

            bool inband_1_Diamond =
                ((massmatchratio * slope_1 + intercept_1 -
                  nSigmaDiamond * sigma_1) < rapiditydelta) &&
                (rapiditydelta < (massmatchratio * slope_1 + intercept_1 +
                                  nSigmaDiamond * sigma_1));
            bool inband_2_Diamond =
                ((massmatchratio * slope_2 + intercept_2 -
                  nSigmaDiamond * sigma_2) < rapiditydelta) &&
                (rapiditydelta < (massmatchratio * slope_2 + intercept_2 +
                                  nSigmaDiamond * sigma_2));
            bool inband_1_Bands =
                ((massmatchratio * slope_1 + intercept_1 -
                  nSigmaBands * sigma_1) < rapiditydelta) &&
                (rapiditydelta < (massmatchratio * slope_1 + intercept_1 +
                                  nSigmaBands * sigma_1));
            bool inband_2_Bands =
                ((massmatchratio * slope_2 + intercept_2 -
                  nSigmaBands * sigma_2) < rapiditydelta) &&
                (rapiditydelta < (massmatchratio * slope_2 + intercept_2 +
                                  nSigmaBands * sigma_2));

            bool passandreacut_signalA =
                (!innormregion) && (inband_1_Diamond && inband_2_Diamond);
            bool passandreacut_signalB =
                (!innormregion) && (inband_1_Bands || inband_2_Bands) &&
                (!passandreacut_signalA) && (massmatchratio < 0);

            bool passmassrapiditymatch_signalA = passandreacut_signalA;
            bool passmassrapiditymatch_signalB = passandreacut_signalB;
            // bool passmassrapiditymatch_signalA = passkseniacut_signalA;
            // bool passmassrapiditymatch_signalB = passkseniacut_signalB;

            // Signal region, only for MC
            if (samplenumber > 0) {
              // Output txt files for mixing. Apply xi_jets, pruned mass, and pT
              // balance cuts
              if (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 &&
                  xijets2 < 0.205 &&
                  (jet_corrmass->at(indleading) >= mwlowcut &&
                   jet_corrmass->at(indleading) <= mwhicut) &&
                  (jet_corrmass->at(indsecond) >= mwlowcut &&
                   jet_corrmass->at(indsecond) <= mwhicut) &&
                  (jet1.Pt() / jet2.Pt() < ptbalcut)) {
                ofs << samplenumber << " " << mc_pu_trueinteractions_ << " "
                    << pileupWeight << " " << mydijet.M() << " "
                    << mydijet.Rapidity() << " " << acop << " "
                    << (jet1.Pt() / jet2.Pt()) << " "
                    << jet_corrmass->at(indleading) << " "
                    << jet_corrmass->at(indsecond) << " " << taut21ddt1 << " "
                    << taut21ddt2 << " " << xijets1 << " " << xijets2 << " "
                    << run << " " << lumiblock << " " << event << " "
                    << ximaxmulti45 << " " << ximaxmulti56 << std::endl;
              }
              if ((acop < acopcut) && (jet1.Pt() / jet2.Pt() < ptbalcut)) {
                npassdijetkine += 1.0 * myweight;
                if ((jet_corrmass->at(indleading) >= mwlowcut &&
                     jet_corrmass->at(indleading) <= mwhicut) &&
                    (jet_corrmass->at(indsecond) >= mwlowcut &&
                     jet_corrmass->at(indsecond) <= mwhicut) &&
                    (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut)) {
                  npassjetsubstr += 1.0 * myweight;

                  // Just counting
                  if (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 &&
                      xijets2 < 0.205)
                    npassjetxi += 1.0 * myweight;

                  if (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 &&
                      xijets2 < 0.205) {
                    if (rotatedprunedmasses <= mrotatedcut) {
                      hmassvvsignalww->Fill(mydijet.M());
                      hywwsignalww->Fill(mydijet.Rapidity());
                    }
                    if (rotatedprunedmasses > mrotatedcut) {
                      hmassvvsignalzz->Fill(mydijet.M());
                      hywwsignalzz->Fill(mydijet.Rapidity());
                    }
                    if (mpp > 0) // MC events with protons - e.g. signal MC
                    {
                      for (Int_t s = 0; s < mppsmultmult->size(); s++) {
                        if (rotatedprunedmasses <= mrotatedcut) {
                          hmassmatchsigmcmmww->Fill(
                              mppsmultmult->at(s) - mydijet.M(), myweight);
                          hymatchsigmcmmww->Fill(yppsmultmult->at(s) -
                                                     mydijet.Rapidity(),
                                                 myweight);
                          hmassmatchratiosigmcmmww->Fill(
                              1 - (mydijet.M() / mppsmultmult->at(s)),
                              myweight);
                          hmassmatchratiosigmcmmshiftupww->Fill(
                              1 - (mydijet.M() / mppsmultmultshiftup->at(s)),
                              myweight);
                          hmassmatchratiosigmcmmshiftdownww->Fill(
                              1 - (mydijet.M() / mppsmultmultshiftdown->at(s)),
                              myweight);
                          hymatchsigmcmmshiftupww->Fill(
                              yppsmultmultshiftup->at(s) - mydijet.Rapidity(),
                              myweight);
                          hymatchsigmcmmshiftdownww->Fill(
                              yppsmultmultshiftdown->at(s) - mydijet.Rapidity(),
                              myweight);
                        }
                        if (rotatedprunedmasses > mrotatedcut) {
                          hmassmatchsigmcmmzz->Fill(
                              mppsmultmult->at(s) - mydijet.M(), myweight);
                          hymatchsigmcmmzz->Fill(yppsmultmult->at(s) -
                                                     mydijet.Rapidity(),
                                                 myweight);
                          hmassmatchratiosigmcmmzz->Fill(
                              1 - (mydijet.M() / mppsmultmult->at(s)),
                              myweight);
                          hmassmatchratiosigmcmmshiftupzz->Fill(
                              1 - (mydijet.M() / mppsmultmultshiftup->at(s)),
                              myweight);
                          hmassmatchratiosigmcmmshiftdownzz->Fill(
                              1 - (mydijet.M() / mppsmultmultshiftdown->at(s)),
                              myweight);
                          hymatchsigmcmmshiftupzz->Fill(
                              yppsmultmultshiftup->at(s) - mydijet.Rapidity(),
                              myweight);
                          hymatchsigmcmmshiftdownzz->Fill(
                              yppsmultmultshiftdown->at(s) - mydijet.Rapidity(),
                              myweight);
                        }
                      }

                      int match45 = 0;
                      int match56 = 0;
                      // GEN-level proton quantities for signal MC
                      for (Int_t gp = 0; gp < gen_proton_xi->size(); gp++) {
                        if (fabs(ximaxmulti45 - gen_proton_xi->at(gp)) < 0.01 &&
                            gen_proton_pz->at(gp) > 0)
                          match45 = 1;
                        if (fabs(ximaxmulti56 - gen_proton_xi->at(gp)) < 0.01 &&
                            gen_proton_pz->at(gp) < 0)
                          match56 = 1;
                        if (gen_proton_pz->at(gp) > 0)
                          xigen45 = gen_proton_xi->at(gp);
                        if (gen_proton_pz->at(gp) < 0)
                          xigen56 = gen_proton_xi->at(gp);
                      }
                      float mppgen =
                          TMath::Sqrt(13000.0 * 13000.0 * xigen45 * xigen56);
                      float yppgen = -0.5 * TMath::Log(xigen56 / xigen45);

                      npasspps += 1.0 * myweight;

                      if (rotatedprunedmasses <= mrotatedcut) {
                        hmassmatchratiosigmcmultww->Fill(
                            1 - (mydijet.M() / mppsmultmult->at(0)), myweight);
                        hymatchsigmcmultww->Fill(
                            yppsmultmult->at(0) - mydijet.Rapidity(), myweight);
                        hmasscorrsigmcmultww->Fill(
                            mydijet.M(), mppsmultmult->at(0), myweight);
                        hycorrsigmcmultww->Fill(mydijet.Rapidity(),
                                                yppsmultmult->at(0), myweight);
                        hmassrapiditymatchsigmcmmww->Fill(
                            1 - (mydijet.M() / mppsmultmult->at(0)),
                            yppsmultmult->at(0) - mydijet.Rapidity(), myweight);

                        if (passmassrapiditymatch_signalA ||
                            passmassrapiditymatch_signalB) {
                          hmvvsigmcsigregionww->Fill(mydijet.M(), myweight);
                          hyvvsigmcsigregionww->Fill(mydijet.Rapidity(),
                                                     myweight);
                          hmppsigmcsigregionww->Fill(mppsmultmult->at(0),
                                                     myweight);
                          hyppsigmcsigregionww->Fill(yppsmultmult->at(0),
                                                     myweight);
                        }
                      }
                      if (rotatedprunedmasses > mrotatedcut) {
                        hmassmatchratiosigmcmultzz->Fill(
                            1 - (mydijet.M() / mppsmultmult->at(0)), myweight);
                        hymatchsigmcmultzz->Fill(
                            yppsmultmult->at(0) - mydijet.Rapidity(), myweight);
                        hmasscorrsigmcmultzz->Fill(
                            mydijet.M(), mppsmultmult->at(0), myweight);
                        hycorrsigmcmultzz->Fill(mydijet.Rapidity(),
                                                yppsmultmult->at(0), myweight);
                        hmassrapiditymatchsigmcmmzz->Fill(
                            1 - (mydijet.M() / mppsmultmult->at(0)),
                            yppsmultmult->at(0) - mydijet.Rapidity(), myweight);

                        if (passmassrapiditymatch_signalA ||
                            passmassrapiditymatch_signalB) {
                          hmvvsigmcsigregionzz->Fill(mydijet.M(), myweight);
                          hyvvsigmcsigregionzz->Fill(mydijet.Rapidity(),
                                                     myweight);
                          hmppsigmcsigregionzz->Fill(mppsmultmult->at(0),
                                                     myweight);
                          hyppsigmcsigregionzz->Fill(yppsmultmult->at(0),
                                                     myweight);
                        }
                      }

                      if (passmassrapiditymatch_signalA) {
                        npassppsmatch_A += 1.0 * myweight;
                        if (rotatedprunedmasses <= mrotatedcut)
                          npassppsmatchkseniaww_A += 1.0 * myweight;
                        if (rotatedprunedmasses > mrotatedcut)
                          npassppsmatchkseniazz_A += 1.0 * myweight;
                      } else {
                        hgenxinomatch->Fill(xigen45, xigen56);
                      }
                      if (passmassrapiditymatch_signalB) {
                        npassppsmatch_B += 1.0 * myweight;
                        if (rotatedprunedmasses <= mrotatedcut)
                          npassppsmatchkseniaww_B += 1.0 * myweight;
                        if (rotatedprunedmasses > mrotatedcut)
                          npassppsmatchkseniazz_B += 1.0 * myweight;
                      } else {
                        hgenxinomatch->Fill(xigen45, xigen56);
                      }

                      if (match45 == 1 && match56 == 1) {
                        if (rotatedprunedmasses <= mrotatedcut)
                          hmasscorrsigmcmulttruthmatchedww->Fill(
                              mydijet.M(), mppsmultmult->at(0));
                        if (rotatedprunedmasses > mrotatedcut)
                          hmasscorrsigmcmulttruthmatchedzz->Fill(
                              mydijet.M(), mppsmultmult->at(0));
                      }

                      // JH - testing with 2018 hard-coded values
                      //					   if((xigen45 >
                      //(0.079 + (4.21E-4 * crossingangle))) || (xigen56 >
                      //(0.074 + (6.6E-4 * crossingangle))))
                      // JH - testing with 2017preTS2 hard-coded values
                      if ((xigen45 > (0.066 + (3.54E-4 * crossingangle))) ||
                          (xigen56 > (0.062 + (5.96E-4 * crossingangle)))) {
                        hmassmatchratiosigmcoutofacceptancemm->Fill(
                            (1 - (mydijet.M() / mppsmultmult->at(0))));
                        hymatchsigmcoutofacceptancemm->Fill(
                            mydijet.Rapidity() - yppsmultmult->at(0));
                      } else {
                        hmassmatchratiosigmcinacceptancemm->Fill(
                            (1 - (mydijet.M() / mppsmultmult->at(0))));
                        hymatchsigmcinacceptancemm->Fill(mydijet.Rapidity() -
                                                         yppsmultmult->at(0));
                        if (match45 == 0 || match56 == 0) {
                          hmassmatchratiosigmcinacceptancenomatchmm->Fill(
                              (1 - (mydijet.M() / mppsmultmult->at(0))));
                          hymatchsigmcinacceptancenomatchmm->Fill(
                              mydijet.Rapidity() - yppsmultmult->at(0));
                        }
                      }
                    }
                  }
                }
              }
            }

            // Control regions in data and background MC
            if (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 &&
                xijets2 < 0.205) {
              // Anti acoplanarity
              if ((acop > acopcut) &&
                  (jet_corrmass->at(indleading) >= mwlowcut &&
                   jet_corrmass->at(indleading) <= mwhicut) &&
                  (jet_corrmass->at(indsecond) >= mwlowcut &&
                   jet_corrmass->at(indsecond) <= mwhicut) &&
                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                  (jet1.Pt() / jet2.Pt() < ptbalcut)) {
                if (rotatedprunedmasses <= mrotatedcut) {
                  hmassvvantiacopww->Fill(mydijet.M(), myweight);
                  hmj1antiacopww->Fill(jet_corrmass->at(indleading), myweight);
                  hmj2antiacopww->Fill(jet_corrmass->at(indsecond), myweight);
                  htau211antiacopww->Fill(taut21ddt1, myweight);
                  htau212antiacopww->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiacopmmww->Fill(mppmm - mydijet.M(), myweight);
                    hymatchantiacopmmww->Fill(yppmm - mydijet.Rapidity(),
                                              myweight);
                    hmassmatchratioantiacopmmww->Fill(1 - (mydijet.M() / mppmm),
                                                      myweight);
                    hmassrapiditymatchantiacopmmww->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA) {
                      npassantiacopsigregionww_A += 1.0 * myweight;
                      hmvvsigmcantiacopsigregionww->Fill(mydijet.M(), myweight);
                      hyvvsigmcantiacopsigregionww->Fill(mydijet.Rapidity(),
                                                         myweight);
                      hmppsigmcantiacopsigregionww->Fill(mppsmultmult->at(0),
                                                         myweight);
                      hyppsigmcantiacopsigregionww->Fill(yppsmultmult->at(0),
                                                         myweight);
                    }
                    if (passmassrapiditymatch_signalB) {
                      npassantiacopsigregionww_B += 1.0 * myweight;
                      hmvvsigmcantiacopsigregionww->Fill(mydijet.M(), myweight);
                      hyvvsigmcantiacopsigregionww->Fill(mydijet.Rapidity(),
                                                         myweight);
                      hmppsigmcantiacopsigregionww->Fill(mppsmultmult->at(0),
                                                         myweight);
                      hyppsigmcantiacopsigregionww->Fill(yppsmultmult->at(0),
                                                         myweight);
                    }
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantiacopnormregionww += 1.0 * myweight;
                  }
                }
                if (rotatedprunedmasses > mrotatedcut) {
                  hmassvvantiacopzz->Fill(mydijet.M(), myweight);
                  hmj1antiacopzz->Fill(jet_corrmass->at(indleading), myweight);
                  hmj2antiacopzz->Fill(jet_corrmass->at(indsecond), myweight);
                  htau211antiacopzz->Fill(taut21ddt1, myweight);
                  htau212antiacopzz->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiacopmmzz->Fill(mppmm - mydijet.M(), myweight);
                    hymatchantiacopmmzz->Fill(yppmm - mydijet.Rapidity(),
                                              myweight);
                    hmassmatchratioantiacopmmzz->Fill(1 - (mydijet.M() / mppmm),
                                                      myweight);
                    hmassrapiditymatchantiacopmmzz->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA) {
                      npassantiacopsigregionzz_A += 1.0 * myweight;
                      hmvvsigmcantiacopsigregionzz->Fill(mydijet.M(), myweight);
                      hyvvsigmcantiacopsigregionzz->Fill(mydijet.Rapidity(),
                                                         myweight);
                      hmppsigmcantiacopsigregionzz->Fill(mppsmultmult->at(0),
                                                         myweight);
                      hyppsigmcantiacopsigregionzz->Fill(yppsmultmult->at(0),
                                                         myweight);
                    }
                    if (passmassrapiditymatch_signalB) {
                      npassantiacopsigregionzz_B += 1.0 * myweight;
                      hmvvsigmcantiacopsigregionzz->Fill(mydijet.M(), myweight);
                      hyvvsigmcantiacopsigregionzz->Fill(mydijet.Rapidity(),
                                                         myweight);
                      hmppsigmcantiacopsigregionzz->Fill(mppsmultmult->at(0),
                                                         myweight);
                      hyppsigmcantiacopsigregionzz->Fill(yppsmultmult->at(0),
                                                         myweight);
                    }
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantiacopnormregionzz += 1.0 * myweight;
                  }
                }
              } // anti-acoplanarity
              // Anti pT balance
              if ((jet1.Pt() / jet2.Pt()) > ptbalcut &&
                  (jet_corrmass->at(indleading) >= mwlowcut &&
                   jet_corrmass->at(indleading) <= mwhicut) &&
                  (jet_corrmass->at(indsecond) >= mwlowcut &&
                   jet_corrmass->at(indsecond) <= mwhicut) &&
                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                  (acop < acopcut)) {
                if (rotatedprunedmasses <= mrotatedcut) {
                  hmassvvantiptbalww->Fill(mydijet.M(), myweight);

                  if (mpp > 0) {
                    hmassmatchantiptbalmmww->Fill(mppmm - mydijet.M(),
                                                  myweight);
                    hymatchantiptbalmmww->Fill(yppmm - mydijet.Rapidity(),
                                               myweight);
                    hmassmatchratioantiptbalmmww->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiptbalmmww->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);
                  }
                }
                if (rotatedprunedmasses > mrotatedcut) {
                  hmassvvantiptbalzz->Fill(mydijet.M(), myweight);

                  if (mpp > 0) {
                    hmassmatchantiptbalmmzz->Fill(mppmm - mydijet.M(),
                                                  myweight);
                    hymatchantiptbalmmzz->Fill(yppmm - mydijet.Rapidity(),
                                               myweight);
                    hmassmatchratioantiptbalmmzz->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiptbalmmzz->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);
                  }
                }
              } // anti-pT balance
              // Anti tau21
              if ((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
                  (jet_corrmass->at(indleading) >= mwlowcut &&
                   jet_corrmass->at(indleading) <= mwhicut) &&
                  (jet_corrmass->at(indsecond) >= mwlowcut &&
                   jet_corrmass->at(indsecond) <= mwhicut) &&
                  (acop < acopcut) && (jet1.Pt() / jet2.Pt()) < ptbalcut) {
                if (rotatedprunedmasses <= mrotatedcut) {
                  hmassvvantitauww->Fill(mydijet.M(), myweight);
                  hmj1antitauww->Fill(jet_corrmass->at(indleading), myweight);
                  hmj2antitauww->Fill(jet_corrmass->at(indsecond), myweight);
                  htau211antitauww->Fill(taut21ddt1, myweight);
                  htau212antitauww->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantitaummww->Fill(mppmm - mydijet.M(), myweight);
                    hymatchantitaummww->Fill(yppmm - mydijet.Rapidity(),
                                             myweight);
                    hmassmatchratioantitaummww->Fill(1 - (mydijet.M() / mppmm),
                                                     myweight);
                    hmassrapiditymatchantitaummww->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantitausigregionww_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantitausigregionww_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantitaunormregionww += 1.0 * myweight;
                  }
                }
                if (rotatedprunedmasses > mrotatedcut) {
                  hmassvvantitauzz->Fill(mydijet.M(), myweight);
                  hmj1antitauzz->Fill(jet_corrmass->at(indleading), myweight);
                  hmj2antitauzz->Fill(jet_corrmass->at(indsecond)), myweight;
                  htau211antitauzz->Fill(taut21ddt1, myweight);
                  htau212antitauzz->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantitaummzz->Fill(mppmm - mydijet.M(), myweight);
                    hymatchantitaummzz->Fill(yppmm - mydijet.Rapidity(),
                                             myweight);
                    hmassmatchratioantitaummzz->Fill(1 - (mydijet.M() / mppmm),
                                                     myweight);
                    hmassrapiditymatchantitaummzz->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantitausigregionzz_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantitausigregionzz_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantitaunormregionzz += 1.0 * myweight;
                  }
                }
              } // anti-tau21
              // anti-pruned mass
              if ((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                  (jet_corrmass->at(indleading) < mwlowcut ||
                   jet_corrmass->at(indleading) > mwhicut) &&
                  (jet_corrmass->at(indsecond) < mwlowcut ||
                   jet_corrmass->at(indsecond) > mwhicut) &&
                  (acop < acopcut) && (jet1.Pt() / jet2.Pt()) < ptbalcut) {
                if (rotatedprunedmasses <= mrotatedcut) {
                  hmassvvantiprunedww->Fill(mydijet.M(), myweight);
                  hmj1antiprunedww->Fill(jet_corrmass->at(indleading),
                                         myweight);
                  hmj2antiprunedww->Fill(jet_corrmass->at(indsecond), myweight);
                  htau211antiprunedww->Fill(taut21ddt1, myweight);
                  htau212antiprunedww->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiprunedmmww->Fill(mppmm - mydijet.M(),
                                                   myweight);
                    hymatchantiprunedmmww->Fill(yppmm - mydijet.Rapidity(),
                                                myweight);
                    hmassmatchratioantiprunedmmww->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiprunedmmww->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantimasssigregionww_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantimasssigregionww_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantimassnormregionww += 1.0 * myweight;
                  }
                }
                if (rotatedprunedmasses > mrotatedcut) {
                  hmassvvantiprunedzz->Fill(mydijet.M(), myweight);
                  hmj1antiprunedzz->Fill(jet_corrmass->at(indleading),
                                         myweight);
                  hmj2antiprunedzz->Fill(jet_corrmass->at(indsecond), myweight);
                  htau211antiprunedzz->Fill(taut21ddt1, myweight);
                  htau212antiprunedzz->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiprunedmmzz->Fill(mppmm - mydijet.M(),
                                                   myweight);
                    hymatchantiprunedmmzz->Fill(yppmm - mydijet.Rapidity(),
                                                myweight);
                    hmassmatchratioantiprunedmmzz->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiprunedmmzz->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantimasssigregionzz_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantimasssigregionzz_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantimassnormregionzz += 1.0 * myweight;
                  }
                }
              } // anti-pruned mass
              // anti-pruned mass - narrow region (55-215)
              if ((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                  (jet_corrmass->at(indleading) < mwlowcut ||
                   jet_corrmass->at(indleading) > mwhicut) &&
                  (jet_corrmass->at(indsecond) < mwlowcut ||
                   jet_corrmass->at(indsecond) > mwhicut) &&
                  (jet_corrmass->at(indleading) >= mwlowpreselcut &&
                   jet_corrmass->at(indsecond) >= mwlowpreselcut) &&
                  (jet_corrmass->at(indleading) <= mwhipreselcut &&
                   jet_corrmass->at(indsecond) <= mwhipreselcut) &&
                  (acop < acopcut) && (jet1.Pt() / jet2.Pt()) < ptbalcut) {
                if (rotatedprunedmasses <= mrotatedcut) {
                  hmassvvantiprunednarrowww->Fill(mydijet.M(), myweight);
                  hmj1antiprunednarrowww->Fill(jet_corrmass->at(indleading),
                                               myweight);
                  hmj2antiprunednarrowww->Fill(jet_corrmass->at(indsecond),
                                               myweight);
                  htau211antiprunednarrowww->Fill(taut21ddt1, myweight);
                  htau212antiprunednarrowww->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiprunednarrowmmww->Fill(mppmm - mydijet.M(),
                                                         myweight);
                    hymatchantiprunednarrowmmww->Fill(
                        yppmm - mydijet.Rapidity(), myweight);
                    hmassmatchratioantiprunednarrowmmww->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiprunednarrowmmww->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantimassnarrowsigregionww_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantimassnarrowsigregionww_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantimassnarrownormregionww += 1.0 * myweight;
                  }
                }
                if (rotatedprunedmasses > mrotatedcut) {
                  hmassvvantiprunednarrowzz->Fill(mydijet.M(), myweight);
                  hmj1antiprunednarrowzz->Fill(jet_corrmass->at(indleading),
                                               myweight);
                  hmj2antiprunednarrowzz->Fill(jet_corrmass->at(indsecond),
                                               myweight);
                  htau211antiprunednarrowzz->Fill(taut21ddt1, myweight);
                  htau212antiprunednarrowzz->Fill(taut21ddt2, myweight);

                  if (mpp > 0) {
                    hmassmatchantiprunednarrowmmzz->Fill(mppmm - mydijet.M(),
                                                         myweight);
                    hymatchantiprunednarrowmmzz->Fill(
                        yppmm - mydijet.Rapidity(), myweight);
                    hmassmatchratioantiprunednarrowmmzz->Fill(
                        1 - (mydijet.M() / mppmm), myweight);
                    hmassrapiditymatchantiprunednarrowmmzz->Fill(
                        1 - (mydijet.M() / mppmm), yppmm - mydijet.Rapidity(),
                        myweight);

                    // Sideband background method
                    if (passmassrapiditymatch_signalA)
                      npassantimassnarrowsigregionzz_A += 1.0 * myweight;
                    if (passmassrapiditymatch_signalB)
                      npassantimassnarrowsigregionzz_B += 1.0 * myweight;
                    if ((fabs(1 - (mydijet.M() / mppsmultmult->at(0))) >
                         massmatchnormregion) ||
                        (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) >
                         rapiditymatchnormregion))
                      npassantimassnarrownormregionzz += 1.0 * myweight;
                  }
                }
              } // anti-pruned mass - narrow region (55-215)
              // All cuts, but with signal region in matching blinded
              if ((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                  (jet_corrmass->at(indleading) >= mwlowcut &&
                   jet_corrmass->at(indleading) <= mwhicut) &&
                  (jet_corrmass->at(indsecond) >= mwlowcut &&
                   jet_corrmass->at(indsecond) <= mwhicut) &&
                  (acop < acopcut) && (jet1.Pt() / jet2.Pt()) < ptbalcut) {
                if (mpp > 0) {
                  Float_t massmatch = 0.0;
                  Float_t ymatch = 0.0;
                  massmatch = 1 - (mydijet.M() / mppmm);
                  ymatch = yppmm - mydijet.Rapidity();

                  // Store rotated mass variable after all central cuts, but
                  // before proton matching
                  hprunedrotatedjjprematchingdat->Fill(rotatedprunedmasses);

                  if (fabs(ymatch) > rapiditymatchnormregion ||
                      fabs(massmatch) > massmatchnormregion) {
                    if (rotatedprunedmasses <= mrotatedcut) {
                      hmassrapiditymatchvetoorsignalregionww->Fill(
                          massmatch, ymatch, myweight);
                      npassnonblindnormregionww += 1.0 * myweight;
                    }
                    if (rotatedprunedmasses > mrotatedcut) {
                      hmassrapiditymatchvetoorsignalregionzz->Fill(
                          massmatch, ymatch, myweight);
                      npassnonblindnormregionzz += 1.0 * myweight;
                    }
                    if (fabs(ymatch) > rapiditymatchnormregion &&
                        fabs(massmatch) > massmatchnormregion) {
                      if (rotatedprunedmasses <= mrotatedcut)
                        hmassrapiditymatchvetosignalregionww->Fill(
                            massmatch, ymatch, myweight);
                      if (rotatedprunedmasses > mrotatedcut)
                        hmassrapiditymatchvetosignalregionzz->Fill(
                            massmatch, ymatch, myweight);
                    }
                  }
                }
              } // blinded signal region
            }   // xi(jets)
          }     // Dijet mass
        }       // Delta-eta
      }         // Single jet pT & eta
    }

    mppsmultmult->clear();
    yppsmultmult->clear();
    xipix45s->clear();
    xipix56s->clear();
    ypix45s->clear();
    ypix56s->clear();
    ximulti45s->clear();
    ximulti56s->clear();
    thystmulti45s->clear();
    thystmulti56s->clear();
    tmulti45s->clear();
    tmulti56s->clear();
    timemulti45s->clear();
    timemulti56s->clear();
    xishiftmultis45->clear();
    xishiftmultis56->clear();
    mppsmultmultshiftup->clear();
    mppsmultmultshiftdown->clear();
    yppsmultmultshiftup->clear();
    yppsmultmultshiftdown->clear();
  }

  delete mppsmultmult;
  delete yppsmultmult;
  delete xipix45s;
  delete xipix56s;
  delete ypix45s;
  delete ypix56s;
  delete ximulti45s;
  delete ximulti56s;
  delete thystmulti45s;
  delete thystmulti56s;
  delete tmulti45s;
  delete tmulti56s;
  delete timemulti45s;
  delete timemulti56s;
  delete xishiftmultis45;
  delete xishiftmultis56;
  delete mppsmultmultshiftup;
  delete mppsmultmultshiftdown;
  delete yppsmultmultshiftup;
  delete yppsmultmultshiftdown;

  // if (Cut(ientry) < 0) continue;

  TFile *fx;

  //   TFile *fx = new
  //   TFile(outputFolder+"vars_cuts_qcdpt170to300.root","RECREATE"); TFile *fx
  //   = new TFile(outputFolder+"vars_cuts_qcdpt300to470.root","RECREATE");
  //   TFile *fx = new
  //   TFile(outputFolder+"vars_cuts_qcdpt470to600.root","RECREATE"); TFile *fx
  //   = new TFile(outputFolder+"vars_cuts_qcdpt600to800.root","RECREATE");
  //   TFile *fx = new
  //   TFile(outputFolder+"vars_cuts_qcdpt800to1000.root","RECREATE"); TFile *fx
  //   = new TFile(outputFolder+"vars_cuts_qcdpt1000to1400.root","RECREATE");
  //   TFile *fx = new
  //   TFile(outputFolder+"vars_cuts_datahist2017C.root","RECREATE"); TFile *fx
  //   = new TFile(outputFolder+"vars_cuts_exclwwa0w2point5.root","RECREATE");

  if (samplenumber == -1)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2017B.root",
                   "RECREATE");
  if (samplenumber == -2)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2017C.root",
                   "RECREATE");
  if (samplenumber == -3)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2017D.root",
                   "RECREATE");
  if (samplenumber == -4)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2017E.root",
                   "RECREATE");
  if (samplenumber == -5)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2017F.root",
                   "RECREATE");

  if (samplenumber == -6)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2016B.root",
                   "RECREATE");
  if (samplenumber == -7)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2016C.root",
                   "RECREATE");
  if (samplenumber == -8)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2016G.root",
                   "RECREATE");
  if (samplenumber == -9)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2016H.root",
                   "RECREATE");

  if (samplenumber == -10)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2018A.root",
                   "RECREATE");
  if (samplenumber == -11)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2018B.root",
                   "RECREATE");
  if (samplenumber == -12)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2018C.root",
                   "RECREATE");
  if (samplenumber == -13)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "datahist2018D.root",
                   "RECREATE");

  if (samplenumber == 1)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt170to300.root",
                   "RECREATE");
  if (samplenumber == 2)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt300to470.root",
                   "RECREATE");
  if (samplenumber == 3)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt470to600.root",
                   "RECREATE");
  if (samplenumber == 4)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt600to800.root",
                   "RECREATE");
  if (samplenumber == 5)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt800to1000.root",
                   "RECREATE");
  if (samplenumber == 6)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1000to1400.root",
                   "RECREATE");
  if (samplenumber == 7)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "ttbarhadronic.root",
                   "RECREATE");
  if (samplenumber == 8)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "wjetshadronic.root",
                   "RECREATE");
  if (samplenumber == 9)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "zjetshadronic.root",
                   "RECREATE");
  if (samplenumber == 10)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1400to1800.root",
                   "RECREATE");
  if (samplenumber == 11)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1800to2400.root",
                   "RECREATE");
  if (samplenumber == 12)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt2400to3200.root",
                   "RECREATE");

  if (samplenumber == 20)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 21)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 22)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2017D.root",
                   "RECREATE");
  if (samplenumber == 23)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 24)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 25)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2017D.root",
                   "RECREATE");
  if (samplenumber == 26)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 27)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 28)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2017D.root",
                   "RECREATE");
  if (samplenumber == 29)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 30)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 31)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2017D.root",
                   "RECREATE");
  if (samplenumber == 32)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 33)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 34)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2017D.root",
                   "RECREATE");
  if (samplenumber == 35)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 36)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2017C.root",
                   "RECREATE");
  if (samplenumber == 37)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2017D.root",
                   "RECREATE");

  if (samplenumber == 40)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z-1E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 41)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z1E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 42)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z5E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 43)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ-1E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 44)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ1E-5_preTS2_2017B.root",
                   "RECREATE");
  if (samplenumber == 45)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ5E-5_preTS2_2017B.root",
                   "RECREATE");

  if (samplenumber == 50)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 51)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_postTS2_2017F.root",
                   "RECREATE");
  if (samplenumber == 52)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 53)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_postTS2_2017F.root",
                   "RECREATE");
  if (samplenumber == 54)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 55)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_postTS2_2017F.root",
                   "RECREATE");
  if (samplenumber == 56)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 57)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_postTS2_2017F.root",
                   "RECREATE");
  if (samplenumber == 58)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 59)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_postTS2_2017F.root",
                   "RECREATE");
  if (samplenumber == 60)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_postTS2_2017E.root",
                   "RECREATE");
  if (samplenumber == 61)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_postTS2_2017F.root",
                   "RECREATE");

  // 2016
  if (samplenumber == 101)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt170to300_2016.root",
                   "RECREATE");
  if (samplenumber == 102)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt300to470_2016.root",
                   "RECREATE");
  if (samplenumber == 103)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt470to600_2016.root",
                   "RECREATE");
  if (samplenumber == 104)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt600to800_2016.root",
                   "RECREATE");
  if (samplenumber == 105)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt800to1000_2016.root",
                   "RECREATE");
  if (samplenumber == 106)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1000to1400_2016.root",
                   "RECREATE");
  if (samplenumber == 107)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "ttbarhadronic1000inf_2016.root",
                   "RECREATE");
  if (samplenumber == 108)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "wjetshadronic_2016.root",
                   "RECREATE");
  if (samplenumber == 109)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "zjetshadronic_2016.root",
                   "RECREATE");
  if (samplenumber == 110)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1400to1800_2016.root",
                   "RECREATE");
  if (samplenumber == 111)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "ttbarhadronic700ot1000_2016.root",
                   "RECREATE");

  if (samplenumber == 120)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 121)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 122)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_preTS2_2016G.root",
                   "RECREATE");
  if (samplenumber == 123)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 124)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 125)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_preTS2_2016G.root",
                   "RECREATE");
  if (samplenumber == 126)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 127)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 128)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_preTS2_2016G.root",
                   "RECREATE");
  if (samplenumber == 129)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 130)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 131)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_preTS2_2016G.root",
                   "RECREATE");
  if (samplenumber == 132)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 133)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 134)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_preTS2_2016G.root",
                   "RECREATE");
  if (samplenumber == 135)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 136)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2016C.root",
                   "RECREATE");
  if (samplenumber == 137)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_preTS2_2016G.root",
                   "RECREATE");

  if (samplenumber == 140)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z-1E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 141)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z1E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 142)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z5E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 143)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ-1E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 144)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ1E-5_preTS2_2016B.root",
                   "RECREATE");
  if (samplenumber == 145)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ5E-5_preTS2_2016B.root",
                   "RECREATE");

  // 2018
  if (samplenumber == 201)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt170to300_2018.root",
                   "RECREATE");
  if (samplenumber == 202)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt300to470_2018.root",
                   "RECREATE");
  if (samplenumber == 203)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt470to600_2018.root",
                   "RECREATE");
  if (samplenumber == 204)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt600to800_2018.root",
                   "RECREATE");
  if (samplenumber == 205)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt800to1000_2018.root",
                   "RECREATE");
  if (samplenumber == 206)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1000to1400_2018.root",
                   "RECREATE");
  if (samplenumber == 207)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "ttbarhadronic_2018.root",
                   "RECREATE");
  if (samplenumber == 208)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "wjetshadronic_2018.root",
                   "RECREATE");
  if (samplenumber == 209)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "zjetshadronic_2018.root",
                   "RECREATE");
  if (samplenumber == 210)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "qcdpt1400to1800_2018.root",
                   "RECREATE");

  if (samplenumber == 220)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_2018A.root",
                   "RECREATE");
  if (samplenumber == 221)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_2018B.root",
                   "RECREATE");
  if (samplenumber == 222)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_2018C.root",
                   "RECREATE");
  if (samplenumber == 223)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W1E-6_2018D.root",
                   "RECREATE");
  if (samplenumber == 224)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_2018A.root",
                   "RECREATE");
  if (samplenumber == 225)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_2018B.root",
                   "RECREATE");
  if (samplenumber == 226)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_2018C.root",
                   "RECREATE");
  if (samplenumber == 227)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W2E-6_2018D.root",
                   "RECREATE");
  if (samplenumber == 228)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_2018A.root",
                   "RECREATE");
  if (samplenumber == 229)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_2018B.root",
                   "RECREATE");
  if (samplenumber == 230)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_2018C.root",
                   "RECREATE");
  if (samplenumber == 231)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWA0W5E-6_2018D.root",
                   "RECREATE");
  if (samplenumber == 232)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 233)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_2018B.root",
                   "RECREATE");
  if (samplenumber == 234)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_2018C.root",
                   "RECREATE");
  if (samplenumber == 235)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW2E-5_2018D.root",
                   "RECREATE");
  if (samplenumber == 236)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_2018A.root",
                   "RECREATE");
  if (samplenumber == 237)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_2018B.root",
                   "RECREATE");
  if (samplenumber == 238)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_2018C.root",
                   "RECREATE");
  if (samplenumber == 239)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW5E-6_2018D.root",
                   "RECREATE");
  if (samplenumber == 240)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_2018A.root",
                   "RECREATE");
  if (samplenumber == 241)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_2018B.root",
                   "RECREATE");
  if (samplenumber == 242)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_2018C.root",
                   "RECREATE");
  if (samplenumber == 243)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclWWACW8E-6_2018D.root",
                   "RECREATE");

  if (samplenumber == 250)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z-1E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 251)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z1E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 252)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZA0Z5E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 253)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ-1E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 254)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ1E-5_2018A.root",
                   "RECREATE");
  if (samplenumber == 255)
    fx = new TFile(outputFolder +
                       "vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_"
                       "exclZZACZ5E-5_2018A.root",
                   "RECREATE");

  if (samplenumber == 999)
    //     fx = new
    //     TFile(outputFolder+"vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_exclWWA0W1E-6_2017preTS2.root","RECREATE");
    //     fx = new
    //     TFile(outputFolder+"vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_exclWWA0W1E-6_2018A.root","RECREATE");
    fx = new TFile(
        outputFolder +
            "vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_"
            "exclWWA0W1E-6_2016B.root",
        "RECREATE");

  ofs.close();

  fx->mkdir("PreselectionAndControl");
  fx->mkdir("JetSubstructure");
  fx->mkdir("Sidebands");
  fx->mkdir("Signal");
  fx->mkdir("SingleProtonDistributions");
  fx->mkdir("MCGenDistributions");

  fx->cd("PreselectionAndControl");
  hmjjdat->Write();
  hyjjdat->Write();
  hptdat1->Write();
  hptdat2->Write();
  hetadat1->Write();
  hetadat2->Write();
  hphidat1->Write();
  hphidat2->Write();
  hdeta->Write();
  hprunedrotatedjjdat->Write();
  hacopdat->Write();
  hmjjdatpfjet->Write();
  hmjjdatpfhttrim->Write();
  hmjjdatpfjettrim->Write();
  hnvtx->Write();
  hcrossingangle->Write();
  hptratio->Write();

  hmppmulti->Write();
  hyppmulti->Write();
  hdtmulti->Write();

  hmassvvsignalww->Write();
  hywwsignalww->Write();
  hmassvvsignalzz->Write();
  hywwsignalzz->Write();

  hmyppsingle->Write();
  hmyppmulti->Write();
  hmyjjdat->Write();
  xijets45->Write();
  xijets56->Write();

  hmasscorrpreseldatmult->Write();
  hycorrpreseldatmult->Write();
  dymassratiocorrpreseldatmult->Write();

  fx->cd("JetSubstructure");
  hmjdat1->Write();
  htau21dat1->Write();
  hmjdat2->Write();
  htau21dat2->Write();
  htau21ddtdat1->Write();
  htau21ddtdat2->Write();
  tau21vrhoprime1->Write();
  tau21vrhoprime2->Write();

  fx->cd("Sidebands");
  hmassmatchantitaummww->Write();
  hymatchantitaummww->Write();
  hmassmatchratioantitaummww->Write();
  hmassmatchantiprunedmmww->Write();
  hymatchantiprunedmmww->Write();
  hmassmatchratioantiprunedmmww->Write();
  hmassmatchantiacopmmww->Write();
  hymatchantiacopmmww->Write();
  hmassmatchratioantiacopmmww->Write();
  hmassmatchantiptbalmmww->Write();
  hymatchantiptbalmmww->Write();
  hmassmatchratioantiptbalmmww->Write();
  hmassmatchantitaummzz->Write();
  hymatchantitaummzz->Write();
  hmassmatchratioantitaummzz->Write();
  hmassmatchantiprunedmmzz->Write();
  hymatchantiprunedmmzz->Write();
  hmassmatchratioantiprunedmmzz->Write();
  hmassmatchantiacopmmzz->Write();
  hymatchantiacopmmzz->Write();
  hmassmatchratioantiacopmmzz->Write();
  hmassmatchantiptbalmmzz->Write();
  hymatchantiptbalmmzz->Write();
  hmassmatchratioantiptbalmmzz->Write();
  hmassmatchantiprunednarrowmmww->Write();
  hymatchantiprunednarrowmmww->Write();
  hmassmatchratioantiprunednarrowmmww->Write();
  hmassmatchantiprunednarrowmmzz->Write();
  hymatchantiprunednarrowmmzz->Write();
  hmassmatchratioantiprunednarrowmmzz->Write();

  hmassvvantitauww->Write();
  hmassvvantiacopww->Write();
  hmassvvantiptbalww->Write();
  hmassvvantiprunedww->Write();
  hmassvvantiprunednarrowww->Write();
  hmj1antiacopww->Write();
  hmj2antiacopww->Write();
  htau211antiacopww->Write();
  htau212antiacopww->Write();
  hmj1antitauww->Write();
  hmj2antitauww->Write();
  htau211antitauww->Write();
  htau212antitauww->Write();
  hmj1antiprunedww->Write();
  hmj2antiprunedww->Write();
  htau211antiprunedww->Write();
  htau212antiprunedww->Write();
  hmj1antiprunednarrowww->Write();
  hmj2antiprunednarrowww->Write();
  htau211antiprunednarrowww->Write();
  htau212antiprunednarrowww->Write();

  hmassvvantitauzz->Write();
  hmassvvantiacopzz->Write();
  hmassvvantiptbalzz->Write();
  hmassvvantiprunedzz->Write();
  hmassvvantiprunednarrowzz->Write();
  hmj1antiacopzz->Write();
  hmj2antiacopzz->Write();
  htau211antiacopzz->Write();
  htau212antiacopzz->Write();
  hmj1antitauzz->Write();
  hmj2antitauzz->Write();
  htau211antitauzz->Write();
  htau212antitauzz->Write();
  hmj1antiprunedzz->Write();
  hmj2antiprunedzz->Write();
  htau211antiprunedzz->Write();
  htau212antiprunedzz->Write();
  hmj1antiprunednarrowzz->Write();
  hmj2antiprunednarrowzz->Write();
  htau211antiprunednarrowzz->Write();
  htau212antiprunednarrowzz->Write();

  hmassvvsignalww->Write();
  hywwsignalww->Write();
  hmassvvsignalzz->Write();
  hywwsignalzz->Write();

  hmassrapiditymatchantiacopmmww->Write();
  hmassrapiditymatchantiptbalmmww->Write();
  hmassrapiditymatchantitaummww->Write();
  hmassrapiditymatchantiprunedmmww->Write();
  hmassrapiditymatchantiprunednarrowmmww->Write();
  hmassrapiditymatchantiacopmmzz->Write();
  hmassrapiditymatchantiptbalmmzz->Write();
  hmassrapiditymatchantitaummzz->Write();
  hmassrapiditymatchantiprunedmmzz->Write();
  hmassrapiditymatchantiprunednarrowmmzz->Write();

  hmassrapiditymatchvetosignalregionww->Write();
  hmassrapiditymatchvetoorsignalregionww->Write();
  hmassrapiditymatchvetosignalregionzz->Write();
  hmassrapiditymatchvetoorsignalregionzz->Write();

  hmvvsigmcantiacopsigregionww->Write();
  hyvvsigmcantiacopsigregionww->Write();
  hmppsigmcantiacopsigregionww->Write();
  hyppsigmcantiacopsigregionww->Write();
  hmvvsigmcantiacopsigregionzz->Write();
  hyvvsigmcantiacopsigregionzz->Write();
  hmppsigmcantiacopsigregionzz->Write();
  hyppsigmcantiacopsigregionzz->Write();

  fx->cd("Signal");
  hmassmatchsigmcmmww->Write();
  hymatchsigmcmmww->Write();
  hmassmatchratiosigmcmmww->Write();
  hmassmatchsigmcmmzz->Write();
  hymatchsigmcmmzz->Write();
  hmassmatchratiosigmcmmzz->Write();

  hmassmatchratiosigmcmmshiftupww->Write();
  hmassmatchratiosigmcmmshiftdownww->Write();
  hymatchsigmcmmshiftupww->Write();
  hymatchsigmcmmshiftdownww->Write();
  hmassmatchratiosigmcmmshiftupzz->Write();
  hmassmatchratiosigmcmmshiftdownzz->Write();
  hymatchsigmcmmshiftupzz->Write();
  hymatchsigmcmmshiftdownzz->Write();

  hmassmatchratiosigmcmultww->Write();
  hymatchsigmcmultww->Write();
  hmasscorrsigmcmultww->Write();
  hycorrsigmcmultww->Write();
  hmasscorrsigmcmulttruthmatchedww->Write();
  hmassmatchratiosigmcmultzz->Write();
  hymatchsigmcmultzz->Write();
  hmasscorrsigmcmultzz->Write();
  hycorrsigmcmultzz->Write();
  hmasscorrsigmcmulttruthmatchedzz->Write();

  hprunedrotatedjjprematchingdat->Write();

  hmassrapiditymatchsigmcmmww->Write();
  hmassrapiditymatchsigmcmmzz->Write();
  hmvvsigmcsigregionww->Write();
  hyvvsigmcsigregionww->Write();
  hmppsigmcsigregionww->Write();
  hyppsigmcsigregionww->Write();
  hmvvsigmcsigregionzz->Write();
  hyvvsigmcsigregionzz->Write();
  hmppsigmcsigregionzz->Write();
  hyppsigmcsigregionzz->Write();

  fx->cd("SingleProtonDistributions");
  hxipix45->Write();
  hypix45->Write();
  hxipix56->Write();
  hypix56->Write();
  hxistrip45->Write();
  hystrip45->Write();
  hxistrip56->Write();
  hystrip56->Write();
  hdxi45->Write();
  hdy45->Write();
  hdxi56->Write();
  hdy56->Write();
  hximult45->Write();
  hximult56->Write();
  hthystmult45->Write();
  hthystmult56->Write();
  htmult45->Write();
  htmult56->Write();
  hnmult45->Write();
  hnmult56->Write();

  fx->cd("MCGenDistributions");
  resxijets45->Write();
  resxijets56->Write();
  resxijetscorr45->Write();
  resxijetscorr56->Write();

  hgenxinomatch->Write();
  hmassmatchratiosigmcoutofacceptancemm->Write();
  hmassmatchratiosigmcinacceptancemm->Write();
  hmassmatchratiosigmcinacceptancenomatchmm->Write();
  hymatchsigmcoutofacceptancemm->Write();
  hymatchsigmcinacceptancemm->Write();
  hymatchsigmcinacceptancenomatchmm->Write();

  fx->Close();

  Float_t normxsec = 0.0;
  Float_t nevgen = 99999999.;
  if (samplenumber == 21) {
    normxsec = 45.4;
    nevgen = 91300.0;
  }
  if (samplenumber == 22) {
    normxsec = 58.3;
    nevgen = 124400.0;
  }
  if (samplenumber == 24) {
    normxsec = 58.3;
    nevgen = 110100.0;
  }
  if (samplenumber == 25) {
    normxsec = 148.13;
    nevgen = 243900.0;
  }
  if (samplenumber == 27) {
    normxsec = 164.8;
    nevgen = 107700.0;
  }
  if (samplenumber == 31) {
    normxsec = 2.64;
    nevgen = 10000.0;
  }

  std::cout << "Ran over " << nentries << " events " << std::endl;

  std::cout << std::endl
            << std::endl
            << "====================================================="
            << std::endl;
  std::cout << "Cut flow" << std::endl;
  std::cout << "====================================================="
            << std::endl;
  std::cout << "Passing preselection = " << npasspresel << std::endl
            << "Passing dijet kinematics = " << npassdijetkine << std::endl
            << "Passing jet substructure = " << npassjetsubstr << std::endl
            << "Passing xi(jets) = " << npassjetxi << std::endl
            << "Passing 2 PPS multi-RP protons = " << npasspps << std::endl
            << "\t(After preselection and before other central cuts = "
            << npassppsbeforecuts << std::endl
            << "Passing pp-diboson matching = "
            << npassppsmatch_A + npassppsmatch_B << std::endl
            << "Passing WW channel cut = "
            << npassppsmatchkseniaww_A + npassppsmatchkseniaww_B << std::endl
            << "Passing WW channel cut A = " << npassppsmatchkseniaww_A
            << std::endl
            << "Passing WW channel cut B = " << npassppsmatchkseniaww_B
            << std::endl
            << "Passing ZZ channel cut = "
            << npassppsmatchkseniazz_A + npassppsmatchkseniazz_B << std::endl
            << "Passing ZZ channel cut A = " << npassppsmatchkseniazz_A
            << std::endl
            << "Passing ZZ channel cut B = " << npassppsmatchkseniazz_B
            << std::endl;

  std::cout << std::endl
            << std::endl
            << "====================================================="
            << std::endl;
  std::cout << "Sideband background method yields" << std::endl;
  std::cout << "====================================================="
            << std::endl;

  std::cout << "Anti-acoplanarity" << std::endl
            << "\t WW norm. region = " << npassantiacopnormregionww
            << ", WW sig. region = "
            << npassantiacopsigregionww_A + npassantiacopsigregionww_B
            << std::endl
            << "\t WW sig. region A = " << npassantiacopsigregionww_A
            << ", WW sig. region B = " << npassantiacopsigregionww_B
            << std::endl
            << "\t ZZ norm. region = " << npassantiacopnormregionzz
            << ", ZZ sig. region = "
            << npassantiacopsigregionzz_A + npassantiacopsigregionzz_B
            << std::endl
            << "\t ZZ sig. region A = " << npassantiacopsigregionzz_A
            << ", ZZ sig. region B = " << npassantiacopsigregionzz_B
            << std::endl;
  std::cout << "Anti-tau21" << std::endl
            << "\t WW norm. region = " << npassantitaunormregionww
            << ", WW sig. region = "
            << npassantitausigregionww_A + npassantitausigregionww_B
            << std::endl
            << "\t WW sig. region A = " << npassantitausigregionww_A
            << ", WW sig. region B = " << npassantitausigregionww_B << std::endl
            << "\t ZZ norm. region = " << npassantitaunormregionzz
            << ", ZZ sig. region = "
            << npassantitausigregionzz_A + npassantitausigregionzz_B
            << std::endl
            << "\t ZZ sig. region A = " << npassantitausigregionzz_A
            << ", ZZ sig. region B = " << npassantitausigregionzz_B
            << std::endl;
  std::cout << "Anti-pruned mass" << std::endl
            << "\t WW norm. region = " << npassantimassnormregionww
            << ", WW sig. region = "
            << npassantimasssigregionww_A + npassantimasssigregionww_B
            << std::endl
            << "\t WW sig. region A = " << npassantimasssigregionww_A
            << ", WW sig. region B = " << npassantimasssigregionww_B
            << std::endl
            << "\t ZZ norm. region = " << npassantimassnormregionzz
            << ", ZZ sig. region = "
            << npassantimasssigregionzz_A + npassantimasssigregionzz_B
            << std::endl
            << "\t ZZ sig. region A = " << npassantimasssigregionzz_A
            << ", ZZ sig. region B = " << npassantimasssigregionzz_B
            << std::endl;
  std::cout << "Anti-pruned mass (narrow region)" << std::endl
            << "\t WW norm. region = " << npassantimassnarrownormregionww
            << ", WW sig. region = "
            << npassantimassnarrowsigregionww_A +
                   npassantimassnarrowsigregionww_B
            << std::endl
            << "\t WW sig. region A = " << npassantimassnarrowsigregionww_A
            << ", WW sig. region B = " << npassantimassnarrowsigregionww_B
            << std::endl
            << "\t ZZ norm. region = " << npassantimassnarrownormregionzz
            << ", ZZ sig. region = "
            << npassantimassnarrowsigregionzz_A +
                   npassantimassnarrowsigregionzz_B
            << std::endl
            << "\t ZZ sig. region A = " << npassantimassnarrowsigregionzz_A
            << ", ZZ sig. region B = " << npassantimassnarrowsigregionzz_B
            << std::endl;
  std::cout << "Non-blinded normalization region" << std::endl
            << "\t WW norm. region = " << npassnonblindnormregionww << std::endl
            << "\t ZZ norm. region = " << npassnonblindnormregionzz
            << std::endl;

  /*
  TCanvas can;
  can.Divide(2,1);
  can.cd(1);
  hxold0->Draw();
  hxnew0->SetLineColor(kRed);
  hxnew0->Draw("same");
  can.cd(2);
  hxold1->Draw();
  hxnew1->SetLineColor(kRed);
  hxnew1->Draw("same");
  can.SaveAs("can2016pre.pdf");
  */
}
