#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"

using namespace CLHEP;

int main() {
  
  // the code must go here
  // this is some example to play with
  // try here all the commands that we saw in class
  
  const G4String elName = "Al";
  G4NistManager::Instance()->PrintElement(elName);
  
  const G4String matCName = "simple";
  G4NistManager::Instance()->ListMaterials(matCName);
  
  const G4String matName = "G4_Si";
  const G4Material* theSi = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (theSi != nullptr) {
    G4cout << theSi << G4endl;
  } else {
    G4cout << " nothing: " << matName << G4endl;
  }
  
  G4Element* elC = new G4Element("Carbon", "C", 6., 12.01*g/mole);
  G4cout << elC << G4endl;
  
  // create the isotopes: iz = number of protons and n=number of nucleons 
  G4Isotope* U5 = new G4Isotope("U235", 92, 235); 
  G4Isotope* U8 = new G4Isotope("U238", 92, 238); 

  // create the element and build up by adding the isotopes with their abundance:  
  G4Element* elU = new G4Element("Enriched Uranium", "U", 2); 
  elU->AddIsotope(U5, 90.*perCent); 
  elU->AddIsotope(U8, 10.*perCent);
  
  G4cout << elU << G4endl;
  
  G4Material* matU = new G4Material("Uranium", 92, 238.03*g/mole, 18.950*g/cm3); 
  G4cout << matU << G4endl;
  
  
  G4NistManager* nistMGR = G4NistManager::Instance(); 
  // get the pre-defined liquid argon (“G4_lAr”) from the NIST DB 
  G4Material* matLAr = nistMGR->FindOrBuildMaterial("G4_lAr"); 

  // get the pre-defined concrete (“G4_CONCRETE”) from the NIST DB 
  G4Material* matConcr = nistMGR->FindOrBuildMaterial("G4_CONCRETE"); 

  G4cout << matLAr << G4endl;
  G4cout << matConcr << G4endl;
  return 0;
}
