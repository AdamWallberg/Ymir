#include "GameStateMenu.h"
#include "Logger.h"

GameStateMenu::GameStateMenu(GameStateMachine* machine)
	: IGameState(machine)
{
}

void GameStateMenu::onCreate()
{
	LOG("Menu: on create", Logger::FLAG_GAME_STATE);
}

void GameStateMenu::onDestroy()
{
	LOG("Menu: on destroy", Logger::FLAG_GAME_STATE);
}

void GameStateMenu::onEnter()
{
	LOG("Menu: on enter", Logger::FLAG_GAME_STATE);
}

void GameStateMenu::onExit()
{
	LOG("Menu: on exit", Logger::FLAG_GAME_STATE);
}

void GameStateMenu::update()
{
	machine_->changeState("game");
}