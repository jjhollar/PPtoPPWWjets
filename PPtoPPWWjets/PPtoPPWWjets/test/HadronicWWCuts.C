#define HadronicWWCuts_cxx
#include "HadronicWWCuts.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <string.h>
#include <TMath.h>

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
   TH1F *hyjjdat = new TH1F("hyjjdat","hyjjdat",250,-5,5);

   TH1F *hmppsingle = new TH1F("hmppsingle","hmppsingle",250,0,5000);
   TH1F *hmppmulti = new TH1F("hmppmulti","hmppmulti",250,0,5000);
   TH1F *hmppmixed = new TH1F("hmppmixed","hmppsmixed",250,0,5000);
   TH1F *hyppsingle = new TH1F("hyppsingle","hyppsingle",250,-5,5);
   TH1F *hyppmulti = new TH1F("hyppmulti","hyppmulti",250,-5,5);
   TH1F *hyppmixed = new TH1F("hyppmixed","hyppmixed",250,-5,5);

   TH2F *hmyppsingle = new TH2F("hmyppsingle","hmyppsingle",100,0,5000,100,-5,5);
   TH2F *hmyjjdat = new TH2F("hmyjjdat","hmyjjdat",100,0,5000,100,-5,5);



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
   TH1F *hximult45 = new TH1F("hximult45","hximult45",500,0,0.5);
   TH1F *hximult56 = new TH1F("hximult56","hximult56",500,0,0.5);

   TH1F *hnpix45 = new TH1F("hnpix45","hnpix45",15,0,15);
   TH1F *hnpix56 = new TH1F("hnpix56","hnpix56",15,0,15);


   TH1F *hdxi45 = new TH1F("hdxi45","hdxi45",500,-0.2,0.2);
   TH1F *hdy45 = new TH1F("hdy45","hdy45",500,-20,20);
   TH1F *hdxi56 = new TH1F("hdxi56","hdxi56",500,-0.2,0.2);
   TH1F *hdy56 = new TH1F("hdy56","hdy56",500,-20,20);

   TH1F *hmassmatchantiw = new TH1F("hmassmatchantiw","hmassmatchantiw",500,-2500,2500);
   TH1F *hymatchantiw = new TH1F("hymatchantiw","hymatchantiw",100,-5,5);
   TH1F *hmassmatchratioantiw = new TH1F("hmassmatchratioantiw","hmassmatchratioantiw",100,-5,5);

   TH1F *hmassmatchantiacop = new TH1F("hmassmatchantiacop","hmassmatchantiacop",500,-2500,2500);
   TH1F *hymatchantiacop = new TH1F("hymatchantiacop","hymatchantiacop",100,-5,5);
   TH1F *hmassmatchratioantiacop = new TH1F("hmassmatchratioantiacop","hmassmatchratioantiacop",100,-5,5);

   TH1F *hmassmatchantitau = new TH1F("hmassmatchantitau","hmassmatchantitau",500,-2500,2500);
   TH1F *hymatchantitau = new TH1F("hymatchantitau","hymatchantitau",100,-5,5);
   TH1F *hmassmatchratioantitau = new TH1F("hmassmatchratioantitau","hmassmatchratioantitau",100,-5,5);

   TH1F *hmassmatchantiptbal = new TH1F("hmassmatchantiptbal","hmassmatchantiptbal",500,-2500,2500);
   TH1F *hymatchantiptbal = new TH1F("hymatchantiptbal","hymatchantiptbal",100,-5,5);
   TH1F *hmassmatchratioantiptbal = new TH1F("hmassmatchratioantiptbal","hmassmatchratioantiptbal",100,-5,5);

   TH1F *hmassmatchsigmc = new TH1F("hmassmatchsigmc","hmassmatchsigmc",500,-2500,2500);
   TH1F *hymatchsigmc = new TH1F("hymatchsigmc","hymatchsigmc",100,-5,5);
   TH1F *hmassmatchratiosigmc = new TH1F("hmassmatchratiosigmc","hmassmatchratiosigmc",500,-5,5);

   TH1F *hmasswwantitau = new TH1F("hmasswwantitau","hmasswwantitau",250,0,5000);
   TH1F *hmasswwantiacop = new TH1F("hmasswwantiacop","hmasswwantiacop",250,0,5000);
   TH1F *hmasswwantiptbal = new TH1F("hmasswwantiptbal","hmasswwantiptbal",250,0,5000);
   TH1F *hmasswwsignal = new TH1F("hmasswwsignal","hmasswwsignal",250,0,5000);
   TH1F *hywwsignal = new TH1F("hywwsignal","hywwsignal",250,-5,5);
   TH1F *hcrossingangle = new TH1F("hcrossingangle","hcrossingangle",70,100,170);

   TH1F *hmppres = new TH1F("hmppres","hmppres",100,0,2);
   TH1F *hmjjres = new TH1F("hmjjres","hmjjres",100,0,2);
   TH1F *hmassmatchratiosigmcmult = new TH1F("hmassmatchratiosigmcmult","hmassmatchratiosigmcmult",500,-5,5);

   std::vector<float> *mppssingsing = new std::vector<float>;
   std::vector<float> *yppssingsing = new std::vector<float>;
   std::vector<float> *mppsmixed = new std::vector<float>;
   std::vector<float> *yppsmixed = new std::vector<float>;
   std::vector<float> *mppsmultmult = new std::vector<float>;
   std::vector<float> *yppsmultmult = new std::vector<float>;
   std::vector<float> *xipix45s = new std::vector<float>;
   std::vector<float> *xipix56s = new std::vector<float>;
   std::vector<float> *ypix45s = new std::vector<float>;
   std::vector<float> *ypix56s = new std::vector<float>;
   std::vector<float> *ximulti45s = new std::vector<float>;
   std::vector<float> *ximulti56s = new std::vector<float>;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       
       if(jentry % 20000 == 0)
	 cout << "Entry " << jentry << "/" << nentries << endl;

       if(jet_pt->size() < 2)
	 continue;

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

       if((passht == 1) || (passpfjet == 1) || (passpfhttrim == 1) || (passpfjettrim == 1))
	 {
	   if(samplenumber > 0)
	     myweight = pileupWeight;


	   TLorentzVector jet1; TLorentzVector jet2; TLorentzVector mydijet;
	   jet1.SetPtEtaPhiE(jet_pt->at(0),jet_eta->at(0),jet_phi->at(0),jet_energy->at(0));
	   jet2.SetPtEtaPhiE(jet_pt->at(1),jet_eta->at(1),jet_phi->at(1),jet_energy->at(1));
	   
	   int indleading = 0;
	   int indsecond = 1;
	   float C_JER1=-999.;
	   float C_JER2=-999.;

	   /* Applying JER smearing to MC before using jets
	    * Note - as of the reprocessing of samples with UL proton RECO in September 2019, this 
	    * is no longer necessary since JER is done in the analyzer step. 
	    * It's left commented out for any comparisons with older plots
	    */

	   /*
	   if(samplenumber > 0)
	     {
	       TLorentzVector recojtmp, genjtmp;
	       TRandom3 randomSrc;
	       int matchedgen=0;
	       int indmatchedgen=-1;
	       float ptleading = 0;
	       float ptsecond = 0;
	       float C_JER=-999;
	       
	       //	       cout << "Starting checks on JER" << endl;
	       for(int ir = 0; ir < jet_pt->size(); ir++)
		 {
		   if(TMath::IsNaN(jet_pt->at(ir)))
		     continue;

		   recojtmp.SetPtEtaPhiE(jet_pt->at(ir),jet_eta->at(ir),jet_phi->at(ir),jet_energy->at(ir));

		   for(int ig=0; ig<gen_jet_pt->size(); ig++)
		     { // loop over gen jets
		       genjtmp.SetPtEtaPhiE(gen_jet_pt->at(ig),gen_jet_eta->at(ig),gen_jet_phi->at(ig),gen_jet_energy->at(ig));
		       if( (recojtmp.DeltaR(genjtmp) < (0.8/2.)) && 
			   (fabs(recojtmp.Pt() - genjtmp.Pt())<(3*jet_jer_res->at(ir)*recojtmp.Pt()) ) )
			 {
			   matchedgen=1; 
			   indmatchedgen=ig;
			 } 
		       // 0.8 is cone radius
		     }
		   
		   if(matchedgen == 1)
		     {
		       C_JER = 1 + (jet_jer_sf->at(ir) -1 )*( (recojtmp.Pt() - gen_jet_pt->at(indmatchedgen)) / recojtmp.Pt() );
		       if(C_JER < 0) {C_JER = 0;}
		     }
		   else       
		     {
		       C_JER = 1 + randomSrc.Gaus(0, jet_jer_res->at(ir))*(sqrt(max(jet_jer_sf->at(ir)*jet_jer_sf->at(ir) - 1., 0.)));
		     }
		   
		   // Re-check for the leading and second leading jets after JER correction
		   //		   cout << "\tChecking " << C_JER*recojtmp.Pt() << " against leading pT = " << ptleading << ", second leading pT = " << ptsecond << endl;
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
		       //		       cout << "\t\tSetting new leading to pT = " << ptleading << ", index = " << indleading << endl;
		     }
		   if((C_JER*recojtmp.Pt() > ptsecond) && (C_JER*recojtmp.Pt() < ptleading) && (ir != indleading))
		     {
		       //		       cout << "\t\t" << C_JER*recojtmp.Pt() << " is greater than " << ptsecond << " and less than " << ptleading << endl;
		       ptsecond = C_JER*recojtmp.Pt();
		       C_JER2 = C_JER;
		       indsecond = ir;
		       //		       cout << "\t\tSetting new second leading to pT = " << ptsecond << ", index = " << indsecond << endl;
		     }
		   //		   cout << "\tjet size = " << jet_pt->size() << ", leading index = " << indleading << ", second leading index = " << indsecond << endl;
		 }
	       if(indleading >= 0 && indsecond >= 0)
		 {
		   //		   cout << "Resetting jets after JER: " << endl;
		   //		   cout << "\tleading pT, index = " << C_JER1*jet_pt->at(indleading) << ", " << indleading << endl;
		   //		   cout << "\tsecond leading pT, index = " << C_JER2*jet_pt->at(indsecond) << ", " << indsecond << endl;
		   
		   
		   //		   cout << "Jet pT's = " << jet1.Pt() << ", " << jet2.Pt() 
		   //			<< ", JER factors (jet1, jet2) = " << C_JER << ", " << C_JER2 << endl;
		   jet1.SetPtEtaPhiE(C_JER1*jet_pt->at(indleading),jet_eta->at(indleading),jet_phi->at(indleading),C_JER1*jet_energy->at(indleading));
		   jet2.SetPtEtaPhiE(C_JER2*jet_pt->at(indsecond),jet_eta->at(indsecond),jet_phi->at(indsecond),C_JER2*jet_energy->at(indsecond));
		 }
	     }
	   else
	     {
	       indleading = 0;
	       indsecond = 1;
	     }

	   // Check that there are still two non-zero jets after the JER corrections
	   if(indleading < 0 || indsecond < 0)
	     {
	       //	       cout << "Skipping this event because one the indices after JER is < 0" << endl;
	       continue;
	     }

	   */

	   mydijet = jet1+jet2;                                                                                                       
	   
	   if((indleading != 0) || (indsecond != 1))
	     {
	       //	       cout << "Index flip! Leading jet is at index = " << indleading << " with pT = " << jet1.Pt() << ", second leading jet is at index = " 
	       //		    << indsecond << " with pT = " << jet2.Pt() << " in collection of size = " << jet_pt->size() << endl;
	     }
	   /* Ending JER */
	   if(jet1.Pt()>200 && jet2.Pt()>200 && fabs(jet_eta->at(indleading))<2.5 && fabs(jet_eta->at(indsecond))<2.5)
	     {
	       if((fabs(jet_eta->at(indleading) - jet_eta->at(indsecond))<1.3))
		 {
		   //		   std::cout << "Filling histograms: " << std::endl
		   //			     << "\tjet1 pT, eta, phi, E = " << jet1.Pt() << ", " << jet1.Eta() << ", " << jet1.Phi() << ", " << jet1.E() << std::endl
		   //			     << "\tjet2 pT, eta, phi, E = " << jet2.Pt() << ", " << jet2.Eta() << ", " << jet2.Phi() << ", " << jet2.E() << std::endl
		   //			     << "\tmjj = " << mydijet.M() << std::endl;

		   hmjjdat->Fill(mydijet.M(),myweight);
		   hyjjdat->Fill(mydijet.Rapidity(),myweight);
		   hmyjjdat->Fill(mydijet.M(),mydijet.Rapidity());
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
			   htau21ddtdat1->Fill(taut21ddt1,myweight);
			 }
		       if(jet_corrmass->at(indsecond) >= 55 && jet_corrmass->at(indsecond) <= 215)
			 {
			   htau21dat2->Fill(jet_tau2->at(indsecond)/jet_tau1->at(indsecond),myweight);
			   hmjdat2->Fill(jet_corrmass->at(indsecond),myweight);
                           rhoprime2 = TMath::Log(jet_corrmass->at(indsecond)*jet_corrmass->at(indsecond)/jet_pt->at(indsecond));
			   taut21ddt2 = (jet_tau2->at(indsecond)/jet_tau1->at(indsecond)) - (-0.082 * rhoprime2);
                           htau21ddtdat2->Fill(taut21ddt2,myweight);
			 }
		       hptdat1->Fill(jet_pt->at(indleading),myweight);
		       hptdat2->Fill(jet_pt->at(indsecond),myweight);
		       hetadat1->Fill(jet_eta->at(indleading),myweight);
		       hetadat2->Fill(jet_eta->at(indsecond),myweight);
		       hphidat1->Fill(jet_phi->at(indleading),myweight);
		       hphidat2->Fill(jet_phi->at(indsecond),myweight);
		       hdeta->Fill(fabs(jet_eta->at(indleading) - jet_eta->at(indsecond)),myweight);
		       hnvtx->Fill(nVertices,myweight);
		       hcrossingangle->Fill(crossingangle,myweight);
		       hptratio->Fill(jet1.Pt()/jet2.Pt(),myweight);
		       
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

		       // Proton part
		       float mpp = 0;
		       float ypp = 0;

		       int ismultimulti = 0;
		       int issinglesingle = 0;
		       int ismixed = 0;
		       int nSinglePixelTracks45 = 0;
		       int nSinglePixelTracks56 = 0;
		       int nMultiTracks45 = 0;
		       int nMultiTracks56 = 0;

		       if(proton_xi->size() > 1)
			 {
			   float thexi = 0;

			   for(int p = 0; p < proton_xi->size(); p++)                                                                                                 
			     {
			       thexi = proton_xi->at(p);

			       if((proton_ismultirp->at(p) == 0) && (proton_rpid->at(p) == 23))                                                                       
				 {
				   if(proton_trackpixshift1->at(p) == 0)
				     {
				       xipix45s->push_back(thexi);
				       hxipix45->Fill(thexi);
				       //				       ypix45s->push_back(proton_tracky1->at(p));
				       nSinglePixelTracks45++;
				     }
				 }
                               if((proton_ismultirp->at(p) == 0) && (proton_rpid->at(p) == 123))
                                 {
                                   if(proton_trackpixshift1->at(p) == 0)
				     {
				       xipix56s->push_back(thexi);
                                       hxipix56->Fill(thexi);
				       //				       ypix56s->push_back(proton_tracky1->at(p));
                                       nSinglePixelTracks56++;
				     }
                                 }
                               if((proton_ismultirp->at(p) == 1) && (proton_arm->at(p) == 0))
                                 {
				   if(proton_trackpixshift1->at(p) == 0)
				     {
				       ximulti45s->push_back(thexi);
				       hximult45->Fill(thexi);
				       nMultiTracks45++;
				     }
                                 }
                               if((proton_ismultirp->at(p) == 1) && (proton_arm->at(p) == 1))
                                 {
				   if(proton_trackpixshift1->at(p) == 0)
				     {
				       ximulti56s->push_back(thexi);
				       hximult56->Fill(thexi);
				       nMultiTracks56++;
				     }
                                 }
			     }

			   if(nMultiTracks45 >= 1 && nMultiTracks56 >= 1)
                             {
                               for(int a = 0; a < nMultiTracks45; a++)
                                 {
                                   for(int b = 0; b < nMultiTracks56; b++)
                                     {
				       mpp = TMath::Sqrt(13000.0*13000.0*ximulti56s->at(b)*ximulti45s->at(a));
				       ypp = 0.5*TMath::Log(ximulti56s->at(b)/ximulti45s->at(a));
                                       mppsmultmult->push_back(mpp);
                                       yppsmultmult->push_back(ypp);
				       hmppmulti->Fill(mpp);
				       hyppmulti->Fill(ypp);
				       ismultimulti = 1;
                                     }
                                 }
                             }
			   else if((nMultiTracks45 >= 1 && nSinglePixelTracks56 >= 1) || (nMultiTracks56 >= 1 && nSinglePixelTracks45 >= 1))
			     {
			       for(int a = 0; a < nSinglePixelTracks45; a++)
                                 {
                                   for(int b = 0; b < nMultiTracks56; b++)
                                     {
				       mpp = TMath::Sqrt(13000.0*13000.0*ximulti56s->at(b)*xipix45s->at(a));
				       ypp = 0.5*TMath::Log(ximulti56s->at(b)/xipix45s->at(a));
                                       mppsmixed->push_back(mpp);
                                       yppsmixed->push_back(ypp);
				       hmppmixed->Fill(mpp);
				       hyppmixed->Fill(ypp);
                                     }
                                 }
			       for(int a = 0; a < nSinglePixelTracks56; a++)
                                 {
                                   for(int b = 0; b < nMultiTracks45; b++)
                                     {
				       mpp = TMath::Sqrt(13000.0*13000.0*xipix56s->at(a)*ximulti45s->at(b));
				       ypp = 0.5*TMath::Log(xipix56s->at(a)/ximulti45s->at(b));
                                       mppsmixed->push_back(mpp);
                                       yppsmixed->push_back(ypp);
				       hmppmixed->Fill(mpp);
				       hyppmixed->Fill(ypp);
                                     }
                                 }
			     }
			   else if(nSinglePixelTracks45 >= 1 && nSinglePixelTracks56 >= 1)
			     {
			       for(int a = 0; a < nSinglePixelTracks45; a++)
				 {
				   for(int b = 0; b < nSinglePixelTracks56; b++)
				     {
				       mpp = TMath::Sqrt(13000.0*13000.0*xipix56s->at(b)*xipix45s->at(a));
				       ypp = 0.5*TMath::Log(xipix56s->at(b)/xipix45s->at(a));
				       mppssingsing->push_back(mpp);
				       yppssingsing->push_back(ypp);
				       hmppsingle->Fill(mpp);
				       hyppsingle->Fill(ypp);
				       hmyppsingle->Fill(mpp,ypp);
				     }
				 }
			     }
			 }
		       hnpix45->Fill(nSinglePixelTracks45);
		       hnpix56->Fill(nSinglePixelTracks56);


                       // Sideband control regions                                                                                                                                                                           
                       if(samplenumber > 0)
                         {
                           // Signal region, only for MC                                                                                                                                                                     
                           if((acop < acopcut) &&
                              (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut &&
                                                                                                                        jet_corrmass->at(indsecond) <= mwhicut) &&
                              (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                              (jet1.Pt()/jet2.Pt() < ptbalcut))
                             {
                               hmasswwsignal->Fill(mydijet.M());
                               hywwsignal->Fill(mydijet.Rapidity());
			       if(samplenumber >= 20 && mpp>0)
				 {
				   hmassmatchsigmc->Fill(mpp-mydijet.M());
				   hymatchsigmc->Fill(ypp-mydijet.Rapidity());
				   hmassmatchratiosigmc->Fill(1 - (mydijet.M()/mpp));
				   if(ismultimulti == 1)
				     hmassmatchratiosigmcmult->Fill(1 - (mydijet.M()/mpp));
				   //				   hmppres->Fill(mpp/genmpp);
				   //				   hmjjres->Fill(mydijet.M()/gen_dijet_mass->at(0));
				 }
                             }
                         }


		       // Control regions
                       // Anti acoplanarity                                                                                                                                                                
                       if((acop > acopcut) &&
                          (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                          (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                          (jet1.Pt()/jet2.Pt() < ptbalcut))
                         {
                           hmasswwantiacop->Fill(mydijet.M());
			   if(samplenumber < 0 && mpp>0)
			     {
			       hmassmatchantiacop->Fill(mpp-mydijet.M());
			       hymatchantiacop->Fill(ypp-mydijet.Rapidity());
			       hmassmatchratioantiacop->Fill(1 - (mydijet.M()/mpp));
			     }
                         }
                       // Anti pT balance                                                                                                                                                                  
                       if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
                          (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                          (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                          (acop < 0.005))
                         {
                           hmasswwantiptbal->Fill(mydijet.M());
                           if(samplenumber < 0 && mpp>0)
                             {
                               hmassmatchantiptbal->Fill(mpp-mydijet.M());
                               hymatchantiptbal->Fill(ypp-mydijet.Rapidity());
                               hmassmatchratioantiptbal->Fill(1 - (mydijet.M()/mpp));
                             }
                         }
                       // Anti tau21                                                                                                                                                                       
                       if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
                          (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                          (acop < 0.005) &&
                          (jet1.Pt()/jet2.Pt()) <  ptbalcut)
                         {
                           hmasswwantitau->Fill(mydijet.M());
                           if(samplenumber < 0 && mpp>0)
                             {
                               hmassmatchantitau->Fill(mpp-mydijet.M());
                               hymatchantitau->Fill(ypp-mydijet.Rapidity());
                               hmassmatchratioantitau->Fill(1 - (mydijet.M()/mpp));

                             }
                         }

		     }
		 }
	     }
	 }
       
       mppssingsing->clear();
       yppssingsing->clear();
       mppsmixed->clear();
       yppsmixed->clear();
       mppsmultmult->clear();
       yppsmultmult->clear();
       xipix45s->clear();
       xipix56s->clear();
       ypix45s->clear();
       ypix56s->clear();
       ximulti45s->clear();
       ximulti56s->clear();
     }

   delete mppssingsing;
   delete yppssingsing;
   delete mppsmixed;
   delete yppsmixed;
   delete mppsmultmult;
   delete yppsmultmult;
   delete xipix45s;
   delete xipix56s;
   delete ypix45s;
   delete ypix56s;
   delete ximulti45s;
   delete ximulti56s;

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
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017B.root","RECREATE");
   if(samplenumber == -2)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017C.root","RECREATE");
   if(samplenumber == -3)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017D.root","RECREATE");
   if(samplenumber == -4)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017E.root","RECREATE");
   if(samplenumber == -5)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2017F.root","RECREATE");

   if(samplenumber == -6)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2016B.root","RECREATE");
   if(samplenumber == -7)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2016C.root","RECREATE");
   if(samplenumber == -8)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2016G.root","RECREATE");
   if(samplenumber == -9)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_datahist2016H.root","RECREATE");


   if(samplenumber == 1)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt170to300.root","RECREATE");
   if(samplenumber == 2)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt300to470.root","RECREATE");
   if(samplenumber == 3)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt470to600.root","RECREATE");
   if(samplenumber == 4)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt600to800.root","RECREATE");                                                           
   if(samplenumber == 5)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt800to1000.root","RECREATE");
   if(samplenumber == 6)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_qcdpt1000to1400.root","RECREATE");
   if(samplenumber == 7)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_ttbarhadronic.root","RECREATE");
   if(samplenumber == 8)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_wjetshadronic.root","RECREATE");
   if(samplenumber == 9)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_zjetshadronic.root","RECREATE");

   if(samplenumber == 20)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwSM.root","RECREATE");
   if(samplenumber == 21)
     //     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w2point5.root","RECREATE");
     //     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w1point0onlyPUprotons.root","RECREATE");
     //     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w1point0noPUprotons_testNoMassCut.root","RECREATE");
     //     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w1point0withPUprotons.root","RECREATE");
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclwwa0w1point0noPUprotons.root","RECREATE");

   if(samplenumber == 31)
     fx = new TFile("vars_cuts_ntupleULv1recalcmjcut_jerallhltfixptetacuts_exclzza0z2point5.root","RECREATE");

   hmjjdat->Write();
   hyjjdat->Write();
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
   hcrossingangle->Write();
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
   hximult45->Write();
   hximult56->Write();
   hnpix45->Write();
   hnpix56->Write();

   hmppsingle->Write();
   hmppmixed->Write();
   hmppmulti->Write();
   hyppsingle->Write();
   hyppmixed->Write();
   hyppmulti->Write();

   hmassmatchantiw->Write();
   hymatchantiw->Write();
   hmassmatchratioantiw->Write();
   hmassmatchantitau->Write();
   hymatchantitau->Write();
   hmassmatchratioantitau->Write();
   hmassmatchantiacop->Write();
   hymatchantiacop->Write();
   hmassmatchratioantiacop->Write();
   hmassmatchantiptbal->Write();
   hymatchantiptbal->Write();
   hmassmatchratioantiptbal->Write();

   hmassmatchsigmc->Write();
   hymatchsigmc->Write();
   hmassmatchratiosigmc->Write();
   hmassmatchratiosigmcmult->Write();

   hmasswwantitau->Write();
   hmasswwantiacop->Write();
   hmasswwantiptbal->Write();
   hmasswwsignal->Write();
   hywwsignal->Write();

   hmyppsingle->Write();
   hmyjjdat->Write();

   fx->Close();
}
