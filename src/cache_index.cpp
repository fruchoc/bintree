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

    cout << root << endl;

    Cache index_root;
    index_root.SetIndex(GetNextIndex(), root);

    m_allcaches.push_back(index_root);
    PrintAllCaches();
}

//! Gets the next index number
int CacheIndex::GetNextIndex() {

    cout << "cache is " << m_allcaches.size() << " long" << endl;
    return m_allcaches.size() + 1;
}

void CacheIndex::PrintAllCaches() {
    vector <Cache>::iterator it;
    for (it = m_allcaches.begin(); it < m_allcaches.end(); it++)
        cout << " " <<  &it;
    cout << endl;
}
