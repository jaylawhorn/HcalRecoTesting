#include <iostream>
#include <cmath>
#include <climits>
#include "Slowboat.h"

using namespace std;

double get_pulse(double *x, double *t) {
  
  TF1 pulse("pulse", "[0]*TMath::Landau(x,[1],[2],0)", 0, 10);
  pulse.SetParameter(0, t[0]);
  pulse.SetParameter(1, t[1]);
  pulse.SetParameter(2, t[2]);

  //double ans = pulse.Eval(x[0])+t[3];                                                                       
  double ans = pulse.Integral(floor(x[0]), floor(x[0])+1)+t[3];

  //double ans = t[0]*(ROOT::Math::landau_cdf(floor(x[0]-t[1]),t[2],0) - ROOT::Math::landau_cdf(floor(x[0]-t[1]),t[2],1.0)) + t[3];

  return ans;

}

Slowboat::Slowboat() {
}

Slowboat::~Slowboat() { 
}

void Slowboat::Init(double init0, double init1, double init2, double init3) {

  fInit0=init0;
  fInit1=init1;
  fInit2=init2;
  fInit3=init3;
}

void Slowboat::apply(const std::vector<double> & inputCharge, const std::vector<double> & inputPedestal, std::vector<double> & Output) const {

  //TF1 f1("that", (this->*get_pulse)(), 0, 10, 4);
  TF1 f1("that", get_pulse, 0, 10, 4);

  TH1D htemp("htemp", "htemp", 10, 0, 10);

  for (uint i=0; i<10; i++) {
    htemp.SetBinContent(i+1, inputCharge[i]);
  }

  f1.SetParameter(0, fInit0);
  f1.SetParameter(1, fInit1);
  f1.SetParameter(2, fInit2);
  f1.SetParameter(3, fInit3);

  htemp.Fit("that");

  Output.clear();
  Output.push_back(f1.GetParameter(0));
  Output.push_back(f1.GetParameter(1));
  Output.push_back(f1.GetParameter(2));
  Output.push_back(f1.GetParameter(3));

  for (uint i=0; i<10; i++) {
    Output.push_back(f1.Eval(i+0.5));
  }

}

//double Slowboat::get_pulse(double *x, double *t) {
//double get_pulse(double *x, double *t) {
//
//  TF1 pulse("pulse", "[0]*TMath::Landau(x,[1],[2],0)", 0, 10);
//  pulse.SetParameter(0, t[0]);
//  pulse.SetParameter(1, t[1]);
//  pulse.SetParameter(2, t[2]);
//
//  //double ans = pulse.Eval(x[0])+t[3];
//  double ans = pulse.Integral(floor(x[0]), floor(x[0])+1)+t[3];                                       
//
//  return ans;
//
//}
