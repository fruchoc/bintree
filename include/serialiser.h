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

    void Serialise(ostream &out, const ParticleClass* input) const
    {

        if (out.good()) {
            // Write version
            const unsigned int version = 1;
            out.write((char*)&version, sizeof(version));
        }

        // Call the recursive serialiser!

        SerialiseLoop(out, input, input);
    }

    void SerialiseLoop(ostream &out, const ParticleClass* root, const ParticleClass* node) const
    {
        // Serialise the state space first
        node->SerialisePrimary(out);

        // Does this primary have children?
        bool children(false);
        if (node->m_leftchild != NULL && node->m_rightchild != NULL) children = true;
        out.write((char*)&children, sizeof(children));

        // Now serialise the children
        if (children) SerialiseLoop(out, root, node->m_leftchild);
        if (children) SerialiseLoop(out, root, node->m_rightchild);

        // Now write the left/right particle connectivity
        int val(0);
        val = GetParticleIndex(root, node->m_leftparticle);
        out.write((char*)&val, sizeof(val));

        val = GetParticleIndex(root, node->m_rightparticle);
        out.write((char*)&val, sizeof(val));
    }

    int GetParticleIndex(const ParticleClass* node, const ParticleClass* target) const
    {
        // Return zero if the target is nothing.
        if (target == NULL) return 0;

        // Otherwise, first particle has ID of 1
        int sum(1);
        bool status(false);
        GetParticleIndexLoop(node, target, &sum, &status);

        // Check the particle was found..
        if (not status) {
            cout << "couldn't find particle!" << endl;
        }

        return sum;
    }

    void GetParticleIndexLoop(
            const ParticleClass* node,
            const ParticleClass* target,
            int *sum,
            bool *status) const
    {
        if (target == node) {
            *status = true;
        } else {
            // Jump to next node
            (*sum)++;
            if (not *status) {
                if (node->m_leftchild != NULL)
                GetParticleIndexLoop(node->m_leftchild, target, sum, status);
            }
            if (not *status) {
                if (node->m_rightchild != NULL)
                GetParticleIndexLoop(node->m_rightchild, target, sum, status);
            }
        }
    }
};


#endif
