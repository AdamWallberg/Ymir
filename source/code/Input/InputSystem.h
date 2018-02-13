#pragma once

#include "ISubSystem.h"

#include <map>

#include "Mappings/KeyboardMapping.h"

class InputSystem : public ISubSystem
{
public:
	InputSystem(Engine* engine);
	IInputMapping* getKeyboardMapping(const char key);
private:
	std::map<char, KeyboardMapping> mappings_;
};
