#pragma once

#include <stdio.h>
#include <stdarg.h>

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

namespace GameEngine
{
    double time();

    namespace LOG
    {
        // Get Current Timestamp
        std::string TIME_NOW();

        // Print a Custom Log
        void CUSTOM(char type, std::string whereami, std::string message, va_list args);

        // Print a Custom Log
        void CUSTOM(char type, std::string whereami, std::string message, ...);

        // Print a System Message
        void SYSTEM(std::string whereami, std::string message, ...);

        // Print a Debug Message
        void DEBUG(std::string whereami, std::string message, ...);

        // Print a Warning Message
        void WARNING(std::string whereami, std::string message, ...);

        // Print an Error Message
        void ERROR(std::string whereami, std::string message, ...);
    }
}