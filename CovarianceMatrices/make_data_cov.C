#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TChain.h>                        // class to access ntuples
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

void make_data_cov() {

  TTree *fChain;

  //TFile *f = new TFile("QCD_MC.root");
  TFile *f = new TFile("OURN_hin_data.root");
  fChain = (TTree*) f->Get("ExportTree/HcalTree");

  /*TChain *fChain = new TChain("ExportTree/HcalTree");
  
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_110.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_111.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_112.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_113.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_114.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_115.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_116.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_117.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_118.root");
  fChain->AddFile("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/Samples/160713_130517/0000/HCALTree_119.root");
  */
  if (fChain == 0) return;

  Double_t        Charge[5184][10];
  Double_t        Pedestal[5184][10];
  Double_t        Gain[5184][10];
  Int_t           IEta[5184];
  Int_t           IPhi[5184];
  Int_t           Depth[5184];

  TBranch        *b_Charge;   //!                                              
  TBranch        *b_Pedestal;   //!                                            
  TBranch        *b_Gain;   //!                                                
  TBranch        *b_IEta;   //!                                                
  TBranch        *b_IPhi;   //!                                                
  TBranch        *b_Depth;   //!   

  fChain->SetBranchAddress("Charge", Charge, &b_Charge);
  fChain->SetBranchAddress("Pedestal", Pedestal, &b_Pedestal);
  fChain->SetBranchAddress("Gain", Gain, &b_Gain);
  fChain->SetBranchAddress("IEta", IEta, &b_IEta);
  fChain->SetBranchAddress("IPhi", IPhi, &b_IPhi);
  fChain->SetBranchAddress("Depth", Depth, &b_Depth);

  Long64_t nentries = fChain->GetEntries();
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

  TFile *of = new TFile("test.root","recreate");
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

    if (jentry%10000 ==0) cout << "ientry = " << jentry << endl;

    for (int k=0; k<5184; k++) {

      Double_t sumQ=0;
      for (UInt_t j=0; j<10; j++) { sumQ+=Charge[k][j];}
      
      if (sumQ<100 || sumQ>200) continue;
      else if (Charge[k][4]<20) continue;

      if (abs(IEta[k])<15) {
	nhits_HB++;

	for (int i=0; i<10; i++) {

	  Double_t qi=Charge[k][i]/Charge[k][4];
	  TS_avg_HB[i]+=qi;
	  TS_rms_HB[i]+=qi*qi;

	  for (int j=0; j<i+1; j++) {
	    Double_t qj=Charge[k][j]/Charge[k][4];

	    TS_cov_HB[i][j]+=qi*qj;

	  }
	}
      }
      else if (abs(IEta[k])>18 && abs(IEta[k])<28) {
	nhits_HE++;

	for (int i=0; i<10; i++) {

	  Double_t qi=Charge[k][i]/Charge[k][4];
	  TS_avg_HE[i]+=qi;
	  TS_rms_HE[i]+=qi*qi;

	  for (int j=0; j<i+1; j++) {
	    Double_t qj=Charge[k][j]/Charge[k][4];

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
      //TS_cov_HB[i][j]/=(TS_rms_HB[i]*TS_rms_HB[j]);
      if (i==4 || j==4) TS_cov_HB[i][j]=0;
      //cout << "HB " << i << ", " << j << ": " << TS_cov_HB[i][j] << endl;
      cout << "array[" << i << "][" << j << "] = " << TS_cov_HB[i][j] << ";" <<endl;
      cout << "array[" << j << "][" << i << "] = " << TS_cov_HB[i][j] << ";" <<endl;

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
      //TS_cov_HE[i][j]/=(TS_rms_HE[i]*TS_rms_HE[j]);
      if (i==4 || j==4) TS_cov_HE[i][j]=0;
      cout << "HE " << i << ", " << j << ": " << TS_cov_HE[i][j] << endl;
    }
  }

  t->Fill();
  of->Write();
  of->Close();

}
