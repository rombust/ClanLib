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

#pragma once

#include "API/VK/volk.h"
#include <cstring>
#include "API/Display/Render/rasterizer_state_description.h"
#include "API/Display/TargetProviders/graphic_context_provider.h"

namespace clan
{
	class VulkanRasterizerStateProvider : public RasterizerStateProvider
	{
	public:
		explicit VulkanRasterizerStateProvider(const RasterizerStateDescription& d);
		~VulkanRasterizerStateProvider() override = default;

		RasterizerStateDescription desc;

		static VkCullModeFlags vk_cull_mode(bool culled, CullMode mode);
		static VkPolygonMode vk_polygon_mode(FillMode m);
	};

	struct VulkanRasterizerKey
	{
		VkCullModeFlags cull_mode = VK_CULL_MODE_NONE;
		VkFrontFace front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		VkPolygonMode polygon_mode = VK_POLYGON_MODE_FILL;
		VkBool32 depth_clamp = VK_FALSE;
		VkBool32 scissor_test = VK_FALSE;
		VkBool32 depth_bias_enable = VK_FALSE;
		float depth_bias_constant = 0.0f; // units in glPolygonOffset
		float depth_bias_slope = 0.0f; // factor in glPolygonOffset
		float line_width = 1.0f;
		float point_size = 1.0f;

		bool operator==(const VulkanRasterizerKey &o) const
		{
			return std::memcmp(this, &o, sizeof(*this)) == 0;
		}

		void fill_from(const RasterizerStateDescription& desc);
		void apply_to(VkPipelineRasterizationStateCreateInfo& rs) const;
	};

} // namespace clan
