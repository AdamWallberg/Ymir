#pragma once

#include "Types.h"

struct GLFWwindow;

class Window
{
public:
	Window();
	~Window();
	bool createWindow(const char* title, uint width, uint height, bool fullscreen = false, bool vsync = false);
	void update();
	void swapBuffers();
	bool shouldClose() const { return should_close_; }

	GLFWwindow* getWindow() const { return window_; }
	GLFWwindow* getThreadContext() const { return thread_context_; }
private:
	GLFWwindow* window_;
	GLFWwindow* thread_context_;
	uint width_;
	uint height_;
	std::string title_;

	bool should_close_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(Window, WindowLocator)