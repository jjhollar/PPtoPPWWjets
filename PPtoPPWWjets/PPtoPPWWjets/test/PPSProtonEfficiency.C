/*                                                                                                                                        
 * This macro retrieves the efficiencies for multi-RP protons, for all effects currently available. 
 * It either returns the numerical value of the efficiency for weighting, or an accept/reject flag. 
 * The efficiencies used here are the luminosity-weighted average of the full pre- and post-TS2 eras 
 * for 2016 and 2017. The pixel and strip efficiency histograms are assumed to be present in the 
 * directory from which the macro is run: https://twiki.cern.ch/twiki/bin/view/CMS/TaggedProtonsGettingStarted#Efficiency_corrections
 * 
 * Usage:
 * [0] .L PPSProtonEfficiency.C
 * [1] PPSProtonEfficiency eff
 * [2] eff.GetMultiRPEfficiency(contributing track1 x, contributing track1 y, contributing track2 x, contributing track2 y, 
                                contributing track1 RPID, contributing track2 RPID, era)
 * [2] eff.GetMultiRPAcceptRejectDecision(contributing track1 x, contributing track1 y, contributing track2 x, contributing track2 y,                         
                                          contributing track1 RPID, contributing track2 RPID, era)                                                            
  
 */

#define PPSProtonEfficiency_cxx

#include "PPSProtonEfficiency.h"



/*
 * This method will return the numerical value of the efficiency for a multi-RP proton, accounting for all presently known 
 * factors, when available: pixel radiation damage, strips radiation damage, strips multi-track inefficiencies, and multi-RP 
 * algorithm/matching efficiency.
 * This number should be used if weighting events to correct for the efficiency.
 */ 
