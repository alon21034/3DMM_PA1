#include "Triangle.h"
#include "Space.h"
#include "ColorImage.h"

Space::Space(Triangle** list, int size) {

}

Space::~Space() {
	for (int i = 0 ; i < _size ; ++i) {
		delete _list[i];
	}
	delete _list;
}

void Space::normalize() {

}

void Space::rasterization() {

}

ColorImage Space::getImage(Vec3 vec, int width, int height) {
	ColorImage image;
	image.init(width, height);
	normalize();

	rasterization();
}