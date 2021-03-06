/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context*  in_context_ptr,
                     const GLenum&     in_read_target,
                     const GLenum&     in_write_target,
                     const GLintptr&   in_read_offset,
                     const GLintptr&   in_write_offset,
                     const GLsizeiptr& in_size)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglCopyBufferSubData(GLenum     readTarget,
                                                 GLenum     writeTarget,
                                                 GLintptr   readOffset,
                                                 GLintptr   writeOffset,
                                                 GLsizeiptr size)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glCopyBufferSubData(readTarget=[%s] writeTarget=[%s] readOffset=[%d] writeOffset=[%d] size=[%d])",
               OpenGL::Utils::get_raw_string_for_gl_enum(readTarget),
               OpenGL::Utils::get_raw_string_for_gl_enum(writeTarget),
               static_cast<int32_t>(readOffset),
               static_cast<int32_t>(writeOffset),
               static_cast<int32_t>(size) );

    dispatch_table_ptr->pGLCopyBufferSubData(dispatch_table_ptr->bound_context_ptr,
                                             readTarget,
                                             writeTarget,
                                             readOffset,
                                             writeOffset,
                                             size);
}

static void vkglCopyBufferSubData_execute(OpenGL::Context*  in_context_ptr,
                                          const GLenum&     in_read_target,
                                          const GLenum&     in_write_target,
                                          const GLintptr&   in_read_offset,
                                          const GLintptr&   in_write_offset,
                                          const GLsizeiptr& in_size)
{
    const auto read_target_vkgl  = OpenGL::Utils::get_buffer_target_for_gl_enum(in_read_target);
    const auto write_target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(in_write_target);

    in_context_ptr->copy_buffer_sub_data(read_target_vkgl,
                                         write_target_vkgl,
                                         in_read_offset,
                                         in_write_offset,
                                         in_size);
}

void OpenGL::vkglCopyBufferSubData_with_validation(OpenGL::Context*  in_context_ptr,
                                                   const GLenum&     in_read_target,
                                                   const GLenum&     in_write_target,
                                                   const GLintptr&   in_read_offset,
                                                   const GLintptr&   in_write_offset,
                                                   const GLsizeiptr& in_size)
{
    if (validate(in_context_ptr,
                 in_read_target,
                 in_write_target,
                 in_read_offset,
                 in_write_offset,
                 in_size) )
    {
        vkglCopyBufferSubData_execute(in_context_ptr,
                                      in_read_target,
                                      in_write_target,
                                      in_read_offset,
                                      in_write_offset,
                                      in_size);
    }
}
