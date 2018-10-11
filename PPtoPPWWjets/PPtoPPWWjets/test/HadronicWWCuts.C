#define HadronicWWCuts_cxx
#include "HadronicWWCuts.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <string.h>
#include <TMath.h>

Int_t HadronicWWCuts::getXangle(int run,int lumi, const char* filename)
{

  /*
  TString runs; runs.Form("%d", run);
  TString lumis; lumis.Form("%d", lumi);

  TString drun;
  TString dfill;
  TString dlumi;
  TString temp;
  */

  int runnum = -1;
  int lsmin = -1;
  int lsmax = -1;
  int Xangle=-1;

  ifstream F;
  F.open((const char*)filename);


  if(F){
    while (!F.eof())
      {
	F>>runnum;
	F>>lsmin;
	F>>lsmax;
	F>>Xangle;

	if( (run == runnum) &&  (lumi>=lsmin) && (lumi<=lsmax) )
	  {
	    //	    cout << "Read: "<< run<<" " << lumi<<"    -----> "<<Xangle << endl;                                                                                                                    
	    break;
	  }
      }
  }//endif                                                                                                                                                                                      
  else cout << "[!] getXangle(): Error reading from file." << endl;

  if(F.eof())
    {
      cout << "[!] getXangle(): Warning: No crossing angle data for Run "<< run<<", LS " << lumi <<" !" <<endl;
      F.close();
      return -1;
    }
  
  else
    {
      F.close();
      return Xangle;
    }
}


