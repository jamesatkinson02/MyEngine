#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normals;
layout(location = 3) in mat4 models;

out vec2 outTexCoords;


layout (std140, binding=0) uniform matrices
{
	uniform mat4 perspective;
	uniform mat4 view;
	//32 bytes
};

void main()
{
	gl_Position = perspective * view * models * vec4(position,1.0);
	outTexCoords = texCoords;
}