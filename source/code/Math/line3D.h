#pragma once

#include "vec3.h"

namespace pm
{

// Uses two 3D vectors to represent a line in 3D space
class line3D
{
public:
	line3D()
	{

	}

	line3D(const vec3& startPos, const vec3& endPos)
	{
		this->startPos = startPos;
		this->endPos = endPos;
	}

	inline const float getLength(vec3* lengthVectorOut = nullptr)
	{
		vec3 lengthVector = endPos - startPos;
		if (lengthVectorOut)
			*lengthVectorOut = lengthVector;

		return lengthVector.length();
	}

	inline const vec3 getPositionAtFraction(const float& fraction)
	{
		return startPos + (endPos - startPos) * fraction;
	}

	vec3 startPos;
	vec3 endPos;
};

}
