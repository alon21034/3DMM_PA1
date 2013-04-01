#include "Utils.h"
#include <math.h>

int Utils::round(float f) {
	return (int) f;
}

Color Utils::blendColor(Color c1, Color c2, float r) {
	Color c;
	c.R = c1.R + (c2.R - c1.R) * r;
	c.G = c1.G + (c2.G - c1.G) * r;
	c.B = c1.B + (c2.B - c1.B) * r;
	return c;
}