#include "display.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui\imgui_impl_opengl3.h"
using namespace corona;

void cursor_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int action, int scancode, int mods);
void scroll_callback(GLFWwindow* window, double xoffs, double yoffs);

display* display::m_instance = 0;

display* display::getInstance()
{
	if (!m_instance)
	{
		m_instance = new display();
	}
	return m_instance;
}

int display::init(const char* title, int w, int h)
{
	logger::trace("Engine Initialising...");

	if (!glfwInit())
	{
		logger::error("Couldn't initialise glfw 3!");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	
	m_window = glfwCreateWindow(w, h, title, nullptr, nullptr);
	if (!m_window)
	{
		logger::error("Couldn't create glfw window!");
		return 1;
	}
	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
	{
		logger::error("could not initialise glew-32!");
		return 1;
	}


	glfwSetErrorCallback([](int error, const char* description) 
	{
			logger::error(description);
	});

	m_isRunning = true;

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	loadScene();

	return 0;


}

void display::loadScene()
{
	logger::trace("Loading scene...");

	m_sun = new dirLight(glm::vec3(0.2f, -0.4f, -0.8f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
	
	m_shaders = new shaderManager("model", "shaders/lightingVert.vert", "shaders/lighting.frag", "shaders/explode.geom");

	m_shaders->use();

	m_shaders->setFloat3("color", vec3(1.0f, 0.7f, 0.4f));

	//m_normalShader = new shaderManager("normals", "shaders/visualNormalVert.vert", "shaders/basicFrag.frag", "shaders/visualNormal.geom");

	m_shaders->addUniformBuffer("matrices", 0, 0, 2 * sizeof(glm::mat4));

	m_quadShader = new shaderManager("quad", "shaders/basicVert.vert", "shaders/basicFrag.frag");

	m_quadShader->addUniformBuffer("matrices", 0, 0, 2 * sizeof(glm::mat4));


	glm::vec3 pos(0.0f, 0.0f, 5.0f);
	glm::vec3 target(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	m_cam = new camera(pos, target, up);

	m_bunny = new model(vec3(0.0f), "bunny");
	m_bunny->loadModel();

	m_brickWall = new model(vec3(0.0f, -1.0f, 0.0f), "quad");
	m_brickWall->loadModel();

	for (int x = -20; x < 22; x += 2)
	{
		for (int z = 0; z > -42; z--)
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.25f, 0.525f, z * 0.25f));
			translation = glm::rotate(translation, glm::radians((float)x + z), glm::vec3(0.0f, 1.0f, 0.0f));
			m_translations.push_back(translation);
		}
	}

	m_quad = new quad(glm::vec3(0.0f), m_translations);

	m_quad->loadTexture("assets/textures/grass_diff.png", 0, true);

	m_tree = new model(vec3(0.0f), "Tree");
	m_tree->loadModel();
	//m_font = new font(18);

	m_skyBox = new skybox();
}

void display::update(float deltaTime)
{
	/* will this ever be used???? */
}

void display::input(float deltaTime)
{
	glfwPollEvents();
	
	if (glfwWindowShouldClose(m_window)) 
		m_isRunning = false;


	m_cam->input(m_window, deltaTime);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

}

void display::drawScene()
{
	glViewport(0, 0, getWindowWidth(), getWindowHeight());
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	m_cam->update();

	m_shaders->use();

	m_shaders->setFloat3("camPos", m_cam->getPos());

	m_shaders->setFloat1("time", (float)glfwGetTime());

	m_sun->draw(*m_shaders);

	//m_shaders->setFloat3("color", vec3(1.0f, 0.7f, 0.4f));
	
	

	m_bunny->identity();
	m_bunny->translate(vec3(0.0f, 0.0f, -5.0f));
	m_bunny->draw(*m_shaders);

	m_bunny->identity();
	m_bunny->translate(vec3(2.0f, 0.0f, -5.0f));
	m_bunny->draw(*m_shaders);

	
	m_sun->draw(*m_shaders);
	
	m_tree->identity();
	m_tree->translate(vec3(9.0f, 0.0f, -2.0f));
	m_tree->draw(*m_shaders);


	glDisable(GL_CULL_FACE);

	m_brickWall->identity();
	m_brickWall->translate(vec3(0.0f, 0.025f, -5.0f));
	m_brickWall->rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_brickWall->scale(vec3(10.0f, 10.0f, 1.0f));

	m_brickWall->draw(*m_shaders);

	m_shaders->fillUniformBuffer("matrices", 0, sizeof(glm::mat4), value_ptr(m_cam->getPerspective()));
	m_shaders->fillUniformBuffer("matrices", sizeof(glm::mat4), sizeof(glm::mat4), value_ptr(m_cam->getView()));


	m_quadShader->use();

	m_quad->drawInstances(*m_quadShader, m_translations.size());

	m_quadShader->fillUniformBuffer("matrices", 0, sizeof(glm::mat4), value_ptr(m_cam->getPerspective()));
	m_quadShader->fillUniformBuffer("matrices", sizeof(glm::mat4), sizeof(glm::mat4), value_ptr(m_cam->getView()));

	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_skyBox->draw(*m_cam);

}

void display::draw()
{
	drawScene();
	glfwSwapBuffers(m_window);

}

void display::clean()
{
	logger::trace("Shutting down...");

	m_skyBox->clean();
	//m_font->clean();
	m_quad->clean();
	m_brickWall->clean();
	m_bunny->clean();
	m_quadShader->clean();
	m_shaders->clean();

	glfwDestroyWindow(m_window);
	delete m_skyBox, m_brickWall, m_bunny, m_quad, m_shaders, m_quadShader, m_cam, m_window, m_instance;
}

bool& display::isRunning()
{
	return m_isRunning;
}

int display::getWindowWidth() const
{
	int width;
	glfwGetWindowSize(m_window, &width, NULL);
	return width;
}

int display::getWindowHeight() const
{
	int height;
	glfwGetWindowSize(m_window, NULL, &height);
	return height;
}

void display::enableVSync()
{
	glfwSwapInterval(1);
}

int display::getRefreshRate()
{
	return glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
}

GLFWwindow* display::getWindow()
{
	return m_window;
}

camera* display::getCamera()
{
	return m_cam;
}

float display::getCurrentTime()
{
	return (float)glfwGetTime();
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	display::getInstance()->getCamera()->rotate(window, xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int action, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		display::getInstance()->isRunning() = false;
	}
}

void scroll_callback(GLFWwindow* window, double xoffs, double yoffs)
{
	display::getInstance()->getCamera()->scroll(window, xoffs, yoffs);
}



