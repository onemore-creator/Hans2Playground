#include "Vec2.hpp"
#include <cmath>
#include <cstdint>
#include <algorithm>

namespace Halib::Data
{
	Vec2::Vec2()
	{
		x = 0;
		y = 0;
	}

	Vec2::Vec2(short xy)
	{
		x = xy;
		y = xy;
	}
	
	Vec2::Vec2(short x, short y)
	{
		this->x = x;
		this->y = y;
	}
	
	Vec2 Vec2::operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}
	Vec2 Vec2::operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}
	Vec2 Vec2::operator*(const Vec2& other) const
	{
		return Vec2(x * other.x, y * other.y);
	}
	Vec2 Vec2::operator/(const Vec2& other) const
	{
		return Vec2(x / other.x, y / other.y);
	}
	
	Vec2 Vec2::operator+(const short& other) const
	{
		return Vec2(x + other, y + other);
	}

	Vec2 Vec2::operator-(const short& other) const
	{
		return Vec2(x - other, y - other);
	}

	Vec2 Vec2::operator*(const short& other) const
	{
		return Vec2(x * other, y * other);
	}

	Vec2 Vec2::operator/(const short& other) const
	{
		return Vec2(x / other, y / other);
	}

	bool Vec2::operator==(const Vec2& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	bool Vec2::operator!=(const Vec2& other) const
	{
		return !(*this == other);
	}
	

	short Vec2::operator[](size_t idx)
	{
		switch (idx)
		{
		case 0: return x;
		case 1: return y;
		default: return INT16_MIN;
		}
	}

	float Vec2::Magnitude()
	{
		float x = this->x;
		float y = this->y;
		return std::sqrt(x * x + y * y);
	}

	Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		short x = (1 - t) * a.x + t * b.x;
		short y = (1 - t) * a.y + t * b.y;
		return Vec2(x, y);
	}
	
} // namespace Halib::Data