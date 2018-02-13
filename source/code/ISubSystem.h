#pragma once

#include "Engine.h"

class ISubSystem
{
public:
	ISubSystem(Engine* engine)
		: engine_(engine)
	{
	}

	virtual ~ISubSystem()
	{
	}

private:
	Engine* engine_;
};