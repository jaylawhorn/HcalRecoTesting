#define Analysis_cxx

#include "Analysis.h"
#include "readparameters/readparameters.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include "TLine.h"
#include "TLegend.h"

using namespace std;

double round_nplaces(double value, int to){
  int places = 1, whole = value;
  for(int i = 0; i < to; i++) places *= 10;
  value -= whole; //leave decimals
  value *= places; //0.1234 -> 123.4
  value = round(value);//123.4 -> 123
  value /= places; //123 -> .123
  value += whole; //bring the whole value back
  return value;
}

string int2string(int i){
  stringstream ss;
  string ret;
  ss<<i;
  ss>>ret;
  return ret;
}

// Ugly hack to apply energy corrections to some HB- cells
double eCorr(int ieta, int iphi, double energy) {
// return energy correction factor for HBM channels 
// iphi=6 ieta=(-1,-15) and iphi=32 ieta=(-1,-7)
// I.Vodopianov 28 Feb. 2011
  static const float low32[7]  = {0.741,0.721,0.730,0.698,0.708,0.751,0.861};
  static const float high32[7] = {0.973,0.925,0.900,0.897,0.950,0.935,1};
  static const float low6[15]  = {0.635,0.623,0.670,0.633,0.644,0.648,0.600,
				  0.570,0.595,0.554,0.505,0.513,0.515,0.561,0.579};
  static const float high6[15] = {0.875,0.937,0.942,0.900,0.922,0.925,0.901,
				  0.850,0.852,0.818,0.731,0.717,0.782,0.853,0.778};
  
  double slope, mid, en;
  double corr = 1.0;

  if (!(iphi==6 && ieta<0 && ieta>-16) && !(iphi==32 && ieta<0 && ieta>-8)) 
    return corr;

  int jeta = -ieta-1;
  double xeta = (double) ieta;
  if (energy > 0.) en=energy;
  else en = 0.;

  if (iphi == 32) {
    slope = 0.2272;
    mid = 17.14 + 0.7147*xeta;
    if (en > 100.) corr = high32[jeta];
    else corr = low32[jeta]+(high32[jeta]-low32[jeta])/(1.0+exp(-(en-mid)*slope));
  }
  else if (iphi == 6) {
    slope = 0.1956;
    mid = 15.96 + 0.3075*xeta;
    if (en > 100.0) corr = high6[jeta];
    else corr = low6[jeta]+(high6[jeta]-low6[jeta])/(1.0+exp(-(en-mid)*slope));
  }

  return corr;
}

int main(int argc, char **argv)
{
  int ret=0;
  if (argc!=2) {
    cerr<<"Usage: ./Analysis <paramfile>"<<endl;
    ret=1;
  } else {

    readparameters rp(argv[1]);
    //TChain* ch = new TChain("HcalNoiseTree");
    TChain* ch = new TChain("ExportTree/HcalTree");
    //TChain* ch = new TChain("HBHEData/Events");
    //TChain* ch2 = new TChain("Timing/Events");

    string filelistname;

    filelistname=rp.get<string>((string("in_filelist")).c_str());
    string line;
    ifstream filelist(filelistname.c_str());
    if (filelist.fail()) { //catch
      cerr << "\nERROR: Could not open " << filelistname << endl;
      exit(1);
    }
    while (getline(filelist,line)) {
      ch->Add(line.c_str());
      //ch2->Add(line.c_str());
    }

    Analysis Ana25ns((TTree*) ch);

    Ana25ns.Init(argv[1], (TTree*) ch);
    Ana25ns.Process();
    Ana25ns.Finish();
  }
 return ret;
}

Analysis::~Analysis() {
}

Analysis::Analysis(TTree *tree):analysistree(tree){};

