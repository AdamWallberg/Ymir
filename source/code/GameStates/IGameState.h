#pragma once

#include "GameStateMachine.h"

class IGameState
{
public:
	IGameState(GameStateMachine* machine)
		: machine_(machine)
	{
	}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void update() = 0;
protected:
	GameStateMachine* machine_;
};