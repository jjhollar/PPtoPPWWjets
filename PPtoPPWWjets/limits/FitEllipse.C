//
// The "fitEllipseTGraphDLSF" macro uses the "Direct Least Squares Fitting"
// algorithm for fitting an ellipse to a set of data points from a TGraph
//
// To try this macro, in a ROOT prompt, do:
// .L fitEllipseTGraphDLSF.cxx // or ".L fitEllipseTGraphDLSF.cxx++"
// fitEllipseTGraphDLSF(TestGraphDLSF());
// for (Int_t i=0; i<10; i++) { fitEllipseTGraphDLSF(); gSystem->Sleep(333); }
//
// Last update: Thu Jul 31 18:00:00 UTC 2014
//
// Changes:
// 2014.07.31 - (initial version)
//

#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TCanvas.h"
#include "TEllipse.h"

#include <cmath>
#include <iostream>

#include "../analysismacros/CMS_lumi.h"

//
// "NUMERICALLY STABLE DIRECT LEAST SQUARES FITTING OF ELLIPSES"
// Radim Halir, Jan Flusser
// http://autotrace.sourceforge.net/WSCG98.pdf
//
// http://en.wikipedia.org/wiki/Ellipse
//
// An "algebraic distance" of a point "(x, y)" to a given conic:
//   F(x, y) = A * (x - X0)^2 + B * (x - X0) * (y - Y0) + C * (y - Y0)^2
//           + D * (x - X0) + E * (y - Y0) + F
//
// Ellipse-specific constraints:
//   F(x, y) = 0
//   B^2 - 4 * A * C < 0
//
// input parameter is a a pointer to a "TGraph" with at least 6 points
//
// returns a "TVectorD" ("empty" in case any problems encountered):
// ellipse[0] = "X0"
// ellipse[1] = "Y0"
// ellipse[2] = "A"
// ellipse[3] = "B"
// ellipse[4] = "C"
// ellipse[5] = "D"
// ellipse[6] = "E"
// ellipse[7] = "F"
//
TVectorD fit_ellipse(TGraph *g)
{
  TVectorD ellipse;

  if (!g) return ellipse; // just a precaution
  if (g->GetN() < 6) return ellipse; // just a precaution

  Int_t i;
  Double_t tmp;

  Int_t N = g->GetN();
  Double_t xmin, xmax, ymin, ymax, X0, Y0;
  g->ComputeRange(xmin, ymin, xmax, ymax);
#if 1 /* 0 or 1 */
  X0 = (xmax + xmin) / 2.0;
  Y0 = (ymax + ymin) / 2.0;
#else /* 0 or 1 */
  X0 = Y0 = 0.0;
#endif /* 0 or 1 */

  TMatrixD D1(N, 3); // quadratic part of the design matrix
  TMatrixD D2(N, 3); // linear part of the design matrix

  for (i = 0; i < N; i++) {
    Double_t x = (g->GetX())[i] - X0;
    Double_t y = (g->GetY())[i] - Y0;
    D1[i][0] = x * x;
    D1[i][1] = x * y;
    D1[i][2] = y * y;
    D2[i][0] = x;
    D2[i][1] = y;
    D2[i][2] = 1.0;
  }

  // quadratic part of the scatter matrix
  TMatrixD S1(TMatrixD::kAtA, D1);
  // combined part of the scatter matrix
  TMatrixD S2(D1, TMatrixD::kTransposeMult, D2);
  // linear part of the scatter matrix
  TMatrixD S3(TMatrixD::kAtA, D2);
  S3.Invert(&tmp); S3 *= -1.0;
  if (tmp == 0.0) {
    std::cout << "fit_ellipse : linear part of the scatter matrix is singular!" << std::endl;
    return ellipse;
  }
  // for getting a2 from a1
  TMatrixD T(S3, TMatrixD::kMultTranspose, S2);
  // reduced scatter matrix
  TMatrixD M(S2, TMatrixD::kMult, T); M += S1;
  // premultiply by inv(C1)
  for (i = 0; i < 3; i++) {
    tmp = M[0][i] / 2.0;
    M[0][i] = M[2][i] / 2.0;
    M[2][i] = tmp;
    M[1][i] *= -1.0;
  }
  // solve eigensystem
  TMatrixDEigen eig(M); // note: eigenvectors are not normalized
  const TMatrixD &evec = eig.GetEigenVectors();
  // const TVectorD &eval = eig.GetEigenValuesRe();
  if ((eig.GetEigenValuesIm()).Norm2Sqr() != 0.0) {
    std::cout << "fit_ellipse : eigenvalues have nonzero imaginary parts!" << std::endl;
    return ellipse;
  }
  // evaluate a’Ca (in order to find the eigenvector for min. pos. eigenvalue)
  for (i = 0; i < 3; i++) {
    tmp = 4.0 * evec[0][i] * evec[2][i] - evec[1][i] * evec[1][i];
    if (tmp > 0.0) break;
  }
  if (i > 2) {
    std::cout << "fit_ellipse : no min. pos. eigenvalue found!" << std::endl;
    // i = 2;
    return ellipse;
  }
  // eigenvector for min. pos. eigenvalue
  TVectorD a1(TMatrixDColumn_const(evec, i));
  tmp = a1.Norm2Sqr();
  if (tmp > 0.0) {
    a1 *= 1.0 / std::sqrt(tmp); // normalize this eigenvector
  } else {
    std::cout << "fit_ellipse : eigenvector for min. pos. eigenvalue is NULL!" << std::endl;
    return ellipse;
  }
  TVectorD a2(T * a1);

  // ellipse coefficients
  ellipse.ResizeTo(8);
  ellipse[0] = X0; // "X0"
  ellipse[1] = Y0; // "Y0"
  ellipse[2] = a1[0]; // "A"
  ellipse[3] = a1[1]; // "B"
  ellipse[4] = a1[2]; // "C"
  ellipse[5] = a2[0]; // "D"
  ellipse[6] = a2[1]; // "E"
  ellipse[7] = a2[2]; // "F"

  return ellipse;
}

