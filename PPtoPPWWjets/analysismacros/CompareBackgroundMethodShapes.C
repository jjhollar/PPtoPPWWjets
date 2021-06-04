void CompareBackgroundMethodShapes(int var = 1, int sigcuts = 0, int year = 2016, int channel = 1)
{
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);

  TFile *f1;
  if(year == 2016)
    f1 = TFile::Open("/eos/cms/store/group/phys_smp/HadronicVV/dataRun2_v3/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
  if(year == 2017)
     f1 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  if(year == 2018)
    f1 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");

  TFile *f2 = TFile::Open("EventMixingOutputHistosNewAndrea.root");
  TH2F *h1, *h2, *h4;

  if(channel == 1)
    {
      h1 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmww");
      h2 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummww");
      h4 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmww");
    }
  if(channel == 2)
    {
      h1 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmzz");
      h2 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummzz");
      h4 = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmzz");
    }
  TH2F *h3; 
  if(year == 2016 && channel == 1)
    h3 = (TH2F *)f2->Get("hmresdysum2016ww");
  if(year == 2017 && channel == 1)
    h3 = (TH2F *)f2->Get("hmresdysum2017ww");
  if(year == 2018 && channel == 1)
    h3 = (TH2F *)f2->Get("hmresdysum2018ww");

  if(year == 2016 && channel == 2)
    h3 = (TH2F *)f2->Get("hmresdysum2016zz");
  if(year == 2017 && channel == 2)
    h3 = (TH2F *)f2->Get("hmresdysum2017zz");
  if(year == 2018 && channel == 2)
    h3 = (TH2F *)f2->Get("hmresdysum2018zz");


  // JH - use THIS!
  h2->Rebin2D(4,4);
  h1->Rebin2D(4,4);
  h4->Rebin2D(4,4);

  float acopscale = 0.0; float tauscale = 0.0; float massscale = 0.0;
  /*
  if(year == 2016 && channel == 1) {acopscale = 0.4375; tauscale = 0.5833; massscale = 0.00498575;}
  if(year == 2017 && channel == 1) {acopscale = 0.54386; tauscale = 0.553571; massscale = 0.00540823;}
  if(year == 2018 && channel == 1) {acopscale = 0.502392; tauscale = 0.542636; massscale = 0.0051463;}

  if(year == 2016 && channel == 2) {acopscale = 0.727273; tauscale = 1; massscale = 0.0223464;}
  if(year == 2017 && channel == 2) {acopscale = 0.322034; tauscale = 0.527778; massscale = 0.0138383;}
  if(year == 2018 && channel == 2) {acopscale = 0.519637; tauscale = 0.5375; massscale = 0.0175171;}
  */

  // These are the ratio of the # of events in the normalization region to the anti-cut normalization region
  if(year == 2016 && channel == 1) {acopscale = 0.4118; tauscale = 0.5833; massscale = 0.00483;}                        
  if(year == 2017 && channel == 1) {acopscale = 0.5254; tauscale = 0.5439; massscale = 0.00523;}                     
  if(year == 2018 && channel == 1) {acopscale = 0.48165; tauscale = 0.53299; massscale = 0.00499;}                     

  if(year == 2016 && channel == 2) {acopscale = 0.667; tauscale = 1; massscale = 0.0215;}                            
  if(year == 2017 && channel == 2) {acopscale = 0.3115; tauscale = 0.5; massscale = 0.01352;}                     
  if(year == 2018 && channel == 2) {acopscale = 0.50588; tauscale = 0.52121; massscale = 0.01697;}                       

  Float_t kseniammatchcut = 0.11506000;
  Float_t kseniarapmatchcut = 0.057220000;

  // Maximum points of the diamond
  Float_t andreammatchcutmin = -0.104;
  Float_t andreammatchcutmax = 0.085;
  Float_t andrearapmatchcutmin = -0.084;
  Float_t andrearapmatchcutmax = 0.073;

  TH1F *hacopm = (TH1F *)h1->ProjectionX();
  TH1F *htaum = (TH1F *)h2->ProjectionX();
  TH1F *hprunedm = (TH1F *)h4->ProjectionX();
  TH1F *hmixm = (TH1F *)h3->ProjectionX();

  /*
  int ybinlo = h1->GetYaxis()->FindBin(-1.0*kseniarapmatchcut);
  int ybinhi = h1->GetYaxis()->FindBin(1.0*kseniarapmatchcut);
  int xbinlo = h1->GetXaxis()->FindBin(-1.0*kseniammatchcut);
  int xbinhi = h1->GetXaxis()->FindBin(1.0*kseniammatchcut);
  */
  int ybinlo = h1->GetYaxis()->FindBin(-1.0*andrearapmatchcutmin); 
  int ybinhi = h1->GetYaxis()->FindBin(1.0*andrearapmatchcutmax);                                                                                               
  int xbinlo = h1->GetXaxis()->FindBin(-1.0*andreammatchcutmin);
  int xbinhi = h1->GetXaxis()->FindBin(1.0*andreammatchcutmax);                                                                                                 
  
  if(var == 1)
    {
      if(sigcuts == 1)
	{
	  hacopm = (TH1F *)h1->ProjectionX("acopm",ybinlo,ybinhi);
	  htaum = (TH1F *)h2->ProjectionX("taum",ybinlo,ybinhi);
	  hmixm = (TH1F *)h3->ProjectionX("mixm",ybinlo,ybinhi);
	  hprunedm = (TH1F *)h4->ProjectionX("prunedm",ybinlo,ybinhi);
	}
    }

  if(var == 2)
    {
      hacopm = (TH1F *)h1->ProjectionY();
      htaum = (TH1F *)h2->ProjectionY();
      hmixm = (TH1F *)h3->ProjectionY();
      hprunedm = (TH1F *)h4->ProjectionY();

      if(sigcuts == 1)
        {
          hacopm = (TH1F *)h1->ProjectionY("acopm",xbinlo,xbinhi);
          htaum = (TH1F *)h2->ProjectionY("taum",xbinlo,xbinhi);
          hmixm = (TH1F *)h3->ProjectionY("mixm",xbinlo,xbinhi);
	  hprunedm = (TH1F *)h4->ProjectionY("prunedm",xbinlo,xbinhi);
        }
    }
  
  Int_t rebinfact = 5;
  //  rebinfact = 2;
  //  rebinfact = 20;

  //  hacopm->Rebin(rebinfact);
  //  htaum->Rebin(rebinfact);
  //  hmixm->Rebin(rebinfact);
  //  hprunedm->Rebin(rebinfact);

  /*
  if(var == 2)
    {
      hacopm->Rebin(2);
      htaum->Rebin(2);
      hmixm->Rebin(2);
    }
  */

  hacopm->Sumw2(); hacopm->Scale(acopscale); hacopm->SetFillColor(2); hacopm->SetFillStyle(3001); hacopm->SetMarkerStyle(0);
  htaum->Sumw2(); htaum->Scale(tauscale); htaum->SetFillColor(4); htaum->SetFillStyle(3001); htaum->SetMarkerStyle(0); 
  hprunedm->Sumw2(); hprunedm->Scale(massscale); hprunedm->SetFillColor(3); hprunedm->SetFillStyle(3001); hprunedm->SetMarkerStyle(0);
  hmixm->SetFillColor(1);  hmixm->SetMarkerStyle(0);

  htaum->GetXaxis()->SetRangeUser(-2,2);

  htaum->GetXaxis()->SetLabelSize(0.07);
  htaum->GetYaxis()->SetLabelSize(0.07);
  htaum->GetXaxis()->SetTitleSize(0.065);
  htaum->GetYaxis()->SetTitleSize(0.065);
  htaum->GetXaxis()->SetTitleOffset(1.0);
  htaum->GetYaxis()->SetTitleOffset(1.0);
  htaum->GetZaxis()->SetLabelSize(0.06);

  htaum->SetYTitle("Events");

  if(sigcuts == 0)
    {
      htaum->SetMaximum(200);
      if(year == 2016) htaum->SetMaximum(25);
      if(year == 2017) htaum->SetMaximum(50);
    }
  if(sigcuts == 1)
    {
      //      htaum->SetMaximum(100);
      htaum->SetMaximum(50);
      if(year == 2016) htaum->SetMaximum(10); // htaum->SetMaximum(15);
      if(year == 2017) htaum->SetMaximum(15); // htaum->SetMaximum(25);
    }

  if(channel == 1)
    {
      htaum->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
      if(var == 2)
	htaum->SetXTitle("y(pp) - y(W_{j} W_{j})");
    }
  if(channel == 2)
    {
      htaum->SetXTitle("1 - m(Z_{j} Z_{j})/m(pp)");
      if(var == 2)
        htaum->SetXTitle("y(pp) - y(Z_{j} Z_{j})");
    }
  TCanvas *c1 = new TCanvas("c1","c1");

  htaum->Draw("E2");
  hacopm->Draw("E2same");
  hprunedm->Draw("E2same");
  hmixm->Draw("E2same");

  TLegend *l1 = new TLegend(0.15,0.6,0.55,0.9);
  l1->AddEntry(hacopm,"Anti-acoplanarity sample");
  l1->AddEntry(htaum,"Anti-tau21 sample");
  l1->AddEntry(hprunedm,"Anti-pruned mass sample");
  l1->AddEntry(hmixm,"Event mixing");
  l1->Draw("same");

  if(year == 2016)
    {
      CMS_lumi2016(c1,0,0,"2016, L = 9.9 fb^{-1}");
      if(channel == 1 && sigcuts == 0 && var == 1)
	c1->SaveAs("MassMatchCompareBkgs2016WW.pdf");
      if(channel == 1 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2016WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 1)
	c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2016WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 2)
	c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2016WW.pdf");
      if(channel == 2 && sigcuts == 0 && var == 1)
        c1->SaveAs("MassMatchCompareBkgs2016ZZ.pdf");
      if(channel == 2 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2016ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 1)
        c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2016ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2016ZZ.pdf");

    }
  if(year == 2017)
    {
      CMS_lumi2016(c1,0,0,"2017, L = 37.2 fb^{-1}");
      if(channel == 1 && sigcuts == 0 && var == 1)
        c1->SaveAs("MassMatchCompareBkgs2017WW.pdf");
      if(channel == 1 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2017WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 1)
        c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2017WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2017WW.pdf");
      if(channel == 2 && sigcuts == 0 && var == 1)
        c1->SaveAs("MassMatchCompareBkgs2017ZZ.pdf");
      if(channel == 2 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2017ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 1)
        c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2017ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2017ZZ.pdf");

    }
  if(year == 2018)
    {
      CMS_lumi2016(c1,0,0,"2018, L = 52.9 fb^{-1}");
      if(channel == 1 && sigcuts == 0 && var == 1)
        c1->SaveAs("MassMatchCompareBkgs2018WW.pdf");
      if(channel == 1 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2018WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 1)
        c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2018WW.pdf");
      if(channel == 1 && sigcuts == 1 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2018WW.pdf");
      if(channel == 2 && sigcuts == 0 && var == 1)
        c1->SaveAs("MassMatchCompareBkgs2018ZZ.pdf");
      if(channel == 2 && sigcuts == 0 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgs2018ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 1)
        c1->SaveAs("MassMatchCompareBkgsRapiditySignalCuts2018ZZ.pdf");
      if(channel == 2 && sigcuts == 1 && var == 2)
        c1->SaveAs("RapidityMatchCompareBkgsMassSignalCuts2018ZZ.pdf");

    }

}


