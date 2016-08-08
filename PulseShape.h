#ifndef PulseShape_h
#define PulseShape_h

#include <vector>

class PulseShape {
public:
  PulseShape() {}
  void setParams(float LandauW, float LandauMPV, float GausSigma, float GausAsym) {
    LandauW_   = LandauW;
    LandauMPV_ = LandauMPV;
    GausSigma_ = GausSigma;
    GausAsym_  = GausAsym;
  }
  void setBin(int ibin) {ibin_ = ibin; }
  //float compute(const float *tshift) {
  float compute(float tshift) {
    int sumBin = 10;
    
    std::vector<float> Shape;
    for (int m = 0; m<sumBin; m++){ Shape.push_back(0.0); }
    
    float tarea = 1.0;
    float invsq2pi = 0.3989422804014; 
    float MPVShift  = -0.22278298;
    
    float np = 100.0;      // number of convolution steps
    float sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
    
    for (int j=0; j<10 ;j++){
      float xx, yy;
      float mpc = LandauMPV_ - MPVShift * LandauW_;
      float fland;
      float summ = 0.0;
      float xlow = j - sc * GausSigma_;
      float xupp = j + sc * GausSigma_;
      float step = (xupp-xlow) / np;
      float asigma;
      
      for(float i=1.0; i<=np/2; i++) {
	//xx = xlow + (i-0.5) * step - *tshift/25;
	xx = xlow + (i-0.5) * step - tshift/25;
	yy = j-xx;
	asigma = GausSigma_+(yy>0.0)*GausAsym_*(yy-0.0);
	fland = TMath::Landau(xx,mpc,LandauW_) / LandauW_;
	summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;

	//xx = xupp - (i-0.5) * step - *tshift/25;
	xx = xupp - (i-0.5) * step - tshift/25;
	yy = j-xx;
	asigma = GausSigma_+(yy>0.0)*GausAsym_*(yy-0.0);
	fland = TMath::Landau(xx,mpc,LandauW_) / LandauW_;
	summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;
      }
      float funcvalue = tarea * step * summ * invsq2pi;
      Shape.at(j) += funcvalue;
    }

    if (Shape.at(ibin_)<1e-8) return 0;
    else return Shape.at(ibin_);
    
  }
  void computeShape(vector<float> &Shape) {
    int sumBin = 10;
    
    Shape.clear();
    for (int m = 0; m<sumBin; m++){ Shape.push_back(0.0); }
    
    float tarea = 1.0;
    
    float invsq2pi = 0.3989422804014; 
    float MPVShift  = -0.22278298;
    
    float np = 100.0;      // number of convolution steps
    float sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
    
    for (int j=0; j<10 ;j++){
      float xx, yy;
      float mpc = LandauMPV_ - MPVShift * LandauW_;
      float fland;
      float summ = 0.0;
      float xlow = j - sc * GausSigma_;
      float xupp = j + sc * GausSigma_;
      float step = (xupp-xlow) / np;
      float asigma;
      
      for(float i=1.0; i<=np/2; i++) {
	xx = xlow + (i-.5) * step;
	yy = j-xx;
	asigma = GausSigma_+(yy>0.0)*GausAsym_*(yy-0.0);
	fland = TMath::Landau(xx,mpc,LandauW_) / LandauW_;
	summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;
	
	xx = xupp - (i-0.5) * step;
	yy = j-xx;
	asigma = GausSigma_+(yy>0.0)*GausAsym_*(yy-0.0);
	fland = TMath::Landau(xx,mpc,LandauW_) / LandauW_;
	summ += fland * exp(-0.5*pow((yy-0.0)/asigma,2)) / asigma;
      }
      float funcvalue = tarea * step * summ * invsq2pi;
      Shape.at(j) += funcvalue;
    }
  }
private:
  float LandauW_;
  float LandauMPV_;
  float GausSigma_;
  float GausAsym_;
  int ibin_;

};

#endif
