
#include <iostream>
#include <fstream>
#include "include/particle_model.h"

using namespace std;

int main(int argc, char *argv[]) {

    ParticleModel test;
    test.SetProperties(5, 6);
    test.PrintParticle();

    // Write to save file
    ofstream ofile("test.sav", ios::binary);
    test.SerialisePrimary(ofile);
    ofile.close();

    // Read from save file
    ifstream ifile("test.sav", ios::binary);
    ParticleModel newtest;
    newtest.DeserialisePrimary(ifile);
    newtest.PrintParticle();
    ifile.close();

    return 0;
}
