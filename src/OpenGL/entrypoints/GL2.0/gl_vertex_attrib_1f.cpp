/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1f.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLuint&    in_index,
                     const GLfloat&   in_x)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglVertexAttrib1f(GLuint  index,
                                              GLfloat x)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glVertexAttrib1f(index=[%u] x=[%.4f])",
               index,
               x);

    dispatch_table_ptr->pGLVertexAttrib1f(dispatch_table_ptr->bound_context_ptr,
                                          index,
                                          x);
}

static void vkglVertexAttrib1f_execute(OpenGL::Context* in_context_ptr,
                                       const GLuint&    in_index,
                                       const GLfloat&   in_x)
{
    in_context_ptr->set_vertex_attribute(in_index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /* in_n_components */
                                         false, /* in_normalized   */
                                        &in_x);
}

void OpenGL::vkglVertexAttrib1f_with_validation(OpenGL::Context* in_context_ptr,
                                                const GLuint&    in_index,
                                                const GLfloat&   in_x)
{
    if (validate(in_context_ptr,
                 in_index,
                 in_x) )
    {
        vkglVertexAttrib1f_execute(in_context_ptr,
                                   in_index,
                                   in_x);
    }
}
