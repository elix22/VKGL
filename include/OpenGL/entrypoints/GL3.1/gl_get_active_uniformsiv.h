#ifndef VKGL_GL_GET_ACTIVE_UNIFORMSIV_H
#define VKGL_GL_GET_ACTIVE_UNIFORMSIV_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glGetActiveUniformsiv(GLuint        program,
                                                  GLsizei       uniformCount,
                                                  const GLuint* uniformIndices,
                                                  GLenum        pname,
                                                  GLint*        params);

#endif /* VKGL_GL_GET_ACTIVE_UNIFORMSIV_H */