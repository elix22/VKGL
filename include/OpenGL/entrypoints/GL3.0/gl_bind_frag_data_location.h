#ifndef VKGL_GL_BIND_FRAG_DATA_LOCATION_H
#define VKGL_GL_BIND_FRAG_DATA_LOCATION_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glBindFragDataLocation(GLuint        program,
                                                   GLuint        color,
                                                   const GLchar* name);

#endif /* VKGL_GL_BIND_FRAG_DATA_LOCATION_H */