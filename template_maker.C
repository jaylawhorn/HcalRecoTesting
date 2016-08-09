#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>                // interface to OS
#include <TMath.h>                  // ROOT math library
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O

#include "Math/Functor.h"
#include "Math/RichardsonDerivator.h"

#include "OldPulseShape.h"
#endif

void template_maker() {

  TFile *f = new TFile("test_input.root","recreate");
  TTree *t = new TTree("PulseInfo","PulseInfo");

  float minCharge, maxCharge;
  float timeSlew;
  float pulseFrac[10], pulseFracDeriv[10];

  t->Branch("minCharge", &minCharge, "minCharge/F");
  t->Branch("maxCharge", &maxCharge, "maxCharge/F");
  t->Branch("timeSlew",  &timeSlew,  "timeSlew/F");
  t->Branch("pulseFrac", &pulseFrac, "pulseFrac[10]/F");
  t->Branch("pulseFracDeriv", &pulseFracDeriv, "pulseFracDeriv[10]/F");

  OldPulseShape pulse;

  //ts1=8. ; ts2=19. ; ts3=29.3; thpd=4.0; tpre=9.0; wd1=2.0; wd2=0.7; wd3=0.32;
  pulse.setParams(8, 19, 29.3, 4.0, 9.0, 2.0, 0.7, 0.32);
  pulse.makeShape();

  for (int i=0; i<58; i++) {
    minCharge=20+10*i;
    maxCharge=30+10*i;
    timeSlew=pulse.delay(25+10*i,1);

    for (int j=0; j<10; j++) {
      pulse.setBin(j);
      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=0.5*(pulse.compute(timeSlew+1)-pulse.compute(timeSlew-1));

      if ( pulse.compute(timeSlew)>0.01 && 
	   ( fabs ( (pulse.compute(timeSlew+5) - pulse.compute(timeSlew) - pulseFracDeriv[j]*5)/(pulse.compute(timeSlew)) ) > 0.08 ||
	     ( fabs ( (pulse.compute(timeSlew-5) - pulse.compute(timeSlew) + pulseFracDeriv[j]*5)/(pulse.compute(timeSlew)) ) > 0.08 ) )
	   ) {
	cout << i << ", " << j << endl;
      }

    }

    t->Fill();
  }

  f->Write();
  f->Close();

  //cout << pulse.Shape_.at(100) << endl;

  //pulse.setParams(0.215959, 4.111022, 0.374303, 0.073503);

  //computeLAGShape(LandauW_Dat_B[0], LandauMPV_Dat_B[0], GausSigma_Dat_B[0], GausAsym_Dat_B[0], Dat_B_Shape); 
  //computeLAGDeriv(LandauW_Dat_B[0], LandauMPV_Dat_B[0], GausSigma_Dat_B[0], GausAsym_Dat_B[0], Dat_B_Deriv); 

    //vector <float> slopes;

  /*  for (int i=0; i<10; i++) {
    pulse.setBin(i);
    slopes.push_back( (pulse.compute(0.01)-pulse.compute(-0.01))/(0.02/25.) );

    cout << pulse.compute(0)+slopes[i]*10/25 << ", " << pulse.compute(10) << ";; " << pulse.compute(0)-slopes[i]*10/25 << ", " << pulse.compute(-10) << endl;

    }*/
  
}
