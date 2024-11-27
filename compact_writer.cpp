// Script to write BDT results to all trees in all .root files in the given directory
// To run (change directory!):
// .L BDTApplication.C+
// BDT calibration file is defined in BDT_ApplyFile(). Names of variables in BDT_ApplyFile() 
// and BDT_ApplyTree() must be the same.
// BDT_ApplyDirectory("/share/users/okuchins/WVZ/code_generator/full_stack/all_region_2/latest_v7_fit_inputs/MC16a")

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TH1F.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TSystemDirectory.h"
#include "utility.h"


using namespace TMVA;

//vector<float> * lepton_pt;
//vector<float> * lepton2_pt;
//vector<float> * lepton3_pt;
//vector<float> * jet_pt;

Float_t lep1Z_pt_var, lep2Z_pt_var, lep3_pt_var, Z_pt_var, W_pt_var, jj_Pt_var, jj_Pz_var, jj_dR_var, sumPz_var, best_Z_Mll, DeltaJet01_var,  dPhi_Wjj_Zll, dR_Wjj_Zll, jet_tot_invMass, notWjjCand_leadJet_eta, notWjjCand_leadJet_pt, dPhi_Wlv_Zll, dR_Zll_other_l, Zll_leadJet_dR, dPhi_Wjj_Wlv, best_Z_Mjj; 



Float_t Mlll012, Mll01,Mll02,Mll12, leadJet_pt, MET_RefFinal_et, MET_RefFinal_phi, HT_lep, HT_had,HT, leptons_jets_MET_tot_invMass, subleadJet_pt;

vector<float>  * lepton_pt;

vector<float>  * lepton_eta;
vector<float>  * lepton_phi;

vector<float>  * jet_pt;
vector<float>  * jet_eta;
vector<float>  * jet_phi;


Float_t mll_1_var;
Float_t mll_2_var;

Float_t Zll_leadJet_invMass, Mjj01, M_T_Wlv, Zll_subleadJet_invMass_var;
Float_t best_W_Mjj, smallest_Mjj;
Float_t my_MCchannelNumber, my_total_charge, my_nJets_OR;
Int_t total_charge, nJets_OR;
//Float_t total_charge, my_total_charge;
UInt_t MCchannelNumber;
//Float_t MCchannelNumber;

TString PAIR="lpair(Mll01, Mll02, Mll12, best_Z_Mll),";
TString LEPTONS="lepton_pt[0], lepton_pt[1], lepton_pt[2], lepton_eta[0], lepton_eta[1], lepton_eta[2], lepton_phi[0], lepton_phi[1], lepton_phi[2]";
TString LEPTONS1="lepton_pt[0], lepton_pt[1], lepton_eta[0], lepton_eta[1], lepton_phi[0], lepton_phi[1]";

