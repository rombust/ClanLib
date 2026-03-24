#version 450

layout(location = 0) in ivec4 Vertex;

layout(push_constant) uniform PushConstants
{
	float ypos_scale;
} pc;

layout(set = 0, binding = 1) uniform sampler2D instance_data;

layout(location = 0) out vec2 vMaskPosition;
layout(location = 1) flat out vec4 vBrushData1;
layout(location = 2) flat out vec4 vBrushData2;
layout(location = 3) out vec4 vVaryData;
layout(location = 4) flat out ivec2 vInstanceOffset;

void main()
{
	const int mask_block_size = 16;
	const int mask_width      = 1024;
	const int instance_width  = 512;

	vec4 canvas_data = texelFetch(instance_data, ivec2(0, 0), 0);

	ivec2 size = ivec2(Vertex.z % 2, Vertex.z / 2);

	gl_Position = vec4(
		((Vertex.x + size.x * mask_block_size) * 2.0 / canvas_data.x) - 1.0,
		pc.ypos_scale * (((Vertex.y + size.y * mask_block_size) * -2.0 / canvas_data.y) + 1.0),
		0.0, 1.0);

	int mask_offset = Vertex.w % 65536;
	int y_offset    = (mask_offset * mask_block_size) / mask_width;
	vMaskPosition   = vec2(mask_offset * mask_block_size - y_offset * mask_width,
	                       y_offset * mask_block_size);
	vMaskPosition  += vec2(size * mask_block_size);
	vMaskPosition  /= float(mask_width);

	int instance_block = Vertex.w / 65536;
	y_offset           = instance_block / instance_width;
	vInstanceOffset    = ivec2(instance_block - y_offset * instance_width, y_offset);

	vBrushData1 = texelFetch(instance_data, vInstanceOffset, 0);
	vBrushData2 = texelFetch(instance_data, ivec2(vInstanceOffset.x + 1, vInstanceOffset.y), 0);
	vec4 brush_data3 = texelFetch(instance_data, ivec2(vInstanceOffset.x + 2, vInstanceOffset.y), 0);

	// Linear / radial gradient: distance from gradient origin
	vVaryData.x = float(Vertex.x + size.x * mask_block_size) - brush_data3.x;
	vVaryData.y = float(Vertex.y + size.y * mask_block_size) - brush_data3.y;

	// Texture fill: pixel position before transform
	vVaryData.z = float(Vertex.x + size.x * mask_block_size);
	vVaryData.w = float(Vertex.y + size.y * mask_block_size);

	// Apply inverse brush transform to texture coords
	mat4 inv_transform = mat4(
		texelFetch(instance_data, ivec2(vInstanceOffset.x + 2, vInstanceOffset.y), 0),
		texelFetch(instance_data, ivec2(vInstanceOffset.x + 3, vInstanceOffset.y), 0),
		texelFetch(instance_data, ivec2(vInstanceOffset.x + 4, vInstanceOffset.y), 0),
		texelFetch(instance_data, ivec2(vInstanceOffset.x + 5, vInstanceOffset.y), 0));
	vVaryData.zw = (vec4(vVaryData.zw, 0.0, 1.0) * transpose(inv_transform)).xy;

	vVaryData.z = (vVaryData.z + vBrushData1.x) / vBrushData2.x;
	vVaryData.w = (vVaryData.w + vBrushData1.y) / vBrushData2.y;
}
