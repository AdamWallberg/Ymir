#pragma once

#include "Camera.h"

class FreecamController
{
public:
	FreecamController();

	void update(float delta_time);

	Camera camera_;
	float speed_;
	float rotation_speed_;
};