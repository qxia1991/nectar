# Simulations in Solid Neon 
Right now the code is simulating events from an AmBe calibraiton source

To run the pacakge, you will need to intall geant4.11 first:
1. Download geant4 source code from https://geant4.web.cern.ch/download/11.3.2.html
2. Inside the GEANT4 folder: ```mkdir geant4-v11.3.2-build```, then ```cd geant4-v11.3.2-build```
3. ```ccmake ../geant4-v11.3.2```
4. Type c for configure
5. Turn on  use-qt, use_opengl_x11, use_raytracer_x11, build_multithreaded, install_data; Change cmake_install_prefix to GEANT4/geant4-v11.3.2-install
6. Type g for generation
7. ```make -j8```
8. ```make install```
9. In ~/.bashrc, add ```alias geant4make=“source /Users/qingxia/Documents/Physics/GEANT4/geant4-v11.3.2-install/share/Geant4/geant4make/geant4make.sh”```

After geant4 has been installed, you can compile the SNe pacakge:
1. ```cd geant4-SNe```
2. ```cd build```
3. ```Cmake ..```
4. Now you can run ```sim``` or ```sim <mac file>```
