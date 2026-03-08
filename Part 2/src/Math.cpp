#include "Math.hpp"
#include <math.h>
#include <bits/stdc++.h>
#include <iostream>

float roundToScale(float f, float zoom)
{
	float pixelUnit = 1.f/zoom;
	float halfPixelUnit = pixelUnit/2.f;

	float d = std::fmod(f, pixelUnit);


	d = abs(d);

	if (d >= halfPixelUnit)
		f += (pixelUnit - d);
	else
		f -= d;


	return f;
}

Vec2 roundToScale(Vec2 vec, float zoom)
{
	vec.x = roundToScale(vec.x, zoom);
	vec.y = roundToScale(vec.y, zoom);

	return vec;
}

int roundToInt(float f)
{
	float d = std::fmod(f, 1.f);

	d = abs(d);
	if(d >= 0.5)
		f += (1.f - d);
	else
		f -= d;

	return (int)f;
}

float distance(Vec2 a, Vec2 b)
{
	return sqrt( powf((a.x - b.x), 2) + powf((a.y - b.y), 2));
}
float sqrDistance(Vec2 a, Vec2 b)
{
	return powf((a.x - b.x), 2) + powf((a.y - b.y), 2);
}



float dotProduct(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

Vec2 normalise(Vec2 vec)
{
	float length = vec.length();

	if (length != 0.0f)
	{
		length = 1.0f / length;
		vec.x *= length;
		vec.y *= length;
	}
	return vec;
}

Vec2 clamp(Vec2 vec, Vec2 min, Vec2 max)
{
	Vec2 clamped = vec;

	if (vec.x < min.x)
		clamped.x = min.x;
	if (vec.y < min.y)
		clamped.y = min.y;

	if (vec.x > max.x)
		clamped.x = max.x;
	if (vec.y > max.y)
		clamped.y = max.y;

	return clamped;
}

Vec2 toVec2(const b2Vec2& vec)
{
	return {vec.x, vec.y};
}

Vec2 scaleToVec2(const b2Vec2& vec)
{
	return {vec.x * 30.f, vec.y * 30.f};
}

b2Vec2 to_b2Vec2(const Vec2& vec)
{
	return {vec.x, vec.y};
}

b2Vec2 scaleToBox2D( const Vec2& vec)
{
	return {vec.x / 30.f, vec.y / 30.f};
}



Mat3::Mat3()
{
	m00 = 1.f; m10 = 0.f; m20 = 0;
	m01 = 0.f; m11 = 1.f; m21 = 0;
	m02 = 0.f; m12 = 0.f; m22 = 1.f;
}

void Mat3::setScale(Vec2 s)
{
	m00 = s.x; m10 = 0;   m20 = 0;
	m01 = 0;   m11 = s.y; m21 = 0;
	m02 = 0;   m12 = 0;   m22 = 1;
//  _         _
// |  Sx 0  0  |
// |  0  Sy 0  |
// |_ 0  0  1 _|
}

void Mat3::setTranslate(Vec2 d)
{
	m00 = 1; m10 = 0; m20 = d.x;
	m01 = 0; m11 = 1; m21 = d.y;
	m02 = 0; m12 = 0; m22 = 1;
//  _        _
// |  1 0 Dx  |
// |  0 1 Dy  |
// |_ 0 0  1 _|
}

void Mat3::setRotation(float theta)
{
	float cos = std::cos(theta);
	float sin = std::sin(theta);


	m00 = cos; m10 = -sin; m20 = 0;
	m01 = sin; m11 = cos;  m21 = 0;
	m02 = 0;   m12 = 0;    m22 = 1;

//  _          _
// |  cos sin 0 |
// | -sin cos 0 |
// |_ 0   0   1_|
}

Vec3 Mat3::getXCol() const
{
	return {m00, m01, m02};
}
Vec3 Mat3::getYCol() const 
{
	return {m10, m11, m12};
}
Vec3 Mat3::getZCol() const
{
	return {m20, m21, m22};
}

void Mat3::setXCol(Vec3 p_vec)
{
	m00 = p_vec.x;
	m01 = p_vec.y;
	m02 = p_vec.z;
}
void Mat3::setYCol(Vec3 p_vec)
{
	m10 = p_vec.x;
	m11 = p_vec.y;
	m12 = p_vec.z;
}
void Mat3::setZCol(Vec3 p_vec)
{
	m20 = p_vec.x;
	m21 = p_vec.y;
	m22 = p_vec.z;
}


Mat3 operator*(const Mat3& p_matrixA, const Mat3& p_matrixB)
{
	Mat3 result;

	Vec3 xColA = p_matrixA.getXCol();
	Vec3 yColA = p_matrixA.getYCol();
	Vec3 zColA = p_matrixA.getZCol();

	xColA = xColA * p_matrixB;
	yColA = yColA * p_matrixB;
	zColA = zColA * p_matrixB;

	result.setXCol(xColA);
	result.setYCol(yColA);
	result.setZCol(zColA);

	return result;

}

Vec3 operator*(const Mat3& p_matrix, const Vec3& p_vec)
{
	Vec3 xCol = p_matrix.getXCol();
	Vec3 yCol = p_matrix.getYCol();
	Vec3 zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * p_vec.z;

	Vec3 result = xCol + yCol + zCol;

	return result;
}


Vec3 operator*(const Vec3& p_vec, const Mat3& p_matrix)
{
	Vec3 xCol = p_matrix.getXCol();
	Vec3 yCol = p_matrix.getYCol();
	Vec3 zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * p_vec.z;

	Vec3 result = xCol + yCol + zCol;

	return result;
}

Vec2 operator*(const Mat3& p_matrix, const Vec2& p_vec)
{
	Vec3 xCol = p_matrix.getXCol();
	Vec3 yCol = p_matrix.getYCol();
	Vec3 zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * 1.f;

	Vec3 result = xCol + yCol + zCol;

	return Vec2(result.x, result.y);
}


Vec2 operator*(const Vec2& p_vec, const Mat3& p_matrix)
{
	Vec3 xCol = p_matrix.getXCol();
	Vec3 yCol = p_matrix.getYCol();
	Vec3 zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * 1.f;

	Vec3 result = xCol + yCol + zCol;

	return Vec2(result.x, result.y);
}


Vec2i operator-(Vec2i a)
{
	return {-a.x, -a.y};
}

Vec2i operator+(Vec2i a, Vec2i b)
{
	return {a.x + b.x, a.y + b.y};
}
Vec2i operator-(Vec2i a, Vec2i b)
{
	return {a.x - b.x, a.y - b.y};
}
Vec2i operator*(Vec2i a, Vec2i b)
{
	return {a.x * b.x, a.y * b.y};
}
Vec2i operator/(Vec2i a, Vec2i b)
{
	return {a.x / b.x, a.y / b.y};
}

Vec2i operator+(Vec2i a, int s)
{
	return {a.x + s, a.y + s};
}
Vec2i operator-(Vec2i a, int s)
{
	return {a.x - s, a.y - s};
}
Vec2i operator*(Vec2i a, int s)
{
	return {a.x * s, a.y * s};
}
Vec2i operator/(Vec2i a, int s)
{
	return {a.x / s, a.y / s};
}

Vec2i operator+(int s, Vec2i a)
{
	return {a.x + s, a.y + s};
}
Vec2i operator-(int s, Vec2i a)
{
	return {a.x - s, a.y - s};
}
Vec2i operator*(int s, Vec2i a)
{
	return {a.x * s, a.y * s};
}
Vec2i operator/(int s, Vec2i a)
{
	return {a.x / s, a.y / s};
}




Vec2 operator-(Vec2 a)
{
	return {-a.x, -a.y};
}

Vec2 operator+(Vec2 a, Vec2 b)
{
	return {a.x + b.x, a.y + b.y};
}
Vec2 operator-(Vec2 a, Vec2 b)
{
	return {a.x - b.x, a.y - b.y};
}
Vec2 operator*(Vec2 a, Vec2 b)
{
	return {a.x * b.x, a.y * b.y};
}
Vec2 operator/(Vec2 a, Vec2 b)
{
	return {a.x / b.x, a.y / b.y};
}

Vec2 operator+(Vec2 a, float s)
{
	return {a.x + s, a.y + s};
}
Vec2 operator-(Vec2 a, float s)
{
	return {a.x - s, a.y - s};
}
Vec2 operator*(Vec2 a, float s)
{
	return {a.x * s, a.y * s};
}
Vec2 operator/(Vec2 a, float s)
{
	return {a.x / s, a.y / s};
}

Vec2 operator+(float s, Vec2 a)
{
	return {a.x + s, a.y + s};
}
Vec2 operator-(float s, Vec2 a)
{
	return {a.x - s, a.y - s};
}
Vec2 operator*(float s, Vec2 a)
{
	return {a.x * s, a.y * s};
}
Vec2 operator/(float s, Vec2 a)
{
	return {a.x / s, a.y / s};
}

/* Vector 3f */

Vec3 operator-(Vec3 a)
{
	return {-a.x, -a.y, -a.z};
}

Vec3 operator+(Vec3 a, Vec3 b)
{
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Vec3 operator-(Vec3 a, Vec3 b)
{
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec3 operator*(Vec3 a, Vec3 b)
{
	return {a.x * b.x, a.y * b.y, a.z * b.z};
}
Vec3 operator/(Vec3 a, Vec3 b)
{
	return {a.x / b.x, a.y / b.y, a.z / b.z};
}

Vec3 operator+(Vec3 a, float s)
{
	return {a.x + s, a.y + s, a.z + s};
}
Vec3 operator-(Vec3 a, float s)
{
	return {a.x - s, a.y - s, a.z - s};
}
Vec3 operator*(Vec3 a, float s)
{
	return {a.x * s, a.y * s, a.z * s};
}
Vec3 operator/(Vec3 a, float s)
{
	return {a.x / s, a.y / s, a.z / s};
}

Vec3 operator+(float s, Vec3 a)
{
	return {a.x + s, a.y + s, a.z + s};
}
Vec3 operator-(float s, Vec3 a)
{
	return {a.x - s, a.y - s, a.z - s};
}
Vec3 operator*(float s, Vec3 a)
{
	return {a.x * s, a.y * s, a.z * s};
}
Vec3 operator/(float s, Vec3 a)
{
	return {a.x / s, a.y / s, a.z / s};
}


float lerp(const float& a, const float& b, const float& t)
{
	return  b * t + a * (1.0f - t);
}

Vec2 lerp(const Vec2& a, const Vec2& b, const float& t)
{
	return b * t + a * (1.0f - t);
}

Vec3 lerp(const Vec3& a, const Vec3& b, const float& t)
{
	return b * t + a * (1.0f - t);
}