#include "skybox.h"
#include "display.h"
#include "data.h"
using namespace corona;

skybox::skybox() : 
	m_skyboxShader{ new shaderManager("skybox", "shaders/skyboxVert.vert", "shaders/skyboxFrag.frag") }, m_factor{ 0.0f }, m_isDay{ true }
{
	vector<const char*> skyFaces = {
		"assets/textures/day/right.jpg",
		"assets/textures/day/left.jpg",
		"assets/textures/day/top.jpg",
		"assets/textures/day/bottom.jpg",
		"assets/textures/day/front.jpg",
		"assets/textures/day/back.jpg"
	};
	vector<const char*> nightFaces = {
		"assets/textures/night/nightRight.png",
		"assets/textures/night/nightLeft.png",
		"assets/textures/night/nightTop.png",
		"assets/textures/night/nightBottom.png",
		"assets/textures/night/nightFront.png",
		"assets/textures/night/nightBack.png"
	};

	m_day= new cubeMap("day", skyFaces, 0);
	m_night = new cubeMap("night", nightFaces, 1);
	loadSkyBox();
}

void skybox::loadSkyBox()
{
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_vboID);

	glBindVertexArray(m_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(GLfloat), &skyboxVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);
}

void skybox::update()
{
	m_factor = 0.0f;
	m_skyboxShader->setFloat1("factor", m_factor);
}

void skybox::draw(camera& cam)
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	m_skyboxShader->use();
	//update();
	m_skyboxShader->setInt1("night", m_night->getUnit());
	m_skyboxShader->setInt1("day", m_day->getUnit());
	m_day->draw();
	m_night->draw();
	m_skyboxShader->setMatrix4f("perspective", cam.getPerspective());
	glm::mat4 skyboxView = glm::mat4(glm::mat3(cam.getView()));
//	skyboxView = glm::rotate(skyboxView, glm::radians((float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
	m_skyboxShader->setMatrix4f("view", skyboxView);
	
	glBindVertexArray(m_vaoID);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(NULL);

	glDepthMask(GL_TRUE);
}

void skybox::clean()
{
	m_night->clean();
	m_day->clean();
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
	m_skyboxShader->clean();
}