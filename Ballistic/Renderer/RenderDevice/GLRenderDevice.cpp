#include "Renderer/RenderDevice/GLRenderDevice.h"
#include "Core/IApplication.h"
#include "Root/Root.h"
#include "Root/LogManager/Log.h"
#include "Renderer/Backends/OpenGL/ShaderGLM.h"

namespace ballistic
{
    bool GLRenderDevice::Init() {

		// BIG VAO

		m_meshVAO = std::make_shared<gl::VertexArray>();
		m_meshVAO->create();
		m_meshVAO->bind();

		m_meshVBO = std::make_shared<gl::Buffer>();
		m_meshVBO->create(GL_ARRAY_BUFFER);
		m_meshVBO->bind();
		m_meshVBO->data(0, nullptr, GL_DYNAMIC_DRAW);
		

		m_meshEBO = std::make_shared<gl::Buffer>();
		m_meshEBO->create(GL_ELEMENT_ARRAY_BUFFER);
		m_meshEBO->bind();
		m_meshEBO->data(0, nullptr, GL_DYNAMIC_DRAW);
		
		m_meshVAO->vertexBuffer(0, m_meshVBO->get(), 0, sizeof(Vertex));
		m_meshVAO->indexBuffer(m_meshEBO->get());

		m_meshVAO->vertexAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
		m_meshVAO->vertexAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, normal));
		m_meshVAO->vertexAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, uv));

		m_indirectBuffer = std::make_shared<gl::Buffer>();
		m_indirectBuffer->create(GL_DRAW_INDIRECT_BUFFER);
		m_indirectBuffer->data(m_maxDraws * sizeof(DrawElementsIndirectCommand), nullptr, GL_DYNAMIC_DRAW);

		// TEXTURES AND STUFF

		m_outputTexture = std::make_shared<gl::Texture2D>();
		m_outputTexture->create(800, 600, GL_RGBA32F, GL_RGBA, GL_FLOAT);
    	m_outputTexture->setParameters(GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

		m_mainFramebuffer = std::make_shared<gl::Framebuffer>();
		m_mainFramebuffer->create();
		m_mainFramebuffer->attachColor(0, *m_outputTexture);

		gl::Renderbuffer depthBuffer;
		depthBuffer.create();
		depthBuffer.storage(GL_DEPTH_COMPONENT24, 800, 600);
		m_mainFramebuffer->attachDepth(depthBuffer);

		if (!m_mainFramebuffer->complete()) {
			LogError("Framebuffer incomplete");
			return false;
		}

		const char* vertexShaderSrc = R"(
		#version 460 core
		out vec2 TexCoords;
		void main() {
			const vec2 verts[3] = vec2[3](
				vec2(-1.0, -1.0),
				vec2( 3.0, -1.0),
				vec2(-1.0,  3.0)
			);
			gl_Position = vec4(verts[gl_VertexID], 0.0, 1.0);
			TexCoords = (gl_Position.xy + 1.0) * 0.5;
		}
		)";
		
		const char* fragmentShaderSrc = R"(
		#version 460 core
		in vec2 TexCoords;
		out vec4 FragColor;
		uniform sampler2D screenTexture;
		void main() {
			FragColor = texture(screenTexture, TexCoords);
		}
		)";
		
		m_blitShader = std::make_shared<gl::Shader>();
		m_blitShader->create();
		m_blitShader->attachShader(GL_VERTEX_SHADER, vertexShaderSrc);
		m_blitShader->attachShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
		m_blitShader->link();
		
		const char* tempVert = R"(
		#version 460 core
		layout(location = 0) in vec3 aPos;

		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProj;

		void main() {
			gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
		}

		)";
		
		const char* tempFrag = R"(
		#version 460 core
		out vec4 FragColor;
		void main() {
			FragColor = vec4(1.0); // pure white
		}
		)";

		tempDraw = std::make_shared<gl::Shader>();
		tempDraw->create();
		tempDraw->attachShader(GL_VERTEX_SHADER, tempVert);
		tempDraw->attachShader(GL_FRAGMENT_SHADER, tempFrag);
		tempDraw->link();

		LogInfo(
			"OpenGL Info: ", 
			"Renderer: ", glGetString(GL_RENDERER), ", ",
			"Vendor: ", glGetString(GL_VENDOR), ", ",
			"Version: ", glGetString(GL_VERSION), ", ",
			"GLSL Version: ", glGetString(GL_SHADING_LANGUAGE_VERSION)
		);

		LogDebug("OpenGL render device Initialized");
		return true;
    }

    void GLRenderDevice::Shutdown() {	
		m_outputTexture->destroy();
		m_mainFramebuffer->destroy();

		m_meshVAO->destroy();
		m_meshVBO->destroy();
		m_meshEBO->destroy();

		m_blitShader->destroy();
    }

    void GLRenderDevice::Execute(const std::vector<DrawElementsIndirectCommand>& commands) {

		GLuint vao, vbo, ebo;
		
		auto meshManager = GetRoot()->GetMeshManager();

		if (meshManager->GetAllMetadata().empty()) return; // nothing to draw

		const MeshMetadata& meta = meshManager->GetAllMetadata()[0];
		auto& verts = meshManager->GetVertexBuffer();
		auto& inds = meshManager->GetIndexBuffer();

		{
			
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, meta.vertexCount * sizeof(Vertex), verts.data() + meta.vertexOffset, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, meta.indexCount * sizeof(uint32_t), inds.data() + meta.indexOffset, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0); // pos
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(1); // normal
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(2); // uv
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		if (!meshManager->GetDirtyMetadata().empty()) {
			for (size_t idx : meshManager->GetDirtyMetadata()) {
				const MeshMetadata& meta = meshManager->GetAllMetadata()[idx];

				m_meshVBO->update(
					meta.vertexOffset * sizeof(Vertex),
					meta.vertexCount * sizeof(Vertex),
					meshManager->GetVertexBuffer().data() + meta.vertexOffset
				);

				m_meshEBO->update(
					meta.indexOffset * sizeof(Vertex),
					meta.indexCount * sizeof(Vertex),
					meshManager->GetIndexBuffer().data() + meta.indexOffset
				);

			}
			meshManager->ClearDirty();
			LogWarn("Reloaded opengl mesh vao, vbo, ebo");
		}

		m_indirectBuffer->update(0, commands.size() * sizeof(DrawElementsIndirectCommand), commands.data());

		m_mainFramebuffer->bind();
		gl::Viewport(0, 0, m_outputTexture->width(), m_outputTexture->height());
		Clear(0.1, 0.1, 0.1, 1.0);
		if (!commands.empty()) Clear(1.0, 0.0, 0.0, 1.0);

		m_meshVBO->update(0, verts.size() * sizeof(Vertex), verts.data());
		m_meshEBO->update(0, inds.size() * sizeof(uint32_t), inds.data());

		tempDraw->use();
		// m_meshVAO->bind();
		// m_indirectBuffer->bind();
		// gl::State::bindBuffer(GL_DRAW_INDIRECT_BUFFER, m_indirectBuffer->get());
		// // if (!commands.empty())
		// // 	m_meshVAO->drawElements(GL_TRIANGLES, commands[0].count, nullptr, 1);

		float time = glfwGetTime(); // seconds
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, time, glm::vec3(0.2f, 1.0f, 0.5f));

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3));
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(m_outputTexture->width()/m_outputTexture->height()), 0.1f, 100.0f);

		gl::setUniform(*tempDraw, "uModel", model);
		gl::setUniform(*tempDraw, "uView", view);
		gl::setUniform(*tempDraw, "uProj", proj);
		
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, meta.indexCount, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(m_meshVAO->get());
		glDrawElements(GL_TRIANGLES, meshManager->GetIndexBuffer().size(), GL_UNSIGNED_INT, 0);

		// glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, commands.size(), 0);

		m_mainFramebuffer->unbind();

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteVertexArrays(1, &vao);
    }
    
	void GLRenderDevice::Clear(float r, float g, float b, float a) {
		gl::ClearColor(r, g, b, a);
		gl::Clear();
	}
    
	void GLRenderDevice::BlitToScreen() {
		gl::State::bindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		gl::Viewport(0, 0, m_outputTexture->width(), m_outputTexture->height());

		m_blitShader->use();
		m_outputTexture->bind(0);
		m_blitShader->setUniform<int>("screenTexture", 0);

		m_meshVAO->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

    void GLRenderDevice::Resize(uint32_t w, uint32_t h) {
        m_outputTexture->resize(w, h);

        m_mainFramebuffer->destroy();
        m_mainFramebuffer->create();
        m_mainFramebuffer->attachColor(0, *m_outputTexture);

        gl::Renderbuffer depthBuffer;
        depthBuffer.create();
        depthBuffer.storage(GL_DEPTH_COMPONENT24, w, h);
        m_mainFramebuffer->attachDepth(depthBuffer);
    }

    void* GLRenderDevice::GetNativeTextureHandle() {
        return (void*)(uintptr_t)m_outputTexture->get();
    }
        
} // namespace ballistic
