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

		maxZ = (z1>maxZ)?z1:maxZ;
		maxZ = (z2>maxZ)?z2:maxZ;
		maxZ = (z3>maxZ)?z3:maxZ;

		minZ = (z1<minZ)?z1:minZ;
		minZ = (z2<minZ)?z2:minZ;
		minZ = (z3<minZ)?z3:minZ;
	}

	float diffX = maxX - minX;
	float diffY = maxY - minY;
	float diffZ = maxZ - minZ;
	float rX = (float)(width)*0.8/diffX;
	float rY = (float)(width)*0.8/diffY;
	float rZ = (float)(width)*0.8/diffZ;
	float offX = (-minX);
	float offY = (-minY);
	float offZ = (-minZ);

	float r = (rX < rY)? rX : rY;
	r = (r < rZ)? r : rZ;

	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->scale(r, r, r, offX, offY, offZ);
	}


	if (!hasColor) {
		for (int i = 0 ; i < _size ; ++i) {
			_list[i]->setColor(minZ, maxZ);
		}
	}

	cout << "r = " << r << endl;
	 cout << "  " << minX << "  " << maxX << "  " << minY << "  " << maxY << "  " << minZ << "  " << maxZ << endl;
	 cout << "rX = " << rX << endl;
	 cout << "rY = " << rY << endl;
	 cout << "rZ = " << rZ << endl;
	 cout << "offset = " << offX << "  " << offY << "  " << offX << endl;
}

void Space::rotation(float a, float b, float c, int w) {
	a *= 3.14159/180.0f;
	b *= 3.14159/180.0f;
	c *= 3.14159/180.0f;
	cout << "start rotation: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->translation(-w/2, -w/2, -w/2);
		_list[i]->rotation(a, b, c);
		_list[i]->translation(w/2, w/2, w/2);
	}
	cout << "space::rotation finished." << endl;
}

void Space::translation(float x, float y, float z) {
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->translation(x,y,z);
	}
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
		cout << "drawTriangle: " << i << endl;
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

ColorImage Space::getImage(int width) {
	ColorImage image;
	image.init(width, width);
	normalize(width, width);
	rotation(90, 180, 0, width);
	// normalize(width,width);
	//translation(-50, -50, 0);
	projection();
	rasterization(image);

	return image;
}

void Space::setHasColor(bool b) {
	hasColor = b;
}