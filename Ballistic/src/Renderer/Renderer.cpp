#include "Renderer.h"

namespace Ballistic {

	void Renderer::Init() {

		const char* source = R"(

		#version 460

		layout(local_size_x = 16, local_size_y = 16) in;

		layout(rgba32f, binding = 0) uniform image2D computeOutput;

		void main() {
		    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
		    ivec2 texSize = imageSize(computeOutput);
		    vec2 uv = vec2(gl_GlobalInvocationID.xy) / vec2(texSize);
		    imageStore(computeOutput, pixel, vec4(uv, 1.0, 1.0));
		}

		)";
    
	    m_Shader = std::make_shared<Shader>();;
	    m_Shader->attachSource(GL_COMPUTE_SHADER, source);
	    m_Shader->link();

	    // rtxComputeStats.timeQuery = new Query();

	    // m_RtxParametersUBO = std::make_shared<Buffer>(GL_UNIFORM_BUFFER);
		// m_RtxParametersUBO->allocate(sizeof(RTXUniformParameters), GL_DYNAMIC_DRAW);
		// m_RtxParametersUBO->bind(0);

	    // ConfigureRtxParametersUBO();
	    // ConfigureRtxTrianglesSSBO();
	    // ConfigureRtxMeshesSSBO();
	    // ConfigureRtxMaterialsSSBO();
	    // ConfigureRtxInstancesSSBO();
	    // ConfigureRtxSpheresSSBO();

	    m_Texture = std::make_shared<Image2D>(1280, 720);
	}

	std::shared_ptr<Image2D> Renderer::Render(AssetPool* assetPool) {
		m_Shader->bind();
		m_Texture->bind(0);

		// rtxInstances.clear();
		// rtxSpheres.clear();

		// UpdateRtxParametersUBO();
		// UpdateRtxTrianglesSSBO();
		// UpdateRtxMeshesSSBO();
		// UpdateRtxMaterialsSSBO();
		// UpdateRtxInstancesSSBO();
		// UpdateRtxSpheresSSBO();

		int groupX = (m_Texture->m_Width + 15) / 16;
	    int groupY = (m_Texture->m_Height + 15) / 16;
		m_Shader->dispatchCompute(groupX, groupY);

		GLuint fbo;
	    glGenFramebuffers(1, &fbo);
	    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
	                           GL_TEXTURE_2D, m_Texture->m_RendererID, 0);

	    GLenum status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
	    if (status != GL_FRAMEBUFFER_COMPLETE) {
	        std::cerr << "Framebuffer incomplete: " << status << std::endl;
	        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	        glDeleteFramebuffers(1, &fbo);
	        m_Texture->unbind(0);
	        return m_Texture;
	    }

	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // default framebuffer

	    // Blit entire texture to the window
	    glBlitFramebuffer(
	        0, 0, m_Texture->m_Width, m_Texture->m_Height,
	        0, 0, m_Texture->m_Width, m_Texture->m_Height,
	        GL_COLOR_BUFFER_BIT,
	        GL_NEAREST
	    );

	    // Cleanup
	    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	    glDeleteFramebuffers(1, &fbo);

		m_Texture->unbind(0);

		return m_Texture;
	}
	
}