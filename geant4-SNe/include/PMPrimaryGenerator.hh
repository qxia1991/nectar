#ifndef PMPRIMARYGENERATOR_HH
#define PMPRIMARYGENERATOR_HH
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include <array>
class PMPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    PMPrimaryGenerator();
    ~PMPrimaryGenerator();
    virtual void GeneratePrimaries(G4Event *);
    enum
    {
        CDFSize0 = 580,
        CDFSize1 = 492,
        CDFSize2 = 299,
        GammaCDFSize = 500
    };
    G4double EnergySampler(const G4double*, const G4double*, unsigned int);

    template <typename T, size_t N>
    std::array<T, N> loadFileToArray(std::string& filename);
private:
    G4ParticleGun *fParticleGun;

    std::array<G4double, CDFSize0> neutronCDFState0;
    std::array<G4double, CDFSize0> neutronEnergyState0;

    std::array<G4double, CDFSize1> neutronCDFState1;
    std::array<G4double, CDFSize1> neutronEnergyState1;

    std::array<G4double, CDFSize2> neutronCDFState2;
    std::array<G4double, CDFSize2> neutronEnergyState2;

    std::array<G4double, GammaCDFSize> gammaCDF;
    //std::array<G4double, GammaCDFSize> gammaAngle;

    G4double GetNeutronEnergy(G4int);
    G4ThreeVector GetRandomDirection();

};
#endif