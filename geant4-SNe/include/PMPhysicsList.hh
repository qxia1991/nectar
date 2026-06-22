#ifndef PMPHYSICSLISTS_HH
#define PMPHYSICSLISTS_HH

#include "G4VModularPhysicsList.hh"
//#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"

class PMPhysicsList : public G4VModularPhysicsList
{
public:
    PMPhysicsList();
    ~PMPhysicsList();
};
#endif