/************************************************\
 * VeritaSTG: ResourcePool.hpp                  *
 * Defines the resource storage class.          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>
#include <unordered_map>

#include <miniaudio.h>

#include "Resource.hpp"

// FNV Hash Constants
#define FNV_PRIME  0x01000193
#define FNV_OFFSET 0x811c9dc5

namespace VeritaSTG {
    unsigned int Fnv1Hash(std::string id);

    class ResourcePool {
        template <typename V>
        using TypePool = std::unordered_map<unsigned int, V>;

        TypePool<LazyResource<ma_sound>> MusicPool;
        // More to come...

    public:
        void AddMusic(std::string id, std::string path);

        LazyResource<ma_sound>* FindMusic(std::string id);
    };
}

