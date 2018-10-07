/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/frontend/gl_object_manager.h"
#include "OpenGL/frontend/gl_reference.h"
#include "OpenGL/types.h"

static const OpenGL::BufferTarget g_indexed_buffer_targets[] =
{
    OpenGL::BufferTarget::Transform_Feedback_Buffer,
    OpenGL::BufferTarget::Uniform_Buffer,
};

static const OpenGL::BufferTarget g_nonindexed_buffer_targets[] =
{
    OpenGL::BufferTarget::Array_Buffer,
    OpenGL::BufferTarget::Copy_Read_Buffer,
    OpenGL::BufferTarget::Copy_Write_Buffer,
    OpenGL::BufferTarget::Element_Array_Buffer,
    OpenGL::BufferTarget::Pixel_Pack_Buffer,
    OpenGL::BufferTarget::Pixel_Unpack_Buffer,
    OpenGL::BufferTarget::Texture_Buffer,
    OpenGL::BufferTarget::Transform_Feedback_Buffer,
    OpenGL::BufferTarget::Uniform_Buffer,
};

OpenGL::ActiveAttributeState::ActiveAttributeState()
{
    size = 0;
    type = VariableType::Unknown;
}

OpenGL::ActiveUniformBlock::ActiveUniformBlock()
{
    binding                       = UINT32_MAX;
    data_size                     = UINT32_MAX;
    referenced_by_fragment_shader = false;
    referenced_by_geometry_shader = false;
    referenced_by_vertex_shader   = false;
}

OpenGL::ActiveUniformState::ActiveUniformState()
{
    is_row_major          = false;
    location              = UINT32_MAX;
    size                  = 0;
    type                  = VariableType::Unknown;
    uniform_array_stride  = UINT32_MAX;
    uniform_block_index   = -1;
    uniform_block_offset  = UINT32_MAX;
    uniform_matrix_stride = UINT32_MAX;
}

OpenGL::BufferState::BufferState()
{
    access           = OpenGL::BufferAccess::Read_Write;
    map_size         = 0;
    map_start_offset = 0;
    mapped           = false;
    size             = 0;
    usage            = OpenGL::BufferUsage::Static_Draw;
}

