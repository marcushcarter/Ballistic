#pragma once

namespace ballistic {

struct Renderer;
struct DevSystems;

struct EditorContext
{
    Renderer* renderer = nullptr;
    DevSystems* dev = nullptr;
};

}