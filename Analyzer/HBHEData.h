//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 15 13:13:55 2016 by ROOT version 5.34/32
// from TTree Events/Events
// found on file: ana_h2_tb_run007480.root
//////////////////////////////////////////////////////////

#ifndef HBHEData_h
#define HBHEData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HBHEData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           numChs;
   Int_t           numTS;
   Int_t           iphi[16];   //[numChs]
   Int_t           ieta[16];   //[numChs]
   Int_t           depth[16];   //[numChs]
   Double_t        pulse[16][50];   //[numChs]
   Double_t        ped[16];   //[numChs]
   Double_t        pulse_adc[16][50];   //[numChs]
   Double_t        ped_adc[16];   //[numChs]

   // List of branches
   TBranch        *b_numChs;   //!
   TBranch        *b_numTS;   //!
   TBranch        *b_iphi;   //!
   TBranch        *b_ieta;   //!
   TBranch        *b_depth;   //!
   TBranch        *b_pulse;   //!
   TBranch        *b_ped;   //!
   TBranch        *b_pulse_adc;   //!
   TBranch        *b_ped_adc;   //!

   HBHEData(TTree *tree=0);
   ~HBHEData();
   Int_t    Cut(Long64_t entry);
   Int_t    GetEntry(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void     Init(TTree *tree);
   void     Loop();
   Bool_t   Notify();
   void     Show(Long64_t entry = -1);
};

#endif

#ifdef HBHEData_cxx
HBHEData::HBHEData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ana_h2_tb_run007480.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ana_h2_tb_run007480.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("ana_h2_tb_run007480.root:/HBHEData");
      dir->GetObject("Events",tree);

   }
   Init(tree);
}

HBHEData::~HBHEData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HBHEData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HBHEData::LoadTree(Long64_t entry)
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

void HBHEData::Init(TTree *tree)
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

   fChain->SetBranchAddress("numChs", &numChs, &b_numChs);
   fChain->SetBranchAddress("numTS", &numTS, &b_numTS);
   fChain->SetBranchAddress("iphi", iphi, &b_iphi);
   fChain->SetBranchAddress("ieta", ieta, &b_ieta);
   fChain->SetBranchAddress("depth", depth, &b_depth);
   fChain->SetBranchAddress("pulse", pulse, &b_pulse);
   fChain->SetBranchAddress("ped", ped, &b_ped);
   fChain->SetBranchAddress("pulse_adc", pulse_adc, &b_pulse_adc);
   fChain->SetBranchAddress("ped_adc", ped_adc, &b_ped_adc);
   Notify();
}

Bool_t HBHEData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HBHEData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HBHEData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HBHEData_cxx
