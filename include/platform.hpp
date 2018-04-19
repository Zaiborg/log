#pragma once

#include <stdexcept>

#ifdef _WIN32

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <stdarg.h>

namespace zaiborg
{
        inline static void change_console_to_ascii() {
                _setmode(_fileno(stdout), _O_TEXT);
        }

        inline static void change_console_to_unicode() {
                _setmode(_fileno(stdout), _O_WTEXT);
        }

        inline static int snprintf(char* b, size_t s, const char* f, ...) {
                va_list args;
                va_start(args, f);
                return vsnprintf(b, s, f, args);
                va_end(args);
        }
        
        inline static int snprintf(wchar_t* b, size_t s, const wchar_t* f, ...) {
                va_list args;
                va_start(args, f);
                return _vsnwprintf_s(b, s, s, f, args);
                va_end(args);
        }
}

#else

namespace zaiborg
{
        inline static void change_console_to_ascii() {
                throw std::runtime_error("TODO: not implemented yet");
        }

        inline static void change_console_to_unicode() {
                throw std::runtime_error("TODO: not implemented yet");
        }

        inline static int snprintf(char* b, size_t s, const char* f, ...) {
                throw std::runtime_error("TODO: not implemented yet");
        }

        inline static int snprintf(wchar_t* b, size_t s, const wchar_t* f, ...) {
                throw std::runtime_error("TODO: not implemented yet");
        }

}
#endif