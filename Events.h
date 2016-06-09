//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 29 01:08:43 2016 by ROOT version 6.02/05
// from TTree Events/Events
// found on file: Output_Testbeam.root
//////////////////////////////////////////////////////////

#ifndef Events_h
#define Events_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Events {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          iphi;
   UInt_t          ieta;
   UInt_t          depth;
   Double_t        pulse[10];
   Double_t        ped[10];
   Double_t        triggerTime;
   Double_t        ttcL1Atime;
   Double_t        bchTime;
   Double_t        recoQ;
   Double_t        recoT;
   Double_t        recoP;
   Double_t        recoChi;
   Double_t        recoPulse[10];

   // List of branches
   TBranch        *b_iphi;   //!
   TBranch        *b_ieta;   //!
   TBranch        *b_depth;   //!
   TBranch        *b_pulse;   //!
   TBranch        *b_ped;   //!
   TBranch        *b_triggerTime;   //!
   TBranch        *b_ttcL1Atime;   //!
   TBranch        *b_bchTime;   //!
   TBranch        *b_recoQ;   //!
   TBranch        *b_recoT;   //!
   TBranch        *b_recoP;   //!
   TBranch        *b_recoChi;   //!
   TBranch        *b_recoPulse;   //!

   Events(TTree *tree=0);
   virtual ~Events();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_cxx
Events::Events(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Output_Testbeam.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Output_Testbeam.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

Events::~Events()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events::LoadTree(Long64_t entry)
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

void Events::Init(TTree *tree)
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

   fChain->SetBranchAddress("iphi", &iphi, &b_iphi);
   fChain->SetBranchAddress("ieta", &ieta, &b_ieta);
   fChain->SetBranchAddress("depth", &depth, &b_depth);
   fChain->SetBranchAddress("pulse", pulse, &b_pulse);
   fChain->SetBranchAddress("ped", ped, &b_ped);
   fChain->SetBranchAddress("triggerTime", &triggerTime, &b_triggerTime);
   fChain->SetBranchAddress("ttcL1Atime", &ttcL1Atime, &b_ttcL1Atime);
   fChain->SetBranchAddress("bchTime", &bchTime, &b_bchTime);
   fChain->SetBranchAddress("recoQ", &recoQ, &b_recoQ);
   fChain->SetBranchAddress("recoT", &recoT, &b_recoT);
   fChain->SetBranchAddress("recoP", &recoP, &b_recoP);
   fChain->SetBranchAddress("recoChi", &recoChi, &b_recoChi);
   fChain->SetBranchAddress("recoPulse", recoPulse, &b_recoPulse);
   Notify();
}

Bool_t Events::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_cxx
