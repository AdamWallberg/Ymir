#pragma once

#include "IGameState.h"

class Model;

class GameStateGame : public IGameState
{
public:
	GameStateGame(GameStateMachine* machine);

	void onCreate() override;
	void onDestroy() override;
	void onEnter() override;
	void onExit() override;
	void update() override;

private:
	Model* models_[3];
};