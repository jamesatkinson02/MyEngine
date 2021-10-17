#pragma once
#include "GL/glew.h"
#include "texture.h"

namespace corona
{
	class frameBuffer
	{
	private:
		GLuint m_fboID, m_texID, m_rboID;
		bool load();
	public:
		frameBuffer();
		void attachTexture(texture& tex);
		void attachRBO();
		void bindFBO();
		void unbindFBO();
		void bindTexture();
		void unbindTexture();
		void clean();
		bool checkStatus();
	};
}
