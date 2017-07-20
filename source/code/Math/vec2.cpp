#include "vec2.h"

namespace pm
{

// Static const vectors
const vec2 vec2::zero = vec2();
const vec2 vec2::posx = vec2(1.0f, 0.0f);
const vec2 vec2::negx = vec2(-1.0f, 0.0f);
const vec2 vec2::posy = vec2(0.0f, 1.0f);
const vec2 vec2::negy = vec2(0.0f, -1.0f);

vec2::vec2(const float& x /*= 0.0f*/, const float& y /*= 0.0f*/)
{
	this->x = x;
	this->y = y;
} // pmV2

vec2::vec2(const vec2& rOther)
{
	this->x = rOther.x;
	this->y = rOther.y;
} // pmV2

vec2::~vec2()
{
} // ~pmV2

const vec2 vec2::operator + (const vec2& in) const
{
	return vec2(x + in.x, y + in.y);

} // operator +

const vec2 vec2::operator + (const float in) const
{
	return vec2(x + in, y + in);

} // operator +

void vec2::operator += (const vec2& in)
{
	x += in.x;
	y += in.y;

} // operator +=

void vec2::operator += (const float in)
{
	x += in;
	y += in;

} // operator +=

const vec2 vec2::operator - (const vec2& in) const
{
	return vec2(x - in.x, y - in.y);

} // operator -

const vec2 vec2::operator - (const float in) const
{
	return vec2(x - in, y - in);

} // operator -

const vec2 vec2::operator - () const
{
	return vec2(-x, -y);
}

void vec2::operator -= (const vec2& in)
{
	x -= in.x;
	y -= in.y;

} // operator -=

void vec2::operator -= (const float in)
{
	x -= in;
	y -= in;

} // operator -=

const vec2 vec2::operator * (const vec2& in) const
{
	return vec2(x * in.x, y * in.y);

} // operator *

const vec2 vec2::operator * (const float in) const
{
	return vec2(x * in, y * in);

} // operator *

void vec2::operator *= (const vec2& in)
{
	x *= in.x;
	y *= in.y;

} // operator *=

void vec2::operator *= (const float in)
{
	x *= in;
	y *= in;

} // operator *=

const vec2 vec2::operator / (const vec2& in) const
{
	return vec2(x / in.x, y / in.y);

} // operator /

const vec2 vec2::operator / (const float in) const
{
	return vec2(x / in, y / in);

} // operator /

void vec2::operator /= (const vec2& in)
{
	x /= in.x;
	y /= in.y;

} // operator /=

void vec2::operator /= (const float in)
{
	x /= in;
	y /= in;

} // operator /=

bool vec2::operator == (const vec2& in) const
{
	return x == in.x && y == in.y;

} // operator ==

bool vec2::operator != (const vec2& in) const
{
	return x != in.x || y != in.y;

} // operator !=

}
