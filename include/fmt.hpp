#pragma once

#include <string>

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


                template <typename ...Args>
                size_t vsnprintf_stringtyped(
                        std::string& result,
                        const std::string& format,
                        Args... args) {

                        return snprintf(
                                const_cast<std::string::value_type*>(
                                        result.data()),
                                result.size(),
                                format.c_str(),
                                args...);
                }

                template <typename ...Args>
                size_t vsnprintf_stringtyped(
                        std::wstring& result,
                        const std::wstring&
                        format,
                        Args... args) {

                        return _snwprintf_s(
                                const_cast<std::wstring::value_type*>(
                                        result.data()),
                                result.size(),
                                result.size(),
                                format.c_str(),
                                args...);
                }
                
                template<typename char_t, typename ...Args>
                std::basic_string<char_t> c_format(
                        const std::basic_string<char_t>& format, Args ...args) {

                        size_t size = format.size() + 50;
                        std::basic_string<char_t> result;
                        for (;;)
                        {
                                result.resize(size);
                                size_t bytes_written = vsnprintf_stringtyped(
                                        result,
                                        format,
                                        convert_argument(args)...);

                                if (bytes_written != -1 &&
                                        bytes_written < size)
                                {
                                        result.resize(bytes_written);
                                        return result;
                                }
                                if (bytes_written > -1)
                                        size = bytes_written + 1;
                                else
                                        size *= 2;
                        }

                        // TODO throw error?
                        return result;
                }
        }
}

