/*
 * Updated for reprocessed samples with UL proton reco
 *
 */
#include "CMS_lumi.h"

void ULPlotStackTest2017(Int_t var = 1, bool saveToRootFile = false)
{
  TString outplotdir = "validationplots/";
  gStyle->SetOptTitle(0);
  gStyle->SetOptTitle(0);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBorderSize(2);
  gStyle->SetLegendBorderSize(0);
  TGaxis::SetExponentOffset(-0.085,-0.02,"y");



  //  Float_t lumi = 2.367+8.681+4.143+9.062+13.242;
  // pre-TS2
  //  Float_t lumi = 2.361+8.577+4.075; // +8.959+13.214;
  Float_t lumi = 2.361+8.577+4.075+8.948+13.214;
  Float_t lumi2017B = 2.361;
  Float_t lumi2017C = 8.577;
  Float_t lumi2017D = 4.075;
  Float_t lumi2017E = 8.948;
  Float_t lumi2017F = 13.214;
  
  // QCD xsections from xsecDB
  /*
  Float_t mc6xsec = 7.47;
  Float_t mc5xsec = 26.28;
  Float_t mc4xsec = 156.5;
  Float_t mc3xsec = 552.1;
  Float_t mc2xsec = 6830.0;
  Float_t mc1xsec = 103500.0;
  */
  // QCD xsections from B2G-18-002, including corr factors
  Float_t mc6xsec = 7.466*1.26149;
  Float_t mc5xsec = 32.293;
  Float_t mc4xsec = 156.4*1.19501;
  Float_t mc3xsec = 551.1*1.17619;
  Float_t mc2xsec = 6838*1.14405;
  Float_t mc1xsec = 103400.0*1.1342;
  Float_t mc10xsec = 0.6481*1.30019;
  Float_t mc11xsec = 0.08741*1.31499;
  Float_t mc12xsec = 0.00522*1.30839;

  Float_t mc7xsec = 377.96;
  Float_t mc8xsec = 33.7;
  Float_t mc9xsec = 14.6;

  //  Float_t mcaxsec = 0.1282; // pb
  Float_t mcaxsec = 0.0454; // pb, a0W=1E-6
  Float_t mcbxsec = 0.07147586892; // pb, a0Z=1E-5
  Float_t mccxsec = 0.005100496092; // pb, aCZ=1E-5
  Float_t mcdxsec = 0.1648; // pb, aCW=2E-5

  Float_t rangelo = 0.0;
  Float_t rangehi = 1.0;
  Float_t rangeylo = 0.0;
  Float_t rangeyhi = 10000000.0;

  TString hist = "hmjjdat";
  TString thetitle = "";
  TString filetitle = "";
  if(var == 1)
    //    {rangelo = 1000; rangehi = 10000; thetitle = "m(jj) [GeV]"; filetitle = "mjj";}
    {rangelo = 1000; rangehi = 3000; thetitle = "m(jj) [GeV]"; filetitle = "mjj";}
  if(var == 2)
    {hist = "hmjdat1"; rangelo = 55; rangehi = 215; thetitle = "m(j1) [GeV]"; filetitle = "mj1";}
  if(var == 3)
    {hist = "htau21dat1"; thetitle = "tau_{21}(j1)"; filetitle = "tau21j1";}
  if(var == 4)
    {hist = "hptdat1"; rangelo = 0; rangehi = 2000; thetitle = "p_{T}(j1) [GeV]"; filetitle = "pTleading";}
  if(var == 5)
    {hist = "hptdat2"; rangelo = 0; rangehi = 2000; thetitle = "p_{T}(j2) [GeV]"; filetitle = "pTtrailing";}
  if(var == 6)
    {hist = "hetadat1"; thetitle = "#eta(j1)"; filetitle = "etaleading";}
  if(var == 7)
    {hist = "hetadat2"; thetitle = "#eta(j2)"; filetitle = "etatrailing";}
  if(var == 8)
    {hist = "hphidat1"; thetitle = "#phi(j1)"; filetitle = "phileading";}
  if(var == 9)
    {hist = "hphidat2"; thetitle = "#phi(j2)"; filetitle = "phitrailing";}
  if(var == 10)
    {hist = "hmjjdatpfjet"; thetitle = "m(jj) [GeV], PF jet triggers"; filetitle = "mjj_pfjettrig";}
  if(var == 11)
    {hist = "hmjjdatpfjettrim"; thetitle = "m(jj) [GeV], PF jet trimmed triggers"; filetitle = "mjj_pfjettrimtrig";}
  if(var == 12)
    {hist = "hmjjdatpfhttrim"; thetitle = "m(jj) [GeV], PF HT trimmed triggers"; filetitle = "mjj_pfhttrimtrig";}
  if(var == 13)
    {hist = "hdeta"; rangelo = 0; rangehi = 1.3; thetitle = "#Delta(#eta)"; filetitle = "deltaeta";}
  if(var == 14)
    {hist = "hacopdat"; thetitle = "acoplanarity(jj)"; filetitle = "acoplanarity"; rangelo = 0; rangehi = 0.2;}
  if(var == 15)
    {hist = "hnvtx"; thetitle = "N(vertices)"; filetitle = "nvertices";}
  if(var == 16)
    {hist = "hptratio"; thetitle = "p_{T}(j1)/p_{T}(j2)"; filetitle = "pTbalance"; rangelo = 1; rangehi = 2;}
  if(var == 17)
    {hist = "hmjdat2"; rangelo = 55; rangehi = 215; thetitle = "m(j2) [GeV]"; filetitle = "mj2";}
  if(var == 18)
    {hist = "htau21dat2"; thetitle = "tau_{21}(j2)"; filetitle = "tau21j2";}
  if(var == 19)
    {hist = "htau21ddtdat1"; thetitle = "tau_{21, DDT}(j1)"; filetitle = "tau21ddtj1";}
  if(var == 20)
    {hist = "htau21ddtdat2"; thetitle = "tau_{21, DDT}(j2)"; filetitle = "tau21ddtj2";}
  if(var == 21)
    {hist = "hyjjdat"; thetitle = "y(jj)"; filetitle = "yjj";}
  if(var == 22)
    {hist = "hprunedrotatedjjdat"; thetitle = "cos(#pi / 4) * m(j1) + sin(#pi / 4) * m(j2) [GeV]"; filetitle = "prunedrotatedjjdat";}

  // WW plots  
  if(var == 32)
    {hist = "hmassvvantitauww"; thetitle = "m(WW), #tau_{21, DDT} > 0.75"; filetitle = "mvvantitauww"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 33)
    {hist = "hmassvvantiacopww"; thetitle = "m(WW), acoplanarity > 0.1"; filetitle = "mvvantiacopww"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 34)
    {hist = "hmassvvantiptbalww"; thetitle = "m(WW), p_{T}(j1/j2) > 1.1"; filetitle = "mvvanttptbalww"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 35)
    {hist = "hmassvvsignalww"; thetitle = "m(WW), signal"; filetitle = "mwwsignalblind"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 36)
    {hist = "hywwsignalww"; thetitle = "y(WW), signal"; filetitle = "ywwsignalblind"; rangelo = -3.0; rangehi = 3.0;}
  if(var == 37)
    {hist = "xijets45"; thetitle = "#xi(jets), 45"; filetitle = "xijets45";}
  if(var == 38)
    {hist = "xijets56"; thetitle = "#xi(jets), 56"; filetitle = "xijets56";}
  if(var == 39)
    {hist = "hmj1antiacopww"; thetitle = "m(j1), anti-acoplanarity"; filetitle = "mj1antiacopww"; rangelo = 65; rangehi = 105;}
  if(var == 40)
    {hist = "hmj2antiacopww"; thetitle = "m(j2), anti-acoplanarity"; filetitle = "mj2antiacopww"; rangelo = 65; rangehi = 105;}
  if(var == 41)
    {hist = "htau211antiacopww"; thetitle = "tau_{21}(j1), anti-acoplanarity"; filetitle = "tau211antiacopww";}
  if(var == 42)
    {hist = "htau212antiacopww"; thetitle = "tau_{21}(j2), anti-acoplanarity"; filetitle = "tau212antiacopww";}
  if(var == 43)
    {hist = "hmj1antitauww"; thetitle = "m(j1), anti-tau"; filetitle = "mj1antitauww"; rangelo = 65; rangehi = 105;}
  if(var == 44)
    {hist = "hmj2antitauww"; thetitle = "m(j2), anti-tau"; filetitle = "mj2antitauww"; rangelo = 65; rangehi = 105;}
  if(var == 45)
    {hist = "htau211antitauww"; thetitle = "tau_{21}(j1), anti-tau"; filetitle = "tau211antitauww";}
  if(var == 46)
    {hist = "htau212antitauww"; thetitle = "tau_{21}(j2), anti-tau"; filetitle = "tau212antitauww";}
  if(var == 47)
    {hist = "hmassvvantiprunedww"; thetitle = "m(WW), m < 60 OR m > 107 GeV"; filetitle = "mvvantiprunedww"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 48)
    {hist = "hmassvvantiprunednarrowww"; thetitle = "m(WW) narrow, m < 60 OR m > 107 GeV"; filetitle = "mvvantiprunednarrowww"; rangelo = 1000.0; rangehi = 3000.0;}  

  // ZZ plots
  if(var == 58)
    {hist = "hmassvvantitauzz"; thetitle = "m(ZZ), #tau_{21, DDT} > 0.75"; filetitle = "mvvantitauzz"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 59)
    {hist = "hmassvvantiacopzz"; thetitle = "m(ZZ), acoplanarity > 0.1"; filetitle = "mvvantiacopzz"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 60)
    {hist = "hmassvvantiptbalzz"; thetitle = "m(ZZ), p_{T}(j1/j2) > 1.1"; filetitle = "mvvanttptbalzz"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 61)
    {hist = "hmassvvsignalzz"; thetitle = "m(ZZ), signal"; filetitle = "mzzsignalblind"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 62)
    {hist = "hywwsignalzz"; thetitle = "y(ZZ), signal"; filetitle = "yzzsignalblind"; rangelo = -3.0; rangehi = 3.0;}
  if(var == 63)
    {hist = "hmj1antiacopzz"; thetitle = "m(j1), anti-acoplanarity"; filetitle = "mj1antiacopzz"; rangelo = 65; rangehi = 105;}
  if(var == 64)
    {hist = "hmj2antiacopzz"; thetitle = "m(j2), anti-acoplanarity"; filetitle = "mj2antiacopzz"; rangelo = 65; rangehi = 105;}
  if(var == 65)
    {hist = "htau211antiacopzz"; thetitle = "tau_{21}(j1), anti-acoplanarity"; filetitle = "tau211antiacopzz";}
  if(var == 66)
    {hist = "htau212antiacopzz"; thetitle = "tau_{21}(j2), anti-acoplanarity"; filetitle = "tau212antiacopzz";}
  if(var == 67)
    {hist = "hmj1antitauzz"; thetitle = "m(j1), anti-tau"; filetitle = "mj1antitauzz"; rangelo = 65; rangehi = 105;}
  if(var == 68)
    {hist = "hmj2antitauzz"; thetitle = "m(j2), anti-tau"; filetitle = "mj2antitauzz"; rangelo = 65; rangehi = 105;}
  if(var == 69)
    {hist = "htau211antitauzz"; thetitle = "tau_{21}(j1), anti-tau"; filetitle = "tau211antitauzz";}
  if(var == 70)
    {hist = "htau212antitauzz"; thetitle = "tau_{21}(j2), anti-tau"; filetitle = "tau212antitauzz";}
  if(var == 71)
    {hist = "hmassvvantiprunedzz"; thetitle = "m(ZZ), m < 60 OR m > 107 GeV"; filetitle = "mvvantiprunedzz"; rangelo = 1000.0; rangehi = 3000.0;}
  if(var == 72)
    {hist = "hmassvvantiprunednarrowzz"; thetitle = "m(ZZ) narrow, m < 60 OR m > 107 GeV"; filetitle = "mvvantiprunednarrowzz"; rangelo = 1000.0; rangehi = 3000.0;}

  if ((var >= 39 && var <= 58) || var == 32 || var == 33 || var == 34 ||
      (var >= 63) || var == 58 || var == 59 || var == 60)
    hist = "Sidebands/"+hist;
  else if ( var == 1  || var == 21 || var == 22 || var == 35 || var == 36 || var == 37 || var == 38  || var == 4 ||  
            var == 5  || var == 6  || var == 7  || var == 8  || var == 9  || var == 10  || var == 11 || 
            var == 12 || var == 13 || var == 14 || var == 15 || var == 16  || var == 61 || var == 62)
    hist = "PreselectionAndControl/"+hist;
  else if ( var == 2  || var == 3  || var == 17 || var == 18 || var == 19 || var == 20 )
    hist = "JetSubstructure/"+hist;


  // TString dataFolder = "/eos/cms/store/group/phys_smp/HadronicVV/dataRun2_v2/"; // blinded
  TString dataFolder = "/eos/cms/store/group/phys_smp/HadronicVV/dataRun2_v4_unblinded/"; // unblinded
  TString signalFolder = "/eos/cms/store/group/phys_smp/HadronicVV/signalSamples_v7/";
  TString backgroundFolder = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/";

  /*
  TFile *f100 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017C.root");
  TH1F *h100 = (TH1F *)f100->Get(hist);

  TFile *f101 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017B.root");
  TH1F *h101 = (TH1F *)f101->Get(hist);

  TFile *f102 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017D.root");
  TH1F *h102 = (TH1F *)f102->Get(hist);

  TFile *f103 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017E.root");
  TH1F *h103 = (TH1F *)f103->Get(hist);

  TFile *f104 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017F.root");
  TH1F *h104 = (TH1F *)f104->Get(hist);
  */
  //  TFile *f100 = TFile::Open("vars_cuts_ntupleULReMiniv4final_datahist2017BCD.root");
  TFile *f100 = TFile::Open(dataFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  TH1F *h100 = (TH1F *)f100->Get(hist);

  TFile *f2 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt300to470.root");
  TH1F *h2 = (TH1F *)f2->Get(hist);

  TFile *f3 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt470to600.root");
  TH1F *h3 = (TH1F *)f3->Get(hist);

  TFile *f4 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt600to800.root");
  TH1F *h4 = (TH1F *)f4->Get(hist);
  
  TFile *f5 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt800to1000.root");
  TH1F *h5 = (TH1F *)f5->Get(hist);
  
  TFile *f6 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1000to1400.root");
  TH1F *h6 = (TH1F *)f6->Get(hist);

  TFile *f7 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_ttbarhadronic.root");
  TH1F *h7 = (TH1F *)f7->Get(hist);

  TFile *f8 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_wjetshadronic.root");
  TH1F *h8 = (TH1F *)f8->Get(hist);

  TFile *f9 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_zjetshadronic.root");
  TH1F *h9 = (TH1F *)f9->Get(hist);

  TFile *f10 = TFile::Open(backgroundFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1400to1800.root");
  TH1F *h10 = (TH1F *)f10->Get(hist);

  // I'm keeping preTS2 and postTS2 easy to separate, in case we need it... 

  TFile *fa1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_preTS2_2017B.root");
  TH1F *ha1 = (TH1F *)fa1->Get(hist);
  TFile *fa1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_preTS2_2017C.root");
  TH1F *ha1_2 = (TH1F *)fa1_2->Get(hist);
  TFile *fa1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_preTS2_2017D.root");
  TH1F *ha1_3 = (TH1F *)fa1_3->Get(hist);

  TFile *fa2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_postTS2_2017E.root");
  TH1F *ha2 = (TH1F *)fa2->Get(hist);
  TFile *fa2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_postTS2_2017F.root");
  TH1F *ha2_2 = (TH1F *)fa2_2->Get(hist);

  TFile *fb1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z1E-5_preTS2_2017B.root");
  TH1F *hb1 = (TH1F *)fb1->Get(hist);
  TFile *fb1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z1E-5_preTS2_2017C.root");
  TH1F *hb1_2 = (TH1F *)fb1_2->Get(hist);
  TFile *fb1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z1E-5_preTS2_2017D.root");
  TH1F *hb1_3 = (TH1F *)fb1_3->Get(hist);

  TFile *fb2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z1E-5_postTS2_2017E.root");
  TH1F *hb2 = (TH1F *)fb2->Get(hist);
  TFile *fb2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z1E-5_postTS2_2017F.root");
  TH1F *hb2_2 = (TH1F *)fb2_2->Get(hist);

  TFile *fc1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ1E-5_preTS2_2017B.root");
  TH1F *hc1 = (TH1F *)fc1->Get(hist);
  TFile *fc1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ1E-5_preTS2_2017C.root");
  TH1F *hc1_2 = (TH1F *)fc1_2->Get(hist);
  TFile *fc1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ1E-5_preTS2_2017D.root");
  TH1F *hc1_3 = (TH1F *)fc1_3->Get(hist);

  TFile *fc2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ1E-5_postTS2_2017E.root");
  TH1F *hc2 = (TH1F *)fc2->Get(hist);
  TFile *fc2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ1E-5_postTS2_2017F.root");
  TH1F *hc2_2 = (TH1F *)fc2_2->Get(hist);

  TFile *fd1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_preTS2_2017B.root");
  TH1F *hd1 = (TH1F *)fd1->Get(hist);
  TFile *fd1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_preTS2_2017C.root");
  TH1F *hd1_2 = (TH1F *)fd1_2->Get(hist);
  TFile *fd1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_preTS2_2017D.root");
  TH1F *hd1_3 = (TH1F *)fd1_3->Get(hist);

  TFile *fd2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_postTS2_2017E.root");
  TH1F *hd2 = (TH1F *)fd2->Get(hist);
  TFile *fd2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_postTS2_2017F.root");
  TH1F *hd2_2 = (TH1F *)fd2_2->Get(hist);

  h100->Sumw2(); //h101->Sumw2(); h102->Sumw2(); h103->Sumw2();  h104->Sumw2();
  //  h100->Add(h101); h100->Add(h102); h100->Add(h103); h100->Add(h104);
  TH1F *h1000 = (TH1F *)h100->Clone("h1000");

  // Canvas for plot + ratio for thesis 
  TCanvas *c_thesis = new TCanvas("c_thesis","c_thesis",700,800);
  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetRightMargin(0.1);
  pad1->SetLeftMargin(0.1);
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  // lower plot will be in pad2
  c_thesis->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
  pad2->SetTopMargin(0);
  pad2->SetRightMargin(0.1);
  pad2->SetLeftMargin(0.1);
  pad2->SetBottomMargin(0.25);
  pad2->Draw();


  TCanvas *c1 = new TCanvas("c1","c1",500,1000);
  c1->Divide(1,3);
  c1->cd(1);

  
  int rebinfactor = 1;
  //  if((var > 20 && var < 25))
  if(var == 3 || var == 6 || var == 7 || var == 8 || var == 9 || var == 18 || var == 19 || var == 20 || var == 16 || var == 35 || var == 36 || (var > 22))
    {
      rebinfactor = 5;
      if(var == 19 || var == 20)
    rebinfactor = 10;
      // if(var == 25 || var == 26) {rebinfactor = 5;}
      if(var == 16) {rebinfactor = 10;}
      if((var > 20 && var < 35) || (var > 57 && var < 61)) {rebinfactor = 10;}
      if(var == 39 || var == 40 || var == 43 || var == 44 || var == 63 || var == 64 || var == 67 || var == 68)
        rebinfactor = 1;
      h2->Rebin(rebinfactor); 
      h3->Rebin(rebinfactor); h4->Rebin(rebinfactor); h5->Rebin(rebinfactor);
      h6->Rebin(rebinfactor); h7->Rebin(rebinfactor);
      h8->Rebin(rebinfactor);  h9->Rebin(rebinfactor);
      h10->Rebin(rebinfactor); 
      h100->Rebin(rebinfactor); //h101->Rebin(rebinfactor); h102->Rebin(rebinfactor); h103->Rebin(rebinfactor); h104->Rebin(rebinfactor);
      h1000->Rebin(rebinfactor);

      ha1->Rebin(rebinfactor); 
      ha1_2->Rebin(rebinfactor); 
      ha1_3->Rebin(rebinfactor); 
      ha2->Rebin(rebinfactor);
      ha2_2->Rebin(rebinfactor);

      hb1->Rebin(rebinfactor); 
      hb1_2->Rebin(rebinfactor); 
      hb1_3->Rebin(rebinfactor);
      hb2->Rebin(rebinfactor);
      hb2_2->Rebin(rebinfactor);

      hc1->Rebin(rebinfactor); 
      hc1_2->Rebin(rebinfactor); 
      hc1_3->Rebin(rebinfactor);
      hc2->Rebin(rebinfactor);
      hc2_2->Rebin(rebinfactor);

      hd1->Rebin(rebinfactor); 
      hd1_2->Rebin(rebinfactor); 
      hd1_3->Rebin(rebinfactor); 
      hd2->Rebin(rebinfactor);
      hd2_2->Rebin(rebinfactor);
    }

  // For MC in higher QCD pT bins, only running on 100k events from the ntuple per bin, so renormalize to that                                               
  
  h2->Sumw2(); // 300-470
  //  h2->Scale((3335454.0/11896906.0)*mc2xsec*1000*lumi/(1000000.0));
  h2->Scale(mc2xsec*1000*lumi/11896906.0);
  h2->SetFillColor(kAzure+1);
  //  h2->SetFillColor(2);

  h3->Sumw2(); // 470-600
  //  h3->Scale((25083178.0/27705084.0)*mc3xsec*1000*lumi/(1000000.0));
  h3->Scale(mc3xsec*1000*lumi/27705084.0);
  h3->SetFillColor(kAzure+1);
  //  h3->SetFillColor(3);

  h4->Sumw2(); // 600-800
  //  h4->Scale((5309553.0/5329382.0)*mc4xsec*1000*lumi/(1000000.0));
  h4->Scale(mc4xsec*1000*lumi/5329382.0);
  h4->SetFillColor(kAzure+1);
  //  h4->SetFillColor(4);

  h5->Sumw2(); // 800-1000
  //  h5->Scale((39469588.0/39525104.0)*mc5xsec*1000*lumi/(1000000.0));
  h5->Scale(mc5xsec*1000*lumi/39525104.0);
  h5->SetFillColor(kAzure+1);
  //  h5->SetFillColor(5);

  h6->Sumw2(); // 1000-1400
  //  h6->Scale((14598037.0/14619206.0)*mc6xsec*1000*lumi/(1000000.0));
  h6->Scale(mc6xsec*1000*lumi/14619206.0);
  h6->SetFillColor(kAzure+1);
  //  h6->Scale((5316947.0/27905480.0)*mc6xsec*1000*lumi/(1000000.0));

  h7->Sumw2(); // ttbar
  //  h7->Scale((824317.0/35540872.0)*mc7xsec*1000*lumi/(1000000.0));
  h7->Scale(mc7xsec*1000*lumi/35540872.0);

  h8->Sumw2(); // wjets
  //  h8->Scale((5647835.0/8081153.0)*mc8xsec*1000*lumi/(1000000.0));
  h8->Scale(mc8xsec*1000*lumi/8081153.0);

  h9->Sumw2(); // zjets 
  //  h9->Scale((7153915.0/9783887.0)*mc9xsec*1000*lumi/(1000000.0));
  h9->Scale(mc9xsec*1000*lumi/9783887.0);

  h10->Sumw2(); // 1400-1800
  //  h10->Scale(mc10xsec*1000*lumi/14286.0);
  h10->Scale(mc10xsec*1000*lumi/14286.0);
  h10->SetFillColor(kAzure+1);

  ha1->Sumw2(); // Signal, a0W=1E-6, 2017B --> 2017preTS2
  ha1->Scale(mcaxsec*1000*lumi2017B/27800.0);
  ha1_2->Sumw2(); // Signal, a0W=1E-6, 2017C 
  ha1_2->Scale(mcaxsec*1000*lumi2017C/110100.0);
  ha1_3->Sumw2(); // Signal, a0W=1E-6, 2017D 
  ha1_3->Scale(mcaxsec*1000*lumi2017D/39100.0);
  ha1->Add(ha1_2);
  ha1->Add(ha1_3);
  ha1->SetLineWidth(3); ha1->SetLineColor(kCyan); ha1->SetMarkerStyle(0); ha1->SetMarkerColor(kCyan);

  ha2->Sumw2(); // Signal, a0W=1E-6, 2017E --> 2017postTS2                                                                                       
  ha2->Scale(mcaxsec*1000*lumi2017E/76700.0);
  ha2_2->Sumw2(); // Signal, a0W=1E-6, 2017F 
  ha2_2->Scale(mcaxsec*1000*lumi2017F/139500.0);
  ha2->Add(ha2_2);
  ha2->SetLineWidth(3); ha2->SetLineColor(kCyan); ha2->SetMarkerStyle(0); ha2->SetMarkerColor(kCyan);
  ha1->Add(ha2);
  
  hb1->Sumw2(); // Signal, a0Z=1E-5, 2017B --> 2017preTS2
  hb1->Scale(mcbxsec*1000*lumi2017B/19686.0);
  hb1_2->Sumw2(); // Signal, a0Z=1E-5, 2017C 
  hb1_2->Scale(mcbxsec*1000*lumi2017C/19768.0);
  hb1_3->Sumw2(); // Signal, a0Z=1E-5, 2017D 
  hb1_3->Scale(mcbxsec*1000*lumi2017D/19786.0);
  hb1->Add(hb1_2);
  hb1->Add(hb1_3);
  hb1->SetLineWidth(3); hb1->SetLineColor(kCyan); hb1->SetMarkerStyle(0); hb1->SetMarkerColor(kCyan); hb1->SetLineStyle(2);

  hb2->Sumw2(); // Signal, a0Z=1E-5, 2017E --> 2017postTS2                                                                                       
  hb2->Scale(mcbxsec*1000*lumi2017E/19543.0);
  hb2_2->Sumw2(); // Signal, a0Z=1E-5, 2017F 
  hb2_2->Scale(mcbxsec*1000*lumi2017F/19882.0);
  hb2->Add(hb2_2);
  hb2->SetLineWidth(3); hb2->SetLineColor(kCyan); hb2->SetMarkerStyle(0); hb2->SetMarkerColor(kCyan);
  hb1->Add(hb2);

  hc1->Sumw2(); // Signal, aCZ=1E-5, 2017B --> 2017preTS2
  hc1->Scale(mccxsec*1000*lumi2017B/19927.0);
  hc1_2->Sumw2(); // Signal, aCZ=1E-5, 2017C 
  hc1_2->Scale(mccxsec*1000*lumi2017C/19930.0);
  hc1_3->Sumw2(); // Signal, aCZ=1E-5, 2017D 
  hc1_3->Scale(mccxsec*1000*lumi2017D/19914.0);
  hc1->Add(hc1_2);
  hc1->Add(hc1_3);
  hc1->SetLineWidth(3); hc1->SetLineColor(kCyan); hc1->SetMarkerStyle(0); hc1->SetMarkerColor(kCyan);

  hc2->Sumw2(); // Signal, aCZ=1E-5, 2017E --> 2017postTS2                                                                                       
  hc2->Scale(mccxsec*1000*lumi2017E/19662.0);
  hc2_2->Sumw2(); // Signal, aCZ=1E-5, 2017F 
  hc2_2->Scale(mccxsec*1000*lumi2017F/19910.0);
  hc2->Add(hc2_2);
  hc2->SetLineWidth(3); hc2->SetLineColor(kCyan); hc2->SetMarkerStyle(0); hc2->SetMarkerColor(kCyan);
  hc1->Add(hc2);
  
  hd1->Sumw2(); // Signal, aCW=2E-5, 2017B --> 2017preTS2
  hd1->Scale(mcdxsec*1000*lumi2017B/27800.0);
  hd1_2->Sumw2(); // Signal, aCW=2E-5, 2017C 
  hd1_2->Scale(mcdxsec*1000*lumi2017C/92100.0);
  hd1_3->Sumw2(); // Signal, aCW=2E-5, 2017D 
  hd1_3->Scale(mcdxsec*1000*lumi2017D/41700.0);
  hd1->Add(hd1_2);
  hd1->Add(hd1_3);
  hd1->SetLineWidth(3); hd1->SetLineColor(kCyan); hd1->SetMarkerStyle(0); hd1->SetMarkerColor(kCyan); hd1->SetLineStyle(2);

  hd2->Sumw2(); // Signal, aCW=2E-5, 2017E --> 2017postTS2                                                                                       
  hd2->Scale(mcdxsec*1000*lumi2017E/92100.0);
  hd2_2->Sumw2(); // Signal, aCW=2E-5, 2017F 
  hd2_2->Scale(mcdxsec*1000*lumi2017F/119900.0);
  hd2->Add(hd2_2);
  hd2->SetLineWidth(3); hd2->SetLineColor(kCyan); hd2->SetMarkerStyle(0); hd2->SetMarkerColor(kCyan);
  hd1->Add(hd2);
  
  /*
  h12->Add(h11);
  h12->Add(h10);
  h12->Add(h6);
  h12->Add(h5);
  h12->Add(h4);
  h12->Add(h3);
  h12->Add(h2);
  h12->Add(h1);
  h12->Add(h7);
  h12->Add(h8);
  h12->Add(h9);

  h12->SetStats(0);
  if(rangelo != 0 || rangehi != 1)
    h12->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h12->SetMaximum(h100->GetMaximum()*1.5);
  h12->SetTitle(thetitle);
  h12->Draw("hist");

  TH1F *h12err = (TH1F *)h12->Clone("h12err");
  h12err->SetFillColor(1);
  h12err->SetFillStyle(3001);
  h12err->Draw("E2same");

  h11->Add(h10);
  h11->Add(h6);
  h11->Add(h5);
  h11->Add(h4);
  h11->Add(h3);
  h11->Add(h2);
  h11->Add(h1);
  h11->Add(h7);
  h11->Add(h8);
  h11->Add(h9);
  h11->Draw("histsame");
  */

  h10->Add(h6);
  h10->Add(h5);
  h10->Add(h4);
  h10->Add(h3);
  h10->Add(h2);
  h10->Add(h7);
  h10->Add(h8);
  h10->Add(h9);
  h10->SetLineWidth(0);
  h10->Draw("histsame");

  h10->SetStats(0);     
  h10->GetXaxis()->SetNdivisions(5);
  h10->GetYaxis()->SetNdivisions(5);
  h10->GetXaxis()->SetLabelSize(0.07);
  h10->GetYaxis()->SetLabelSize(0.07);
  h10->GetXaxis()->SetTitleSize(0.07);
  h10->GetYaxis()->SetTitleSize(0.065);
  h10->GetXaxis()->SetLabelOffset(0.025);
  h10->GetYaxis()->SetLabelOffset(0.04);
  h10->GetXaxis()->SetTitleOffset(1.1);

  if(rangelo != 0 || rangehi != 1)                                                                                                                        
    h10->GetXaxis()->SetRangeUser(rangelo,rangehi);                                                                                                       
  if(var != 35 && var != 36 && var != 61 && var != 62)
    h10->SetMaximum(h100->GetMaximum()*2.5);
  else
    h10->SetMaximum(h10->GetMaximum()*2.5);
  h10->SetTitle(thetitle);                                                                                                                                
  h10->SetXTitle(thetitle);
  h10->Draw("hist");                                                                                                                                      

  TH1F *h10err = (TH1F *)h10->Clone("h10err");                                                                                                                
  h10err->SetFillColor(1);                                                                                                                                    
  h10err->SetFillStyle(3001);                                                                                                                                 
  h10err->SetMarkerStyle(0);
  h10err->Draw("E2same");                                                                                                                                     

  h6->Add(h5);
  h6->Add(h4);
  h6->Add(h3);
  h6->Add(h2);
  h6->Add(h7);
  h6->Add(h8);
  h6->Add(h9);
  h6->SetLineWidth(0);
  h6->Draw("histsame");

  h5->Add(h4);
  h5->Add(h3);
  h5->Add(h2);
  h5->Add(h7);
  h5->Add(h8);
  h5->Add(h9);
  h5->SetLineWidth(0);
  h5->Draw("histsame");


  h4->Add(h3);
  h4->Add(h2);
  h4->Add(h7);
  h4->Add(h8);
  h4->Add(h9);
  h4->SetLineWidth(0);
  h4->Draw("histsame");

  h3->Add(h2);
  h3->Add(h7);
  h3->Add(h8);
  h3->Add(h9);
  h3->SetLineWidth(0);
  h3->Draw("histsame");

  h2->Add(h7);
  h2->Add(h8);
  h2->Add(h9);
  h2->SetLineWidth(0);
  h2->Draw("histsame");

  h8->SetFillColor(kGreen+1);
  h8->Add(h7);
  h8->Add(h9);
  h8->SetLineWidth(0);
  h8->Draw("histsame");

  h9->SetFillColor(kYellow+1);
  h9->Add(h7);
  h9->SetLineWidth(0);
  h9->Draw("histsame");

  h7->SetFillColor(kOrange+1);
  h7->SetLineWidth(0);
  h7->Draw("histsame");

  h100->SetMarkerStyle(20); h100->SetLineWidth(3); h100->SetLineColor(kBlack);
  h100->Draw("esame");

  TLegend *lg1 = new TLegend(0.35,0.5,0.8,0.85);
  h10->SetMarkerStyle(0); 
  h7->SetMarkerStyle(0); h7->SetLineWidth(0);
  h8->SetMarkerStyle(0); h8->SetLineWidth(0);
  h9->SetMarkerStyle(0); h9->SetLineWidth(0);
  lg1->AddEntry(h10,"QCD","f");
  lg1->AddEntry(h8,"W+jets","f");
  lg1->AddEntry(h7,"t#bar{t}","f");
  lg1->AddEntry(h9,"Z+jets","f");

  // Signal MC
  if (var < 32){
    ha1->Draw("histsame");
    hb1->Draw("histsame");
    lg1->AddEntry(ha1,"#gamma#gamma#rightarrowWW, a^{0}_{W}/#Lambda^{2}=1*10^{-6} GeV^{-2}");
    lg1->AddEntry(hb1,"#gamma#gamma#rightarrowZZ, a^{0}_{Z}/#Lambda^{2}=1*10^{-5} GeV^{-2}");
  } else if (var < 58) {
    ha1->Draw("histsame");
    hd1->Draw("histsame");
    lg1->AddEntry(ha1,"#gamma#gamma#rightarrowWW, a^{0}_{W}/#Lambda^{2}=1*10^{-6} GeV^{-2}");
    lg1->AddEntry(hd1,"#gamma#gamma#rightarrowWW, a^{C}_{W}/#Lambda^{2}=2*10^{-5} GeV^{-2}");
  } else {
    hb1->Draw("histsame");
    hc1->Draw("histsame");
    lg1->AddEntry(hb1,"#gamma#gamma#rightarrowZZ, a^{0}_{Z}/#Lambda^{2}=1*10^{-5} GeV^{-2}");
    lg1->AddEntry(hc1,"#gamma#gamma#rightarrowZZ, a^{C}_{Z}/#Lambda^{2}=1*10^{-5} GeV^{-2}");
  }

  h100->SetLineColor(kBlack);
  h100->SetLineWidth(2);

  lg1->AddEntry(h100,"2017 Data", "elp");
  lg1->Draw("same");
  
  c1->cd(2);
  /*
  h12->SetStats(0);
  h12->SetMinimum(0.01);
  h12->Draw("hist");
  h12err->Draw("e2same");
  h11->Draw("histsame");
  h10->Draw("histsame");
  */
  h10->SetStats(0);                                                                                                                                           
  h10->SetMinimum(0.01);                                                                                                                                      
  h10->Draw("hist");                                                                                                                                          
  h10err->Draw("e2same");                                                                                                                                     

  h6->Draw("histsame");
  h5->Draw("histsame");
  h4->Draw("histsame");
  h3->Draw("histsame");
  h2->Draw("histsame");
  h8->Draw("histsame");
  h9->Draw("histsame");
  h7->Draw("histsame");
  gPad->SetLogy();
  h100->Draw("esame");

  // Signal MC                                                                                                                                                                        
  if (var < 32){
    ha1->Draw("histsame");
    hb1->Draw("histsame");
  } else if (var < 58) {
    ha1->Draw("histsame");
    hd1->Draw("histsame");
  } else {
    hb1->Draw("histsame");
    hc1->Draw("histsame");
  }

  c1->cd(3);
  /*
  TH1F *h1000err = (TH1F *)h12err->Clone("h1000err");
  h1000err->Divide(h12);
  */
  TH1F *h1000err = (TH1F *)h10err->Clone("h1000err");                                                                                                         
  h1000err->Divide(h10);                                                                                                                                      

  h1000err->SetMinimum(0); h1000err->SetMaximum(2.0);
  h1000err->Draw("E2");


  h1000->SetMarkerStyle(20); h1000->SetLineWidth(3);
  h1000->Sumw2();
  cout << "MC = " << h10->GetSumOfWeights() << ", data = " << h1000->GetSumOfWeights() << ", ratio = " << h1000->GetSumOfWeights()/h10->GetSumOfWeights() << endl;

  h1000->Divide(h10);
  h1000->SetMaximum(2.0);
  h1000->SetMinimum(0.0);
  if(rangelo != 0 || rangehi != 1)
    h1000->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h1000->SetStats(0);
  h1000->SetTitle(thetitle);
  h1000->SetXTitle(thetitle);
  h1000->SetMarkerStyle(20); h1000->SetLineWidth(3); h1000->SetLineColor(kBlack);
  h1000->Draw("esame");

  TLine *l1;
  TLine *l2;
  TLine *l3;
  if(rangelo != 0 || rangehi != 1)
    {
      l1 = new TLine(rangelo,1.0,rangehi,1.0);
      l2 = new TLine(rangelo,1.1,rangehi,1.1);
      l3 = new TLine(rangelo,0.9,rangehi,0.9);
    }
  else
    {
      l1 = new TLine(h1000->GetXaxis()->GetXmin(),1.0,h1000->GetXaxis()->GetXmax(),1.0);
      l2 = new TLine(h1000->GetXaxis()->GetXmin(),1.1,h1000->GetXaxis()->GetXmax(),1.1);
      l3 = new TLine(h1000->GetXaxis()->GetXmin(),0.9,h1000->GetXaxis()->GetXmax(),0.9);
    }
  l1->SetLineColor(2);
  l1->SetLineStyle(2);
  l1->SetLineWidth(3);
  l1->Draw("same");

  l2->SetLineColor(2);
  l2->SetLineStyle(2);                                                                                                               
  l2->SetLineWidth(3);
  //  l2->Draw("same");

  l3->SetLineColor(2);
  l3->SetLineStyle(2);
  l3->SetLineWidth(3);
  //  l3->Draw("same");

  CMS_lumi((TPad*)c1->GetPad(1),0,0,"2017, L = 37.2 fb^{-1}");
  CMS_lumi((TPad*)c1->GetPad(2),0,0,"2017, L = 37.2 fb^{-1}");
  CMS_lumi((TPad*)c1->GetPad(3),0,0,"2017, L = 37.2 fb^{-1}");

  c1->Update();
  TString outplotname = outplotdir+"validationplots2017BCDEF_ntupleULReMiniv4final_" + filetitle + ".pdf";
  c1->SaveAs(outplotname);

  // Draw on thesis histogram
  pad1->cd();
  h10->SetStats(0);                                                                                                                                           
  h10->SetMinimum(0.03);
  h10->SetMaximum(h10err->GetMaximum()*1E5);
  h10->GetYaxis()->SetLabelOffset(0.01);                                                                                                                             
  h10->GetYaxis()->SetLabelFont(43);                                                                                                                             
  h10->GetYaxis()->SetLabelSize(20);
  h10->GetYaxis()->SetTitleFont(43);
  h10->GetYaxis()->SetTitleSize(24);
  h10->GetYaxis()->SetTitleOffset(1.5);

  // Logic for y axis title 
  h10->GetYaxis()->SetTitle("Events / bin");
  h10->Draw("hist");
  lg1->SetX1NDC(0.4); 
  lg1->Draw();

  // h10->GetYaxis()->SetLabelSize(0.);
  // TGaxis *axis = new TGaxis( 0.5, 0., 0.5, 1, 0,1,510,"");
  // axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  // axis->SetLabelSize(15);
  // axis->Draw();            
  h10err->Draw("e2same");                                                                                                                                     

  h6->Draw("histsame");
  h5->Draw("histsame");
  h4->Draw("histsame");
  h3->Draw("histsame");
  h2->Draw("histsame");
  h8->Draw("histsame");
  h9->Draw("histsame");
  h7->Draw("histsame");
  gPad->SetLogy();
  h100->Draw("esame");
  gPad->RedrawAxis();

  // Signal MC on thesis pad                                                                                                                                                                       
  if (var < 32){
    ha1->Draw("histsame");
    hb1->Draw("histsame");
  } else if (var < 58) {
    ha1->Draw("histsame");
    hd1->Draw("histsame");
  } else {
    hb1->Draw("histsame");
    hc1->Draw("histsame");
  }

  pad2->cd();
  h1000err->GetYaxis()->SetLabelFont(43);
  h1000err->GetYaxis()->SetLabelOffset(0.01);
  h1000err->GetYaxis()->SetLabelSize(20);
  h1000err->GetXaxis()->SetLabelFont(43);
  h1000err->GetXaxis()->SetLabelSize(20);
  h1000err->GetXaxis()->SetTitleFont(43);
  h1000err->GetXaxis()->SetTitleSize(24);
  h1000err->GetXaxis()->SetTitleOffset(3.3);
  h1000err->SetMinimum(0.2);
  h1000err->SetMaximum(1.8);
  h1000err->Draw("E2");
  h1000err->GetYaxis()->SetTitleFont(43);
  h1000err->GetYaxis()->SetTitleSize(24);
  h1000err->GetYaxis()->SetTitleOffset(1.5);
  h1000err->GetYaxis()->SetTitle("Data/Simulation ");
  h1000->Draw("esame");
  l1->Draw("same");



  pad1->cd();
  TLatex l;
  l.SetNDC();
  l.SetTextSize(0.06);
  l.SetTextAlign(13);
  l.SetTextColor(kBlack);
  l.DrawLatex(0.15,0.85,"#splitline{#font[61]{CMS-TOTEM}}{#scale[0.76]{#font[52]{Internal}}}");
  l.SetTextAlign(31);
  l.DrawLatex(0.9,0.92,"#scale[0.85]{2017, 37.2 fb^{-1} (13 TeV)}");

  c_thesis->SaveAs("ch-6/fig/validationplots2017BCDEF_ntupleULReMiniv4final_"+filetitle+".pdf");

  if (saveToRootFile){
    TString outplotname_root = "validationplots2017BCDEF_ntupleULReMiniv4final_" + filetitle + ".root";
    TFile *outRoot = new TFile(outplotname_root,"RECREATE");
    std::cout << "Data and MC plot saved in " << outRoot->GetName() << std::endl;
    outRoot->cd();    
    h10->SetName("MC");
    h10->Write();
    h100->SetName("Data");
    h100->Write();
    outRoot->Close();
  }
  // Signal MC only
  //  TCanvas *c3 = new TCanvas("c3","c3");
  //  h7->Draw("hist");
  //  ha->Draw("hist");
  // f100->Close();
  // f2->Close();
  // f3->Close();
  // f4->Close();
  // f5->Close();
  // f6->Close();
  // f7->Close();
  // f8->Close();
  // f9->Close();
  // f10->Close();
  // fa1->Close();
  // fa1_2->Close();
  // fa1_3->Close();
  // fa2->Close();
  // fa2_2->Close();
  // fb1->Close();
  // fb1_2->Close();
  // fb1_3->Close();
  // fb2->Close();
  // fb2_2->Close();
  // fd1->Close();
  // fd1_2->Close();
  // fd1_3->Close();
  // fd2->Close();
  // fd2_2->Close();
}

void PlotStackAll2017()
{
  ULPlotStackTest2017(1);
  ULPlotStackTest2017(2);
  ULPlotStackTest2017(3);
  ULPlotStackTest2017(4);
  ULPlotStackTest2017(5);
  ULPlotStackTest2017(6);
  ULPlotStackTest2017(7);
  ULPlotStackTest2017(8);
  ULPlotStackTest2017(9);
  ULPlotStackTest2017(13);
  ULPlotStackTest2017(14);
  ULPlotStackTest2017(15);
  ULPlotStackTest2017(16);
  ULPlotStackTest2017(17);
  ULPlotStackTest2017(18);
  ULPlotStackTest2017(19);
  ULPlotStackTest2017(20);
  ULPlotStackTest2017(22);
  ULPlotStackTest2017(32);
  ULPlotStackTest2017(33);
  ULPlotStackTest2017(34);
  ULPlotStackTest2017(35);
  ULPlotStackTest2017(36);
  ULPlotStackTest2017(37);  
  ULPlotStackTest2017(38);

  ULPlotStackTest2017(58);
  ULPlotStackTest2017(59);
  ULPlotStackTest2017(60);
  ULPlotStackTest2017(61);
  ULPlotStackTest2017(62);
}

void PlotStackSideband2017()
{
  ULPlotStackTest2017(39);
  ULPlotStackTest2017(40);
  ULPlotStackTest2017(41);
  ULPlotStackTest2017(42);
  ULPlotStackTest2017(43);
  ULPlotStackTest2017(44);
  ULPlotStackTest2017(45);
  ULPlotStackTest2017(46);
  ULPlotStackTest2017(47);
  ULPlotStackTest2017(48);

  ULPlotStackTest2017(63);
  ULPlotStackTest2017(64);
  ULPlotStackTest2017(65);
  ULPlotStackTest2017(66);
  ULPlotStackTest2017(67);
  ULPlotStackTest2017(68);
  ULPlotStackTest2017(69);
  ULPlotStackTest2017(70);
  ULPlotStackTest2017(71);
  ULPlotStackTest2017(72);
}

void PlotEverything2017()
{
  ULPlotStackTest2017(1);
  ULPlotStackTest2017(2);
  ULPlotStackTest2017(3);
  ULPlotStackTest2017(4);
  ULPlotStackTest2017(5);
  ULPlotStackTest2017(6);
  ULPlotStackTest2017(7);
  ULPlotStackTest2017(8);
  ULPlotStackTest2017(9);
  ULPlotStackTest2017(13);
  ULPlotStackTest2017(14);
  ULPlotStackTest2017(15);
  ULPlotStackTest2017(16);
  ULPlotStackTest2017(17);
  ULPlotStackTest2017(18);
  ULPlotStackTest2017(19);
  ULPlotStackTest2017(20);
  ULPlotStackTest2017(22);
  ULPlotStackTest2017(32);
  ULPlotStackTest2017(33);
  ULPlotStackTest2017(34);
  ULPlotStackTest2017(35);
  ULPlotStackTest2017(36);
  ULPlotStackTest2017(37);  
  ULPlotStackTest2017(38);

  ULPlotStackTest2017(58);
  ULPlotStackTest2017(59);
  ULPlotStackTest2017(60);
  ULPlotStackTest2017(61);
  ULPlotStackTest2017(62);

  ULPlotStackTest2017(39);
  ULPlotStackTest2017(40);
  ULPlotStackTest2017(41);
  ULPlotStackTest2017(42);
  ULPlotStackTest2017(43);
  ULPlotStackTest2017(44);
  ULPlotStackTest2017(45);
  ULPlotStackTest2017(46);
  ULPlotStackTest2017(47);
  ULPlotStackTest2017(48);

  ULPlotStackTest2017(63);
  ULPlotStackTest2017(64);
  ULPlotStackTest2017(65);
  ULPlotStackTest2017(66);
  ULPlotStackTest2017(67);
  ULPlotStackTest2017(68);
  ULPlotStackTest2017(69);
  ULPlotStackTest2017(70);
  ULPlotStackTest2017(71);
  ULPlotStackTest2017(72);
}

void PlotThesis2017(){
  ULPlotStackTest2017(2);
  ULPlotStackTest2017(14);
  ULPlotStackTest2017(16);
  ULPlotStackTest2017(17);
}