void Analysis::Init(char* paramfile, TTree* tree)
{
  try {
    readparameters rp(paramfile);
    try {Output_File=rp.get<string>("Output_File");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Entries=rp.get<int>("Entries");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Plot_Dir=rp.get<string>("Plot_Dir");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Region=rp.get<int>("Region");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Condition=rp.get<int>("Condition");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Baseline=rp.get<int>("Baseline");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Time_Slew=rp.get<int>("Time_Slew");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Neg_Charges=rp.get<int>("Neg_Charges");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Threshold=rp.get<float>("Threshold");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
    try {Quantile=rp.get<float>("Quantile");}
    catch (exception& e) {cerr<<e.what()<<endl;} 
  } 
  catch (exception& e) {cerr<<e.what()<<endl;} 

  cout << "Running on ";
  if (Entries==-1) cout << "all events." << endl;
  else cout << "first " << Entries << " events. " << endl;

  cout << "Output ROOT file: " << Output_File << endl;

  cout << "Using channels in ";
  if (Region==All) { cout << "all HCAL regions. " << endl; }
  else if (Region==Barrel) { cout << "HCAL barrel. " << endl; }
  else if (Region==Endcap) { cout << "HCAL endcap. " << endl; }

  //if (Condition==0) {
  //  cout << "With no PU. " << endl;
  //}
  //else if (Condition==50) {
  //  cout << "50 ns spacing, 20 PU." << endl;
  //}
  //else if (Condition==25) {
  //  cout << "25 ns spacing, 20 PU." << endl;
  //}
  //else {
  //  Condition=0;
  //  cout << "Unrecognized run condition, using no PU." << endl;
  //}

  int check=mkdir(Plot_Dir.c_str(),755);
  if (!check) {
    cout << "Saving files to: " << Plot_Dir << endl;
  }
  else {
    cout << "Double check your plot directory exists! Something funny happened." << endl;
    //exit(1);
  }

  //if (Baseline==PedestalSub::DoNothing) {
  //  cout << "Pedestal subtraction only." << endl;
  //}
  //else if (Baseline==PedestalSub::AvgWithThresh) {
  //  cout << "Pedestal subtraction, average baseline subtraction with threshold: " << Threshold << endl;
  //}
  //else if (Baseline==PedestalSub::AvgWithoutThresh) {
  //  cout << "Pedestal subtraction, average baseline subtraction with no threshold. " << endl;
  //}
  //else if (Baseline==PedestalSub::AvgWithThreshNoPedSub) {
  //  cout << "Average baseline+pedestal subtraction with threshold: " << Threshold << endl;
  //}
  //else if (Baseline==PedestalSub::Percentile) {
  //  cout << "Percentile-based pedestal subtraction ";
  //  if (Quantile<0 || Quantile>1) {
  //    cout << endl << "Quantile value out of range. Not running." << endl;
  //    exit(1);
  //  }
  //  else  {
  //    cout << "with quantile value: " << Quantile << endl;
  //  }
  //}
  //
  //if (Time_Slew==HcalTimeSlew::TestStand) cout << "Using test stand medium WP time slew parameterization." << endl;
  //else cout << "Sorry, I don't know which time slew correction you asked for." << endl;
  //
  //if (Neg_Charges==HLTv2::DoNothing) cout << "Not requiring positive charge outputs." << endl;
  //else cout << "Requiring positive charge outputs." << endl;

  //tTime = tree;

  return; 
}

void Analysis::Process() {
  if (fChain == 0) return;

  if (Entries==-1) Entries=fChain->GetEntries();

  //std::cout << Entries << std::endl;

  fout = new TFile(Output_File.c_str(), "RECREATE");

  tout = new TTree("Events", "Events");
  

  DoHlt();
}

void Analysis::DoHlt() {

  //=========================================================================      
  // These are the values we should set for Method 2 config with the python files
  // Don't currently have a setup to input with python but we shouldn't have to
  // change these values for our tests
  
  // --------------------------------------------------------------------
  bool iPedestalConstraint = true;
  bool iTimeConstraint = false;
  bool iAddPulseJitter = false;
  bool iUnConstrainedFit = false;
  bool iApplyTimeSlew = true;
  double iTS4Min = 5.;
  double iTS4Max = 500.;
  double iPulseJitter = 1.;
  double iTimeMean = 0;
  double iTimeSig = 5.;
  double iPedMean = 0.;
  double iPedSig = 0.5;
  double iNoise = 1.;
  double iTMin = -50.;
  double iTMax = 50.;
  double its3Chi2 = 10000.;
  double its4Chi2 = 10000.;
  double its345Chi2 = 10000.;
  double iChargeThreshold = 6.;
  int iFitTimes = 1;
    
  //========================================================================
  // Set the Method 2 Parameters here
  psFitOOTpuCorr_->setPUParams(iPedestalConstraint,iTimeConstraint,iAddPulseJitter,iUnConstrainedFit,
			       iApplyTimeSlew,iTS4Min, iTS4Max, iPulseJitter,iTimeMean,iTimeSig,
			       iPedMean,iPedSig,iNoise,iTMin,iTMax,its3Chi2,its4Chi2,its345Chi2,
			       iChargeThreshold,HcalTimeSlew::Medium, iFitTimes);
  
  // Now set the Pulse shape type
  psFitOOTpuCorr_->setPulseShapeTemplate(theHcalPulseShapes_.getShape(105));

  Slowboat_->Init(20.0, 5.0, 1.0, 5.0);
  
  //Setup HLT pedestal/baseline subtraction module
  //pedSubFxn_->Init(((PedestalSub::Method)Baseline), Condition, Threshold, Quantile);
  //pedSubFxn_->Init(((PedestalSub::Method)1), Condition, 2.7, 0.0);

  //hltv2_->Init(HcalTimeSlew::MC, HcalTimeSlew::Medium, (HLTv2::NegStrategy)2, *pedSubFxn_); // Greg's correction

  Int_t iphi, ieta, depth;
  Int_t TS[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Double_t Pulse[10];
  Double_t Ped[10];

  Double_t trigTime=0, ttcL1=0, bchTime0=0, s1Time0=0;
  //Double_t bchTime[10];
  //Double_t s1Time[10];

  Double_t m2Charge, m2Time, m2Ped, m2Chi;
  Double_t m2Pulse[10];

  Double_t wTime;

  Double_t slow0, slow1, slow2, slow3;
  Double_t slowPulse[10];

  //tTime->SetBranchAddress("triggerTime", &trigTime);
  //tTime->SetBranchAddress("ttcL1Atime",  &ttcL1);
  //tTime->SetBranchAddress("bchTime",     &bchTime);
  //tTime->SetBranchAddress("s1Time",      &s1Time);

  tout->Branch("iphi",  &iphi,  "iphi/I");
  tout->Branch("ieta",  &ieta,  "ieta/I");
  tout->Branch("depth", &depth, "depth/I");
  tout->Branch("TS",    &TS,    "TS[10]/I");
  tout->Branch("pulse", &Pulse, "pulse[10]/D");
  tout->Branch("ped",   &Ped,   "ped[10]/D");

  //tout->Branch("triggerTime", &trigTime, "triggerTime/D");
  //tout->Branch("ttcL1Atime",  &ttcL1,    "ttcL1Atime/D");
  //tout->Branch("bchTime",     &bchTime0, "bchTime/D");
  //tout->Branch("s1Time",      &s1Time0,  "s1Time/D");

  tout->Branch("m2Charge", &m2Charge, "m2Charge/D");
  tout->Branch("m2Time",   &m2Time,   "m2Time/D");
  tout->Branch("m2Ped",    &m2Ped,    "m2Ped/D");
  tout->Branch("m2Chi",    &m2Chi,    "m2Chi/D");
  tout->Branch("m2Pulse",  &m2Pulse,  "m2Pulse[10]/D");

  tout->Branch("wTime", &wTime, "wTime/D");

  tout->Branch("slow0", &slow0, "slow0/D");
  tout->Branch("slow1", &slow1, "slow1/D");
  tout->Branch("slow2", &slow2, "slow2/D");
  tout->Branch("slow3", &slow3, "slow3/D");
  tout->Branch("slowPulse", &slowPulse, "slowPulse[10]/D");
  
  //Loop over all events
  for (int jentry=0; jentry<Entries;jentry++) {

    fChain->GetEntry(jentry);
    //tTime->GetEntry(jentry);

    //s1Time0=s1Time[0];
    //bchTime0=bchTime[0];

    for (int j = 0; j < (int)PulseCount; j++) {

      if (IEta[j]>16 && Region==Barrel) continue;
      if (IEta[j]<17 && Region==Endcap) continue;

      std::vector<double> inputCaloSample, inputPedestal, inputGain;                                                           
      std::vector<double> offlineAns, slowAns;
      
      ieta=IEta[j]; iphi=IPhi[j]; depth=Depth[j];

      //float sum=0;
      //for (uint i=0; i<10; i++) sum+=Charge[j][i];
      //
      //if (sum<50) continue;
      //
      //bool filter=true;
      //int npeak=0;
      //
      //for (int i=0; i<10; i++) {
      //	if (Charge[j][i]>15) {
      //	  if (i==0) {
      //	    filter=false;
      //	    if (Charge[j][0]>Charge[j][1]) npeak++;
      //	  } if (i==9) {
      //	    filter=false;
      //	    if (Charge[j][9]>Charge[j][8]) npeak++;
      //	  } else {
      //	    if (Charge[j][i]>Charge[j][i+1] && Charge[j][i]>Charge[j][i-1]) npeak++;
      //	  }
      //	}
      //}
      //if (npeak>1) filter=false;
      //
      //if (filter==false) continue;

      wTime=0;
      Double_t temp=0;

      for (int i=0; i<10; i++) {
	inputCaloSample.push_back(Charge[j][i]+Pedestal[j][i]);
	inputPedestal.push_back(Pedestal[j][i]);
	inputGain.push_back(Gain[j][i]);
      	//inputCaloSample.push_back(pulse[j][i]);
      	//inputPedestal.push_back(0);
      	//inputGain.push_back(1.0);
      	
      	Pulse[i]=Charge[j][i]+Pedestal[j][i];
	Ped[i]=Pedestal[j][i];

	wTime+=i*Pulse[i];
	temp+=Pulse[i];

      }

      wTime=wTime/temp;

      psFitOOTpuCorr_->apply(inputCaloSample,inputPedestal,inputGain,offlineAns);

      m2Charge=offlineAns[0];
      m2Time=offlineAns[1];
      m2Ped=offlineAns[2];
      m2Chi=offlineAns[3];

      for (uint i=0; i<offlineAns.size(); i++) {
      	if (i>3 && uint(i-4) < 10) {
      	  m2Pulse[uint(i-4)] = offlineAns[i];
      	}
      }

      //Slowboat_->apply(inputCaloSample,inputPedestal,slowAns);
      
      slow0=0;//slowAns[0];
      slow1=0;//slowAns[1];
      slow2=0;//slowAns[2];
      slow3=0;//slowAns[3];
      
      for (uint i=0; i<slowAns.size(); i++) {
      	if (i>3 && uint(i-4) < 10) {
      	  slowPulse[uint(i-4)] = 0;//slowAns[i];
      	}
      }

      tout->Fill();
    }
  }

}

void Analysis::Finish()
{

  fout->cd();
  fout->Write();
  fout->Close();
}
