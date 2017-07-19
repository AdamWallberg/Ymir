#include "Graphics/Window.h"
#include <assert.h>

int main()
{
	Window* window = new Window;
	
	if (!window->createWindow("Ymir Engine", 1280, 720))
	{
		assert(false);
	}
	else
	{
		while (!window->shouldClose())
		{
			window->update();
			window->swapBuffers();
		}
	}

	delete window;
	return 0;
}