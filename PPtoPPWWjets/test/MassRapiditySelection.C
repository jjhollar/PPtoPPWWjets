#include "../analysismacros/CMS_lumi.h"

void MassRapiditySelectionWW(TFile *file= new TFile("/eos/cms/store/group/phys_smp/HadronicVV/signalSamples_v7/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W2E-6_2018ABCD.root")) {

  // Band1 lower                                                                                                                                                            
  TLine *l1 = new TLine(-0.69695, -0.5,-0.0838473, -0.0144293);
  TLine *l2 = new TLine(-0.570629, -0.5,-0.0234464, -0.0666299);
  TLine *l3 = new TLine(-0.0838473, -0.0144293,-0.0234464, -0.0666299);
  TLine *l4 = new TLine(-0.69695, -0.5,-0.570629, -0.5);
  // Band1 upper                                                                                                                                                            
  //  TLine *l5 = new TLine(0.00465359, 0.055671,0.565635, 0.500041);
  //  TLine *l6 = new TLine(0.0649541, 0.00347064,0.691956, 0.500041);
  //  TLine *l7 = new TLine(0.00465359, 0.055671,0.0649541, 0.00347064);
  //  TLine *l8 = new TLine(0.565635, 0.500041,0.691956, 0.500041);
  // Band2 lower                                                                                                                                                            
  TLine *l9 = new TLine(-0.0333464, 0.0590711,-0.542277, 0.5);
  TLine *l10 = new TLine(-0.0862473, 0.0171706,-0.643812, 0.5);
  TLine *l11 = new TLine(-0.0333464, 0.0590711,-0.0862473, 0.0171706);
  TLine *l12 = new TLine(-0.643812, 0.5,-0.542277, 0.5);
  // Band2 upper                                                                                                                                                            
  //  TLine *l13 = new TLine(0.0144536, -0.07003,0.510813, -0.5);
  //  TLine *l14 = new TLine(0.0673542, -0.0281293,0.612348, -0.5);
  //  TLine *l15 = new TLine(0.0144536, -0.07003,0.0673542, -0.0281293);
  //  TLine *l16 = new TLine(0.510813, -0.5,0.612348, -0.5);
  // Diamond                                                                                                                                                                
  TLine *l17 = new TLine(-0.103848, 0.00305359,-0.0155464, 0.0730542);
  TLine *l18 = new TLine(-0.0155464, 0.0730542,0.0850544, -0.0140464);
  TLine *l19 = new TLine(0.0850544, -0.0140464,-0.00334641, -0.0839473);
  TLine *l20 = new TLine(-0.00334641, -0.0839473,-0.103848, 0.00305359);

	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
  TH2D *hmassrapiditymatchsigmcmmww =
      (TH2D *)file->Get("Signal/hmassrapiditymatchsigmcmmww");
  TCanvas* c1 = new TCanvas("c1", "c1", 1920, 1080);
  TCanvas* c2 = new TCanvas("c2", "c2", 1400, 1080);
  c1->Divide(3, 2);
  TH2F *rotated = new TH2F("rotated", "rotated", 500, -5, 5, 500, -5, 5);
  vector<double> th, peak;
  for (int t = 0; t < 180; t++) {
    double theta = t * TMath::Pi() / 180.;
    th.push_back(theta);
    // rotate counter-clockwise by theta
    for (int i = 0; i < hmassrapiditymatchsigmcmmww->GetNbinsX(); i++) {
      for (int j = 0; j < hmassrapiditymatchsigmcmmww->GetNbinsY(); j++) {
        double x = hmassrapiditymatchsigmcmmww->GetXaxis()->GetBinCenter(i);
        double y = hmassrapiditymatchsigmcmmww->GetYaxis()->GetBinCenter(j);
        double content = hmassrapiditymatchsigmcmmww->GetBinContent(i, j);
        double x_r = x * TMath::Cos(theta) - y * TMath::Sin(theta);
        double y_r = x * TMath::Sin(theta) + y * TMath::Cos(theta);
        rotated->Fill(x_r, y_r, content);
      }
    }

    // project the rotation on X
    TH1D *projectionX = rotated->ProjectionX();
    projectionX->Rebin(2);
    peak.push_back(projectionX->GetMaximum());
    rotated->Reset();
    projectionX->Reset();
  }
  c1->cd(1);
  TGraph *g = new TGraph(th.size(), &th[0], &peak[0]);
  g->SetMarkerStyle(8);
  g->Draw("AP");

  auto it_max1 = std::max_element(peak.begin(), peak.begin() + peak.size() / 2);
  auto it_max2 = std::max_element(peak.begin() + peak.size() / 2, peak.end());
  double th_rot1 = th[it_max1 - peak.begin()];
  double th_rot2 = th[it_max2 - peak.begin()];
  double max1 = *it_max1;
  double max2 = *it_max2;

  TH2F *rotated_1 = new TH2F("Rotated_1", "Rotated_1", 500, -5, 5, 500, -5, 5);
  TH2F *rotated_2 = new TH2F("Rotated_2", "Rotated_2", 500, -5, 5, 500, -5, 5);

  for (int i = 0; i < hmassrapiditymatchsigmcmmww->GetNbinsX(); i++) {
    for (int j = 0; j < hmassrapiditymatchsigmcmmww->GetNbinsY(); j++) {
      double x = hmassrapiditymatchsigmcmmww->GetXaxis()->GetBinCenter(i);
      double y = hmassrapiditymatchsigmcmmww->GetYaxis()->GetBinCenter(j);
      double content = hmassrapiditymatchsigmcmmww->GetBinContent(i, j);
      double x_r = x * TMath::Cos(th_rot1) - y * TMath::Sin(th_rot1);
      double y_r = x * TMath::Sin(th_rot1) + y * TMath::Cos(th_rot1);
      rotated_1->Fill(x_r, y_r, content);
    }
  }
  c1->cd(2);
  rotated_1->GetXaxis()->SetRangeUser(-1.5, 1.5);
  rotated_1->GetYaxis()->SetRangeUser(-1.5, 1.5); 
  rotated_1->GetXaxis()->SetTitle("(1 - m(WW)/m(pp))*cos(#theta_{1})-(y(pp)-y(WW))*sin(#theta_{1})");
  rotated_1->GetYaxis()->SetTitle("(1 - m(WW)/m(pp))*sin(#theta_{1})+(y(pp)-y(WW))*cos(#theta_{1})");
  rotated_1->Draw("colz");
  c1->cd(5);
  TH1D *proj1 = rotated_1->ProjectionX();
  proj1->GetXaxis()->SetRangeUser(-2, 2);
  proj1->Rebin(2);
  proj1->Draw();
  TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)", -2, 2);
  f1->SetParameters(max1, 0, 0.05, 0, -0.5, 0.5);
  f1->SetNpx(10000);

  proj1->Fit(f1);

  for (int i = 0; i < hmassrapiditymatchsigmcmmww->GetNbinsX(); i++) {
    for (int j = 0; j < hmassrapiditymatchsigmcmmww->GetNbinsY(); j++) {
      double x = hmassrapiditymatchsigmcmmww->GetXaxis()->GetBinCenter(i);
      double y = hmassrapiditymatchsigmcmmww->GetYaxis()->GetBinCenter(j);
      double content = hmassrapiditymatchsigmcmmww->GetBinContent(i, j);
      double x_r = x * TMath::Cos(th_rot2) - y * TMath::Sin(th_rot2);
      double y_r = x * TMath::Sin(th_rot2) + y * TMath::Cos(th_rot2);
      rotated_2->Fill(x_r, y_r, content);
    }
  }
  c1->cd(3);
  rotated_2->GetXaxis()->SetRangeUser(-1.5, 1.5);
  rotated_2->GetYaxis()->SetRangeUser(-1.5, 1.5);
  rotated_2->GetXaxis()->SetTitle("(1 - m(WW)/m(pp))*cos(#theta_{2})-(y(pp)-y(WW))*sin(#theta_{2})");
  rotated_2->GetYaxis()->SetTitle("(1 - m(WW)/m(pp))*sin(#theta_{2})+(y(pp)-y(WW))*cos(#theta_{2})");

  rotated_2->Draw("colz");
  c1->cd(6);
  TH1D *proj2 = rotated_2->ProjectionX();
  proj2->GetXaxis()->SetRangeUser(-1.5, 1.5);
  proj2->Rebin(2);
  proj2->Draw();
  TF1 *f2 = new TF1("f2", "gaus(0)+gaus(3)", -2, 2);
  f2->SetParameters(max2, 0, 0.05, 0, 0.5, 0.5);
  proj2->Fit(f2);

  c1->cd(4);
  hmassrapiditymatchsigmcmmww->GetXaxis()->SetRangeUser(-1.5, 0.4);
  hmassrapiditymatchsigmcmmww->GetYaxis()->SetRangeUser(-1.1, 0.9);
  hmassrapiditymatchsigmcmmww->GetXaxis()->SetTitle("1 - m(WW)/m(pp)");
  hmassrapiditymatchsigmcmmww->GetYaxis()->SetTitle("y(pp)-y(WW)");
  hmassrapiditymatchsigmcmmww->Draw("colz");

  TGraphErrors *band1 = new TGraphErrors(4);
  TGraphErrors *band2 = new TGraphErrors(4);
  TGraphErrors *diamond = new TGraphErrors(4);

  double nSigmaDiamond = 1.25;
  double nSigmaBands = 0.75;

  TF1 *band1Center =
      new TF1("band1Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double sigma_1 =
      TMath::Abs(f1->GetParameter(2)) /
      (TMath::Sin(th_rot1));
  double slope_1 = 1./TMath::Tan(th_rot1);
  double intercept_1 = - f1->GetParameter(1)/TMath::Sin(th_rot1);
  band1Center->SetParameters(th_rot1,
                             f1->GetParameter(1));
  TF1 *band2Center =
      new TF1("band2Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double sigma_2 =
      TMath::Abs(f2->GetParameter(2)) /
      (TMath::Sin(th_rot2));
  double slope_2 = 1./TMath::Tan(th_rot2);
  double intercept_2 = - f2->GetParameter(1)/TMath::Sin(th_rot2);
  band2Center->SetParameters(th_rot2,
                             f2->GetParameter(1));

  // Find parameters for the diamond (four interceptions in ascending order)
  // Interceptions are found as (q2-q1)/(m1-m2)
  double deltaM = slope_1 - slope_2;
  double diamondX_0 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_1 = (intercept_2 + nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_2 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_3 = (intercept_2 + nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaDiamond*sigma_1))/deltaM;
  if (diamondX_1 > diamondX_2){
  	auto tmp = diamondX_2;
  	diamondX_2 = diamondX_1;
  	diamondX_1 = tmp;
  }

  double diamondWidth = (sigma_1 < sigma_2) ? sigma_1 : sigma_2;
  TF1* diamondCenter = (sigma_1 < sigma_2) ? band1Center : band2Center;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_1;
  double band1X_0 = (-0.5 - (intercept_1 + nSigmaBands*sigma_1))/deltaM;
  double band1X_1 = (-0.5 - (intercept_1 - nSigmaBands*sigma_1))/deltaM;
  deltaM = slope_1 - slope_2;
  double band1X_2 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaBands*sigma_1))/deltaM;
  double band1X_3 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaBands*sigma_1))/deltaM;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_2;
  double band2X_0 = (0.5 - (intercept_2 - nSigmaBands*sigma_2))/deltaM;
  double band2X_1 = (0.5 - (intercept_2 + nSigmaBands*sigma_2))/deltaM;
  deltaM = slope_1 - slope_2;
  double band2X_2 = (intercept_2 - nSigmaBands*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double band2X_3 = (intercept_2 + nSigmaBands*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;

  band1->SetPoint(0, band1X_0, -0.5);
  band1->SetPointError(0, 0, 0);
  band1->SetPoint(1, band1X_1, band1Center->Eval(band1X_1));
  band1->SetPointError(1, 0, nSigmaBands*sigma_1);
  band1->SetPoint(2, band1X_2, band1Center->Eval(band1X_2));
  band1->SetPointError(2, 0, nSigmaBands*sigma_1);
  band1->SetPoint(3, band1X_3, band1Center->Eval(band1X_3) - nSigmaBands*sigma_1);
  band1->SetPointError(3, 0, 0);

  band1->SetFillColor(46);
  band1->SetFillStyle(3001);
  // band1->Draw("3same");

  band2->SetPoint(0, band2X_0, 0.5);
  band2->SetPointError(0, 0, 0);
  band2->SetPoint(1, band2X_1, band2Center->Eval(band2X_1));
  band2->SetPointError(1, 0, nSigmaBands*sigma_2);
  band2->SetPoint(2, band2X_2, band2Center->Eval(band2X_2));
  band2->SetPointError(2, 0, nSigmaBands*sigma_2);
  band2->SetPoint(3, band2X_3, band2Center->Eval(band2X_3) + nSigmaBands*sigma_2);
  band2->SetPointError(3, 0, 0);
  band2->SetFillColor(46);
  band2->SetFillStyle(3001);
  // band2->Draw("3same");

  diamond->SetPoint(0, diamondX_0, slope_1*diamondX_0 + nSigmaDiamond * sigma_1);
  diamond->SetPointError(0, 0, 0);
  diamond->SetPoint(1, diamondX_1, diamondCenter->Eval(diamondX_1));
  diamond->SetPointError(1, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(2, diamondX_2, diamondCenter->Eval(diamondX_2));
  diamond->SetPointError(2, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(3, diamondX_3, slope_1*diamondX_3 - nSigmaDiamond * sigma_1);
  diamond->SetPointError(3, 0, 0);
  diamond->SetFillColor(kGreen);
  diamond->SetFillStyle(3001);
  // diamond->Draw("3same");
  l1->SetLineColor(1); l1->SetLineWidth(3); l1->Draw();
  l2->SetLineColor(1); l2->SetLineWidth(3); l2->Draw("same");
  l3->SetLineColor(1); l3->SetLineWidth(3); l3->Draw("same");
  l4->SetLineColor(1);l4->SetLineWidth(3); l4->Draw("same");
  /*
  l5->SetLineColor(1); l5->SetLineWidth(3); l5->Draw("same");
  l6->SetLineColor(1); l6->SetLineWidth(3); l6->Draw("same");
  l7->SetLineColor(1); l7->SetLineWidth(3); l7->Draw("same");
  l8->SetLineColor(1); l8->SetLineWidth(3); l8->Draw("same");
  */
  l9->SetLineColor(1); l9->SetLineWidth(3); l9->Draw("same");
  l10->SetLineColor(1); l10->SetLineWidth(3); l10->Draw("same");
  l11->SetLineColor(1); l11->SetLineWidth(3); l11->Draw("same");
  l12->SetLineColor(1); l12->SetLineWidth(3); l12->Draw("same");
  /*
  l13->SetLineColor(1); l13->SetLineWidth(3); l13->Draw("same");
  l14->SetLineColor(1); l14->SetLineWidth(3); l14->Draw("same");
  l15->SetLineColor(1); l15->SetLineWidth(3); l15->Draw("same");
  l16->SetLineColor(1); l16->SetLineWidth(3); l16->Draw("same");
  */
  l17->SetLineColor(kRed); l17->SetLineWidth(3); l17->Draw("same");
  l18->SetLineColor(kRed); l18->SetLineWidth(3); l18->Draw("same");
  l19->SetLineColor(kRed); l19->SetLineWidth(3); l19->Draw("same");
  l20->SetLineColor(kRed); l20->SetLineWidth(3); l20->Draw("same");
  c2->cd();
  gPad->SetRightMargin(0.13);
  hmassrapiditymatchsigmcmmww->GetZaxis()->SetTitle("Events / bin");
  hmassrapiditymatchsigmcmmww->Draw("colz");
  // band1->Draw("3same");
  // band2->Draw("3same");
  // diamond->Draw("3same");
  CMS_TOTEM_lumi((TPad*)c2->GetPad(0),4,0,"");
  gPad->SetTicks(1,1);
  // TPaletteAxis *pal = (TPaletteAxis*)(hmassrapiditymatchsigmcmmww->GetListOfFunctions()->FindObject("palette"));

  TLatex latex;
  latex.DrawLatexNDC(0.15,0.83,"#scale[0.76]{a_{W}^{0}/#Lambda^{2} = 2 #times 10^{-6} GeV^{-2}}");
  c2->Print("MassMatchRatio.pdf");

  l1->SetLineColor(1); l1->SetLineWidth(3); l1->Draw();
  l2->SetLineColor(1); l2->SetLineWidth(3); l2->Draw("same");
  l3->SetLineColor(1); l3->SetLineWidth(3); l3->Draw("same");
  l4->SetLineColor(1);l4->SetLineWidth(3); l4->Draw("same");
  /*
  l5->SetLineColor(1); l5->SetLineWidth(3); l5->Draw("same");
  l6->SetLineColor(1); l6->SetLineWidth(3); l6->Draw("same");
  l7->SetLineColor(1); l7->SetLineWidth(3); l7->Draw("same");
  l8->SetLineColor(1); l8->SetLineWidth(3); l8->Draw("same");
  */
  l9->SetLineColor(1); l9->SetLineWidth(3); l9->Draw("same");
  l10->SetLineColor(1); l10->SetLineWidth(3); l10->Draw("same");
  l11->SetLineColor(1); l11->SetLineWidth(3); l11->Draw("same");
  l12->SetLineColor(1); l12->SetLineWidth(3); l12->Draw("same");
  /*
  l13->SetLineColor(1); l13->SetLineWidth(3); l13->Draw("same");
  l14->SetLineColor(1); l14->SetLineWidth(3); l14->Draw("same");
  l15->SetLineColor(1); l15->SetLineWidth(3); l15->Draw("same");
  l16->SetLineColor(1); l16->SetLineWidth(3); l16->Draw("same");
  */
  l17->SetLineColor(kRed); l17->SetLineWidth(3); l17->Draw("same");
  l18->SetLineColor(kRed); l18->SetLineWidth(3); l18->Draw("same");
  l19->SetLineColor(kRed); l19->SetLineWidth(3); l19->Draw("same");
  l20->SetLineColor(kRed); l20->SetLineWidth(3); l20->Draw("same");

  c2->Print("SignalRegionsDefinition.pdf");
  rotated_1->Draw("colz");
  CMS_lumi((TPad*)c2->GetPad(0),0,0,"a_{W}^{0}/#Lambda^{2} = 2*10^{-6} GeV^{-2}");
  c2->Print("SignalRegionsDefinition_rotated.pdf");
  proj1->Draw();
  CMS_lumi((TPad*)c2->GetPad(0),0,0,"a_{W}^{0}/#Lambda^{2} = 2*10^{-6} GeV^{-2}");
  c2->Print("SignalRegionsDefinition_bandFitted.pdf");  




  cout << "Found good rotation angles: " << th_rot1 << " " << th_rot2
       << std::endl;
  cout << "I suggest applying the following cut:\n"
       << "Let Mn = 1 - (mydijet.M()/mppsmultmult->at(0))\n and Yn = "
          "yppsmultmult->at(0)-mydijet.Rapidity()\n"
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) - sigma_1 << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) + sigma_1 << "\nOR\n"
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) - sigma_2 << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) + sigma_2 << endl;
}

