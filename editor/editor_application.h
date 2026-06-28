
#pragma once
#include <core/application/application.h>
#include <editor/editor.h>

namespace ballistic {

struct EditorApplication : Application
{
    Editor editor;

    Error on_init() override;
    void on_update(float p_dt) override;
    void on_shutdown() override;
};

}