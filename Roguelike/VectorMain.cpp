#include <cmath>
#include "VectorMain.h"

namespace Arkanoid 
{
	VectorMain::VectorMain(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	VectorMain VectorMain::operator+(const VectorMain& vec) const
	{
		return VectorMain(x + vec.x, y + vec.y);
	}

	VectorMain& VectorMain::operator+=(const VectorMain& vec)
	{
		return *this = *this + vec;
	}

	VectorMain VectorMain::operator*(float vec) const
	{
		return VectorMain(x * vec, y * vec);
	}

	VectorMain& VectorMain::operator*=(float vec)
	{
		return *this = *this * vec;
	}

	VectorMain VectorMain::operator-(const VectorMain& vec) const
	{
		return VectorMain(x - vec.x, y - vec.y);
	}

	VectorMain& VectorMain::operator-=(const VectorMain& vec)
	{
		return *this = *this - vec;
	}

	float VectorMain::GetLength() const
	{
		return x * x + y * y;
	}

	float VectorMain::GetLengthSq() const
	{
		return std::sqrt(GetLength());
	}

	VectorMain& VectorMain::Normalize()
	{
		return *this = GetNormalized();
	}

	VectorMain& VectorMain::GetNormalized()
	{
		const float len = GetLengthSq();
		if (len != 0.0f)
		{
			return *this *= (1.0f / len);
		}
		return *this;
	}

}