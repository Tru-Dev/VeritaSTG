/************************************************\
 * VeritaSTG: Log.hpp                           *
 * Defines logging that is split between        *
 * standard output and file verita.log.         *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>
#include <fstream>
// #include <iostream>
// #include <fmt/core.h>

namespace VeritaSTG {
    enum class LogLevel {
        Error,
        Warning,
        Info,
        Debug,
        Verbose,
    };

    void Log(LogLevel level, std::string str);
}