#include "Vertex.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Vertex::Vertex(float xi, float yi, float zi): _x(xi), _y(yi), _z(zi) {
	this->x = xi;
	this->y = yi;
	this->z = zi;
}

Vertex::Vertex(Vertex* v) {
	this->x = _x = v->getX();
	this->y = _y = v->getY();
	this->z = _z = v->getZ();
	this->_p = v->getColor();
}

Vertex::~Vertex() {
	
}

void Vertex::scale(float rx, float ry, float rz, float ox, float oy, float oz) {
	//cout << x << "  " << y << " -> ";
	x = (x+ox)*rx;
	y = (y+oy)*ry;
	z = (z+oz)*rz;
	//cout << x << "  " << y << endl;
}

void Vertex::projection() {

}

void Vertex::rotation(float a, float b, float c) {
	Utils::rotation(a, b, c, x, y, z);
}

void Vertex::setColor(float r, float g, float b) {
	//cout << "Vertex::setColor " << r << " " << g << " " << b << endl;
	_p.R = r;
	_p.G = g;
	_p.B = b;
}

void Vertex::translation(float ox, float oy, float oz) {
	x += ox;
	y += oy;
	z += oz;
}

void Vertex::print() {
	printf("coordinate = (%f, %f, %f) \t color = (%d, %d, %d)\n",
			 _x, _y, _z, _p.R, _p.G, _p.B);
}