//
// http://mathworld.wolfram.com/Ellipse.html
// http://mathworld.wolfram.com/QuadraticCurve.html
// http://mathworld.wolfram.com/ConicSection.html
//
// "Using the Ellipse to Fit and Enclose Data Points"
// Charles F. Van Loan
// http://www.cs.cornell.edu/cv/OtherPdf/Ellipse.pdf
//
// input parameter is a reference to a "TVectorD" which describes
// an ellipse according to the equation:
//   0 = A * (x - X0)^2 + B * (x - X0) * (y - Y0) + C * (y - Y0)^2
//     + D * (x - X0) + E * (y - Y0) + F
// conic[0] = "X0"
// conic[1] = "Y0"
// conic[2] = "A"
// conic[3] = "B"
// conic[4] = "C"
// conic[5] = "D"
// conic[6] = "E"
// conic[7] = "F"
//
// returns a "TVectorD" ("empty" in case any problems encountered):
// ellipse[0] = ellipse's "x" center ("x0")
// ellipse[1] = ellipse's "y" center ("y0")
// ellipse[2] = ellipse's "semimajor" axis along "x" ("a" > 0)
// ellipse[3] = ellipse's "semiminor" axis along "y" ("b" > 0)
// ellipse[4] = ellipse's axes rotation angle ("theta" = -45 ... 135 degrees)
//
TVectorD ConicToParametric(const TVectorD &conic)
{
  TVectorD ellipse;

  if (conic.GetNrows() != 8) {
    std::cout << "ConicToParametric : improper input vector length!" << std::endl;
    return ellipse;
  }

  Double_t a, b, theta;
  Double_t x0 = conic[0]; // = X0
  Double_t y0 = conic[1]; // = Y0

  // http://mathworld.wolfram.com/Ellipse.html
  Double_t A = conic[2];
  Double_t B = conic[3] / 2.0;
  Double_t C = conic[4];
  Double_t D = conic[5] / 2.0;
  Double_t F = conic[6] / 2.0;
  Double_t G = conic[7];

  Double_t J = B * B - A * C;
  Double_t Delta = A * F * F + C * D * D + J * G - 2.0 * B * D * F;
  Double_t I = - (A + C);

  // http://mathworld.wolfram.com/QuadraticCurve.html
  if (!( (Delta != 0.0) && (J < 0.0) && (I != 0.0) && (Delta / I < 0.0) )) {
    std::cout << "ConicToParametric : ellipse (real) specific constraints not met!" << std::endl;
    return ellipse;
  }

  x0 += (C * D - B * F) / J;
  y0 += (A * F - B * D) / J;

  Double_t tmp = std::sqrt((A - C) * (A - C) + 4.0 * B * B);
  a = std::sqrt(2.0 * Delta / J / (I + tmp));
  b = std::sqrt(2.0 * Delta / J / (I - tmp));

  theta = 0.0;
  if (B != 0.0) {
    tmp = (A - C) / 2.0 / B;
    theta = -45.0 * (std::atan(tmp) / TMath::PiOver2());
    if (tmp < 0.0) { theta -= 45.0; } else { theta += 45.0; }
    if (A > C) theta += 90.0;
  } else if (A > C) theta = 90.0;

  // try to keep "a" > "b"
  if (a < b) { tmp = a; a = b; b = tmp; theta -= 90.0; }
  // try to keep "theta" = -45 ... 135 degrees
  if (theta < -45.0) theta += 180.0;
  if (theta > 135.0) theta -= 180.0;

  // ellipse coefficients
  ellipse.ResizeTo(5);
  ellipse[0] = x0; // ellipse's "x" center
  ellipse[1] = y0; // ellipse's "y" center
  ellipse[2] = a; // ellipse's "semimajor" axis along "x"
  ellipse[3] = b; // ellipse's "semiminor" axis along "y"
  ellipse[4] = theta; // ellipse's axes rotation angle (in degrees)

  return ellipse;
}

