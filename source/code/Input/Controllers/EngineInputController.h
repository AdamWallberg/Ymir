#pragma once

#include <map>
#include "Input/InputAction.h"

class EngineInputController
{
public:
	EngineInputController();
	void update();
	bool getPressed(const std::string& action_name) { return actions_[action_name].getPressed(); }
	bool getHeld(const std::string& action_name) { return actions_[action_name].getHeld(); }
	bool getReleased(const std::string& action_name) { return actions_[action_name].getReleased(); }
	float getValue(const std::string& action_name) { return actions_[action_name].getValue(); }
private:
	std::map<std::string, InputAction> actions_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(EngineInputController, InputController)