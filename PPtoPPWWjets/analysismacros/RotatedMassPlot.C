#include "CMS_lumi.h"

void RotatedMassPlot()
{
  // TString outplotdir = "validationplots/";
  TString outplotdir = "";
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  TGaxis::SetExponentOffset(-0.085,-0.02,"y");

  Float_t mcaxsec = 0.0454; // pb, a0W=1E-6
  Float_t mcbxsec = 1.7859991686478713; // pb, a0Z=5E-5
  Float_t mccxsec = 0.12741628575501507; // pb, aCZ=5E-5
  Float_t mcdxsec = 0.1648; // pb, aCW=2E-5

  Float_t lumi2017B = 2.361;
  Float_t lumi2017C = 8.577;
  Float_t lumi2017D = 4.075;
  Float_t lumi2017E = 8.948;
  Float_t lumi2017F = 13.214;
  TString hist = "hprunedrotatedjjdat";
  TString thextitle = "cos(#pi / 4)m(j1) + sin(#pi / 4)m(j2) [GeV]";
  TString theytitle = "Events / 2 GeV";
  TString filetitle = "prunedrotatedjjdatsignal";
  hist = "PreselectionAndControl/"+hist;

  TString signalFolder = "/eos/cms/store/group/phys_smp/HadronicVV/signalSamples_v6/";
  // Load signal MC files
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

  TFile *fb1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z5E-5_preTS2_2017B.root");
  TH1F *hb1 = (TH1F *)fb1->Get(hist);
  TFile *fb1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z5E-5_preTS2_2017C.root");
  TH1F *hb1_2 = (TH1F *)fb1_2->Get(hist);
  TFile *fb1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z5E-5_preTS2_2017D.root");
  TH1F *hb1_3 = (TH1F *)fb1_3->Get(hist);

  TFile *fb2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z5E-5_postTS2_2017E.root");
  TH1F *hb2 = (TH1F *)fb2->Get(hist);
  TFile *fb2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZA0Z5E-5_postTS2_2017F.root");
  TH1F *hb2_2 = (TH1F *)fb2_2->Get(hist);

  TFile *fc1 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ5E-5_preTS2_2017B.root");
  TH1F *hc1 = (TH1F *)fc1->Get(hist);
  TFile *fc1_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ5E-5_preTS2_2017C.root");
  TH1F *hc1_2 = (TH1F *)fc1_2->Get(hist);
  TFile *fc1_3 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ5E-5_preTS2_2017D.root");
  TH1F *hc1_3 = (TH1F *)fc1_3->Get(hist);

  TFile *fc2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ5E-5_postTS2_2017E.root");
  TH1F *hc2 = (TH1F *)fc2->Get(hist);
  TFile *fc2_2 = TFile::Open(signalFolder+"vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclZZACZ5E-5_postTS2_2017F.root");
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

  TCanvas *c1 = new TCanvas("c1","c1",1000,666);
  c1->cd(1);  
  int rebinfactor = 1;

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

  cout << "Using binsize: " << ha1->GetBinWidth(1) << " GeV" << endl;
  ha1->Sumw2(); // Signal, a0W=1E-6, 2017B --> 2017preTS2
  ha1->Scale(mcaxsec*1000*lumi2017B/27800.0);
  ha1_2->Sumw2(); // Signal, a0W=1E-6, 2017C 
  ha1_2->Scale(mcaxsec*1000*lumi2017C/110100.0);
  ha1_3->Sumw2(); // Signal, a0W=1E-6, 2017D 
  ha1_3->Scale(mcaxsec*1000*lumi2017D/39100.0);
  ha1->Add(ha1_2);
  ha1->Add(ha1_3);
  ha1->SetLineWidth(3); ha1->SetLineColor(kGray+3); ha1->SetMarkerStyle(0); ha1->SetMarkerColor(kGray+3);

  ha2->Sumw2(); // Signal, a0W=1E-6, 2017E --> 2017postTS2                                                                                       
  ha2->Scale(mcaxsec*1000*lumi2017E/76700.0);
  ha2_2->Sumw2(); // Signal, a0W=1E-6, 2017F 
  ha2_2->Scale(mcaxsec*1000*lumi2017F/139500.0);
  ha2->Add(ha2_2);
  ha2->SetLineWidth(3); ha2->SetLineColor(kGray+3); ha2->SetMarkerStyle(0); ha2->SetMarkerColor(kGray+3);
  ha1->Add(ha2);
  
  hb1->Sumw2(); // Signal, a0Z=5E-5, 2017B --> 2017preTS2
  hb1->Scale(mcbxsec*1000*lumi2017B/19624.0);
  hb1_2->Sumw2(); // Signal, a0Z=5E-5, 2017C 
  hb1_2->Scale(mcbxsec*1000*lumi2017C/19031.0);
  hb1_3->Sumw2(); // Signal, a0Z=5E-5, 2017D 
  hb1_3->Scale(mcbxsec*1000*lumi2017D/19918.0);
  hb1->Add(hb1_2);
  hb1->Add(hb1_3);
  hb1->SetLineWidth(3); hb1->SetLineColor(kAzure-2); hb1->SetMarkerStyle(0); hb1->SetMarkerColor(kAzure-2);

  hb2->Sumw2(); // Signal, a0Z=5E-5, 2017E --> 2017postTS2                                                                                       
  hb2->Scale(mcbxsec*1000*lumi2017E/19895.0);
  hb2_2->Sumw2(); // Signal, a0Z=5E-5, 2017F 
  hb2_2->Scale(mcbxsec*1000*lumi2017F/19698.0);
  hb2->Add(hb2_2);
  hb2->SetLineWidth(3); hb2->SetLineColor(kAzure-2); hb2->SetMarkerStyle(0); hb2->SetMarkerColor(kAzure-2);
  hb1->Add(hb2);
  
  hc1->Sumw2(); // Signal, aCZ=5E-5, 2017B --> 2017preTS2
  hc1->Scale(mccxsec*1000*lumi2017B/19730.0);
  hc1_2->Sumw2(); // Signal, aCZ=5E-5, 2017C 
  hc1_2->Scale(mccxsec*1000*lumi2017C/19516.0);
  hc1_3->Sumw2(); // Signal, aCZ=5E-5, 2017D 
  hc1_3->Scale(mccxsec*1000*lumi2017D/19792.0);
  hc1->Add(hc1_2);
  hc1->Add(hc1_3);
  hc1->SetLineWidth(3); hc1->SetLineColor(kOrange+2); hc1->SetMarkerStyle(0); hc1->SetMarkerColor(kOrange+2);

  hc2->Sumw2(); // Signal, aCZ=5E-5, 2017E --> 2017postTS2                                                                                       
  hc2->Scale(mccxsec*1000*lumi2017E/19842.0);
  hc2_2->Sumw2(); // Signal, aCZ=5E-5, 2017F 
  hc2_2->Scale(mccxsec*1000*lumi2017F/19800.0);
  hc2->Add(hc2_2);
  hc2->SetLineWidth(3); hc2->SetLineColor(kOrange+2); hc2->SetMarkerStyle(0); hc2->SetMarkerColor(kOrange+2);
  hc1->Add(hc2);
  
  hd1->Sumw2(); // Signal, aCW=2E-5, 2017B --> 2017preTS2
  hd1->Scale(mcdxsec*1000*lumi2017B/27800.0);
  hd1_2->Sumw2(); // Signal, aCW=2E-5, 2017C 
  hd1_2->Scale(mcdxsec*1000*lumi2017C/92100.0);
  hd1_3->Sumw2(); // Signal, aCW=2E-5, 2017D 
  hd1_3->Scale(mcdxsec*1000*lumi2017D/41700.0);
  hd1->Add(hd1_2);
  hd1->Add(hd1_3);
  hd1->SetLineWidth(3); hd1->SetLineColor(kSpring-1); hd1->SetMarkerStyle(0); hd1->SetMarkerColor(kSpring-1); 

  hd2->Sumw2(); // Signal, aCW=2E-5, 2017E --> 2017postTS2                                                                                       
  hd2->Scale(mcdxsec*1000*lumi2017E/92100.0);
  hd2_2->Sumw2(); // Signal, aCW=2E-5, 2017F 
  hd2_2->Scale(mcdxsec*1000*lumi2017F/119900.0);
  hd2->Add(hd2_2);
  hd2->SetLineWidth(3); hd2->SetLineColor(kSpring-1); hd2->SetMarkerStyle(0); hd2->SetMarkerColor(kSpring-1);
  hd1->Add(hd2);
  
  TLegend *lg1 = new TLegend(0.45,0.5,0.8,0.85);
  ha1->GetXaxis()->SetTitle(thextitle);
  ha1->GetXaxis()->SetRangeUser(50,300);
  ha1->GetYaxis()->SetTitle(theytitle);

  auto clone = ha1->DrawNormalized("hist");
  hb1->DrawNormalized("histsame");
  hc1->DrawNormalized("histsame");
  hd1->DrawNormalized("histsame");
  lg1->SetBorderSize(0);
  lg1->AddEntry(ha1,"#gamma#gamma#rightarrowWW, a^{W}_{0}/#Lambda^{2} = 1 #times 10^{-6} GeV^{-2}");
  lg1->AddEntry(hd1,"#gamma#gamma#rightarrowWW, a^{W}_{C}/#Lambda^{2} = 2 #times 10^{-5} GeV^{-2}");
  lg1->AddEntry(hb1,"#gamma#gamma#rightarrowZZ, a^{Z}_{0}/#Lambda^{2} = 5 #times 10^{-5} GeV^{-2}");
  lg1->AddEntry(hc1,"#gamma#gamma#rightarrowZZ, a^{Z}_{C}/#Lambda^{2} = 5 #times 10^{-5} GeV^{-2}");
  lg1->Draw("same");
  CMS_lumi((TPad*)c1->GetPad(0),4,0,"");
  clone->GetYaxis()->SetRangeUser(0,0.12);
  c1->Update();
  TString outplotname = outplotdir+"validationplots2017BCDEF_ntupleULReMiniv4final_" + filetitle + ".pdf";
  c1->SaveAs(outplotname);
  fa1->Close();
  fa1_2->Close();
  fa1_3->Close();
  fa2->Close();
  fa2_2->Close();
  fb1->Close();
  fb1_2->Close();
  fb1_3->Close();
  fb2->Close();
  fb2_2->Close();
  fd1->Close();
  fd1_2->Close();
  fd1_3->Close();
  fd2->Close();
  fd2_2->Close();
}
