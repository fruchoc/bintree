/*
 * cache_index.cpp
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

// Includes
#include <vector>
#include "../include/cache.h"
#include "../include/cache_index.h"

using namespace std;

//! Default constructor
CacheIndex::CacheIndex() :
    m_allcaches(0),
    m_nodes(0),
    m_leaf(0),
    m_nonleaf(0)
{}

//! Default destructor
CacheIndex::~CacheIndex() {}

//! Create the index from the root of a particle tree
void CacheIndex::CreateIndex(const ParticleModel *root) {

    // Call the recursive function to do grunt work
    CreateIndexLoop(root);

    // Loop over all caches to assign their connectivity
    int i(0);
    for (i = 0; i < (int)m_allcaches.size(); i++) {
            FindAllIndices(i);
    }
}

/*!
 * @brief       Recursive function to write the binary tree status
 * @param p     Pointer to the particle node to be cached
 */
void CacheIndex::CreateIndexLoop(const ParticleModel *p) {

    // Only do if there is a node to output
    if (p != NULL) {
        // Create a new cache to hold this particle
        Cache pcache;
        pcache.SetIndex(GetNextIndex(), p);
        m_allcaches.push_back(pcache);

        // Add a particle to total number
        m_nodes++;

        // Now do for L/R child
        CreateIndexLoop(p->GetLeftChild());
        CreateIndexLoop(p->GetRightChild());
    }
}

void CacheIndex::FindAllIndices(int id) {

    const ParticleModel *p = m_allcaches[id].GetParticlePointer();

    int lc = GetPointerIndex(p->GetLeftChild());
    int rc = GetPointerIndex(p->GetRightChild());
    int lp = GetPointerIndex(p->GetLeftParticle());
    int rp = GetPointerIndex(p->GetRightParticle());
    int par = GetPointerIndex(p->GetParent());

    m_allcaches[id].SetChildrenParticleIndices(lc, rc, lp, rp, par);

    cout << p << " " << lc << " " << rc << " " << lp << " " << rp << " " << par << endl;
}

//! Gets the next index number
int CacheIndex::GetNextIndex() {
    return m_allcaches.size() + 1;
}

//! Prints information about the caches
void CacheIndex::PrintAllCaches() {
    vector <Cache>::iterator it;
    for (it = m_allcaches.begin(); it < m_allcaches.end(); it++)
        cout << " " <<  it->GetParticlePointer();
    cout << endl;
}

/*!
 * @brief       Given a constant pointer to a particle, return its index
 *
 * Returns the index of a constant pointer to a particle. If the particle
 * cannot be found, it returns 0 (i.e. NULL pointer)
 *
 * @param p     Constant pointer to particle
 * @return      Integer index of particle
 */
int CacheIndex::GetPointerIndex(const ParticleModel *p) {
    int val(0);
    vector <Cache>::iterator it;
    for (it = m_allcaches.begin(); it < m_allcaches.end(); it++) {
        if (p == it->GetParticlePointer()) {
            val = it->GetIndex();
        }
    }

    if (val < 1) {
        cout << "Pointer not found." << endl;
    }
    return val;
}

/*!
 * @brief       Writes the binary tree objects
 * @param p     Constant pointer to particle to be written
 * @param out   Binary output stream
 */
void CacheIndex::SerialiseBinaryTree(const ParticleModel *p, ostream &out) const {

    // Only do if there is a particle to serialise
    if (p != NULL) {
        p->SerialisePrimary(out);

        // Do for left and right primaries
        if (p->GetLeftChild() != NULL) p->GetLeftChild()->SerialisePrimary(out);
        if (p->GetRightChild() != NULL) p->GetRightChild()->SerialisePrimary(out);
    }
}

/*!
 * @brief       Writes the index to a binary file
 * @param out   Binary output stream
 */
void CacheIndex::SerialiseIndex(ostream &out) const {

    // Loop over the allcaches vector
    int i(0);
    for (i = 0; i < (int)m_allcaches.size(); i++) {
            m_allcaches[i].Serialise(out);
    }
}
