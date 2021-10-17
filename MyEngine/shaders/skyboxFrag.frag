#version 330 core

in vec3 texCoords;

out vec4 finalColor;

uniform samplerCube day;
uniform samplerCube night;

//uniform float factor;

void main()
{
	finalColor = texture(day, texCoords);
}