#pragma once

#include <include/glm.h>
#include <include/math.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace glm;

namespace Transform2D
{
	// Translate matrix
	inline mat3 Translate(float translateX, float translateY)
	{
		return transpose(
			mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1));
	}

	// Scale matrix
	inline mat3 Scale(float scaleX, float scaleY)
	{
		return transpose(
			mat3(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1));
	}

	// Rotate matrix
	inline mat3 Rotate(float radians)
	{
		return transpose(
			mat3(cos(radians), -sin(radians), 0,
				sin(radians), cos(radians), 0,
				0, 0, 1));
	}

	inline float Angle(vec2 a, vec2 b)
	{
		return atan2(b.y - a.y, b.x - a.x) + RADIANS(90);
	}
}

