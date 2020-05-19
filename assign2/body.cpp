#include "body.h"

#include <iostream>

body::body(float _mass, float _radius, vec3 &_position, vec3 &_velocity)
	:position(_position.getx(), _position.gety(), _position.getz()),
	velocity(_velocity)
{
	mass = _mass;
	radius = _radius;
}


body::~body()
{
}


vec3& body::pos() {
	return position;
}

void body::increment(vec3 &force, float timestep) {
	//std::cout << "increment with force ";
	//force.print();
	float temp = timestep / mass;
	vec3 dv((force).getx()*temp, force.gety()*temp, 0.0);
	/*std::cout << "dv = ";
	dv.print();*/
	if (dv.norm() > velocity.norm()) {
		velocity = dv + velocity;
	}
	else {
		velocity = velocity + dv;
	}
	//std::cout << "newvel = ";
	//velocity.print();
	vec3 dr((velocity).getx()*timestep, velocity.gety()*timestep, 0.0);
	if (dr.norm() > position.norm()) {
		position = dr + position;
	}
	else {
		position = position + dr;
	}
	/*std::cout << "newpos = ";
	position.print();*/
}

float body::getmass() {
	return mass;
}

body& body::operator=(const body &other) {
	mass = other.mass;
	radius = other.radius;
	position = other.position;
	velocity = other.velocity;
	return *this;
}