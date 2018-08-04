#ifndef VKGL_GL_CLEAR_BUFFER_UIV_H
#define VKGL_GL_CLEAR_BUFFER_UIV_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glClearBufferuiv(GLenum        buffer,
                                             GLint         drawbuffer,
                                             const GLuint* value);

#endif /* VKGL_GL_CLEAR_BUFFER_UIV_H */