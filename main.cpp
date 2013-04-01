#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Vertex.h"
#include "ColorImage.h"
#include "Triangle.h"
#include "Space.h"

using namespace std;

#define VERTEX_IDENTIFIER "Vertices"
#define COLOR_IDENTIFIER "Colors"
#define TRIANGLE_IDENTIFIER "Triangle_list"

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

	char str[100];
	int mode = VERTEX_MODE;
	Vertex** vertexList = NULL;
	Triangle** triangleList = NULL;
	int vertexNum;
	int triangleNum;

	// read identifier
	while(fscanf(inputFile, "%s", str)) {
		cout << str << endl;
		if (strcmp(str, VERTEX_IDENTIFIER) == 0) {
			// read vertex

			fscanf(inputFile, "%d", &vertexNum);
			printf("start reading vertex(%d)\n", vertexNum);
			// allocate memory to save vertexList
			vertexList = new Vertex*[vertexNum];

			for (int i = 0; i < vertexNum; ++i) {
				float x, y, z;
				fscanf(inputFile, "%f %f %f", &x, &y, &z);
				vertexList[i] = new Vertex(x,y,z);
			}
		} else if (strcmp(str, COLOR_IDENTIFIER) == 0) {
			// read color
			if (vertexList == NULL) {
				printf("should read vertex first.\n");
				break;
			}
			printf("start reading colors\n");
			int colorNum;
			fscanf(inputFile, "%d", &colorNum);
			if (colorNum != vertexNum) {
				cout << "error" << endl;
				break;
			}
			for (int i = 0; i < vertexNum; ++i) {
				float r, g, b;
				fscanf(inputFile, "%f %f %f", &r, &g, &b);
				//cout << i << "  " << r << " " << g << " " << b << endl;
				vertexList[i]->setColor(r*255,g*255,b*255);
			}
		} else if (strcmp(str, TRIANGLE_IDENTIFIER) == 0) {
			// read triangles
			if (vertexList == NULL) {
				printf("should read vertex first.\n");
				break;
			}
			fscanf(inputFile, "%d", &triangleNum);
			printf("strat reading triangles(%d)\n", triangleNum);

			
			triangleList = new Triangle*[triangleNum];

			for (int i = 0 ; i < triangleNum ; ++i) {
				int a, b, c;
				fscanf(inputFile, "%d %d %d", &a, &b, &c);
				triangleList[i] = new Triangle(vertexList[a], vertexList[b], vertexList[c]);
			}
			break;
		} else {
			printf("error: stop reading file\n");
			return 0;
		}
	}
	printf("finished reading input file\n");

	Space* space = new Space(triangleList, triangleNum);
	ColorImage image = space->getImage(500, 500);
	image.outputPPM("result.ppm");
    /**/
}