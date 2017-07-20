#pragma once

#include "Mappings/IInputMapping.h"
#include <vector>

class InputAction
{
public:
	InputAction();

	void addMapping(IInputMapping* mapping, const float scale);

	bool getPressed() const { return pressed_; }
	bool getHeld() const { return held_; }
	bool getReleased() const { return released_; }
	float getValue() const { return value_; }

	void update();
private:
	std::vector<std::pair<IInputMapping*, float>> mappings_;

	bool pressed_;
	bool held_;
	bool released_;
	float value_;
};