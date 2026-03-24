echo off
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" color_only.vert -o color_only_vert_debug_12.spv -g -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" color_only.frag -o color_only_frag_debug_12.spv -g -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" single_texture.vert -o single_texture_vert_debug_12.spv -g -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" single_texture.frag -o single_texture_frag_debug_12.spv -g -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" sprite.vert -o sprite_vert_debug_12.spv -g -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" sprite.frag -o sprite_frag_debug_12.spv -g -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" path.vert -o path_vert_debug_12.spv -g -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" path.frag -o path_frag_debug_12.spv -g -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" color_only.vert -o color_only_vert_release_12.spv -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" color_only.frag -o color_only_frag_release_12.spv -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" single_texture.vert -o single_texture_vert_release_12.spv -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" single_texture.frag -o single_texture_frag_release_12.spv -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" sprite.vert -o sprite_vert_release_12.spv -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" sprite.frag -o sprite_frag_release_12.spv -O --target-env=vulkan1.2

"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" path.vert -o path_vert_release_12.spv -O --target-env=vulkan1.2
"C:\VulkanSDK\1.4.341.1\Bin\glslc.exe" path.frag -o path_frag_release_12.spv -O --target-env=vulkan1.2

echo Use linux:  "for i in *.spv; do xxd -i $i >$i.h; done"
echo Put headers in "Sources\VK\Shaders"

pause
