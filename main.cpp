#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Vertex.h"

using namespace std;

#define VERTEX_IDENTIFIER "Vertices"
#define COLOR_IDENTIFIER "Colors"
#define TRIANGLE_IDENTIFIER "Triangle_List"

#define VERTEX_MODE 1
#define COLOR_MODE 2

int main(int argc, char** argv) {
	char* inputFilePath;
	char* outputFilePath;
	if (argc < 3) {
		inputFilePath = new char[20];
		inputFilePath = "Models/cube.txt";

		outputFilePath = new char[20];
		outputFilePath = "result_image,ppm";
	} else {
		inputFilePath = argv[1];
		outputFilePath = argv[2];
	}
	FILE* inputFile = fopen(inputFilePath, "r");

	char str[10];
	int mode = VERTEX_MODE;
	Vertex* vertices = NULL;
	int vertexNum;

	// read identifier
	while(fscanf(inputFile, "%s", str)) {
		if (strcmp(str, VERTEX_IDENTIFIER) == 0) {
			// read vertices

			fscanf(inputFile, "%d", &vertexNum);
			printf("start reading vertices(%d): \n", vertexNum);
			// allocate memory to save vertices
			vertices = new Vertex[vertexNum];

			for (int i = 0; i < vertexNum; ++i) {
				cout << i <<endl;
				float x, y, z;
				fscanf(inputFile, "%f %f %f", &x, &y, &z);
				vertices[i].setCoordinate(x, y, z);
			}
		} else if (strcmp(str, COLOR_IDENTIFIER) == 0) {
			// read color
			if (vertices == NULL) {
				printf("should read vertices first.\n");
				break;
			}
			printf("start reading colors\n");

			for (int i = 0; i < vertexNum; ++i) {
				float r, g, b;
				fscanf(inputFile, "%f %f %f", &r, &g, &b);
				vertices[i].setColor(r, g, b);
			}
		} else if (strcmp(str, TRIANGLE_IDENTIFIER) == 0) {
			// read triangles
			break;
		} else {
			printf("error: stop reading file\n");
			break;
		}
	}
	printf("finished reading input file");

	// initial color image.

	// for output ppm image file
	FILE* outFile = fopen(outputFilePath, "w");


	fprintf("P3");

}