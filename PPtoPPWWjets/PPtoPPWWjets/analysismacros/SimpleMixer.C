/*
 * Note (Aug 20, 2020): txt files and cross sections/numbers here are up to date for 2017 re-MiniAOD. 
 * The proton distributions for mixing are still the old ones, to be updated.
 */
void SimpleMixer(Int_t mcsample = -1, Int_t remix = 1)
{
  Float_t lumi2017 = 37.175;
  Float_t eqlumi = 0.0;

  TString centralfile = "MC_EventsForMixing_QCD1000to1400.txt";

  if(mcsample == 0)
    {
      centralfile = "MC_EventsForMixing_QCD300to470_2017.txt";
      eqlumi = 11896906.0/(6838*1.14405*1000.0);
    }
  if(mcsample == 1)
    {
      centralfile = "MC_EventsForMixing_QCD470to600_2017.txt";
      eqlumi = 27705084.0/(551.1*1.17619*1000.0);
    }
  
  if(mcsample == 2)
    {
      centralfile = "MC_EventsForMixing_QCD600to800_2017.txt";
      eqlumi = 5329382.0/(156.4*1.19501*1000.0);
    }
  if(mcsample == 3)
    {
      centralfile = "MC_EventsForMixing_QCD800to1000_2017.txt";
      eqlumi = 39525104.0/(32.293*1000.0);
    }
  if(mcsample == 4)
    {
      centralfile = "MC_EventsForMixing_QCD1000to1400_2017.txt";

      eqlumi = 14619206.0/(7.466*1.26149*1000.0);
    }
  if(mcsample == 5)
    {
      centralfile = "MC_EventsForMixing_QCD1400to1800_2017.txt";
      eqlumi = 14286.0/(0.6481*1.30019*1000.0);
    }
  if(mcsample == 6)
    {
      centralfile = "MC_EventsForMixing_ttbar_2017.txt";
      eqlumi = 35540872.0/(377.96*1000.0);
    }
  if(mcsample == 7)
    {
      centralfile = "MC_EventsForMixing_wjets_2017.txt";
      eqlumi = 8081153.0/(33.7*1000.0);
    }
  if(mcsample == 8)
    {
      centralfile = "MC_EventsForMixing_zjets_2017.txt";
      eqlumi = 9783887.0/(14.6*1000.0);
    }
  
  ifstream ifs(centralfile);

  TFile *f;
  f = TFile::Open("DistrForMixing2017FIX.root"); 
  
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

  while(true)
    {
      Float_t xi45 = 0;
      Float_t xi56 = 0;

      ifs >> channel >> PU >> PUweight >> mww >> yww
           >> acop >> jetptbal
           >> jetmass1  >> jetmass2
           >> taut21ddt1 >> taut21ddt2
           >> xijets1 >> xijets2
           >> run >> ls  >> event;

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


  hmjj->Sumw2(); hmjj->Scale(lumi2017/eqlumi/remix); hmjj->SetLineWidth(3); hmjj->SetLineColor(9); hmjj->SetFillColor(9); hmjj->SetMaximum(5); 
  //  hmjj->Draw("hist");

  std::cout << "N(bkg in signal region) = " << scaledsignalbox << " for lumi=" << lumi2017 << std::endl;
}

void AllSimpleMixer(Int_t remix = 1)
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


  TString centralfile0 = "MC_EventsForMixing_QCD300to470_2017.txt";
  Float_t eqlumi0 = eqlumi02017;
  TString centralfile1 = "MC_EventsForMixing_QCD470to600_2017.txt";
  Float_t eqlumi1 = eqlumi12017;
  TString centralfile2 = "MC_EventsForMixing_QCD600to800_2017.txt";
  Float_t eqlumi2 = eqlumi22017;
  TString centralfile3 = "MC_EventsForMixing_QCD800to1000_2017.txt";
  Float_t eqlumi3 = eqlumi32017; 
  TString centralfile4 = "MC_EventsForMixing_QCD1000to1400_2017.txt";
  Float_t eqlumi4 = eqlumi42017;
  TString centralfile5 = "MC_EventsForMixing_QCD1400to1800_2017.txt";
  Float_t eqlumi5 = eqlumi52017;
  TString centralfile6 = "MC_EventsForMixing_ttbar_2017.txt";
  Float_t eqlumi6 = eqlumi62017;
  TString centralfile7 = "MC_EventsForMixing_wjets_2017.txt";
  Float_t eqlumi7 = eqlumi72017;
  TString centralfile8 = "MC_EventsForMixing_zjets_2017.txt";
  Float_t eqlumi8 = eqlumi82017;

  Float_t nbkg0;
  Float_t nbkg1;
  Float_t nbkg2;
  Float_t nbkg3;
  Float_t nbkg4;
  Float_t nbkg5;
  Float_t nbkg6;
  Float_t nbkg7;
  Float_t nbkg8;

  TFile *f;
  f = TFile::Open("DistrForMixing2017FIX.root");

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

  TH1F *hmjjsumstack = new TH1F("hmjjsumstack","hmjjsumstack",250,0,5000);
  TH1F *hmjjqcd = new TH1F("hmjjqcd","hmjjqcd",250,0,5000);
  TH1F *hmjjwjets = new TH1F("hmjjwjets","hmjjwjet",250,0,5000);
  TH1F *hmjjzjets = new TH1F("hmjjzjets","hmjjzjets",250,0,5000);
  TH1F *hmjjttbar = new TH1F("hmjjttbar","hmjjttbar",250,0,5000);



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

  TH1F *nbkgbyexperiment = new TH1F("nbkgbyexperiment","nbkgbyexperiment",25,0,25);

  Float_t xicut = 0.05;
  Int_t ntotal = 0;
  Int_t ntwoarms = 0;
  Int_t ntwoarmsxi5 = 0;

  Int_t subremix = 1;

  // QCD
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

      nbkg0 = 0;
      nbkg1 = 0;
      nbkg2 = 0;
      nbkg3 = 0;
      nbkg4 = 0;
      nbkg5 = 0;
      nbkg6 = 0;
      nbkg7 = 0;
      nbkg8 = 0;


      cout << "Experiment #" << i << endl;

      cout << "\tRunning QCD" << endl;
      while(!ifs0.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs0 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  //	  if( ifs0.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj0->Fill(mww,PUweight);
			  nbkg0 = PUweight;
			}
		    }
		}
	    }
	}
      
      while(!ifs1.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs1 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  
	  //	  if( ifs1.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj1->Fill(mww,PUweight);
                          nbkg1 = PUweight;
			}
		    }
		}
	    }
	}
      while(!ifs2.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs2 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  
	  //	  if( ifs2.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj2->Fill(mww,PUweight);
                          nbkg2 = PUweight;
			}
		    }
		}
	    }
	}
	 
      while(!ifs3.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs3 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs3.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj3->Fill(mww,PUweight);
			  nbkg3 = PUweight;
			}
		    }
		}
	    }
	}
      while(!ifs4.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs4 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs4.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj4->Fill(mww,PUweight);
                          nbkg4 = PUweight;
			}
		    }
		}
	    }
	}
      while(!ifs5.eof())
	{
	  Float_t xi45 = 0;
	  Float_t xi56 = 0;
	  
	  ifs5 >> channel >> PU >> PUweight >> mww >> yww
	       >> acop >> jetptbal
	       >> jetmass1  >> jetmass2
	       >> taut21ddt1 >> taut21ddt2
	       >> xijets1 >> xijets2
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs5.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj5->Fill(mww,PUweight);
                          nbkg5 = PUweight;
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
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs6.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj6->Fill(mww,PUweight);
                          nbkg6 = PUweight;
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
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs7.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj7->Fill(mww,PUweight);
                          nbkg7 = PUweight;
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
	       >> run >> ls  >> event;
	  
	  
	  //	      if( ifs8.eof() ) break;
	  
	  if((acop < acopcut) && (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
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
			  hmjj8->Fill(mww,PUweight);
                          nbkg8 = PUweight;
			}
		    }
		}
	    }
	}
      Float_t nbkgtotal = nbkg0+nbkg1+nbkg2+nbkg3+nbkg4+nbkg5+nbkg6+nbkg7+nbkg8;
      nbkgbyexperiment->Fill(nbkgtotal);
    }


  // JH
  std::cout << "Total events = " << ntotal << ", 2-arm events = " << ntwoarms/remix << " (" << 1.0*ntwoarms/ntotal/remix << "), 2-arm events with xi>0.05 = " 
	    << ntwoarmsxi5/remix << " (" << 1.0*ntwoarmsxi5/ntotal/remix << ")" << std::endl;


  hmresdy0->Sumw2(); hmresdy1->Sumw2(); hmresdy2->Sumw2(); hmresdy3->Sumw2(); hmresdy4->Sumw2(); hmresdy5->Sumw2();
  hmresdy6->Sumw2(); hmresdy7->Sumw2(); hmresdy8->Sumw2(); 

  hmresdy0->Scale(lumi2017/eqlumi0/remix);
  hmresdy0->SetMarkerStyle(20);
  hmresdy1->Scale(lumi2017/eqlumi1/remix);
  hmresdy1->SetMarkerStyle(20);
  hmresdy2->Scale(lumi2017/eqlumi2/remix);
  hmresdy2->SetMarkerStyle(20);
  hmresdy3->Scale(lumi2017/eqlumi3/remix);
  hmresdy3->SetMarkerStyle(20);
  hmresdy4->Scale(lumi2017/eqlumi4/remix);
  hmresdy4->SetMarkerStyle(20);
  hmresdy5->Scale(lumi2017/eqlumi5/remix);
  hmresdy5->SetMarkerStyle(20);
  hmresdy6->Scale(lumi2017/eqlumi6/remix);
  hmresdy6->SetMarkerStyle(20);
  hmresdy7->Scale(lumi2017/eqlumi7/remix);
  hmresdy7->SetMarkerStyle(20);
  hmresdy8->Scale(lumi2017/eqlumi8/remix);
  hmresdy8->SetMarkerStyle(20);

  hmresdysum->Add(hmresdy0); hmresdysum->Add(hmresdy1); hmresdysum->Add(hmresdy2); hmresdysum->Add(hmresdy3); hmresdysum->Add(hmresdy4); hmresdysum->Add(hmresdy5);
  hmresdysum->Add(hmresdy6); hmresdysum->Add(hmresdy7); hmresdysum->Add(hmresdy8);

  TCanvas *c1 = new TCanvas("c1","c1");
  //  hmresdysum->Rebin2D(4,4);
  hmresdysum->GetXaxis()->SetRangeUser(-3,3);
  hmresdysum->GetYaxis()->SetRangeUser(-1.5,1.5);

  hmresdysum->SetXTitle("1 - m(W_{j}W_{j})/m(pp)");
  hmresdysum->SetYTitle("y(pp) - y(W_{j}W_{j})");
  hmresdysum->GetXaxis()->SetTitleSize(0.04); hmresdysum->GetXaxis()->SetTitleOffset(1.2);
  hmresdysum->GetYaxis()->SetTitleSize(0.04);
  hmresdysum->SetStats(0);
  hmresdysum->SetTitle("Event mixing background, L=37.2fb^{-1}");
  hmresdysum->Draw("colz");

  CMS_lumi2016(c1,0,0,"2017, L = 37.2 fb^{-1}");

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



  std::cout << "N(bkg in signal region) = " << scaledsignalbox << " for lumi=" << lumi2017 << std::endl;
  std::cout << "N(unblinded normalization region = " << unblindnormregion << " for lumi=" << lumi2017 << std::endl;


  hmjj0->Scale(lumi2017/eqlumi0/remix);
  hmjj1->Scale(lumi2017/eqlumi1/remix);
  hmjj2->Scale(lumi2017/eqlumi2/remix);
  hmjj3->Scale(lumi2017/eqlumi3/remix);
  hmjj4->Scale(lumi2017/eqlumi4/remix);
  hmjj5->Scale(lumi2017/eqlumi5/remix);
  hmjj6->Scale(lumi2017/eqlumi6/remix);
  hmjj7->Scale(lumi2017/eqlumi7/remix);
  hmjj8->Scale(lumi2017/eqlumi8/remix);

  hmjjsum->Add(hmjj0);
  hmjjsum->Add(hmjj1);
  hmjjsum->Add(hmjj2);
  hmjjsum->Add(hmjj3);
  hmjjsum->Add(hmjj4);
  hmjjsum->Add(hmjj5);
  hmjjsum->Add(hmjj6);
  hmjjsum->Add(hmjj7);
  hmjjsum->Add(hmjj8);

  hmjjqcd->Add(hmjj0); 
  hmjjqcd->Add(hmjj1);
  hmjjqcd->Add(hmjj2);
  hmjjqcd->Add(hmjj3);
  hmjjqcd->Add(hmjj4);
  hmjjqcd->Add(hmjj5);
  hmjjqcd->Add(hmjj6);
  hmjjqcd->Add(hmjj7);
  hmjjqcd->Add(hmjj8);

  hmjjwjets->Add(hmjj7);
  hmjjwjets->Add(hmjj8);
  hmjjwjets->Add(hmjj6);

  hmjjzjets->Add(hmjj8);
  hmjjzjets->Add(hmjj7);

  hmjjttbar->Add(hmjj7);

  hmjjqcd->Rebin(10);
  hmjjwjets->Rebin(10);
  hmjjzjets->Rebin(10);
  hmjjttbar->Rebin(10);
  
  hmjjqcd->GetXaxis()->SetRangeUser(1000.0,3000);
  hmjjqcd->SetFillColor(kAzure+2);
  hmjjwjets->GetXaxis()->SetRangeUser(1000.0,3000);
  hmjjwjets->SetFillColor(kGreen+2);
  hmjjzjets->GetXaxis()->SetRangeUser(1000.0,3000);
  hmjjzjets->SetFillColor(kYellow+2);
  hmjjttbar->GetXaxis()->SetRangeUser(1000.0,3000);
  hmjjttbar->SetFillColor(kOrange+2);

  TCanvas *c2 = new TCanvas("c2","c2");
  hmjjsum->Sumw2(); hmjjsum->SetLineWidth(3); hmjjsum->SetLineColor(11); hmjjsum->SetFillColor(11); hmjjsum->SetMaximum(5);
  hmjjsum->SetXTitle("m(W_{j}W_{j}) [GeV]");
  hmjjsum->SetYTitle("Events");

  hmjjqcd->Sumw2(); hmjjqcd->SetMaximum(5);
  hmjjqcd->SetXTitle("m(W_{j}W_{j}) [GeV]");
  hmjjqcd->SetYTitle("Events");
  hmjjqcd->GetXaxis()->SetTitleSize(0.04);  hmjjqcd->GetXaxis()->SetTitleOffset(1.2);
  hmjjqcd->GetYaxis()->SetTitleSize(0.04);
  hmjjqcd->Draw("hist");
  hmjjwjets->Draw("histsame");
  hmjjzjets->Draw("histsame");
  hmjjttbar->Draw("histsame");

  TLegend *lg1 = new TLegend(0.6,0.6,0.9,0.9);
  hmjjqcd->SetMarkerStyle(0); hmjjqcd->SetLineWidth(0);
  hmjjwjets->SetMarkerStyle(0); hmjjwjets->SetLineWidth(0);
  hmjjzjets->SetMarkerStyle(0); hmjjzjets->SetLineWidth(0);
  hmjjttbar->SetMarkerStyle(0); hmjjttbar->SetLineWidth(0);

  lg1->AddEntry(hmjjqcd,"Pythia8 QCD (bins) + mixed protons");
  lg1->AddEntry(hmjjwjets,"Madgraph W+jets + mixed protons");
  lg1->AddEntry(hmjjzjets,"Powheg ttbar + mixed protons");
  lg1->AddEntry(hmjjttbar,"Madgraph Z+jets + mixed protons");
  lg1->Draw("same");

  CMS_lumi2016(c2,0,0,"2017, L = 37.2 fb^{-1}");


  //  hmjjsum->Draw("hist");

  hmjjcentral0->Scale(lumi2017/eqlumi0);
  hmjjcentral1->Scale(lumi2017/eqlumi1);
  hmjjcentral2->Scale(lumi2017/eqlumi2);
  hmjjcentral3->Scale(lumi2017/eqlumi3);
  hmjjcentral4->Scale(lumi2017/eqlumi4);
  hmjjcentral5->Scale(lumi2017/eqlumi5);
  hmjjcentral5->Scale(lumi2017/eqlumi6);
  hmjjcentral5->Scale(lumi2017/eqlumi7);
  hmjjcentral8->Scale(lumi2017/eqlumi8);

  hmyjjcentral0->Scale(lumi2017/eqlumi0);
  hmyjjcentral1->Scale(lumi2017/eqlumi1);
  hmyjjcentral2->Scale(lumi2017/eqlumi2);
  hmyjjcentral3->Scale(lumi2017/eqlumi3);
  hmyjjcentral4->Scale(lumi2017/eqlumi4);
  hmyjjcentral5->Scale(lumi2017/eqlumi5);
  hmyjjcentral5->Scale(lumi2017/eqlumi6);
  hmyjjcentral5->Scale(lumi2017/eqlumi7);
  hmyjjcentral8->Scale(lumi2017/eqlumi8);


  hmjjanyprotons0->Scale(lumi2017/eqlumi0/remix);
  hmjjanyprotons1->Scale(lumi2017/eqlumi1/remix);
  hmjjanyprotons2->Scale(lumi2017/eqlumi2/remix);
  hmjjanyprotons3->Scale(lumi2017/eqlumi3/remix);
  hmjjanyprotons4->Scale(lumi2017/eqlumi4/remix);
  hmjjanyprotons5->Scale(lumi2017/eqlumi5/remix);
  hmjjanyprotons5->Scale(lumi2017/eqlumi6/remix);
  hmjjanyprotons5->Scale(lumi2017/eqlumi7/remix);
  hmjjanyprotons8->Scale(lumi2017/eqlumi8/remix);

  hmjjcentralsum->Add(hmjjcentral0);
  hmjjcentralsum->Add(hmjjcentral1);
  hmjjcentralsum->Add(hmjjcentral2);
  hmjjcentralsum->Add(hmjjcentral3);
  hmjjcentralsum->Add(hmjjcentral4);
  hmjjcentralsum->Add(hmjjcentral5);
  hmjjcentralsum->Add(hmjjcentral6);
  hmjjcentralsum->Add(hmjjcentral7);
  hmjjcentralsum->Add(hmjjcentral8);
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
  hmjjanyprotonssum->Sumw2(); hmjjanyprotonssum->SetLineWidth(3); hmjjanyprotonssum->SetLineColor(7); hmjjanyprotonssum->SetFillColor(7); 
  //  hmjjanyprotonssum->SetMaximum(5);


  //  hmjjcentralsum->Draw("hist");
  //  hmjjanyprotonssum->Draw("histsame");
  //  hmjjsum->Draw("hist");
  //  hmyjjcentralsum->Draw("colz");

  TCanvas *c3 = new TCanvas("c3","c3");
  nbkgbyexperiment->SetLineColor(4); nbkgbyexperiment->SetLineWidth(3); 
  nbkgbyexperiment->SetXTitle("N(bkg., event mixing)");
  nbkgbyexperiment->SetYTitle("N(experiments)");
  nbkgbyexperiment->GetXaxis()->SetTitleSize(0.04); nbkgbyexperiment->GetXaxis()->SetTitleOffset(1.2);
  nbkgbyexperiment->GetYaxis()->SetTitleSize(0.04);

  nbkgbyexperiment->Draw("hist");

  CMS_lumi2016(c3,0,0,"2017, L = 37.2 fb^{-1}");

}
