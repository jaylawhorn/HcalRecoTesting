#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TBenchmark.h>                   // class to track macro running statistics
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#endif

//#include "tree.h"

void make_noise_cov() {

  TTree *fChain;

  /*vector<float>   *HBHEDigiEta;
  vector<float>   *HBHEDigiPhi;
  vector<float>   *HBHEDigiRecEnergy;
  vector<float>   *HBHEDigiRecTime;*/
  vector<vector<float> > *HBHEDigiAllFC=0;
  vector<vector<float> > *HBHEDigiFC=0;
  vector<vector<float> > *HBHEDigiNomFC=0;
  vector<vector<float> > *HBHEDigiPedFC=0;
  vector<int>     *HBHEDigiDepth=0;
  vector<int>     *HBHEDigiIEta=0;
  vector<int>     *HBHEDigiIPhi=0;
  //vector<int>     *HBHEDigiSubdet;
  UInt_t          bx;
  UInt_t          event;
  UInt_t          ls;
  UInt_t          run;

  TFile *f = new TFile("USC_269836_unpacked.root");
  fChain = (TTree*) f->Get("hcalTupleTree/tree");

  if (fChain == 0) return;

  TBranch        *b_HBHEDigiAllFC = 0;   //!
  TBranch        *b_HBHEDigiFC = 0;   //!
  TBranch        *b_HBHEDigiNomFC = 0;   //!
  TBranch        *b_HBHEDigiPedFC = 0;   //!
  TBranch        *b_HBHEDigiDepth = 0;   //!
  TBranch        *b_HBHEDigiIEta = 0;   //!
  TBranch        *b_HBHEDigiIPhi = 0;   //!
  TBranch        *b_run = 0;   //!
  TBranch        *b_bx = 0;   //!
  TBranch        *b_event = 0;   //!
  TBranch        *b_ls = 0;   //!

  fChain->SetBranchAddress("HBHEDigiAllFC", &HBHEDigiAllFC, &b_HBHEDigiAllFC);
  fChain->SetBranchAddress("HBHEDigiFC", &HBHEDigiFC, &b_HBHEDigiFC);
  fChain->SetBranchAddress("HBHEDigiNomFC", &HBHEDigiNomFC, &b_HBHEDigiNomFC);
  fChain->SetBranchAddress("HBHEDigiPedFC", &HBHEDigiPedFC, &b_HBHEDigiPedFC);
  fChain->SetBranchAddress("HBHEDigiDepth", &HBHEDigiDepth, &b_HBHEDigiDepth);
  fChain->SetBranchAddress("HBHEDigiIEta", &HBHEDigiIEta, &b_HBHEDigiIEta);
  fChain->SetBranchAddress("HBHEDigiIPhi", &HBHEDigiIPhi, &b_HBHEDigiIPhi);
  fChain->SetBranchAddress("bx", &bx, &b_bx);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("ls", &ls, &b_ls);
  fChain->SetBranchAddress("run", &run, &b_run);

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  Long64_t nhits_HB=0, nhits_HE=0;

  double TS_avg_HB[10];
  double TS_rms_HB[10];
  double TS_avg_HE[10];
  double TS_rms_HE[10];
  double TS_cov_HB[10][10];
  double TS_cov_HE[10][10];

  for (int i=0; i<10; i++) {
    TS_avg_HB[i]=0;
    TS_rms_HB[i]=0;
    TS_avg_HE[i]=0;
    TS_rms_HE[i]=0;

    for (int j=0; j<10; j++) {
      TS_cov_HB[i][j]=0;
      TS_cov_HE[i][j]=0;
    }
  }

  TFile *of = new TFile("PED_RUN.root","recreate");
  TTree *t = new TTree("cor","");

  t->Branch("nhits_HB",&nhits_HB,"nhits_HB/D");
  t->Branch("nhits_HE",&nhits_HE,"nhits_HE/D");

  t->Branch("TS_avg_HB",&TS_avg_HB,"TS_avg_HB[10]/D");
  t->Branch("TS_avg_HE",&TS_avg_HE,"TS_avg_HE[10]/D");

  t->Branch("TS_rms_HB",&TS_rms_HB,"TS_rms_HB[10]/D");
  t->Branch("TS_rms_HE",&TS_rms_HE,"TS_rms_HE[10]/D");

  t->Branch("TS_cov_HB",&TS_cov_HB,"TS_cov_HB[10][10]/D");
  t->Branch("TS_cov_HE",&TS_cov_HE,"TS_cov_HE[10][10]/D");

  cout << nentries << endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = fChain->LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    for (uint k=0; k<HBHEDigiFC->size(); k++) {

      if (abs(HBHEDigiIEta->at(k))<15) {
        nhits_HB++;

        for (int i=0; i<10; i++) {

          Double_t qi=HBHEDigiFC->at(k).at(i);
          TS_avg_HB[i]+=qi;
          TS_rms_HB[i]+=qi*qi;

          for (int j=0; j<i+1; j++) {
            Double_t qj=HBHEDigiFC->at(k).at(j);

            TS_cov_HB[i][j]+=qi*qj;

          }
        }
      }
      else if (abs(HBHEDigiIEta->at(k))>18 && abs(HBHEDigiIEta->at(k))<28) {
        nhits_HE++;

	for (int i=0; i<10; i++) {

          Double_t qi=HBHEDigiFC->at(k).at(i);
          TS_avg_HE[i]+=qi;
          TS_rms_HE[i]+=qi*qi;

          for (int j=0; j<i+1; j++) {
            Double_t qj=HBHEDigiFC->at(k).at(j);

            TS_cov_HE[i][j]+=qi*qj;
          }
	}
      }
    }
  }

  for (int i=0; i<10; i++) {
    TS_avg_HB[i]/=nhits_HB;
    TS_rms_HB[i]/=nhits_HB;
    TS_rms_HB[i]=sqrt(TS_rms_HB[i]-TS_avg_HB[i]*TS_avg_HB[i]);
    cout << "HB " << i << ": " << TS_avg_HB[i] << ", " << TS_rms_HB[i] << endl;
  }

  cout << endl;
  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      TS_cov_HB[i][j]/=nhits_HB;
      TS_cov_HB[i][j]-=TS_avg_HB[i]*TS_avg_HB[j];
      TS_cov_HB[i][j]/=(TS_rms_HB[i]*TS_rms_HB[j]);
      cout << "HB " << i << ", " << j << ": " << TS_cov_HB[i][j] << endl;

    }
  }

  cout << endl << endl;

  for (int i=0; i<10; i++) {
    TS_avg_HE[i]/=nhits_HE;
    TS_rms_HE[i]/=nhits_HE;
    TS_rms_HE[i]=sqrt(TS_rms_HE[i]-TS_avg_HE[i]*TS_avg_HE[i]);
    cout << "HE " << i << ": " << TS_avg_HE[i] << ", " << TS_rms_HE[i] << endl;
  }

  cout << endl;
  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      TS_cov_HE[i][j]/=nhits_HE;
      TS_cov_HE[i][j]-=TS_avg_HE[i]*TS_avg_HE[j];
      TS_cov_HE[i][j]/=(TS_rms_HE[i]*TS_rms_HE[j]);
      cout << "HE " << i << ", " << j << ": " << TS_cov_HE[i][j] << endl;
    }
  }

  t->Fill();
  of->Write();
  of->Close();


}
