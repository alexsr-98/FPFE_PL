#include "YourPrimaryGeneratorAction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"


YourPrimaryGeneratorAction::YourPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  // particle type: e- 
  G4ParticleDefinition* part = G4Electron::Definition(); 
  fParticleGun->SetParticleDefinition(part);
  
  // direction: 1,0,0 i.e. to the target 
  fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1.0, 0.0, 0.0) );  
  
  // kinetic energy:  30 MeV 
  fParticleGun->SetParticleEnergy(30.0*CLHEP::MeV); 
  
  // set postion 
  fParticleGun->SetParticlePosition( G4ThreeVector(fYourDetector->GetGunXPosition(), 0.0, 0.0) ); 
  
  
}

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction() {}

void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
fParticleGun->GeneratePrimaryVertex(anEvent);
}