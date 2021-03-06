/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_clear_depth.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLdouble&  in_depth)
{
    bool result = false;

    // ..

    result = true;
    return result;
}


void VKGL_APIENTRY OpenGL::vkglClearDepth(GLdouble depth)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glClearDepth(depth=[%.4f])",
               static_cast<float>(depth) );

    dispatch_table_ptr->pGLClearDepth(dispatch_table_ptr->bound_context_ptr,
                                      depth);
}

static void vkglClearDepth_execute(OpenGL::Context* in_context_ptr,
                                   const GLdouble&  in_depth)
{
    in_context_ptr->set_clear_depth_value(in_depth);
}

void OpenGL::vkglClearDepth_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLdouble&  in_depth)
{
    if (validate(in_context_ptr,
                 in_depth) )
    {
        vkglClearDepth_execute(in_context_ptr,
                               in_depth);
    }
}