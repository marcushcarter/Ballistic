#pragma once
#include <cstdint>

namespace ballistic {

struct EditorContext;

struct ViewportPanel {
    bool open = false;
    uint32_t last_viewport_w = 0, last_viewport_h = 0;

    void draw(EditorContext& ctx);
};

}