#version 430 core

in vec2 outTexCoords;

uniform sampler2D glyph;

uniform vec3 fontColor;

out vec4 fragColor;

void main()
{
	fragColor = vec4(fontColor,1.0f) *  vec4(1.0f, 1.0f, 1.0f, texture(glyph, outTexCoords).r);
	
}