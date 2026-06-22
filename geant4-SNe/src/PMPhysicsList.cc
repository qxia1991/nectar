#include "PMPhysicsList.hh"

PMPhysicsList::PMPhysicsList()
{
 //EM Physics
 //RegisterPhysics(new G4EmStandardPhysics());   
 RegisterPhysics(new G4EmLivermorePhysics());  

 // Radioactive decay physics
 RegisterPhysics(new G4RadioactiveDecayPhysics());

 //Decay  physics
 RegisterPhysics(new G4DecayPhysics());

 //hadron physics
 RegisterPhysics(new G4HadronElasticPhysicsHP());
 //RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());


 
}

PMPhysicsList::~PMPhysicsList()
{
    
}