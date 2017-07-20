#include "GameStateGame.h"
#include "Logger.h"

GameStateGame::GameStateGame(GameStateMachine* machine)
	: IGameState(machine)
{
}

void GameStateGame::onCreate()
{
	LOG("Game: on create", Logger::FLAG_GAME_STATE);
}

void GameStateGame::onDestroy()
{
	LOG("Game: on destroy", Logger::FLAG_GAME_STATE);
}

void GameStateGame::onEnter()
{
	LOG("Game: on enter", Logger::FLAG_GAME_STATE);
}

void GameStateGame::onExit()
{
	LOG("Game: on exit", Logger::FLAG_GAME_STATE);
}

void GameStateGame::update()
{
}