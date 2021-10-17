#include "texture.h"
#include <string>
#include <iostream>
#include <cassert>
#include "logger.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
namespace corona
{
	texture::texture(const char* filePath, int unit, bool isTransparent) : m_width{ 0 }, m_height{ 0 }, m_unit{ unit }, m_textureLoaded{ false }
	{
		m_name = filePath;
		load(filePath, isTransparent);
	}

	bool texture::load(const char* filePath, bool isTransparent)
	{
		logger::trace("loading: " + std::string(filePath));
		glGenTextures(1, &m_id);
		bind();

		int channels;

		GLenum stbiFormat = STBI_rgb;
		if (isTransparent)
			stbiFormat = STBI_rgb_alpha;

		unsigned char* image = stbi_load(filePath, &m_width, &m_height, &channels, stbiFormat);

		if (!image)
		{
			logger::error("Could not load texture: " + std::string(filePath));
			return false;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum format = GL_RGB;

		if (isTransparent)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);

		glBindTexture(GL_TEXTURE_2D, NULL);

		return true;
	}

	void texture::draw()
	{
		glActiveTexture(GL_TEXTURE0 + m_unit);
		bind();
	}

	void texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void texture::clean()
	{
		glDeleteTextures(1, &m_id);
	}

	int texture::getWidth()
	{
		return m_width;
	}

	int texture::getHeight()
	{
		return m_height;
	}

	int texture::getIndex() const
	{
		return m_unit;
	}

	bool texture::hasTextureLoaded()
	{
		return m_textureLoaded;
	}

	const std::string& texture::getName()
	{
		return m_name;
	}

	texture::~texture()
	{

	}

	cubeMap::cubeMap(std::string name, std::vector<const char*> faces, int unit) : m_name{ name }, m_unit{ unit }
	{
		load(faces);
	}

	bool cubeMap::load(std::vector<const char*> faces)
	{
		glGenTextures(1, &m_id);
		bind();

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (int i = 0; i < faces.size(); i++)
		{
			int channels;

			unsigned char* image = stbi_load(faces[i], &m_width, &m_height, &channels, STBI_rgb);

			if (!image)
			{
				std::cout << "Could not load face: " << faces[i] << '\n';
				return false;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}

		logger::trace("loaded " + m_name + " cubemap!");

		return true;
	}

	void cubeMap::bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	}

	void cubeMap::draw()
	{
		glActiveTexture(GL_TEXTURE0 + m_unit);
		bind();
	}

	std::string cubeMap::getName() const
	{
		return m_name;
	}

	int cubeMap::getWidth() const
	{
		return m_width;
	}

	int cubeMap::getHeight() const
	{
		return m_height;
	}

	void cubeMap::clean()
	{
		glDeleteTextures(1, &m_id);
	}

	int cubeMap::getUnit() const
	{
		return m_unit;
	}

	void cubeMap::setUnit(int unit)
	{
		m_unit = unit;
	}

}

