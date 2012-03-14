/*
 * particle_model.h
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

#ifndef PARTICLE_MODEL_H_
#define PARTICLE_MODEL_H_

// Includes
#include <iostream>
#include <stack>

// Namespaces
using namespace std;

class ParticleModel {
public:
    //! Default constructor
    ParticleModel();

    //! Default destructor
    virtual ~ParticleModel(void);

    // RETURNING INFORMATION ABOUT THE OBJECT
    //! Print the particle state space
    void PrintParticle() const;

    //! Return the left child
    const ParticleModel *GetLeftChild() const;

    //! Return the right child
    const ParticleModel *GetRightChild() const;

    // MODIFYING THE OBJECT
    void SetProperties(int prop1, int prop2);

    // CREATION OF PARTICLE TREES FOR ILLUSTRATION
    //! Creates a particle tree (example 1)
    void CreateParticle1();

    // SERIALISATION OF OBJECT
    //! Write object to output stream
    void Serialise(ostream &out) const;

    //! Write state space to stream
    void SerialisePrimary(ostream &out) const;

    //! Read object from stream
    void Deserialise(istream &in);

    //! Read state space from stream
    void DeserialisePrimary(istream &in);

private:
    //! State of particle property 1
    int m_prop1;

    //! State of particle property 2
    int m_prop2;

    //! Pointer to leftchild
    ParticleModel *m_leftchild;

    //! Pointer to rightchild
    ParticleModel *m_rightchild;

    //! Pointer to leftparticle
    ParticleModel *m_leftparticle;

    //! Pointer to rightparticle
    ParticleModel *m_rightparticle;

    //! Pointer to parent
    ParticleModel *m_parent;
};

#endif /* PARTICLE_MODEL_H_ */
