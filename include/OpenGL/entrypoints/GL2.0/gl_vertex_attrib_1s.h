/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_VERTEX_ATTRIB_1S_H
#define VKGL_GL_VERTEX_ATTRIB_1S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglVertexAttrib1s(GLuint  index,
                                          GLshort x);

    void vkglVertexAttrib1s_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLuint&    in_index,
                                            const GLshort&   in_x);
}

#endif /* VKGL_GL_VERTEX_ATTRIB_1S_H */