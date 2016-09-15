#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
#include <TGraph.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TF1.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#endif

//subdet: HB=0, HE=1
double landauWidth(double q, int subdet, double sigma=0);
double mostProb(double q, int subdet, double sigma=0);
double gausSigma(double q, int subdet, double sigma=0);
double asym(double q, int subdet, double sigma=0);

double granularity(double q) {
  if (q<75) return (0.577+0.0686*q)/3;
  else return (2.75+0.0373*q+3e-6*q*q)/3;
};

void computeLAGShape(double q, int subdet, double t, vector<double> &Shape, double sigma=0);

void fromPulseShape() {

  double q = 400;
  double t=0, dt=1.5;

  vector<double> TS, TSp, TSm;

  computeLAGShape(q,0,t,TS);
  computeLAGShape(q,0,t+dt,TSp);
  computeLAGShape(q,0,t-dt,TSm);

  for (int i=0; i<10; i++) {
    TS[i] /= TS[4];
    TSp[i] /= TSp[4];
    TSm[i] /= TSm[4];
  }

  TCanvas *c = new TCanvas("c","",800,800);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  gStyle->SetPaintTextFormat("2.2f");

  TH2D *cov = new TH2D("cov","",10,-0.5,9.5,10,-0.5,9.5);

  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {
      //double tmp=0.5*((TSp[i]-TS[i])*(TSp[j]-TS[j]) + (TSm[i]-TS[i])*(TSm[j]-TS[j]));
      //double tmp=(TSp[i]-TS[i])*(TSp[j]-TS[j]);//0.5*((TSp[i]-TS[i])*(TSp[j]-TS[j]) + (TSm[i]-TS[i])*(TSm[j]-TS[j]));
      double tmp=(TSm[i]-TS[i])*(TSm[j]-TS[j]);
      cov->SetBinContent( cov->GetBin(i,j),tmp );
      cov->SetBinContent( cov->GetBin(j,i),tmp );
    }
  }

  cov->GetZaxis()->SetRangeUser(-1,1);

  cov->Draw("colz text");

}

double landauWidth(double q, int subdet, double sigma) {
  double qt = (q<550 ? q : 550);
  if (subdet==0) return exp( -2.69212 + 0.339142*sigma + (-0.0200032+0.00775682*sigma) * qt ) + 0.166766 + 0.00137787*sigma;
  else if (subdet==1) return exp( -1.25575 + 0.0782487*sigma + (-0.033789+0.00217511*sigma) * qt ) + 0.138741 + 0.000636494*sigma;
  else {
    cout << "unknown subdetector!" << endl;
    return 0;
  }
}

double mostProb(double q, int subdet, double sigma) {
  double qt = (q<550 ? q : 550);
  if (subdet==0) return 4.13324 + 0.00465576*sigma + (-0.000471641+ 3.44855e-05*sigma) * qt + (3.69809e-07 +5.40687e-08*sigma) * qt*qt;
  else if (subdet==1) {
    double tmp=3.98878+0.00707374*sigma;
    tmp+=(0.00274516+0.000264674*sigma)*qt;
    tmp+=(-2.29749e-05+3.33247e-06*sigma)*qt*qt;
    tmp+=(9.044e-08+1.90669e-08*sigma)*qt*qt*qt;
    tmp+=(-1.92282e-10+5.43992e-11*sigma)*qt*qt*qt*qt;
    tmp+=(2.13577e-13+7.5391e-14*sigma)*qt*qt*qt*qt*qt;
    tmp+=(-9.72045e-17+4.04107e-17*sigma)*qt*qt*qt*qt*qt*qt;
    return tmp;
  }
  else {
    cout << "unknown subdetector!" << endl;
    return 0;
  }

}

double gausSigma(double q, int subdet, double sigma) {
  double qt = (q<550 ? q : 550);
  if (subdet==0) return exp( -1.41872 + 0.573027*sigma + (-0.0558063 + 0.0186813*sigma) * qt ) + 0.315172 + 0.00127181*sigma;
  else if (subdet==1) return exp( -1.9489 + 0.0675424*sigma + (-0.026614 +0.00164744*sigma) * qt ) + 0.316884 + 0.000473545*sigma;
  else {
    cout << "unknown subdetector!" << endl;
    return 0;
  }

}

double asym(double q, int subdet, double sigma) {
  double qt = (q<550 ? q : 550);
  if (subdet==0) return exp( -1.85949 + 0.0476665*sigma + (-0.00946504+0.00072732*sigma) * qt ) + -0.0595725 + 0.00189319*sigma;
  else if (subdet==1) return exp( -1.533 +0.0303588*sigma + (-0.00696893+0.000480861*sigma) * qt ) + -0.101749 + 0.00305867*sigma;
  else {
    cout << "unknown subdetector!" << endl;
    return 0;
  }

}


void computeLAGShape(double q, int subdet, double t, vector<double> &Shape, double sigma) {
  double lwidth = landauWidth(q, subdet, sigma);
  double MProb = mostProb(q, subdet, sigma) + (t/25.0);
  double gsigma = gausSigma(q, subdet, sigma);
  double asymmcoef = asym(q, subdet, sigma);

  double timeslice[10] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
  double funcvalue[10];
  for (int m = 0; m<10; m++){ funcvalue[m] = 0.0;}

  double invsq2pi = 0.3989422804014; 
  double mpshift  = -0.22278298;
  
  double np = 100.0;      // number of convolution steps
  double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

  for (int j=0; j<10 ;j++){
    double xx;
    double yy;
    double mpc = MProb - mpshift * lwidth;
    double fland;
    double summ = 0.0;
    double xlow = timeslice[j] - sc * gsigma;
    double xupp = timeslice[j] + sc * gsigma;
    double step = (xupp-xlow) / np;
    double asigma;
  
    for(double i=1.0; i<=np/2; i++) {
      xx = xlow + (i-.5) * step;
      yy = timeslice[j]-xx;
      asigma = gsigma+(yy>0.0)*asymmcoef*(yy-0.0);
      fland = TMath::Landau(xx,mpc,lwidth) / lwidth;
      summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;

      xx = xupp - (i-.5) * step;
      yy = timeslice[j]-xx;
      asigma = gsigma+(yy>0.0)*asymmcoef*(yy-0.0);
      fland = TMath::Landau(xx,mpc,lwidth) / lwidth;
      summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;
    }
    funcvalue[j] = step * summ * invsq2pi;
  }

  for (int i=0; i<10; i++) {
    //Shape.push_back( funcvalue[i]/funcvalue[4]);
    if (q*funcvalue[i]>1e-3) 
      Shape.push_back(q*funcvalue[i]);
    else Shape.push_back(0);
    //cout << i << ", " << q*funcvalue[i] << ", " << granularity(q*funcvalue[i]) << endl;
  }
 
}//end miao's

