#ifndef __VERTEX__H
#define __VERTEX__H

#include "ColorImage.h"

class Vertex {
public:
	Vertex();
	~Vertex();

	void setCoordinate(float, float, float);
	void setPixel(Pixel*);

	void print();
private:
	float _x;
	float _y;
	float _z;

	Pixel _p;
};

#endif