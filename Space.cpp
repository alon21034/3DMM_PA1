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

void Space::normalize(int width, int height, int xx, int yy) {

	//cout << "start normalization" << endl;

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
		//_list[i]->translation(offX, offY, offZ);
		_list[i]->scale(r, r, r, 0, 0 ,0);
		_list[i]->translation(xx, yy, 0);
	}


	if (!hasColor) {
		for (int i = 0 ; i < _size ; ++i) {
			_list[i]->setColor(minZ * r, maxZ * r);
		}
	}

	// cout << "r = " << r << endl;
	// cout << "  " << minX << "  " << maxX << "  " << minY << "  " << maxY << "  " << minZ << "  " << maxZ << endl;
	// cout << "rX = " << rX << endl;
	// cout << "rY = " << rY << endl;
	// cout << "rZ = " << rZ << endl;
	// cout << "offset = " << offX << "  " << offY << "  " << offX << endl;
}

void Space::rotation(float a, float b, float c, int w) {
	a *= 3.14159/180.0f;
	b *= 3.14159/180.0f;
	c *= 3.14159/180.0f;
	//cout << "start rotation: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		//_list[i]->translation(-w/2, -w/2, -w/2);
		_list[i]->rotation(a, b, c);
		//_list[i]->translation(w/2, w/2, w/2);
	}
	//cout << "space::rotation finished." << endl;
}

void Space::translation(float x, float y, float z) {
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->translation(x,y,z);
	}
}

void Space::projection() {
	//cout << "start projection: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		_list[i]->projection();
	}
	//cout << "space::projection finished." << endl;
}

void Space::rasterization(ColorImage& image) {
	//cout << "start rasterization: " << endl;
	for (int i = 0 ; i < _size ; ++i) {
		//cout << "drawTriangle: " << i << endl;
		drawTriangle(image, _list[i]);
	}
	//cout << "space::rasterization finished." << endl;
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

ColorImage Space::getImage(int width, int index) {
	ColorImage image;
	image.init(width, width);
	switch (index) {
		case 0: rotation(150, 180, 0, width); break;
		case 1: rotation(10, 170, 0, width); break;
		case 2: rotation(30, 120, 20, width); break;
		case 3: rotation(40, 150, 30, width); break;
		case 4: rotation(0, 180, 0, width); break;
		case 5: rotation(0, 120, 0, width); break;
		case 6: rotation(0, 180, 0, width); break;
		case 7: rotation(90, 180, 90, width); break;
		case 8: rotation(10, 10, 10, width); break;
		case 9: rotation(0, -90, 0, width); break;
		case 10: rotation(70, 180, 0, width); break;
		case 11: rotation(30, 30, 0, width); break;
		default: rotation(0,0,0,width); break;
	}

	switch (index) {
		case 0: normalize(width, width, 0.5*width, 0.6*width); break;
		case 1: normalize(width, width, 0.5*width, 0.5*width); break;
		case 2: normalize(width, width, 0.5*width, 0.5*width); break;
		case 3: normalize(width, width, 0.45*width, 0.45*width); break;
		case 4: normalize(width, width, 0.5*width, width); break;
		case 5: normalize(width, width, 0.5*width, 0.45*width); break;
		case 6: normalize(width, width, 0.5*width, width); break;
		case 7: normalize(width, width, 0.5*width, 0.5*width); break;
		case 8: normalize(width, width, 0.5*width, 0.5*width); break;
		case 9: normalize(width, width, 1.1*width, 0.75*width); break;
		case 10: normalize(width, width, 0.5*width, 0.5*width); break;
		case 11: normalize(width, width, 0.5*width, 0.5*width); break;
		default: normalize(width, width,0.5*width, 0.5*width); break;
	}
	projection();
	rasterization(image);

	return image;
}

void Space::setHasColor(bool b) {
	hasColor = b;
}