#include "Engine.h"

// Subsystems
#include "Logger.h"
#include "Graphics/Window.h"
#include "Clock.h"
#include "Input/InputSystem.h"
#include "Input/Controllers/EngineInputController.h"
#include "GameStates/GameStateMachine.h"
#include "Graphics/ModelSystem.h"
#include "Graphics/Renderer.h"

Engine* Engine::engine_ = nullptr;

Engine::Engine()
	: logger_(nullptr)
	, window_(nullptr)
	, clock_(nullptr)
	, input_system_(nullptr)
	, input_controller_(nullptr)
	, game_state_machine_(nullptr)
	, model_system_(nullptr)
	, renderer_(nullptr)
{
	engine_ = this;
}

Engine::~Engine()
{
	engine_ = nullptr;
}

bool Engine::init()
{
	// Create logger
	logger_ = newp Logger(this);

	// Create window
	window_ = newp Window(this);
	window_->createWindow("Ymir Engine", 1280, 720);

	// Create clock
	clock_ = newp Clock(this);

	// Create input system
	input_system_ = newp InputSystem;

	// Create input controller
	input_controller_ = newp EngineInputController;

	// Create model system
	model_system_ = newp ModelSystem;
	model_system_->updateInstanceBuffers();

	// Create game state machine 
	game_state_machine_ = newp GameStateMachine;

	// Create renderer
	renderer_ = newp Renderer;

	return true;
}

void Engine::destroy()
{
	delete renderer_;

	delete model_system_;

	delete game_state_machine_;

	delete input_controller_;

	delete input_system_;

	delete clock_;

	delete window_;

	delete logger_;
}

void Engine::run()
{
	while (true)
	{
		update();
	}
}

void Engine::update()
{
	window_->update();
	clock_->update();
	input_controller_->update();
	game_state_machine_->update(clock_->deltaTime());

	model_system_->updateInstanceBuffers();

	if (window_->hasResized())
	{
		renderer_->resize();
	}
	renderer_->render();

	window_->swapBuffers();
}

Engine& Engine::get()
{
	assert(engine_ && "Engine not created!");
	return *engine_;
}