//
// creates a test TGraph with an ellipse
//
TGraph *TestGraphDLSF(Bool_t randomize = kFALSE) {
  Int_t i;

  // define the test ellipse
  Double_t x0 = 4; // ellipse's "x" center
  Double_t y0 = 3; // ellipse's "y" center
  Double_t a = 2; // ellipse's "semimajor" axis along "x" (> 0)
  Double_t b = 1; // ellipse's "semiminor" axis along "y" (> 0)
  Double_t theta = 100; // ellipse's axes rotation angle (-45 ... 135 degrees)

  // gRandom->SetSeed(0);
  if (randomize) {
    x0 = 10.0 - 20.0 * gRandom->Rndm();
    y0 = 10.0 - 20.0 * gRandom->Rndm();
    a = 0.5 + 4.5 * gRandom->Rndm();
    b = 0.5 + 4.5 * gRandom->Rndm();
    theta = 180.0 - 360.0 * gRandom->Rndm();
  }

  const Int_t n = 8; // number of points
  Double_t x[n], y[n];
  Double_t dt = TMath::TwoPi() / Double_t(n);
  Double_t tmp;
  theta *= TMath::PiOver2() / 90.0; // degrees -> radians
  for (i = 0; i < n; i++) {
    x[i] = a * (std::cos(dt * Double_t(i)) + 0.1 * gRandom->Rndm() - 0.05);
    y[i] = b * (std::sin(dt * Double_t(i)) + 0.1 * gRandom->Rndm() - 0.05);
    // rotate the axes
    tmp = x[i];
    x[i] = x[i] * std::cos(theta) - y[i] * std::sin(theta);
    y[i] = y[i] * std::cos(theta) + tmp * std::sin(theta);
    // shift the center
    x[i] += x0;
    y[i] += y0;
  }

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "test ellipse");
  g->SetMarkerStyle(20);

  return g;
}

