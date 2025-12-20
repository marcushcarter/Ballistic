#pragma once
#include <glad/glad.h>
#include "State.h"
#include <utility>

namespace gl {

    class Buffer {
    public:
        Buffer() = default;
        ~Buffer() { destroy(); }

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;

        Buffer(Buffer&& other) noexcept { *this = std::move(other); }
        Buffer& operator=(Buffer&& other) noexcept {
            if (this != &other) {
                destroy();
                m_id = other.m_id;
                m_size = other.m_size;
                m_target = other.m_target;
                other.m_id = 0;
                other.m_size = 0;
                other.m_target = 0;
            }
            return *this;
        }

        void create(GLenum target) {
            if (m_id) return;
            m_target = target;
            if (GLAD_GL_VERSION_4_5)
                glCreateBuffers(1, &m_id);
            else
                glGenBuffers(1, &m_id);
        }

        void destroy() {
            if (!m_id) return;
            glDeleteBuffers(1, &m_id);
            m_id = 0;
            m_size = 0;
            m_target = 0;
        }

        bool valid() const { return m_id != 0 && glIsBuffer(m_id); }
        GLuint get() const { return m_id; }

        void bind() const { State::bindBuffer(m_target, m_id); }
        void unbind() const { State::bindBuffer(m_target, 0); }

        void bindBase(GLenum target, GLuint index) const { glBindBufferBase(target, index, m_id); }
        void bindRange(GLenum target, GLuint index, GLintptr offset, GLsizeiptr size) const { glBindBufferRange(target, index, m_id, offset, size); }

        void data(GLsizeiptr size, const void* data, GLenum usage) {
            m_size = size;
            if (GLAD_GL_VERSION_4_5)
                glNamedBufferData(m_id, size, data, usage);
            else {
                bind();
                glBufferData(m_target, size, data, usage);
            }
        }

        void update(GLintptr offset, GLsizeiptr size, const void* data) {
            if (GLAD_GL_VERSION_4_5)
                glNamedBufferSubData(m_id, offset, size, data);
            else {
                bind();
                glBufferSubData(m_target, offset, size, data);
            }
        }

        void storage(GLsizeiptr size, const void* data, GLbitfield flags) {
            if (GLAD_GL_VERSION_4_5)
                glNamedBufferStorage(m_id, size, data, flags);
            else {
                bind();
                glBufferStorage(m_target, size, data, flags);
            }
        }

        void clear(GLenum internalFormat, GLenum format, GLenum type, const void* data) {
            if (GLAD_GL_VERSION_4_5)
                glClearNamedBufferData(m_id, internalFormat, format, type, data);
            else {
                bind();
                glClearBufferData(m_target, internalFormat, format, type, data);
            }
        }

        void clearRange(GLenum internalFormat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data) {
            if (GLAD_GL_VERSION_4_5)
                glClearNamedBufferSubData(m_id, internalFormat, offset, size, format, type, data);
            else {
                bind();
                glClearBufferSubData(m_target, internalFormat, offset, size, format, type, data);
            }
        }
        
        void copy(const Buffer& src, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
            if (GLAD_GL_VERSION_4_5)
                glCopyNamedBufferSubData(src.m_id, m_id, readOffset, writeOffset, size);
            else
                glCopyBufferSubData(src.m_target, m_target, readOffset, writeOffset, size);
        }

        void* map(GLenum access) {
            if (GLAD_GL_VERSION_4_5) 
                return glMapNamedBuffer(m_id, access);
            bind();
            return glMapBuffer(m_target, access);
        }

        void* mapRange(GLintptr offset, GLsizeiptr length, GLbitfield access) {
            if (GLAD_GL_VERSION_4_5)
                return glMapNamedBufferRange(m_id, offset, length, access);
            bind();
            return glMapBufferRange(m_target, offset, length, access);
        }

        template<typename T>
        T* mapTyped(GLenum access) { return static_cast<T*>(map(access)); }

        void flush(GLintptr offset, GLsizeiptr length) {
            if (GLAD_GL_VERSION_4_5)
                glFlushMappedNamedBufferRange(m_id, offset, length);
            else {
                bind();
                glFlushMappedBufferRange(m_target, offset, length);
            }
        }

        void unmap() {
            if (GLAD_GL_VERSION_4_5)
                glUnmapNamedBuffer(m_id);
            else {
                bind();
                glUnmapBuffer(m_target);
            }
        }

        // void getParameter(GLenum pname, GLint* params) {
        //     if (GLAD_GL_VERSION_4_5)
        //         glGetNamedBufferParameteriv(m_id, pname, params);
        //     else {
        //         bind();
        //         glGetBufferParameteriv(m_target, pname, params);
        //     }
        // }

        // void getPointer(GLenum target, GLenum pname, void** params) {
        //     if (GLAD_GL_VERSION_4_5)
        //         glGetNamedBufferPointerv(m_id, pname, params);
        //     else {
        //         bind();
        //         glGetBufferPointerv(m_target, pname, params);
        //     }
        // }

        void label(const char* name) {
            if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
                glObjectLabel(GL_BUFFER, m_id, -1, name);
        }
        
        GLsizeiptr size() const { return m_size; }
        GLenum target() const { return m_target; }

    private:
        GLuint m_id{0};
        GLsizeiptr m_size{0};
        GLenum m_target{0};
    };

}