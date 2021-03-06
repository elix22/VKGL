/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_GET_VERTEX_ATTRIBFV_H
#define VKGL_GL_GET_VERTEX_ATTRIBFV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglGetVertexAttribfv(GLuint   index,
                                             GLenum   pname,
                                             GLfloat* params);

    void vkglGetVertexAttribfv_with_validation(OpenGL::Context* in_context_ptr,
                                               const GLuint&    in_index,
                                               const GLenum&    in_pname,
                                               GLfloat*         out_params_ptr);
}

#endif /* VKGL_GL_GET_VERTEX_ATTRIBFV_H */