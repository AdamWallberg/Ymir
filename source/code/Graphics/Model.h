#pragma once

#include "Math/ymath.h"

#include "Transform.h"

class Model
{
public:
	Model();
	~Model();

	//pm::mat4 transform; // Make sure this is the first piece of data in this class
	Transform* transform_;
};