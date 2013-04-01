#include "Utils.h"
#include <math.h>
#include <iostream>

using namespace std;

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

float Utils::inner(float a, float b, float r) {
	return a + (b-a)*r;
}

void Utils::rotation(float ax, float ay, float az, float& x, float& y, float& z) {

	float cosax = cos(ax);
	float cosbx = cos(ay);
	float coscx = cos(az);

	float sinax = sin(ax);
	float sinbx = sin(ay);
	float sincx = sin(az);

	float mat[3][3] = {
		{cosax * coscx		, cosbx * sincx + sinbx * sinax * coscx		, sinbx * sincx - cosbx * sinax * coscx},
		{-cosax * sincx		, cosbx * coscx - sinbx * sinax * sincx		, sinbx * coscx + cosbx * sinax * sincx},
		{sinax				, -sinbx * cosax 							, cosbx * cosax}
	};

	float xx = mat[0][0] * x + mat[0][1] * y + mat[0][2] * z;
	float yy = mat[1][0] * x + mat[1][1] * y + mat[1][2] * z;
	float zz = mat[2][0] * x + mat[2][1] * y + mat[2][2] * z;

	// for (int i = 0 ; i < 3 ; i++) {
	// 	for (int j = 0 ; j < 3 ; j++) {
	// 		cout << mat[i][j] << "  ";
	// 	}
	// 	cout << endl;
	// }

	x = xx;
	y = yy;
	z = zz;
}