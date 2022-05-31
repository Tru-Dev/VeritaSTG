/************************************************\
 * VeritaSTG: CallbackRegistry.hpp              *
 * Definitions for callback hooks.              *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include "GlobalEventContext.hpp"

#define CREATE_CALLBACK(cb_name, data_type) \
private: \
    EventCallback<data_type> cb_name##Callback = nullptr; \
public: \
    inline int Set##cb_name##Callback(EventCallback<data_type> cb_name##Callback) { \
        int ret = 0; \
        if (cb_name##Callback) ret = -1; \
        this->cb_name##Callback = cb_name##Callback; \
        return ret; \
    } \
    inline int cb_name(GlobalEventContext<data_type> ctx) { \
        if (!cb_name##Callback) return -1; \
        cb_name##Callback(&ctx); \
        return 0; \
    }
// end define CREATE_CALLBACK


namespace VeritaSTG {
    template <typename D>
    using EventCallback = void (*)(GlobalEventContext<D>*);
    class CallbackRegistry {
        CREATE_CALLBACK(Init, OnceData)
        CREATE_CALLBACK(Cleanup, OnceData)
        CREATE_CALLBACK(Frame, FrameData)
        CREATE_CALLBACK(Key, KeyData)
    };
}
