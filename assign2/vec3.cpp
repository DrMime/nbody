#include "vec3.h"



vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

vec3::vec3(vec3 &in) {
	x = in.x;
	y = in.y;
	z = in.z;
}

vec3::vec3(float _X, float _y, float _z) 
{
	x = _X;
	y = _y;
	z = _z;
}

vec3::~vec3()
{
}

vec3 operator+(vec3 &lhs, vec3 &rhs)
{
	return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

vec3 operator-(vec3 &lhs, vec3 &rhs)
{
	return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

vec3 operator*(vec3 &lhs, float &rhs)
{
	return vec3(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs);
}

vec3 operator/(vec3 &lhs, float &rhs)
{
	if (rhs == 0) { return lhs; }
	return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

float operator*(vec3 &lhs, vec3 &rhs)
{
	return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
}


float vec3::norm()
{
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}


float vec3::getx() {
	return x;
}
float vec3::gety() {
	return y;
}
float vec3::getz() {
	return z;
}