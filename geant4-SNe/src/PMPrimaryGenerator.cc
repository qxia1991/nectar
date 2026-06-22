#include "PMPrimaryGenerator.hh"
#include "iostream"
#include "fstream"
#include "G4UniformRandPool.hh"

PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    //Particle position
    /*G4double x = 0. *m;
    G4double y= 0. *m;
    G4double z= -1.*cm;

    G4double px= 0.;
    G4double py= 0.;
    G4double pz= 1.;
    G4ThreeVector pos(x,y,z);
    G4ThreeVector mom(px,py,pz);*/
    
    //G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    //G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

    //fParticleGun->SetParticlePosition(pos);
    //fParticleGun->SetParticleMomentumDirection(mom);
    //fParticleGun->SetParticleEnergy(2.45 *MeV);
    //fParticleGun->SetParticleDefinition(particle);

    std::string datapath = "/Users/qingxia/Documents/Physics/GEANT4/geant4-SNe/";
    // Neutron group n0
    std::string neutronCDF0File = datapath + "/generator/data/AmBe_SOURCES4A_n0_neutronCDF.dat";
    std::string neutronEnergy0File = datapath + "/generator/data/AmBe_SOURCES4A_n0_neutronEnergy.dat";
    
// Neutron group n1
    std::string neutronCDF1File = datapath + "/generator/data/AmBe_SOURCES4A_n1_neutronCDF.dat";
    std::string neutronEnergy1File = datapath + "/generator/data/AmBe_SOURCES4A_n1_neutronEnergy.dat";
// Neutron group n2
    std::string neutronCDF2File = datapath + "/generator/data/AmBe_SOURCES4A_n2_neutronCDF.dat";
    std::string neutronEnergy2File = datapath + "/generator/data/AmBe_SOURCES4A_n2_neutronEnergy.dat";
// Gamma angle for the neutron group n2
    std::string gammaCDFFile = datapath + "/generator/data/AmBe_SOURCES4A_gammaCDF.dat";
    //std::string gammaAngleFile = datapath + "/generator/data/AmBe_SOURCES4A_gammaAngle.dat";

    neutronCDFState0 = loadFileToArray<G4double,CDFSize0>(neutronCDF0File);
    neutronEnergyState0 = loadFileToArray<G4double,CDFSize0>(neutronEnergy0File);

    neutronCDFState1 = loadFileToArray<G4double,CDFSize1>(neutronCDF1File);
    neutronEnergyState1 = loadFileToArray<G4double,CDFSize1>(neutronEnergy1File);

    neutronCDFState2 = loadFileToArray<G4double,CDFSize2>(neutronCDF2File);
    neutronEnergyState2 = loadFileToArray<G4double,CDFSize2>(neutronEnergy2File);

    gammaCDF = loadFileToArray<G4double,GammaCDFSize>(gammaCDFFile);
    //gammaAngle = loadFileToArray<G4double,GammaCDFSize>(gammaAngleFile);

   /*for (const double& element : neutronCDFState0) {
    std::cout << element << "!!!"<<std::endl;
    }*/
}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}


