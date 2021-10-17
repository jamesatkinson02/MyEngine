#include "display.h"
#include <thread>

using namespace corona;

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;


int main(int argc, char** argv)
{
	display::getInstance()->init("untitled", WINDOW_WIDTH, WINDOW_HEIGHT);
	display::getInstance()->enableVSync();
	
	int frames = 0, fps = 0;
	float deltaTime = 0.0f, lastTime = 0.0f;

	while (display::getInstance()->isRunning())
	{
		float currentTime = display::getInstance()->getCurrentTime();
		deltaTime = (currentTime - lastTime);
	
		frames++;

		if (deltaTime >= 1.0f / display::getInstance()->getRefreshRate())
		{
			display::getInstance()->draw();
			display::getInstance()->input(deltaTime);
			display::getInstance()->update(deltaTime);

			lastTime = currentTime;
			frames = 0;

		}


	}
	display::getInstance()->clean();
	return 0;
}