void AllCompareBackgroundMethodShapes()
{
  //  int var = 1, int sigcuts = 0, int year = 2017, int channel = 1
  
  // WW, all
  CompareBackgroundMethodShapes(1,0,2016,1);
  CompareBackgroundMethodShapes(1,0,2017,1);
  CompareBackgroundMethodShapes(1,0,2018,1);
  CompareBackgroundMethodShapes(2,0,2016,1);
  CompareBackgroundMethodShapes(2,0,2017,1);
  CompareBackgroundMethodShapes(2,0,2018,1);
  // WW, sig cuts
  CompareBackgroundMethodShapes(1,1,2016,1);
  CompareBackgroundMethodShapes(1,1,2017,1);
  CompareBackgroundMethodShapes(1,1,2018,1);
  CompareBackgroundMethodShapes(2,1,2016,1);
  CompareBackgroundMethodShapes(2,1,2017,1);
  CompareBackgroundMethodShapes(2,1,2018,1);
  // ZZ, all                                                                                                                                                    
  CompareBackgroundMethodShapes(1,0,2016,2);
  CompareBackgroundMethodShapes(1,0,2017,2);
  CompareBackgroundMethodShapes(1,0,2018,2);
  CompareBackgroundMethodShapes(2,0,2016,2);
  CompareBackgroundMethodShapes(2,0,2017,2);
  CompareBackgroundMethodShapes(2,0,2018,2);
  // ZZ, sig cuts                                                                                                                                               
  CompareBackgroundMethodShapes(1,1,2016,2);
  CompareBackgroundMethodShapes(1,1,2017,2);
  CompareBackgroundMethodShapes(1,1,2018,2);
  CompareBackgroundMethodShapes(2,1,2016,2);
  CompareBackgroundMethodShapes(2,1,2017,2);
  CompareBackgroundMethodShapes(2,1,2018,2);

}
