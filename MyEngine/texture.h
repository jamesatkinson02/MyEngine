#pragma once
#include "GL/glew.h"
#include <string>
#include <vector>
#include "shaderManager.h"

namespace corona
{
	class texture
	{
	private:
		int m_width, m_height;
		GLuint m_id;
		int m_unit;
		bool m_textureLoaded;
		std::string m_name;
		bool m_isTransparent;
		bool load(const char* filePath, bool isTransparent);
	public:
		texture(const char* filePath, int unit, bool isTransparent);
		 void draw();
		 void bind();
		 void clean();
		 int getWidth();
		 int getHeight();
		 int getIndex() const;
		 bool hasTextureLoaded();
		 const std::string& getName();
		 ~texture();
	};

	class cubeMap
	{
	private:
		GLuint m_id;
		std::string m_name;
		int m_width, m_height, m_unit;
		bool load(std::vector<const char*> faces);
	public:
		cubeMap(std::string name, std::vector<const char*> faces, int unit);
		void bind();
		void draw();
		void clean();
		std::string getName() const;
		int getWidth() const;
		int getHeight() const;
		int getUnit() const;
		void setUnit(int unit);
	};

}
