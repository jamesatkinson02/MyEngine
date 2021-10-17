#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normals;
//layout(location = 3) in mat4 instancedModel;

out VS_OUT
{
	out vec2 outTexCoords;
	out vec3 outNormals;
	out vec4 fragPosLightSpace;
	out vec3 fragPos;
} vs_out;

uniform mat4 model; 

layout (std140, binding=0) uniform matrices
{
	uniform mat4 perspective;
	uniform mat4 view;
	//32 bytes
};

uniform mat4 lightSpaceMatrix;

//uniform vec3 offsets[100];

void main()
{
	//vec3 currentVertex = offsets[gl_InstanceID];
	//gl_Position = perspective * view * model * vec4(position,1.0);
	vs_out.fragPos = position * mat3(model);
	gl_Position = perspective * view * model * vec4(position,1.0);
	vs_out.fragPosLightSpace = lightSpaceMatrix * vec4(vs_out.fragPos,1.0);
	vs_out.outTexCoords = texCoords;
	vs_out.outNormals = normals;
}