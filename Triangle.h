#ifndef __TRIANGLE__H
#define __TRIANGLE__H

#include "Vertex.h"
#include "Utils.h"

class Span {
public:
	Color color1, color2;
	float X1, X2;
	float Z1, Z2;

	Span(const Color &c1, float x1, float z1, const Color &c2, float x2, float z2) {
		if(x1 < x2) {
			color1 = c1;
			X1 = x1;
			color2 = c2;
			X2 = x2;
			Z1 = z1;
			Z2 = z2;
		} else {
			color1 = c2;
			X1 = x2;
			color2 = c1;
			X2 = x1;
			Z1 = z1;
			Z2 = z2;
		}
	}

	void switchValue() {
		float temp = X1;
		X1 = X2;
		X2 = temp;

		Color t = color1;
		color1 = color2;
		color2 = t;

		float tempz = Z1;
		Z1 = Z2;
		Z2 = tempz;
	}
};

class Triangle {
public:
	Triangle(Vertex*, Vertex*, Vertex*);

	Vertex* getVertex(int);

	void drawVertex(ColorImage&);
	void drawEdge(ColorImage&);
	void fillColor(ColorImage&);

	void scale(float, float, float, float, float, float);
	void rotation(float, float, float);
	void projection();
	void translation(float, float, float);

	bool getOrientation();

	float getX(int i) {
		switch (i) {
			case 1: return _v1->getX();
			case 2: return _v2->getX();
			case 3: return _v3->getX();
			default: return 0;
		}
	}

	float getY(int i) {
		switch (i) {
			case 1: return _v1->getY();
			case 2: return _v2->getY();
			case 3: return _v3->getY();
			default: return 0;
		}		
	}

	float getZ(int i) {
		switch (i) {
			case 1: return _v1->getZ();
			case 2: return _v2->getZ();
			case 3: return _v3->getZ();
			default: return 0;
		}		
	}

	void setColor(float a, float b);	
private:
	void drawLine(ColorImage&, Vertex*, Vertex*);
	void drawSpan(ColorImage&, Span&, int);
	void drawSpansBetweenEdges(ColorImage&, Vertex*, Vertex*, Vertex*, Vertex*);

	Vertex* _v1;
	Vertex* _v2;
	Vertex* _v3;
};

#endif