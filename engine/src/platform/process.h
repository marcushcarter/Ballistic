#pragma once
#include <filesystem>
#include <string>

bool LaunchProcess(const std::filesystem::path& exePath, const std::filesystem::path& workingDir, const std::wstring& args = L"");
