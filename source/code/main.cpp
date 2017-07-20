#include "Application.h"
#include "Core.h"
int main()
{
#ifdef DEBUG 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Application* application = newp Application;
	application->init();
	application->run();
	application->destroy();

	delete application;

	return 0;
}