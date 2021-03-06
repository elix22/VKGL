/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_gen_queries.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLsizei&   in_n,
                     GLuint*          out_ids_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglGenQueries(GLsizei n,
                                          GLuint* ids)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glGenQueries(n=[%d] id=[%p])",
               static_cast<int32_t>(n),
               ids);

    dispatch_table_ptr->pGLGenQueries(dispatch_table_ptr->bound_context_ptr,
                                      n,
                                      ids);
}

static void vkglGenQueries_execute(OpenGL::Context* in_context_ptr,
                                   const GLsizei&   in_n,
                                   GLuint*          out_ids_ptr)
{
    in_context_ptr->gen_queries(in_n,
                                out_ids_ptr);
}

void OpenGL::vkglGenQueries_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLsizei&   in_n,
                                            GLuint*          out_ids_ptr)
{
    if (validate(in_context_ptr,
                 in_n,
                 out_ids_ptr) )
    {
        vkglGenQueries_execute(in_context_ptr,
                               in_n,
                               out_ids_ptr);
    }
}
