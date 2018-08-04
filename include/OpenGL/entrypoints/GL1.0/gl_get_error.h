/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_GET_ERROR_H
#define VKGL_GL_GET_ERROR_H

#include "OpenGL/types.h"

VKGL_API GLenum VKGL_APIENTRY glGetError(void);

GLenum vkglGetError_with_validadtion(VKGL::Context* in_context_ptr);

#endif /* VKGL_GL_GET_ERROR_H */