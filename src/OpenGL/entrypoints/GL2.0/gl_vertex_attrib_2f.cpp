/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2f.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLuint&    in_index,
                     const GLfloat&   in_x,
                     const GLfloat&   in_y)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglVertexAttrib2f(GLuint  index,
                                              GLfloat x,
                                              GLfloat y)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glVertexAttrib2f(index=[%u] x=[%.4f] y=[%.4f])",
               index,
               x,
               y);

    dispatch_table_ptr->pGLVertexAttrib2f(dispatch_table_ptr->bound_context_ptr,
                                          index,
                                          x,
                                          y);
}

static void vkglVertexAttrib2f_execute(OpenGL::Context* in_context_ptr,
                                       const GLuint&    in_index,
                                       const GLfloat&   in_x,
                                       const GLfloat&   in_y)
{
    const float data[] =
    {
        in_x,
        in_y
    };

    in_context_ptr->set_vertex_attribute(in_index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /* in_n_components */
                                         false, /* in_normalized   */
                                         data);
}

void OpenGL::vkglVertexAttrib2f_with_validation(OpenGL::Context* in_context_ptr,
                                                const GLuint&    in_index,
                                                const GLfloat&   in_x,
                                                const GLfloat&   in_y)
{
    if (validate(in_context_ptr,
                 in_index,
                 in_x,
                 in_y) )
    {
        vkglVertexAttrib2f_execute(in_context_ptr,
                                   in_index,
                                   in_x,
                                   in_y);
    }
}
