#include "vec3.h"

class body
{
public:
	body(float _mass, float _radius, vec3 &_position, vec3 &_velocity);
	~body();
	void increment(vec3 &force, float timestep);
	vec3& pos();
	float getmass();
	body& operator=(const body &other);
	
private:
	float mass;
	float radius;
	vec3 position;
	vec3 velocity;
};

