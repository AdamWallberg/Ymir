#include "GameStateGame.h"
#include "Logger.h"
#include "Graphics/ModelSystem.h"
#include "Clock.h"

GameStateGame::GameStateGame(GameStateMachine* machine)
	: IGameState(machine)
{
	camera_.camera_.position_ = pm::vec3(0.0f, 0.0f, -20.0f);

	for (int i = 0; i < NUM_MODELS; i++)
	{
		models_[i] = ModelSystemLocator::get()->loadModel("test/suzanne.obj");


		switch (i)
		{
		case 0:
			models_[i]->transform_->local_matrix_.translate(pm::vec3(-4.0f, 0.0f, 0.0f));
			models_[i]->transform_->local_matrix_.scale(pm::vec3(2.0f, 2.0f, 2.0f));
			break;
		case 1:
			models_[i]->transform_->local_matrix_.translate(pm::vec3(4.0f, 0.0f, 0.0f));
			break;
		case 2:
			models_[i]->transform_->local_matrix_.translate(pm::vec3(-4.0f, -4.0f, 0.0f));
			models_[i]->transform_->local_matrix_.scale(pm::vec3(2.0f, 2.0f, 2.0f));
			break;
		case 3:
			models_[i]->transform_->local_matrix_.translate(pm::vec3(4.0f, -4.0f, 0.0f));
			break;
		}
	}	
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
	camera_.update(ClockLocator::get()->deltaTime());

	float rotationDelta = ClockLocator::get()->deltaTime() * 45.0f;

	static bool has_adopted = false;
	if (!has_adopted && ClockLocator::get()->time() > 3.0f)
	{
		models_[1]->transform_->addChild(models_[0]->transform_, false);
		models_[3]->transform_->addChild(models_[2]->transform_, true);
		LOG("Has been adopted!");
		has_adopted = true;
	}

	for (int i = 0; i < NUM_MODELS; i++)
	{
		models_[i]->transform_->update();
	}
}