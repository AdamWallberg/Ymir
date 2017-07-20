#include "vec4.h"

namespace pm
{

// Static const vectors
const vec4 vec4::zero = vec4();
const vec4 vec4::posx = vec4(1.0f, 0.0f, 0.0f, 0.0f);
const vec4 vec4::negx = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
const vec4 vec4::posy = vec4(0.0f, 1.0f, 0.0f, 0.0f);
const vec4 vec4::negy = vec4(0.0f, -1.0f, 0.0f, 0.0f);
const vec4 vec4::posz = vec4(0.0f, 0.0f, 1.0f, 0.0f);
const vec4 vec4::negz = vec4(0.0f, 0.0f, -1.0f, 0.0f);
const vec4 vec4::posw = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 vec4::negw = vec4(0.0f, 0.0f, 0.0f, -1.0f);

// Color constants
const vec4 vec4::white = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 vec4::black = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 vec4::gray = vec4(0.5f, 0.5f, 0.5f, 1.0f);
const vec4 vec4::red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
const vec4 vec4::green = vec4(0.0f, 1.0f, 0.0f, 1.0f);
const vec4 vec4::blue = vec4(0.0f, 0.0f, 1.0f, 1.0f);
const vec4 vec4::magenta = vec4(1.0f, 0.0f, 1.0f, 1.0f);
const vec4 vec4::yellow = vec4(1.0f, 1.0f, 0.0f, 1.0f);
const vec4 vec4::turquoise = vec4(0.0f, 1.0f, 1.0f, 1.0f);

vec4::vec4(const float& x /*= 0.0f*/, const float& y /*= 0.0f*/, const float& z /*= 0.0f*/, const float& w/*= 0.0f*/)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
} // pmV4

vec4::vec4(const vec4& rOther)
{
	this->x = rOther.x;
	this->y = rOther.y;
	this->z = rOther.z;
	this->w = rOther.w;
} // pmV4

vec4::~vec4()
{
} // ~pmV4

const vec4 vec4::operator + (const vec4& in) const
{
	return vec4(x + in.x, y + in.y, z + in.z, w + in.w);

} // operator +

const vec4 vec4::operator + (const float in) const
{
	return vec4(x + in, y + in, z + in, w + in);

} // operator +

void vec4::operator += (const vec4& in)
{
	x += in.x;
	y += in.y;
	z += in.z;
	w += in.w;

} // operator +=

void vec4::operator += (const float in)
{
	x += in;
	y += in;
	z += in;
	w += in;

} // operator +=

const vec4 vec4::operator - (const vec4& in) const
{
	return vec4(x - in.x, y - in.y, z - in.z, w - in.w);

} // operator -

const vec4 vec4::operator - (const float in) const
{
	return vec4(x - in, y - in, z - in, w - in);

} // operator -

const vec4 vec4::operator - () const
{
	return vec4(-x, -y, -z, -w);
}

void vec4::operator -= (const vec4& in)
{
	x -= in.x;
	y -= in.y;
	z -= in.z;
	w -= in.w;

} // operator -=

void vec4::operator -= (const float in)
{
	x -= in;
	y -= in;
	z -= in;
	w -= in;

} // operator -=

const vec4 vec4::operator * (const vec4& in) const
{
	return vec4(x * in.x, y * in.y, z * in.z, w * in.w);

} // operator *

const vec4 vec4::operator * (const float in) const
{
	return vec4(x * in, y * in, z * in, w * in);

} // operator *

void vec4::operator *= (const vec4& in)
{
	x *= in.x;
	y *= in.y;
	z *= in.z;
	w *= in.w;

} // operator *=

void vec4::operator *= (const float in)
{
	x *= in;
	y *= in;
	z *= in;
	w *= in;

} // operator *=

const vec4 vec4::operator / (const vec4& in) const
{
	return vec4(x / in.x, y / in.y, z / in.z, w / in.w);

} // operator /

const vec4 vec4::operator / (const float in) const
{
	return vec4(x / in, y / in, z / in, w / in);

} // operator /

void vec4::operator /= (const vec4& in)
{
	x /= in.x;
	y /= in.y;
	z /= in.z;
	w /= in.w;

} // operator /=

void vec4::operator /= (const float in)
{
	x /= in;
	y /= in;
	z /= in;
	w /= in;

} // operator /=

bool vec4::operator == (const vec4& in) const
{
	return x == in.x && y == in.y && z == in.z && w == in.w;

} // operator ==



bool vec4::operator != (const vec4& in) const
{
	return x != in.x || y != in.y || z != in.z || w != in.w;

} // operator !=

}
