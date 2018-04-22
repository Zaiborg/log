#pragma once

#include <string>
#include <stdarg.h>
#include <wchar.h>

#include "platform.hpp"

namespace zaiborg
{
        namespace fmt
        {
                template <typename T>
                T convert_argument(T value) {
                        return value;
                }
                template <typename T>
                const T* convert_argument(const std::basic_string<T>& value) {
                        return value.c_str();
                }


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
                        int res = vswprintf(b, s, f, args);
                        va_end(args);
                        return res;
                }

               
                template<typename char_t, typename ...Args>
                std::basic_string<char_t> c_format(
                        const std::basic_string<char_t>& format,
                        Args ...args) {

                        int size = format.size() + 50;
                        std::basic_string<char_t> result;
                        for (;;)
                        {
                                result.resize(size);
                                int bytes_written = fmt::snprintf(
                                        const_cast<char_t*>(result.data()),
                                        result.size(),
                                        format.c_str(),
                                        convert_argument(args)...);

                                if (bytes_written != -1 &&
                                        bytes_written < size)
                                {
                                        result.resize(bytes_written);
                                        break;
                                }
                                if (bytes_written > -1)
                                        size = bytes_written + 1;
                                else
                                        size *= 2;
                        }

                        return result;
                }
        }
}

