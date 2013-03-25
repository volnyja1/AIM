#include "Vertex.h"

class MyPolygon
{
public:
	MyPolygon();
	~MyPolygon();
	Vertex* selectedVertex(int _x, int _y);
	void drawPolygon();
	void hit(int _x, int _y);
	void move(int _x, int _y);
private:
	Vertex vertices[4];
};