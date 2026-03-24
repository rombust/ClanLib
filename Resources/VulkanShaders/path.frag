#version 450

layout(location = 0) in  vec2 vMaskPosition;
layout(location = 1) flat in vec4 vBrushData1;
layout(location = 2) flat in vec4 vBrushData2;
layout(location = 3) in  vec4 vVaryData;
layout(location = 4) flat in ivec2 vInstanceOffset;

layout(location = 0) out vec4 fragColor;

layout(set = 0, binding = 0) uniform sampler2D mask_texture;
layout(set = 0, binding = 1) uniform sampler2D instance_data;
layout(set = 0, binding = 2) uniform sampler2D image_texture;

vec4 mask_alpha(vec4 color)
{
	return color * texture(mask_texture, vMaskPosition).r;
}

vec4 gradient_color(int stop_start, int stop_end, float t)
{
	vec4  color          = texelFetch(instance_data, ivec2(vInstanceOffset.x + stop_start, vInstanceOffset.y), 0);
	float last_stop_pos  = texelFetch(instance_data, ivec2(vInstanceOffset.x + stop_start + 1, vInstanceOffset.y), 0).x;
	for (int i = stop_start; i < stop_end; i += 2)
	{
		vec4  stop_color = texelFetch(instance_data, ivec2(vInstanceOffset.x + i,     vInstanceOffset.y), 0);
		float stop_pos   = texelFetch(instance_data, ivec2(vInstanceOffset.x + i + 1, vInstanceOffset.y), 0).x;
		float tt         = clamp((t - last_stop_pos) / (stop_pos - last_stop_pos), 0.0, 1.0);
		color            = mix(color, stop_color, tt);
		last_stop_pos    = stop_pos;
	}
	return color;
}

void solid_fill()
{
	fragColor = mask_alpha(vBrushData2);
}

void linear_gradient_fill()
{
	vec2  grad_start     = vVaryData.xy;
	vec2  grad_dir       = vBrushData1.zw;
	float rcp_grad_length = vBrushData2.x;
	int   stop_start     = int(vBrushData2.y);
	int   stop_end       = int(vBrushData2.z);

	float t = dot(grad_start, grad_dir) * rcp_grad_length;
	fragColor = mask_alpha(gradient_color(stop_start, stop_end, t));
}

void radial_gradient_fill()
{
	vec2  grad_center    = vVaryData.xy;
	float rcp_grad_length = vBrushData2.x;
	int   stop_start     = int(vBrushData2.y);
	int   stop_end       = int(vBrushData2.z);

	float t = length(grad_center) * rcp_grad_length;
	fragColor = mask_alpha(gradient_color(stop_start, stop_end, t));
}

void image_fill()
{
	vec2 uv = vVaryData.zw;
	fragColor = mask_alpha(texture(image_texture, uv));
}

void main()
{
	switch (int(vBrushData1.x))
	{
	default:
	case 0: solid_fill();           break;
	case 1: linear_gradient_fill(); break;
	case 2: radial_gradient_fill(); break;
	case 3: image_fill();           break;
	}
}
