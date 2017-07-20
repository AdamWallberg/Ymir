#include "EngineInputController.h"
#include "../InputAction.h"
#include "../InputSystem.h"
#include "Graphics/GL.h"

EngineInputController::EngineInputController()
{
	InputSystem* input_system = InputSystemLocator::get();
	InputAction* current_action = nullptr;

#define CREATE_ACTION(NAME) \
	current_action = &actions_[NAME]; \
	*current_action = InputAction()

#define ADD_MAPPING(KEY, SCALE) \
	current_action->addMapping(input_system->getKeyboardMapping(KEY), SCALE)

	CREATE_ACTION("move_forward");
	ADD_MAPPING('W', 1.0f);
	ADD_MAPPING('S', -1.0f);

	CREATE_ACTION("move_sideways");
	ADD_MAPPING('A', -1.0f);
	ADD_MAPPING('D', 1.0f);

	CREATE_ACTION("move_up");
	ADD_MAPPING((char)GLFW_KEY_SPACE, 1.0f);
	ADD_MAPPING((char)GLFW_KEY_LEFT_CONTROL, -1.0f);

#undef CREATE_ACTION
#undef ADD_MAPPING
}

void EngineInputController::update()
{
	for (auto& it : actions_)
	{
		it.second.update();
	}
}

SERVICE_LOCATOR_SOURCE(EngineInputController, InputController)