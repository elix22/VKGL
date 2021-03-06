/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_end_transform_feedback.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglEndTransformFeedback(void)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glEndTransformFeedback()");

    dispatch_table_ptr->pGLEndTransformFeedback(dispatch_table_ptr->bound_context_ptr);
}


static void vkglEndTransformFeedback_execute(OpenGL::Context* in_context_ptr)
{
    in_context_ptr->end_transform_feedback();
}

void OpenGL::vkglEndTransformFeedback_with_validation(OpenGL::Context* in_context_ptr)
{
    if (validate(in_context_ptr) )
    {
        vkglEndTransformFeedback_execute(in_context_ptr);
    }
}
