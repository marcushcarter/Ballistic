#pragma once
#include "bepch.h"
#include "Renderer/DrawElementsIndirectCommand.h"
#include "Renderer/RenderDevice/IRenderDevice.h"
#include "Renderer/Backends/OpenGL/all.h"

namespace ballistic
{
    class GLRenderDevice : public IRenderDevice {
    public:
        GLRenderDevice() = default;
        virtual ~GLRenderDevice() { Shutdown(); }

        bool Init() override;
        void Shutdown() override;

        void Execute(const std::vector<DrawElementsIndirectCommand>& commands) override;
		
        void Clear(float r, float g, float b, float a) override;
		void BlitToScreen() override;

        void Resize(uint32_t w, uint32_t h) override;

        void* GetNativeTextureHandle() override;

    private:
		std::shared_ptr<gl::Texture2D> m_outputTexture;
		std::shared_ptr<gl::Framebuffer> m_mainFramebuffer;
	  
		std::shared_ptr<gl::Shader> m_blitShader;

        std::shared_ptr<gl::VertexArray> m_meshVAO;
        std::shared_ptr<gl::Buffer> m_meshVBO;
        std::shared_ptr<gl::Buffer> m_meshEBO;
        std::shared_ptr<gl::Buffer> m_indirectBuffer;
        
		std::shared_ptr<gl::Shader> tempDraw;
    };

} // namespace ballistic
