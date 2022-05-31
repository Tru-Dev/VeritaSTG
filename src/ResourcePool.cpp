/************************************************\
 * VeritaSTG: ResourcePool.cpp                  *
 * Root engine implementation.                  *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/ResourcePool.hpp>

#include <string>

#include <miniaudio.h>

// #include <Game.hpp>
#include <VeritaSTG/Resource.hpp>

using namespace VeritaSTG;

unsigned int Fnv1Hash(std::string id) {
    unsigned int hash = FNV_OFFSET;
    for (unsigned char c : id) {
        hash *= FNV_PRIME;
        hash ^= c;
    }
    return hash;
}

void ResourcePool::AddMusic(std::string id, std::string path) {
    LazyResource<ma_sound> music(path);
    MusicPool.emplace(Fnv1Hash(id), music);
}

LazyResource<ma_sound>* ResourcePool::FindMusic(std::string id) {
    return &MusicPool[Fnv1Hash(id)];
}