TGraph *GraphWW() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -3.699e-6;    y[0] = 0; // limit on a0W
  x[1] =  3.699e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.383e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.383e-5; // limit on aCW
  x[4] =  1.96942e-6;   y[4] = 0.7e-5;
  x[5] =  -5.46232e-06;  y[5] = 0.7e-5;
  x[6] =  5.557e-6;   y[6] = -0.7e-5;
  x[7] =  -1.970e-6;  y[7] = -0.7e-5;
  x[8] =  -1.719e-6;   y[8] = 2.0e-5;
  x[9] =  -8.339e-6;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_plusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -4.736e-6;    y[0] = 0; // limit on a0W
  x[1] =  4.736e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.772e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.772e-5; // limit on aCW
  x[4] =  2.97514e-6;   y[4] = 0.7e-5;
  x[5] =  -6.46804e-6;  y[5] = 0.7e-5;
  x[6] =  6.5555e-6;   y[6] = -0.7e-5;
  x[7] =  -2.96835e-6;  y[7] = -0.7e-5;
  x[8] =  -6.3158e-7;   y[8] = 2.0e-5;
  x[9] =  -9.42674e-6;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_minusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -2.961e-6;    y[0] = 0; // limit on a0W
  x[1] =  2.961e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.110e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.110e-5; // limit on aCW
  x[4] =  1.16134e-6;   y[4] = 0.7e-5;
  x[5] =  -4.65424e-6;  y[5] = 0.7e-5;
  x[6] =  4.75919e-6;   y[6] = -0.7e-5;
  x[7] =  -1.17202e-6;  y[7] = -0.7e-5;
  x[8] =  -2.64861e-6;   y[8] = 2.0e-5;
  x[9] =  -7.40971e-6;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}



TGraph *GraphWW_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -3.699e-6;    y[0] = 0; // limit on a0W
  x[1] =  3.699e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.383e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.383e-5; // limit on aCW
  // x[4] =  2.065e-6;   y[4] = 0.7e-5;
  // x[5] =  -5.558e-6;  y[5] = 0.7e-5;
  // x[6] =  5.652e-6;   y[6] = -0.7e-5;
  // x[7] =  -2.064e-6;  y[7] = -0.7e-5;
  // x[8] =  -4.170e-6;   y[8] = 2.8e-5;
  // x[9] =  -9.825e-6;  y[9] = 2.8e-5;

  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "WW ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5,3e-5);
  g_aux->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g_aux->SetMarkerStyle(20);

  return g_aux;
}


