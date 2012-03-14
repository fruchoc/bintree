/*
 * cache_index.h
 *
 *  Created on: 14 Mar 2012
 *      Author: wjm34
 */

// Includes
#include "../include/cache.h"
#include <vector>

#ifndef CACHE_INDEX_H_
#define CACHE_INDEX_H_


class CacheIndex {
public:
    //! Default constructor
    CacheIndex();

    //! Default destructor
    virtual ~CacheIndex();

    //! Creates the Cache Index
    void CreateIndex(const ParticleModel *root);

    //! Gets the next index number
    int GetNextIndex();

    void PrintAllCaches();

private:
    //! A vector containing the list of all caches, each holding a particle
    std::vector<Cache> m_allcaches;

    //! Number of nodes
    int m_nodes;

    //! Number of leaf nodes
    int m_leaf;

    //! Number of non-leaf nodes
    int m_nonleaf;
};

#endif /* CACHE_INDEX_H_ */
