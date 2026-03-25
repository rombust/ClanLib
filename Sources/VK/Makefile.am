lib_LTLIBRARIES = libclan42VK.la

libclan42VK_la_SOURCES = \
vulkan_device.cpp \
State/vulkan_depth_stencil_state.cpp \
State/vulkan_blend_state.cpp \
State/vulkan_rasterizer_state.cpp \
precomp.cpp \
volk.c \
vulkan_vma.cpp \
VK1/vulkan_primitives_array_provider.cpp \
VK1/vulkan_transfer_buffer_provider.cpp \
VK1/vulkan_render_buffer_provider.cpp \
VK1/vulkan_standard_programs.cpp \
VK1/vulkan_program_object_provider.cpp \
VK1/vulkan_pixel_buffer_provider.cpp \
VK1/vulkan_vertex_array_buffer_provider.cpp \
VK1/vulkan_storage_buffer_provider.cpp \
VK1/vulkan_occlusion_query_provider.cpp \
VK1/vulkan_texture_provider.cpp \
VK1/vulkan_element_array_buffer_provider.cpp \
VK1/vulkan_uniform_buffer_provider.cpp \
VK1/vulkan_shader_object_provider.cpp \
VK1/vulkan_frame_buffer_provider.cpp \
VK1/vulkan_graphic_context_provider.cpp \
VK1/vulkan_buffer_object_provider.cpp \
setup_vulkan.cpp \
vulkan_context_description.cpp \
vulkan_window_provider_base.cpp
if WIN32
libclan42VK_la_SOURCES += \
Platform/Win32/vulkan_window_provider.cpp
else
libclan42VK_la_SOURCES += \
Platform/X11/vulkan_window_provider_x11.cpp
endif
libclan42VK_la_LDFLAGS = \
  -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) $(LDFLAGS_LT_RELEASE) \
  $(extra_LIBS_clanVK)

libclan42VK_la_CXXFLAGS=$(clanVK_CXXFLAGS) $(extra_CFLAGS_clanVK)

# EOF #

