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
#include "VK/State/vulkan_depth_stencil_state.h"

namespace clan
{
	VulkanDepthStencilStateProvider::VulkanDepthStencilStateProvider(const DepthStencilStateDescription& d)
			: desc(d.clone())
	{
	}
	VkCompareOp VulkanDepthStencilStateProvider::vk_compare_op(CompareFunction f)
	{
		switch (f)
		{
		case CompareFunction::never: return VK_COMPARE_OP_NEVER;
		case CompareFunction::less: return VK_COMPARE_OP_LESS;
		case CompareFunction::lequal: return VK_COMPARE_OP_LESS_OR_EQUAL;
		case CompareFunction::greater: return VK_COMPARE_OP_GREATER;
		case CompareFunction::gequal: return VK_COMPARE_OP_GREATER_OR_EQUAL;
		case CompareFunction::equal: return VK_COMPARE_OP_EQUAL;
		case CompareFunction::notequal: return VK_COMPARE_OP_NOT_EQUAL;
		case CompareFunction::always: return VK_COMPARE_OP_ALWAYS;
		default: return VK_COMPARE_OP_ALWAYS;
		}
	}

	VkStencilOp VulkanDepthStencilStateProvider::vk_stencil_op(StencilOp op)
	{
		switch (op)
		{
		case StencilOp::keep: return VK_STENCIL_OP_KEEP;
		case StencilOp::zero: return VK_STENCIL_OP_ZERO;
		case StencilOp::replace: return VK_STENCIL_OP_REPLACE;
		case StencilOp::incr: return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
		case StencilOp::decr: return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
		case StencilOp::invert: return VK_STENCIL_OP_INVERT;
		case StencilOp::incr_wrap: return VK_STENCIL_OP_INCREMENT_AND_WRAP;
		case StencilOp::decr_wrap: return VK_STENCIL_OP_DECREMENT_AND_WRAP;
		default: return VK_STENCIL_OP_KEEP;
		}
	}

	void VulkanDepthStencilKey::fill_from(const DepthStencilStateDescription& desc)
	{
		depth_test = desc.is_depth_test_enabled() ? VK_TRUE : VK_FALSE;
		depth_write = desc.is_depth_write_enabled() ? VK_TRUE : VK_FALSE;
		depth_func = VulkanDepthStencilStateProvider::vk_compare_op(desc.get_depth_compare_function());

		stencil_test = desc.is_stencil_test_enabled() ? VK_TRUE : VK_FALSE;

		CompareFunction f_func; int f_ref; int f_mask;
		CompareFunction b_func; int b_ref; int b_mask;
		unsigned char f_write, b_write;
		StencilOp f_fail, f_dfail, f_dpass;
		StencilOp b_fail, b_dfail, b_dpass;

		desc.get_stencil_compare_front(f_func, f_ref, f_mask);
		desc.get_stencil_compare_back(b_func, b_ref, b_mask);
		desc.get_stencil_write_mask(f_write, b_write);
		desc.get_stencil_op_front(f_fail, f_dfail, f_dpass);
		desc.get_stencil_op_back(b_fail, b_dfail, b_dpass);

		front_func = VulkanDepthStencilStateProvider::vk_compare_op(f_func);
		front_compare_mask = static_cast<uint32_t>(f_mask);
		front_write_mask = static_cast<uint32_t>(f_write);
		front_fail = VulkanDepthStencilStateProvider::vk_stencil_op(f_fail);
		front_depth_fail = VulkanDepthStencilStateProvider::vk_stencil_op(f_dfail);
		front_pass = VulkanDepthStencilStateProvider::vk_stencil_op(f_dpass);

		back_func = VulkanDepthStencilStateProvider::vk_compare_op(b_func);
		back_compare_mask = static_cast<uint32_t>(b_mask);
		back_write_mask = static_cast<uint32_t>(b_write);
		back_fail = VulkanDepthStencilStateProvider::vk_stencil_op(b_fail);
		back_depth_fail = VulkanDepthStencilStateProvider::vk_stencil_op(b_dfail);
		back_pass = VulkanDepthStencilStateProvider::vk_stencil_op(b_dpass);
	}

	void VulkanDepthStencilKey::apply_to(VkPipelineDepthStencilStateCreateInfo& ds,
		uint32_t stencil_ref) const
	{
		ds = {};
		ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		ds.depthTestEnable = depth_test;
		ds.depthWriteEnable = depth_write;
		ds.depthCompareOp = depth_func;
		ds.depthBoundsTestEnable = VK_FALSE;
		ds.stencilTestEnable = stencil_test;

		ds.front.compareOp = front_func;
		ds.front.compareMask = front_compare_mask;
		ds.front.writeMask = front_write_mask;
		ds.front.reference = stencil_ref;
		ds.front.failOp = front_fail;
		ds.front.depthFailOp = front_depth_fail;
		ds.front.passOp = front_pass;

		ds.back.compareOp = back_func;
		ds.back.compareMask = back_compare_mask;
		ds.back.writeMask = back_write_mask;
		ds.back.reference = stencil_ref;
		ds.back.failOp = back_fail;
		ds.back.depthFailOp = back_depth_fail;
		ds.back.passOp = back_pass;
	}
} // namespace clan
