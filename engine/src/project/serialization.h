#pragma once

struct Project;

// std::string FormatToString(VkFormat format);
// VkFormat StringToFormat(const std::string& s);

bool Serialize(const Project& project);
bool Deserialize(Project& project);
