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

    void Serialise(ostream &out, const ParticleClass* root) const
    {

        if (out.good()) {
            // Write version
            const unsigned int version = 1;
            out.write((char*)&version, sizeof(version));

            // Call the recursive serialiser!
            SerialiseLoop(out, root, root);
        }
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


    /*###############################
     * Deserialise functionality
     */
    void Deserialise(istream &in, ParticleClass *root)
    {
        if (in.good()) {
            // Read version
            unsigned int version = 0;
            in.read(reinterpret_cast<char*>(&version), sizeof(version));

            if (version == 1) {
                DeserialiseLoop(in, root, root);
            } else {
                throw;
            }

        }
    }

    void DeserialiseLoop(istream &in, ParticleClass* root, ParticleClass* node)
    {
        // Read in the state space first
        node->DeserialisePrimary(in);

        // Does the primary have children?
        bool children(false);
        in.read(reinterpret_cast<char*>(&children), sizeof(children));

        if (children) {
            // Create new children particles
            node->m_leftchild = new ParticleClass();
            node->m_rightchild = new ParticleClass();

            // Read in the children
            DeserialiseLoop(in, root, node->m_leftchild);
            node->m_leftchild->m_parent = node;
            DeserialiseLoop(in, root, node->m_rightchild);
            node->m_rightchild->m_parent = node;
        }

        /*
         * Now use the connectivity indices to reconnect particles
         * NOTE: we are able to do this because this section is not reached until
         * the rightmost child is created, thus *all* particles should have been
         * created before we attempt to establish pointer links between them.
         */
        int val(0);
        // Check the left particle
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        if (val != 0) node->m_leftparticle = FindParticleFromIndex(root, val);

        // Check the right particle
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        if (val != 0) node->m_rightparticle = FindParticleFromIndex(root, val);
    }

    ParticleClass* FindParticleFromIndex(ParticleClass* node, int index) {

        // Use the null pointer where 0 is given.
        if (index == 0) return NULL;

        // Otherwise, start at the top of the tree and work downwards...
        bool status(false);                 // Success flag for loop
        int sum(1);                         // Counter for tracking node number

        return FindParticleFromIndexLoop(node, &index, &sum, &status);
    }

    ParticleClass* FindParticleFromIndexLoop(ParticleClass* node, int *index, int *sum, bool *status)
    {
        if (*index == *sum) {
            *status = true;
            return node;
        } else {
            // Jump to next node
            (*sum)++;
            ParticleClass* ans;
            if (not *status) {
                if (node->m_leftchild != NULL)
                    ans = FindParticleFromIndexLoop(node->m_leftchild, index, sum, status);
            }
            if (not *status) {
                if (node->m_rightchild != NULL)
                    ans = FindParticleFromIndexLoop(node->m_rightchild, index, sum, status);
            }
            return ans;
        }
    }

};


#endif
