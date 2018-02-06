#include "GameStateGame.h"
#include "Logger.h"
#include "Graphics/ModelSystem.h"
#include "Clock.h"

GameStateGame::GameStateGame(GameStateMachine* machine)
	: IGameState(machine)
{
	models_[0] = ModelSystemLocator::get()->loadModel("test/box.obj");
	models_[1] = ModelSystemLocator::get()->loadModel("test/box.obj");
	//models_[2] = ModelSystemLocator::get()->loadModel("test/box.obj");
//	models_[1]->transform_->parent_ = models_[0]->transform_;
//	models_[1]->transform_->local_matrix_.translate(pm::vec3(2, 0, 0));
	models_[1]->transform_->local_matrix_.translate(pm::vec3(4.0f, pm::sin(ClockLocator::get()->time() * 90.0f), 0.0f), pm::mat4::COMBINE_REPLACE);
	models_[1]->transform_->SetParent(models_[0]->transform_);
	
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
	float rotationDelta = ClockLocator::get()->time() * 45.0f;
	models_[0]->transform_->local_matrix_.translate(pm::vec3(0.0f, pm::sin(ClockLocator::get()->time() * 90.0f), 0.0f), pm::mat4::COMBINE_REPLACE);
	models_[0]->transform_->local_matrix_.rotateXYZ(pm::vec3(0.0f, pm::toRadians(rotationDelta), 0.0f));
}