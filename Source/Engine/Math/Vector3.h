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

	template<typename T>
	std::ostream& operator << (std::ostream& os, const Vector3<T>& v) {
		os << "{" << v.x << ", " << v.y << "," << v.z << "}";
		return os;
	}

	template<typename T>
	std::istream& operator >> (std::istream& is, Vector3<T>& v) {
		char ch = '\00';

		//{x,y,z]
		 
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

		//,
		if (!(is >> std::ws >> ch) || ch != ',') {
			is.setstate(std::ios::failbit);
			return is;
		}

		//z
		if (!(is >> std::ws >> v.z)) {
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

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}