void BDTG_ApplyTree( TTree *tree_WORK , TMVA::Reader *reader )
{
   // create a set of variables and declare them to the reader
   // - the variable names must corresponds in name and type to
   // those given in the weight file(s) that you use
  

   float newBDTG_32_3l3j_1;
   TBranch *b_newBDTG_32_3l3j_1 = tree_WORK->Branch("newBDTG_32_3l3j_1",&newBDTG_32_3l3j_1,"newBDTG_32_3l3j_1/F");

   // prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   tree_WORK->SetBranchAddress("best_Z_Mll", &best_Z_Mll );
   tree_WORK->SetBranchAddress( "HT_lep",               &HT_lep );
   tree_WORK->SetBranchAddress( "HT_had",               &HT_had );
   tree_WORK->SetBranchAddress( "HT",                   &HT );
   tree_WORK->SetBranchAddress( "leadJet_pt",           &leadJet_pt );
   tree_WORK->SetBranchAddress( "lepton_pt",            &lepton_pt );
   tree_WORK->SetBranchAddress( "leptons_jets_MET_tot_invMass",&leptons_jets_MET_tot_invMass );
   tree_WORK->SetBranchAddress( "M_T_Wlv",              &M_T_Wlv );
   tree_WORK->SetBranchAddress( "MET_RefFinal_et",      &MET_RefFinal_et ); // tree_WORK->SetBranchAddress( "mll_1",              &mll_1_var);
   tree_WORK->SetBranchAddress( "Mlll012",		&Mlll012 );
   tree_WORK->SetBranchAddress( "subleadJet_pt",        &subleadJet_pt );
   tree_WORK->SetBranchAddress( "total_charge",         &total_charge );
   tree_WORK->SetBranchAddress( "Zll_leadJet_invMass",  &Zll_leadJet_invMass );
   tree_WORK->SetBranchAddress( "best_W_Mjj",           &best_W_Mjj );
   tree_WORK->SetBranchAddress( "smallest_Mjj",         &smallest_Mjj );
   tree_WORK->SetBranchAddress( "nJets_OR",             &nJets_OR );
   tree_WORK->SetBranchAddress( "best_Z_Mjj",             &best_Z_Mjj );
   tree_WORK->SetBranchAddress( "dPhi_Wjj_Zll",             &dPhi_Wjj_Zll );
   tree_WORK->SetBranchAddress( "dR_Wjj_Zll",             &dR_Wjj_Zll );
   tree_WORK->SetBranchAddress( "dPhi_Wjj_Wlv",             &dPhi_Wjj_Wlv );
   tree_WORK->SetBranchAddress( "jet_tot_invMass",             &jet_tot_invMass );
   tree_WORK->SetBranchAddress( "notWjjCand_leadJet_eta",             &notWjjCand_leadJet_eta );
   tree_WORK->SetBranchAddress( "notWjjCand_leadJet_pt",             &notWjjCand_leadJet_pt );
   tree_WORK->SetBranchAddress( "dPhi_Wlv_Zll",             &dPhi_Wlv_Zll );
   tree_WORK->SetBranchAddress( "dR_Zll_other_l",             &dR_Zll_other_l );
   tree_WORK->SetBranchAddress( "Zll_leadJet_dR",             &Zll_leadJet_dR );
   // tree_WORK->SetBranchAddress( "Z_pt",             &Z_pt_var );
   // tree_WORK->SetBranchAddress( "W_pt",             &W_pt_var );
   // tree_WORK->SetBranchAddress( "jj_Pt",             &jj_Pt_var );
   // tree_WORK->SetBranchAddress( "jj_Pz",             &jj_Pz_var );
   // tree_WORK->SetBranchAddress( "jj_dR",             &jj_dR_var );
   // tree_WORK->SetBranchAddress( "sumPz",             &sumPz_var );
   // tree_WORK->SetBranchAddress( "DeltaJet01",        &DeltaJet01_var );  
   TStopwatch sw;
   sw.Start();

   for (Long64_t ievt=0; ievt<tree_WORK->GetEntries();ievt++) {
      if (ievt%2000 == 0){
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      tree_WORK->GetEntry(ievt);
      mll_1_var = mll_1( Mll01, Mll02, Mll12, best_Z_Mll) ;
      mll_2_var =mll_2(Mll01, Mll02, Mll12, best_Z_Mll);

      lep1Z_pt_var = lep1Z_pt( lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2]);
      lep2Z_pt_var =lep2Z_pt(lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2]);
      lep3_pt_var =lep3_pt (lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2]);

      Z_pt_var =Z_pt( lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2], (*lepton_eta)[0], (*lepton_eta)[1], (*lepton_eta)[2], (*lepton_phi)[0], (*lepton_phi)[1], (*lepton_phi)[2] );
      W_pt_var =W_pt( lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2], (*lepton_eta)[0], (*lepton_eta)[1], (*lepton_eta)[2], (*lepton_phi)[0], (*lepton_phi)[1], (*lepton_phi)[2], MET_RefFinal_et, MET_RefFinal_phi);
      jj_Pt_var =jj_Pt((*jet_pt)[0], (*jet_pt)[1], (*jet_eta)[0], (*jet_eta)[1], (*jet_phi)[0], (*jet_phi)[1]);
      jj_Pz_var =jj_Pz((*jet_pt)[0], (*jet_pt)[1], (*jet_eta)[0], (*jet_eta)[1], (*jet_phi)[0], (*jet_phi)[1]);
      jj_dR_var =jj_dR((*jet_eta)[0], (*jet_eta)[1], (*jet_phi)[0], (*jet_phi)[1]);
      sumPz_var =sumPz((*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2], (*lepton_eta)[0], (*lepton_eta)[1], (*lepton_eta)[2], (*lepton_phi)[0], (*lepton_phi)[1], (*lepton_phi)[2], (*jet_pt)[0],(*jet_pt)[1],(*jet_eta)[0],(*jet_eta)[1],(*jet_phi)[0],(*jet_phi)[1]);
      Zll_subleadJet_invMass_var = Zll_subleadJet_invMass( lpair(Mll01, Mll02, Mll12, best_Z_Mll), (*lepton_pt)[0], (*lepton_pt)[1], (*lepton_pt)[2], (*lepton_eta)[0], (*lepton_eta)[1], (*lepton_eta)[2], (*lepton_phi)[0], (*lepton_phi)[1],(*lepton_phi)[2], (*jet_pt)[1], (*jet_eta)[1], (*jet_phi)[1]);
      DeltaJet01_var = DeltaJet01((*jet_phi)[0],(*jet_phi)[1]);
     
      my_total_charge=total_charge;
      my_MCchannelNumber=MCchannelNumber;
