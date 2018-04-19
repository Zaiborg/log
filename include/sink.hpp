#pragma once

#include "platform.hpp"

#include <string>
#include <fstream>
#include <codecvt>

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

        class FileSink : public Sink
        {
        public:
                FileSink(const std::string& filename) 
                {
                        fs.open(filename.c_str(), std::wfstream::out | std::wfstream::app);
                        fs.imbue(std::locale(fs.getloc(), new std::codecvt_utf8_utf16<wchar_t>()));
                }

                virtual void write(const std::wstring& line)override {
                        fs << line << std::endl;
                }
                virtual void write(const std::string& line) override {
                        write(std::wstring(line.begin(), line.end()));
                }

                std::wfstream fs;

        };
}
