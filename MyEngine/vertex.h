#pragma once
#include "glm.hpp"

using namespace glm;

namespace corona
{
	struct vertex
	{
		vec3 m_vertex;
		vec2 m_texCoord;
		vec3 m_normal;

		vertex(const vec3& v, const vec2& texCoord, const vec3& normal);
	};

}
