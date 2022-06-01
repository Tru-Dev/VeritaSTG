/************************************************\
 * VeritaSTG: log.hpp                           *
 * Implements logging, split between            *
 * standard output and file verita.log.         *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/log.hpp>

#include <string>
#include <fstream>
#include <iostream>

#include <fmt/core.h>

std::ofstream logFile("verita.log", std::ofstream::trunc);

void VeritaSTG::Log(VeritaSTG::LogLevel level, std::string str) {
    std::string prefix;
    switch (level) {
    case VeritaSTG::LogLevel::Error:
        prefix = "[ERROR]";
        break;
    case VeritaSTG::LogLevel::Warning:
        prefix = "[WARNING]";
        break;
    case VeritaSTG::LogLevel::Info:
        prefix = "[INFO]";
        break;
    case VeritaSTG::LogLevel::Debug:
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

void VeritaSTG::CloseLogFile() { logFile.close(); }
