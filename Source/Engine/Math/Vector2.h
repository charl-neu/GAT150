#pragma once
#include "math.h"
#include <cassert>
#include <iostream>

namespace nebula {
	template<typename T>
	class Vector2
	{
	public:
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }


		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a 2D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components, representing the squared length of the vector.</returns>
		float LengthSqr() const { return ((x * x) + (y * y)); }

		/// <summary>
		/// Calculates the length (magnitude) of a vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const { return nebula::sqrtf(LengthSqr()); }

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A new Vector2 that has the same direction as the original but with a length of 1.</returns>
		Vector2 Normalized() const { return *this / Length(); }

		/// <summary>
		/// Returns the angle, in radians, between the positive x-axis and the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
		float Angle() const { return nebula::atan2f(y, x); };

		Vector2 Rotate(float radians) const {
			Vector2 v;
			v.x = x * nebula::cosf(radians) - y * nebula::sinf(radians);
			v.y = x * nebula::sinf(radians) + y * nebula::cosf(radians);

			return v;
		}

		/// <summary>
		/// returns the cross product between two vectors
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static	float Cross(const Vector2& a, const Vector2& b) {
			return a.x * b.y - a.y * b.x;
		}

		/// <summary>
		/// returns the dot product of two vectors
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}

		/// <summary>
		/// returns the angle in radians between two vectors
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return nebula::acosf(Dot(a, b));
		}

		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			float x = Dot(a, b);
			float y = Cross(a, b);
			return nebula::atan2f(y, x);
		}

	};
	
	template<typename T>
	std::ostream& operator << (std::ostream& os, const Vector2<T>& v) {
		os << "{" << v.x << ", " << v.y << "}";
		return os;
	}

	template<typename T>
	std::istream& operator >> (std::istream& is, Vector2<T>& v) {
		char ch = '\00';

		//{x,y]

		//{
		if (!(is >> std::ws >> ch) || ch != '{') { 
			is.setstate(std::ios::failbit);
			return is; 
		}

		//x
		if (!(is >> std::ws >> v.x)) { 
			is.setstate(std::ios::failbit);
			return is; 
		}

		//,
		if (!(is >> std::ws >> ch) || ch != ',') { 
			is.setstate(std::ios::failbit); 
			return is; 
		}

		//y
		if (!(is >> std::ws >> v.y)) { 
			is.setstate(std::ios::failbit); 
			return is; 
		}

		//}
		if (!(is >> std::ws >> ch) || ch != '}') { 
			is.setstate(std::ios::failbit); 
			return is; 
		}


		return is;
	}

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}