#pragma once
#include "glm.hpp"
#include "GL/glew.h"
#include "shaderManager.h"
#include "texture.h"
#include "scene.h"

using namespace glm;

namespace corona
{
	class material
	{
	private:
		texture* m_diffuseMap;
		texture* m_specularMap;
		texture* m_bumpMap;
		vec3 m_ambient, m_diffuse, m_specular;
		float m_shininess;
		bool m_isTransparent;
		bool m_hasDiffuse, m_hasSpecular, m_hasNormalMap;
		std::string m_name;
		void applyMaterial(shaderManager& program);
	public:
		material(const char* filePath, int index);
		std::string getName() const;
		bool loadMaterial(const char* filePath, int index);
		void draw(shaderManager& program);
		void clean();
		float getShininess() const;
		vec3& getAmbient();
		vec3& getDiffuse();
		vec3& getSpecular();
		int getTextureWidth() const;
		int getTextureHeight() const;
		bool hasDiffuse() const;
		bool hasSpecular() const;
		bool hasNormalMap() const;

	};

}
