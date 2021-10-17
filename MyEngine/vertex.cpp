#include "vertex.h"

namespace corona
{
	vertex::vertex(const vec3& v, const vec2& texCoord, const vec3& normal) :
		m_vertex{ v }, m_texCoord{ texCoord }, m_normal{ normal } {}

}