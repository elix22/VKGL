#ifndef VKGL_GL_UNIFORM_MATRIX_4X2_FV_H
#define VKGL_GL_UNIFORM_MATRIX_4X2_FV_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glUniformMatrix4x2fv(GLint          location,
                                                 GLsizei        count,
                                                 GLboolean      transpose,
                                                 const GLfloat* value);

#endif /* VKGL_GL_UNIFORM_MATRIX_4X2_FV_H */