void HadronicWWCuts::Loop()
{
//   In a ROOT session, you can do:
//      root> .L HadronicWWCuts.C
//      root> HadronicWWCuts t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // RP ID's
   // 3   strips sector 45  -z, left
   // 103 strips sector 56  +z, right
   // 23  pixels sector 45  -z, left
   // 123 pixels sector 56  +z, right

   Int_t nentries = fChain->GetEntries();
   if(samplenumber > 1 && samplenumber < 20)
     nentries = 100000;
   Float_t myweight = 1.0;

   Float_t Dx45ref140 = -8.226;
   Float_t Dx56ref140 = -6.191;
   Float_t Dx45ref130 = -8.591;
   Float_t Dx56ref130 = -6.621;
   Float_t Dx45ref120 = -9.145;
   Float_t Dx56ref120 = -7.291;

   Float_t Aln45pixels = -42.05;
   Float_t Aln56pixels = -42.05;
   Float_t Aln45strips = -3.70;
   Float_t Aln56strips = -2.75;

   TH1F *hmjjdat = new TH1F("hmjjdat","hmjjdat",250,0,5000);
   TH1F *hmjjdatpfjet = new TH1F("hmjjdatpfjet","hmjjdatpfjet",250,0,5000);
   TH1F *hmjjdatpfhttrim = new TH1F("hmjjdatpfhttrim","hmjjdatpfhttrim",250,0,5000);
   TH1F *hmjjdatpfjettrim = new TH1F("hmjjdatpfjettrim","hmjjdatpfjettrim",250,0,5000);


   TH1F *hmjdat1 = new TH1F("hmjdat1","hmjdat1",250,0,1000);
   TH1F *htau21dat1 = new TH1F("htau21dat1","htau21dat1",250,0,1);
   TH1F *hmjdat2 = new TH1F("hmjdat2","hmjdat2",250,0,1000);
   TH1F *htau21dat2 = new TH1F("htau21dat2","htau21dat2",250,0,1);
   TH1F *htau21ddtdat1 = new TH1F("htau21ddtdat1","htau21ddtdat1",250,0,1.5);
   TH1F *htau21ddtdat2 = new TH1F("htau21ddtdat2","htau21ddtdat2",250,0,1.5);
   TH1F *hptdat1 = new TH1F("hptdat1","hptdat1",250,0,5000);
   TH1F *hetadat1 = new TH1F("hetadat1","hetadat1",250,-5,5);
   TH1F *hphidat1 = new TH1F("hphidat1","hphidat1",200,-4,4);
   TH1F *hptdat2 = new TH1F("hptdat2","hptdat2",250,0,5000);
   TH1F *hetadat2 = new TH1F("hetadat2","hetadat2",250,-5,5);
   TH1F *hphidat2 = new TH1F("hphidat2","hphidat2",200,-4,4);
   TH1F *hdeta = new TH1F("hdeta","hdeta",150,-7.5,7.5);
   TH1F *hacopdat = new TH1F("hacopdat","hacopdat",250,0,1);
   TH1F *hnvtx = new TH1F("hnvtx","hnvtx",100,0,100);
   TH1F *hptratio = new TH1F("hptratio","hptratio",500,0,5);

   TH1F *hxipix45 = new TH1F("hxipix45","hxipix45",500,0,0.5);
   TH1F *hypix45 = new TH1F("hypix45","hypix45",500,-50,50);
   TH1F *hxipix56 = new TH1F("hxipix56","hxipix56",500,0,0.5);
   TH1F *hypix56 = new TH1F("hypix56","hypix56",500,-50,50);
   TH1F *hxistrip45 = new TH1F("hxistrip45","hxistrip45",500,0,0.5);
   TH1F *hystrip45 = new TH1F("hystrip45","hystrip45",500,-50,50);
   TH1F *hxistrip56 = new TH1F("hxistrip56","hxistrip56",500,0,0.5);
   TH1F *hystrip56 = new TH1F("hystrip56","hystrip56",500,-50,50);
   TH1F *hdxi45 = new TH1F("hdxi45","hdxi45",500,-0.2,0.2);
   TH1F *hdy45 = new TH1F("hdy45","hdy45",500,-20,20);
   TH1F *hdxi56 = new TH1F("hdxi56","hdxi56",500,-0.2,0.2);
   TH1F *hdy56 = new TH1F("hdy56","hdy56",500,-20,20);
   TH1F *hnpix45 = new TH1F("hnpix45","hnpix45",10,0,10);
   TH1F *hnpix56 = new TH1F("hnpix56","hnpix56",10,0,10);

   TH1F *hmassmatchantiw = new TH1F("hmassmatchantiw","hmassmatchantiw",500,-2500,2500);
   TH1F *hymatchantiw = new TH1F("hymatchantiw","hymatchantiw",100,-5,5);
   TH1F *hmassmatchantiacop = new TH1F("hmassmatchantiacop","hmassmatchantiacop",500,-2500,2500);
   TH1F *hymatchantiacop = new TH1F("hymatchantiacop","hymatchantiacop",100,-5,5);
   TH1F *hmassmatchantitau = new TH1F("hmassmatchantitau","hmassmatchantitau",500,-2500,2500);
   TH1F *hymatchantitau = new TH1F("hymatchantitau","hymatchantitau",100,-5,5);
   TH1F *hmassmatchantiptbal = new TH1F("hmassmatchantiptbal","hmassmatchantiptbal",500,-2500,2500);
   TH1F *hymatchantiptbal = new TH1F("hymatchantiptbal","hymatchantiptbal",100,-5,5);
   TH1F *hmassmatchsigmc = new TH1F("hmassmatchsigmc","hmassmatchsigmc",500,-2500,2500);
   TH1F *hymatchsigmc = new TH1F("hymatchsigmc","hymatchsigmc",100,-5,5);

   TH1F *hmasswwantitau = new TH1F("hmasswwantitau","hmasswwantitau",250,0,5000);
   TH1F *hmasswwantiacop = new TH1F("hmasswwantiacop","hmasswwantiacop",250,0,5000);
   TH1F *hmasswwantiptbal = new TH1F("hmasswwantiptbal","hmasswwantiptbal",250,0,5000);
   TH1F *hmasswwsignal = new TH1F("hmasswwsignal","hmasswwsignal",250,0,5000);
   TH1F *hywwsignal = new TH1F("hywwsignal","hywwsignal",250,-5,5);


   std::vector<float> *mpps = new std::vector<float>;
   std::vector<float> *ypps = new std::vector<float>;
   std::vector<float> *xipix45s = new std::vector<float>;
   std::vector<float> *xipix56s = new std::vector<float>;
   std::vector<float> *ypix45s = new std::vector<float>;
   std::vector<float> *ypix56s = new std::vector<float>;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       
       if(jentry % 5000 == 0)
	 cout << "Entry " << jentry << "/" << nentries << endl;

       if(jet_pt->size() < 2)
	 continue;

       if(jet_pt->at(0)>200 && jet_pt->at(1)>200 && fabs(jet_eta->at(0))<2.5 && fabs(jet_eta->at(1))<2.5)// && dijet_mass->at(0)>0)
	 {
	   if((fabs(jet_eta->at(0) - jet_eta->at(1))<1.3))
	   //	   if((fabs(jet_eta->at(0) - jet_eta->at(1))<5.0))
	     {
	       Int_t passht = 0;
	       Int_t passpfjet = 0;
	       Int_t passpfjettrim = 0;
	       Int_t passpfhttrim = 0;

	       for(Int_t j = 0; j < hlt->size(); j++)
		 {
		   TString myhlt = hlt->at(j);
		   if(strstr(myhlt,"HLT_PFHT1050_v")) {passht = 1;} 
		   if(strstr(myhlt,"HLT_AK8PFJet500_v")) {passpfjet = 1;};
		   if(strstr(myhlt,"HLT_AK8PFJet360_TrimMass30_") || 
		      strstr(myhlt,"HLT_AK8PFJet380_TrimMass30_") || 
		      strstr(myhlt,"HLT_AK8PFJet400_TrimMass30_") || 
		      strstr(myhlt,"HLT_AK8PFJet420_TrimMass30_")) {passpfjettrim = 1;} 
		   if(strstr(myhlt,"HLT_AK8PFHT750_TrimMass50_") || 
		      strstr(myhlt,"HLT_AK8PFHT800_TrimMass50_") || 
		      strstr(myhlt,"HLT_AK8PFHT850_TrimMass50_") || 
		      strstr(myhlt,"HLT_AK8PFHT900_TrimMass50_")) {passpfhttrim = 1;}
		 }

	       if(samplenumber > 0)
		 myweight = pileupWeight;

	       //	       if(passpfjettrim == 1)
	       //		 hmjjdatpfjettrim->Fill(dijet_mass->at(0),myweight);

	       //	       if((passht == 1) || (passpfjet == 1) || (passpfhttrim == 1))
	       if((passht == 1) || (passpfjet == 1) || (passpfhttrim == 1) || (passpfjettrim == 1))
	       //	       if(1)
		 {
		   TLorentzVector jet1; TLorentzVector jet2; TLorentzVector mydijet;
		   jet1.SetPtEtaPhiE(jet_pt->at(0),jet_eta->at(0),jet_phi->at(0),jet_energy->at(0));
		   jet2.SetPtEtaPhiE(jet_pt->at(1),jet_eta->at(1),jet_phi->at(1),jet_energy->at(1));

		   int indleading = -1;
		   int indsecond = -1;
		   float C_JER1=-999.;
		   float C_JER2=-999.;

		   /* Applying JER smearing to MC before using jets */
		   if(samplenumber > 0)
		     {
		       TLorentzVector recojtmp, genjtmp;
		       TRandom3 randomSrc;
		       int matchedgen=0;
		       int indmatchedgen=-1;
		       float ptleading = 0;
		       float ptsecond = 0;
		       float C_JER=-999;

		       //		       cout << "Starting checks on JER" << endl;
		       for(int ir = 0; ir < jet_pt->size(); ir++)
			 {
			   recojtmp.SetPtEtaPhiE(jet_pt->at(ir),jet_eta->at(ir),jet_phi->at(ir),jet_energy->at(ir));

			   for(int ig=0; ig<gen_jet_pt->size(); ig++)
			     { // loop over gen jets
			       genjtmp.SetPtEtaPhiE(gen_jet_pt->at(ig),gen_jet_eta->at(ig),gen_jet_phi->at(ig),gen_jet_energy->at(ig));
			       if( (recojtmp.DeltaR(genjtmp) < (0.8/2.)) && 
				   (fabs(recojtmp.Pt() - genjtmp.Pt())<(3*jet_jer_res->at(0)*recojtmp.Pt()) ) )
				 {
				   matchedgen=1; 
				   indmatchedgen=ig;
				 } 
			       // 0.8 is cone radius
			     }
			   
			   if(matchedgen == 1)
			     {
			       C_JER = 1 + (jet_jer_sf->at(0) -1 )*( (recojtmp.Pt() - gen_jet_pt->at(indmatchedgen)) / recojtmp.Pt() );
			       if(C_JER < 0) C_JER = 0;
			     }
			   else       
			     {
			       C_JER = 1 + randomSrc.Gaus(0, jet_jer_res->at(0))*(sqrt(max(jet_jer_sf->at(0)*jet_jer_sf->at(0) - 1., 0.)));
			     }
			   
			   // Re-check for the leading and second leading jets after JER correction
			   //			   cout << "\tChecking " << C_JER*recojtmp.Pt() << " against leading pT = " << ptleading << ", second leading pT = " << ptsecond << endl;
			   if(C_JER*recojtmp.Pt() > ptleading) 
			     {
			       // If we already found 1 jet with lower pT, make that the second leading jet
			       if(ptleading > 0)
				 {
				   ptsecond = ptleading;
				   indsecond = indleading;
				   C_JER2 = C_JER1;
				 }
			       ptleading = C_JER*recojtmp.Pt();
			       C_JER1 = C_JER;
			       indleading = ir;
			       //			       cout << "\t\tSetting new leading to pT = " << ptleading << ", index = " << indleading << endl;
			     }
			   if((C_JER*recojtmp.Pt() > ptsecond) && (C_JER*recojtmp.Pt() < ptleading) && (ir != indleading))
			     {
			       //			       cout << "\t\t" << C_JER*recojtmp.Pt() << " is greater than " << ptsecond << " and less than " << ptleading << endl;
			       ptsecond = C_JER*recojtmp.Pt();
			       C_JER2 = C_JER;
			       indsecond = ir;
			       //			       cout << "\t\tSetting new second leading to pT = " << ptsecond << ", index = " << indsecond << endl;
			     }
			   //			   cout << "\tjet size = " << jet_pt->size() << ", leading index = " << indleading << ", second leading index = " << indsecond << endl;
			 }
		       //		       cout << "Resetting jets after JER: " << endl;
		       //		       cout << "\tleading pT, index = " << C_JER1*jet_pt->at(indleading) << ", " << indleading << endl;
		       //		       cout << "\tsecond leading pT, index = " << C_JER2*jet_pt->at(indsecond) << ", " << indsecond << endl;


		       //		       cout << "Jet pT's = " << jet1.Pt() << ", " << jet2.Pt() 
		       //			    << ", JER factors (jet1, jet2) = " << C_JER << ", " << C_JER2 << endl;
		       jet1.SetPtEtaPhiE(C_JER1*jet_pt->at(indleading),jet_eta->at(indleading),jet_phi->at(indleading),C_JER1*jet_energy->at(indleading));
		       jet2.SetPtEtaPhiE(C_JER2*jet_pt->at(indsecond),jet_eta->at(indsecond),jet_phi->at(indsecond),C_JER2*jet_energy->at(indsecond));
		     }
		   else
		     {
		       indleading = 0;
		       indsecond = 1;
		     }
		   mydijet = jet1+jet2;                                                                                                       

		   if(indleading != 0 || indsecond != 1)
		     {
		       cout << "Index flip! Leading jet is at index = " << indleading << " with pT = " << jet1.Pt() << ", second leading jet is at index = " 
			    << indsecond << " with pT = " << jet2.Pt() << endl;
		     }
                   /* Ending JER */
		   
		   hmjjdat->Fill(mydijet.M(),myweight);
		   if(passpfjet == 1)
		     hmjjdatpfjet->Fill(mydijet.M(),myweight);
		   if(passpfhttrim == 1)
		     hmjjdatpfhttrim->Fill(mydijet.M(),myweight);
		   
		   if(mydijet.M() > 1126 && mydijet.M() < 2500)
		     {

		       Float_t rhoprime1 = 0;
		       Float_t taut21ddt1 = 0;
		       Float_t rhoprime2 = 0;
		       Float_t taut21ddt2 = 0;

		       if(jet_corrmass->at(indleading) >= 55 && jet_corrmass->at(indleading) <= 215)
			 {
			   htau21dat1->Fill(jet_tau2->at(indleading)/jet_tau1->at(indleading),myweight);
                           hmjdat1->Fill(jet_corrmass->at(indleading),myweight);
			   rhoprime1 = TMath::Log(jet_corrmass->at(indleading)*jet_corrmass->at(indleading)/jet_pt->at(indleading));
			   taut21ddt1 = (jet_tau2->at(indleading)/jet_tau1->at(indleading)) - (-0.082 * rhoprime1);
			   htau21ddtdat1->Fill(taut21ddt1);
			 }
		       if(jet_corrmass->at(indsecond) >= 55 && jet_corrmass->at(indsecond) <= 215)
			 {
			   htau21dat2->Fill(jet_tau2->at(indsecond)/jet_tau1->at(indsecond),myweight);
			   hmjdat2->Fill(jet_corrmass->at(indsecond),myweight);
                           rhoprime2 = TMath::Log(jet_corrmass->at(indsecond)*jet_corrmass->at(indsecond)/jet_pt->at(indsecond));
			   taut21ddt2 = (jet_tau2->at(indsecond)/jet_tau1->at(indsecond)) - (-0.082 * rhoprime2);
                           htau21ddtdat2->Fill(taut21ddt2);
			 }
		       hptdat1->Fill(jet_pt->at(indleading),myweight);
		       hptdat2->Fill(jet_pt->at(indsecond),myweight);
		       hetadat1->Fill(jet_eta->at(indleading),myweight);
		       hetadat2->Fill(jet_eta->at(indsecond),myweight);
		       hphidat1->Fill(jet_phi->at(indleading),myweight);
		       hphidat2->Fill(jet_phi->at(indsecond),myweight);
		       hdeta->Fill(fabs(jet_eta->at(indleading) - jet_eta->at(indsecond)),myweight);
		       hnvtx->Fill(nVertices,myweight);
		       hptratio->Fill(jet_pt->at(indleading)/jet_pt->at(indsecond),myweight);
		       
		       float dphi = fabs(jet_phi->at(indleading) - jet_phi->at(indsecond));
		       if(dphi > 3.14159)
			 dphi = (2*3.14159)-dphi;
		       float acop = 1 - (dphi/3.14159);
		       hacopdat->Fill(acop,myweight);
		       //		       std::cout << "phi1 = " << jet_phi->at(indleading) << ", phi2 = " << jet_phi->at(indsecond) << ", dphi = " << dphi 
		       //				 << ", acop = " << acop << std::endl;
			   
		       Float_t ptbalcut = 1.1;
		       Float_t acopcut = 0.01;
		       Float_t mwlowcut = 65.0;
		       Float_t mwhicut = 105.0;
		       Float_t tau21cut = 0.75;

		       // Sideband control regions
		       if(samplenumber > 0)
			 {
			   // Signal region, only for MC
			   if((acop < acopcut) && 
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			      (jet_pt->at(indleading)/jet_pt->at(indsecond) < ptbalcut))
			     {
			       hmasswwsignal->Fill(mydijet.M());
			       hywwsignal->Fill(mydijet.Rapidity());
			     }
			 }
		       // Anti acoplanarity                                                                                                                                        
		       if((acop > acopcut) &&
			  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			  (jet_pt->at(indleading)/jet_pt->at(indsecond) < ptbalcut))
			 {
			   hmasswwantiacop->Fill(mydijet.M());
			 }
		       // Anti pT balance                                                                                                                                          
		       if((jet_pt->at(indleading)/jet_pt->at(indsecond)) > ptbalcut &&
			  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			  (acop < 0.005))
			 {
                           hmasswwantiptbal->Fill(mydijet.M());
			 }
		       // Anti tau21                                                                                                                                               
		       if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
			  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			  (acop < 0.005) &&
			  (jet_pt->at(indleading)/jet_pt->at(indsecond) <  ptbalcut))
			 {
			   hmasswwantitau->Fill(mydijet.M());
			 }

		       

		       // Proton part
		       float mpp = 0;
		       float ypp = 0;

		       if(pps_track_x->size() > 0)
			 {
			   int nPixelTracks45 = 0;
			   int nPixelTracks56 = 0;
			   float pixelx45smallesty = 0.;
			   float pixelx56smallesty = 0.;
			   float pixely45smallesty = 9999.;
			   float pixely56smallesty = 9999.;
			   float stripx45 = 0;
			   float stripy45 = 0;
			   float stripx56 = 0;
			   float stripy56 = 0;

                           float pixelxi45smallesty = 0.;
                           float pixelxi56smallesty = 0.;
                           float stripxi45 = 0;
                           float stripxi56 = 0;
			   
			   float dxpixstrip45 = 0;
			   float dypixstrip45 = 0;
			   float dxpixstrip56 = 0;
			   float dypixstrip56 = 0;
			   
			   //			   int angle = getXangle(run,  lumiblock , "xangle_tillTS2_STABLEBEAMS_CLEANUP.csv");
			   //			   int angle = getXangle(run, lumiblock, "xinganglerange_tillTS2.txt");
			   int angle = 0;

			   if(run < 303719)
			     angle = getXangle(run, lumiblock, "xinganglerange_tillTS2.txt");
			   else
			     angle = getXangle(run, lumiblock, "xinganglerange_afterTS2.txt");                                               


			   Float_t Dx45 = 0;
			   Float_t Dx56 = 0;

			   if(angle == 120)
			     {
			       Dx45 = Dx45ref120;
			       Dx56 = Dx56ref120;
			     }
			   else if(angle == 130)
                             {
                               Dx45 = Dx45ref130;
                               Dx56 = Dx56ref130;
                             }
                           else if(angle == 140)
                             {
                               Dx45 = Dx45ref140;
                               Dx56 = Dx56ref140;
                             }
			   else
			     {
			       Dx45 = Dx45ref140 - 0.46*((angle-140.)/10.) ;
                               Dx56 = Dx56ref140 - 0.46*((angle-140.)/10.) ;
			     }

			   Dx45 *= -1.0;
			   Dx56 *= -1.0;

			   for(int p = 0; p < pps_track_x->size(); p++)                                                                                                                
			     {
			       if(pps_track_rpid->at(p) == 23)                                                                                                       
			       //			       if(pps_track_rpid->at(p) == 3)
				 {
				   float thexi = (pps_track_x->at(p)+ Aln45pixels)/(Dx45*10.0);
				   xipix45s->push_back(thexi);
				   ypix45s->push_back(pps_track_y->at(p));
				   nPixelTracks45++;
				 }  
			       if(pps_track_rpid->at(p) == 123)                                                                                                       
			       //			       if(pps_track_rpid->at(p) == 103)
                                 {                                                                                                                                                     
				   xipix56s->push_back((pps_track_x->at(p)+ Aln56pixels)/(Dx56*10.0));
				   ypix56s->push_back(pps_track_y->at(p));
				   nPixelTracks56++;
				 }
                               if(pps_track_rpid->at(p) == 3)                                                                                                                          
                                 {                                                                                                                                                     
                                   stripx45 = pps_track_x->at(p);                                                                                                                      
                                   stripy45 = pps_track_y->at(p);                                                                                                                      
                                   stripxi45 = (stripx45 + Aln45strips)/(Dx45*10.0);                                                                                                   
                                 }                                                                                                                                                     
                               if(pps_track_rpid->at(p) == 103)                                                                                                                        
                                 {                                                                                                                                                     
                                   stripx56 = pps_track_x->at(p);                                                                                                                      
                                   stripy56 = pps_track_y->at(p);                                                                                                                      
                                   stripxi56 = (stripx56 + Aln56strips)/(Dx56*10.0);                                                                                                   
                                 }                                                                                                                                                     
			     }

			   if(nPixelTracks45 > 1 || nPixelTracks56 > 1)
			     {
			       for(int a = 0; a < nPixelTracks45; a++)
				 {
				   for(int b = 0; b < nPixelTracks56; b++)
				     {
				       mpps->push_back(TMath::Sqrt(13000.0*13000.0*xipix56s->at(b)*xipix45s->at(a)));
				       ypps->push_back(0.5*TMath::Log(xipix56s->at(b)/xipix45s->at(a)));
				     }
				 }
			     }
			   else if(nPixelTracks45 == 1 && nPixelTracks56 == 1)
			     {
			       mpps->push_back(TMath::Sqrt(13000.0*13000.0*xipix56s->at(0)*xipix45s->at(0)));
			       ypps->push_back(0.5*TMath::Log(xipix56s->at(0)/xipix45s->at(0)));
			     }

			   /*
			   for(int p = 0; p < pps_track_x->size(); p++)
			     {
			       if(pps_track_rpid->at(p) == 23)
				 {
				   if(fabs(3.75-pps_track_y->at(p)) < pixely45smallesty)
				     {
				       pixely45smallesty = pps_track_y->at(p);
				       pixelx45smallesty = pps_track_x->at(p);
                                       pixelxi45smallesty = (pixelx45smallesty + Aln45pixels)/(Dx45*10.0);
				     }
				 }
			       if(pps_track_rpid->at(p) == 123)
				 {
				   if(fabs(3.75-pps_track_y->at(p)) < pixely56smallesty)
				     {
				       pixely56smallesty = pps_track_y->at(p);
				       pixelx56smallesty = pps_track_x->at(p);
				       pixelxi56smallesty = (pixelx56smallesty + Aln56pixels)/(Dx56*10.0);
				     }
				 }
			       if(pps_track_rpid->at(p) == 3)
				 {
				   stripx45 = pps_track_x->at(p);
				   stripy45 = pps_track_y->at(p);
				   stripxi45 = (stripx45 + Aln45strips)/(Dx45*10.0);
				 }
			       if(pps_track_rpid->at(p) == 103)
				 {
				   stripx56 = pps_track_x->at(p);
				   stripy56 = pps_track_y->at(p);
                                   stripxi56 = (stripx56 + Aln56strips)/(Dx56*10.0);
				 }
			     }
			   if(pixelx45smallesty != 0)
			     {
			       hxipix45->Fill(pixelxi45smallesty);
			       hypix45->Fill(pixely45smallesty);
			     }
			   if(pixelx56smallesty != 0)
			     {
			       hxipix56->Fill(pixelxi56smallesty);
			       hypix56->Fill(pixely56smallesty);
			     }
			   if(stripx45 != 0)
			     {
			       hxistrip45->Fill(stripxi45);
			       hystrip45->Fill(stripy45);
			     }
			   if(stripx56 != 0)
			     {
			       hxistrip56->Fill(stripxi56);
			       hystrip56->Fill(stripy56);
			     }
			   if(stripx45 != 0)
			     {
			       hdxi45->Fill(pixelxi45smallesty-stripxi45);
			       hdy45->Fill(pixely45smallesty-stripy45);
			     }
			   if(stripx56 != 0)
			     {
			       hdxi56->Fill(pixelxi56smallesty-stripxi56);
			       hdy56->Fill(pixely56smallesty-stripy56);
			     }
			   if(hxipix56>0 && hxipix45>0)
			     {
			       mpp = TMath::Sqrt(13000.0*13000.0*pixelxi45smallesty*pixelxi56smallesty);
			       ypp = 0.5*TMath::Log(pixelxi56smallesty/pixelxi45smallesty);
			     }
			   */
			 }
		   
		       // Control regions
		       for(Int_t pr = 0; pr < mpps->size(); pr++)
			 {
			   if(mpps->at(pr)>0)
			     {
			       hmassmatchsigmc->Fill(mydijet.M()-mpps->at(pr));
			       hymatchsigmc->Fill(mydijet.Rapidity()-ypps->at(pr));
			       // Anti W-mass                                                                                                                                                          
			       if((jet_corrmass->at(indleading) < 65 || jet_corrmass->at(indleading) > 105) && (jet_corrmass->at(indsecond) < 65 || jet_corrmass->at(indsecond) > 105) && 
				  (jet_tau2->at(indsecond)/jet_tau1->at(indsecond) <= 0.75) && (jet_tau2->at(indleading)/jet_tau1->at(indleading) <= 0.75) && 
				  (acop < 0.005) && 
				  (jet_pt->at(indleading)/jet_pt->at(indsecond) < 1.08))
				 {
				   hmassmatchantiw->Fill(mydijet.M()-mpps->at(pr));
				   hymatchantiw->Fill(mydijet.Rapidity()-ypps->at(pr));
				 }
			       // Anti tau21
			       if((jet_tau2->at(indsecond)/jet_tau1->at(indsecond) > 0.75) && (jet_tau2->at(indleading)/jet_tau1->at(indleading) > 0.75) && 
				  (jet_corrmass->at(indleading) >= 65 && jet_corrmass->at(indleading) <= 105) && (jet_corrmass->at(indsecond) >= 65 && jet_corrmass->at(indsecond) <= 105) && 
                                  (acop < 0.005) &&
                                  (jet_pt->at(indleading)/jet_pt->at(indsecond) < 1.08))
				 {
				   hmassmatchantitau->Fill(mydijet.M()-mpps->at(pr));
				   hymatchantitau->Fill(mydijet.Rapidity()-ypps->at(pr));
				 }
			       // Debugging
			       if((jet_tau2->at(indsecond)/jet_tau1->at(indsecond) > 0.75) && (jet_tau2->at(indleading)/jet_tau1->at(indleading) > 0.75))
				 {
				   //				   cout << "Anti tau selection: " << endl;
				   if((jet_corrmass->at(indleading) >= 65 && jet_corrmass->at(indleading) <= 105) && (jet_corrmass->at(indsecond) >= 65 && jet_corrmass->at(indsecond) <= 105))
				     {
				       cout << "\tPassed jet mass cuts: " << jet_corrmass->at(indleading) << ", " << jet_corrmass->at(indsecond) << endl;
				       if(acop < 0.005)
					 {
					   cout << "\t\tPassed acop cuts: = " << acop << endl;
					   if(jet_pt->at(indleading)/jet_pt->at(indsecond) < 1.08)
					     cout << "\t\t\tPassed pT balance cuts: " << jet_pt->at(indleading) << "/" << jet_pt->at(indsecond) << " = " << jet_pt->at(indleading)/jet_pt->at(indsecond) << endl;
					 }
				     }
				 }
			       // Anti acoplanarity
			       if((acop > 0.01) && 
				  (jet_corrmass->at(indleading) >= 65 && jet_corrmass->at(indleading) <= 105) && (jet_corrmass->at(indsecond) >= 65 && jet_corrmass->at(indsecond) <= 105) &&
                                  (jet_tau2->at(indsecond)/jet_tau1->at(indsecond) <= 0.75) && (jet_tau2->at(indleading)/jet_tau1->at(indleading) <= 0.75) &&
                                  (jet_pt->at(indleading)/jet_pt->at(indsecond) < 1.08))
				 {
				   hmassmatchantiacop->Fill(mydijet.M()-mpps->at(pr));
				   hymatchantiacop->Fill(mydijet.Rapidity()-ypps->at(pr));
				 }
			       // Anti pT balance
			       if((jet_pt->at(indleading)/jet_pt->at(indsecond)) > 1.2 && 
                                  (jet_corrmass->at(indleading) >= 65 && jet_corrmass->at(indleading) <= 105) && (jet_corrmass->at(indsecond) >= 65 && jet_corrmass->at(indsecond) <= 105) &&
                                  (jet_tau2->at(indsecond)/jet_tau1->at(indsecond) <= 0.75) && (jet_tau2->at(indleading)/jet_tau1->at(indleading) <= 0.75) &&
                                  (acop < 0.005))
				 {
				   hmassmatchantiptbal->Fill(mydijet.M()-mpps->at(pr));
				   hymatchantiptbal->Fill(mydijet.Rapidity()-ypps->at(pr));
				 }
			     }
			 }
		     }
		 }
	     }
	 }

       mpps->clear();
       ypps->clear();
       xipix45s->clear();
       xipix56s->clear();
       ypix45s->clear();
       ypix56s->clear();

     }

   delete mpps;
   delete ypps;
   delete xipix45s;
   delete xipix56s;
   delete ypix45s;
   delete ypix56s;

   // if (Cut(ientry) < 0) continue;

   TFile *fx; 

   //   TFile *fx = new TFile("vars_cuts_qcdpt170to300.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_qcdpt300to470.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_qcdpt470to600.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_qcdpt600to800.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_qcdpt800to1000.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_qcdpt1000to1400.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_datahist2017C.root","RECREATE");
   //   TFile *fx = new TFile("vars_cuts_exclwwa0w2point5.root","RECREATE");

   if(samplenumber == -1)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_datahist2017B.root","RECREATE");
   if(samplenumber == -2)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_datahist2017C.root","RECREATE");
   if(samplenumber == -3)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_datahist2017D.root","RECREATE");
   if(samplenumber == -4)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_datahist2017E.root","RECREATE");
   if(samplenumber == -5)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_datahist2017F.root","RECREATE");

   if(samplenumber == 1)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt170to300.root","RECREATE");
   if(samplenumber == 2)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt300to470.root","RECREATE");
   if(samplenumber == 3)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt470to600.root","RECREATE");
   if(samplenumber == 4)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt600to800.root","RECREATE");                                                           
   if(samplenumber == 5)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt800to1000.root","RECREATE");
   if(samplenumber == 6)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_qcdpt1000to1400.root","RECREATE");

   if(samplenumber == 21)
     fx = new TFile("vars_cuts_ntuplev2recalcmjcut_jerallhlt_exclwwa0w2point5.root","RECREATE");


   hmjjdat->Write();
   hmjdat1->Write();
   htau21dat1->Write();
   hmjdat2->Write();
   htau21dat2->Write();
   htau21ddtdat1->Write();
   htau21ddtdat2->Write();
   hptdat1->Write();
   hptdat2->Write();
   hetadat1->Write();
   hetadat2->Write();
   hphidat1->Write();
   hphidat2->Write();
   hdeta->Write();
   hacopdat->Write();
   hmjjdatpfjet->Write();
   hmjjdatpfhttrim->Write();
   hmjjdatpfjettrim->Write();
   hnvtx->Write();
   hptratio->Write();

   hxipix45->Write();
   hypix45->Write();
   hxipix56->Write();
   hypix56->Write();
   hxistrip45->Write();
   hystrip45->Write();
   hxistrip56->Write();
   hystrip56->Write();
   hdxi45->Write();
   hdy45->Write();
   hdxi56->Write();
   hdy56->Write();

   hmassmatchantiw->Write();
   hymatchantiw->Write();
   hmassmatchantitau->Write();
   hymatchantitau->Write();
   hmassmatchantiacop->Write();
   hymatchantiacop->Write();
   hmassmatchantiptbal->Write();
   hymatchantiptbal->Write();

   hmassmatchsigmc->Write();
   hymatchsigmc->Write();

   hmasswwantitau->Write();
   hmasswwantiacop->Write();
   hmasswwantiptbal->Write();
   hmasswwsignal->Write();
   hywwsignal->Write();

   fx->Close();
}
