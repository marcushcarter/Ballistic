#pragma once

struct Project;

bool Serialize(const Project& project);
bool Deserialize(Project& project);
