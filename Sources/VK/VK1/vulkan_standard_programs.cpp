/*
**  ClanLib SDK
**  Copyright (c) 1997-2026 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**	claim that you wrote the original software. If you use this software
**	in a product, an acknowledgment in the product documentation would be
**	appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**	misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**	Magnus Norddahl
**	Mark Page
*/

#include "VK/precomp.h"
#include "VK/VK1/vulkan_standard_programs.h"
#include "VK/VK1/vulkan_program_object_provider.h"
#include "VK/VK1/vulkan_shader_object_provider.h"
#include "VK/vulkan_device.h"

namespace clan
{

#ifdef DEBUG
#include "../Shaders/color_only_frag_debug_12.spv.h"
#include "../Shaders/color_only_vert_debug_12.spv.h"
#include "../Shaders/path_frag_debug_12.spv.h"
#include "../Shaders/path_vert_debug_12.spv.h"
#include "../Shaders/single_texture_frag_debug_12.spv.h"
#include "../Shaders/single_texture_vert_debug_12.spv.h"
#include "../Shaders/sprite_frag_debug_12.spv.h"
#include "../Shaders/sprite_vert_debug_12.spv.h"
#else
#include "../Shaders/color_only_frag_release_12.spv.h"
#include "../Shaders/color_only_vert_release_12.spv.h"
#include "../Shaders/path_frag_release_12.spv.h"
#include "../Shaders/path_vert_release_12.spv.h"
#include "../Shaders/single_texture_frag_release_12.spv.h"
#include "../Shaders/single_texture_vert_release_12.spv.h"
#include "../Shaders/sprite_frag_release_12.spv.h"
#include "../Shaders/sprite_vert_release_12.spv.h"
#endif

void VulkanStandardPrograms::create(VulkanDevice *device,
									VulkanProgramObjectProvider *&out_color_only,
									VulkanProgramObjectProvider *&out_single_texture,
									VulkanProgramObjectProvider *&out_sprite,
									VulkanProgramObjectProvider *&out_path)
{
	auto make_program = [&](const unsigned char *vertex_shader, unsigned int vertex_shader_size, const unsigned char* fragment_shader, unsigned int fragment_shader_size) -> VulkanProgramObjectProvider *
	{
		auto *vert = new VulkanShaderObjectProvider(device);
		vert->create(ShaderType::vertex, vertex_shader, vertex_shader_size);
		vert->compile();
		if (!vert->get_compile_status())
			throw Exception("VulkanStandardPrograms: vertex shader compile failed:\n" + vert->get_info_log());

		auto *frag = new VulkanShaderObjectProvider(device);
		frag->create(ShaderType::fragment, fragment_shader, fragment_shader_size);
		frag->compile();
		if (!frag->get_compile_status())
			throw Exception("VulkanStandardPrograms: fragment shader compile failed:\n" + frag->get_info_log());

		auto *prog = new VulkanProgramObjectProvider(device);
		prog->attach_shader(vert);
		prog->attach_shader(frag);
		prog->link();
		if (!prog->get_link_status())
			throw Exception("VulkanStandardPrograms: program link failed:\n" + prog->get_info_log());
		return prog;
	};

#ifdef DEBUG
	out_color_only = make_program(color_only_vert_debug_12_spv, color_only_vert_debug_12_spv_len, color_only_frag_debug_12_spv, color_only_frag_debug_12_spv_len);
	out_single_texture = make_program(single_texture_vert_debug_12_spv, single_texture_vert_debug_12_spv_len, single_texture_frag_debug_12_spv, single_texture_frag_debug_12_spv_len);
	out_sprite = make_program(sprite_vert_debug_12_spv, sprite_vert_debug_12_spv_len, sprite_frag_debug_12_spv, sprite_frag_debug_12_spv_len);
	out_path = make_program(path_vert_debug_12_spv, path_vert_debug_12_spv_len, path_frag_debug_12_spv, path_frag_debug_12_spv_len);
#else
	out_color_only = make_program(color_only_vert_release_12_spv, color_only_vert_release_12_spv_len, color_only_frag_release_12_spv, color_only_frag_release_12_spv_len);
	out_single_texture = make_program(single_texture_vert_release_12_spv, single_texture_vert_release_12_spv_len, single_texture_frag_release_12_spv, single_texture_frag_release_12_spv_len);
	out_sprite = make_program(sprite_vert_release_12_spv, sprite_vert_release_12_spv_len, sprite_frag_release_12_spv, sprite_frag_release_12_spv_len);
	out_path = make_program(path_vert_release_12_spv, path_vert_release_12_spv_len, path_frag_release_12_spv, path_frag_release_12_spv_len);
#endif

	// ypos_scale is a push constant at offset 0 in the path vertex shader.
	// Write the initial value (1.0) directly
	out_path->set_uniform1f(0, 1.0f);

	// single_texture: binding 0 - Texture0
	out_single_texture->register_sampler_binding(0);

	// sprite: bindings 0–15 - Texture0–Texture15
	for (uint32_t b = 0; b <= 15; ++b)
		out_sprite->register_sampler_binding(b);

	// path: bindings 0–2 - mask_texture, instance_data, image_texture
	out_path->register_sampler_binding(0);
	out_path->register_sampler_binding(1);
	out_path->register_sampler_binding(2);
}

} // namespace clan
