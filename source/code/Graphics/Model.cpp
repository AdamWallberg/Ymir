#include "Model.h"
#include "Core.h"

Model::Model()
	: selected_(false)
{
	transform_ = newp Transform;
}

Model::~Model()
{
	delete transform_;
}