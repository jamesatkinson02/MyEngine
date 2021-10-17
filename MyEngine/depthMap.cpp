#include "depthMap.h"

namespace corona
{

	depthMap::depthMap(const int width, const int height)
	{
		load(width, height);
	}

	bool depthMap::load(const int width, const int height)
	{
		glGenTextures(1, &m_depthMap);
		glBindTexture(GL_TEXTURE_2D, m_depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		return true;
	}

	void depthMap::draw(shaderManager& program)
	{
		glBindTexture(GL_TEXTURE_2D, m_depthMap);
	}

	void depthMap::clean()
	{
		glDeleteTextures(1, &m_depthMap);
	}

	GLuint& depthMap::getDepthMap()
	{
		return m_depthMap;
	}
}