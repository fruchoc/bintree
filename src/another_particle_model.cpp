/*
 * another_particle_model.cpp
 *
 *  Created on: 20 Mar 2012
 *      Author: wjm34
 */

#include "../include/another_particle_model.h"
#include "../include/serialiser.h"
#include <iostream>
#include <stack>

// Namespaces
using namespace std;

/*!
 * @brief       Initialising constructor.
 */
AnotherParticleModel::AnotherParticleModel() :
    // State space
    m_num1(0),
    m_num2(0),
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
AnotherParticleModel::~AnotherParticleModel()
{
    delete m_leftchild;
    delete m_rightchild;
}

/*!
 * @brief       Writes the state of the particle to console.
 */
void AnotherParticleModel::PrintParticle() const
{
    cout << this << " p1: " << m_num1 << " p2: " << m_num2;
    if (m_leftchild == NULL) {
        cout << " lc: " << m_leftchild << " rc: " << m_rightchild;
        cout << " lp: " << m_leftparticle << " rp: " << m_rightparticle;
    } else {
        cout << " lc: " << m_leftchild->m_num1 << " rc: " << m_rightchild->m_num1;
        cout << " lp: " << m_leftparticle->m_num1 << " rp: " << m_rightparticle->m_num1;
    }
    cout << " parent: " << m_parent << endl;

    if (m_leftchild != NULL) {
        m_leftchild->PrintParticle();
        m_rightchild->PrintParticle();
    }
}

/*!
 * @brief       Sets the state space of the particle
 * @param num1  Parameter 1
 * @param num2  Parameter 2
 */
void AnotherParticleModel::SetProperties(int num1, int num2) {
    m_num1 = num1;
    m_num2 = num2;
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
void AnotherParticleModel::CreateParticle2() {
    // Create root node
    SetProperties(11, 12);

    // Create node 2
    m_leftchild = new AnotherParticleModel();
    m_leftchild->SetProperties(22, 23);
    m_leftchild->m_parent = this;

    // Create node 3
    m_leftchild->m_leftchild = new AnotherParticleModel();
    m_leftchild->m_leftchild->SetProperties(33, 34);
    m_leftchild->m_leftchild->m_parent = m_leftchild;

    // Create node 4
    m_leftchild->m_leftchild->m_leftchild = new AnotherParticleModel();
    m_leftchild->m_leftchild->m_leftchild->SetProperties(44, 45);
    m_leftchild->m_leftchild->m_leftchild->m_parent = m_leftchild->m_leftchild;

    // Create node 5
    m_leftchild->m_leftchild->m_rightchild = new AnotherParticleModel();
    m_leftchild->m_leftchild->m_rightchild->SetProperties(55, 56);
    m_leftchild->m_leftchild->m_rightchild->m_parent = m_leftchild->m_leftchild;

    // Create node 6
    m_leftchild->m_rightchild = new AnotherParticleModel();
    m_leftchild->m_rightchild->SetProperties(66, 67);
    m_leftchild->m_rightchild->m_parent = m_leftchild;

    // Create node 7
    m_rightchild = new AnotherParticleModel();
    m_rightchild->SetProperties(77, 78);
    m_rightchild->m_parent = this;

    // Create node 8
    m_rightchild->m_leftchild = new AnotherParticleModel();
    m_rightchild->m_leftchild->SetProperties(88, 89);
    m_rightchild->m_leftchild->m_parent = m_rightchild;

    // Create node 9
    m_rightchild->m_rightchild = new AnotherParticleModel();
    m_rightchild->m_rightchild->SetProperties(99, 98);
    m_rightchild->m_rightchild->m_parent = m_rightchild;

    // Create node 10
    m_rightchild->m_rightchild->m_leftchild = new AnotherParticleModel();
    m_rightchild->m_rightchild->m_leftchild->SetProperties(100, 101);
    m_rightchild->m_rightchild->m_leftchild->m_parent = m_rightchild->m_rightchild;

    // Create node 11
    m_rightchild->m_rightchild->m_rightchild = new AnotherParticleModel();
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
void AnotherParticleModel::Serialise(ostream &out) const
{
    if (out.good()) {
        // Write version
        const unsigned int version(0);
        out.write((char*)&version, sizeof(version));

        Serialiser <AnotherParticleModel> newclass;
        newclass.Serialise(out, this);
    }
}


/*!
 * @brief           Writes the state space to a binary stream
 * @param   out     Output binary stream
 */
void AnotherParticleModel::SerialisePrimary(ostream &out) const
{
    if (out.good()) {
        // Write state space
        int val = 0;
        val = m_num1;
        out.write((char*)&val, sizeof(val));

        val = m_num2;
        out.write((char*)&val, sizeof(val));
    }
}


/*!
 * @brief           Reads the object from a binary stream
 * @param   in      Input binary stream
 */
void AnotherParticleModel::Deserialise(istream &in)
{
    if (in.good()) {
        // Read version
        unsigned int version(0);
        in.read(reinterpret_cast<char*>(&version), sizeof(version));

        // Now call the recursive loop to read the structure
        Serialiser <AnotherParticleModel> newclass;
        newclass.Deserialise(in, this);

    }
}

/*!
 * @brief           Reads the state space from a binary stream
 * @param   in      Input binary stream
 */
void AnotherParticleModel::DeserialisePrimary(istream &in)
{
    if (in.good()) {
        // Read state space
        int val = 0;
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_num1 = (int)val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_num2 = (int)val;
    }
}


