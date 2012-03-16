/*
 * particle_model.cpp
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

// Includes
#include "../include/particle_model.h"
#include "../include/cache_index.h"
#include <iostream>
#include <stack>

// Namespaces
using namespace std;

/*!
 * @brief       Initialising constructor.
 */
ParticleModel::ParticleModel() :
    // State space
    m_prop1(0),
    m_prop2(0),
    // Children
    m_leftchild(NULL),
    m_rightchild(NULL),
    // Particles
    m_leftparticle(NULL),
    m_rightparticle(NULL),
    // Parent
    m_parent(NULL)
{}

/*!
 * @brief       Default destructor.
 */
ParticleModel::~ParticleModel()
{
    delete m_leftchild;
    delete m_rightchild;
}

/*!
 * @brief       Writes the state of the particle to console.
 */
void ParticleModel::PrintParticle() const
{
    cout << this << " p1: " << m_prop1 << " p2: " << m_prop2;
    cout << " lc: " << m_leftchild << " rc: " << m_rightchild;
    cout << " lp: " << m_leftparticle << " rp: " << m_rightparticle;
    cout << " parent: " << m_parent << endl;
}


/*!
 * @brief           Sets the state space of the particle
 * @param prop1     Value of property 1
 * @param prop2     Value of property 2
 */
void ParticleModel::SetProperties(int prop1, int prop2)
{
    m_prop1 = prop1;
    m_prop2 = prop2;
}


/*!
 * @brief       Creates a basic particle tree (example 1)
 *
 * This is a particle composed of two real primaries connected by the root
 * node. Diagram:
 *    root
 *    /  \
 *  left right
 *
 */
void ParticleModel::CreateParticle1() {
    // Adjust the base node of the tree
    SetProperties(11, 22);

    // Create children
    m_leftchild = new ParticleModel();
    m_leftchild->SetProperties(33, 44);

    m_rightchild = new ParticleModel();
    m_rightchild->SetProperties(55, 66);

    // Link particles
    m_leftparticle = m_leftchild;
    m_rightparticle = m_rightchild;

    // Link parents
    m_leftparticle->m_parent = this;
    m_rightparticle->m_parent = this;
}

/*!
 * @brief       Creates a basic particle tree (example 2)
 *
 * This is a particle is based on Markus Sander's thesis test particle
 * Connectivity:
 * id   lc  rc  lp  rp  p
 * 1    2   7   4   11  0
 * 2    3   6   5   6   1
 * 3    4   5   4   5   2
 * 4    0   0   0   0   3
 * 5    0   0   0   0   3
 * 6    0   0   0   0   2
 * 7    8   9   8   11  1
 * 8    0   0   0   0   7
 * 9    10  11  10  11  7
 * 10   0   0   0   0   9
 * 11   0   0   0   0   9
 *
 */
