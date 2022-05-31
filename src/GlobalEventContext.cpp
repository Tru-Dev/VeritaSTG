/************************************************\
 * VeritaSTG: GlobalEventContext.cpp            *
 * Wraps engine state and behaviors for passing *
 * to event callbacks.                          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/GlobalEventContext.hpp>

using namespace VeritaSTG;

template <typename E>
void GlobalEventContext<E>::PlayMusic(std::string id) {
    auto bgm = resPool->FindMusic(id);
    if (!bgm->Initialized()) {
        auto resres = resEngines->LoadMusic(bgm->GetPath());
        if (!resres.result) {
            Log(LogLevel::Error,
                fmt::format("Error upon loading music: {}", resres.result)
            );
            return;
        }
        bgm->Initialize(resres.resource);
    }

    ma_sound_start(bgm->Unwrap());
}

template <typename E>
void GlobalEventContext<E>::StopMusic(std::string id) {
    auto bgm = resPool->FindMusic(id);
    if (!bgm->Initialized()) return;
    ma_sound* inner_bgm = bgm->Unwrap();
    if (!ma_sound_is_playing(inner_bgm)) return;
    ma_sound_stop(inner_bgm);
    ma_sound_seek_to_pcm_frame(inner_bgm, 0);
}