float PPSProtonEfficiency::GetMultiRPEfficiency(Float_t trackx1, Float_t tracky1, Float_t trackx2, Float_t tracky2, 
						Int_t trackrpid1, Int_t trackrpid2, TString era)
{
  Float_t effcorr = 1.0;
  Float_t effrad1 = 0.0;
  Float_t effrad2 = 0.0;
  Float_t effraderr1 = 0.0;
  Float_t effraderr2 = 0.0;
  Float_t effmulttrack1 = 0.0;
  Float_t effmulttrack2 = 0.0;

  // The pixel efficiencies combine the radiation damage + multi-RP algorithm efficiencies
  // The strip efficiencies are separated into radiation damage and multi-track efficiency
  // 
  // 2016 pre-TS2: preliminarily use the multi-track efficiency of the near RP only, assuming 100% correlation
  // 2016 post-TS2: not currently available
  // 2018: not currently available

  if(era == "2016preTS2")
    {
      if(trackrpid1 == 2)
	{
	  effmulttrack1 = hmultistreff2016PreTS245near->GetBinContent(1);
	  effrad1 = hstreff2016PreTS245near->GetBinContent(hstreff2016PreTS245near->FindBin(trackx1,tracky1));
	}
      if(trackrpid1 == 3)
        {
	  //          effmulttrack1 = hmultistreff2016PreTS245far->GetBinContent(1);
	  effmulttrack1 = 1.0;
          effrad1 = hstreff2016PreTS245far->GetBinContent(hstreff2016PreTS245far->FindBin(trackx1,tracky1));
        }
      if(trackrpid1 == 102)
        {
          effmulttrack1 = hmultistreff2016PreTS256near->GetBinContent(1);
          effrad1 = hstreff2016PreTS256near->GetBinContent(hstreff2016PreTS256near->FindBin(trackx1,tracky1));
        }
      if(trackrpid1 == 103)
        {
	  //          effmulttrack1 = hmultistreff2016PreTS256far->GetBinContent(1);
	  effmulttrack1 = 1.0;
          effrad1 = hstreff2016PreTS256far->GetBinContent(hstreff2016PreTS256far->FindBin(trackx1,tracky1));
        }
      if(trackrpid2 == 2)
        {
          effmulttrack2 = hmultistreff2016PreTS245near->GetBinContent(1);
          effrad2 = hstreff2016PreTS245near->GetBinContent(hstreff2016PreTS245near->FindBin(trackx1,tracky1));
        }
      if(trackrpid2 == 3)
        {
	  //          effmulttrack2 = hmultistreff2016PreTS245far->GetBinContent(1);
          effmulttrack2 = 1.0;
          effrad2 = hstreff2016PreTS245far->GetBinContent(hstreff2016PreTS245far->FindBin(trackx1,tracky1));
        }
      if(trackrpid2 == 102)
        {
          effmulttrack2 = hmultistreff2016PreTS256near->GetBinContent(1);
          effrad2 = hstreff2016PreTS256near->GetBinContent(hstreff2016PreTS256near->FindBin(trackx1,tracky1));
        }
      if(trackrpid2 == 103)
        {
	  //          effmulttrack2 = hmultistreff2016PreTS256far->GetBinContent(1);
          effmulttrack2 = 1.0;
          effrad2 = hstreff2016PreTS256far->GetBinContent(hstreff2016PreTS256far->FindBin(trackx1,tracky1));
        }

    }
  if(era == "2016postTS2")
    {
    }
  if(era == "2017preTS2")
    {
      if(trackrpid1 == 3)
	{
	  effmulttrack1 = hmultistreff2017PreTS245->GetBinContent(1);
	  effrad1 = hstreff2017PreTS245->GetBinContent(hstreff2017PreTS245->FindBin(trackx1,tracky1));
	}
      if(trackrpid1 == 23)
	{
          effmulttrack1 = 1.0;
          effrad1 = hpixeff2017PreTS245->GetBinContent(hpixeff2017PreTS245->FindBin(trackx1,tracky1));;
	}
      if(trackrpid1 == 103)
	{
          effmulttrack1 = hmultistreff2017PreTS256->GetBinContent(1);
          effrad1 = hstreff2017PreTS256->GetBinContent(hstreff2017PreTS256->FindBin(trackx1,tracky1));
	}
      if(trackrpid1 == 123)
	{
          effmulttrack1 = 1.0;
          effrad1 = hpixeff2017PreTS256->GetBinContent(hpixeff2017PreTS256->FindBin(trackx1,tracky1));;
	}
      if(trackrpid2 == 3)
        {
          effmulttrack2 = hmultistreff2017PreTS245->GetBinContent(1);
          effrad2 = hstreff2017PreTS245->GetBinContent(hstreff2017PreTS245->FindBin(trackx2,tracky2));
        }
      if(trackrpid2 == 23)
        {
          effmulttrack2 = 1.0;
          effrad2 = hpixeff2017PreTS245->GetBinContent(hpixeff2017PreTS245->FindBin(trackx2,tracky2));;
        }
      if(trackrpid2 == 103)
        {
          effmulttrack2 = hmultistreff2017PreTS256->GetBinContent(1);
          effrad2 = hstreff2017PreTS256->GetBinContent(hstreff2017PreTS256->FindBin(trackx2,tracky2));
        }
      if(trackrpid2 == 123)
        {
          effmulttrack2 = 1.0;
          effrad2 = hpixeff2017PreTS256->GetBinContent(hpixeff2017PreTS256->FindBin(trackx2,tracky2));;
        }
    }
  if(era == "2017postTS2")
    {
      if(trackrpid1 == 3)
        {
          effmulttrack1 = hmultistreff2017PostTS245->GetBinContent(1);
          effrad1 = hstreff2017PostTS245->GetBinContent(hstreff2017PostTS245->FindBin(trackx1,tracky1));
        }
      if(trackrpid1 == 23)
        {
          effmulttrack1 = 1.0;
          effrad1 = hpixeff2017PostTS245->GetBinContent(hpixeff2017PostTS245->FindBin(trackx1,tracky1));;
        }
      if(trackrpid1 == 103)
        {
          effmulttrack1 = hmultistreff2017PostTS256->GetBinContent(1);
          effrad1 = hstreff2017PostTS256->GetBinContent(hstreff2017PostTS256->FindBin(trackx1,tracky1));
        }
      if(trackrpid1 == 123)
        {
          effmulttrack1 = 1.0;
          effrad1 = hpixeff2017PostTS256->GetBinContent(hpixeff2017PostTS256->FindBin(trackx1,tracky1));;
        }
      if(trackrpid2 == 3)
        {
          effmulttrack2 = hmultistreff2017PostTS245->GetBinContent(1);
          effrad2 = hstreff2017PostTS245->GetBinContent(hstreff2017PostTS245->FindBin(trackx2,tracky2));
        }
      if(trackrpid2 == 23)
        {
          effmulttrack2 = 1.0;
          effrad2 = hpixeff2017PostTS245->GetBinContent(hpixeff2017PostTS245->FindBin(trackx2,tracky2));;
        }
      if(trackrpid2 == 103)
        {
          effmulttrack2 = hmultistreff2017PostTS256->GetBinContent(1);
          effrad2 = hstreff2017PostTS256->GetBinContent(hstreff2017PostTS256->FindBin(trackx2,tracky2));
        }
      if(trackrpid2 == 123)
        {
          effmulttrack2 = 1.0;
          effrad2 = hpixeff2017PostTS256->GetBinContent(hpixeff2017PostTS256->FindBin(trackx2,tracky2));;
        }
    }
  if(era == "2018")
    {
    }

  effcorr = effrad1*effmulttrack1*effrad2*effmulttrack2;

  return effcorr;
}

