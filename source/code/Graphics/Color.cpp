#include "Color.h"

Color Color::red		= Color(1.0f, 0.0f, 0.0f, 1.0);
Color Color::green		= Color(0.0f, 1.0f, 0.0f, 1.0);
Color Color::blue		= Color(0.0f, 0.0f, 1.0f, 1.0);
Color Color::cyan		= Color(0.0f, 1.0f, 1.0f, 1.0);
Color Color::magenta	= Color(1.0f, 0.0f, 1.0f, 1.0);
Color Color::yellow		= Color(1.0f, 1.0f, 0.0f, 1.0);
Color Color::black		= Color(0.0f, 0.0f, 0.0f, 1.0);
Color Color::white		= Color(1.0f, 1.0f, 1.0f, 1.0);
Color Color::gray		= Color(0.5f, 0.5f, 0.5f, 1.0);
Color Color::light_gray	= Color(0.75f, 0.75f, 0.75f, 1.0);
Color Color::dark_gray	= Color(0.25f, 0.25f, 0.25f, 1.0);

Color::Color(
	float r /*= 1.0f*/, 
	float g /*= 1.0f*/, 
	float b /*= 1.0f*/, 
	float a /*= 1.0f*/)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{
}

Color::Color(pm::vec4 v)
	: r(v.x)
	, g(v.y)
	, b(v.z)
	, a(v.w)
{
}
