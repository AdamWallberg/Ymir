#include "GameStateGame.h"
#include "Logger.h"
#include "Graphics/ModelSystem.h"
#include "Clock.h"
#include "Graphics/Window.h"
#include "Graphics/GL.h"
#include "Graphics/Renderer.h"

GameStateGame::GameStateGame(GameStateMachine* machine)
	: IGameState(machine)
	, selected_model_(nullptr)
{
	camera_.camera_.position_ = pm::vec3(0.0f, 0.0f, -20.0f);

	for (int i = 0; i < NUM_MODELS; i++)
	{
		models_.push_back(ModelSystemLocator::get()->loadModel("test/box.obj"));
	
		if (i != 0)
		{
			models_[i]->transform_->local_matrix_.translate(pm::vec3(0.0f, -4.0f * i, 0.0f));
			//models_[i]->transform_->setParent(models_[i - 1]->transform_, false);
		}
		else
		{
			models_[i]->transform_->local_matrix_.translate(pm::vec3(0.0f, 0.0f, 0.0f));
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

	float rotationDelta = pm::toRadians(ClockLocator::get()->deltaTime() * 90.0f);

	for (int i = 0; i < NUM_MODELS; i++)
	{
		//models_[i]->transform_->local_matrix_.rotateXYZ(pm::vec3(0.0f, rotationDelta, 0.0f));
		models_[i]->transform_->update();
	}

	// Handle model selection
	static bool pressed = false;
	if (glfwGetMouseButton(WindowLocator::get()->getWindow(), 0) == GLFW_PRESS)
	{
		if (!pressed)
		{
			pressed = true;
			double x, y;
			glfwGetCursorPos(WindowLocator::get()->getWindow(), &x, &y);

			uint id = RendererLocator::get()->getObjectIDAt(INT_S(x), INT_S(y));
			if (id <= models_.size())
			{
				auto it = std::find_if(models_.begin(), models_.end(), [&id](const Model* obj) {return obj->id_ == id; });

				if (it != models_.end())
				{
					if (selected_model_)
						selected_model_->selected_ = false;
					int64 index = (int64)std::distance(models_.begin(), it);
					selected_model_ = models_[index];
					selected_model_->selected_ = true;
				}
			}
			else
			{
				if (selected_model_)
					selected_model_->selected_ = false;
				selected_model_ = nullptr;
			}
		}
	}
	else
	{
		pressed = false;
	}
}