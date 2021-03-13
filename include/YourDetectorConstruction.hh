#ifndef YOURDETECTORCONSTRUCTION_HH
#define YOURDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4NistManager.hh"

class G4Material;

class YourDetectorConstruction : public G4VUserDetectorConstruction {
public: 
  YourDetectorConstruction();
  virtual ~YourDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  //Some methods:
  
  //----GUN POSITION---- 
  void SetGunXPosition(G4double GunXPosition){
  fGunXPosition = GunXPosition;
  };
  
  G4double GetGunXPosition(){
  return fGunXPosition;
  };
  //----GUN POSITION----
  //----TARGET THICKNESS----
  void SetTargetThickness(const G4double thick) { fTargetThickness = thick; }
  G4double GetTargetThickness() const { return fTargetThickness;  }  
  //----TARGET THICKNESS----
  //----TARGET MATERIAL----
  void SetTargetMaterial(const G4String& matName) {
      // try to find the material in the NIST DB
  fTargetMaterial  = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (fTargetMaterial == nullptr) {
    G4cerr << "  ERROR YourDetectorConstruction() \n" 
           << "  Material with name " << matName << " was not found! \n"
           << G4endl; }
  }
  const G4Material* GetTargetMaterial() const  { return fTargetMaterial; }
  //----TARGET MATERIAL----
  //----TARGET PHYSICAL VOLUME----
  const G4VPhysicalVolume* GetTargetPhysicalVolume() const { 
        return fTargetPhysicalVolume; 
    } 
  //----TARGET PHYSICAL VOLUME---- 
  
private:
  
  G4Material* fTargetMaterial;   
  G4double    fGunXPosition;
  G4double    fTargetThickness;
  G4VPhysicalVolume*     fTargetPhysicalVolume;
};

#endif
