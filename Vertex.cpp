#include "Vertex.h"
#include <stdio.h>
#include <stdlib.h>

Vertex::Vertex() {

}

Vertex::~Vertex() {
	
}

void Vertex::setColor(float r, float g, float b) {
	_r = r;
	_g = g;
	_b = b;
}

void Vertex::setCoordinate(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

void Vertex::print() {
	printf("coordinate = (%f, %f, %f) \t color = (%f, %f, %f)\n",
			 _x, _y, _z, _r, _g, _b);
}
