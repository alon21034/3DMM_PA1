#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ColorImage.h"
#include <iostream>

using namespace std;

ColorImage::ColorImage(){
    pPixel = 0;
}

ColorImage::~ColorImage(){
    if (pPixel) delete[] pPixel;
    pPixel = 0;
}

void ColorImage::init(int xSize, int ySize){
    Color p;
    xRes = xSize;
    yRes = ySize;
    pPixel = new Color[xSize*ySize];
    clear(p);
}

void ColorImage::clear(Color background){
    int i;

    if (! pPixel) return;
    for (i=0; i<xRes*yRes; i++) pPixel[i] = background;
}

Color ColorImage::getColor(int x, int y){
    assert(pPixel); // die if image not initialized
    return pPixel[x + y*yRes];
}

void ColorImage::setColor(int x, int y, Color color){
    Color orig = pPixel[x + y*yRes];
    pPixel[x + y*yRes] = color;
}

void ColorImage::outputPPM(char *filename){
    FILE *outFile = fopen(filename, "w");

    assert(outFile); // die if file can't be opened

    fprintf(outFile, "P6 %d %d 255\n", xRes, yRes);
    fwrite(pPixel, 1, 3*xRes*yRes, outFile );

    fclose(outFile);
}

Color Color::blendColor(Color c) {
    //return (this->Z > c.Z)? c : *this;
}