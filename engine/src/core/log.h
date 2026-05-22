#pragma once
#include "pch.h"

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

struct Logger
{
    static inline LogLevel level = LogLevel::Trace;

    static void Trace(const char* fmt, ...);
    static void Debug(const char* fmt, ...);
    static void Info(const char* fmt, ...);
    static void Warn(const char* fmt, ...);
    static void Error(const char* fmt, ...);
    static void Fatal(const char* fmt, ...);
    static void Log(LogLevel level, const char* fmt, va_list args);

    static void SetLevel(LogLevel lvl) { level = lvl;}
};

#define LOG_TRACE(...) Logger::Trace(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::Debug(__VA_ARGS__)
#define LOG_INFO(...) Logger::Info(__VA_ARGS__)
#define LOG_WARN(...) Logger::Warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::Error(__VA_ARGS__)
#define LOG_FATAL(...) Logger::Fatal(__VA_ARGS__)