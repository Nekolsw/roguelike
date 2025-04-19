#pragma once
#include <cmath>
namespace Engine 
{
	template<typename T>
	struct Vector2D 
	{
		T x = (T)0;
		T y = (T)0;
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

	template<typename T>
	Vector2D<T> operator==(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return { left.x == right.x && left.y == right.y };
	}

	template<typename T>
	Vector2D<T> operator+(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return { left.x + right.x, left.y + right.y };
	}

	template<typename T>
	Vector2D<T>& operator+=(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return { left + right };
	}

	template<typename T>
	Vector2D<T> operator*(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return Vector2D<T>(left.x * right, left.y * right);
	}

	template<typename T>
	Vector2D<T>& operator*=(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return left = left * right;
	}

	template<typename T>
	Vector2D<T> operator-(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return Vector2D<T>(left.x - right.x, left.y - right.y);
	}

	template<typename T>
	Vector2D<T>& operator-=(const Vector2D<T>& left, const Vector2D<T>& right)
	{
		return left = left - right;
	}

	template<typename T>
	float GetVectorLength(const Vector2D<T>& left)
	{
		return left.x * left.x + left.y * left.y;
	}

	template<typename T>
	float GetVectorLengthSqrt(const Vector2D<T>& left)
	{
		return std::sqrt(GetVectorLength(left));
	}

	template<typename T>
	Vector2D<T>& Normalize(const Vector2D<T>& left)
	{
		return GetNormalized(left);
	}

	template<typename T>
	Vector2D<T>& GetNormalized (Vector2D<T>& left)
	{
		const float len = GetVectorLengthSqrt(left);
		if (len != 0.0f)
		{
			return left *= (1.0f / len);
		}
		return left;
	}
	
	 //This complex template allows us to convert any vector type to any other vector type (like our Vector2D to SFML's Vector and vice versa)
	template<typename U, typename V>
	U Convert(const V& v)
	{
		// decltype deduces ty[e from expression
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}

