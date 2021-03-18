#include "YourDetectorMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "YourDetectorConstruction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"

YourDetectorMessenger::YourDetectorMessenger(YourDetectorConstruction* det):   
    G4UImessenger(), 
    fYourDetector(det), 
    fDirCMD(nullptr), 
    fTargetThicknessCMD(nullptr),
    fTargetMaterialCMD(nullptr){

fDirCMD = new G4UIdirectory("/yourApp/det/");
fDirCMD->SetGuidance("UI commands to define the detector construction of this application");

//Set the target thickness
fTargetThicknessCMD = new G4UIcmdWithADoubleAndUnit("/yourApp/det/setTargetThickness", this);
fTargetThicknessCMD->SetGuidance("Sets the thickness of the Target.");
fTargetThicknessCMD->SetParameterName("TargetSizeX",false);
fTargetThicknessCMD->SetRange("TargetSizeX>0.");
fTargetThicknessCMD->SetUnitCategory("Length");
fTargetThicknessCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
fTargetThicknessCMD->SetToBeBroadcasted(false);

// Set target material (NIST material i.e. with G4_ prefix)
fTargetMaterialCMD  = new G4UIcmdWithAString("/yourApp/det/setTargetMaterial",this);
fTargetMaterialCMD->SetGuidance("Sets the Material of the Target.");
fTargetMaterialCMD->SetParameterName("TargetMaterial",false);  
fTargetMaterialCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
fTargetMaterialCMD->SetToBeBroadcasted(false);
}


YourDetectorMessenger::~YourDetectorMessenger() {
	delete fTargetThicknessCMD;
	delete fTargetMaterialCMD;
  delete fDirCMD;
}


void YourDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    // set target thickness
    if (command == fTargetThicknessCMD) { 
  	    G4double thickness = fTargetThicknessCMD->GetNewDoubleValue(newValue);
        fYourDetector->SetTargetThickness(thickness);
    }
    // set target material name 
    if (command == fTargetMaterialCMD) { 
        fYourDetector->SetTargetMaterial(newValue);
   }
}







