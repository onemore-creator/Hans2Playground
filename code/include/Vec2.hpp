#pragma once
#include <cstdint>
#include <iostream>

namespace Halib::Data
{
	struct Vec2
	{
		short x;
		short y;

		Vec2 ();
		Vec2 (short xy);
		Vec2 (short x, short);
		Vec2 operator+(const Vec2& other) const;
		Vec2 operator-(const Vec2& other) const;
		Vec2 operator*(const Vec2& other) const;
		Vec2 operator/(const Vec2& other) const;
		Vec2 operator+(const short& other) const;
		Vec2 operator-(const short& other) const;
		Vec2 operator*(const short& other) const;
		Vec2 operator/(const short& other) const;

		void operator+=(const Vec2& other);
		void operator-=(const Vec2& other);
		void operator*=(const Vec2& other);
		void operator/=(const Vec2& other);
		void operator+=(const short& other);
		void operator-=(const short& other);
		void operator*=(const short& other);
		void operator/=(const short& other);

		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;

		short operator[](size_t idx);

		float Magnitude();

		/// @brief Interpolates linearly between a and b
		/// @param a 
		/// @param b 
		/// @param t value between 0 and 1. 0 == a, 1 == b.
		/// @return 
		static Vec2 Lerp(const Vec2& a, const Vec2& b, float t);
	};

	std::ostream& operator<<(std::ostream& os, const Vec2& vec);
} // namespace Halib::Data