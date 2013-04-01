#ifndef __COLORIMAGE__H
#define __COLORIMAGE__H

class Color {
public:
	Color(float r = 0, float g = 0, float b = 0, float z = 0) : R(r), G(g), B(b){}
	// only for 0 to 255.
	unsigned char R, G, B;
    //unsigned int Z;

    Color blendColor(Color);
};

class ColorImage {
public:
    ColorImage();
    ~ColorImage();
    void init(int xSize, int ySize);
    void clear(Color background);
    Color getColor(int, int);
    void setColor(int, int, Color, float);
    void outputPPM(char *filename);

    int getWidth() { return xRes; }
    int getHeight() { return yRes; }
private:
    Color *pPixel;
    float* zbuffer;
    int xRes, yRes;
};

#endif