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
   if((samplenumber > 1 && samplenumber < 20) || (samplenumber > 100 && samplenumber < 120))
     nentries = 1000000;
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

   TH1F *hnpix45 = new TH1F("hnpix45","hnpix45",15,0,15);
   TH1F *hnpix56 = new TH1F("hnpix56","hnpix56",15,0,15);


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

   TH1F *hmassmatchantiacopmix = new TH1F("hmassmatchantiacopmix","hmassmatchantiacopmix",500,-2500,2500);
   TH1F *hymatchantiacopmix = new TH1F("hymatchantiacopmix","hymatchantiacopmix",100,-5,5);
   TH1F *hmassmatchratioantiacopmix = new TH1F("hmassmatchratioantiacopmix","hmassmatchratioantiacopmix",100,-5,5);
   TH1F *hmassmatchantitaumix = new TH1F("hmassmatchantitaumix","hmassmatchantitaumix",500,-2500,2500);
   TH1F *hymatchantitaumix = new TH1F("hymatchantitaumix","hymatchantitaumix",100,-5,5);
   TH1F *hmassmatchratioantitaumix = new TH1F("hmassmatchratioantitaumix","hmassmatchratioantitaumix",100,-5,5);
   TH1F *hmassmatchantiptbalmix = new TH1F("hmassmatchantiptbalmix","hmassmatchantiptbalmix",500,-2500,2500);
   TH1F *hymatchantiptbalmix = new TH1F("hymatchantiptbalmix","hymatchantiptbalmix",100,-5,5);
   TH1F *hmassmatchratioantiptbalmix = new TH1F("hmassmatchratioantiptbalmix","hmassmatchratioantiptbalmix",100,-5,5);

   TH1F *hmassmatchantiacopss = new TH1F("hmassmatchantiacopss","hmassmatchantiacopss",500,-2500,2500);
   TH1F *hymatchantiacopss = new TH1F("hymatchantiacopss","hymatchantiacopss",100,-5,5);
   TH1F *hmassmatchratioantiacopss = new TH1F("hmassmatchratioantiacopss","hmassmatchratioantiacopss",100,-5,5);
   TH1F *hmassmatchantitauss = new TH1F("hmassmatchantitauss","hmassmatchantitauss",500,-2500,2500);
   TH1F *hymatchantitauss = new TH1F("hymatchantitauss","hymatchantitauss",100,-5,5);
   TH1F *hmassmatchratioantitauss = new TH1F("hmassmatchratioantitauss","hmassmatchratioantitauss",100,-5,5);
   TH1F *hmassmatchantiptbalss = new TH1F("hmassmatchantiptbalss","hmassmatchantiptbalss",500,-2500,2500);
   TH1F *hymatchantiptbalss = new TH1F("hymatchantiptbalss","hymatchantiptbalss",100,-5,5);
   TH1F *hmassmatchratioantiptbalss = new TH1F("hmassmatchratioantiptbalss","hmassmatchratioantiptbalss",100,-5,5);


   TH1F *hmassmatchsigmcmm = new TH1F("hmassmatchsigmcmm","hmassmatchsigmcmm",500,-2500,2500);
   TH1F *hymatchsigmcmm = new TH1F("hymatchsigmcmm","hymatchsigmcmm",500,-5,5);
   TH1F *hmassmatchratiosigmcmm = new TH1F("hmassmatchratiosigmcmm","hmassmatchratiosigmcmm",500,-5,5);
   TH1F *hmassmatchsigmcmix = new TH1F("hmassmatchsigmcmix","hmassmatchsigmcmix",500,-2500,2500);
   TH1F *hymatchsigmcmix = new TH1F("hymatchsigmcmix","hymatchsigmcmix",100,-5,5);
   TH1F *hmassmatchratiosigmcmix = new TH1F("hmassmatchratiosigmcmix","hmassmatchratiosigmcmix",500,-5,5);
   TH1F *hmassmatchsigmcss = new TH1F("hmassmatchsigmcss","hmassmatchsigmcss",500,-2500,2500);
   TH1F *hymatchsigmcss = new TH1F("hymatchsigmcss","hymatchsigmcss",100,-5,5);
   TH1F *hmassmatchratiosigmcss = new TH1F("hmassmatchratiosigmcss","hmassmatchratiosigmcss",500,-5,5);

   TH2F *hmassrapiditymatchvetosignalregion = new TH2F("hmassrapiditymatchvetosignalregion","hmassrapiditymatchvetosignalregion",500,-5,5,500,-5,5);
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

   TH1F *hmasswwantitau = new TH1F("hmasswwantitau","hmasswwantitau",250,0,5000);
   TH1F *hmasswwantiacop = new TH1F("hmasswwantiacop","hmasswwantiacop",250,0,5000);
   TH1F *hmasswwantiptbal = new TH1F("hmasswwantiptbal","hmasswwantiptbal",250,0,5000);
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

   // Counters for # of MC events passing cuts
   Int_t npasspresel = 0;
   Int_t npassdijetkine = 0;
   Int_t npassjetsubstr = 0;
   Int_t npassjetxi = 0;
   Int_t npasspps = 0;
   Int_t npassppsmatchksenia = 0;

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

		       float mppss = 0;
		       float yppss = 0;
		       float mppmm = 0;
		       float yppmm = 0;
		       float mppmix = 0;
		       float yppmix = 0;

		       float multisubtrackx21045 = 0.0;
		       float multisubtrackx22045 = 0.0;
		       float multisubtrackx21056 = 0.0;
		       float multisubtrackx22056 = 0.0;
		       float multisubtracky21045 = 0.0;
		       float multisubtracky22045 = 0.0;
                       float multisubtracky21056 = 0.0;
		       float multisubtracky22056 = 0.0;
		       int multisubtrackshift45 = 0;
		       int multisubtrackshift56 = 0;
		       
		       int ismultimulti = 0;
		       int issinglesingle = 0;
		       int ismixed = 0;
		       int nSinglePixelTracks45 = 0;
		       int nSinglePixelTracks56 = 0;
		       int nMultiTracks45 = 0;
		       int nMultiTracks56 = 0;
		       float ximulti45 = 0;
		       float ximulti56 = 0;
		       float xigen45 = 0;
		       float xigen56 = 0;
		       float mppgen = 0;

                       // Include aperture cutoffs for data                                                                                                                       
		       float aperture45 = 999.0; 
		       float aperture56 = 999.0;
		       if(samplenumber < 0 && samplenumber > -4)
			 {
			   aperture45 = Aperture(crossingangle,0,"2017preTS2");
			   aperture56 = Aperture(crossingangle,1,"2017preTS2");
			 }
		       if(samplenumber < -3 && samplenumber > -6)
			 {
			   aperture45 = Aperture(crossingangle,0,"2017postTS2");
                           aperture56 = Aperture(crossingangle,1,"2017postTS2");
			 }
		       if(samplenumber < -5 && samplenumber > -9)
			 {
			   aperture45 = Aperture(crossingangle,0,"2016preTS2");
                           aperture56 = Aperture(crossingangle,1,"2016preTS2");
			 }
		       if(samplenumber == -9)
			 {
			   aperture45 = Aperture(crossingangle,0,"2016postTS2");
                           aperture56 = Aperture(crossingangle,1,"2016postTS2");
			 }
		       if(samplenumber < -9)
			 {
                           aperture45 = Aperture(crossingangle,0,"2018");
                           aperture56 = Aperture(crossingangle,1,"2018");
			 }
		       // Include aperture cutoffs for signal MC - for now using a hard-coded crossing angle, 
		       // until figuring out how to retrieve this for MC
		       if(samplenumber == 21 || samplenumber == 22 || samplenumber == 31)
			 {
			   aperture45 = Aperture(130,0,"2017preTS2");
			   aperture56 = Aperture(130,1,"2017preTS2");
			 }
		       if(samplenumber == 41)
			 {
			   aperture45 = Aperture(130,0,"2017postTS2");
                           aperture56 = Aperture(130,1,"2017postTS2");
			 }

		       if(proton_xi->size() > 1)
			 {
			   float thexi = 0;

			   for(int p = 0; p < proton_xi->size(); p++)                                                                                                 
			     {
			       thexi = proton_xi->at(p);
			       bool passfiducialcuts = false;
			       bool passpixraddam = true;
			       bool passmultirpfull = true;

			       if((proton_ismultirp->at(p) == 0) && (proton_rpid->at(p) == 23))                                                                       
				 {
				   passfiducialcuts = PixelFiducial(proton_trackx1->at(p), proton_tracky1->at(p), 0, samplenumber);
				   passpixraddam = SingleRPEffCorr(proton_trackx1->at(p), proton_tracky1->at(p), 0, samplenumber);

				   if((proton_trackpixshift1->at(p) == 0) && (thexi <= aperture45) && (passfiducialcuts == true) && (passpixraddam == true))
				     {
				       xipix45s->push_back(thexi);
				       hxipix45->Fill(thexi);
				       //				       ypix45s->push_back(proton_tracky1->at(p));
				       nSinglePixelTracks45++;
				     }

				   // Due to stupidity, the pixel ROC shift info is not saved correctly for the pixel 
				   // sub-tracks of a multi-RP proton. So here we use the info of the single-RP proton 
				   // and associate it to the x,y of the multi-RP pixel track
				   if(proton_trackpixshift1->at(p) == 1)
				     {
				       if(proton_rpid2->size() > 0)
					 if((proton_rpid2->at(0) == 23) && (proton_trackx2->at(0) == proton_trackx1->at(p)) && (proton_tracky2->at(0) == proton_tracky1->at(p)))
					   multisubtrackshift45 = 1;					   
                                       if(proton_rpid2->size() > 1)
                                         if((proton_rpid2->at(1) == 23) && (proton_trackx2->at(1) == proton_trackx1->at(p)) && (proton_tracky2->at(1) == proton_tracky1->at(p)))
					   multisubtrackshift45 = 1;
				     }
				 }
                               if((proton_ismultirp->at(p) == 0) && (proton_rpid->at(p) == 123))
                                 {
				   passfiducialcuts = PixelFiducial(proton_trackx1->at(p), proton_tracky1->at(p), 1, samplenumber);
				   passpixraddam = SingleRPEffCorr(proton_trackx1->at(p), proton_tracky1->at(p), 1, samplenumber);

				   if((proton_trackpixshift1->at(p) == 0) && (thexi <= aperture56) && (passfiducialcuts == true) && (passpixraddam == true))
				     {
				       xipix56s->push_back(thexi);
                                       hxipix56->Fill(thexi);
				       //				       ypix56s->push_back(proton_tracky1->at(p));
                                       nSinglePixelTracks56++;
				     }

                                   // Due to stupidity, the pixel ROC shift info is not saved correctly for the pixel                                                             
                                   // sub-tracks of a multi-RP proton. So here we use the info of the single-RP proton                                                            
                                   // and associate it to the x,y of the multi-RP pixel track                                                                                     
                                   if(proton_trackpixshift1->at(p) == 1)
                                     {
                                       if(proton_rpid2->size() > 0)
                                         if((proton_rpid2->at(0) == 123) && (proton_trackx2->at(0) == proton_trackx1->at(p)) && (proton_tracky2->at(0) == proton_tracky1->at(p)))
					   multisubtrackshift56 = 1;
                                       if(proton_rpid2->size() > 1)
                                         if((proton_rpid2->at(1) == 123) && (proton_trackx2->at(1) == proton_trackx1->at(p)) && (proton_tracky2->at(1) == proton_tracky1->at(p)))
                                           multisubtrackshift56 = 1;
                                     }
                                 }
                               if((proton_ismultirp->at(p) == 1) && (proton_arm->at(p) == 0))
                                 {
				   // Fix for mis-alignment of storing multi-RP sub-tracks in the ntuples
				   // Here for 2017 - track1 is always(?) strips, find pixels track2
				   multisubtrackx21045 = proton_trackx1->at(p);
				   multisubtracky21045 = proton_tracky1->at(p);
				   if(proton_rpid2->at(0) == 23) 
				     {
				       multisubtrackx22045 = proton_trackx2->at(0); 
				       multisubtracky22045 = proton_tracky2->at(0);
				     }
				   else if(proton_rpid2->size() > 1)
				     {
				       if(proton_rpid2->at(1) == 23) 
					 {
					   multisubtrackx22045 = proton_trackx2->at(1); 
					   multisubtracky22045 = proton_tracky2->at(1);
					 }
				     }
				   //				   else std::cout << "ERROR - could not find 220 sub-track of multi-RP candidate" << std::endl;

				   passfiducialcuts = PixelFiducial(multisubtrackx21045, multisubtracky21045, 0, samplenumber);
				   passmultirpfull = MultiRPEffCorr(multisubtrackx21045, multisubtracky21045, multisubtrackx22045, multisubtracky22045, 0, samplenumber);

				   if((multisubtrackshift45 == 0) && (thexi <= aperture45) && (passfiducialcuts == true) && (passmultirpfull == true))
				     {
				       ximulti45s->push_back(thexi);
				       hximult45->Fill(thexi);
				       ximulti45 = thexi;
				       nMultiTracks45++;
				     }
                                 }
                               if((proton_ismultirp->at(p) == 1) && (proton_arm->at(p) == 1))
                                 {
                                   // Fix for mis-alignment of storing multi-RP sub-tracks in the ntuples                                                                         
                                   // Here for 2017 - track1 is always(?) strips, find pixels track2                                                                              
                                   multisubtrackx21056 = proton_trackx1->at(p);
                                   multisubtracky21056 = proton_tracky1->at(p);
                                   if(proton_rpid2->at(0) == 123)
                                     {
                                       multisubtrackx22056 = proton_trackx2->at(0);
                                       multisubtracky22056 = proton_tracky2->at(0);
                                     }
                                   else if(proton_rpid2->size() > 1)
                                     {
                                       if(proton_rpid2->at(1) == 123)
                                         {
                                           multisubtrackx22056 = proton_trackx2->at(1);
                                           multisubtracky22056 = proton_tracky2->at(1);
                                         }
                                     }
				   //                                   else std::cout << "ERROR - could not find 220 sub-track of multi-RP candidate" << std::endl;

				   passfiducialcuts = PixelFiducial(multisubtrackx22056, multisubtracky22056, 1, samplenumber);
                                   passmultirpfull = MultiRPEffCorr(multisubtrackx21056, multisubtracky21056, multisubtrackx22056, multisubtracky22056, 1, samplenumber);

				   if((multisubtrackshift56 == 0) && (thexi <= aperture56) && (passfiducialcuts == true) && (passmultirpfull == true))
				     {
				       ximulti56s->push_back(thexi);
				       hximult56->Fill(thexi);
				       ximulti56 = thexi;
				       nMultiTracks56++;
				     }
                                 }
			     }

			   // Multi-multi
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
				   ismultimulti = 1;                                                                                                                                         
				 }                                                                                                                                                           
			     }                                                                                                                                                               
			   // Mixed
			   for(int a = 0; a < nSinglePixelTracks45; a++)                                                                                                                     
			     {                                                                                                                                                               
			       for(int b = 0; b < nMultiTracks56; b++)                                                                                                                       
				 {                                                                                                                                                           
				   mpp = TMath::Sqrt(13000.0*13000.0*ximulti56s->at(b)*xipix45s->at(a));                                                                                     
				   ypp = -0.5*TMath::Log(ximulti56s->at(b)/xipix45s->at(a));                                                                                                  
				   mppmix = mpp;
				   yppmix = ypp;
				   mppsmixed->push_back(mpp);                                                                                                                                
				   yppsmixed->push_back(ypp);                                                                                                                                
				   hmppmixed->Fill(mpp);                                                                                                                                     
				   hyppmixed->Fill(ypp);                                                                                                                                     
				   ismixed = 1;
				 }                                                                                                                                                           
 			     }                                                                                                                                                               
 			   for(int a = 0; a < nSinglePixelTracks56; a++)                                                                                                                     
 			     {                                                                                                                                                               
			       for(int b = 0; b < nMultiTracks45; b++)                                                                                                                       
				 {                                                                                                                                                           
				   mpp = TMath::Sqrt(13000.0*13000.0*xipix56s->at(a)*ximulti45s->at(b));                                                                                     
				   ypp = -0.5*TMath::Log(xipix56s->at(a)/ximulti45s->at(b));                                                                                                  
                                   mppmix = mpp;
                                   yppmix = ypp;
				   mppsmixed->push_back(mpp);                                                                                                                                
				   yppsmixed->push_back(ypp);                                                                                                                                
				   hmppmixed->Fill(mpp);                                                                                                                                     
				   hyppmixed->Fill(ypp);                                                                                                                                     
				   ismixed = 1;
				 }                                                                                                                                                           
			     }                                                                                                                                                               
			   // Single-single
			   for(int a = 0; a < nSinglePixelTracks45; a++)                                                                                                                     
			     {                                                                                                                                                               
			       for(int b = 0; b < nSinglePixelTracks56; b++)                                                                                                                 
				 {                                                                                                                                                           
				   mpp = TMath::Sqrt(13000.0*13000.0*xipix56s->at(b)*xipix45s->at(a));                                                                                       
				   ypp = -0.5*TMath::Log(xipix56s->at(b)/xipix45s->at(a));                                                                                                    
				   mppss = mpp;
				   yppss = ypp;
				   mppssingsing->push_back(mpp);                                                                                                                             
				   yppssingsing->push_back(ypp);                                                                                                                             
				   hmppsingle->Fill(mpp);                                                                                                                                    
				   hyppsingle->Fill(ypp);                                                                                                                                    
				   hmyppsingle->Fill(mpp,ypp);                                                                                                                               
				   issinglesingle = 1;
				 }                                                                                                                                                           
			     }                                                                                                                                                               

			   /* Splitting by best category - no overlaps
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
			   */
			 }
		       hnpix45->Fill(nSinglePixelTracks45);
		       hnpix56->Fill(nSinglePixelTracks56);


                       // Sideband control regions                                                                                                                                                                           
                       if(samplenumber > 0)
                         {
                           // Signal region, only for MC                                                                                                                                                                     
                           if((acop < acopcut) && (jet1.Pt()/jet2.Pt() < ptbalcut))
			     {
			       npassdijetkine++;
			       if((jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
				 {
				   npassjetsubstr++;

				   hmasswwsignal->Fill(mydijet.M());
				   hywwsignal->Fill(mydijet.Rapidity());

				   // Just counting, no cut yet
				   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
				     npassjetxi++;

				   if(samplenumber >= 20 && mpp>0 && (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205))
				     {
				       for(Int_t s = 0; s < mppsmultmult->size(); s++)
					 {
					   hmassmatchsigmcmm->Fill(mppsmultmult->at(s)-mydijet.M());
					   hymatchsigmcmm->Fill(yppsmultmult->at(s)-mydijet.Rapidity());
					   hmassmatchratiosigmcmm->Fill(1 - (mydijet.M()/mppsmultmult->at(s)));
					 }
				       for(Int_t s = 0; s < mppsmixed->size(); s++)
					 {
					   hmassmatchsigmcmix->Fill(mppsmixed->at(s)-mydijet.M());
					   hymatchsigmcmix->Fill(yppsmixed->at(s)-mydijet.Rapidity());
					   hmassmatchratiosigmcmix->Fill(1 - (mydijet.M()/mppsmixed->at(s)));
					 }
				       for(Int_t s = 0; s < mppssingsing->size(); s++)
					 {
					   hmassmatchsigmcss->Fill(mppssingsing->at(s)-mydijet.M());
					   hymatchsigmcss->Fill(yppssingsing->at(s)-mydijet.Rapidity());
					   hmassmatchratiosigmcss->Fill(1 - (mydijet.M()/mppssingsing->at(s)));
					 }

                                       if(ismultimulti == 1)
					 {				       
					   int match45 = 0; int match56 = 0;
					   for(Int_t gp = 0; gp < gen_proton_xi->size(); gp++)
					     {
					       if(fabs(ximulti45 - gen_proton_xi->at(gp)) < 0.01 && gen_proton_pz->at(gp) > 0)
						 match45 = 1;
					       if(fabs(ximulti56 - gen_proton_xi->at(gp)) < 0.01 && gen_proton_pz->at(gp) < 0)
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
				       //				       hmppres->Fill(mpp/mppgen);
				       //				   hmjjres->Fill(mydijet.M()/gen_dijet_mass->at(0));
				       }
				 }
			     }
			 }
		       
		       // Control regions
		       if(samplenumber < 0 && mpp>0 && (xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205))
			 {
			   for(Int_t s = 0; s < mppsmultmult->size(); s++)
			     {
			       // Anti acoplanarity                                                                                                                                          
			       if((acop > acopcut) &&
				  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
				  (jet1.Pt()/jet2.Pt() < ptbalcut))
				 {
                                   hmassmatchantiacopmm->Fill(mppmm-mydijet.M());
                                   hymatchantiacopmm->Fill(yppmm-mydijet.Rapidity());
                                   hmassmatchratioantiacopmm->Fill(1 - (mydijet.M()/mppmm));
				   hmassrapiditymatchantiacopmm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			       // Anti pT balance                                                                                                                                            
			       if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
				  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
				  (acop < acopcut))
				 {
                                   hmassmatchantiptbalmm->Fill(mppmm-mydijet.M());
                                   hymatchantiptbalmm->Fill(yppmm-mydijet.Rapidity());
                                   hmassmatchratioantiptbalmm->Fill(1 - (mydijet.M()/mppmm));
                                   hmassrapiditymatchantiptbalmm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			       // Anti tau21                                                                                                                                                 
			       if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
				  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (acop < acopcut) &&
				  (jet1.Pt()/jet2.Pt()) <  ptbalcut)
				 {
                                   hmassmatchantitaumm->Fill(mppmm-mydijet.M());
                                   hymatchantitaumm->Fill(yppmm-mydijet.Rapidity());
                                   hmassmatchratioantitaumm->Fill(1 - (mydijet.M()/mppmm));
				   hmassrapiditymatchantitaumm->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				 }
			       // All cuts, but with signal region in matching blinded
			       if((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (acop < acopcut) &&
                                  (jet1.Pt()/jet2.Pt()) <  ptbalcut)
				 {
				   Float_t massmatch = 0.0;
				   Float_t ymatch = 0.0;
				   massmatch = 1 - (mydijet.M()/mppmm);
				   ymatch = yppmm-mydijet.Rapidity();
				   if(fabs(ymatch) > 0.5)
				     {
				       if(fabs(massmatch) > 1.0)
					 {
					   hmassrapiditymatchvetosignalregion->Fill(massmatch,ymatch);
					 }
				     }
				 }

			     }
			   for(Int_t s = 0; s < mppsmixed->size(); s++)
			     {
                               // Anti acoplanarity                                                                                                                                            
                               if((acop > acopcut) &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                                  (jet1.Pt()/jet2.Pt() < ptbalcut))
                                 {
                                   hmassmatchantiacopmix->Fill(mppmix-mydijet.M());
                                   hymatchantiacopmix->Fill(yppmix-mydijet.Rapidity());
                                   hmassmatchratioantiacopmix->Fill(1 - (mydijet.M()/mppmix));
                                 }
                               // Anti pT balance                                                                                                                                              
                               if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                                  (acop < acopcut))
                                 {
                                   hmassmatchantiptbalmix->Fill(mppmix-mydijet.M());
                                   hymatchantiptbalmix->Fill(yppmix-mydijet.Rapidity());
                                   hmassmatchratioantiptbalmix->Fill(1 - (mydijet.M()/mppmix));
                                 }
                               // Anti tau21                                                                                                                                                   
                               if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (acop < acopcut) &&
                                  (jet1.Pt()/jet2.Pt()) <  ptbalcut)
                                 {
                                   hmassmatchantitaumix->Fill(mppmix-mydijet.M());
                                   hymatchantitaumix->Fill(yppmix-mydijet.Rapidity());
                                   hmassmatchratioantitaumix->Fill(1 - (mydijet.M()/mppmix));
                                 }
			     }
			   for(Int_t s = 0; s < mppssingsing->size(); s++)
			     {
                               // Anti acoplanarity                                                                                                                                            
                               if((acop > acopcut) &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                                  (jet1.Pt()/jet2.Pt() < ptbalcut))
                                 {
                                   hmassmatchantiacopss->Fill(mppss-mydijet.M());
                                   hymatchantiacopss->Fill(yppss-mydijet.Rapidity());
                                   hmassmatchratioantiacopss->Fill(1 - (mydijet.M()/mppss));
                                 }
                               // Anti pT balance                                                                                                                                              
                               if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                                  (acop < acopcut))
                                 {
                                   hmassmatchantiptbalss->Fill(mppss-mydijet.M());
                                   hymatchantiptbalss->Fill(yppss-mydijet.Rapidity());
                                   hmassmatchratioantiptbalss->Fill(1 - (mydijet.M()/mppss));
                                 }
                               // Anti tau21                                                                                                                                                   
                               if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
                                  (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) &&
                                  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
                                  (acop < acopcut) &&
                                  (jet1.Pt()/jet2.Pt()) <  ptbalcut)
                                 {
                                   hmassmatchantitauss->Fill(mppss-mydijet.M());
                                   hymatchantitauss->Fill(yppss-mydijet.Rapidity());
                                   hmassmatchratioantitauss->Fill(1 - (mydijet.M()/mppss));
                                 }
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
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017B.root","RECREATE");
   if(samplenumber == -2)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017C.root","RECREATE");
   if(samplenumber == -3)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017D.root","RECREATE");
   if(samplenumber == -4)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017E.root","RECREATE");
   if(samplenumber == -5)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2017F.root","RECREATE");

   if(samplenumber == -6)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2016B.root","RECREATE");
   if(samplenumber == -7)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2016C.root","RECREATE");
   if(samplenumber == -8)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2016G.root","RECREATE");
   if(samplenumber == -9)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2016H.root","RECREATE");
   if(samplenumber == -10)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2018A.root","RECREATE");
   if(samplenumber == -11)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_datahist2018B.root","RECREATE");

   if(samplenumber == 1)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt170to300.root","RECREATE");
   if(samplenumber == 2)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt300to470.root","RECREATE");
   if(samplenumber == 3)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt470to600.root","RECREATE");
   if(samplenumber == 4)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt600to800.root","RECREATE");                                                           
   if(samplenumber == 5)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt800to1000.root","RECREATE");
   if(samplenumber == 6)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1000to1400.root","RECREATE");
   if(samplenumber == 7)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_ttbarhadronic.root","RECREATE");
   if(samplenumber == 8)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_wjetshadronic.root","RECREATE");
   if(samplenumber == 9)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_zjetshadronic.root","RECREATE");
   if(samplenumber == 10)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1400to1800.root","RECREATE");
   if(samplenumber == 11)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1800to2400.root","RECREATE");
   if(samplenumber == 12)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt2400to3200.root","RECREATE");


   if(samplenumber == 20)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwSM.root","RECREATE");
   if(samplenumber == 21)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w1point0noPUprotons_withFiducialAndKilling.root","RECREATE");
     //     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w1point0noPUprotons_noFiducial.root","RECREATE");
   if(samplenumber == 22)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w2point0noPUprotons_withFiducialAndKilling.root","RECREATE");
   if(samplenumber == 24)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w2point0noPUprotons_withFiducialAndKillingPostTS2.root","RECREATE");
   if(samplenumber == 25)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w5point0noPUprotons_withFiducialAndKillingPostTS2.root","RECREATE");


   if(samplenumber == 27)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwaCw2point0E5noPUprotons_withFiducialAndKilling.root","RECREATE");

   if(samplenumber == 31)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclzza0z5point0.root","RECREATE");

   if(samplenumber == 41)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwa0w1point0noPUprotons2017postTS2_withFiducialAndKilling.root","RECREATE");

   if(samplenumber == 99)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_exclwwaCWOnlyPUprotons2017postTS2_withFiducialAndKilling.root","RECREATE");

   // 2016
   if(samplenumber == 101)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt170to300_2016.root","RECREATE");
   if(samplenumber == 102)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt300to470_2016.root","RECREATE");
   if(samplenumber == 103)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt470to600_2016.root","RECREATE");
   if(samplenumber == 104)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt600to800_2016.root","RECREATE");
   if(samplenumber == 105)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt800to1000_2016.root","RECREATE");
   if(samplenumber == 106)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1000to1400_2016.root","RECREATE");
   if(samplenumber == 107)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_ttbarhadronic_2016.root","RECREATE");
   if(samplenumber == 108)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_wjetshadronic_2016.root","RECREATE");
   if(samplenumber == 109)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_zjetshadronic_2016.root","RECREATE");
   if(samplenumber == 110)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1400to1800_2016.root","RECREATE");
   if(samplenumber == 111)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt1800to2400_2016.root","RECREATE");
   if(samplenumber == 112)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJER_qcdpt2400to3200_2016.root","RECREATE");


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

   hmassmatchantitaumm->Write();
   hymatchantitaumm->Write();
   hmassmatchratioantitaumm->Write();
   hmassmatchantiacopmm->Write();
   hymatchantiacopmm->Write();
   hmassmatchratioantiacopmm->Write();
   hmassmatchantiptbalmm->Write();
   hymatchantiptbalmm->Write();
   hmassmatchratioantiptbalmm->Write();

   hmassmatchantitaumix->Write();
   hymatchantitaumix->Write();
   hmassmatchratioantitaumix->Write();
   hmassmatchantiacopmix->Write();
   hymatchantiacopmix->Write();
   hmassmatchratioantiacopmix->Write();
   hmassmatchantiptbalmix->Write();
   hymatchantiptbalmix->Write();
   hmassmatchratioantiptbalmix->Write();

   hmassmatchantitauss->Write();
   hymatchantitauss->Write();
   hmassmatchratioantitauss->Write();
   hmassmatchantiacopss->Write();
   hymatchantiacopss->Write();
   hmassmatchratioantiacopss->Write();
   hmassmatchantiptbalss->Write();
   hymatchantiptbalss->Write();
   hmassmatchratioantiptbalss->Write();

   hmassmatchsigmcmm->Write();
   hymatchsigmcmm->Write();
   hmassmatchratiosigmcmm->Write();
   hmassmatchsigmcmix->Write();
   hymatchsigmcmix->Write();
   hmassmatchratiosigmcmix->Write();
   hmassmatchsigmcss->Write();
   hymatchsigmcss->Write();
   hmassmatchratiosigmcss->Write();

   hmassmatchratiosigmcmult->Write();
   hymatchsigmcmult->Write();
   hmasscorrsigmcmult->Write();
   hycorrsigmcmult->Write();
   hmasscorrsigmcmulttruthmatched->Write();

   //   hmppres->Write();

   hmasswwantitau->Write();
   hmasswwantiacop->Write();
   hmasswwantiptbal->Write();
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
   std::cout << "Passing preselection = " << normxsec*npasspresel/nevgen << std::endl
	     << "Passing dijet kinematics = " << normxsec*npassdijetkine/nevgen << std::endl
	     << "Passing jet substructure = " << normxsec*npassjetsubstr/nevgen << std::endl
	     << "Passing xi(jets) = " << normxsec*npassjetxi/nevgen << std::endl
	     << "Passing 2 PPS multi-RP protons = " << normxsec*npasspps/nevgen << std::endl
	     << "Passing pp-WW matching = " << normxsec*npassppsmatchksenia/nevgen << std::endl;

}
