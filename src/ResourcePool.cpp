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

unsigned int VeritaSTG::Fnv1Hash(std::string id) {
    unsigned int hash = FNV_OFFSET;
    for (unsigned char c : id) {
        hash *= FNV_PRIME;
        hash ^= c;
    }
    return hash;
}

void VeritaSTG::ResourcePool::AddMusic(std::string id, std::string path) {
    LazyResource<ma_sound> music(path);
    MusicPool.emplace(VeritaSTG::Fnv1Hash(id), music);
}

VeritaSTG::LazyResource<ma_sound>* VeritaSTG::ResourcePool::FindMusic(std::string id) {
    return &MusicPool[VeritaSTG::Fnv1Hash(id)];
}
