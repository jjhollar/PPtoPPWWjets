/*
 * Note (Aug 20, 2020): txt files and cross sections/numbers here are up to date for 2017 re-MiniAOD. 
 * The proton distributions for mixing are still the old ones, to be updated.
 */
void SimpleMixer(Int_t mcsample = -1, Int_t remix = 1)
{
  Float_t lumi2017 = 37.175;
  Float_t eqlumi = 0.0;

  TString centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD1000to1400.txt";

  if(mcsample == 0)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD300to470_2017.txt";
      eqlumi = 11896906.0/(6838*1.14405*1000.0);
    }
  if(mcsample == 1)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD470to600_2017.txt";
      eqlumi = 27705084.0/(551.1*1.17619*1000.0);
    }
  
  if(mcsample == 2)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD600to800_2017.txt";
      eqlumi = 5329382.0/(156.4*1.19501*1000.0);
    }
  if(mcsample == 3)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD800to1000_2017.txt";
      eqlumi = 39525104.0/(32.293*1000.0);
    }
  if(mcsample == 4)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD1000to1400_2017.txt";

      eqlumi = 14619206.0/(7.466*1.26149*1000.0);
    }
  if(mcsample == 5)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_QCD1400to1800_2017.txt";
      eqlumi = 14286.0/(0.6481*1.30019*1000.0);
    }
  if(mcsample == 6)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_ttbar_2017.txt";
      eqlumi = 35540872.0/(377.96*1000.0);
    }
  if(mcsample == 7)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_wjets_2017.txt";
      eqlumi = 8081153.0/(33.7*1000.0);
    }
  if(mcsample == 8)
    {
      centralfile = "/tmp/jjhollar/MC_EventsForMixing_zjets_2017.txt";
      eqlumi = 9783887.0/(14.6*1000.0);
    }
  
  ifstream ifs(centralfile);

  TFile *f;
  //  f = TFile::Open("NewMixingDistributions2017.root"); 
  f = TFile::Open("NewMixingDistributions2016.root");

  TH1D *hn45 = (TH1D *)f->Get("mtpl_multi_S45");
  TH1D *hn56 = (TH1D *)f->Get("mtpl_multi_S56");
  TH1D *hxi45 = (TH1D *)f->Get("xi_multi_S45");
  TH1D *hxi56 = (TH1D *)f->Get("xi_multi_S56");

  Int_t channel = 0;
  unsigned int PU = 0;
  Float_t PUweight = 0;
  Float_t mww = 0;
  Float_t yww = 0;
  Int_t run = 0;
  Int_t ls = 0;
  Int_t event = 0;

  Float_t acop = 0;
  Float_t jetptbal = 0;
  Float_t jetmass1 = 0;
  Float_t jetmass2 = 0;
  Float_t taut21ddt1 = 0;
  Float_t taut21ddt2 = 0;
  Float_t xijets1 = 0;
  Float_t xijets2 = 0;

  Float_t acopcut = 0.01;
  Float_t mwlowcut = 65.0;
  Float_t mwhicut = 105.0;
  Float_t tau21cut = 0.75;

  Float_t kseniammatchcut = 0.11506000;
  Float_t kseniarapmatchcut = 0.057220000;


  TH2F *hmresdy = new TH2F("hmresdy","hmresdy",500,-5,5,500,-5,5);
  TH1F *hmjj = new TH1F("hmjj","hmjj",25,0,2500);

  Int_t i = 0;
  Int_t dummy1 = 0;
  Int_t dummy2 = 0;

  while(!ifs.eof())
    {
      Float_t xi45 = 0;
      Float_t xi56 = 0;

      ifs >> channel >> PU >> PUweight >> mww >> yww
           >> acop >> jetptbal
           >> jetmass1  >> jetmass2
           >> taut21ddt1 >> taut21ddt2
           >> xijets1 >> xijets2
	  >> run >> ls  >> event
	  >> dummy1 >> dummy2;

      if(i % 10000 == 0)
	{
	  std::cout << "i = " << i << std::endl;
	  std::cout << "acop = " << acop << std::endl;
	}

      if( ifs.eof() ) break;

      for(Int_t j = 0; j < remix; j++)
	{
	  Double_t n45 = hn45->GetRandom(); 
	  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
	  Double_t n56 = hn56->GetRandom();
	  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
	  if(n45 > 0.5 && n56 > 0.5 && xi45 >= 0.05 && xi56 >= 0.05)
	    {
	      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
	      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
	      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
	      if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
		{
		  hmresdy->Fill(1-(mww/mpp),ypp-yww,PUweight);
		  if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww) < kseniarapmatchcut)
		    hmjj->Fill(mww,PUweight);
		}
	    }
	}
      i++;
    }

  //  hmresdy->Rebin2D(4,4);
  hmresdy->GetXaxis()->SetRangeUser(-3,3);
  hmresdy->GetYaxis()->SetRangeUser(-1.5,1.5);

  hmresdy->Scale(lumi2017/eqlumi/remix);
  hmresdy->SetMarkerStyle(20);
  hmresdy->Draw("colz");
  TBox *b1 = new TBox(-0.10,-0.06,0.10,0.06);
  b1->SetLineColor(2); b1->SetLineWidth(3); b1->SetFillStyle(0); b1->Draw("same");
  TBox *b2 = new TBox(-1,-0.5,1,0.5);
  b2->SetLineColor(2); b2->SetLineWidth(3); b2->SetLineStyle(2); b2->SetFillStyle(0); b2->Draw("same");

  Float_t scaledsignalbox = hmresdy->Integral(hmresdy->GetXaxis()->FindBin(-1*kseniammatchcut),hmresdy->GetXaxis()->FindBin(1*kseniammatchcut), 
					      hmresdy->GetYaxis()->FindBin(-1*kseniarapmatchcut), hmresdy->GetYaxis()->FindBin(1*kseniarapmatchcut));


  hmjj->Sumw2(); hmjj->Scale(lumi2017/eqlumi/remix); hmjj->SetLineWidth(3); hmjj->SetLineColor(9); hmjj->SetFillColor(9); hmjj->SetMaximum(30); 
  //  hmjj->Draw("hist");

  std::cout << "N(bkg in signal region) = " << scaledsignalbox << " for lumi=" << lumi2017 << std::endl;
}

