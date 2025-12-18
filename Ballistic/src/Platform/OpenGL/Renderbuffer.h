#pragma once
#include <glad/glad.h>
#include "State.h"
#include <utility>
#include <vector>

namespace gl {

    class Renderbuffer {
    public:
        Renderbuffer() = default;
        ~Renderbuffer() { destroy(); }

        Renderbuffer(const Renderbuffer&) = delete;
        Renderbuffer& operator=(const Renderbuffer&) = delete;

        Renderbuffer(Renderbuffer&& other) noexcept { *this = std::move(other); }
        Renderbuffer& operator=(Renderbuffer&& other) noexcept {
            if (this != &other) {
                destroy();
                m_id = other.m_id;
                m_width = other.m_width;
                m_height = other.m_height;
                m_samples = other.m_samples;
                m_internalFormat = other.m_internalFormat;
                other.m_id = 0;
                other.m_width = 0;
                other.m_height = 0;
                other.m_samples = 0;
                other.m_internalFormat = 0;
            }
            return *this;
        }

        void create() {
            if (m_id) return;
            if (GLAD_GL_VERSION_4_5)
                glCreateRenderbuffers(1, &m_id);
            else
                glGenRenderbuffers(1, &m_id);
        }

        void destroy() {
            if (!m_id) return;
            glDeleteRenderbuffers(1, &m_id);
            m_id = 0;
            m_width = 0;
            m_height = 0;
            m_samples = 0;
            m_internalFormat = 0;
        }

        bool valid() const { return m_id != 0 && glIsRenderbuffer(m_id); }
        GLuint get() const { return m_id; }

        void bind() const { State::bindRenderbuffer(m_id); }
        void unbind() const { State::bindRenderbuffer(0); }

        void storage(GLenum internalFormat, GLsizei width, GLsizei height) {
            m_internalFormat = internalFormat;
            m_width = width;
            m_height = height;
            m_samples = 0;

            if (GLAD_GL_VERSION_4_5)
                glNamedRenderbufferStorage(m_id, internalFormat, width, height);
            else {
                bind();
                glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
            }
        }

        void storageMultisample(GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height) {
            m_internalFormat = internalFormat;
            m_width = width;
            m_height = height;
            m_samples = samples;

            if (GLAD_GL_VERSION_4_5)
                glNamedRenderbufferStorageMultisample(m_id, samples, internalFormat, width, height);
            else {
                bind();
                glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height);
            }
        }

        void attachToFramebuffer(GLenum target, GLenum attachment) const {
            glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, m_id);
        }

        void resize(GLsizei width, GLsizei height) {
            if (!m_id) return;

            if (m_samples > 0)
                storageMultisample(m_samples, m_internalFormat, width, height);
            else
                storage(m_internalFormat, width, height);
        }

        void label(const char* name) {
            if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
                glObjectLabel(GL_RENDERBUFFER, m_id, -1, name);
        }

        GLsizei width() const { return m_width; }
        GLsizei height() const { return m_height; }
        GLsizei samples() const { return m_samples; }
        GLenum internalFormat() const { return m_internalFormat; }

    private:
        GLuint m_id = 0;
        GLsizei m_width = 0;
        GLsizei m_height = 0;
        GLsizei m_samples = 0;
        GLenum m_internalFormat = 0;
    };

}