OpenGL::ContextState::ContextState(const IGLObjectManager<OpenGL::GLBufferReferenceUniquePtr>* in_buffer_manager_ptr,
                                   const IGLObjectManager<OpenGL::GLVAOReferenceUniquePtr>*    in_vao_manager_ptr,
                                   const IGLLimits*                                            in_limits_ptr,
                                   const int32_t*                                              in_viewport_ivec4_ptr,
                                   const int32_t*                                              in_scissor_box_ivec4_ptr)
    :texture_image_units     (in_limits_ptr->get_max_texture_image_units() ),
     user_clip_planes_enabled(in_limits_ptr->get_max_clip_distances     (), false)
{
    constexpr uint32_t n_max_stencil_bits = 8; /* todo: extract this info from vk backend */

    vkgl_assert(in_limits_ptr->get_max_draw_buffers() <= 8);

    is_primitive_restart_enabled = false;
    primitive_restart_index      = 0;

    memcpy(viewport,
           in_viewport_ivec4_ptr,
           sizeof(int32_t) * 4);

    depth_range[0]         = 0.0f;
    depth_range[1]         = 1.0f;
    is_depth_clamp_enabled = false;

    clamp_read_color = OpenGL::ClampReadColorMode::Fixed_Only;
    provoking_vertex = OpenGL::ProvokingVertexConvention::Last;

    is_line_smooth_enabled    = false;
    line_width                = 1.0f;
    point_fade_threshold_size = 1.0f;
    point_size                = 1.0f;
    point_sprite_coord_origin = OpenGL::PointSpriteCoordOrigin::Upper_Left;

    cull_face_mode                  = OpenGL::CullMode::Back;
    front_face                      = OpenGL::FrontFaceOrientation::Counter_Clockwise;
    is_cull_face_enabled            = false;
    is_polygon_offset_fill_enabled  = false;
    is_polygon_offset_line_enabled  = false;
    is_polygon_offset_point_enabled = false;
    is_polygon_smooth_enabled       = false;
    polygon_offset_factor           = 0;
    polygon_offset_units            = 0;

    vkgl_assert(in_limits_ptr->get_max_samples() <= 32);

    is_multisample_enabled              = true;
    is_sample_alpha_to_coverage_enabled = false;
    is_sample_alpha_to_one_enabled      = false;
    is_sample_coverage_enabled          = false;
    is_sample_coverage_invert_enabled   = false;
    is_sample_mask_enabled              = false;
    sample_coverage_value               = 1.0f;
    sample_mask                         = (~0) & ((1 << in_limits_ptr->get_max_samples() ) - 1);

    active_texture_unit = 0;

    memcpy(scissor_box,
           in_scissor_box_ivec4_ptr,
           sizeof(int32_t) * 4);

    is_scissor_test_enabled          = false;
    is_stencil_test_enabled          = false;
    stencil_function_back            = OpenGL::StencilFunction::Always;
    stencil_function_front           = OpenGL::StencilFunction::Always;
    stencil_op_fail_back             = OpenGL::StencilOperation::Keep;
    stencil_op_fail_front            = OpenGL::StencilOperation::Keep;
    stencil_op_pass_depth_fail_back  = OpenGL::StencilOperation::Keep;
    stencil_op_pass_depth_fail_front = OpenGL::StencilOperation::Keep;
    stencil_op_pass_depth_pass_back  = OpenGL::StencilOperation::Keep;
    stencil_op_pass_depth_pass_front = OpenGL::StencilOperation::Keep;
    stencil_reference_value_back     = 0;
    stencil_reference_value_front    = 0;
    stencil_value_mask_back          = (1 << n_max_stencil_bits) - 1;
    stencil_value_mask_front         = (1 << n_max_stencil_bits) - 1;

    blend_color[0]                    = 0;
    blend_color[1]                    = 0;
    blend_color[2]                    = 0;
    blend_color[3]                    = 0;
    blend_equation_alpha              = OpenGL::BlendEquation::Function_Add;
    blend_equation_rgb                = OpenGL::BlendEquation::Function_Add;
    blend_func_dst_alpha              = OpenGL::BlendFunction::Zero;
    blend_func_dst_rgb                = OpenGL::BlendFunction::Zero;
    blend_func_src_alpha              = OpenGL::BlendFunction::One;
    blend_func_src_rgb                = OpenGL::BlendFunction::One;
    depth_function                    = OpenGL::DepthFunction::Less;
    is_blend_enabled_for_draw_buffers = 0;
    is_color_logic_op_enabled         = false;
    is_depth_test_enabled             = false;
    is_dither_enabled                 = true;
    is_framebuffer_srgb_enabled       = false;
    logic_op_mode                     = OpenGL::LogicOpMode::Copy;

    color_clear_value[0]             = 0;
    color_clear_value[1]             = 0;
    color_clear_value[2]             = 0;
    color_clear_value[3]             = 0;
    color_writemask_for_draw_buffers = ~0;
    depth_clear_value                = 1.0f;
    depth_writemask                  = true;
    stencil_clear_value              = 0;
    stencil_writemask_back           = ~0;
    stencil_writemask_front          = ~0;

    binding_draw_framebuffer = 0;
    binding_read_framebuffer = 0;
    binding_renderbuffer     = 0;

    pack_alignment      = 4;
    pack_image_height   = 0;
    pack_lsb_first      = false;
    pack_row_length     = 0;
    pack_skip_images    = 0;
    pack_skip_pixels    = 0;
    pack_skip_rows      = 0;
    pack_swap_bytes     = false;
    unpack_alignment    = 4;
    unpack_image_height = 0;
    unpack_lsb_first    = false;
    unpack_row_length   = 0;
    unpack_skip_images  = 0;
    unpack_skip_pixels  = 0;
    unpack_skip_rows    = 0;
    unpack_swap_bytes   = false;

    hint_fragment_shader_derivative = OpenGL::HintMode::Dont_Care;
    hint_line_smooth                = OpenGL::HintMode::Dont_Care;
    hint_polygon_smooth             = OpenGL::HintMode::Dont_Care;
    hint_texture_compression        = OpenGL::HintMode::Dont_Care;

    is_texture_cube_map_seamless_enabled = false;

    active_any_samples_passed_query_id                    = 0;
    active_primitives_generated_query_id                  = 0;
    active_samples_passed_query_id                        = 0;
    active_time_elapsed_query_id                          = 0;
    active_timestamp_query_id                             = 0;
    active_transform_feedback_primitives_written_query_id = 0;

    is_program_point_size_enabled = false;
    polygon_mode                  = PolygonMode::Fill;

    for (const auto& current_indexed_target : g_indexed_buffer_targets)
    {
        const auto n_max_bindings = (current_indexed_target == OpenGL::BufferTarget::Transform_Feedback_Buffer) ? in_limits_ptr->get_max_transform_feedback_separate_attribs()
                                                                                                                : in_limits_ptr->get_max_uniform_buffer_bindings            ();

        for (uint32_t n_binding = 0;
                      n_binding < n_max_bindings;
                    ++n_binding)
        {
            indexed_buffer_binding_ptrs[IndexedBufferTarget(current_indexed_target, n_binding)] = IndexedBufferBinding(in_buffer_manager_ptr->get_default_object_reference(),
                                                                                                                       0,  /* in_start_offset */
                                                                                                                       0); /* in_size         */
        }
    }

    for (const auto& current_nonindexed_target : g_nonindexed_buffer_targets)
    {
        nonindexed_buffer_binding_ptrs[current_nonindexed_target] = in_buffer_manager_ptr->get_default_object_reference();
    }

    /* Set up default VAO binding */
    vao_reference_ptr = in_vao_manager_ptr->get_default_object_reference();
}

