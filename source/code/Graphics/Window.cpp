#include "Window.h"
#include "GL.h"
#include "ModelSystem.h"

Window::Window(Engine* engine)
	: ISubSystem(engine)
	, window_(nullptr)
	, thread_context_(nullptr)
	, width_(0)
	, height_(0)
	, title_("")
	, should_close_(false)
	, has_resized_(false)
{
}

Window::~Window()
{
	glfwTerminate();
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

	// Set resize callback
	glfwSetWindowSizeCallback(window_, onWindowResize);

	// Set drop callback
	glfwSetDropCallback(window_, onFileDropped);

	return true;
}

void Window::update()
{
	glfwPollEvents();
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window_) == 1)
		should_close_ = true;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window_);
	has_resized_ = false;
}

void Window::setTitle(const std::string& title)
{
	glfwSetWindowTitle(window_, title.c_str());
}


void Window::onWindowResize(GLFWwindow* window, int width, int height)
{
	Window* w = WINDOW;
	w->width_ = width;
	w->height_ = height;
	w->has_resized_ = true;
}

void Window::onFileDropped(GLFWwindow* window, int num_files, const char** directories)
{
	// TODO: Handle this using a file system or similar
	for (int i = 0; i < num_files; i++)
	{
		std::string path = directories[i];
		std::string extension = path.substr(path.find_last_of(".") + 1);

		// Convert all backslashes to forward slashes
		size_t pos = 0;
		while ((pos = path.find("\\", pos)) != std::string::npos)
		{
			path.replace(pos, 1, "/");
			pos += 1;
		}

		// Handle loading of obj files
		if (extension == "obj")
		{
			MODEL_SYSTEM->loadModel(path);
		}
	}
}