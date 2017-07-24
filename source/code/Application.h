#pragma once

#include "Logger.h"
#include "Graphics/Window.h"
#include "Clock.h"
#include "Input/InputSystem.h"
#include "Input/Controllers/EngineInputController.h"
#include "GameStates/GameStateMachine.h"
#include "Graphics/ModelSystem.h"
#include "Graphics/Renderer.h"

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

	float frame_timer_;
	float second_timer_;

	Logger* logger_;
	Window* window_;
	Clock* clock_;
	InputSystem* input_system_;
	EngineInputController* input_controller_;
	GameStateMachine* game_state_machine_;
	ModelSystem* model_system_;
	Renderer* renderer_;
};