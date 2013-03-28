#include "Vertex.h"
#include <stdio.h>
#include <stdlib.h>

Vertex::Vertex() {

}

Vertex::~Vertex() {
	
}

void Vertex::setPixel(Pixel* p) {
	_p = *p;
}

void Vertex::setCoordinate(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
}

void Vertex::print() {
	printf("coordinate = (%f, %f, %f) \t color = (%d, %d, %d)\n",
			 _x, _y, _z, _p.R, _p.G, _p.B);
}