void ParticleModel::CreateParticle2() {
    // Create root node
    SetProperties(11, 12);

    // Create node 2
    m_leftchild = new ParticleModel();
    m_leftchild->SetProperties(22, 23);
    m_leftchild->m_parent = this;

    // Create node 3
    m_leftchild->m_leftchild = new ParticleModel();
    m_leftchild->m_leftchild->SetProperties(33, 34);
    m_leftchild->m_leftchild->m_parent = m_leftchild;

    // Create node 4
    m_leftchild->m_leftchild->m_leftchild = new ParticleModel();
    m_leftchild->m_leftchild->m_leftchild->SetProperties(44, 45);
    m_leftchild->m_leftchild->m_leftchild->m_parent = m_leftchild->m_leftchild;

    // Create node 5
    m_leftchild->m_leftchild->m_rightchild = new ParticleModel();
    m_leftchild->m_leftchild->m_rightchild->SetProperties(55, 56);
    m_leftchild->m_leftchild->m_rightchild->m_parent = m_leftchild->m_leftchild;

    // Create node 6
    m_leftchild->m_rightchild = new ParticleModel();
    m_leftchild->m_rightchild->SetProperties(66, 67);
    m_leftchild->m_rightchild->m_parent = m_leftchild;

    // Create node 7
    m_rightchild = new ParticleModel();
    m_rightchild->SetProperties(77, 78);
    m_rightchild->m_parent = this;

    // Create node 8
    m_rightchild->m_leftchild = new ParticleModel();
    m_rightchild->m_leftchild->SetProperties(88, 89);
    m_rightchild->m_leftchild->m_parent = m_rightchild;

    // Create node 9
    m_rightchild->m_rightchild = new ParticleModel();
    m_rightchild->m_rightchild->SetProperties(99, 98);
    m_rightchild->m_rightchild->m_parent = m_rightchild;

    // Create node 10
    m_rightchild->m_rightchild->m_leftchild = new ParticleModel();
    m_rightchild->m_rightchild->m_leftchild->SetProperties(100, 101);
    m_rightchild->m_rightchild->m_leftchild->m_parent = m_rightchild->m_rightchild;

    // Create node 11
    m_rightchild->m_rightchild->m_rightchild = new ParticleModel();
    m_rightchild->m_rightchild->m_rightchild->SetProperties(111, 112);
    m_rightchild->m_rightchild->m_rightchild->m_parent = m_rightchild->m_rightchild;

    // ESTABLISH PARTICLE LINKAGES
    // node 1: left = 4, right = 11
    m_leftparticle = m_leftchild->m_leftchild->m_leftchild;
    m_rightparticle = m_rightchild->m_rightchild->m_rightchild;

    // node 2: left = 5, right = 6
    m_leftchild->m_leftparticle = m_leftchild->m_leftchild->m_rightchild;
    m_leftchild->m_rightparticle = m_leftchild->m_rightchild;

    // node 3: left = 4, right = 5
    m_leftchild->m_leftchild->m_leftparticle = m_leftchild->m_leftchild->m_leftchild;
    m_leftchild->m_leftchild->m_rightparticle = m_leftchild->m_leftchild->m_rightchild;

    // node 7: left = 8, right = 11
    m_rightchild->m_leftparticle = m_rightchild->m_leftchild;
    m_rightchild->m_rightparticle = m_rightchild->m_rightchild->m_rightchild;

    // node 9: left = 10, right = 11
    m_rightchild->m_rightchild->m_leftparticle = m_rightchild->m_rightchild->m_leftchild;
    m_rightchild->m_rightchild->m_rightparticle = m_rightchild->m_rightchild->m_rightchild;

}


/*!
 * @brief           Writes the object to a binary stream
 * @param   out     Output binary stream
 */
void ParticleModel::Serialise(ostream &out) const
{
    if (out.good()) {
        // Write version
        const unsigned int version = 0;
        out.write((char*)&version, sizeof(version));

        // First create the index
        CacheIndex index;
        index.CreateIndex(this);
        index.SerialiseIndex(out);

        // Now write the objects
        index.SerialiseBinaryTree(this, out);
    }
}

/*!
 * @brief           Writes the state space to a binary stream
 * @param   out     Output binary stream
 */
void ParticleModel::SerialisePrimary(ostream &out) const
{
    if (out.good()) {
        // Write state space
        int val = 0;
        val = m_prop1;
        out.write((char*)&val, sizeof(val));

        val = m_prop2;
        out.write((char*)&val, sizeof(val));
    }
}


/*!
 * @brief           Reads the object from a binary stream
 * @param   in      Input binary stream
 */
void ParticleModel::Deserialise(istream &in)
{
    if (in.good()) {
        // Read version
        unsigned int version = 0;
        in.read(reinterpret_cast<char*>(&version), sizeof(version));

        // First create an index
        CacheIndex index;
        index.DeserialiseIndex(in);

        // Now read the node details in (creates children-parent structure)
        index.DeserialiseBinaryTree(this, in);

        // Now re-establish the right/left particle structure

    }
}


/*!
 * @brief           Reads the state space from a binary stream
 * @param   in      Input binary stream
 */
void ParticleModel::DeserialisePrimary(istream &in)
{
    if (in.good()) {
        // Read state space
        int val = 0;
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_prop1 = (int)val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_prop2 = (int)val;
    }
}
