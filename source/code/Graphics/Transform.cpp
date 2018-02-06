#include "Transform.h"

Transform::Transform()
	: parent_(nullptr)
{
	local_matrix_ = pm::mat4(1.0f);
	world_matrix_ = pm::mat4(1.0f);
}

void Transform::SetParent(Transform* parent)
{
	parent_ = parent;
	parent->children_.push_back(this);
}

void Transform::Update()
{
	// Apply parent transform
	if (parent_)
	{
		world_matrix_ = local_matrix_ * parent_->world_matrix_;
	}
	else
	{
		world_matrix_ = local_matrix_;
	}

	// Update children
	for (Transform* child : children_)
	{
		child->Update();
	}
}