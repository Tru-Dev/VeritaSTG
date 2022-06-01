/************************************************\
 * VeritaSTG: ResourcePool.cpp                  *
 * Root engine implementation.                  *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/ResourcePool.hpp>

#include <string>
#include <utility>

#include <miniaudio.h>

// #include <Game.hpp>
#include <VeritaSTG/Resource.hpp>

unsigned int VeritaSTG::Fnv1Hash(std::string id) {
    unsigned int hash = FNV_OFFSET;
    for (unsigned char c : id) {
        hash *= FNV_PRIME;
        hash ^= c;
    }
    return hash;
}

void VeritaSTG::ResourcePool::AddMusic(std::string id, std::string path) {
    MusicPool.emplace(std::piecewise_construct,
        std::forward_as_tuple(VeritaSTG::Fnv1Hash(id)),
        std::forward_as_tuple(new VeritaSTG::LazyResourceReference<ma_sound>(path))
    );
}

VeritaSTG::LazyResourceReference<ma_sound>* VeritaSTG::ResourcePool::FindMusic(std::string id) {
    int hash = VeritaSTG::Fnv1Hash(id);
    if (MusicPool.contains(hash))
        return MusicPool[hash];
    return nullptr;
}
