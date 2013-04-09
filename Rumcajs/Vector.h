#include "Vertex.h"

class Vector{
public:
	Vector();
	Vector(float _x, float _y);
	Vector(Vertex v);
	~Vector();
	void setVector(float _x, float _y);
	void addVector(Vector v);
	Vector addedVector(Vector v);
	Vector subtractedVector(Vector v);
	Vector perpendicularVector();
	float dotProduct(Vector v);
	float getX();
	float getY();
private:
	float x, y;
};