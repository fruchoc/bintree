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
