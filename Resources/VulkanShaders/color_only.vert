#version 450

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color0;

layout(push_constant) uniform PushConstants
{
	float point_size;
} pc;

layout(location = 0) out vec4 vColor;

void main()
{
	gl_Position  = Position;
	gl_PointSize = pc.point_size;
	vColor       = Color0;
}
