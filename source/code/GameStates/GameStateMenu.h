#pragma once

#include "IGameState.h"

class GameStateMenu : public IGameState
{
public:
	GameStateMenu(GameStateMachine* machine);

	void onCreate() override;
	void onDestroy() override;
	void onEnter() override;
	void onExit() override;
	void update() override;
};