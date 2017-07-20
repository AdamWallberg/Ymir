#pragma once

#include <map>

#include "Mappings/KeyboardMapping.h"

class InputSystem
{
public:
	InputSystem();
	IInputMapping* getKeyboardMapping(const char key);
private:
	std::map<char, KeyboardMapping> mappings_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(InputSystem, InputSystemLocator)