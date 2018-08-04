/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_CLEAR_COLOR_H
#define VKGL_GL_CLEAR_COLOR_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glClearColor(GLfloat red,
                                         GLfloat green,
                                         GLfloat blue,
                                         GLfloat alpha);

void vkglClearColor_with_validation(VKGL::Context* in_context_ptr,
                                    const GLfloat& in_red,
                                    const GLfloat& in_green,
                                    const GLfloat& in_blue,
                                    const GLfloat& in_alpha);

#endif /* VKGL_GL_CLEAR_COLOR_H */