/*
 * Serialiser.h
 *
 *  Created on: 20 Mar 2012
 *      Author: wjm34
 */

#ifndef SERIALISER_H_
#define SERIALISER_H_

//Includes
#include <iostream>
#include <stack>

// Namespaces
using namespace std;

template <class ParticleClass>
class Serialiser
{
public:
    void PrintParams(ParticleClass input) {
        input.PrintParticle();
    }

    void Serialise(ostream &out, const ParticleClass* input) const {

        if (out.good()) {
            // Write version
            const unsigned int version = 1;
            out.write((char*)&version, sizeof(version));
        }

        // Call the recursive serialiser!

        SerialiseLoop(out, input, input);
    }

    void SerialiseLoop(ostream &out, const ParticleClass* root, const ParticleClass* node) const {
        // Serialise the state space first
        node->SerialisePrimary(out);

        // Does this primary have children?
        bool children(false);
        //if (node->m_leftchild != NULL && node->m_rightchild != NULL) children = true;
        out.write((char*)&children, sizeof(children));
    }
};


#endif
