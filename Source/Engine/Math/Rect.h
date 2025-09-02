#pragma once

namespace viper {

	template <typename T>
	struct Rect {
		T x, y, w, h;
		Rect() : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {}

		Rect(T ix, T iy, T iw, T ih) : x{ ix }, y{ iy }, w{ iw }, h{ ih } {}
	};

	using rect = Rect<float>;
	using irect = Rect<int>;
}