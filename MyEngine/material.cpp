#include "material.h"

using namespace corona;

material::material(const char* filePath, int index) : m_ambient{ vec3(1.0f) }, m_diffuse{ vec3(1.0f) }, m_specular{ vec3(1.0f) }, 
m_shininess{ 0 }, m_hasDiffuse{ false }, m_hasSpecular{ false }, m_hasNormalMap{ false }
{
	loadMaterial(filePath, index);
}

bool material::loadMaterial(const char* filePath, int index)
{
	std::string diffuseMapPath, specularMapPath, bumpMapPath;

	std::ifstream file(filePath, std::ios::in);
	if (!file.is_open())
	{
		logger::error("Could not open material file!");
		return false;
	}

	for (std::string line; std::getline(file, line);)
	{
		std::istringstream ss(line);
		std::string type;
		ss >> type;
		
		if (type == "Ka")
		{
			ss >> m_ambient.x >> m_ambient.y >> m_ambient.z;
		}
		else if (type == "Kd")
		{
			ss >> m_diffuse.x >> m_diffuse.y >> m_diffuse.z;
		}
		else if (type == "Ks")
		{
			ss >> m_specular.x >> m_specular.y >> m_specular.z;
		}
		else if (type == "Ns")
		{
			ss >> m_shininess;
		}
		else if (type == "map_Kd")
		{
			ss >> diffuseMapPath;
		}
		else if (type == "map_Ks")
		{
			ss >> specularMapPath;
		}
		else if (type == "map_bump")
		{
			ss >> bumpMapPath;
		}
		else if (type == "newmtl")
		{
			ss >> m_name;
		}
		else if (type == "Tr")
		{
			float val;
			ss >> val;
			m_isTransparent = (val == 1.0 ? false : true);
		}
	}
	if (!diffuseMapPath.empty())
	{
		m_diffuseMap = new texture(diffuseMapPath.c_str(), 0, m_isTransparent);
		m_hasDiffuse = true;
	}
	if (!bumpMapPath.empty())
	{
		m_bumpMap = new texture(bumpMapPath.c_str(), 1, false);
		m_hasNormalMap = true;
	}

	if (!specularMapPath.empty())
	{
		m_specularMap = new texture(specularMapPath.c_str(), 2, false);
		m_hasSpecular = true;
	}

	return true;
}

void material::applyMaterial(shaderManager& program)
{
	program.setFloat1("mat.shininess", m_shininess);
	program.setFloat3("mat.ambient", m_ambient);
	program.setFloat3("mat.diffuse", m_diffuse);
	program.setFloat3("mat.specular", m_specular);
	program.setInt1("mat.hasDiffuse", m_hasDiffuse);
	program.setInt1("mat.hasSpecular", m_hasSpecular);
	program.setInt1("mat.hasNormalMap", m_hasNormalMap);
}

void material::draw(shaderManager& program)
{

	if (m_hasSpecular)
	{
		m_specularMap->draw();
		program.setInt1("mat.specularMap", m_specularMap->getIndex());
	}


	if (m_hasNormalMap)
	{
		program.setInt1("mat.normalMap", m_bumpMap->getIndex());
		m_bumpMap->draw();
	}
	
	if (m_hasDiffuse)
	{
		if (m_isTransparent)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		program.setInt1("mat.diffuseMap", m_diffuseMap->getIndex());
		m_diffuseMap->draw();
	
	}


	applyMaterial(program);
}

void material::clean()
{
	if(m_bumpMap)
		m_bumpMap->clean();

	if(m_specularMap)
		m_specularMap->clean();

	if(m_diffuseMap)
		m_diffuseMap->clean();
}

float material::getShininess() const
{
	return m_shininess;
}

vec3& material::getAmbient()
{
	return m_ambient;
}

vec3& material::getDiffuse()
{
	return m_ambient;
}

vec3& material::getSpecular()
{
	return m_ambient;
}

std::string material::getName() const
{
	return m_name;
}

int material::getTextureWidth() const
{
	return m_diffuseMap->getWidth();
}

int material::getTextureHeight() const
{
	return m_diffuseMap->getHeight();
}

bool material::hasDiffuse() const
{
	return m_hasDiffuse;
}

bool material::hasSpecular() const
{
	return m_hasSpecular;
}

bool material::hasNormalMap() const
{
	return m_hasNormalMap;
}

