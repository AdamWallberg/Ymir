#pragma once

#include <string>

#include "math.h"
#include "vec2.h"

namespace pm
{

class vec3
{
public:

	// Constructors / Destructor
	vec3(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);
	vec3(const vec3& rOther);

	~vec3();

	// Static instances
	static const vec3 zero;

	static const vec3 posx;
	static const vec3 negx;

	static const vec3 posy;
	static const vec3 negy;

	static const vec3 posz;
	static const vec3 negz;

	// Member variables
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		vec2 xy;
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
		return x * x + y * y + z * z;

	} // lengthSquared

		// Returns a normalized version of this vector. 
		// normalize() automatically calculates the length
		// of the vector, which can be stored in a float pointer.
	inline const vec3 normalize(float* pOutLength = nullptr) const
	{
		vec3 out;
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
		}

		return out;

	} // normalize

		// Dot product methods
	inline const float dot(const vec3& rOther) const
	{
		return x * rOther.x + y * rOther.y + z * rOther.z;

	} // dot

		// Cross product methods
	inline const vec3 cross(const vec3& in) const
	{
		return vec3(y * in.z - in.y * z, z * in.x - in.z * x, x * in.y - in.x * y);

	} // cross

		// String conversion
	inline const std::string toString()
	{
		return "x: " + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z);

	} // toString

		////////////////////////////////////////////////////////////////

		// Addition operators
	const vec3 operator + (const vec3& in) const;
	const vec3 operator + (const float in) const;
	void operator += (const vec3& in);
	void operator += (const float in);

	// Subtraction operators
	const vec3 operator - (const vec3& in) const;
	const vec3 operator - (const float in) const;
	const vec3 operator - () const;
	void operator -= (const vec3& in);
	void operator -= (const float in);

	// Multiplication
	const vec3 operator * (const vec3& in) const;
	const vec3 operator * (const float in) const;
	void operator *= (const vec3& in);
	void operator *= (const float in);

	// Division operators
	const vec3 operator / (const vec3& in) const;
	const vec3 operator / (const float in) const;
	void operator /= (const vec3& in);
	void operator /= (const float in);

	// Comparison operators
	bool operator == (const vec3& in) const;
	bool operator != (const vec3& in) const;

};

}
