#pragma once

#include "Math/ymath.h"

class Color
{
public:
	Color(
		float r = 1.0f, 
		float g = 1.0f, 
		float b = 1.0f, 
		float a = 1.0f);

	Color(pm::vec4 v);

	union
	{
		struct
		{
			float r, g, b, a;
		};

		struct 
		{
			float x, y, z, w;
		};
	};

	static Color red;
	static Color green;
	static Color blue;
	static Color cyan;
	static Color magenta;
	static Color yellow;
	static Color black;
	static Color white;
	static Color gray;
	static Color light_gray;
	static Color dark_gray;
};