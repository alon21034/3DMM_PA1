class Vertex {
public:
	Vertex();
	~Vertex();

	void setCoordinate(float, float, float);
	void setColor(float, float, float);

	void print();
private:
	float _x;
	float _y;
	float _z;

	float _r;
	float _g;
	float _b;
};