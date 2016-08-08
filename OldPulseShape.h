#ifndef OldPulseShape_h
#define OldPulseShape_h

#include <vector>

class OldPulseShape {
public:
  OldPulseShape() {}
  void setParams(float ts1, float ts2, float ts3, float thpd, float tpre, float wd1, float wd2, float wd3) {
    ts1_ = ts1;
    ts2_ = ts2;
    ts3_ = ts3;
    thpd_ = thpd;
    tpre_ = tpre;
    wd1_ = wd1;
    wd2_ = wd2;
    wd3_ = wd3;

  }
  void setBin(int ibin) {ibin_ = ibin; }

  double delay(double fC, int bias) {

    static const double tzero[3]= {23.960177, 13.307784, 9.109694};
    static const double slope[3] = {-3.178648,  -1.556668, -1.075824 };
    static const double tmax[3] = {16.00, 10.00, 6.25 };

    double rawDelay=tzero[bias]+slope[bias]*log(fC);
    return (rawDelay<0)?(0):((rawDelay>tmax[bias])?(tmax[bias]):(rawDelay));   
  }

  void makeShape() {

    // pulse shape componnts over a range of time 0 ns to 255 ns in 1 ns steps
    unsigned int nbin = 256;

    for (unsigned int i=0; i<nbin; i++) {Shape_.push_back(0.0);}
    //Shape_(nbin,0.0);  // zeroing output pulse shape
    std::vector<float> nth(nbin,0.0);   // zeroing HPD drift shape
    std::vector<float> ntp(nbin,0.0);   // zeroing Binkley preamp shape
    std::vector<float> ntd(nbin,0.0);   // zeroing Scintillator decay shape

    unsigned int i,j,k;
    float norm;

    // HPD starts at I and rises to 2I in thpd of time
    norm=0.0;
    for(j=0;j<thpd_ && j<nbin;j++){
      nth[j] = 1.0 + ((float)j)/thpd_;
      norm += nth[j];
    }
    // normalize integrated current to 1.0
    for(j=0;j<thpd_ && j<nbin;j++){
      nth[j] /= norm;
    }
  
    // Binkley shape over 6 time constants
    norm=0.0;
    for(j=0;j<6*tpre_ && j<nbin;j++){
      ntp[j] = ((float)j)*exp(-((float)(j*j))/(tpre_*tpre_));
      norm += ntp[j];
    }
    // normalize pulse area to 1.0
    for(j=0;j<6*tpre_ && j<nbin;j++){
      ntp[j] /= norm;
    }

    // effective tile plus wave-length shifter decay time over 4 time constants
    unsigned int tmax = 6 * (int)ts3_;
 
    norm=0.0;
    for(j=0;j<tmax && j<nbin;j++){
      ntd[j] = wd1_ * exp(-((float)j)/ts1_) + 
	wd2_ * exp(-((float)j)/ts2_) + 
	wd3_ * exp(-((float)j)/ts3_) ; 
      norm += ntd[j];
    }
    // normalize pulse area to 1.0
    for(j=0;j<tmax && j<nbin;j++){
      ntd[j] /= norm;
    }
  
    unsigned int t1,t2,t3,t4;
    for(i=0;i<tmax && i<nbin;i++){
      t1 = i;
      //    t2 = t1 + top*rand;
      // ignoring jitter from optical path length
      t2 = t1;
      for(j=0;j<thpd_ && j<nbin;j++){
	t3 = t2 + j;
	for(k=0;k<4*tpre_ && k<nbin;k++){       // here "4" is set deliberately,
	  t4 = t3 + k;                         // as in test fortran toy MC ...
	  if(t4<nbin){                         
	    unsigned int ntb=t4;                        
	    Shape_[ntb] += ntd[i]*nth[j]*ntp[k];
	  }
	}
      }
    }
  
    // normalize for 1 GeV pulse height
    norm = 0.;
    for(i=0;i<nbin;i++){
      norm += Shape_[i];
    }

    //cout << " Convoluted SHAPE ==============  " << endl;
    for(i=0; i<nbin; i++){
      Shape_[i] /= norm;
      //std::cout << i << ",  " << ntmp[i] << std::endl;   
    }

  }
  
  float compute(float tshift) {

    float val=0;

    int i_start = ( -92.5 - tshift >0 ? 0 : (int)std::abs(-92.5-tshift) + 1);
    double offset_start = i_start - 92.5 - tshift; 

    if( offset_start == 1.0 ){ offset_start = 0.; i_start-=1; } //Deal with boundary

    const int bin_start        = (int) offset_start; //bin off to integer
    const int bin_0_start      = ( offset_start < bin_start + 0.5 ? bin_start -1 : bin_start ); //Round it

    const int iTS_start        = i_start/25;         //Time Slice for time shift
    const int distTo25ns_start = 92.5 - 1 - i_start%25;    //Delta ns 
    const double factor = offset_start - bin_0_start - 0.5; //Small correction?

    cout << i_start << ", " << iTS_start << ", " << distTo25ns_start << ", " << 25*ibin_ - distTo25ns_start <<  ", " << 25*(ibin_ - iTS_start -1) << ", ";

    for (int j=0; j<25; j++) {
      if (25*(ibin_) - distTo25ns_start + j > -1) 
	val+=Shape_.at(25*(ibin_) -distTo25ns_start+j);
    }
    
    return val;

  }

  //int shapeSize() { return Shape_.size(); }

private:
  float ts1_, ts2_, ts3_;
  float thpd_, tpre_;
  float wd1_, wd2_, wd3_;
  int ibin_;

  vector<float> Shape_;  

  std::vector<float> acc25nsVec, diff25nsItvlVec;
  std::vector<float> accVarLenIdxZEROVec, diffVarItvlIdxZEROVec;
  std::vector<float> accVarLenIdxMinusOneVec, diffVarItvlIdxMinusOneVec;

};

#endif
