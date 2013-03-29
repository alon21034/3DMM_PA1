#ifndef __SPACE__H
#define __SPACE__H

#include "ColorImage.h"

class Vec3{
public:
	Vec3(float x,float y ,float z):X(x), Y(y), Z(z){};
	float X, Y, Z;
};

class Space{
public:
	Space(Triangle**, int);
	~Space();

	ColorImage getImage(Vec3, int, int);
private:

	int _size;
	Triangle** _list;

	void normalize();
	void rasterization();

};
#endif