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
#include "VK/State/vulkan_rasterizer_state.h"

namespace clan
{
	VulkanRasterizerStateProvider::VulkanRasterizerStateProvider(const RasterizerStateDescription& d)
			: desc(d.clone()) {
		}

	VkCullModeFlags VulkanRasterizerStateProvider::vk_cull_mode(bool culled, CullMode mode)
	{
		if (!culled) return VK_CULL_MODE_NONE;
		switch (mode)
		{
		case CullMode::front: return VK_CULL_MODE_FRONT_BIT;
		case CullMode::back: return VK_CULL_MODE_BACK_BIT;
		case CullMode::front_and_back: return VK_CULL_MODE_FRONT_AND_BACK;
		default: return VK_CULL_MODE_BACK_BIT;
		}
	}

	VkPolygonMode VulkanRasterizerStateProvider::vk_polygon_mode(FillMode m)
	{
		switch (m)
		{
		case FillMode::line: return VK_POLYGON_MODE_LINE;
		case FillMode::point: return VK_POLYGON_MODE_POINT;
		default: return VK_POLYGON_MODE_FILL;
		}
	}

	void VulkanRasterizerKey::fill_from(const RasterizerStateDescription& desc)
	{
		cull_mode = VulkanRasterizerStateProvider::vk_cull_mode(desc.get_culled(), desc.get_face_cull_mode());
		front_face = (desc.get_front_face() == FaceSide::counter_clockwise)
			? VK_FRONT_FACE_COUNTER_CLOCKWISE
			: VK_FRONT_FACE_CLOCKWISE;
		polygon_mode = VulkanRasterizerStateProvider::vk_polygon_mode(desc.get_face_fill_mode());
		scissor_test = desc.get_enable_scissor() ? VK_TRUE : VK_FALSE;

		depth_bias_enable = (desc.get_offset_point() ||
			desc.get_offset_line() ||
			desc.get_offset_fill()) ? VK_TRUE : VK_FALSE;
		if (depth_bias_enable)
		{
			float factor = 0.0f, units = 0.0f;
			desc.get_polygon_offset(factor, units);
			depth_bias_slope = factor;
			depth_bias_constant = units;
		}
		else
		{
			depth_bias_slope = 0.0f;
			depth_bias_constant = 0.0f;
		}
		line_width = 1.0f;
	}

	void VulkanRasterizerKey::apply_to(VkPipelineRasterizationStateCreateInfo& rs) const
	{
		rs = {};
		rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rs.depthClampEnable = depth_clamp;
		rs.rasterizerDiscardEnable = VK_FALSE;
		rs.polygonMode = polygon_mode;
		rs.cullMode = cull_mode;
		rs.frontFace = front_face;
		rs.depthBiasEnable = depth_bias_enable;
		rs.depthBiasConstantFactor = depth_bias_constant;
		rs.depthBiasClamp = 0.0f;
		rs.depthBiasSlopeFactor = depth_bias_slope;
		rs.lineWidth = line_width;
	}

} // namespace clan