OpenGL::ContextState::ContextState(const OpenGL::ContextState& in_context_state)
{
    *this = in_context_state;
}

OpenGL::ContextState::~ContextState()
{
    binding_draw_framebuffer.reset();
    binding_read_framebuffer.reset();
    binding_renderbuffer.reset    ();
    program_reference_ptr.reset   ();
    vao_reference_ptr.reset       ();

    indexed_buffer_binding_ptrs.clear   ();
    nonindexed_buffer_binding_ptrs.clear();
    texture_unit_to_state_ptr_map.clear ();
}

OpenGL::ContextState& OpenGL::ContextState::operator=(const OpenGL::ContextState& in_context_state)
{
    /* GL references need extra care.. */
    binding_draw_framebuffer = (in_context_state.binding_draw_framebuffer != nullptr) ? in_context_state.binding_draw_framebuffer->clone() : nullptr;
    binding_read_framebuffer = (in_context_state.binding_read_framebuffer != nullptr) ? in_context_state.binding_read_framebuffer->clone() : nullptr;
    binding_renderbuffer     = (in_context_state.binding_renderbuffer     != nullptr) ? in_context_state.binding_renderbuffer->clone    () : nullptr;
    program_reference_ptr    = (in_context_state.program_reference_ptr    != nullptr) ? in_context_state.program_reference_ptr->clone   () : nullptr;
    vao_reference_ptr        = (in_context_state.vao_reference_ptr        != nullptr) ? in_context_state.vao_reference_ptr->clone       () : nullptr;

    for (const auto& current_nonindexed_buffer_binding : in_context_state.nonindexed_buffer_binding_ptrs)
    {
        nonindexed_buffer_binding_ptrs[current_nonindexed_buffer_binding.first] = (current_nonindexed_buffer_binding.second != nullptr) ? current_nonindexed_buffer_binding.second->clone()
                                                                                                                                        : nullptr;
    }

    for (const auto& current_texture_unit_to_state_ptr_map_item : texture_unit_to_state_ptr_map)
    {
        texture_unit_to_state_ptr_map[current_texture_unit_to_state_ptr_map_item.first].reset(
            new OpenGL::TextureUnitState(*current_texture_unit_to_state_ptr_map_item.second)
        );
    }

    /* Arrays.. */
    memcpy(blend_color,
           in_context_state.blend_color,
           sizeof(blend_color) );
    memcpy(color_clear_value,
           in_context_state.color_clear_value,
           sizeof(color_clear_value) );
    memcpy(depth_range,
           in_context_state.depth_range,
           sizeof(depth_range) );
    memcpy(scissor_box,
           in_context_state.scissor_box,
           sizeof(scissor_box) );
    memcpy(viewport,
           in_context_state.viewport,
           sizeof(viewport) );

    /* Follow with trivial copy ops.. */
    indexed_buffer_binding_ptrs = in_context_state.indexed_buffer_binding_ptrs;

    is_primitive_restart_enabled = in_context_state.is_primitive_restart_enabled;
    primitive_restart_index      = in_context_state.primitive_restart_index;

    is_depth_clamp_enabled   = in_context_state.is_depth_clamp_enabled;
    user_clip_planes_enabled = in_context_state.user_clip_planes_enabled;

    clamp_read_color = in_context_state.clamp_read_color;
    provoking_vertex = in_context_state.provoking_vertex;

    is_line_smooth_enabled    = in_context_state.is_line_smooth_enabled;
    line_width                = in_context_state.line_width;
    point_fade_threshold_size = in_context_state.point_fade_threshold_size;
    point_size                = in_context_state.point_size;
    point_sprite_coord_origin = in_context_state.point_sprite_coord_origin;

    cull_face_mode                  = in_context_state.cull_face_mode;
    front_face                      = in_context_state.front_face;
    is_cull_face_enabled            = in_context_state.is_cull_face_enabled;
    is_polygon_offset_fill_enabled  = in_context_state.is_polygon_offset_fill_enabled;
    is_polygon_offset_line_enabled  = in_context_state.is_polygon_offset_line_enabled;
    is_polygon_offset_point_enabled = in_context_state.is_polygon_offset_point_enabled;
    is_polygon_smooth_enabled       = in_context_state.is_polygon_smooth_enabled;
    polygon_offset_factor           = in_context_state.polygon_offset_factor;
    polygon_offset_units            = in_context_state.polygon_offset_units;

    is_multisample_enabled              = in_context_state.is_multisample_enabled;
    is_sample_alpha_to_coverage_enabled = in_context_state.is_sample_alpha_to_coverage_enabled;
    is_sample_alpha_to_one_enabled      = in_context_state.is_sample_alpha_to_one_enabled;
    is_sample_coverage_enabled          = in_context_state.is_sample_coverage_enabled;
    is_sample_coverage_invert_enabled   = in_context_state.is_sample_coverage_invert_enabled;
    is_sample_mask_enabled              = in_context_state.is_sample_mask_enabled;
    sample_coverage_value               = in_context_state.sample_coverage_value;
    sample_mask                         = in_context_state.sample_mask;

    active_texture_unit = in_context_state.active_texture_unit;
    texture_image_units = in_context_state.texture_image_units;

    is_scissor_test_enabled          = in_context_state.is_scissor_test_enabled;
    is_stencil_test_enabled          = in_context_state.is_stencil_test_enabled;
    stencil_function_back            = in_context_state.stencil_function_back;
    stencil_function_front           = in_context_state.stencil_function_front;
    stencil_op_fail_back             = in_context_state.stencil_op_fail_back;
    stencil_op_fail_front            = in_context_state.stencil_op_fail_front;
    stencil_op_pass_depth_fail_back  = in_context_state.stencil_op_pass_depth_fail_back;
    stencil_op_pass_depth_fail_front = in_context_state.stencil_op_pass_depth_fail_front;
    stencil_op_pass_depth_pass_back  = in_context_state.stencil_op_pass_depth_pass_back;
    stencil_op_pass_depth_pass_front = in_context_state.stencil_op_pass_depth_pass_front;
    stencil_reference_value_back     = in_context_state.stencil_reference_value_back;
    stencil_reference_value_front    = in_context_state.stencil_reference_value_front;
    stencil_value_mask_back          = in_context_state.stencil_value_mask_back;
    stencil_value_mask_front         = in_context_state.stencil_value_mask_front;

    blend_equation_alpha              = in_context_state.blend_equation_alpha;
    blend_equation_rgb                = in_context_state.blend_equation_rgb;
    blend_func_dst_alpha              = in_context_state.blend_func_dst_alpha;
    blend_func_dst_rgb                = in_context_state.blend_func_dst_rgb;
    blend_func_src_alpha              = in_context_state.blend_func_src_alpha;
    blend_func_src_rgb                = in_context_state.blend_func_src_rgb;
    depth_function                    = in_context_state.depth_function;
    is_blend_enabled_for_draw_buffers = in_context_state.is_blend_enabled_for_draw_buffers;
    is_color_logic_op_enabled         = in_context_state.is_color_logic_op_enabled;
    is_depth_test_enabled             = in_context_state.is_depth_test_enabled;
    is_dither_enabled                 = in_context_state.is_dither_enabled;
    is_framebuffer_srgb_enabled       = in_context_state.is_framebuffer_srgb_enabled;
    logic_op_mode                     = in_context_state.logic_op_mode;

    color_writemask_for_draw_buffers = in_context_state.color_writemask_for_draw_buffers;
    depth_clear_value                = in_context_state.depth_clear_value;
    depth_writemask                  = in_context_state.depth_writemask;
    stencil_clear_value              = in_context_state.stencil_clear_value;
    stencil_writemask_back           = in_context_state.stencil_writemask_back;
    stencil_writemask_front          = in_context_state.stencil_writemask_front;

    pack_alignment      = in_context_state.pack_alignment;
    pack_image_height   = in_context_state.pack_image_height;
    pack_lsb_first      = in_context_state.pack_lsb_first;
    pack_row_length     = in_context_state.pack_row_length;
    pack_skip_images    = in_context_state.pack_skip_images;
    pack_skip_pixels    = in_context_state.pack_skip_pixels;
    pack_skip_rows      = in_context_state.pack_skip_rows;
    pack_swap_bytes     = in_context_state.pack_swap_bytes;
    unpack_alignment    = in_context_state.unpack_alignment;
    unpack_image_height = in_context_state.unpack_image_height;
    unpack_lsb_first    = in_context_state.unpack_lsb_first;
    unpack_row_length   = in_context_state.unpack_row_length;
    unpack_skip_images  = in_context_state.unpack_skip_images;
    unpack_skip_pixels  = in_context_state.unpack_skip_pixels;
    unpack_skip_rows    = in_context_state.unpack_skip_rows;
    unpack_swap_bytes   = in_context_state.unpack_swap_bytes;

    hint_fragment_shader_derivative = in_context_state.hint_fragment_shader_derivative;
    hint_line_smooth                = in_context_state.hint_line_smooth;
    hint_polygon_smooth             = in_context_state.hint_polygon_smooth;
    hint_texture_compression        = in_context_state.hint_texture_compression;

    is_texture_cube_map_seamless_enabled = in_context_state.is_texture_cube_map_seamless_enabled;

    active_any_samples_passed_query_id                    = in_context_state.active_any_samples_passed_query_id;
    active_primitives_generated_query_id                  = in_context_state.active_primitives_generated_query_id;
    active_samples_passed_query_id                        = in_context_state.active_samples_passed_query_id;
    active_time_elapsed_query_id                          = in_context_state.active_time_elapsed_query_id;
    active_timestamp_query_id                             = in_context_state.active_timestamp_query_id;
    active_transform_feedback_primitives_written_query_id = in_context_state.active_transform_feedback_primitives_written_query_id;

    is_program_point_size_enabled = in_context_state.is_program_point_size_enabled;
    polygon_mode                  = in_context_state.polygon_mode;

    return *this;
}

