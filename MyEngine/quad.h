#pragma once
#include "GL/glew.h"
#include "shaderManager.h"
#include "texture.h"
#include "arrayBuffer.h"
namespace corona
{
	class quad
	{
	private:
		ArrayBuffer* m_quadBuffer;
		texture* m_quadTexture;
		glm::mat4 m_transform;
		glm::vec3 m_pos;
	public:
		quad(glm::vec3 pos, const std::vector<glm::mat4>& translations=std::vector<glm::mat4>());
		bool loadTexture(const char* filePath, int unit, bool isTransparent);
		void draw(shaderManager& program);
		void drawInstances(shaderManager& program, int count);
		void clean();
		void translate(glm::vec3 pos);
		void scale(glm::vec3 factor);
		void rotate(float degrees, glm::vec3 axis);
		void identity();
	};

}
