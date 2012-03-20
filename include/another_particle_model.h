/*
 * another_particle_model.h
 *
 *  Created on: 20 Mar 2012
 *      Author: wjm34
 */

#ifndef ANOTHER_PARTICLE_MODEL_H_
#define ANOTHER_PARTICLE_MODEL_H_

// Includes
#include <iostream>
#include <stack>
#include "../include/parent_particle_model.h"

class AnotherParticleModel : public ParentParticleModel
{
public:
    //! Default constructor
    AnotherParticleModel();

    //! Default destructor
    virtual ~AnotherParticleModel();

    //! Set the state space of the particle
    void SetProperties(int num1, int num2);

private:
    //! State of particle property 1
    int m_num1;

    //! State of particle property 2
    int m_num2;

    //! Pointer to leftchild
    AnotherParticleModel *m_leftchild;

    //! Pointer to rightchild
    AnotherParticleModel *m_rightchild;

    //! Pointer to leftparticle
    AnotherParticleModel *m_leftparticle;

    //! Pointer to rightparticle
    AnotherParticleModel *m_rightparticle;

    //! Pointer to parent
    AnotherParticleModel *m_parent;
};

#endif /* ANOTHER_PARTICLE_MODEL_H_ */
