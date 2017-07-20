#pragma once

#include "Logger.h"
#include "Graphics/Window.h"
#include "GameStates/GameStateMachine.h"

class Application
{
public:
	Application();
	~Application();
	bool init();
	void destroy();
	void run();
private:
	void update();

	Logger* logger_;
	Window* window_;
	GameStateMachine* game_state_machine_;
};