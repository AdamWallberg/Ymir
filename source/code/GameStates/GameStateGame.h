#pragma once

#include "IGameState.h"
#include "Types.h"
#include "Camera/FreecamController.h"
#include <vector>

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
	// Model test case
	static const uint NUM_MODELS = 12;
	std::vector<Model*> models_;
	Model* selected_model_;

	// Camera test case
	FreecamController camera_;
};