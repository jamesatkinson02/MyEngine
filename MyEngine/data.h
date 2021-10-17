#pragma once
#include <vector>
#include "vertex.h"

namespace corona
{
	vector<vertex> cubeVertices = {
		// Front face
		vertex(vec3(-1.0, -1.0,  1.0), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
		vertex(vec3(1.0, -1.0,  1.0),  vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
		vertex(vec3(1.0,  1.0,  1.0),  vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
		vertex(vec3(-1.0,  1.0,  1.0), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),

		// Back face
		vertex(vec3(-1.0, -1.0, -1.0), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
		vertex(vec3(-1.0,  1.0, -1.0), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
		vertex(vec3(1.0,  1.0, -1.0),  vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
		vertex(vec3(1.0, -1.0, -1.0),  vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),

		// Top face
		vertex(vec3(-1.0,  1.0, -1.0), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		vertex(vec3(-1.0,  1.0,  1.0), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		vertex(vec3(1.0,  1.0,  1.0), vec2(1.0f, 1.0f),	 vec3(0.0f, 1.0f, 0.0f)),
		vertex(vec3(1.0,  1.0, -1.0), vec2(0.0f, 0.0f),	 vec3(0.0f, 1.0f, 0.0f)),

		// Bottom face
		vertex(vec3(-1.0, -1.0, -1.0), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		vertex(vec3(1.0, -1.0, -1.0),  vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		vertex(vec3(1.0, -1.0,  1.0),  vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
		vertex(vec3(-1.0, -1.0,  1.0), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),

		// Right face
		vertex(vec3(1.0, -1.0, -1.0), vec2(0.0f, 0.0f),	vec3(1.0f, 0.0f, 0.0f)),
		vertex(vec3(1.0,  1.0, -1.0), vec2(1.0f, 0.0f),	vec3(1.0f, 0.0f, 0.0f)),
		vertex(vec3(1.0,  1.0,  1.0), vec2(1.0f, 1.0f),	vec3(1.0f, 0.0f, 0.0f)),
		vertex(vec3(1.0, -1.0,  1.0), vec2(0.0f, 0.0f),	vec3(1.0f, 0.0f, 0.0f)),

		// Left face
		vertex(vec3(-1.0, -1.0, -1.0), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)),
		vertex(vec3(-1.0, -1.0,  1.0), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)),
		vertex(vec3(-1.0,  1.0,  1.0), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)),
		vertex(vec3(-1.0,  1.0, -1.0), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f))
	};

	std::vector<GLfloat> skyboxVertices = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	vector<GLuint> cubeIndices = {
		0,  1,  2,      0,  2,  3,    // front
		4,  5,  6,      4,  6,  7,    // back
		8,  9,  10,     8,  10, 11,   // top
		12, 13, 14,     12, 14, 15,   // bottom
		16, 17, 18,     16, 18, 19,   // right
		20, 21, 22,     20, 22, 23,   // left
};
}