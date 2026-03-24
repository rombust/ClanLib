#version 450

layout(location = 0) in vec4  Position;
layout(location = 1) in vec4  Color0;
layout(location = 2) in vec2  TexCoord0;
layout(location = 3) in int   TexIndex0;

layout(location = 0) out vec4 vColor;
layout(location = 1) out vec2 vTexCoord;
layout(location = 2) flat out int vTexIndex;

void main()
{
	gl_Position = Position;
	vColor	= Color0;
	vTexCoord   = TexCoord0;
	vTexIndex   = TexIndex0;
}
