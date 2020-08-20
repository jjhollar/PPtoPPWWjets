void NormTemplate(int region = 1, int year = 2016)
{
  TFile *f1;
  if(year == 2017)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  if(year == 2016)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
  if(year == 2018)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");


  //  TFile *f2 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w2point0noPUprotons_withFiducialAndKillingjetxicuts.root");

  //  TH1F *hsigmc = (TH1F *)f2->Get("hmassmatchratiosigmcmult");
  
  //  TH2F *hatemplate = (TH2F *)f1->Get("hmassrapiditymatchantiacopmm");
  TH2F *hatemplate;
  if(region == 1 || region == 0)
    hatemplate = (TH2F *)f1->Get("hmassrapiditymatchantiacopmm");
  if(region == 2)
    hatemplate = (TH2F *)f1->Get("hmassrapiditymatchantiptbalmm");
  if(region == 3)
    hatemplate = (TH2F *)f1->Get("hmassrapiditymatchantitaumm");

  TH2F *hsideband = (TH2F *)f1->Get("hmassrapiditymatchvetoorsignalregion");
  std::cout << "JH: hmassrapiditymatchvetoorsignalregion has entries = " << hsideband->GetEntries() << std::endl;

  Float_t extrapolatedsigbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1),hatemplate->GetXaxis()->FindBin(1), hatemplate->GetYaxis()->FindBin(-0.5), hatemplate->GetYaxis()->FindBin(0.5));
  Float_t extraplotedtightsigbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1*2*0.06),hatemplate->GetXaxis()->FindBin(1*2*0.06), hatemplate->GetYaxis()->FindBin(-1*2*0.03), hatemplate->GetYaxis()->FindBin(1*2*0.03));
  Float_t ntemplate = hatemplate->GetSumOfWeights() - extrapolatedsigbox;
  Float_t nsideband = hsideband->GetSumOfWeights();

  std::cout << "Raw anti-cut blinded region = " << extrapolatedsigbox << std::endl
	    << "Raw anti-cut sideband = " << ntemplate << std::endl
	    << "Raw anti-cut signal box = " << extraplotedtightsigbox << std::endl
	    << "Raw signal cuts sideband = " << nsideband << std::endl << std::endl;

  hatemplate->Sumw2();
  // Scale anti-cut sideband region to signal sideband region
  hatemplate->Scale(nsideband/ntemplate);
  Float_t scalefactor = nsideband/ntemplate;
  Float_t scaledextrapolatedsignalbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1*2*0.06),hatemplate->GetXaxis()->FindBin(1*2*0.06), hatemplate->GetYaxis()->FindBin(-1*2*0.03), hatemplate->GetYaxis()->FindBin(1*2*0.03));
  Float_t scaledntemplate = hatemplate->GetSumOfWeights() - scaledextrapolatedsignalbox;

  //  Float_t staterr = TMath::Sqrt(scaledextrapolatedsignalbox/scalefactor)*scalefactor;

  Float_t staterr = TMath::Sqrt((extraplotedtightsigbox/(extraplotedtightsigbox*extraplotedtightsigbox)) + 
				(nsideband/(nsideband*nsideband)) + 
				(ntemplate/(ntemplate*ntemplate)))*(extraplotedtightsigbox*nsideband/ntemplate);


  std::cout << "Total anti-cut = " << hatemplate->GetSumOfWeights() << std::endl
	    << "Sideband anti-cut = " << scaledntemplate << std::endl 
	    << "Signal selection sideband = " << nsideband << std::endl
	    << "Scale factor = " << scalefactor << std::endl
            << "Signal box anti-cut = " << scaledextrapolatedsignalbox << " +- " << staterr << std::endl;


  hsideband->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
  hsideband->SetYTitle("y(pp) - y(W_{j} W_{j})");
  hsideband->SetStats(0);
  hatemplate->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
  hatemplate->SetYTitle("y(pp) - y(W_{j} W_{j})");
  hatemplate->SetStats(0);

  TCanvas *c1 = new TCanvas("c1","c1");


  if(year == 2016)
    {
      hsideband->SetTitle("2016, 10.0 fb^{-1}");
      if(region == 1)
        hatemplate->SetTitle("2016, 10.0 fb^{-1}, anti-acoplanarity");
      if(region == 3)
        hatemplate->SetTitle("2016, 10.0 fb^{-1}, anti-#tau_{21}");
    }
  if(year == 2017)
    {
      hsideband->SetTitle("2017, 37.2 fb^{-1}");
      if(region == 1)
	hatemplate->SetTitle("2017, 37.2 fb^{-1}, anti-acoplanarity");
      if(region == 3)
	hatemplate->SetTitle("2017, 37.2 fb^{-1}, anti-#tau_{21}");
    }
  if(year == 2018)
    {
      hsideband->SetTitle("2018, 52.9 fb^{-1}");
      if(region == 1)
        hatemplate->SetTitle("2018, 52.9 fb^{-1}, anti-acoplanarity");
      if(region == 3)
        hatemplate->SetTitle("2018, 52.9 fb^{-1}, anti-#tau_{21}");
    }


  hatemplate->Rebin2D(4,4);
  hatemplate->GetXaxis()->SetRangeUser(-3,3);
  hatemplate->GetYaxis()->SetRangeUser(-1.5,1.5);
  hatemplate->GetXaxis()->SetTitleSize(0.04); 
  hatemplate->GetYaxis()->SetTitleSize(0.04);
  hatemplate->GetXaxis()->SetTitleOffset(1.2);
  hatemplate->GetYaxis()->SetTitleOffset(1.2);

  hatemplate->SetMaximum(20.0);
  hatemplate->Draw("colz");
  hsideband->Rebin2D(4,4);
  hsideband->GetXaxis()->SetRangeUser(-3,3);
  hsideband->GetYaxis()->SetRangeUser(-1.5,1.5);
  hsideband->SetMaximum(20);

  if(region == 0)
    hsideband->Draw("colz");
  
  TBox *b1 = new TBox(-0.10,-0.06,0.10,0.06);
  b1->SetLineColor(2); b1->SetLineWidth(3); b1->SetFillStyle(0); b1->Draw("same");
  TBox *b2 = new TBox(-1,-0.5,1,0.5);
  b2->SetLineColor(2); b2->SetLineWidth(3); b2->SetLineStyle(2); b2->SetFillStyle(0); b2->Draw("same");

  if(year == 2016)
    {
      CMS_lumi2016(c1,0,0,"2016, L = 10.0 fb^{-1}");
    }
  if(year == 2017)
    {
      CMS_lumi2016(c1,0,0,"2017, L = 37.2 fb^{-1}");
    }
  if(year == 2018)
    {
      CMS_lumi2016(c1,0,0,"2018, L = 52.9 fb^{-1}");
    }      

  TLatex latex;
  float l = gPad->GetLeftMargin();
  float t = gPad->GetTopMargin();
  latex.SetTextAlign(11);
  latex.SetTextSize(0.6*t);

  if(region == 0)
    {
      TString cmsText     = "#scale[0.76]{#font[52]{Normalization region}}";
      latex.DrawLatexNDC(l+0.05,1-t-0.5*t,cmsText);
    }
  if(region == 1)
    {
      TString cmsText     = "#scale[0.76]{#font[52]{anti-acoplanarity region}}";
      latex.DrawLatexNDC(l+0.05,1-t-0.5*t,cmsText);                                                                                                                          
    }
  if(region == 3)
    {
      TString cmsText     = "#scale[0.76]{#font[52]{anti-#tau_{21, DDT} region}}";
      latex.DrawLatexNDC(l+0.05,1-t-0.5*t,cmsText);
    }


  //  hsigmc->SetMarkerStyle(20); hsigmc->SetLineWidth(3);
  //  hsigmc->Draw("esame");



}
