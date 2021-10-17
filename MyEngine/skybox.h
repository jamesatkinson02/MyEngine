#pragma once
#include <vector>
#include "texture.h"
#include "camera.h"

namespace corona
{
	class skybox
	{
	private:
		cubeMap* m_day;
		cubeMap* m_night;
		GLuint m_vaoID, m_vboID;
		int m_count;
		shaderManager* m_skyboxShader;
		float m_factor;
		bool m_isDay;
	public:
		skybox();
		void loadSkyBox();
		void update();
		void draw(camera& cam);
		void clean();
	};

}
