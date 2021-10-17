#pragma once
#include "GL/glew.h"
#include "depthMap.h"
#include "shaderManager.h"
#include "light.h"

namespace corona
{
	class shadowMap
	{
	private:
		GLuint m_fboID;
		static const GLuint SHADOW_WIDTH = 1024;
		static const GLuint SHADOW_HEIGHT = 1024;
		depthMap* m_depthMap;
		shaderManager* m_program;
		dirLight* m_directional;
		const float NEAR_PLANE = 1.0f;
		const float FAR_PLANE = 7.5f;
		glm::mat4 m_lightSpace;
	public:
		shadowMap(shaderManager* program, dirLight* source);
		bool loadDepthMap();
		void drawToDepthMap();
		void setModelSpace(glm::mat4& model);
		void unbindFbo();
		void bindDepthMap(shaderManager& program, int index);
		void clean();
		glm::mat4& getLightSpace();
	};

}
