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

#define ENGINE			Engine::get()
#define LOGGER			ENGINE.logger_
#define CLOCK			ENGINE.clock_
#define INPUT_SYSTEM	ENGINE.input_system_
#define INPUT			ENGINE.input_controller_
#define MODEL_SYSTEM	ENGINE.model_system_
#define WINDOW			ENGINE.window_
#define RENDERER		ENGINE.renderer_

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void destroy();
	void run();

	Logger* logger_;
	Window* window_;
	Clock* clock_;
	InputSystem* input_system_;
	EngineInputController* input_controller_;
	GameStateMachine* game_state_machine_;
	ModelSystem* model_system_;
	Renderer* renderer_;

	static Engine& get();

private:
	void update();

	static Engine* engine_;
};