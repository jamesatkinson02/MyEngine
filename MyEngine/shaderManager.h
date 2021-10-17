#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "logger.h"
#include <map>

namespace corona
{
	class shaderManager
	{
	private:
		enum class SHADER_TYPE
		{
			VERTEX,
			FRAGMENT,
			GEOMETRY,
			PROGRAM
		};
		int m_vertexID, m_fragmentID, m_geometryID, m_programID;
		void getShaderSource(SHADER_TYPE type, const char* path);
		void showShaderLogInfo(SHADER_TYPE type, const int length);
		std::map<std::string, GLuint> m_uniformBuffers;
		std::string m_name;
	public:
		shaderManager(std::string name, const char* vertexPath, const char* fragmentPath, const char* geoPath=0);
		void use();
		void clean();
		int getAttribLoc(const char* name);
		void bindAttribLoc(int index, const char* name);
		int getUniformLoc(const char* name);
		void addUniformBuffer(std::string name ,GLuint binding, GLintptr offset, GLsizeiptr size);
		void fillUniformBuffer(std::string name, GLintptr offset, GLsizeiptr size, const void* data);
		void setMatrix4f(const char* name, glm::mat4& val);
		void setFloat1(const char* name, float val);
		void setFloat2(const char* name, glm::vec2 val);
		void setFloat3(std::string name, glm::vec3 val);
		void setInt1(const char* name, int val);
		std::string getProgramName() const;
	};
}
