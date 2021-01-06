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
   // Limit bkg MC samples to 1M events for quick tests
   //   if((samplenumber > 1 && samplenumber < 20) || (samplenumber > 100 && samplenumber < 120) || (samplenumber > 200 && samplenumber < 220))
   //     nentries = 1000000;

   // Total event weight (PU + anything else)
   Float_t myweight = 1.0;

   // Pre-selection plots
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
   TH1F *hprunedrotatedjjdat = new TH1F("hprunedrotatedjjdat","hprunedrotatedjjdat",250,0,500);

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

   // Sideband control region plots - WW
   TH1F *hmassmatchantiacopmmww = new TH1F("hmassmatchantiacopmmww","hmassmatchantiacopmmww",500,-2500,2500);
   TH1F *hymatchantiacopmmww = new TH1F("hymatchantiacopmmww","hymatchantiacopmmww",100,-5,5);
   TH1F *hmassmatchratioantiacopmmww = new TH1F("hmassmatchratioantiacopmmww","hmassmatchratioantiacopmmww",100,-5,5);
   TH1F *hmassmatchantitaummww = new TH1F("hmassmatchantitaummww","hmassmatchantitaummww",500,-2500,2500);
   TH1F *hymatchantitaummww = new TH1F("hymatchantitaummww","hymatchantitaummww",100,-5,5);
   TH1F *hmassmatchratioantitaummww = new TH1F("hmassmatchratioantitaummww","hmassmatchratioantitaummww",100,-5,5);
   TH1F *hmassmatchantiptbalmmww = new TH1F("hmassmatchantiptbalmmww","hmassmatchantiptbalmmww",500,-2500,2500);
   TH1F *hymatchantiptbalmmww = new TH1F("hymatchantiptbalmmww","hymatchantiptbalmmww",100,-5,5);
   TH1F *hmassmatchratioantiptbalmmww = new TH1F("hmassmatchratioantiptbalmmww","hmassmatchratioantiptbalmmww",100,-5,5);
   TH1F *hmassmatchantiprunedmmww = new TH1F("hmassmatchantiprunedmmww","hmassmatchantiprunedmmww",500,-2500,2500);
   TH1F *hymatchantiprunedmmww = new TH1F("hymatchantiprunedmmww","hymatchantiprunedmmww",100,-5,5);
   TH1F *hmassmatchratioantiprunedmmww = new TH1F("hmassmatchratioantiprunedmmww","hmassmatchratioantiprunedmmww",100,-5,5);
   TH1F *hmassmatchantiprunednarrowmmww = new TH1F("hmassmatchantiprunednarrowmmww","hmassmatchantiprunednarrowmmww",500,-2500,2500);
   TH1F *hymatchantiprunednarrowmmww = new TH1F("hymatchantiprunednarrowmmww","hymatchantiprunednarrowmmww",100,-5,5);
   TH1F *hmassmatchratioantiprunednarrowmmww = new TH1F("hmassmatchratioantiprunednarrowmmww","hmassmatchratioantiprunednarrowmmww",100,-5,5);

   // Sideband control region plots - ZZ                                                                                                                                                                        
   TH1F *hmassmatchantiacopmmzz = new TH1F("hmassmatchantiacopmmzz","hmassmatchantiacopmmzz",500,-2500,2500);
   TH1F *hymatchantiacopmmzz = new TH1F("hymatchantiacopmmzz","hymatchantiacopmmzz",100,-5,5);
   TH1F *hmassmatchratioantiacopmmzz = new TH1F("hmassmatchratioantiacopmmzz","hmassmatchratioantiacopmmzz",100,-5,5);
   TH1F *hmassmatchantitaummzz = new TH1F("hmassmatchantitaummzz","hmassmatchantitaummzz",500,-2500,2500);
   TH1F *hymatchantitaummzz = new TH1F("hymatchantitaummzz","hymatchantitaummzz",100,-5,5);
   TH1F *hmassmatchratioantitaummzz = new TH1F("hmassmatchratioantitaummzz","hmassmatchratioantitaummzz",100,-5,5);
   TH1F *hmassmatchantiptbalmmzz = new TH1F("hmassmatchantiptbalmmzz","hmassmatchantiptbalmmzz",500,-2500,2500);
   TH1F *hymatchantiptbalmmzz = new TH1F("hymatchantiptbalmmzz","hymatchantiptbalmmzz",100,-5,5);
   TH1F *hmassmatchratioantiptbalmmzz = new TH1F("hmassmatchratioantiptbalmmzz","hmassmatchratioantiptbalmmzz",100,-5,5);
   TH1F *hmassmatchantiprunedmmzz = new TH1F("hmassmatchantiprunedmmzz","hmassmatchantiprunedmmzz",500,-2500,2500);
   TH1F *hymatchantiprunedmmzz = new TH1F("hymatchantiprunedmmzz","hymatchantiprunedmmzz",100,-5,5);
   TH1F *hmassmatchratioantiprunedmmzz = new TH1F("hmassmatchratioantiprunedmmzz","hmassmatchratioantiprunedmmzz",100,-5,5);
   TH1F *hmassmatchantiprunednarrowmmzz = new TH1F("hmassmatchantiprunednarrowmmzz","hmassmatchantiprunednarrowmmzz",500,-2500,2500);
   TH1F *hymatchantiprunednarrowmmzz = new TH1F("hymatchantiprunednarrowmmzz","hymatchantiprunednarrowmmzz",100,-5,5);
   TH1F *hmassmatchratioantiprunednarrowmmzz = new TH1F("hmassmatchratioantiprunednarrowmmzz","hmassmatchratioantiprunednarrowmmzz",100,-5,5);


   // 1-D proton-VV matching plots                                                                                                                                                                              
   TH2F *hgenxinomatch = new TH2F("hgenxinomatch","hgenxinomatch",500,0,0.5,500,0,0.5);
   TH1F *hmassmatchratiosigmcoutofacceptancemm = new TH1F("hmassmatchratiosigmcoutofacceptancemm","hmassmatchratiosigmcoutofacceptancemm",100,-5,5);
   TH1F *hmassmatchratiosigmcinacceptancemm = new TH1F("hmassmatchratiosigmcinacceptancemm","hmassmatchratiosigmcinacceptancemm",100,-5,5);
   TH1F *hmassmatchratiosigmcinacceptancenomatchmm = new TH1F("hmassmatchratiosigmcinacceptancenomatchmm","hmassmatchratiosigmcinacceptancenomatchmm",100,-5,5);
   TH1F *hymatchsigmcoutofacceptancemm = new TH1F("hymatchsigmcoutofacceptancemm","hymatchsigmcoutofacceptancemm",500,-5,5);
   TH1F *hymatchsigmcinacceptancemm = new TH1F("hymatchsigmcinacceptancemm","hymatchsigmcinacceptancemm",500,-5,5);
   TH1F *hymatchsigmcinacceptancenomatchmm = new TH1F("hymatchsigmcinacceptancenomatchmm","hymatchsigmcinacceptancenomatchmm",500,-5,5);
   
   // 1-D proton-VV matching plots with systematic shifts
   TH1F *hmassmatchratiosigmcmmshiftupww = new TH1F("hmassmatchratiosigmcmmshiftupww","hmassmatchratiosigmcmmshiftupww",500,-5,5);
   TH1F *hmassmatchratiosigmcmmshiftdownww = new TH1F("hmassmatchratiosigmcmmshiftdownww","hmassmatchratiosigmcmmshiftdownww",500,-5,5);
   TH1F *hymatchsigmcmmshiftupww = new TH1F("hymatchsigmcmmshiftupww","hymatchsigmcmmshiftupww",500,-5,5);
   TH1F *hymatchsigmcmmshiftdownww = new TH1F("hymatchsigmcmmshiftdownww","hymatchsigmcmmshiftdownww",500,-5,5);
   TH1F *hmassmatchratiosigmcmmshiftupzz = new TH1F("hmassmatchratiosigmcmmshiftupzz","hmassmatchratiosigmcmmshiftupzz",500,-5,5);
   TH1F *hmassmatchratiosigmcmmshiftdownzz = new TH1F("hmassmatchratiosigmcmmshiftdownzz","hmassmatchratiosigmcmmshiftdownzz",500,-5,5);
   TH1F *hymatchsigmcmmshiftupzz = new TH1F("hymatchsigmcmmshiftupzz","hymatchsigmcmmshiftupzz",500,-5,5);
   TH1F *hymatchsigmcmmshiftdownzz = new TH1F("hymatchsigmcmmshiftdownzz","hymatchsigmcmmshiftdownzz",500,-5,5);


   // 2-D proton-VV matching plots
   TH2F *hmassrapiditymatchvetosignalregionww = new TH2F("hmassrapiditymatchvetosignalregionww","hmassrapiditymatchvetosignalregionww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchvetoorsignalregionww = new TH2F("hmassrapiditymatchvetoorsignalregionww","hmassrapiditymatchvetoorsignalregionww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchvetosignalregionzz = new TH2F("hmassrapiditymatchvetosignalregionzz","hmassrapiditymatchvetosignalregionzz",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchvetoorsignalregionzz = new TH2F("hmassrapiditymatchvetoorsignalregionzz","hmassrapiditymatchvetoorsignalregionzz",500,-5,5,500,-5,5);

   TH2F *hmassrapiditymatchantitaummww = new TH2F("hmassrapiditymatchantitaummww","hmassrapiditymatchantitaummww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiacopmmww = new TH2F("hmassrapiditymatchantiacopmmww","hmassrapiditymatchantiacopmmww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiptbalmmww = new TH2F("hmassrapiditymatchantiptbalmmww","hmassrapiditymatchantiptbalmmww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiprunedmmww = new TH2F("hmassrapiditymatchantiprunedmmww","hmassrapiditymatchantiprunedmmww",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiprunednarrowmmww = new TH2F("hmassrapiditymatchantiprunednarrowmmww","hmassrapiditymatchantiprunednarrowmmww",500,-5,5,500,-5,5);

   TH2F *hmassrapiditymatchantitaummzz = new TH2F("hmassrapiditymatchantitaummzz","hmassrapiditymatchantitaummzz",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiacopmmzz = new TH2F("hmassrapiditymatchantiacopmmzz","hmassrapiditymatchantiacopmmzz",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiptbalmmzz = new TH2F("hmassrapiditymatchantiptbalmmzz","hmassrapiditymatchantiptbalmmzz",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiprunedmmzz = new TH2F("hmassrapiditymatchantiprunedmmzz","hmassrapiditymatchantiprunedmmzz",500,-5,5,500,-5,5);
   TH2F *hmassrapiditymatchantiprunednarrowmmzz = new TH2F("hmassrapiditymatchantiprunednarrowmmzz","hmassrapiditymatchantiprunednarrowmmzz",500,-5,5,500,-5,5);

   TH2F *hycorrpreseldatmult = new TH2F("hycorrpreseldatmult","hycorrpreseldatmult",100,-5,5,100,-5,5);
   TH2F *hmasscorrpreseldatmult = new TH2F("hmasscorrpreseldatmult","hmasscorrpreseldatmult",250,0,2500,250,0,2500);
   TH2F *dymassratiocorrpreseldatmult = new TH2F("dymassratiocorrpreseldatmult","dymassratiocorrpreseldatmult",500,-5,5,500,-5,5);

   // Anit-pT balance control plots
   TH1F *hmassvvantiptbalww = new TH1F("hmassvvantiptbalww","hmassvvantiptbalww",250,0,5000);
   TH1F *hmassvvantiptbalzz = new TH1F("hmassvvantiptbalzz","hmassvvantiptbalzz",250,0,5000);

   // Anti-acoplanarity control plots
   TH1F *hmassvvantiacopww = new TH1F("hmassvvantiacopww","hmassvvantiacopww",250,0,5000);
   TH1F *hmj1antiacopww = new TH1F("hmj1antiacopww","hmj1antiacopww",250,0,1000);
   TH1F *htau211antiacopww = new TH1F("htau211antiacopww","htau211antiacopww",250,0,1);
   TH1F *hmj2antiacopww = new TH1F("hmj2antiacopww","hmj2antiacopww",250,0,1000);
   TH1F *htau212antiacopww = new TH1F("htau212antiacopww","htau212antiacopww",250,0,1);
   TH1F *hmassvvantiacopzz = new TH1F("hmassvvantiacopzz","hmassvvantiacopzz",250,0,5000);
   TH1F *hmj1antiacopzz = new TH1F("hmj1antiacopzz","hmj1antiacopzz",250,0,1000);
   TH1F *htau211antiacopzz = new TH1F("htau211antiacopzz","htau211antiacopzz",250,0,1);
   TH1F *hmj2antiacopzz = new TH1F("hmj2antiacopzz","hmj2antiacopzz",250,0,1000);
   TH1F *htau212antiacopzz = new TH1F("htau212antiacopzz","htau212antiacopzz",250,0,1);

   // Anti-tau21 control plots
   TH1F *hmassvvantitauww = new TH1F("hmassvvantitauww","hmassvvantitauww",250,0,5000);
   TH1F *hmj1antitauww = new TH1F("hmj1antitauww","hmj1antitauww",250,0,1000);
   TH1F *htau211antitauww = new TH1F("htau211antitauww","htau211antitauww",250,0,1);
   TH1F *hmj2antitauww = new TH1F("hmj2antitauww","hmj2antitauww",250,0,1000);
   TH1F *htau212antitauww = new TH1F("htau212antitauww","htau212antitauww",250,0,1);
   TH1F *hmassvvantitauzz = new TH1F("hmassvvantitauzz","hmassvvantitauzz",250,0,5000);
   TH1F *hmj1antitauzz = new TH1F("hmj1antitauzz","hmj1antitauzz",250,0,1000);
   TH1F *htau211antitauzz = new TH1F("htau211antitauzz","htau211antitauzz",250,0,1);
   TH1F *hmj2antitauzz = new TH1F("hmj2antitauzz","hmj2antitauzz",250,0,1000);
   TH1F *htau212antitauzz = new TH1F("htau212antitauzz","htau212antitauzz",250,0,1);

   // Anti-pruned mass control plots                                                                                                                                                               
   TH1F *hmassvvantiprunedww = new TH1F("hmassvvantiprunedww","hmassvvantiprunedww",250,0,5000);
   TH1F *hmj1antiprunedww = new TH1F("hmj1antiprunedww","hmj1antiprunedww",250,0,1000);
   TH1F *htau211antiprunedww = new TH1F("htau211antiprunedww","htau211antiprunedww",250,0,1);
   TH1F *hmj2antiprunedww = new TH1F("hmj2antiprunedww","hmj2antiprunedww",250,0,1000);
   TH1F *htau212antiprunedww = new TH1F("htau212antiprunedww","htau212antiprunedww",250,0,1);
   TH1F *hmassvvantiprunedzz = new TH1F("hmassvvantiprunedzz","hmassvvantiprunedzz",250,0,5000);
   TH1F *hmj1antiprunedzz = new TH1F("hmj1antiprunedzz","hmj1antiprunedzz",250,0,1000);
   TH1F *htau211antiprunedzz = new TH1F("htau211antiprunedzz","htau211antiprunedzz",250,0,1);
   TH1F *hmj2antiprunedzz = new TH1F("hmj2antiprunedzz","hmj2antiprunedzz",250,0,1000);
   TH1F *htau212antiprunedzz = new TH1F("htau212antiprunedzz","htau212antiprunedzz",250,0,1);

   // Anti-pruned mass control plots, narrow mass region
   TH1F *hmassvvantiprunednarrowww = new TH1F("hmassvvantiprunednarrowww","hmassvvantiprunednarrowww",250,0,5000);
   TH1F *hmj1antiprunednarrowww = new TH1F("hmj1antiprunednarrowww","hmj1antiprunednarrowww",250,0,1000);
   TH1F *htau211antiprunednarrowww = new TH1F("htau211antiprunednarrowww","htau211antiprunednarrowww",250,0,1);
   TH1F *hmj2antiprunednarrowww = new TH1F("hmj2antiprunednarrowww","hmj2antiprunednarrowww",250,0,1000);
   TH1F *htau212antiprunednarrowww = new TH1F("htau212antiprunednarrowww","htau212antiprunednarrowww",250,0,1);
   TH1F *hmassvvantiprunednarrowzz = new TH1F("hmassvvantiprunednarrowzz","hmassvvantiprunednarrowzz",250,0,5000);
   TH1F *hmj1antiprunednarrowzz = new TH1F("hmj1antiprunednarrowzz","hmj1antiprunednarrowzz",250,0,1000);
   TH1F *htau211antiprunednarrowzz = new TH1F("htau211antiprunednarrowzz","htau211antiprunednarrowzz",250,0,1);
   TH1F *hmj2antiprunednarrowzz = new TH1F("hmj2antiprunednarrowzz","hmj2antiprunednarrowzz",250,0,1000);
   TH1F *htau212antiprunednarrowzz = new TH1F("htau212antiprunednarrowzz","htau212antiprunednarrowzz",250,0,1);


   TH1F *hcrossingangle = new TH1F("hcrossingangle","hcrossingangle",70,100,170);

   TH1F *hmppres = new TH1F("hmppres","hmppres",100,0,2);
   TH1F *hmjjres = new TH1F("hmjjres","hmjjres",100,0,2);
   TH1F *hmassmatchratiosigmcmultww = new TH1F("hmassmatchratiosigmcmultww","hmassmatchratiosigmcmultww",500,-5,5);
   TH1F *hmassmatchratiosigmcmultzz = new TH1F("hmassmatchratiosigmcmultzz","hmassmatchratiosigmcmultzz",500,-5,5);

   TH1F *xijets45= new TH1F("xijets45","xijets45",250,0,0.25);
   TH1F *xijets56= new TH1F("xijets56","xijets56",250,0,0.25);
   TH1F *resxijets45= new TH1F("resxijets45","resxijets45",100,0,2);
   TH1F *resxijets56= new TH1F("resxijets56","resxijets56",100,0,2);
   TH2F *resxijetscorr45= new TH2F("resxijetscorr45","resxijetscorr45",300,0,0.3,300,0,0.3);
   TH2F *resxijetscorr56= new TH2F("resxijetscorr56","resxijetscorr56",300,0,0.3,300,0,0.3);

   TH1F *hmassvvsignalww = new TH1F("hmassvvsignalww","hmassvvsignalww",250,0,5000);
   TH1F *hywwsignalww = new TH1F("hywwsignalww","hywwsignalww",250,-5,5);
   TH1F *hmassvvsignalzz = new TH1F("hmassvvsignalzz","hmassvvsignalzz",250,0,5000);
   TH1F *hywwsignalzz = new TH1F("hywwsignalzz","hywwsignalzz",250,-5,5);

   // Signal region plots                                                                                                                                                                          
   TH1F *hmassmatchsigmcmmww = new TH1F("hmassmatchsigmcmmww","hmassmatchsigmcmmww",500,-2500,2500);
   TH1F *hymatchsigmcmmww = new TH1F("hymatchsigmcmmww","hymatchsigmcmmww",500,-5,5);
   TH1F *hmassmatchratiosigmcmmww = new TH1F("hmassmatchratiosigmcmmww","hmassmatchratiosigmcmmww",500,-5,5);
   TH1F *hymatchsigmcmultww = new TH1F("hymatchsigmcmultww","hymatchsigmcmultww",500,-5,5);
   TH2F *hmasscorrsigmcmultww = new TH2F("hmasscorrsigmcmultww","hmasscorrsigmcmultww",250,0,2500,250,0,2500);
   TH2F *hycorrsigmcmultww = new TH2F("hycorrsigmcmultww","hycorrsigmcmultww",100,-5,5,100,-5,5);
   TH2F *hmasscorrsigmcmulttruthmatchedww = new TH2F("hmasscorrsigmcmulttruthmatchedww","hmasscorrsigmcmulttruthmatchedww",250,0,2500,250,0,2500);
 
   TH1F *hmassmatchsigmcmmzz = new TH1F("hmassmatchsigmcmmzz","hmassmatchsigmcmmzz",500,-2500,2500);
   TH1F *hymatchsigmcmmzz = new TH1F("hymatchsigmcmmzz","hymatchsigmcmmzz",500,-5,5);
   TH1F *hmassmatchratiosigmcmmzz = new TH1F("hmassmatchratiosigmcmmzz","hmassmatchratiosigmcmmzz",500,-5,5);
   TH1F *hymatchsigmcmultzz = new TH1F("hymatchsigmcmultzz","hymatchsigmcmultzz",500,-5,5);
   TH2F *hmasscorrsigmcmultzz = new TH2F("hmasscorrsigmcmultzz","hmasscorrsigmcmultzz",250,0,2500,250,0,2500);
   TH2F *hycorrsigmcmultzz = new TH2F("hycorrsigmcmultzz","hycorrsigmcmultzz",100,-5,5,100,-5,5);
   TH2F *hmasscorrsigmcmulttruthmatchedzz = new TH2F("hmasscorrsigmcmulttruthmatchedzz","hmasscorrsigmcmulttruthmatchedzz",250,0,2500,250,0,2500);



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
   std::vector<float> *xishiftmultis45 = new std::vector<float>;
   std::vector<float> *xishiftmultis56 = new std::vector<float>;
   std::vector<float> *mppsmultmultshiftup = new std::vector<float>;
   std::vector<float> *mppsmultmultshiftdown = new std::vector<float>;
   std::vector<float> *yppsmultmultshiftup = new std::vector<float>;
   std::vector<float> *yppsmultmultshiftdown = new std::vector<float>;


   // Counters for # of MC events passing cuts
   Float_t npasspresel = 0;
   Float_t npassdijetkine = 0;
   Float_t npassjetsubstr = 0;
   Float_t npassjetxi = 0;
   Float_t npasspps = 0;
   Float_t npassppsbeforecuts = 0;
   Float_t npassppsmatchksenia = 0;
   Float_t npassppsmatchkseniaww = 0;
   Float_t npassppsmatchkseniazz = 0;

   // Counters for sideband background normalization
   Float_t npassnonblindnormregionww = 0;
   Float_t npassantiacopnormregionww = 0;
   Float_t npassantitaunormregionww = 0;
   Float_t npassantimassnormregionww = 0;
   Float_t npassantimassnarrownormregionww = 0;
   Float_t npassantiacopsigregionww = 0;
   Float_t npassantitausigregionww = 0;
   Float_t npassantimasssigregionww = 0;
   Float_t npassantimassnarrowsigregionww = 0;

   Float_t npassnonblindnormregionzz = 0;
   Float_t npassantiacopnormregionzz = 0;
   Float_t npassantitaunormregionzz = 0;
   Float_t npassantimassnormregionzz = 0;
   Float_t npassantimassnarrownormregionzz = 0;
   Float_t npassantiacopsigregionzz = 0;
   Float_t npassantitausigregionzz = 0;
   Float_t npassantimasssigregionzz = 0;
   Float_t npassantimassnarrowsigregionzz = 0;


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
   if(samplenumber == 21)
     outtextfile = "MC_EventsForMixing_signal_WWA0W2E-6_preTS2_2017.txt";
   if(samplenumber == 22)
     outtextfile = "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2017.txt";
   if(samplenumber == 23)
     outtextfile = "MC_EventsForMixing_signal_WWACW2E-5_preTS2_2017.txt";

   if(samplenumber == 40)
     outtextfile = "MC_EventsForMixing_signal_WWA0W1E-6_postTS2_2017.txt";
   if(samplenumber == 42)
     outtextfile = "MC_EventsForMixing_signal_WWA0W5E-6_postTS2_2017.txt";
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
   if(samplenumber == 122)
     outtextfile = "MC_EventsForMixing_signal_WWA0W5E-6_preTS2_2016.txt";
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
   if(samplenumber == 222)
     outtextfile = "MC_EventsForMixing_signal_WWA0W5E-6_2018.txt";
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

   // JH: "999" is a dummy samplenumber used for testing new ntuples
   if(samplenumber == 999)
     erastring = "2016preTS2";
     //     erastring = "2018";
     //     erastring = "2017preTS2";

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
	   Float_t rotatedprunedmasses = 0.0;
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

	   Float_t mwlowpreselcut = 55.0;
	   Float_t mwhipreselcut = 215.0;

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

		       npasspresel+= 1.0*myweight;

		       if(jet_corrmass->at(indleading) >= mwlowpreselcut && jet_corrmass->at(indleading) <= mwhipreselcut)
			 {
			   htau21dat1->Fill(jet_tau2->at(indleading)/jet_tau1->at(indleading),myweight);
                           hmjdat1->Fill(jet_corrmass->at(indleading),myweight);
			   rhoprime1 = TMath::Log(jet_corrmass->at(indleading)*jet_corrmass->at(indleading)/jet_pt->at(indleading));
			   tau21vrhoprime1->Fill(rhoprime1,jet_tau2->at(indleading)/jet_tau1->at(indleading));
			   taut21ddt1 = (jet_tau2->at(indleading)/jet_tau1->at(indleading)) - (-0.082 * rhoprime1);
			   htau21ddtdat1->Fill(taut21ddt1,myweight);
			 }
		       if(jet_corrmass->at(indsecond) >= mwlowpreselcut && jet_corrmass->at(indsecond) <= mwhipreselcut)
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

		       // Ksenia's rotation of the pruned mass correlation for WW/ZZ separation
		       rotatedprunedmasses = (TMath::Cos(TMath::Pi()/4.0)*jet_corrmass->at(indleading)) + (TMath::Sin(TMath::Pi()/4.0)*jet_corrmass->at(indsecond));
		       if(jet_corrmass->at(indleading) >= 55 && jet_corrmass->at(indleading) <= 215 && jet_corrmass->at(indsecond) >= 55 && jet_corrmass->at(indsecond) <= 215)
			 hprunedrotatedjjdat->Fill(rotatedprunedmasses,myweight);
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
		       Float_t mwlowcut = 60.0;
		       Float_t mwhicut = 107.0;
		       Float_t mrotatedcut = 117.8;
		       Float_t tau21cut = 0.75;
		       Float_t massmatchcutksenia = 0.11506000;
		       Float_t rapiditymatchcutksenia = 0.057220000;
		       Float_t massmatchnormregion = 1.0;
		       Float_t rapiditymatchnormregion = 0.5;
		       
		       // Proton part
		       float mpp = 0;
		       float ypp = 0;

		       float mppmm = 0;
		       float yppmm = 0;

		       float mppshiftup = 0;
		       float mppshiftdown = 0;
		       float yppshiftup  = 0;
		       float yppshiftdown = 0;
		       
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
			   float thethetastx = 0;
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

			   float xishiftmag56 = 0;
			   float xishiftmag45 = 0;

			   /*
			    * First loop over all protons to get good multi-RP candidates and apply eff. corrections to MC
			    */
			   for(int p = 0; p < proton_xi->size(); p++)                                                           
			     {
			       if(proton_ismultirp->at(p) == 1)
				 {
				   thexi = proton_xi->at(p);
				   thethetasty = proton_thy->at(p);
				   thethetastx = proton_thx->at(p);
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
									   crossingangle, erastring, thexi, thethetasty, 						      
									   theshift1, theshift2);
				     }

				   if(samplenumber > 0)
				     {
                                       passesselector = TightMultiRPProton(thex1, they1, thex2, they2,
                                                                           thetax1, thetay1, thetax2, thetay2,
                                                                           thearm, rpid1, rpid2,
                                                                           crossingangle, erastring, thexi, thethetasty,
                                                                           theshift1, theshift2);
				       
				       // Note: As of Nov. 2020, the efficiencies are applied at the ntuple-making level (A. Bellora). 
				       // Therefore we do not re-apply them here, but leave the call commented out in case it's needed to 
				       // compare to older studies. 
				       // passesprotonefficiency = eff.GetMultiRPAcceptRejectDecision(thex1, they1, thex2, they2, rpid1, rpid2, erastring);
				       passesprotonefficiency = true; 
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
					   
					   // Apply xi scale systematic shifts for MC                                                                                  
					   // For now comment this out, until systematics ROOT file is officially released
					   /*
					   if(samplenumber > 0)
					     {
					       xishiftmag45 = eff.GetMultiRPXiScaleUncertainty(thearm, thexi, erastring);
					       xishiftmultis45->push_back(xishiftmag45);
					     }
					   */
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

                                           // Apply xi scale systematic shifts for MC                                                                                  
					   // For now comment this out, until systematics ROOT file is officially released             
					   /*
                                           if(samplenumber > 0)
                                             {
                                               xishiftmag56 = eff.GetMultiRPXiScaleUncertainty(thearm, thexi, erastring);
                                               xishiftmultis56->push_back(xishiftmag56);
                                             }
					   */
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

			       // For now comment systematic scale shifts, until official release
			       /*
			       mppshiftup = TMath::Sqrt(13000.0*13000.0*
							(ximulti56s->at(indexmaxmulti56)+xishiftmultis56->at(indexmaxmulti56))*
							(ximulti45s->at(indexmaxmulti45)+xishiftmultis45->at(indexmaxmulti45)));
			       yppshiftup = -0.5*TMath::Log((ximulti56s->at(indexmaxmulti56)+xishiftmultis56->at(indexmaxmulti56))/
							    (ximulti45s->at(indexmaxmulti45)+xishiftmultis45->at(indexmaxmulti45)));
                               mppshiftdown = TMath::Sqrt(13000.0*13000.0*
                                                        (ximulti56s->at(indexmaxmulti56)-xishiftmultis56->at(indexmaxmulti56))*
							  (ximulti45s->at(indexmaxmulti45)-xishiftmultis45->at(indexmaxmulti45)));
                               yppshiftdown = -0.5*TMath::Log((ximulti56s->at(indexmaxmulti56)-xishiftmultis56->at(indexmaxmulti56))/
                                                            (ximulti45s->at(indexmaxmulti45)-xishiftmultis45->at(indexmaxmulti45)));
			       */

			       mppmm = mpp;
			       yppmm = ypp;
			       mppsmultmult->push_back(mpp);
			       yppsmultmult->push_back(ypp);
			       mppsmultmultshiftup->push_back(mppshiftup);
                               mppsmultmultshiftdown->push_back(mppshiftdown);
                               yppsmultmultshiftup->push_back(yppshiftup);
                               yppsmultmultshiftdown->push_back(yppshiftdown);

			       hmppmulti->Fill(mpp);
			       hyppmulti->Fill(ypp);
			       hmyppmulti->Fill(mpp,ypp);
			       
			       hmasscorrpreseldatmult->Fill(mpp,mydijet.M());
			       hycorrpreseldatmult->Fill(ypp,mydijet.Rapidity());
			       dymassratiocorrpreseldatmult->Fill(1-mydijet.M()/mpp,mydijet.Rapidity()-ypp);

			       hdtmulti->Fill(timemulti45s->at(indexmaxmulti45) - timemulti56s->at(indexmaxmulti56));
			       ismultimulti = 1;
			       npassppsbeforecuts+= 1.0*myweight;
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
			       npassdijetkine+= 1.0*myweight;
			       if((jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
				  (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
				  (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut))
				 {
				   npassjetsubstr+= 1.0*myweight;

				   // Just counting
				   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
				     npassjetxi+= 1.0*myweight;

				   if(xijets1 > 0.04 && xijets1 < 0.205 && xijets2 > 0.04 && xijets2 < 0.205)
				     {
				       if(rotatedprunedmasses <= mrotatedcut)
					 {
					   hmassvvsignalww->Fill(mydijet.M());
					   hywwsignalww->Fill(mydijet.Rapidity());
					 }
				       if(rotatedprunedmasses > mrotatedcut)
					 {
                                           hmassvvsignalzz->Fill(mydijet.M());
                                           hywwsignalzz->Fill(mydijet.Rapidity());
					 }
				       if(mpp>0) // MC events with protons - e.g. signal MC
					 {
					   for(Int_t s = 0; s < mppsmultmult->size(); s++)
					     {
					       if(rotatedprunedmasses <= mrotatedcut)
						 {
						   hmassmatchsigmcmmww->Fill(mppsmultmult->at(s)-mydijet.M());
						   hymatchsigmcmmww->Fill(yppsmultmult->at(s)-mydijet.Rapidity());
						   hmassmatchratiosigmcmmww->Fill(1 - (mydijet.M()/mppsmultmult->at(s)));
						   hmassmatchratiosigmcmmshiftupww->Fill(1 - (mydijet.M()/mppsmultmultshiftup->at(s)));
						   hmassmatchratiosigmcmmshiftdownww->Fill(1 - (mydijet.M()/mppsmultmultshiftdown->at(s)));
						   hymatchsigmcmmshiftupww->Fill(yppsmultmultshiftup->at(s)-mydijet.Rapidity());
						   hymatchsigmcmmshiftdownww->Fill(yppsmultmultshiftdown->at(s)-mydijet.Rapidity());
						 }
                                               if(rotatedprunedmasses > mrotatedcut)
                                                 {
                                                   hmassmatchsigmcmmzz->Fill(mppsmultmult->at(s)-mydijet.M());
                                                   hymatchsigmcmmzz->Fill(yppsmultmult->at(s)-mydijet.Rapidity());
                                                   hmassmatchratiosigmcmmzz->Fill(1 - (mydijet.M()/mppsmultmult->at(s)));
                                                   hmassmatchratiosigmcmmshiftupzz->Fill(1 - (mydijet.M()/mppsmultmultshiftup->at(s)));
                                                   hmassmatchratiosigmcmmshiftdownzz->Fill(1 - (mydijet.M()/mppsmultmultshiftdown->at(s)));
                                                   hymatchsigmcmmshiftupzz->Fill(yppsmultmultshiftup->at(s)-mydijet.Rapidity());
                                                   hymatchsigmcmmshiftdownzz->Fill(yppsmultmultshiftdown->at(s)-mydijet.Rapidity());
                                                 }

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
					   float mppgen = TMath::Sqrt(13000.0*13000.0*xigen45*xigen56);
					   float yppgen = -0.5*TMath::Log(xigen56/xigen45);

					   npasspps+= 1.0*myweight;

					   if(rotatedprunedmasses <= mrotatedcut)
					     {
					       hmassmatchratiosigmcmultww->Fill(1 - (mydijet.M()/mppsmultmult->at(0)));
					       hymatchsigmcmultww->Fill(yppsmultmult->at(0)-mydijet.Rapidity());
					       hmasscorrsigmcmultww->Fill(mydijet.M(),mppsmultmult->at(0));
					       hycorrsigmcmultww->Fill(mydijet.Rapidity(),yppsmultmult->at(0));
					     }
					   if(rotatedprunedmasses > mrotatedcut)
					     {
                                               hmassmatchratiosigmcmultzz->Fill(1 - (mydijet.M()/mppsmultmult->at(0)));
                                               hymatchsigmcmultzz->Fill(yppsmultmult->at(0)-mydijet.Rapidity());
                                               hmasscorrsigmcmultzz->Fill(mydijet.M(),mppsmultmult->at(0));
                                               hycorrsigmcmultzz->Fill(mydijet.Rapidity(),yppsmultmult->at(0));
					     }

					   if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) && 
					      (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
					     {
					       npassppsmatchksenia+= 1.0*myweight;
					       if(rotatedprunedmasses <= mrotatedcut)
						 npassppsmatchkseniaww+= 1.0*myweight;
					       if(rotatedprunedmasses > mrotatedcut)
						 npassppsmatchkseniazz+= 1.0*myweight;
					     }
					   else
					     {
					       hgenxinomatch->Fill(xigen45,xigen56);
					     }
					   
					   if(match45 == 1 && match56 == 1)
					     {
                                               if(rotatedprunedmasses <= mrotatedcut)
						 hmasscorrsigmcmulttruthmatchedww->Fill(mydijet.M(),mppsmultmult->at(0));
                                               if(rotatedprunedmasses > mrotatedcut)
                                                 hmasscorrsigmcmulttruthmatchedzz->Fill(mydijet.M(),mppsmultmult->at(0));
					     }

					   // JH - testing with 2018 hard-coded values
					   //					   if((xigen45 > (0.079 + (4.21E-4 * crossingangle))) || (xigen56 > (0.074 + (6.6E-4 * crossingangle))))
					   //					   JH - testing with 2017preTS2 hard-coded values
					   if((xigen45 > (0.066 + (3.54E-4 * crossingangle))) || (xigen56 > (0.062 + (5.96E-4 * crossingangle))))
					     {
					       hmassmatchratiosigmcoutofacceptancemm->Fill((1 - (mydijet.M()/mppsmultmult->at(0))));
					       hymatchsigmcoutofacceptancemm->Fill(mydijet.Rapidity() - yppsmultmult->at(0));
					     }
					   else
					     {
					       hmassmatchratiosigmcinacceptancemm->Fill((1 - (mydijet.M()/mppsmultmult->at(0))));
					       hymatchsigmcinacceptancemm->Fill(mydijet.Rapidity() - yppsmultmult->at(0));
                                               if(match45 == 0 || match56 == 0)
                                                 {
						   hmassmatchratiosigmcinacceptancenomatchmm->Fill((1 - (mydijet.M()/mppsmultmult->at(0))));
						   hymatchsigmcinacceptancenomatchmm->Fill(mydijet.Rapidity() - yppsmultmult->at(0));
						 }
					     }
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
                               if(rotatedprunedmasses <= mrotatedcut)
                                 {
				   hmassvvantiacopww->Fill(mydijet.M());
				   hmj1antiacopww->Fill(jet_corrmass->at(indleading));
				   hmj2antiacopww->Fill(jet_corrmass->at(indsecond));
				   htau211antiacopww->Fill(taut21ddt1);
				   htau212antiacopww->Fill(taut21ddt2);
				   
				   if(mpp>0)
				     {
				       hmassmatchantiacopmmww->Fill(mppmm-mydijet.M());
				       hymatchantiacopmmww->Fill(yppmm-mydijet.Rapidity());
				       hmassmatchratioantiacopmmww->Fill(1 - (mydijet.M()/mppmm));
				       hmassrapiditymatchantiacopmmww->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

				       // Sideband background method
				       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
					  (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
					 npassantiacopsigregionww += 1.0*myweight;
				       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) || 
					  (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
					 npassantiacopnormregionww += 1.0*myweight ;
				     }
				 }
                               if(rotatedprunedmasses > mrotatedcut)
                                 {
                                   hmassvvantiacopzz->Fill(mydijet.M());
                                   hmj1antiacopzz->Fill(jet_corrmass->at(indleading));
                                   hmj2antiacopzz->Fill(jet_corrmass->at(indsecond));
                                   htau211antiacopzz->Fill(taut21ddt1);
                                   htau212antiacopzz->Fill(taut21ddt2);

                                   if(mpp>0)
                                     {
                                       hmassmatchantiacopmmzz->Fill(mppmm-mydijet.M());
                                       hymatchantiacopmmzz->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantiacopmmzz->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantiacopmmzz->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

                                       // Sideband background method                                                                                                                             
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantiacopsigregionzz += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantiacopnormregionzz += 1.0*myweight ;
                                     }
                                 }
			     } // anti-acoplanarity
			   // Anti pT balance                                                                                                                     
			   if((jet1.Pt()/jet2.Pt()) > ptbalcut &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
			      (acop < acopcut))
			     {
                               if(rotatedprunedmasses <= mrotatedcut)
                                 {
				   hmassvvantiptbalww->Fill(mydijet.M());
				   
				   if(mpp>0)
				     {
				       hmassmatchantiptbalmmww->Fill(mppmm-mydijet.M());
				       hymatchantiptbalmmww->Fill(yppmm-mydijet.Rapidity());
				       hmassmatchratioantiptbalmmww->Fill(1 - (mydijet.M()/mppmm));
				       hmassrapiditymatchantiptbalmmww->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				     }
				 }
                               if(rotatedprunedmasses > mrotatedcut)
                                 {
                                   hmassvvantiptbalzz->Fill(mydijet.M());

                                   if(mpp>0)
                                     {
                                       hmassmatchantiptbalmmzz->Fill(mppmm-mydijet.M());
                                       hymatchantiptbalmmzz->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantiptbalmmzz->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantiptbalmmzz->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
                                     }
                                 }
			     } // anti-pT balance
			   // Anti tau21                                                                                                                          
			   if((taut21ddt1 > tau21cut) && (taut21ddt2 > tau21cut) &&
			      (jet_corrmass->at(indleading) >= mwlowcut && jet_corrmass->at(indleading) <= mwhicut) && 
			      (jet_corrmass->at(indsecond) >= mwlowcut && jet_corrmass->at(indsecond) <= mwhicut) &&
			      (acop < acopcut) &&
			      (jet1.Pt()/jet2.Pt()) <  ptbalcut)
			     {
			       if(rotatedprunedmasses <= mrotatedcut)
				 {
				   hmassvvantitauww->Fill(mydijet.M());
				   hmj1antitauww->Fill(jet_corrmass->at(indleading));
				   hmj2antitauww->Fill(jet_corrmass->at(indsecond));
				   htau211antitauww->Fill(taut21ddt1);
				   htau212antitauww->Fill(taut21ddt2);
				   
				   if(mpp>0)
				     {
				       hmassmatchantitaummww->Fill(mppmm-mydijet.M());
				       hymatchantitaummww->Fill(yppmm-mydijet.Rapidity());
				       hmassmatchratioantitaummww->Fill(1 - (mydijet.M()/mppmm));
				       hmassrapiditymatchantitaummww->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

                                       // Sideband background method                                                                                                                             
				       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantitausigregionww += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantitaunormregionww += 1.0*myweight ;
				     }
				 }
                               if(rotatedprunedmasses > mrotatedcut)
                                 {
                                   hmassvvantitauzz->Fill(mydijet.M());
                                   hmj1antitauzz->Fill(jet_corrmass->at(indleading));
                                   hmj2antitauzz->Fill(jet_corrmass->at(indsecond));
                                   htau211antitauzz->Fill(taut21ddt1);
                                   htau212antitauzz->Fill(taut21ddt2);

                                   if(mpp>0)
                                     {
                                       hmassmatchantitaummzz->Fill(mppmm-mydijet.M());
                                       hymatchantitaummzz->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantitaummzz->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantitaummzz->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

                                       // Sideband background method                                                                                                                             
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantitausigregionzz += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantitaunormregionzz += 1.0*myweight ;
                                     }
                                 }
			     } // anti-tau21
			   // anti-pruned mass
			   if((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                              (jet_corrmass->at(indleading) < mwlowcut || jet_corrmass->at(indleading) > mwhicut) &&
                              (jet_corrmass->at(indsecond) < mwlowcut || jet_corrmass->at(indsecond) > mwhicut) &&
                              (acop < acopcut) &&
                              (jet1.Pt()/jet2.Pt()) <  ptbalcut)
                             {
                               if(rotatedprunedmasses <= mrotatedcut)
                                 {
				   hmassvvantiprunedww->Fill(mydijet.M());
				   hmj1antiprunedww->Fill(jet_corrmass->at(indleading));
				   hmj2antiprunedww->Fill(jet_corrmass->at(indsecond));
				   htau211antiprunedww->Fill(taut21ddt1);
				   htau212antiprunedww->Fill(taut21ddt2);
				   
				   if(mpp>0)
				     {
				       hmassmatchantiprunedmmww->Fill(mppmm-mydijet.M());
				       hymatchantiprunedmmww->Fill(yppmm-mydijet.Rapidity());
				       hmassmatchratioantiprunedmmww->Fill(1 - (mydijet.M()/mppmm));
				       hmassrapiditymatchantiprunedmmww->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

                                       // Sideband background method                                                                                                                             
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantimasssigregionww += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantimassnormregionww += 1.0*myweight ;
				     }
				 }
                               if(rotatedprunedmasses > mrotatedcut)
                                 {
                                   hmassvvantiprunedzz->Fill(mydijet.M());
                                   hmj1antiprunedzz->Fill(jet_corrmass->at(indleading));
                                   hmj2antiprunedzz->Fill(jet_corrmass->at(indsecond));
                                   htau211antiprunedzz->Fill(taut21ddt1);
                                   htau212antiprunedzz->Fill(taut21ddt2);

                                   if(mpp>0)
                                     {
                                       hmassmatchantiprunedmmzz->Fill(mppmm-mydijet.M());
                                       hymatchantiprunedmmzz->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantiprunedmmzz->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantiprunedmmzz->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());

                                       // Sideband background method                                                                                                                             
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantimasssigregionzz += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantimassnormregionzz += 1.0*myweight ;
                                     }
                                 }
                             }// anti-pruned mass
                           // anti-pruned mass - narrow region (55-215) 
                           if((taut21ddt1 <= tau21cut) && (taut21ddt2 <= tau21cut) &&
                              (jet_corrmass->at(indleading) < mwlowcut || jet_corrmass->at(indleading) > mwhicut) &&
                              (jet_corrmass->at(indsecond) < mwlowcut || jet_corrmass->at(indsecond) > mwhicut) &&
			      (jet_corrmass->at(indleading) >= mwlowpreselcut && jet_corrmass->at(indsecond) >= mwlowpreselcut) && 
			      (jet_corrmass->at(indleading) <= mwhipreselcut && jet_corrmass->at(indsecond) <= mwhipreselcut) && 
                              (acop < acopcut) &&
                              (jet1.Pt()/jet2.Pt()) <  ptbalcut)
                             {
                               if(rotatedprunedmasses <= mrotatedcut)
                                 {
                                   hmassvvantiprunednarrowww->Fill(mydijet.M());
                                   hmj1antiprunednarrowww->Fill(jet_corrmass->at(indleading));
                                   hmj2antiprunednarrowww->Fill(jet_corrmass->at(indsecond));
                                   htau211antiprunednarrowww->Fill(taut21ddt1);
                                   htau212antiprunednarrowww->Fill(taut21ddt2);
				   
                                   if(mpp>0)
                                     {
                                       hmassmatchantiprunednarrowmmww->Fill(mppmm-mydijet.M());
                                       hymatchantiprunednarrowmmww->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantiprunednarrowmmww->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantiprunednarrowmmww->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				       
                                       // Sideband background method                                                                                                                                   
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantimassnarrowsigregionww += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantimassnarrownormregionww += 1.0*myweight ;
                                     }
                                 }
                               if(rotatedprunedmasses > mrotatedcut)
                                 {
                                   hmassvvantiprunednarrowzz->Fill(mydijet.M());
                                   hmj1antiprunednarrowzz->Fill(jet_corrmass->at(indleading));
                                   hmj2antiprunednarrowzz->Fill(jet_corrmass->at(indsecond));
                                   htau211antiprunednarrowzz->Fill(taut21ddt1);
                                   htau212antiprunednarrowzz->Fill(taut21ddt2);
				   
                                   if(mpp>0)
                                     {
                                       hmassmatchantiprunednarrowmmzz->Fill(mppmm-mydijet.M());
                                       hymatchantiprunednarrowmmzz->Fill(yppmm-mydijet.Rapidity());
                                       hmassmatchratioantiprunednarrowmmzz->Fill(1 - (mydijet.M()/mppmm));
                                       hmassrapiditymatchantiprunednarrowmmzz->Fill(1 - (mydijet.M()/mppmm),yppmm-mydijet.Rapidity());
				       
                                       // Sideband background method                                                                                                                                     
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) <= massmatchcutksenia) &&
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) <= rapiditymatchcutksenia))
                                         npassantimassnarrowsigregionzz += 1.0*myweight;
                                       if((fabs(1 - (mydijet.M()/mppsmultmult->at(0))) > massmatchnormregion) ||
                                          (fabs(mydijet.Rapidity() - yppsmultmult->at(0)) > rapiditymatchnormregion))
                                         npassantimassnarrownormregionzz += 1.0*myweight ;
                                     }
                                 }
			     }// anti-pruned mass - narrow region (55-215)
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
				   if(fabs(ymatch) > rapiditymatchnormregion || fabs(massmatch) > massmatchnormregion)
				     {
				       if(rotatedprunedmasses <= mrotatedcut)
					 {
					   hmassrapiditymatchvetoorsignalregionww->Fill(massmatch,ymatch);
					   npassnonblindnormregionww += 1.0*myweight;
					 }
				       if(rotatedprunedmasses > mrotatedcut)
					 {
					   hmassrapiditymatchvetoorsignalregionzz->Fill(massmatch,ymatch);
					   npassnonblindnormregionzz += 1.0*myweight;
					 }
				       if(fabs(ymatch) > rapiditymatchnormregion && fabs(massmatch) > massmatchnormregion)
					 {
					   if(rotatedprunedmasses <= mrotatedcut)
					     hmassrapiditymatchvetosignalregionww->Fill(massmatch,ymatch);
					   if(rotatedprunedmasses > mrotatedcut)
                                             hmassrapiditymatchvetosignalregionzz->Fill(massmatch,ymatch);
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
       xishiftmultis45->clear();
       xishiftmultis56->clear();
       mppsmultmultshiftup->clear();
       mppsmultmultshiftdown->clear();
       yppsmultmultshiftup->clear();
       yppsmultmultshiftdown->clear();
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
   delete xishiftmultis45;
   delete xishiftmultis56;
   delete mppsmultmultshiftup;
   delete mppsmultmultshiftdown;
   delete yppsmultmultshiftup;
   delete yppsmultmultshiftdown;

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
   if(samplenumber == 21)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W2E-6_2017preTS2.root","RECREATE");
   if(samplenumber == 22)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W5E-6_2017preTS2.root","RECREATE");
   if(samplenumber == 23)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2017preTS2.root","RECREATE");


   if(samplenumber == 40)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W1E-6_2017postTS2.root","RECREATE");
   if(samplenumber == 42)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W5E-6_2017postTS2.root","RECREATE");
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
   if(samplenumber == 122)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W5E-6_2016preTS2.root","RECREATE");
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
   if(samplenumber == 222)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWA0W5E-6_2018.root","RECREATE");
   if(samplenumber == 223)
     fx = new TFile("vars_cuts_ntupleULReMiniv4finalWithJERandMultiCand_exclWWACW2E-5_2018.root","RECREATE");

   if(samplenumber == 999)
     //     fx = new TFile("vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_exclWWA0W1E-6_2017preTS2.root","RECREATE");
     //     fx = new TFile("vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_exclWWA0W1E-6_2018A.root","RECREATE");
     fx = new TFile("vars_cuts_ntupleULReMiniv5finalWithAndreasMixingEfficiencies_exclWWA0W1E-6_2016B.root","RECREATE");

   ofs.close();

   fx->mkdir("PreselectionAndControl");
   fx->mkdir("JetSubstructure");
   fx->mkdir("Sidebands");
   fx->mkdir("Signal");
   fx->mkdir("SingleProtonDistributions");
   fx->mkdir("MCGenDistributions");

   fx->cd("PreselectionAndControl");
   hmjjdat->Write();
   hyjjdat->Write();
   hptdat1->Write();
   hptdat2->Write();
   hetadat1->Write();
   hetadat2->Write();
   hphidat1->Write();
   hphidat2->Write();
   hdeta->Write();
   hprunedrotatedjjdat->Write();
   hacopdat->Write();
   hmjjdatpfjet->Write();
   hmjjdatpfhttrim->Write();
   hmjjdatpfjettrim->Write();
   hnvtx->Write();
   hcrossingangle->Write();
   hptratio->Write();

   hmppmulti->Write();
   hyppmulti->Write();
   hdtmulti->Write(); 

   hmassvvsignalww->Write();
   hywwsignalww->Write();
   hmassvvsignalzz->Write();
   hywwsignalzz->Write();

   hmyppsingle->Write();
   hmyppmulti->Write();
   hmyjjdat->Write();
   xijets45->Write();
   xijets56->Write();

   hmasscorrpreseldatmult->Write();
   hycorrpreseldatmult->Write();
   dymassratiocorrpreseldatmult->Write();

   fx->cd("JetSubstructure");
   hmjdat1->Write();
   htau21dat1->Write();
   hmjdat2->Write();
   htau21dat2->Write();
   htau21ddtdat1->Write();
   htau21ddtdat2->Write();
   tau21vrhoprime1->Write();
   tau21vrhoprime2->Write();


   fx->cd("Sidebands");
   hmassmatchantitaummww->Write();
   hymatchantitaummww->Write();
   hmassmatchratioantitaummww->Write();
   hmassmatchantiprunedmmww->Write();
   hymatchantiprunedmmww->Write();
   hmassmatchratioantiprunedmmww->Write();
   hmassmatchantiacopmmww->Write();
   hymatchantiacopmmww->Write();
   hmassmatchratioantiacopmmww->Write();
   hmassmatchantiptbalmmww->Write();
   hymatchantiptbalmmww->Write();
   hmassmatchratioantiptbalmmww->Write();
   hmassmatchantitaummzz->Write();
   hymatchantitaummzz->Write();
   hmassmatchratioantitaummzz->Write();
   hmassmatchantiprunedmmzz->Write();
   hymatchantiprunedmmzz->Write();
   hmassmatchratioantiprunedmmzz->Write();
   hmassmatchantiacopmmzz->Write();
   hymatchantiacopmmzz->Write();
   hmassmatchratioantiacopmmzz->Write();
   hmassmatchantiptbalmmzz->Write();
   hymatchantiptbalmmzz->Write();
   hmassmatchratioantiptbalmmzz->Write();
   hmassmatchantiprunednarrowmmww->Write();
   hymatchantiprunednarrowmmww->Write();
   hmassmatchratioantiprunednarrowmmww->Write();
   hmassmatchantiprunednarrowmmzz->Write();
   hymatchantiprunednarrowmmzz->Write();
   hmassmatchratioantiprunednarrowmmzz->Write();


   hmassvvantitauww->Write();
   hmassvvantiacopww->Write();
   hmassvvantiptbalww->Write();
   hmassvvantiprunedww->Write();
   hmassvvantiprunednarrowww->Write();
   hmj1antiacopww->Write();
   hmj2antiacopww->Write();
   htau211antiacopww->Write();
   htau212antiacopww->Write();
   hmj1antitauww->Write();
   hmj2antitauww->Write();
   htau211antitauww->Write();
   htau212antitauww->Write();
   hmj1antiprunedww->Write();
   hmj2antiprunedww->Write();
   htau211antiprunedww->Write();
   htau212antiprunedww->Write();
   hmj1antiprunednarrowww->Write();
   hmj2antiprunednarrowww->Write();
   htau211antiprunednarrowww->Write();
   htau212antiprunednarrowww->Write();

   hmassvvantitauzz->Write();
   hmassvvantiacopzz->Write();
   hmassvvantiptbalzz->Write();
   hmassvvantiprunedzz->Write();
   hmassvvantiprunednarrowzz->Write();
   hmj1antiacopzz->Write();
   hmj2antiacopzz->Write();
   htau211antiacopzz->Write();
   htau212antiacopzz->Write();
   hmj1antitauzz->Write();
   hmj2antitauzz->Write();
   htau211antitauzz->Write();
   htau212antitauzz->Write();
   hmj1antiprunedzz->Write();
   hmj2antiprunedzz->Write();
   htau211antiprunedzz->Write();
   htau212antiprunedzz->Write();
   hmj1antiprunednarrowzz->Write();
   hmj2antiprunednarrowzz->Write();
   htau211antiprunednarrowzz->Write();
   htau212antiprunednarrowzz->Write();

   hmassvvsignalww->Write();
   hywwsignalww->Write();
   hmassvvsignalzz->Write();
   hywwsignalzz->Write();

   hmassrapiditymatchantiacopmmww->Write();
   hmassrapiditymatchantiptbalmmww->Write();
   hmassrapiditymatchantitaummww->Write();
   hmassrapiditymatchantiprunedmmww->Write();
   hmassrapiditymatchantiprunednarrowmmww->Write();
   hmassrapiditymatchantiacopmmzz->Write();
   hmassrapiditymatchantiptbalmmzz->Write();
   hmassrapiditymatchantitaummzz->Write();
   hmassrapiditymatchantiprunedmmzz->Write();
   hmassrapiditymatchantiprunednarrowmmzz->Write();

   hmassrapiditymatchvetosignalregionww->Write();
   hmassrapiditymatchvetoorsignalregionww->Write();
   hmassrapiditymatchvetosignalregionzz->Write();
   hmassrapiditymatchvetoorsignalregionzz->Write();

   fx->cd("Signal");
   hmassmatchsigmcmmww->Write();
   hymatchsigmcmmww->Write();
   hmassmatchratiosigmcmmww->Write();
   hmassmatchsigmcmmzz->Write();
   hymatchsigmcmmzz->Write();
   hmassmatchratiosigmcmmzz->Write();

   hmassmatchratiosigmcmmshiftupww->Write();
   hmassmatchratiosigmcmmshiftdownww->Write();
   hymatchsigmcmmshiftupww->Write();
   hymatchsigmcmmshiftdownww->Write();
   hmassmatchratiosigmcmmshiftupzz->Write();
   hmassmatchratiosigmcmmshiftdownzz->Write();
   hymatchsigmcmmshiftupzz->Write();
   hymatchsigmcmmshiftdownzz->Write();

   hmassmatchratiosigmcmultww->Write();
   hymatchsigmcmultww->Write();
   hmasscorrsigmcmultww->Write();
   hycorrsigmcmultww->Write();
   hmasscorrsigmcmulttruthmatchedww->Write();
   hmassmatchratiosigmcmultzz->Write();
   hymatchsigmcmultzz->Write();
   hmasscorrsigmcmultzz->Write();
   hycorrsigmcmultzz->Write();
   hmasscorrsigmcmulttruthmatchedzz->Write();


   fx->cd("SingleProtonDistributions");
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

   fx->cd("MCGenDistributions");
   resxijets45->Write();
   resxijets56->Write();
   resxijetscorr45->Write();
   resxijetscorr56->Write();

   hgenxinomatch->Write();
   hmassmatchratiosigmcoutofacceptancemm->Write();
   hmassmatchratiosigmcinacceptancemm->Write();
   hmassmatchratiosigmcinacceptancenomatchmm->Write();
   hymatchsigmcoutofacceptancemm->Write();
   hymatchsigmcinacceptancemm->Write();
   hymatchsigmcinacceptancenomatchmm->Write();


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

   std::cout << std::endl << std::endl << "=====================================================" << std::endl;
   std::cout << "Cut flow" << std::endl;
   std::cout <<  "=====================================================" << std::endl;
   std::cout << "Passing preselection = " << npasspresel << std::endl
	     << "Passing dijet kinematics = " << npassdijetkine << std::endl
	     << "Passing jet substructure = " << npassjetsubstr << std::endl
	     << "Passing xi(jets) = " << npassjetxi << std::endl
	     << "Passing 2 PPS multi-RP protons = " << npasspps << std::endl
	     << "\t(After preselection and before other central cuts = " << npassppsbeforecuts << std::endl
	     << "Passing pp-diboson matching = " << npassppsmatchksenia << std::endl
	     << "Passing WW channel cut = " << npassppsmatchkseniaww << std::endl
	     << "Passing ZZ channel cut = " << npassppsmatchkseniazz << std::endl;

   std::cout << std::endl << std::endl << "=====================================================" << std::endl;
   std::cout << "Sideband background method yields" << std::endl;
   std::cout <<  "=====================================================" << std::endl;
   
   std::cout << "Anti-acoplanarity" << std::endl
	     << "\t WW norm. region = " << npassantiacopnormregionww << ", WW sig. region = " << npassantiacopsigregionww << std::endl
	     << "\t ZZ norm. region = " << npassantiacopnormregionzz << ", ZZ sig. region = " << npassantiacopsigregionzz << std::endl;
   std::cout << "Anti-tau21" << std::endl
             << "\t WW norm. region = " << npassantitaunormregionww << ", WW sig. region = " << npassantitausigregionww << std::endl
             << "\t ZZ norm. region = " << npassantitaunormregionzz << ", ZZ sig. region = " << npassantitausigregionzz << std::endl;
   std::cout << "Anti-pruned mass" << std::endl
             << "\t WW norm. region = " << npassantimassnormregionww << ", WW sig. region = " << npassantimasssigregionww << std::endl
             << "\t ZZ norm. region = " << npassantimassnormregionzz << ", ZZ sig. region = " << npassantimasssigregionzz << std::endl;
   std::cout << "Anti-pruned mass (narrow region)" << std::endl
             << "\t WW norm. region = " << npassantimassnarrownormregionww << ", WW sig. region = " << npassantimassnarrowsigregionww << std::endl
             << "\t ZZ norm. region = " << npassantimassnarrownormregionzz << ", ZZ sig. region = " << npassantimassnarrowsigregionzz << std::endl;
   std::cout << "Non-blinded normalization region" << std::endl
	     << "\t WW norm. region = " << npassnonblindnormregionww << std::endl
	     << "\t ZZ norm. region = " << npassnonblindnormregionzz << std::endl;
 
}
