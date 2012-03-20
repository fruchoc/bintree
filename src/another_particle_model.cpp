/*
 * another_particle_model.cpp
 *
 *  Created on: 20 Mar 2012
 *      Author: wjm34
 */

#include "../include/another_particle_model.h"
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
