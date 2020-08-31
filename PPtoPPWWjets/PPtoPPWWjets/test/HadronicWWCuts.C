#define HadronicWWCuts_cxx
#include "HadronicWWCuts.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <string.h>
#include <TMath.h>

/*                                                                                                                                                                          
 * This function applies the 2017 pixel radiation damage efficiencies to signal MC, using the 2-d x,y maps. 
 * The efficiencies are averaged over all currently available tables for pre-TS2 and post-TS2. 
 * Currently it throws a random number to accept-reject the proton, rather than weighting the event (could be changed). 
 *
 * This should be used for single-RP pixel protons.                                                                                                                         
 * Requires the following files to be present in the working directory: pixelEfficiencies.root, PreliminaryEfficiencies_October92019_1D2DMultiTrack.root 
 * Ref: https://indico.cern.ch/event/854012/contributions/3610560/attachments/1930919/3198180/POGPixelEfficiency_2017.pdf                                                   
 */
bool HadronicWWCuts::SingleRPEffCorr(Float_t trackx220, Float_t tracky220, Int_t arm, Int_t thesample)
{
  float effcorr = 1.0;
  bool passes = true;

  // Apply to signal MC - here for 2017 pre-TS2
  if(thesample == 21 || thesample == 22 || thesample == 27 || thesample == 31 || thesample == 99)
    {
      if(arm == 0)
	effcorr = hpixeff2017PreTS245->GetBinContent(hpixeff2017PreTS245->FindBin(trackx220,tracky220));
      if(arm == 1)
	effcorr = hpixeff2017PreTS256->GetBinContent(hpixeff2017PreTS256->FindBin(trackx220,tracky220));
    }
  // 2017 post-TS2
  if(thesample == 24 || thesample == 25 || thesample == 41)
    {
      if(arm == 0)
        effcorr = hpixeff2017PostTS245->GetBinContent(hpixeff2017PostTS245->FindBin(trackx220,tracky220));
      if(arm == 1)
        effcorr = hpixeff2017PostTS256->GetBinContent(hpixeff2017PostTS256->FindBin(trackx220,tracky220));
    }

  float therand = rnd->Uniform();
  if(therand <= effcorr)
    passes = true;
  else
    {
      passes = false;
    }

  return passes;
}

/*                                                                                                                                                                          
 * This function applies the 2017 pixel radiation damage and strip radiation damage, plus the strip multi-track efficiencies, to signal MC.
 * The total efficiency is taken as the product of those 3 terms. The 2-d x,y maps are used for the radiation damage efficiency.                                            
 * The efficiencies are averaged over all currently available tables for pre-TS2 and post-TS2.                                                                              
 * Currently it throws a random number to accept-reject the proton, rather than weighting the event (could be changed).                                                     
 *                                                                                                                                                                          
 * This should be used for multi-RP protons.                                                                                                                         
 * Requires the following files to be present in the working directory: pixelEfficiencies.root, PreliminaryEfficiencies_October92019_1D2DMultiTrack.root                    
 * Refs: https://indico.cern.ch/event/854012/contributions/3610560/attachments/1930919/3198180/POGPixelEfficiency_2017.pdf                                                   
 * https://indico.cern.ch/event/853567/contributions/3591200/attachments/1922308/3180339/StripsEffPOG_08102019.pdf
 */
bool HadronicWWCuts::MultiRPEffCorr(Float_t trackx210, Float_t tracky210, Float_t trackx220, Float_t tracky220, Int_t arm, Int_t thesample)
{
  float effcorrpixrad = 1.0;
  float effcorrstrrad = 1.0;
  float effcorrstrmultitrk = 1.0;

  bool passes = true;

  // Apply to signal MC - here for 2017 pre-TS2 rad damage                                                                                                                         
  if(thesample == 21 || thesample == 22 || thesample == 27 || thesample == 31 || thesample == 99)
    {
      if(arm == 0)
	{
	  effcorrpixrad = hpixeff2017PreTS245->GetBinContent(hpixeff2017PreTS245->FindBin(trackx220,tracky220));
	  effcorrstrrad = hstreff2017PreTS245->GetBinContent(hstreff2017PreTS245->FindBin(trackx210,tracky210));
	  effcorrstrmultitrk = hmultistreff2017PreTS245->GetBinContent(1);
	}
      if(arm == 1)
	{
	  effcorrpixrad = hpixeff2017PreTS256->GetBinContent(hpixeff2017PreTS256->FindBin(trackx220,tracky220));
          effcorrstrrad = hstreff2017PreTS256->GetBinContent(hstreff2017PreTS256->FindBin(trackx210,tracky210));
          effcorrstrmultitrk = hmultistreff2017PreTS256->GetBinContent(1);
	}
    }
  // 2017 post-TS2 rad damage
  if(thesample == 24 || thesample == 25 || thesample == 41)
    {
      if(arm == 0)
        {
          effcorrpixrad = hpixeff2017PostTS245->GetBinContent(hpixeff2017PostTS245->FindBin(trackx220,tracky220));
          effcorrstrrad = hstreff2017PostTS245->GetBinContent(hstreff2017PostTS245->FindBin(trackx210,tracky210));
          effcorrstrmultitrk = hmultistreff2017PostTS245->GetBinContent(1);
        }
      if(arm == 1)
        {
          effcorrpixrad = hpixeff2017PostTS256->GetBinContent(hpixeff2017PostTS256->FindBin(trackx220,tracky220));
          effcorrstrrad = hstreff2017PostTS256->GetBinContent(hstreff2017PostTS256->FindBin(trackx210,tracky210));
          effcorrstrmultitrk = hmultistreff2017PostTS256->GetBinContent(1);
        }
    }

  float therand = rnd->Uniform();
  if(therand <= (effcorrpixrad*effcorrstrrad*effcorrstrmultitrk))
    passes = true;
  else
    {
      passes = false;
    }

  return passes;
}

/*
 * This function applies the 2017 pixel fiducial cuts on data or signal MC. Depending on the sample 2 different sets of cuts are used 
 * for pre-TS2 and post-TS2. In case the fiducial cuts are given for finer time periods, the most strict set is used.
 *
 * Ref: https://indico.cern.ch/event/854012/contributions/3610560/attachments/1930919/3198180/POGPixelEfficiency_2017.pdf
 */
