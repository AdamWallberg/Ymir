#include "Logger.h"
#include "Graphics/Window.h"

int main()
{
	Logger* logger = new Logger;
	LoggerLocator::provide(logger);

	Window* window = new Window;
	WindowLocator::provide(window);

	if (window->createWindow("Ymir Engine", 1280, 720))
	{
		while (!window->shouldClose())
		{
			window->update();
			window->swapBuffers();
		}
	}

	WindowLocator::provide(nullptr);
	delete window;

	LoggerLocator::provide(nullptr);
	delete logger;

	return 0;
}