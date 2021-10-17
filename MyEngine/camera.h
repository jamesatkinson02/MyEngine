#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "shaderManager.h"

using namespace glm; 

namespace corona
{
	class camera
	{
	private:
		vec3 m_pos, m_target, m_up;
		mat4 m_view, m_perspective;
		float m_pitch, m_yaw;
		float m_lastX, m_lastY;
		float m_fov;
		bool m_firstMouse;
		const float m_sensitivity = 0.07f;
	public:
		camera(vec3& pos, vec3& target, vec3& up);
		void input(GLFWwindow* window, float deltaTime);
		void update();
		void rotate(GLFWwindow* window, double& xpos, double& ypos);
		void scroll(GLFWwindow* window, double& xoffs, double& yoffs);
		vec3& getPos();
		vec3 getTarget();
		mat4& getView();
		mat4& getPerspective();

};
}