class Pixel {
public:
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