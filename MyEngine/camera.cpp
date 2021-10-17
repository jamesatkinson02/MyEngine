#include "camera.h"
#include "display.h"

namespace corona
{
	camera::camera(vec3& pos, vec3& target, vec3& up) : m_pos{ pos }, m_target{ target }, m_up{ up }, m_view{ glm::mat4(1.0f) }, m_pitch{ 0.0f }, m_yaw{ -90.0f }, m_lastX{ 1280 / 2 }, m_lastY{ 720 / 2 }, m_firstMouse{ true }, m_fov{ 45.0f }
	{

	}

	void camera::input(GLFWwindow* window, float deltaTime)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_pos += m_target * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_pos -= m_target * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			vec3 right = normalize(cross(m_up, m_target));
			m_pos += right * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			vec3 right = normalize(cross(m_up, m_target));
			m_pos -= right * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			m_pos += m_up * deltaTime;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			m_pos -= m_up * deltaTime;
		}
	}

	void camera::update()
	{
		if (m_fov <= 10.0f)
			m_fov = 10.0f;
		else if (m_fov >= 90.0f)
			m_fov = 90.0f;

		using namespace corona;

		m_perspective = perspective(glm::radians(m_fov), (float)(display::getInstance()->getWindowWidth()) / (float)(display::getInstance()->getWindowHeight()), 0.1f, 100.0f);

		m_view = lookAt(m_pos, m_pos + m_target, m_up);
	}

	void camera::rotate(GLFWwindow* window, double& xpos, double& ypos)
	{

		if (m_firstMouse)
		{
			m_firstMouse = false;
			m_lastX = xpos;
			m_lastY = ypos;

		}

		double xoffs = xpos - m_lastX;
		double yoffs = m_lastY - ypos;


		m_lastX = xpos;
		m_lastY = ypos;

		xoffs *= m_sensitivity;
		yoffs *= m_sensitivity;

		m_yaw += xoffs;
		m_pitch += yoffs;

		if (m_pitch >= 89.0f)
		{
			m_pitch = 89.0f;
		}

		else if (m_pitch <= -89.0f)
		{
			m_pitch = -89.0f;
		}

		vec3 direction;
		direction.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
		direction.y = sinf(glm::radians(m_pitch));
		direction.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));

		m_target = normalize(direction);
	}

	void camera::scroll(GLFWwindow* window, double& xoffs, double& yoffs)
	{
		m_fov -= yoffs;
	}

	vec3& camera::getPos()
	{
		return m_pos;
	}

	vec3 camera::getTarget()
	{
		return m_target;
	}

	mat4& camera::getView()
	{
		return m_view;
	}

	mat4& camera::getPerspective()
	{
		return m_perspective;
	}

}

