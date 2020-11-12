#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#ifndef PPSProtonEfficiency_h
#define PPSProtonEfficiency_h

class PPSProtonEfficiency {
 public :

  // Efficiency correction histograms                                                                                                                                            
  TH2F *hstreff2016B45near, *hstreff2016C45near, *hstreff2016G45near, *hstreff2016H45near;
  TH2F *hstreff2016B56near, *hstreff2016C56near, *hstreff2016G56near, *hstreff2016H56near;
  TH2F *hstreff2016PreTS245near, *hstreff2016PostTS245near;
  TH2F *hstreff2016PreTS256near, *hstreff2016PostTS256near;
  TH2F *hstreff2016B45far, *hstreff2016C45far, *hstreff2016G45far, *hstreff2016H45far;
  TH2F *hstreff2016B56far, *hstreff2016C56far, *hstreff2016G56far, *hstreff2016H56far;
  TH2F *hstreff2016PreTS245far, *hstreff2016PostTS245far;
  TH2F *hstreff2016PreTS256far, *hstreff2016PostTS256far;


  TH2F *hpixeff2017B45, *hpixeff2017C145, *hpixeff2017C245, *hpixeff2017D45, *hpixeff2017E45, *hpixeff2017F145, *hpixeff2017F245, *hpixeff2017F345;
  TH2F *hpixeff2017B56, *hpixeff2017C156, *hpixeff2017C256, *hpixeff2017D56, *hpixeff2017E56, *hpixeff2017F156, *hpixeff2017F256, *hpixeff2017F356;
  TH2F *hpixeff2017PreTS245, *hpixeff2017PostTS245;
  TH2F *hpixeff2017PreTS256, *hpixeff2017PostTS256;
  
  TH2F *hstreff2017B45, *hstreff2017C45, *hstreff2017D45, *hstreff2017E45, *hstreff2017F45;
  TH2F *hstreff2017B56, *hstreff2017C56, *hstreff2017D56, *hstreff2017E56, *hstreff2017F56;
  TH2F *hstreff2017PreTS245, *hstreff2017PostTS245;
  TH2F *hstreff2017PreTS256, *hstreff2017PostTS256;
  
  TH1F *hmultistreff2016B45near, *hmultistreff2016C45near, *hmultistreff2016G45near, *hmultistreff2016H45near;
  TH1F *hmultistreff2016B56near, *hmultistreff2016C56near, *hmultistreff2016G56near, *hmultistreff2016H56near;
  TH1F *hmultistreff2016PreTS245near, *hmultistreff2016PostTS245near;
  TH1F *hmultistreff2016PreTS256near, *hmultistreff2016PostTS256near;
  TH1F *hmultistreff2016B45far, *hmultistreff2016C45far, *hmultistreff2016G45far, *hmultistreff2016H45far;
  TH1F *hmultistreff2016B56far, *hmultistreff2016C56far, *hmultistreff2016G56far, *hmultistreff2016H56far;
  TH1F *hmultistreff2016PreTS245far, *hmultistreff2016PostTS245far;
  TH1F *hmultistreff2016PreTS256far, *hmultistreff2016PostTS256far;

  TH1F *hmultistreff2017B45, *hmultistreff2017C45, *hmultistreff2017D45, *hmultistreff2017E45, *hmultistreff2017F45;
  TH1F *hmultistreff2017B56, *hmultistreff2017C56, *hmultistreff2017D56, *hmultistreff2017E56, *hmultistreff2017F56;
  TH1F *hmultistreff2017PreTS245, *hmultistreff2017PostTS245;
  TH1F *hmultistreff2017PreTS256, *hmultistreff2017PostTS256;
  
  TRandom *rnd;
  
  TString erastring;

  // xi systematics shifts
  TGraph *xisyst452016preTS2, *xisyst562016preTS2;
  TGraph *xisyst452017preTS2, *xisyst562017preTS2, *xisyst452017postTS2, *xisyst562017postTS2;
  TGraph *xisyst452018postTS2, *xisyst562018postTS2;

  // Lumis for weighting
  Float_t lumi2016B = 4.718;
  Float_t lumi2016C = 1.631;
  Float_t lumi2016G = 3.667;
  Float_t lumi2016H = 5.095;

