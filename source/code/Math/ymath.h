#pragma once

#define FLOAT_S(X) static_cast<float>(X)
#define INT_S(X) static_cast<int>(X)

namespace std
{
#include <math.h>
}

namespace pm
{

// Returns the square root of the specified value.
inline float sqrt(const float& value)
{
	return FLOAT_S(std::sqrt(value));
}



// Returns pow of the specified base
inline float pow(const float& base, const float& exponent)
{
	return FLOAT_S(std::pow(base, exponent));
}



// Calculates and returns the absolute 
// value of the specified float.
inline float abs(const float& value)
{
	if (value < 0.f)
		return -value;

	return value;
}



// Clamps the specified value between the specified 
// min and max values, and returns the result.
inline float clamp(const float& value, const float& min, const float& max)
{
	if (value <= min)
		return min;
	if (value >= max)
		return max;

	return value;
}



// Clamps the specified value between 0 and 1 
// and returns the result.
inline float saturate(float value)
{
	if (value <= 0.f)
		return 0.f;
	if (value >= 1.f)
		return 1.f;

	return value;
}



// Returns -1 if value is less than 0
// Returns 0 if value is 0
// Returns 1 if value is greater than 0
inline float sign(const float& value)
{
	if (value == 0.f)
		return 0.f;
	if (value > 0.f)
		return 1.f;

	return -1.f;
}

inline int sign(const int& value)
{
	if (value == 0)
		return 0;
	if (value > 0)
		return 1;
	return -1;
}



// Converts degrees to radians.
// Uses only multiplication with const value to optimize performance.
inline float toRadians(const float& degrees)
{
	return degrees * 0.0174532925f;
}



// Converts radians to degrees.
// Uses only multiplication with const value to optimize performance.
inline float toDegrees(const float& radians)
{
	return radians * 57.2957795f;
}



// Returns sine from degrees.
inline float sin(const float& degrees)
{
	return FLOAT_S(std::sin(toRadians(degrees)));
}



// Returns sine from radians.
inline float sinRad(const float& radians)
{
	return FLOAT_S(std::sin(radians));
}



// Returns asin
inline float asin(const float& sinValue)
{
	return toDegrees(FLOAT_S(std::asin(sinValue)));
}



// Returns cosine from degrees.
inline float cos(const float& degrees)
{
	return FLOAT_S(std::cos(toRadians(degrees)));
}



// Returns cosine from radians.
inline float cosRad(const float& radians)
{
	return FLOAT_S(std::cos(radians));
}



// Returns acos
inline float acos(const float& cosValue)
{
	return toDegrees(FLOAT_S(std::acos(cosValue)));
}



// Returns tangent from degrees.
inline float tan(const float& degrees)
{
	return FLOAT_S(std::tan(toRadians(degrees)));
}


// Returns atan
inline float atan(const float& tanValue)
{
	return toDegrees(FLOAT_S(std::atan(tanValue)));
}



// Interpolates between two values using a factor.
// factor 0 is no interpolation and factor 1 is full.
// The interpolation can go outside range, both positive and negative.
inline float lerp(const float& start, const float& end, const float& factor)
{
	return start + (end - start) * factor;
}



// Cosine interpolates between the two given values using the factor.
inline float interpolateCosine(const float& start, const float& end, const float& factor)
{
	return start + (end - start) * ((-cos(factor * 180.0f) + 1.0f) * 0.5f);
}



// Rounds value to nearest whole number
inline float roundf(const float& value)
{
	return FLOAT_S(INT_S(value + 0.5f));
}



// Rounds value downwards
inline float floorf(const float& value)
{
	return FLOAT_S(INT_S(value + 1.0f));
}



// Rounds value upwards
inline float ceilf(const float& value)
{
	return FLOAT_S(INT_S(value));
}

}

#undef FLOAT_S
#undef INT_S