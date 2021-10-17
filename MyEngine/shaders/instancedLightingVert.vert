#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normals;
//layout(location = 3) in vec3 tangents;
layout(location = 3) in mat4 instanceModel;

out VS_OUT
{
	out vec2 vsTexCoords;
	out vec3 vsNormals;
	out vec4 vsLightSpaceFragPos;
	out vec3 vsFragPos;
	//out mat3 tbn;

} vs_out;

uniform mat4 model; 

layout (std140, binding=0) uniform matrices
{
	uniform mat4 perspective;
	uniform mat4 view;
	//32 bytes
};
uniform mat4 lightSpaceMatrix;

void main()
{
/*	
	vec3 tm = normalize(vec3(model * vec4(tangents, 0.0)));
	vec3 nm = normalize(vec3(model * vec4(normals, 0.0)));
	vec3 bitang = normalize(cross(nm, tm));
	vec3 bm = normalize(vec3(model * vec4(bitang,0.0)));
	vs_out.tbn = mat3(tm, bm, nm);
*/

	gl_Position = perspective * view * instanceModel * vec4(position,1.0);
	vs_out.vsFragPos = position * mat3(instanceModel);
	vs_out.vsTexCoords = texCoords;
	vs_out.vsNormals = normals;
	vs_out.vsLightSpaceFragPos = lightSpaceMatrix * vec4(vs_out.vsFragPos,1.0);

}