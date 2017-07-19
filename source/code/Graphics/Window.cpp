#include "Window.h"
#include "GL.h"

Window::Window()
	: window_(nullptr)
	, thread_context_(nullptr)
	, width_(0)
	, height_(0)
	, title_("")
	, should_close_(false)
{
}

Window::~Window()
{

}

bool Window::createWindow(const char* title, uint width, uint height, bool fullscreen, bool vsync)
{
	width_ = width;
	height_ = height;
	title_ = title;

	// Init GLFW
	if (!glfwInit())
	{
		return false;
	}

	// Setup window flags
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window context
	glfwWindowHint(GLFW_VISIBLE, false);
	thread_context_ = glfwCreateWindow(1, 1, "thread_context", nullptr, nullptr);
	if (!thread_context_)
	{
		glfwTerminate();
		return false;
	}
	glfwWindowHint(GLFW_VISIBLE, true);

	// Create window
	GLFWmonitor* monitor = nullptr;
	if (fullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);
		width = vid_mode->width;
		height = vid_mode->height;
	}

	window_ = glfwCreateWindow(width, height, title, monitor, thread_context_);
	if (!window_)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window_);

	// Set vsync
	glfwSwapInterval(vsync);

	// Init glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	return true;
}

void Window::update()
{
	glfwPollEvents();
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE))
		should_close_ = true;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window_);
}

SERVICE_LOCATOR_SOURCE(Window, WindowLocator)