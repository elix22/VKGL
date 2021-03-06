/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_CHOOSE_PIXEL_FORMAT_H
#define VKGL_CHOOSE_PIXEL_FORMAT_H

#include <windows.h>

namespace GDI32
{
    int WINAPI choose_pixel_format(HDC                          in_hdc,
                                   CONST PIXELFORMATDESCRIPTOR* in_pixel_format_descriptor_ptr);
}

#endif /* VKGL_CHOOSE_PIXEL_FORMAT_H */