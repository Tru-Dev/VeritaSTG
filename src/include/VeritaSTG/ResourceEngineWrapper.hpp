/************************************************\
 * VeritaSTG: ResourceEngineWrapper.cpp         *
 * Wraps the implementations of resources.      *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>

#include <fmt/core.h>
#include <miniaudio.h>

#include "Resource.hpp"
#include "engine_panic.hpp"
#include "log.hpp"

namespace VeritaSTG {
    class ResourceEngineWrapper{
        ma_engine miniaudio_inst;

        bool initialized = false;
    public:
        ~ResourceEngineWrapper() {
            if (initialized) Uninitialize();
        }

        void Initialize(void) {
            if (initialized) return;
            ma_result result = ma_engine_init(NULL, &miniaudio_inst);
            if (result != 0) 
                EnginePanic(fmt::format("Could not load the audio engine: {}", result));
            initialized = true;
        }

        void Uninitialize(void) {
            if (!initialized) return;
            ma_engine_uninit(&miniaudio_inst);
            initialized = false;
        }

        ResourceResult<ma_sound*> LoadMusic(std::string path) {
            ma_sound* bgm = new ma_sound;
            ma_result result = ma_sound_init_from_file(
                &miniaudio_inst,
                path.c_str(),
                MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
                NULL,
                NULL,
                bgm
            );
            return {
                // resource =
                bgm,
                // result =
                result,
            };
        }
    };
}
