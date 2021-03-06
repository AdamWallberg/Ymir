#pragma once

#include "ISubSystem.h"

#include <map>
#include <thread>

class IGameState;

class GameStateMachine : public ISubSystem
{
public:
	GameStateMachine(Engine* engine);
	~GameStateMachine();
	void update(float delta_time);
	void changeState(const char* state);
private:
	std::map<std::string, IGameState*> game_states_;
	IGameState* current_state_;
	IGameState* next_state_;

	bool loading_;
	std::thread* loading_thread_;

	static void unloadCurrentStateAndLoadNext(GameStateMachine* machine);
};