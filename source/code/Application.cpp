#include "Application.h"
#include "Core.h"

Application::Application()
	: logger_(nullptr)
	, window_(nullptr)
	, input_system_(nullptr)
	, input_controller_(nullptr)
	, game_state_machine_(nullptr)
{
}

Application::~Application()
{
}

bool Application::init()
{
	// Create logger
	logger_ = newp Logger;
	LoggerLocator::provide(logger_);
#ifdef NDEBUG
	logger_->setFlag(Logger::FLAG_GAME_STATE, false);
#endif

	// Create window
	window_ = newp Window;
	WindowLocator::provide(window_);
	window_->createWindow("Ymir Engine", 1280, 720);

	// Create input system
	input_system_ = newp InputSystem;
	InputSystemLocator::provide(input_system_);

	// Create input controller
	input_controller_ = newp EngineInputController;
	InputController::provide(input_controller_);

	// Create game state machine 
	game_state_machine_ = newp GameStateMachine;
	GameStateMachineLocator::provide(game_state_machine_);

	return true;
}

void Application::destroy()
{
	delete game_state_machine_;
	GameStateMachineLocator::provide(nullptr);

	delete input_controller_;
	InputController::provide(nullptr);

	delete input_system_;
	InputSystemLocator::provide(nullptr);

	delete window_;
	WindowLocator::provide(nullptr);

	delete logger_;
	LoggerLocator::provide(nullptr);
}

void Application::run()
{
	while (!window_->shouldClose())
	{
		update();
	}
}

void Application::update()
{
	window_->update();
	input_controller_->update();
	game_state_machine_->update(0.f);

	window_->swapBuffers();
}

