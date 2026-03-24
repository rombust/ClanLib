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
#include "API/Display/Render/blend_state_description.h"
#include "API/Display/TargetProviders/graphic_context_provider.h"

namespace clan
{
	class VulkanBlendStateProvider : public BlendStateProvider
	{
	public:
		explicit VulkanBlendStateProvider(const BlendStateDescription& d);
		~VulkanBlendStateProvider() override = default;

		BlendStateDescription desc;

		static VkBlendFactor vk_blend_factor(BlendFunc f);
		static VkBlendOp vk_blend_op(BlendEquation eq);
		static VkLogicOp vk_logic_op(LogicOp op);
	};

	struct VulkanBlendKey
	{
		VkBool32 blend_enable = VK_FALSE;
		VkBlendFactor src_color = VK_BLEND_FACTOR_ONE;
		VkBlendFactor dst_color = VK_BLEND_FACTOR_ZERO;
		VkBlendOp color_op = VK_BLEND_OP_ADD;
		VkBlendFactor src_alpha = VK_BLEND_FACTOR_ONE;
		VkBlendFactor dst_alpha = VK_BLEND_FACTOR_ZERO;
		VkBlendOp alpha_op = VK_BLEND_OP_ADD;
		VkColorComponentFlags color_write = VK_COLOR_COMPONENT_R_BIT |
											VK_COLOR_COMPONENT_G_BIT |
											VK_COLOR_COMPONENT_B_BIT |
											VK_COLOR_COMPONENT_A_BIT;
		VkBool32 logic_op_enable = VK_FALSE;
		VkLogicOp logic_op = VK_LOGIC_OP_COPY;

		bool operator==(const VulkanBlendKey &o) const
		{
			return std::memcmp(this, &o, sizeof(*this)) == 0;
		}

		void fill_from(const BlendStateDescription& desc);
		VkPipelineColorBlendAttachmentState to_attachment_state() const;
	};

} // namespace clan
