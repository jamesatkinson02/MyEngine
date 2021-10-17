#include "quad.h"
#include "mesh.h"
using namespace corona;

quad::quad(glm::vec3 pos, const std::vector<glm::mat4>& translations) : m_pos{ pos }
{
	const std::vector<vertex> quadVertices = {
	vertex(vec3(0.5f,  0.5f, 0.0f),	 vec2(1.0f, 0.0f),  vec3(0.0f, 0.0f, -1.0f)),   // top right
	vertex(vec3(0.5f, -0.5f, 0.0f),	 vec2(1.0f, 1.0f),  vec3(0.0f, 0.0f, -1.0f)),   // bottom right
	vertex(vec3(-0.5f, -0.5f, 0.0f), vec2(0.0f, 1.0f),  vec3(0.0f, 0.0f, -1.0f)), 	// bottom left
	vertex(vec3(-0.5f,  0.5f, 0.0f), vec2(0.0f, 0.0f),  vec3(0.0f, 0.0f, -1.0f))	// top left
	};

	const std::vector<unsigned int> quadIndices = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	m_transform = glm::mat4(1.0f);
	m_quadBuffer = new ArrayBuffer();
	m_quadBuffer->genVao();

	m_quadBuffer->bindVao();
	m_quadBuffer->loadBuffer(quadVertices, quadIndices, translations);
	
	m_quadBuffer->setAttribute(0, 3, GL_FLOAT, sizeof(vertex), (const void*)(0));
	m_quadBuffer->setAttribute(1, 2, GL_FLOAT, sizeof(vertex), (const void*)(offsetof(vertex, m_texCoord)));
	m_quadBuffer->setAttribute(2, 3, GL_FLOAT, sizeof(vertex), (const void*)(offsetof(vertex, m_normal)));

	if (!translations.empty())
	{
		int startIndex = 3;
		for (int i = startIndex; i <= startIndex + 3; i++)
		{
			m_quadBuffer->setAttribute(i, 4, GL_FLOAT, 4 * sizeof(glm::vec4), (GLvoid*)((i - startIndex) * sizeof(glm::vec4)));
			m_quadBuffer->setAttribDivisor(i, 1);
		}
	}



	m_quadBuffer->unbindVao();

}

bool quad::loadTexture(const char* filePath, int unit, bool isTransparent)
{
	m_quadTexture = new texture(filePath, unit, isTransparent);

	if (!m_quadTexture)
		return false;

	return true;
}

void quad::draw(shaderManager& program)
{
	m_quadBuffer->bindVao();

	program.setMatrix4f("model", m_transform);

	if (m_quadTexture)
		m_quadTexture->draw();

	m_quadBuffer->draw();
}

void quad::drawInstances(shaderManager& program, int count)
{
	m_quadBuffer->bindVao();

	program.setMatrix4f("model", m_transform);

	if (m_quadTexture)
		m_quadTexture->draw();

	m_quadBuffer->drawInstances(count);
}

void quad::clean()
{
	if(m_quadTexture)
		m_quadTexture->clean();

	m_quadBuffer->clean();

	delete m_quadBuffer, m_quadTexture;
}

void quad::translate(glm::vec3 pos)
{
	m_transform = glm::translate(m_transform, pos);
	
}

void quad::scale(glm::vec3 factor)
{
	m_transform = glm::scale(m_transform, factor);
}

void quad::rotate(float degrees, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, glm::radians(degrees), axis);
}

void quad::identity()
{
	m_transform = glm::mat4(1.0f);
}