#pragma once
#include <glad/glad.h>
#include "State.h"
#include <utility>
#include <vector>

namespace gl {

    class VertexArray {
    public:
        VertexArray() = default;
        ~VertexArray() { destroy(); }

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept { *this = std::move(other); }
        VertexArray& operator=(VertexArray&& other) noexcept {
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
                glCreateVertexArrays(1, &m_id);
            else
                glGenVertexArrays(1, &m_id);
        }

        void destroy() {
            if (!m_id) return;
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }

        bool valid() const { return m_id != 0 && glIsVertexArray(m_id); }
        GLuint get() const { return m_id; }

        void bind() const { State::bindVertexArray(m_id); }
        void unbind() const { State::bindVertexArray(0); }

        void vertexBuffer(GLuint bindingIndex, GLuint buffer, GLintptr offset = 0, GLsizei stride = 0) {
            if (GLAD_GL_VERSION_4_5)
                glVertexArrayVertexBuffer(m_id, bindingIndex, buffer, offset, stride);
            else {
                bind();
                glBindVertexBuffer(bindingIndex, buffer, offset, stride);
            }
        }

        void indexBuffer(GLuint buffer) {
            if (GLAD_GL_VERSION_4_5)
                glVertexArrayElementBuffer(m_id, buffer);
            else {
                bind();
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            }
        }

        void vertexAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLuint bindingIndex, GLuint relativeOffset = 0) {
            if (GLAD_GL_VERSION_4_5) {
                glEnableVertexArrayAttrib(m_id, index);
                glVertexArrayAttribFormat(m_id, index, size, type, normalized, relativeOffset);
                glVertexArrayAttribBinding(m_id, index, bindingIndex);
            } else {
                bind();
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index, size, type, normalized, 0, (void*)(uintptr_t)relativeOffset);
            }
        }

        void enableAttrib(GLuint index) {
            if (GLAD_GL_VERSION_4_5)
                glEnableVertexArrayAttrib(m_id, index);
            else {
                bind();
                glEnableVertexAttribArray(index);
            }
        }

        void disableAttrib(GLuint index) {
            if (GLAD_GL_VERSION_4_5)
                glDisableVertexArrayAttrib(m_id, index);
            else {
                bind();
                glDisableVertexAttribArray(index);
            }
        }

        void attribDivisor(GLuint index, GLuint divisor) {
            if (GLAD_GL_VERSION_4_5)
                glVertexArrayBindingDivisor(m_id, index, divisor);
            else {
                bind();
                glVertexBindingDivisor(index, divisor);
            }
        }

        void drawArrays(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount = 1) const {
            bind();
            if (instanceCount > 1)
                glDrawArraysInstanced(mode, first, count, instanceCount);
            else
                glDrawArrays(mode, first, count);
        }


        void drawElements(GLenum mode, GLsizei count, const void* indices = nullptr, GLsizei instanceCount = 1) const {
            bind();
            if (instanceCount > 1)
                glDrawElementsInstanced(mode, count, m_indexType, indices, instanceCount);
            else
                glDrawElements(mode, count, m_indexType, indices);
        }

        void label(const char* name) {
            if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
                glObjectLabel(GL_VERTEX_ARRAY, m_id, -1, name);
        }

    private:
        GLuint m_id{0};
        GLenum m_indexType{GL_UNSIGNED_INT};
    };

}