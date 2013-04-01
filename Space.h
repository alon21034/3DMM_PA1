#ifndef __SPACE__H
#define __SPACE__H

#include "ColorImage.h"

class Vec3{
public:
	// the plane function is ax+by+c+offset = 0
	Vec3(float x,float y ,float z):X(x), Y(y), Z(z){};
	float X, Y, Z;
	float Offset;
};

class Space{
public:
	Space(Triangle**, int);
	~Space();

	void setHasColor(bool);

	ColorImage getImage(int);
private:

	int _size;
	Triangle** _list;
	bool hasColor;

	void translation(float, float, float);
	void normalize(int, int);
	void projection();
	void rotation(float, float, float, int);
	void rasterization(ColorImage&);
	void drawTriangle(ColorImage&, Triangle*);

};
#endif