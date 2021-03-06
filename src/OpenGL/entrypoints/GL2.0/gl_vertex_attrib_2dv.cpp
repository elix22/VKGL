/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2dv.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLuint&    in_index,
                     const GLdouble*  in_v_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglVertexAttrib2dv(GLuint          index,
                                               const GLdouble* v)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    /* TODO: Make me more useful */
    VKGL_TRACE("glVertexAttriv2dv(index=[%u] v=[%p])",
               index,
               v);

    dispatch_table_ptr->pGLVertexAttrib2dv(dispatch_table_ptr->bound_context_ptr,
                                           index,
                                           v);
}

static void vkglVertexAttrib2dv_execute(OpenGL::Context* in_context_ptr,
                                        const GLuint&    in_index,
                                        const GLdouble*  in_v_ptr)
{
    in_context_ptr->set_vertex_attribute(in_index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /* in_n_components */
                                         false, /* in_normalized   */
                                         in_v_ptr);
}

void OpenGL::vkglVertexAttrib2dv_with_validation(OpenGL::Context* in_context_ptr,
                                                 const GLuint&    in_index,
                                                 const GLdouble*  in_v_ptr)
{
    if (validate(in_context_ptr,
                 in_index,
                 in_v_ptr) )
    {
        vkglVertexAttrib2dv_execute(in_context_ptr,
                                    in_index,
                                    in_v_ptr);
    }
}
