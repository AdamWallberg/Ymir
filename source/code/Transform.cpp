#include "Transform.h"

Transform::Transform()
	: parent_(nullptr)
{
	local_matrix_ = pm::mat4(1.0f);
	world_matrix_ = pm::mat4(1.0f);
}

void Transform::setParent(
	Transform* parent, 
	bool keep_world_transformation /*= true*/)
{
	if (parent->parent_ == this)
		return;
	parent->update();
	parent_ = parent;
	parent->children_.push_back(this);

	// Handle position
	if (keep_world_transformation)
	{
		// Multiply local matrix with inverse parent world matrix.
		local_matrix_ = 
			local_matrix_ * parent_->world_matrix_.getInverseMatrix();
	}
}

void Transform::addChild(
	Transform* child,
	bool keep_world_transformation /*= true*/)
{
	if (std::find(
		children_.begin(), 
		children_.end(), 
		child) != children_.end())
	{
		// Transform is already child
		return;
	}

	update();
	child->parent_ = this;
	children_.push_back(child);

	// Handle position
	if (keep_world_transformation)
	{
		// Multiply local matrix with inverse parent world matrix.
		child->local_matrix_ =
			child->local_matrix_ * world_matrix_.getInverseMatrix();
	}
}

void Transform::update()
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
		child->update();
	}
}