OpenGL::DispatchTable::DispatchTable()
{
    memset(this,
           0,
           sizeof(*this) );
}

OpenGL::FramebufferAttachmentPointState::FramebufferAttachmentPointState()
{
    component_type           = OpenGL::FramebufferAttachmentComponentType::None;
    layered                  = false;
    name                     = 0;
    size_alpha               = 0;
    size_blue                = 0;
    size_depth               = 0;
    size_green               = 0;
    size_red                 = 0;
    size_stencil             = 0;
    texture_cube_map_face    = OpenGL::TextureCubeMapFace::None;
    texture_layer            = 0;
    texture_level            = 0;
    type                     = OpenGL::FramebufferAttachmentObjectType::None;
    uses_srgb_color_encoding = false;
}

OpenGL::FramebufferState::FramebufferState(const uint32_t& in_n_color_attachments)
    :color_attachments           (in_n_color_attachments),
     draw_buffer_per_color_output(in_n_color_attachments)
{
    is_doublebuffer  = false;
    is_stereo        = false;
    n_sample_buffers = 0;
    n_samples        = 1;
    read_buffer      = 0;
}

OpenGL::IndexedBufferBinding::IndexedBufferBinding(const OpenGL::IndexedBufferBinding& in_binding)
{
    *this = in_binding;
}

