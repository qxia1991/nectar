#include "PMRunAction.hh"

PMRunAction::PMRunAction()
    {
        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

        analysisManager->CreateH1("Edep","Energy deposit",100,0.,6*MeV, "MeV");

        analysisManager->CreateNtuple("Photons","Photons");
        analysisManager->CreateNtupleIColumn("iEvent");
        analysisManager->CreateNtupleDColumn("fX");
        analysisManager->CreateNtupleDColumn("fY");
        analysisManager->CreateNtupleDColumn("fZ");
        analysisManager->CreateNtupleDColumn("fGlobalTime");
        analysisManager->CreateNtupleDColumn("fWlen");
        analysisManager->FinishNtuple(0);

        analysisManager->SetDefaultFileType("root");
        analysisManager->SetNtupleMerging(true);
        analysisManager->SetVerboseLevel(1);
        analysisManager->SetFileName("output");
         // Set ntuple output file
        analysisManager->SetNtupleFileName(0, "output");
    }

PMRunAction::~PMRunAction()
{

}

void PMRunAction::BeginOfRunAction(const G4Run *run)
{
      // Get analysis manager
      auto analysisManager = G4AnalysisManager::Instance();
    // Reset histograms from previous run
    //analysisManager->Reset();
    //G4int runID = run->GetRunID();
    
    //std::stringstream strRunID;
    //strRunID<<runID;
    analysisManager->OpenFile();
}

void PMRunAction::EndOfRunAction(const G4Run*run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4int runID = run->GetRunID();
    G4cout<<"Finishing run "<<runID<<G4endl;
}