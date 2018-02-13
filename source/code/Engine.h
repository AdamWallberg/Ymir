#pragma once

#include "Core.h"

class Logger;
class Window;
class Clock;
class InputSystem;
class EngineInputController;
class GameStateMachine;
class ModelSystem;
class Renderer;

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void destroy();
	void run();

private:
	void update();

	Logger* logger_;
	Window* window_;
	Clock* clock_;
	InputSystem* input_system_;
	EngineInputController* input_controller_;
	GameStateMachine* game_state_machine_;
	ModelSystem* model_system_;
	Renderer* renderer_;
};