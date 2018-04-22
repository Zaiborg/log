#pragma once

#include <stdexcept>

#ifdef _WIN32

#include <iostream>
#include <stdarg.h>

namespace zaiborg
{
        inline static int snprintf(
                char* b,
                size_t s,
                const char* f,
                ...) {

                va_list args;
                va_start(args, f);
                int res = vsnprintf(b, s, f, args);
                va_end(args);
                return res;
        }
        
        inline static int snprintf(
                wchar_t* b,
                size_t s,
                const wchar_t* f,
                ...) {

                va_list args;
                va_start(args, f);
                int res = _vsnwprintf_s(b, s, s, f, args);
                va_end(args);
                return res;
        }
}

#else

namespace zaiborg
{
        inline static int snprintf(
                char* b,
                size_t s,
                const char* f,
                ...) {

                throw std::runtime_error("TODO: not implemented yet");
        }

        inline static int snprintf(
                wchar_t* b,
                size_t s,
                const wchar_t* f,
                ...) {

                throw std::runtime_error("TODO: not implemented yet");
        }

}
#endif