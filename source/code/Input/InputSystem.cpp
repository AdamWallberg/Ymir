#include "InputSystem.h"
#include "Mappings/KeyboardMapping.h"

InputSystem::InputSystem()
{

}

IInputMapping* InputSystem::getKeyboardMapping(const char key)
{
	if (!mappings_.count(key))
	{
		mappings_[key] = KeyboardMapping(key);
	}

	return &mappings_[key];
}

SERVICE_LOCATOR_SOURCE(InputSystem, InputSystemLocator)