#include "Vec2.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.14159265358979323846f

// ---------- Constructores ---------- //

Vec2::Vec2()
{
	x = 0;
	y = 0;
	alpha = 0;
}
Vec2::Vec2(float _x, float _y)
{
	x = _x;
	y = _y;
	alpha = 0;
}
Vec2::Vec2(const Vec2& other)
{
	x = other.x;
	y = other.y;
	alpha = other.alpha;
}


// ---------- Operaciones ---------- //

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(x + other.x, y + other.y);
}
Vec2 Vec2::operator+(const float& other)
{
	return Vec2(x + other, y + other);
}


Vec2 Vec2::operator-(const Vec2& other)
{
	return Vec2(x - other.x, y - other.y);
}
Vec2 Vec2::operator-(const float& other)
{
	return Vec2(x - other, y - other);
}


Vec2 Vec2::operator*(const float& other)
{
	return Vec2(x * other, y * other);
}


float Vec2::dot(const Vec2& other)
{
	return (x * other.x + y * other.y);
}


Vec2 Vec2::operator/(const float& other)
{
	return Vec2(x / other, y / other);
}



float Vec2::absolute()
{
	float mod = longitud();
	if (mod < 0.0f)
	{
		return 0.0f;
	}
	return mod;
}


float Vec2::longitud()
{
	return sqrt((x * x) + (y * y));
}


Vec2 Vec2::normal()
{
	float lon = longitud();

	if (lon == 0.0f)
	{
		return Vec2(0.0f, 0.0f);
	}

	return Vec2(x / lon, y / lon);
}



// ---------- Metodos adicionales ---------- //

float Vec2::angle(const Vec2& other) const
{
	float dot = (x * other.x + y * other.y);
	float norm_self  = sqrt( (      x *       x) + (      y *       y));
	float norm_other = sqrt( (other.x * other.x) + (other.y * other.y));

	float alpha = (dot) / (norm_self * norm_other);
	return alpha * (PI / 180.0);
}

float Vec2::distance(const Vec2& other) const
{
	return sqrt(((x - other.x) * (x - other.x)) + ((y - other.y) * (y - other.y)));
}

void Vec2::rotate(const float& angle, const float& fixedLen)
{
	x = x + cos(angle) * fixedLen;
	y = y - sin(angle) * fixedLen;
}
