#pragma once

#include "ISubSystem.h"

class Window;

class Clock : public ISubSystem
{
public:
	Clock(Engine* engine);
	void update();
	float deltaTime() const { return delta_time_; }
	float time() const { return time_; }
private:
	float delta_time_;
	float time_;
	double last_time_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(Clock, ClockLocator)