void AllSimpleMixer(Int_t remix = 1, Int_t year = 2017, Int_t bosons = 1)
{
  Float_t lumi2017 = 37.175;
  Float_t eqlumi02017 = 11896906.0/(6838*1.14405*1000.0);
  Float_t eqlumi12017 = 27705084.0/(551.1*1.17619*1000.0);
  Float_t eqlumi22017 = 5329382.0/(156.4*1.19501*1000.0);
  Float_t eqlumi32017 = 39525104.0/(32.293*1000.0);
  Float_t eqlumi42017 = 14619206.0/(7.466*1.26149*1000.0);
  Float_t eqlumi52017 = 14286.0/(0.6481*1.30019*1000.0);
  Float_t eqlumi62017 = 35540872.0/(377.96*1000.0);
  Float_t eqlumi72017 = 8081153.0/(33.7*1000.0);
  Float_t eqlumi82017 = 9783887.0/(14.6*1000.0);

  Float_t lumi2016 = 10.016;
  Float_t eqlumi02016 = 18319816.0/(6830.0*1000.0);
  Float_t eqlumi12016 = 3959986.0/(642.1*1000.0);
  Float_t eqlumi22016 = 3896412.0/(185.9*1000.0);
  Float_t eqlumi32016 = 15704980.0/(32.293*1000.0);
  Float_t eqlumi42016 = 2999069.0/(9.4183*1000.0);
  Float_t eqlumi52016 = 335704.0/(0.84265*1000.0);
  Float_t eqlumi62016 = 38426513.0/(66.85*1000.0);
  Float_t eqlumi72016 = 1026587.0/(98.4*1000.0);
  Float_t eqlumi82016 = 1000000.0/(41.3*1000.0);
  Float_t eqlumi92016 = 24577608.0/(21.3*1000.0);

  Float_t lumi2018 = 52.871;
  Float_t eqlumi02018 = 10828000.0/(6838.0*1.14405*1000.0);
  Float_t eqlumi12018 = 14952000.0/(551.1*1.17619*1000.0);
  Float_t eqlumi22018 = 40367000.0/(156.4*1.19501*1000.0);
  Float_t eqlumi32018 = 23097000.0/(32.293*1000.0);
  Float_t eqlumi42018 = 8121000.0/(7.466*1.26149*1000.0);
  Float_t eqlumi52018 = 1944000.0/(0.6481*1.30019*1000.0);
  Float_t eqlumi62018 = 134160000.0/(377.96*1000.0);
  Float_t eqlumi72018 = 9828980.0/(33.7*1000.0);
  Float_t eqlumi82018 = 7857468.0/(14.6*1000.0);



  TString centralfile0 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD300to470_2018.txt";
  Float_t eqlumi0 = eqlumi02017;
  TString centralfile1 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD470to600_2017.txt";
  Float_t eqlumi1 = eqlumi12017;
  TString centralfile2 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD600to800_2017.txt";
  Float_t eqlumi2 = eqlumi22017;
  TString centralfile3 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD800to1000_2017.txt";
  Float_t eqlumi3 = eqlumi32017; 
  TString centralfile4 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1000to1400_2017.txt";
  Float_t eqlumi4 = eqlumi42017;
  TString centralfile5 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1400to1800_2017.txt";
  Float_t eqlumi5 = eqlumi52017;
  TString centralfile6 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_ttbar_2017.txt";
  Float_t eqlumi6 = eqlumi62017;
  TString centralfile7 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_wjets_2017.txt";
  Float_t eqlumi7 = eqlumi72017;
  TString centralfile8 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_zjets_2017.txt";
  Float_t eqlumi8 = eqlumi82017;
  TString centralfile9 = "";
  Float_t eqlumi9 = 0;

  TString scentralfile1 = "/eos/cms/store/group/phys_smp/HadronicVV/signalSamples_v3/MC_EventsForMixing_signal_WWA0W5E-6_2018D.txt";
  Float_t seqlumi1 = 10.;

  Float_t lumi = lumi2017;

  if(year == 2016)
    {
      centralfile0 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD300to470_2016.txt";
      eqlumi0 = eqlumi02016;
      centralfile1 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD470to600_2016.txt";
      eqlumi1 = eqlumi12016;
      centralfile2 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD600to800_2016.txt";
      eqlumi2 = eqlumi22016;
      centralfile3 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD800to1000_2016.txt";
      eqlumi3 = eqlumi32016;
      centralfile4 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1000to1400_2016.txt";
      eqlumi4 = eqlumi42016;
      centralfile5 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1400to1800_2016.txt";
      eqlumi5 = eqlumi52016;
      centralfile6 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_ttbar700to1000_2016.txt";
      eqlumi6 = eqlumi62016;
      centralfile7 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_wjets_2016.txt";
      eqlumi7 = eqlumi72016;
      centralfile8 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_zjets_2016.txt";
      eqlumi8 = eqlumi82016;
      centralfile9 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_ttbar1000inf_2016.txt";
      eqlumi9 = eqlumi92016;

      lumi = lumi2016;
    }
  if(year == 2018)
    {
      centralfile0 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD300to470_2018.txt";
      eqlumi0 = eqlumi02018;
      centralfile1 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD470to600_2018.txt";
      eqlumi1 = eqlumi12018;
      centralfile2 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD600to800_2018.txt";
      eqlumi2 = eqlumi22018;
      centralfile3 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD800to1000_2018.txt";
      eqlumi3 = eqlumi32018;
      centralfile4 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1000to1400_2018.txt";
      eqlumi4 = eqlumi42018;
      centralfile5 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_QCD1400to1800_2018.txt";
      eqlumi5 = eqlumi52018;
      centralfile6 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_ttbar_2018.txt";
      eqlumi6 = eqlumi62018;
      centralfile7 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_wjets_2018.txt";
      eqlumi7 = eqlumi72018;
      centralfile8 = "/eos/cms/store/group/phys_smp/HadronicVV/backgroundSamples/MC_EventsForMixing_zjets_2018.txt";
      eqlumi8 = eqlumi82018;

      lumi = lumi2018;
    }


  Float_t nbkg0;
  Float_t nbkg1;
  Float_t nbkg2;
  Float_t nbkg3;
  Float_t nbkg4;
  Float_t nbkg5;
  Float_t nbkg6;
  Float_t nbkg7;
  Float_t nbkg8;
  Float_t nbkg9;

  TFile *f;

  f = TFile::Open("NewMixingDistributions2017.root");
  if(year == 2016)
    f = TFile::Open("NewMixingDistributions2016.root");
  if(year == 2018)
    f = TFile::Open("NewMixingDistributions2018.root");


  TH1D *hn45 = (TH1D *)f->Get("mtpl_multi_S45");
  TH1D *hn56 = (TH1D *)f->Get("mtpl_multi_S56");
  TH1D *hxi45 = (TH1D *)f->Get("xi_multi_S45");
  TH1D *hxi56 = (TH1D *)f->Get("xi_multi_S56");

  Int_t channel = 0;
  unsigned int PU = 0;
  Float_t PUweight = 0;
  Float_t mww = 0;
  Float_t yww = 0;
  Int_t run = 0;
  Int_t ls = 0;
  Int_t event = 0;

  Float_t acop = 0;
  Float_t jetptbal = 0;
  Float_t jetmass1 = 0;
  Float_t jetmass2 = 0;
  Float_t taut21ddt1 = 0;
  Float_t taut21ddt2 = 0;
  Float_t xijets1 = 0;
  Float_t xijets2 = 0;
  Float_t rotatedprunedmasses = 0.0;

  Int_t dummy1 = 0; 
  Int_t dummy2 = 0;

  Float_t acopcut = 0.01;
  Float_t mwlowcut = 60.0;
  Float_t mwhicut = 107.0;
  Float_t mrotatedcut = 117.8;
  Float_t tau21cut = 0.75;

  Float_t kseniammatchcut = 0.11506000;
  Float_t kseniarapmatchcut = 0.057220000;
  
  TH2F *hmresdysum = new TH2F("hmresdysum","hmresdysum",500,-5,5,500,-5,5);
  TH2F *hmresdy0 = new TH2F("hmresdy0","hmresdy0",500,-5,5,500,-5,5);
  TH2F *hmresdy1 = new TH2F("hmresdy1","hmresdy1",500,-5,5,500,-5,5);
  TH2F *hmresdy2 = new TH2F("hmresdy2","hmresdy2",500,-5,5,500,-5,5);
  TH2F *hmresdy3 = new TH2F("hmresdy3","hmresdy3",500,-5,5,500,-5,5);
  TH2F *hmresdy4 = new TH2F("hmresdy4","hmresdy4",500,-5,5,500,-5,5);
  TH2F *hmresdy5 = new TH2F("hmresdy5","hmresdy5",500,-5,5,500,-5,5);
  TH2F *hmresdy6 = new TH2F("hmresdy6","hmresdy6",500,-5,5,500,-5,5);
  TH2F *hmresdy7 = new TH2F("hmresdy7","hmresdy7",500,-5,5,500,-5,5);
  TH2F *hmresdy8 = new TH2F("hmresdy8","hmresdy8",500,-5,5,500,-5,5);
  TH2F *hmresdy9 = new TH2F("hmresdy9","hmresdy9",500,-5,5,500,-5,5);


  TH1F *hmjjsum = new TH1F("hmjjsum","hmjjsum",250,0,5000);
  TH1F *hmjj0 = new TH1F("hmjj0","hmjj0",250,0,5000);
  TH1F *hmjj1 = new TH1F("hmjj1","hmjj1",250,0,5000);
  TH1F *hmjj2 = new TH1F("hmjj2","hmjj2",250,0,5000);
  TH1F *hmjj3 = new TH1F("hmjj3","hmjj3",250,0,5000);
  TH1F *hmjj4 = new TH1F("hmjj4","hmjj4",250,0,5000);
  TH1F *hmjj5 = new TH1F("hmjj5","hmjj5",250,0,5000);
  TH1F *hmjj6 = new TH1F("hmjj6","hmjj6",250,0,5000);
  TH1F *hmjj7 = new TH1F("hmjj7","hmjj7",250,0,5000);
  TH1F *hmjj8 = new TH1F("hmjj8","hmjj8",250,0,5000);
  TH1F *hmjj9 = new TH1F("hmjj9","hmjj9",250,0,5000);

  TH1F *shmjj1 = new TH1F("shmjj1","shmjj1",250,0,5000);

  TH1F *hmjjsumstack = new TH1F("hmjjsumstack","hmjjsumstack",250,0,5000);
  TH1F *hmjjqcd = new TH1F("hmjjqcd","hmjjqcd",250,0,5000);
  TH1F *hmjjwjets = new TH1F("hmjjwjets","hmjjwjet",250,0,5000);
  TH1F *hmjjzjets = new TH1F("hmjjzjets","hmjjzjets",250,0,5000);
  TH1F *hmjjttbar = new TH1F("hmjjttbar","hmjjttbar",250,0,5000);

  TH1F *hyjjsum = new TH1F("hyjjsum","hyjjsum",250,-5,5);
  TH1F *hyjj0 = new TH1F("hyjj0","hyjj0",250,-5,5);
  TH1F *hyjj1 = new TH1F("hyjj1","hyjj1",250,-5,5);
  TH1F *hyjj2 = new TH1F("hyjj2","hyjj2",250,-5,5);
  TH1F *hyjj3 = new TH1F("hyjj3","hyjj3",250,-5,5);
  TH1F *hyjj4 = new TH1F("hyjj4","hyjj4",250,-5,5);
  TH1F *hyjj5 = new TH1F("hyjj5","hyjj5",250,-5,5);
  TH1F *hyjj6 = new TH1F("hyjj6","hyjj6",250,-5,5);
  TH1F *hyjj7 = new TH1F("hyjj7","hyjj7",250,-5,5);
  TH1F *hyjj8 = new TH1F("hyjj8","hyjj8",250,-5,5);
  TH1F *hyjj9 = new TH1F("hyjj9","hyjj9",250,-5,5);

  TH1F *hyjjsumstack = new TH1F("hyjjsumstack","hyjjsumstack",250,-5,5);
  TH1F *hyjjqcd = new TH1F("hyjjqcd","hyjjqcd",250,-5,5);
  TH1F *hyjjwjets = new TH1F("hyjjwjets","hyjjwjet",250,-5,5);
  TH1F *hyjjzjets = new TH1F("hyjjzjets","hyjjzjets",250,-5,5);
  TH1F *hyjjttbar = new TH1F("hyjjttbar","hyjjttbar",250,-5,5);


  TH1F *hmjjanyprotonssum = new TH1F("hmjjanyprotonssum","hmjjanyprotonssum",250,0,5000);
  TH1F *hmjjanyprotons0 = new TH1F("hmjjanyprotons0","hmjjanyprotons0",250,0,5000);
  TH1F *hmjjanyprotons1 = new TH1F("hmjjanyprotons1","hmjjanyprotons1",250,0,5000);
  TH1F *hmjjanyprotons2 = new TH1F("hmjjanyprotons2","hmjjanyprotons2",250,0,5000);
  TH1F *hmjjanyprotons3 = new TH1F("hmjjanyprotons3","hmjjanyprotons3",250,0,5000);
  TH1F *hmjjanyprotons4 = new TH1F("hmjjanyprotons4","hmjjanyprotons4",250,0,5000);
  TH1F *hmjjanyprotons5 = new TH1F("hmjjanyprotons5","hmjjanyprotons5",250,0,5000);
  TH1F *hmjjanyprotons6 = new TH1F("hmjjanyprotons6","hmjjanyprotons6",250,0,5000);
  TH1F *hmjjanyprotons7 = new TH1F("hmjjanyprotons7","hmjjanyprotons7",250,0,5000);
  TH1F *hmjjanyprotons8 = new TH1F("hmjjanyprotons8","hmjjanyprotons8",250,0,5000);
  TH1F *hmjjanyprotons9 = new TH1F("hmjjanyprotons9","hmjjanyprotons9",250,0,5000);


  TH1F *hmjjcentralsum = new TH1F("hmjjcentralsum","hmjjcentralsum",250,0,5000);
  TH1F *hmjjcentral0 = new TH1F("hmjjcentral0","hmjjcentral0",250,0,5000);
  TH1F *hmjjcentral1 = new TH1F("hmjjcentral1","hmjjcentral1",250,0,5000);
  TH1F *hmjjcentral2 = new TH1F("hmjjcentral2","hmjjcentral2",250,0,5000);
  TH1F *hmjjcentral3 = new TH1F("hmjjcentral3","hmjjcentral3",250,0,5000);
  TH1F *hmjjcentral4 = new TH1F("hmjjcentral4","hmjjcentral4",250,0,5000);
  TH1F *hmjjcentral5 = new TH1F("hmjjcentral5","hmjjcentral5",250,0,5000);
  TH1F *hmjjcentral6 = new TH1F("hmjjcentral6","hmjjcentral6",250,0,5000);
  TH1F *hmjjcentral7 = new TH1F("hmjjcentral7","hmjjcentral7",250,0,5000);
  TH1F *hmjjcentral8 = new TH1F("hmjjcentral8","hmjjcentral8",250,0,5000);
  TH1F *hmjjcentral9 = new TH1F("hmjjcentral9","hmjjcentral9",250,0,5000);

  TH2F *hmyjjcentralsum = new TH2F("hmyjjcentralsum","hmyjjcentralsum",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral0 = new TH2F("hmyjjcentral0","hmyjjcentral0",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral1 = new TH2F("hmyjjcentral1","hmyjjcentral1",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral2 = new TH2F("hmyjjcentral2","hmyjjcentral2",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral3 = new TH2F("hmyjjcentral3","hmyjjcentral3",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral4 = new TH2F("hmyjjcentral4","hmyjjcentral4",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral5 = new TH2F("hmyjjcentral5","hmyjjcentral5",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral6 = new TH2F("hmyjjcentral6","hmyjjcentral6",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral7 = new TH2F("hmyjjcentral7","hmyjjcentral7",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral8 = new TH2F("hmyjjcentral8","hmyjjcentral8",250,0,5000,250,-5,5);
  TH2F *hmyjjcentral9 = new TH2F("hmyjjcentral9","hmyjjcentral9",250,0,5000,250,-5,5);

  TH1F *nbkgbyexperiment = new TH1F("nbkgbyexperiment","nbkgbyexperiment",100,0,100);

  Float_t xicut = 0.05;
  Int_t ntotal = 0;
  Int_t ntwoarms = 0;
  Int_t ntwoarmsxi5 = 0;

  Float_t nbkgaveragetotal = 0.0;

  Int_t subremix = 1;

  for(Int_t i = 0; i < remix; i++)
    {
      ifstream ifs0(centralfile0);
      ifstream ifs1(centralfile1);
      ifstream ifs2(centralfile2);
      ifstream ifs3(centralfile3);
      ifstream ifs4(centralfile4);
      ifstream ifs5(centralfile5);
      ifstream ifs6(centralfile6);
      ifstream ifs7(centralfile7);
      ifstream ifs8(centralfile8);
      ifstream ifs9(centralfile9);

      nbkg0 = 0.0;
      nbkg1 = 0.0;
      nbkg2 = 0.0;
      nbkg3 = 0.0;
      nbkg4 = 0.0;
      nbkg5 = 0.0;
      nbkg6 = 0.0;
      nbkg7 = 0.0;
      nbkg8 = 0.0;
      nbkg9 = 0.0;

      cout << "Experiment #" << i << endl;

      // QCD                                                                                                                                                                                  
      cout << "\tRunning QCD sample0" << endl;
      while(!ifs0.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs0 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;

	  if( ifs0.eof() ) break;
	  rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) && 
	     (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) && 
	     ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral0->Fill(mww,PUweight);
	      hmyjjcentral0->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //              std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;                  
		      hmjjanyprotons0->Fill(mww);
		      hmresdy0->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj0->Fill(mpp,PUweight);
			  hyjj0->Fill(ypp,PUweight);
			  nbkg0 += PUweight;
			}
		    }
		}
	    }
	}

      cout << "\tRunning QCD sample1" << endl;
      while(!ifs1.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs1 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs1.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral1->Fill(mww,PUweight);
	      hmyjjcentral1->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons1->Fill(mww);
		      hmresdy1->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj1->Fill(mpp,PUweight);
                          hyjj1->Fill(ypp,PUweight);
                          nbkg1 += PUweight;
			}
		    }
		}
	    }
	}

      cout << "\tRunning QCD sample2" << endl;
      while(!ifs2.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs2 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs2.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral2->Fill(mww,PUweight);
	      hmyjjcentral2->Fill(mww,yww,PUweight);
	      
	      // JH
	      ntotal++;
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  
		  // JH
		  if((n45 > 0.5) && (n56 > 0.5))
		    ntwoarms++;
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    ntwoarmsxi5++;	    
		  
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons2->Fill(mww);
		      hmresdy2->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj2->Fill(mpp,PUweight);
                          hyjj2->Fill(ypp,PUweight);
                          nbkg2 += PUweight;
			}
		    }
		}
	    }
	}
	 
      cout << "\tRunning QCD sample3" << endl;
      while(!ifs3.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs3 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs3.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral3->Fill(mww,PUweight);
	      hmyjjcentral3->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons3->Fill(mww);
		      hmresdy3->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj3->Fill(mpp,PUweight);
                          hyjj3->Fill(ypp,PUweight);
			  nbkg3 += PUweight;
			}
		    }
		}
	    }
	}

      cout << "\tRunning QCD sample4" << endl;
      while(!ifs4.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs4 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs4.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral4->Fill(mww,PUweight);
	      hmyjjcentral4->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons4->Fill(mww);
		      hmresdy4->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj4->Fill(mpp,PUweight);
                          hyjj4->Fill(ypp,PUweight);
                          nbkg4 += PUweight;
			}
		    }
		}
	    }
	}

      cout << "\tRunning QCD sample5" << endl;
      while(!ifs5.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs5 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs5.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral5->Fill(mww,PUweight);
	      hmyjjcentral5->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons5->Fill(mww);
		      hmresdy5->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj5->Fill(mpp,PUweight);
                          hyjj5->Fill(ypp,PUweight);
                          nbkg5 += PUweight;
			}
		    }
		}
	    }
	}    
      
      // ttbar
      cout << "\tRunning ttbar" << endl;
      while(!ifs6.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs6 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs6.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral6->Fill(mww,PUweight);
	      hmyjjcentral6->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //              std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;                                                                       
		      hmjjanyprotons6->Fill(mww);
		      hmresdy6->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj6->Fill(mpp,PUweight);
                          hyjj6->Fill(ypp,PUweight);
                          nbkg6 += PUweight;
			}
		    }
		}
	    }
	}

      // For 2016 only we have 2 ttbar bins
      if(year == 2016)
	{
	  while(!ifs9.eof())
	    {
	      Float_t xi45 = 0;
	      Float_t xi56 = 0;

	      ifs9 >> channel >> PU >> PUweight >> mww >> yww
		   >> acop >> jetptbal
		   >> jetmass1  >> jetmass2
		   >> taut21ddt1 >> taut21ddt2
		   >> xijets1 >> xijets2
		   >> run >> ls  >> event >> dummy1 >> dummy2;


	      if( ifs9.eof() ) break;                                                                                                                                             
	      rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

	      if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
		 (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
		 ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
		{
		  hmjjcentral9->Fill(mww,PUweight);
		  hmyjjcentral9->Fill(mww,yww,PUweight);

		  for(Int_t j = 0; j < subremix; j++)
		    {
		      int passes = 0;

		      Double_t n45 = hn45->GetRandom();
		      if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		      Double_t n56 = hn56->GetRandom();
		      if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		      if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
			{
			  Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
			  Float_t ypp = 0.5*TMath::Log(xi45/xi56);
			  //              std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;                                                      

			  hmjjanyprotons9->Fill(mww);
			  hmresdy9->Fill(1-(mww/mpp),ypp-yww,PUweight);
			  if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			    {
			      hmjj9->Fill(mpp,PUweight);
			      hyjj9->Fill(ypp,PUweight);
			      nbkg9 += PUweight;
			    }
			}
		    }
		}
	    }
	}

      // wjets
      cout << "\tRunning W+jets" << endl;
      
      while(!ifs7.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs7 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs7.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral7->Fill(mww,PUweight);
	      hmyjjcentral7->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //              std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;                                                                       
		      hmjjanyprotons7->Fill(mww);
		      hmresdy7->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj7->Fill(mpp,PUweight);
                          hyjj7->Fill(ypp,PUweight);
                          nbkg7 += PUweight;
			}
		    }
		}
	    }
	}
      // zjets
      cout << "\tRunning Z+jets" << endl;
      
      while(!ifs8.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs8 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event >> dummy1 >> dummy2;
	  
	  
	  if( ifs8.eof() ) break;
          rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);

          if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
             (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
             ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	    {
	      hmjjcentral8->Fill(mww,PUweight);
	      hmyjjcentral8->Fill(mww,yww,PUweight);
	      
	      for(Int_t j = 0; j < subremix; j++)
		{
		  int passes = 0;
		  
		  Double_t n45 = hn45->GetRandom();
		  if(n45 > 0.5) {xi45 = hxi45->GetRandom();}
		  Double_t n56 = hn56->GetRandom();
		  if(n56 > 0.5) {xi56 = hxi56->GetRandom();}
		  if(n45 > 0.5 && n56 > 0.5 && xi45 >= xicut && xi56 >= xicut)
		    {
		      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
		      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
		      //	      std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl;
		      hmjjanyprotons8->Fill(mww);
		      hmresdy8->Fill(1-(mww/mpp),ypp-yww,PUweight);
		      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
			{
			  hmjj8->Fill(mpp,PUweight);
                          hyjj8->Fill(ypp,PUweight);
                          nbkg8 += PUweight;
			}
		    }
		}
	    }
	}
      
      Float_t nbkgtotal = (nbkg0*lumi/eqlumi0)
	+(nbkg1*lumi/eqlumi1)
	+(nbkg2*lumi/eqlumi2)
	+(nbkg3*lumi/eqlumi3)
	+(nbkg4*lumi/eqlumi4)
	+(nbkg5*lumi/eqlumi5)
	+(nbkg6*lumi/eqlumi6)
	+(nbkg7*lumi/eqlumi7)
	+(nbkg8*lumi/eqlumi8);
      if(year == 2016)
	{
	  nbkgtotal += (nbkg9*lumi/eqlumi9);
	}
      
      std::cout << "\tExperiment N(bkg) = " << nbkgtotal << std::endl;
      std::cout << "\t\tQCD = " << (nbkg0*lumi/eqlumi0) << " + " << (nbkg1*lumi/eqlumi1) << " + " 
		<< (nbkg2*lumi/eqlumi2) << " + " << (nbkg3*lumi/eqlumi3) << " + " << (nbkg4*lumi/eqlumi4)
		<< " + " << (nbkg5*lumi/eqlumi5) << std::endl;

      
      nbkgaveragetotal += nbkgtotal;
      nbkgbyexperiment->Fill(nbkgtotal);
    }

  // Signal MC
  ifstream sifs1(scentralfile1);

  while(!sifs1.eof())
    {
      Float_t xi45 = 0;
      Float_t xi56 = 0;
      
      sifs1 >> channel >> PU >> PUweight >> mww >> yww
	    >> acop >> jetptbal
	    >> jetmass1  >> jetmass2
	    >> taut21ddt1 >> taut21ddt2
	    >> xijets1 >> xijets2
	    >> run >> ls  >> event >> xi45 >> xi56;
      
      
      if( sifs1.eof() ) break;
      rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jetmass1) + (TMath::Sin(TMath::Pi()/4.0)*jetmass2);
      
      if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
	 (jetmass1>=mwlowcut && jetmass1 <=mwhicut) && (jetmass2>=mwlowcut && jetmass2 <=mwhicut) &&
	 ((rotatedprunedmasses <= mrotatedcut && bosons==1) || (rotatedprunedmasses>mrotatedcut && bosons==2)))
	{
	  if(xi45 >= xicut && xi56 >= xicut)
	    {
	      Float_t mpp = 13000.0*TMath::Sqrt(xi45*xi56);
	      Float_t ypp = 0.5*TMath::Log(xi45/xi56);
	      //              std::cout << "Mass match = " << 1-(mww/mpp) << ", rapidity macth = " << ypp-yww << std::endl; \
              
	      if(fabs(1-(mww/mpp)) < kseniammatchcut && fabs(ypp-yww)<kseniarapmatchcut)
		{
		  shmjj1->Fill(mpp,PUweight);
		}
	    }
	}
    }
  // JH
  std::cout << "Total events = " << ntotal << ", 2-arm events = " << ntwoarms/remix << " (" << 1.0*ntwoarms/ntotal/remix << "), 2-arm events with xi>0.05 = " 
	    << ntwoarmsxi5/remix << " (" << 1.0*ntwoarmsxi5/ntotal/remix << ")" << std::endl;


  hmresdy0->Sumw2(); hmresdy1->Sumw2(); hmresdy2->Sumw2(); hmresdy3->Sumw2(); hmresdy4->Sumw2(); hmresdy5->Sumw2();
  hmresdy6->Sumw2(); hmresdy7->Sumw2(); hmresdy8->Sumw2(); hmresdy9->Sumw2();

  hmresdy0->Scale(lumi/eqlumi0/remix/subremix);
  hmresdy0->SetMarkerStyle(20);
  hmresdy1->Scale(lumi/eqlumi1/remix/subremix);
  hmresdy1->SetMarkerStyle(20);
  hmresdy2->Scale(lumi/eqlumi2/remix/subremix);
  hmresdy2->SetMarkerStyle(20);
  hmresdy3->Scale(lumi/eqlumi3/remix/subremix);
  hmresdy3->SetMarkerStyle(20);
  hmresdy4->Scale(lumi/eqlumi4/remix/subremix);
  hmresdy4->SetMarkerStyle(20);
  hmresdy5->Scale(lumi/eqlumi5/remix/subremix);
  hmresdy5->SetMarkerStyle(20);
  hmresdy6->Scale(lumi/eqlumi6/remix/subremix);
  hmresdy6->SetMarkerStyle(20);
  hmresdy7->Scale(lumi/eqlumi7/remix/subremix);
  hmresdy7->SetMarkerStyle(20);
  hmresdy8->Scale(lumi/eqlumi8/remix/subremix);
  hmresdy8->SetMarkerStyle(20);
  if(year == 2016)
    {
      hmresdy9->Scale(lumi/eqlumi9/remix/subremix);
      hmresdy9->SetMarkerStyle(20);
    }

  hmresdysum->Add(hmresdy0); hmresdysum->Add(hmresdy1); hmresdysum->Add(hmresdy2); hmresdysum->Add(hmresdy3); hmresdysum->Add(hmresdy4); hmresdysum->Add(hmresdy5);
  hmresdysum->Add(hmresdy6); hmresdysum->Add(hmresdy7); hmresdysum->Add(hmresdy8); 
  if(year == 2016)
    hmresdysum->Add(hmresdy9);

  TCanvas *c1 = new TCanvas("c1","c1");
  //  hmresdysum->Rebin2D(4,4);
  hmresdysum->GetXaxis()->SetRangeUser(-3,3);
  hmresdysum->GetYaxis()->SetRangeUser(-1.5,1.5);

  if(bosons == 1)
    {
      hmresdysum->SetXTitle("1 - m(W_{j}W_{j})/m(pp)");
      hmresdysum->SetYTitle("y(pp) - y(W_{j}W_{j})");
    }
  if(bosons == 2)
    {
      hmresdysum->SetXTitle("1 - m(Z_{j}Z_{j})/m(pp)");
      hmresdysum->SetYTitle("y(pp) - y(Z_{j}Z_{j})");
    }

  hmresdysum->GetXaxis()->SetTitleSize(0.04); hmresdysum->GetXaxis()->SetTitleOffset(1.2);
  hmresdysum->GetYaxis()->SetTitleSize(0.04);
  hmresdysum->SetStats(0);
  hmresdysum->SetTitle("Event mixing background, L=37.2fb^{-1}");
  hmresdysum->Draw("colz");

  if(year == 2017)
    CMS_lumi2016(c1,0,0,"2017, L = 37.2 fb^{-1}");
  if(year == 2016)
    CMS_lumi2016(c1,0,0,"2016, L = 10.2 fb^{-1}");
  if(year == 2018)
    CMS_lumi2016(c1,0,0,"2018, L = 52.9 fb^{-1}");


  TBox *b1 = new TBox(-0.10,-0.06,0.10,0.06);
  b1->SetLineWidth(3); b1->SetFillStyle(0); b1->Draw("same");
  TBox *b2 = new TBox(-1,-0.5,1,0.5);
  b2->SetLineWidth(3); b2->SetLineStyle(2); b2->SetFillStyle(0); b2->Draw("same");

  Float_t scaledsignalbox = hmresdysum->Integral(hmresdysum->GetXaxis()->FindBin(-1*kseniammatchcut),hmresdysum->GetXaxis()->FindBin(1*kseniammatchcut),
                                              hmresdysum->GetYaxis()->FindBin(-1*kseniarapmatchcut), hmresdysum->GetYaxis()->FindBin(1*kseniarapmatchcut));


  Float_t unblindnormregion = (hmresdysum->Integral(hmresdysum->GetXaxis()->FindBin(-5),hmresdysum->GetXaxis()->FindBin(-5),
						    hmresdysum->GetXaxis()->FindBin(5),hmresdysum->GetXaxis()->FindBin(-0.5))) + 
    (hmresdysum->Integral(hmresdysum->GetXaxis()->FindBin(-5),hmresdysum->GetXaxis()->FindBin(-0.5),
			  hmresdysum->GetXaxis()->FindBin(-1),hmresdysum->GetXaxis()->FindBin(0.5))) +
    (hmresdysum->Integral(hmresdysum->GetXaxis()->FindBin(-5),hmresdysum->GetXaxis()->FindBin(0.5),
			  hmresdysum->GetXaxis()->FindBin(5),hmresdysum->GetXaxis()->FindBin(5)));



  std::cout << "N(bkg in signal region, mean for L=" << lumi << ") = " << nbkgaveragetotal/remix << std::endl;
  std::cout << "N(bkg in signal region from 2D histogram) = " << scaledsignalbox << std::endl;
  std::cout << "N(unblinded normalization region = " << unblindnormregion << " for lumi=" << lumi << std::endl;

  // Mass
  hmjj0->Scale(lumi/eqlumi0/remix/subremix);
  hmjj1->Scale(lumi/eqlumi1/remix/subremix);
  hmjj2->Scale(lumi/eqlumi2/remix/subremix);
  hmjj3->Scale(lumi/eqlumi3/remix/subremix);
  hmjj4->Scale(lumi/eqlumi4/remix/subremix);
  hmjj5->Scale(lumi/eqlumi5/remix/subremix);
  hmjj6->Scale(lumi/eqlumi6/remix/subremix);
  hmjj7->Scale(lumi/eqlumi7/remix/subremix);
  hmjj8->Scale(lumi/eqlumi8/remix/subremix);
  if(year == 2016)
    hmjj9->Scale(lumi/eqlumi9/remix/subremix);

  hmjjsum->Add(hmjj0);
  hmjjsum->Add(hmjj1);
  hmjjsum->Add(hmjj2);
  hmjjsum->Add(hmjj3);
  hmjjsum->Add(hmjj4);
  hmjjsum->Add(hmjj5);
  hmjjsum->Add(hmjj6);
  hmjjsum->Add(hmjj7);
  hmjjsum->Add(hmjj8);
  if(year == 2016)
    hmjjsum->Add(hmjj9);

  hmjjqcd->Add(hmjj0); 
  hmjjqcd->Add(hmjj1);
  hmjjqcd->Add(hmjj2);
  hmjjqcd->Add(hmjj3);
  hmjjqcd->Add(hmjj4);
  hmjjqcd->Add(hmjj5);
  hmjjqcd->Add(hmjj6);
  hmjjqcd->Add(hmjj7);
  hmjjqcd->Add(hmjj8);
  if(year == 2016)
    hmjjqcd->Add(hmjj9);

  hmjjwjets->Add(hmjj7);
  hmjjwjets->Add(hmjj8);
  hmjjwjets->Add(hmjj6);
  if(year == 2016)
    hmjjwjets->Add(hmjj9);

  hmjjzjets->Add(hmjj8);
  hmjjzjets->Add(hmjj7);
  if(year == 2016)
    hmjjzjets->Add(hmjj9);

  hmjjttbar->Add(hmjj7);
  if(year == 2016)
    hmjjttbar->Add(hmjj9);

  /*
  hmjjqcd->Rebin(10);
  hmjjwjets->Rebin(10);
  hmjjzjets->Rebin(10);
  hmjjttbar->Rebin(10);
  */
  hmjjqcd->Rebin(5);                                                                                                                    
  hmjjwjets->Rebin(5);                                                                                                                  
  hmjjzjets->Rebin(5);                                                                                                                  
  hmjjttbar->Rebin(5);                                                                                                                  

  hmjjqcd->GetXaxis()->SetRangeUser(1000.0,2500);
  hmjjqcd->SetFillColor(kAzure+2);
  hmjjwjets->GetXaxis()->SetRangeUser(1000.0,2500);
  hmjjwjets->SetFillColor(kGreen+2);
  hmjjzjets->GetXaxis()->SetRangeUser(1000.0,2500);
  hmjjzjets->SetFillColor(kYellow+2);
  hmjjttbar->GetXaxis()->SetRangeUser(1000.0,2500);
  hmjjttbar->SetFillColor(kOrange+2);

  // Rapidity
  hyjj0->Scale(lumi/eqlumi0/remix/subremix);
  hyjj1->Scale(lumi/eqlumi1/remix/subremix);
  hyjj2->Scale(lumi/eqlumi2/remix/subremix);
  hyjj3->Scale(lumi/eqlumi3/remix/subremix);
  hyjj4->Scale(lumi/eqlumi4/remix/subremix);
  hyjj5->Scale(lumi/eqlumi5/remix/subremix);
  hyjj6->Scale(lumi/eqlumi6/remix/subremix);
  hyjj7->Scale(lumi/eqlumi7/remix/subremix);
  hyjj8->Scale(lumi/eqlumi8/remix/subremix);
  if(year == 2016)
    hyjj9->Scale(lumi/eqlumi9/remix/subremix);

  hyjjsum->Add(hyjj0);
  hyjjsum->Add(hyjj1);
  hyjjsum->Add(hyjj2);
  hyjjsum->Add(hyjj3);
  hyjjsum->Add(hyjj4);
  hyjjsum->Add(hyjj5);
  hyjjsum->Add(hyjj6);
  hyjjsum->Add(hyjj7);
  hyjjsum->Add(hyjj8);
  if(year == 2016)
    hyjjsum->Add(hyjj9);

  hyjjqcd->Add(hyjj0);
  hyjjqcd->Add(hyjj1);
  hyjjqcd->Add(hyjj2);
  hyjjqcd->Add(hyjj3);
  hyjjqcd->Add(hyjj4);
  hyjjqcd->Add(hyjj5);
  hyjjqcd->Add(hyjj6);
  hyjjqcd->Add(hyjj7);
  hyjjqcd->Add(hyjj8);
  if(year == 2016)
    hyjjqcd->Add(hyjj9);

  hyjjwjets->Add(hyjj7);
  hyjjwjets->Add(hyjj8);
  hyjjwjets->Add(hyjj6);
  if(year == 2016)
    hyjjwjets->Add(hyjj9);

  hyjjzjets->Add(hyjj8);
  hyjjzjets->Add(hyjj7);
  if(year == 2016)
    hyjjzjets->Add(hyjj9);

  hyjjttbar->Add(hyjj7);
  if(year == 2016)
    hyjjttbar->Add(hyjj9);

  hyjjqcd->Rebin(5);
  hyjjwjets->Rebin(5);
  hyjjzjets->Rebin(5);
  hyjjttbar->Rebin(5);

  hyjjqcd->GetXaxis()->SetRangeUser(-1.5,1.5);
  hyjjqcd->SetFillColor(kAzure+2);
  hyjjwjets->GetXaxis()->SetRangeUser(-1.5,1.5);
  hyjjwjets->SetFillColor(kGreen+2);
  hyjjzjets->GetXaxis()->SetRangeUser(-1.5,1.5);
  hyjjzjets->SetFillColor(kYellow+2);
  hyjjttbar->GetXaxis()->SetRangeUser(-1.5,1.5);
  hyjjttbar->SetFillColor(kOrange+2);

  // Draw mass
  TCanvas *c2 = new TCanvas("c2","c2");
  hmjjsum->Sumw2(); hmjjsum->SetLineWidth(3); hmjjsum->SetLineColor(11); hmjjsum->SetFillColor(11); hmjjsum->SetMaximum(30);
  //  hmjjsum->SetXTitle("m(W_{j}W_{j}) [GeV]");
  hmjjsum->SetXTitle("m(pp) [GeV]");
  hmjjsum->SetYTitle("Events");

  hmjjqcd->Sumw2(); hmjjqcd->SetMaximum(30);
  //  hmjjqcd->SetXTitle("m(W_{j}W_{j}) [GeV]");
  hmjjqcd->SetXTitle("m(pp) [GeV]");                                                                                                                                                                 
  hmjjqcd->SetYTitle("Events");
  hmjjqcd->GetXaxis()->SetTitleSize(0.04);  hmjjqcd->GetXaxis()->SetTitleOffset(1.2);
  hmjjqcd->GetYaxis()->SetTitleSize(0.04);
  hmjjqcd->Draw("hist");
  hmjjwjets->Draw("histsame");
  hmjjzjets->Draw("histsame");
  hmjjttbar->Draw("histsame");

  // Signal MC
  shmjj1->Rebin(5);
  shmjj1->GetXaxis()->SetRangeUser(1000.0,2500);
  shmjj1->Scale(0.1); shmjj1->SetLineWidth(3); shmjj1->SetLineColor(6);
  //  shmjj1->Draw("histsame");

  TLegend *lg1 = new TLegend(0.6,0.6,0.9,0.9);
  hmjjqcd->SetMarkerStyle(0); hmjjqcd->SetLineWidth(0);
  hmjjwjets->SetMarkerStyle(0); hmjjwjets->SetLineWidth(0);
  hmjjzjets->SetMarkerStyle(0); hmjjzjets->SetLineWidth(0);
  hmjjttbar->SetMarkerStyle(0); hmjjttbar->SetLineWidth(0);

  lg1->AddEntry(hmjjqcd,"Pythia8 QCD (bins) + mixed protons");
  lg1->AddEntry(hmjjwjets,"Madgraph W+jets + mixed protons");
  lg1->AddEntry(hmjjzjets,"Madgraph Z+jets + mixed protons");
  lg1->AddEntry(hmjjttbar,"Powheg ttbar + mixed protons");
  lg1->Draw("same");

  if(year == 2017)
    CMS_lumi2016(c2,0,0,"2017, L = 37.2 fb^{-1}");
  if(year == 2016)
    CMS_lumi2016(c2,0,0,"2016, L = 10.2 fb^{-1}");
  if(year == 2018)
    CMS_lumi2016(c2,0,0,"2018, L = 52.9 fb^{-1}");


  //  hmjjsum->Draw("hist");

  hmjjcentral0->Scale(lumi/eqlumi0);
  hmjjcentral1->Scale(lumi/eqlumi1);
  hmjjcentral2->Scale(lumi/eqlumi2);
  hmjjcentral3->Scale(lumi/eqlumi3);
  hmjjcentral4->Scale(lumi/eqlumi4);
  hmjjcentral5->Scale(lumi/eqlumi5);
  hmjjcentral5->Scale(lumi/eqlumi6);
  hmjjcentral5->Scale(lumi/eqlumi7);
  hmjjcentral8->Scale(lumi/eqlumi8);
  if(year == 2016)
    hmjjcentral9->Scale(lumi/eqlumi9);

  hmyjjcentral0->Scale(lumi/eqlumi0);
  hmyjjcentral1->Scale(lumi/eqlumi1);
  hmyjjcentral2->Scale(lumi/eqlumi2);
  hmyjjcentral3->Scale(lumi/eqlumi3);
  hmyjjcentral4->Scale(lumi/eqlumi4);
  hmyjjcentral5->Scale(lumi/eqlumi5);
  hmyjjcentral5->Scale(lumi/eqlumi6);
  hmyjjcentral5->Scale(lumi/eqlumi7);
  hmyjjcentral8->Scale(lumi/eqlumi8);
  if(year == 2016)
    hmyjjcentral9->Scale(lumi/eqlumi9);


  hmjjanyprotons0->Scale(lumi/eqlumi0/remix/subremix);
  hmjjanyprotons1->Scale(lumi/eqlumi1/remix/subremix);
  hmjjanyprotons2->Scale(lumi/eqlumi2/remix/subremix);
  hmjjanyprotons3->Scale(lumi/eqlumi3/remix/subremix);
  hmjjanyprotons4->Scale(lumi/eqlumi4/remix/subremix);
  hmjjanyprotons5->Scale(lumi/eqlumi5/remix/subremix);
  hmjjanyprotons5->Scale(lumi/eqlumi6/remix/subremix);
  hmjjanyprotons5->Scale(lumi/eqlumi7/remix/subremix);
  hmjjanyprotons8->Scale(lumi/eqlumi8/remix/subremix);
  if(year == 2016)
    hmjjanyprotons9->Scale(lumi/eqlumi9/remix/subremix);

  hmjjcentralsum->Add(hmjjcentral0);
  hmjjcentralsum->Add(hmjjcentral1);
  hmjjcentralsum->Add(hmjjcentral2);
  hmjjcentralsum->Add(hmjjcentral3);
  hmjjcentralsum->Add(hmjjcentral4);
  hmjjcentralsum->Add(hmjjcentral5);
  hmjjcentralsum->Add(hmjjcentral6);
  hmjjcentralsum->Add(hmjjcentral7);
  hmjjcentralsum->Add(hmjjcentral8);
  if(year == 2016)
    hmjjcentralsum->Add(hmjjcentral9);
  hmjjcentralsum->Sumw2(); hmjjcentralsum->SetLineWidth(3); hmjjcentralsum->SetLineColor(9); hmjjcentralsum->SetFillColor(9); 

  hmyjjcentralsum->Add(hmyjjcentral0);
  hmyjjcentralsum->Add(hmyjjcentral1);
  hmyjjcentralsum->Add(hmyjjcentral2);
  hmyjjcentralsum->Add(hmyjjcentral3);
  hmyjjcentralsum->Add(hmyjjcentral4);
  hmyjjcentralsum->Add(hmyjjcentral5);
  hmyjjcentralsum->Add(hmyjjcentral6);
  hmyjjcentralsum->Add(hmyjjcentral7);
  hmyjjcentralsum->Add(hmyjjcentral8);
  if(year == 2016)
    hmyjjcentralsum->Add(hmyjjcentral9);
  hmyjjcentralsum->Sumw2(); hmyjjcentralsum->SetLineWidth(3); hmyjjcentralsum->SetLineColor(9); hmyjjcentralsum->SetFillColor(9);


  hmjjanyprotonssum->Add(hmjjanyprotons0);
  hmjjanyprotonssum->Add(hmjjanyprotons1);
  hmjjanyprotonssum->Add(hmjjanyprotons2);
  hmjjanyprotonssum->Add(hmjjanyprotons3);
  hmjjanyprotonssum->Add(hmjjanyprotons4);
  hmjjanyprotonssum->Add(hmjjanyprotons5);
  hmjjanyprotonssum->Add(hmjjanyprotons6);
  hmjjanyprotonssum->Add(hmjjanyprotons7);
  hmjjanyprotonssum->Add(hmjjanyprotons8);
  if(year == 2016)
    hmjjanyprotonssum->Add(hmjjanyprotons9);
  hmjjanyprotonssum->Sumw2(); hmjjanyprotonssum->SetLineWidth(3); hmjjanyprotonssum->SetLineColor(7); hmjjanyprotonssum->SetFillColor(7); 
  //  hmjjanyprotonssum->SetMaximum(5);


  //  hmjjcentralsum->Draw("hist");
  //  hmjjanyprotonssum->Draw("histsame");
  //  hmjjsum->Draw("hist");
  //  hmyjjcentralsum->Draw("colz");

  // Draw rapidity
  TCanvas *c2a = new TCanvas("c2a","c2a");
  hyjjsum->Sumw2(); hyjjsum->SetLineWidth(3); hyjjsum->SetLineColor(11); hyjjsum->SetFillColor(11); hyjjsum->SetMaximum(30);
  //  hyjjsum->SetXTitle("y(W_{j}W_{j}");
  hyjjsum->SetXTitle("y(pp)");
  hyjjsum->SetYTitle("Events");

  hyjjqcd->Sumw2(); hyjjqcd->SetMaximum(30);
  //  hyjjqcd->SetXTitle("y(W_{j}W_{j})");
  hyjjqcd->SetXTitle("y(pp)");
  hyjjqcd->SetYTitle("Events");
  hyjjqcd->GetXaxis()->SetTitleSize(0.04);  hyjjqcd->GetXaxis()->SetTitleOffset(1.2);
  hyjjqcd->GetYaxis()->SetTitleSize(0.04);
  hyjjqcd->Draw("hist");
  hyjjwjets->Draw("histsame");
  hyjjzjets->Draw("histsame");
  hyjjttbar->Draw("histsame");

  TLegend *lg1a = new TLegend(0.6,0.6,0.9,0.9);
  hyjjqcd->SetMarkerStyle(0); hyjjqcd->SetLineWidth(0);
  hyjjwjets->SetMarkerStyle(0); hyjjwjets->SetLineWidth(0);
  hyjjzjets->SetMarkerStyle(0); hyjjzjets->SetLineWidth(0);
  hyjjttbar->SetMarkerStyle(0); hyjjttbar->SetLineWidth(0);

  lg1a->AddEntry(hyjjqcd,"Pythia8 QCD (bins) + mixed protons");
  lg1a->AddEntry(hyjjwjets,"Madgraph W+jets + mixed protons");
  lg1a->AddEntry(hyjjzjets,"Madgraph Z+jets + mixed protons");
  lg1a->AddEntry(hyjjttbar,"Powheg ttbar + mixed protons");
  lg1a->Draw("same");

  if(year == 2017)
    CMS_lumi2016(c2,0,0,"2017, L = 37.2 fb^{-1}");
  if(year == 2016)
    CMS_lumi2016(c2,0,0,"2016, L = 10.2 fb^{-1}");
  if(year == 2018)
    CMS_lumi2016(c2,0,0,"2018, L = 52.9 fb^{-1}");

  TCanvas *c3 = new TCanvas("c3","c3");
  nbkgbyexperiment->SetLineColor(4); nbkgbyexperiment->SetLineWidth(3); 
  nbkgbyexperiment->SetXTitle("N(bkg., event mixing)");
  nbkgbyexperiment->SetYTitle("N(experiments)");
  nbkgbyexperiment->GetXaxis()->SetTitleSize(0.04); nbkgbyexperiment->GetXaxis()->SetTitleOffset(1.2);
  nbkgbyexperiment->GetYaxis()->SetTitleSize(0.04);

  nbkgbyexperiment->Draw("hist");

  cout << "Distribution of experiments: mean = " << nbkgbyexperiment->GetMean() << ", RMS = " << nbkgbyexperiment->GetRMS() << endl;

  if(year == 2017)
    CMS_lumi2016(c3,0,0,"2017, L = 37.2 fb^{-1}");
  if(year == 2016)
    CMS_lumi2016(c3,0,0,"2016, L = 10.2 fb^{-1}");
  if(year == 2018)
    CMS_lumi2016(c2,0,0,"2018, L = 52.9 fb^{-1}");

  if(year == 2018 && bosons == 1)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2018WW.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2018WW.C");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2018WW.pdf");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2018WW.C");
      c2a->SaveAs("EventMixingBackgroudYWWSignalRegion2018WW.C");
      c3->SaveAs("BackgroundEventMixingToys2018WW.pdf");
      c3->SaveAs("BackgroundEventMixingToys2018WW.C");
    }
  if(year == 2017 && bosons == 1)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2017WW.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2017WW.C");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2017WW.pdf");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2017WW.C");
      c2a->SaveAs("EventMixingBackgroudYWWSignalRegion2017WW.C");
      c3->SaveAs("BackgroundEventMixingToys2017WW.pdf");
      c3->SaveAs("BackgroundEventMixingToys2017WW.C");
    }
  if(year == 2016 && bosons == 1)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2016WW.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2016WW.C");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2016WW.pdf");
      c2->SaveAs("EventMixingBackgroudMWWSignalRegion2016WW.C");
      c2a->SaveAs("EventMixingBackgroudYWWSignalRegion2016WW.C");
      c3->SaveAs("BackgroundEventMixingToys2016WW.pdf");
      c3->SaveAs("BackgroundEventMixingToys2016WW.C");
    }
  if(year == 2018 && bosons == 2)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2018ZZ.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2018ZZ.C");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2018ZZ.pdf");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2018ZZ.C");
      c2a->SaveAs("EventMixingBackgroudYZZSignalRegion2018ZZ.C");
      c3->SaveAs("BackgroundEventMixingToys2018ZZ.pdf");
      c3->SaveAs("BackgroundEventMixingToys2018ZZ.C");
    }
  if(year == 2017 && bosons == 2)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2017ZZ.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2017ZZ.C");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2017ZZ.pdf");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2017ZZ.C");
      c2a->SaveAs("EventMixingBackgroudYZZSignalRegion2017ZZ.C");
      c3->SaveAs("BackgroundEventMixingToys2017ZZ.pdf");
      c3->SaveAs("BackgroundEventMixingToys2017ZZ.C");
    }
  if(year == 2016 && bosons == 2)
    {
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2016ZZ.pdf");
      c1->SaveAs("EventMixingBackgroudMassRapidityMatch2016ZZ.C");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2016ZZ.pdf");
      c2->SaveAs("EventMixingBackgroudMZZSignalRegion2016ZZ.C");
      c2a->SaveAs("EventMixingBackgroudYZZSignalRegion2016ZZ.C");
      c3->SaveAs("BackgroundEventMixingToys2016ZZ.pdf");
      c3->SaveAs("BackgroundEventMixingToys2016ZZ.C");
    }

}