//
// creates a test TGraph with an ellipse
//
TGraph *GraphZZ() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -9.742e-6;    y[0] = 0; // limit on a0W
  x[1] =  9.742e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.652e-5; // limit on aCW
  x[3] =  0;          y[3] = 3.652e-5; // limit on aCW
  x[4] =  4.048e-6;   y[4] = 2.2e-5;
  x[5] =  -1.504e-5;  y[5] = 2.2e-5;
  x[6] =  1.503e-5;   y[6] = -2.2e-5;
  x[7] =  -4.031e-6;  y[7] = -2.2e-5;
  x[8] =  -3.791e-6;   y[8] = 5e-5;
  x[9] =  -2.127e-5;  y[9] = 5e-5;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5,4e-5);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4,2e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_plusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -1.205e-5;    y[0] = 0; // limit on a0W
  x[1] =  1.205e-5;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -4.508e-5; // limit on aCW
  x[3] =  0;          y[3] = 4.508e-5; // limit on aCW
  x[4] =  6.3806e-6;   y[4] = 2.2e-5;
  x[5] =  -1.73776e-5;  y[5] = 2.2e-5;
  x[6] =  1.73664e-5;   y[6] = -2.2e-5;
  x[7] =  -6.36685e-6;  y[7] = -2.2e-5;
  x[8] =  -1.28928e-6;   y[8] = 5e-5;
  x[9] =  -2.37714e-5;  y[9] = 5e-5;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5,4e-5);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4,2e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_minusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -8.011e-6;    y[0] = 0; // limit on a0W
  x[1] =  8.011e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.999e-5; // limit on aCW
  x[3] =  0;          y[3] = 2.999e-5; // limit on aCW
  x[4] =  2.27569e-6;   y[4] = 2.2e-5;
  x[5] =  -1.32727e-5;  y[5] = 2.2e-5;
  x[6] =  1.32541e-5;   y[6] = -2.2e-5;
  x[7] =  -2.25459e-6;  y[7] = -2.2e-5;
  x[8] =  -5.77339e-6;   y[8] = 5e-5;
  x[9] =  -1.92873e-5;  y[9] = 5e-5;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5,4e-5);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4,2e-4);
  g->SetMarkerStyle(6);

  return g;
}


TGraph *GraphZZ_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -9.742e-6;    y[0] = 0; // limit on a0W
  x[1] =  9.742e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.652e-5; // limit on aCW
  x[3] =  0;          y[3] = 3.652e-5; // limit on aCW
  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "ZZ ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5,3e-5);
  g_aux->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetYaxis()->SetTitleOffset(1.2);
  g_aux->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g_aux->SetMarkerStyle(20);

  return g_aux;
}

TEllipse* fitEllipseTGraphDLSF(TGraph *g = ((TGraph *)0))
{
  if (!g) g = TestGraphDLSF(kTRUE); // create a "random" ellipse

  // fit the TGraph
  TVectorD conic = fit_ellipse(g);
  TVectorD ellipse = ConicToParametric(conic);

#if 1 /* 0 or 1 */
  if ( ellipse.GetNrows() == 5 ) {
    std::cout << std::endl;
    std::cout << "x0 = " << ellipse[0] << std::endl;
    std::cout << "y0 = " << ellipse[1] << std::endl;
    std::cout << "a = " << ellipse[2] << std::endl;
    std::cout << "b = " << ellipse[3] << std::endl;
    std::cout << "theta = " << ellipse[4] << std::endl;
    std::cout << std::endl;
  }
#endif /* 0 or 1 */

#if 1 /* 0 or 1 */
  // draw everything
  TCanvas *c = ((TCanvas *)(gROOT->GetListOfCanvases()->FindObject("c")));
  TEllipse *e;
  if (c) { c->Clear(); } else { c = new TCanvas("c", "c"); }
  c->SetGrid(1, 1);
  // g->Draw("AP");
  if ( ellipse.GetNrows() == 5 ) {
    e = new TEllipse(ellipse[0], ellipse[1], // "x0", "y0"
                               ellipse[2], ellipse[3], // "a", "b"
                               0, 360,
                               ellipse[4]); // "theta" (in degrees)
    e->SetFillStyle(0); // hollow
    e->SetLineColor(kRed);
    e->SetLineWidth(2);
    // e->Draw();
  }
  c->Modified(); c->Update(); // make sure it's really drawn
#endif /* 0 or 1 */

  return e ;
}

