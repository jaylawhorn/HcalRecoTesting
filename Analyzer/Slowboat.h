#ifndef Slowboat_h
#define Slowboat_h 1

#include <typeinfo>

#include "HcalTimeSlew.h"
#include "PedestalSub.h"

#include "Math/ProbFunc.h"
#include "Math/Functor.h"
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"

class Slowboat {
 public:
  Slowboat();
  ~Slowboat();

  void Init(double init0, double init1, double init2, double init3);

  // This is the CMSSW Implementation of the apply function
  //void apply(const CaloSamples & cs, const std::vector<int> & capidvec, const HcalCalibrations & calibs, std::vector<double> & correctedOutput) const;
  // This is the edited implementation for our standalone test code

  void apply(const std::vector<double> & inputCharge, const std::vector<double> & inputPedestal, std::vector<double> & Output) const;

  //double get_pulse(double *x, double *t);

 private:
  double fInit0;
  double fInit1;
  double fInit2;
  double fInit3;

};

#endif // SlowBoat.h
