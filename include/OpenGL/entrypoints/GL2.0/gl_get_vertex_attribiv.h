#ifndef VKGL_GL_GET_VERTEX_ATTRIBIV_H
#define VKGL_GL_GET_VERTEX_ATTRIBIV_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glGetVertexAttribiv(GLuint index,
                                                GLenum pname,
                                                GLint* params);

#endif /* VKGL_GL_GET_VERTEX_ATTRIBIV_H */