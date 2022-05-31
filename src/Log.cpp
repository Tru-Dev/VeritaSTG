/************************************************\
 * VeritaSTG: Log.hpp                           *
 * Implements logging, split between            *
 * standard output and file verita.log.         *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/Log.hpp>

#include <string>
#include <fstream>
#include <iostream>

#include <fmt/core.h>

using namespace VeritaSTG;

std::ofstream logFile("verita.log", std::ofstream::app | std::ofstream::trunc);

void Log(LogLevel level, std::string str) {
    std::string prefix;
    switch (level) {
    case LogLevel::Error:
        prefix = "[ERROR]";
        break;
    case LogLevel::Warning:
        prefix = "[WARNING]";
        break;
    case LogLevel::Info:
        prefix = "[INFO]";
        break;
    case LogLevel::Debug:
        prefix = "[DEBUG]";
        break;
    default:
        prefix = "[VERBOSE]";
        break;
    }
    std::string output = fmt::format("{:<12}{}", prefix, str);

    logFile << output.c_str() << '\n';
    std::cout << output.c_str() << '\n';
}
