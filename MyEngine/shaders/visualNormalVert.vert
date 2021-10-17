#version 430 core

layout(location=0) in vec3 position;
layout(location=2) in vec3 normal;

out VS_OUT
{
	vec3 vsNormal;
} vs_out;

layout (std140, binding=0) uniform matrices
{
	mat4 perspective;
	mat4 view;
};

uniform mat4 model;

void main()
{
	mat3 normalMatrix = inverse(transpose(mat3(mat4(model * view))));
	vs_out.vsNormal = normalMatrix * normal;
	gl_Position = perspective * view * model * vec4(position,1.0);
}