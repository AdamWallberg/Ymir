#include "GameStateGame.h"
#include "Logger.h"
#include "Graphics/ModelSystem.h"
#include "Clock.h"

GameStateGame::GameStateGame(GameStateMachine* machine)
	: IGameState(machine)
{
	for (int i = 0; i < NUM_MODELS; i++)
	{
		models_[i] = ModelSystemLocator::get()->loadModel("test/suzanne.obj");
		models_[i]->transform_->local_matrix_.position = pm::vec3(0.0f, i == 0 ? 3.0f : -2.0f, 0.0f);

		if (i != 0)
		{
			models_[i]->transform_->setParent(models_[i - 1]->transform_);
			models_[i]->transform_->local_matrix_.translate(pm::vec3(1.0f, 0.0f, 0.0f));
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
	//models_[0]->transform_->local_matrix_.translate(pm::vec3(0.0f, pm::sin(ClockLocator::get()->time() * 90.0f), 0.0f), pm::mat4::COMBINE_REPLACE);
	//models_[0]->transform_->local_matrix_.forward = pm::vec3(1, 0, 0);

	for (int i = 0; i < NUM_MODELS; i++)
	{
		//models_[i]->transform_->local_matrix_.rotateXYZ(pm::vec3(0.0f, pm::toRadians(rotationDelta), 0.0f));
		//models_[i]->transform_->local_matrix_.translate(pm::vec3(ClockLocator::get()->deltaTime(), 0.0f, 0.0f));
		models_[0]->transform_->update();
	}
}