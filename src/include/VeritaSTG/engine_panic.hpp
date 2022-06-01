/************************************************\
 * VeritaSTG: engine_panic.hpp                  *
 * Implements a handler for unrecoverable       *
 * errors.                                      *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>

#include <boxer/boxer.h>

#include "log.hpp"

namespace VeritaSTG {
    inline void EnginePanic(std::string message, int code = -1) {
        Log(LogLevel::Error, message);
        boxer::show(message.c_str(), "VeritaSTG Error", boxer::Style::Error, boxer::Buttons::OK);

        exit(code);
    }
}
