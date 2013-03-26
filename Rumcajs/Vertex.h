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
	void setSelectable(bool _selectable);
	void select(int _x, int _y);
	void deselect(int _x, int _y);
	void hit(int _x, int _y);
	void move(int _x, int _y);
	void drawVertex();
	int getX();
	int getY();
private:
	bool selected, selectable;
	int x, y;
	int range;
};