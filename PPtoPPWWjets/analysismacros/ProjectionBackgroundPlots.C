void ProjectionBackgroundPlots(int year = 2016, int channel = 1)
{
  TFile *f1;
  if(year == 2017)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");                                                          
    f1 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017BCDEF.root");
  if(year == 2016)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");                                                            
    f1 = TFile::Open("/eos/cms/store/group/phys_smp/HadronicVV/dataRun2_v3/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016BCG.root");
  if(year == 2018)
    //    f1 = TFile::Open("../test/vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");                                                           
    f1 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018ABCD.root");

  TH1F *hmassmatch1 = new TH1F("hmassmatch1", "hmassmatch1", 20,-3,1);
  TH1F *hmassmatch2 = new TH1F("hmassmatch2", "hmassmatch2", 20,-3,1);
  TH1F *hmassmatch3 = new TH1F("hmassmatch3", "hmassmatch3", 20,-3,1);
  TH1F *hmassmatch4 = new TH1F("hmassmatch4", "hmassmatch4", 20,-3,1);

  TH1F *hymatch1 = new TH1F("hymatch1", "hymatch1", 20,-2,2);
  TH1F *hymatch2 = new TH1F("hymatch2", "hymatch2", 20,-2,2);
  TH1F *hymatch3 = new TH1F("hymatch3", "hymatch3", 20,-2,2);
  TH1F *hymatch4 = new TH1F("hymatch4", "hymatch4", 20,-2,2);

  // Signal region
  //  float mmatchcut = 0.11506000;
  //  float ymatchcut = 0.057220000;
  // Non-blinded region
  float mmatchcut = 1.0;
  float ymatchcut = 0.5;

  // Scale factors: 0.448276, 1, 0.43871, 0.596491, 0.488498, 0.574841
  float acopscale = 0.0; float tauscale = 0.0; float massscale = 0.0;
  //  if(year == 2016 && channel == 1) {acopscale = 0.4375; tauscale = 0.5833; massscale = 0.00498575;}
  //  if(year == 2017 && channel == 1) {acopscale = 0.54386; tauscale = 0.553571; massscale = 0.00540823;}
  //  if(year == 2018 && channel == 1) {acopscale = 0.502392; tauscale = 0.542636; massscale = 0.0051463;}
  //  if(year == 2016 && channel == 2) {acopscale = 0.727273; tauscale = 1; massscale = 0.0223464;}
  //  if(year == 2017 && channel == 2) {acopscale = 0.322034; tauscale = 0.527778; massscale = 0.0138383;}
  //  if(year == 2018 && channel == 2) {acopscale = 0.519637; tauscale = 0.5375; massscale = 0.0175171;}

  // These are the ratio of the # of events in the normalization region to the anti-cut normalization region                                                    
  if(year == 2016 && channel == 1) {acopscale = 0.4118; tauscale = 0.5833; massscale = 0.00483;}
  if(year == 2017 && channel == 1) {acopscale = 0.5254; tauscale = 0.5439; massscale = 0.00523;}
  if(year == 2018 && channel == 1) {acopscale = 0.48165; tauscale = 0.53299; massscale = 0.00499;}
  if(year == 2016 && channel == 2) {acopscale = 0.667; tauscale = 1; massscale = 0.0215;}
  if(year == 2017 && channel == 2) {acopscale = 0.3115; tauscale = 0.5; massscale = 0.01352;}
  if(year == 2018 && channel == 2) {acopscale = 0.50588; tauscale = 0.52121; massscale = 0.01697;}


  TH2F *hatemplatea, *hatemplateb, *hatemplatec, *hatemplated, *hsideband;
  if(channel == 1) // WW
    {
      hatemplatea = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmww");
      hatemplateb = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummww");
      hatemplatec = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmww");
      hatemplated = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunednarrowmmww");
      hsideband = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchvetoorsignalregionww");
    }
  if(channel == 2) // ZZ
    {
      hatemplatea = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiacopmmzz");
      hatemplateb = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantitaummzz");
      hatemplatec = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunedmmzz");
      hatemplated = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchantiprunednarrowmmzz");
      hsideband = (TH2F *)f1->Get("Sidebands/hmassrapiditymatchvetoorsignalregionzz");
    }
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

              hmassmatch4->Fill(hatemplatec->GetXaxis()->GetBinCenter(x), hatemplatec->GetBinContent(x,y));
              hymatch4->Fill(hatemplatec->GetYaxis()->GetBinCenter(y),hatemplatec->GetBinContent(x,y));
	    }
	  else if(hsideband->GetBinContent(x,y) > 0)
	    cout << "WTF??? point with x = " << hsideband->GetXaxis()->GetBinCenter(x) << ", y = " << hsideband->GetYaxis()->GetBinCenter(y) << endl;
	}
    }

  hmassmatch2->Sumw2(); hmassmatch2->Scale(acopscale); hymatch2->Sumw2(); hymatch2->Scale(acopscale);
  hmassmatch3->Sumw2(); hmassmatch3->Scale(tauscale); hymatch3->Sumw2(); hymatch3->Scale(tauscale);
  hmassmatch4->Sumw2(); hmassmatch4->Scale(massscale); hymatch4->Sumw2(); hymatch4->Scale(massscale);


  hmassmatch2->SetMaximum(hmassmatch1->GetMaximum()*2.0);
  hymatch2->SetMaximum(hymatch1->GetMaximum()*2.0);

  if(channel == 1)
    {
      hmassmatch2->SetXTitle("1 - m(W_{j} W_{j})/m(pp)");
      hymatch2->SetXTitle("y(pp) - y(W_{j} W_{j})");
    }
  if(channel == 2)
    {
      hmassmatch2->SetXTitle("1 - m(Z_{j} Z_{j})/m(pp)");
      hymatch2->SetXTitle("y(pp) - y(Z_{j} Z_{j})");
    }
  hmassmatch2->SetYTitle("Events");
  hymatch2->SetYTitle("Events");
  hmassmatch2->GetXaxis()->SetTitleSize(0.04); hmassmatch2->GetXaxis()->SetTitleOffset(1.3); 
  hymatch2->GetXaxis()->SetTitleSize(0.04); hymatch2->GetXaxis()->SetTitleOffset(1.3);
  hmassmatch2->GetYaxis()->SetTitleSize(0.04); hmassmatch2->GetYaxis()->SetTitleOffset(1.3);
  hymatch2->GetYaxis()->SetTitleSize(0.04); hymatch2->GetYaxis()->SetTitleOffset(1.3);


  hmassmatch1->SetLineWidth(3); hymatch1->SetLineWidth(3); 

  if(year == 2016)
    {
      hmassmatch2->SetMaximum(15); hymatch2->SetMaximum(15);
    }
  if(year == 2017)
    {
      hmassmatch2->SetMaximum(30); hymatch2->SetMaximum(30);
    }
  if(year == 2018)
    {
      hmassmatch2->SetMaximum(130); hymatch2->SetMaximum(130);
    }


  TCanvas *c1 = new TCanvas("c1","c1", 1200, 600);
  c1->Divide(2,1);

  c1->cd(1);
  hmassmatch2->SetFillStyle(3001); hmassmatch2->SetFillColor(2); hmassmatch2->SetMarkerStyle(0); hmassmatch2->Draw("E2");
  hmassmatch3->SetFillStyle(3001); hmassmatch3->SetFillColor(4); hmassmatch3->SetMarkerStyle(0); hmassmatch3->Draw("E2same");
  hmassmatch4->SetFillStyle(3001); hmassmatch4->SetFillColor(5); hmassmatch4->SetMarkerStyle(0); hmassmatch4->Draw("E2same");
  hmassmatch1->Draw("E0same");

  TLegend *l1 = new TLegend(0.1,0.6,0.5,0.9);
  l1->AddEntry(hmassmatch2,"Anti-acoplanarity sideband");
  l1->AddEntry(hmassmatch3,"Anti-tau21 sideband");
  l1->AddEntry(hmassmatch4,"Anti-pruned mass sideband");
  l1->AddEntry(hmassmatch1,"Data, normalization region");
  l1->Draw("same");

  c1->cd(2);
  hymatch2->SetFillStyle(3001); hymatch2->SetFillColor(2); hymatch2->SetMarkerStyle(0); hymatch2->Draw("E2");
  hymatch3->SetFillStyle(3001); hymatch3->SetFillColor(4); hymatch3->SetMarkerStyle(0); hymatch3->Draw("E2same");
  hymatch4->SetFillStyle(3001); hymatch4->SetFillColor(5); hymatch4->SetMarkerStyle(0); hymatch4->Draw("E2same");
  hymatch1->Draw("E0same");

  cout << "K-S probabilities: " << endl
       << "\t" << hmassmatch1->KolmogorovTest(hmassmatch2) << ", " << hymatch1->KolmogorovTest(hymatch2) << endl
       << "\t" << hmassmatch1->KolmogorovTest(hmassmatch3) << ", " << hymatch1->KolmogorovTest(hymatch3) << endl
       << "\t" << hmassmatch1->KolmogorovTest(hmassmatch4) << ", " << hymatch1->KolmogorovTest(hymatch4) << endl;


  if(year == 2016)
    {
      CMS_lumi2016((TPad*)c1->GetPad(1),0,0,"2016, L = 9.9 fb^{-1}");
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
  
