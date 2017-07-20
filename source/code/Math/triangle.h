#pragma once

#include "vec3.h"

namespace pm
{

// Represents a triangle in 3D space
class triangle
{
public:

	triangle()
	{
	}

	triangle(const vec3& p1, const vec3& p2, const vec3& p3)
	{
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}

	// TODO: Methods for line intersection, normals, area, etc..

	vec3 p1;
	vec3 p2;
	vec3 p3;
};

}
