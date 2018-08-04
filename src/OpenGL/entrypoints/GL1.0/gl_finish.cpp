/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

VKGL_API void VKGL_APIENTRY glFinish(void)
{
    const auto dispatch_table_ptr = g_dispatch_table_ptr;

    dispatch_table_ptr->pGLFinish(dispatch_table_ptr->bound_context_ptr);
}

void vkglFinish_with_validation(VKGL::Context* in_context_ptr)
{
    in_context_ptr->finish();
}