/*                                                                                                                                        
 * This method will apply a simple "killing" approach to accept or reject multi-RP protons based on the numerical value of the 
 * efficiency calculated above. A random number uniform between 0 and 1 is selected, and the proton is rejected if the 
 * value is above the efficiency for this proton
 * The can be used instead of weigthing, in cases where preserving event-by-event correlations is important.
 */

bool PPSProtonEfficiency::GetMultiRPAcceptRejectDecision(Float_t trackx1, Float_t tracky1, Float_t trackx2, Float_t tracky2, 
							 Int_t trackrpid1, Int_t trackrpid2, TString era)
{
  bool passes = false;
  Float_t effcorr = 0.0;

  float therand = rnd->Uniform();
  effcorr = GetMultiRPEfficiency(trackx1,tracky1,trackx2,tracky2,trackrpid1,trackrpid2,era);

  if(therand <= effcorr)
    passes = true;
  else
    {
      passes = false;
    }

  return passes;
}

/*
 * Get xi scale systematics and return the shifted xi value (commented until ROOT file officially released)
 */
/*
float PPSProtonEfficiency::GetMultiRPXiScaleUncertainty(Int_t arm, Float_t xi, TString era)
{
  float xishifted = 0.0;

  if(arm == 0 && era == "2016preTS2")
    xishifted = xisyst452016preTS2->Eval(xi);
  if(arm == 1 && era == "2016preTS2")
    xishifted = xisyst562016preTS2->Eval(xi);

  if(arm == 0 && era == "2017preTS2")
    xishifted = xisyst452017preTS2->Eval(xi);
  if(arm == 1 && era == "2017preTS2")
    xishifted = xisyst562017preTS2->Eval(xi);
  if(arm == 0 && era == "2017postTS2")
    xishifted = xisyst452017postTS2->Eval(xi);
  if(arm == 1 && era == "2017postTS2")
    xishifted = xisyst562017postTS2->Eval(xi);

  if(arm == 0 && era == "2018")
    xishifted = xisyst452018postTS2->Eval(xi);
  if(arm == 1 && era == "2018")
    xishifted = xisyst562018postTS2->Eval(xi);

  return xishifted;
}
*/