//      my_nJets_OR=nJets_OR;

      newBDTG_32_3l3j_1=reader->EvaluateMVA("BDTG");
      b_newBDTG_32_3l3j_1->Fill();
      }
   tree_WORK->Write("", TObject::kOverwrite); // save only the new version of the tree
   
   
   // get elapsed time
   sw.Stop();
   std::cout << "--- End of tree event loop: "; sw.Print();
}

// Write BDT to all tree in the given file
// 
//
void BDTG_ApplyFile(const char * FILE="VH.root")
{

   TMVA::Tools::Instance();
   // create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   lepton_pt = new vector<float>(20);
   //lepton_pt = new vector<float>(20);
   //lepton2_pt = new vector<float>(20);
   //lepton3_pt = new vector<float>(20);
   jet_pt    = new vector<float>(20);
   

   reader->AddVariable( "best_Z_Mll",           &best_Z_Mll );
//   reader->AddVariable( "DeltaJet01(jet_phi[0],jet_phi[1])",        &DeltaJet01_var );
   reader->AddVariable( "HT",                   &HT );
   reader->AddVariable( "HT_had",               &HT_had );
   reader->AddVariable( "HT_lep",               &HT_lep );
  // reader->AddVariable( "jet_eta[0]",           &(*jet_eta)[0] );
  // reader->AddVariable( "jet_eta[1]",           &(*jet_eta)[1] );
  // reader->AddVariable( "jj_dR(jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_dR_var );
   //reader->AddVariable( "jj_Pt(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_Pt_var );
   //reader->AddVariable( "jj_Pz(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_Pz_var );
   reader->AddVariable( "leadJet_pt",           &leadJet_pt );
   reader->AddVariable( "lep1Z_pt(" +PAIR+ "lepton_pt[0], lepton_pt[1], lepton_pt[2])",         &lep1Z_pt_var );
   reader->AddVariable( "lep2Z_pt(" +PAIR+ "lepton_pt[0], lepton_pt[1], lepton_pt[2])",         &lep2Z_pt_var );
   reader->AddVariable( "lep3_pt (" +PAIR+ "lepton_pt[0], lepton_pt[1], lepton_pt[2])",         &lep3_pt_var );
   reader->AddVariable( "leptons_jets_MET_tot_invMass", &leptons_jets_MET_tot_invMass);
   reader->AddVariable( "M_T_Wlv",              &M_T_Wlv );
   reader->AddVariable( "MET_RefFinal_et",      &MET_RefFinal_et);
   //reader->AddVariable( "Mjj01",                &Mjj01 );
   reader->AddVariable( "mll_1(Mll01, Mll02, Mll12, best_Z_Mll)",               &mll_1_var );
   reader->AddVariable( "mll_2(Mll01, Mll02, Mll12, best_Z_Mll)",               &mll_2_var );
   reader->AddVariable( "Mlll012",              &Mlll012);
   reader->AddVariable( "subleadJet_pt",        &subleadJet_pt );
   //reader->AddVariable( "sumPz(" + LEPTONS + ",jet_pt[0],jet_pt[1],jet_eta[0],jet_eta[1],jet_phi[0],jet_phi[1])",     &sumPz_var );
   reader->AddVariable( "total_charge",         &my_total_charge );
   reader->AddVariable( "W_pt(" + PAIR + LEPTONS + ",MET_RefFinal_et, MET_RefFinal_phi)",     &W_pt_var );
   reader->AddVariable( "Zll_leadJet_invMass",        &Zll_leadJet_invMass );
 //  reader->AddVariable( "Zll_subleadJet_invMass(" + PAIR + LEPTONS + ",jet_pt[1], jet_eta[1], jet_phi[1])", &Zll_subleadJet_invMass_var );
   reader->AddVariable( "Z_pt(" + PAIR + LEPTONS + ")",     &Z_pt_var );
  // reader->AddSpectator( "MCchannelNumber",	&my_MCchannelNumber);
   reader->AddVariable( "nJets_OR",     &my_nJets_OR );
  // reader->AddSpectator( "MET_RefFinal_phi",  	&MET_RefFinal_phi);
   reader->AddVariable( "best_W_Mjj",   &best_W_Mjj );
   reader->AddVariable( "smallest_Mjj", &smallest_Mjj );

   reader->AddVariable( "best_Z_Mjj", &best_Z_Mjj );
   reader->AddVariable( "dPhi_Wjj_Zll", &dPhi_Wjj_Zll );
   reader->AddVariable( "dR_Wjj_Zll", &dR_Wjj_Zll );
   reader->AddVariable( "dPhi_Wjj_Wlv", &dPhi_Wjj_Wlv );
   reader->AddVariable( "jet_tot_invMass", &jet_tot_invMass );
   reader->AddVariable( "notWjjCand_leadJet_eta", &notWjjCand_leadJet_eta );
   reader->AddVariable( "notWjjCand_leadJet_pt", &notWjjCand_leadJet_pt );
   reader->AddVariable( "dPhi_Wlv_Zll", &dPhi_Wlv_Zll );
   reader->AddVariable( "dR_Zll_other_l", &dR_Zll_other_l );
   reader->AddVariable( "Zll_leadJet_dR", &Zll_leadJet_dR );
   

  // reader->AddVariable( "Z_pt(" + PAIR + LEPTONS + ")",     &Z_pt_var );
  // reader->AddVariable( "W_pt(" + PAIR + LEPTONS + ",MET_RefFinal_et, MET_RefFinal_phi)",     &W_pt_var );
  // reader->AddVariable( "jj_Pt(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_Pt_var );
  // reader->AddVariable( "jj_Pz(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_Pz_var );
   //reader->AddVariable( "jj_dR(jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])",     &jj_dR_var );
  // reader->AddVariable( "sumPz(" + LEPTONS + ",jet_pt[0],jet_pt[1],jet_eta[0],jet_eta[1],jet_phi[0],jet_phi[1])",     &sumPz_var );
  // reader->AddVariable( "Zll_subleadJet_invMass(" + PAIR + LEPTONS + ",jet_pt[1], jet_eta[1], jet_phi[1])", &Zll_subleadJet_invMass_var );
   // book the MVA methods
   //TString weightfile  = "/share/users/okuchins/dataset/weights/TMVAClassification_BDTG.weights.xml";
   //TString weightfile  = "/share/users/okuchins/WVZ/myProject/dataset/weights/TMVAClassification_BDTG.weights.xml";
   TString weightfile  = "/share/users/okuchins/WVZ/code_generator/full_stack/all_region_2/3_jets/dataset/weights/TMVAClassification_BDTG.weights.xml";
   TString methodName  = "BDTG";

   reader->BookMVA( methodName, weightfile );

   //----Simple version!
   //TString maindir = "/eos/atlas/atlascerngroupdisk/phys-sm/WVZ_Run2/latest_v7_fit_inputs";
   //TFile *file_WORK = TFile::Open( maindir + "/nominal/VH.root", "update" );
   //TTree *tree_WORK = (TTree*)file_WORK->Get("nominal");
   //BDT_ApplyTree(tree_WORK,reader);
   //------------------------------------------------------------------------

   
   //TString maindir = "/eos/home-v/vkost/WVZ_Run2";
   //TFile *file_WORK = TFile::Open( maindir + "/nominal/"+FILE+".root", "update" );
   TFile *file_WORK = TFile::Open( FILE, "update" );
   TList * TreesInFile=file_WORK->GetListOfKeys();
   vector<string> nameTrees(0);
   for(const auto && curtree: *TreesInFile){      nameTrees.push_back(string(curtree->GetName()));  }

   for( auto & name : nameTrees){
      std::cout<<" Write to "<<FILE<<"/"<<name;
      TTree *tree_WORK = (TTree*)file_WORK->Get(name.c_str());
      std::cout << "-- Processing: " << tree_WORK->GetEntries() << " events" << std::endl;
      BDTG_ApplyTree(tree_WORK,reader);
   }
 
   file_WORK->Close();

   delete reader;
   //delete lepton_pt;
   //delete jet_pt;
}

