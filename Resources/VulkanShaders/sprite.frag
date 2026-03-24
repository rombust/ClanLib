#version 450

layout(location = 0) in  vec4 vColor;
layout(location = 1) in  vec2 vTexCoord;
layout(location = 2) flat in int vTexIndex;
layout(location = 0) out vec4 fragColor;

layout(set = 0, binding =  0) uniform sampler2D Texture0;
layout(set = 0, binding =  1) uniform sampler2D Texture1;
layout(set = 0, binding =  2) uniform sampler2D Texture2;
layout(set = 0, binding =  3) uniform sampler2D Texture3;
layout(set = 0, binding =  4) uniform sampler2D Texture4;
layout(set = 0, binding =  5) uniform sampler2D Texture5;
layout(set = 0, binding =  6) uniform sampler2D Texture6;
layout(set = 0, binding =  7) uniform sampler2D Texture7;
layout(set = 0, binding =  8) uniform sampler2D Texture8;
layout(set = 0, binding =  9) uniform sampler2D Texture9;
layout(set = 0, binding = 10) uniform sampler2D Texture10;
layout(set = 0, binding = 11) uniform sampler2D Texture11;
layout(set = 0, binding = 12) uniform sampler2D Texture12;
layout(set = 0, binding = 13) uniform sampler2D Texture13;
layout(set = 0, binding = 14) uniform sampler2D Texture14;
layout(set = 0, binding = 15) uniform sampler2D Texture15;

void main()
{
	vec4 texel;
	switch (vTexIndex)
	{
	case  0: texel = texture(Texture0,  vTexCoord); break;
	case  1: texel = texture(Texture1,  vTexCoord); break;
	case  2: texel = texture(Texture2,  vTexCoord); break;
	case  3: texel = texture(Texture3,  vTexCoord); break;
	case  4: texel = texture(Texture4,  vTexCoord); break;
	case  5: texel = texture(Texture5,  vTexCoord); break;
	case  6: texel = texture(Texture6,  vTexCoord); break;
	case  7: texel = texture(Texture7,  vTexCoord); break;
	case  8: texel = texture(Texture8,  vTexCoord); break;
	case  9: texel = texture(Texture9,  vTexCoord); break;
	case 10: texel = texture(Texture10, vTexCoord); break;
	case 11: texel = texture(Texture11, vTexCoord); break;
	case 12: texel = texture(Texture12, vTexCoord); break;
	case 13: texel = texture(Texture13, vTexCoord); break;
	case 14: texel = texture(Texture14, vTexCoord); break;
	case 15: texel = texture(Texture15, vTexCoord); break;
	default: texel = vec4(1.0, 1.0, 1.0, 1.0);
	}
	fragColor = vColor * texel;
}
