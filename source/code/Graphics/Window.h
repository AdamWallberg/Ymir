#pragma once

#include "ISubSystem.h"
#include "Types.h"

struct GLFWwindow;

class Window : public ISubSystem
{
public:
	Window(Engine* engine);
	~Window();
	bool createWindow(const char* title, uint width, uint height, bool fullscreen = false, bool vsync = false);
	void update();
	void swapBuffers();
	bool shouldClose() const { return should_close_; }
	const std::string& getTitle() const { return title_; }
	void setTitle(const std::string& title);
	uint getWidth() const { return width_; }
	uint getHeight() const { return height_; }
	GLFWwindow* getWindow() const { return window_; }
	GLFWwindow* getThreadContext() const { return thread_context_; }
	bool hasResized() const { return has_resized_; }
private:
	GLFWwindow* window_;
	GLFWwindow* thread_context_;
	uint width_;
	uint height_;
	std::string title_;

	bool should_close_;
	bool has_resized_;

	static void onWindowResize(GLFWwindow* window, int width, int height);
	static void onFileDropped(GLFWwindow* window, int num_files, const char** directories);
};