#ifndef YOURPRIMARYGENERATORACTION_HH 
#define YOURPRIMARYGENERATORACTION_HH 

#include "G4VUserPrimaryGeneratorAction.hh" 
#include "YourDetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
 



class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction { 

public: 

   YourPrimaryGeneratorAction(); 
   ~YourPrimaryGeneratorAction(); 

 
  virtual void GeneratePrimaries(G4Event*); 
  
  // method to access particle gun
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
 
  // Public method to get the primary particle name. 
  const G4String& GetParticleName() const; 

  // Public method to get the primary particle kinetic energy. 
  G4double GetParticleEnergy() const; 

  // Public method to set the default primary particle kinematics 
  void SetDefaultKinematic(); 

  // Public method to set the position of the particle gun: will be taken for the actual detector construction 
  void UpdatePosition();
 
 
 
private: 
   G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
   YourDetectorConstruction* fYourDetector; 

};

#endif