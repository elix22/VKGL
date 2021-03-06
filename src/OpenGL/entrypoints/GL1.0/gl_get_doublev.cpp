/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_doublev.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLenum&    in_pname,
                     GLdouble*        out_data_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

static void vkglGetDoublev_execute(OpenGL::Context* in_context_ptr,
                                   const GLenum&    in_pname,
                                   GLdouble*        out_data_ptr)
{
    const auto pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(in_pname);

    in_context_ptr->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Double,
                                  out_data_ptr);
}

void OpenGL::vkglGetDoublev_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLenum&    in_pname,
                                            GLdouble*        out_data_ptr)
{
    if (validate(in_context_ptr,
                 in_pname,
                 out_data_ptr) )
    {
        vkglGetDoublev_execute(in_context_ptr,
                               in_pname,
                               out_data_ptr);
    }
}

void VKGL_APIENTRY OpenGL::vkglGetDoublev(GLenum    pname,
                                          GLdouble* data)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glGetDoublev(pname=[%s] data=[%p])",
               OpenGL::Utils::get_raw_string_for_gl_enum(pname),
               data);

    dispatch_table_ptr->pGLGetDoublev(dispatch_table_ptr->bound_context_ptr,
                                      pname,
                                      data);
}