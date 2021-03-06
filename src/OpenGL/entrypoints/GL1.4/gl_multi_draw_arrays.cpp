/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLenum&    in_mode,
                     const GLint*     in_first_ptr,
                     const GLsizei*   in_count_ptr,
                     const GLsizei&   in_drawcount)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglMultiDrawArrays(GLenum         mode,
                                               const GLint*   first,
                                               const GLsizei* count,
                                               GLsizei        drawcount)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glMultiDrawArrays(mode=[%s] first=[%p] count=[%p] drawcount=[%d])",
               OpenGL::Utils::get_raw_string_for_gl_enum(mode),
               first,
               count,
               static_cast<int32_t>(drawcount) );

    dispatch_table_ptr->pGLMultiDrawArrays(dispatch_table_ptr->bound_context_ptr,
                                           mode,
                                           first,
                                           count,
                                           drawcount);
}

static void vkglMultiDrawArrays_execute(OpenGL::Context* in_context_ptr,
                                        const GLenum&    in_mode,
                                        const GLint*     in_first_ptr,
                                        const GLsizei*   in_count_ptr,
                                        const GLsizei&   in_drawcount)
{
    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum(in_mode);

    in_context_ptr->multi_draw_arrays(mode_vkgl,
                                      in_first_ptr,
                                      in_count_ptr,
                                      in_drawcount);
}

void OpenGL::vkglMultiDrawArrays_with_validation(OpenGL::Context* in_context_ptr,
                                                 const GLenum&    in_mode,
                                                 const GLint*     in_first_ptr,
                                                 const GLsizei*   in_count_ptr,
                                                 const GLsizei&   in_drawcount)
{
    if (validate(in_context_ptr,
                 in_mode,
                 in_first_ptr,
                 in_count_ptr,
                 in_drawcount) )
    {
        vkglMultiDrawArrays_execute(in_context_ptr,
                                    in_mode,
                                    in_first_ptr,
                                    in_count_ptr,
                                    in_drawcount);
    }
}
