#include "GameStateMachine.h"

#include "Core.h"
#include "GameStateMenu.h"
#include "GameStateGame.h"
#include "Graphics/Window.h"
#include "Graphics/GL.h"

GameStateMachine::GameStateMachine(Engine* engine)
	: ISubSystem(engine)
	, current_state_(nullptr)
	, next_state_(nullptr)
	, loading_(false)
	, loading_thread_(false)
{
	game_states_["menu"] = newp GameStateMenu(this);
	game_states_["game"] = newp GameStateGame(this);

	current_state_ = game_states_["menu"];
	current_state_->onCreate();
	current_state_->onEnter();
}

GameStateMachine::~GameStateMachine()
{
	current_state_->onExit();
	current_state_->onDestroy();

	for (auto& it : game_states_)
	{
		delete it.second;
	}
}

void GameStateMachine::update(float delta_time)
{
	if (loading_thread_)
	{
		if (!loading_)
		{
			loading_thread_->join();
			delete loading_thread_;
			loading_thread_ = nullptr;

			next_state_->onEnter();

			current_state_ = next_state_;
			next_state_ = nullptr;
		}
		else
		{
			// We are loading, update loading screen
		}
	}
	else
	{
		if (current_state_)
		{
			current_state_->update();
		}
	}
}

void GameStateMachine::changeState(const char * state)
{
	if (loading_ || loading_thread_ || next_state_)
	{
		return;
	}

	next_state_ = game_states_[state];

	if (!next_state_)
	{
		return;
	}

	current_state_->onExit();

	loading_ = true;
	loading_thread_ = newp std::thread(unloadCurrentStateAndLoadNext, this);
}

void GameStateMachine::unloadCurrentStateAndLoadNext(GameStateMachine* machine)
{
	glfwMakeContextCurrent(WINDOW->getThreadContext());
	machine->current_state_->onDestroy();
	machine->next_state_->onCreate();
	machine->loading_ = false;
}