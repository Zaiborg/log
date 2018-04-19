#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

#include "fmt.hpp"
#include "sink.hpp"

namespace zaiborg
{
        class Logger
        {
        public:
                Logger() {}

                explicit Logger(std::unique_ptr<Sink>&& s) {
                        sinks.emplace_back(std::move(s));
                }
                explicit Logger(Sink* s) : Logger(std::unique_ptr<Sink>(s)) {
                }


                template <typename ...Args>
                void write(const std::string& format, Args ...args) {
                        write_impl(format, args...);
                }
                void write(const std::string& format) {
                        write_impl(std::string("%s"), format);
                }

                template <typename ...Args>
                void write(const std::wstring& format, Args ...args) {
                        write_impl(format, args...);
                }

                void write(const std::wstring& format) {
                        write_impl(std::wstring(L"%ls"), format);
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
