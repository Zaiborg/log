#pragma once

#include <exception>

#ifdef _WIN32

#include <io.h>
#include <fcntl.h>
#include <iostream>

namespace zaiborg
{
        inline static void change_console_to_ascii() {
                _setmode(_fileno(stdout), _O_TEXT);
        }

        inline static void change_console_to_unicode() {
                _setmode(_fileno(stdout), _O_WTEXT);
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
}
#endif