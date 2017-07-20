#include "KeyboardMapping.h"
#include "Graphics/Window.h"
#include "Graphics/GL.h"

KeyboardMapping::KeyboardMapping(uint key)
	: IInputMapping()
	, window_(nullptr)
	, key_(key)
	, pressed_(false)
	, held_(false)
	, released_(false)
{
	window_ = WindowLocator::get();
}

void KeyboardMapping::update()
{
	int state = glfwGetKey(window_->getWindow(), key_);

	if (state == GLFW_PRESS)
	{
		if (!held_)
		{
			pressed_ = true;
			held_ = true;
			released_ = false;
		}
		else
		{
			pressed_ = false;
		}
	}
	else if (state == GLFW_RELEASE)
	{
		if (held_)
		{
			held_ = false;
			released_ = true;
			pressed_ = false;
		}
		else
		{
			released_ = false;
		}
	}
}
