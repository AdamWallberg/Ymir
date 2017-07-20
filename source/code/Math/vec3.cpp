#include "vec3.h"

namespace pm
{

// Static const vectors
const vec3 vec3::zero = vec3();
const vec3 vec3::posx = vec3(1.0f, 0.0f, 0.0f);
const vec3 vec3::negx = vec3(-1.0f, 0.0f, 0.0f);
const vec3 vec3::posy = vec3(0.0f, 1.0f, 0.0f);
const vec3 vec3::negy = vec3(0.0f, -1.0f, 0.0f);
const vec3 vec3::posz = vec3(0.0f, 0.0f, 1.0f);
const vec3 vec3::negz = vec3(0.0f, 0.0f, -1.0f);

vec3::vec3(const float& x /*= 0.0f*/, const float& y /*= 0.0f*/, const float& z /*= 0.0f*/)
{
	this->x = x;
	this->y = y;
	this->z = z;
} // pmV3

vec3::vec3(const vec3& rOther)
{
	this->x = rOther.x;
	this->y = rOther.y;
	this->z = rOther.z;
} // pmV3

vec3::~vec3()
{
} // ~pmV3

const vec3 vec3::operator + (const vec3& in) const
{
	return vec3(x + in.x, y + in.y, z + in.z);

} // operator +

const vec3 vec3::operator + (const float in) const
{
	return vec3(x + in, y + in, z + in);

} // operator +

void vec3::operator += (const vec3& in)
{
	x += in.x;
	y += in.y;
	z += in.z;

} // operator +=

void vec3::operator += (const float in)
{
	x += in;
	y += in;
	z += in;

} // operator +=

const vec3 vec3::operator - (const vec3& in) const
{
	return vec3(x - in.x, y - in.y, z - in.z);

} // operator -

const vec3 vec3::operator - (const float in) const
{
	return vec3(x - in, y - in, z - in);

} // operator -

const vec3 vec3::operator - () const
{
	return vec3(-x, -y, -z);
}

void vec3::operator -= (const vec3& in)
{
	x -= in.x;
	y -= in.y;
	z -= in.z;

} // operator -=

void vec3::operator -= (const float in)
{
	x -= in;
	y -= in;
	z -= in;

} // operator -=

const vec3 vec3::operator * (const vec3& in) const
{
	return vec3(x * in.x, y * in.y, z * in.z);

} // operator *

const vec3 vec3::operator * (const float in) const
{
	return vec3(x * in, y * in, z * in);

} // operator *

void vec3::operator *= (const vec3& in)
{
	x *= in.x;
	y *= in.y;
	z *= in.z;

} // operator *=

void vec3::operator *= (const float in)
{
	x *= in;
	y *= in;
	z *= in;

} // operator *=

const vec3 vec3::operator / (const vec3& in) const
{
	return vec3(x / in.x, y / in.y, z / in.z);

} // operator /

const vec3 vec3::operator / (const float in) const
{
	return vec3(x / in, y / in, z / in);

} // operator /

void vec3::operator /= (const vec3& in)
{
	x /= in.x;
	y /= in.y;
	z /= in.z;

} // operator /=

void vec3::operator /= (const float in)
{
	x /= in;
	y /= in;
	z /= in;

} // operator /=

bool vec3::operator == (const vec3& in) const
{
	return x == in.x && y == in.y && z == in.z;

} // operator ==

bool vec3::operator != (const vec3& in) const
{
	return x != in.x || y != in.y || z != in.z;

} // operator !=

}
