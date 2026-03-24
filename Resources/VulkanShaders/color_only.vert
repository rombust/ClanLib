#version 450

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color0;

layout(location = 0) out vec4 vColor;

void main()
{
	gl_Position = Position;
	vColor	= Color0;
}
