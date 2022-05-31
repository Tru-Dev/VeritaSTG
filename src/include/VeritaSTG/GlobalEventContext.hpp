/************************************************\
 * VeritaSTG: GlobalEventContext.hpp            *
 * Wraps engine state and behaviors for passing *
 * to event callbacks.                          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include "miniaudio.h"
#include "fmt/core.h"

#include "Log.hpp"
#include "ResourceEngineWrapper.hpp"
#include "ResourcePool.hpp"

namespace VeritaSTG {
    // For one-time callbacks (Init, Cleanup)
    struct OnceData {
        double timeTotal;
    };

    // For Frame callback
    struct FrameData {
        double timeDelta;
        double timeTotal;
    };

    // For Key callback
    struct KeyData {
        int key;
        int scancode;
        int action;
        int mods;
    };

    template <typename E>
    class GlobalEventContext {
        ResourceEngineWrapper* resEngines;
        ResourcePool* resPool;

        E eventData;
    public:
        GlobalEventContext(void) = delete;
        GlobalEventContext(const GlobalEventContext&) = delete;
        GlobalEventContext& operator=(const GlobalEventContext) = delete;

        inline GlobalEventContext(
            ResourceEngineWrapper* resEngines, ResourcePool* resPool, E eventData
        ) {
            this->resEngines = resEngines;
            this->resPool = resPool;
            this->eventData = eventData;
        }

        inline void LoadMusic(std::string id, std::string path) { resPool->AddMusic(id, path); }
        void PlayMusic(std::string id);
        void StopMusic(std::string id);
        inline E GetEventData(void) { return eventData; }
    };
}
