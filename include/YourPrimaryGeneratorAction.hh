#ifndef YOURPRIMARYGENERATORACTION_HH 
#define YOURPRIMARYGENERATORACTION_HH 

#include "G4VUserPrimaryGeneratorAction.hh" 


#include "globals.hh"

class YourDetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;

class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction { 

public: 

   YourPrimaryGeneratorAction(YourDetectorConstruction* det); 
   virtual ~YourPrimaryGeneratorAction(); 

 
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
   G4ParticleGun*  fParticleGun; // pointer to a G4 gun class
   YourDetectorConstruction* fYourDetector; 

};

#endif