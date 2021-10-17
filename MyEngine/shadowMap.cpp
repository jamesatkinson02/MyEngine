#include "shadowMap.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "depthMap.h"

using namespace corona;


shadowMap::shadowMap(shaderManager* program, dirLight* source) : m_program{ program }, m_directional{ source }, m_fboID{ 0 }, m_lightSpace{glm::mat4{1.0f}}
{

}

bool shadowMap::loadDepthMap()
{
	glGenFramebuffers(1, &m_fboID);

	m_depthMap = new depthMap(SHADOW_WIDTH, SHADOW_HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap->getDepthMap(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	unbindFbo();

	return true;
}

void shadowMap::unbindFbo()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void shadowMap::drawToDepthMap()
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_program->use();
	glm::mat4 lightOrtho = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NEAR_PLANE, FAR_PLANE);
	glm::mat4 lightView = glm::lookAt(m_directional->getTarget(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_lightSpace = lightOrtho * lightView;
	m_program->setMatrix4f("lightSpaceMatrix", m_lightSpace);
}

void shadowMap::setModelSpace(glm::mat4& model)
{
	m_program->setMatrix4f("model", model);
}

void shadowMap::bindDepthMap(shaderManager& program, int index)
{
	m_depthMap->draw(program);
	glActiveTexture(GL_TEXTURE0 + index);
	program.setInt1("shadowMap", index);
}

void shadowMap::clean()
{
	glDeleteFramebuffers(1, &m_fboID);
	m_depthMap->clean();
}

glm::mat4& shadowMap::getLightSpace()
{
	return m_lightSpace;
}