#ifndef __COLORIMAGE__H
#define __COLORIMAGE__H

class Pixel {
public:
	Pixel(float r = 0, float g = 0, float b = 0) : R(r), G(g), B(b){}
	// only for 0 to 255.
	unsigned char R, G, B;
};

class ColorImage {
    Pixel *pPixel;
    int xRes, yRes;
public:
    ColorImage();
    ~ColorImage();
    void init(int xSize, int ySize);
    void clear(Pixel background);
    Pixel readPixel(int x, int y);
    void writePixel(int x, int y, Pixel p);
    void outputPPM(char *filename);
};

#endif