bool HadronicWWCuts::PixelFiducial(Float_t trackx, Float_t tracky, Int_t arm, Int_t thesample)
{
  bool passesfiducial = false; 

  float pixacceptxmin = -999.;
  float pixacceptxmax = 999.;
  float pixacceptymin = -999.;
  float pixacceptymax = 999.;

  if((thesample < 0 && thesample > -4) || (thesample == 21 || thesample == 22 || thesample == 27 || thesample == 31 || thesample == 99)) // preTS2 2017
    {
      if(arm == 0)
	{
	  pixacceptxmin = 1.995;
	  pixacceptxmax = 24.334;
	  pixacceptymin = -11.098;
	  pixacceptymax = 4.298;
	}
      if(arm == 1)
	{
          pixacceptxmin = 2.137;
          pixacceptxmax = 24.620;
          pixacceptymin = -10.698;
          pixacceptymax = 4.698;
	}
    }
  if((thesample < -3 && thesample > -6) || (thesample == 24 || thesample == 25))// postTS2 2017
    {
      if(arm == 0)
        {
          pixacceptxmin = 1.995;
          pixacceptxmax = 24.497;
          pixacceptymin = -10.098;
          pixacceptymax = 4.998;
        }
      if(arm == 1)
        {
          pixacceptxmin = 2.422;
          pixacceptxmax = 24.620;
          pixacceptymin = -9.698;
          pixacceptymax = 5.398;
        }
    }

  if((trackx > pixacceptxmin) && (trackx < pixacceptxmax) && (tracky > pixacceptymin) && (tracky < pixacceptymax))
    passesfiducial = true;

  return passesfiducial;
}

/*                                                                                                                                                                          
 * This function applies the collimator aperture cuts on data or signal MC, based on the crossing angle, arm, and era. 
 *                                                                                                                                                                          
 * Ref: https://indico.cern.ch/event/849095/contributions/3568020/attachments/1913799/3163250/j_kaspar_apertures.pdf
 */
