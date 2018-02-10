#include "mat4.h"
#include "ymath.h"

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
	Result.position = translation;

	MULTIPLY_THIS(Order, Result);
}

void mat4::rotateZYX(const vec3& axis, EMultiplyOrder Order)
{
	float ca = pm::cosRad(axis.x);
	float sa = pm::sinRad(axis.x);
	float cb = pm::cosRad(axis.y);
	float sb = pm::sinRad(axis.y);
	float cc = pm::cosRad(axis.z);
	float sc = pm::sinRad(axis.z);

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
	float ca = pm::cosRad(axis.x);
	float sa = pm::sinRad(axis.x);
	float cb = pm::cosRad(axis.y);
	float sb = pm::sinRad(axis.y);
	float cc = pm::cosRad(axis.z);
	float sc = pm::sinRad(axis.z);

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

	result.position.x = -left.dot(position);
	result.position.y = -up.dot(position);
	result.position.z = forward.dot(position);

	return result;
}

mat4 mat4::getInverseMatrix() const
{
	// Based off the Sparky engine inverse matrix calculations
	float temp[16];

	temp[0] = elements[5] * elements[10] * elements[15] -
		elements[5] * elements[11] * elements[14] -
		elements[9] * elements[6] * elements[15] +
		elements[9] * elements[7] * elements[14] +
		elements[13] * elements[6] * elements[11] -
		elements[13] * elements[7] * elements[10];

	temp[4] = -elements[4] * elements[10] * elements[15] +
		elements[4] * elements[11] * elements[14] +
		elements[8] * elements[6] * elements[15] -
		elements[8] * elements[7] * elements[14] -
		elements[12] * elements[6] * elements[11] +
		elements[12] * elements[7] * elements[10];

	temp[8] = elements[4] * elements[9] * elements[15] -
		elements[4] * elements[11] * elements[13] -
		elements[8] * elements[5] * elements[15] +
		elements[8] * elements[7] * elements[13] +
		elements[12] * elements[5] * elements[11] -
		elements[12] * elements[7] * elements[9];

	temp[12] = -elements[4] * elements[9] * elements[14] +
		elements[4] * elements[10] * elements[13] +
		elements[8] * elements[5] * elements[14] -
		elements[8] * elements[6] * elements[13] -
		elements[12] * elements[5] * elements[10] +
		elements[12] * elements[6] * elements[9];

	temp[1] = -elements[1] * elements[10] * elements[15] +
		elements[1] * elements[11] * elements[14] +
		elements[9] * elements[2] * elements[15] -
		elements[9] * elements[3] * elements[14] -
		elements[13] * elements[2] * elements[11] +
		elements[13] * elements[3] * elements[10];

	temp[5] = elements[0] * elements[10] * elements[15] -
		elements[0] * elements[11] * elements[14] -
		elements[8] * elements[2] * elements[15] +
		elements[8] * elements[3] * elements[14] +
		elements[12] * elements[2] * elements[11] -
		elements[12] * elements[3] * elements[10];

	temp[9] = -elements[0] * elements[9] * elements[15] +
		elements[0] * elements[11] * elements[13] +
		elements[8] * elements[1] * elements[15] -
		elements[8] * elements[3] * elements[13] -
		elements[12] * elements[1] * elements[11] +
		elements[12] * elements[3] * elements[9];

	temp[13] = elements[0] * elements[9] * elements[14] -
		elements[0] * elements[10] * elements[13] -
		elements[8] * elements[1] * elements[14] +
		elements[8] * elements[2] * elements[13] +
		elements[12] * elements[1] * elements[10] -
		elements[12] * elements[2] * elements[9];

	temp[2] = elements[1] * elements[6] * elements[15] -
		elements[1] * elements[7] * elements[14] -
		elements[5] * elements[2] * elements[15] +
		elements[5] * elements[3] * elements[14] +
		elements[13] * elements[2] * elements[7] -
		elements[13] * elements[3] * elements[6];

	temp[6] = -elements[0] * elements[6] * elements[15] +
		elements[0] * elements[7] * elements[14] +
		elements[4] * elements[2] * elements[15] -
		elements[4] * elements[3] * elements[14] -
		elements[12] * elements[2] * elements[7] +
		elements[12] * elements[3] * elements[6];

	temp[10] = elements[0] * elements[5] * elements[15] -
		elements[0] * elements[7] * elements[13] -
		elements[4] * elements[1] * elements[15] +
		elements[4] * elements[3] * elements[13] +
		elements[12] * elements[1] * elements[7] -
		elements[12] * elements[3] * elements[5];

	temp[14] = -elements[0] * elements[5] * elements[14] +
		elements[0] * elements[6] * elements[13] +
		elements[4] * elements[1] * elements[14] -
		elements[4] * elements[2] * elements[13] -
		elements[12] * elements[1] * elements[6] +
		elements[12] * elements[2] * elements[5];

	temp[3] = -elements[1] * elements[6] * elements[11] +
		elements[1] * elements[7] * elements[10] +
		elements[5] * elements[2] * elements[11] -
		elements[5] * elements[3] * elements[10] -
		elements[9] * elements[2] * elements[7] +
		elements[9] * elements[3] * elements[6];

	temp[7] = elements[0] * elements[6] * elements[11] -
		elements[0] * elements[7] * elements[10] -
		elements[4] * elements[2] * elements[11] +
		elements[4] * elements[3] * elements[10] +
		elements[8] * elements[2] * elements[7] -
		elements[8] * elements[3] * elements[6];

	temp[11] = -elements[0] * elements[5] * elements[11] +
		elements[0] * elements[7] * elements[9] +
		elements[4] * elements[1] * elements[11] -
		elements[4] * elements[3] * elements[9] -
		elements[8] * elements[1] * elements[7] +
		elements[8] * elements[3] * elements[5];

	temp[15] = elements[0] * elements[5] * elements[10] -
		elements[0] * elements[6] * elements[9] -
		elements[4] * elements[1] * elements[10] +
		elements[4] * elements[2] * elements[9] +
		elements[8] * elements[1] * elements[6] -
		elements[8] * elements[2] * elements[5];

	mat4 result = *this;
	float determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
	determinant = 1.0f / determinant;

	for (uint i = 0; i < 16; i++)
		result.elements[i] = temp[i] * determinant;

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

	result.position.x = -((right + left) / W);
	result.position.y = -((top + bottom) / H);
	result.position.z = -((far + near) / D);
	result.elements[15] = 1.0f;

	return result;
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result(0.0f);

	const float tf = 1.0f / pm::tan(fov * 0.5f);
	const float fn = far - near;

	result.left.x = tf / aspectRatio;
	result.up.y = tf;
	result.forward.z = -(near + far) / fn;
	result.position.z = -(2.0f * near * far) / fn;
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
