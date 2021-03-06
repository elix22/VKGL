/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context*  in_context_ptr,
                     const GLsync&     in_sync,
                     const GLbitfield& in_flags,
                     const GLuint64&   in_timeout)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

GLenum VKGL_APIENTRY OpenGL::vkglClientWaitSync(GLsync     sync,
                                                GLbitfield flags,
                                                GLuint64   timeout)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    VKGL_TRACE("glClientWaitSync(sync=[%p] flags=[%s] timeout=[%d])",
               sync,
               OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Wait_Sync_Mask, flags),
               static_cast<uint32_t>(timeout) );

    return dispatch_table_ptr->pGLClientWaitSync(dispatch_table_ptr->bound_context_ptr,
                                                 sync,
                                                 flags,
                                                 timeout);
}

static GLenum vkglClientWaitSync_execute(OpenGL::Context*  in_context_ptr,
                                         const GLsync&     in_sync,
                                         const GLbitfield& in_flags,
                                         const GLuint64&   in_timeout)
{
    const auto flags_vkgl = OpenGL::Utils::get_wait_sync_bits_for_gl_enum(in_flags);
    const auto result     = in_context_ptr->client_wait_sync             (in_sync,
                                                                          flags_vkgl,
                                                                          in_timeout);

    return OpenGL::Utils::get_gl_enum_for_wait_result(result);
}

GLenum OpenGL::vkglClientWaitSync_with_validation(OpenGL::Context*  in_context_ptr,
                                                  const GLsync&     in_sync,
                                                  const GLbitfield& in_flags,
                                                  const GLuint64&   in_timeout)
{
    GLenum result = UINT32_MAX;

    if (validate(in_context_ptr,
                 in_sync,
                 in_flags,
                 in_timeout) )
    {
        result = vkglClientWaitSync_execute(in_context_ptr,
                                            in_sync,
                                            in_flags,
                                            in_timeout);
    }

    return result;
}
