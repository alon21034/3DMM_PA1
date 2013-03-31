#include "Vertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Vertex::Vertex(float xi, float yi, float zi): _x(xi), _y(yi), _z(zi) {
	this->x = xi;
	this->y = yi;
	this->z = zi;
	_p = new Color(255, 255, 255);
}

Vertex::Vertex(Vertex* v) {
	this->x = _x = v->getX();
	this->y = _y = v->getY();
	this->z = _z = v->getZ();
	_p = new Color(255, 255, 255);
}

Vertex::~Vertex() {
	
}

void Vertex::scale(float rx, float ry, float ox, float oy) {
	//cout << x << "  " << y << " -> ";
	x = (x+ox)*rx + 1;
	y = (y+oy)*ry + 1;
	//cout << x << "  " << y << endl;
}

void Vertex::projection() {
	//_p->Z = z;
	// float temp = z;
	// z = x;
	// x = temp;
}

void Vertex::setColor(float r, float g, float b) {
	_p = new Color(r,g,b);
}

void Vertex::print() {
	printf("coordinate = (%f, %f, %f) \t color = (%d, %d, %d)\n",
			 _x, _y, _z, _p->R, _p->G, _p->B);
}
