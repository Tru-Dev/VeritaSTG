/************************************************\
 * VeritaSTG: GlobalEventContext.hpp            *
 * Wraps engine state and behaviors for passing *
 * to event callbacks.                          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <miniaudio.h>
#include <filesystem>

#include <fmt/core.h>

#include "log.hpp"
#include "engine_panic.hpp"
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
        void PlayMusic(std::string id) {
            auto bgm = resPool->FindMusic(id);
            if (!bgm->Initialized()) {
                std::string bgmPath = bgm->GetPath();
                if (!std::filesystem::exists(bgmPath)) {
                    VeritaSTG::EnginePanic(fmt::format(
                        "Error upon loading music \"{}\": path \"{}\" does not exist",
                        id, bgmPath
                    ));
                }
                auto resres = resEngines->LoadMusic(bgmPath);
                if (resres.result != 0) {
                    VeritaSTG::EnginePanic(
                        fmt::format("Error upon loading music \"{}\": {}", id, resres.result)
                    );
                    return;
                }
                bgm->Initialize(resres.resource);
            }

            ma_sound_start(bgm->Unwrap());
        }
        void StopMusic(std::string id) {
            auto bgm = resPool->FindMusic(id);
            if (!bgm->Initialized()) return;
            ma_sound* inner_bgm = bgm->Unwrap();
            if (!ma_sound_is_playing(inner_bgm)) return;
            ma_sound_stop(inner_bgm);
            ma_sound_seek_to_pcm_frame(inner_bgm, 0);
        }
        inline E GetEventData(void) { return eventData; }
    };
}
