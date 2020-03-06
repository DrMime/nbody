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
	vec3 dv((force*temp).getx(), force.gety()*temp, (force*temp).getz());
	/*std::cout << "dv = ";
	dv.print();*/
	velocity = velocity + dv;
	//std::cout << "newvel = ";
	//velocity.print();
	vec3 dr((velocity*timestep).getx(), velocity.gety()*timestep, (velocity*timestep).getz());
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