OpenGL::IndexedBufferBinding& OpenGL::IndexedBufferBinding::operator=(const OpenGL::IndexedBufferBinding& in_binding)
{
    reference_ptr = (in_binding.reference_ptr != nullptr) ? in_binding.reference_ptr->clone()
                                                          : nullptr;
    size          = in_binding.size;
    start_offset  = in_binding.start_offset;

    return *this;
}

OpenGL::ProgramState::ProgramState(const uint32_t& in_n_max_indexed_uniform_buffer_bindings)
    :uniform_buffer_binding_indexed(in_n_max_indexed_uniform_buffer_bindings)
{
    active_attribute_max_length           = 0;
    active_uniform_block_max_length       = 0;
    active_uniform_max_length             = 0;
    delete_status                         = false;
    link_status                           = false;
    n_geometry_vertices_out               = 0;
    n_transform_feedback_varyings         = 0;
    geometry_input_type                   = OpenGL::GeometryInputType::Unknown;
    geometry_output_type                  = OpenGL::GeometryOutputType::Unknown;
    transform_feedback_buffer_mode        = OpenGL::TransformFeedbackBufferMode::Unknown;
    transform_feedback_varying_max_length = 0;
    validate_status                       = false;
}

OpenGL::RangedBufferBinding::RangedBufferBinding()
{
    buffer_id    = 0;
    size         = 0;
    start_offset = 0;
}

