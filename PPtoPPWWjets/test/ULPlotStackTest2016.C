/*
 * Updated for reprocessed samples with UL proton reco
 *
 */

void ULPlotStackTest2016(Int_t var = 1)
{
  // pre-TS2
  Float_t lumi = 4.718+1.631+3.667+5.095;


  // QCD xsections from xsecDB
  /*
  Float_t mc6xsec = 7.47;
  Float_t mc5xsec = 26.28;
  Float_t mc4xsec = 156.5;
  Float_t mc3xsec = 552.1;
  Float_t mc2xsec = 6830.0;
  Float_t mc1xsec = 103500.0;
  */

  // QCD xsections from B2G-18-002, including corr factors
  Float_t mc6xsec = 9.4183;
  Float_t mc5xsec = 32.293;
  Float_t mc4xsec = 185.9;
  Float_t mc3xsec = 642.1;
  Float_t mc2xsec = 6830.0;
  Float_t mc1xsec = 103500.0;
  Float_t mc10xsec = 0.84265;
  Float_t mc11xsec = 66.85;
  Float_t mc7xsec = 21.3;
  Float_t mc8xsec = 41.3;
  Float_t mc9xsec = 21.3;

  //  Float_t mcaxsec = 0.1282; // pb
  Float_t mcaxsec = 0.0454; // pb, a0W=1E-6
  Float_t mcbxsec = 0.0583; // pb, a0W=2E-6
  Float_t mcdxsec = 0.1648; // pb, aCW=2E-5
  Float_t mbaaxsec = 0.1074; // pb 
  Float_t mcaaxsec = 0.00264; // pb, a0Z=5E-5


  Float_t rangelo = 0.0;
  Float_t rangehi = 1.0;
  Float_t rangeylo = 0.0;
  Float_t rangeyhi = 10000000.0;

  TString hist = "hmjjdat";
  TString thetitle = "";
  TString filetitle = "";
  if(var == 1)
    //    {rangelo = 1000; rangehi = 10000; thetitle = "m(jj) [GeV]"; filetitle = "mjj";}
    {rangelo = 1000; rangehi = 3000; thetitle = "m(jj) [GeV]"; filetitle = "mjj";}
  if(var == 2)
    {hist = "hmjdat1"; rangelo = 55; rangehi = 215; thetitle = "m(j1) [GeV]"; filetitle = "mj1";}
  if(var == 3)
    {hist = "htau21dat1"; thetitle = "tau_{21}(j1)"; filetitle = "tau21j1";}
  if(var == 4)
    {hist = "hptdat1"; rangelo = 0; rangehi = 2000; thetitle = "p_{T}(j1) [GeV]"; filetitle = "pTleading";}
  if(var == 5)
    {hist = "hptdat2"; rangelo = 0; rangehi = 2000; thetitle = "p_{T}(j2) [GeV]"; filetitle = "pTtrailing";}
  if(var == 6)
    {hist = "hetadat1"; thetitle = "#eta(j1)"; filetitle = "etaleading";}
  if(var == 7)
    {hist = "hetadat2"; thetitle = "#eta(j2)"; filetitle = "etatrailing";}
  if(var == 8)
    {hist = "hphidat1"; thetitle = "#phi(j1)"; filetitle = "phileading";}
  if(var == 9)
    {hist = "hphidat2"; thetitle = "#phi(j2)"; filetitle = "phitrailing";}
  if(var == 10)
    {hist = "hmjjdatpfjet"; thetitle = "m(jj) [GeV], PF jet triggers"; filetitle = "mjj_pfjettrig";}
  if(var == 11)
    {hist = "hmjjdatpfjettrim"; thetitle = "m(jj) [GeV], PF jet trimmed triggers"; filetitle = "mjj_pfjettrimtrig";}
  if(var == 12)
    {hist = "hmjjdatpfhttrim"; thetitle = "m(jj) [GeV], PF HT trimmed triggers"; filetitle = "mjj_pfhttrimtrig";}
  if(var == 13)
    {hist = "hdeta"; rangelo = 0; rangehi = 1.3; thetitle = "#Delta(#eta)"; filetitle = "deltaeta";}
  if(var == 14)
    {hist = "hacopdat"; thetitle = "acoplanarity(jj)"; filetitle = "acoplanarity";}
  if(var == 15)
    {hist = "hnvtx"; thetitle = "N(vertices)"; filetitle = "nvertices";}
  if(var == 16)
    {hist = "hptratio"; thetitle = "p_{T}(j1)/p_{T}(j2)"; filetitle = "pTbalance";}
  if(var == 17)
    {hist = "hmjdat2"; rangelo = 55; rangehi = 215; thetitle = "m(j2) [GeV]"; filetitle = "mj2";}
  if(var == 18)
    {hist = "htau21dat2"; thetitle = "tau_{21}(j2)"; filetitle = "tau21j2";}
  if(var == 19)
    {hist = "htau21ddtdat1"; thetitle = "tau_{21, DDT}(j1)"; filetitle = "tau21ddtj1";}
  if(var == 20)
    {hist = "htau21ddtdat2"; thetitle = "tau_{21, DDT}(j2)"; filetitle = "tau21ddtj2";}
  if(var == 21)
    {hist = "hyjjdat"; thetitle = "y(jj)"; filetitle = "yjj";}
  if(var == 22)
    {hist = "hmasswwantitau"; thetitle = "m(WW), #tau_{21, DDT} > 0.75"; filetitle = "mwwantitau";}
  if(var == 23)
    {hist = "hmasswwantiacop"; thetitle = "m(WW), acoplanarity > 0.1"; filetitle = "mwwantiacop";}
  if(var == 24)
    {hist = "hmasswwantiptbal"; thetitle = "m(WW), p_{T}(j1/j2) > 1.1"; filetitle = "mwwanttptbal";}
  if(var == 25)
    {hist = "hmasswwsignal"; thetitle = "m(WW), signal"; filetitle = "mwwsignalblind";}
  if(var == 26)
    {hist = "hywwsignal"; thetitle = "y(WW), signal"; filetitle = "ywwsignalblind";}
  if(var == 27)
    {hist = "xijets45"; thetitle = "#xi(jets), 45"; filetitle = "xijets45";}
  if(var == 28)
    {hist = "xijets56"; thetitle = "#xi(jets), 56"; filetitle = "xijets56";}


  /*
  TFile *f100 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017C.root");
  TH1F *h100 = (TH1F *)f100->Get(hist);

  TFile *f101 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017B.root");
  TH1F *h101 = (TH1F *)f101->Get(hist);

  TFile *f102 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017D.root");
  TH1F *h102 = (TH1F *)f102->Get(hist);

  TFile *f103 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017E.root");
  TH1F *h103 = (TH1F *)f103->Get(hist);

  TFile *f104 = TFile::Open("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017F.root");
  TH1F *h104 = (TH1F *)f104->Get(hist);
  */
  //  TFile *f100 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017BCD.root");
  TFile *f100 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2016BCGH.root");
  TH1F *h100 = (TH1F *)f100->Get(hist);

  TFile *f2 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt300to470_2016.root");
  TH1F *h2 = (TH1F *)f2->Get(hist);

  TFile *f3 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt470to600_2016.root");
  TH1F *h3 = (TH1F *)f3->Get(hist);

  TFile *f4 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt600to800_2016.root");
  TH1F *h4 = (TH1F *)f4->Get(hist);
  
  TFile *f5 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt800to1000_2016.root");
  TH1F *h5 = (TH1F *)f5->Get(hist);
  
  TFile *f6 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1000to1400_2016.root");
  TH1F *h6 = (TH1F *)f6->Get(hist);

  TFile *f7 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_ttbarhadronic1000inf_2016.root");
  TH1F *h7 = (TH1F *)f7->Get(hist);

  TFile *f8 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_wjetshadronic_2016.root");
  TH1F *h8 = (TH1F *)f8->Get(hist);

  TFile *f9 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_zjetshadronic_2016.root");
  TH1F *h9 = (TH1F *)f9->Get(hist);

  TFile *f10 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1400to1800_2016.root");
  TH1F *h10 = (TH1F *)f10->Get(hist);

  TFile *f11 = TFile::Open("vars_cuts_ntupleULReMiniv4finalWithJER_ttbarhadronic700ot1000_2016.root");
  TH1F *h11 = (TH1F *)f11->Get(hist);


  h100->Sumw2(); //h101->Sumw2(); h102->Sumw2(); h103->Sumw2();  h104->Sumw2();
  //  h100->Add(h101); h100->Add(h102); h100->Add(h103); h100->Add(h104);
  TH1F *h1000 = (TH1F *)h100->Clone("h1000");

  TCanvas *c1 = new TCanvas("c1","c1",600,800);
  c1->Divide(1,3);
  c1->cd(1);

  
  int rebinfactor = 1;
  //  if((var > 20 && var < 25))
  if(var == 3 || var == 6 || var == 7 || var == 8 || var == 9 || var == 18 || var == 19 || var == 20 || var == 16 || var == 25 || (var > 20 && var < 25))
    {
      rebinfactor = 5;
      if(var == 19 || var == 20)
	rebinfactor = 10;
      if(var == 25) {rebinfactor = 5;}
      if(var == 16) {rebinfactor = 10;}
      if(var > 20 && var < 25) {rebinfactor = 10;}
      h2->Rebin(rebinfactor); 
      h3->Rebin(rebinfactor); h4->Rebin(rebinfactor); h5->Rebin(rebinfactor);
      h6->Rebin(rebinfactor); h7->Rebin(rebinfactor);
      h8->Rebin(rebinfactor);  h9->Rebin(rebinfactor);
      h10->Rebin(rebinfactor); 
      h11->Rebin(rebinfactor);
      h100->Rebin(rebinfactor); //h101->Rebin(rebinfactor); h102->Rebin(rebinfactor); h103->Rebin(rebinfactor); h104->Rebin(rebinfactor);
      h1000->Rebin(rebinfactor);
    }

  // For MC in higher QCD pT bins, only running on 100k events from the ntuple per bin, so renormalize to that                                               
  
  h2->Sumw2(); // 300-470, higher-stats extension
  h2->Scale((2578238.0/18319816.0)*mc2xsec*1000*lumi/(1000000.0));
  h2->SetFillColor(kAzure+1);
  //  h2->SetFillColor(2);

  h3->Sumw2(); // 470-600
  h3->Scale((3691791.0/3959986.0)*mc3xsec*1000*lumi/(1000000.0));
  h3->SetFillColor(kAzure+1);
  //  h3->SetFillColor(3);

  h4->Sumw2(); // 600-800
  h4->Scale((3866084.0/3896412.0)*mc4xsec*1000*lumi/(1000000.0));
  h4->SetFillColor(kAzure+1);
  //  h4->SetFillColor(4);

  h5->Sumw2(); // 800-1000
  h5->Scale((15679031.0/15704980.0)*mc5xsec*1000*lumi/(1000000.0));
  h5->SetFillColor(kAzure+1);
  //  h5->SetFillColor(5);

  h6->Sumw2(); // 1000-1400
  h6->Scale((2999069.0/2995724.0)*mc6xsec*1000*lumi/(1000000.0));
  h6->SetFillColor(kAzure+1);
  //  h6->Scale((5316947.0/27905480.0)*mc6xsec*1000*lumi/(1000000.0));

  h7->Sumw2(); // ttbar 1000-inf
  h7->Scale((3732532.0/24577608.0)*mc7xsec*1000*lumi/(1000000.0));

  h8->Sumw2(); // wjets
  h8->Scale((139514.0/1026587.0)*mc8xsec*1000*lumi/(1000000.0));

  h9->Sumw2(); // zjets 
  h9->Scale((192621.0/1000000.0)*mc9xsec*1000*lumi/(1000000.0));

  h10->Sumw2(); // 1400-1800
  h10->Scale((335704.0/395902.0)*mc10xsec*1000*lumi/1000000.0);
  h10->SetFillColor(kAzure+1);

  h11->Sumw2(); // ttbar 700-1000                                                                                                                                        
  h11->Scale((913088.0/38426513.0)*mc11xsec*1000*lumi/(1000000.0));

  /*
  h12->Add(h11);
  h12->Add(h10);
  h12->Add(h6);
  h12->Add(h5);
  h12->Add(h4);
  h12->Add(h3);
  h12->Add(h2);
  h12->Add(h1);
  h12->Add(h7);
  h12->Add(h8);
  h12->Add(h9);

  h12->SetStats(0);
  if(rangelo != 0 || rangehi != 1)
    h12->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h12->SetMaximum(h100->GetMaximum()*1.5);
  h12->SetTitle(thetitle);
  h12->Draw("hist");

  TH1F *h12err = (TH1F *)h12->Clone("h12err");
  h12err->SetFillColor(1);
  h12err->SetFillStyle(3001);
  h12err->Draw("E2same");

  h11->Add(h10);
  h11->Add(h6);
  h11->Add(h5);
  h11->Add(h4);
  h11->Add(h3);
  h11->Add(h2);
  h11->Add(h1);
  h11->Add(h7);
  h11->Add(h8);
  h11->Add(h9);
  h11->Draw("histsame");
  */

  h10->Add(h6);
  h10->Add(h5);
  h10->Add(h4);
  h10->Add(h3);
  h10->Add(h2);
  h10->Add(h7);
  h10->Add(h8);
  h10->Add(h9);
  h10->Add(h11);
  h10->Draw("histsame");

  h10->SetStats(0);     
  if(rangelo != 0 || rangehi != 1)                                                                                                                        
    h10->GetXaxis()->SetRangeUser(rangelo,rangehi);                                                                                                       
  h10->SetMaximum(h100->GetMaximum()*1.5);                                                                                                                
  h10->SetTitle(thetitle);                                                                                                                                
  h10->Draw("hist");                                                                                                                                      

  TH1F *h10err = (TH1F *)h10->Clone("h10err");                                                                                                                
  h10err->SetFillColor(1);                                                                                                                                    
  h10err->SetFillStyle(3001);                                                                                                                                 
  h10err->SetMarkerStyle(0);
  h10err->Draw("E2same");                                                                                                                                     

  h6->Add(h5);
  h6->Add(h4);
  h6->Add(h3);
  h6->Add(h2);
  h6->Add(h7);
  h6->Add(h11);
  h6->Add(h8);
  h6->Add(h9);
  h6->Draw("histsame");

  h5->Add(h4);
  h5->Add(h3);
  h5->Add(h2);
  h5->Add(h7);
  h5->Add(h11);
  h5->Add(h8);
  h5->Add(h9);
  h5->Draw("histsame");


  h4->Add(h3);
  h4->Add(h2);
  h4->Add(h7);
  h4->Add(h11);
  h4->Add(h8);
  h4->Add(h9);
  h4->Draw("histsame");

  h3->Add(h2);
  h3->Add(h7);
  h3->Add(h11);
  h3->Add(h8);
  h3->Add(h9);
  h3->Draw("histsame");

  h2->Add(h7);
  h2->Add(h11);
  h2->Add(h8);
  h2->Add(h9);
  h2->Draw("histsame");

  h8->SetFillColor(kGreen+1);
  h8->Add(h7);
  h8->Add(h11);
  h8->Add(h9);
  h8->Draw("histsame");

  h9->SetFillColor(kYellow+1);
  h9->Add(h7);
  h9->Add(h11);
  h9->Draw("histsame");

  h7->SetFillColor(kOrange+1);
  h7->Add(h11);
  h7->Draw("histsame");

  h11->SetFillColor(kOrange+1);
  h11->Draw("histsame");

  h100->SetMarkerStyle(20); h100->SetLineWidth(3);
  h100->Draw("esame");


  TLegend *lg1 = new TLegend(0.6,0.6,0.9,0.9);
  lg1->AddEntry(h10,"Pythia8 QCD (bins)");
  lg1->AddEntry(h8,"Madgraph W+jets");
  lg1->AddEntry(h7,"Powheg ttbar (1000-inf)");
  lg1->AddEntry(h9,"Madgraph Z+jets");
  lg1->AddEntry(h100,"201GBCGH Data");
  lg1->Draw("same");
  
  c1->cd(2);
  /*
  h12->SetStats(0);
  h12->SetMinimum(0.01);
  h12->Draw("hist");
  h12err->Draw("e2same");
  h11->Draw("histsame");
  h10->Draw("histsame");
  */
  h10->SetStats(0);                                                                                                                                           
  h10->SetMinimum(0.01);                                                                                                                                      
  h10->Draw("hist");                                                                                                                                          
  h10err->Draw("e2same");                                                                                                                                     

  h6->Draw("histsame");
  h5->Draw("histsame");
  h4->Draw("histsame");
  h3->Draw("histsame");
  h2->Draw("histsame");
  h8->Draw("histsame");
  h9->Draw("histsame");
  h7->Draw("histsame");
  h11->Draw("histsame");
  gPad->SetLogy();
  h100->Draw("esame");

  c1->cd(3);
  /*
  TH1F *h1000err = (TH1F *)h12err->Clone("h1000err");
  h1000err->Divide(h12);
  */
  TH1F *h1000err = (TH1F *)h10err->Clone("h1000err");                                                                                                         
  h1000err->Divide(h10);                                                                                                                                      

  h1000err->SetMinimum(0); h1000err->SetMaximum(2.0);
  h1000err->Draw("E2");


  h1000->SetMarkerStyle(20); h1000->SetLineWidth(3);
  h1000->Sumw2();
  cout << "MC = " << h10->GetSumOfWeights() << ", data = " << h1000->GetSumOfWeights() << ", ratio = " << h1000->GetSumOfWeights()/h10->GetSumOfWeights() << endl;

  h1000->Divide(h10);
  h1000->SetMaximum(2.0);
  h1000->SetMinimum(0.0);
  if(rangelo != 0 || rangehi != 1)
    h1000->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h1000->SetStats(0);
  h1000->SetTitle(thetitle);
  h1000->Draw("esame");

  TLine *l1;
  TLine *l2;
  TLine *l3;
  if(rangelo != 0 || rangehi != 1)
    {
      l1 = new TLine(rangelo,1.0,rangehi,1.0);
      l2 = new TLine(rangelo,1.1,rangehi,1.1);
      l3 = new TLine(rangelo,0.9,rangehi,0.9);
    }
  else
    {
      l1 = new TLine(h1000->GetXaxis()->GetXmin(),1.0,h1000->GetXaxis()->GetXmax(),1.0);
      l2 = new TLine(h1000->GetXaxis()->GetXmin(),1.1,h1000->GetXaxis()->GetXmax(),1.1);
      l3 = new TLine(h1000->GetXaxis()->GetXmin(),0.9,h1000->GetXaxis()->GetXmax(),0.9);
    }
  l1->SetLineColor(2);
  l1->SetLineStyle(2);
  l1->SetLineWidth(3);
  l1->Draw("same");

  l2->SetLineColor(2);
  l2->SetLineStyle(2);                                                                                                               
  l2->SetLineWidth(3);
  //  l2->Draw("same");

  l3->SetLineColor(2);
  l3->SetLineStyle(2);
  l3->SetLineWidth(3);
  //  l3->Draw("same");

  TString outplotname = "validationplots2016BCGH_ntupleULReMiniv4final_" + filetitle + ".pdf";
  c1->SaveAs(outplotname);

  // Signal MC only
  //  TCanvas *c3 = new TCanvas("c3","c3");
  //  h7->Draw("hist");
  //  ha->Draw("hist");
}

void PlotStackAll()
{
  ULPlotStackTest2016(1);
  ULPlotStackTest2016(2);
  ULPlotStackTest2016(3);
  ULPlotStackTest2016(4);
  ULPlotStackTest2016(5);
  ULPlotStackTest2016(6);
  ULPlotStackTest2016(7);
  ULPlotStackTest2016(8);
  ULPlotStackTest2016(9);
  ULPlotStackTest2016(13);
  ULPlotStackTest2016(14);
  ULPlotStackTest2016(15);
  ULPlotStackTest2016(16);
  ULPlotStackTest2016(17);
  ULPlotStackTest2016(18);
  ULPlotStackTest2016(19);
  ULPlotStackTest2016(20);
  ULPlotStackTest2016(27);
  ULPlotStackTest2016(28);

}