float HadronicWWCuts::Aperture(Float_t xangle, Int_t arm, TString era)
{
  float aperturelimit = 0.0;
  if(era == "2016preTS2")
    {
      if(arm == 0)
	aperturelimit = 0.111;
      if(arm == 1)
	aperturelimit = 0.138;
    }
  if(era == "2016postTS2")
    {
      if(arm == 0)
        aperturelimit = 0.104;
      if(arm == 1) // Note - 1 strip RP was not in, so no aperture cuts derived
        aperturelimit = 999.9;
    }
  if(era == "2017preTS2")
    {
      if(arm == 0)
	aperturelimit = 0.066 + (3.54E-4 * xangle);
      if(arm == 1)
        aperturelimit = 0.062 + (5.96E-4 * xangle);
    }
  if(era == "2017postTS2")
    {
      if(arm == 0)
        aperturelimit = 0.073 + (4.11E-4 * xangle);
      if(arm == 1)
        aperturelimit = 0.067 + (6.87E-4 * xangle);
    }
  if(era == "2018")
    {
      if(arm == 0)
        aperturelimit = 0.079 + (4.21E-4 * xangle);
      if(arm == 1)
        aperturelimit = 0.074 + (6.6E-4 * xangle);
    }

  return aperturelimit;
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
   // Limit bkg MC samples to 1M events for quick tests
   //   if((samplenumber > 1 && samplenumber < 20) || (samplenumber > 100 && samplenumber < 120) || (samplenumber > 200 && samplenumber < 220))
   //     nentries = 1000000;
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

   TH1F *hmppmulti = new TH1F("hmppmulti","hmppmulti",250,0,5000);
   TH1F *hyppmulti = new TH1F("hyppmulti","hyppmulti",250,-5,5);

   TH2F *hmyppsingle = new TH2F("hmyppsingle","hmyppsingle",100,0,5000,100,-5,5);
   TH2F *hmyppmulti = new TH2F("hmyppmulti","hmyppmulti",100,0,5000,100,-5,5);
   TH2F *hmyjjdat = new TH2F("hmyjjdat","hmyjjdat",100,0,5000,100,-5,5);



   TH1F *hmjdat1 = new TH1F("hmjdat1","hmjdat1",250,0,1000);
   TH1F *htau21dat1 = new TH1F("htau21dat1","htau21dat1",250,0,1);
   TH1F *hmjdat2 = new TH1F("hmjdat2","hmjdat2",250,0,1000);
   TH1F *htau21dat2 = new TH1F("htau21dat2","htau21dat2",250,0,1);
   TH1F *htau21ddtdat1 = new TH1F("htau21ddtdat1","htau21ddtdat1",250,0,1.5);
   TH1F *htau21ddtdat2 = new TH1F("htau21ddtdat2","htau21ddtdat2",250,0,1.5);
   TH2F *tau21vrhoprime1 = new TH2F("tau21vrhoprime1","tau21vrhoprime1",100,0,5,100,0,1);
   TH2F *tau21vrhoprime2 = new TH2F("tau21vrhoprime2","tau21vrhoprime2",100,0,5,100,0,1);

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
   TH1F *hthystmult45 = new TH1F("hthystmult45","hthystmult45",500,-0.001,0.001);
   TH1F *hthystmult56 = new TH1F("hthystmult56","hthystmult56",500,-0.001,0.001);
   TH1F *htmult45 = new TH1F("htmult45","htmult45",500,0,10);
   TH1F *htmult56 = new TH1F("htmult56","htmult56",500,0,10);
   TH1F *hdtmulti = new TH1F("hdtmulti","hdtmulti",500,-25,25);

   TH1F *hnmult45 = new TH1F("hnmult45","hnmult45",15,0,15);
   TH1F *hnmult56 = new TH1F("hnmult56","hnmult56",15,0,15);

   TH1F *hdxi45 = new TH1F("hdxi45","hdxi45",500,-0.2,0.2);
   TH1F *hdy45 = new TH1F("hdy45","hdy45",500,-20,20);
   TH1F *hdxi56 = new TH1F("hdxi56","hdxi56",500,-0.2,0.2);
   TH1F *hdy56 = new TH1F("hdy56","hdy56",500,-20,20);

   TH1F *hmassmatchantiw = new TH1F("hmassmatchantiw","hmassmatchantiw",500,-2500,2500);
   TH1F *hymatchantiw = new TH1F("hymatchantiw","hymatchantiw",100,-5,5);
   TH1F *hmassmatchratioantiw = new TH1F("hmassmatchratioantiw","hmassmatchratioantiw",100,-5,5);

   TH1F *hmassmatchantiacopmm = new TH1F("hmassmatchantiacopmm","hmassmatchantiacopmm",500,-2500,2500);
   TH1F *hymatchantiacopmm = new TH1F("hymatchantiacopmm","hymatchantiacopmm",100,-5,5);
   TH1F *hmassmatchratioantiacopmm = new TH1F("hmassmatchratioantiacopmm","hmassmatchratioantiacopmm",100,-5,5);
   TH1F *hmassmatchantitaumm = new TH1F("hmassmatchantitaumm","hmassmatchantitaumm",500,-2500,2500);
   TH1F *hymatchantitaumm = new TH1F("hymatchantitaumm","hymatchantitaumm",100,-5,5);
   TH1F *hmassmatchratioantitaumm = new TH1F("hmassmatchratioantitaumm","hmassmatchratioantitaumm",100,-5,5);
   TH1F *hmassmatchantiptbalmm = new TH1F("hmassmatchantiptbalmm","hmassmatchantiptbalmm",500,-2500,2500);
   TH1F *hymatchantiptbalmm = new TH1F("hymatchantiptbalmm","hymatchantiptbalmm",100,-5,5);
   TH1F *hmassmatchratioantiptbalmm = new TH1F("hmassmatchratioantiptbalmm","hmassmatchratioantiptbalmm",100,-5,5);

   TH1F *hmassmatchsigmcmm = new TH1F("hmassmatchsigmcmm","hmassmatchsigmcmm",500,-2500,2500);
   TH1F *hymatchsigmcmm = new TH1F("hymatchsigmcmm","hymatchsigmcmm",500,-5,5);
   TH1F *hmassmatchratiosigmcmm = new TH1F("hmassmatchratiosigmcmm","hmassmatchratiosigmcmm",500,-5,5);

   TH2F *hmassrapiditymatchvetosignalregion = new TH2F("hmassrapiditymatchvetosignalregion","hmassrapiditymatchvetosignalregion",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchvetoorsignalregion = new TH2F("hmassrapiditymatchvetoorsignalregion","hmassrapiditymatchvetoorsignalregion",500,-5,5,500,-5,5);

   TH2F *hmassrapiditymatchantitaumm = new TH2F("hmassrapiditymatchantitaumm","hmassrapiditymatchantitaumm",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiacopmm = new TH2F("hmassrapiditymatchantiacopmm","hmassrapiditymatchantiacopmm",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiptbalmm = new TH2F("hmassrapiditymatchantiptbalmm","hmassrapiditymatchantiptbalmm",500,-5,5,500,-5,5);


   TH1F *hymatchsigmcmult = new TH1F("hymatchsigmcmult","hymatchsigmcmult",500,-5,5);
   TH2F *hmasscorrsigmcmult = new TH2F("hmasscorrsigmcmult","hmasscorrsigmcmult",250,0,2500,250,0,2500);
   TH2F *hycorrsigmcmult = new TH2F("hycorrsigmcmult","hycorrsigmcmult",100,-5,5,100,-5,5);
   TH2F *hmasscorrsigmcmulttruthmatched = new TH2F("hmasscorrsigmcmulttruthmatched","hmasscorrsigmcmulttruthmatched",250,0,2500,250,0,2500);

   TH2F *hycorrpreseldatmult = new TH2F("hycorrpreseldatmult","hycorrpreseldatmult",100,-5,5,100,-5,5);
   TH2F *hmasscorrpreseldatmult = new TH2F("hmasscorrpreseldatmult","hmasscorrpreseldatmult",250,0,2500,250,0,2500);
   TH2F *dymassratiocorrpreseldatmult = new TH2F("dymassratiocorrpreseldatmult","dymassratiocorrpreseldatmult",500,-5,5,500,-5,5);

   TH1F *hmasswwantiptbal = new TH1F("hmasswwantiptbal","hmasswwantiptbal",250,0,5000);

   // Anti-acoplanarity control plots
   TH1F *hmasswwantiacop = new TH1F("hmasswwantiacop","hmasswwantiacop",250,0,5000);
   TH1F *hmj1antiacop = new TH1F("hmj1antiacop","hmj1antiacop",250,0,1000);
   TH1F *htau211antiacop = new TH1F("htau211antiacop","htau211antiacop",250,0,1);
   TH1F *hmj2antiacop = new TH1F("hmj2antiacop","hmj2antiacop",250,0,1000);
   TH1F *htau212antiacop = new TH1F("htau212antiacop","htau212antiacop",250,0,1);

   // Anti-tau21 control plots
   TH1F *hmasswwantitau = new TH1F("hmasswwantitau","hmasswwantitau",250,0,5000);
   TH1F *hmj1antitau = new TH1F("hmj1antitau","hmj1antitau",250,0,1000);
   TH1F *htau211antitau = new TH1F("htau211antitau","htau211antitau",250,0,1);
   TH1F *hmj2antitau = new TH1F("hmj2antitau","hmj2antitau",250,0,1000);
   TH1F *htau212antitau = new TH1F("htau212antitau","htau212antitau",250,0,1);

   TH1F *hmasswwsignal = new TH1F("hmasswwsignal","hmasswwsignal",250,0,5000);
   TH1F *hywwsignal = new TH1F("hywwsignal","hywwsignal",250,-5,5);
   TH1F *hcrossingangle = new TH1F("hcrossingangle","hcrossingangle",70,100,170);

   TH1F *hmppres = new TH1F("hmppres","hmppres",100,0,2);
   TH1F *hmjjres = new TH1F("hmjjres","hmjjres",100,0,2);
   TH1F *hmassmatchratiosigmcmult = new TH1F("hmassmatchratiosigmcmult","hmassmatchratiosigmcmult",500,-5,5);

   TH1F *xijets45= new TH1F("xijets45","xijets45",250,0,0.25);
   TH1F *xijets56= new TH1F("xijets56","xijets56",250,0,0.25);
   TH1F *resxijets45= new TH1F("resxijets45","resxijets45",100,0,2);
   TH1F *resxijets56= new TH1F("resxijets56","resxijets56",100,0,2);
   TH2F *resxijetscorr45= new TH2F("resxijetscorr45","resxijetscorr45",300,0,0.3,300,0,0.3);
   TH2F *resxijetscorr56= new TH2F("resxijetscorr56","resxijetscorr56",300,0,0.3,300,0,0.3);


   std::vector<float> *mppsmultmult = new std::vector<float>;
   std::vector<float> *yppsmultmult = new std::vector<float>;
   std::vector<float> *xipix45s = new std::vector<float>;
   std::vector<float> *xipix56s = new std::vector<float>;
   std::vector<float> *ypix45s = new std::vector<float>;
   std::vector<float> *ypix56s = new std::vector<float>;
   std::vector<float> *ximulti45s = new std::vector<float>;
   std::vector<float> *ximulti56s = new std::vector<float>;
   std::vector<float> *thystmulti45s = new std::vector<float>;
   std::vector<float> *thystmulti56s = new std::vector<float>;
   std::vector<float> *tmulti45s = new std::vector<float>;
   std::vector<float> *tmulti56s = new std::vector<float>;
   std::vector<float> *timemulti45s = new std::vector<float>;
   std::vector<float> *timemulti56s = new std::vector<float>;


   // Counters for # of MC events passing cuts
   Int_t npasspresel = 0;
   Int_t npassdijetkine = 0;
   Int_t npassjetsubstr = 0;
   Int_t npassjetxi = 0;
   Int_t npasspps = 0;
   Int_t npassppsbeforecuts = 0;
   Int_t npassppsmatchksenia = 0;

   TString outtextfile = "MC_EventsForMixing.txt";

   if(samplenumber == 2)
     outtextfile = "MC_EventsForMixing_QCD300to470_2017.txt";
   if(samplenumber == 3)
     outtextfile = "MC_EventsForMixing_QCD470to600_2017.txt";
   if(samplenumber == 4)
     outtextfile = "MC_EventsForMixing_QCD600to800_2017.txt";
   if(samplenumber == 5)
     outtextfile = "MC_EventsForMixing_QCD800to1000_2017.txt";
   if(samplenumber == 6)
     outtextfile = "MC_EventsForMixing_QCD1000to1400_2017.txt";
   if(samplenumber == 10)
     outtextfile = "MC_EventsForMixing_QCD1400to1800_2017.txt";
   if(samplenumber == 7)
     outtextfile = "MC_EventsForMixing_ttbar_2017.txt";
   if(samplenumber == 8)
     outtextfile = "MC_EventsForMixing_wjets_2017.txt";
   if(samplenumber == 9)
     outtextfile = "MC_EventsForMixing_zjets_2017.txt";

   if(samplenumber == 20)
     outtextfile = "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2017.txt";
   if(samplenumber == 23)
     outtextfile = "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2017.txt";

   if(samplenumber == 40)
     outtextfile = "MC_EventsForMixing_signal_WWA0W1E-6_postTS2_2017.txt";
   if(samplenumber == 43)
     outtextfile = "MC_EventsForMixing_signal_WWACW2E-5_postTS2_2017.txt";


   if(samplenumber == 102)
     outtextfile = "MC_EventsForMixing_QCD300to470_2016.txt";
   if(samplenumber == 103)
     outtextfile = "MC_EventsForMixing_QCD470to600_2016.txt";
   if(samplenumber == 104)
     outtextfile = "MC_EventsForMixing_QCD600to800_2016.txt";
   if(samplenumber == 105)
     outtextfile = "MC_EventsForMixing_QCD800to1000_2016.txt";
   if(samplenumber == 106)
     outtextfile = "MC_EventsForMixing_QCD1000to1400_2016.txt";
   if(samplenumber == 110)
     outtextfile = "MC_EventsForMixing_QCD1400to1800_2016.txt";
   if(samplenumber == 107)
     outtextfile = "MC_EventsForMixing_ttbar1000inf_2016.txt";
   if(samplenumber == 108)
     outtextfile = "MC_EventsForMixing_wjets_2016.txt";
   if(samplenumber == 109)
     outtextfile = "MC_EventsForMixing_zjets_2016.txt";
   if(samplenumber == 111)
     outtextfile = "MC_EventsForMixing_ttbar700to1000_2016.txt";

   if(samplenumber == 120)
     outtextfile = "MC_EventsForMixing_signal_WWA0W1E-6_preTS2_2016.txt";
   if(samplenumber == 123)
     outtextfile = "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2016.txt";

   if(samplenumber == 202)
     outtextfile = "MC_EventsForMixing_QCD300to470_2018.txt";
   if(samplenumber == 203)
     outtextfile = "MC_EventsForMixing_QCD470to600_2018.txt";
   if(samplenumber == 204)
     outtextfile = "MC_EventsForMixing_QCD600to800_2018.txt";
   if(samplenumber == 205)
     outtextfile = "MC_EventsForMixing_QCD800to1000_2018.txt";
   if(samplenumber == 206)
     outtextfile = "MC_EventsForMixing_QCD1000to1400_2018.txt";
   if(samplenumber == 210)
     outtextfile = "MC_EventsForMixing_QCD1400to1800_2018.txt";
   if(samplenumber == 207)
     outtextfile = "MC_EventsForMixing_ttbar_2018.txt";
   if(samplenumber == 208)
     outtextfile = "MC_EventsForMixing_wjets_2018.txt";
   if(samplenumber == 209)
     outtextfile = "MC_EventsForMixing_zjets_2018.txt";

   if(samplenumber == 220)
     outtextfile = "MC_EventsForMixing_signal_WWA0W1E-6_2018.txt";
   if(samplenumber == 223)
     outtextfile = "MC_EventsForMixing_signal_WWACW2E-5_2018.txt";


   ofstream ofs(outtextfile);


   // Mapping of sample number to era for data
   if(samplenumber < 0 && samplenumber > -4)
     {
       erastring = "2017preTS2";
     }
   if(samplenumber < -3 && samplenumber > -6)
     {
       erastring = "2017postTS2";
     }
   if(samplenumber < -5 && samplenumber > -9)
     {
       erastring = "2016preTS2";
     }
   if(samplenumber == -9)
     {
       erastring = "2016postTS2";
     }
   if(samplenumber < -9)
     {
       erastring = "2018";
     }
   // Mapping of sample number to era for signal MC
   if(samplenumber >= 20 && samplenumber < 40)
     {
       erastring = "2017preTS2";
     }
   if(samplenumber >= 40 && samplenumber <= 60)
     {
       erastring = "2017postTS2";
     }
   if(samplenumber >= 120 && samplenumber < 200)
     {
       erastring = "2016preTS2";
     }
   if(samplenumber >= 220 && samplenumber < 300)
     {
       erastring = "2018";
     }

   PPSProtonEfficiency eff;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       
       //       if(jentry % 20000 == 0)
       if(jentry % 200 == 0)
	 cout << "Entry " << jentry << "/" << nentries << endl;

       if(jet_pt->size() < 2)
	 continue;

       Int_t passht = 0;
       Int_t passpfjet = 0;
       Int_t passpfjettrim = 0;
       Int_t passpfhttrim = 0;

       /* Now filtering on HLT at ntuple-making level!
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
       */
       if(1)
	 {
	   Float_t ptjet1 = 0.0; Float_t ptjet2 = 0.0;
           Float_t etajet1 = 0.0; Float_t etajet2 = 0.0;
           Float_t phijet1 = 0.0; Float_t phijet2 = 0.0;
           Float_t ejet1 = 0.0; Float_t ejet2 = 0.0;
           int indleading = 0;
           int indsecond = 1;

           TLorentzVector jet1; TLorentzVector jet2; TLorentzVector mydijet;
           float C_JER1=-999.;
           float C_JER2=-999.;

	   if(samplenumber > 0)
	     {
	       myweight = pileupWeight;

	       /* Apply JER smearing */
	       TLorentzVector recojtmp, genjtmp;
	       TRandom3 randomSrc;
	       int matchedgen=0;
	       int indmatchedgen=-1;
	       float ptleading = 0;
	       float ptsecond = 0;
	       float C_JER=-999;

	       //       cout << "Starting checks on JER" << endl;
	       for(int ir = 0; ir < jet_pt->size(); ir++)
		 {
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
		   //   cout << "\tChecking " << C_JER*recojtmp.Pt() << " against leading pT = " << ptleading << ", second leading pT = " << ptsecond << endl;
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
		       //       cout << "\t\tSetting new leading to pT = " << ptleading << ", index = " << indleading << endl;
		     }
		   if((C_JER*recojtmp.Pt() > ptsecond) && (C_JER*recojtmp.Pt() < ptleading) && (ir != indleading))
		     {
		       //       cout << "\t\t" << C_JER*recojtmp.Pt() << " is greater than " << ptsecond << " and less than " << ptleading << endl;
		       ptsecond = C_JER*recojtmp.Pt();
		       C_JER2 = C_JER;
		       indsecond = ir;
		       //       cout << "\t\tSetting new second leading to pT = " << ptsecond << ", index = " << indsecond << endl;
		     }
		   //   cout << "\tjet size = " << jet_pt->size() << ", leading index = " << indleading << ", second leading index = " << indsecond << endl;
		 }

	       ptjet1 = ptleading;
	       etajet1 = jet_eta->at(indleading);
	       phijet1 = jet_phi->at(indleading);
	       ejet1 = jet_energy->at(indleading);

	       ptjet2 = ptsecond;
	       etajet2 = jet_eta->at(indsecond);
	       phijet2 = jet_phi->at(indsecond);
	       ejet2 = jet_energy->at(indsecond);
	       /* End JER smearing */
	     }
	   else
	     {
	       ptjet1 = jet_pt->at(0);
	       etajet1 =jet_eta->at(0);
	       phijet1 =jet_phi->at(0);
	       ejet1 =jet_energy->at(0);
	       ptjet2 =jet_pt->at(1);
	       etajet2 =jet_eta->at(1);
               phijet2 =jet_phi->at(1);
               ejet2 =jet_energy->at(1);
	       indleading = 0;
	       indsecond = 1;
	     }
	   // We don't have 2 jets - skip this event                                                                                                                                        
	   if(ptjet1 == 0 || ptjet2 == 0)
	     continue;

	   Float_t xijets1 = (1.0/13000.0)*(ptjet1*TMath::Exp(etajet1) + ptjet2*TMath::Exp(etajet2));
	   Float_t xijets2 = (1.0/13000.0)*(ptjet1*TMath::Exp(-1*etajet1) + ptjet2*TMath::Exp(-1*etajet2));

	   //	   Float_t genxijets1 = (1.0/13000.0)*(gen_jet_pt->at(0)*TMath::Exp(gen_jet_eta->at(0)) + gen_jet_pt->at(1)*TMath::Exp(gen_jet_eta->at(1)));
	   //	   Float_t genxijets2 = (1.0/13000.0)*(gen_jet_pt->at(0)*TMath::Exp(-1*gen_jet_eta->at(0)) + gen_jet_pt->at(1)*TMath::Exp(-1*gen_jet_eta->at(1)));

	   jet1.SetPtEtaPhiE(ptjet1,etajet1,phijet1,ejet1);
	   jet2.SetPtEtaPhiE(ptjet2,etajet2,phijet2,ejet2);
	   
	   mydijet = jet1+jet2;                                                                                                       

	   /* 
	    * Now start preselection cuts
	    */
	   if(jet1.Pt()>200 && jet2.Pt()>200 && fabs(jet_eta->at(indleading))<2.5 && fabs(jet_eta->at(indsecond))<2.5)
	     {
	       if((fabs(jet_eta->at(indleading) - jet_eta->at(indsecond))<1.3))
		 {
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

		       npasspresel++;

		       if(jet_corrmass->at(indleading) >= 55 && jet_corrmass->at(indleading) <= 215)
			 {
			   htau21dat1->Fill(jet_tau2->at(indleading)/jet_tau1->at(indleading),myweight);
                           hmjdat1->Fill(jet_corrmass->at(indleading),myweight);
			   rhoprime1 = TMath::Log(jet_corrmass->at(indleading)*jet_corrmass->at(indleading)/jet_pt->at(indleading));
			   tau21vrhoprime1->Fill(rhoprime1,jet_tau2->at(indleading)/jet_tau1->at(indleading));
			   taut21ddt1 = (jet_tau2->at(indleading)/jet_tau1->at(indleading)) - (-0.082 * rhoprime1);
			   htau21ddtdat1->Fill(taut21ddt1,myweight);
			 }
		       if(jet_corrmass->at(indsecond) >= 55 && jet_corrmass->at(indsecond) <= 215)
			 {
			   htau21dat2->Fill(jet_tau2->at(indsecond)/jet_tau1->at(indsecond),myweight);
			   hmjdat2->Fill(jet_corrmass->at(indsecond),myweight);
			   rhoprime2 = TMath::Log(jet_corrmass->at(indsecond)*jet_corrmass->at(indsecond)/jet_pt->at(indsecond));
			   tau21vrhoprime2->Fill(rhoprime2,jet_tau2->at(indsecond)/jet_tau1->at(indsecond));
			   taut21ddt2 = (jet_tau2->at(indsecond)/jet_tau1->at(indsecond)) - (-0.082 * rhoprime2);
                           htau21ddtdat2->Fill(taut21ddt2,myweight);
			 }
		       hptdat1->Fill(jet_pt->at(indleading),myweight);
		       hptdat2->Fill(jet_pt->at(indsecond),myweight);
		       hetadat1->Fill(jet_eta->at(indleading),myweight);
		       hetadat2->Fill(jet_eta->at(indsecond),myweight);
		       hphidat1->Fill(jet_phi->at(indleading),myweight);
		       hphidat2->Fill(jet_phi->at(indsecond),myweight);
		       xijets45->Fill(xijets1);
		       xijets56->Fill(xijets2);
		       //		       resxijets45->Fill(xijets1/genxijets1);
		       //		       resxijets56->Fill(xijets2/genxijets2);
		       //		       resxijetscorr45->Fill(xijets1,genxijets1);
		       //		       resxijetscorr56->Fill(xijets2,genxijets2);
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
			   
		       Float_t ptbalcut = 1.3;
		       Float_t acopcut = 0.01;
		       Float_t mwlowcut = 65.0;
		       Float_t mwhicut = 105.0;
		       Float_t tau21cut = 0.75;

		       // Proton part
		       float mpp = 0;
		       float ypp = 0;

		       float mppmm = 0;
		       float yppmm = 0;

		       int ismultimulti = 0;
		       int nSinglePixelTracks45 = 0;
		       int nSinglePixelTracks56 = 0;
		       int nMultiTracks45 = 0;
		       int nMultiTracks56 = 0;
		       int nMultiRP = 0;
		       float xigen45 = 0;
		       float xigen56 = 0;
		       float mppgen = 0;

		       // Multiple candidate selection for 2018. Record and select the highest xi protons                                                                                           
		       float ximaxmulti45 = -999;
		       float ximaxmulti56 = -999;
		       int indexmaxmulti45 = -1;
		       int indexmaxmulti56 = -1;

		       if(proton_xi->size() > 1)
			 {
			   float thexi = 0;
			   float thethetasty = 0;
			   float thet = 0;
			   float thetime = -999;
			   float thetax1 = 0;
			   float thetay1 = 0;
			   float thetax2 = 0;
			   float thetay2 = 0;
			   int rpid1 = 0;
			   int rpid2 = 0;
			   int thex1 = 0;
			   int thex2 = 0;
			   int they1 = 0;
			   int they2 = 0;
			   int theshift1 = -1;
			   int theshift2 = -1;
			   int thearm = -1;
			   
			   /*
			    * First loop over all protons to get good multi-RP candidates and apply eff. corrections to MC
			    */
			   for(int p = 0; p < proton_xi->size(); p++)                                                           
			     {
			       if(proton_ismultirp->at(p) == 1)
				 {
				   thexi = proton_xi->at(p);
				   thethetasty = proton_thy->at(p);
				   thet = -1.0 * proton_t->at(p);
				   thetime = proton_time->at(p);
				   rpid1 = proton_rpid1->at(p);
				   rpid2 = proton_rpid2->at(nMultiRP);
				   thex1 = proton_trackx1->at(p);
				   thex2 = proton_trackx2->at(nMultiRP);
				   they1 = proton_tracky1->at(p);
				   they2 = proton_tracky2->at(nMultiRP);
				   theshift1 = proton_trackpixshift1->at(p);
				   theshift2 = proton_trackpixshift2->at(nMultiRP);
				   thearm = proton_arm->at(p);
				   nMultiRP++;
				   
				   // Apply all good proton cuts
				   bool passesselector = false;
				   bool passesprotonefficiency = true;
				   if(samplenumber < 0)
				     {
				       passesselector = TightMultiRPProton(thex1, they1, thex2, they2,
									   thetax1, thetay1, thetax2, thetay2,
									   thearm, rpid1, rpid2, 
									   crossingangle, erastring, thexi, 						      
									   theshift1, theshift2);
				     }

				   if(samplenumber > 0)
				     {
                                       passesselector = TightMultiRPProton(thex1, they1, thex2, they2,
                                                                           thetax1, thetay1, thetax2, thetay2,
                                                                           thearm, rpid1, rpid2,
                                                                           130, erastring, thexi,
                                                                           theshift1, theshift2);
				       
				       passesprotonefficiency = eff.GetMultiRPAcceptRejectDecision(thex1, they1, thex2, they2, rpid1, rpid2, erastring);

				       //				       if(samplenumber > 200)
				       if(samplenumber > 200)
					 {
					   //					   passesprotonefficiency = true; // JH testing effect of efficiencies
					   passesprotonefficiency = true; // JH - for 2018 set eff = 100% until final values available
					 }
				     }

				   if((passesselector == true) && (passesprotonefficiency == true) && (thexi >= 0.05))
				     {
				       if(thearm==0)
					 {
					   if(thexi > ximaxmulti45)
					     {
					       ximaxmulti45 = thexi;
					       indexmaxmulti45 = nMultiTracks45;
					     }					       

					   ximulti45s->push_back(thexi);
					   thystmulti45s->push_back(thethetasty);
					   tmulti45s->push_back(thet);
					   timemulti45s->push_back(thetime);

					   nMultiTracks45++;
					 }
				       if(thearm==1)
					 {
                                           if(thexi > ximaxmulti56)
                                             {
                                               ximaxmulti56 = thexi;
                                               indexmaxmulti56 = nMultiTracks56;
                                             }

					   ximulti56s->push_back(thexi);
                                           thystmulti56s->push_back(thethetasty);
                                           tmulti56s->push_back(thet);
					   timemulti56s->push_back(thetime);

					   nMultiTracks56++;
					 }
				     }
				 }
			     }
			   
			   /*
			    * Now select 2-arm events. Exclude events with >3 tracks/arm in 2018, to reduce showers. 
			    */
			   if(nMultiTracks45 > 0 && nMultiTracks56 > 0 && nMultiTracks45 < 4 && nMultiTracks56 < 4)
			     {
			       // single-arm distributions
			       hximult45->Fill(ximulti45s->at(indexmaxmulti45));
			       hthystmult45->Fill(thystmulti45s->at(indexmaxmulti45));
			       htmult45->Fill(tmulti45s->at(indexmaxmulti45));

			       hximult56->Fill(ximulti56s->at(indexmaxmulti56));
                               hthystmult56->Fill(thystmulti56s->at(indexmaxmulti56));
                               htmult56->Fill(tmulti56s->at(indexmaxmulti56));

			       // 2-arm combinations: mass, rapidity, and timing
			       mpp = TMath::Sqrt(13000.0*13000.0*ximulti56s->at(indexmaxmulti56)*ximulti45s->at(indexmaxmulti45));
			       ypp = -0.5*TMath::Log(ximulti56s->at(indexmaxmulti56)/ximulti45s->at(indexmaxmulti45));

			       mppmm = mpp;
			       yppmm = ypp;
			       mppsmultmult->push_back(mpp);
			       yppsmultmult->push_back(ypp);
			       hmppmulti->Fill(mpp);
			       hyppmulti->Fill(ypp);
			       hmyppmulti->Fill(mpp,ypp);
			       hmasscorrpreseldatmult->Fill(mpp,mydijet.M());
			       hycorrpreseldatmult->Fill(ypp,mydijet.Rapidity());
			       dymassratiocorrpreseldatmult->Fill(1-mydijet.M()/mpp,mydijet.Rapidity()-ypp);
			       hdtmulti->Fill(timemulti45s->at(indexmaxmulti45) - timemulti56s->at(indexmaxmulti56));
			       ismultimulti = 1;
			       npassppsbeforecuts++;
			     }

			   // Old - all combinations
			   /*
			   for(int a = 0; a < nMultiTracks45; a++)                                                                                                                    
			     {                                                                                                                                                            
			       for(int b = 0; b < nMultiTracks56; b++)                                                                                                                    
				 {                                                                                                                                                        
				   mpp = TMath::Sqrt(13000.0*13000.0*ximulti56s->at(b)*ximulti45s->at(a));                                                                                
				   ypp = -0.5*TMath::Log(ximulti56s->at(b)/ximulti45s->at(a));                                                                                            
    
				   mppmm = mpp;
				   yppmm = ypp;
				   mppsmultmult->push_back(mpp);                                                                                                                          
				   yppsmultmult->push_back(ypp);                                                                                                                          
				   hmppmulti->Fill(mpp);                                                                                                                                  
				   hyppmulti->Fill(ypp);                                                                                                                     
				   hmyppmulti->Fill(mpp,ypp);
				   hmasscorrpreseldatmult->Fill(mpp,mydijet.M());
				   hycorrpreseldatmult->Fill(ypp,mydijet.Rapidity());
				   dymassratiocorrpreseldatmult->Fill(1-mydijet.M()/mpp,mydijet.Rapidity()-ypp);
				   hdtmulti->Fill(timemulti45s->at(a) - timemulti56s->at(b));
				   ismultimulti = 1;                                                                                                                                      
 				 } 
			     }
			   */     
			 }

		       hnmult45->Fill(nMultiTracks45);
		       hnmult56->Fill(nMultiTracks56);

                       // Signal region, only for MC
                       if(samplenumber > 0)
                         {
			   // Output txt files for mixing. Apply xi_jets, pruned mass, and pT balance cuts
			   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205 && 
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (jet1.Pt()/jet2.Pt() < ptbalcut))
			     {			   
			       ofs << samplenumber << " "
				   << mc_pu_trueinteractions_ << " " << pileupWeight << " "
				   << mydijet.M() << " " << mydijet.Rapidity() << " "
				   << acop << " " << (jet1.Pt()/jet2.Pt()) << " "
				   << jet_corrmass->at(indleading) << " " << jet_corrmass->at(indsecond) << " "
				   << taut21ddt1 << " " << taut21ddt2 << " "
				   << xijets1 << " " << xijets2 << " "
				   << run << " " << lumiblock << " " << event << " " 
				   << ximaxmulti45 << " " << ximaxmulti56 << std::endl;
			     }
                           if((acop < acopcut) && (jet1.Pt()/jet2.Pt() < ptbalcut))
			     {
			       npassdijetkine++;
			       if((jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
				 {
				   npassjetsubstr++;

				   // Just counting
				   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
				     npassjetxi++;

				   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
				     {
				       hmasswwsignal->Fill(mydijet.M());
				       hywwsignal->Fill(mydijet.Rapidity());

				       if(mpp>0) // MC events with protons - e.g. signal MC
					 {
					   for(Int_t s = 0; s < mppsmultmult->size(); s++)
					     {
					       hmassmatchsigmcmm->Fill(mppsmultmult->at(s)-mydijet.M());
					       hymatchsigmcmm->Fill(yppsmultmult->at(s)-mydijet.Rapidity());
					       hmassmatchratiosigmcmm->Fill(1 - (mydijet.M()/mppsmultmult->at(s)));
					     }
					   
					   int match45 = 0; int match56 = 0;
					   // GEN-level proton quantities for signal MC
					   for(Int_t gp = 0; gp < gen_proton_xi->size(); gp++)
					     {
					       if(fabs(ximaxmulti45 - gen_proton_xi->at(gp)) < 0.01 && gen_proton_pz->at(gp) > 0)
						 match45 = 1;
					       if(fabs(ximaxmulti56 - gen_proton_xi->at(gp)) < 0.01 && gen_proton_pz->at(gp) < 0)
						 match56 = 1;
					       if(gen_proton_pz->at(gp) > 0)
						 xigen45 = gen_proton_xi->at(gp);
					       if(gen_proton_pz->at(gp) < 0)
						 xigen56 = gen_proton_xi->at(gp);
					     }
					   
					   
					   npasspps++;
					   hmassmatchratiosigmcmult->Fill(1 - (mydijet.M()/mppsmultmult->at(0)));
					   hymatchsigmcmult->Fill(yppsmultmult->at(0)-mydijet.Rapidity());
					   hmasscorrsigmcmult->Fill(mydijet.M(),mppsmultmult->at(0));
					   hycorrsigmcmult->Fill(mydijet.Rapidity(),yppsmultmult->at(0));
					   if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= 0.11506000) && 
					      (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= 0.057220000))
					     npassppsmatchksenia++;
					   if(match45 == 1 && match56 == 1)
					     hmasscorrsigmcmulttruthmatched->Fill(mydijet.M(),mppsmultmult->at(0));
					 }
				     }
				 }
			     }
			 }
		       
		       // Control regions in data and background MC
		       if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
			 {
			   // Anti acoplanarity                                                                                                                                          
			   if((acop > acopcut) &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			      (jet1.Pt()/jet2.Pt() < ptbalcut))
			     {
			       hmasswwantiacop->Fill(mydijet.M());
			       hmj1antiacop->Fill(jet_corrmass->at(indleading));
			       hmj2antiacop->Fill(jet_corrmass->at(indsecond));
			       htau211antiacop->Fill(taut21ddt1);
			       htau212antiacop->Fill(taut21ddt2);

			       if(mpp>0)
				 {
				   hmassmatchantiacopmm->Fill(mppmm-mydijet.M());
				   hymatchantiacopmm->Fill(yppmm-mydijet.Rapidity());
				   hmassmatchratioantiacopmm->Fill(1 - (mydijet.M()/mppmm));
				   hmassrapiditymatchantiacopmm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			     } // anti-acoplanarity
			   // Anti pT balance                                                                                                                     
			   if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			      (acop < acopcut))
			     {
			       hmasswwantiptbal->Fill(mydijet.M());

			       if(mpp>0)
				 {
				   hmassmatchantiptbalmm->Fill(mppmm-mydijet.M());
                                   hymatchantiptbalmm->Fill(yppmm-mydijet.Rapidity());
                                   hmassmatchratioantiptbalmm->Fill(1 - (mydijet.M()/mppmm));
                                   hmassrapiditymatchantiptbalmm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			     } // anti-pT balance
			   // Anti tau21                                                                                                                          
			   if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (acop < acopcut) &&
			      (jet1.Pt()/jet2.Pt()) <  ptbalcut)
			     {
			       hmasswwantitau->Fill(mydijet.M());
                               hmj1antitau->Fill(jet_corrmass->at(indleading));
                               hmj2antitau->Fill(jet_corrmass->at(indsecond));
                               htau211antitau->Fill(taut21ddt1);
                               htau212antitau->Fill(taut21ddt2);

			       if(mpp>0)
				 {
				   hmassmatchantitaumm->Fill(mppmm-mydijet.M());
				   hymatchantitaumm->Fill(yppmm-mydijet.Rapidity());
				   hmassmatchratioantitaumm->Fill(1 - (mydijet.M()/mppmm));
				   hmassrapiditymatchantitaumm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			     } // anti-tau21
			   // All cuts, but with signal region in matching blinded
			   if((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (acop < acopcut) &&
			      (jet1.Pt()/jet2.Pt()) <  ptbalcut)
			     {
			       if(mpp>0)
				 {
				   Float_t massmatch = 0.0;
				   Float_t ymatch = 0.0;
				   massmatch = 1 - (mydijet.M()/mppmm);
				   ymatch = yppmm-mydijet.Rapidity();
				   if(fabs(ymatch) > 0.5 || fabs(massmatch) > 1.0)
				     {
				       hmassrapiditymatchvetoorsignalregion->Fill(massmatch,ymatch);
				       if(fabs(massmatch) > 1.0 && fabs(massmatch) > 1.0)
					 {
					   hmassrapiditymatchvetosignalregion->Fill(massmatch,ymatch);
					 }
				     }
				 }
			     } // blinded signal region
			 } // xi(jets)
		     } // Dijet mass
		 } // Delta-eta
	     } // Single jet pT & eta
	 }
       
       mppsmultmult->clear();
       yppsmultmult->clear();
       xipix45s->clear();
       xipix56s->clear();
       ypix45s->clear();
       ypix56s->clear();
       ximulti45s->clear();
       ximulti56s->clear();
       thystmulti45s->clear();
       thystmulti56s->clear();
       tmulti45s->clear();
       tmulti56s->clear();
       timemulti45s->clear();
       timemulti56s->clear();
     }

   delete mppsmultmult;
   delete yppsmultmult;
   delete xipix45s;
   delete xipix56s;
   delete ypix45s;
   delete ypix56s;
   delete ximulti45s;
   delete ximulti56s;
   delete thystmulti45s;
   delete thystmulti56s;
   delete tmulti45s;
   delete tmulti56s;
   delete timemulti45s;
   delete timemulti56s;

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
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017B.root","RECREATE");
   if(samplenumber == -2)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017C.root","RECREATE");
   if(samplenumber == -3)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017D.root","RECREATE");
   if(samplenumber == -4)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017E.root","RECREATE");
   if(samplenumber == -5)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2017F.root","RECREATE");

   if(samplenumber == -6)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016B.root","RECREATE");
   if(samplenumber == -7)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016C.root","RECREATE");
   if(samplenumber == -8)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016G.root","RECREATE");
   if(samplenumber == -9)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2016H.root","RECREATE");

   if(samplenumber == -10)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018A.root","RECREATE");
   if(samplenumber == -11)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018B.root","RECREATE");
   if(samplenumber == -12)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018C.root","RECREATE");
   if(samplenumber == -13)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_datahist2018D.root","RECREATE");

   if(samplenumber == 1)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt170to300.root","RECREATE");
   if(samplenumber == 2)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt300to470.root","RECREATE");
   if(samplenumber == 3)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt470to600.root","RECREATE");
   if(samplenumber == 4)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt600to800.root","RECREATE");                                                           
   if(samplenumber == 5)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt800to1000.root","RECREATE");
   if(samplenumber == 6)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1000to1400.root","RECREATE");
   if(samplenumber == 7)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_ttbarhadronic.root","RECREATE");
   if(samplenumber == 8)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_wjetshadronic.root","RECREATE");
   if(samplenumber == 9)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_zjetshadronic.root","RECREATE");
   if(samplenumber == 10)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1400to1800.root","RECREATE");
   if(samplenumber == 11)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1800to2400.root","RECREATE");
   if(samplenumber == 12)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt2400to3200.root","RECREATE");


   if(samplenumber == 20)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_2017preTS2.root","RECREATE");
   if(samplenumber == 23)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2017preTS2.root","RECREATE");


   if(samplenumber == 40)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_2017postTS2.root","RECREATE");
   if(samplenumber == 43)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2017postTS2.root","RECREATE");

   // 2016
   if(samplenumber == 101)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt170to300_2016.root","RECREATE");
   if(samplenumber == 102)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt300to470_2016.root","RECREATE");
   if(samplenumber == 103)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt470to600_2016.root","RECREATE");
   if(samplenumber == 104)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt600to800_2016.root","RECREATE");
   if(samplenumber == 105)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt800to1000_2016.root","RECREATE");
   if(samplenumber == 106)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1000to1400_2016.root","RECREATE");
   if(samplenumber == 107)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_ttbarhadronic1000inf_2016.root","RECREATE");
   if(samplenumber == 108)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_wjetshadronic_2016.root","RECREATE");
   if(samplenumber == 109)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_zjetshadronic_2016.root","RECREATE");
   if(samplenumber == 110)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1400to1800_2016.root","RECREATE");
   if(samplenumber == 111)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_ttbarhadronic700ot1000_2016.root","RECREATE");

   if(samplenumber == 120)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_2016preTS2.root","RECREATE");
   if(samplenumber == 123)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2016preTS2.root","RECREATE");

   // 2018
   if(samplenumber == 201)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt170to300_2018.root","RECREATE");
   if(samplenumber == 202)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt300to470_2018.root","RECREATE");
   if(samplenumber == 203)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt470to600_2018.root","RECREATE");
   if(samplenumber == 204)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt600to800_2018.root","RECREATE");
   if(samplenumber == 205)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt800to1000_2018.root","RECREATE");
   if(samplenumber == 206)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1000to1400_2018.root","RECREATE");
   if(samplenumber == 207)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_ttbarhadronic_2018.root","RECREATE");
   if(samplenumber == 208)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_wjetshadronic_2018.root","RECREATE");
   if(samplenumber == 209)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_zjetshadronic_2018.root","RECREATE");
   if(samplenumber == 210)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_qcdpt1400to1800_2018.root","RECREATE");

   if(samplenumber == 220)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_2018.root","RECREATE");
   if(samplenumber == 223)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2018.root","RECREATE");

   ofs.close();

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
   tau21vrhoprime1->Write();
   tau21vrhoprime2->Write();
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
   hthystmult45->Write();
   hthystmult56->Write();
   htmult45->Write();
   htmult56->Write();
   hnmult45->Write();
   hnmult56->Write();

   hmppmulti->Write();
   hyppmulti->Write();
   hdtmulti->Write(); 

   hmassmatchantiw->Write();
   hymatchantiw->Write();
   hmassmatchratioantiw->Write();

   hmassmatchantitaumm->Write();
   hymatchantitaumm->Write();
   hmassmatchratioantitaumm->Write();
   hmassmatchantiacopmm->Write();
   hymatchantiacopmm->Write();
   hmassmatchratioantiacopmm->Write();
   hmassmatchantiptbalmm->Write();
   hymatchantiptbalmm->Write();
   hmassmatchratioantiptbalmm->Write();

   hmassmatchsigmcmm->Write();
   hymatchsigmcmm->Write();
   hmassmatchratiosigmcmm->Write();

   hmassmatchratiosigmcmult->Write();
   hymatchsigmcmult->Write();
   hmasscorrsigmcmult->Write();
   hycorrsigmcmult->Write();
   hmasscorrsigmcmulttruthmatched->Write();

   //   hmppres->Write();

   hmasswwantitau->Write();
   hmasswwantiacop->Write();
   hmasswwantiptbal->Write();
   hmj1antiacop->Write();
   hmj2antiacop->Write();
   htau211antiacop->Write();
   htau212antiacop->Write();
   hmj1antitau->Write();
   hmj2antitau->Write();
   htau211antitau->Write();
   htau212antitau->Write();


   hmasswwsignal->Write();
   hywwsignal->Write();

   hmyppsingle->Write();
   hmyppmulti->Write();
   hmyjjdat->Write();
   xijets45->Write();
   xijets56->Write();
   resxijets45->Write();
   resxijets56->Write();
   resxijetscorr45->Write();
   resxijetscorr56->Write();

   hmasscorrpreseldatmult->Write();
   hycorrpreseldatmult->Write();
   dymassratiocorrpreseldatmult->Write();

   hmassrapiditymatchantiacopmm->Write();
   hmassrapiditymatchantiptbalmm->Write();
   hmassrapiditymatchantitaumm->Write();
   hmassrapiditymatchvetosignalregion->Write();
   hmassrapiditymatchvetoorsignalregion->Write();

   fx->Close();

   Float_t normxsec = 0.0; 
   Float_t nevgen = 99999999.;
   if(samplenumber == 21)
     {normxsec = 45.4; nevgen = 91300.0;}
   if(samplenumber == 22)
     {normxsec = 58.3; nevgen = 124400.0;}
   if(samplenumber == 24)
     {normxsec = 58.3; nevgen = 110100.0;}
   if(samplenumber == 25)
     {normxsec = 148.13; nevgen = 243900.0;}
   if(samplenumber == 27)
     {normxsec = 164.8; nevgen = 107700.0;}
   if(samplenumber == 31)
     {normxsec = 2.64; nevgen = 10000.0;}

   std::cout << "Ran over " << nentries << " events " << std::endl;
   std::cout << "Passing preselection = " << npasspresel << std::endl
	     << "Passing dijet kinematics = " << npassdijetkine << std::endl
	     << "Passing jet substructure = " << npassjetsubstr << std::endl
	     << "Passing xi(jets) = " << npassjetxi << std::endl
	     << "Passing 2 PPS multi-RP protons = " << npasspps << std::endl
	     << "\t(After preselection and before other central cuts = " << npassppsbeforecuts << std::endl
	     << "Passing pp-WW matching = " << npassppsmatchksenia << std::endl;

}
