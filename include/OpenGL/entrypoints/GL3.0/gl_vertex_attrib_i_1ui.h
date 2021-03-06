/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_VERTEX_ATTRIB_I_1UI_H
#define VKGL_GL_VERTEX_ATTRIB_I_1UI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglVertexAttribI1ui(GLuint index,
                                            GLuint x);

    void vkglVertexAttribI1ui_with_validation(OpenGL::Context* in_context_ptr,
                                              const GLuint&    in_index,
                                              const GLuint&    in_x);
}

#endif /* VKGL_GL_VERTEX_ATTRIB_I_1UI_H */