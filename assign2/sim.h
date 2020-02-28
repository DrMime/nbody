#include "body.h"

class sim
{
public:
	sim();
	~sim();

	void advance(float time);
	int bodycount();
	float** positions();
private:
	int _numbodies;
	body* bodies;
};

