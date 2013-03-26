#include "Vertex.h"

class MyPolygon
{
public:
	MyPolygon();
	MyPolygon(Vertex v0, Vertex v1, Vertex v2, Vertex v3);
	MyPolygon(Vertex v0, Vertex v1, Vertex v2, Vertex v3,float _texX0, float _texY0, float _texX1, float _texY1);
	~MyPolygon();
	void drawPolygon();
	void hit(int _x, int _y);
	void select(int _x, int _y);
	void deselect(int _x, int _y);
	void move(int _x, int _y);
	Vertex getV0();
	Vertex getV1();
	Vertex getV2();
	Vertex getV3();
	void setTex(float _texX0, float _texY0, float _texX1, float _texY1);
	float getTexX0();
	float getTexX1();
	float getTexY0();
	float getTexY1();
private:
	Vertex vertices[4];
	float texX0, texY0, texX1, texY1;
};