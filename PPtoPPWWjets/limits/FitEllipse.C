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
  x[0] =  -3.699e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  3.699e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.383e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.383e-5*1e+7; // limit on aCW
  x[4] =  1.96942e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -5.46232e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  5.557e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -1.970e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -1.719e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -8.339e-6*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_observed() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -4.13276e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  4.13276e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.4936e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.4936e-5*1e+7; // limit on aCW
  x[4] =  2.31e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -5.80e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  5.89e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -2.30e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -1.35e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -8.71e-6*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_plusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -4.736e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  4.736e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.772e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.772e-5*1e+7; // limit on aCW
  x[4] =  2.97514e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -6.46804e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  6.5555e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -2.96835e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -6.3158e-7*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -9.42674e-6*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_plus2Sigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -6.001e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  6.001e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.249e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 2.249e-5*1e+7; // limit on aCW
  x[4] =  4.22678e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -7.71968e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  7.80223e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -4.21506e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  6.773e-7*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -1.07356e-5*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_minusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -2.961e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  2.961e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.110e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.110e-5*1e+7; // limit on aCW
  x[4] =  1.16134e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -4.65424e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  4.75919e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -1.17202e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -2.64861e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -7.40971e-6*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_minus2Sigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -2.504e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  2.504e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -9.354e-6*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 9.354e-6*1e+7; // limit on aCW
  x[4] =  6.84303e-7*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -4.1772e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  4.29163e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -7.04459e-7*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -3.25405e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -6.80427e-6*1e+7;  y[9] = 2.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -3.699e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  3.699e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.383e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.383e-5*1e+7; // limit on aCW
  // x[4] =  2.065e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  // x[5] =  -5.558e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  // x[6] =  5.652e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  // x[7] =  -2.064e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  // x[8] =  -4.170e-6*1e+7;   y[8] = 2.8e-5*1e+7;
  // x[9] =  -9.825e-6*1e+7;  y[9] = 2.8e-5*1e+7;

  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "WW ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g_aux->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
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
  x[0] =  -9.742e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  9.742e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.652e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 3.652e-5*1e+7; // limit on aCW
  x[4] =  4.048e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -1.504e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  1.503e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -4.031e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  -3.791e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -2.127e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-5e-5*1e+7,5e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2.5e-4*1e+7,2.5e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_observed() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -8.1864e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  8.1864e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.0124e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 3.0124e-5*1e+7; // limit on aCW
  x[4] =  2.38e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -1.34e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  1.34e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -2.36e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  -5.65e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -1.94e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5*1e+7,4e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4*1e+7,2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_plusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -1.205e-5*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  1.205e-5*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -4.508e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 4.508e-5*1e+7; // limit on aCW
  x[4] =  6.3806e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -1.73776e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  1.73664e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -6.36685e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  -1.28928e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -2.37714e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5*1e+7,4e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4*1e+7,2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_plus2Sigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -1.489e-5*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  1.489e-5*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -5.572e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 5.572e-5*1e+7; // limit on aCW
  x[4] =  9.24572e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -2.02427e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  2.02343e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -9.23477e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  1.70584e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -2.67665e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5*1e+7,4e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4*1e+7,2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_minusSigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -8.011e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  8.011e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.999e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 2.999e-5*1e+7; // limit on aCW
  x[4] =  2.27569e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -1.32727e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  1.32541e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -2.25459e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  -5.77339e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -1.92873e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5*1e+7,4e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4*1e+7,2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_minus2Sigma() {

  const Int_t n = 10; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -6.847e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  6.847e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.563e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 2.563e-5*1e+7; // limit on aCW
  x[4] =  1.07365e-6*1e+7;   y[4] = 2.2e-5*1e+7;
  x[5] =  -1.20707e-5*1e+7;  y[5] = 2.2e-5*1e+7;
  x[6] =  1.20482e-5*1e+7;   y[6] = -2.2e-5*1e+7;
  x[7] =  -1.04872e-6*1e+7;  y[7] = -2.2e-5*1e+7;
  x[8] =  -7.2007e-6*1e+7;   y[8] = 5e-5*1e+7;
  x[9] =  -1.786e-5*1e+7;  y[9] = 5e-5*1e+7;

  // create the test TGraph
  TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  if (g) delete g;
  g = new TGraph(n, x, y);
  g->SetNameTitle("g", "ZZ ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-4e-5*1e+7,4e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-2e-4*1e+7,2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphZZ_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -9.742e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  9.742e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.652e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 3.652e-5*1e+7; // limit on aCW
  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "ZZ ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g_aux->GetYaxis()->SetTitle("a_{C}^{Z}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetYaxis()->SetTitleOffset(1.2);
  g_aux->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
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

  const Int_t n = 14; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -5.456e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  5.456e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.906e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.906e-5*1e+7; // limit on aCW
  x[4] =  3.504e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -6.997e-6*1e+7; y[5] = 0.7e-5*1e+7;
  x[6] =  7.082e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -3.495e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -7.409e-8;  y[8] = 2.0e-5*1e+7;
  x[9] =  -9.984e-6*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  1.2054e-5*1e+7;   y[10] = -3.0e-5*1e+7;
  x[11] =  2.87904e-6*1e+7;  y[11] = -3.0e-5*1e+7;
  x[12] =  1.51365e-5*1e+7;  y[12] = -5.0e-5*1e+7;
  x[13] =  9.78867e-6*1e+7;  y[13] = -5.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1.2e-4*1e+7,1.2e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_observed_clip() {

  const Int_t n = 14; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -5.4781e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  5.4781e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.8675e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.8675e-5*1e+7; // limit on aCW
  x[4] =  3.48e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -6.97e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  7.05e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -3.47e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -1.04e-7*1e+7;  y[8] = 2.0e-5*1e+7;
  x[9] =  -9.95e-6*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  1.2022e-5*1e+7;  y[10] = -3.0e-5*1e+7;
  x[11] =  2.9114e-6*1e+7;  y[11] = -3.0e-5*1e+7;
  x[12] =  1.5081e-5*1e+7;  y[12] = -5.0e-5*1e+7;
  x[13] =  9.8446e-6*1e+7;  y[13] = -5.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_plusSigma() {

  const Int_t n = 14; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -7.077e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  7.077e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.395e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 2.395e-5*1e+7; // limit on aCW
  x[4] =  4.997e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -8.490e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  8.571e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -4.984e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  1.470e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -1.153e-5*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  1.36952e-5*1e+7;  y[10] = -3.0e-5*1e+7;
  x[11] =  1.23782e-6*1e+7;  y[11] = -3.0e-5*1e+7;
  x[12] =  1.74552e-5*1e+7;  y[12] = -5.0e-5*1e+7;
  x[13] =  7.47002e-6*1e+7;  y[13] = -5.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_plus2Sigma() {

  const Int_t n = 14; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -9.50916e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  9.50916e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -3.1262e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 3.1262e-5*1e+7; // limit on aCW
  x[4] =  7.22772e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -1.07206e-5*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  1.07991e-5*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -7.21195e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  3.73897e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -1.37973e-5*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  1.60423e-5*1e+7;  y[10] = -3.0e-5*1e+7;
  x[11] =  -1.10927e-6*1e+7;  y[11] = -3.0e-5*1e+7;
  x[12] =  2.0191e-5*1e+7;  y[12] = -5.0e-5*1e+7;
  x[13] =  4.7347e-6*1e+7;  y[13] = -5.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_minusSigma() {

  const Int_t n = 12; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -4.290e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  4.290e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.545e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.545e-5*1e+7; // limit on aCW
  x[4] =  2.451e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -5.944e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  6.035e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -2.448e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -1.192e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -8.866e-6*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  1.08105e-5*1e+7;   y[10] = -3.0e-5*1e+7;
  x[11] =  4.12258e-6*1e+7;  y[11] = -3.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}

TGraph *GraphWW_clip_minus2Sigma() {

  const Int_t n = 12; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -3.4249e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  3.4249e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -1.27098e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 1.27098e-5*1e+7; // limit on aCW
  x[4] =  1.6232e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  x[5] =  -5.1161e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  x[6] =  5.21457e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  x[7] =  -1.6274e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  x[8] =  -2.1083e-6*1e+7;   y[8] = 2.0e-5*1e+7;
  x[9] =  -7.95003e-6*1e+7;  y[9] = 2.0e-5*1e+7;
  x[10] =  9.69613e-6*1e+7;   y[10] = -3.0e-5*1e+7;
  x[11] =  5.23691e-6*1e+7;  y[11] = -3.0e-5*1e+7;

  // create the test TGraph
  // TGraph *g = ((TGraph *)(gROOT->FindObject("g")));
  // if (g) delete g;
  TGraph *g = new TGraph(n, x, y);
  g->SetNameTitle("g", "WW ellipse");
  g->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g->GetYaxis()->SetTitleOffset(1.2);
  g->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g->SetMarkerStyle(6);

  return g;
}



TGraph *GraphWW_clip_realPoints() {

  const Int_t n = 4; // number of points
  Double_t x[n], y[n];

  // Manually add points
  x[0] =  -5.1e-6*1e+7;    y[0] = 0; // limit on a0W
  x[1] =  5.1e-6*1e+7;     y[1] = 0; // limit on a0W
  x[2] =  0;          y[2] = -2.0e-5*1e+7; // limit on aCW
  x[3] =  0;          y[3] = 2.0e-5*1e+7; // limit on aCW
  // x[4] =  2.065e-6*1e+7;   y[4] = 0.7e-5*1e+7;
  // x[5] =  -5.558e-6*1e+7;  y[5] = 0.7e-5*1e+7;
  // x[6] =  5.652e-6*1e+7;   y[6] = -0.7e-5*1e+7;
  // x[7] =  -2.064e-6*1e+7;  y[7] = -0.7e-5*1e+7;
  // x[8] =  -4.170e-6*1e+7;   y[8] = 2.8e-5*1e+7;
  // x[9] =  -9.825e-6*1e+7;  y[9] = 2.8e-5*1e+7;

  // create the test TGraph
  TGraph *g_aux = ((TGraph *)(gROOT->FindObject("g_aux")));
  if (g_aux) delete g_aux;
  g_aux = new TGraph(n, x, y);
  g_aux->SetNameTitle("g_aux", "WW ellipse");
  g_aux->GetXaxis()->SetTitle("a_{0}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetXaxis()->SetLimits(-3e-5*1e+7,3e-5*1e+7);
  g_aux->GetYaxis()->SetTitle("a_{C}^{W}/#Lambda^{2} [#times 10^{-7} GeV^{-2}]");
  g_aux->GetYaxis()->SetRangeUser(-1e-4*1e+7,1e-4*1e+7);
  g_aux->SetMarkerStyle(20);

  return g_aux;
}

void FitEllipse(){

  // WW plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_ww = fitEllipseTGraphDLSF(GraphWW());
  TEllipse *obsEllipse_ww = fitEllipseTGraphDLSF(GraphWW_observed());
  TEllipse *oneSigmaSmallEllipse_ww = fitEllipseTGraphDLSF(GraphWW_minusSigma());
  TEllipse *twoSigmaSmallEllipse_ww = fitEllipseTGraphDLSF(GraphWW_minus2Sigma());
  TEllipse *oneSigmaLargeEllipse_ww = fitEllipseTGraphDLSF(GraphWW_plusSigma());
  TEllipse *twoSigmaLargeEllipse_ww = fitEllipseTGraphDLSF(GraphWW_plus2Sigma());
  expEllipse_ww->SetLineColor(kRed);
  expEllipse_ww->SetLineWidth(2);
  obsEllipse_ww->SetLineColor(kBlack);
  obsEllipse_ww->SetLineWidth(2);
  // obsEllipse_ww->SetLineStyle(7);
  oneSigmaSmallEllipse_ww->SetFillStyle(1001);
  oneSigmaSmallEllipse_ww->SetFillColor(kYellow);
  oneSigmaSmallEllipse_ww->SetLineColor(kBlack);
  oneSigmaSmallEllipse_ww->SetLineWidth(0);
  twoSigmaSmallEllipse_ww->SetFillStyle(1001);
  twoSigmaSmallEllipse_ww->SetLineColor(kBlack);
  twoSigmaSmallEllipse_ww->SetLineWidth(0);
  oneSigmaLargeEllipse_ww->SetFillColor(kGreen);
  oneSigmaLargeEllipse_ww->SetFillStyle(1001);
  oneSigmaLargeEllipse_ww->SetLineColor(kBlack);
  oneSigmaLargeEllipse_ww->SetLineWidth(0);
  twoSigmaLargeEllipse_ww->SetFillColor(kYellow);
  twoSigmaLargeEllipse_ww->SetFillStyle(1001);
  twoSigmaLargeEllipse_ww->SetLineColor(kBlack);
  twoSigmaLargeEllipse_ww->SetLineWidth(0);
  TCanvas *c_ww = new TCanvas();
  TGraph *g_ww  = GraphWW();
  TH1F *g_ww_leg = new TH1F("Expected 95\% CL limit","Expected 95\% CL limit",1,0,1);
  g_ww_leg->SetFillColor(kWhite);
  g_ww_leg->SetLineWidth(2);
  g_ww_leg->SetLineColor(kRed);

  TH1F *g_ww_leg_1s = new TH1F("Expected 95\% CL limit #pm 1#sigma","Expected 95\% CL limit #pm 1#sigma",1,0,1);
  g_ww_leg_1s->SetFillColor(kGreen);
  g_ww_leg_1s->SetLineWidth(2);
  g_ww_leg_1s->SetLineColor(kGreen);

  TH1F *g_ww_leg_2s = new TH1F("Expected 95\% CL limit #pm 2#sigma","Expected 95\% CL limit #pm 2#sigma",1,0,1);
  g_ww_leg_2s->SetFillColor(kYellow);
  g_ww_leg_2s->SetLineWidth(2);
  g_ww_leg_2s->SetLineColor(kYellow);
  
  TH1F *g_ww_obs_leg = new TH1F("Observed 95\% CL limit","Observed 95\% CL limit",1,0,1);
  g_ww_obs_leg->SetLineWidth(2);
  g_ww_obs_leg->SetLineColor(kBlack);
  TGraph *g_ww_realpoints = GraphWW_realPoints();
  g_ww_realpoints->SetMarkerColor(kRed);
  g_ww_realpoints->SetMarkerStyle(20);
  g_ww_realpoints->SetMarkerSize(0.8);

  TGraph *g_ww_forARC = GraphWW();
  g_ww_forARC->SetMarkerColor(kRed);
  g_ww_forARC->SetMarkerStyle(20);
  g_ww_forARC->SetMarkerSize(0.8);

  TGraph *g_ww_forARC_obs = GraphWW_observed();
  g_ww_forARC_obs->SetMarkerColor(kBlack);
  g_ww_forARC_obs->SetMarkerStyle(20);
  g_ww_forARC_obs->SetMarkerSize(0.8);

  TLegend *leg_ww = new TLegend(0.44,0.7,0.9,0.9);
  leg_ww->AddEntry(g_ww_obs_leg,"Observed 95\% CL limit");
  leg_ww->AddEntry(g_ww_leg,"Expected 95\% CL limit");
  leg_ww->AddEntry(g_ww_leg_1s,"Expected 95\% CL limit #pm 1#sigma","F");
  leg_ww->AddEntry(g_ww_leg_2s,"Expected 95\% CL limit #pm 2#sigma","F");
  // leg_ww->AddEntry(g_ww_realpoints,"Points tested with full CMS simulation","P");
  gStyle->SetLegendTextSize(0.042);

  gPad->SetBottomMargin(0.17);
  gPad->SetLeftMargin(0.17);
  g_ww->GetXaxis()->SetLabelOffset(0.015);
  g_ww->GetXaxis()->SetLabelSize(0.05);
  g_ww->GetXaxis()->SetTitleOffset(1.1);
  g_ww->GetXaxis()->SetTitleSize(0.07);
  g_ww->GetYaxis()->SetLabelOffset(0.015);
  g_ww->GetYaxis()->SetLabelSize(0.05);
  g_ww->GetYaxis()->SetTitleOffset(1.2);
  g_ww->GetYaxis()->SetTitleSize(0.07);
  g_ww->GetYaxis()->SetRangeUser(-900,1100);
  
  cout << "Label size: " << g_ww->GetXaxis()->GetLabelSize()<<endl;
  g_ww->Draw("AP");
  twoSigmaLargeEllipse_ww->Draw("same");
  oneSigmaLargeEllipse_ww->Draw("same");
  oneSigmaSmallEllipse_ww->Draw("same");
  twoSigmaSmallEllipse_ww->Draw("same");
  expEllipse_ww->Draw("same");
  // g_ww_forARC->Draw("Psame");
  // g_ww_realpoints->Draw("Psame");
  obsEllipse_ww->Draw("same");
  // g_ww_forARC_obs->Draw("Psame");
  fixDivisionsAndGrid(g_ww,506,510,-0.1e-3*1e+7,0.1e-3*1e+7);
  CMS_TOTEM_lumi((TPad*)c_ww->GetPad(0),4,11,"2",true);
  leg_ww->Draw("same");

  c_ww->SaveAs("Ellipse_ww.pdf");

  // ZZ plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_zz = fitEllipseTGraphDLSF(GraphZZ());
  TEllipse *obsEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_observed());
  TEllipse *oneSigmaSmallEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_minusSigma());
  TEllipse *twoSigmaSmallEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_minus2Sigma());
  TEllipse *oneSigmaLargeEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_plusSigma());
  TEllipse *twoSigmaLargeEllipse_zz = fitEllipseTGraphDLSF(GraphZZ_plus2Sigma());
  expEllipse_zz->SetLineColor(kRed);
  expEllipse_zz->SetLineWidth(2);
  obsEllipse_zz->SetLineColor(kBlack);
  obsEllipse_zz->SetLineWidth(2);
  oneSigmaSmallEllipse_zz->SetFillStyle(1001);
  oneSigmaSmallEllipse_zz->SetFillColor(kYellow);
  oneSigmaSmallEllipse_zz->SetLineColor(kBlack);
  oneSigmaSmallEllipse_zz->SetLineWidth(0);
  twoSigmaSmallEllipse_zz->SetFillStyle(1001);
  twoSigmaSmallEllipse_zz->SetLineColor(kBlack);
  twoSigmaSmallEllipse_zz->SetLineWidth(0);
  oneSigmaLargeEllipse_zz->SetFillColor(kGreen);
  oneSigmaLargeEllipse_zz->SetFillStyle(1001);
  oneSigmaLargeEllipse_zz->SetLineColor(kBlack);
  oneSigmaLargeEllipse_zz->SetLineWidth(0);
  twoSigmaLargeEllipse_zz->SetFillColor(kYellow);
  twoSigmaLargeEllipse_zz->SetFillStyle(1001);
  twoSigmaLargeEllipse_zz->SetLineColor(kBlack);
  twoSigmaLargeEllipse_zz->SetLineWidth(0);
  TCanvas *c_zz = new TCanvas();
  TGraph *g_zz  = GraphZZ();
  TH1F *g_zz_leg = new TH1F("Expected 95\% CL limit #pm 1#sigma","Expected 95\% CL limit #pm 1#sigma",1,0,1);
  g_zz_leg->SetFillColor(kWhite);
  g_zz_leg->SetLineWidth(2);
  g_zz_leg->SetLineColor(kRed);

  TH1F *g_zz_leg_1s = new TH1F("Expected 95\% CL limit #pm 1#sigma","Expected 95\% CL limit #pm 1#sigma",1,0,1);
  g_zz_leg_1s->SetFillColor(kGreen);
  g_zz_leg_1s->SetLineWidth(2);
  g_zz_leg_1s->SetLineColor(kGreen);

  TH1F *g_zz_leg_2s = new TH1F("Expected 95\% CL limit #pm 2#sigma","Expected 95\% CL limit #pm 2#sigma",1,0,1);
  g_zz_leg_2s->SetFillColor(kYellow);
  g_zz_leg_2s->SetLineWidth(2);
  g_zz_leg_2s->SetLineColor(kYellow);

  TH1F *g_zz_obs_leg = new TH1F("Observed 95\% CL limit #pm 1#sigma","Expected 95\% CL limit #pm 1#sigma",1,0,1);
  g_zz_obs_leg->SetLineWidth(2);
  g_zz_obs_leg->SetLineColor(kBlack);

  TGraph *g_zz_realpoints = GraphZZ_realPoints();
  g_zz_realpoints->SetMarkerColor(kRed);
  g_zz_realpoints->SetMarkerStyle(20);
  g_zz_realpoints->SetMarkerSize(0.8);  

  TGraph *g_zz_forARC = GraphZZ();
  g_zz_forARC->SetMarkerColor(kRed);
  g_zz_forARC->SetMarkerStyle(20);
  g_zz_forARC->SetMarkerSize(0.8);  

  TGraph *g_zz_forARC_obs = GraphZZ_observed();
  g_zz_forARC_obs->SetMarkerColor(kBlack);
  g_zz_forARC_obs->SetMarkerStyle(20);
  g_zz_forARC_obs->SetMarkerSize(0.8);

  TLegend *leg_zz = new TLegend(0.44,0.7,0.9,0.9);
  leg_zz->AddEntry(g_zz_obs_leg,"Observed 95\% CL limit");
  leg_zz->AddEntry(g_zz_leg,"Expected 95\% CL limit");
  leg_zz->AddEntry(g_zz_leg_1s,"Expected 95\% CL limit #pm 1#sigma","F");
  leg_zz->AddEntry(g_zz_leg_2s,"Expected 95\% CL limit #pm 2#sigma","F");
  // leg_zz->AddEntry(g_ww_realpoints,"Points tested with full CMS simulation","P");
  gStyle->SetLegendTextSize(0.042);

  gPad->SetBottomMargin(0.17);
  gPad->SetLeftMargin(0.17);
  g_zz->GetXaxis()->SetLabelOffset(0.015);
  g_zz->GetXaxis()->SetLabelSize(0.05);
  g_zz->GetXaxis()->SetTitleOffset(1.1);
  g_zz->GetXaxis()->SetTitleSize(0.07);
  g_zz->GetYaxis()->SetLabelOffset(0.015);
  g_zz->GetYaxis()->SetLabelSize(0.05);
  g_zz->GetYaxis()->SetTitleOffset(1.2);
  g_zz->GetYaxis()->SetTitleSize(0.07);
  
  g_zz->Draw("AP");
  twoSigmaLargeEllipse_zz->Draw("same");
  oneSigmaLargeEllipse_zz->Draw("same");
  oneSigmaSmallEllipse_zz->Draw("same");
  twoSigmaSmallEllipse_zz->Draw("same");
  expEllipse_zz->Draw("same");
  // g_zz_realpoints->Draw("Psame");
  // g_zz_forARC->Draw("Psame");
  obsEllipse_zz->Draw("same");
  // g_zz_forARC_obs->Draw("Psame");
  fixDivisionsAndGrid(g_zz,508,510,-0.25e-3*1e+7,0.25e-3*1e+7);
  CMS_TOTEM_lumi((TPad*)c_zz->GetPad(0),4,11,"2",true);
  leg_zz->Draw("same");

  c_zz->SaveAs("Ellipse_zz.pdf");


  // WW clipped plot
  gStyle->SetOptTitle(0);
  TEllipse *expEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip());
  TEllipse *obsEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_observed_clip());
  TEllipse *oneSigmaSmallEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_minusSigma());
  TEllipse *twoSigmaSmallEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_minus2Sigma());
  TEllipse *oneSigmaLargeEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_plusSigma());
  TEllipse *twoSigmaLargeEllipse_ww_clip = fitEllipseTGraphDLSF(GraphWW_clip_plus2Sigma());
  expEllipse_ww_clip->SetLineColor(kRed);
  expEllipse_ww_clip->SetLineWidth(2);
  obsEllipse_ww_clip->SetLineColor(kBlack);
  obsEllipse_ww_clip->SetLineWidth(2);
  // obsEllipse_ww_clip->SetLineStyle(7);
  oneSigmaSmallEllipse_ww_clip->SetFillStyle(1001);
  oneSigmaSmallEllipse_ww_clip->SetFillColor(kYellow);
  oneSigmaSmallEllipse_ww_clip->SetLineColor(kBlack);
  oneSigmaSmallEllipse_ww_clip->SetLineWidth(0);
  twoSigmaSmallEllipse_ww_clip->SetFillStyle(1001);
  twoSigmaSmallEllipse_ww_clip->SetLineColor(kBlack);
  twoSigmaSmallEllipse_ww_clip->SetLineWidth(0);
  oneSigmaLargeEllipse_ww_clip->SetFillColor(kGreen);
  oneSigmaLargeEllipse_ww_clip->SetFillStyle(1001);
  oneSigmaLargeEllipse_ww_clip->SetLineColor(kBlack);
  oneSigmaLargeEllipse_ww_clip->SetLineWidth(0);
  twoSigmaLargeEllipse_ww_clip->SetFillStyle(1001);
  twoSigmaLargeEllipse_ww_clip->SetFillColor(kYellow);
  twoSigmaLargeEllipse_ww_clip->SetLineColor(kBlack);
  twoSigmaLargeEllipse_ww_clip->SetLineWidth(0);
  TCanvas *c_ww_clip = new TCanvas();
  TGraph *g_ww_clip  = GraphWW_clip();
  TH1F *g_ww_clip_leg = new TH1F("Expected 95\% CL limit","Expected 95\% CL limit",1,0,1);
  g_ww_clip_leg->SetFillColor(kWhite);
  g_ww_clip_leg->SetLineWidth(2);
  g_ww_clip_leg->SetLineColor(kRed);

  TH1F *g_ww_clip_leg_1s = new TH1F("Expected 95\% CL limit #pm 1#sigma","Expected 95\% CL limit #pm 1#sigma",1,0,1);
  g_ww_clip_leg_1s->SetFillColor(kGreen);
  g_ww_clip_leg_1s->SetLineWidth(2);
  g_ww_clip_leg_1s->SetLineColor(kGreen);

  TH1F *g_ww_clip_leg_2s = new TH1F("Expected 95\% CL limit #pm 2#sigma","Expected 95\% CL limit #pm 2#sigma",1,0,1);
  g_ww_clip_leg_2s->SetFillColor(kYellow);
  g_ww_clip_leg_2s->SetLineWidth(2);
  g_ww_clip_leg_2s->SetLineColor(kYellow);
  
  TH1F *g_ww_clip_obs_leg = new TH1F("Observed 95\% CL limit","Observed 95\% CL limit",1,0,1);
  g_ww_clip_obs_leg->SetLineWidth(2);
  g_ww_clip_obs_leg->SetLineColor(kBlack);

  TGraph *g_ww_clip_realpoints = GraphWW_clip_realPoints();
  g_ww_clip_realpoints->SetMarkerColor(kRed);
  g_ww_clip_realpoints->SetMarkerStyle(20);
  g_ww_clip_realpoints->SetMarkerSize(0.8);  

  TGraph *g_ww_clip_forARC = GraphWW_clip();
  g_ww_clip_forARC->SetMarkerColor(kRed);
  g_ww_clip_forARC->SetMarkerStyle(20);
  g_ww_clip_forARC->SetMarkerSize(0.8);  

  TGraph *g_ww_clip_forARC_obs = GraphWW_observed_clip();
  g_ww_clip_forARC_obs->SetMarkerColor(kBlack);
  g_ww_clip_forARC_obs->SetMarkerStyle(20);
  g_ww_clip_forARC_obs->SetMarkerSize(0.8);  

  TLegend *leg_ww_clip = new TLegend(0.44,0.7,0.9,0.9);
  leg_ww_clip->AddEntry(g_ww_clip_obs_leg,"Observed 95\% CL limit");
  leg_ww_clip->AddEntry(g_ww_clip_leg,"Expected 95\% CL limit");
  leg_ww_clip->AddEntry(g_ww_clip_leg_1s,"Expected 95\% CL limit #pm 1#sigma","F");
  leg_ww_clip->AddEntry(g_ww_clip_leg_2s,"Expected 95\% CL limit #pm 2#sigma","F");
  // leg_ww_clip->AddEntry(g_ww_realpoints,"Points tested with full CMS simulation","P");
  gStyle->SetLegendTextSize(0.042);

  gPad->SetBottomMargin(0.17);
  gPad->SetLeftMargin(0.17);
  g_ww_clip->GetXaxis()->SetLabelOffset(0.015);
  g_ww_clip->GetXaxis()->SetLabelSize(0.05);
  g_ww_clip->GetXaxis()->SetTitleOffset(1.1);
  g_ww_clip->GetXaxis()->SetTitleSize(0.07);
  g_ww_clip->GetYaxis()->SetLabelOffset(0.015);
  g_ww_clip->GetYaxis()->SetLabelSize(0.05);
  g_ww_clip->GetYaxis()->SetTitleOffset(1.2);
  g_ww_clip->GetYaxis()->SetTitleSize(0.07);  
  g_ww_clip->GetYaxis()->SetRangeUser(-1100,1300);
  g_ww_clip->Draw("AP");
  twoSigmaLargeEllipse_ww_clip->Draw("same");
  oneSigmaLargeEllipse_ww_clip->Draw("same");
  oneSigmaSmallEllipse_ww_clip->Draw("same");
  twoSigmaSmallEllipse_ww_clip->Draw("same");
  expEllipse_ww_clip->Draw("same");
  // g_ww_clip_realpoints->Draw("Psame");
  // g_ww_clip_forARC->Draw("Psame");
  obsEllipse_ww_clip->Draw("same");
  // g_ww_clip_forARC_obs->Draw("Psame");
  fixDivisionsAndGrid(g_ww_clip,506,512,-0.12e-3*1e+7,0.12e-3*1e+7);
  CMS_TOTEM_lumi((TPad*)c_ww_clip->GetPad(0),4,11,"2",true);
  leg_ww_clip->Draw("same");

  c_ww_clip->SaveAs("Ellipse_ww_clip.pdf");  
  cout << "Legend text size " << gStyle->GetLegendTextSize() << endl;
  return;
}

