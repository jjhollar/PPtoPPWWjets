void ProjectionBackgroundPlots(int year = 2016)
{
  TFile *f1;
  if(year == 2017)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  if(year == 2016)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
  if(year == 2018)
    f1 = TFile::Open("../datamcplots/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");

  TH1F *hmassmatch1 = new TH1F("hmassmatch1", "hmassmatch1", 20,-3,1);
  TH1F *hmassmatch2 = new TH1F("hmassmatch2", "hmassmatch2", 20,-3,1);
  TH1F *hmassmatch3 = new TH1F("hmassmatch3", "hmassmatch3", 20,-3,1);

  TH1F *hymatch1 = new TH1F("hymatch1", "hymatch1", 20,-2,2);
  TH1F *hymatch2 = new TH1F("hymatch2", "hymatch2", 20,-2,2);
  TH1F *hymatch3 = new TH1F("hymatch3", "hymatch3", 20,-2,2);

  // Signal region
  //  float mmatchcut = 0.11506000;
  //  float ymatchcut = 0.057220000;
  // Non-blinded region
  float mmatchcut = 1.0;
  float ymatchcut = 0.5;

  // Scale factors: 0.448276, 1, 0.43871, 0.596491, 0.488498, 0.574841
  float acopscale = 0.0; float tauscale = 0.0;
  if(year == 2016) {acopscale = 0.448276; tauscale = 1.0;}
  if(year == 2017) {acopscale = 0.43871; tauscale = 0.596491;}
  if(year == 2018) {acopscale = 0.488498; tauscale = 0.574841;}

  TH2F *hatemplatea, *hatemplateb;
  hatemplatea = (TH2F *)f1->Get("hmassrapiditymatchantiacopmm");
  hatemplateb = (TH2F *)f1->Get("hmassrapiditymatchantitaumm");
  TH2F *hsideband = (TH2F *)f1->Get("hmassrapiditymatchvetoorsignalregion");

  for(Int_t x = 1; x < hsideband->GetXaxis()->GetNbins(); x++)
    {
      for(Int_t y = 1; y < hsideband->GetYaxis()->GetNbins(); y++)
	{
	  if(!(fabs(hsideband->GetXaxis()->GetBinCenter(x)) <= mmatchcut && fabs(hsideband->GetYaxis()->GetBinCenter(y)) <= ymatchcut))
	    {
	      hmassmatch1->Fill(hsideband->GetXaxis()->GetBinCenter(x), hsideband->GetBinContent(x,y));
	      hymatch1->Fill(hsideband->GetYaxis()->GetBinCenter(y), hsideband->GetBinContent(x,y));

	      hmassmatch2->Fill(hatemplatea->GetXaxis()->GetBinCenter(x), hatemplatea->GetBinContent(x,y));
	      hymatch2->Fill(hatemplatea->GetYaxis()->GetBinCenter(y),hatemplatea->GetBinContent(x,y));

              hmassmatch3->Fill(hatemplateb->GetXaxis()->GetBinCenter(x), hatemplateb->GetBinContent(x,y));
              hymatch3->Fill(hatemplateb->GetYaxis()->GetBinCenter(y),hatemplateb->GetBinContent(x,y));
	    }
	  else if(hsideband->GetBinContent(x,y) > 0)
	    cout << "WTF??? point with x = " << hsideband->GetXaxis()->GetBinCenter(x) << ", y = " << hsideband->GetYaxis()->GetBinCenter(y) << endl;
	}
    }

  hmassmatch2->Sumw2(); hmassmatch2->Scale(acopscale); hymatch2->Sumw2(); hymatch2->Scale(acopscale);
  hmassmatch3->Sumw2(); hmassmatch3->Scale(tauscale); hymatch3->Sumw2(); hymatch3->Scale(tauscale);

  hmassmatch2->SetMaximum(hmassmatch1->GetMaximum()*2.0);
  hymatch2->SetMaximum(hymatch1->GetMaximum()*2.0);

  hmassmatch2->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
  hymatch2->SetXTitle("y(pp) - y(W_{j} W_{j})");
  hmassmatch2->SetYTitle("Events");
  hymatch2->SetYTitle("Events");
  hmassmatch2->GetXaxis()->SetTitleSize(0.04); hmassmatch2->GetXaxis()->SetTitleOffset(1.3); 
  hymatch2->GetXaxis()->SetTitleSize(0.04); hymatch2->GetXaxis()->SetTitleOffset(1.3);
  hmassmatch2->GetYaxis()->SetTitleSize(0.04); hmassmatch2->GetYaxis()->SetTitleOffset(1.3);
  hymatch2->GetYaxis()->SetTitleSize(0.04); hymatch2->GetYaxis()->SetTitleOffset(1.3);


  hmassmatch1->SetLineWidth(3); hymatch1->SetLineWidth(3); 

  TCanvas *c1 = new TCanvas("c1","c1", 1200, 600);
  c1->Divide(2,1);

  c1->cd(1);
  hmassmatch2->SetFillStyle(3001); hmassmatch2->SetFillColor(2); hmassmatch2->SetMarkerStyle(0); hmassmatch2->Draw("E2");
  hmassmatch3->SetFillStyle(3001); hmassmatch3->SetFillColor(4); hmassmatch3->SetMarkerStyle(0); hmassmatch3->Draw("E2same");
  hmassmatch1->Draw("E0same");

  TLegend *l1 = new TLegend(0.1,0.6,0.5,0.9);
  l1->AddEntry(hmassmatch2,"Anti-acoplanarity sideband");
  l1->AddEntry(hmassmatch3,"Anti-tau21 sideband");
  l1->AddEntry(hmassmatch1,"Data, normalization region");
  l1->Draw("same");

  c1->cd(2);
  hymatch2->SetFillStyle(3001); hymatch2->SetFillColor(2); hymatch2->SetMarkerStyle(0); hymatch2->Draw("E2");
  hymatch3->SetFillStyle(3001); hymatch3->SetFillColor(4); hymatch3->SetMarkerStyle(0); hymatch3->Draw("E2same");
  hymatch1->Draw("E0same");

  cout << "K-S probabilities: " << endl
       << "\t" << hmassmatch1->KolmogorovTest(hmassmatch2) << ", " << hymatch1->KolmogorovTest(hymatch2) << endl
       << "\t" << hmassmatch1->KolmogorovTest(hmassmatch3) << ", " << hymatch1->KolmogorovTest(hymatch3) << endl;

  if(year == 2016)
    {
      CMS_lumi2016((TPad*)c1->GetPad(1),0,0,"2016, L = 10.0 fb^{-1}");
    }
  if(year == 2017)
    {
      CMS_lumi2016((TPad*)c1->GetPad(1),0,0,"2017, L = 37.2 fb^{-1}");
    }
  if(year == 2018)
    {
      CMS_lumi2016((TPad*)c1->GetPad(1),0,0,"2018, L = 52.9 fb^{-1}");
    }

}
  
