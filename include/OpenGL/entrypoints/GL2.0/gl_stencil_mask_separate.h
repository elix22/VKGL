/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_STENCIL_MASK_SEPARATE_H
#define VKGL_GL_STENCIL_MASK_SEPARATE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglStencilMaskSeparate(GLenum face,
                                               GLuint mask);

    void vkglStencilMaskSeparate_with_validation(OpenGL::Context* in_context_ptr,
                                                 const GLenum&    in_face,
                                                 const GLuint&    in_mask);
}

#endif /* VKGL_GL_STENCIL_MASK_SEPARATE_H */