// end of file fitEllipseTGraphDLSF.cxx by Silesius Anonymus

TMultiGraph* checkFit(TGraph* graph_orig = GraphWW()){

  bool print = false;

  const int nPoints =  graph_orig->GetN();
  double *x_orig = graph_orig->GetX();
  double *y_orig = graph_orig->GetY();

  TEllipse *ellipse_orig = fitEllipseTGraphDLSF(graph_orig);
  double x1_orig = ellipse_orig->GetX1();
  double y1_orig = ellipse_orig->GetY1();
  double r1_orig = ellipse_orig->GetR1();
  double r2_orig = ellipse_orig->GetR2();
  double theta_orig = ellipse_orig->GetTheta();

  double x[nPoints-1],y[nPoints-1];
  double point_idx[nPoints];
  TGraph *graph;
  double x1,y1,r1,r2,theta;
  double max_delta_x1 = 0, max_delta_y1 = 0;
  double delta_x1[nPoints],delta_y1[nPoints],delta_r1[nPoints],delta_r2[nPoints],delta_theta[nPoints];
  // Do this for every point
  for (int i=0;i<nPoints;i++){
    if (print) cout << "Removing " << i << ": ";
    point_idx[i] = i;
    // Remove point i from xy arrays
    int addedPoints = 0;
    for (int j=0;j<nPoints;j++){
      if (j != i){
        if (print)
          cout << j << " ";
        x[addedPoints] = x_orig[j];
        y[addedPoints] = y_orig[j];
        addedPoints++;
      }
    }
    if (print)
      cout << "\n";
    // create modified graph
    graph = new TGraph(nPoints-1,x,y);
    
    // Re-fit the ellipse and get parameter relative variation
    TEllipse *ellipse = fitEllipseTGraphDLSF(graph);
    x1 = ellipse->GetX1();
    y1 = ellipse->GetY1();
    r1 = ellipse->GetR1();
    r2 = ellipse->GetR2();
    theta = ellipse->GetTheta();
    delta_x1[i] = (x1_orig-x1)/x1_orig;
    delta_y1[i] = (y1_orig-y1)/y1_orig;
    delta_r1[i] = (r1_orig-r1)/r1_orig;
    delta_r2[i] = (r2_orig-r2)/r2_orig;
    delta_theta[i] = (theta_orig-theta)/theta_orig;

    if (TMath::Abs(x1_orig-x1) > max_delta_x1)
      max_delta_x1 = TMath::Abs(x1_orig-x1);
    if (TMath::Abs(y1_orig-y1) > max_delta_y1)
      max_delta_y1 = TMath::Abs(y1_orig-y1);
    delete graph;
  }

  if (print){
    cout << "Delta_r1: ";
    for (int i = 0;i<nPoints;i++)
      cout << delta_r1[i] << " ";
    cout << endl;
    cout << "Delta_r2: ";
    for (int i = 0;i<nPoints;i++)
      cout << delta_r2[i] << " ";
    cout << endl;
  }
    
  cout << "Maximum delta x1 = " << max_delta_x1 << endl;
  cout << "Maximum delta y1 = " << max_delta_y1 << endl;
  TMultiGraph *mg = new TMultiGraph();
  // TGraph *g_delta_x1 = new TGraph(nPoints-1,point_idx,delta_x1);
  // g_delta_x1->SetNameTitle("x center","x center");
  // g_delta_x1->SetLineWidth(2);
  // g_delta_x1->SetMarkerStyle(20);
  // mg->Add(g_delta_x1);
  // TGraph *g_delta_y1 = new TGraph(nPoints-1,point_idx,delta_y1);
  // g_delta_y1->SetNameTitle("y center","y center");
  // g_delta_y1->SetLineWidth(2);
  // g_delta_y1->SetMarkerStyle(20);
  // mg->Add(g_delta_y1);
  TGraph *g_delta_r1 = new TGraph(nPoints-1,point_idx,delta_r1);
  g_delta_r1->SetNameTitle("a semi-axis","a semi-axis");
  g_delta_r1->SetLineWidth(2);
  g_delta_r1->SetMarkerStyle(20);
  mg->Add(g_delta_r1);
  TGraph *g_delta_r2 = new TGraph(nPoints-1,point_idx,delta_r2);
  g_delta_r2->SetNameTitle("b semi-axis","b semi-axis");
  g_delta_r2->SetLineWidth(2);
  g_delta_r2->SetMarkerStyle(20);
  mg->Add(g_delta_r2);
  TGraph *g_delta_theta = new TGraph(nPoints-1,point_idx,delta_theta);
  g_delta_theta->SetLineWidth(2);
  g_delta_theta->SetMarkerStyle(20);
  g_delta_theta->SetNameTitle("rotation angle","rotation angle");
  mg->Add(g_delta_theta);
  mg->SetMinimum(-0.5);
  mg->SetMaximum(0.5);

  return mg;
}

