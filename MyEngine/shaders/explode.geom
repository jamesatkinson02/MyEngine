#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in VS_OUT
{
	in vec2 vsTexCoords;
	in vec3 vsNormals;
	in vec4 vsLightSpaceFragPos;
	in vec3 vsFragPos;
	//in mat3 tbn;
} gs_in[];

out GS_OUT
{
	out vec2 outTexCoords;
	out vec3 outNormals;
	out vec4 outLightSpaceFragPos;
	out vec3 outFragPos;
	//out mat3 outTBN;
} gs_out;

uniform float time;

vec3 getNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a,b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 2.0f;
	vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
	return position + vec4(direction,0.0);
	
}

void main(void)
{
	vec3 normal = getNormal();
	gl_Position = explode(gl_in[0].gl_Position, normal);
	gl_Position = gl_in[0].gl_Position;
	gs_out.outTexCoords = gs_in[0].vsTexCoords;
	gs_out.outNormals = gs_in[0].vsNormals;
	gs_out.outLightSpaceFragPos = gs_in[0].vsLightSpaceFragPos;
	gs_out.outFragPos = gs_in[0].vsFragPos;
	//gs_out.outTBN = gs_in[0].tbn;
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
	gl_Position = gl_in[1].gl_Position;
	gs_out.outTexCoords = gs_in[1].vsTexCoords;
	gs_out.outNormals = gs_in[1].vsNormals;
	gs_out.outLightSpaceFragPos = gs_in[1].vsLightSpaceFragPos;
	gs_out.outFragPos = gs_in[1].vsFragPos;
	//gs_out.outTBN = gs_in[1].tbn;
	EmitVertex();
	gl_Position = explode(gl_in[2].gl_Position, normal);
	gl_Position = gl_in[2].gl_Position;
	gs_out.outTexCoords = gs_in[2].vsTexCoords;
	gs_out.outNormals = gs_in[2].vsNormals;
	gs_out.outLightSpaceFragPos = gs_in[2].vsLightSpaceFragPos;
	gs_out.outFragPos = gs_in[2].vsFragPos;
	//gs_out.outTBN = gs_in[2].tbn;
	EmitVertex();
	EndPrimitive();
}