void MassRapiditySelectionZZ(TFile *file) {
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
  TH2D *hmassrapiditymatchsigmcmmzz =
      (TH2D *)file->Get("Signal/hmassrapiditymatchsigmcmmzz");
  TCanvas* c1 = new TCanvas("c1", "c1", 1920, 1080);
  c1->Divide(3, 2);
  TH2F *rotated = new TH2F("rotated", "rotated", 500, -5, 5, 500, -5, 5);
  vector<double> th, peak;
  for (int t = 0; t < 180; t++) {
    double theta = t * TMath::Pi() / 180.;
    th.push_back(theta);
    // rotate counter-clockwise by theta
    for (int i = 0; i < hmassrapiditymatchsigmcmmzz->GetNbinsX(); i++) {
      for (int j = 0; j < hmassrapiditymatchsigmcmmzz->GetNbinsY(); j++) {
        double x = hmassrapiditymatchsigmcmmzz->GetXaxis()->GetBinCenter(i);
        double y = hmassrapiditymatchsigmcmmzz->GetYaxis()->GetBinCenter(j);
        double content = hmassrapiditymatchsigmcmmzz->GetBinContent(i, j);
        double x_r = x * TMath::Cos(theta) - y * TMath::Sin(theta);
        double y_r = x * TMath::Sin(theta) + y * TMath::Cos(theta);
        rotated->Fill(x_r, y_r, content);
      }
    }

    // project the rotation on X
    TH1D *projectionX = rotated->ProjectionX();
    projectionX->Rebin(2);
    peak.push_back(projectionX->GetMaximum());
    rotated->Reset();
    projectionX->Reset();
  }
  c1->cd(1);
  TGraph *g = new TGraph(th.size(), &th[0], &peak[0]);
  g->SetMarkerStyle(8);
  g->Draw("AP");

  auto it_max1 = std::max_element(peak.begin(), peak.begin() + peak.size() / 2);
  auto it_max2 = std::max_element(peak.begin() + peak.size() / 2, peak.end());
  double th_rot1 = th[it_max1 - peak.begin()];
  double th_rot2 = th[it_max2 - peak.begin()];
  double max1 = *it_max1;
  double max2 = *it_max2;

  TH2F *rotated_1 = new TH2F("Rotated_1", "Rotated_1", 500, -5, 5, 500, -5, 5);
  TH2F *rotated_2 = new TH2F("Rotated_2", "Rotated_2", 500, -5, 5, 500, -5, 5);

  for (int i = 0; i < hmassrapiditymatchsigmcmmzz->GetNbinsX(); i++) {
    for (int j = 0; j < hmassrapiditymatchsigmcmmzz->GetNbinsY(); j++) {
      double x = hmassrapiditymatchsigmcmmzz->GetXaxis()->GetBinCenter(i);
      double y = hmassrapiditymatchsigmcmmzz->GetYaxis()->GetBinCenter(j);
      double content = hmassrapiditymatchsigmcmmzz->GetBinContent(i, j);
      double x_r = x * TMath::Cos(th_rot1) - y * TMath::Sin(th_rot1);
      double y_r = x * TMath::Sin(th_rot1) + y * TMath::Cos(th_rot1);
      rotated_1->Fill(x_r, y_r, content);
    }
  }
  c1->cd(2);
  rotated_1->GetXaxis()->SetRangeUser(-2, 2);
  rotated_1->GetYaxis()->SetRangeUser(-2, 2);
  rotated_1->GetXaxis()->SetTitle("1 - m(WW)/m(pp)");
  rotated_1->GetYaxis()->SetTitle("y(pp)-y(WW)");
  rotated_1->Draw("colz");
  c1->cd(5);
  TH1D *proj1 = rotated_1->ProjectionX();
  proj1->GetXaxis()->SetRangeUser(-2, 2);
  proj1->Rebin(2);
  proj1->Draw();
  TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)", -2, 2);
  f1->SetParameters(max1, 0, 0.05, 0, -0.5, 0.5);
  proj1->Fit(f1);

  for (int i = 0; i < hmassrapiditymatchsigmcmmzz->GetNbinsX(); i++) {
    for (int j = 0; j < hmassrapiditymatchsigmcmmzz->GetNbinsY(); j++) {
      double x = hmassrapiditymatchsigmcmmzz->GetXaxis()->GetBinCenter(i);
      double y = hmassrapiditymatchsigmcmmzz->GetYaxis()->GetBinCenter(j);
      double content = hmassrapiditymatchsigmcmmzz->GetBinContent(i, j);
      double x_r = x * TMath::Cos(th_rot2) - y * TMath::Sin(th_rot2);
      double y_r = x * TMath::Sin(th_rot2) + y * TMath::Cos(th_rot2);
      rotated_2->Fill(x_r, y_r, content);
    }
  }
  c1->cd(3);
  rotated_2->GetXaxis()->SetRangeUser(-2, 2);
  rotated_2->GetYaxis()->SetRangeUser(-2, 2);
  rotated_2->GetXaxis()->SetTitle("1 - m(WW)/m(pp)");
  rotated_2->GetYaxis()->SetTitle("y(pp)-y(WW)");
  rotated_2->Draw("colz");
  c1->cd(6);
  TH1D *proj2 = rotated_2->ProjectionX();
  proj2->GetXaxis()->SetRangeUser(-2, 2);
  proj2->Rebin(2);
  proj2->Draw();
  TF1 *f2 = new TF1("f2", "gaus(0)+gaus(3)", -2, 2);
  f2->SetParameters(max2, 0, 0.05, 0, 0.5, 0.5);
  proj2->Fit(f2);

  c1->cd(4);
  hmassrapiditymatchsigmcmmzz->GetXaxis()->SetRangeUser(-2, 2);
  hmassrapiditymatchsigmcmmzz->GetYaxis()->SetRangeUser(-2, 2);
  hmassrapiditymatchsigmcmmzz->GetXaxis()->SetTitle("1 - m(WW)/m(pp)");
  hmassrapiditymatchsigmcmmzz->GetYaxis()->SetTitle("y(pp)-y(WW)");
  hmassrapiditymatchsigmcmmzz->Draw("colz");

  TGraphErrors *band1 = new TGraphErrors(4);
  TGraphErrors *band2 = new TGraphErrors(4);
  TGraphErrors *diamond = new TGraphErrors(4);

  double nSigmaDiamond = 1.25;
  double nSigmaBands = 0.75;

  TF1 *band1Center =
      new TF1("band1Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double sigma_1 =
      TMath::Abs(f1->GetParameter(2)) /
      (TMath::Sin(th_rot1));
  double slope_1 = 1./TMath::Tan(th_rot1);
  double intercept_1 = - f1->GetParameter(1)/TMath::Sin(th_rot1);
  band1Center->SetParameters(th_rot1,
                             f1->GetParameter(1));
  TF1 *band2Center =
      new TF1("band2Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double sigma_2 =
      TMath::Abs(f2->GetParameter(2)) /
      (TMath::Sin(th_rot2));
  double slope_2 = 1./TMath::Tan(th_rot2);
  double intercept_2 = - f2->GetParameter(1)/TMath::Sin(th_rot2);
  band2Center->SetParameters(th_rot2,
                             f2->GetParameter(1));

  // Find parameters for the diamond (four interceptions in ascending order)
  // Interceptions are found as (q2-q1)/(m1-m2)
  double deltaM = slope_1 - slope_2;
  double diamondX_0 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_1 = (intercept_2 + nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_2 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaDiamond*sigma_1))/deltaM;
  double diamondX_3 = (intercept_2 + nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaDiamond*sigma_1))/deltaM;
  if (diamondX_1 > diamondX_2){
  	auto tmp = diamondX_2;
  	diamondX_2 = diamondX_1;
  	diamondX_1 = tmp;
  }

  double diamondWidth = (sigma_1 < sigma_2) ? sigma_1 : sigma_2;
  TF1* diamondCenter = (sigma_1 < sigma_2) ? band1Center : band2Center;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_1;
  double band1X_0 = (-0.5 - (intercept_1 + nSigmaBands*sigma_1))/deltaM;
  double band1X_1 = (-0.5 - (intercept_1 - nSigmaBands*sigma_1))/deltaM;
  deltaM = slope_1 - slope_2;
  double band1X_2 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 + nSigmaBands*sigma_1))/deltaM;
  double band1X_3 = (intercept_2 - nSigmaDiamond*sigma_2 - (intercept_1 - nSigmaBands*sigma_1))/deltaM;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_2;
  double band2X_0 = (0.5 - (intercept_2 - nSigmaBands*sigma_2))/deltaM;
  double band2X_1 = (0.5 - (intercept_2 + nSigmaBands*sigma_2))/deltaM;
  deltaM = slope_1 - slope_2;
  double band2X_2 = (intercept_2 - nSigmaBands*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;
  double band2X_3 = (intercept_2 + nSigmaBands*sigma_2 - (intercept_1 + nSigmaDiamond*sigma_1))/deltaM;

  band1->SetPoint(0, band1X_0, -0.5);
  band1->SetPointError(0, 0, 0);
  band1->SetPoint(1, band1X_1, band1Center->Eval(band1X_1));
  band1->SetPointError(1, 0, nSigmaBands*sigma_1);
  band1->SetPoint(2, band1X_2, band1Center->Eval(band1X_2));
  band1->SetPointError(2, 0, nSigmaBands*sigma_1);
  band1->SetPoint(3, band1X_3, band1Center->Eval(band1X_3) - nSigmaBands*sigma_1);
  band1->SetPointError(3, 0, 0);

  band1->SetFillColor(46);
  band1->SetFillStyle(3001);
  band1->Draw("3same");

  band2->SetPoint(0, band2X_0, 0.5);
  band2->SetPointError(0, 0, 0);
  band2->SetPoint(1, band2X_1, band2Center->Eval(band2X_1));
  band2->SetPointError(1, 0, nSigmaBands*sigma_2);
  band2->SetPoint(2, band2X_2, band2Center->Eval(band2X_2));
  band2->SetPointError(2, 0, nSigmaBands*sigma_2);
  band2->SetPoint(3, band2X_3, band2Center->Eval(band2X_3) + nSigmaBands*sigma_2);
  band2->SetPointError(3, 0, 0);
  band2->SetFillColor(46);
  band2->SetFillStyle(3001);
  band2->Draw("3same");

  diamond->SetPoint(0, diamondX_0, slope_1*diamondX_0 + nSigmaDiamond * sigma_1);
  diamond->SetPointError(0, 0, 0);
  diamond->SetPoint(1, diamondX_1, diamondCenter->Eval(diamondX_1));
  diamond->SetPointError(1, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(2, diamondX_2, diamondCenter->Eval(diamondX_2));
  diamond->SetPointError(2, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(3, diamondX_3, slope_1*diamondX_3 - nSigmaDiamond * sigma_1);
  diamond->SetPointError(3, 0, 0);
  diamond->SetFillColor(kGreen);
  diamond->SetFillStyle(3001);
  diamond->Draw("3same");


  cout << "Found good rotation angles: " << th_rot1 << " " << th_rot2
       << std::endl;
  cout << "I suggest applying the following cut:\n"
       << "Let Mn = 1 - (mydijet.M()/mppsmultmult->at(0))\n and Yn = "
          "yppsmultmult->at(0)-mydijet.Rapidity()\n"
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) - sigma_1 << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) + sigma_1 << "\nOR\n"
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) - sigma_2 << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) + sigma_2 << endl;
}