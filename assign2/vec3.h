#pragma once
#include <cmath>

class vec3
{
public:
	vec3();
	vec3(float _X, float _y, float _z);
	~vec3();
	float getx();
	float gety();
	float getz();

	vec3& operator+(vec3 &rhs);
	vec3& operator-(vec3 &rhs);
	vec3& operator*(float rhs);
	vec3& operator/(float rhs);
	float operator*(vec3 &rhs);

	float norm();
	void print();
private:
	float x, y, z;
};

