
#pragma once
#include <core/application/application.h>

namespace ballistic {

struct GameApplication : Application
{
    bool debug_menu_visible = true;

    Error on_init() override;
    void on_update(float p_dt) override;
    void on_shutdown() override;
    
    void draw_menu_bar();
};

}