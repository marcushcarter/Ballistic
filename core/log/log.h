#pragma once
#include <vector>
#include <string>
#include <mutex>

namespace ballistic {

struct LogSink
{
    std::vector<std::string> lines;
    size_t max_lines = 4096;
    std::mutex mutex;

    void write(const char* s);
    void clear();
    std::string to_string();
};

LogSink& log_sink();
void log_write(const char* fmt, ...); 

}