#include "YourActionInitialization.hh" 
#include "YourPrimaryGeneratorAction.hh" 
#include "YourDetectorConstruction.hh" 
#include "globals.hh"
 

YourActionInitialization::YourActionInitialization(YourDetectorConstruction* det) 
:   G4VUserActionInitialization(){
    fYourDetector = det;  
    }


YourActionInitialization::~YourActionInitialization() {} 

 

// Create all User Actions here:  
// - for sequential mode (will be invoked immediately by the only one G4RunManager  
//   when the ActionInitialization object is registered in it in the main) 
// - for worker threads (will be invoked later by all worker G4RunManager-s)  

void YourActionInitialization::Build() const { 

  // Set UserPrimaryGeneratorAction 
  YourPrimaryGeneratorAction* primaryAction = new YourPrimaryGeneratorAction(fYourDetector); 
  SetUserAction(primaryAction); 
//  // Set UserRunAction 
//  YourRunAction* runAction = new YourRunAction(primaryAction); 
//  SetUserAction(runAction);  
//  // Set UserEventAction 
//  YourEventAction* eventAction = new YourEventAction(); 
//  SetUserAction(eventAction); 
//  // Set UserSteppingAction 
//  SetUserAction( new YourSteppingAction(fYourDetector, eventAction) ); 
}