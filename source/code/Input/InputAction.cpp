#include "InputAction.h"
#include "Math/ymath.h"

InputAction::InputAction()
	: pressed_(false)
	, held_(false)
	, released_(false)
	, value_(false)
{
}

void InputAction::addMapping(IInputMapping* mapping, const float scale)
{
	mappings_.push_back(std::pair<IInputMapping*, float>(mapping, scale));
}

void InputAction::update()
{
	IInputMapping* strongest_signal = nullptr;
	float highest_value = 0.f;

	for (auto& it : mappings_)
	{
		IInputMapping* mapping = it.first;
		const float& scale = it.second;
		mapping->update();

		const float mapping_value = mapping->getValue() * scale;
		if (pm::abs(mapping_value) >= pm::abs(highest_value))
		{
			strongest_signal = mapping;
			highest_value = mapping_value;
		}
	}

	if (strongest_signal)
	{
		pressed_ = strongest_signal->getPressed();
		held_ = strongest_signal->getHeld();
		released_ = strongest_signal->getReleased();
		value_ = highest_value;
	}
	else
	{
		pressed_ = false;
		held_ = false;
		released_ = false;
		value_ = 0.f;
	}
}