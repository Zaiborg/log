#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

#include "fmt.hpp"
#include "sink.hpp"

namespace zaiborg
{
        template <typename char_t>
        class Logger
        {
        public:
                template <typename T>
                const T& check_string(const T& arg) {
                        return arg;
                }

                template <typename T>
                const std::basic_string<T>& check_string(const std::basic_string<T>& arg) {
                        static_assert(std::is_same<T, char_t>::value,
                                "invalid string in arguments");
                        return arg;
                }
                template <typename T>
                const T* check_string(const T* arg) {
                        static_assert(std::is_same<T, char_t>::value,
                                "invalid string in arguments");
                        return arg;
                }


                Logger() {}

                explicit Logger(std::unique_ptr<Sink>&& s) {
                        sinks.emplace_back(std::move(s));
                }
                explicit Logger(Sink* s) : Logger(std::unique_ptr<Sink>(s)) {
                }

                template <typename ...Args>
                void write(const std::basic_string<char_t>& format, Args ...args) {
                        write_impl(format, check_string(args)...);
                }

                template <typename C = char_t>
                typename std::enable_if<std::is_same<char, C>::value>::type
                write(const std::basic_string<char>& format) {
                        write_impl(std::basic_string<char>("%s"), format);
                }

                template <typename C = char_t>
                typename std::enable_if<std::is_same<wchar_t, C>::value>::type
                write(const std::basic_string<wchar_t>& format) {
                        write_impl(std::basic_string<wchar_t>(L"%ls"), format);
                }


        private:
                std::vector<std::unique_ptr<Sink>> sinks;

                template<typename string_t, typename ...Args>
                void write_impl(const string_t& format, Args ...args) {
                        string_t message = fmt::c_format(format, args...);

                        for (auto& sink : sinks)
                                sink->write(message);
                }

        };
}
