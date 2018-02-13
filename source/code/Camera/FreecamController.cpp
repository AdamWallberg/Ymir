#include "FreecamController.h"
#include "Input/Controllers/EngineInputController.h"
#include "Logger.h"

FreecamController::FreecamController()
	: speed_(5.0f)
	, rotation_speed_(180.0f)
{
	MainCam::provide(&camera_);
}

void FreecamController::update(float delta_time)
{
	EngineInputController* input = INPUT;
	const pm::mat4& cam_mat = camera_.transform_->local_matrix_;

	// Get input
	float sideways = input->getValue("move_sideways") * speed_;
	float forward = input->getValue("move_forward") * speed_;
	float upwards = input->getValue("move_up") * speed_;
	float rot_x = input->getValue("rotate_x");
	float rot_y = input->getValue("rotate_y");

	// Move camera
	camera_.position_ += cam_mat.forward * forward * delta_time;
	camera_.position_ += cam_mat.left * sideways * delta_time;
	camera_.position_ += cam_mat.up * upwards * delta_time;

	// Rotate camera
	camera_.rotation_ += pm::vec3(
		rot_x * rotation_speed_ * delta_time,
		rot_y * rotation_speed_ * delta_time,
		0.0f);

	camera_.rotation_.x = pm::clamp(camera_.rotation_.x, -90.0f, 90.0f);

	camera_.update();
}