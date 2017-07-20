#pragma once

#include "IGameState.h"

class GameStateGame : public IGameState
{
public:
	GameStateGame(GameStateMachine* machine);

	void onCreate() override;
	void onDestroy() override;
	void onEnter() override;
	void onExit() override;
	void update() override;
};