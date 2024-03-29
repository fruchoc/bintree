
#include <iostream>
#include <fstream>
#include "include/serialiser.h"
#include "include/particle_model.h"
#include "include/another_particle_model.h"

using namespace std;


int main(int argc, char *argv[]) {

    AnotherParticleModel test;
    test.CreateParticle2();

    // Write to save file
    ofstream ofile("test.sav", ios::binary);
    test.Serialise(ofile);
    ofile.close();

    cout << "###########################" << endl;


    // Read from save file
    ifstream ifile("test.sav", ios::binary);
    AnotherParticleModel newtest;
    newtest.Deserialise(ifile);
    newtest.PrintParticle();
    ifile.close();

    return 0;
}


