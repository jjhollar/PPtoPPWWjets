void PlotLimitsFinalReMiniAOD()
{
  // Using anti-acoplanarity backgrounds with stat. errors only
  // arbitrary 20% systematic on signal eff.

  TFile *fa0w1 = TFile::Open("higgsCombinea0W1e6.AsymptoticLimits.mH120.root");
  TFile *fa0w2 = TFile::Open("higgsCombinea0W2e6.AsymptoticLimits.mH120.root");
  TFile *fa0w3 = TFile::Open("higgsCombinea0W5e6.AsymptoticLimits.mH120.root");
  TFile *faCw1 = TFile::Open("higgsCombineaCW5e6.AsymptoticLimits.mH120.root");
  TFile *faCw2 = TFile::Open("higgsCombineaCW8e6.AsymptoticLimits.mH120.root");
  TFile *faCw3 = TFile::Open("higgsCombineaCW2e5.AsymptoticLimits.mH120.root");

  TFile *fa0z1 = TFile::Open("higgsCombinea0Z1e5.AsymptoticLimits.mH120.root");
  TFile *fa0z2 = TFile::Open("higgsCombinea0Z5e5.AsymptoticLimits.mH120.root");
  TFile *faCz1 = TFile::Open("higgsCombineaCZ1e5.AsymptoticLimits.mH120.root");
  TFile *faCz2 = TFile::Open("higgsCombineaCZ5e5.AsymptoticLimits.mH120.root");

  Double_t la0w1, la0w2, la0w3, laCw1, laCw2, laCw3, la0z1, la0z2, laCz1, laCz2;
  TTree *ta0w1 = (TTree *)fa0w1->Get("limit");
  //  TTree *ta0w2 = (TTree *)fa0w2->Get("limit");
  TTree *ta0w3 = (TTree *)fa0w3->Get("limit");
  TTree *taCw1 = (TTree *)faCw1->Get("limit");
  //  TTree *taCw2 = (TTree *)faCw2->Get("limit");
  TTree *taCw3 = (TTree *)faCw3->Get("limit");
  TTree *ta0z1 = (TTree *)fa0z1->Get("limit");
  TTree *ta0z2 = (TTree *)fa0z2->Get("limit");
  TTree *taCz1 = (TTree *)faCz1->Get("limit");
  TTree *taCz2 = (TTree *)faCz2->Get("limit");

  ta0w1->SetBranchAddress("limit", &la0w1);
  //  ta0w2->SetBranchAddress("limit", &la0w2);
  ta0w3->SetBranchAddress("limit", &la0w3);
  taCw1->SetBranchAddress("limit", &laCw1);
  //  taCw2->SetBranchAddress("limit", &laCw2);
  taCw3->SetBranchAddress("limit", &laCw3);
  ta0z1->SetBranchAddress("limit", &la0z1);
  ta0z2->SetBranchAddress("limit", &la0z2);
  taCz1->SetBranchAddress("limit", &laCz1);
  taCz2->SetBranchAddress("limit", &laCz2);



  Float_t a0[3] = {1E-6,2E-6,5E-6};
  Float_t u0[3] = {11.0000,2.7109,0.4727};
  //  TGraph *g1 = new TGraph(3,a0,u0);

  Float_t a0z[2] = {1E-5,5E-5};
  Float_t u0z[2] = {0.7930,0.0298};
  //  TGraph *g1z = new TGraph(2,a0z,u0z);

  Float_t aC[3] = {5E-6,8E-6,2E-5};
  Float_t uC[3] = {5.5625,2.2667,0.4039};
  //  TGraph *g2 = new TGraph(3,aC,uC);

  Float_t aCz[2] = {1E-5,5E-5};
  Float_t uCz[2] = {6.5938,0.3555};
  //  TGraph *g2z = new TGraph(2,aCz,uCz);

  // WW bands
  Float_t x0green[6]; Float_t x0yellow[6]; 
  Float_t y0green[6]; Float_t y0yellow[6];
  Float_t xCgreen[6]; Float_t xCyellow[6];
  Float_t yCgreen[6]; Float_t yCyellow[6];
  // ZZ bands                                                                                                                                                                                                 
  Float_t x0greenZ[4]; Float_t x0yellowZ[4];
  Float_t y0greenZ[4]; Float_t y0yellowZ[4];
  Float_t xCgreenZ[4]; Float_t xCyellowZ[4];
  Float_t yCgreenZ[4]; Float_t yCyellowZ[4];

  for(Int_t i = 0; i < 5; i++)
    {
      ta0w1->GetEntry(i);
      //      ta0w2->GetEntry(i);
      ta0w3->GetEntry(i);
      taCw1->GetEntry(i);
      //      taCw2->GetEntry(i);
      taCw3->GetEntry(i);
      ta0z1->GetEntry(i);
      ta0z2->GetEntry(i);
      taCz1->GetEntry(i);
      taCz2->GetEntry(i);
  
      if(i == 0)
	{
	  y0yellow[0] = la0w1;
	  y0yellow[1] = la0w2;
	  y0yellow[2] = la0w3;
	  yCyellow[0] = laCw1;
	  yCyellow[1] = laCw2;
	  yCyellow[2] = laCw3;
	  y0yellowZ[0] = la0z1;
	  y0yellowZ[1] = la0z2;
	  yCyellowZ[0] = laCz1;
	  yCyellowZ[1] = laCz2;
	}
      if(i == 1)
	{
	  y0green[0] = la0w1;
	  y0green[1] = la0w2;
	  y0green[2] = la0w3;
          yCgreen[0] = laCw1;
          yCgreen[1] = laCw2;
          yCgreen[2] = laCw3;
          y0greenZ[0] = la0z1;
          y0greenZ[1] = la0z2;
          yCgreenZ[0] = laCz1;
          yCgreenZ[1] = laCz2;
	}
      if(i == 2)
	{
	  u0[0] = la0w1;
	  u0[1] = la0w2;
          u0[2] = la0w3;
          uC[0] = laCw1;
          uC[1] = laCw2;
          uC[2] = laCw3;
          u0z[0] = la0z1;
          u0z[1] = la0z2;
          uCz[0] = laCz1;
          uCz[1] = laCz2;
	}
      if(i == 3)
	{
	  y0green[3] = la0w3;
          y0green[4] = la0w2;
          y0green[5] = la0w1;
          yCgreen[3] = laCw3;
          yCgreen[4] = laCw2;
          yCgreen[5] = laCw1;
          y0greenZ[2] = la0z2;
          y0greenZ[3] = la0z1;
          yCgreenZ[2] = laCz2;
          yCgreenZ[3] = laCz1;
	}
      if(i == 4)
        {
          y0yellow[3] = la0w3;
          y0yellow[4] = la0w2;
          y0yellow[5] = la0w1;
          yCyellow[3] = laCw3;
          yCyellow[4] = laCw2;
          yCyellow[5] = laCw1;
          y0yellowZ[2] = la0z2;
          y0yellowZ[3] = la0z1;
          yCyellowZ[2] = laCz2;
          yCyellowZ[3] = laCz1;
	}
    }      
  
  for(Int_t j = 0; j < 3; j++)
    {
      x0green[j] = a0[j];
      x0yellow[j] = a0[j];
      xCgreen[j] = aC[j];
      xCyellow[j] = aC[j];
      x0green[5-j] = a0[j];
      x0yellow[5-j] = a0[j];
      xCgreen[5-j] = aC[j];
      xCyellow[5-j] = aC[j];


      if(j < 2)
	{
	  x0greenZ[j] = a0z[j];
	  x0yellowZ[j] = a0z[j];
	  xCgreenZ[j] = aCz[j];
	  xCyellowZ[j] = aCz[j];
	  x0greenZ[3-j] = a0z[j];
          x0yellowZ[3-j] = a0z[j];
          xCgreenZ[3-j] = aCz[j];
          xCyellowZ[3-j] = aCz[j];

	}
    }

  TGraph *g1 = new TGraph(3,a0,u0);
  TGraph *g1z = new TGraph(2,a0z,u0z);
  TGraph *g2 = new TGraph(3,aC,uC);
  TGraph *g2z = new TGraph(2,aCz,uCz);

  TGraph *a0greenbox = new TGraph(6,x0green,y0green);
  a0greenbox->SetFillColor(3); a0greenbox->SetLineColor(3);
  TGraph *a0yellowbox = new TGraph(6,x0yellow,y0yellow);
  a0yellowbox->SetFillColor(5); a0yellowbox->SetLineColor(5);

  TGraph *aCgreenbox = new TGraph(6,xCgreen,yCgreen);
  aCgreenbox->SetFillColor(3); aCgreenbox->SetLineColor(3);
  TGraph *aCyellowbox = new TGraph(6,xCyellow,yCyellow);
  aCyellowbox->SetFillColor(5); aCyellowbox->SetLineColor(5);

  TGraph *a0greenZbox = new TGraph(4,x0greenZ,y0greenZ);
  a0greenZbox->SetFillColor(3); a0greenZbox->SetLineColor(3);
  TGraph *a0yellowZbox = new TGraph(4,x0yellowZ,y0yellowZ);
  a0yellowZbox->SetFillColor(5); a0yellowZbox->SetLineColor(5);

  TGraph *aCgreenZbox = new TGraph(4,xCgreenZ,yCgreenZ);
  aCgreenZbox->SetFillColor(3); aCgreenZbox->SetLineColor(3);
  TGraph *aCyellowZbox = new TGraph(4,xCyellowZ,yCyellowZ);
  aCyellowZbox->SetFillColor(5); aCyellowZbox->SetLineColor(5);


  TCanvas *c1 = new TCanvas("c1","c1",1000,600);
  c1->Divide(2,2);

  c1->cd(1);

  TH2F *haxis0 = new TH2F("haxis0","haxis0",2,0.9E-6,5E-6,2,0,25);
  TH2F *haxisC = new TH2F("haxisC","haxisC",2,4.9E-6,2E-5,2,0,15);
  TH2F *haxis0Z = new TH2F("haxis0Z","haxis0Z",2,0.9E-5,5E-5,2,0,5);
  TH2F *haxisCZ = new TH2F("haxisCZ","haxisCZ",2,0.9E-5,5E-5,2,0,25);


  haxis0->SetXTitle("a^{0}_{W}/#Lambda^{2}");
  haxis0->SetYTitle("#sigma/#sigma_{AQGC}");
  haxis0->Draw();
  haxis0->GetYaxis()->SetTitleOffset(0.8);
  haxis0->GetXaxis()->SetTitleOffset(0.8);
  haxis0->GetYaxis()->SetTitleSize(0.05);
  haxis0->GetXaxis()->SetTitleSize(0.05);

  a0yellowbox->Draw("fsame");
  a0greenbox->Draw("fsame");
  g1->Draw("LPsame");


  TLine *l1 = new TLine(0.9E-6,1,5E-6,1);
  l1->SetLineWidth(3); l1->SetLineStyle(2); l1->Draw("same");

  c1->cd(2);

  haxisC->SetXTitle("a^{C}_{W}/#Lambda^{2}");
  haxisC->SetYTitle("#sigma/#sigma_{AQGC}");
  haxisC->GetYaxis()->SetTitleOffset(0.8); 
  haxisC->GetXaxis()->SetTitleOffset(0.8);
  haxisC->GetYaxis()->SetTitleSize(0.05);
  haxisC->GetXaxis()->SetTitleSize(0.05);

  haxisC->Draw();

  aCyellowbox->Draw("fsame");
  aCgreenbox->Draw("fsame");
  g2->Draw("LPsame");

  TLine *l2 = new TLine(4.9E-6,1,2E-5,1);
  l2->SetLineWidth(3); l2->SetLineStyle(2); l2->Draw("same");
  l2->Draw("same");

  CMS_lumi2016((TPad*)c1->GetPad(1),0,0,"2016+2017+2018, L = 100.1 fb^{-1}");

  c1->cd(3);

  haxis0Z->SetXTitle("a^{0}_{Z}/#Lambda^{2}");
  haxis0Z->SetYTitle("#sigma/#sigma_{AQGC}");
  haxis0Z->Draw();
  haxis0Z->GetYaxis()->SetTitleOffset(0.8);
  haxis0Z->GetXaxis()->SetTitleOffset(0.8);
  haxis0Z->GetYaxis()->SetTitleSize(0.05);
  haxis0Z->GetXaxis()->SetTitleSize(0.05);

  a0yellowZbox->Draw("fsame");
  a0greenZbox->Draw("fsame");
  g1z->Draw("LPsame");

  TLine *l3 = new TLine(0.9E-5,1,5E-5,1);
  l3->SetLineWidth(3); l3->SetLineStyle(2); l3->Draw("same");

  c1->cd(4);

  haxisCZ->SetXTitle("a^{C}_{Z}/#Lambda^{2}");
  haxisCZ->SetYTitle("#sigma/#sigma_{AQGC}");
  haxisCZ->Draw();
  haxisCZ->GetYaxis()->SetTitleOffset(0.8);
  haxisCZ->GetXaxis()->SetTitleOffset(0.8);
  haxisCZ->GetYaxis()->SetTitleSize(0.05);
  haxisCZ->GetXaxis()->SetTitleSize(0.05);

  aCyellowZbox->Draw("fsame");
  aCgreenZbox->Draw("fsame");
  g2z->Draw("LPsame");

  TLine *l4 = new TLine(0.9E-5,1,5E-5,1);
  l4->SetLineWidth(3); l4->SetLineStyle(2); l4->Draw("same");
}


