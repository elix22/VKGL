/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLenum&    in_target,
                     const GLenum&    in_access)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void *APIENTRY OpenGL::vkglMapBuffer(GLenum target,
                                     GLenum access)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glMapBuffer(target=[%s] access=[%s])",
               OpenGL::Utils::get_raw_string_for_gl_enum(target),
               OpenGL::Utils::get_raw_string_for_gl_enum(access) );

    return dispatch_table_ptr->pGLMapBuffer(dispatch_table_ptr->bound_context_ptr,
                                            target,
                                            access);
}

static void* vkglMapBuffer_execute(OpenGL::Context* in_context_ptr,
                                   const GLenum&    in_target,
                                   const GLenum&    in_access)
{
    const auto access_vkgl = OpenGL::Utils::get_buffer_access_for_gl_enum(in_access);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(in_target);

    return in_context_ptr->map_buffer(target_vkgl,
                                      access_vkgl);
}

void* OpenGL::vkglMapBuffer_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLenum&    in_target,
                                            const GLenum&    in_access)
{
    void* result_ptr = nullptr;

    if (validate(in_context_ptr,
                 in_target,
                 in_access) )
    {
        result_ptr = vkglMapBuffer_execute(in_context_ptr,
                                           in_target,
                                           in_access);
    }

    return result_ptr;
}
