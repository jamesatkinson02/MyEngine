#version 430 core

in vec2 outTexCoords;

out vec4 finalColor;

uniform sampler2D tex;

void main(void)
{
	vec4 texColor =texture(tex, outTexCoords);
	if(texColor.a < 0.1f)
		discard;

	finalColor = texColor * 0.7f;

	
}
