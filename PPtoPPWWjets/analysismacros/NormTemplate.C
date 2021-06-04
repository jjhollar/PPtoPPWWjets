void NormTemplate(int region = 1, int year = 2016, int channel = 1)
{
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPalette(105);

  TFile *f1;
  if(year == 2016)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
    f1 = TFile::Open("/eos/cms/store/group/phys_smp/HadronicVV/dataRun2_v3/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
  if(year == 2017)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
    f1 = TFile::Open("/eos/cms/store/group/phys_smp/HadronicVV/dataRun2/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  if(year == 2018)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");
    f1 = TFile::Open("/eos/cms/store/group/phys_smp/HadronicVV/dataRun2/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");


  //  TFile *f2 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w2point0noPUprotons_withFiducialAndKillingjetxicuts.root");

  //  TH1F *hsigmc = (TH1F *)f2->Get("hmassmatchratiosigmcmult");
  
  Float_t massmatchcut = 0.11506000/2.0;
  Float_t rapmatchcut  = 0.057220000/2.0;
  //  Float_t rapmatchcut = 0.03;
  //  Float_t massmatchcut = 0.06;

  //  TH2F *hatemplate = (TH2F *)f1->Get("hmassrapiditymatchantiacopmm");
  TH2F *hatemplate;
  TH2F *hsideband;

  if((region == 1 || region == 0) && (channel == 1))
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmww");
  if(region == 2 && channel == 1)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummww");
  if(region == 3 && channel == 1)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmww");
  if(region == 4 && channel == 1)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiptbalmmww");
  if(region == 5 && channel == 1)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunednarrozzmw");

  if((region == 1 || region == 0) && (channel == 2))
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmzz");
  if(region == 2 && channel == 2)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummzz");
  if(region == 3 && channel == 2)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmzz");
  if(region == 4 && channel == 2)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiptbalmmzz");
  if(region == 5 && channel == 2)
    hatemplate = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunednarrozzmzz");
  
  if(channel == 1)
    hsideband = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchvetoorsignalregionww");
  if(channel == 2)
    hsideband = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchvetoorsignalregionzz");


  std::cout << "JH: hmassrapiditymatchvetoorsignalregion has entries = " << hsideband->GetEntries() << std::endl;

  Float_t extrapolatedsigbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1),hatemplate->GetXaxis()->FindBin(1), hatemplate->GetYaxis()->FindBin(-0.5), hatemplate->GetYaxis()->FindBin(0.5));
  Float_t extraplotedtightsigbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1*2*massmatchcut),hatemplate->GetXaxis()->FindBin(1*2*massmatchcut), hatemplate->GetYaxis()->FindBin(-1*2*rapmatchcut), hatemplate->GetYaxis()->FindBin(1*2*rapmatchcut));
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
  Float_t scaledextrapolatedsignalbox = hatemplate->Integral(hatemplate->GetXaxis()->FindBin(-1*2*massmatchcut),hatemplate->GetXaxis()->FindBin(1*2*massmatchcut), hatemplate->GetYaxis()->FindBin(-1*2*rapmatchcut), hatemplate->GetYaxis()->FindBin(1*2*rapmatchcut));
  Float_t scaledntemplate = hatemplate->GetSumOfWeights() - scaledextrapolatedsignalbox;

  //  Float_t staterr = TMath::Sqrt(scaledextrapolatedsignalbox/scalefactor)*scalefactor;

  Float_t staterr = TMath::Sqrt((extraplotedtightsigbox/(extraplotedtightsigbox*extraplotedtightsigbox)) + 
				(nsideband/(nsideband*nsideband)) + 
				(ntemplate/(ntemplate*ntemplate)))*(extraplotedtightsigbox*nsideband/ntemplate);


  std::cout << "Total anti-cut = " << hatemplate->GetSumOfWeights() << std::endl
	    << "Sideband anti-cut = " << scaledntemplate << std::endl 
	    << "Sideband passing signal cuts = " << nsideband << std::endl
	    << "Scale factor = " << scalefactor << std::endl
            << "Signal box anti-cut = " << scaledextrapolatedsignalbox << " +- " << staterr << std::endl;


  if(channel == 1)
    {
      hsideband->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
      hsideband->SetYTitle("y(pp) - y(W_{j} W_{j})");
      hsideband->SetStats(0);
      hatemplate->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
      hatemplate->SetYTitle("y(pp) - y(W_{j} W_{j})");
    }
  if(channel == 2)
    {
      hsideband->SetXTitle("1 - m(Z_{j} Z_{j})/m(pp)");
      hsideband->SetYTitle("y(pp) - y(Z_{j} Z_{j})");
      hsideband->SetStats(0);
      hatemplate->SetXTitle("1 - m(Z_{j} Z_{j})/m(pp)");
      hatemplate->SetYTitle("y(pp) - y(Z_{j} Z_{j})");
    }
  hatemplate->SetStats(0);

  TCanvas *c1 = new TCanvas("c1","c1");


  if(year == 2016)
    {
      hsideband->SetTitle("2016, 9.9 fb^{-1}");
      if(region == 1)
        hatemplate->SetTitle("2016, 9.9 fb^{-1}, anti-acoplanarity");
      if(region == 3)
        hatemplate->SetTitle("2016, 9.9 fb^{-1}, anti-#tau_{21}");
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


  //  hatemplate->Rebin2D(4,4);
  hatemplate->Rebin2D(4,4);
  hsideband->Rebin2D(4,4);
  hatemplate->GetXaxis()->SetRangeUser(-3,3);
  hatemplate->GetYaxis()->SetRangeUser(-1.5,1.5);
  hatemplate->GetXaxis()->SetLabelSize(0.06);
  hatemplate->GetYaxis()->SetLabelSize(0.06);
  hatemplate->GetXaxis()->SetTitleSize(0.065); 
  hatemplate->GetYaxis()->SetTitleSize(0.065);
  hatemplate->GetXaxis()->SetTitleOffset(1);
  hatemplate->GetYaxis()->SetTitleOffset(1);
  hatemplate->GetZaxis()->SetLabelSize(0.06);
  hatemplate->SetMaximum(20.0);
  hatemplate->Draw("colz");
  //  hsideband->Rebin2D(4,4);
  hsideband->GetXaxis()->SetRangeUser(-3,3);
  hsideband->GetYaxis()->SetRangeUser(-1.5,1.5);
  hsideband->GetXaxis()->SetLabelSize(0.06);
  hsideband->GetYaxis()->SetLabelSize(0.06);
  hsideband->GetXaxis()->SetTitleSize(0.065);
  hsideband->GetYaxis()->SetTitleSize(0.065);
  hsideband->GetXaxis()->SetTitleOffset(1);
  hsideband->GetYaxis()->SetTitleOffset(1);
  hsideband->SetMaximum(20);

  if(region == 0)
    {
      hsideband->Draw("colz");
      hsideband->GetZaxis()->SetLabelSize(0.06);
    }
  TBox *b1 = new TBox(-0.10,-0.06,0.10,0.06);
  b1->SetLineColor(2); b1->SetLineWidth(3); b1->SetFillStyle(0); // b1->Draw("same");
  TBox *b2 = new TBox(-1,-0.5,1,0.5);
  b2->SetLineColor(2); b2->SetLineWidth(3); b2->SetLineStyle(2); b2->SetFillStyle(0); b2->Draw("same");

  if(year == 2016)
    {
      CMS_lumi2016(c1,0,0,"2016, L = 9.9 fb^{-1}");
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
      TString cmsText     = "#scale[0.76]{#font[52]{anti-pruned mass region}}";
      latex.DrawLatexNDC(l+0.05,1-t-0.5*t,cmsText);
    }
  if(region == 2)
    {
      TString cmsText     = "#scale[0.76]{#font[52]{anti-#tau_{21, DDT} region}}";
      latex.DrawLatexNDC(l+0.05,1-t-0.5*t,cmsText);
    }

  //  hsigmc->SetMarkerStyle(20); hsigmc->SetLineWidth(3);
  //  hsigmc->Draw("esame");

  /*
   * New Andrea regions
   */
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

  l1->SetLineColor(2); l1->SetLineWidth(3); l1->Draw();
  l2->SetLineColor(2); l2->SetLineWidth(3); l2->Draw("same");
  l3->SetLineColor(2); l3->SetLineWidth(3); l3->Draw("same");
  l4->SetLineColor(2);l4->SetLineWidth(3); l4->Draw("same");
  /*
  l5->SetLineColor(2); l5->SetLineWidth(3); l5->Draw("same");
  l6->SetLineColor(2); l6->SetLineWidth(3); l6->Draw("same");
  l7->SetLineColor(2); l7->SetLineWidth(3); l7->Draw("same");
  l8->SetLineColor(2); l8->SetLineWidth(3); l8->Draw("same");
  */
  l9->SetLineColor(2); l9->SetLineWidth(3); l9->Draw("same");
  l10->SetLineColor(2); l10->SetLineWidth(3); l10->Draw("same");
  l11->SetLineColor(2); l11->SetLineWidth(3); l11->Draw("same");
  l12->SetLineColor(2); l12->SetLineWidth(3); l12->Draw("same");
  /*
  l13->SetLineColor(2); l13->SetLineWidth(3); l13->Draw("same");
  l14->SetLineColor(2); l14->SetLineWidth(3); l14->Draw("same");
  l15->SetLineColor(2); l15->SetLineWidth(3); l15->Draw("same");
  l16->SetLineColor(2); l16->SetLineWidth(3); l16->Draw("same");
  */
  l17->SetLineColor(2); l17->SetLineWidth(3); l17->Draw("same");
  l18->SetLineColor(2); l18->SetLineWidth(3); l18->Draw("same");
  l19->SetLineColor(2); l19->SetLineWidth(3); l19->Draw("same");
  l20->SetLineColor(2); l20->SetLineWidth(3); l20->Draw("same");


}
