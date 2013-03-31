#ifndef __TRIANGLE__H
#define __TRIANGLE__H

#include "Vertex.h"

class Triangle {
public:
	Triangle(Vertex*, Vertex*, Vertex*);

	Vertex* getVertex(int);

	void drawVertex(ColorImage&);
	void drawEdge(ColorImage&);
	void fill(ColorImage&);

	void scale(float, float, float, float);
	void projection();

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

private:

	void drawLine(ColorImage&, Vertex*, Vertex*);

	Vertex* _v1;
	Vertex* _v2;
	Vertex* _v3;
};

#endif