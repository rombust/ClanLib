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
#include "API/Display/Render/depth_stencil_state_description.h"
#include "API/Display/TargetProviders/graphic_context_provider.h"

namespace clan
{
	class VulkanDepthStencilStateProvider : public DepthStencilStateProvider
	{
	public:
		explicit VulkanDepthStencilStateProvider(const DepthStencilStateDescription& d);
		~VulkanDepthStencilStateProvider() override = default;

		DepthStencilStateDescription desc;

		static VkCompareOp vk_compare_op(CompareFunction f);
		static VkStencilOp vk_stencil_op(StencilOp op);
	};

	struct VulkanDepthStencilKey
	{
		VkBool32 depth_test = VK_FALSE;
		VkBool32 depth_write = VK_TRUE;
		VkCompareOp depth_func = VK_COMPARE_OP_LESS;

		VkBool32 stencil_test = VK_FALSE;

		VkCompareOp front_func = VK_COMPARE_OP_ALWAYS;
		uint32_t front_compare_mask = 0xFF;
		uint32_t front_write_mask = 0xFF;
		VkStencilOp front_fail = VK_STENCIL_OP_KEEP;
		VkStencilOp front_depth_fail = VK_STENCIL_OP_KEEP;
		VkStencilOp front_pass = VK_STENCIL_OP_KEEP;

		VkCompareOp back_func = VK_COMPARE_OP_ALWAYS;
		uint32_t back_compare_mask = 0xFF;
		uint32_t back_write_mask = 0xFF;
		VkStencilOp back_fail = VK_STENCIL_OP_KEEP;
		VkStencilOp back_depth_fail = VK_STENCIL_OP_KEEP;
		VkStencilOp back_pass = VK_STENCIL_OP_KEEP;

		bool operator==(const VulkanDepthStencilKey &o) const
		{
			return std::memcmp(this, &o, sizeof(*this)) == 0;
		}

		void fill_from(const DepthStencilStateDescription& desc);
		void apply_to(VkPipelineDepthStencilStateCreateInfo& ds, uint32_t stencil_ref) const;
	};

} // namespace clan
