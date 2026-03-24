#version 450

layout(location = 0) in  vec4 vColor;
layout(location = 1) in  vec2 vTexCoord;
layout(location = 0) out vec4 fragColor;

layout(set = 0, binding = 0) uniform sampler2D Texture0;

void main()
{
	fragColor = vColor * texture(Texture0, vTexCoord);
}
