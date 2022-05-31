/************************************************\
 * VeritaSTG: ResourceEngineWrapper.cpp         *
 * Wraps the implementations of resources.      *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>

#include <miniaudio.h>

#include "Resource.hpp"

namespace VeritaSTG {
    class ResourceEngineWrapper{
        ma_engine miniaudio_bgm;
        // ma_engine miniaudio_sfx;
    public:
        inline ResourceResult<ma_sound> LoadMusic(std::string path) {
            ma_sound bgm;
            ma_result result = ma_sound_init_from_file(
                &miniaudio_bgm,
                path.c_str(),
                MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION,
                NULL,
                NULL,
                &bgm
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