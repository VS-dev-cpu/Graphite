#include <GameEngine/core/log.h>
#include <chrono>

namespace GameEngine
{
    // Return Time in Seconds
    double time()
    {
        struct timespec res;
        clock_gettime(CLOCK_MONOTONIC, &res);
        return (1000.0 * res.tv_sec + (double)res.tv_nsec / 1e6) / 1000.0;
    }

    // Get Current Timestamp
    std::string stime()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        // Extract to Variables
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        std::string date = oss.str();
        oss.str("");
        oss << std::put_time(&tm, "%H:%M:%S");
        std::string time = oss.str();

        return time.c_str();
    }

    namespace LOG
    {
        int max = 12;
        int c = 0;

        // Print a Custom Log
        void CUSTOM(char type, std::string whereami, std::string message, va_list args)
        {
            if (whereami.length() > max)
            {
                if (c > 8)
                {
                    c = 0;
                    max = whereami.length();
                }
                else
                    c++;
            }

            for (int i = whereami.length(); i < max; i++)
                whereami += ' ';
            if (whereami.length() > max)
            {
                whereami.erase(max, std::string::npos);
                whereami[max - 1] = '.';
            }

            vprintf(("[ " + stime() + " ]  [" + type + "]  " + whereami + "  =>  " + message + "\n").c_str(), args);
        }

        // Print a Custom Log
        void CUSTOM(char type, std::string whereami, std::string message, ...)
        {
            va_list args;
            va_start(args, message);

            CUSTOM(type, whereami, message, args);

            va_end(args);
        }

        // Print a System Message
        void SYSTEM(std::string whereami, std::string message, ...)
        {
            va_list args;
            va_start(args, message);

            CUSTOM('S', whereami, message, args);

            va_end(args);
        }

        // Print a Debug Message
        void DEBUG(std::string whereami, std::string message, ...)
        {
            va_list args;
            va_start(args, message);

            CUSTOM('D', whereami, message, args);

            va_end(args);
        }

        // Print a Warning Message
        void WARNING(std::string whereami, std::string message, ...)
        {
            va_list args;
            va_start(args, message);

            CUSTOM('W', whereami, message, args);

            va_end(args);
        }

        // Print an Error Message
        void ERROR(std::string whereami, std::string message, ...)
        {
            va_list args;
            va_start(args, message);

            CUSTOM('E', whereami, message, args);

            va_end(args);
        }
    }
}