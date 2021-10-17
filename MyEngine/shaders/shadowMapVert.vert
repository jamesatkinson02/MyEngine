#version 430 core

layout(location=0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main(void)
{
	gl_Position = lightSpaceMatrix * model * vec4(position,1.0);
}