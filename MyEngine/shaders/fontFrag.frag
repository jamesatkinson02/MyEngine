#version 430 core

in vec2 outTexCoords;

uniform sampler2D glyph;

uniform vec3 fontColor;

out vec4 fragColor;

void main()
{
	fragColor = vec4(fontColor, texture(glyph, outTexCoords).r);
}