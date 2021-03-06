/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context*   in_context_ptr,
                     const GLenum&      in_mode,
                     const GLsizei*     in_count_ptr,
                     const GLenum&      in_type,
                     const void* const* in_indices_ptr,
                     const GLsizei&     in_drawcount,
                     const GLint*       in_basevertex_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}


void VKGL_APIENTRY OpenGL::vkglMultiDrawElementsBaseVertex(GLenum             mode,
                                                           const GLsizei*     count,
                                                           GLenum             type,
                                                           const void* const* indices,
                                                           GLsizei            drawcount,
                                                           const GLint*       basevertex)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glMultiDrawElementsBaseVertex(mode={%s] count=[%p] type=[%s] indices=[%p] drawcount=[%d] basevertex=[%p])",
               OpenGL::Utils::get_raw_string_for_gl_enum(mode),
               count,
               OpenGL::Utils::get_raw_string_for_gl_enum(type),
               indices,
               static_cast<int32_t>(drawcount),
               basevertex);

    dispatch_table_ptr->pGLMultiDrawElementsBaseVertex(dispatch_table_ptr->bound_context_ptr,
                                                       mode,
                                                       count,
                                                       type,
                                                       indices,
                                                       drawcount,
                                                       basevertex);
}

static void vkglMultiDrawElementsBaseVertex_execute(OpenGL::Context*   in_context_ptr,
                                                    const GLenum&      in_mode,
                                                    const GLsizei*     in_count_ptr,
                                                    const GLenum&      in_type,
                                                    const void* const* in_indices_ptr,
                                                    const GLsizei&     in_drawcount,
                                                    const GLint*       in_basevertex_ptr)
{
    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (in_mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(in_type);

    in_context_ptr->multi_draw_elements_base_vertex(mode_vkgl,
                                                    in_count_ptr,
                                                    type_vkgl,
                                                    in_indices_ptr,
                                                    in_drawcount,
                                                    in_basevertex_ptr);
}

void OpenGL::vkglMultiDrawElementsBaseVertex_with_validation(OpenGL::Context*   in_context_ptr,
                                                             const GLenum&      in_mode,
                                                             const GLsizei*     in_count_ptr,
                                                             const GLenum&      in_type,
                                                             const void* const* in_indices_ptr,
                                                             const GLsizei&     in_drawcount,
                                                             const GLint*       in_basevertex_ptr)
{
    if (validate(in_context_ptr,
                 in_mode,
                 in_count_ptr,
                 in_type,
                 in_indices_ptr,
                 in_drawcount,
                 in_basevertex_ptr) )
    {
        vkglMultiDrawElementsBaseVertex_execute(in_context_ptr,
                                                in_mode,
                                                in_count_ptr,
                                                in_type,
                                                in_indices_ptr,
                                                in_drawcount,
                                                in_basevertex_ptr);
    }
}
