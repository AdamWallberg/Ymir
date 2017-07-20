#pragma once

#include "IInputMapping.h"
#include "Types.h"

class Window;

class KeyboardMapping : public IInputMapping
{
public:
	KeyboardMapping(uint key);
	bool getPressed() const override { return pressed_; }
	bool getHeld() const override { return held_; }
	bool getReleased() const override { return released_; }
	float getValue() const override { return FLOAT_S(held_); }
	void update() override;
private:
	Window* window_;
	uint key_;
	bool pressed_;
	bool held_;
	bool released_;
};