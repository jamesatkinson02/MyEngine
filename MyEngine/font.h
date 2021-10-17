#pragma once
#include "glm.hpp"
#include <map>
#include "shaderManager.h"
#include "arrayBuffer.h"
#include "ft2build.h"
#include FT_FREETYPE_H

using namespace glm;
using namespace std;

namespace corona

{
	struct character
	{
		float width, height; 
		float left, top;
		float advanceX, advanceY;
		float txOffset;
	};

	class font
	{
	private:
		character m_chars[128];
		FT_Face* m_face;
		FT_Library* m_ft;
	//	buffer* m_buffer;
		GLuint m_vaoID, m_vboID, m_fontTexID;
		unsigned int m_atlasWidth, m_atlasHeight;
	public:
		font(unsigned int fontSize);
		bool init();
		bool loadGlyph(unsigned char glyph);
		void loadBuffer();
		void clean();
		void renderText(shaderManager& shader, const string& text, float x, float y, float sx, float sy, glm::vec3 color);
	};


}
