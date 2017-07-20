#include "Application.h"
#include "Core.h"

int main()
{
	Application* application = newp Application;
	application->init();
	application->run();
	
	delete application;
	return 0;
}