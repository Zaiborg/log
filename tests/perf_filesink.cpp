﻿
#include <chrono>

#include "../include/logger.hpp"

struct tmr
{
        tmr() {}
        
        void start(){
                _start = std::chrono::high_resolution_clock::now();
        }

        std::chrono::nanoseconds ellapsed()const {
                auto end = std::chrono::high_resolution_clock::now();
                return end - _start;
        }

        std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};


int main(int argc, char** argv) {

        zaiborg::Logger<char> afile_log(new zaiborg::FileSink("test_ascii.log"));
        zaiborg::Logger<wchar_t> wfile_log(new zaiborg::FileSink("test_unicode.log"));
        zaiborg::Logger<char> console(new zaiborg::ConsoleSink);


        tmr t;

        for (int n = 0; n < 10; ++n) {
                t.start();
                for (int i = 0; i < 100000; ++i)
                        afile_log.write("zaiborg::Logger printing message nr. %d -> Hello World! and some garbage: %s", i, "aaaaaaaaaaaaaaaaaaeeeeeeeeeeeeeeeeeeeeeeeiiiiiiiiiiiiiiiiiiiiiiooooooooooooooooooooouuuuuuuuuuuuuuuuuu");
                auto w1 = std::chrono::duration_cast<std::chrono::microseconds>(
                        t.ellapsed());

                console.write("logging 100000 ascii entries took\t%luus", 
                        std::chrono::duration_cast<std::chrono::microseconds>(w1).count());

                t.start();
                for (int i = 0; i < 100000; ++i)
                        wfile_log.write(L"zaiborg::Logger printing message nr. %d -> 「こんにちは世界」 and some garbage: %ls", i, L"aaaaaaaaaaaaaaaaaaeeeeeeeeeeeeeeeeeeeeeeeiiiiiiiiiiiiiiiiiiiiiiooooooooooooooooooooouuuuuuuuuuuuuuuuuu");
                auto w2 = std::chrono::duration_cast<std::chrono::microseconds>(
                        t.ellapsed());

                console.write("logging 100000 unicode entries took\t%luus", 
                        std::chrono::duration_cast<std::chrono::microseconds>(w2).count());

        }



}