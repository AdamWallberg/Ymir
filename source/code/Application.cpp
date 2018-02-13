#include "Application.h"
#include "Core.h"

Application::Application()
	: logger_(nullptr)
	, window_(nullptr)
	, clock_(nullptr)
	, input_system_(nullptr)
	, input_controller_(nullptr)
	, game_state_machine_(nullptr)
	, model_system_(nullptr)
	, renderer_(nullptr)
	, frame_timer_(0.f)
	, second_timer_(0.f)
{
}

Application::~Application()
{
}

bool Application::init()
{
	// Create logger
	logger_ = newp Logger(nullptr);
	//LoggerLocator::provide(logger_);
#ifdef NDEBUG
	logger_->setFlag(Logger::FLAG_GAME_STATE, false);
#endif

	// Create window
	window_ = newp Window(nullptr);
	window_->createWindow("Ymir Engine", 1280, 720);

	// Create clock
	clock_ = newp Clock(nullptr);

	// Create input system
	input_system_ = newp InputSystem(nullptr);

	// Create input controller
	input_controller_ = newp EngineInputController;

	// Create model system
	model_system_ = newp ModelSystem(nullptr);
	model_system_->updateInstanceBuffers();

	// Create game state machine 
	game_state_machine_ = newp GameStateMachine(nullptr);

	// Create renderer
	renderer_ = newp Renderer(nullptr);

	return true;
}

void Application::destroy()
{
	delete renderer_;

	delete model_system_;

	delete game_state_machine_;

	delete input_controller_;

	delete input_system_;

	delete clock_;

	delete window_;

	delete logger_;
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
	clock_->update();
	input_controller_->update();
	game_state_machine_->update(clock_->deltaTime());

	// Update timers
	frame_timer_ += clock_->deltaTime();
	while (frame_timer_ >= 1.0f / 60.0f)
	{
		frame_timer_ -= 1.0f / 60.0f;
	}
	
	second_timer_ += clock_->deltaTime();
	while (second_timer_ >= 1.0f)
	{
		second_timer_ -= 1.0f;

		window_->setTitle("Ymir Engine | FPS: " + std::to_string(INT_S(1.0f / clock_->deltaTime())));
	}

	model_system_->updateInstanceBuffers();

	if (window_->hasResized())
	{
		renderer_->resize();
	}
	renderer_->render();

	window_->swapBuffers();
}

