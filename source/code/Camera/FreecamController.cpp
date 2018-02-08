#include "FreecamController.h"
#include "Input/Controllers/EngineInputController.h"

FreecamController::FreecamController()
	: speed_(3.0f)
{
	MainCam::provide(&camera_);
}

void FreecamController::update(float delta_time)
{
	// Get input
	EngineInputController* input = InputController::get();
	float sideways = input->getValue("move_sideways") * speed_;
	float forward = input->getValue("move_forward") * speed_;
	float upwards = input->getValue("move_up") * speed_;

	// Move camera
	const pm::mat4& cam_mat = camera_.transform_->local_matrix_;
	camera_.position_ += cam_mat.forward * forward * delta_time;
	camera_.position_ += cam_mat.left * sideways * delta_time;
	camera_.position_ += cam_mat.up * upwards * delta_time;

	camera_.update();

	// TODO: Rotate camera
}