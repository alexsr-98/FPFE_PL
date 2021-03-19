#include "YourDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "YourDetectorMessenger.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

YourDetectorConstruction::YourDetectorConstruction() 
: G4VUserDetectorConstruction(), fTargetMaterial(nullptr), 
    fTargetPhysicalVolume(nullptr) {
  // set default target material
  SetTargetMaterial("G4_Si");
  
  // set default target thickness
  fTargetThickness = 1.0*CLHEP::cm;
  fDetMessenger    = new YourDetectorMessenger(this);
}

YourDetectorConstruction::~YourDetectorConstruction() {
delete fDetMessenger;
}


G4VPhysicalVolume* YourDetectorConstruction::Construct() {

  G4double zet        = 1.0; 
  G4double amass    = 1.01*CLHEP::g/CLHEP::mole; 
  G4double density  = CLHEP::universe_mean_density; 
  G4double pressure = 3.0E-18*CLHEP::pascal; 
  G4double temp     = 2.73*CLHEP::kelvin; 
  G4Material* materialWorld = new G4Material("Galactic", zet, amass, density, kStateGas, temp, pressure); 
  
  
  //-----WORLD-------
  G4double worldXSize = fTargetThickness * 8;
  G4double worldYSize = fTargetThickness * 8;
  G4double worldZSize = fTargetThickness * 8;
  
  
  G4Box* worldSolid = new G4Box( "solid-World",   // name 
                                0.5*worldXSize,  // box half x-size 
                                0.5*worldYSize, // box half y-size 
                                0.5*worldZSize // box half z-size 
                              );   

  G4LogicalVolume* worldLogical = new G4LogicalVolume( worldSolid,    // solid 
                                                     materialWorld, // material 
                                                    "logic-World"  // name 
                                                     );
                                                     
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement( nullptr,                    // (no) rotation 
                                                        G4ThreeVector(0., 0., 0.),  // translation 
                                                        worldLogical,               // logical volume 
                                                        "World",                    // name 
                                                        nullptr,                    // mother volume (!) 
                                                        false,                      // don't care 
                                                        0                           // cpy number 
                                                      );  
  //-----WORLD-------
  
  //-----TARGET------
  G4double targetXSize = fTargetThickness;
  G4double targetYSize = 3*fTargetThickness;
  G4double targetZSize = 3*fTargetThickness;
  fGunXPosition = -3.0*fTargetThickness; 
  G4Box* targetSolid = new G4Box( "solid-target",   // name 
                                0.5*targetXSize,  // box half x-size 
                                0.5*targetYSize, // box half y-size 
                                0.5*targetZSize // box half z-size 
                              );   

  G4LogicalVolume* targetLogical = new G4LogicalVolume( targetSolid,    // solid 
                                                     fTargetMaterial, // material 
                                                    "logic-Target"  // name 
                                                     );
                                                     
  G4VPhysicalVolume* targetPhysical = new G4PVPlacement( nullptr,                    // (no) rotation 
                                                        G4ThreeVector(0., 0., 0.),  // translation 
                                                        targetLogical,               // logical volume 
                                                        "Target",                    // name 
                                                        worldLogical,                    // mother volume (!) 
                                                        false,                      // don't care 
                                                        0                           // cpy number 
                                                      );
  //-----TARGET------
  
  fTargetPhysicalVolume = targetPhysical;
  return worldPhysical;
}