//======================================================
//  Write BDT to all .root files in the given directory 
//
//
void BDTG_ApplyDirectory(const char *DIRE="/share/users/okuchins/WVZ/code_generator/full_stack/all_region_2/latest_v7_fit_inputs/MC16a")
//void BDTG1_ApplyDirectory(const char *DIRE="/share/users/okuchins/TRexProblem/WVZ_Run2/data")
{
  vector<TString> listOfFiles(0);
  TSystemDirectory dir(DIRE, DIRE);
  TList *files = dir.GetListOfFiles();
  if (files) { 
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (!file->IsDirectory() && fname.EndsWith(".root"))  listOfFiles.push_back(fname);
    }
  }
  for(auto & file : listOfFiles) {
    std::cout<<TString(DIRE)+file<<'\n';
    BDTG_ApplyFile((TString(DIRE)+"/"+file).Data());
  }
}


void BDTApplicationBDTG_fullvariables() 

{
lepton_pt = new vector<float>(20);

lepton_eta = new vector<float>(20);
lepton_phi = new vector<float>(20);

jet_pt = new vector<float>(20);
jet_eta = new vector<float>(20);
jet_phi = new vector<float>(20);

  BDTG_ApplyDirectory("/share/users/okuchins/WVZ/code_generator/full_stack/all_region_2/latest_v7_fit_inputs/MC16a");

delete lepton_pt;
delete lepton_eta;
delete lepton_phi;

delete jet_pt;
delete jet_eta;
delete jet_phi;

  //BDTG2_ApplyDirectory("/share/users/okuchins/TRexProblem/WVZ_Run2/MC16a");
}
