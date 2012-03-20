
#include <iostream>
#include <fstream>
#include "include/serialiser.h"
#include "include/particle_model.h"


using namespace std;


int main(int argc, char *argv[]) {

    ParticleModel test;
    test.CreateParticle1();

    // Write to save file
    ofstream ofile("test.sav", ios::binary);
    test.Serialise(ofile);
    ofile.close();
    Serialiser <ParticleModel> newclass;
    newclass.PrintParams(test);
    cout << "test";

    // Read from save file
    //ifstream ifile("test.sav", ios::binary);
    //ParticleModel newtest;
    //newtest.Deserialise(ifile);
    //newtest.PrintParticle();
    //ifile.close();

    return 0;
}


