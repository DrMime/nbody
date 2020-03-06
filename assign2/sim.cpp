#include "sim.h"
#include <iostream>


sim::sim()
{
	bodies.push_back(body(50.0, 5, vec3(0, 0, 0), vec3(0, 0, 0)));
	bodies.push_back(body(0.1, 1, vec3(0, 40, 0), vec3(-8, 0, 0)));
	//bodies.push_back(body(0.1, 1, vec3(0, -30, 0), vec3(6, 0, 0)));
}


sim::~sim()
{
}


void sim::advance(float time) {
	for (unsigned int i = 0; i < bodies.size(); i++) {
		vec3 force(0.0, 0.0, 0.0);
		for (unsigned int j = 0; j < bodies.size(); j++) {
			if (j != i) {
				vec3 r = bodies[j].pos() - bodies[i].pos();
				float m1 = bodies[i].getmass();
				float m2 = bodies[j].getmass();
				float mag = gConst * m1*m2 / r.norm()/r.norm();
				vec3 contri(r.getx()*mag / r.norm(), r.gety()*mag / r.norm(), r.getz()*mag / r.norm());\
				force = force + contri;
			}
		}
		/*std::cout << "position = ";
		bodies[i].pos().print();
		std::cout << "force = ";
		force.print();*/
		bodies[i].increment(force, time);
	}
}


std::vector<std::pair<float, float>> sim::positions()
{
	std::vector<std::pair<float, float>> result;
	for (unsigned int i = 0; i < bodies.size(); i++) {
		result.push_back(std::pair<float, float>(bodies[i].pos().getx(), bodies[i].pos().gety()));
	}
	return result;
}

int sim::bodycount() {
	return bodies.size();
}