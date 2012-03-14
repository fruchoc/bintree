
#include <iostream>
#include <fstream>
#include "include/particle_model.h"
#include "include/cache.h"
#include "include/cache_index.h"

using namespace std;

int main(int argc, char *argv[]) {

    ParticleModel test;
    test.CreateParticle1();

    // Write to save file
    ofstream ofile("test.sav", ios::binary);
    test.Serialise(ofile);
    ofile.close();

    // Read from save file
    //ifstream ifile("test.sav", ios::binary);
    //ParticleModel newtest;
    //newtest.DeserialisePrimary(ifile);
    //newtest.PrintParticle();
    //ifile.close();

    return 0;
}


