#pragma once

#include <string>

#include "math.h"

namespace pm
{

class vec2
{
public:

	// Constructors / Destructor
	vec2(const float& x = 0.0f, const float& y = 0.0f);
	vec2(const vec2& rOther);

	~vec2();

	// Static instances
	static const vec2 zero;

	static const vec2 posx;
	static const vec2 negx;

	static const vec2 posy;
	static const vec2 negy;

	// Member variables
	union
	{
		struct
		{
			float x;
			float y;
		};
	};

	////////////////////////////////////////////////////////////////

	// Methods

	// Performance heavy, use lengthSquared() when possible.
	inline const float length() const
	{
		return sqrt(lengthSquared());

	} // length

	const float lengthSquared() const
	{
		return x * x + y * y;

	} // lengthSquared

	// Returns a normalized version of this vector. 
	// normalize() automatically calculates the length
	// of the vector, which can be stored in a float pointer.
	inline const vec2 normalize(float* pOutLength = nullptr) const
	{
		vec2 out;
		const float length = this->length();

		// return length if pointer is given
		if (pOutLength)
			*pOutLength = length;

		// Don't divide by zero
		if (length != 0.0f)
		{
			out.x = x / length;
			out.y = y / length;
		}

		return out;

	} // normalize

	// Dot product methods
	inline const float& dot(const vec2& rOther) const
	{
		return x * rOther.x + y * rOther.y;

	} // dot

	// String conversion
	inline const std::string toString()
	{
		return "x: " + std::to_string(x) + " y: " + std::to_string(y);

	} // toString

		////////////////////////////////////////////////////////////////

		// Addition operators
	const vec2 operator + (const vec2& in) const;
	const vec2 operator + (const float in) const;
	void operator += (const vec2& in);
	void operator += (const float in);

	// Subtraction operators
	const vec2 operator - (const vec2& in) const;
	const vec2 operator - (const float in) const;
	const vec2 operator - () const;
	void operator -= (const vec2& in);
	void operator -= (const float in);

	// Multiplication
	const vec2 operator * (const vec2& in) const;
	const vec2 operator * (const float in) const;
	void operator *= (const vec2& in);
	void operator *= (const float in);

	// Division operators
	const vec2 operator / (const vec2& in) const;
	const vec2 operator / (const float in) const;
	void operator /= (const vec2& in);
	void operator /= (const float in);

	// Comparison operators
	bool operator == (const vec2& in) const;
	bool operator != (const vec2& in) const;

};

}
