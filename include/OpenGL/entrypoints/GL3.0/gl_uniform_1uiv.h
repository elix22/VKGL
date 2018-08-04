#ifndef VKGL_GL_UNIFORM_1UIV_H
#define VKGL_GL_UNIFORM_1UIV_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glUniform1uiv(GLint         location,
                                          GLsizei       count,
                                          const GLuint* value);

#endif /* VKGL_GL_UNIFORM_1UIV_H */