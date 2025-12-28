#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #include <shellapi.h>
#endif

#include <algorithm>
#include <atomic>
#include <cfloat>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <deque>
#include <sstream>