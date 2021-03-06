/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_GEN_FRAMEBUFFERS_H
#define VKGL_GL_GEN_FRAMEBUFFERS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglGenFramebuffers(GLsizei n,
                                           GLuint* framebuffers);

    void vkglGenFramebuffers_with_validation(OpenGL::Context* in_context_ptr,
                                             const GLsizei&   in_n,
                                             GLuint*          out_framebuffers_ptr);
}

#endif /* VKGL_GL_GEN_FRAMEBUFFERS_H */