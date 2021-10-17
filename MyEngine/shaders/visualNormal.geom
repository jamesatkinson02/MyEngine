#version 430 core

layout (triangles) in;
layout(line_strip, max_vertices=2) out;

in VS_OUT
{
	vec3 vsNormal;
} gs_in[];

uniform mat4 projection;

void visualize(int index)
{
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = gl_in[index].gl_Position + (vec4(gs_in[index].vsNormal,0.0f) * projection);
	EmitVertex();
	EndPrimitive();
}

void main()
{
	visualize(0);
	visualize(1);
	visualize(2);
}

