#include "editor_render_path.h"
#include "graphics/render_graph/render_graph.h"
#include "graphics/passes/scene_placeholder_pass.h"
#include "graphics/passes/editor_imgui_pass.h"

void EditorRenderPath::Build(RenderGraph& g)
{
    g.AddPass(std::make_unique<ScenePlaceholderPass>());
    g.AddPass(std::make_unique<EditorImGuiPass>(*imguiLayer));
}
