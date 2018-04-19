#pragma once

#include "platform.hpp"

namespace zaiborg
{
        class Sink
        {
        public:
                virtual void write(const std::string& line) = 0;
                virtual void write(const std::wstring& line) = 0;
        };

        class ConsoleSink : public Sink
        {
        public:
                virtual void write(const std::string& line) override {
                        zaiborg::change_console_to_ascii();
                        std::cout << line << std::endl;
                }
                virtual void write(const std::wstring& line)override {
                        zaiborg::change_console_to_unicode();
                        std::wcout << line << std::endl;
                }
        };
}
