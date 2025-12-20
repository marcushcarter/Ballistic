#pragma once
#include <glad/glad.h>
#include "State.h"
#include "Renderbuffer.h"
#include "Texture2D.h"
#include <vector>

namespace gl {

    class Framebuffer {
    public:
        Framebuffer() = default;
        ~Framebuffer() { destroy(); }

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        Framebuffer(Framebuffer&& other) noexcept { *this = std::move(other); }
        Framebuffer& operator=(Framebuffer&& other) noexcept {
            if (this != &other) {
                destroy();
                m_id = other.m_id;
                other.m_id = 0;
            }
            return *this;
        }

        void create() {
            if (m_id) return;
            if (GLAD_GL_VERSION_4_5)
                glCreateFramebuffers(1, &m_id);
            else
                glGenFramebuffers(1, &m_id);
        }

        void destroy() {
            if (!m_id) return;
            glDeleteFramebuffers(1, &m_id);
            m_id = 0;
            m_colorAttachments.clear();
            m_depthRBO = nullptr;
            m_depthTexture = nullptr;
        }

        bool valid() const { return m_id != 0 && glIsFramebuffer(m_id); }
        bool complete() const { bind(); return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE; }
        GLuint get() const { return m_id; }

        void bind(GLenum target = GL_FRAMEBUFFER) const { State::bindFramebuffer(m_id, target); }
        void unbind(GLenum target = GL_FRAMEBUFFER) const { State::bindFramebuffer(0, target); }

        void attachColor(GLuint slot, Texture2D& texture) {
            create();
            m_colorAttachments.resize(std::max<size_t>(slot + 1, m_colorAttachments.size()));
            m_colorAttachments[slot] = &texture;
            if (GLAD_GL_VERSION_4_5)
                glNamedFramebufferTexture(m_id, GL_COLOR_ATTACHMENT0 + slot, texture.get(), 0);
            else {
                bind();
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, texture.get(), 0);
            }
        }

        void attachDepth(Renderbuffer& rbo) {
            m_depthRBO = &rbo;
            m_depthTexture = nullptr;
            rbo.attachToFramebuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);
        }

        void attachDepth(Texture2D& texture) {
            m_depthTexture = &texture;
            m_depthRBO = nullptr;
            if (GLAD_GL_VERSION_4_5)
                glNamedFramebufferTexture(m_id, GL_DEPTH_ATTACHMENT, texture.get(), 0);
            else {
                bind();
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.get(), 0);
            }
        }

        void label(const char* name) {
            if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
                glObjectLabel(GL_FRAMEBUFFER, m_id, -1, name);
        }

        Texture2D* getColorAttachment(GLuint slot) const {
            if (slot >= m_colorAttachments.size()) return nullptr;
            return m_colorAttachments[slot];
        }
        
    private:
        GLuint m_id = 0;
        std::vector<Texture2D*> m_colorAttachments;
        Texture2D* m_depthTexture = nullptr;
        Renderbuffer* m_depthRBO = nullptr;
    };

}
