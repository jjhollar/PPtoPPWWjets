// Getting values from the FiducialCrossSections spreadsheet

#include "../analysismacros/CMS_lumi.h"

void fiducialCrossSectionsPlot() {
  vector<string> axisLabels_ww = {"WW_A0W5e-7",
                               "WW_A0W1e-6",
                               "WW_A0W2e-6",
                               "WW_A0W3_5e-6",
                               "WW_A0W5e-6",
                               "WW_ACW2e-6",
                               "WW_ACW5e-6",
                               "WW_ACW8e-6",
                               "WW_ACW1_4e-5",
                               "WW_ACW2e-5"};
  
  vector<string> axisLabels_zz = {
                               "ZZ_A0Z5e-6",
                               "ZZ_A0Z1e-5",
                               "ZZ_A0Z2e-5",
                               "ZZ_A0Z5e-5",
                               "ZZ_ACZ5e-6",
                               "ZZ_ACZ1e-5",
                               "ZZ_ACZ2e-5",
                               "ZZ_ACZ5e-5"};

  // Observed results
  double fxs_obs[] = {55.00223515,65.89629224,63.84255152,63.71658407,67.66722886,87.51797046,81.45688824,54.43125861,64.96817224,63.67435934,43.19968393,44.2832963,44.73748346,45.38404367,40.65836998,43.36063732,43.66551844,41.33586072,-10,-10};
  // Expected results
  double fxs[] = {44.87760160650001, 53.0246839263125, 52.6345118853125, 54.523536851289066, 53.100893679531254, 59.34207747725001, 58.73610758071876, 46.622174032124995, 53.332566677359374, 50.84585517722656, 63.0735455634375, 65.7443974159375, 63.406256584374994, 63.14876846142579, 58.923959135625, 61.192787105625, 58.57540426546875, 60.06848897539063, -10, -10};
  double fxs_plusSigma[] = {78.15003416423119, 83.03761705768989, 85.36384214297387, 89.73150657034873, 85.6969102305286, 103.33853304714064, 96.19605021915012, 76.72792725455847, 84.58269457518756, 82.05761211378896, 97.01441934663065, 101.38455290743043, 98.28438541238474, 96.87840490452531, 91.57136605883615, 93.63375554144741, 90.5627249308438, 92.63172749004258, -10, -10};
  double fxs_plus2Sigma[] = {136.01064059461015, 127.63759483008747, 136.12971499740843, 146.1871946359846, 137.2003276403734, 179.84815598588276, 156.0734249822117, 126.01854847258, 132.4726506102113, 131.94069170515706, 148.84888741218356, 155.27063796062524, 152.19304256238135, 143.7089484455716, 140.1663073065025, 141.30049015196022, 139.12923158827283, 141.16232639031816, -10, -10};
  double fxs_minusSigma[] = {27.88141520706565, 35.244067868502384, 34.4578719776527, 35.46492506251145, 34.53956444963163, 37.02179229331732, 37.90744638418702, 30.207378444703547, 35.315247551432606, 33.41414323078604, 42.83661559269775, 44.68564511864502, 42.937769580300326, 43.723121913233285, 39.607517209511606, 41.83100681048584, 39.51980705264231, 40.76547417708547, -10, -10};
  double fxs_minus2Sigma[] = {19.283344440292975, 25.2695759336333, 24.26122032213623, 25.131942767391052, 24.476193180408938, 25.73035390615137, 26.614798747513188, 21.307790475619626, 25.20797096859564, 23.63537799253891, 31.29039174436157, 32.87219870796875, 31.45544760240478, 32.06773398431778, 28.771464421691892, 30.5963935528125, 28.830081786910398, 29.564959417575075, -10, -10};

  double ey_fxs_l_1s[19];
  double ey_fxs_h_1s[19];
  double ex_fxs_l[19];
  double ex_fxs_h[19];
  double ey_fxs_l_2s[19];
  double ey_fxs_h_2s[19];
  for (int i = 0; i < 19; i++) {
    ey_fxs_l_1s[i] = fxs[i] - fxs_minusSigma[i];
    ey_fxs_h_1s[i] = fxs_plusSigma[i] - fxs[i];
    ex_fxs_l[i] = 0.5;
    ex_fxs_h[i] = 0.5;
    ey_fxs_l_2s[i] = fxs[i] - fxs_minus2Sigma[i];
    ey_fxs_h_2s[i] = fxs_plus2Sigma[i] - fxs[i];
  }

  const int ww_points = axisLabels_ww.size();
  const int zz_points = axisLabels_zz.size();
  
  // WW and ZZ
  double fxs_obs_m[] = {TMath::Mean(ww_points, fxs_obs),TMath::Mean(zz_points, fxs_obs+ww_points)};
  double fxs_m[] = {TMath::Mean(ww_points, fxs),TMath::Mean(zz_points, fxs+ww_points)};
  double e_fxs_m_l[] = {TMath::Mean(ww_points, ey_fxs_l_1s),TMath::Mean(zz_points, ey_fxs_l_1s+ww_points)};
  double e_fxs_m_h[] = {TMath::Mean(ww_points, ey_fxs_h_1s),TMath::Mean(zz_points, ey_fxs_h_1s+ww_points)};

  // WW plot
  double x_ww[ww_points];
  double x_ww_aux[ww_points+2];
  double y_ww_aux[ww_points+2];
  
  for(int i=0;i<ww_points+2;i++){
    x_ww_aux[i] = i-2;
    y_ww_aux[i] = 0;
    if (i < ww_points)
      x_ww[i] = i;
  }
  TCanvas* c_ww = new TCanvas();
  TGraph* g_aux_ww = new TGraph(ww_points+2,x_ww_aux,y_ww_aux);
  TGraphAsymmErrors *g_fxs_obs_1s_ww_line = new TGraphAsymmErrors(ww_points, x_ww, fxs_obs, ex_fxs_l, ex_fxs_h, nullptr, nullptr);

  TGraphAsymmErrors *g_fxs_1s_ww = new TGraphAsymmErrors(ww_points, x_ww, fxs, ex_fxs_l, ex_fxs_h, ey_fxs_l_1s, ey_fxs_h_1s);
  TGraphAsymmErrors *g_fxs_1s_ww_line = new TGraphAsymmErrors(ww_points, x_ww, fxs, ex_fxs_l, ex_fxs_h, nullptr, nullptr);
  TGraphAsymmErrors *g_fxs_2s_ww = new TGraphAsymmErrors(ww_points, x_ww, fxs, ex_fxs_l, ex_fxs_h, ey_fxs_l_2s, ey_fxs_h_2s);
  g_fxs_1s_ww->SetName("g_fxs_1s_ww");
  g_fxs_2s_ww->SetName("g_fxs_2s_ww");
  for (int i = 0; i < ww_points+2; i++) {
    if (i-2 >= 0)
      g_aux_ww->GetXaxis()->SetBinLabel(g_aux_ww->GetXaxis()->FindBin(i-2), axisLabels_ww[i-2].data());
    else
      g_aux_ww->GetXaxis()->SetBinLabel(g_aux_ww->GetXaxis()->FindBin(i-2), nullptr);
  }

  g_aux_ww->GetXaxis()->SetLabelSize(0.03);
  g_aux_ww->GetXaxis()->SetTitleOffset(2.8);
  g_aux_ww->GetXaxis()->SetRangeUser(-1,12);
  g_aux_ww->GetXaxis()->SetTickSize(0);
  g_aux_ww->GetYaxis()->SetRangeUser(0, 200);
  g_aux_ww->SetTitle(";Coupling point;95\% limit on fiducial cross section [fb]");
  g_aux_ww->GetXaxis()->SetNdivisions(0,kFALSE);
  g_aux_ww->Draw("ap");
  gPad->SetBottomMargin(0.2);
  g_fxs_2s_ww->SetFillColor(kYellow);
  g_fxs_2s_ww->Draw("2same");
  // g_fxs_1s_ww->SetMarkerStyle(20);
  g_fxs_1s_ww->SetFillColor(kGreen);
  g_fxs_1s_ww->Draw("2same");
  g_fxs_1s_ww_line->SetLineWidth(2);
  g_fxs_1s_ww_line->SetLineColor(kRed);
  g_fxs_1s_ww_line->SetMarkerColor(kRed);
  // g_fxs_1s_ww_line->SetLineStyle(2);
  g_fxs_1s_ww_line->Draw("pzsame");
  g_fxs_obs_1s_ww_line->SetLineWidth(2);
  g_fxs_obs_1s_ww_line->SetMarkerStyle(8);
  g_fxs_obs_1s_ww_line->Draw("psame");

  // TCanvas* c_ww = new TCanvas();
  // TGraph* g_aux_ww = new TGraph(ww_points+2,y_ww_aux,x_ww_aux);
  // TGraphAsymmErrors *g_fxs_1s_ww = new TGraphAsymmErrors(ww_points, fxs, x_ww, ey_fxs_l_1s, ey_fxs_h_1s, ex_fxs_l, ex_fxs_h);
  // TGraphAsymmErrors *g_fxs_1s_ww_line = new TGraphAsymmErrors(ww_points, fxs, x_ww, nullptr, nullptr, ex_fxs_l, ex_fxs_h);
  // TGraphAsymmErrors *g_fxs_2s_ww = new TGraphAsymmErrors(ww_points, fxs, x_ww, ey_fxs_l_2s, ey_fxs_h_2s, ex_fxs_l, ex_fxs_h);
  // g_fxs_1s_ww->SetName("g_fxs_1s_ww");
  // g_fxs_2s_ww->SetName("g_fxs_2s_ww");
  // // for (int i = 0; i < ww_points+2; i++) {
  // //   std::cout << "Found bin " << g_fxs_2s_ww->GetYaxis()->FindBin(i-2) << std::endl;
  // //   if (i-2 >= 0)
  // //     g_fxs_2s_ww->GetYaxis()->SetBinLabel(g_fxs_2s_ww->GetYaxis()->FindBin(i-2), axisLabels_ww[i-2].data());
  // //   else
  // //     g_fxs_2s_ww->GetYaxis()->SetBinLabel(g_fxs_2s_ww->GetYaxis()->FindBin(i-2), nullptr);
  // // }

  // g_fxs_2s_ww->GetYaxis()->SetLabelSize(0.03);
  // g_fxs_2s_ww->GetYaxis()->SetTitleOffset(2.8);
  // g_fxs_2s_ww->GetYaxis()->SetRangeUser(-1,12);
  // g_fxs_2s_ww->GetYaxis()->SetTickSize(0);
  // g_fxs_2s_ww->GetXaxis()->SetRangeUser(0, 200);
  // g_fxs_2s_ww->SetTitle(";Coupling point;95\% limit on fiducial cross section [fb]");
  // g_fxs_2s_ww->GetYaxis()->SetNdivisions(0,kFALSE);
  // // g_aux_ww->Draw("ap");
  // gPad->SetBottomMargin(0.2);
  // g_fxs_2s_ww->SetFillColor(kYellow);
  // g_fxs_2s_ww->Draw("a2same");
  // // g_fxs_1s_ww->SetMarkerStyle(20);
  // g_fxs_1s_ww->SetFillColor(kGreen);
  // g_fxs_1s_ww->Draw("2same");
  // g_fxs_1s_ww_line->SetLineWidth(2);
  // g_fxs_1s_ww_line->SetLineStyle(2);
  // g_fxs_1s_ww_line->Draw("pzsame");

  CMS_TOTEM_lumi((TPad*)c_ww->GetPad(0),0,0,"L = 100.0 fb^{-1}");
  c_ww->SaveAs("FiducialCrossSections_ww.pdf");

  // ZZ plot
  double x_zz[zz_points];
  double x_zz_aux[zz_points+2];
  double y_zz_aux[zz_points+2];
  
  for(int i=0;i<zz_points+2;i++){
    x_zz_aux[i] = i-2;
    y_zz_aux[i] = 0;
    if (i < zz_points)
      x_zz[i] = i;
  }
  TCanvas* c_zz = new TCanvas();
  TGraph* g_aux_zz = new TGraph(zz_points+2,x_zz_aux,y_zz_aux);
  TGraphAsymmErrors *g_fxs_obs_1s_zz_line = new TGraphAsymmErrors(zz_points, x_zz, fxs_obs+ww_points, ex_fxs_l+ww_points, ex_fxs_h+ww_points, nullptr, nullptr);
  
  TGraphAsymmErrors *g_fxs_1s_zz = new TGraphAsymmErrors(zz_points, x_zz, fxs+ww_points, ex_fxs_l+ww_points, ex_fxs_h+ww_points, ey_fxs_l_1s+ww_points, ey_fxs_h_1s+ww_points);
  TGraphAsymmErrors *g_fxs_1s_zz_line = new TGraphAsymmErrors(zz_points, x_zz, fxs+ww_points, ex_fxs_l+ww_points, ex_fxs_h+ww_points, nullptr, nullptr);
  TGraphAsymmErrors *g_fxs_2s_zz = new TGraphAsymmErrors(zz_points, x_zz, fxs+ww_points, ex_fxs_l+ww_points, ex_fxs_h+ww_points, ey_fxs_l_2s+ww_points, ey_fxs_h_2s+ww_points);
  g_fxs_1s_zz->SetName("g_fxs_1s_zz");
  g_fxs_2s_zz->SetName("g_fxs_2s_zz");
  for (int i = 0; i < zz_points+2; i++) {
    if (i-2 >= 0)
      g_aux_zz->GetXaxis()->SetBinLabel(g_aux_zz->GetXaxis()->FindBin(i-2), axisLabels_zz[i-2].data());
    else
      g_aux_zz->GetXaxis()->SetBinLabel(g_aux_zz->GetXaxis()->FindBin(i-2), nullptr);
  }

  g_aux_zz->GetXaxis()->SetLabelSize(0.03);
  g_aux_zz->GetXaxis()->SetTitleOffset(2.8);
  g_aux_zz->GetXaxis()->SetRangeUser(-1,12);
  g_aux_zz->GetXaxis()->SetTickSize(0);
  g_aux_zz->GetYaxis()->SetRangeUser(0, 200);
  g_aux_zz->SetTitle(";Coupling point;95\% limit on fiducial cross section [fb]");
  g_aux_zz->GetXaxis()->SetNdivisions(0,kFALSE);
  g_aux_zz->Draw("ap");
  gPad->SetBottomMargin(0.2);
  g_fxs_2s_zz->SetFillColor(kYellow);
  g_fxs_2s_zz->Draw("2same");
  // g_fxs_1s_zz->SetMarkerStyle(20);
  g_fxs_1s_zz->SetFillColor(kGreen);
  g_fxs_1s_zz->Draw("2same");
  g_fxs_1s_zz_line->SetLineWidth(2);
  g_fxs_1s_zz_line->SetLineColor(kRed);
  g_fxs_1s_zz_line->SetMarkerColor(kRed);
  // g_fxs_1s_zz_line->SetLineStyle(2);v
  g_fxs_1s_zz_line->Draw("pzsame");
  g_fxs_obs_1s_zz_line->SetLineWidth(2);
  g_fxs_obs_1s_zz_line->SetMarkerStyle(8);
  g_fxs_obs_1s_zz_line->Draw("psame");

  CMS_TOTEM_lumi((TPad*)c_zz->GetPad(0),0,0,"L = 100.0 fb^{-1}");
  c_zz->SaveAs("FiducialCrossSections_zz.pdf");

  cout << "Mean value expected for WW: " << TMath::Mean(ww_points, fxs) << " 1sigma: (+" << TMath::Mean(ww_points, fxs_plusSigma) - TMath::Mean(ww_points, fxs) << "/-"
       << TMath::Mean(ww_points, fxs) - TMath::Mean(ww_points, fxs_minusSigma) << ") 2sigma: (+" << TMath::Mean(ww_points, fxs_plus2Sigma) - TMath::Mean(ww_points, fxs) << "/-" << TMath::Mean(ww_points, fxs) - TMath::Mean(ww_points, fxs_minus2Sigma) << ") fb. Observed: " << TMath::Mean(ww_points, fxs_obs) << " fb." << endl;
  cout << "Mean value expected for ZZ: " << TMath::Mean(zz_points, fxs+ww_points) << " 1sigma: (+" << TMath::Mean(zz_points, fxs_plusSigma+ww_points) - TMath::Mean(zz_points, fxs+ww_points) << "/-"
       << TMath::Mean(zz_points, fxs+ww_points) - TMath::Mean(zz_points, fxs_minusSigma+ww_points) << ") 2sigma: (+" << TMath::Mean(zz_points, fxs_plus2Sigma+ww_points) - TMath::Mean(zz_points, fxs+ww_points) << "/-" << TMath::Mean(zz_points, fxs+ww_points) - TMath::Mean(zz_points, fxs_minus2Sigma+ww_points) << ") fb. Observed: " << TMath::Mean(zz_points, fxs_obs+ww_points) << " fb." << endl;
}