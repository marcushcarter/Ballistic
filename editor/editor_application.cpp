#include <editor/editor_application.h>
#include <core/io/embedded_resource.h>
#include <core/error/error_macros.h>
#include <imgui.h>

namespace ballistic {

Error EditorApplication::on_init()
{
    using enum Error;
    Error err;

    EditorContext ctx{};
    ctx.renderer = &renderer;
    ctx.dev = &dev_systems;

    err = editor.create(ctx);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    err = window.set_icon(EmbeddedResource::load_icon(L"BALLISTIC_ICON"));
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);
    err = window.set_titlebar_color(RGB(20, 20, 25));
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    return Ok;
}

void EditorApplication::on_update(float p_dt)
{
    editor.update(p_dt);
    editor.draw();
}

void EditorApplication::on_shutdown()
{
    editor.destroy();
}

}