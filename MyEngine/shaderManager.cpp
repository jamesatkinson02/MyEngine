#include "shaderManager.h"
using namespace corona;

shaderManager::shaderManager(std::string name, const char* vertexPath, const char* fragmentPath, const char* geoPath) : m_name{ name }
{
	logger::trace("initialising " + name + " shader!");

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	getShaderSource(SHADER_TYPE::VERTEX, vertexPath);
	glCompileShader(m_vertexID);
	showShaderLogInfo(SHADER_TYPE::VERTEX, 512);

	if (geoPath)
	{
		m_geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		getShaderSource(SHADER_TYPE::GEOMETRY, geoPath);
		glCompileShader(m_geometryID);
		showShaderLogInfo(SHADER_TYPE::GEOMETRY, 512);
	}

	m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	getShaderSource(SHADER_TYPE::FRAGMENT, fragmentPath);
	glCompileShader(m_fragmentID);
	showShaderLogInfo(SHADER_TYPE::FRAGMENT, 512);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexID);
	if (geoPath)
		glAttachShader(m_programID, m_geometryID);
	glAttachShader(m_programID, m_fragmentID);
	
	glLinkProgram(m_programID);
	showShaderLogInfo(SHADER_TYPE::PROGRAM, 512);
}

void shaderManager::use()
{
	glUseProgram(m_programID);
}

void shaderManager::clean()
{
	for (auto& buffers : m_uniformBuffers)
	{
		glDeleteBuffers(1, &buffers.second);
	}

	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_geometryID);
	glDetachShader(m_programID, m_fragmentID);
	glDeleteShader(m_vertexID);
	glDeleteShader(m_geometryID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
}

void shaderManager::getShaderSource(SHADER_TYPE type, const char* path)
{
	const char* c;
	std::string code;
	std::ifstream file(path);
	if (!file)
	{
		logger::error("Error reading shader file!");
		return;
	}
	std::stringstream temp;
	temp << file.rdbuf();
	code = temp.str();
	c = code.c_str();

	switch (type)
	{
	case SHADER_TYPE::VERTEX:
		glShaderSource(m_vertexID, 1, &c, 0);
		break;
	case SHADER_TYPE::FRAGMENT:
		glShaderSource(m_fragmentID, 1, &c, 0);
		break;
	case SHADER_TYPE::GEOMETRY:
		glShaderSource(m_geometryID, 1, &c, 0);
		break;
	default:
		break;
	}

	file.close();
}
	

void shaderManager::showShaderLogInfo(SHADER_TYPE type, const int length)
{
	switch (type)
	{
	case SHADER_TYPE::VERTEX:
	{
		int success;
		char* log = new char[length];

		glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_vertexID, length, NULL, log);
			logger::error(std::string(log));
		}
		break;
	}
	case SHADER_TYPE::FRAGMENT:
	{
		int success;
		char* log = new char[length];

		glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_fragmentID, length, NULL, log);
			logger::error(std::string(log));
		}
		break;

	}
	case SHADER_TYPE::GEOMETRY:
	{
		int success;
		char* log = new char[length];

		glGetShaderiv(m_geometryID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_geometryID, length, NULL, log);
			logger::error(std::string(log));
		}
		break;
	}
	case SHADER_TYPE::PROGRAM:
	{
		int success;
		char* log = new char[length];
		glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_programID, length, NULL, log);
			logger::error(std::string(log));
		}
		break;
	}
	default:
		break;
	}
}

void shaderManager::addUniformBuffer(std::string name, GLuint binding, GLintptr offset, GLsizeiptr size)
{
//	GLuint blockIndex = glGetUniformBlockIndex(m_programID, name.c_str());
//	glUniformBlockBinding(m_programID, blockIndex, binding);

	GLuint uboID;
	glGenBuffers(1, &uboID);
	glBindBuffer(GL_UNIFORM_BUFFER, uboID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, binding, uboID, offset, size);
	m_uniformBuffers[name] = uboID;
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}

void shaderManager::fillUniformBuffer(std::string name, GLintptr offset, GLsizeiptr size, const void* data)
{
	if (!m_uniformBuffers[name])
		return;

	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffers[name]);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}

void shaderManager::setInt1(const char* name, int value)
{
	glUniform1i(getUniformLoc(name), value);
}

void shaderManager::setFloat1(const char* name, float val)
{
	glUniform1f(getUniformLoc(name), val);
}

void shaderManager::setFloat2(const char* name, glm::vec2 val)
{
	glUniform2f(getUniformLoc(name), val.x, val.y);
}

void shaderManager::setFloat3(std::string name, glm::vec3 val)
{
	glUniform3f(getUniformLoc(name.c_str()), val.x, val.y, val.z);
}

void shaderManager::setMatrix4f(const char* name, glm::mat4& val)
{
	glUniformMatrix4fv(getUniformLoc(name), 1, false, glm::value_ptr(val));
}

int shaderManager::getUniformLoc(const char* name)
{
	int location = glGetUniformLocation(m_programID, name);
	return location;
}

int shaderManager::getAttribLoc(const char* name)
{
	int location =  glGetAttribLocation(m_programID, name);
	return location;
}

void shaderManager::bindAttribLoc(int index, const char* name)
{
	glBindAttribLocation(m_programID, index, name);
}

std::string shaderManager::getProgramName() const
{
	return m_name;
}