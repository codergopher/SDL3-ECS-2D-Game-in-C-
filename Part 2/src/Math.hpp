#pragma once

#include <string>
#include <math.h>
#include <bits/stdc++.h>
#include <box2d/box2d.h>

struct Vec2i
{
	int x, y;
	Vec2i():x(0.f), y(0.f) {};
	Vec2i(int p_x, int p_y)
	:x(p_x), y(p_y) {}

	std::string print()
	{
		std::string s = "";
		s += std::to_string(x);
		s += ", ";
		s += std::to_string(y);

		return s;
	}

	float length()
	{
		return sqrt(x*x + y*y);
	}

	void operator+=(Vec2i p_v)
	{
		x += p_v.x;
		y += p_v.y;
	}
	void operator-=(Vec2i p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
	}
	void operator*=(Vec2i p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
	}
	void operator/=(Vec2i p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
	}

	// Scalar
	void operator+=(int p_s)
	{
		x += p_s;
		y += p_s;
	}
	void operator-=(int p_s)
	{
		x -= p_s;
		y -= p_s;
	}
	void operator*=(int p_s)
	{
		x *= p_s;
		y *= p_s;
	}
	void operator/=(int p_s)
	{
		x /= p_s;
		y /= p_s;
	}
};

struct Vec2
{
	float x, y;
	Vec2():x(0.f), y(0.f) {};
	Vec2(float p_x, float p_y)
	:x(p_x), y(p_y) {}

	std::string print()
	{
		std::string s = "";
		s += std::to_string(x);
		s += ", ";
		s += std::to_string(y);

		return s;
	}


	float length()
	{
		return sqrt(x*x + y*y);
	}

	void operator+=(Vec2 p_v)
	{
		x += p_v.x;
		y += p_v.y;
	}
	void operator-=(Vec2 p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
	}
	void operator*=(Vec2 p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
	}
	void operator/=(Vec2 p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
	}

	// Scalar
	void operator+=(float p_s)
	{
		x += p_s;
		y += p_s;
	}
	void operator-=(float p_s)
	{
		x -= p_s;
		y -= p_s;
	}
	void operator*=(float p_s)
	{
		x *= p_s;
		y *= p_s;
	}
	void operator/=(float p_s)
	{
		x /= p_s;
		y /= p_s;
	}
};



struct Vec3
{
	float x, y, z;
	Vec3():x(0.f), y(0.f), z(0.f) {};
	Vec3(float p_x, float p_y, float p_z)
	:x(p_x), y(p_y), z(p_z) {}

	std::string print()
	{
		std::string s = "";
		s += std::to_string(x);
		s += ", ";
		s += std::to_string(y);
		s += ", ";
		s += std::to_string(z);

		return s;
	}


	float length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	void operator+=(Vec3 p_v)
	{
		x += p_v.x;
		y += p_v.y;
		z += p_v.z;
	}
	void operator-=(Vec3 p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
		z -= p_v.z;
	}
	void operator*=(Vec3 p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
		z *= p_v.z;
	}
	void operator/=(Vec3 p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
		z /= p_v.z;
	}

	// Scalar
	void operator+=(float p_s)
	{
		x += p_s;
		y += p_s;
		z += p_s;
	}
	void operator-=(float p_s)
	{
		x -= p_s;
		y -= p_s;
		z -= p_s;
	}
	void operator*=(float p_s)
	{
		x *= p_s;
		y *= p_s;
		z *= p_s;
	}
	void operator/=(float p_s)
	{
		x /= p_s;
		y /= p_s;
		z /= p_s;
	}
};


struct IntRect
{
	int x, y, w, h;
	IntRect() {}
	IntRect(int p_x, int p_y, int p_w, int p_h) 
	:x(p_x), y(p_y), w(p_w), h(p_h) 
	{}
};

float roundToScale(float f, float p_zoom);

Vec2 roundToScale(Vec2 vec, float p_zoom);

int roundToInt(float f);

float distance(Vec2 a, Vec2 b);
float sqrDistance(Vec2 a, Vec2 b);

float dotProduct(Vec2 a, Vec2 b);

Vec2 normalise(Vec2 vec);

Vec2 clamp(Vec2 vec, Vec2 min, Vec2 max);

Vec2 toVec2(const b2Vec2& vec);
Vec2 scaleToVec2(const b2Vec2& vec);

b2Vec2 to_b2Vec2( const Vec2& vec);
b2Vec2 scaleToBox2D( const Vec2& vec);

struct Mat3
{
	Mat3();

	float m00, m10, m20,
	      m01, m11, m21,
	      m02, m12, m22;

	void setScale(Vec2 s);
	void setTranslate(Vec2 d);
	// In radians
	void setRotation(float theta);

	Vec3 getXCol() const;
	Vec3 getYCol() const;
	Vec3 getZCol() const;

	void setXCol(Vec3 p_vec);
	void setYCol(Vec3 p_vec);
	void setZCol(Vec3 p_vec);

};

Mat3 operator*(const Mat3& p_matrixA, const Mat3& p_matrixB);

Vec3 operator*(const Mat3& p_matrix, const Vec3& p_vec);
Vec3 operator*(const Vec3& p_vec, const Mat3& p_matrix);

Vec2 operator*(const Mat3& p_matrix, const Vec2& p_vec);
Vec2 operator*(const Vec2& p_vec, const Mat3& p_matrix);

Vec2i operator-(Vec2i a);
Vec2i operator+(Vec2i a, Vec2i b);
Vec2i operator-(Vec2i a, Vec2i b);
Vec2i operator*(Vec2i a, Vec2i b);
Vec2i operator/(Vec2i a, Vec2i b);
Vec2i operator+(Vec2i a, float s);
Vec2i operator-(Vec2i a, float s);
Vec2i operator*(Vec2i a, float s);
Vec2i operator/(Vec2i a, float s);
Vec2i operator+(float s, Vec2i a);
Vec2i operator-(float s, Vec2i a);
Vec2i operator*(float s, Vec2i a);
Vec2i operator/(float s, Vec2i a);

Vec2 operator-(Vec2 a);
Vec2 operator+(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a, Vec2 b);
Vec2 operator*(Vec2 a, Vec2 b);
Vec2 operator/(Vec2 a, Vec2 b);
Vec2 operator+(Vec2 a, float s);
Vec2 operator-(Vec2 a, float s);
Vec2 operator*(Vec2 a, float s);
Vec2 operator/(Vec2 a, float s);
Vec2 operator+(float s, Vec2 a);
Vec2 operator-(float s, Vec2 a);
Vec2 operator*(float s, Vec2 a);
Vec2 operator/(float s, Vec2 a);

Vec3 operator-(Vec3 a);
Vec3 operator+(Vec3 a, Vec3 b);
Vec3 operator-(Vec3 a, Vec3 b);
Vec3 operator*(Vec3 a, Vec3 b);
Vec3 operator/(Vec3 a, Vec3 b);
Vec3 operator+(Vec3 a, float s);
Vec3 operator-(Vec3 a, float s);
Vec3 operator*(Vec3 a, float s);
Vec3 operator/(Vec3 a, float s);
Vec3 operator+(float s, Vec3 a);
Vec3 operator-(float s, Vec3 a);
Vec3 operator*(float s, Vec3 a);
Vec3 operator/(float s, Vec3 a);

namespace math
{
	const float degToRad = 0.017453293f;
	const float pi = 3.14159265359f;
}


float lerp(const float& a, const float& b, const float& t);

Vec2 lerp(const Vec2& a, const Vec2& b, const float& t);

Vec3 lerp(const Vec3& a, const Vec3& b, const float& t);
