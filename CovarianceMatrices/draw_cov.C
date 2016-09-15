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

void draw_cov(
	      TString infile = "test.root", 
	      TString label = "test"
	      //TString infile = "COV_qcd_mc.root", 
	      //TString label = "qcd"
	      //TString infile = "COV_ped_run_dat.root", 
	      //TString label = "ped_run"
	      //TString infile = "COV_empty_mc.root", 
	      //TString label = "empty"
	      ) {

  TFile *inf = new TFile(infile,"read");
  TTree *t = (TTree*) inf->Get("cor");

  double nhits_HB=0, nhits_HE=0;
  double TS_avg_HB[10];
  double TS_rms_HB[10];
  double TS_avg_HE[10];
  double TS_rms_HE[10];
  double TS_cov_HB[10][10];
  double TS_cov_HE[10][10];

  t->SetBranchAddress("nhits_HB", &nhits_HB );
  t->SetBranchAddress("nhits_HE", &nhits_HE );
  t->SetBranchAddress("TS_avg_HB",&TS_avg_HB);
  t->SetBranchAddress("TS_avg_HE",&TS_avg_HE);
  t->SetBranchAddress("TS_rms_HB",&TS_rms_HB);
  t->SetBranchAddress("TS_rms_HE",&TS_rms_HE);
  t->SetBranchAddress("TS_cov_HB",&TS_cov_HB);
  t->SetBranchAddress("TS_cov_HE",&TS_cov_HE);

  t->GetEntry(0);

  TCanvas *c = new TCanvas("c","",800, 800);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  gStyle->SetPaintTextFormat("2.2f");

  TH2D* corr_matrix_hb = new TH2D("corr_matrix_hb","",10,-0.5,9.5,10,-0.5,9.5);
  TH1D* avg_hist_hb = new TH1D("avg_hist_hb","",10,-0.5,9.5);
  TH1D* rms_hist_hb = new TH1D("rms_hist_hb","",10,-0.5,9.5);


  TH2D* corr_matrix_he = new TH2D("corr_matrix_he","",10,-0.5,9.5,10,-0.5,9.5);
  TH1D* avg_hist_he = new TH1D("avg_hist_he","",10,-0.5,9.5);
  TH1D* rms_hist_he = new TH1D("rms_hist_he","",10,-0.5,9.5);


  for (int i=0; i<10; i++) {
    avg_hist_hb->SetBinContent(i+1,TS_avg_HB[i]);
    rms_hist_hb->SetBinContent(i+1,TS_rms_HB[i]);

    avg_hist_he->SetBinContent(i+1,TS_avg_HE[i]);
    rms_hist_he->SetBinContent(i+1,TS_rms_HE[i]);
  }


  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      corr_matrix_hb->SetBinContent( 
				    corr_matrix_hb->GetBin(i+1, j+1),
				    TS_cov_HB[i][j]);

      corr_matrix_hb->SetBinContent( 
				    corr_matrix_hb->GetBin(j+1, i+1),
				    TS_cov_HB[i][j]);

      corr_matrix_he->SetBinContent( 
				    corr_matrix_he->GetBin(i+1, j+1),
				    TS_cov_HE[i][j]);

      corr_matrix_he->SetBinContent( 
				    corr_matrix_he->GetBin(j+1, i+1),
				    TS_cov_HE[i][j]);

    }
  }

  corr_matrix_hb->GetZaxis()->SetRangeUser(-1,1);
  corr_matrix_hb->GetXaxis()->SetTitle("Time Slice");
  corr_matrix_hb->GetYaxis()->SetTitle("Time Slice");
  corr_matrix_hb->Draw("colz text");

  c->SaveAs(label+"_hb_cov.png");

  avg_hist_hb->GetXaxis()->SetTitle("Time Slice");
  avg_hist_hb->GetYaxis()->SetTitle("Average");
  avg_hist_hb->Draw("hist");

  c->SaveAs(label+"_hb_avg.png");

  rms_hist_hb->GetXaxis()->SetTitle("Time Slice");
  rms_hist_hb->GetYaxis()->SetTitle("RMS");
  rms_hist_hb->Draw("hist");

  c->SaveAs(label+"_hb_rms.png");

  corr_matrix_he->GetZaxis()->SetRangeUser(-1,1);
  corr_matrix_he->GetXaxis()->SetTitle("Time Slice");
  corr_matrix_he->GetYaxis()->SetTitle("Time Slice");
  corr_matrix_he->Draw("colz text");

  c->SaveAs(label+"_he_cov.png");

  avg_hist_he->GetXaxis()->SetTitle("Time Slice");
  avg_hist_he->GetYaxis()->SetTitle("Average");
  avg_hist_he->Draw("hist");

  c->SaveAs(label+"_he_avg.png");

  rms_hist_he->GetXaxis()->SetTitle("Time Slice");
  rms_hist_he->GetYaxis()->SetTitle("RMS");
  rms_hist_he->Draw("hist");

  c->SaveAs(label+"_he_rms.png");

}
