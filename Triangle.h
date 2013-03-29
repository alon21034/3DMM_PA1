#ifndef __TRIANGLE__H
#define __TRIANGLE__H

#include "Vertex.h"

class Triangle {
public:
	Triangle(Vertex*, Vertex*, Vertex*);
private:
	Vertex* _v1;
	Vertex* _v2;
	Vertex* _v3;
};

#endif