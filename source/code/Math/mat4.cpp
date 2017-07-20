#include "mat4.h"

#define MULTIPLY_THIS( ORDER, RESULT ) \
if( ORDER == COMBINE_REPLACE ) \
{ \
	*this = RESULT; \
} \
else if( ORDER == COMBINE_POST_MULTIPLY ) \
{ \
	*this = *this * RESULT; \
} \
else if( ORDER == COMBINE_PRE_MULTIPLY ) \
{ \
	*this = RESULT * *this; \
} \

using namespace pm;

namespace pm
{

mat4::mat4()
{
	// Set all elements to 0
	memset(elements, 0, 16 * sizeof(float));
}

mat4::mat4(const mat4& other)
{
	for (unsigned char i = 0; i < 16; i++)
	{
		elements[i] = other.elements[i];
	}
}

mat4::mat4(const float diagonal)
{
	// Set all elements to 0
	memset(elements, 0, 16 * sizeof(float));

	// Set the diagonal
	for (unsigned char i = 0; i < 4; ++i)
	{
		elements[i + i * 4] = diagonal;
	}
}

mat4::~mat4()
{
}

void mat4::translate(const vec3& translation, EMultiplyOrder Order)
{
	mat4 Result(1.0f);
	Result.translation = translation;

	MULTIPLY_THIS(Order, Result);
}

void mat4::rotateZYX(const vec3& axis, EMultiplyOrder Order)
{
	float ca = cos(axis.x);
	float sa = sin(axis.x);
	float cb = cos(axis.y);
	float sb = sin(axis.y);
	float cc = cos(axis.z);
	float sc = sin(axis.z);

	// ZYX
	mat4 result(1.0f);
	result.left.x = cc * cb;
	result.left.y = sc * cb;
	result.left.z = -sb;

	result.up.x = -sc * ca + cc * sb * sa;
	result.up.y = cc * ca + sc * sb * sa;
	result.up.z = cb * sa;

	result.forward.x = sc * sa + cc * sb * ca;
	result.forward.y = -cc * sa + sc * sb * ca;
	result.forward.z = cb * ca;

	MULTIPLY_THIS(Order, result);
}

void mat4::rotateXYZ(const vec3& axis, EMultiplyOrder Order)
{
	float ca = cos(axis.x);
	float sa = sin(axis.x);
	float cb = cos(axis.y);
	float sb = sin(axis.y);
	float cc = cos(axis.z);
	float sc = sin(axis.z);

	mat4 result(1.0f);
	result.left.x = cb * cc;
	result.left.y = sa * sb * cc + ca * sc;
	result.left.z = -ca * sb * cc + sa * sc;

	result.up.x = -cb * sc;
	result.up.y = -sa * sb * sc + ca * cc;
	result.up.z = ca * sb * sc + sa * cc;

	result.forward.x = sb;
	result.forward.y = -sa * cb;
	result.forward.z = ca * cb;

	MULTIPLY_THIS(Order, result);
}

void mat4::scale(const vec3& scale, EMultiplyOrder Order)
{
	elements[0 + 0 * 4] = scale.x;
	elements[1 + 1 * 4] = scale.y;
	elements[2 + 2 * 4] = scale.z;
}

void mat4::transpose()
{
	mat4 result(1);
	for (unsigned char c = 0; c < 4; ++c)
	{
		for (unsigned char r = 0; r < 4; ++r)
		{
			result.elements[c + r * 4] = elements[r + c * 4];
		}
	}

	*this = result;
}

void mat4::orthonormalize()
{
	orthogonalize();
	left.normalize();
	up.normalize();
	forward.normalize();
}

void mat4::orthogonalize()
{
	left = forward.cross(up);
	up = left.cross(forward);
}

mat4 mat4::getViewMatrix() const
{
	mat4 result(1.0f);

	result.left.x = left.x;
	result.left.y = up.x;
	result.left.z = -forward.x;

	result.up.x = left.y;
	result.up.y = up.y;
	result.up.z = -forward.y;

	result.forward.x = left.z;
	result.forward.y = up.z;
	result.forward.z = -forward.z;

	result.translation.x = -left.dot(translation);
	result.translation.y = -up.dot(translation);
	result.translation.z = forward.dot(translation);

	return result;
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 result;

	float W = right - left;
	float H = top - bottom;
	float D = far - near;

	result.left.x = 2.0f / W;
	result.up.y = 2.0f / H;
	result.forward.z = -2.0f / D;

	result.translation.x = -((right + left) / W);
	result.translation.y = -((top + bottom) / H);
	result.translation.z = -((far + near) / D);
	result.elements[15] = 1.0f;

	return result;
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result(0.0f);

	result.left.x = (1.0f / tan(fov * 0.5f)) / aspectRatio;
	result.up.y = 1.0f / tan(fov * 0.5f);
	result.forward.z = (near + far) / (near - far);
	result.translation.z = (2.0f * near * far) / (near - far);
	result.elements[11] = -1.0f;

	return result;
}

mat4 mat4::operator*(const mat4& other)
{
	mat4 result;
	float sum;
	for (unsigned char row = 0; row < 4; ++row)
	{
		for (unsigned char col = 0; col < 4; ++col)
		{
			sum = 0.0f;
			for (unsigned char i = 0; i < 4; ++i)
			{
				sum += elements[i + row * 4] * other.elements[col + i * 4];
			}
			result.elements[col + row * 4] = sum;
		}
	}

	return result;
}

float& mat4::operator[](unsigned char id)
{
	return elements[id];
}

}
