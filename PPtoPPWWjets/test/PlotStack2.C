void PlotStack2(Int_t var = 1)
{
  Float_t lumi = 2.367+8.681+4.143+9.062+13.242;
  Float_t mc6xsec = 9.4183;
  Float_t mc5xsec = 32.293;
  Float_t mc3xsec = 642.1;
  Float_t mc4xsec = 185.9;
  Float_t mc2xsec = 6830.0;
  Float_t mc1xsec = 103500.0;
  Float_t mc7xsec = 377.96;
  Float_t mc8xsec = 33.7;
  Float_t mc9xsec = 14.6;

  Float_t mcaxsec = 0.1282; // pb
  Float_t mbaaxsec = 0.1074; // pb 
  Float_t mcbxsec = 0.0391; // pb

  Float_t rangelo = 0.0;
  Float_t rangehi = 1.0;
  Float_t rangeylo = 0.0;
  Float_t rangeyhi = 10000000.0;

  TString hist = "hmjjdat";
  TString thetitle = "";
  TString filetitle = "";
  if(var == 1)
    {rangelo = 00; rangehi = 2500; thetitle = "m(jj) [GeV]"; filetitle = "mjj";}
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
    {hist = "hmasswwantitau"; thetitle = "m(WW), #tau_{21, DDT} > 0.75"; filetitle = "mwwantitau";}
  if(var == 22)
    {hist = "hmasswwantiacop"; thetitle = "m(WW), acoplanarity > 0.1"; filetitle = "mwwantiacop";}
  if(var == 23)
    {hist = "hmasswwantiptbal"; thetitle = "m(WW), p_{T}(j1/j2) > 1.1"; filetitle = "mwwanttptbal";}
  if(var == 24)
    {hist = "hmasswwsignal"; thetitle = "m(WW), signal"; filetitle = "mwwsignalblind";}
  if(var == 25)
    {hist = "hywwsignal"; thetitle = "y(WW), signal"; filetitle = "ywwsignalblind";}


  TFile *f100 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_datahist2017C.root");
  TH1F *h100 = (TH1F *)f100->Get(hist);

  TFile *f101 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_datahist2017B.root");
  TH1F *h101 = (TH1F *)f101->Get(hist);

  TFile *f102 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_datahist2017D.root");
  TH1F *h102 = (TH1F *)f102->Get(hist);

  TFile *f103 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_datahist2017E.root");
  TH1F *h103 = (TH1F *)f103->Get(hist);

  TFile *f104 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_datahist2017F.root");
  TH1F *h104 = (TH1F *)f104->Get(hist);
  
  TFile *f1 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_qcdpt170to300.root");
  TH1F *h1 = (TH1F *)f1->Get(hist);

  TFile *f2 = TFile::Open("vars_cuts_ntuplev3recalcmjcut_jerallhltfixptetacuts_qcdpt300to470.root");
  TH1F *h2 = (TH1F *)f2->Get(hist);

  TFile *f3 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_qcdpt470to600.root");
  TH1F *h3 = (TH1F *)f3->Get(hist);

  TFile *f4 = TFile::Open("vars_cuts_ntuplev3recalcmjcut_jerallhltfixptetacuts_qcdpt600to800.root");
  TH1F *h4 = (TH1F *)f4->Get(hist);

  TFile *f5 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_qcdpt800to1000.root");
  TH1F *h5 = (TH1F *)f5->Get(hist);

  TFile *f6 = TFile::Open("vars_cuts_ntuplev3recalcmjcut_jerallhltfixptetacuts_qcdpt1000to1400.root");
  TH1F *h6 = (TH1F *)f6->Get(hist);

  TFile *f7 = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_ttbarhadronic.root");
  TH1F *h7 = (TH1F *)f7->Get(hist);

  TFile *f8 = TFile::Open("vars_cuts_ntuplev3recalcmjcut_jerallhltfixptetacuts_wjetshadronic.root");
  TH1F *h8 = (TH1F *)f8->Get(hist);

  TFile *f9 = TFile::Open("vars_cuts_ntuplev3recalcmjcut_jerallhltfixptetacuts_zjetshadronic.root");
  TH1F *h9 = (TH1F *)f9->Get(hist);

  TFile *fa = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_exclwwa0w2point5.root");
  TH1F *ha = (TH1F *)fa->Get(hist);

  TFile *fb = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_exclwwSM.root");
  TH1F *hb = (TH1F *)fb->Get(hist);

  TFile *faa = TFile::Open("vars_cuts_ntuplev2recalcmjcut_jerallhltfixptetacuts_exclzza0z2point5.root");
  TH1F *haa = (TH1F *)faa->Get(hist);

  h100->Sumw2(); h101->Sumw2(); h102->Sumw2(); h103->Sumw2();  h104->Sumw2();
  h100->Add(h101); h100->Add(h102); h100->Add(h103); h100->Add(h104);
  TH1F *h1000 = (TH1F *)h100->Clone("h1000");

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(1,3);
  c1->cd(1);

  
  int rebinfactor = 1;
  //  if((var > 20 && var < 25) || (var == 16))
  if((var > 20 && var < 25))
    {
      rebinfactor = 25;
      if(var == 25) {rebinfactor = 5;}
      if(var == 16) {rebinfactor = 10;}
      h1->Rebin(rebinfactor); h2->Rebin(rebinfactor); h3->Rebin(rebinfactor); h4->Rebin(rebinfactor); h5->Rebin(rebinfactor); h6->Rebin(rebinfactor); 
      h7->Rebin(rebinfactor); h8->Rebin(rebinfactor); h9->Rebin(rebinfactor);
      ha->Rebin(rebinfactor); hb->Rebin(rebinfactor);
      haa->Rebin(rebinfactor);
      h100->Rebin(rebinfactor); h101->Rebin(rebinfactor); h102->Rebin(rebinfactor); h103->Rebin(rebinfactor); h104->Rebin(rebinfactor);
      h1000->Rebin(rebinfactor);
    }

  h1->Sumw2();
  h1->Scale(mc1xsec*1000*lumi/29791322.0);
  h1->SetFillColor(kAzure+1);

  // For MC in higher QCD pT bins, only running on 1M events from the ntuple per bin, so renormalize to that
  h2->Sumw2();
  h2->Scale(mc2xsec*1000*lumi/(65665222.0*100000.0/14999535.0));
  h2->SetFillColor(kAzure+1);

  h3->Sumw2();
  h3->Scale(mc3xsec*1000*lumi/(27384428.0*100000.0/24828195.0));
  h3->SetFillColor(kAzure+1);

  h4->Sumw2();
  h4->Scale(mc4xsec*1000*lumi/(65665222.0*100000.0/65529198.0));
  h4->SetFillColor(kAzure+1);

  h5->Sumw2();
  h5->Scale(mc5xsec*1000*lumi/(33677480.0*100000.0/33670567.0));
  h5->SetFillColor(kAzure+1);

  h6->Sumw2();
  h6->Scale(mc6xsec*1000*lumi/(19631814.0*100000.0/19630824.0));
  h6->SetFillColor(kAzure+1);

  h7->Sumw2();
  h7->Scale(mc7xsec*1000*lumi/(41248864.0*100000.0/987692.0));

  h8->Sumw2();
  h8->Scale(mc8xsec*1000*lumi/(9412869.0*100000.0/7488475.0));

  h9->Sumw2();
  h9->Scale(mc9xsec*1000*lumi/(9736656.0*100000.0/7200365.0));

  h6->Add(h5);
  h6->Add(h4);
  h6->Add(h3);
  h6->Add(h2);
  h6->Add(h1);
  h6->Add(h7);
  h6->Add(h8);
  h6->Add(h9);

  h6->SetStats(0);
  if(rangelo != 0 || rangehi != 1)
    h6->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h6->SetMaximum(h100->GetMaximum()*1.5);
  h6->SetTitle(thetitle);
  h6->Draw("hist");

  TH1F *h6err = (TH1F *)h6->Clone("h6err");
  h6err->SetFillColor(8);
  //  h6err->SetFillStyle(21);
  h6err->Draw("e2same");


  h5->Add(h4);
  h5->Add(h3);
  h5->Add(h2);
  h5->Add(h1);
  h5->Add(h7);
  h5->Add(h8);
  h5->Add(h9);
  h5->Draw("histsame");

  h4->Add(h3);
  h4->Add(h2);
  h4->Add(h1);
  h4->Add(h7);
  h4->Add(h8);
  h4->Add(h9);
  h4->Draw("histsame");

  h3->Add(h2);
  h3->Add(h1);
  h3->Add(h7);
  h3->Add(h8);
  h3->Add(h9);
  h3->Draw("histsame");

  h2->Add(h1);
  h2->Add(h7);
  h2->Add(h8);
  h2->Add(h9);
  h2->Draw("histsame");

  h1->Add(h7);
  h1->Add(h8);
  h1->Add(h9);
  h1->Draw("histsame");

  h8->SetFillColor(kGreen+1);
  h8->Add(h7);
  h8->Add(h9);
  h8->Draw("histsame");

  h9->SetFillColor(kYellow+1);
  h9->Add(h7);
  h9->Draw("histsame");

  h7->SetFillColor(kOrange+1);
  h7->Draw("histsame");

  h100->SetMarkerStyle(20); h100->SetLineWidth(3);
  h100->Draw("esame");

  ha->SetLineWidth(3); ha->SetLineColor(kCyan); ha->Scale(mcaxsec*1000.0*lumi/993.0); ha->Draw("histsame");
  hb->SetFillColor(kCyan); hb->Scale(mcbxsec*1000.0*lumi/38000.0); hb->Draw("histsame");

  haa->SetLineWidth(3); haa->SetLineColor(6); haa->Scale(mbaaxsec*1000.0*lumi/5000.0); haa->Draw("histsame");

  TLegend *lg1 = new TLegend(0.6,0.6,0.9,0.9);
  lg1->AddEntry(h6,"Pythia8 QCD (bins)");
  lg1->AddEntry(h8,"Madgraph W+jets");
  lg1->AddEntry(h9,"Madgraph Z+jets");
  lg1->AddEntry(h7,"Powheg ttbar");
  lg1->AddEntry(ha,"Excl. WW signal (a0W = 2.5E-6), arb. normalization");
  lg1->AddEntry(haa,"Excl. ZZ signal (a0Z = 2.5E-6), arb. normalization");
  lg1->AddEntry(h100,"2017BCDEF Data");
  lg1->Draw("same");
  
  c1->cd(2);
  h6->SetStats(0);
  h6->Draw("hist");
  h6err->Draw("e2same");
  h5->Draw("histsame");
  h4->Draw("histsame");
  h3->Draw("histsame");
  h2->Draw("histsame");
  h1->Draw("histsame");
  h8->Draw("histsame");
  h9->Draw("histsame");
  h7->Draw("histsame");
  gPad->SetLogy();
  h100->Draw("esame");

  ha->Draw("histsame");
  hb->Draw("histsame");

  haa->Draw("histsame");

  c1->cd(3);
  h1000->SetMarkerStyle(20); h1000->SetLineWidth(3);
  h1000->Sumw2();
  cout << "MC = " << h6->GetSumOfWeights() << ", data = " << h1000->GetSumOfWeights() << ", ratio = " << h1000->GetSumOfWeights()/h6->GetSumOfWeights() << endl;
  h1000->Divide(h6);
  h1000->SetMaximum(2.0);
  h1000->SetMinimum(0.0);
  if(rangelo != 0 || rangehi != 1)
    h1000->GetXaxis()->SetRangeUser(rangelo,rangehi);
  h1000->SetStats(0);
  h1000->SetTitle(thetitle);
  h1000->Draw("e");

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

  TString outplotname = "validationplots2017BCDEF_ntuplesv2recalcmjcutjerallhltfixptetacuts_preselection_" + filetitle + ".png";
  c1->SaveAs(outplotname);

  // Signal MC only
  //  TCanvas *c3 = new TCanvas("c3","c3");
  //  h7->Draw("hist");
  //  ha->Draw("hist");
}

void PlotStackAll()
{
  PlotStack2(1);
  PlotStack2(2);
  PlotStack2(3);
  PlotStack2(4);
  PlotStack2(5);
  PlotStack2(6);
  PlotStack2(7);
  PlotStack2(8);
  PlotStack2(9);
  PlotStack2(13);
  PlotStack2(14);
  PlotStack2(15);
  PlotStack2(16);
  PlotStack2(17);
  PlotStack2(18);
  PlotStack2(19);
  PlotStack2(20);
}
