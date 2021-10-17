#include "font.h"
#include "logger.h"
#include "display.h"
#include <algorithm>
namespace corona
{

	font::font(unsigned int fontSize)
	{
	
		if (!init())
			return;
	
		m_face = new FT_Face();
		if (FT_New_Face(*m_ft, "assets/fonts/arial.ttf", 0, m_face))
		{
			logger::error("Could not load font!");
			return;
		}

		FT_Set_Pixel_Sizes(*m_face, 0, fontSize);
		

		FT_GlyphSlot g = (*m_face)->glyph;
		m_atlasWidth = m_atlasHeight = 0;
		for (int i = 32; i < 128; i++)
		{
			if (FT_Load_Char(*m_face, (char)i, FT_LOAD_RENDER))
			{
				logger::error("Loading character failed");
				continue;
			}

			m_atlasWidth += g->bitmap.width;
			m_atlasHeight = std::max(m_atlasHeight, g->bitmap.rows);


		}

		GLuint m_fontTexID;
		glGenTextures(1, &m_fontTexID);
		glBindTexture(GL_TEXTURE_2D, m_fontTexID);
		glActiveTexture(GL_TEXTURE0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_atlasWidth, m_atlasHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		/* Stores 1 byte per pixel */
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		int x = 0;
		int j = 0;
		for (int i = 32; i < 128; i++)
		{
			if (FT_Load_Char(*m_face, (char)i, FT_LOAD_RENDER))
				continue;

			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			m_chars[j].advanceX = g->advance.x >> 6;
			m_chars[j].advanceY = g->advance.y >> 6;

			m_chars[j].width = g->bitmap.width;
			m_chars[j].height = g->bitmap.rows;

			m_chars[j].left = g->bitmap_left;
			m_chars[j].top = g->bitmap_top;

			m_chars[j].txOffset = x / m_atlasWidth;
				
			x += g->bitmap.width;
			++j;
		}


		
		FT_Done_Face(*m_face);
		FT_Done_FreeType(*m_ft);

		loadBuffer();
	}

	bool font::init()
	{
		m_ft = new FT_Library();
		if (FT_Init_FreeType(m_ft))
		{
			logger::error("Could not init FreeType library!");
			return false;
		}

		return true;
	}

	void font::loadBuffer()
	{


		glGenVertexArrays(1, &m_vaoID);
		glGenBuffers(1, &m_vboID);

		glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void font::renderText(shaderManager& shader, const string& text, float x, float y, float sx, float sy, glm::vec3 color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader.use();
		glBindVertexArray(m_vaoID);
		glActiveTexture(GL_TEXTURE0);

		shader.setFloat3("fontColor", color);

		mat4 projection = ortho(0, display::getInstance()->getWindowWidth(), 0, display::getInstance()->getWindowHeight());
		shader.setMatrix4f("projection", projection);

		int j = 0;
		for (int i = 0; i < text.size(); i++)
		{

			float xpos = x + m_chars[i].left * sx;
			float ypos = (y - (y - m_chars[i].top) * sy);

			float w = m_chars[i].width * sx;
			float h = m_chars[i].height * sy;

			x += m_chars[i].advanceX * sx;
			y += m_chars[i].advanceY * sx;


			float vertices[6][4] = {
				 { xpos,     -ypos,   m_chars[i].txOffset, 0.0f },
				 { xpos + w,     -ypos,       m_chars[i].txOffset + m_chars[i].width / m_atlasWidth, 0.0f },
				 { xpos, -ypos - h,      m_chars[i].txOffset, m_chars[i].height / m_atlasHeight},

				 { xpos + w,     -ypos,   m_chars[i].txOffset + m_chars[i].width / m_atlasWidth, 0.0f },
				 { xpos, -ypos - h,       m_chars[i].txOffset, m_chars[i].height / m_atlasHeight},
				 { xpos + w, -ypos - h,   m_chars[i].txOffset + m_chars[i].width / m_atlasWidth,  m_chars[i].height / m_atlasHeight}
			};
	
			glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
			glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

			glDrawArrays(GL_TRIANGLES, 0, 6);

		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	}

	void font::clean()
	{
		glDeleteBuffers(1, &m_vboID);
		glDeleteVertexArrays(1, &m_vaoID);
		glDeleteTextures(1, &m_fontTexID);
		
		delete m_face, m_ft;
	
	}

}