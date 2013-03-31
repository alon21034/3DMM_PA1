#include "Triangle.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

using namespace std;

Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3) {
	_v1 = new Vertex(v1);
	_v2 = new Vertex(v2);
	_v3 = new Vertex(v3);
}

void Triangle::drawVertex(ColorImage& image) {
	//cout << "draw vertex" << endl;
	Color color = _v1->getColor();
	cout << "x: " << _v1->getX() << ", y: " << _v1->getY() << ", c: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
	image.setColor(_v1->getX(), _v1->getY(), _v1->getColor());
	image.setColor(_v2->getX(), _v2->getY(), _v2->getColor());
	image.setColor(_v3->getX(), _v3->getY(), _v3->getColor());
}

void Triangle::drawEdge(ColorImage& image) {
	drawLine(image, _v1, _v2);
	drawLine(image, _v2, _v3);
	drawLine(image, _v3, _v1);
}

void Triangle::drawLine(ColorImage& image, Vertex* v1, Vertex* v2) {

	// maybe we can reuse some variable?
	float x2 = v2->getX();
	float x1 = v1->getX();
	float y2 = v2->getY();
	float y1 = v1->getY();

	Color color1 = v1->getColor();
	Color color2 = v2->getColor();

	float xDiff = (x2 - x1);
	float yDiff = (y2 - y1);

	if (xDiff == 0.0f && yDiff == 0.0f) {
		image.setColor(x1, y1, color1);
		return;
	}

	if (fabs(xDiff) > fabs(yDiff)) {
		// vertical
		float xmin, xmax;
		if (x1 < x2) {
			xmin = x1;
			xmax = x2;
		} else {
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = yDiff / xDiff;
		for (float x = xmin; x <= xmax; x += 1.0f) {
			float y = y1 + ((x - x1) * slope);
			Color color = Utils::blendColor(color1, color2, ((x - x1) / xDiff));
			image.setColor(x, y, color);
		}
	} else {
		// vertical 
		float ymin, ymax;
		if (y1 < y2) {
			ymin = y1;
			ymax = y2;
		} else {
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xDiff / yDiff;
		for (float y = ymin; y <= ymax; y += 1.0f) {
			float x = x1 + ((y - y1) * slope);
			Color color = Utils::blendColor(color1, color2, ((y - y1) / yDiff));
			image.setColor(x, y, color);
		}
	}
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