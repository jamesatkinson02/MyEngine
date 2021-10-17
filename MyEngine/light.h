#pragma once
#include "glm.hpp"
#include "shaderManager.h"

namespace corona
{

	struct attenuation
	{
		float m_constant;
		float m_linear;
		float m_quadratic;
		attenuation(float constant, float linear, float quadratic);
	};

	class pointLight
	{
	private:
		glm::vec3 m_pos;
		attenuation* m_attenuation;
		glm::vec3 m_target;
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
	public:
		pointLight(glm::vec3 pos, glm::vec3 target, attenuation* atten, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		void addAttenuation(float aConstant, float aLinear, float aQuadratic);
		void draw(shaderManager& program);
		glm::vec3& getPos();
		attenuation* getAttenuation();
		glm::vec3& getTarget();
		glm::vec3& getAmbient();
		glm::vec3& getDiffuse();
		glm::vec3& getSpecular();
	};

	class spotLight
	{
	private:
		glm::vec3 m_pos;
		glm::vec3 m_target;
		attenuation* m_att;
		float m_cutOff;
	public:
		spotLight(glm::vec3 pos, glm::vec3 target, attenuation* att, float cutOff);
		void draw(shaderManager& program);
		glm::vec3& getPos();
		glm::vec3& getTarget();
		attenuation* getAttenuation();
		float getCutOff();
		void setCutOff(float cutOff);
	};

	class dirLight
	{
	private:
		glm::vec3 m_target;
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
	public:
		dirLight(glm::vec3 target, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		void draw(shaderManager& program);
		glm::vec3& getTarget();
		glm::vec3& getAmbient();
		glm::vec3& getDiffuse();
		glm::vec3& getSpecular();

	};

}
