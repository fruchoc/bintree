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

    //! Print all caches from the object
    void PrintAllCaches();

    //! Recursive function to serialise the binary tree object
    void SerialiseBinaryTree(const ParticleModel *p, ostream &out) const;

    //! Serialise the binary tree index
    void SerialiseIndex(ostream &out) const;

private:

    //! Recursive helper function to create loop
    void CreateIndexLoop(const ParticleModel *p);

    //! Helper function to collect all indices
    void FindAllIndices(int id);

    //! Gets the next index number
    int GetNextIndex();

    //! Return the index of a given pointer
    int GetPointerIndex(const ParticleModel *p);

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
