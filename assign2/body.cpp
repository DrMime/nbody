#include "body.h"



body::body(float _mass, float _radius, vec3 &_position, vec3 &_velocity)
{
	mass = _mass;
	radius = _radius;
	position = new vec3(_position);
	velocity = new vec3(_velocity);
}


body::~body()
{
	delete position;
	delete velocity;
}

void body::increment(vec3 &force, float timestep) {

}
