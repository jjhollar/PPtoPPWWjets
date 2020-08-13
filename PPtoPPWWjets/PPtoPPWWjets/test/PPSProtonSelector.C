/*
 * This macro applies cuts to select good multi-RP protons. Based on 
 *  a) Collimator aperture cuts
 *  b) Fiducial cuts on the sensor area, for eras where pixel tracking is use, and pixel track local 
 *     angles, for eras where pixel tracking is used                                                              
 *  d) Rejecting pixel tracks built with BX-shifted planes, in periods where the pixels used 3+3 mode in 2017
 *
 * The method "TightMultiRPProton" applies the AND of all of these cuts
 *
 * Usage: 
 * [0] .L PPSProtonSelector.C
 * [1] TightMultiRPProton(contributing track1 x, contributing track1 y, contributing track2 x, contributing track2 y, 
                          contributing track1 theta_x, contributing track1 theta_y, contributing track2 theta_x, contributing track2 theta_y,
			  proton arm, contributing track1 RPID, contributing track2 RPID, 
			  crossing angle, era, xi,
			  contributing track1 pixel shift, contributing track2 pixel shift)
 */


/*
 * Pixel sensor area fiducial cuts. Note that for now, only the tightest value of each era is used.
 */
bool PixelFiducialCuts(Float_t trackx=0.0, Float_t tracky=0.0, Float_t trackthetax=0.0, Float_t trackthetay=0.0, 
		       Int_t thearm=0, TString theera="", Int_t therpid=23)
{
  // Do not apply these cuts to Strip RP's
  if(theera == "2016preTS2" || theera == "2016postTS2" || 
     ((theera == "2017preTS2" || theera == "2017postTS2") && (therpid != 23 && therpid != 123)))
    return true;

  float xmin_45_220 = -999.;
  float xmax_45_220 = -999.;
  float ymin_45_220 = -999.;
  float ymax_45_220 = -999.;
  float xmin_56_220 = -999.;
  float xmax_56_220 = -999.;
  float ymin_56_220 = -999.;
  float ymax_56_220 = -999.;
  float xmin_45_210 = -999.;
  float xmax_45_210 = -999.;
  float ymin_45_210 = -999.;
  float ymax_45_210 = -999.;
  float xmin_56_210 = -999.;
  float xmax_56_210 = -999.;
  float ymin_56_210 = -999.;
  float ymax_56_210 = -999.;

  if(theera == "2017preTS2")               
    {
      if(thearm == 0)
        {
          xmin_45_220 = 1.995;
          xmax_45_220 = 24.334;
          ymin_45_220 = -11.098;
          ymax_45_220 = 4.298;
        }
      if(thearm == 1)
        {
          xmin_56_220 = 2.137;
          xmax_56_220 = 24.620;
          ymin_56_220 = -10.698;
          ymax_56_220 = 4.698;
        }
    }
  if(theera == "2017postTS2")
    {
      if(thearm == 0)
        {
          xmin_45_220 = 1.995;
          xmax_45_220 = 24.497;
          ymin_45_220 = -10.098;
          ymax_45_220 = 4.998;
        }
      if(thearm == 1)
        {
          xmin_56_220 = 2.422;
          xmax_56_220 = 24.620;
          ymin_56_220 = -9.698;
          ymax_56_220 = 5.398;
        }
    }
  if(theera == "2018")
    {
      if(thearm == 0)
	{
	  xmin_45_210 = 2.850;
	  xmax_45_210 = 17.640;
	  ymin_45_210 = -10.598;
	  ymax_45_210 = 3.698;
          xmin_45_220 = 2.421;
          xmax_45_220 = 24.479;
          ymin_45_220 = -10.898;
          ymax_45_220 = 3.298;
	}
      if(thearm == 1)
	{
	  xmin_56_210 = 3.275;
          xmax_56_210 = 17.931;
          ymin_56_210 = -9.998;
          ymax_56_210 = 3.298;
          xmin_56_220 = 2.564;
          xmax_56_220 = 20.045;
          ymin_56_220 = -10.398;
          ymax_56_220 = 3.898;
	}
    }

  std::map<std::pair<int, int>, double> fiducialXLow_ = {
    {std::pair<int,int>(0,0), xmin_45_210},
    {std::pair<int,int>(0,2), xmin_45_220},
    {std::pair<int,int>(1,0), xmin_56_210},
    {std::pair<int,int>(1,2), xmin_56_220},
  };
  std::map<std::pair<int, int>, double> fiducialXHigh_ = {
    {std::pair<int,int>(0,0), xmax_45_210},
    {std::pair<int,int>(0,2), xmax_45_220},
    {std::pair<int,int>(1,0), xmax_56_210},
    {std::pair<int,int>(1,2), xmax_56_220},
  };
  std::map<std::pair<int, int>, double> fiducialYLow_ = {
    {std::pair<int,int>(0,0), ymin_45_210},
    {std::pair<int,int>(0,2), ymin_45_220},
    {std::pair<int,int>(1,0), ymin_56_210},
    {std::pair<int,int>(1,2), ymin_56_220},
  };
  std::map<std::pair<int, int>, double> fiducialYHigh_ = {
    {std::pair<int,int>(0,0), ymax_45_210},
    {std::pair<int,int>(0,2), ymax_45_220},
    {std::pair<int,int>(1,0), ymax_56_210},
    {std::pair<int,int>(1,2), ymax_56_220},
  };

  uint32_t station;
  int arm; 

  double x = trackx;
  double y = tracky;
  arm = thearm;
  
  if(therpid == 3 || therpid == 103)
    station = 0;
  if(therpid == 23 || therpid == 123)
    station = 2;

  float pixelX0_rotated = 0;
  float pixelY0_rotated = 0;
  if (station == 0) {
    pixelX0_rotated = x * TMath::Cos((-8. / 180.) * TMath::Pi()) -
      y * TMath::Sin((-8. / 180.) * TMath::Pi());
    pixelY0_rotated = x * TMath::Sin((-8. / 180.) * TMath::Pi()) +
      y * TMath::Cos((-8. / 180.) * TMath::Pi());
    x = pixelX0_rotated;
    y = pixelY0_rotated;
  }

  double maxTx = 0.02;
  double maxTy = 0.02;

  if(
     ((fabs(trackthetax) > maxTx) || (fabs(trackthetay) > maxTy)) || 
     y > fiducialYHigh_[std::pair<int, int>(arm, station)] ||
     y < fiducialYLow_[std::pair<int, int>(arm, station)] ||
     x < fiducialXLow_[std::pair<int, int>(arm, station)] ||
     x > fiducialXHigh_[std::pair<int, int>(arm, station)]
     )
    {
      return false;
    }
  else
    {
      return true;
    }
  
}

