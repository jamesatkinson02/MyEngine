#pragma once
#include "texture.h"

namespace corona
{
	class depthMap
	{
	private:
		GLuint m_depthMap;
	public:
		depthMap(const int width, const int height);
		bool load(const int width, const int height);
		void draw(shaderManager& program);
		void clean();
		GLuint& getDepthMap();
	};

}
