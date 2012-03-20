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
#include "../include/parent_particle_model.h"
#include "../include/serialiser.h"

// Namespaces
using namespace std;

class ParticleModel : public ParentParticleModel
{
public:
    friend class Serialiser<class ParticleModel>;
    //! Default constructor
    ParticleModel();

    //! Default destructor
    virtual ~ParticleModel(void);

    // RETURNING INFORMATION ABOUT THE OBJECT
    //! Print the particle state space
    void PrintParticle() const;

    //! Return the left child
    const ParticleModel *GetLeftChild() const {return m_leftchild;};

    //! Return the right child
    const ParticleModel *GetRightChild() const {return m_rightchild;};

    //! Return the left particle
    const ParticleModel *GetLeftParticle() const {return m_leftparticle;};

    //! Return the right particle
    const ParticleModel *GetRightParticle() const {return m_rightparticle;};

    //! Return the parent
    const ParticleModel *GetParent() const {return m_parent;};

    // MODIFYING THE OBJECT
    //! Set the state space of the particle
    void SetProperties(int prop1, int prop2);

    //! Set the left child
    void SetLeftChild(ParticleModel *p) {m_leftchild = p;};

    //! Set the right child
    void SetRightChild(ParticleModel *p) {m_rightchild = p;};

    //! Set the left particle
    void SetLeftParticle(ParticleModel *p) {m_leftparticle = p;};

    //! Set the left particle
    void SetRightParticle(ParticleModel *p) {m_rightparticle = p;};

    //! Set the parent
    void SetParent(ParticleModel *p) {m_parent = p;};

    // CREATION OF PARTICLE TREES FOR ILLUSTRATION
    //! Creates a particle tree (example 1)
    void CreateParticle1();

    //! Creates a more complex particle tree (example 2)
    void CreateParticle2();

    // SERIALISATION OF OBJECT
    //! Write object to output stream
    void Serialise(ostream &out) const;

    void SerialiseLoop(ostream &out, const ParticleModel *root) const;

    int GetParticleIndex(const ParticleModel *target, const ParticleModel *p) const;
    void GetParticleIndexLoop(const ParticleModel *target, const ParticleModel *p, int *sum, bool *status) const;

    //! Write state space to stream
    void SerialisePrimary(ostream &out) const;

    //! Read object from stream
    void Deserialise(istream &in);

    void DeserialiseLoop(istream &in, ParticleModel *root);

    ParticleModel* FindParticleFromIndex(int index);

    ParticleModel* ReturnAddress(ParticleModel* target);

    ParticleModel* FindParticleFromIndexLoop(
            int *index,
            int *sum,
            bool *status);

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
