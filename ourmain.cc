#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"


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
  
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a=12.01*g/mole);
  
//  // create the isotopes: iz = number of protons and n=number of nucleons 
//  G4Isotope* U5 = new G4Isotope(name="U235", iz=92, n=235); 
//  G4Isotope* U8 = new G4Isotope(name="U238", iz=92, n=238); 
//  
//  // create the element and build up by adding the isotopes with their abundance:  
//  G4Element* elU = new G4Element(name="Enriched Uranium", symbol="U", numisotopes=2); 
//  elU->AddIsotope(U5,abundance=90.*perCent); 
//  elU->AddIsotope(U8,abundance=10.*perCent); 
  
  
  return 0;
}
