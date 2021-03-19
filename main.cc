#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"
#include "YourDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "YourActionInitialization.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv){
  
  // Detect interactive mode (if no arguments) and define UI: 
  G4UIExecutive* ui=0;
  if (argc ==1 ){
    ui = new G4UIExecutive(argc,argv, "Qt");
  }
  
  //1. create the RunManager object 
  G4RunManager* runManager = new G4RunManager(); 
  
  //2. Create an object from YourDetectorConstruction and register in the Run-Manager 
  YourDetectorConstruction* detector = new YourDetectorConstruction(); 
  runManager->SetUserInitialization( detector ); 
  
  //3. Create/obtain an Physics List and register it in the Run-Manager 
  G4PhysListFactory physListFactory; 
  const G4String plName = "FTFP_BERT"; 
  G4VModularPhysicsList* pl = G4PhysListFactory().GetReferencePhysList( plName ); 
  runManager->SetUserInitialization( pl );

  //4. Create your action initialization and register in the Run-Manager 
  runManager->SetUserInitialization( new YourActionInitialization( detector ) );
  
  
  
  // Initialization of the visualization 
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    ui->SessionStart();
    delete ui;
  }
  

//  // initialization of the run 
//  runManager->Initialize(); 
//
//  // add verbosity 
//  G4EventManager::GetEventManager()->GetTrackingManager()->SetVerboseLevel(1); 
//
//  // simulate 10 events 
//  runManager->BeamOn(10); 

  // delete the Run-manager 
  delete runManager; 
  delete visManager;
  
  return 0;
}


// Sugerencias para ampliacion: poner campo magnetico, crear un detector un poco mas complejo