void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    //Particle position
    G4double x = 0. *m;
    G4double y= 0. *m;
    G4double z= -1.*cm;
    G4ThreeVector pos(x,y,z);

    //G4int Z=9;
    //G4int A=18;
   // G4int Z = 98;
    //G4int A=252;

    //G4double charge = 0.*eplus;
    //G4double energy = 0. *keV;

    /*G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticleEnergy(energy);*/
  
    G4double probability_state;
    G4double singleNeutronEnergy = 0.0;

    //n0->27%, n1->62.7% and n2->10.3% (individual probabilities)
    // Down below are the cumulative probabilities
    G4double AmBe_n0 = 0.270;
    G4double AmBe_n1 = 0.897;

    // First determine the neutron group
    probability_state = G4UniformRand();
    G4int state = 0;

    if (probability_state < AmBe_n0)
    {
        state = 0;
    }
    else if (probability_state < AmBe_n1)
    {
        state = 1;
    }
    else
    {
        state = 2;
    }

    // Choose the neutron energy for the particular state
    singleNeutronEnergy = GetNeutronEnergy(state);

    // now generate a neutron 
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("neutron");
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(GetRandomDirection());
    fParticleGun->SetParticleEnergy(singleNeutronEnergy * MeV);
    fParticleGun->SetParticleDefinition(particle);
 
    fParticleGun->GeneratePrimaryVertex(anEvent);

    //Generate correlated gamma only for 1st excited state (two gamma emission for the 2nd state is very low, and thus ignored)
    /*if (state == 1)
    {
        G4ParticleDefinition *particle2 = particleTable->FindParticle("gamma");
        fParticleGun->SetParticlePosition(pos);
        fParticleGun->SetParticleMomentumDirection(GetRandomDirection());
        fParticleGun->SetParticleEnergy(4439. * keV);
        fParticleGun->SetParticleDefinition(particle2);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }*/
    
    //fParticleGun->SetParticleEnergy(2.45 *MeV);
    //fParticleGun->SetParticleDefinition(particle);
    //Create vertex
    //fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4double PMPrimaryGenerator::GetNeutronEnergy(G4int state)
{
    G4double energy = 0.;
    if (state == 0)
    {
        energy = EnergySampler(neutronCDFState0.begin(), neutronEnergyState0.begin(), neutronCDFState0.size());
    }
    else if (state == 1)
    {
        energy = EnergySampler(neutronCDFState1.begin(), neutronEnergyState1.begin(), neutronCDFState1.size());
    }
    else
    {
        energy = EnergySampler(neutronCDFState2.begin(), neutronEnergyState2.begin(), neutronCDFState2.size());
    }
    return energy;
}

G4double PMPrimaryGenerator::EnergySampler(const G4double* ptr_NeutronCDF, const G4double* ptr_NeutronEnergy, unsigned int size)
{

    G4double prob = G4UniformRand();
    G4int indexLow = 0;
    G4int indexHigh = size - 1;

    while (!(*(ptr_NeutronCDF + indexLow + 1) > prob && *(ptr_NeutronCDF + indexHigh - 1) < prob))
    {
        if (*(ptr_NeutronCDF + (indexLow + indexHigh) / 2) < prob)
        {
            indexLow = (indexLow + indexHigh) / 2;
        }
        else
        {
            indexHigh = (indexLow + indexHigh) / 2;
        }
    }

    G4double split = (prob - *(ptr_NeutronCDF + indexLow)) / (*(ptr_NeutronCDF + indexHigh) - *(ptr_NeutronCDF + indexLow));
    G4double energy = *(ptr_NeutronEnergy + indexLow) + split * (*(ptr_NeutronEnergy + indexHigh) - *(ptr_NeutronEnergy + indexLow));

    return (energy);
}

G4ThreeVector PMPrimaryGenerator::GetRandomDirection()
{
    G4double xDir, yDir, zDir;
    G4double cosTheta, sinTheta, phi;
    cosTheta = -1. + 2. * G4UniformRand();
    sinTheta = sqrt(1. - cosTheta * cosTheta);
    phi = 2. * 3.141592653589793238 * G4UniformRand();
    xDir = sinTheta * cos(phi);
    yDir = sinTheta * sin(phi);
    zDir = cosTheta;
    G4ThreeVector direction(xDir, yDir, zDir);

    return direction;
}

template <typename T, size_t N>
std::array<T, N> PMPrimaryGenerator::loadFileToArray(std::string& filename) {
    std::array<T, N> data;
    std::ifstream file(filename);
    std::cout<<filename<<"!!!"<<std::endl;
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (size_t i = 0; i < N; ++i) {
        if (file.eof()) {
            // Handle the case where the file ends prematurely
            std::cerr << "Warning: File ended before filling the array. Filling remaining elements with default values." << std::endl;
            for (; i < N; ++i) {
                data[i] = T(); // Default value for type T
            }
            break;
        }
        if (!(file >> data[i])) {
             // Handle the case where the extraction fails
            std::cerr << "Warning: Failed to read data from file at index " << i << ". Filling with default value." << std::endl;
            file.clear();  // Clear error flags
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
            data[i] = T();
            continue;
        }
        //else{
          //  std::cout<<data[i]<<"!!!"<<std::endl;
        //}
    }

    return data;
}