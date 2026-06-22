#include "PMDetectorConstruction.hh"
//#define TEMPERATURE 173 * kelvin // Sets the T of the LXe,GXe
//#define PRESSURE 1.57 * bar 
#define TEMPERATURE 25 * kelvin // Sets the T of SNe
#define PRESSURE 0.43 * bar 
#define N_l 2.888 * g / cm3 //	NIST LXe density
//#define N_g 15e-3 * g / cm3 //	NIST GXe density for 1.57 bar and 173.1 K 
#define N_s 1.444 * g / cm3 // SNe density
PMDetectorConstruction::PMDetectorConstruction()
{

}

PMDetectorConstruction::~PMDetectorConstruction()
{

}

G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    //G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
    //G4Material *detMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4Isotope* Xe124 = new G4Isotope("Xe124", 54, 124, 123.9058942 * g / mole);
    G4Isotope* Xe126 = new G4Isotope("Xe126", 54, 126, 125.904281 * g / mole);
    G4Isotope* Xe128 = new G4Isotope("Xe128", 54, 128, 127.9035312 * g / mole);
    G4Isotope* Xe129 = new G4Isotope("Xe129", 54, 129, 128.9047801 * g / mole);
    G4Isotope* Xe130 = new G4Isotope("Xe130", 54, 130, 129.9035094 * g / mole);
    G4Isotope* Xe131 = new G4Isotope("Xe131", 54, 131, 130.905072 * g / mole);
    G4Isotope* Xe132 = new G4Isotope("Xe132", 54, 132, 131.904144 * g / mole);
    G4Isotope* Xe134 = new G4Isotope("Xe134", 54, 134, 133.905395 * g / mole);
    G4Isotope* Xe136 = new G4Isotope("Xe136", 54, 136, 135.907214 * g / mole);
    G4Element* natXe = new G4Element("Natural Xe", "natXe", 9);
    natXe->AddIsotope(Xe124, 0.09 * perCent);
    natXe->AddIsotope(Xe126, 0.09 * perCent);
    natXe->AddIsotope(Xe128, 1.92 * perCent);
    natXe->AddIsotope(Xe129, 26.44 * perCent);
    natXe->AddIsotope(Xe130, 4.08 * perCent);
    natXe->AddIsotope(Xe131, 21.18 * perCent);
    natXe->AddIsotope(Xe132, 26.89 * perCent);
    natXe->AddIsotope(Xe134, 10.44 * perCent);
    natXe->AddIsotope(Xe136, 8.87 * perCent);

    G4Isotope* Ne20 = new G4Isotope("Ne20", 10, 20, 19.99244018 * g / mole);
    G4Isotope* Ne21 = new G4Isotope("Ne21", 10, 21, 20.9938467 * g / mole);
    G4Isotope* Ne22 = new G4Isotope("Ne22", 10, 22, 21.9913851 * g / mole);
    G4Element* natNe = new G4Element("Natural Ne", "natNe", 3);
    natNe->AddIsotope(Ne20, 90.5 * perCent);
    natNe->AddIsotope(Ne21, 0.27 * perCent);
    natNe->AddIsotope(Ne22, 9.25 * perCent);

     /*std::unique_ptr<G4Material> detMat_ = std::make_unique<G4Material>(
         "liquidXe", N_l, 1, kStateLiquid,TEMPERATURE, PRESSURE);
    
     detMat_->AddElement(natXe, 1);
     G4Material *detMat = detMat_.get();*/
    G4Material *detMat = new G4Material("solidNe", N_s, 1, kStateSolid,TEMPERATURE, PRESSURE);
    //G4Material *detMat = new G4Material("liquidXe", N_l, 1, kStateLiquid,TEMPERATURE, PRESSURE);
    detMat->AddElement(natNe, 1);
    

    //Define Fluorine-18
    /*G4Isotope *F18=new G4Isotope("F18", 9, 18, 18.000938*g/mole);
    G4Element *elF18=new G4Element("Fluorine-18","F18",1);
    elF18->AddIsotope(F18,100.0*perCent);
    G4Material *matF18 = new G4Material("F18source",1.51*g/cm3,1);
    matF18->AddElement(elF18,100.0*perCent);*/


    G4double xWorld = 1.* m;
    G4double yWorld = 1.* m;
    G4double zWorld = 1.* m;

    G4Box *solidWorld = new G4Box ("solidWorld",0.5*xWorld, 0.5*yWorld, 0.5*zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,checkOverlaps);

//Fluorine source
    /*G4double sourceRadius = 1.*mm;
    G4Sphere *solidSource = new G4Sphere("solidSource",0.0,sourceRadius,0.0,360.*deg,0.0,180.*deg);
    G4LogicalVolume *logicSource = new G4LogicalVolume(solidSource,matF18,"logicSource");
    G4VPhysicalVolume *physSource = new G4PVPlacement(0,G4ThreeVector(0.,0.,-1.*cm),logicSource,"physSource",logicWorld,0,checkOverlaps);

    G4VisAttributes *sourceVisAtt = new G4VisAttributes(G4Color(1.0,0.0,1.0,0.5));
    sourceVisAtt->SetForceSolid(true);
    logicSource->SetVisAttributes(sourceVisAtt);*/

    /*G4double leadThickness=2.*mm;
    G4double leadSize = 10. *cm;
    G4Box *solidLead = new G4Box("solidLead",0.5*leadSize,0.5*leadSize,0.5*leadThickness);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicLead");
    G4VPhysicalVolume *physLead = new G4PVPlacement(0,G4ThreeVector(0.,0.,5.*cm),logicLead, "physLead", logicWorld, false,checkOverlaps);
    G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0,0.0, 0.0,0.5));
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);*/

    G4double detectorSize = 3.0*cm;
    //G4Box *solidDetector = new G4Box("solidDetector",0.5*detectorSize, 0.5*detectorSize,0.5*detectorSize);
    G4Tubs *solidDetector = new G4Tubs("solidDetector",0.*cm, 0.5*detectorSize,0.5*detectorSize,0.*deg,360.*deg);
    G4RotationMatrix* Rotation = new G4RotationMatrix();
    Rotation->rotateX(90. * deg);
    Rotation->rotateY(0. * deg);
    Rotation->rotateZ(0.0 * deg);
    //auto RotInv = new G4RotationMatrix(Rotation.inverse());
    //logicDetector = new G4LogicalVolume(solidDetector,detMat,"logicDetector");
    //G4VPhysicalVolume *physDetector = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.5*detectorSize),logicDetector,"physDetector",logicWorld,false, checkOverlaps);
    /*G4Tubs* neutronTubeSmallBranch_solid = new G4Tubs("neutronTubeSmallBranch_solid",
        0. * cm,
       0.3*cm,
        detectorSize ,
        0. * deg, 360. * deg);
    G4RotationMatrix* smallBranchRotation = new G4RotationMatrix();
    smallBranchRotation->rotateX(-30.*deg);
    G4UnionSolid* neutronTube_solid = new G4UnionSolid("neutronTube",
        solidDetector,
        neutronTubeSmallBranch_solid,
        smallBranchRotation,
        G4ThreeVector(0, -3.*cm,0));*/
    logicDetector = new G4LogicalVolume(solidDetector,detMat,"logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(Rotation,G4ThreeVector(0.,0.,0.5*detectorSize),logicDetector,"physDetector",logicWorld,false, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0,1.0,0.0,0.5));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);
    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}