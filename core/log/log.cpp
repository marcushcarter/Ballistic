#include <core/log/log.h>
#include <cstdio>
#include <cstdarg>

namespace ballistic {

LogSink& log_sink() {
    static LogSink instance;
    return instance;
}

void LogSink::write(const char* s)
{
    std::lock_guard lock(mutex);
    fputs(s, stderr);
    fputc('\n', stderr);
    lines.emplace_back(s);
    if (lines.size() > max_lines)
        lines.erase(lines.begin(), lines.begin() + (lines.size() - max_lines));
}

void LogSink::clear() {
    std::lock_guard lock(mutex);
    lines.clear();
}

std::string LogSink::to_string()
{
    std::lock_guard lock(mutex);
    std::string out;
    for (const std::string& line : lines) {
        out += line;
        out += '\n';
    }
    return out;
}

void log_write(const char* fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    log_sink().write(buf);
}

}