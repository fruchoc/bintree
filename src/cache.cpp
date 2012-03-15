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
#include <stdexcept>

using namespace std;

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

//! Set the connectivity information of a particle cache
void Cache::SetChildrenParticleIndices(int lc, int rc, int lp, int rp, int par) {
    m_lc_id = lc;
    m_rc_id = rc;
    m_lp_id = lp;
    m_rp_id = rp;
    m_p_id = par;
}

//! Returns the pointer to the cache's particle
const ParticleModel* Cache::GetParticlePointer() {
    return m_prim;
}

//! Returns the index of a cache
int Cache::GetIndex() {
    return m_id;
}

//! Returns whether the cache has a particle pointer
bool Cache::HasPointer() const {
    if (m_prim != NULL) {
        return true;
    } else {
        return false;
    }
}

//! Returns whether the cache has L/R particles
bool Cache::HasParticles() const {
    if (m_lp_id > 0 && m_rp_id > 0) {
        return true;
    } else {
        return false;
    }
}

//! Returns whether the cache has children
bool Cache::HasChildren() const {
    if (m_lc_id > 0 && m_rc_id > 0) {
        return true;
    } else {
        return false;
    }
}

//! Print the connectivity information
void Cache::PrintIndices() const {
    cout << m_id << " " << m_lc_id << " " << m_rc_id << " " << m_lp_id << " " << m_rp_id << " " << m_p_id << endl;
}

/*!
 * @brief       Writes all cache parameters to binary file
 * @param out   Output binary stream
 */
void Cache::Serialise(ostream &out) const {

    if (out.good()) {
        int val(0);

        val = m_id;
        out.write((char*)&val, sizeof(val));

        val = m_lc_id;
        out.write((char*)&val, sizeof(val));

        val = m_rc_id;
        out.write((char*)&val, sizeof(val));

        val = m_lp_id;
        out.write((char*)&val, sizeof(val));

        val = m_rp_id;
        out.write((char*)&val, sizeof(val));

        val = m_p_id;
        out.write((char*)&val, sizeof(val));
    } else {
        throw invalid_argument("Output stream not ready " "Cache::Serialise");
    }
}

/*!
 * @brief       Reads all cache parameters from binary file
 * @param in    Input binary stream
 */
void Cache::Deserialise(istream &in) {

    if (in.good()) {
        int val(0);

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_id = val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_lc_id = val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_rc_id = val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_lp_id = val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_rp_id = val;

        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        m_p_id = val;
    } else {
        throw invalid_argument("Output stream not ready " "Cache::Deserialise");
    }
}
