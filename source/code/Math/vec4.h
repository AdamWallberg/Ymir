#pragma once

#include <string>

#include "math.h"
#include "vec2.h"
#include "vec3.h"

namespace pm
{

class vec4
{
public:

	// Constructors / Destructor
	vec4(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f, const float& w = 0.0f);
	vec4(const vec4& rOther);

	~vec4();

	// Static instances
	static const vec4 zero;

	static const vec4 posx;
	static const vec4 negx;

	static const vec4 posy;
	static const vec4 negy;

	static const vec4 posz;
	static const vec4 negz;

	static const vec4 posw;
	static const vec4 negw;

	// Color constants
	static const vec4 white;
	static const vec4 black;
	static const vec4 gray;
	static const vec4 red;
	static const vec4 green;
	static const vec4 blue;
	static const vec4 magenta;
	static const vec4 yellow;
	static const vec4 turquoise;

	// Member variables
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		vec2 xy;
		vec3 xyz;
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		vec2 rg;
		vec3 rgb;
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
		return x * x + y * y + z * z + w * w;

	} // lengthSquared

		// Returns a normalized version of this vector. 
		// normalize() automatically calculates the length
		// of the vector, which can be stored in a float pointer.
	inline const vec4 normalize(float* pOutLength = nullptr) const
	{
		vec4 out;
		const float length = this->length();

		// return length if pointer is given
		if (pOutLength)
			*pOutLength = length;

		// Don't divide by zero
		if (length != 0.0f)
		{
			out.x = x / length;
			out.y = y / length;
			out.z = z / length;
			out.w = w / length;
		}

		return out;

	} // normalize

		// Dot product methods
	inline const float dot(const vec4& rOther) const
	{
		return x * rOther.x + y * rOther.y + z * rOther.z + w * rOther.w;

	} // dot

		// String conversion
	inline const std::string toString()
	{
		return "x: " + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z) + " w: " + std::to_string(w);

	} // toString

		////////////////////////////////////////////////////////////////

		// Addition operators
	const vec4 operator + (const vec4& in) const;
	const vec4 operator + (const float in) const;
	void operator += (const vec4& in);
	void operator += (const float in);

	// Subtraction operators
	const vec4 operator - (const vec4& in) const;
	const vec4 operator - (const float in) const;
	const vec4 operator - () const;
	void operator -= (const vec4& in);
	void operator -= (const float in);

	// Multiplication
	const vec4 operator * (const vec4& in) const;
	const vec4 operator * (const float in) const;
	void operator *= (const vec4& in);
	void operator *= (const float in);

	// Division operators
	const vec4 operator / (const vec4& in) const;
	const vec4 operator / (const float in) const;
	void operator /= (const vec4& in);
	void operator /= (const float in);

	// Comparison operators
	bool operator == (const vec4& in) const;
	bool operator != (const vec4& in) const;

};

}

