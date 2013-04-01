#ifndef __VERTEX__H
#define __VERTEX__H

#include "ColorImage.h"

class Vertex {
public:
	Vertex(float, float, float);
	Vertex(Vertex*);
	~Vertex();

	void setCoordinate(float, float, float);
	void setColor(float, float, float);
	void scale(float, float, float, float);
	void projection();
	void rotation(float, float, float);

	void print();
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	
	Color getColor(){ return _p; }
private:
	float _x;
	float _y;
	float _z;

	float x;
	float y;
	float z;

	Color _p;
};

#endif