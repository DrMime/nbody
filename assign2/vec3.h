#pragma once
#include <cmath>

class vec3
{
public:
	vec3();
	vec3(vec3& in);
	vec3(float _X, float _y, float _z);
	~vec3();
	float getx();
	float gety();
	float getz();

	friend vec3 operator+(vec3 &lhs, vec3 &rhs);
	friend vec3 operator-(vec3 &lhs, vec3 &rhs);
	friend vec3 operator*(vec3 &lhs, float &rhs);
	friend vec3 operator/(vec3 &lhs, float &rhs);
	friend float operator*(vec3 &lhs, vec3 &rhs);

	float norm();
private:
	float x, y, z;
};

