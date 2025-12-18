#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <utility>

namespace gl {

    struct pair_hash {
        size_t operator()(const std::pair<GLenum, GLuint>& p) const noexcept {
            return std::hash<GLenum>{}(p.first) ^ (std::hash<GLuint>{}(p.second) << 1);
        }
    };

    class State {
    public:
        static void bindBuffer(GLenum target, GLuint id) {
            if (boundBuffers[target] != id) {
                glBindBuffer(target, id);
                boundBuffers[target] = id;
            }
        }

        static void bindBufferBase(GLenum target, GLuint index, GLuint id) {
            auto key = std::make_pair(target, index);
            if (boundBases[key] != id) {
                glBindBufferBase(target, index, id);
                boundBases[key] = id;
            }
        }

        static void bindBufferRange(GLenum target, GLuint index, GLuint id, GLintptr offset, GLsizeiptr size) {
            auto key = std::make_pair(target, index);
            if (boundBases[key] != id) {
                glBindBufferRange(target, index, id, offset, size);
                boundBases[key] = id;
            }
        }
        
        static void bindVertexArray(GLuint id) {
            if (boundVertexArray != id) {
                glBindVertexArray(id);
                boundVertexArray = id;
            }
        }

        static void bindShader(GLuint id) {
            if (boundShader != id) {
                glUseProgram(id);
                boundShader = id;
            }
        }

        static void bindTexture(GLuint unit, GLenum target, GLuint id) {
            activeTexture(unit);

            if (GLAD_GL_VERSION_4_5 || GLAD_GL_ARB_direct_state_access) {
                if (boundTextureUnits[unit] != id) {
                    glBindTextureUnit(unit, id);
                    boundTextureUnits[unit] = id;
                }
            } else {
                auto key = std::make_pair(target, unit);
                if (boundTextures[key] != id) {
                    glBindTexture(target, id);
                    boundTextures[key] = id;
                }
            }
        }

        static void activeTexture(GLuint unit) {
            if (activeTexUnit != unit) {
                glActiveTexture(GL_TEXTURE0 + unit);
                activeTexUnit = unit;
            }
        }

        static void bindRenderbuffer(GLuint id) {
            if (boundRenderbuffer != id) {
                glBindRenderbuffer(GL_RENDERBUFFER, id);
                boundRenderbuffer = id;
            }
        }

        static void bindFramebuffer(GLuint id, GLenum target = GL_FRAMEBUFFER) {
            GLuint* slot = nullptr;

            switch (target) {
                case GL_FRAMEBUFFER:
                    slot = &boundFramebuffer;
                    break;
                case GL_DRAW_FRAMEBUFFER:
                    slot = &boundDrawFramebuffer;
                    break;
                case GL_READ_FRAMEBUFFER:
                    slot = &boundReadFramebuffer;
                    break;
                default:
                    glBindFramebuffer(target, id);
                    return;
            }

            if (*slot != id) {
                glBindFramebuffer(target, id);
                *slot = id;
            }
        }

        static void reset() {
            boundBuffers.clear();
            boundBases.clear();
            boundTextures.clear();
            boundTextureUnits.clear();

            boundVertexArray = 0;
            boundShader = 0;
            boundRenderbuffer = 0;

            boundFramebuffer = 0;
            boundDrawFramebuffer = 0;
            boundReadFramebuffer = 0;

            activeTexUnit = 0;
        }
    
    private:
        static inline std::unordered_map<GLenum, GLuint> boundBuffers;
        static inline std::unordered_map<std::pair<GLenum, GLuint>, GLuint, pair_hash> boundBases;

        static inline GLuint boundVertexArray = 0;
        static inline GLuint boundShader = 0;
        static inline GLuint boundRenderbuffer = 0;

        static inline GLuint boundFramebuffer = 0;
        static inline GLuint boundDrawFramebuffer = 0;
        static inline GLuint boundReadFramebuffer = 0;

        static inline GLuint activeTexUnit = 0;
        static inline std::unordered_map<std::pair<GLenum, GLuint>, GLuint, pair_hash> boundTextures;
        static inline std::unordered_map<GLuint, GLuint> boundTextureUnits;
    };
}