#pragma once
#include <glad/glad.h>
#include "State.h"

namespace gl {

    class Texture2D {
    public:
        Texture2D() = default;
        ~Texture2D() { destroy(); }

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&& other) noexcept { *this = std::move(other); }
        Texture2D& operator=(Texture2D&& other) noexcept {
            if (this != &other) {
                destroy();
                m_id = other.m_id;
                other.m_id = 0;
            }
            return *this;
        }

        void create(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLsizei levels = 1) {
            if (m_id) return;

            if (GLAD_GL_VERSION_4_5) {
                glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
                glTextureStorage2D(m_id, levels, internalFormat, width, height);
            } else {
                glGenTextures(1, &m_id);
                bind();
                glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, width, height);
            }

            m_width = width;
            m_height = height;
            m_internalFormat = internalFormat;
            m_format = format;
            m_type = type;
            m_levels = levels;
        }

        void destroy() {
            if (!m_id) return;
            glDeleteTextures(1, &m_id);
            m_id = 0;
        }
        
        bool valid() const { return m_id != 0 && glIsTexture(m_id); }
        GLuint get() const { return m_id; }

        void bind(GLuint unit = 0) const { State::bindTexture(unit, GL_TEXTURE_2D, m_id); }
        void unbind(GLuint unit = 0) const { State::bindTexture(unit, GL_TEXTURE_2D, 0); }
        void bindImage(GLuint unit, GLenum access = GL_READ_WRITE, GLint level = 0) const { glBindImageTexture(unit, m_id, level, GL_FALSE, 0, access, m_internalFormat); }

        void setData(const void* data) const {
            if (GLAD_GL_VERSION_4_5) {
                glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, m_type, data);
            } else {
                bind();
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_format, m_type, data);
            }
        }

        void getData(void* data) const {
            bind();
            glGetTexImage(GL_TEXTURE_2D, 0, m_format, m_type, data);
        }

        void generateMipmaps() const {
            if (GLAD_GL_VERSION_4_5) {
                glGenerateTextureMipmap(m_id);
            } else {
                bind();
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }

        void setParameters(GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT) const {
            if (GLAD_GL_VERSION_4_5) {
                glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, minFilter);
                glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, magFilter);
                glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapS);
                glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapT);
            } else {
                bind();
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
            }
        }

        void resize(GLsizei width, GLsizei height) {
            if (!m_id) return;

            if (width == m_width && height == m_height)
                return;

            m_width = width;
            m_height = height;

            if (GLAD_GL_VERSION_4_5) {
                glTextureStorage2D(m_id, m_levels, m_internalFormat, width, height);
            } else {
                bind();
                glTexStorage2D(GL_TEXTURE_2D, m_levels, m_internalFormat, width, height);
            }
        }

        void label(const char* name) {
            if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
                glObjectLabel(GL_TEXTURE, m_id, -1, name);
        }

        GLsizei width() const { return m_width; }
        GLsizei height() const { return m_height; }

    private:
        GLuint m_id{0};
        GLsizei m_width{0}, m_height{0};
        GLsizei m_levels{1};
        GLenum m_internalFormat{0}, m_format{0}, m_type{0}; 
    };

}