void MassRapiditySelectionWW(TFile *file) {
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
  TH2D *hmassrapiditymatchsigmcmmww =
      (TH2D *)file->Get("Signal/hmassrapiditymatchsigmcmmww");
  TCanvas* c1 = new TCanvas("c1", "c1", 1920, 1080);
  TCanvas* c2 = new TCanvas("c2", "c2", 1920, 1080);
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
  rotated_1->GetXaxis()->SetRangeUser(-2, 2);
  rotated_1->GetYaxis()->SetRangeUser(-2, 2);
  rotated_1->Draw("colz");
  c1->cd(5);
  TH1D *proj1 = rotated_1->ProjectionX();
  proj1->GetXaxis()->SetRangeUser(-2, 2);
  proj1->Rebin(2);
  proj1->Draw();
  TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)", -2, 2);
  f1->SetParameters(max1, 0, 0.05, 0, -0.5, 0.5);
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
  rotated_2->GetXaxis()->SetRangeUser(-2, 2);
  rotated_2->GetYaxis()->SetRangeUser(-2, 2);
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
  hmassrapiditymatchsigmcmmww->GetXaxis()->SetRangeUser(-2, 2);
  hmassrapiditymatchsigmcmmww->GetXaxis()->SetTitle("Mass match ratio");
  hmassrapiditymatchsigmcmmww->GetYaxis()->SetRangeUser(-2, 2);
  hmassrapiditymatchsigmcmmww->GetYaxis()->SetTitle("Delta rapidity");
  hmassrapiditymatchsigmcmmww->Draw("colz");

  TGraphErrors *band1 = new TGraphErrors(4);
  TGraphErrors *band2 = new TGraphErrors(4);
  TGraphErrors *diamond = new TGraphErrors(4);

  double nSigmaDiamond = 1.25;
  double nSigmaBands = 0.75;

  TF1 *band1Center =
      new TF1("band1Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double band1Sigma =
      TMath::Abs(f1->GetParameter(2)) /
      (TMath::Sin(th_rot1));
  double slope_1 = 1./TMath::Tan(th_rot1);
  double intercept_1 = - f1->GetParameter(1)/TMath::Sin(th_rot1);
  band1Center->SetParameters(th_rot1,
                             f1->GetParameter(1));
  TF1 *band2Center =
      new TF1("band2Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double band2Sigma =
      TMath::Abs(f2->GetParameter(2)) /
      (TMath::Sin(th_rot2));
  double slope_2 = 1./TMath::Tan(th_rot2);
  double intercept_2 = - f2->GetParameter(1)/TMath::Sin(th_rot2);
  band2Center->SetParameters(th_rot2,
                             f2->GetParameter(1));

  // Find parameters for the diamond (four interceptions in ascending order)
  // Interceptions are found as (q2-q1)/(m1-m2)
  double deltaM = slope_1 - slope_2;
  double diamondX_0 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_1 = (intercept_2 + nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_2 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_3 = (intercept_2 + nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaDiamond*band1Sigma))/deltaM;
  if (diamondX_1 > diamondX_2){
  	auto tmp = diamondX_2;
  	diamondX_2 = diamondX_1;
  	diamondX_1 = tmp;
  }

  double diamondWidth = (band1Sigma < band2Sigma) ? band1Sigma : band2Sigma;
  TF1* diamondCenter = (band1Sigma < band2Sigma) ? band1Center : band2Center;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_1;
  double band1X_0 = (-0.5 - (intercept_1 + nSigmaBands*band1Sigma))/deltaM;
  double band1X_1 = (-0.5 - (intercept_1 - nSigmaBands*band1Sigma))/deltaM;
  deltaM = slope_1 - slope_2;
  double band1X_2 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaBands*band1Sigma))/deltaM;
  double band1X_3 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaBands*band1Sigma))/deltaM;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_2;
  double band2X_0 = (0.5 - (intercept_2 - nSigmaBands*band2Sigma))/deltaM;
  double band2X_1 = (0.5 - (intercept_2 + nSigmaBands*band2Sigma))/deltaM;
  deltaM = slope_1 - slope_2;
  double band2X_2 = (intercept_2 - nSigmaBands*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double band2X_3 = (intercept_2 + nSigmaBands*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;

  band1->SetPoint(0, band1X_0, -0.5);
  band1->SetPointError(0, 0, 0);
  band1->SetPoint(1, band1X_1, band1Center->Eval(band1X_1));
  band1->SetPointError(1, 0, nSigmaBands*band1Sigma);
  band1->SetPoint(2, band1X_2, band1Center->Eval(band1X_2));
  band1->SetPointError(2, 0, nSigmaBands*band1Sigma);
  band1->SetPoint(3, band1X_3, band1Center->Eval(band1X_3) - nSigmaBands*band1Sigma);
  band1->SetPointError(3, 0, 0);

  band1->SetFillColor(46);
  band1->SetFillStyle(3001);
  band1->Draw("3same");

  band2->SetPoint(0, band2X_0, 0.5);
  band2->SetPointError(0, 0, 0);
  band2->SetPoint(1, band2X_1, band2Center->Eval(band2X_1));
  band2->SetPointError(1, 0, nSigmaBands*band2Sigma);
  band2->SetPoint(2, band2X_2, band2Center->Eval(band2X_2));
  band2->SetPointError(2, 0, nSigmaBands*band2Sigma);
  band2->SetPoint(3, band2X_3, band2Center->Eval(band2X_3) + nSigmaBands*band2Sigma);
  band2->SetPointError(3, 0, 0);
  band2->SetFillColor(46);
  band2->SetFillStyle(3001);
  band2->Draw("3same");

  diamond->SetPoint(0, diamondX_0, slope_1*diamondX_0 + nSigmaDiamond * band1Sigma);
  diamond->SetPointError(0, 0, 0);
  diamond->SetPoint(1, diamondX_1, diamondCenter->Eval(diamondX_1));
  diamond->SetPointError(1, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(2, diamondX_2, diamondCenter->Eval(diamondX_2));
  diamond->SetPointError(2, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(3, diamondX_3, slope_1*diamondX_3 - nSigmaDiamond * band1Sigma);
  diamond->SetPointError(3, 0, 0);
  diamond->SetFillColor(kGreen);
  diamond->SetFillStyle(3001);
  diamond->Draw("3same");

  c2->cd();
  hmassrapiditymatchsigmcmmww->Draw("colz");
  band1->Draw("3same");
  band2->Draw("3same");
  diamond->Draw("3same");

  cout << "Found good rotation angles: " << th_rot1 << " " << th_rot2
       << std::endl;
  cout << "I suggest applying the following cut:\n"
       << "Let Mn = 1 - (mydijet.M()/mppsmultmult->at(0))\n and Yn = "
          "yppsmultmult->at(0)-mydijet.Rapidity()\n"
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) - band1Sigma << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) + band1Sigma << "\nOR\n"
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) - band2Sigma << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) + band2Sigma << endl;
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
  hmassrapiditymatchsigmcmmzz->Draw("colz");

  TGraphErrors *band1 = new TGraphErrors(4);
  TGraphErrors *band2 = new TGraphErrors(4);
  TGraphErrors *diamond = new TGraphErrors(4);

  double nSigmaDiamond = 1.25;
  double nSigmaBands = 0.75;

  TF1 *band1Center =
      new TF1("band1Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double band1Sigma =
      TMath::Abs(f1->GetParameter(2)) /
      (TMath::Sin(th_rot1));
  double slope_1 = 1./TMath::Tan(th_rot1);
  double intercept_1 = - f1->GetParameter(1)/TMath::Sin(th_rot1);
  band1Center->SetParameters(th_rot1,
                             f1->GetParameter(1));
  TF1 *band2Center =
      new TF1("band2Center",
              "x/TMath::Tan([0]) - ([1])/(TMath::Sin([0]))", -1, 1);
  double band2Sigma =
      TMath::Abs(f2->GetParameter(2)) /
      (TMath::Sin(th_rot2));
  double slope_2 = 1./TMath::Tan(th_rot2);
  double intercept_2 = - f2->GetParameter(1)/TMath::Sin(th_rot2);
  band2Center->SetParameters(th_rot2,
                             f2->GetParameter(1));

  // Find parameters for the diamond (four interceptions in ascending order)
  // Interceptions are found as (q2-q1)/(m1-m2)
  double deltaM = slope_1 - slope_2;
  double diamondX_0 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_1 = (intercept_2 + nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_2 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaDiamond*band1Sigma))/deltaM;
  double diamondX_3 = (intercept_2 + nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaDiamond*band1Sigma))/deltaM;
  if (diamondX_1 > diamondX_2){
  	auto tmp = diamondX_2;
  	diamondX_2 = diamondX_1;
  	diamondX_1 = tmp;
  }

  double diamondWidth = (band1Sigma < band2Sigma) ? band1Sigma : band2Sigma;
  TF1* diamondCenter = (band1Sigma < band2Sigma) ? band1Center : band2Center;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_1;
  double band1X_0 = (-0.5 - (intercept_1 + nSigmaBands*band1Sigma))/deltaM;
  double band1X_1 = (-0.5 - (intercept_1 - nSigmaBands*band1Sigma))/deltaM;
  deltaM = slope_1 - slope_2;
  double band1X_2 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 + nSigmaBands*band1Sigma))/deltaM;
  double band1X_3 = (intercept_2 - nSigmaDiamond*band2Sigma - (intercept_1 - nSigmaBands*band1Sigma))/deltaM;

  // Find band1 interceptions (bottom range given by norm region)
  deltaM = slope_2;
  double band2X_0 = (0.5 - (intercept_2 - nSigmaBands*band2Sigma))/deltaM;
  double band2X_1 = (0.5 - (intercept_2 + nSigmaBands*band2Sigma))/deltaM;
  deltaM = slope_1 - slope_2;
  double band2X_2 = (intercept_2 - nSigmaBands*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;
  double band2X_3 = (intercept_2 + nSigmaBands*band2Sigma - (intercept_1 + nSigmaDiamond*band1Sigma))/deltaM;

  band1->SetPoint(0, band1X_0, -0.5);
  band1->SetPointError(0, 0, 0);
  band1->SetPoint(1, band1X_1, band1Center->Eval(band1X_1));
  band1->SetPointError(1, 0, nSigmaBands*band1Sigma);
  band1->SetPoint(2, band1X_2, band1Center->Eval(band1X_2));
  band1->SetPointError(2, 0, nSigmaBands*band1Sigma);
  band1->SetPoint(3, band1X_3, band1Center->Eval(band1X_3) - nSigmaBands*band1Sigma);
  band1->SetPointError(3, 0, 0);

  band1->SetFillColor(46);
  band1->SetFillStyle(3001);
  band1->Draw("3same");

  band2->SetPoint(0, band2X_0, 0.5);
  band2->SetPointError(0, 0, 0);
  band2->SetPoint(1, band2X_1, band2Center->Eval(band2X_1));
  band2->SetPointError(1, 0, nSigmaBands*band2Sigma);
  band2->SetPoint(2, band2X_2, band2Center->Eval(band2X_2));
  band2->SetPointError(2, 0, nSigmaBands*band2Sigma);
  band2->SetPoint(3, band2X_3, band2Center->Eval(band2X_3) + nSigmaBands*band2Sigma);
  band2->SetPointError(3, 0, 0);
  band2->SetFillColor(46);
  band2->SetFillStyle(3001);
  band2->Draw("3same");

  diamond->SetPoint(0, diamondX_0, slope_1*diamondX_0 + nSigmaDiamond * band1Sigma);
  diamond->SetPointError(0, 0, 0);
  diamond->SetPoint(1, diamondX_1, diamondCenter->Eval(diamondX_1));
  diamond->SetPointError(1, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(2, diamondX_2, diamondCenter->Eval(diamondX_2));
  diamond->SetPointError(2, 0, nSigmaDiamond*diamondWidth);
  diamond->SetPoint(3, diamondX_3, slope_1*diamondX_3 - nSigmaDiamond * band1Sigma);
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
       << band1Center->Eval(0) - band1Sigma << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot1) << " + "
       << band1Center->Eval(0) + band1Sigma << "\nOR\n"
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) - band2Sigma << " < Yn < "
       << "Mn/" << TMath::Tan(th_rot2) << " + "
       << band2Center->Eval(0) + band2Sigma << endl;
}