  Float_t lumi2017B = 2.361;
  Float_t lumi2017C1 = 5.3;
  Float_t lumi2017C2 = 3.3;
  Float_t lumi2017C = 8.577;
  Float_t lumi2017D = 4.075;
  Float_t lumi2017E = 8.948;
  Float_t lumi2017F1 = 1.7;
  Float_t lumi2017F2 = 7.9;
  Float_t lumi2017F3 = 3.6;
  Float_t lumi2017F = 13.214;


  PPSProtonEfficiency();
  virtual ~PPSProtonEfficiency();
  virtual Float_t GetMultiRPEfficiency(Float_t trackx1, Float_t tracky1, Float_t trackx2, Float_t tracky2, 
				       Int_t trackrpid1, Int_t trackrpid2, TString era);
  virtual bool GetMultiRPAcceptRejectDecision(Float_t trackx1, Float_t tracky1, Float_t trackx2, Float_t tracky2, 
					      Int_t trackrpid1, Int_t trackrpid2, TString era);
  //  virtual Float_t GetMultiRPXiScaleUncertainty(Int_t arm, Float_t xi, TString era);
};

#endif

#ifdef PPSProtonEfficiency_cxx
PPSProtonEfficiency::PPSProtonEfficiency ()
{
  // Setup for efficiency corrections ("killing")                                                                                                                                      
  rnd = new TRandom();
  rnd->SetSeed(123456);

  // Pixels - lumi-weighted rad. damage + multi-RP averages for pre- and post-TS2 2017
  TFile *fpixeff = TFile::Open("pixelEfficiencies_multiRP.root");
  hpixeff2017B45 = (TH2F *)fpixeff->Get("Pixel/2017/2017B/h45_220_2017B_all_2D"); // 2.4fb                                                
  hpixeff2017B56 = (TH2F *)fpixeff->Get("Pixel/2017/2017B/h56_220_2017B_all_2D");
  hpixeff2017C145 = (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h45_220_2017C1_all_2D"); // 5.3fb                                             
  hpixeff2017C156 = (TH2F *)fpixeff->Get("Pixel/2017/2017C1/h56_220_2017C1_all_2D");
  hpixeff2017C245 = (TH2F *)fpixeff->Get("Pixel/2017/2017C2/h45_220_2017C2_all_2D"); // 3.3fb                                             
  hpixeff2017C256 = (TH2F *)fpixeff->Get("Pixel/2017/2017C2/h56_220_2017C2_all_2D");
  hpixeff2017D45 = (TH2F *)fpixeff->Get("Pixel/2017/2017D/h45_220_2017D_all_2D"); // 4.075fb                                              
  hpixeff2017D56 = (TH2F *)fpixeff->Get("Pixel/2017/2017D/h56_220_2017D_all_2D");
  hpixeff2017E45 = (TH2F *)fpixeff->Get("Pixel/2017/2017E/h45_220_2017E_all_2D"); // 9fb                                                  
  hpixeff2017E56 = (TH2F *)fpixeff->Get("Pixel/2017/2017E/h56_220_2017E_all_2D");
  hpixeff2017F145 = (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h45_220_2017F1_all_2D"); // 1.7fb                                             
  hpixeff2017F156 = (TH2F *)fpixeff->Get("Pixel/2017/2017F1/h56_220_2017F1_all_2D");
  hpixeff2017F245 = (TH2F *)fpixeff->Get("Pixel/2017/2017F2/h45_220_2017F2_all_2D"); // 7.9fb                                             
  hpixeff2017F256 = (TH2F *)fpixeff->Get("Pixel/2017/2017F2/h56_220_2017F2_all_2D");
  hpixeff2017F345 = (TH2F *)fpixeff->Get("Pixel/2017/2017F3/h45_220_2017F3_all_2D"); // 1.7fb                                             
  hpixeff2017F356 = (TH2F *)fpixeff->Get("Pixel/2017/2017F3/h56_220_2017F3_all_2D");

  hpixeff2017B45->Scale(lumi2017B/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017B56->Scale(lumi2017B/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017C145->Scale(lumi2017C1/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017C156->Scale(lumi2017C1/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017C245->Scale(lumi2017C2/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017C256->Scale(lumi2017C2/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017D45->Scale(lumi2017D/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017D56->Scale(lumi2017D/(lumi2017B+lumi2017C1+lumi2017C2+lumi2017D));
  hpixeff2017PreTS245 = (TH2F *)hpixeff2017B45->Clone("hpixeff2017PreTS245");
  hpixeff2017PreTS256 = (TH2F *)hpixeff2017B56->Clone("hpixeff2017PreTS256");
  hpixeff2017PreTS245->Add(hpixeff2017C145);
  hpixeff2017PreTS256->Add(hpixeff2017C156);
  hpixeff2017PreTS245->Add(hpixeff2017C245);
  hpixeff2017PreTS256->Add(hpixeff2017C256);
  hpixeff2017PreTS245->Add(hpixeff2017D45);
  hpixeff2017PreTS256->Add(hpixeff2017D56);
  
  hpixeff2017E45->Scale(lumi2017E/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017E56->Scale(lumi2017E/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F145->Scale(lumi2017F1/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F156->Scale(lumi2017F1/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F245->Scale(lumi2017F2/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F256->Scale(lumi2017F2/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F345->Scale(lumi2017F3/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017F356->Scale(lumi2017F3/(lumi2017E+lumi2017F1+lumi2017F2+lumi2017F3));
  hpixeff2017PostTS245 = (TH2F *)hpixeff2017E45->Clone("hpixeff2017PostTS245");
  hpixeff2017PostTS256 = (TH2F *)hpixeff2017E56->Clone("hpixeff2017PostTS256");
  hpixeff2017PostTS245->Add(hpixeff2017F145);
  hpixeff2017PostTS256->Add(hpixeff2017F156);
  hpixeff2017PostTS245->Add(hpixeff2017F245);
  hpixeff2017PostTS256->Add(hpixeff2017F256);
  hpixeff2017PostTS245->Add(hpixeff2017F345);
  hpixeff2017PostTS256->Add(hpixeff2017F356);
  
  // Strips
  TFile *fstripeff = TFile::Open("PreliminaryEfficiencies_July132020_1D2DMultiTrack.root");

  // Strips - lumi-weighted rad. damage averages for pre-TS2 2016
  hstreff2016B45near = (TH2F *)fstripeff->Get("Strips/2016/2016B/h45_2016B_RP2_all_2D");
  hstreff2016C45near = (TH2F *)fstripeff->Get("Strips/2016/2016C/h45_2016C_RP2_all_2D");
  hstreff2016G45near = (TH2F *)fstripeff->Get("Strips/2016/2016G/h45_2016G_RP2_all_2D");
  hstreff2016B56near = (TH2F *)fstripeff->Get("Strips/2016/2016B/h56_2016B_RP102_all_2D");
  hstreff2016C56near = (TH2F *)fstripeff->Get("Strips/2016/2016C/h56_2016C_RP102_all_2D");
  hstreff2016G56near = (TH2F *)fstripeff->Get("Strips/2016/2016G/h56_2016G_RP102_all_2D");
  hstreff2016B45far = (TH2F *)fstripeff->Get("Strips/2016/2016B/h45_2016B_RP3_all_2D");
  hstreff2016C45far = (TH2F *)fstripeff->Get("Strips/2016/2016C/h45_2016C_RP3_all_2D");
  hstreff2016G45far = (TH2F *)fstripeff->Get("Strips/2016/2016G/h45_2016G_RP3_all_2D");
  hstreff2016B56far = (TH2F *)fstripeff->Get("Strips/2016/2016B/h56_2016B_RP103_all_2D");
  hstreff2016C56far = (TH2F *)fstripeff->Get("Strips/2016/2016C/h56_2016C_RP103_all_2D");
  hstreff2016G56far = (TH2F *)fstripeff->Get("Strips/2016/2016G/h56_2016G_RP103_all_2D");

  hstreff2016B45near->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016B56near->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016C45near->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016C56near->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016G45near->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016G56near->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016PreTS245near = (TH2F *)hstreff2016B45near->Clone("hstreff2016PreTS245near");
  hstreff2016PreTS256near = (TH2F *)hstreff2016B56near->Clone("hstreff2016PreTS256near");
  hstreff2016PreTS245near->Add(hstreff2016C45near); hstreff2016PreTS245near->Add(hstreff2016G45near);
  hstreff2016PreTS256near->Add(hstreff2016C56near); hstreff2016PreTS256near->Add(hstreff2016G56near);
  hstreff2016B45far->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016B56far->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016C45far->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016C56far->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016G45far->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016G56far->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hstreff2016PreTS245far = (TH2F *)hstreff2016B45far->Clone("hstreff2016PreTS245far");
  hstreff2016PreTS256far = (TH2F *)hstreff2016B56far->Clone("hstreff2016PreTS256far");
  hstreff2016PreTS245far->Add(hstreff2016C45far); hstreff2016PreTS245far->Add(hstreff2016G45far);
  hstreff2016PreTS256far->Add(hstreff2016C56far); hstreff2016PreTS256far->Add(hstreff2016G56far);


  // Strips - lumi-weighted multi-track averages for pre-TS2 2016                                                                                                      
  hmultistreff2016B45near = (TH1F *)fstripeff->Get("Strips/2016/2016B/h45multitrackeff_2016B_avg_RP2");
  hmultistreff2016C45near = (TH1F *)fstripeff->Get("Strips/2016/2016C/h45multitrackeff_2016C_avg_RP2");
  hmultistreff2016G45near = (TH1F *)fstripeff->Get("Strips/2016/2016G/h45multitrackeff_2016G_avg_RP2");
  hmultistreff2016B56near = (TH1F *)fstripeff->Get("Strips/2016/2016B/h56multitrackeff_2016B_avg_RP102");
  hmultistreff2016C56near = (TH1F *)fstripeff->Get("Strips/2016/2016C/h56multitrackeff_2016C_avg_RP102");
  hmultistreff2016G56near = (TH1F *)fstripeff->Get("Strips/2016/2016G/h56multitrackeff_2016G_avg_RP102");

  hmultistreff2016B45far = (TH1F *)fstripeff->Get("Strips/2016/2016B/h45multitrackeff_2016B_avg_RP3");
  hmultistreff2016C45far = (TH1F *)fstripeff->Get("Strips/2016/2016C/h45multitrackeff_2016C_avg_RP3");
  hmultistreff2016G45far = (TH1F *)fstripeff->Get("Strips/2016/2016G/h45multitrackeff_2016G_avg_RP3");
  hmultistreff2016B56far = (TH1F *)fstripeff->Get("Strips/2016/2016B/h56multitrackeff_2016B_avg_RP103");
  hmultistreff2016C56far = (TH1F *)fstripeff->Get("Strips/2016/2016C/h56multitrackeff_2016C_avg_RP103");
  hmultistreff2016G56far = (TH1F *)fstripeff->Get("Strips/2016/2016G/h56multitrackeff_2016G_avg_RP103");

  hmultistreff2016B45near->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016B56near->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016C45near->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016C56near->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016G45near->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016G56near->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016PreTS245near = (TH1F *)hmultistreff2016B45near->Clone("hmultistreff2016PreTS245near");
  hmultistreff2016PreTS256near = (TH1F *)hmultistreff2016B56near->Clone("hmultistreff2016PreTS256near");
  hmultistreff2016PreTS245near->Add(hmultistreff2016C45near); hmultistreff2016PreTS245near->Add(hmultistreff2016G45near);
  hmultistreff2016PreTS256near->Add(hmultistreff2016C56near); hmultistreff2016PreTS256near->Add(hmultistreff2016G56near);
  hmultistreff2016B45far->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016B56far->Scale(lumi2016B/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016C45far->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016C56far->Scale(lumi2016C/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016G45far->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016G56far->Scale(lumi2016G/(lumi2016B+lumi2016C+lumi2016G));
  hmultistreff2016PreTS245far = (TH1F *)hmultistreff2016B45far->Clone("hmultistreff2016PreTS245far");
  hmultistreff2016PreTS256far = (TH1F *)hmultistreff2016B56far->Clone("hmultistreff2016PreTS256far");
  hmultistreff2016PreTS245far->Add(hmultistreff2016C45far); hmultistreff2016PreTS245far->Add(hmultistreff2016G45far);
  hmultistreff2016PreTS256far->Add(hmultistreff2016C56far); hmultistreff2016PreTS256far->Add(hmultistreff2016G56far);


  // Strips - lumi-weighted rad. damage averages for pre- and post-TS2 2017                                                                                                      
  hstreff2017B45 = (TH2F *)fstripeff->Get("Strips/2017/2017B/h45_2017B_all_2D");
  hstreff2017C45 = (TH2F *)fstripeff->Get("Strips/2017/2017C/h45_2017C_all_2D");
  hstreff2017D45 = (TH2F *)fstripeff->Get("Strips/2017/2017D/h45_2017D_all_2D");
  hstreff2017E45 = (TH2F *)fstripeff->Get("Strips/2017/2017E/h45_2017E_all_2D");
  hstreff2017F45 = (TH2F *)fstripeff->Get("Strips/2017/2017F/h45_2017F_all_2D");
  hstreff2017B56 = (TH2F *)fstripeff->Get("Strips/2017/2017B/h56_2017B_all_2D");
  hstreff2017C56 = (TH2F *)fstripeff->Get("Strips/2017/2017C/h56_2017C_all_2D");
  hstreff2017D56 = (TH2F *)fstripeff->Get("Strips/2017/2017D/h56_2017D_all_2D");
  hstreff2017E56 = (TH2F *)fstripeff->Get("Strips/2017/2017E/h56_2017E_all_2D");
  hstreff2017F56 = (TH2F *)fstripeff->Get("Strips/2017/2017F/h56_2017F_all_2D");
  
  hstreff2017B45->Scale(lumi2017B/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017B56->Scale(lumi2017B/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017C45->Scale(lumi2017C/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017C56->Scale(lumi2017C/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017D45->Scale(lumi2017D/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017D56->Scale(lumi2017D/(lumi2017B+lumi2017C+lumi2017D));
  hstreff2017PreTS245 = (TH2F *)hstreff2017B45->Clone("hstreff2017PreTS245");
  hstreff2017PreTS256 = (TH2F *)hstreff2017B56->Clone("hstreff2017PreTS256");
  hstreff2017PreTS245->Add(hstreff2017C45); hstreff2017PreTS245->Add(hstreff2017D45);
  hstreff2017PreTS256->Add(hstreff2017C56); hstreff2017PreTS256->Add(hstreff2017D56);
  
  hstreff2017E45->Scale(lumi2017E/(lumi2017E+lumi2017F));
  hstreff2017E56->Scale(lumi2017E/(lumi2017E+lumi2017F));
  hstreff2017F45->Scale(lumi2017F/(lumi2017E+lumi2017F));
  hstreff2017F56->Scale(lumi2017F/(lumi2017E+lumi2017F));
  hstreff2017PostTS245 = (TH2F *)hstreff2017E45->Clone("hstreff2017PostTS245");
  hstreff2017PostTS256 = (TH2F *)hstreff2017E56->Clone("hstreff2017PostTS256");
  hstreff2017PostTS245->Add(hstreff2017F45);
  hstreff2017PostTS256->Add(hstreff2017F56);
  
  // Strips - lumi-weighted multi-track averages for pre- and post-TS2 2017
  hmultistreff2017B45 = (TH1F *)fstripeff->Get("Strips/2017/2017B/h45multitrackeff_2017B_avg_RP3");
  hmultistreff2017C45 = (TH1F *)fstripeff->Get("Strips/2017/2017C/h45multitrackeff_2017C_avg_RP3");
  hmultistreff2017D45 = (TH1F *)fstripeff->Get("Strips/2017/2017D/h45multitrackeff_2017D_avg_RP3");
  hmultistreff2017E45 = (TH1F *)fstripeff->Get("Strips/2017/2017E/h45multitrackeff_2017E_avg_RP3");
  hmultistreff2017F45 = (TH1F *)fstripeff->Get("Strips/2017/2017F/h45multitrackeff_2017F_avg_RP3");
  hmultistreff2017B56 = (TH1F *)fstripeff->Get("Strips/2017/2017B/h56multitrackeff_2017B_avg_RP103");
  hmultistreff2017C56 = (TH1F *)fstripeff->Get("Strips/2017/2017C/h56multitrackeff_2017C_avg_RP103");
  hmultistreff2017D56 = (TH1F *)fstripeff->Get("Strips/2017/2017D/h56multitrackeff_2017D_avg_RP103");
  hmultistreff2017E56 = (TH1F *)fstripeff->Get("Strips/2017/2017E/h56multitrackeff_2017E_avg_RP103");
  hmultistreff2017F56 = (TH1F *)fstripeff->Get("Strips/2017/2017F/h56multitrackeff_2017F_avg_RP103");
  
  hmultistreff2017B45->Scale(lumi2017B/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017B56->Scale(lumi2017B/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017C45->Scale(lumi2017C/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017C56->Scale(lumi2017C/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017D45->Scale(lumi2017D/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017D56->Scale(lumi2017D/(lumi2017B+lumi2017C+lumi2017D));
  hmultistreff2017PreTS245 = (TH1F *)hmultistreff2017B45->Clone("hmultistreff2017PreTS245");
  hmultistreff2017PreTS256 = (TH1F *)hmultistreff2017B56->Clone("hmultistreff2017PreTS256");
  hmultistreff2017PreTS245->Add(hmultistreff2017C45); hmultistreff2017PreTS245->Add(hmultistreff2017D45);
  hmultistreff2017PreTS256->Add(hmultistreff2017C56); hmultistreff2017PreTS256->Add(hmultistreff2017D56);
  
  hmultistreff2017E45->Scale(lumi2017E/(lumi2017E+lumi2017F));
  hmultistreff2017E56->Scale(lumi2017E/(lumi2017E+lumi2017F));
  hmultistreff2017F45->Scale(lumi2017F/(lumi2017E+lumi2017F));
  hmultistreff2017F56->Scale(lumi2017F/(lumi2017E+lumi2017F));
  hmultistreff2017PostTS245 = (TH1F *)hmultistreff2017E45->Clone("hmultistreff2017PostTS245");
  hmultistreff2017PostTS256 = (TH1F *)hmultistreff2017E56->Clone("hmultistreff2017PostTS256");
  hmultistreff2017PostTS245->Add(hmultistreff2017F45);
  hmultistreff2017PostTS256->Add(hmultistreff2017F56);

  std::cout << "PPSProtonEfficiency: Finished loading all available efficiency tables" << std::endl;

  // xi systematic shifts
  // Uncomment when officially released
  /*
  TFile *fxisyst = TFile::Open("xi_uncertainty.root");
  xisyst452016preTS2 = (TGraph *)fxisyst->Get("2016_preTS2/multi rp-0/g_xi_unc_vs_xi");
  xisyst562016preTS2 = (TGraph *)fxisyst->Get("2016_preTS2/multi rp-1/g_xi_unc_vs_xi");
  xisyst452017preTS2 = (TGraph *)fxisyst->Get("2017_preTS2/multi rp-0/g_xi_unc_vs_xi");
  xisyst562017preTS2 = (TGraph *)fxisyst->Get("2017_preTS2/multi rp-1/g_xi_unc_vs_xi");
  xisyst452017postTS2 = (TGraph *)fxisyst->Get("2017_postTS2/multi rp-0/g_xi_unc_vs_xi");
  xisyst562017postTS2 = (TGraph *)fxisyst->Get("2017_postTS2/multi rp-1/g_xi_unc_vs_xi");
  xisyst452018postTS2 = (TGraph *)fxisyst->Get("2018_postTS2/multi rp-0/g_xi_unc_vs_xi");
  xisyst562018postTS2 = (TGraph *)fxisyst->Get("2018_postTS2/multi rp-1/g_xi_unc_vs_xi");
  */
}

PPSProtonEfficiency::~PPSProtonEfficiency()
{
}

#endif // #ifdef PPSProtonEfficiency_cxx
