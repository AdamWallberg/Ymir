#include "Graphics/Window.h"

int main()
{
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
	return 0;
}