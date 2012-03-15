/*
 * cache.h
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

// Includes
#include "../include/particle_model.h"

#ifndef CACHE_H_
#define CACHE_H_

class Cache {
public:
    //! Default constructor
    Cache();

    //! Default destructor
    virtual ~Cache();

    //! Set index and pointer to particle
    void SetIndex(int id, const ParticleModel *p);

    //! Sets the children/particle indices.
    void SetChildrenParticleIndices(int lc, int rc, int lp, int rp, int par);

    //! Gets the pointer of a particle
    const ParticleModel* GetParticlePointer();

    //! Gets the index of the Cache particle
    int GetIndex();

    //! Serialise the cache
    void Serialise(ostream &out) const;

    //! Deserialise the cache
    void Deserialise(istream &in);

private:

    //! Particle id
    int m_id;

    //! Left child id
    int m_lc_id;

    //! Right child id
    int m_rc_id;

    //! Left particle id
    int m_lp_id;

    //! Right particle id
    int m_rp_id;

    //! Parent id
    int m_p_id;

    //! Pointer to particle object
    const ParticleModel *m_prim;
};

#endif /* CACHE_H_ */
