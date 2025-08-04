#pragma once
#include <cassert>
#include "math.h"

namespace viper {
	template<typename T>
	class Vector3
	{
	public:
		T x, y, z;

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }


		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }
		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
			  
		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }
			  
		Vector3& operator += (const Vector3& v) {x += v.x; y += v.y; z += v.z; return *this;}
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
			  
		Vector3& operator += (float s) { x += s; y += s; y += s; return *this;
		}
		Vector3& operator -= (float s) { x -= s; y -= s; y -= s; return *this; }
		Vector3& operator *= (float s) { x *= s; y *= s; y *= s; return *this; }
		Vector3& operator /= (float s) { x /= s; y /= s; y /= s; return *this; }

		float LengthSqr() { return ((x * x) + (y * y)) + (z * z); }
		float Length() { return viper::sqrtf(LengthSqr()); }
	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}