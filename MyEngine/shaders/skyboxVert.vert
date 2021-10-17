#version 330 core

layout(location=0) in vec3 pos;

out vec3 texCoords;

uniform mat4 perspective;
uniform mat4 view;

void main(void)
{
	texCoords = pos;
	vec4 newPos = perspective * view * vec4(pos,1.0);
	gl_Position = newPos.xyww;
}