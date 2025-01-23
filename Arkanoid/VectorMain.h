#pragma once
namespace Arkanoid 
{
	class VectorMain
	{
	public:
		float x;
		float y;
		VectorMain() = default;
		VectorMain(float newX, float newY);
		VectorMain operator+(const VectorMain& vec) const;
		VectorMain& operator+=(const VectorMain& vec);
		VectorMain operator*(float vec) const;
		VectorMain& operator*=(float vec);
		VectorMain operator-(const VectorMain& vec) const;
		VectorMain& operator-=(const VectorMain& vec);
		float GetLength() const;
		float GetLengthSq() const;
		VectorMain& Normalize();
		VectorMain& GetNormalized();
	};
}