OpenGL::RenderbufferState::RenderbufferState()
{
    height          = 0;
    internal_format = OpenGL::InternalFormat::RGBA;
    samples         = 0;
    size_alpha      = 0;
    size_blue       = 0;
    size_depth      = 0;
    size_green      = 0;
    size_red        = 0;
    size_stencil    = 0;
    width           = 0;
}

OpenGL::SamplePosition::SamplePosition()
{
    x = FLT_MAX;
    y = FLT_MAX;
}

OpenGL::ShaderState::ShaderState()
{
    compile_status = false;
    delete_status  = false;
    type           = OpenGL::ShaderType::Unknown;
}

OpenGL::TextureImageState::TextureImageState(const OpenGL::InternalFormat& in_internal_format)
{
    binding_texture_buffer_data_store = 0;
    compressed_image_size             = 0;
    fixed_sample_locations            = true;
    depth                             = 0;
    height                            = 0;
    internal_format                   = in_internal_format;
    samples                           = 0;
    width                             = 0;
}

OpenGL::TextureState::TextureState(const OpenGL::TextureMinFilter& in_min_filter,
                                   const OpenGL::TextureWrapMode&  in_wrap_s,
                                   const OpenGL::TextureWrapMode&  in_wrap_t,
                                   const OpenGL::TextureWrapMode&  in_wrap_r)
{
    base_level       = 0;
    border_color[0]  = 0;
    border_color[1]  = 0;
    border_color[2]  = 0;
    border_color[3]  = 0;
    compare_function = OpenGL::TextureCompareFunction::LEqual;
    compare_mode     = OpenGL::TextureCompareMode::None;
    lod_bias         = 0.0f;
    mag_filter       = OpenGL::TextureMagFilter::Linear;
    max_level        = 1000;
    max_lod          = 1000.0f;
    min_filter       = in_min_filter;
    min_lod          = -1000.0f;
    wrap_r           = in_wrap_r;
    wrap_s           = in_wrap_s;
    wrap_t           = in_wrap_t;
}

