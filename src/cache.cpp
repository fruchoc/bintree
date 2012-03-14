/*
 * cache.cpp
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

#include "../include/cache.h"
#include "../include/particle_model.h"
#include <iostream>
#include <stack>

/*!
 * @brief       Initialising constructor
 */
Cache::Cache() :
    m_id(0),
    m_lc_id(0),
    m_rc_id(0),
    m_lp_id(0),
    m_rp_id(0),
    m_p_id(0),
    m_prim(NULL)
{}

//! Default destructor
Cache::~Cache() {}

//! Sets the index and pointer to a particle
void Cache::SetIndex(int id, const ParticleModel *p) {
    m_id = id;
    m_prim = p;
}
