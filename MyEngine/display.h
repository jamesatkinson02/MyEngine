#pragma once

#include "shaderManager.h"
#include "camera.h"
#include <iostream>
#include "model.h"
#include "material.h"
#include "light.h"
#include "skybox.h"
#include "logger.h"
#include "shadowMap.h"
#include "quad.h"


using namespace std;

namespace corona
{
	class display
	{
	private:
		GLFWwindow* m_window;
		bool m_isRunning;
		static display* m_instance;
		shaderManager* m_shaders;
		shaderManager* m_quadShader;
		camera* m_cam;
		model* m_bunny;
		dirLight* m_sun;
		skybox* m_skyBox;
		model* m_brickWall;
		model* m_tree;
		quad* m_quad;
		std::vector<glm::mat4> m_translations;
	public:
		static display* getInstance();
		int init(const char* title, int w, int h);
		void loadScene();
		void input(float deltaTime);
		void update(float deltaTime);
		void draw();
		void drawScene();
		void clean();
		bool& isRunning();
		int getWindowWidth() const;
		int getWindowHeight() const;
		GLFWwindow* getWindow();
		camera* getCamera();
		float getCurrentTime();
		void enableVSync();
		int getRefreshRate();
	};

}
