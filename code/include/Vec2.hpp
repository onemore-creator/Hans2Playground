#pragma once
#include <cstdint>

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
		
		/// @brief Component wise multiplication!
		/// @param other 
		/// @return 
		Vec2 operator*(const Vec2& other) const;
		
				/// @brief Component wise division!
				/// @param other 
				/// @return 
				Vec2 operator/(const Vec2& other) const;

		Vec2 operator+(const short& other) const;
		Vec2 operator-(const short& other) const;
		Vec2 operator*(const short& other) const;
		Vec2 operator/(const short& other) const;

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
} // namespace Halib::Data