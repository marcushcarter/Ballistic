#pragma once
#include <string>
#include <vector>

std::string FileDialog(const char* title = "Select", const char* defaultPath = nullptr, bool pickFolder = false, const std::vector<std::pair<std::wstring, std::wstring>>& filters = {});