void fixDivisionsAndGrid(TGraph*g,int nXdivisions, int nYdivisions,double yrangemin, double yrangemax){
  const int nLines_x = nXdivisions%100 - 1;
  const int nLines_y = nYdivisions%100 - 1;
  g->GetXaxis()->SetNdivisions(nXdivisions,kFALSE);
  g->GetYaxis()->SetNdivisions(nYdivisions,kFALSE);
  TLine *l_x,*l_y;
  for (int i=1;i<=nLines_x;i++){
    double line_x_coord = g->GetXaxis()->GetXmin() + i * (g->GetXaxis()->GetXmax()-g->GetXaxis()->GetXmin())/(nLines_x+1);
    l_x = new TLine(line_x_coord,yrangemin,line_x_coord,yrangemax);
    l_x->SetLineStyle(3);
    l_x->Draw("same");
  }

  for (int i=1;i<=nLines_y;i++){
    double line_y_coord = yrangemin + i * (yrangemax-yrangemin)/(nLines_y+1);
    l_y = new TLine(g->GetXaxis()->GetXmin(),line_y_coord,g->GetXaxis()->GetXmax(),line_y_coord);
    l_y->SetLineStyle(3);
    l_y->Draw("same");
  }

} 

TGraph *GraphWW_clip() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -5.456e-6;    y[0] = 0; // limit on a0W
  x[1] =  5.456e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.906e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.906e-5; // limit on aCW
  x[4] =  3.504e-6;   y[4] = 0.7e-5;
  x[5] =  -6.997e-06;  y[5] = 0.7e-5;
  x[6] =  7.082e-6;   y[6] = -0.7e-5;
  x[7] =  -3.495e-6;  y[7] = -0.7e-5;
  x[8] =  -7.409e-8;   y[8] = 2.0e-5;
  x[9] =  -9.984e-6;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_plusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -7.077e-6;    y[0] = 0; // limit on a0W
  x[1] =  7.077e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.395e-5; // limit on aCW
  x[3] =  0;          y[3] = 2.395e-5; // limit on aCW
  x[4] =  4.997e-6;   y[4] = 0.7e-5;
  x[5] =  -8.490e-6;  y[5] = 0.7e-5;
  x[6] =  8.571e-6;   y[6] = -0.7e-5;
  x[7] =  -4.984e-6;  y[7] = -0.7e-5;
  x[8] =  1.470e-6;   y[8] = 2.0e-5;
  x[9] =  -1.153e-5;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_minusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -4.290e-6;    y[0] = 0; // limit on a0W
  x[1] =  4.290e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.545e-5; // limit on aCW
  x[3] =  0;          y[3] = 1.545e-5; // limit on aCW
  x[4] =  2.451e-6;   y[4] = 0.7e-5;
  x[5] =  -5.944e-6;  y[5] = 0.7e-5;
  x[6] =  6.035e-6;   y[6] = -0.7e-5;
  x[7] =  -2.448e-6;  y[7] = -0.7e-5;
  x[8] =  -1.192e-6;   y[8] = 2.0e-5;
  x[9] =  -8.866e-6;  y[9] = 2.0e-5;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5,3e-5);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g->SetMarkerStyle(6);

  return g;
}



TGraph *GraphWW_clip_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -5.1e-6;    y[0] = 0; // limit on a0W
  x[1] =  5.1e-6;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.0e-5; // limit on aCW
  x[3] =  0;          y[3] = 2.0e-5; // limit on aCW
  // x[4] =  2.065e-6;   y[4] = 0.7e-5;
  // x[5] =  -5.558e-6;  y[5] = 0.7e-5;
  // x[6] =  5.652e-6;   y[6] = -0.7e-5;
  // x[7] =  -2.064e-6;  y[7] = -0.7e-5;
  // x[8] =  -4.170e-6;   y[8] = 2.8e-5;
  // x[9] =  -9.825e-6;  y[9] = 2.8e-5;

  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "WW ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5,3e-5);
  g_aux->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [GeV^{-2}]");
  g_aux->GetYaxis()->SetRangeUser(-1e-4,1e-4);
  g_aux->SetMarkerStyle(20);

  return g_aux;
}

