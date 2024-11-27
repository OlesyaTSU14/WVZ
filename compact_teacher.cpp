//  compact_teacher.cpp
//  Created by Olesia Kuchinskaia on 30/10/2021.
//  Script to train BDT results to all trees in all .root files in the given directory

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/DataLoader.h"
#include "utility.h"

using namespace std;

void compact_teacher() {
    TString maindir = "/share/shared_data/ntuples/latest_v7_fit_inputs";

    TFile *sig__MC16a_363507 = TFile::Open(maindir + "/MC16a/363507.root");
    TFile *sig__MC16a_363508 = TFile::Open(maindir + "/MC16a/363508.root");
    TFile *sig__MC16a_363509 = TFile::Open(maindir + "/MC16a/363509.root");
    TFile *sig__MC16a_364243 = TFile::Open(maindir + "/MC16a/364243.root");
    TFile *sig__MC16a_364245 = TFile::Open(maindir + "/MC16a/364245.root");
    TFile *sig__MC16a_364246 = TFile::Open(maindir + "/MC16a/364246.root");
    TFile *sig__MC16d_363507 = TFile::Open(maindir + "/MC16d/363507.root");
    TFile *sig__MC16d_363508 = TFile::Open(maindir + "/MC16d/363508.root");
    TFile *sig__MC16d_363509 = TFile::Open(maindir + "/MC16d/363509.root");
    TFile *sig__MC16d_364243 = TFile::Open(maindir + "/MC16d/364243.root");
    TFile *sig__MC16d_364245 = TFile::Open(maindir + "/MC16d/364245.root");
    TFile *sig__MC16d_364246 = TFile::Open(maindir + "/MC16d/364246.root");
    TFile *bkg__MC16a_345705 = TFile::Open(maindir + "/MC16a/345705.root");
    TFile *bkg__MC16a_345706 = TFile::Open(maindir + "/MC16a/345706.root");
    TFile *bkg__MC16a_364250 = TFile::Open(maindir + "/MC16a/364250.root");
    TFile *bkg__MC16a_364253 = TFile::Open(maindir + "/MC16a/364253.root");
    TFile *bkg__MC16a_410218 = TFile::Open(maindir + "/MC16a/410218.root");
    TFile *bkg__MC16a_410219 = TFile::Open(maindir + "/MC16a/410219.root");
    TFile *bkg__MC16a_410408 = TFile::Open(maindir + "/MC16a/410408.root");
    TFile *bkg__MC16d_345705 = TFile::Open(maindir + "/MC16d/345705.root");
    TFile *bkg__MC16d_345706 = TFile::Open(maindir + "/MC16d/345706.root");
    TFile *bkg__MC16d_364250 = TFile::Open(maindir + "/MC16d/364250.root");
    TFile *bkg__MC16d_364253 = TFile::Open(maindir + "/MC16d/364253.root");
    TFile *bkg__MC16d_410218 = TFile::Open(maindir + "/MC16d/410218.root");
    TFile *bkg__MC16d_410219 = TFile::Open(maindir + "/MC16d/410219.root");
    TFile *bkg__MC16d_410220 = TFile::Open(maindir + "/MC16d/410220.root");
    TFile *bkg__MC16d_410408 = TFile::Open(maindir + "/MC16d/410408.root");
    TFile *bkg__nominal_Zgamma = TFile::Open(maindir + "/nominal/Zgamma.root");
    TFile *bkg__nominal_Zjets = TFile::Open(maindir + "/nominal/Zjets.root");
    TFile *bkg__nominal_lllljj = TFile::Open(maindir + "/nominal/lllljj.root");
    TFile *bkg__nominal_lllvjj = TFile::Open(maindir + "/nominal/lllvjj.root");
    TFile *bkg__nominal_others = TFile::Open(maindir + "/nominal/others.root");
    TFile *bkg__nominal_tZ = TFile::Open(maindir + "/nominal/tZ.root");

    TFile *nominal_VH = TFile::Open(maindir + "/nominal/VH.root");

    TTree *tree_sig__MC16a_363507 = (TTree *)sig__MC16a_363507->Get("nominal");
    TTree *tree_sig__MC16a_363508 = (TTree *)sig__MC16a_363508->Get("nominal");
    TTree *tree_sig__MC16a_363509 = (TTree *)sig__MC16a_363509->Get("nominal");
    TTree *tree_sig__MC16a_364243 = (TTree *)sig__MC16a_364243->Get("nominal");
    TTree *tree_sig__MC16a_364245 = (TTree *)sig__MC16a_364245->Get("nominal");
    TTree *tree_sig__MC16a_364246 = (TTree *)sig__MC16a_364246->Get("nominal");
    TTree *tree_sig__MC16d_363507 = (TTree *)sig__MC16d_363507->Get("nominal");
    TTree *tree_sig__MC16d_363508 = (TTree *)sig__MC16d_363508->Get("nominal");
    TTree *tree_sig__MC16d_363509 = (TTree *)sig__MC16d_363509->Get("nominal");
    TTree *tree_sig__MC16d_364243 = (TTree *)sig__MC16d_364243->Get("nominal");
    TTree *tree_sig__MC16d_364245 = (TTree *)sig__MC16d_364245->Get("nominal");
    TTree *tree_sig__MC16d_364246 = (TTree *)sig__MC16d_364246->Get("nominal");
    TTree *tree_bkg__MC16a_345705 = (TTree *)bkg__MC16a_345705->Get("nominal");
    TTree *tree_bkg__MC16a_345706 = (TTree *)bkg__MC16a_345706->Get("nominal");
    TTree *tree_bkg__MC16a_364250 = (TTree *)bkg__MC16a_364250->Get("nominal");
    TTree *tree_bkg__MC16a_364253 = (TTree *)bkg__MC16a_364253->Get("nominal");
    TTree *tree_bkg__MC16a_410218 = (TTree *)bkg__MC16a_410218->Get("nominal");
    TTree *tree_bkg__MC16a_410219 = (TTree *)bkg__MC16a_410219->Get("nominal");
    TTree *tree_bkg__MC16a_410408 = (TTree *)bkg__MC16a_410408->Get("nominal");
    TTree *tree_bkg__MC16d_345705 = (TTree *)bkg__MC16d_345705->Get("nominal");
    TTree *tree_bkg__MC16d_345706 = (TTree *)bkg__MC16d_345706->Get("nominal");
    TTree *tree_bkg__MC16d_364250 = (TTree *)bkg__MC16d_364250->Get("nominal");
    TTree *tree_bkg__MC16d_364253 = (TTree *)bkg__MC16d_364253->Get("nominal");
    TTree *tree_bkg__MC16d_410218 = (TTree *)bkg__MC16d_410218->Get("nominal");
    TTree *tree_bkg__MC16d_410219 = (TTree *)bkg__MC16d_410219->Get("nominal");
    TTree *tree_bkg__MC16d_410220 = (TTree *)bkg__MC16d_410220->Get("nominal");
    TTree *tree_bkg__MC16d_410408 = (TTree *)bkg__MC16d_410408->Get("nominal");
    TTree *tree_bkg__nominal_Zgamma = (TTree *)bkg__nominal_Zgamma->Get("nominal");
    TTree *tree_bkg__nominal_Zjets = (TTree *)bkg__nominal_Zjets->Get("nominal");
    TTree *tree_bkg__nominal_lllljj = (TTree *)bkg__nominal_lllljj->Get("nominal");
    TTree *tree_bkg__nominal_lllvjj = (TTree *)bkg__nominal_lllvjj->Get("nominal");
    TTree *tree_bkg__nominal_others = (TTree *)bkg__nominal_others->Get("nominal");
    TTree *tree_bkg__nominal_tZ = (TTree *)bkg__nominal_tZ->Get("nominal");

    TTree *common_VH = (TTree*)nominal_VH->Get("nominal");

    TTree *tree_VH_bkg = common_VH->CopyTree("(!( (higgsDecayMode<-1) || ( ((MCchannelNumber==342284) && ((higgsDecayMode==1) || (higgsDecayMode==5))) || ((MCchannelNumber==342285) && (higgsDecayMode==1)) ) ))");
    TTree *tree_VH_sig = common_VH->CopyTree("( (higgsDecayMode<-1) || ( ((MCchannelNumber==342284) && ((higgsDecayMode==1) || (higgsDecayMode==5))) || ((MCchannelNumber==342285) && (higgsDecayMode==1)) ) )");
    

    TString outfileName("TMVA.root");
    TFile *outputFile = TFile::Open(outfileName, "RECREATE");

    TMVA::Factory *factory = new TMVA::Factory(
        "TMVAClassification", outputFile,
        "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

    TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

    dataloader->AddVariable("best_Z_Mll:=best_Z_Mll", "best_Z_Mll", "", 'F');
    dataloader->AddVariable("DeltaJet01_var:=DeltaJet01(jet_phi[0],jet_phi[1])", "DeltaJet01_var", "", 'F');
    dataloader->AddVariable("HT:=HT", "HT", "", 'F');
    dataloader->AddVariable("HT_had:=HT_had", "HT_had", "", 'F');
    dataloader->AddVariable("HT_lep:=HT_lep", "HT_lep", "", 'F');
    dataloader->AddVariable("jet_eta_0:=jet_eta[0]", "jet_eta_0", "", 'F');
    dataloader->AddVariable("jet_eta_1:=jet_eta[1]", "jet_eta_1", "", 'F');
    dataloader->AddVariable("jj_dR_var:=jj_dR(jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])", "jj_dR_var", "", 'F');
    dataloader->AddVariable("jj_Pt_var:=jj_Pt(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])", "jj_Pt_var", "", 'F');
    dataloader->AddVariable("jj_Pz_var:=jj_Pz(jet_pt[0], jet_pt[1], jet_eta[0], jet_eta[1], jet_phi[0], jet_phi[1])", "jj_Pz_var", "", 'F');
    dataloader->AddVariable("leadJet_pt:=leadJet_pt", "leadJet_pt", "", 'F');
    dataloader->AddVariable("lep1Z_pt_var:=lep1Z_pt(lpair(Mll01, Mll02, Mll12, best_Z_Mll),lepton_pt[0], lepton_pt[1], lepton_pt[2])", "lep1Z_pt_var", "", 'F');
    dataloader->AddVariable("lep2Z_pt_var:=lep2Z_pt(lpair(Mll01, Mll02, Mll12, best_Z_Mll),lepton_pt[0], lepton_pt[1], lepton_pt[2])", "lep2Z_pt_var", "", 'F');
    dataloader->AddVariable("lep3_pt_var:=lep3_pt (lpair(Mll01, Mll02, Mll12, best_Z_Mll),lepton_pt[0], lepton_pt[1], lepton_pt[2])", "lep3_pt_var", "", 'F');
    dataloader->AddVariable("leptons_jets_MET_tot_invMass:=leptons_jets_MET_tot_invMass", "leptons_jets_MET_tot_invMass", "", 'F');
    dataloader->AddVariable("M_T_Wlv:=M_T_Wlv", "M_T_Wlv", "", 'F');
    dataloader->AddVariable("MET_RefFinal_et:=MET_RefFinal_et", "MET_RefFinal_et", "", 'F');
    dataloader->AddVariable("Mjj01:=Mjj01", "Mjj01", "", 'F');
    dataloader->AddVariable("mll_1_var:=mll_1(Mll01, Mll02, Mll12, best_Z_Mll)", "mll_1_var", "", 'F');
    dataloader->AddVariable("mll_2_var:=mll_2(Mll01, Mll02, Mll12, best_Z_Mll)", "mll_2_var", "", 'F');
    dataloader->AddVariable("Mlll012:=Mlll012", "Mlll012", "", 'F');
    dataloader->AddVariable("subleadJet_pt:=subleadJet_pt", "subleadJet_pt", "", 'F');
    dataloader->AddVariable("sumPz_var:=sumPz(lepton_pt[0], lepton_pt[1], lepton_pt[2], lepton_eta[0], lepton_eta[1], lepton_eta[2], lepton_phi[0], lepton_phi[1], lepton_phi[2],jet_pt[0],jet_pt[1],jet_eta[0],jet_eta[1],jet_phi[0],jet_phi[1])", "sumPz_var", "", 'F');
    dataloader->AddVariable("total_charge:=total_charge", "total_charge", "", 'I');
    dataloader->AddVariable("W_pt_var:=W_pt(lpair(Mll01, Mll02, Mll12, best_Z_Mll),lepton_pt[0], lepton_pt[1], lepton_pt[2], lepton_eta[0], lepton_eta[1], lepton_eta[2], lepton_phi[0], lepton_phi[1], lepton_phi[2],MET_RefFinal_et, MET_RefFinal_phi)", "W_pt_var", "", 'F');
    dataloader->AddVariable("Zll_leadJet_invMass:=Zll_leadJet_invMass", "Zll_leadJet_invMass", "", 'F');
    dataloader->AddVariable("Zpt_var:=Z_pt(lpair(Mll01, Mll02, Mll12, best_Z_Mll),lepton_pt[0], lepton_pt[1], lepton_pt[2], lepton_eta[0], lepton_eta[1], lepton_eta[2], lepton_phi[0], lepton_phi[1], lepton_phi[2])", "Zpt_var", "", 'F');


    Double_t signalWeight = 1.0;
    Double_t backgroundWeight = 1.0;

    dataloader->AddSignalTree(tree_sig__MC16a_363507, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16a_363508, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16a_363509, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16a_364243, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16a_364245, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16a_364246, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_363507, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_363508, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_363509, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_364243, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_364245, signalWeight);
    dataloader->AddSignalTree(tree_sig__MC16d_364246, signalWeight);
    dataloader->AddSignalTree(tree_VH_sig, signalWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_345705, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_345706, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_364250, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_364253, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_410218, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_410219, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16a_410408, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_345705, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_345706, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_364250, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_364253, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_410218, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_410219, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_410220, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__MC16d_410408, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_Zgamma, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_Zjets, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_lllljj, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_lllvjj, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_others, backgroundWeight);
    dataloader->AddBackgroundTree(tree_bkg__nominal_tZ, backgroundWeight);
    dataloader->AddBackgroundTree(tree_VH_bkg, backgroundWeight);


    TCut mycuts = "( (passEventCleaning && passTrigger && isTrigMatched) && (@lepton_pt.size()==3) && (abs(total_charge)==1) && ((lepton_ID[0]!=-lepton_ID[1] || Mll01>12e3) && (lepton_ID[0]!=-lepton_ID[2] || Mll02>12e3) && (lepton_ID[1]!=-lepton_ID[2] || Mll12>12e3)) && ((lepton_ID[0]==-lepton_ID[1] && abs(Mll01-91.2e3)<10e3) || (lepton_ID[0]==-lepton_ID[2] && abs(Mll02-91.2e3)<10e3) || (lepton_ID[1]==-lepton_ID[2] && abs(Mll12-91.2e3)<10e3)) && ( (Mll12==best_Z_Mll && lepton_isTightLH[0] && lepton_ambiguityType[0]==0 && lepton_isolationFixedCutLoose[0] && ((lepton_PromptLeptonVeto[0]<-0.7 && abs(lepton_ID[0])==11) || (lepton_PromptLeptonVeto[0]<-0.5 && abs(lepton_ID[0])==13))) || (Mll02==best_Z_Mll && lepton_isTightLH[1] && lepton_ambiguityType[1]==0 && lepton_isolationFixedCutLoose[1] && ((lepton_PromptLeptonVeto[1]<-0.7 && abs(lepton_ID[1])==11) || (lepton_PromptLeptonVeto[1]<-0.5 && abs(lepton_ID[1])==13))) || (Mll01==best_Z_Mll && lepton_isTightLH[2] && lepton_ambiguityType[2]==0 && lepton_isolationFixedCutLoose[2] && ((lepton_PromptLeptonVeto[2]<-0.7 && abs(lepton_ID[2])==11) || (lepton_PromptLeptonVeto[2]<-0.5 && abs(lepton_ID[2])==13))) ) && (@jet_pt.size()!=0) && (nJets_mv2c10_70==0) && (lepton_pt[2]/1000.>15.) && ((HT_lep+HT_had)/1000.)>200. && (@jet_pt.size()==2)  )";

    TString baseWgt("( ((Mll12==best_Z_Mll)*lepton_SFObjTightLH[0]+(Mll12!=best_Z_Mll)*lepton_SFObjLoose[0])*((Mll02==best_Z_Mll)*lepton_SFObjTightLH[1]+(Mll02!=best_Z_Mll)*lepton_SFObjLoose[1])*((Mll01==best_Z_Mll)*lepton_SFObjTightLH[2]+(Mll01!=best_Z_Mll)*lepton_SFObjLoose[2]) ) *( (mcWeightOrg*xsec*(1./tot_weight)*pileupEventWeight*JVT_EventWeight*MV2c10_FixedCutBEff_70_EventWeight)*(36184.86*(RunYear<2016.5) + 43593.8*(RunYear>2016.5)) * ( 1 + (MCchannelNumber==364253)*( 0.05*(@jet_pt.size()==1) + (-0.02)*(@jet_pt.size()==2) + (-0.07)*(@jet_pt.size()>2) ) ) * ( 1 + (MCchannelNumber==364250 || MCchannelNumber==345705 || MCchannelNumber==345706)*( 0.04*(@jet_pt.size()==0 || @jet_pt.size()==1) + (-0.30)*(@jet_pt.size()==2) + (-0.36)*(@jet_pt.size()>2) ) ) )");
    TString regionWgt("( ( ((Mll12==best_Z_Mll)*lepton_SFObjTightLH[0]+(Mll12!=best_Z_Mll)*lepton_SFObjLoose[0])*((Mll02==best_Z_Mll)*lepton_SFObjTightLH[1]+(Mll02!=best_Z_Mll)*lepton_SFObjLoose[1])*((Mll01==best_Z_Mll)*lepton_SFObjTightLH[2]+(Mll01!=best_Z_Mll)*lepton_SFObjLoose[2]) ) )");

    dataloader->SetSignalWeightExpression(baseWgt + "*" + regionWgt);
    dataloader->SetBackgroundWeightExpression(baseWgt + "*" + regionWgt);

    TCut wgtLimitLow("(" + baseWgt + "*" + regionWgt + ")>-0.10");
    TCut wgtLimitHigh("(" + baseWgt + "*" + regionWgt + ")<0.07");

    TCut cutSignal = mycuts && wgtLimitHigh;
    TCut cutBackgr = mycuts && wgtLimitLow;

    dataloader->PrepareTrainingAndTestTree(cutSignal, cutBackgr, "SplitMode=Random:NormMode=NumEvents:!V");

    factory->BookMethod(
        dataloader, TMVA::Types::kBDT, "BDTG",
        "!H:!V:NTrees=715:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:NegWeightTreatment=IgnoreNegWeightsInTraining:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3");

    // Train MVAs using the set of training events
    factory->TrainAllMethods();

    // Evaluate all MVAs using the set of test events
    factory->TestAllMethods();

    // Evaluate and compare performance of all configured MVAs
    factory->EvaluateAllMethods();

    // Save the output
    outputFile->Close();

    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    delete factory;
    delete dataloader;
}
