#pragma once

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

                ConsoleSink() {
                        std::cout.imbue(std::locale(std::cout.getloc()));
                        std::wcout.imbue(std::locale(std::wcout.getloc()));
                }

                virtual void write(const std::string& line) override {
                        std::cout << line << std::endl;
                }
                virtual void write(const std::wstring& line)override {
                        std::wcout << line << std::endl;
                }
        };

        class FileSink : public Sink
        {
        public:
                FileSink(const std::string& filename) 
                {
                        afs.open(filename.c_str(),
                                std::fstream::out | std::fstream::app);
                        wfs.open(filename.c_str(),
                                std::wfstream::out | std::wfstream::app);

                        wfs.imbue(std::locale(wfs.getloc(),
                                new std::codecvt_utf8_utf16<wchar_t>()));
                }

                virtual void write(const std::wstring& line)override {
                        wfs << line << std::endl;
                }
                virtual void write(const std::string& line) override {
                        afs << line << std::endl;;
                }

                std::fstream afs;
                std::wfstream wfs;

        };
}
