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

    m_allcaches[id].PrintIndices();
}

//! Gets the next index number
int CacheIndex::GetNextIndex() {
    return m_allcaches.size() + 1;
}

//! Gets the next cache without a particle attached
int CacheIndex::GetNextEmptyCache() {
    int val(-1);
    int i(0);
    for (i = 0; i < (int)m_allcaches.size(); i++) {
        if (m_allcaches[i].HasPointer() == false) {
            val = i;
            break;
        } else {
            cout << "No empty cache found!";
        }

    }
    return val;
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
            break;
        }
    }

    /*if (val < 1) {
        cout << "Pointer not found." << endl;
    }*/
    return val;
}

const ParticleModel *CacheIndex::GetPointerReference(int id) {
    const ParticleModel *p;
    vector <Cache>::iterator it;
    for (it = m_allcaches.begin(); it < m_allcaches.end(); it++) {
        if (id == it->GetIndex()) {
            p = it->GetParticlePointer();
            break;
        }
    }
    return p;
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
        if (p->GetLeftChild() != NULL) SerialiseBinaryTree(p->GetLeftChild(), out);
        if (p->GetRightChild() != NULL) SerialiseBinaryTree(p->GetRightChild(), out);
    }
}

/*!
 * @brief       Writes the index to a binary file
 * @param out   Binary output stream
 */
void CacheIndex::SerialiseIndex(ostream &out) const {

    // Write the number of nodes
    int val(0);
    val = m_nodes;
    out.write((char*)&val, sizeof(val));

    // Loop over the allcaches vector
    int i(0);
    for (i = 0; i < (int)m_allcaches.size(); i++) {
            m_allcaches[i].Serialise(out);
    }
}

void CacheIndex::DeserialiseBinaryTree(ParticleModel *p, istream &in) {

    // Read in the node
    p->DeserialisePrimary(in);
    // Find the particle's cache!
    Cache *p_cache;
    if (GetPointerIndex(p) < 1) {
        p_cache = &(m_allcaches[GetNextEmptyCache()]);
        p_cache->SetParticle(p);
    } else {
        cout << "ERROR: no cache found!" << endl;
    }

    // Now read the children..
    if (p_cache->HasChildren()) {
        ParticleModel new_lc;
        DeserialiseBinaryTree(&new_lc, in);
        p->SetLeftChild(&new_lc);
        new_lc.SetParent(p);

        ParticleModel new_rc;
        DeserialiseBinaryTree(&new_rc, in);
        p->SetRightChild(&new_rc);
        new_rc.SetParent(p);
    }
}

void CacheIndex::RegenerateParticleLinks(ParticleModel *p) {
    Cache *p_cache;
    // Loop over all particles
    int i(0);
    for (i = 0; i < (int)m_allcaches.size(); i++) {
        p_cache = &m_allcaches[i];
        if (p_cache->HasParticles() == true) {
            int lp_id(0);
            int rp_id(0);

            lp_id = p_cache->GetIndexLP();
            rp_id = p_cache->GetIndexRP();

            //p->SetLeftParticle(GetPointerReference(lp_id));
        }
    }
}

void CacheIndex::DeserialiseIndex(istream &in) {

    // Read number of nodes of the tree
    int val(0);
    in.read(reinterpret_cast<char*>(&val), sizeof(val));
    m_nodes = (int)val;

    // Add caches to allcaches vector
    int i(0);
    for (i = 0; i < m_nodes; i++) {
        Cache newnode;
        newnode.Deserialise(in);
        m_allcaches.push_back(newnode);
    }

    /*Check index information
    for (i = 0; i < m_nodes; i++) {
        m_allcaches[i].PrintIndices();
    }*/

}
