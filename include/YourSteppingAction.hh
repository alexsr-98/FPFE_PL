#ifndef YOURSTEPPINGACTION_HH
#define YOURSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class YourDetectorConstruction;
class YourEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles and
/// updated in YourEventAction.

class YourSteppingAction : public G4UserSteppingAction
{
public:
  YourSteppingAction(const YourDetectorConstruction* detectorConstruction,
                    YourEventAction* eventAction);
  virtual ~YourSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const YourDetectorConstruction* fDetConstruction;
  YourEventAction*  fEventAction;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif