#include "Model.h"
#include "Core.h"

Model::Model()
{
	transform_ = newp Transform;
}

Model::~Model()
{
	delete transform_;
}