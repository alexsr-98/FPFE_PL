#include "YourDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

YourDetectorConstruction::YourDetectorConstruction() 
: G4VUserDetectorConstruction() {
  // set default target material
  G4String matName = "G4_Si";
  fTargetMaterial  = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (fTargetMaterial == nullptr) {
    G4cerr << "  ERROR YourDetectorConstruction() \n" 
           << "  Material with name " << matName << " was not found! \n"
           << G4endl;
  }
  // set default target thickness
  fTargetThickness = 1.0*CLHEP::cm;
  

    
}

YourDetectorConstruction::~YourDetectorConstruction() {}


G4VPhysicalVolume* YourDetectorConstruction::Construct() {

  G4double zet        = 1.0; 
  G4double amass    = 1.01*CLHEP::g/CLHEP::mole; 
  G4double density  = CLHEP::universe_mean_density; 
  G4double pressure = 3.0E-18*CLHEP::pascal; 
  G4double temp     = 2.73*CLHEP::kelvin; 
  G4Material* materialWorld = new G4Material("Galactic", zet, amass, density, kStateGas, temp, pressure); 
  
  
  //-----WORLD-------
  G4double worldXSize = fTargetThickness * 4;
  G4double worldYSize = fTargetThickness * 4;
  G4double worldZSize = fTargetThickness * 4;
  
  
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
  G4double targetYSize = fTargetThickness;
  G4double targetZSize = fTargetThickness;
  
  G4Box* targetSolid = new G4Box( "solid-target",   // name 
                                0.5*targetXSize,  // box half x-size 
                                0.5*targetYSize, // box half y-size 
                                0.5*targetZSize // box half z-size 
                              );   

  G4LogicalVolume* targetLogical = new G4LogicalVolume( targetSolid,    // solid 
                                                     fTargetMaterial, // material 
                                                    "logic-target"  // name 
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
  
  return 0;
}