/*
 * First approximate collimator aperture cuts
 * Ref: https://indico.cern.ch/event/849095/contributions/3568020/attachments/1913799/3163250/j_kaspar_apertures.pdf                                                                   
 */
bool ApertureCuts(Float_t xangle, Int_t arm, TString era, Float_t thexi)
{
  bool passes = false;

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
      if(arm == 1) // Note - 1 strip RP was not in, so no aperture cuts derived. Automatically reject for multi-RP
        aperturelimit = -999.9;
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

  passes = (thexi <= aperturelimit);

  return passes;
}

/*
 * Exclude tracks build with BX-shifted pixel planes during part of 2017 data
 */
bool PixelBXShiftCuts(Int_t trackpixshift1, Int_t proton_trackpixshift2)
{
  bool passes = false;

  passes = (trackpixshift1==0) && (proton_trackpixshift2==0);

  return passes;
}

/*                                                                                                                                        
 * Basic check for valid combination of era, arm, and RP ID
 */
bool SanityCheck(Int_t thearm=0, TString theera="", Int_t therpid=23)
{
  bool passes = false;

  if(thearm == 0)
    {
      if(theera == "2016preTS2" || theera == "2016postTS2")
	if((therpid == 2) || (therpid == 3))
	  passes = true;
      if(theera == "2017preTS2" || theera == "2017postTS2" || theera == "2018")
	if((therpid == 3) || (therpid == 23))
	  passes = true;
    }
  if(thearm == 1)
    {
      if(theera == "2016preTS2" || theera == "2016postTS2")
        if((therpid == 102) || (therpid == 103))
          passes = true;
      if(theera == "2017preTS2" || theera == "2017postTS2" || theera == "2018")
        if((therpid == 103) || (therpid == 123))
          passes = true;
    }

  if(passes == false)
    std::cout << "ERROR in PPSProtonSelecton: INVALID COMBINATION OF ERA, ARM, AND RP ID: " << theera << ", " << thearm 
	      << ", " << therpid << std::endl;
  
  return passes;
}

/*
 * Final selector decision, combining all proton cuts above.
 */
bool TightMultiRPProton(Float_t trackx1=0.0, Float_t tracky1=0.0, Float_t trackx2=0.0, Float_t tracky2=0.0, 
			Float_t trackthetax1=0.0, Float_t trackthetay1=0.0, Float_t trackthetax2=0.0, Float_t trackthetay2=0.0, 
			Int_t thearm=0, Int_t therpid1=103, Int_t therpid2=123,  
			Float_t xangle=0.0, TString era="2015", Float_t xi=0.0, 
			Int_t trackpixshift1=0, Int_t trackpixshift2=0)
{
  bool passesall = false;

  if(era == "2017preTS2" || era == "2017postTS2" || era == "2018")
    {
      // Pixels+Strips (2017) or Pixels only (2018)
      passesall =
	SanityCheck(thearm, era, therpid1) && 
	SanityCheck(thearm, era, therpid2) &&
	PixelFiducialCuts(trackx1, tracky1, trackthetax1, trackthetay1, thearm, era, therpid1) &&
	PixelFiducialCuts(trackx2, tracky2, trackthetax2, trackthetay2, thearm, era, therpid2) &&
	PixelBXShiftCuts(trackpixshift1, trackpixshift2) && 
	ApertureCuts(xangle, thearm, era, xi);
    }
  else if(era == "2016preTS2" || era == "2016postTS2")
    {
      // Strips only
      passesall = 
	SanityCheck(thearm, era, therpid1) &&
        SanityCheck(thearm, era, therpid2) &&
	ApertureCuts(xangle, thearm, era, xi);
    }
  else
    {
      // Unknown era
      passesall = false;
    }

  return passesall;
}
