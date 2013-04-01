#ifndef __UTILS__H
#define __UTILS__H

#include "ColorImage.h"

class Utils {
public:
	static int round(float f);
	static float getSlope(float, float, float, float);
	static Color blendColor(Color, Color, float);
};

#endif