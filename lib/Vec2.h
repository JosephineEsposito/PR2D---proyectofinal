#pragma once

class Vec2
{
public:
	// ---------- Variables ---------- //
	float x;
	float y;

	float alpha;

	// ---------- Constructores ---------- //

	//Constructor de default
	Vec2();
	//Constructor con valores float
	Vec2(float _x, float _y);
	//Constructor con Vec2
	Vec2::Vec2(const Vec2& other);

	// ---------- Operaciones ---------- //

	// To obtain the sum between self and vector 2
	Vec2 operator+(const Vec2& other);
	// To obtain the sum between self and float
	Vec2 operator+(const float& other);

	// To obtain the rest between self and vector 2
	Vec2 operator-(const Vec2& other);
	// To obtain the rest between self and number
	Vec2 operator-(const float& other);

	// To obtain the product between self and a float
	Vec2 operator*(const float& other);

	// To obtain the dot product between two vectors
	float dot(const Vec2& other);

	// To obtain the division between self and a float
	Vec2 operator/(const float& other);

	// To obtain the absolute value of self
	float absolute();
	// To obtain the longitude of self
	float longitud();

	// To obtain the normal of self
	Vec2 normal();

	// ---------- Metodos adicionales ---------- //

	// To obtain the angle between self and other vector
	float angle(const Vec2& other) const;

	// To obtain distance between self and other vector
	float distance(const Vec2& other) const;

	// To rotate self given the angle and the origin
	void rotate(const float& angle, const float& fixedLen);

};