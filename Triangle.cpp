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
	image.setColor(_v1->getX(), _v1->getY(), _v1->getColor(), _v1->getZ());
	image.setColor(_v2->getX(), _v2->getY(), _v2->getColor(), _v2->getZ());
	image.setColor(_v3->getX(), _v3->getY(), _v3->getColor(), _v3->getZ());
	Color color = _v1->getColor();
	cout << "x: " << _v1->getX() << ", y: " << _v1->getY() << ", c: " << (int)color.R << " " << (int)color.G << " " << (int)color.B << endl;
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

	float z1 = v1->getZ();
	float z2 = v2->getZ();

	Color color1 = v1->getColor();
	Color color2 = v2->getColor();

	float xDiff = (x2 - x1);
	float yDiff = (y2 - y1);

	if (xDiff == 0.0f && yDiff == 0.0f) {
		image.setColor(x1, y1, color1, z1);
		return;
	}

	if (fabs(xDiff) > fabs(yDiff)) {
		// horizontal
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
			float z = z1 + fabs(((x - xmin)/xDiff));
			Color color = Utils::blendColor(color1, color2, ((x - x1) / xDiff));
			image.setColor(x, y, color, z);
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
			float z = z1 + fabs(((y - ymin)/yDiff));
			Color color = Utils::blendColor(color1, color2, ((y - y1) / yDiff));
			image.setColor(x, y, color, z);
		}
	}
}

void Triangle::fillColor(ColorImage& image) {

	float y1 = _v1->getY();
	float y2 = _v2->getY();
	float y3 = _v3->getY();

	if (y1 < y2 && y1 < y3) {
		if (y2 < y3) {
			drawSpansBetweenEdges(image, _v1, _v3, _v1, _v2);
			drawSpansBetweenEdges(image, _v1, _v3, _v2, _v3);
		} else {
			drawSpansBetweenEdges(image, _v1, _v2, _v1, _v3);
			drawSpansBetweenEdges(image, _v1, _v2, _v3, _v2);
		}
	} else if (y2 < y3 && y2 < y1) {
		if (y1 < y3) {
			drawSpansBetweenEdges(image, _v2, _v3, _v2, _v1);
			drawSpansBetweenEdges(image, _v2, _v3, _v1, _v3);
		} else {
			drawSpansBetweenEdges(image, _v2, _v1, _v2, _v3);
			drawSpansBetweenEdges(image, _v2, _v1, _v3, _v1);
		}
	} else {
		if (y1 < y2) {
			drawSpansBetweenEdges(image, _v3, _v2, _v3, _v1);
			drawSpansBetweenEdges(image, _v3, _v2, _v1, _v2);
		} else {
			drawSpansBetweenEdges(image, _v3, _v1, _v3, _v2);
			drawSpansBetweenEdges(image, _v3, _v1, _v2, _v1);
		}
	}

}

void Triangle::drawSpan(ColorImage& image, Span &span, int y) {
	float xdiff = span.X2 - span.X1;
	if((int)xdiff == 0)
		return;

	if (span.X2 < span.X1) {
		span.switchValue();
	}

	float factor = 0.0f;
	float factorStep = 1.0f / xdiff;

	// draw each pixel in the span
	for(float x = span.X1; x < span.X2; x+=1.0f) {
		image.setColor(x, y, Utils::blendColor(span.color1, span.color2, factor), Utils::inner(span.Z1, span.Z2, factor));
		factor += factorStep;
	}
}

void Triangle::drawSpansBetweenEdges(ColorImage& image, Vertex* v1, Vertex* v2, Vertex* v3, Vertex* v4) {

	float yDiff1 = v2->getY() - v1->getY();
	float yDiff2 = v4->getY() - v3->getY();

	if((int)v2->getY() == (int)v1->getY() || (int)v4->getY() == (int)v3->getY())
		return;

	// calculate differences between the x coordinates
	// and colors of the points of the edges
	float xDiff1 = v2->getX() - v1->getX();
	float xDiff2 = v4->getX() - v3->getX();

	Color color11 = v1->getColor();
	Color color12 = v2->getColor();
	Color color21 = v3->getColor();
	Color color22 = v4->getColor();

	float z1 = v1->getZ();
	float z2 = v2->getZ();
	float z3 = v3->getZ();
	float z4 = v4->getZ();

	// calculate factors to use for interpolation
	// with the edges and the step values to increase
	// them by after drawing each span
	// float factor1 = (v3->getY() - v1->getY()) / yDiff1;
	// float factorStep1 = 1.0f / yDiff1;
	// float factor2 = 0.0f;
	// float factorStep2 = 1.0f / yDiff2;

	// loop through the lines between the edges and draw spans
	for(float y = v3->getY(); y <= v4->getY(); y+=1.0f) {

		float factor1 = (y - v1->getY()) / yDiff1;
		float factor2 = (y - v3->getY()) / yDiff2;

		// create and draw span
		Span span(Utils::blendColor(color11, color12, factor1),
		          v1->getX() + (xDiff1 * factor1),
		          Utils::inner(z1, z2, factor1),
		          Utils::blendColor(color21, color22, factor2),
		          v3->getX() + (xDiff2 * factor2),
		          Utils::inner(z3, z4, factor2));
		drawSpan(image, span, y);

		// increase factors
		// factor1 += factorStep1;
		// factor2 += factorStep2;
	}
}

void Triangle::scale(float rx, float ry, float rz, float ox, float oy, float oz) {
	_v1->scale(rx, ry, rz, ox, oy, oz);
	_v2->scale(rx, ry, rz, ox, oy, oz);
	_v3->scale(rx, ry, rz, ox, oy, oz);
}

void Triangle::translation(float ox, float oy, float oz) {
	_v1->translation(ox, oy, oz);
	_v2->translation(ox, oy, oz);
	_v3->translation(ox, oy, oz);
}

void Triangle::rotation(float a, float b, float c) {
	_v1->rotation(a, b, c);
	_v2->rotation(a, b, c);
	_v3->rotation(a, b, c);
}

void Triangle::projection() {
	_v1->projection();
	_v2->projection();
	_v3->projection();
}

bool Triangle::getOrientation() {
	float vec1x, vec1y, vec1z;
	float vec2x, vec2y, vec2z;

	vec1x = _v2->getX() - _v1->getX();
	vec1y = _v2->getY() - _v1->getY();
	vec1z = _v2->getZ() - _v2->getZ();

	vec2x = _v3->getX() - _v1->getX();
	vec2y = _v3->getY() - _v1->getY();
	vec2z = _v3->getZ() - _v1->getZ();

	float vx, vy, vz;
	vz = vec1x * vec2y - vec1y * vec2x;

	return vz >= 0;
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