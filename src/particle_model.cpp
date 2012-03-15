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

const ParticleModel *ParticleModel::GetLeftChild() const
{
    return m_leftchild;
}

const ParticleModel *ParticleModel::GetRightChild() const
{
    return m_rightchild;
}

const ParticleModel *ParticleModel::GetLeftParticle() const
{
    return m_leftparticle;
}

const ParticleModel *ParticleModel::GetRightParticle() const
{
    return m_rightparticle;
}

const ParticleModel *ParticleModel::GetParent() const
{
    return m_parent;
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
 * @brief           Writes the object to a binary stream
 * @param   out     Output binary stream
 */
void ParticleModel::Serialise(ostream &out) const
{
    if (out.good()) {
        // Write version
        const unsigned int version = 0;
        out.write((char*)&version, sizeof(version));

        CacheIndex index;
        index.CreateIndex(this);
        index.SerialiseBinaryTree(this, out);
        index.SerialiseIndex(out);
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
