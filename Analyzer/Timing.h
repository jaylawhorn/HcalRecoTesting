//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 15 13:14:11 2016 by ROOT version 5.34/32
// from TTree Events/Events
// found on file: ana_h2_tb_run007480.root
//////////////////////////////////////////////////////////

#ifndef Timing_h
#define Timing_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Timing {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           s1Count;
   Int_t           s2Count;
   Int_t           s3Count;
   Int_t           s4Count;
   Int_t           bcCount;
   Double_t        triggerTime;
   Double_t        ttcL1Atime;
   Double_t        qiePhase;
   Double_t        bchTime[5];   //[bcCount]
   Double_t        s1Time[5];   //[bcCount]

   // List of branches
   TBranch        *b_s1Count;   //!
   TBranch        *b_s2Count;   //!
   TBranch        *b_s3Count;   //!
   TBranch        *b_s4Count;   //!
   TBranch        *b_bcCount;   //!
   TBranch        *b_triggerTime;   //!
   TBranch        *b_ttcL1Atime;   //!
   TBranch        *b_qiePhase;   //!
   TBranch        *b_bchTime;   //!
   TBranch        *b_s1Time;   //!

   Timing(TTree *tree=0);
   virtual ~Timing();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Timing_cxx
Timing::Timing(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ana_h2_tb_run007480.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ana_h2_tb_run007480.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("ana_h2_tb_run007480.root:/Timing");
      dir->GetObject("Events",tree);

   }
   Init(tree);
}

Timing::~Timing()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Timing::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Timing::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Timing::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("s1Count", &s1Count, &b_s1Count);
   fChain->SetBranchAddress("s2Count", &s2Count, &b_s2Count);
   fChain->SetBranchAddress("s3Count", &s3Count, &b_s3Count);
   fChain->SetBranchAddress("s4Count", &s4Count, &b_s4Count);
   fChain->SetBranchAddress("bcCount", &bcCount, &b_bcCount);
   fChain->SetBranchAddress("triggerTime", &triggerTime, &b_triggerTime);
   fChain->SetBranchAddress("ttcL1Atime", &ttcL1Atime, &b_ttcL1Atime);
   fChain->SetBranchAddress("qiePhase", &qiePhase, &b_qiePhase);
   fChain->SetBranchAddress("bchTime", bchTime, &b_bchTime);
   fChain->SetBranchAddress("s1Time", s1Time, &b_s1Time);
   Notify();
}

Bool_t Timing::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Timing::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Timing::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Timing_cxx
