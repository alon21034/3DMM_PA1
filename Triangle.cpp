#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3) {
	_v1 = new Vertex(v1);
	_v2 = new Vertex(v2);
	_v3 = new Vertex(v3);
}

void Triangle::drawVertex(ColorImage& image) {
	//cout << "draw vertex" << endl;
	//Color color = _v1->getColor();
	//cout << "x: " << _v1->getX() << ", y: " << _v1->getY() << ", c: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
	image.setColor(_v1->getX(), _v1->getY(), _v1->getColor());
	image.setColor(_v2->getX(), _v2->getY(), _v2->getColor());
	image.setColor(_v3->getX(), _v3->getY(), _v3->getColor());
}

void Triangle::scale(float rx, float ry, float ox, float oy) {
	_v1->scale(rx, ry, ox, oy);
	_v2->scale(rx, ry, ox, oy);
	_v3->scale(rx, ry, ox, oy);
}

void Triangle::projection() {
	_v1->projection();
	_v2->projection();
	_v3->projection();
}

Vertex* Triangle::getVertex(int a) {
	switch(a) {
		case 0:
			return _v1;
		case 1:
			return _v2;
		case 2:
			return _v3;
		default:
			return NULL;
	}
}