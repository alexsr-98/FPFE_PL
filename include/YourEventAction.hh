#ifndef YOUREVENTACTION_HH
#define YOUREVENTACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles:
/// - fEnergy, fTrackL
/// which are collected step by step via the function
/// - Add()

class YourEventAction : public G4UserEventAction
{
  public:
    YourEventAction();
    virtual ~YourEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void Add(G4double de, G4double dl);

    
  private:
    G4double  fEnergy;
    G4double  fTrackL; 

};

// inline functions

inline void YourEventAction::Add(G4double de, G4double dl) {
  fEnergy += de; 
  fTrackL += dl;
}
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
