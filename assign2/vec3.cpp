#include "vec3.h"
#include <iostream>


vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
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

vec3& vec3::operator+(vec3 &rhs)
{
	return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

vec3& vec3::operator-(vec3 &rhs)
{
	return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

vec3& vec3::operator*(float rhs)
{
	return vec3(x*rhs, y*rhs, z*rhs);
}

vec3& vec3::operator/(float rhs)
{
	if (rhs == 0) { return *this; }
	return vec3(x / rhs, y / rhs, z / rhs);
}

float vec3::operator*(vec3 &rhs)
{
	return (x*rhs.x + y*rhs.y + z*rhs.z);
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

void vec3::print() {
	std::cout << "x " << x << " y " << y << std::endl;
}