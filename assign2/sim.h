#include "body.h"
#include <vector>

class sim
{
public:
	sim();
	~sim();

	void advance(float time);
	int bodycount();
	std::vector<std::pair<float, float>> positions();
private:
	float gConst = 100.0;
	std::vector<body> bodies;
};

