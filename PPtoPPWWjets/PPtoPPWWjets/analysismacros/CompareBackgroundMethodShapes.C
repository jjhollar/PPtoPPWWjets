void CompareBackgroundMethodShapes(int var = 1, int sigcuts = 0, int year = 2017)
{
  TFile *f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  TFile *f2 = TFile::Open("../eventmixing/EventMixingOutputHistos.root");

  TH2F *h1 = (TH2F *)f1->Get("hmassrapiditymatchantiacopmm");
  TH2F *h2 = (TH2F *)f1->Get("hmassrapiditymatchantitaumm");
  TH2F *h3 = (TH2F *)f2->Get("hmresdysum");

  float acopscale = 0.0; float tauscale = 0.0;
  if(year == 2016) {acopscale = 0.448276; tauscale = 1.0;}
  if(year == 2017) {acopscale = 0.43871; tauscale = 0.596491;}
  if(year == 2018) {acopscale = 0.488498; tauscale = 0.574841;}

  Float_t kseniammatchcut = 0.11506000;
  Float_t kseniarapmatchcut = 0.057220000;

  int ybinlo = h1->GetYaxis()->FindBin(-1.0*kseniarapmatchcut);
  int ybinhi = h1->GetYaxis()->FindBin(1.0*kseniarapmatchcut);
  int xbinlo = h1->GetXaxis()->FindBin(-1.0*kseniammatchcut);
  int xbinhi = h1->GetXaxis()->FindBin(1.0*kseniammatchcut);

  TH1F *hacopm = (TH1F *)h1->ProjectionX();
  TH1F *htaum = (TH1F *)h2->ProjectionX();
  TH1F *hmixm = (TH1F *)h3->ProjectionX();

  if(var == 1)
    {
      if(sigcuts == 1)
	{
	  hacopm = (TH1F *)h1->ProjectionX("acopm",ybinlo,ybinhi);
	  htaum = (TH1F *)h2->ProjectionX("taum",ybinlo,ybinhi);
	  hmixm = (TH1F *)h3->ProjectionX("mixm",ybinlo,ybinhi);
	}
    }

  if(var == 2)
    {
      hacopm = (TH1F *)h1->ProjectionY();
      htaum = (TH1F *)h2->ProjectionY();
      hmixm = (TH1F *)h3->ProjectionY();

      if(sigcuts == 1)
        {
          hacopm = (TH1F *)h1->ProjectionY("acopm",xbinlo,xbinhi);
          htaum = (TH1F *)h2->ProjectionY("taum",xbinlo,xbinhi);
          hmixm = (TH1F *)h3->ProjectionY("mixm",xbinlo,xbinhi);
        }
    }
  
  hacopm->Rebin(5);
  htaum->Rebin(5);
  hmixm->Rebin(5);

  hacopm->Sumw2(); hacopm->Scale(acopscale); hacopm->SetFillColor(2); hacopm->SetFillStyle(3001); hacopm->SetMarkerStyle(0);
  htaum->Sumw2(); htaum->Scale(tauscale); htaum->SetFillColor(4); htaum->SetFillStyle(3001); htaum->SetMarkerStyle(0); 
  hmixm->SetFillColor(1);  hmixm->SetMarkerStyle(0);

  htaum->GetXaxis()->SetRangeUser(-2,1);
  htaum->SetMaximum(50);

  htaum->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
  if(var == 2)
    htaum->SetXTitle("y(pp) - y(W_{j} W_{j})");

  TCanvas *c1 = new TCanvas("c1","c1");

  htaum->Draw("E2");
  hacopm->Draw("E2same");
  hmixm->Draw("E2same");

  TLegend *l1 = new TLegend(0.1,0.6,0.5,0.9);
  l1->AddEntry(hacopm,"Anti-acoplanarity sample");
  l1->AddEntry(htaum,"Anti-tau21 sample");
  l1->AddEntry(hmixm,"Event mixing");
  l1->Draw("same");

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

}
