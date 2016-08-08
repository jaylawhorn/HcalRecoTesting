#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
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

//void computeLAGShape(double LandauW, double LandauMPV, double GausSigma, double GausAsym, vector<double> &Shape);
//void computeLAGDeriv(double LandauW, double LandauMPV, double GausSigma, double GausAsym, vector<double> &Deriv);

void template_maker(TString infile="data_barrel_values.txt") {

  ifstream ifs;
  ifs.open(infile);
  assert(ifs.is_open());
  string line;

  OldPulseShape pulse;

  //ts1=8. ; ts2=19. ; ts3=29.3; thpd=4.0; tpre=9.0; wd1=2.0; wd2=0.7; wd3=0.32;
  pulse.setParams(8, 19, 29.3, 4.0, 9.0, 2.0, 0.7, 0.32);
  pulse.makeShape();

  pulse.setBin(4);

  for (int i=-15; i<15; i++) {
    cout << i << ", " << pulse.compute(i) << endl;
  }

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
