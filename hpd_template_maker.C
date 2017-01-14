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

#include "OldPulseShape.h"
#endif

void hpd_template_maker(string outname="test_result.csv") {

  float dt=2.5;

  float minCharge, maxCharge;
  float timeSlew=0;
  float pulseFrac[10], pulseFracDeriv[10];

  OldPulseShape pulse;

  ts1=8. ; ts2=19. ; ts3=29.3; thpd=4.0; tpre=9.0; wd1=2.0; wd2=0.7; wd3=0.32;
  pulse.setParams(8, 19, 29.3, 4.0, 9.0, 2.0, 0.7, 0.32);
  pulse.makeShape();
  
  ofstream outfile;
  outfile.open(outname.c_str());

  outfile << "#minQ, maxQ, frac[0-10], deriv[0-10] \n";

  for (int i=0; i<58; i++) {
  //for (int i=0; i<2; i++) {
    //cout << "-------" << endl;
    minCharge=20+10*i;
    maxCharge=30+10*i;
    //timeSlew=pulse.delay(25+10*i,1);
    
    for (int j=0; j<10; j++) {
      pulse.setBin(j);
      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=0.5*(pulse.compute(timeSlew+1)-pulse.compute(timeSlew-1));
      /*if (j==4) {
	cout << timeSlew+5 << endl;
	cout << pulse.compute(timeSlew+5) << ", " << pulse.compute(timeSlew+1) << ", " << pulse.compute(timeSlew) << ", " << pulse.compute(timeSlew-1) << ", " << pulse.compute(timeSlew-5) << endl;
	cout << pulse.compute(timeSlew+5) << " vs " << pulseFrac[j]+5*pulseFracDeriv[j] << " = " << 100*abs(pulse.compute(timeSlew+5) - (pulseFrac[j]+5*pulseFracDeriv[j]))/(pulse.compute(timeSlew+5)) << endl;
	cout << pulse.compute(timeSlew-5) << " vs " << pulseFrac[j]-5*pulseFracDeriv[j] << " = " << 100*abs(pulse.compute(timeSlew-5) - (pulseFrac[j]-5*pulseFracDeriv[j]))/(pulse.compute(timeSlew-5)) << endl;
	}*/

    }
     
    outfile << minCharge << ", " << maxCharge;
    //cout << minCharge << ", " << maxCharge;

    //for (int i=0;

    /*for (int j=0; j<10; j++) {
      pulse.setBin(j);
    outfile << ", " << abs(pulseFrac[j]+pulseFracDeriv[j]*5 - pulse.compute(timeSlew+5))/pulse.compute(timeSlew+5);
    cout << "; " << pulseFrac[j]+pulseFracDeriv[j]*5 << ", " << pulse.compute(timeSlew+5);
    cout << "    ; " << pulseFrac[j]-pulseFracDeriv[j]*5 << ", " << pulse.compute(timeSlew-5);
      cout << " : " <<  max (
			    100*abs(pulse.compute(timeSlew+dt) - (pulseFrac[j]+dt*pulseFracDeriv[j]))/(pulse.compute(timeSlew+dt)), 
			    100*abs(pulse.compute(timeSlew-dt) - (pulseFrac[j]-dt*pulseFracDeriv[j]))/(pulse.compute(timeSlew-dt)) );
    }
    */

    for (int j=0; j<10; j++) { outfile << ", " << pulseFrac[j]; }
    for (int j=0; j<10; j++) { outfile << ", " << pulseFracDeriv[j]; }
    outfile << "\n";
    //cout << "\n";

  }

  outfile.close();

}