void FitEllipse(){

  // WW plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_ww = fitEllipseTGraphDLSF(GraphWW());
  TEllipse *smallEllipse_ww = fitEllipseTGraphDLSF(GraphWW_minusSigma());
  TEllipse *largeEllipse_ww = fitEllipseTGraphDLSF(GraphWW_plusSigma());
  expEllipse_ww->SetLineColor(kBlack);
  expEllipse_ww->SetLineWidth(2);
  expEllipse_ww->SetLineStyle(7);
  smallEllipse_ww->SetFillStyle(1001);
  smallEllipse_ww->SetLineColor(kBlack);
  smallEllipse_ww->SetLineWidth(0);
  largeEllipse_ww->SetFillColor(kGreen);
  largeEllipse_ww->SetFillStyle(1001);
  largeEllipse_ww->SetLineColor(kBlack);
  largeEllipse_ww->SetLineWidth(0);
  TCanvas *c_ww = new TCanvas();
  TGraph *g_ww  = GraphWW();
  TH1F *g_ww_leg = new TH1F("Expected 95\% CL exclusion contour #pm 1#sigma","Expected 95\% CL exclusion contour #pm 1#sigma",1,0,1);
  g_ww_leg->SetFillColor(kGreen);
  g_ww_leg->SetLineWidth(2);
  g_ww_leg->SetLineStyle(7);
  TGraph *g_ww_realpoints = GraphWW_realPoints();
  g_ww_realpoints->SetMarkerColor(12);
  TLegend *leg_ww = new TLegend(0.4,0.7,0.9,0.9);
  leg_ww->AddEntry(g_ww_leg,"Expected 95\% CL exclusion contour #pm 1#sigma");
  leg_ww->AddEntry(g_ww_realpoints,"Points tested with full CMS simulation");
  gStyle->SetLegendTextSize(0.03);

  g_ww->GetXaxis()->SetLabelOffset(0.015);
  g_ww->GetXaxis()->SetTitleOffset(1.2);
  g_ww->GetYaxis()->SetLabelOffset(0.015);
  g_ww->GetYaxis()->SetTitleOffset(1.3);
  
  g_ww->Draw("AP");
  largeEllipse_ww->Draw("same");
  smallEllipse_ww->Draw("same");
  expEllipse_ww->Draw("same");
  g_ww_realpoints->Draw("Psame");
  fixDivisionsAndGrid(g_ww,506,510,-0.1e-3,0.1e-3);
  CMS_TOTEM_lumi((TPad*)c_ww->GetPad(0),4,11,"");
  leg_ww->Draw("same");

  c_ww->SaveAs("Ellipse_ww.pdf");

  // ZZ plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_zz = fitEllipseTGraphDLSF(GraphZZ());
  TEllipse *smallEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_minusSigma());
  TEllipse *largeEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_plusSigma());
  expEllipse_zz->SetLineColor(kBlack);
  expEllipse_zz->SetLineWidth(2);
  expEllipse_zz->SetLineStyle(7);
  smallEllipse_zz->SetFillStyle(1001);
  smallEllipse_zz->SetLineColor(kBlack);
  smallEllipse_zz->SetLineWidth(0);
  largeEllipse_zz->SetFillColor(kGreen);
  largeEllipse_zz->SetFillStyle(1001);
  largeEllipse_zz->SetLineColor(kBlack);
  largeEllipse_zz->SetLineWidth(0);
  TCanvas *c_zz = new TCanvas();
  TGraph *g_zz  = GraphZZ();
  TH1F *g_zz_leg = new TH1F("Expected 95\% CL exclusion contour #pm 1#sigma","Expected 95\% CL exclusion contour #pm 1#sigma",1,0,1);
  g_zz_leg->SetFillColor(kGreen);
  g_zz_leg->SetLineWidth(2);
  g_zz_leg->SetLineStyle(7);
  TGraph *g_zz_realpoints = GraphZZ_realPoints();
  g_zz_realpoints->SetMarkerColor(12);
  TLegend *leg_zz = new TLegend(0.4,0.7,0.9,0.9);
  leg_zz->AddEntry(g_zz_leg,"Expected 95\% CL exclusion contour #pm 1#sigma");
  leg_zz->AddEntry(g_zz_realpoints,"Points tested with full CMS simulation");
  gStyle->SetLegendTextSize(0.03);

  g_zz->GetXaxis()->SetLabelOffset(0.015);
  g_zz->GetXaxis()->SetTitleOffset(1.2);
  g_zz->GetYaxis()->SetLabelOffset(0.015);
  g_zz->GetYaxis()->SetTitleOffset(1.3);
  
  g_zz->Draw("AP");
  largeEllipse_zz->Draw("same");
  smallEllipse_zz->Draw("same");
  expEllipse_zz->Draw("same");
  g_zz_realpoints->Draw("Psame");
  fixDivisionsAndGrid(g_zz,508,510,-0.2e-3,0.2e-3);
  CMS_TOTEM_lumi((TPad*)c_zz->GetPad(0),4,11,"");
  leg_zz->Draw("same");

  c_zz->SaveAs("Ellipse_zz.pdf");


  // WW clipped plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip());
  TEllipse *smallEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_minusSigma());
  TEllipse *largeEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_plusSigma());
  expEllipse_ww_clip->SetLineColor(kBlack);
  expEllipse_ww_clip->SetLineWidth(2);
  expEllipse_ww_clip->SetLineStyle(7);
  smallEllipse_ww_clip->SetFillStyle(1001);
  smallEllipse_ww_clip->SetLineColor(kBlack);
  smallEllipse_ww_clip->SetLineWidth(0);
  largeEllipse_ww_clip->SetFillColor(kGreen);
  largeEllipse_ww_clip->SetFillStyle(1001);
  largeEllipse_ww_clip->SetLineColor(kBlack);
  largeEllipse_ww_clip->SetLineWidth(0);
  TCanvas *c_ww_clip = new TCanvas();
  TGraph *g_ww_clip  = GraphWW();
  TH1F *g_ww_clip_leg = new TH1F("Expected 95\% CL exclusion contour #pm 1#sigma","Expected 95\% CL exclusion contour #pm 1#sigma",1,0,1);
  g_ww_clip_leg->SetFillColor(kGreen);
  g_ww_clip_leg->SetLineWidth(2);
  g_ww_clip_leg->SetLineStyle(7);
  TGraph *g_ww_clip_realpoints = GraphWW_clip_realPoints();
  g_ww_clip_realpoints->SetMarkerColor(12);
  TLegend *leg_ww_clip = new TLegend(0.4,0.7,0.9,0.9);
  leg_ww_clip->AddEntry(g_ww_clip_leg,"Expected 95\% CL exclusion contour #pm 1#sigma");
  leg_ww_clip->AddEntry(g_ww_clip_realpoints,"Points tested with full CMS simulation");
  gStyle->SetLegendTextSize(0.03);

  g_ww_clip->GetXaxis()->SetLabelOffset(0.015);
  g_ww_clip->GetXaxis()->SetTitleOffset(1.2);
  g_ww_clip->GetYaxis()->SetLabelOffset(0.015);
  g_ww_clip->GetYaxis()->SetTitleOffset(1.3);
  
  g_ww_clip->Draw("AP");
  largeEllipse_ww_clip->Draw("same");
  smallEllipse_ww_clip->Draw("same");
  expEllipse_ww_clip->Draw("same");
  g_ww_clip_realpoints->Draw("Psame");
  fixDivisionsAndGrid(g_ww_clip,506,510,-0.1e-3,0.1e-3);
  CMS_TOTEM_lumi((TPad*)c_ww_clip->GetPad(0),4,11,"");
  leg_ww_clip->Draw("same");

  c_ww_clip->SaveAs("Ellipse_ww_clip.pdf");  
  return;
}

// end of file fitEllipseTGraphDLSF.cxx by Silesius Anonymus
