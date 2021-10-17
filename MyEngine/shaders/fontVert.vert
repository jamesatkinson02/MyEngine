#version 430 core

layout(location = 0) in vec4 vertex; //combined positions & tex coords

out vec2 outTexCoords;

uniform mat4 projection; 

void main()
{
	gl_Position = projection * vertex;
	outTexCoords = vertex.zw;
}