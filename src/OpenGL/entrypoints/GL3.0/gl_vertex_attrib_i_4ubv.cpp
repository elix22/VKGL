/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLuint&    in_index,
                     const GLubyte*   in_v_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglVertexAttribI4ubv(GLuint         index,
                                                 const GLubyte* v)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    /* TODO: Make me more useful */
    VKGL_TRACE("glVertexAttribI4ubv(index=[%u] v=[%p])",
               index,
               v);

    dispatch_table_ptr->pGLVertexAttribI4ubv(dispatch_table_ptr->bound_context_ptr,
                                             index,
                                             v);
}

static void vkglVertexAttribI4ubv_execute(OpenGL::Context* in_context_ptr,
                                          const GLuint&  in_index,
                                          const GLubyte* in_v_ptr)
{
    in_context_ptr->set_vertex_attribute(in_index,
                                         OpenGL::GetSetArgumentType::Unsigned_Byte,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         4,     /* in_n_components */
                                         false, /* in_normalized   */
                                         in_v_ptr);
}

void OpenGL::vkglVertexAttribI4ubv_with_validation(OpenGL::Context* in_context_ptr,
                                                   const GLuint&    in_index,
                                                   const GLubyte*   in_v_ptr)
{
    if (validate(in_context_ptr,
                 in_index,
                 in_v_ptr) )
    {
        vkglVertexAttribI4ubv_execute(in_context_ptr,
                                      in_index,
                                      in_v_ptr);
    }
}
