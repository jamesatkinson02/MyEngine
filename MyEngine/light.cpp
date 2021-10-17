#include "light.h"

using namespace corona;

attenuation::attenuation(float constant, float linear, float quadratic) 
	: m_constant{ constant }, m_linear{ linear }, m_quadratic{quadratic}
{
}

pointLight::pointLight(glm::vec3 pos, glm::vec3 target, attenuation* atten, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	m_pos{ pos }, m_target{ target }, m_attenuation{ atten }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{specular}
{
}

void pointLight::addAttenuation(float aConstant, float aLinear, float aQuadratic)
{
	m_attenuation = new attenuation(aConstant, aLinear, aQuadratic);
}

void pointLight::draw(shaderManager& program)
{
	program.setFloat3("pointLight.pos", getPos());
	program.setFloat3("pointLight.target", getTarget());
	if (m_attenuation)
	{
		program.setFloat1("pointLight.aConstant", m_attenuation->m_constant);
		program.setFloat1("pointLight.aLinear", m_attenuation->m_linear);
		program.setFloat1("pointLight.aQuadratic", m_attenuation->m_quadratic);
	}
}

glm::vec3& pointLight::getPos()
{
	return m_pos;
}

attenuation* pointLight::getAttenuation()
{
	if(m_attenuation)
		return m_attenuation;
}

glm::vec3& pointLight::getTarget()
{
	return m_target;
}

glm::vec3& pointLight::getAmbient()
{
	return m_ambient;
}

glm::vec3& pointLight::getDiffuse()
{
	return m_diffuse;
}

glm::vec3& pointLight::getSpecular()
{
	return m_specular;
}

spotLight::spotLight(glm::vec3 pos, glm::vec3 target, attenuation* att, float cutOff) 
	: m_pos{ pos }, m_target{ target }, m_att{ att }, m_cutOff{ cutOff }
{
}

void spotLight::draw(shaderManager& program)
{
	program.setFloat3("spotLight.pos", m_pos);
	program.setFloat3("spotLight.target", m_target);
	program.setFloat1("pointLight.aConstant", m_att->m_constant);
	program.setFloat1("pointLight.aLinear", m_att->m_linear);
	program.setFloat1("pointLight.aQuadratic", m_att->m_quadratic);
	program.setFloat1("spotLight.cutOff", m_cutOff);
}

glm::vec3& spotLight::getPos()
{
	return m_pos;
}

glm::vec3& spotLight::getTarget()
{
	return m_target;
}

attenuation* spotLight::getAttenuation()
{
	return m_att;
}

float spotLight::getCutOff()
{
	return m_cutOff;
}

void spotLight::setCutOff(float cutOff)
{
	m_cutOff = cutOff;
}

dirLight::dirLight(glm::vec3 target, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
	: m_target{ target }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular }
{

}

void dirLight::draw(shaderManager& program) 
{
	program.setFloat3("sun.target", m_target);
	program.setFloat3("sun.ambient", m_ambient);
	program.setFloat3("sun.diffuse", m_diffuse);
	program.setFloat3("sun.specular", m_specular);
	
}

glm::vec3& dirLight::getTarget()
{
	return m_target;
}

glm::vec3& dirLight::getAmbient()
{
	return m_ambient;
}

glm::vec3& dirLight::getDiffuse()
{
	return m_diffuse;
}

glm::vec3& dirLight::getSpecular()
{
	return m_specular;
}