OpenGL::TextureUnitState::TextureUnitState()
{
    binding_1d                   = 0;
    binding_1d_array             = 0;
    binding_2d                   = 0;
    binding_2d_array             = 0;
    binding_2d_multisample       = 0;
    binding_2d_multisample_array = 0;
    binding_3d                   = 0;
    binding_cube_map             = 0;
    binding_rectangle            = 0;
    binding_texture_buffer       = 0;
}

OpenGL::TransformFeedbackVaryingState::TransformFeedbackVaryingState()
{
    size = 0;
    type = VariableType::Unknown;
}

OpenGL::UniformValue::UniformValue()
{
    ivec4[0] = 0;
    ivec4[1] = 0;
    ivec4[2] = 0;
    ivec4[3] = 0;
}

OpenGL::VertexArrayObjectState::VertexArrayObjectState(const uint32_t& in_n_vertex_attribute_arrays)
    :vertex_attribute_arrays(in_n_vertex_attribute_arrays)
{
    element_array_buffer_binding = 0;
}

OpenGL::VertexAttributeArrayState::VertexAttributeArrayState()
{
    /* As per table 6.4, core GL 3.2 spec */
    enabled    = false;
    integer    = false;
    normalized = false;
    pointer    = nullptr;
    size       = 4;
    stride     = 0;
    type       = VertexAttributeArrayType::Float;
}

OpenGL::VertexAttributeArrayState::VertexAttributeArrayState(const VertexAttributeArrayState& in_vaa_state)
{
    buffer_binding_ptr = (in_vaa_state.buffer_binding_ptr != nullptr) ? in_vaa_state.buffer_binding_ptr->clone()
                                                                      : GLBufferReferenceUniquePtr();
    enabled            = in_vaa_state.enabled;
    integer            = in_vaa_state.integer;
    normalized         = in_vaa_state.normalized;
    pointer            = in_vaa_state.pointer;
    size               = in_vaa_state.size;
    stride             = in_vaa_state.stride;
    type               = in_vaa_state.type;
}

OpenGL::VertexAttributeArrayState& OpenGL::VertexAttributeArrayState::operator=(const VertexAttributeArrayState& in_state)
{
    buffer_binding_ptr = (in_state.buffer_binding_ptr != nullptr) ? in_state.buffer_binding_ptr->clone()
                                                                  : GLBufferReferenceUniquePtr();
    enabled            = in_state.enabled;
    integer            = in_state.integer;
    normalized         = in_state.normalized;
    pointer            = in_state.pointer;
    size               = in_state.size;
    stride             = in_state.stride;
    type               = in_state.type;

    return *this;
}

bool OpenGL::VertexAttributeArrayState::operator==(const VertexAttributeArrayState& in_state)
{
    bool result = false;

    if (enabled    == in_state.enabled    &&
        integer    == in_state.integer    &&
        normalized == in_state.normalized &&
        pointer    == in_state.pointer    &&
        size       == in_state.size       &&
        stride     == in_state.stride     &&
        type       == in_state.type)
    {
        if ((buffer_binding_ptr == nullptr && in_state.buffer_binding_ptr == nullptr)                                                       ||
            (buffer_binding_ptr != nullptr && in_state.buffer_binding_ptr != nullptr && *buffer_binding_ptr == *in_state.buffer_binding_ptr))
        {
            result = true;
        }
    }

    return result;
}