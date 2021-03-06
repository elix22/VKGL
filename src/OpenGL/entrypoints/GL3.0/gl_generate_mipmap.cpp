/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLenum&    in_target)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglGenerateMipmap(GLenum target)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glGenerateMipmap(target=[%s])",
               OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    dispatch_table_ptr->pGLGenerateMipmap(dispatch_table_ptr->bound_context_ptr,
                                          target);
}

static void vkglGenerateMipmap_execute(OpenGL::Context* in_context_ptr,
                                       const GLenum&    in_target)
{
    const auto target_vkgl = OpenGL::Utils::get_mipmap_generation_texture_target_for_gl_enum(in_target);

    in_context_ptr->generate_mipmap(target_vkgl);
}

void OpenGL::vkglGenerateMipmap_with_validation(OpenGL::Context* in_context_ptr,
                                                const GLenum&    in_target)
{
    if (validate(in_context_ptr,
                 in_target) )
    {
        vkglGenerateMipmap_execute(in_context_ptr,
                                   in_target);
    }
}
