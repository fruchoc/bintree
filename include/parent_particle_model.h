/*
 * parent_particle_model.h
 *
 *  Created on: 20 Mar 2012
 *      Author: wjm34
 */

#ifndef PARENT_PARTICLE_MODEL_H_
#define PARENT_PARTICLE_MODEL_H_

class ParentParticleModel {
public:
    //! Default constructor
    ParentParticleModel();

    //! Destructor
    virtual ~ParentParticleModel();

private:
    //! Collision diameter
    int m_dcol;

    //! Primary diameter
    int m_dpri;
};

#endif /* PARENT_PARTICLE_MODEL_H_ */
