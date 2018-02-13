#include "Clock.h"
#include "Graphics/GL.h"
#include "Types.h"

Clock::Clock(Engine* engine)
	: ISubSystem(engine)
	, delta_time_(0.0f)
	, time_(0.0f)
	, last_time_(0.0)
{
}

void Clock::update()
{
	double current_time = glfwGetTime();
	delta_time_ = FLOAT_S(current_time - last_time_);
	last_time_ = current_time;
	const float delta_cap = 1.0f / 15.0f;
	if (delta_time_ >= delta_cap)
	{
		delta_time_ = delta_cap;
	}
	time_ += delta_time_;
}

SERVICE_LOCATOR_SOURCE(Clock, ClockLocator)