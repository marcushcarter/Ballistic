#include "splash_render_path.h"
#include "graphics/render_graph/render_graph.h"
#include "graphics/passes/splash_pass.h"

void SplashRenderPath::Build(RenderGraph& g)
{
    g.AddPass(std::make_unique<SplashPass>(*renderer, *splash));
}
