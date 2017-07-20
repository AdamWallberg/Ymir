#pragma once

class IInputMapping
{
public:
	virtual ~IInputMapping() {}
	virtual bool getPressed() const = 0;
	virtual bool getHeld() const = 0;
	virtual bool getReleased() const = 0;
	virtual float getValue() const = 0;

	virtual void update() = 0;
};