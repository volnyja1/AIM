#include <stdio.h>

class Vertex
{
public:
	Vertex();
	Vertex(int _x, int _y);
	~Vertex();
	void setVertex(int _x, int _y);
	bool isSelected();
	void setSelected(bool _selected);
	void hit(int _x, int _y);
	void move(int _x, int _y);
	void drawVertex();
	int getX();
	int getY();
private:
	bool selected;
	int x, y;
	int range;
};