#pragma once

#include "vec2.h"

namespace pm
{

// Uses two 2D vectors to represent a line in 2D space
class line2D
{
public:
	line2D()
	{

	}

	line2D(const vec2& startPos, const vec2& endPos)
	{
		this->startPos = startPos;
		this->endPos = endPos;
	}

	inline const float getLength(vec2* lengthVectorOut = nullptr)
	{
		vec2 lengthVector = endPos - startPos;
		if (lengthVectorOut)
			*lengthVectorOut = lengthVector;

		return lengthVector.length();
	}

	inline const vec2 getPositionAtFraction(const float& fraction)
	{
		return startPos + (endPos - startPos) * fraction;
	}

	vec2 startPos;
	vec2 endPos;
};

}