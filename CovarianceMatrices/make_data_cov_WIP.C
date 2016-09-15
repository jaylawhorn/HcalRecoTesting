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

void make_data_cov(TString fname = "root://eoscms//store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/HighPtJet80/Samples/160522_083815/0000/HCALTree_111.root", TString oname = "HCALTree_111.root") {

  //TTree *fChain;

  //TFile *f = new TFile("QCD_MC.root");
  //TFile *f = new TFile("OURN_hin_data.root");
  //fChain = (TTree*) f->Get("ExportTree/HcalTree");

  TChain *fChain = new TChain("ExportTree/HcalTree");
  fChain->AddFile(fname);

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

  double TS_avg_noise_HB[10];
  double TS_rms_noise_HB[10];
  double TS_avg_noise_HE[10];
  double TS_rms_noise_HE[10];
  double TS_cov_noise_HB[10][10];
  double TS_cov_noise_HE[10][10];

  for (int i=0; i<10; i++) { 
    TS_avg_HB[i]=0;
    TS_rms_HB[i]=0;
    TS_avg_HE[i]=0;
    TS_rms_HE[i]=0;

    TS_avg_noise_HB[i]=0;
    TS_rms_noise_HB[i]=0;
    TS_avg_noise_HE[i]=0;
    TS_rms_noise_HE[i]=0;

    for (int j=0; j<10; j++) {
      TS_cov_HB[i][j]=0;
      TS_cov_HE[i][j]=0;

      TS_cov_noise_HB[i][j]=0;
      TS_cov_noise_HE[i][j]=0;
    }
  }

  double noiseCor[10][10];
  for (int i=0; i<10; i++) {
    noiseCor[i][i] = 1;

    for (int j=0; j<i; j++) {
      if (abs(i-j)==1) {
	noiseCor[i][j] = -0.396341;
	noiseCor[j][i] = -0.396341;
      }
      else if (abs(i-j)==2) {
	noiseCor[i][j] = -0.0172;
	noiseCor[j][i] = -0.0172;
      }
      else if (abs(i-j)%2==1) {
	noiseCor[i][j] = -0.016;
	noiseCor[j][i] = -0.016;
      }
      else {
	noiseCor[i][j] = 0.016;
	noiseCor[j][i] = 0.016;
      }
    }
  }


  TFile *of = new TFile(oname,"recreate");
  TTree *t = new TTree("cor","");

  t->Branch("nhits_HB",&nhits_HB,"nhits_HB/LL");
  t->Branch("nhits_HE",&nhits_HE,"nhits_HE/LL");
  
  t->Branch("TS_sum_HB",&TS_avg_HB,"TS_sum_HB[10]/D");
  t->Branch("TS_sum_HE",&TS_avg_HE,"TS_sum_HE[10]/D");

  t->Branch("TS_sumSq_HB",&TS_rms_HB,"TS_sumSq_HB[10]/D");
  t->Branch("TS_sumSq_HE",&TS_rms_HE,"TS_sumSq_HE[10]/D");

  t->Branch("TS_xSum_HB",&TS_cov_HB,"TS_xSum_HB[10][10]/D");
  t->Branch("TS_xSum_HE",&TS_cov_HE,"TS_xSum_HE[10][10]/D");

  t->Branch("TS_sum_noise_HB",&TS_avg_noise_HB,"TS_sum_noise_HB[10]/D");
  t->Branch("TS_sum_noise_HE",&TS_avg_noise_HE,"TS_sum_noise_HE[10]/D");

  t->Branch("TS_sumSq_noise_HB",&TS_rms_noise_HB,"TS_sumSq_noise_HB[10]/D");
  t->Branch("TS_sumSq_noise_HE",&TS_rms_noise_HE,"TS_sumSq_noise_HE[10]/D");

  t->Branch("TS_xSum_noise_HB",&TS_cov_noise_HB,"TS_xSum_noise_HB[10][10]/D");
  t->Branch("TS_xSum_noise_HE",&TS_cov_noise_HE,"TS_xSum_noise_HE[10][10]/D");

  TH1D *hSum = new TH1D("hSum","",50,100,200);

  cout << nentries << endl;

  //for (Long64_t jentry=floor(nentries/2); jentry<nentries;jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = fChain->LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (jentry%10000 ==0) cout << "ientry = " << jentry << endl;

    for (int k=0; k<5184; k++) {

      Double_t sumQ=0;
      for (UInt_t j=0; j<10; j++) { sumQ+=Charge[k][j]; }//+Pedestal[k][j];}
      
      if (sumQ<100 || sumQ>200) continue;
      //else if (Charge[k][4]+Pedestal[k][4]<20) continue;
      else if (Charge[k][4]<20) continue;

      if (abs(IEta[k])<15) {
	nhits_HB++;
	hSum->Fill(sumQ);
	for (int i=0; i<10; i++) {

	  //Double_t qi=(Charge[k][i]+Pedestal[k][i])/(Charge[k][4]+Pedestal[k][4]);
	  Double_t qi=(Charge[k][i])/(Charge[k][4]);
	  TS_avg_HB[i]+=qi;
	  TS_rms_HB[i]+=qi*qi;

	  //Double_t ni=Pedestal[k][i]/(Charge[k][4]+Pedestal[k][4]);
	  Double_t ni=Pedestal[k][i]/(Charge[k][4]);
	  TS_avg_noise_HB[i]+=ni;
	  TS_rms_noise_HB[i]+=ni*ni;

	  for (int j=0; j<i+1; j++) {
	    //Double_t qj=(Charge[k][j]+Pedestal[k][j])/(Charge[k][4]+Pedestal[k][4]);
	    Double_t qj=(Charge[k][j])/(Charge[k][4]);

	    TS_cov_HB[i][j]+=qi*qj;
	    //TS_cov_noise_HB[i][j]+=noiseCor[i][j]/(Charge[k][4]+Pedestal[k][4])/(Charge[k][4]+Pedestal[k][4]);
	    TS_cov_noise_HB[i][j]+=noiseCor[i][j]/(Charge[k][4])/(Charge[k][4]);

	  }
	}
      }
      else if (abs(IEta[k])>18 && abs(IEta[k])<28) {
	nhits_HE++;

	for (int i=0; i<10; i++) {

	  //Double_t qi=(Charge[k][i]+Pedestal[k][i])/(Charge[k][4]+Pedestal[k][4]);
	  Double_t qi=(Charge[k][i])/(Charge[k][4]);
	  TS_avg_HE[i]+=qi;
	  TS_rms_HE[i]+=qi*qi;

	  //Double_t ni=Pedestal[k][i]/(Charge[k][4]+Pedestal[k][4]);
	  Double_t ni=Pedestal[k][i]/(Charge[k][4]);
	  TS_avg_noise_HE[i]+=ni;
	  TS_rms_noise_HE[i]+=ni*ni;

	  for (int j=0; j<i+1; j++) {
	    //Double_t qj=(Charge[k][j]+Pedestal[k][j])/(Charge[k][4]+Pedestal[k][4]);
	    Double_t qj=(Charge[k][j])/(Charge[k][4]);

	    TS_cov_HE[i][j]+=qi*qj;
	    //TS_cov_noise_HE[i][j]+=noiseCor[i][j]/(Charge[k][4]+Pedestal[k][4])/(Charge[k][4]+Pedestal[k][4]);
	    TS_cov_noise_HE[i][j]+=noiseCor[i][j]/(Charge[k][4])/(Charge[k][4]);
	  }
	}
      }

    }
  }

  //cout<< nhits_HB << endl;

  /*  for (int i=0; i<10; i++) {
    TS_avg_HB[i]/=nhits_HB;
    TS_rms_HB[i]/=nhits_HB;
    TS_rms_HB[i]=sqrt(TS_rms_HB[i]-TS_avg_HB[i]*TS_avg_HB[i]);

    TS_avg_noise_HB[i]/=nhits_HB;
    TS_rms_noise_HB[i]/=nhits_HB;
    TS_rms_noise_HB[i]=sqrt(TS_rms_noise_HB[i]-TS_avg_noise_HB[i]*TS_avg_noise_HB[i]);

  }

  //cout << endl;
  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {
      //TS_cov_HB[i][j]-=TS_cov_noise_HB[i][j];
      TS_cov_HB[i][j]/=nhits_HB;
      TS_cov_HB[i][j]-=TS_avg_HB[i]*TS_avg_HB[j];
    }
  }

  for (int i=0; i<10; i++) {
    cout << i << ", " << sqrt(TS_cov_HB[i][i]) << ", " << TS_rms_HB[i] << endl;
    for (int j=0; j<10; j++) {
      TS_cov_HB[i][j]/=sqrt(TS_cov_HB[i][i]*TS_cov_HB[j][j]);
      if (i==4 || j==4) TS_cov_HB[i][j]=0;
    }
  }

  //cout << endl << endl;

  for (int i=0; i<10; i++) {
    TS_avg_HE[i]/=nhits_HE;
    TS_rms_HE[i]/=nhits_HE;
    TS_rms_HE[i]=sqrt(TS_rms_HE[i]-TS_avg_HE[i]*TS_avg_HE[i]);

    TS_avg_noise_HE[i]/=nhits_HE;
    TS_rms_noise_HE[i]/=nhits_HE;
    TS_rms_noise_HE[i]=sqrt(TS_rms_noise_HE[i]-TS_avg_noise_HE[i]*TS_avg_noise_HE[i]);

  }

  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {
      //TS_cov_HE[i][j]-=TS_cov_noise_HE[i][j];
      TS_cov_HE[i][j]/=nhits_HE;
      TS_cov_HE[i][j]-=TS_avg_HE[i]*TS_avg_HE[j];
    }
  }

  for (int i=0; i<10; i++) {
    cout << i << ", " << sqrt(TS_cov_HE[i][i]) << ", " << TS_rms_HE[i] << endl;
      for (int j=0; j<10; j++) {
	TS_cov_HE[i][j]/=sqrt(TS_cov_HE[i][i]*TS_cov_HE[j][j]);
	if (i==4 || j==4) TS_cov_HE[i][j]=0;
      }
      }*/
  
  t->Fill();
  of->Write();
  of->Close();

}

/*
void getNoiseCor(double *noiseCor) {

  for (int i=0; i<10; i++) {
    noiseCor[i][i] = 1;

    for (int j=0; j<i; j++) {      
      if (abs(i-j)==1) {
	noiseCor[i][j] = -0.396341;
	noiseCor[j][i] = -0.396341;
      }
      else if (abs(i-j)==2) {
	noiseCor[i][j] = -0.0172;
	noiseCor[j][i] = -0.0172;
      }
      else if (abs(i-j)%2==1) {
	noiseCor[i][j] = -0.016;
	noiseCor[j][i] = -0.016;
      }
      else {
	noiseCor[i][j] = 0.016;
	noiseCor[j][i] = 0.016;
      }
    }
  }

}  
*/
