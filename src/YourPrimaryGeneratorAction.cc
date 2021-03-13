#include "YourPrimaryGeneratorAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include "globals.hh"

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction(YourDetectorConstruction* det)
: G4VUserPrimaryGeneratorAction()
{
  fYourDetector = det;
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  SetDefaultKinematic();
}

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction() {
delete fParticleGun;
}

void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
fParticleGun->GeneratePrimaryVertex(anEvent);
}

void YourPrimaryGeneratorAction::SetDefaultKinematic() {
  // particle type: e- 
  G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( "e-" );
  fParticleGun->SetParticleDefinition(part);
  
  // direction: 1,0,0 i.e. to the target 
  fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1.0, 0.0, 0.0) );  
  
  // kinetic energy:
  fParticleGun->SetParticleEnergy(200.0*CLHEP::MeV); 
  
  // set position
  UpdatePosition(); 
}

void YourPrimaryGeneratorAction::UpdatePosition() {
  fParticleGun->SetParticlePosition( G4ThreeVector( fYourDetector->GetGunXPosition(), 0.0, 0.0 ) );
}

const G4String& YourPrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}

G4double YourPrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}

