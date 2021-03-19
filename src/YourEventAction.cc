#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"


#include "Randomize.hh"
#include <iomanip>

#include "YourEventAction.hh"
#include "g4root.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YourEventAction::YourEventAction()
 : G4UserEventAction(),
   fEnergy(0.),
   fTrackL(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YourEventAction::~YourEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YourEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // initialisation per event
  fEnergy = 0.;
  fTrackL = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YourEventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fEnergy);
  analysisManager->FillH1(1, fTrackL);
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, fEnergy);
  analysisManager->FillNtupleDColumn(1, fTrackL);
  analysisManager->AddNtupleRow();  
  
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    G4cout
       << "       Total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergy,"Energy")
       << "       Total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackL,"Length")
       << G4endl;
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......