void checkFitsExpected(){
  gStyle->SetPalette(kViridis);
  gStyle->SetLegendBorderSize(0);
  auto c = new TCanvas("CheckFits","CheckFits",500,900);
  c->Divide(1,3);
  auto mg1 = checkFit(GraphWW());
  // mg1->GetXaxis()->SetTitle("");
  mg1->SetTitle("WW limit - no clipping;Index of the removed point;Parameter relative variation");
  c->cd(1);
  mg1->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  auto mg2 = checkFit(GraphZZ());
  mg2->SetTitle("ZZ limit;Index of the removed point;Parameter relative variation");
  c->cd(2);
  mg2->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  auto mg3 = checkFit(GraphWW_clip());
  mg3->SetTitle("WW limit - clipped;Index of the removed point;Parameter relative variation");
  c->cd(3);
  mg3->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  c->SaveAs("CheckFitsExpected.pdf");

}

void checkFitsObserved(){
  gStyle->SetPalette(kViridis);
  gStyle->SetLegendBorderSize(0);
  auto c = new TCanvas("CheckFits","CheckFits",500,900);
  c->Divide(1,3);
  auto mg1 = checkFit(GraphWW_observed());
  // mg1->GetXaxis()->SetTitle("");
  mg1->SetTitle("WW limit - no clipping;Index of the removed point;Parameter relative variation");
  c->cd(1);
  mg1->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  auto mg2 = checkFit(GraphZZ_observed());
  mg2->SetTitle("ZZ limit;Index of the removed point;Parameter relative variation");
  c->cd(2);
  mg2->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  auto mg3 = checkFit(GraphWW_observed_clip());
  mg3->SetTitle("WW limit - clipped;Index of the removed point;Parameter relative variation");
  c->cd(3);
  mg3->Draw("ALP pmc plc");
  gPad->BuildLegend(0.65,0.7,0.89,0.89);
  c->SaveAs("CheckFitsObserved.pdf");

}