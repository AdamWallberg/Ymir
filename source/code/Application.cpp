#include "Application.h"
#include "Core.h"

Application::Application()
	: logger_(nullptr)
	, window_(nullptr)
	, game_state_machine_(nullptr)
{
}

Application::~Application()
{
}

bool Application::init()
{
	logger_ = newp Logger;
	LoggerLocator::provide(logger_);
#ifdef NDEBUG
	logger_->setFlag(Logger::FLAG_GAME_STATE, false);
#endif

	window_ = newp Window;
	WindowLocator::provide(window_);
	window_->createWindow("Ymir Engine", 1280, 720);

	game_state_machine_ = newp GameStateMachine;
	GameStateMachineLocator::provide(game_state_machine_);

	return true;
}

void Application::destroy()
{
	delete game_state_machine_;
	GameStateMachineLocator::provide(nullptr);

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
	game_state_machine_->update(0.f);

	window_->swapBuffers();
}

