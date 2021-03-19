#ifndef YOURRUNACTION_HH
#define YOURRUNACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class YourPrimaryGeneratorAction;
/// Run action class
///
/// It accumulates statistic and computes dispersion of the energy deposit 
/// and track lengths of charged particles with use of analysis tools:
/// H1D histograms are created in BeginOfRunAction() for the following 
/// physics quantities:
/// - E deposit
/// - Track length
/// The same values are also saved in the ntuple.
/// The histograms and ntuple are saved in the output file in a root format
///
/// In EndOfRunAction(), the accumulated statistic and computed 
/// dispersion is printed.
///

class YourRunAction : public G4UserRunAction
{
  public:
    YourRunAction(YourPrimaryGeneratorAction* primaryAction);
    virtual ~YourRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
  
  private:
  	YourPrimaryGeneratorAction*  fYourPrimary; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif