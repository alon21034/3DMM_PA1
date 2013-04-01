#include "Triangle.h"
#include "Space.h"
#include "ColorImage.h"
#include <iostream>

using namespace std;

Space::Space(Triangle** list, int size) {
	_size = size;
	_list = list;
}

Space::~Space() {
	for (int i = 0 ; i < _size ; ++i) {
		delete _list[i];
	}
	delete _list;
}

void Space::normalize(int width, int height) {

	cout << "start normalization" << endl;

	// (TODO) find max, min x/y can be calculate when loading file.
	float maxX = 0, minX = INT_MAX, maxY = 0, minY = INT_MAX, maxZ = 0, minZ = INT_MAX;

	for (int i = 0 ; i < _size ; ++i) {
		float x1 = _list[i]->getX(1);
		float x2 = _list[i]->getX(2);
		float x3 = _list[i]->getX(3);

		//cout << "triangle(" << i << ") : " << x1 << " " << x2 << " " << x3 << endl;

		maxX = (x1>maxX)?x1:maxX;
		maxX = (x2>maxX)?x2:maxX;
		maxX = (x3>maxX)?x3:maxX;

		minX = (x1<minX)?x1:minX;
		minX = (x2<minX)?x2:minX;
		minX = (x3<minX)?x3:minX;

		float y1 = _list[i]->getY(1);
		float y2 = _list[i]->getY(2);
		float y3 = _list[i]->getY(3);

		maxY = (y1>maxY)?y1:maxY;
		maxY = (y2>maxY)?y2:maxY;
		maxY = (y3>maxY)?y3:maxY;

		minY = (y1<minY)?y1:minY;
		minY = (y2<minY)?y2:minY;
		minY = (y3<minY)?y3:minY;

		float z1 = _list[i]->getZ(1);
		float z2 = _list[i]->getZ(2);
		float z3 = _list[i]->getZ(3);

		maxZ = (z1>maxY)?z1:maxZ;
		maxZ = (z2>maxY)?z2:maxZ;
		maxZ = (z3>maxY)?z3:maxZ;

		minZ = (z1<minY)?z1:minZ;
		minZ = (z2<minY)?z2:minZ;
		minZ = (z3<minY)?z3:minZ;
	}

	float diffX = maxX - minX;
	float diffY = maxY - minY;
	float rX = (float)(width)*0.8/diffX;
	float rY = (float)(height)*0.8/diffY;
	float offX = - minX;
	float offY = - minY;

	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->scale(rX, rY, offX, offY);
	}


	if (!hasColor) {
		for (int i = 0 ; i < _size ; ++i) {
			_list[i]->setColor(minZ, maxZ	);
		}
	}
	// cout << "  " << minX << "  " << maxX << "  " << minY << "  " << maxY << endl;
	// cout << "rX = " << rX << endl;
	// cout << "rY = " << rY << endl;
	// cout << "offset = " << offX << "  " << offY << endl;
}

void Space::rotation(float a, float b, float c) {
	a *= 3.14159/180.0f;
	b *= 3.14159/180.0f;
	c *= 3.14159/180.0f;
	cout << "start rotation: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->rotation(a, b, c);
	}
	cout << "space::rotation finished." << endl;
}

void Space::projection() {
	cout << "start projection: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->projection();
	}
	cout << "space::projection finished." << endl;
}

void Space::rasterization(ColorImage& image) {
	cout << "start rasterization: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		//cout << "drawTriangle: " << i << endl;
		drawTriangle(image, _list[i]);
	}
	cout << "space::rasterization finished." << endl;
}

void Space::drawTriangle(ColorImage& image, Triangle* triangle) {
	// if (triangle->getOrientation()) {
	// 	return ;
	// }
	triangle->drawVertex(image);
	triangle->drawEdge(image);
	if (hasColor)
		triangle->fillColor(image);
}

ColorImage Space::getImage(int width, int height) {
	ColorImage image;
	image.init(width, height);
	rotation(0, 0, 0);
	normalize(width, height);
	projection();
	rasterization(image);

	return image;
}

void Space::setHasColor(bool b) {
	hasColor = b;
}