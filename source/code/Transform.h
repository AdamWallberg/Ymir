#pragma once

#include "Math/mat4.h"
#include <vector>

class Transform
{
public:
	Transform();

	void setParent(Transform* parent);

	void update();

	pm::mat4 world_matrix_;
	pm::mat4 local_matrix_;

	Transform* parent_;
	std::vector<Transform*> children_;	
};